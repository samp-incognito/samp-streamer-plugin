/*
 * Copyright (C) 2017 Incognito
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "main.h"

#include "chunk-streamer.h"
#include "core.h"

ChunkStreamer::ChunkStreamer()
{
	chunkSize[STREAMER_TYPE_OBJECT] = 100;
	chunkSize[STREAMER_TYPE_MAP_ICON] = 100;
	chunkSize[STREAMER_TYPE_3D_TEXT_LABEL] = 100;
	chunkStreamingEnabled = false;
}

std::size_t ChunkStreamer::getChunkSize(int type)
{
	switch (type)
	{
		case STREAMER_TYPE_OBJECT:
		{
			return chunkSize[STREAMER_TYPE_OBJECT];
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			return chunkSize[STREAMER_TYPE_MAP_ICON];
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			return chunkSize[STREAMER_TYPE_3D_TEXT_LABEL];
		}
	}
	return 0;
}

bool ChunkStreamer::setChunkSize(int type, std::size_t value)
{
	if (value > 0)
	{
		switch (type)
		{
			case STREAMER_TYPE_OBJECT:
			{
				chunkSize[STREAMER_TYPE_OBJECT] = value;
				return true;
			}
			case STREAMER_TYPE_MAP_ICON:
			{
				chunkSize[STREAMER_TYPE_MAP_ICON] = value;
				return true;
			}
			case STREAMER_TYPE_3D_TEXT_LABEL:
			{
				chunkSize[STREAMER_TYPE_3D_TEXT_LABEL] = value;
				return true;
			}
		}
	}
	return false;
}

void ChunkStreamer::performPlayerChunkUpdate(Player &player, bool automatic)
{
	for (std::vector<int>::const_iterator t = core->getData()->typePriority.begin(); t != core->getData()->typePriority.end(); ++t)
	{
		switch (*t)
		{
			case STREAMER_TYPE_OBJECT:
			{
				if (player.processingChunks[STREAMER_TYPE_OBJECT])
				{
					streamObjects(player, automatic);
				}
				break;
			}
			case STREAMER_TYPE_MAP_ICON:
			{
				if (player.processingChunks[STREAMER_TYPE_MAP_ICON])
				{
					streamMapIcons(player, automatic);
				}
				break;
			}
			case STREAMER_TYPE_3D_TEXT_LABEL:
			{
				if (player.processingChunks[STREAMER_TYPE_3D_TEXT_LABEL])
				{
					streamTextLabels(player, automatic);
				}
				break;
			}
		}
	}
}

void ChunkStreamer::discoverMapIcons(Player &player, const std::vector<SharedCell> &cells)
{
	for (std::vector<SharedCell>::const_iterator c = cells.begin(); c != cells.end(); ++c)
	{
		for (std::unordered_map<int, Item::SharedMapIcon>::const_iterator m = (*c)->mapIcons.begin(); m != (*c)->mapIcons.end(); ++m)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (doesPlayerSatisfyConditions(m->second->players, player.playerId, m->second->interiors, player.interiorId, m->second->worlds, player.worldId, m->second->areas, player.internalAreas, m->second->inverseAreaChecking))
			{
				if (m->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
				{
					distance = std::numeric_limits<float>::infinity() * -1.0f;
				}
				else
				{
					distance = static_cast<float>(boost::geometry::comparable_distance(player.position, Eigen::Vector3f(m->second->position + m->second->positionOffset)));
				}
			}
			std::unordered_map<int, int>::iterator i = player.internalMapIcons.find(m->first);
			if (distance < (m->second->comparableStreamDistance * player.radiusMultipliers[STREAMER_TYPE_MAP_ICON]))
			{
				if (i == player.internalMapIcons.end())
				{
					player.discoveredMapIcons.insert(Item::Bimap<Item::SharedMapIcon>::Type::value_type(std::make_tuple(m->second->priority, distance), std::make_tuple(m->first, m->second)));
				}
				else
				{
					if (m->second->cell)
					{
						player.visibleCell->mapIcons.insert(*m);
					}
					player.existingMapIcons.insert(Item::Bimap<Item::SharedMapIcon>::Type::value_type(std::make_tuple(m->second->priority, distance), std::make_tuple(m->first, m->second)));
				}
			}
			else
			{
				if (i != player.internalMapIcons.end())
				{
					player.removedMapIcons.insert(i->first);
				}
			}
		}
	}
	if (!player.discoveredMapIcons.empty() || !player.removedMapIcons.empty())
	{
		player.processingChunks.set(STREAMER_TYPE_MAP_ICON);
	}
}

void ChunkStreamer::streamMapIcons(Player &player, bool automatic)
{
	if (!automatic || ++player.chunkTickCount[STREAMER_TYPE_MAP_ICON] >= player.chunkTickRate[STREAMER_TYPE_MAP_ICON])
	{
		std::size_t chunkCount = 0;
		if (!player.removedMapIcons.empty())
		{
			std::unordered_set<int>::iterator r = player.removedMapIcons.begin();
			while (r != player.removedMapIcons.end())
			{
				if (automatic && ++chunkCount > chunkSize[STREAMER_TYPE_MAP_ICON])
				{
					break;
				}
				std::unordered_map<int, int>::iterator i = player.internalMapIcons.find(*r);
				if (i != player.internalMapIcons.end())
				{
					ompgdk::RemovePlayerMapIcon(player.playerId, i->second);
					std::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(*r);
					if (m != core->getData()->mapIcons.end())
					{
						if (m->second->streamCallbacks)
						{
							streamOutCallbacks.push_back(std::make_tuple(STREAMER_TYPE_MAP_ICON, *r, player.playerId));
						}
					}
					player.mapIconIdentifier.remove(i->second, player.internalMapIcons.size());
					player.internalMapIcons.erase(i);
				}
				r = player.removedMapIcons.erase(r);
			}
		}
		else
		{
			Item::Bimap<Item::SharedMapIcon>::Type::left_iterator d = player.discoveredMapIcons.left.begin();
			while (d != player.discoveredMapIcons.left.end())
			{
				if (automatic && ++chunkCount > chunkSize[STREAMER_TYPE_MAP_ICON])
				{
					break;
				}
				std::unordered_map<int, int>::iterator i = player.internalMapIcons.find(std::get<1>(d->second)->mapIconId);
				if (i != player.internalMapIcons.end())
				{
					d = player.discoveredMapIcons.left.erase(d);
					continue;
				}
				if (player.internalMapIcons.size() == player.maxVisibleMapIcons)
				{
					Item::Bimap<Item::SharedMapIcon>::Type::left_reverse_iterator e = player.existingMapIcons.left.rbegin();
					if (e != player.existingMapIcons.left.rend())
					{
						if (std::get<0>(e->first) < std::get<0>(d->first) || (std::get<1>(e->first) > STREAMER_STATIC_DISTANCE_CUTOFF && std::get<1>(d->first) < std::get<1>(e->first)))
						{
							std::unordered_map<int, int>::iterator j = player.internalMapIcons.find(std::get<0>(e->second));
							if (j != player.internalMapIcons.end())
							{
								ompgdk::RemovePlayerMapIcon(player.playerId, j->second);
								if (std::get<1>(e->second)->streamCallbacks)
								{
									streamOutCallbacks.push_back(std::make_tuple(STREAMER_TYPE_MAP_ICON, std::get<0>(e->second), player.playerId));
								}
								player.mapIconIdentifier.remove(j->second, player.internalMapIcons.size());
								player.internalMapIcons.erase(j);
							}
							if (std::get<1>(e->second)->cell)
							{
								player.visibleCell->mapIcons.erase(std::get<0>(e->second));
							}
							Item::Bimap<Item::SharedMapIcon>::Type::left_iterator f = e.base().base();
							player.existingMapIcons.left.erase(--f);
						}
					}
					if (player.internalMapIcons.size() == player.maxVisibleMapIcons)
					{
						player.discoveredMapIcons.clear();
						break;
					}
				}
				int internalId = player.mapIconIdentifier.get();
				ompgdk::SetPlayerMapIcon(player.playerId, internalId, std::get<1>(d->second)->position[0], std::get<1>(d->second)->position[1], std::get<1>(d->second)->position[2], std::get<1>(d->second)->type, std::get<1>(d->second)->color, std::get<1>(d->second)->style);
				if (std::get<1>(d->second)->streamCallbacks)
				{
					streamInCallbacks.push_back(std::make_tuple(STREAMER_TYPE_MAP_ICON, std::get<1>(d->second)->mapIconId, player.playerId));
				}
				player.internalMapIcons.insert(std::make_pair(std::get<1>(d->second)->mapIconId, internalId));
				if (std::get<1>(d->second)->cell)
				{
					player.visibleCell->mapIcons.insert(std::make_pair(std::get<0>(d->second), std::get<1>(d->second)));
				}
				d = player.discoveredMapIcons.left.erase(d);
			}
		}
		player.chunkTickCount[STREAMER_TYPE_MAP_ICON] = 0;
	}
	if (player.discoveredMapIcons.empty() && player.removedMapIcons.empty())
	{
		player.existingMapIcons.clear();
		player.processingChunks.reset(STREAMER_TYPE_MAP_ICON);
	}
}

void ChunkStreamer::discoverObjects(Player &player, const std::vector<SharedCell> &cells)
{
	for (std::vector<SharedCell>::const_iterator c = cells.begin(); c != cells.end(); ++c)
	{
		for (std::unordered_map<int, Item::SharedObject>::const_iterator o = (*c)->objects.begin(); o != (*c)->objects.end(); ++o)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (doesPlayerSatisfyConditions(o->second->players, player.playerId, o->second->interiors, player.interiorId, o->second->attach ? o->second->attach->worlds : o->second->worlds, player.worldId, o->second->areas, player.internalAreas, o->second->inverseAreaChecking))
			{
				if (o->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
				{
					distance = std::numeric_limits<float>::infinity() * -1.0f;
				}
				else
				{
					if (o->second->attach)
					{
						distance = static_cast<float>(boost::geometry::comparable_distance(player.position, o->second->attach->position)) + std::numeric_limits<float>::epsilon();
					}
					else
					{
						distance = static_cast<float>(boost::geometry::comparable_distance(player.position, Eigen::Vector3f(o->second->position + o->second->positionOffset)));
					}
				}
			}
			std::unordered_map<int, int>::iterator i = player.internalObjects.find(o->first);
			if (distance < (o->second->comparableStreamDistance * player.radiusMultipliers[STREAMER_TYPE_OBJECT]))
			{
				if (i == player.internalObjects.end())
				{
					player.discoveredObjects.insert(Item::Bimap<Item::SharedObject>::Type::value_type(std::make_tuple(o->second->priority, distance), std::make_tuple(o->first, o->second)));
				}
				else
				{
					if (o->second->cell)
					{
						player.visibleCell->objects.insert(*o);
					}
					player.existingObjects.insert(Item::Bimap<Item::SharedObject>::Type::value_type(std::make_tuple(o->second->priority, distance), std::make_tuple(o->first, o->second)));
				}
			}
			else
			{
				if (i != player.internalObjects.end())
				{
					player.removedObjects.insert(i->first);
				}
			}
		}
	}
	if (!player.discoveredObjects.empty() || !player.removedObjects.empty())
	{
		player.processingChunks.set(STREAMER_TYPE_OBJECT);
	}
}

void ChunkStreamer::streamObjects(Player &player, bool automatic)
{
	if (!automatic || ++player.chunkTickCount[STREAMER_TYPE_OBJECT] >= player.chunkTickRate[STREAMER_TYPE_OBJECT])
	{
		std::size_t chunkCount = 0;
		if (!player.removedObjects.empty())
		{
			std::unordered_set<int>::iterator r = player.removedObjects.begin();
			while (r != player.removedObjects.end())
			{
				if (automatic && ++chunkCount > chunkSize[STREAMER_TYPE_OBJECT])
				{
					break;
				}
				std::unordered_map<int, int>::iterator i = player.internalObjects.find(*r);
				if (i != player.internalObjects.end())
				{
					ompgdk::DestroyPlayerObject(player.playerId, i->second);
					std::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(*r);
					if (o != core->getData()->objects.end())
					{
						if (o->second->streamCallbacks)
						{
							streamOutCallbacks.push_back(std::make_tuple(STREAMER_TYPE_OBJECT, *r, player.playerId));
						}
					}
					player.internalObjects.erase(i);
				}
				r = player.removedObjects.erase(r);
			}
		}
		else
		{
			bool streamingCanceled = false;
			Item::Bimap<Item::SharedObject>::Type::left_iterator d = player.discoveredObjects.left.begin();
			while (d != player.discoveredObjects.left.end())
			{
				if (automatic && ++chunkCount > chunkSize[STREAMER_TYPE_OBJECT])
				{
					break;
				}
				std::unordered_map<int, int>::iterator i = player.internalObjects.find(std::get<1>(d->second)->objectId);
				if (i != player.internalObjects.end())
				{
					d = player.discoveredObjects.left.erase(d);
					continue;
				}
				int internalBaseId = INVALID_STREAMER_ID;
				if (std::get<1>(d->second)->attach)
				{
					if (std::get<1>(d->second)->attach->object != INVALID_STREAMER_ID)
					{
						std::unordered_map<int, int>::iterator j = player.internalObjects.find(std::get<1>(d->second)->attach->object);
						if (j == player.internalObjects.end())
						{
							d = player.discoveredObjects.left.erase(d);
							continue;
						}
						internalBaseId = j->second;
					}
				}
				if (player.internalObjects.size() == player.currentVisibleObjects)
				{
					Item::Bimap<Item::SharedObject>::Type::left_reverse_iterator e = player.existingObjects.left.rbegin();
					if (e != player.existingObjects.left.rend())
					{
						if (std::get<0>(e->first) < std::get<0>(d->first) || (std::get<1>(e->first) > STREAMER_STATIC_DISTANCE_CUTOFF && std::get<1>(d->first) < std::get<1>(e->first)))
						{
							std::unordered_map<int, int>::iterator j = player.internalObjects.find(std::get<0>(e->second));
							if (j != player.internalObjects.end())
							{
								ompgdk::DestroyPlayerObject(player.playerId, j->second);
								if (std::get<1>(e->second)->streamCallbacks)
								{
									streamOutCallbacks.push_back(std::make_tuple(STREAMER_TYPE_OBJECT, std::get<0>(e->second), player.playerId));
								}
								player.internalObjects.erase(j);
							}
							if (std::get<1>(e->second)->cell)
							{
								player.visibleCell->objects.erase(std::get<0>(e->second));
							}
							Item::Bimap<Item::SharedObject>::Type::left_iterator f = e.base().base();
							player.existingObjects.left.erase(--f);
						}
					}
				}
				if (player.internalObjects.size() == player.maxVisibleObjects)
				{
					streamingCanceled = true;
					break;
				}
				int internalId = ompgdk::CreatePlayerObject(player.playerId, std::get<1>(d->second)->modelId, std::get<1>(d->second)->position[0], std::get<1>(d->second)->position[1], std::get<1>(d->second)->position[2], std::get<1>(d->second)->rotation[0], std::get<1>(d->second)->rotation[1], std::get<1>(d->second)->rotation[2], std::get<1>(d->second)->drawDistance);
				if (internalId == INVALID_OBJECT_ID)
				{
					streamingCanceled = true;
					break;
				}
				if (std::get<1>(d->second)->streamCallbacks)
				{
					streamInCallbacks.push_back(std::make_tuple(STREAMER_TYPE_OBJECT, std::get<0>(d->second), player.playerId));
				}
				if (std::get<1>(d->second)->attach)
				{
					if (internalBaseId != INVALID_STREAMER_ID)
					{
						ompgdk::AttachPlayerObjectToObject(player.playerId, internalId, internalBaseId, std::get<1>(d->second)->attach->positionOffset[0], std::get<1>(d->second)->attach->positionOffset[1], std::get<1>(d->second)->attach->positionOffset[2], std::get<1>(d->second)->attach->rotation[0], std::get<1>(d->second)->attach->rotation[1], std::get<1>(d->second)->attach->rotation[2]);
					}
					else if (std::get<1>(d->second)->attach->player != INVALID_PLAYER_ID)
					{
						ompgdk::AttachPlayerObjectToPlayer(player.playerId, internalId, std::get<1>(d->second)->attach->player, std::get<1>(d->second)->attach->positionOffset[0], std::get<1>(d->second)->attach->positionOffset[1], std::get<1>(d->second)->attach->positionOffset[2], std::get<1>(d->second)->attach->rotation[0], std::get<1>(d->second)->attach->rotation[1], std::get<1>(d->second)->attach->rotation[2]);
					}
					else if (std::get<1>(d->second)->attach->vehicle != INVALID_VEHICLE_ID)
					{
						ompgdk::AttachPlayerObjectToVehicle(player.playerId, internalId, std::get<1>(d->second)->attach->vehicle, std::get<1>(d->second)->attach->positionOffset[0], std::get<1>(d->second)->attach->positionOffset[1], std::get<1>(d->second)->attach->positionOffset[2], std::get<1>(d->second)->attach->rotation[0], std::get<1>(d->second)->attach->rotation[1], std::get<1>(d->second)->attach->rotation[2]);
					}
				}
				else if (std::get<1>(d->second)->move)
				{
					ompgdk::MovePlayerObject(player.playerId, internalId, std::get<0>(std::get<1>(d->second)->move->position)[0], std::get<0>(std::get<1>(d->second)->move->position)[1], std::get<0>(std::get<1>(d->second)->move->position)[2], std::get<1>(d->second)->move->speed, std::get<0>(std::get<1>(d->second)->move->rotation)[0], std::get<0>(std::get<1>(d->second)->move->rotation)[1], std::get<0>(std::get<1>(d->second)->move->rotation)[2]);
				}
				for (std::unordered_map<int, Item::Object::Material>::iterator m = std::get<1>(d->second)->materials.begin(); m != std::get<1>(d->second)->materials.end(); ++m)
				{
					if (m->second.main)
					{
						ompgdk::SetPlayerObjectMaterial(player.playerId, internalId, m->first, m->second.main->modelId, m->second.main->txdFileName.c_str(), m->second.main->textureName.c_str(), m->second.main->materialColor);
					}
					else if (m->second.text)
					{
						ompgdk::SetPlayerObjectMaterialText(player.playerId, internalId, m->second.text->materialText.c_str(), m->first, m->second.text->materialSize, m->second.text->fontFace.c_str(), m->second.text->fontSize, m->second.text->bold, m->second.text->fontColor, m->second.text->backColor, m->second.text->textAlignment);
					}
				}
				if (std::get<1>(d->second)->noCameraCollision)
				{
					ompgdk::SetPlayerObjectNoCameraCol(player.playerId, internalId);
				}
				player.internalObjects.insert(std::make_pair(std::get<0>(d->second), internalId));
				if (std::get<1>(d->second)->cell)
				{
					player.visibleCell->objects.insert(std::make_pair(std::get<0>(d->second), std::get<1>(d->second)));
				}
				d = player.discoveredObjects.left.erase(d);
			}
			if (streamingCanceled)
			{
				player.currentVisibleObjects = player.internalObjects.size();
				player.discoveredObjects.clear();
			}
		}
		player.chunkTickCount[STREAMER_TYPE_OBJECT] = 0;
	}
	if (player.discoveredObjects.empty() && player.removedObjects.empty())
	{
		player.existingObjects.clear();
		player.processingChunks.reset(STREAMER_TYPE_OBJECT);
	}
}

void ChunkStreamer::discoverTextLabels(Player &player, const std::vector<SharedCell> &cells)
{
	for (std::vector<SharedCell>::const_iterator c = cells.begin(); c != cells.end(); ++c)
	{
		for (std::unordered_map<int, Item::SharedTextLabel>::const_iterator t = (*c)->textLabels.begin(); t != (*c)->textLabels.end(); ++t)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (doesPlayerSatisfyConditions(t->second->players, player.playerId, t->second->interiors, player.interiorId, t->second->attach ? t->second->attach->worlds : t->second->worlds, player.worldId, t->second->areas, player.internalAreas, t->second->inverseAreaChecking))
			{
				if (t->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
				{
					distance = std::numeric_limits<float>::infinity() * -1.0f;
				}
				else
				{
					if (t->second->attach)
					{
						distance = static_cast<float>(boost::geometry::comparable_distance(player.position, t->second->attach->position));
					}
					else
					{
						distance = static_cast<float>(boost::geometry::comparable_distance(player.position, Eigen::Vector3f(t->second->position + t->second->positionOffset)));
					}
				}
			}
			std::unordered_map<int, int>::iterator i = player.internalTextLabels.find(t->first);
			if (distance < (t->second->comparableStreamDistance * player.radiusMultipliers[STREAMER_TYPE_3D_TEXT_LABEL]))
			{
				if (i == player.internalTextLabels.end())
				{
					player.discoveredTextLabels.insert(Item::Bimap<Item::SharedTextLabel>::Type::value_type(std::make_tuple(t->second->priority, distance), std::make_tuple(t->first, t->second)));
				}
				else
				{
					if (t->second->cell)
					{
						player.visibleCell->textLabels.insert(*t);
					}
					player.existingTextLabels.insert(Item::Bimap<Item::SharedTextLabel>::Type::value_type(std::make_tuple(t->second->priority, distance), std::make_tuple(t->first, t->second)));
				}
			}
			else
			{
				if (i != player.internalTextLabels.end())
				{
					player.removedTextLabels.insert(i->first);
				}
			}
		}
	}
	if (!player.discoveredTextLabels.empty() || !player.removedTextLabels.empty())
	{
		player.processingChunks.set(STREAMER_TYPE_3D_TEXT_LABEL);
	}
}

void ChunkStreamer::streamTextLabels(Player &player, bool automatic)
{
	if (!automatic || ++player.chunkTickCount[STREAMER_TYPE_3D_TEXT_LABEL] >= player.chunkTickRate[STREAMER_TYPE_3D_TEXT_LABEL])
	{
		std::size_t chunkCount = 0;
		if (!player.removedTextLabels.empty())
		{
			std::unordered_set<int>::iterator r = player.removedTextLabels.begin();
			while (r != player.removedTextLabels.end())
			{
				if (automatic && ++chunkCount > chunkSize[STREAMER_TYPE_3D_TEXT_LABEL])
				{
					break;
				}
				std::unordered_map<int, int>::iterator i = player.internalTextLabels.find(*r);
				if (i != player.internalTextLabels.end())
				{
					ompgdk::DeletePlayer3DTextLabel(player.playerId, i->second);
					std::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(*r);
					if (t != core->getData()->textLabels.end())
					{
						if (t->second->streamCallbacks)
						{
							streamOutCallbacks.push_back(std::make_tuple(STREAMER_TYPE_3D_TEXT_LABEL, *r, player.playerId));
						}
					}
					player.internalTextLabels.erase(i);
				}
				r = player.removedTextLabels.erase(r);
			}
		}
		else
		{
			bool streamingCanceled = false;
			Item::Bimap<Item::SharedTextLabel>::Type::left_iterator d = player.discoveredTextLabels.left.begin();
			while (d != player.discoveredTextLabels.left.end())
			{
				if (automatic && ++chunkCount > chunkSize[STREAMER_TYPE_3D_TEXT_LABEL])
				{
					break;
				}
				std::unordered_map<int, int>::iterator i = player.internalTextLabels.find(std::get<1>(d->second)->textLabelId);
				if (i != player.internalTextLabels.end())
				{
					d = player.discoveredTextLabels.left.erase(d);
					continue;
				}
				if (player.internalTextLabels.size() == player.currentVisibleTextLabels)
				{
					Item::Bimap<Item::SharedTextLabel>::Type::left_reverse_iterator e = player.existingTextLabels.left.rbegin();
					if (e != player.existingTextLabels.left.rend())
					{
						if (std::get<0>(e->first) < std::get<0>(d->first) || (std::get<1>(e->first) > STREAMER_STATIC_DISTANCE_CUTOFF && std::get<1>(d->first) < std::get<1>(e->first)))
						{
							std::unordered_map<int, int>::iterator j = player.internalTextLabels.find(std::get<0>(e->second));
							if (j != player.internalTextLabels.end())
							{
								ompgdk::DeletePlayer3DTextLabel(player.playerId, j->second);
								if (std::get<1>(e->second)->streamCallbacks)
								{
									streamOutCallbacks.push_back(std::make_tuple(STREAMER_TYPE_3D_TEXT_LABEL, std::get<0>(e->second), player.playerId));
								}
								player.internalTextLabels.erase(j);
							}
							if (std::get<1>(e->second)->cell)
							{
								player.visibleCell->textLabels.erase(std::get<0>(e->second));
							}
							Item::Bimap<Item::SharedTextLabel>::Type::left_iterator f = e.base().base();
							player.existingTextLabels.left.erase(--f);
						}
					}
				}
				if (player.internalTextLabels.size() == player.maxVisibleTextLabels)
				{
					streamingCanceled = true;
					break;
				}
				int internalId = ompgdk::CreatePlayer3DTextLabel(player.playerId, std::get<1>(d->second)->text.c_str(), std::get<1>(d->second)->color, std::get<1>(d->second)->position[0], std::get<1>(d->second)->position[1], std::get<1>(d->second)->position[2], std::get<1>(d->second)->drawDistance, std::get<1>(d->second)->attach ? std::get<1>(d->second)->attach->player : INVALID_PLAYER_ID, std::get<1>(d->second)->attach ? std::get<1>(d->second)->attach->vehicle : INVALID_VEHICLE_ID, std::get<1>(d->second)->testLOS);
				if (internalId == INVALID_TEXT_LABEL_ID)
				{
					streamingCanceled = true;
					break;
				}
				if (std::get<1>(d->second)->streamCallbacks)
				{
					streamInCallbacks.push_back(std::make_tuple(STREAMER_TYPE_3D_TEXT_LABEL, std::get<0>(d->second), player.playerId));
				}
				player.internalTextLabels.insert(std::make_pair(std::get<0>(d->second), internalId));
				if (std::get<1>(d->second)->cell)
				{
					player.visibleCell->textLabels.insert(std::make_pair(std::get<0>(d->second), std::get<1>(d->second)));
				}
				d = player.discoveredTextLabels.left.erase(d);
			}
			if (streamingCanceled)
			{
				player.currentVisibleTextLabels = player.internalTextLabels.size();
				player.discoveredTextLabels.clear();
			}
		}
		player.chunkTickCount[STREAMER_TYPE_3D_TEXT_LABEL] = 0;
	}
	if (player.discoveredTextLabels.empty() && player.removedTextLabels.empty())
	{
		player.existingTextLabels.clear();
		player.processingChunks.reset(STREAMER_TYPE_3D_TEXT_LABEL);
	}
}
