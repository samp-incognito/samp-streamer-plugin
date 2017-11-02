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

#include "streamer.h"

#include "core.h"
#include "utility.h"

#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>
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
	averageElapsedTime = 0.0f;
	chunkSize[STREAMER_TYPE_OBJECT] = 100;
	chunkSize[STREAMER_TYPE_MAP_ICON] = 100;
	chunkSize[STREAMER_TYPE_3D_TEXT_LABEL] = 100;
	chunkStreamingEnabled = false;
	lastUpdateTime = 0.0f;
	tickCount = 0;
	tickRate = 50;
	velocityBoundaries = boost::make_tuple(0.25f, 7.5f);
}

std::size_t Streamer::getChunkSize(int type)
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

bool Streamer::setChunkSize(int type, std::size_t value)
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

void Streamer::calculateAverageElapsedTime()
{
	boost::chrono::steady_clock::time_point currentTime = boost::chrono::steady_clock::now();
	static boost::chrono::steady_clock::time_point lastRecordedTime;
	static Eigen::Array<float, 5, 1> recordedTimes = Eigen::Array<float, 5, 1>::Zero();
	if (lastRecordedTime.time_since_epoch().count())
	{
		if (!(recordedTimes > 0).all())
		{
			boost::chrono::duration<float> elapsedTime = currentTime - lastRecordedTime;
			recordedTimes[(recordedTimes > 0).count()] = elapsedTime.count();
		}
		else
		{
			averageElapsedTime = recordedTimes.mean() * 50.0f;
			recordedTimes.setZero();
		}
	}
	lastRecordedTime = currentTime;
}

void Streamer::startAutomaticUpdate()
{
	if (!core->getData()->interfaces.empty())
	{
		boost::chrono::steady_clock::time_point currentTime = boost::chrono::steady_clock::now();
		if (!core->getData()->players.empty())
		{
			bool updatedActiveItems = false;
			for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
			{
				if (chunkStreamingEnabled && p->second.processingChunks.any())
				{
					performPlayerChunkUpdate(p->second, true);
				}
				else
				{
					if (++p->second.tickCount >= p->second.tickRate)
					{
						if (!updatedActiveItems)
						{
							processActiveItems();
							updatedActiveItems = true;
						}
						if (!p->second.delayedUpdate)
						{
							performPlayerUpdate(p->second, true);
						}
						else
						{
							startManualUpdate(p->second, p->second.delayedUpdateType);
						}
						p->second.tickCount = 0;
					}
				}
			}
		}
		else
		{
			processActiveItems();
		}
		if (++tickCount >= tickRate)
		{
			for (std::vector<int>::const_iterator t = core->getData()->typePriority.begin(); t != core->getData()->typePriority.end(); ++t)
			{
				switch (*t)
				{
					case STREAMER_TYPE_PICKUP:
					{
						if (Utility::haveAllPlayersCheckedPickups())
						{
							streamPickups();
						}
						break;
					}
					case STREAMER_TYPE_ACTOR:
					{
						Utility::processPendingDestroyedActors();
						if (Utility::haveAllPlayersCheckedActors())
						{
							streamActors();
						}
						break;
					}
				}
			}
			executeCallbacks();
			tickCount = 0;
		}
		calculateAverageElapsedTime();
		lastUpdateTime = boost::chrono::duration<float, boost::milli>(boost::chrono::steady_clock::now() - currentTime).count();
	}
}

void Streamer::startManualUpdate(Player &player, int type)
{
	std::bitset<STREAMER_MAX_TYPES> enabledItems = player.enabledItems;
	if (player.delayedUpdate)
	{
		if (player.delayedUpdateTime.time_since_epoch() <= boost::chrono::steady_clock::now().time_since_epoch())
		{
			if (player.delayedUpdateFreeze)
			{
				sampgdk::TogglePlayerControllable(player.playerID, true);
			}
			player.delayedUpdate = false;
		}
	}
	if (type >= 0 && type < STREAMER_MAX_TYPES)
	{
		if (chunkStreamingEnabled)
		{
			switch (type)
			{
				case STREAMER_TYPE_OBJECT:
				{
					player.discoveredObjects.clear();
					player.existingObjects.clear();
					player.processingChunks.reset(STREAMER_TYPE_OBJECT);
					break;
				}
				case STREAMER_TYPE_MAP_ICON:
				{
					player.discoveredMapIcons.clear();
					player.existingMapIcons.clear();
					player.processingChunks.reset(STREAMER_TYPE_MAP_ICON);
					break;
				}
				case STREAMER_TYPE_3D_TEXT_LABEL:
				{
					player.discoveredTextLabels.clear();
					player.existingTextLabels.clear();
					player.processingChunks.reset(STREAMER_TYPE_3D_TEXT_LABEL);
					break;
				}
			}
		}
		player.enabledItems.reset();
		player.enabledItems.set(type);
	}
	else if (chunkStreamingEnabled)
	{
		player.discoveredMapIcons.clear();
		player.discoveredObjects.clear();
		player.discoveredTextLabels.clear();
		player.existingMapIcons.clear();
		player.existingObjects.clear();
		player.existingTextLabels.clear();
		player.processingChunks.reset();
	}
	processActiveItems();
	performPlayerUpdate(player, false);
	if (chunkStreamingEnabled)
	{
		performPlayerChunkUpdate(player, false);
	}
	player.enabledItems = enabledItems;
}

void Streamer::performPlayerChunkUpdate(Player &player, bool automatic)
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

