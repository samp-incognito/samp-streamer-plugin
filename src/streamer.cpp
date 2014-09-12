/*
 * Copyright (C) 2014 Incognito
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

#include "streamer.h"

#include "core.h"
#include "utility.h"

#include <boost/chrono.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/variant.hpp>

#include <Eigen/Core>

#include <bitset>
#include <limits>
#include <map>
#include <set>
#include <string>
#include <vector>

Streamer::Streamer()
{
	averageUpdateTime = 0.0f;
	processingFinalPlayer = false;
	tickCount = 0;
	tickRate = 50;
	velocityBoundaries = boost::make_tuple(0.25f, 25.0f);
	visibleMapIcons = 100;
	visibleObjects = 500;
	visiblePickups = 4096;
	visibleTextLabels = 1024;
}

std::size_t Streamer::getVisibleItems(int type)
{
	switch (type)
	{
		case STREAMER_TYPE_OBJECT:
		{
			return visibleObjects;
		}
		case STREAMER_TYPE_PICKUP:
		{
			return visiblePickups;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			return visibleMapIcons;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			return visibleTextLabels;
		}
	}
	return 0;
}

bool Streamer::setVisibleItems(int type, std::size_t value)
{
	switch (type)
	{
		case STREAMER_TYPE_OBJECT:
		{
			visibleObjects = value;
			return true;
		}
		case STREAMER_TYPE_PICKUP:
		{
			visiblePickups = value;
			return true;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			visibleMapIcons = value;
			return true;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			visibleTextLabels = value;
			return true;
		}
	}
	return false;
}

void Streamer::calculateAverageUpdateTime()
{
	static boost::chrono::steady_clock::time_point currentTime, lastRecordedTime;
	static Eigen::Array<float, 5, 1> recordedTimes = Eigen::Array<float, 5, 1>::Zero();
	currentTime = boost::chrono::steady_clock::now();
	if (lastRecordedTime.time_since_epoch().count())
	{
		if (!(recordedTimes > 0).all())
		{
			boost::chrono::duration<float> elapsedTime = currentTime - lastRecordedTime;
			recordedTimes[(recordedTimes > 0).count()] = elapsedTime.count();
		}
		else
		{
			averageUpdateTime = recordedTimes.mean() * 50.0f;
			recordedTimes.setZero();
		}
	}
	lastRecordedTime = currentTime;
}

void Streamer::startAutomaticUpdate()
{
	if (tickCount >= tickRate)
	{
		calculateAverageUpdateTime();
		processActiveItems();
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			processingFinalPlayer = isLastPlayer(p, core->getData()->players);
			performPlayerUpdate(p->second, true);
		}
		processingFinalPlayer = false;
		tickCount = 0;
	}
	if (!core->getData()->interfaces.empty())
	{
		++tickCount;
	}
}

void Streamer::startManualUpdate(Player &player, bool getData)
{
	if (getData)
	{
		player.interiorID = GetPlayerInterior(player.playerID);
		player.worldID = GetPlayerVirtualWorld(player.playerID);
		GetPlayerPos(player.playerID, &player.position[0], &player.position[1], &player.position[2]);
	}
	processActiveItems();
	performPlayerUpdate(player, false);
}

void Streamer::performPlayerUpdate(Player &player, bool automatic)
{
	Eigen::Vector3f delta = Eigen::Vector3f::Zero(), position = player.position;
	int state = GetPlayerState(player.playerID);
	bool update = true;
	if (automatic)
	{
		player.interiorID = GetPlayerInterior(player.playerID);
		player.worldID = GetPlayerVirtualWorld(player.playerID);
		GetPlayerPos(player.playerID, &player.position[0], &player.position[1], &player.position[2]);
		if (state != PLAYER_STATE_NONE && state != PLAYER_STATE_WASTED)
		{
			if (player.position != position)
			{
				position = player.position;
				Eigen::Vector3f velocity = Eigen::Vector3f::Zero();
				if (state == PLAYER_STATE_ONFOOT)
				{
					GetPlayerVelocity(player.playerID, &velocity[0], &velocity[1], &velocity[2]);
				}
				else if (state == PLAYER_STATE_DRIVER || state == PLAYER_STATE_PASSENGER)
				{
					GetVehicleVelocity(GetPlayerVehicleID(player.playerID), &velocity[0], &velocity[1], &velocity[2]);
				}
				float velocityNorm = velocity.squaredNorm();
				if (velocityNorm >= velocityBoundaries.get<0>() && velocityNorm <= velocityBoundaries.get<1>())
				{
					delta = velocity * averageUpdateTime;
					player.position += delta;
				}
			}
			else
			{
				update = player.updateWhenIdle;
			}
		}
		else
		{
			update = false;
		}
	}
	std::vector<SharedCell> cells;
	if (update)
	{
		core->getGrid()->findAllCells(player, cells);
		if (!cells.empty())
		{
			if (!core->getData()->objects.empty() && player.enabledItems[STREAMER_TYPE_OBJECT] && !IsPlayerNPC(player.playerID))
			{
				processObjects(player, cells);
			}
			if (!core->getData()->checkpoints.empty() && player.enabledItems[STREAMER_TYPE_CP])
			{
				processCheckpoints(player, cells);
			}
			if (!core->getData()->raceCheckpoints.empty() && player.enabledItems[STREAMER_TYPE_RACE_CP])
			{
				processRaceCheckpoints(player, cells);
			}
			if (!core->getData()->mapIcons.empty() && player.enabledItems[STREAMER_TYPE_MAP_ICON] && !IsPlayerNPC(player.playerID))
			{
				processMapIcons(player, cells);
			}
			if (!core->getData()->textLabels.empty() && player.enabledItems[STREAMER_TYPE_3D_TEXT_LABEL] && !IsPlayerNPC(player.playerID))
			{
				processTextLabels(player, cells);
			}
			if (!core->getData()->areas.empty() && player.enabledItems[STREAMER_TYPE_AREA])
			{
				if (!delta.isZero())
				{
					player.position = position;
				}
				processAreas(player, cells);
				if (!delta.isZero())
				{
					player.position += delta;
				}
			}
		}
	}
	if (automatic)
	{
		if (!core->getData()->pickups.empty())
		{
			if (!update)
			{
				core->getGrid()->findMinimalCells(player, cells);
			}
			processPickups(player, cells);
		}
		if (!delta.isZero())
		{
			player.position = position;
		}
		executeCallbacks();
	}
}

void Streamer::executeCallbacks()
{
	for (std::vector<boost::tuple<int, int> >::const_iterator c = areaLeaveCallbacks.begin(); c != areaLeaveCallbacks.end(); ++c)
	{
		for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
		{
			int amxIndex = 0;
			if (!amx_FindPublic(*a, "OnPlayerLeaveDynamicArea", &amxIndex))
			{
				amx_Push(*a, static_cast<cell>(c->get<0>()));
				amx_Push(*a, static_cast<cell>(c->get<1>()));
				amx_Exec(*a, NULL, amxIndex);
			}
		}
	}
	areaLeaveCallbacks.clear();
	for (std::vector<boost::tuple<int, int> >::const_iterator c = areaEnterCallbacks.begin(); c != areaEnterCallbacks.end(); ++c)
	{
		for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
		{
			int amxIndex = 0;
			if (!amx_FindPublic(*a, "OnPlayerEnterDynamicArea", &amxIndex))
			{
				amx_Push(*a, static_cast<cell>(c->get<0>()));
				amx_Push(*a, static_cast<cell>(c->get<1>()));
				amx_Exec(*a, NULL, amxIndex);
			}
		}
	}
	areaEnterCallbacks.clear();
	for (std::vector<int>::const_iterator c = objectMoveCallbacks.begin(); c != objectMoveCallbacks.end(); ++c)
	{
		for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
		{
			int amxIndex = 0;
			if (!amx_FindPublic(*a, "OnDynamicObjectMoved", &amxIndex))
			{
				amx_Push(*a, static_cast<cell>(*c));
				amx_Exec(*a, NULL, amxIndex);
			}
		}
	}
	objectMoveCallbacks.clear();
}

void Streamer::processAreas(Player &player, const std::vector<SharedCell> &cells)
{
	for (std::vector<SharedCell>::const_iterator c = cells.begin(); c != cells.end(); ++c)
	{
		for (boost::unordered_map<int, Item::SharedArea>::const_iterator a = (*c)->areas.begin(); a != (*c)->areas.end(); ++a)
		{
			bool in = false;
			if (checkPlayer(a->second->players, player.playerID, a->second->interiors, player.interiorID, a->second->worlds, player.worldID))
			{
				boost::unordered_set<int>::iterator d = player.disabledAreas.find(a->first);
				if (d == player.disabledAreas.end())
				{
					in = Utility::isPointInArea(player.position, a->second);
				}
			}
			boost::unordered_set<int>::iterator i = player.internalAreas.find(a->first);
			if (in)
			{
				if (i == player.internalAreas.end())
				{
					player.internalAreas.insert(a->first);
					areaEnterCallbacks.push_back(boost::make_tuple(a->first, player.playerID));
				}
				if (a->second->cell)
				{
					player.visibleCell->areas.insert(*a);
				}
			}
			else
			{
				if (i != player.internalAreas.end())
				{
					player.internalAreas.quick_erase(i);
					areaLeaveCallbacks.push_back(boost::make_tuple(a->first, player.playerID));
				}
			}
		}
	}
}

void Streamer::processCheckpoints(Player &player, const std::vector<SharedCell> &cells)
{
	std::multimap<float, Item::SharedCheckpoint> discoveredCheckpoints;
	for (std::vector<SharedCell>::const_iterator c = cells.begin(); c != cells.end(); ++c)
	{
		for (boost::unordered_map<int, Item::SharedCheckpoint>::const_iterator d = (*c)->checkpoints.begin(); d != (*c)->checkpoints.end(); ++d)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (checkPlayer(d->second->players, player.playerID, d->second->interiors, player.interiorID, d->second->worlds, player.worldID))
			{
				boost::unordered_set<int>::iterator e = player.disabledCheckpoints.find(d->first);
				if (e == player.disabledCheckpoints.end())
				{
					distance = static_cast<float>(boost::geometry::comparable_distance(player.position, d->second->position));
				}
			}
			if (distance <= d->second->streamDistance)
			{
				discoveredCheckpoints.insert(std::make_pair(distance, d->second));
			}
			else
			{
				if (d->first == player.visibleCheckpoint)
				{
					DisablePlayerCheckpoint(player.playerID);
					player.activeCheckpoint = 0;
					player.visibleCheckpoint = 0;
				}
			}
		}
	}
	if (!discoveredCheckpoints.empty())
	{
		std::multimap<float, Item::SharedCheckpoint>::iterator d = discoveredCheckpoints.begin();
		if (d->second->checkpointID != player.visibleCheckpoint)
		{
			if (player.visibleCheckpoint)
			{
				DisablePlayerCheckpoint(player.playerID);
				player.activeCheckpoint = 0;
			}
			SetPlayerCheckpoint(player.playerID, d->second->position[0], d->second->position[1], d->second->position[2], d->second->size);
			player.visibleCheckpoint = d->second->checkpointID;
		}
		if (d->second->cell)
		{
			player.visibleCell->checkpoints.insert(std::make_pair(d->second->checkpointID, d->second));
		}
	}
}

void Streamer::processMapIcons(Player &player, const std::vector<SharedCell> &cells)
{
	std::multimap<float, Item::SharedMapIcon> discoveredMapIcons, existingMapIcons;
	for (std::vector<SharedCell>::const_iterator c = cells.begin(); c != cells.end(); ++c)
	{
		for (boost::unordered_map<int, Item::SharedMapIcon>::const_iterator m = (*c)->mapIcons.begin(); m != (*c)->mapIcons.end(); ++m)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (checkPlayer(m->second->players, player.playerID, m->second->interiors, player.interiorID, m->second->worlds, player.worldID))
			{
				distance = static_cast<float>(boost::geometry::comparable_distance(player.position, m->second->position));
			}
			boost::unordered_map<int, int>::iterator i = player.internalMapIcons.find(m->first);
			if (distance <= m->second->streamDistance)
			{
				if (i == player.internalMapIcons.end())
				{
					discoveredMapIcons.insert(std::make_pair(distance, m->second));
				}
				else
				{
					if (m->second->cell)
					{
						player.visibleCell->mapIcons.insert(*m);
					}
					existingMapIcons.insert(std::make_pair(distance, m->second));
				}
			}
			else
			{
				if (i != player.internalMapIcons.end())
				{
					RemovePlayerMapIcon(player.playerID, i->second);
					player.mapIconIdentifier.remove(i->second, player.internalMapIcons.size());
					player.internalMapIcons.quick_erase(i);
				}
			}
		}
	}
	for (std::multimap<float, Item::SharedMapIcon>::iterator d = discoveredMapIcons.begin(); d != discoveredMapIcons.end(); ++d)
	{
		if (player.internalMapIcons.size() == visibleMapIcons)
		{
			std::multimap<float, Item::SharedMapIcon>::reverse_iterator e = existingMapIcons.rbegin();
			if (e != existingMapIcons.rend())
			{
				if (d->first < e->first)
				{
					boost::unordered_map<int, int>::iterator i = player.internalMapIcons.find(e->second->mapIconID);
					if (i != player.internalMapIcons.end())
					{
						RemovePlayerMapIcon(player.playerID, i->second);
						player.mapIconIdentifier.remove(i->second, player.internalMapIcons.size());
						player.internalMapIcons.quick_erase(i);
					}
					if (e->second->cell)
					{
						player.visibleCell->mapIcons.erase(e->second->mapIconID);
					}
					existingMapIcons.erase(--e.base());
				}
			}
			if (player.internalMapIcons.size() == visibleMapIcons)
			{
				break;
			}
		}
		int internalID = player.mapIconIdentifier.get();
		SetPlayerMapIcon(player.playerID, internalID, d->second->position[0], d->second->position[1], d->second->position[2], d->second->type, d->second->color, d->second->style);
		player.internalMapIcons.insert(std::make_pair(d->second->mapIconID, internalID));
		if (d->second->cell)
		{
			player.visibleCell->mapIcons.insert(std::make_pair(d->second->mapIconID, d->second));
		}
	}
}

void Streamer::processObjects(Player &player, const std::vector<SharedCell> &cells)
{
	std::multimap<float, Item::SharedObject> discoveredObjects, existingObjects;
	for (std::vector<SharedCell>::const_iterator c = cells.begin(); c != cells.end(); ++c)
	{
		for (boost::unordered_map<int, Item::SharedObject>::const_iterator o = (*c)->objects.begin(); o != (*c)->objects.end(); ++o)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (checkPlayer(o->second->players, player.playerID, o->second->interiors, player.interiorID, o->second->worlds, player.worldID))
			{
				if (o->second->attach)
				{
					distance = static_cast<float>(boost::geometry::comparable_distance(player.position, o->second->attach->position));
				}
				else
				{
					distance = static_cast<float>(boost::geometry::comparable_distance(player.position, o->second->position));
				}
			}
			boost::unordered_map<int, int>::iterator i = player.internalObjects.find(o->first);
			if (distance <= o->second->streamDistance)
			{
				if (i == player.internalObjects.end())
				{
					discoveredObjects.insert(std::make_pair(distance, o->second));
				}
				else
				{
					if (o->second->cell)
					{
						player.visibleCell->objects.insert(*o);
					}
					existingObjects.insert(std::make_pair(distance, o->second));
				}
			}
			else
			{
				if (i != player.internalObjects.end())
				{
					DestroyPlayerObject(player.playerID, i->second);
					player.internalObjects.quick_erase(i);
				}
			}
		}
	}
	for (std::multimap<float, Item::SharedObject>::iterator d = discoveredObjects.begin(); d != discoveredObjects.end(); ++d)
	{
		if (player.internalObjects.size() == player.visibleObjects)
		{
			std::multimap<float, Item::SharedObject>::reverse_iterator e = existingObjects.rbegin();
			if (e != existingObjects.rend())
			{
				if (d->first < e->first)
				{
					boost::unordered_map<int, int>::iterator i = player.internalObjects.find(e->second->objectID);
					if (i != player.internalObjects.end())
					{
						DestroyPlayerObject(player.playerID, i->second);
						player.internalObjects.quick_erase(i);
					}
					if (e->second->cell)
					{
						player.visibleCell->objects.erase(e->second->objectID);
					}
					existingObjects.erase(--e.base());
				}
			}
		}
		if (player.internalObjects.size() == visibleObjects)
		{
			player.visibleObjects = player.internalObjects.size();
			break;
		}
		int internalID = CreatePlayerObject(player.playerID, d->second->modelID, d->second->position[0], d->second->position[1], d->second->position[2], d->second->rotation[0], d->second->rotation[1], d->second->rotation[2], d->second->drawDistance);
		if (internalID == INVALID_GENERIC_ID)
		{
			player.visibleObjects = player.internalObjects.size();
			break;
		}
		if (d->second->attach)
		{
			AttachPlayerObjectToVehicle(player.playerID, internalID, d->second->attach->vehicle, d->second->attach->offset[0], d->second->attach->offset[1], d->second->attach->offset[2], d->second->attach->rotation[0], d->second->attach->rotation[1], d->second->attach->rotation[2]);
		}
		else if (d->second->move)
		{
			MovePlayerObject(player.playerID, internalID, d->second->move->position.get<0>()[0], d->second->move->position.get<0>()[1], d->second->move->position.get<0>()[2], d->second->move->speed, d->second->move->rotation.get<0>()[0], d->second->move->rotation.get<0>()[1], d->second->move->rotation.get<0>()[2]);
		}
		for (boost::unordered_map<int, Item::Object::Material>::iterator m = d->second->materials.begin(); m != d->second->materials.end(); ++m)
		{
			if (m->second.main)
			{
				SetPlayerObjectMaterial(player.playerID, internalID, m->first, m->second.main->modelID, m->second.main->txdFileName.c_str(), m->second.main->textureName.c_str(), m->second.main->materialColor);
			}
			else if (m->second.text)
			{
				SetPlayerObjectMaterialText(player.playerID, internalID, m->second.text->materialText.c_str(), m->first, m->second.text->materialSize, m->second.text->fontFace.c_str(), m->second.text->fontSize, m->second.text->bold, m->second.text->fontColor, m->second.text->backColor, m->second.text->textAlignment);
			}
		}
		player.internalObjects.insert(std::make_pair(d->second->objectID, internalID));
		if (d->second->cell)
		{
			player.visibleCell->objects.insert(std::make_pair(d->second->objectID, d->second));
		}
	}
}

void Streamer::processPickups(Player &player, const std::vector<SharedCell> &cells)
{
	static boost::unordered_map<int, Item::SharedPickup> discoveredPickups;
	for (std::vector<SharedCell>::const_iterator c = cells.begin(); c != cells.end(); ++c)
	{
		for (boost::unordered_map<int, Item::SharedPickup>::const_iterator p = (*c)->pickups.begin(); p != (*c)->pickups.end(); ++p)
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator d = discoveredPickups.find(p->first);
			if (d == discoveredPickups.end())
			{
				if (checkPlayer(p->second->players, player.playerID, p->second->interiors, player.interiorID, p->second->worlds, player.worldID))
				{
					if (boost::geometry::comparable_distance(player.position, p->second->position) <= p->second->streamDistance)
					{
						boost::unordered_map<int, int>::iterator i = internalPickups.find(p->first);
						if (i == internalPickups.end())
						{
							p->second->worldID = !p->second->worlds.empty() ? player.worldID : -1;
						}
						discoveredPickups.insert(*p);
					}
				}
			}
		}
	}
	if (processingFinalPlayer)
	{
		boost::unordered_map<int, int>::iterator i = internalPickups.begin();
		while (i != internalPickups.end())
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator d = discoveredPickups.find(i->first);
			if (d == discoveredPickups.end())
			{
				DestroyPickup(i->second);
				i = internalPickups.erase(i);
			}
			else
			{
				discoveredPickups.erase(d);
				++i;
			}
		}
		for (boost::unordered_map<int, Item::SharedPickup>::iterator d = discoveredPickups.begin(); d != discoveredPickups.end(); ++d)
		{
			if (internalPickups.size() == visiblePickups)
			{
				break;
			}
			int internalID = CreatePickup(d->second->modelID, d->second->type, d->second->position[0], d->second->position[1], d->second->position[2], d->second->worldID);
			if (internalID == INVALID_ALTERNATE_ID)
			{
				break;
			}
			internalPickups.insert(std::make_pair(d->second->pickupID, internalID));
		}
		discoveredPickups.clear();
	}
}

void Streamer::processRaceCheckpoints(Player &player, const std::vector<SharedCell> &cells)
{
	std::multimap<float, Item::SharedRaceCheckpoint> discoveredRaceCheckpoints;
	for (std::vector<SharedCell>::const_iterator c = cells.begin(); c != cells.end(); ++c)
	{
		for (boost::unordered_map<int, Item::SharedRaceCheckpoint>::const_iterator r = (*c)->raceCheckpoints.begin(); r != (*c)->raceCheckpoints.end(); ++r)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (checkPlayer(r->second->players, player.playerID, r->second->interiors, player.interiorID, r->second->worlds, player.worldID))
			{
				boost::unordered_set<int>::iterator d = player.disabledRaceCheckpoints.find(r->first);
				if (d == player.disabledRaceCheckpoints.end())
				{
					distance = static_cast<float>(boost::geometry::comparable_distance(player.position, r->second->position));
				}
			}
			if (distance <= r->second->streamDistance)
			{
				discoveredRaceCheckpoints.insert(std::make_pair(distance, r->second));
			}
			else
			{
				if (r->first == player.visibleRaceCheckpoint)
				{
					DisablePlayerRaceCheckpoint(player.playerID);
					player.activeRaceCheckpoint = 0;
					player.visibleRaceCheckpoint = 0;
				}
			}
		}
	}
	if (!discoveredRaceCheckpoints.empty())
	{
		std::multimap<float, Item::SharedRaceCheckpoint>::iterator d = discoveredRaceCheckpoints.begin();
		if (d->second->raceCheckpointID != player.visibleRaceCheckpoint)
		{
			if (player.visibleRaceCheckpoint)
			{
				DisablePlayerRaceCheckpoint(player.playerID);
				player.activeRaceCheckpoint = 0;
			}
			SetPlayerRaceCheckpoint(player.playerID, d->second->type, d->second->position[0], d->second->position[1], d->second->position[2], d->second->next[0], d->second->next[1], d->second->next[2], d->second->size);
			player.visibleRaceCheckpoint = d->second->raceCheckpointID;
		}
		if (d->second->cell)
		{
			player.visibleCell->raceCheckpoints.insert(std::make_pair(d->second->raceCheckpointID, d->second));
		}
	}
}

void Streamer::processTextLabels(Player &player, const std::vector<SharedCell> &cells)
{
	std::multimap<float, Item::SharedTextLabel> discoveredTextLabels, existingTextLabels;
	for (std::vector<SharedCell>::const_iterator c = cells.begin(); c != cells.end(); ++c)
	{
		for (boost::unordered_map<int, Item::SharedTextLabel>::const_iterator t = (*c)->textLabels.begin(); t != (*c)->textLabels.end(); ++t)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (checkPlayer(t->second->players, player.playerID, t->second->interiors, player.interiorID, t->second->worlds, player.worldID))
			{
				if (t->second->attach)
				{
					distance = static_cast<float>(boost::geometry::comparable_distance(player.position, t->second->attach->position));
				}
				else
				{
					distance = static_cast<float>(boost::geometry::comparable_distance(player.position, t->second->position));
				}
			}
			boost::unordered_map<int, int>::iterator i = player.internalTextLabels.find(t->first);
			if (distance <= t->second->streamDistance)
			{
				if (i == player.internalTextLabels.end())
				{
					discoveredTextLabels.insert(std::make_pair(distance, t->second));
				}
				else
				{
					if (t->second->cell)
					{
						player.visibleCell->textLabels.insert(*t);
					}
					existingTextLabels.insert(std::make_pair(distance, t->second));
				}
			}
			else
			{
				if (i != player.internalTextLabels.end())
				{
					DeletePlayer3DTextLabel(player.playerID, i->second);
					player.internalTextLabels.quick_erase(i);
				}
			}
		}
	}
	for (std::multimap<float, Item::SharedTextLabel>::iterator d = discoveredTextLabels.begin(); d != discoveredTextLabels.end(); ++d)
	{
		if (player.internalTextLabels.size() == player.visibleTextLabels)
		{
			std::multimap<float, Item::SharedTextLabel>::reverse_iterator e = existingTextLabels.rbegin();
			if (e != existingTextLabels.rend())
			{
				if (d->first < e->first)
				{
					boost::unordered_map<int, int>::iterator i = player.internalTextLabels.find(e->second->textLabelID);
					if (i != player.internalTextLabels.end())
					{
						DeletePlayer3DTextLabel(player.playerID, i->second);
						player.internalTextLabels.quick_erase(i);
					}
					if (e->second->cell)
					{
						player.visibleCell->textLabels.erase(e->second->textLabelID);
					}
					existingTextLabels.erase(--e.base());
				}
			}
		}
		if (player.internalTextLabels.size() == visibleTextLabels)
		{
			player.visibleTextLabels = player.internalTextLabels.size();
			break;
		}
		int internalID = CreatePlayer3DTextLabel(player.playerID, d->second->text.c_str(), d->second->color, d->second->position[0], d->second->position[1], d->second->position[2], d->second->drawDistance, d->second->attach ? d->second->attach->player : INVALID_GENERIC_ID, d->second->attach ? d->second->attach->vehicle : INVALID_GENERIC_ID, d->second->testLOS);
		if (internalID == INVALID_GENERIC_ID)
		{
			player.visibleTextLabels = player.internalTextLabels.size();
			break;
		}
		player.internalTextLabels.insert(std::make_pair(d->second->textLabelID, internalID));
		if (d->second->cell)
		{
			player.visibleCell->textLabels.insert(std::make_pair(d->second->textLabelID, d->second));
		}
	}
}

void Streamer::processActiveItems()
{
	if (!movingObjects.empty())
	{
		processMovingObjects();
	}
	if (!attachedAreas.empty())
	{
		processAttachedAreas();
	}
	if (!attachedObjects.empty())
	{
		processAttachedObjects();
	}
	if (!attachedTextLabels.empty())
	{
		processAttachedTextLabels();
	}
}

void Streamer::processMovingObjects()
{
	boost::chrono::steady_clock::time_point currentTime = boost::chrono::steady_clock::now();
	boost::unordered_set<Item::SharedObject>::iterator o = movingObjects.begin();
	while (o != movingObjects.end())
	{
		bool objectFinishedMoving = false;
		if ((*o)->move)
		{
			boost::chrono::duration<float, boost::milli> elapsedTime = currentTime - (*o)->move->time;
			if (elapsedTime.count() < (*o)->move->duration)
			{
				(*o)->position = (*o)->move->position.get<1>() + ((*o)->move->position.get<2>() * elapsedTime.count());
				if (((*o)->move->rotation.get<0>().maxCoeff() + 1000.0f) > std::numeric_limits<float>::epsilon())
				{
					(*o)->rotation = (*o)->move->rotation.get<1>() + ((*o)->move->rotation.get<2>() * elapsedTime.count());
				}
			}
			else
			{
				(*o)->position = (*o)->move->position.get<0>();
				if (((*o)->move->rotation.get<0>().maxCoeff() + 1000.0f) > std::numeric_limits<float>::epsilon())
				{
					(*o)->rotation = (*o)->move->rotation.get<0>();
				}
				(*o)->move.reset();
				objectMoveCallbacks.push_back((*o)->objectID);
				objectFinishedMoving = true;
			}
			if ((*o)->cell)
			{
				core->getGrid()->removeObject(*o, true);
			}
		}
		if (objectFinishedMoving)
		{
			o = movingObjects.erase(o);
		}
		else
		{
			++o;
		}
	}
}

void Streamer::processAttachedAreas()
{
	for (boost::unordered_set<Item::SharedArea>::iterator a = attachedAreas.begin(); a != attachedAreas.end(); ++a)
	{
		if ((*a)->attach)
		{
			bool adjust = false;
			if ((*a)->attach->object.get<0>() != INVALID_GENERIC_ID)
			{
				switch ((*a)->attach->object.get<1>())
				{
					case STREAMER_OBJECT_TYPE_GLOBAL:
					{
						adjust = GetObjectPos((*a)->attach->object.get<0>(), &(*a)->attach->position[0], &(*a)->attach->position[1], &(*a)->attach->position[2]);
						break;
					}
					case STREAMER_OBJECT_TYPE_PLAYER:
					{
						adjust = GetPlayerObjectPos((*a)->attach->object.get<2>(), (*a)->attach->object.get<0>(), &(*a)->attach->position[0], &(*a)->attach->position[1], &(*a)->attach->position[2]);
						break;
					}
					case STREAMER_OBJECT_TYPE_DYNAMIC:
					{
						boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find((*a)->attach->object.get<0>());
						if (o != core->getData()->objects.end())
						{
							(*a)->attach->position = o->second->position;
							adjust = true;
						}
						break;
					}
				}
			}
			else if ((*a)->attach->player != INVALID_GENERIC_ID)
			{
				adjust = GetPlayerPos((*a)->attach->player, &(*a)->attach->position[0], &(*a)->attach->position[1], &(*a)->attach->position[2]);
			}
			else if ((*a)->attach->vehicle != INVALID_GENERIC_ID)
			{
				adjust = GetVehiclePos((*a)->attach->vehicle, &(*a)->attach->position[0], &(*a)->attach->position[1], &(*a)->attach->position[2]);
			}
			if (adjust)
			{
				if ((*a)->cell)
				{
					core->getGrid()->removeArea(*a, true);
				}
			}
			else
			{
				(*a)->attach->position.fill(std::numeric_limits<float>::infinity());
			}
		}
	}
}

void Streamer::processAttachedObjects()
{
	for (boost::unordered_set<Item::SharedObject>::iterator o = attachedObjects.begin(); o != attachedObjects.end(); ++o)
	{
		if ((*o)->attach)
		{
			bool adjust = false;
			if ((*o)->attach->vehicle != INVALID_GENERIC_ID)
			{
				adjust = GetVehiclePos((*o)->attach->vehicle, &(*o)->attach->position[0], &(*o)->attach->position[1], &(*o)->attach->position[2]);
			}
			if (adjust)
			{
				if ((*o)->cell)
				{
					core->getGrid()->removeObject(*o, true);
				}
			}
			else
			{
				(*o)->attach->position.fill(std::numeric_limits<float>::infinity());
			}
		}
	}
}

void Streamer::processAttachedTextLabels()
{
	for (boost::unordered_set<Item::SharedTextLabel>::iterator t = attachedTextLabels.begin(); t != attachedTextLabels.end(); ++t)
	{
		bool adjust = false;
		if ((*t)->attach)
		{
			if ((*t)->attach->player != INVALID_GENERIC_ID)
			{
				adjust = GetPlayerPos((*t)->attach->player, &(*t)->attach->position[0], &(*t)->attach->position[1], &(*t)->attach->position[2]);
			}
			else if ((*t)->attach->vehicle != INVALID_GENERIC_ID)
			{
				adjust = GetVehiclePos((*t)->attach->vehicle, &(*t)->attach->position[0], &(*t)->attach->position[1], &(*t)->attach->position[2]);
			}
			if (adjust)
			{
				if ((*t)->cell)
				{
					core->getGrid()->removeTextLabel(*t, true);
				}
			}
			else
			{
				(*t)->attach->position.fill(std::numeric_limits<float>::infinity());
			}
		}
	}
}
