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

#include "chunk-streamer.h"

#include "core.h"

#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

#include <Eigen/Core>

#include <limits>
#include <string>
#include <vector>

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
		for (boost::unordered_map<int, Item::SharedMapIcon>::const_iterator m = (*c)->mapIcons.begin(); m != (*c)->mapIcons.end(); ++m)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (doesPlayerSatisfyConditions(m->second->players, player.playerID, m->second->interiors, player.interiorID, m->second->worlds, player.worldID, m->second->areas, player.internalAreas, m->second->inverseAreaChecking))
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
			boost::unordered_map<int, int>::iterator i = player.internalMapIcons.find(m->first);
			if (distance < (m->second->comparableStreamDistance * player.radiusMultipliers[STREAMER_TYPE_MAP_ICON]))
			{
				if (i == player.internalMapIcons.end())
				{
					player.discoveredMapIcons.insert(Item::Bimap<Item::SharedMapIcon>::Type::value_type(boost::make_tuple(m->second->priority, distance), boost::make_tuple(m->first, m->second)));
				}
				else
				{
					if (m->second->cell)
					{
						player.visibleCell->mapIcons.insert(*m);
					}
					player.existingMapIcons.insert(Item::Bimap<Item::SharedMapIcon>::Type::value_type(boost::make_tuple(m->second->priority, distance), boost::make_tuple(m->first, m->second)));
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
			boost::unordered_set<int>::iterator r = player.removedMapIcons.begin();
			while (r != player.removedMapIcons.end())
			{
				if (automatic && ++chunkCount > chunkSize[STREAMER_TYPE_MAP_ICON])
				{
					break;
				}
				boost::unordered_map<int, int>::iterator i = player.internalMapIcons.find(*r);
				if (i != player.internalMapIcons.end())
				{
					sampgdk::RemovePlayerMapIcon(player.playerID, i->second);
					boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(*r);
					if (m != core->getData()->mapIcons.end())
					{
						if (m->second->streamCallbacks)
						{
							streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_MAP_ICON, *r));
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
				boost::unordered_map<int, int>::iterator i = player.internalMapIcons.find(d->second.get<1>()->mapIconID);
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
						if (e->first.get<0>() < d->first.get<0>() || (e->first.get<1>() > STREAMER_STATIC_DISTANCE_CUTOFF && d->first.get<1>() < e->first.get<1>()))
						{
							boost::unordered_map<int, int>::iterator j = player.internalMapIcons.find(e->second.get<0>());
							if (j != player.internalMapIcons.end())
							{
								sampgdk::RemovePlayerMapIcon(player.playerID, j->second);
								if (e->second.get<1>()->streamCallbacks)
								{
									streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_MAP_ICON, e->second.get<0>()));
								}
								player.mapIconIdentifier.remove(j->second, player.internalMapIcons.size());
								player.internalMapIcons.erase(j);
							}
							if (e->second.get<1>()->cell)
							{
								player.visibleCell->mapIcons.erase(e->second.get<0>());
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
				int internalID = player.mapIconIdentifier.get();
				sampgdk::SetPlayerMapIcon(player.playerID, internalID, d->second.get<1>()->position[0], d->second.get<1>()->position[1], d->second.get<1>()->position[2], d->second.get<1>()->type, d->second.get<1>()->color, d->second.get<1>()->style);
				if (d->second.get<1>()->streamCallbacks)
				{
					streamInCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_MAP_ICON, d->second.get<1>()->mapIconID));
				}
				player.internalMapIcons.insert(std::make_pair(d->second.get<1>()->mapIconID, internalID));
				if (d->second.get<1>()->cell)
				{
					player.visibleCell->mapIcons.insert(std::make_pair(d->second.get<0>(), d->second.get<1>()));
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
		for (boost::unordered_map<int, Item::SharedObject>::const_iterator o = (*c)->objects.begin(); o != (*c)->objects.end(); ++o)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (doesPlayerSatisfyConditions(o->second->players, player.playerID, o->second->interiors, player.interiorID, o->second->worlds, player.worldID, o->second->areas, player.internalAreas, o->second->inverseAreaChecking))
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
			boost::unordered_map<int, int>::iterator i = player.internalObjects.find(o->first);
			if (distance < (o->second->comparableStreamDistance * player.radiusMultipliers[STREAMER_TYPE_OBJECT]))
			{
				if (i == player.internalObjects.end())
				{
					player.discoveredObjects.insert(Item::Bimap<Item::SharedObject>::Type::value_type(boost::make_tuple(o->second->priority, distance), boost::make_tuple(o->first, o->second)));
				}
				else
				{
					if (o->second->cell)
					{
						player.visibleCell->objects.insert(*o);
					}
					player.existingObjects.insert(Item::Bimap<Item::SharedObject>::Type::value_type(boost::make_tuple(o->second->priority, distance), boost::make_tuple(o->first, o->second)));
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
			boost::unordered_set<int>::iterator r = player.removedObjects.begin();
			while (r != player.removedObjects.end())
			{
				if (automatic && ++chunkCount > chunkSize[STREAMER_TYPE_OBJECT])
				{
					break;
				}
				boost::unordered_map<int, int>::iterator i = player.internalObjects.find(*r);
				if (i != player.internalObjects.end())
				{
					sampgdk::DestroyPlayerObject(player.playerID, i->second);
					boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(*r);
					if (o != core->getData()->objects.end())
					{
						if (o->second->streamCallbacks)
						{
							streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_OBJECT, *r));
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
				boost::unordered_map<int, int>::iterator i = player.internalObjects.find(d->second.get<1>()->objectID);
				if (i != player.internalObjects.end())
				{
					d = player.discoveredObjects.left.erase(d);
					continue;
				}
				int internalBaseID = INVALID_STREAMER_ID;
				if (d->second.get<1>()->attach)
				{
					if (d->second.get<1>()->attach->object != INVALID_STREAMER_ID)
					{
						boost::unordered_map<int, int>::iterator j = player.internalObjects.find(d->second.get<1>()->attach->object);
						if (j == player.internalObjects.end())
						{
							d = player.discoveredObjects.left.erase(d);
							continue;
						}
						internalBaseID = j->second;
					}
				}
				if (player.internalObjects.size() == player.currentVisibleObjects)
				{
					Item::Bimap<Item::SharedObject>::Type::left_reverse_iterator e = player.existingObjects.left.rbegin();
					if (e != player.existingObjects.left.rend())
					{
						if (e->first.get<0>() < d->first.get<0>() || (e->first.get<1>() > STREAMER_STATIC_DISTANCE_CUTOFF && d->first.get<1>() < e->first.get<1>()))
						{
							boost::unordered_map<int, int>::iterator j = player.internalObjects.find(e->second.get<0>());
							if (j != player.internalObjects.end())
							{
								sampgdk::DestroyPlayerObject(player.playerID, j->second);
								if (e->second.get<1>()->streamCallbacks)
								{
									streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_OBJECT, e->second.get<0>()));
								}
								player.internalObjects.erase(j);
							}
							if (e->second.get<1>()->cell)
							{
								player.visibleCell->objects.erase(e->second.get<0>());
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
				int internalID = sampgdk::CreatePlayerObject(player.playerID, d->second.get<1>()->modelID, d->second.get<1>()->position[0], d->second.get<1>()->position[1], d->second.get<1>()->position[2], d->second.get<1>()->rotation[0], d->second.get<1>()->rotation[1], d->second.get<1>()->rotation[2], d->second.get<1>()->drawDistance);
				if (internalID == INVALID_OBJECT_ID)
				{
					streamingCanceled = true;
					break;
				}
				if (d->second.get<1>()->streamCallbacks)
				{
					streamInCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_OBJECT, d->second.get<0>()));
				}
				if (d->second.get<1>()->attach)
				{
					if (internalBaseID != INVALID_STREAMER_ID)
					{
						static AMX_NATIVE native = sampgdk::FindNative("AttachPlayerObjectToObject");
						if (native != NULL)
						{
							sampgdk::InvokeNative(native, "dddffffffb", player.playerID, internalID, internalBaseID, d->second.get<1>()->attach->positionOffset[0], d->second.get<1>()->attach->positionOffset[1], d->second.get<1>()->attach->positionOffset[2], d->second.get<1>()->attach->rotation[0], d->second.get<1>()->attach->rotation[1], d->second.get<1>()->attach->rotation[2], d->second.get<1>()->attach->syncRotation);
						}
					}
					else if (d->second.get<1>()->attach->player != INVALID_PLAYER_ID)
					{
						static AMX_NATIVE native = sampgdk::FindNative("AttachPlayerObjectToPlayer");
						if (native != NULL)
						{
							sampgdk::InvokeNative(native, "dddffffffd", player.playerID, internalID, d->second.get<1>()->attach->player, d->second.get<1>()->attach->positionOffset[0], d->second.get<1>()->attach->positionOffset[1], d->second.get<1>()->attach->positionOffset[2], d->second.get<1>()->attach->rotation[0], d->second.get<1>()->attach->rotation[1], d->second.get<1>()->attach->rotation[2], 1);
						}
					}
					else if (d->second.get<1>()->attach->vehicle != INVALID_VEHICLE_ID)
					{
						sampgdk::AttachPlayerObjectToVehicle(player.playerID, internalID, d->second.get<1>()->attach->vehicle, d->second.get<1>()->attach->positionOffset[0], d->second.get<1>()->attach->positionOffset[1], d->second.get<1>()->attach->positionOffset[2], d->second.get<1>()->attach->rotation[0], d->second.get<1>()->attach->rotation[1], d->second.get<1>()->attach->rotation[2]);
					}
				}
				else if (d->second.get<1>()->move)
				{
					sampgdk::MovePlayerObject(player.playerID, internalID, d->second.get<1>()->move->position.get<0>()[0], d->second.get<1>()->move->position.get<0>()[1], d->second.get<1>()->move->position.get<0>()[2], d->second.get<1>()->move->speed, d->second.get<1>()->move->rotation.get<0>()[0], d->second.get<1>()->move->rotation.get<0>()[1], d->second.get<1>()->move->rotation.get<0>()[2]);
				}
				for (boost::unordered_map<int, Item::Object::Material>::iterator m = d->second.get<1>()->materials.begin(); m != d->second.get<1>()->materials.end(); ++m)
				{
					if (m->second.main)
					{
						sampgdk::SetPlayerObjectMaterial(player.playerID, internalID, m->first, m->second.main->modelID, m->second.main->txdFileName.c_str(), m->second.main->textureName.c_str(), m->second.main->materialColor);
					}
					else if (m->second.text)
					{
						sampgdk::SetPlayerObjectMaterialText(player.playerID, internalID, m->second.text->materialText.c_str(), m->first, m->second.text->materialSize, m->second.text->fontFace.c_str(), m->second.text->fontSize, m->second.text->bold, m->second.text->fontColor, m->second.text->backColor, m->second.text->textAlignment);
					}
				}
				if (d->second.get<1>()->noCameraCollision)
				{
					sampgdk::SetPlayerObjectNoCameraCol(player.playerID, internalID);
				}
				player.internalObjects.insert(std::make_pair(d->second.get<0>(), internalID));
				if (d->second.get<1>()->cell)
				{
					player.visibleCell->objects.insert(std::make_pair(d->second.get<0>(), d->second.get<1>()));
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
		for (boost::unordered_map<int, Item::SharedTextLabel>::const_iterator t = (*c)->textLabels.begin(); t != (*c)->textLabels.end(); ++t)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (doesPlayerSatisfyConditions(t->second->players, player.playerID, t->second->interiors, player.interiorID, t->second->worlds, player.worldID, t->second->areas, player.internalAreas, t->second->inverseAreaChecking))
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
			boost::unordered_map<int, int>::iterator i = player.internalTextLabels.find(t->first);
			if (distance < (t->second->comparableStreamDistance * player.radiusMultipliers[STREAMER_TYPE_3D_TEXT_LABEL]))
			{
				if (i == player.internalTextLabels.end())
				{
					player.discoveredTextLabels.insert(Item::Bimap<Item::SharedTextLabel>::Type::value_type(boost::make_tuple(t->second->priority, distance), boost::make_tuple(t->first, t->second)));
				}
				else
				{
					if (t->second->cell)
					{
						player.visibleCell->textLabels.insert(*t);
					}
					player.existingTextLabels.insert(Item::Bimap<Item::SharedTextLabel>::Type::value_type(boost::make_tuple(t->second->priority, distance), boost::make_tuple(t->first, t->second)));
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
			boost::unordered_set<int>::iterator r = player.removedTextLabels.begin();
			while (r != player.removedTextLabels.end())
			{
				if (automatic && ++chunkCount > chunkSize[STREAMER_TYPE_3D_TEXT_LABEL])
				{
					break;
				}
				boost::unordered_map<int, int>::iterator i = player.internalTextLabels.find(*r);
				if (i != player.internalTextLabels.end())
				{
					sampgdk::DeletePlayer3DTextLabel(player.playerID, i->second);
					boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(*r);
					if (t != core->getData()->textLabels.end())
					{
						if (t->second->streamCallbacks)
						{
							streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_3D_TEXT_LABEL, *r));
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
				boost::unordered_map<int, int>::iterator i = player.internalTextLabels.find(d->second.get<1>()->textLabelID);
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
						if (e->first.get<0>() < d->first.get<0>() || (e->first.get<1>() > STREAMER_STATIC_DISTANCE_CUTOFF && d->first.get<1>() < e->first.get<1>()))
						{
							boost::unordered_map<int, int>::iterator j = player.internalTextLabels.find(e->second.get<0>());
							if (j != player.internalTextLabels.end())
							{
								sampgdk::DeletePlayer3DTextLabel(player.playerID, j->second);
								if (e->second.get<1>()->streamCallbacks)
								{
									streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_3D_TEXT_LABEL, e->second.get<0>()));
								}
								player.internalTextLabels.erase(j);
							}
							if (e->second.get<1>()->cell)
							{
								player.visibleCell->textLabels.erase(e->second.get<0>());
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
				int internalID = sampgdk::CreatePlayer3DTextLabel(player.playerID, d->second.get<1>()->text.c_str(), d->second.get<1>()->color, d->second.get<1>()->position[0], d->second.get<1>()->position[1], d->second.get<1>()->position[2], d->second.get<1>()->drawDistance, d->second.get<1>()->attach ? d->second.get<1>()->attach->player : INVALID_PLAYER_ID, d->second.get<1>()->attach ? d->second.get<1>()->attach->vehicle : INVALID_VEHICLE_ID, d->second.get<1>()->testLOS);
				if (internalID == INVALID_3DTEXT_ID)
				{
					streamingCanceled = true;
					break;
				}
				if (d->second.get<1>()->streamCallbacks)
				{
					streamInCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_3D_TEXT_LABEL, d->second.get<0>()));
				}
				player.internalTextLabels.insert(std::make_pair(d->second.get<0>(), internalID));
				if (d->second.get<1>()->cell)
				{
					player.visibleCell->textLabels.insert(std::make_pair(d->second.get<0>(), d->second.get<1>()));
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