void Streamer::performPlayerUpdate(Player &player, bool automatic)
{
	Eigen::Vector3f delta = Eigen::Vector3f::Zero(), position = player.position;
	bool update = true;
	if (automatic)
	{
		player.interiorID = sampgdk::GetPlayerInterior(player.playerID);
		player.worldID = sampgdk::GetPlayerVirtualWorld(player.playerID);
		if (!player.updateUsingCameraPosition)
		{
			int state = sampgdk::GetPlayerState(player.playerID);
			if ((state != PLAYER_STATE_NONE && state != PLAYER_STATE_WASTED) || (state == PLAYER_STATE_SPECTATING && !player.requestingClass))
			{
				if (!sampgdk::IsPlayerInAnyVehicle(player.playerID))
				{
					sampgdk::GetPlayerPos(player.playerID, &player.position[0], &player.position[1], &player.position[2]);
				}
				else
				{
					sampgdk::GetVehiclePos(sampgdk::GetPlayerVehicleID(player.playerID), &player.position[0], &player.position[1], &player.position[2]);
				}
				if (player.position != position)
				{
					position = player.position;
					Eigen::Vector3f velocity = Eigen::Vector3f::Zero();
					if (state == PLAYER_STATE_ONFOOT)
					{
						sampgdk::GetPlayerVelocity(player.playerID, &velocity[0], &velocity[1], &velocity[2]);
					}
					else if (state == PLAYER_STATE_DRIVER || state == PLAYER_STATE_PASSENGER)
					{
						sampgdk::GetVehicleVelocity(sampgdk::GetPlayerVehicleID(player.playerID), &velocity[0], &velocity[1], &velocity[2]);
					}
					float velocityNorm = velocity.squaredNorm();
					if (velocityNorm > velocityBoundaries.get<0>() && velocityNorm < velocityBoundaries.get<1>())
					{
						delta = velocity * averageElapsedTime;
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
		else
		{
			sampgdk::GetPlayerCameraPos(player.playerID, &player.position[0], &player.position[1], &player.position[2]);
		}
		if (player.delayedCheckpoint)
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(player.delayedCheckpoint);
			if (c != core->getData()->checkpoints.end())
			{
				sampgdk::SetPlayerCheckpoint(player.playerID, c->second->position[0], c->second->position[1], c->second->position[2], c->second->size);
				if (c->second->streamCallbacks)
				{
					streamInCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_CP, c->first));
				}
				player.visibleCheckpoint = c->first;
			}
			player.delayedCheckpoint = 0;
		}
		else if (player.delayedRaceCheckpoint)
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(player.delayedRaceCheckpoint);
			if (r != core->getData()->raceCheckpoints.end())
			{
				sampgdk::SetPlayerRaceCheckpoint(player.playerID, r->second->type, r->second->position[0], r->second->position[1], r->second->position[2], r->second->next[0], r->second->next[1], r->second->next[2], r->second->size);
				if (r->second->streamCallbacks)
				{
					streamInCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_RACE_CP, r->first));
				}
				player.visibleRaceCheckpoint = r->first;
			}
			player.delayedRaceCheckpoint = 0;
		}
	}
	std::vector<SharedCell> cells;
	if (update)
	{
		core->getGrid()->findAllCellsForPlayer(player, cells);
	}
	else
	{
		core->getGrid()->findMinimalCellsForPlayer(player, cells);
	}
	if (!cells.empty())
	{
		if (!delta.isZero())
		{
			player.position += delta;
		}
		for (std::vector<int>::const_iterator t = core->getData()->typePriority.begin(); t != core->getData()->typePriority.end(); ++t)
		{
			if (update)
			{
				switch (*t)
				{
					case STREAMER_TYPE_OBJECT:
					{
						if (!core->getData()->objects.empty() && player.enabledItems[STREAMER_TYPE_OBJECT] && !sampgdk::IsPlayerNPC(player.playerID))
						{
							if (chunkStreamingEnabled)
							{
								discoverObjects(player, cells);
							}
							else
							{
								processObjects(player, cells);
							}
						}
						break;
					}
					case STREAMER_TYPE_CP:
					{
						if (!core->getData()->checkpoints.empty() && player.enabledItems[STREAMER_TYPE_CP])
						{
							processCheckpoints(player, cells);
						}
						break;
					}
					case STREAMER_TYPE_RACE_CP:
					{
						if (!core->getData()->raceCheckpoints.empty() && player.enabledItems[STREAMER_TYPE_RACE_CP])
						{
							processRaceCheckpoints(player, cells);
						}
						break;
					}
					case STREAMER_TYPE_MAP_ICON:
					{
						if (!core->getData()->mapIcons.empty() && player.enabledItems[STREAMER_TYPE_MAP_ICON] && !sampgdk::IsPlayerNPC(player.playerID))
						{
							if (chunkStreamingEnabled)
							{
								discoverMapIcons(player, cells);
							}
							else
							{
								processMapIcons(player, cells);
							}
						}
						break;
					}
					case STREAMER_TYPE_3D_TEXT_LABEL:
					{
						if (!core->getData()->textLabels.empty() && player.enabledItems[STREAMER_TYPE_3D_TEXT_LABEL] && !sampgdk::IsPlayerNPC(player.playerID))
						{
							if (chunkStreamingEnabled)
							{
								discoverTextLabels(player, cells);
							}
							else
							{
								processTextLabels(player, cells);
							}
						}
						break;
					}
					case STREAMER_TYPE_AREA:
					{
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
						break;
					}
				}
			}
			if (automatic)
			{
				switch (*t)
				{
					case STREAMER_TYPE_PICKUP:
					{
						if (!core->getData()->pickups.empty() && player.enabledItems[STREAMER_TYPE_PICKUP])
						{
							discoverPickups(player, cells);
						}
						break;
					}
					case STREAMER_TYPE_ACTOR:
					{
						if (!core->getData()->actors.empty() && player.enabledItems[STREAMER_TYPE_ACTOR] && !sampgdk::IsPlayerNPC(player.playerID))
						{
							discoverActors(player, cells);
						}
						break;
					}
				}
			}
		}
		if (!delta.isZero())
		{
			player.position = position;
		}
	}
}

