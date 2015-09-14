/*
 * Copyright (C) 2015 Incognito
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
	defaultVehicleRespawn = true;
	velocityBoundaries = boost::make_tuple(0.25f, 25.0f);
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
		executeCallbacks();
		processingFinalPlayer = false;
		tickCount = 0;
	}
	if (!core->getData()->interfaces.empty())
	{
		++tickCount;
	}
}

void Streamer::startManualUpdate(Player &player, int type)
{
	std::bitset<STREAMER_MAX_TYPES> enabledItems = player.enabledItems;
	if (type >= 0 && type < STREAMER_MAX_TYPES)
	{
		player.enabledItems.reset();
		player.enabledItems.set(type);
	}
	processActiveItems();
	performPlayerUpdate(player, false);
	player.enabledItems = enabledItems;
}

void Streamer::performPlayerUpdate(Player &player, bool automatic)
{
	Eigen::Vector3f delta = Eigen::Vector3f::Zero(), position = player.position;
	bool update = true;
	if (automatic)
	{
		int state = GetPlayerState(player.playerID);
		player.interiorID = GetPlayerInterior(player.playerID);
		player.worldID = GetPlayerVirtualWorld(player.playerID);
		if (!player.updateUsingCameraPosition)
		{
			GetPlayerPos(player.playerID, &player.position[0], &player.position[1], &player.position[2]);
		}
		else
		{
			GetPlayerCameraPos(player.playerID, &player.position[0], &player.position[1], &player.position[2]);
		}
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
				if (velocityNorm > velocityBoundaries.get<0>() && velocityNorm < velocityBoundaries.get<1>())
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
		if (player.delayedCheckpoint)
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(player.delayedCheckpoint);
			if (c != core->getData()->checkpoints.end())
			{
				SetPlayerCheckpoint(player.playerID, c->second->position[0], c->second->position[1], c->second->position[2], c->second->size);
				player.visibleCheckpoint = c->first;
			}
			player.delayedCheckpoint = 0;
		}
		else if (player.delayedRaceCheckpoint)
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(player.delayedRaceCheckpoint);
			if (r != core->getData()->raceCheckpoints.end())
			{
				SetPlayerRaceCheckpoint(player.playerID, r->second->type, r->second->position[0], r->second->position[1], r->second->position[2], r->second->next[0], r->second->next[1], r->second->next[2], r->second->size);
				player.visibleRaceCheckpoint = r->first;
			}
			player.delayedRaceCheckpoint = 0;
		}
	}
	std::vector<SharedCell> cells;
	if (update)
	{
		core->getGrid()->findAllCellsForPlayer(player, cells);
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
		if (!update)
		{
			core->getGrid()->findMinimalCellsForPlayer(player, cells);
		}
		if (!core->getData()->pickups.empty())
		{
			processPickups(player, cells);
		}
		if (!core->getData()->vehicles.empty())
		{
			processVehicles(player, cells);
		}
		if (!delta.isZero())
		{
			player.position = position;
		}
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
					if (d->second->streamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
					{
						distance = std::numeric_limits<float>::infinity() * -1.0f;
					}
					else
					{
						distance = static_cast<float>(boost::geometry::comparable_distance(player.position, d->second->position));
					}
				}
			}
			if (distance < (d->second->streamDistance * player.radiusMultipliers[STREAMER_TYPE_CP]))
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
			player.delayedCheckpoint = d->second->checkpointID;
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
				if (m->second->streamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
				{
					distance = std::numeric_limits<float>::infinity() * -1.0f;
				}
				else
				{
					distance = static_cast<float>(boost::geometry::comparable_distance(player.position, m->second->position));
				}
			}
			boost::unordered_map<int, int>::iterator i = player.internalMapIcons.find(m->first);
			if (distance < (m->second->streamDistance * player.radiusMultipliers[STREAMER_TYPE_MAP_ICON]))
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
		if (player.internalMapIcons.size() == player.maxVisibleMapIcons)
		{
			std::multimap<float, Item::SharedMapIcon>::reverse_iterator e = existingMapIcons.rbegin();
			if (e != existingMapIcons.rend())
			{
				if (e->first > STREAMER_STATIC_DISTANCE_CUTOFF && d->first < e->first)
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
			if (player.internalMapIcons.size() == player.maxVisibleMapIcons)
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
				if (o->second->streamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
				{
					distance = std::numeric_limits<float>::infinity() * -1.0f;
				}
				else
				{
					if (o->second->attach)
					{
						distance = static_cast<float>(boost::geometry::comparable_distance(player.position, o->second->attach->position)) + 0.01f;
					}
					else
					{
						distance = static_cast<float>(boost::geometry::comparable_distance(player.position, o->second->position));
					}
				}
			}
			boost::unordered_map<int, int>::iterator i = player.internalObjects.find(o->first);
			if (distance < (o->second->streamDistance * player.radiusMultipliers[STREAMER_TYPE_OBJECT]))
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
		if (player.internalObjects.size() == player.currentVisibleObjects)
		{
			std::multimap<float, Item::SharedObject>::reverse_iterator e = existingObjects.rbegin();
			if (e != existingObjects.rend())
			{
				if (e->first > STREAMER_STATIC_DISTANCE_CUTOFF && d->first < e->first)
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
		if (player.internalObjects.size() == player.maxVisibleObjects)
		{
			player.currentVisibleObjects = player.internalObjects.size();
			break;
		}
		int internalID = CreatePlayerObject(player.playerID, d->second->modelID, 0.0f, 0.0f, 0.0f, d->second->rotation[0], d->second->rotation[1], d->second->rotation[2], d->second->drawDistance);
		if (internalID == INVALID_GENERIC_ID)
		{
			player.currentVisibleObjects = player.internalObjects.size();
			break;
		}
		SetPlayerObjectPos(player.playerID, internalID, d->second->position[0], d->second->position[1], d->second->position[2]);
		if (d->second->attach)
		{
			if (d->second->attach->object != INVALID_STREAMER_ID)
			{
				boost::unordered_map<int, int>::iterator i = player.internalObjects.find(d->second->attach->object);
				if (i != player.internalObjects.end())
				{
					AMX_NATIVE native = sampgdk::FindNative("AttachPlayerObjectToObject");
					if (native != NULL)
					{
						sampgdk::InvokeNative(native, "dddffffffb", player.playerID, internalID, i->second, d->second->attach->offset[0], d->second->attach->offset[1], d->second->attach->offset[2], d->second->attach->rotation[0], d->second->attach->rotation[1], d->second->attach->rotation[2], d->second->attach->syncRotation);
					}
				}
			}
			else if (d->second->attach->player != INVALID_GENERIC_ID)
			{
				AMX_NATIVE native = sampgdk::FindNative("AttachPlayerObjectToPlayer");
				if (native != NULL)
				{
					sampgdk::InvokeNative(native, "dddffffff", player.playerID, internalID, d->second->attach->player, d->second->attach->offset[0], d->second->attach->offset[1], d->second->attach->offset[2], d->second->attach->rotation[0], d->second->attach->rotation[1], d->second->attach->rotation[2]);
				}
			}
			else if (d->second->attach->vehicle != INVALID_GENERIC_ID)
			{
				if (d->second->attach->vehicleType == STREAMER_VEHICLE_TYPE_DYNAMIC) 
				{
					boost::unordered_map<int, int>::iterator v = core->getData()->internalVehicles.find(d->second->attach->vehicle);
					if (v != core->getData()->internalVehicles.end())
					{
						AttachPlayerObjectToVehicle(player.playerID, internalID, v->second, d->second->attach->offset[0], d->second->attach->offset[1], d->second->attach->offset[2], d->second->attach->rotation[0], d->second->attach->rotation[1], d->second->attach->rotation[2]);
					}
				}
				else 
				{
					AttachPlayerObjectToVehicle(player.playerID, internalID, d->second->attach->vehicle, d->second->attach->offset[0], d->second->attach->offset[1], d->second->attach->offset[2], d->second->attach->rotation[0], d->second->attach->rotation[1], d->second->attach->rotation[2]);
				}
			}
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
		if (d->second->noCameraCollision)
		{
			SetPlayerObjectNoCameraCol(player.playerID, internalID);
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
					if (p->second->streamDistance < STREAMER_STATIC_DISTANCE_CUTOFF || boost::geometry::comparable_distance(player.position, p->second->position) < (p->second->streamDistance * player.radiusMultipliers[STREAMER_TYPE_PICKUP]))
					{
						boost::unordered_map<int, int>::iterator i = core->getData()->internalPickups.find(p->first);
						if (i == core->getData()->internalPickups.end())
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
		boost::unordered_map<int, int>::iterator i = core->getData()->internalPickups.begin();
		while (i != core->getData()->internalPickups.end())
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator d = discoveredPickups.find(i->first);
			if (d == discoveredPickups.end())
			{
				DestroyPickup(i->second);
				i = core->getData()->internalPickups.erase(i);
			}
			else
			{
				discoveredPickups.erase(d);
				++i;
			}
		}
		for (boost::unordered_map<int, Item::SharedPickup>::iterator d = discoveredPickups.begin(); d != discoveredPickups.end(); ++d)
		{
			if (core->getData()->internalPickups.size() == core->getData()->getGlobalMaxVisibleItems(STREAMER_TYPE_PICKUP))
			{
				break;
			}
			int internalID = CreatePickup(d->second->modelID, d->second->type, d->second->position[0], d->second->position[1], d->second->position[2], d->second->worldID);
			if (internalID == INVALID_ALTERNATE_ID)
			{
				break;
			}
			core->getData()->internalPickups.insert(std::make_pair(d->second->pickupID, internalID));
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
					if (r->second->streamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
					{
						distance = std::numeric_limits<float>::infinity() * -1.0f;
					}
					else
					{
						distance = static_cast<float>(boost::geometry::comparable_distance(player.position, r->second->position));
					}
				}
			}
			if (distance < (r->second->streamDistance * player.radiusMultipliers[STREAMER_TYPE_RACE_CP]))
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
			player.delayedRaceCheckpoint = d->second->raceCheckpointID;
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
				if (t->second->streamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
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
						distance = static_cast<float>(boost::geometry::comparable_distance(player.position, t->second->position));
					}
				}
			}
			boost::unordered_map<int, int>::iterator i = player.internalTextLabels.find(t->first);
			if (distance < (t->second->streamDistance * player.radiusMultipliers[STREAMER_TYPE_3D_TEXT_LABEL]))
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
		if (player.internalTextLabels.size() == player.currentVisibleTextLabels)
		{
			std::multimap<float, Item::SharedTextLabel>::reverse_iterator e = existingTextLabels.rbegin();
			if (e != existingTextLabels.rend())
			{
				if (e->first > STREAMER_STATIC_DISTANCE_CUTOFF && d->first < e->first)
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
		if (player.internalTextLabels.size() == player.maxVisibleTextLabels)
		{
			player.currentVisibleTextLabels = player.internalTextLabels.size();
			break;
		}
		bool createText = true;
		int attachedVehicle = d->second->attach ? d->second->attach->vehicle : INVALID_GENERIC_ID;
		if(attachedVehicle != INVALID_GENERIC_ID)
		{
			if(d->second->attach->vehicleType = STREAMER_VEHICLE_TYPE_DYNAMIC)
			{
				boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(attachedVehicle);
				if (i == core->getData()->internalVehicles.end())
				{
					createText = false;
				}
				else
				{
					attachedVehicle = i->second;
				}
			}
		}

		if(createText)
		{
			int internalID = CreatePlayer3DTextLabel(player.playerID, d->second->text.c_str(), d->second->color, d->second->position[0], d->second->position[1], d->second->position[2], d->second->drawDistance, d->second->attach ? d->second->attach->player : INVALID_GENERIC_ID, attachedVehicle, d->second->testLOS);
			if (internalID == INVALID_GENERIC_ID)
			{
				player.currentVisibleTextLabels = player.internalTextLabels.size();
				break;
			}
			player.internalTextLabels.insert(std::make_pair(d->second->textLabelID, internalID));
			if (d->second->cell)
			{
				player.visibleCell->textLabels.insert(std::make_pair(d->second->textLabelID, d->second));
			}
		}
	}
}

void Streamer::processVehicles(Player &player, const std::vector<SharedCell> &cells)
{
	static boost::unordered_map<int, Item::SharedVehicle> discoveredVehicles;
	for (std::vector<SharedCell>::const_iterator c = cells.begin(); c != cells.end(); ++c)
	{
		for (boost::unordered_map<int, Item::SharedVehicle>::const_iterator p = (*c)->vehicles.begin(); p != (*c)->vehicles.end(); ++p)
		{
			boost::unordered_map<int, Item::SharedVehicle>::iterator d = discoveredVehicles.find(p->first);
			if (d == discoveredVehicles.end())
			{
				if(p->second->interior == GetPlayerInterior(player.playerID) && p->second->worldID == GetPlayerVirtualWorld(player.playerID))		
				{
					if (p->second->streamDistance < STREAMER_STATIC_DISTANCE_CUTOFF || boost::geometry::comparable_distance(player.position, p->second->position) < (p->second->streamDistance * player.radiusMultipliers[STREAMER_TYPE_VEHICLE]))
					{
						discoveredVehicles.insert(*p);
					}
				}
			}
		}
	}
	if (processingFinalPlayer)
	{
		boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.begin();
		while (i != core->getData()->internalVehicles.end())
		{
			boost::unordered_map<int, Item::SharedVehicle>::iterator d = discoveredVehicles.find(i->first);
			if (d == discoveredVehicles.end())
			{
				boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find(i->second);
				if (v != core->getData()->vehicles.end())
				{
					GetVehiclePos(i->second, &v->second->position[0], &v->second->position[1], &v->second->position[2]);
					GetVehicleRotationQuat(i->second, &v->second->qw, &v->second->qx, &v->second->qy, &v->second->qz);
					GetVehicleZAngle(i->second, &v->second->angle);
					GetVehicleHealth(i->second, &v->second->health);
				}

				//sampgdk_logprintf("d == discoveredVehicles.end() internal: %d, streamer: %d", i->first, i->second);
				DestroyVehicle(i->second);
				i = core->getData()->internalVehicles.erase(i);
			}
			else
			{
				//sampgdk_logprintf("discoveredVehicles.erase(d) %d", d->second->vehicleID);
				discoveredVehicles.erase(d);
				++i;
			}
		}
		for (boost::unordered_map<int, Item::SharedVehicle>::iterator d = discoveredVehicles.begin(); d != discoveredVehicles.end(); ++d)
		{
			if (core->getData()->internalVehicles.size() == core->getData()->getGlobalMaxVisibleItems(STREAMER_TYPE_PICKUP))
			{
				sampgdk_logprintf("limit reached");
				break;
			}
			int internalID = INVALID_VEHICLE_ID;
			switch(d->second->modelID)
			{
				case 537:
				case 538:
				{
					//internalID = AddStaticVehicle(d->second->modelID, d->second->position[0], d->second->position[1], d->second->position[2], d->second->angle, d->second->color1, d->second->color2);
					// TODO - This won't work properly without modifing train handling in samp server
					// If you create train, then you create 4 vehicle - the base model ID has been returned, but the last 3 trailer not and you can't get these IDs - only when these ids are in sequence
					// but these IDs won't be in sequence when server randomly destroy and create vehicles at different ids - for more info: http://pastebin.com/wZsiVHBr
					break;
				}
				default:
				{
					internalID = CreateVehicle(d->second->modelID, d->second->position[0], d->second->position[1], d->second->position[2], d->second->angle, d->second->color1, d->second->color2, -1, d->second->spawn.addsiren);
					break;
				}
			}
			if (internalID == INVALID_VEHICLE_ID)
			{
				break;
			}
			if (!d->second->numberplate.empty())
			{
				SetVehicleNumberPlate(internalID, d->second->numberplate.c_str());
			}
			if(d->second->interior)
			{
				LinkVehicleToInterior(internalID, d->second->interior);
			}
			if(d->second->worldID)
			{
				SetVehicleVirtualWorld(internalID, d->second->worldID);
			}
			if (!d->second->carmods.empty())
			{
				for (std::vector<int>::iterator c = d->second->carmods.begin(); c != d->second->carmods.end(); c++)
				{
					AddVehicleComponent(internalID, *c);
				}
			}
			if (d->second->paintjob != 4)
			{
				ChangeVehiclePaintjob(internalID, d->second->paintjob);
			}
			if(d->second->panels != 0 || d->second->doors != 0 || d->second->lights != 0|| d->second->tires != 0)
			{
				UpdateVehicleDamageStatus(internalID, d->second->panels, d->second->doors, d->second->lights, d->second->tires);
			}
			if (d->second->health != 1000.0f)
			{
				SetVehicleHealth(internalID, d->second->health);
			}
			if(d->second->params.engine != VEHICLE_PARAMS_UNSET || d->second->params.lights != VEHICLE_PARAMS_UNSET || d->second->params.alarm != VEHICLE_PARAMS_UNSET || d->second->params.doors != VEHICLE_PARAMS_UNSET || d->second->params.bonnet != VEHICLE_PARAMS_UNSET || d->second->params.boot != VEHICLE_PARAMS_UNSET || d->second->params.objective != VEHICLE_PARAMS_UNSET)
			{
				SetVehicleParamsEx(internalID, d->second->params.engine, d->second->params.lights, d->second->params.alarm, d->second->params.doors, d->second->params.bonnet, d->second->params.boot, d->second->params.objective);
			}
			if(d->second->params.cardoors.driver != VEHICLE_PARAMS_UNSET || d->second->params.cardoors.passenger != VEHICLE_PARAMS_UNSET || d->second->params.cardoors.backleft != VEHICLE_PARAMS_UNSET || d->second->params.cardoors.backright != VEHICLE_PARAMS_UNSET)
			{
				SetVehicleParamsCarDoors(internalID, d->second->params.cardoors.driver, d->second->params.cardoors.passenger, d->second->params.cardoors.backleft, d->second->params.cardoors.backright);
			}
			if(d->second->params.carwindows.driver != VEHICLE_PARAMS_UNSET || d->second->params.carwindows.passenger != VEHICLE_PARAMS_UNSET || d->second->params.carwindows.backleft != VEHICLE_PARAMS_UNSET || d->second->params.carwindows.backright != VEHICLE_PARAMS_UNSET)
			{
				SetVehicleParamsCarWindows(internalID, d->second->params.carwindows.driver, d->second->params.carwindows.passenger, d->second->params.carwindows.backleft, d->second->params.carwindows.backright);
			}
			core->getData()->internalVehicles.insert(std::make_pair(d->second->vehicleID, internalID));
		}
		discoveredVehicles.clear();
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
	if (!movingVehicles.empty())
	{
		processMovingVehicles();
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
				if (!Utility::almostEquals((*o)->move->rotation.get<0>().maxCoeff(), -1000.0f))
				{
					(*o)->rotation = (*o)->move->rotation.get<1>() + ((*o)->move->rotation.get<2>() * elapsedTime.count());
				}
			}
			else
			{
				(*o)->position = (*o)->move->position.get<0>();
				if (!Utility::almostEquals((*o)->move->rotation.get<0>().maxCoeff(), -1000.0f))
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
			if (((*a)->attach->object.get<0>() != INVALID_GENERIC_ID && (*a)->attach->object.get<1>() != STREAMER_OBJECT_TYPE_DYNAMIC) || ((*a)->attach->object.get<0>() != INVALID_STREAMER_ID && (*a)->attach->object.get<1>() == STREAMER_OBJECT_TYPE_DYNAMIC))
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
				if((*a)->attach->vehicleType == STREAMER_VEHICLE_TYPE_STATIC)
				{			
					adjust = GetVehiclePos((*a)->attach->vehicle, &(*a)->attach->position[0], &(*a)->attach->position[1], &(*a)->attach->position[2]);
				}
				else
				{					
					boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find((*a)->attach->vehicle);
					if (v != core->getData()->vehicles.end())
					{
						boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
						if (i != core->getData()->internalVehicles.end())
						{
							adjust = GetVehiclePos(i->second, &(*a)->attach->position[0], &(*a)->attach->position[1], &(*a)->attach->position[2]);
						}
						else
						{
							(*a)->attach->position = v->second->position;
							adjust = true;
						}
					}
				}
			}
			(*a)->attach->position += (*a)->attach->offset;
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
			if ((*o)->attach->object != INVALID_STREAMER_ID)
			{
				boost::unordered_map<int, Item::SharedObject>::iterator p = core->getData()->objects.find((*o)->attach->object);
				if (p != core->getData()->objects.end())
				{
					(*o)->attach->position = p->second->position;
					adjust = true;
				}
			}
			else if ((*o)->attach->player != INVALID_GENERIC_ID)
			{
				adjust = GetPlayerPos((*o)->attach->player, &(*o)->attach->position[0], &(*o)->attach->position[1], &(*o)->attach->position[2]);
			}
			else if ((*o)->attach->vehicle != INVALID_GENERIC_ID)
			{
				if((*o)->attach->vehicleType == STREAMER_VEHICLE_TYPE_STATIC)
				{
					adjust = GetVehiclePos((*o)->attach->vehicle, &(*o)->attach->position[0], &(*o)->attach->position[1], &(*o)->attach->position[2]);
				}
				else
				{
					boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find((*o)->attach->vehicle);
					if (v != core->getData()->vehicles.end())
					{
						boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
						if (i != core->getData()->internalVehicles.end())
						{
							adjust = GetVehiclePos(i->second, &(*o)->attach->position[0], &(*o)->attach->position[1], &(*o)->attach->position[2]);
						}
						else
						{
							(*o)->attach->position = v->second->position;
							adjust = true;
						}
					}
				}
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
				if((*t)->attach->vehicleType == STREAMER_VEHICLE_TYPE_STATIC)
				{
					adjust = GetVehiclePos((*t)->attach->vehicle, &(*t)->attach->position[0], &(*t)->attach->position[1], &(*t)->attach->position[2]);
				}
				else
				{
					boost::unordered_map<int, Item::SharedVehicle>::iterator v = core->getData()->vehicles.find((*t)->attach->vehicle);
					if (v != core->getData()->vehicles.end())
					{
						boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find(v->first);
						if (i != core->getData()->internalVehicles.end())
						{
							adjust = GetVehiclePos(i->second, &(*t)->attach->position[0], &(*t)->attach->position[1], &(*t)->attach->position[2]);
						}
						else
						{
							(*t)->attach->position = v->second->position;
							adjust = true;
						}
					}
				}
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

void Streamer::processMovingVehicles()
{
	boost::unordered_set<Item::SharedVehicle>::iterator v = movingVehicles.begin();
	while (v != movingVehicles.end())
	{
		bool adjust = false;
		if ((*v)->touched)
		{
			// Custom vehicle respawn
			if((*v)->respawnDelay != -1)
			{
				int tick = GetTickCount();
				
				bool respawnVehicle;
				if(core->getStreamer()->defaultVehicleRespawn)
				{
					// Do not check for respawn in first 10 second after spawned
					respawnVehicle = static_cast<int>(tick - (*v)->spawnedTick > 10000);
				}
				else
				{
					// Do not check for respawn in first 10 second after spawned, and respawn only if vehicle was used at least one time.
					respawnVehicle = static_cast<int>((tick - (*v)->spawnedTick > 10000) && (*v)->used);
				}

				if(respawnVehicle)
				{
					// If respawnDelay time passed since last update, then respawn
					if(tick - (*v)->lastUpdatedTick >=  (*v)->respawnDelay)
					{
						(*v)->position = (*v)->spawn.position;
						(*v)->angle = (*v)->spawn.angle;
						(*v)->color1 = (*v)->spawn.color1;
						(*v)->color2 = (*v)->spawn.color2;
						(*v)->paintjob = 4; // In GTA, you can use 0 - 3 IDs for paintjobs, 4 is invalid
						(*v)->health = 1000.0f;

						(*v)->carmods.clear();
						(*v)->touched = false;
						(*v)->spawnedTick = GetTickCount();
						(*v)->lastUpdatedTick = 0;

						// Reset vehicle damage
						(*v)->panels = 0;
						(*v)->doors = 0;
						(*v)->lights = 0;
						(*v)->tires = 0;

						// Set vehicle parameters as unset
						(*v)->params.engine = VEHICLE_PARAMS_UNSET;
						(*v)->params.lights = VEHICLE_PARAMS_UNSET;
						(*v)->params.alarm = VEHICLE_PARAMS_UNSET;
						(*v)->params.doors = VEHICLE_PARAMS_UNSET;
						(*v)->params.bonnet = VEHICLE_PARAMS_UNSET;
						(*v)->params.boot = VEHICLE_PARAMS_UNSET;
						(*v)->params.objective = VEHICLE_PARAMS_UNSET;
						(*v)->params.siren = VEHICLE_PARAMS_UNSET;
						(*v)->params.cardoors.driver = VEHICLE_PARAMS_UNSET;
						(*v)->params.cardoors.passenger = VEHICLE_PARAMS_UNSET;
						(*v)->params.cardoors.backleft = VEHICLE_PARAMS_UNSET;
						(*v)->params.cardoors.backright = VEHICLE_PARAMS_UNSET;
						(*v)->params.carwindows.driver = VEHICLE_PARAMS_UNSET;
						(*v)->params.carwindows.passenger = VEHICLE_PARAMS_UNSET;
						(*v)->params.carwindows.backleft = VEHICLE_PARAMS_UNSET;
						(*v)->params.carwindows.backright = VEHICLE_PARAMS_UNSET;

						if((*v)->cell)
						{
							core->getGrid()->removeVehicle(*v, true);
						}

						boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find((*v)->vehicleID);
						if (i != core->getData()->internalVehicles.end())
						{
							SetVehicleToRespawn(i->second);
						}
						else
						{
							for (std::set<AMX*>::iterator a = core->getData()->interfaces.begin(); a != core->getData()->interfaces.end(); ++a)
							{
								int amxIndex = 0;
								if (!amx_FindPublic(*a, "OnDynamicVehicleSpawn", &amxIndex))
								{
									amx_Push(*a, static_cast<cell>((*v)->vehicleID));
									amx_Exec(*a, NULL, amxIndex);
								}
							}
						}
						//sampgdk_logprintf("respawn occupied: %d", (*v)->vehicleID);
						v = movingVehicles.erase(v);
						continue;
					}
				}
			}
	
			boost::unordered_map<int, int>::iterator i = core->getData()->internalVehicles.find((*v)->vehicleID);
			if(i != core->getData()->internalVehicles.end())
			{
				if ((*v)->vehicleID)
				{
					adjust = GetVehiclePos(i->second, &(*v)->position[0], &(*v)->position[1], &(*v)->position[2]);
					GetVehicleZAngle(i->second, &(*v)->angle);
					GetVehicleHealth(i->second, &(*v)->health);
					GetVehicleRotationQuat(i->second, &(*v)->qw, &(*v)->qx, &(*v)->qy, &(*v)->qz);
					(*v)->lastUpdatedTick = GetTickCount();
				}

				if (adjust)
				{
					if ((*v)->cell)
					{
						core->getGrid()->removeVehicle(*v, true);
					}
				}
				else
				{
					sampgdk_logprintf("fill infinity: %d", (*v)->vehicleID);
					(*v)->position.fill(std::numeric_limits<float>::infinity());
				}
			}
		}
		v++;
	}
}