void Streamer::executeCallbacks()
{
	if (!areaLeaveCallbacks.empty())
	{
		std::multimap<int, boost::tuple<int, int> > callbacks;
		std::swap(areaLeaveCallbacks, callbacks);
		for (std::multimap<int, boost::tuple<int, int> >::reverse_iterator c = callbacks.rbegin(); c != callbacks.rend(); ++c)
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(c->second.get<0>());
			if (a != core->getData()->areas.end())
			{
				for (std::set<AMX*>::iterator i = core->getData()->interfaces.begin(); i != core->getData()->interfaces.end(); ++i)
				{
					int amxIndex = 0;
					if (!amx_FindPublic(*i, "OnPlayerLeaveDynamicArea", &amxIndex))
					{
						amx_Push(*i, static_cast<cell>(c->second.get<0>()));
						amx_Push(*i, static_cast<cell>(c->second.get<1>()));
						amx_Exec(*i, NULL, amxIndex);
					}
				}
			}
		}
	}
	if (!areaEnterCallbacks.empty())
	{
		std::multimap<int, boost::tuple<int, int> > callbacks;
		std::swap(areaEnterCallbacks, callbacks);
		for (std::multimap<int, boost::tuple<int, int> >::reverse_iterator c = callbacks.rbegin(); c != callbacks.rend(); ++c)
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(c->second.get<0>());
			if (a != core->getData()->areas.end())
			{
				for (std::set<AMX*>::iterator i = core->getData()->interfaces.begin(); i != core->getData()->interfaces.end(); ++i)
				{
					int amxIndex = 0;
					if (!amx_FindPublic(*i, "OnPlayerEnterDynamicArea", &amxIndex))
					{
						amx_Push(*i, static_cast<cell>(c->second.get<0>()));
						amx_Push(*i, static_cast<cell>(c->second.get<1>()));
						amx_Exec(*i, NULL, amxIndex);
					}
				}
			}
		}
	}
	if (!objectMoveCallbacks.empty())
	{
		std::vector<int> callbacks;
		std::swap(objectMoveCallbacks, callbacks);
		for (std::vector<int>::const_iterator c = callbacks.begin(); c != callbacks.end(); ++c)
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(*c);
			if (o != core->getData()->objects.end())
			{
				for (std::set<AMX*>::iterator i = core->getData()->interfaces.begin(); i != core->getData()->interfaces.end(); ++i)
				{
					int amxIndex = 0;
					if (!amx_FindPublic(*i, "OnDynamicObjectMoved", &amxIndex))
					{
						amx_Push(*i, static_cast<cell>(*c));
						amx_Exec(*i, NULL, amxIndex);
					}
				}
			}
		}
	}
	if (!streamInCallbacks.empty())
	{
		std::vector<boost::tuple<int, int> > callbacks;
		std::swap(streamInCallbacks, callbacks);
		for (std::vector<boost::tuple<int, int> >::const_iterator c = callbacks.begin(); c != callbacks.end(); ++c)
		{
			switch (c->get<0>())
			{
				case STREAMER_TYPE_OBJECT:
				{
					if (core->getData()->objects.find(c->get<1>()) == core->getData()->objects.end())
					{
						continue;
					}
					break;
				}
				case STREAMER_TYPE_PICKUP:
				{
					if (core->getData()->pickups.find(c->get<1>()) == core->getData()->pickups.end())
					{
						continue;
					}
					break;
				}
				case STREAMER_TYPE_CP:
				{
					if (core->getData()->checkpoints.find(c->get<1>()) == core->getData()->checkpoints.end())
					{
						continue;
					}
					break;
				}
				case STREAMER_TYPE_RACE_CP:
				{
					if (core->getData()->raceCheckpoints.find(c->get<1>()) == core->getData()->raceCheckpoints.end())
					{
						continue;
					}
					break;
				}
				case STREAMER_TYPE_MAP_ICON:
				{
					if (core->getData()->mapIcons.find(c->get<1>()) == core->getData()->mapIcons.end())
					{
						continue;
					}
					break;
				}
				case STREAMER_TYPE_3D_TEXT_LABEL:
				{
					if (core->getData()->textLabels.find(c->get<1>()) == core->getData()->textLabels.end())
					{
						continue;
					}
					break;
				}
			}
			for (std::set<AMX*>::iterator i = core->getData()->interfaces.begin(); i != core->getData()->interfaces.end(); ++i)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*i, "Streamer_OnItemStreamIn", &amxIndex))
				{
					amx_Push(*i, static_cast<cell>(c->get<1>()));
					amx_Push(*i, static_cast<cell>(c->get<0>()));
					amx_Exec(*i, NULL, amxIndex);
				}
			}
		}
	}
	if (!streamOutCallbacks.empty())
	{
		std::vector<boost::tuple<int, int> > callbacks;
		std::swap(streamOutCallbacks, callbacks);
		for (std::vector<boost::tuple<int, int> >::const_iterator c = callbacks.begin(); c != callbacks.end(); ++c)
		{
			switch (c->get<0>())
			{
				case STREAMER_TYPE_OBJECT:
				{
					if (core->getData()->objects.find(c->get<1>()) == core->getData()->objects.end())
					{
						continue;
					}
					break;
				}
				case STREAMER_TYPE_PICKUP:
				{
					if (core->getData()->pickups.find(c->get<1>()) == core->getData()->pickups.end())
					{
						continue;
					}
					break;
				}
				case STREAMER_TYPE_CP:
				{
					if (core->getData()->checkpoints.find(c->get<1>()) == core->getData()->checkpoints.end())
					{
						continue;
					}
					break;
				}
				case STREAMER_TYPE_RACE_CP:
				{
					if (core->getData()->raceCheckpoints.find(c->get<1>()) == core->getData()->raceCheckpoints.end())
					{
						continue;
					}
					break;
				}
				case STREAMER_TYPE_MAP_ICON:
				{
					if (core->getData()->mapIcons.find(c->get<1>()) == core->getData()->mapIcons.end())
					{
						continue;
					}
					break;
				}
				case STREAMER_TYPE_3D_TEXT_LABEL:
				{
					if (core->getData()->textLabels.find(c->get<1>()) == core->getData()->textLabels.end())
					{
						continue;
					}
					break;
				}
			}
			for (std::set<AMX*>::iterator i = core->getData()->interfaces.begin(); i != core->getData()->interfaces.end(); ++i)
			{
				int amxIndex = 0;
				if (!amx_FindPublic(*i, "Streamer_OnItemStreamOut", &amxIndex))
				{
					amx_Push(*i, static_cast<cell>(c->get<1>()));
					amx_Push(*i, static_cast<cell>(c->get<0>()));
					amx_Exec(*i, NULL, amxIndex);
				}
			}
		}
	}
}

void Streamer::discoverActors(Player &player, const std::vector<SharedCell> &cells)
{
	for (std::vector<SharedCell>::const_iterator c = cells.begin(); c != cells.end(); ++c)
	{
		for (boost::unordered_map<int, Item::SharedActor>::const_iterator a = (*c)->actors.begin(); a != (*c)->actors.end(); ++a)
		{
			boost::unordered_map<int, Item::SharedActor>::iterator d = core->getData()->discoveredActors.find(a->first);
			if (d == core->getData()->discoveredActors.end())
			{
				if (doesPlayerSatisfyConditions(a->second->players, player.playerID, a->second->interiors, player.interiorID, a->second->worlds, player.worldID, a->second->areas, player.internalAreas, a->second->inverseAreaChecking))
				{
					if (a->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF || boost::geometry::comparable_distance(player.position, Eigen::Vector3f(a->second->position + a->second->positionOffset)) < (a->second->comparableStreamDistance * player.radiusMultipliers[STREAMER_TYPE_ACTOR]))
					{
						boost::unordered_map<int, int>::iterator i = core->getData()->internalActors.find(a->first);
						if (i == core->getData()->internalActors.end())
						{
							a->second->worldID = !a->second->worlds.empty() ? player.worldID : 0;
						}
						core->getData()->discoveredActors.insert(*a);
					}
				}
			}
		}
	}
	player.checkedActors = true;
}

void Streamer::streamActors()
{
	boost::unordered_map<int, int>::iterator i = core->getData()->internalActors.begin();
	while (i != core->getData()->internalActors.end())
	{
		boost::unordered_map<int, Item::SharedActor>::iterator d = core->getData()->discoveredActors.find(i->first);
		if (d == core->getData()->discoveredActors.end())
		{
			sampgdk::DestroyActor(i->second);
			i = core->getData()->internalActors.erase(i);
		}
		else
		{
			core->getData()->discoveredActors.erase(d);
			++i;
		}
	}
	std::multimap<int, Item::SharedActor> sortedActors;
	for (boost::unordered_map<int, Item::SharedActor>::iterator d = core->getData()->discoveredActors.begin(); d != core->getData()->discoveredActors.end(); ++d)
	{
		sortedActors.insert(std::make_pair(d->second->priority, d->second));
	}
	core->getData()->discoveredActors.clear();
	for (std::multimap<int, Item::SharedActor>::iterator s = sortedActors.begin(); s != sortedActors.end(); ++s)
	{
		if (core->getData()->internalActors.size() == core->getData()->getGlobalMaxVisibleItems(STREAMER_TYPE_ACTOR))
		{
			break;
		}
		int internalID = sampgdk::CreateActor(s->second->modelID, s->second->position[0], s->second->position[1], s->second->position[2], s->second->rotation);
		if (internalID == INVALID_ACTOR_ID)
		{
			break;
		}
		sampgdk::SetActorInvulnerable(internalID, s->second->invulnerable);
		sampgdk::SetActorHealth(internalID, s->second->health);
		sampgdk::SetActorVirtualWorld(internalID, s->second->worldID);
		if (s->second->anim)
		{
			sampgdk::ApplyActorAnimation(internalID, s->second->anim->lib.c_str(), s->second->anim->name.c_str(), s->second->anim->delta, s->second->anim->loop, s->second->anim->lockx, s->second->anim->locky, s->second->anim->freeze, s->second->anim->time);
		}
		core->getData()->internalActors.insert(std::make_pair(s->second->actorID, internalID));
	}
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		p->second.checkedActors = false;
	}
}

void Streamer::processAreas(Player &player, const std::vector<SharedCell> &cells)
{
	int state = sampgdk::GetPlayerState(player.playerID);
	for (std::vector<SharedCell>::const_iterator c = cells.begin(); c != cells.end(); ++c)
	{
		for (boost::unordered_map<int, Item::SharedArea>::const_iterator a = (*c)->areas.begin(); a != (*c)->areas.end(); ++a)
		{
			Streamer::processPlayerArea(player, a->second, state);
		}
	}
}

bool Streamer::processPlayerArea(Player &player, const Item::SharedArea &a, const int state)
{
	bool inArea = false;
	if (doesPlayerSatisfyConditions(a->players, player.playerID, a->interiors, player.interiorID, a->worlds, player.worldID) && ((!a->spectateMode && state != PLAYER_STATE_SPECTATING) || a->spectateMode))
	{
		inArea = Utility::isPointInArea(player.position, a);
	}
	boost::unordered_set<int>::iterator foundArea = player.internalAreas.find(a->areaID);
	if (inArea)
	{
		if (foundArea == player.internalAreas.end())
		{
			player.internalAreas.insert(a->areaID);
			areaEnterCallbacks.insert(std::make_pair(a->priority, boost::make_tuple(a->areaID, player.playerID)));
		}
		if (a->cell)
		{
			player.visibleCell->areas.insert(std::make_pair(a->areaID, a));
		}
	}
	else
	{
		if (foundArea != player.internalAreas.end())
		{
			player.internalAreas.erase(foundArea);
			areaLeaveCallbacks.insert(std::make_pair(a->priority, boost::make_tuple(a->areaID, player.playerID)));
		}
	}
	return inArea;
}

void Streamer::processCheckpoints(Player &player, const std::vector<SharedCell> &cells)
{
	std::multimap<std::pair<int, float>, Item::SharedCheckpoint, Item::PairCompare> discoveredCheckpoints;
	for (std::vector<SharedCell>::const_iterator c = cells.begin(); c != cells.end(); ++c)
	{
		for (boost::unordered_map<int, Item::SharedCheckpoint>::const_iterator d = (*c)->checkpoints.begin(); d != (*c)->checkpoints.end(); ++d)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (doesPlayerSatisfyConditions(d->second->players, player.playerID, d->second->interiors, player.interiorID, d->second->worlds, player.worldID, d->second->areas, player.internalAreas, d->second->inverseAreaChecking))
			{
				if (d->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
				{
					distance = std::numeric_limits<float>::infinity() * -1.0f;
				}
				else
				{
					distance = static_cast<float>(boost::geometry::comparable_distance(player.position, Eigen::Vector3f(d->second->position + d->second->positionOffset)));
				}
			}
			if (distance < (d->second->comparableStreamDistance * player.radiusMultipliers[STREAMER_TYPE_CP]))
			{
				discoveredCheckpoints.insert(std::make_pair(std::make_pair(d->second->priority, distance), d->second));
			}
			else
			{
				if (d->first == player.visibleCheckpoint)
				{
					sampgdk::DisablePlayerCheckpoint(player.playerID);
					if (d->second->streamCallbacks)
					{
						streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_CP, d->second->checkpointID));
					}
					player.activeCheckpoint = 0;
					player.visibleCheckpoint = 0;

				}
			}
		}
	}
	if (!discoveredCheckpoints.empty())
	{
		std::multimap<std::pair<int, float>, Item::SharedCheckpoint, Item::PairCompare>::iterator d = discoveredCheckpoints.begin();
		if (d->second->checkpointID != player.visibleCheckpoint)
		{
			if (player.visibleCheckpoint)
			{
				sampgdk::DisablePlayerCheckpoint(player.playerID);
				if (d->second->streamCallbacks)
				{
					streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_CP, d->second->checkpointID));
				}
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

// Stable streaming code (map icons)

void Streamer::processMapIcons(Player &player, const std::vector<SharedCell> &cells)
{
	std::multimap<std::pair<int, float>, Item::SharedMapIcon, Item::PairCompare> discoveredMapIcons, existingMapIcons;
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
					distance = static_cast<float>(boost::geometry::comparable_distance(player.position, m->second->position));
				}
			}
			boost::unordered_map<int, int>::iterator i = player.internalMapIcons.find(m->first);
			if (distance < (m->second->comparableStreamDistance * player.radiusMultipliers[STREAMER_TYPE_MAP_ICON]))
			{
				if (i == player.internalMapIcons.end())
				{
					discoveredMapIcons.insert(std::make_pair(std::make_pair(m->second->priority, distance), m->second));
				}
				else
				{
					if (m->second->cell)
					{
						player.visibleCell->mapIcons.insert(*m);
					}
					existingMapIcons.insert(std::make_pair(std::make_pair(m->second->priority, distance), m->second));
				}
			}
			else
			{
				if (i != player.internalMapIcons.end())
				{
					sampgdk::RemovePlayerMapIcon(player.playerID, i->second);
					if (m->second->streamCallbacks)
					{
						streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_MAP_ICON, m->first));
					}
					player.mapIconIdentifier.remove(i->second, player.internalMapIcons.size());
					player.internalMapIcons.erase(i);
				}
			}
		}
	}
	for (std::multimap<std::pair<int, float>, Item::SharedMapIcon, Item::PairCompare>::iterator d = discoveredMapIcons.begin(); d != discoveredMapIcons.end(); ++d)
	{
		boost::unordered_map<int, int>::iterator i = player.internalMapIcons.find(d->second->mapIconID);
		if (i != player.internalMapIcons.end())
		{
			continue;
		}
		if (player.internalMapIcons.size() == player.maxVisibleMapIcons)
		{
			std::multimap<std::pair<int, float>, Item::SharedMapIcon, Item::PairCompare>::reverse_iterator e = existingMapIcons.rbegin();
			if (e != existingMapIcons.rend())
			{
				if (e->first.first < d->first.first || (e->first.second > STREAMER_STATIC_DISTANCE_CUTOFF && d->first.second < e->first.second))
				{
					boost::unordered_map<int, int>::iterator i = player.internalMapIcons.find(e->second->mapIconID);
					if (i != player.internalMapIcons.end())
					{
						sampgdk::RemovePlayerMapIcon(player.playerID, i->second);
						if (e->second->streamCallbacks)
						{
							streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_MAP_ICON, e->second->mapIconID));
						}
						player.mapIconIdentifier.remove(i->second, player.internalMapIcons.size());
						player.internalMapIcons.erase(i);
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
		sampgdk::SetPlayerMapIcon(player.playerID, internalID, d->second->position[0], d->second->position[1], d->second->position[2], d->second->type, d->second->color, d->second->style);
		if (d->second->streamCallbacks)
		{
			streamInCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_MAP_ICON, d->second->mapIconID));
		}
		player.internalMapIcons.insert(std::make_pair(d->second->mapIconID, internalID));
		if (d->second->cell)
		{
			player.visibleCell->mapIcons.insert(std::make_pair(d->second->mapIconID, d->second));
		}
	}
}

// Experimental chunk streaming code (map icons - first portion)

void Streamer::discoverMapIcons(Player &player, const std::vector<SharedCell> &cells)
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

// Experimental chunk streaming code (map icons - second portion)

void Streamer::streamMapIcons(Player &player, bool automatic)
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
							boost::unordered_map<int, int>::iterator i = player.internalMapIcons.find(e->second.get<0>());
							if (i != player.internalMapIcons.end())
							{
								sampgdk::RemovePlayerMapIcon(player.playerID, i->second);
								if (e->second.get<1>()->streamCallbacks)
								{
									streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_MAP_ICON, e->second.get<0>()));
								}
								player.mapIconIdentifier.remove(i->second, player.internalMapIcons.size());
								player.internalMapIcons.erase(i);
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

// Stable streaming code (objects)

void Streamer::processObjects(Player &player, const std::vector<SharedCell> &cells)
{
	std::multimap<std::pair<int, float>, Item::SharedObject, Item::PairCompare> discoveredObjects, existingObjects;
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
						distance = static_cast<float>(boost::geometry::comparable_distance(player.position, o->second->attach->position)) +  std::numeric_limits<float>::epsilon();
					}
					else
					{
						distance = static_cast<float>(boost::geometry::comparable_distance(player.position, o->second->position));
					}
				}
			}
			boost::unordered_map<int, int>::iterator i = player.internalObjects.find(o->first);
			if (distance < (o->second->comparableStreamDistance * player.radiusMultipliers[STREAMER_TYPE_OBJECT]))
			{
				if (i == player.internalObjects.end())
				{
					discoveredObjects.insert(std::make_pair(std::make_pair(o->second->priority, distance), o->second));
				}
				else
				{
					if (o->second->cell)
					{
						player.visibleCell->objects.insert(*o);
					}
					existingObjects.insert(std::make_pair(std::make_pair(o->second->priority, distance), o->second));
				}
			}
			else
			{
				if (i != player.internalObjects.end())
				{
					sampgdk::DestroyPlayerObject(player.playerID, i->second);
					if (o->second->streamCallbacks)
					{
						streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_OBJECT, o->first));
					}
					player.internalObjects.erase(i);
				}
			}
		}
	}
	for (std::multimap<std::pair<int, float>, Item::SharedObject, Item::PairCompare>::iterator d = discoveredObjects.begin(); d != discoveredObjects.end(); ++d)
	{
		boost::unordered_map<int, int>::iterator i = player.internalObjects.find(d->second->objectID);
		if (i != player.internalObjects.end())
		{
			continue;
		}
		int internalBaseID = INVALID_STREAMER_ID;
		if (d->second->attach)
		{
			if (d->second->attach->object != INVALID_STREAMER_ID)
			{
				boost::unordered_map<int, int>::iterator i = player.internalObjects.find(d->second->attach->object);
				if (i == player.internalObjects.end())
				{
					continue;
				}
				internalBaseID = i->second;
			}
		}
		if (player.internalObjects.size() == player.currentVisibleObjects)
		{
			std::multimap<std::pair<int, float>, Item::SharedObject, Item::PairCompare>::reverse_iterator e = existingObjects.rbegin();
			if (e != existingObjects.rend())
			{
				if (e->first.first < d->first.first || (e->first.second > STREAMER_STATIC_DISTANCE_CUTOFF && d->first.second < e->first.second))
				{
					boost::unordered_map<int, int>::iterator i = player.internalObjects.find(e->second->objectID);
					if (i != player.internalObjects.end())
					{
						sampgdk::DestroyPlayerObject(player.playerID, i->second);
						if (e->second->streamCallbacks)
						{
							streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_OBJECT, e->second->objectID));
						}
						player.internalObjects.erase(i);
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
		int internalID = sampgdk::CreatePlayerObject(player.playerID, d->second->modelID, d->second->position[0], d->second->position[1], d->second->position[2], d->second->rotation[0], d->second->rotation[1], d->second->rotation[2], d->second->drawDistance);
		if (internalID == INVALID_OBJECT_ID)
		{
			player.currentVisibleObjects = player.internalObjects.size();
			break;
		}
		if (d->second->streamCallbacks)
		{
			streamInCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_OBJECT, d->second->objectID));
		}
		if (d->second->attach)
		{
			if (internalBaseID != INVALID_STREAMER_ID)
			{
				static AMX_NATIVE native = sampgdk::FindNative("AttachPlayerObjectToObject");
				if (native != NULL)
				{
					sampgdk::InvokeNative(native, "dddffffffb", player.playerID, internalID, internalBaseID, d->second->attach->positionOffset[0], d->second->attach->positionOffset[1], d->second->attach->positionOffset[2], d->second->attach->rotation[0], d->second->attach->rotation[1], d->second->attach->rotation[2], d->second->attach->syncRotation);
				}
			}
			else if (d->second->attach->player != INVALID_PLAYER_ID)
			{
				static AMX_NATIVE native = sampgdk::FindNative("AttachPlayerObjectToPlayer");
				if (native != NULL)
				{
					sampgdk::InvokeNative(native, "dddffffffd", player.playerID, internalID, d->second->attach->player, d->second->attach->positionOffset[0], d->second->attach->positionOffset[1], d->second->attach->positionOffset[2], d->second->attach->rotation[0], d->second->attach->rotation[1], d->second->attach->rotation[2], 1);
				}
			}
			else if (d->second->attach->vehicle != INVALID_VEHICLE_ID)
			{
				sampgdk::AttachPlayerObjectToVehicle(player.playerID, internalID, d->second->attach->vehicle, d->second->attach->positionOffset[0], d->second->attach->positionOffset[1], d->second->attach->positionOffset[2], d->second->attach->rotation[0], d->second->attach->rotation[1], d->second->attach->rotation[2]);
			}
		}
		else if (d->second->move)
		{
			sampgdk::MovePlayerObject(player.playerID, internalID, d->second->move->position.get<0>()[0], d->second->move->position.get<0>()[1], d->second->move->position.get<0>()[2], d->second->move->speed, d->second->move->rotation.get<0>()[0], d->second->move->rotation.get<0>()[1], d->second->move->rotation.get<0>()[2]);
		}
		for (boost::unordered_map<int, Item::Object::Material>::iterator m = d->second->materials.begin(); m != d->second->materials.end(); ++m)
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
		if (d->second->noCameraCollision)
		{
			sampgdk::SetPlayerObjectNoCameraCol(player.playerID, internalID);
		}
		player.internalObjects.insert(std::make_pair(d->second->objectID, internalID));
		if (d->second->cell)
		{
			player.visibleCell->objects.insert(std::make_pair(d->second->objectID, d->second));
		}
	}
}

// Experimental chunk streaming code (objects - first portion)

void Streamer::discoverObjects(Player &player, const std::vector<SharedCell> &cells)
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

// Experimental chunk streaming code (objects - second portion)

void Streamer::streamObjects(Player &player, bool automatic)
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
						boost::unordered_map<int, int>::iterator i = player.internalObjects.find(d->second.get<1>()->attach->object);
						if (i == player.internalObjects.end())
						{
							d = player.discoveredObjects.left.erase(d);
							continue;
						}
						internalBaseID = i->second;
					}
				}
				if (player.internalObjects.size() == player.currentVisibleObjects)
				{
					Item::Bimap<Item::SharedObject>::Type::left_reverse_iterator e = player.existingObjects.left.rbegin();
					if (e != player.existingObjects.left.rend())
					{
						if (e->first.get<0>() < d->first.get<0>() || (e->first.get<1>() > STREAMER_STATIC_DISTANCE_CUTOFF && d->first.get<1>() < e->first.get<1>()))
						{
							boost::unordered_map<int, int>::iterator i = player.internalObjects.find(e->second.get<0>());
							if (i != player.internalObjects.end())
							{
								sampgdk::DestroyPlayerObject(player.playerID, i->second);
								if (e->second.get<1>()->streamCallbacks)
								{
									streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_OBJECT, e->second.get<0>()));
								}
								player.internalObjects.erase(i);
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

void Streamer::discoverPickups(Player &player, const std::vector<SharedCell> &cells)
{
	for (std::vector<SharedCell>::const_iterator c = cells.begin(); c != cells.end(); ++c)
	{
		for (boost::unordered_map<int, Item::SharedPickup>::const_iterator p = (*c)->pickups.begin(); p != (*c)->pickups.end(); ++p)
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator d = core->getData()->discoveredPickups.find(p->first);
			if (d == core->getData()->discoveredPickups.end())
			{
				if (doesPlayerSatisfyConditions(p->second->players, player.playerID, p->second->interiors, player.interiorID, p->second->worlds, player.worldID, p->second->areas, player.internalAreas, p->second->inverseAreaChecking))
				{
					if (p->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF || boost::geometry::comparable_distance(player.position, Eigen::Vector3f(p->second->position + p->second->positionOffset)) < (p->second->comparableStreamDistance * player.radiusMultipliers[STREAMER_TYPE_PICKUP]))
					{
						boost::unordered_map<int, int>::iterator i = core->getData()->internalPickups.find(p->first);
						if (i == core->getData()->internalPickups.end())
						{
							p->second->worldID = !p->second->worlds.empty() ? player.worldID : -1;
						}
						core->getData()->discoveredPickups.insert(*p);
					}
				}
			}
		}
	}
	player.checkedPickups = true;
}

void Streamer::streamPickups()
{
	boost::unordered_map<int, int>::iterator i = core->getData()->internalPickups.begin();
	while (i != core->getData()->internalPickups.end())
	{
		boost::unordered_map<int, Item::SharedPickup>::iterator d = core->getData()->discoveredPickups.find(i->first);
		if (d == core->getData()->discoveredPickups.end())
		{
			sampgdk::DestroyPickup(i->second);
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(i->first);
			if (p != core->getData()->pickups.end())
			{
				if (p->second->streamCallbacks)
				{
					streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_PICKUP, i->first));
				}
			}
			i = core->getData()->internalPickups.erase(i);
		}
		else
		{
			core->getData()->discoveredPickups.erase(d);
			++i;
		}
	}
	std::multimap<int, Item::SharedPickup> sortedPickups;
	for (boost::unordered_map<int, Item::SharedPickup>::iterator d = core->getData()->discoveredPickups.begin(); d != core->getData()->discoveredPickups.end(); ++d)
	{
		sortedPickups.insert(std::make_pair(d->second->priority, d->second));
	}
	core->getData()->discoveredPickups.clear();
	for (std::multimap<int, Item::SharedPickup>::iterator s = sortedPickups.begin(); s != sortedPickups.end(); ++s)
	{
		if (core->getData()->internalPickups.size() == core->getData()->getGlobalMaxVisibleItems(STREAMER_TYPE_PICKUP))
		{
			break;
		}
		int internalID = sampgdk::CreatePickup(s->second->modelID, s->second->type, s->second->position[0], s->second->position[1], s->second->position[2], s->second->worldID);
		if (internalID == INVALID_PICKUP_ID)
		{
			break;
		}
		if (s->second->streamCallbacks)
		{
			streamInCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_PICKUP, s->second->pickupID));
		}
		core->getData()->internalPickups.insert(std::make_pair(s->second->pickupID, internalID));
	}
	for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
	{
		p->second.checkedPickups = false;
	}
}

void Streamer::processRaceCheckpoints(Player &player, const std::vector<SharedCell> &cells)
{
	std::multimap<std::pair<int, float>, Item::SharedRaceCheckpoint, Item::PairCompare> discoveredRaceCheckpoints;
	for (std::vector<SharedCell>::const_iterator c = cells.begin(); c != cells.end(); ++c)
	{
		for (boost::unordered_map<int, Item::SharedRaceCheckpoint>::const_iterator r = (*c)->raceCheckpoints.begin(); r != (*c)->raceCheckpoints.end(); ++r)
		{
			float distance = std::numeric_limits<float>::infinity();
			if (doesPlayerSatisfyConditions(r->second->players, player.playerID, r->second->interiors, player.interiorID, r->second->worlds, player.worldID, r->second->areas, player.internalAreas, r->second->inverseAreaChecking))
			{
				if (r->second->comparableStreamDistance < STREAMER_STATIC_DISTANCE_CUTOFF)
				{
					distance = std::numeric_limits<float>::infinity() * -1.0f;
				}
				else
				{
					distance = static_cast<float>(boost::geometry::comparable_distance(player.position, Eigen::Vector3f(r->second->position + r->second->positionOffset)));
				}
			}
			if (distance < (r->second->comparableStreamDistance * player.radiusMultipliers[STREAMER_TYPE_RACE_CP]))
			{
				discoveredRaceCheckpoints.insert(std::make_pair(std::make_pair(r->second->priority, distance), r->second));
			}
			else
			{
				if (r->first == player.visibleRaceCheckpoint)
				{
					sampgdk::DisablePlayerRaceCheckpoint(player.playerID);
					if (r->second->streamCallbacks)
					{
						streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_RACE_CP, r->second->raceCheckpointID));
					}
					player.activeRaceCheckpoint = 0;
					player.visibleRaceCheckpoint = 0;
				}
			}
		}
	}
	if (!discoveredRaceCheckpoints.empty())
	{
		std::multimap<std::pair<int, float>, Item::SharedRaceCheckpoint, Item::PairCompare>::iterator d = discoveredRaceCheckpoints.begin();
		if (d->second->raceCheckpointID != player.visibleRaceCheckpoint)
		{
			if (player.visibleRaceCheckpoint)
			{
				sampgdk::DisablePlayerRaceCheckpoint(player.playerID);
				if (d->second->streamCallbacks)
				{
					streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_RACE_CP, d->second->raceCheckpointID));
				}
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

// Stable streaming code (3D text labels)

void Streamer::processTextLabels(Player &player, const std::vector<SharedCell> &cells)
{
	std::multimap<std::pair<int, float>, Item::SharedTextLabel, Item::PairCompare> discoveredTextLabels, existingTextLabels;
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
						distance = static_cast<float>(boost::geometry::comparable_distance(player.position, t->second->position));
					}
				}
			}
			boost::unordered_map<int, int>::iterator i = player.internalTextLabels.find(t->first);
			if (distance < (t->second->comparableStreamDistance * player.radiusMultipliers[STREAMER_TYPE_3D_TEXT_LABEL]))
			{
				if (i == player.internalTextLabels.end())
				{
					discoveredTextLabels.insert(std::make_pair(std::make_pair(t->second->priority, distance), t->second));
				}
				else
				{
					if (t->second->cell)
					{
						player.visibleCell->textLabels.insert(*t);
					}
					existingTextLabels.insert(std::make_pair(std::make_pair(t->second->priority, distance), t->second));
				}
			}
			else
			{
				if (i != player.internalTextLabels.end())
				{
					sampgdk::DeletePlayer3DTextLabel(player.playerID, i->second);
					if (t->second->streamCallbacks)
					{
						streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_3D_TEXT_LABEL, t->first));
					}
					player.internalTextLabels.erase(i);
				}
			}
		}
	}
	for (std::multimap<std::pair<int, float>, Item::SharedTextLabel, Item::PairCompare>::iterator d = discoveredTextLabels.begin(); d != discoveredTextLabels.end(); ++d)
	{
		boost::unordered_map<int, int>::iterator i = player.internalTextLabels.find(d->second->textLabelID);
		if (i != player.internalTextLabels.end())
		{
			continue;
		}
		if (player.internalTextLabels.size() == player.currentVisibleTextLabels)
		{
			std::multimap<std::pair<int, float>, Item::SharedTextLabel, Item::PairCompare>::reverse_iterator e = existingTextLabels.rbegin();
			if (e != existingTextLabels.rend())
			{
				if (e->first.first < d->first.first || (e->first.second > STREAMER_STATIC_DISTANCE_CUTOFF && d->first.second < e->first.second))
				{
					boost::unordered_map<int, int>::iterator i = player.internalTextLabels.find(e->second->textLabelID);
					if (i != player.internalTextLabels.end())
					{
						sampgdk::DeletePlayer3DTextLabel(player.playerID, i->second);
						if (e->second->streamCallbacks)
						{
							streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_3D_TEXT_LABEL, e->second->textLabelID));
						}
						player.internalTextLabels.erase(i);
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
		int internalID = sampgdk::CreatePlayer3DTextLabel(player.playerID, d->second->text.c_str(), d->second->color, d->second->position[0], d->second->position[1], d->second->position[2], d->second->drawDistance, d->second->attach ? d->second->attach->player : INVALID_PLAYER_ID, d->second->attach ? d->second->attach->vehicle : INVALID_VEHICLE_ID, d->second->testLOS);
		if (internalID == INVALID_3DTEXT_ID)
		{
			player.currentVisibleTextLabels = player.internalTextLabels.size();
			break;
		}
		if (d->second->streamCallbacks)
		{
			streamInCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_3D_TEXT_LABEL, d->second->textLabelID));
		}
		player.internalTextLabels.insert(std::make_pair(d->second->textLabelID, internalID));
		if (d->second->cell)
		{
			player.visibleCell->textLabels.insert(std::make_pair(d->second->textLabelID, d->second));
		}
	}
}

// Experimental chunk streaming code (3D text labels - first portion)

void Streamer::discoverTextLabels(Player &player, const std::vector<SharedCell> &cells)
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

// Experimental chunk streaming code (3D text labels - second portion)

void Streamer::streamTextLabels(Player &player, bool automatic)
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
							boost::unordered_map<int, int>::iterator i = player.internalTextLabels.find(e->second.get<0>());
							if (i != player.internalTextLabels.end())
							{
								sampgdk::DeletePlayer3DTextLabel(player.playerID, i->second);
								if (e->second.get<1>()->streamCallbacks)
								{
									streamOutCallbacks.push_back(boost::make_tuple(STREAMER_TYPE_3D_TEXT_LABEL, e->second.get<0>()));
								}
								player.internalTextLabels.erase(i);
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
	boost::unordered_set<Item::SharedObject>::iterator o = movingObjects.begin();
	while (o != movingObjects.end())
	{
		bool objectFinishedMoving = false;
		if ((*o)->move)
		{
			boost::chrono::duration<float, boost::milli> elapsedTime = boost::chrono::steady_clock::now() - (*o)->move->time;
			if (boost::chrono::duration_cast<boost::chrono::milliseconds>(elapsedTime).count() < (*o)->move->duration)
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
			if (((*a)->attach->object.get<0>() != INVALID_OBJECT_ID && (*a)->attach->object.get<1>() != STREAMER_OBJECT_TYPE_DYNAMIC) || ((*a)->attach->object.get<0>() != INVALID_STREAMER_ID && (*a)->attach->object.get<1>() == STREAMER_OBJECT_TYPE_DYNAMIC))
			{
				switch ((*a)->attach->object.get<1>())
				{
					case STREAMER_OBJECT_TYPE_GLOBAL:
					{
						Eigen::Vector3f position = Eigen::Vector3f::Zero(), rotation = Eigen::Vector3f::Zero();
						adjust = sampgdk::GetObjectPos((*a)->attach->object.get<0>(), &position[0], &position[1], &position[2]);
						sampgdk::GetObjectRot((*a)->attach->object.get<0>(), &rotation[0], &rotation[1], &rotation[2]);
						Utility::constructAttachedArea(*a, boost::variant<float, Eigen::Vector3f, Eigen::Vector4f>(rotation), position);
						break;
					}
					case STREAMER_OBJECT_TYPE_PLAYER:
					{
						Eigen::Vector3f position = Eigen::Vector3f::Zero(), rotation = Eigen::Vector3f::Zero();
						adjust = sampgdk::GetPlayerObjectPos((*a)->attach->object.get<2>(), (*a)->attach->object.get<0>(), &position[0], &position[1], &position[2]);
						sampgdk::GetPlayerObjectRot((*a)->attach->object.get<2>(), (*a)->attach->object.get<0>(), &rotation[0], &rotation[1], &rotation[2]);
						Utility::constructAttachedArea(*a, boost::variant<float, Eigen::Vector3f, Eigen::Vector4f>(rotation), position);
						break;
					}
					case STREAMER_OBJECT_TYPE_DYNAMIC:
					{
						boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find((*a)->attach->object.get<0>());
						if (o != core->getData()->objects.end())
						{
							Utility::constructAttachedArea(*a, boost::variant<float, Eigen::Vector3f, Eigen::Vector4f>(o->second->rotation), o->second->position);
							adjust = true;
						}
						break;
					}
				}
			}
			else if ((*a)->attach->player != INVALID_PLAYER_ID)
			{
				float heading = 0.0f;
				Eigen::Vector3f position = Eigen::Vector3f::Zero();
				adjust = sampgdk::GetPlayerPos((*a)->attach->player, &position[0], &position[1], &position[2]);
				sampgdk::GetPlayerFacingAngle((*a)->attach->player, &heading);
				Utility::constructAttachedArea(*a, boost::variant<float, Eigen::Vector3f, Eigen::Vector4f>(heading), position);
			}
			else if ((*a)->attach->vehicle != INVALID_VEHICLE_ID)
			{
				bool occupied = false;
				for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
				{
					if (sampgdk::GetPlayerState(p->first) == PLAYER_STATE_DRIVER)
					{
						if (sampgdk::GetPlayerVehicleID(p->first) == (*a)->attach->vehicle)
						{
							occupied = true;
							break;
						}
					}
				}
				Eigen::Vector3f position = Eigen::Vector3f::Zero();
				adjust = sampgdk::GetVehiclePos((*a)->attach->vehicle, &position[0], &position[1], &position[2]);
				if (!occupied)
				{
					float heading = 0.0f;
					sampgdk::GetVehicleZAngle((*a)->attach->vehicle, &heading);
					Utility::constructAttachedArea(*a, boost::variant<float, Eigen::Vector3f, Eigen::Vector4f>(heading), position);
				}
				else
				{
					Eigen::Vector4f quaternion = Eigen::Vector4f::Zero();
					sampgdk::GetVehicleRotationQuat((*a)->attach->vehicle, &quaternion[0], &quaternion[1], &quaternion[2], &quaternion[3]);
					Utility::constructAttachedArea(*a, boost::variant<float, Eigen::Vector3f, Eigen::Vector4f>(quaternion), position);
				}
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
				switch ((*a)->type)
				{
					case STREAMER_AREA_TYPE_CIRCLE:
					case STREAMER_AREA_TYPE_CYLINDER:
					{
						boost::get<Eigen::Vector2f>((*a)->attach->position).fill(std::numeric_limits<float>::infinity());
						break;
					}
					case STREAMER_AREA_TYPE_SPHERE:
					{
						boost::get<Eigen::Vector3f>((*a)->attach->position).fill(std::numeric_limits<float>::infinity());
						break;
					}
					case STREAMER_AREA_TYPE_RECTANGLE:
					{
						boost::get<Box2D>((*a)->attach->position).min_corner().fill(std::numeric_limits<float>::infinity());
						boost::get<Box2D>((*a)->attach->position).max_corner().fill(std::numeric_limits<float>::infinity());
						break;
					}
					case STREAMER_AREA_TYPE_CUBOID:
					{
						boost::get<Box3D>((*a)->attach->position).min_corner().fill(std::numeric_limits<float>::infinity());
						boost::get<Box3D>((*a)->attach->position).max_corner().fill(std::numeric_limits<float>::infinity());
						break;
					}
					case STREAMER_AREA_TYPE_POLYGON:
					{
						boost::get<Polygon2D>((*a)->attach->position).clear();
						break;
					}
				}
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
			Eigen::Vector3f position = (*o)->attach->position;
			if ((*o)->attach->object != INVALID_STREAMER_ID)
			{
				boost::unordered_map<int, Item::SharedObject>::iterator p = core->getData()->objects.find((*o)->attach->object);
				if (p != core->getData()->objects.end())
				{
					(*o)->attach->position = p->second->position;
					adjust = true;
				}
			}
			else if ((*o)->attach->player != INVALID_PLAYER_ID)
			{
				adjust = sampgdk::GetPlayerPos((*o)->attach->player, &(*o)->attach->position[0], &(*o)->attach->position[1], &(*o)->attach->position[2]);
			}
			else if ((*o)->attach->vehicle != INVALID_VEHICLE_ID)
			{
				adjust = sampgdk::GetVehiclePos((*o)->attach->vehicle, &(*o)->attach->position[0], &(*o)->attach->position[1], &(*o)->attach->position[2]);
			}
			if (adjust)
			{
				if ((*o)->cell && !(*o)->attach->position.isApprox(position))
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
		Eigen::Vector3f position = (*t)->attach->position;
		if ((*t)->attach)
		{
			if ((*t)->attach->player != INVALID_PLAYER_ID)
			{
				adjust = sampgdk::GetPlayerPos((*t)->attach->player, &(*t)->attach->position[0], &(*t)->attach->position[1], &(*t)->attach->position[2]);
			}
			else if ((*t)->attach->vehicle != INVALID_VEHICLE_ID)
			{
				adjust = sampgdk::GetVehiclePos((*t)->attach->vehicle, &(*t)->attach->position[0], &(*t)->attach->position[1], &(*t)->attach->position[2]);
			}
			if (adjust)
			{
				if ((*t)->cell && !(*t)->attach->position.isApprox(position))
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
