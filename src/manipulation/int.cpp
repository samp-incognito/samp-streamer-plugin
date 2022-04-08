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

#include "../precompiled.h"
#include "ompgdk.hpp"
#include "int.h"
#include "../core.h"
#include "../utility.h"

int Manipulation::getIntData(AMX *amx, cell *params)
{
	int error = -1;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AreaId:
					{
						return Utility::getFirstValueInContainer(o->second->areas);
					}
					case AttachedObject:
					{
						if (o->second->attach)
						{
							return o->second->attach->object;
						}
						return INVALID_STREAMER_ID;
					}
					case AttachedPlayer:
					{
						if (o->second->attach)
						{
							return o->second->attach->player;
						}
						return INVALID_PLAYER_ID;
					}
					case AttachedVehicle:
					{
						if (o->second->attach)
						{
							return o->second->attach->vehicle;
						}
						return INVALID_VEHICLE_ID;
					}
					case ExtraId:
					{
						return Utility::getFirstValueInContainer(o->second->extras);
					}
					case InteriorId:
					{
						return Utility::getFirstValueInContainer(o->second->interiors);
					}
					case ModelId:
					{
						return o->second->modelId;
					}
					case PlayerId:
					{
						return Utility::getFirstValueInContainer(o->second->players);
					}
					case Priority:
					{
						return o->second->priority;
					}
					case SyncRotation:
					{
						if (o->second->attach)
						{
							if (o->second->attach->object != INVALID_STREAMER_ID)
							{
								return o->second->attach->syncRotation != 0;
							}
						}
						return 0;
					}
					case WorldId:
					{
						return Utility::getFirstValueInContainer(o->second->worlds);
					}
					default:
					{
						if (static_cast<int>(params[3]) & 0x40000000)
						{
							boost::unordered_map<int, std::vector<int> >::const_iterator p = o->second->extraExtras.find(static_cast<int>(params[3]) & ~0xC0000000);
							if (p != o->second->extraExtras.end())
							{
								return Utility::getFirstValueInContainer(p->second);
							}
						}
						error = InvalidData;
						break;
					}
				}
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AreaId:
					{
						return Utility::getFirstValueInContainer(p->second->areas);
					}
					case ExtraId:
					{
						return Utility::getFirstValueInContainer(p->second->extras);
					}
					case InteriorId:
					{
						return Utility::getFirstValueInContainer(p->second->interiors);
					}
					case ModelId:
					{
						return p->second->modelId;
					}
					case PlayerId:
					{
						return Utility::getFirstValueInContainer(p->second->players);
					}
					case Priority:
					{
						return p->second->priority;
					}
					case Type:
					{
						return p->second->type;
					}
					case WorldId:
					{
						return Utility::getFirstValueInContainer(p->second->worlds);
					}
					default:
					{
						if (static_cast<int>(params[3]) & 0x40000000)
						{
							boost::unordered_map<int, std::vector<int> >::iterator x = p->second->extraExtras.find(static_cast<int>(params[3]) & ~0xC0000000);
							if (x != p->second->extraExtras.end())
							{
								return Utility::getFirstValueInContainer(x->second);
							}
						}
						error = InvalidData;
						break;
					}
				}
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AreaId:
					{
						return Utility::getFirstValueInContainer(c->second->areas);
					}
					case ExtraId:
					{
						return Utility::getFirstValueInContainer(c->second->extras);
					}
					case InteriorId:
					{
						return Utility::getFirstValueInContainer(c->second->interiors);
					}
					case PlayerId:
					{
						return Utility::getFirstValueInContainer(c->second->players);
					}
					case Priority:
					{
						return c->second->priority;
					}
					case WorldId:
					{
						return Utility::getFirstValueInContainer(c->second->worlds);
					}
					default:
					{
						if (static_cast<int>(params[3]) & 0x40000000)
						{
							boost::unordered_map<int, std::vector<int> >::iterator p = c->second->extraExtras.find(static_cast<int>(params[3]) & ~0xC0000000);
							if (p != c->second->extraExtras.end())
							{
								return Utility::getFirstValueInContainer(p->second);
							}
						}
						error = InvalidData;
						break;
					}
				}
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AreaId:
					{
						return Utility::getFirstValueInContainer(r->second->areas);
					}
					case ExtraId:
					{
						return Utility::getFirstValueInContainer(r->second->extras);
					}
					case InteriorId:
					{
						return Utility::getFirstValueInContainer(r->second->interiors);
					}
					case PlayerId:
					{
						return Utility::getFirstValueInContainer(r->second->players);
					}
					case Priority:
					{
						return r->second->priority;
					}
					case Type:
					{
						return r->second->type;
					}
					case WorldId:
					{
						return Utility::getFirstValueInContainer(r->second->worlds);
					}
					default:
					{
						if (static_cast<int>(params[3]) & 0x40000000)
						{
							boost::unordered_map<int, std::vector<int> >::iterator p = r->second->extraExtras.find(static_cast<int>(params[3]) & ~0xC0000000);
							if (p != r->second->extraExtras.end())
							{
								return Utility::getFirstValueInContainer(p->second);
							}
						}
						error = InvalidData;
						break;
					}
				}
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AreaId:
					{
						return Utility::getFirstValueInContainer(m->second->areas);
					}
					case Color:
					{
						return m->second->color;
					}
					case ExtraId:
					{
						return Utility::getFirstValueInContainer(m->second->extras);
					}
					case InteriorId:
					{
						return Utility::getFirstValueInContainer(m->second->interiors);
					}
					case PlayerId:
					{
						return Utility::getFirstValueInContainer(m->second->players);
					}
					case Priority:
					{
						return m->second->priority;
					}
					case Style:
					{
						return m->second->style;
					}
					case Type:
					{
						return m->second->type;
					}
					case WorldId:
					{
						return Utility::getFirstValueInContainer(m->second->worlds);
					}
					default:
					{
						if (static_cast<int>(params[3]) & 0x40000000)
						{
							boost::unordered_map<int, std::vector<int> >::iterator p = m->second->extraExtras.find(static_cast<int>(params[3]) & ~0xC0000000);
							if (p != m->second->extraExtras.end())
							{
								return Utility::getFirstValueInContainer(p->second);
							}
						}
						error = InvalidData;
						break;
					}
				}
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AreaId:
					{
						return Utility::getFirstValueInContainer(t->second->areas);
					}
					case AttachedPlayer:
					{
						if (t->second->attach)
						{
							return t->second->attach->player;
						}
						return INVALID_PLAYER_ID;
					}
					case AttachedVehicle:
					{
						if (t->second->attach)
						{
							return t->second->attach->vehicle;
						}
						return INVALID_VEHICLE_ID;
					}
					case Color:
					{
						return t->second->color;
					}
					case ExtraId:
					{
						return Utility::getFirstValueInContainer(t->second->extras);
					}
					case InteriorId:
					{
						return Utility::getFirstValueInContainer(t->second->interiors);
					}
					case PlayerId:
					{
						return Utility::getFirstValueInContainer(t->second->players);
					}
					case Priority:
					{
						return t->second->priority;
					}
					case TestLOS:
					{
						return t->second->testLOS;
					}
					case WorldId:
					{
						return Utility::getFirstValueInContainer(t->second->worlds);
					}
					default:
					{
						if (static_cast<int>(params[3]) & 0x40000000)
						{
							boost::unordered_map<int, std::vector<int> >::iterator p = t->second->extraExtras.find(static_cast<int>(params[3]) & ~0xC0000000);
							if (p != t->second->extraExtras.end())
							{
								return Utility::getFirstValueInContainer(p->second);
							}
						}
						error = InvalidData;
						break;
					}
				}
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachedObject:
					{
						if (a->second->attach)
						{
							return a->second->attach->object.get<0>();
						}
						return INVALID_STREAMER_ID;
					}
					case AttachedPlayer:
					{
						if (a->second->attach)
						{
							return a->second->attach->player;
						}
						return INVALID_PLAYER_ID;
					}
					case AttachedVehicle:
					{
						if (a->second->attach)
						{
							return a->second->attach->vehicle;
						}
						return INVALID_VEHICLE_ID;
					}
					case ExtraId:
					{
						return Utility::getFirstValueInContainer(a->second->extras);
					}
					case InteriorId:
					{
						return Utility::getFirstValueInContainer(a->second->interiors);
					}
					case PlayerId:
					{
						return Utility::getFirstValueInContainer(a->second->players);
					}
					case Priority:
					{
						return a->second->priority;
					}
					case Type:
					{
						return a->second->type;
					}
					case WorldId:
					{
						return Utility::getFirstValueInContainer(a->second->worlds);
					}
					default:
					{
						if (static_cast<int>(params[3]) & 0x40000000)
						{
							boost::unordered_map<int, std::vector<int> >::iterator p = a->second->extraExtras.find(static_cast<int>(params[3]) & ~0xC0000000);
							if (p != a->second->extraExtras.end())
							{
								return Utility::getFirstValueInContainer(p->second);
							}
						}
						error = InvalidData;
						break;
					}
				}
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(static_cast<int>(params[2]));
			if (a != core->getData()->actors.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AreaId:
					{
						return Utility::getFirstValueInContainer(a->second->areas);
					}
					case ExtraId:
					{
						return Utility::getFirstValueInContainer(a->second->extras);
					}
					case InteriorId:
					{
						return Utility::getFirstValueInContainer(a->second->interiors);
					}
					case Invulnerable:
					{
						return a->second->invulnerable;
					}
					case ModelId:
					{
						return a->second->modelId;
					}
					case PlayerId:
					{
						return Utility::getFirstValueInContainer(a->second->players);
					}
					case Priority:
					{
						return a->second->priority;
					}
					case WorldId:
					{
						return Utility::getFirstValueInContainer(a->second->worlds);
					}
					default:
					{
						if (static_cast<int>(params[3]) & 0x40000000)
						{
							boost::unordered_map<int, std::vector<int> >::iterator p = a->second->extraExtras.find(static_cast<int>(params[3]) & ~0xC0000000);
							if (p != a->second->extraExtras.end())
							{
								return Utility::getFirstValueInContainer(p->second);
							}
						}
						error = InvalidData;
						break;
					}
				}
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		default:
		{
			error = InvalidType;
			break;
		}
	}
	switch (error)
	{
		case InvalidData:
		{
			Utility::logError("Streamer_GetIntData: Invalid data specified.");
			break;
		}
		case InvalidId:
		{
			Utility::logError("Streamer_GetIntData: Invalid ID specified.");
			break;
		}
		case InvalidType:
		{
			Utility::logError("Streamer_GetIntData: Invalid type specified.");
			break;
		}
	}
	return 0;
}

int Manipulation::hasIntData(AMX *amx, cell *params)
{
	int error = -1;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				if (static_cast<int>(params[3]) & 0x40000000)
				{
					return o->second->extraExtras.find(static_cast<int>(params[3]) & ~0xC0000000) != o->second->extraExtras.end();
				}
				error = InvalidData;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				if (static_cast<int>(params[3]) & 0x40000000)
				{
					return p->second->extraExtras.find(static_cast<int>(params[3]) & ~0xC0000000) != p->second->extraExtras.end();
				}
				error = InvalidData;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				if (static_cast<int>(params[3]) & 0x40000000)
				{
					return c->second->extraExtras.find(static_cast<int>(params[3]) & ~0xC0000000) != c->second->extraExtras.end();
				}
				error = InvalidData;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				if (static_cast<int>(params[3]) & 0x40000000)
				{
					return r->second->extraExtras.find(static_cast<int>(params[3]) & ~0xC0000000) != r->second->extraExtras.end();
				}
				error = InvalidData;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				if (static_cast<int>(params[3]) & 0x40000000)
				{
					return m->second->extraExtras.find(static_cast<int>(params[3]) & ~0xC0000000) != m->second->extraExtras.end();
				}
				error = InvalidData;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				if (static_cast<int>(params[3]) & 0x40000000)
				{
					return t->second->extraExtras.find(static_cast<int>(params[3]) & ~0xC0000000) != t->second->extraExtras.end();
				}
				error = InvalidData;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				if (static_cast<int>(params[3]) & 0x40000000)
				{
					return a->second->extraExtras.find(static_cast<int>(params[3]) & ~0xC0000000) != a->second->extraExtras.end();
				}
				error = InvalidData;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(static_cast<int>(params[2]));
			if (a != core->getData()->actors.end())
			{
				if (static_cast<int>(params[3]) & 0x40000000)
				{
					return a->second->extraExtras.find(static_cast<int>(params[3]) & ~0xC0000000) != a->second->extraExtras.end();
				}
				error = InvalidData;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		default:
		{
			error = InvalidType;
			break;
		}
	}
	switch (error)
	{
		case InvalidData:
		{
			Utility::logError("Streamer_Has(Int|Array)Data: Invalid data specified.");
			break;
		}
		case InvalidId:
		{
			Utility::logError("Streamer_Has(Int|Array)Data: Invalid ID specified.");
			break;
		}
		case InvalidType:
		{
			Utility::logError("Streamer_Has(Int|Array)Data: Invalid type specified.");
			break;
		}
	}
	return 0;
}

int Manipulation::removeIntData(AMX *amx, cell *params)
{
	int error = -1;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				if (static_cast<int>(params[3]) & 0x40000000)
				{
					return o->second->extraExtras.erase(static_cast<int>(params[3]) & ~0xC0000000);
				}
				error = InvalidData;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				if (static_cast<int>(params[3]) & 0x40000000)
				{
					return p->second->extraExtras.erase(static_cast<int>(params[3]) & ~0xC0000000);
				}
				error = InvalidData;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				if (static_cast<int>(params[3]) & 0x40000000)
				{
					return c->second->extraExtras.erase(static_cast<int>(params[3]) & ~0xC0000000);
				}
				error = InvalidData;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				if (static_cast<int>(params[3]) & 0x40000000)
				{
					return r->second->extraExtras.erase(static_cast<int>(params[3]) & ~0xC0000000);
				}
				error = InvalidData;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				if (static_cast<int>(params[3]) & 0x40000000)
				{
					return m->second->extraExtras.erase(static_cast<int>(params[3]) & ~0xC0000000);
				}
				error = InvalidData;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				if (static_cast<int>(params[3]) & 0x40000000)
				{
					return t->second->extraExtras.erase(static_cast<int>(params[3]) & ~0xC0000000);
				}
				error = InvalidData;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				if (static_cast<int>(params[3]) & 0x40000000)
				{
					return a->second->extraExtras.erase(static_cast<int>(params[3]) & ~0xC0000000);
				}
				error = InvalidData;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(static_cast<int>(params[2]));
			if (a != core->getData()->actors.end())
			{
				if (static_cast<int>(params[3]) & 0x40000000)
				{
					return a->second->extraExtras.erase(static_cast<int>(params[3]) & ~0xC0000000);
				}
				error = InvalidData;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		default:
		{
			error = InvalidType;
			break;
		}
	}
	switch (error)
	{
		case InvalidData:
		{
			Utility::logError("Streamer_RemoveIntData: Invalid data specified.");
			break;
		}
		case InvalidId:
		{
			Utility::logError("Streamer_RemoveIntData: Invalid ID specified.");
			break;
		}
		case InvalidType:
		{
			Utility::logError("Streamer_RemoveIntData: Invalid type specified.");
			break;
		}
	}
	return 0;
}

int Manipulation::setIntData(AMX *amx, cell *params)
{
	int error = -1;
	bool update = false;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AreaId:
					{
						return Utility::setFirstValueInContainer(o->second->areas, static_cast<int>(params[4])) != 0;
					}
					case AttachedObject:
					{
						if (static_cast<int>(params[4]) != INVALID_STREAMER_ID)
						{
							// Now we have AttachPlayerObjectToObject built in, no need for YSF
							if (o->second->move)
							{
								Utility::logError("Streamer_SetIntData: Object is currently moving and must be stopped first.");
								return 0;
							}
							o->second->attach = boost::intrusive_ptr<Item::Object::Attach>(new Item::Object::Attach);
							o->second->attach->player = INVALID_PLAYER_ID;
							o->second->attach->vehicle = INVALID_VEHICLE_ID;
							o->second->attach->object = static_cast<int>(params[4]);
							o->second->attach->positionOffset.setZero();
							o->second->attach->rotation.setZero();
							o->second->attach->syncRotation = true;
							core->getStreamer()->attachedObjects.insert(o->second);
							update = true;
						}
						else
						{
							if (o->second->attach)
							{
								if (o->second->attach->object != INVALID_STREAMER_ID)
								{
									o->second->attach.reset();
									core->getStreamer()->attachedObjects.erase(o->second);
									core->getGrid()->removeObject(o->second, true);
									update = true;
								}
							}
						}
						break;
					}
					case AttachedPlayer:
					{
						if (static_cast<int>(params[4]) != INVALID_PLAYER_ID)
						{
							// Attaching player object to player is currently not available 
							return 0;

							// if (o->second->move)
							// {
							// 	Utility::logError("Streamer_SetIntData: Object is currently moving and must be stopped first.");
							// 	return 0;
							// }
							// static AMX_NATIVE native = sampgdk::FindNative("SetPlayerGravity");
							// if (native == NULL)
							// {
							// 	Utility::logError("Streamer_SetIntData: YSF plugin must be loaded to attach objects to players.");
							// 	return 0;
							// }
							// o->second->attach = boost::intrusive_ptr<Item::Object::Attach>(new Item::Object::Attach);
							// o->second->attach->object = INVALID_STREAMER_ID;
							// o->second->attach->vehicle = INVALID_VEHICLE_ID;
							// o->second->attach->player = static_cast<int>(params[4]);
							// o->second->attach->positionOffset.setZero();
							// o->second->attach->rotation.setZero();
							// core->getStreamer()->attachedObjects.insert(o->second);
							// update = true;
						}
						else
						{
							if (o->second->attach)
							{
								if (o->second->attach->player != INVALID_PLAYER_ID)
								{
									o->second->attach.reset();
									core->getStreamer()->attachedObjects.erase(o->second);
									core->getGrid()->removeObject(o->second, true);
									update = true;
								}
							}
						}
						break;
					}
					case AttachedVehicle:
					{
						if (static_cast<int>(params[4]) != INVALID_VEHICLE_ID)
						{
							if (o->second->move)
							{
								Utility::logError("Streamer_SetIntData: Object is currently moving and must be stopped first.");
								return 0;
							}
							o->second->attach = boost::intrusive_ptr<Item::Object::Attach>(new Item::Object::Attach);
							o->second->attach->object = INVALID_STREAMER_ID;
							o->second->attach->player = INVALID_PLAYER_ID;
							o->second->attach->vehicle = static_cast<int>(params[4]);
							o->second->attach->positionOffset.setZero();
							o->second->attach->rotation.setZero();
							core->getStreamer()->attachedObjects.insert(o->second);
							update = true;
						}
						else
						{
							if (o->second->attach)
							{
								if (o->second->attach->vehicle != INVALID_VEHICLE_ID)
								{
									o->second->attach.reset();
									core->getStreamer()->attachedObjects.erase(o->second);
									core->getGrid()->removeObject(o->second, true);
									update = true;
								}
							}
						}
						break;
					}
					case ExtraId:
					{
						return Utility::setFirstValueInContainer(o->second->extras, static_cast<int>(params[4])) != 0;
					}
					case InteriorId:
					{
						return Utility::setFirstValueInContainer(o->second->interiors, static_cast<int>(params[4])) != 0;
					}
					case ModelId:
					{
						o->second->modelId = static_cast<int>(params[4]);
						update = true;
						break;
					}
					case PlayerId:
					{
						return Utility::setFirstValueInContainer(o->second->players, static_cast<int>(params[4])) != 0;
					}
					case Priority:
					{
						o->second->priority = static_cast<int>(params[4]);
						break;
					}
					case SyncRotation:
					{
						if (o->second->attach)
						{
							if (o->second->attach->object != INVALID_STREAMER_ID)
							{
								o->second->attach->syncRotation = static_cast<int>(params[4]) != 0;
								update = true;
							}
						}
						break;
					}
					case WorldId:
					{
						return Utility::setFirstValueInContainer(o->second->worlds, static_cast<int>(params[4])) != 0;
					}
					default:
					{
						if (static_cast<int>(params[3]) & 0x40000000)
						{
							o->second->extraExtras[static_cast<int>(params[3]) & ~0xC0000000] = std::vector<int>(1, static_cast<int>(params[4]));
							break;
						}
						error = InvalidData;
						break;
					}
				}
				if (update)
				{
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
						if (i != p->second.internalObjects.end())
						{
							ompgdk::DestroyPlayerObject(p->first, i->second);
							i->second = ompgdk::CreatePlayerObject(p->first, o->second->modelId, o->second->position[0], o->second->position[1], o->second->position[2], o->second->rotation[0], o->second->rotation[1], o->second->rotation[2], o->second->drawDistance);
							if (o->second->attach)
							{
								if (o->second->attach->object != INVALID_STREAMER_ID)
								{
									boost::unordered_map<int, int>::iterator j = p->second.internalObjects.find(o->second->attach->object);
									if (j != p->second.internalObjects.end())
									{
										ompgdk::AttachPlayerObjectToObject(p->first, i->second, j->second, o->second->attach->positionOffset[0], o->second->attach->positionOffset[1], o->second->attach->positionOffset[2], o->second->attach->rotation[0], o->second->attach->rotation[1], o->second->attach->rotation[2]);
									}
								}
								else if (o->second->attach->player != INVALID_PLAYER_ID)
								{
									ompgdk::AttachPlayerObjectToPlayer(p->first, i->second, o->second->attach->player, o->second->attach->positionOffset[0], o->second->attach->positionOffset[1], o->second->attach->positionOffset[2], o->second->attach->rotation[0], o->second->attach->rotation[1], o->second->attach->rotation[2]);
								}
								else if (o->second->attach->vehicle != INVALID_VEHICLE_ID)
								{
									ompgdk::AttachPlayerObjectToVehicle(p->first, i->second, o->second->attach->vehicle, o->second->attach->positionOffset[0], o->second->attach->positionOffset[1], o->second->attach->positionOffset[2], o->second->attach->rotation[0], o->second->attach->rotation[1], o->second->attach->rotation[2]);
								}
							}
							else if (o->second->move)
							{
								ompgdk::MovePlayerObject(p->first, i->second, o->second->move->position.get<0>()[0], o->second->move->position.get<0>()[1], o->second->move->position.get<0>()[2], o->second->move->speed, o->second->move->rotation.get<0>()[0], o->second->move->rotation.get<0>()[1], o->second->move->rotation.get<0>()[2]);
							}
							for (boost::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.begin(); m != o->second->materials.end(); ++m)
							{
								if (m->second.main)
								{
									ompgdk::SetPlayerObjectMaterial(p->first, i->second, m->first, m->second.main->modelId, m->second.main->txdFileName.c_str(), m->second.main->textureName.c_str(), m->second.main->materialColor);
								}
								else if (m->second.text)
								{
									ompgdk::SetPlayerObjectMaterialText(p->first, i->second, m->second.text->materialText.c_str(), m->first, m->second.text->materialSize, m->second.text->fontFace.c_str(), m->second.text->fontSize, m->second.text->bold, m->second.text->fontColor, m->second.text->backColor, m->second.text->textAlignment);
								}
							}
							if (o->second->noCameraCollision)
							{
								ompgdk::SetPlayerObjectNoCameraCol(p->first, i->second);
							}
						}
					}
				}
				return 1;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			boost::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AreaId:
					{
						return Utility::setFirstValueInContainer(p->second->areas, static_cast<int>(params[4])) != 0;
					}
					case ExtraId:
					{
						return Utility::setFirstValueInContainer(p->second->extras, static_cast<int>(params[4])) != 0;
					}
					case InteriorId:
					{
						return Utility::setFirstValueInContainer(p->second->interiors, static_cast<int>(params[4])) != 0;
					}
					case ModelId:
					{
						p->second->modelId = static_cast<int>(params[4]);
						update = true;
						break;
					}
					case PlayerId:
					{
						return Utility::setFirstValueInContainer(p->second->players, static_cast<int>(params[4])) != 0;
					}
					case Priority:
					{
						p->second->priority = static_cast<int>(params[4]);
						return 1;
					}
					case Type:
					{
						p->second->type = static_cast<int>(params[4]);
						update = true;
						break;
					}
					case WorldId:
					{
						return Utility::setFirstValueInContainer(p->second->worlds, static_cast<int>(params[4])) != 0;
					}
					default:
					{
						if (static_cast<int>(params[3]) & 0x40000000)
						{
							p->second->extraExtras[static_cast<int>(params[3]) & ~0xC0000000] = std::vector<int>(1, static_cast<int>(params[4]));
							break;
						}
						error = InvalidData;
						break;
					}
				}
				if (update)
				{
					for (boost::unordered_set<int>::const_iterator w = p->second->worlds.begin(); w != p->second->worlds.end(); ++w)
					{
						boost::unordered_map<std::pair<int, int>, int>::iterator i = core->getData()->internalPickups.find(std::make_pair(p->first, *w));
						if (i != core->getData()->internalPickups.end())
						{
							ompgdk::DestroyPickup(i->second);
							i->second = ompgdk::CreatePickup(p->second->modelId, p->second->type, p->second->position[0], p->second->position[1], p->second->position[2], *w);
						}
					}
				}
				return 1;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_CP:
		{
			boost::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AreaId:
					{
						return Utility::setFirstValueInContainer(c->second->areas, static_cast<int>(params[4])) != 0;
					}
					case ExtraId:
					{
						return Utility::setFirstValueInContainer(c->second->extras, static_cast<int>(params[4])) != 0;
					}
					case InteriorId:
					{
						return Utility::setFirstValueInContainer(c->second->interiors, static_cast<int>(params[4])) != 0;
					}
					case PlayerId:
					{
						return Utility::setFirstValueInContainer(c->second->players, static_cast<int>(params[4])) != 0;
					}
					case Priority:
					{
						c->second->priority = static_cast<int>(params[4]);
						return 1;
					}
					case WorldId:
					{
						return Utility::setFirstValueInContainer(c->second->worlds, static_cast<int>(params[4])) != 0;
					}
					default:
					{
						if (static_cast<int>(params[3]) & 0x40000000)
						{
							c->second->extraExtras[static_cast<int>(params[3]) & ~0xC0000000] = std::vector<int>(1, static_cast<int>(params[4]));
							break;
						}
						error = InvalidData;
						break;
					}
				}
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			boost::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AreaId:
					{
						return Utility::setFirstValueInContainer(r->second->areas, static_cast<int>(params[4])) != 0;
					}
					case ExtraId:
					{
						return Utility::setFirstValueInContainer(r->second->extras, static_cast<int>(params[4])) != 0;
					}
					case InteriorId:
					{
						return Utility::setFirstValueInContainer(r->second->interiors, static_cast<int>(params[4])) != 0;
					}
					case PlayerId:
					{
						return Utility::setFirstValueInContainer(r->second->players, static_cast<int>(params[4])) != 0;
					}
					case Priority:
					{
						r->second->priority = static_cast<int>(params[4]);
						return 1;
					}
					case Type:
					{
						r->second->type = static_cast<int>(params[4]);
						update = true;
						break;
					}
					case WorldId:
					{
						return Utility::setFirstValueInContainer(r->second->worlds, static_cast<int>(params[4])) != 0;
					}
					default:
					{
						if (static_cast<int>(params[3]) & 0x40000000)
						{
							r->second->extraExtras[static_cast<int>(params[3]) & ~0xC0000000] = std::vector<int>(1, static_cast<int>(params[4]));
							break;
						}
						error = InvalidData;
						break;
					}
				}
				if (update)
				{
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						if (p->second.visibleRaceCheckpoint == r->first)
						{
							ompgdk::DisablePlayerRaceCheckpoint(p->first);
							p->second.delayedRaceCheckpoint = r->first;
						}
					}
				}
				return 1;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			boost::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AreaId:
					{
						return Utility::setFirstValueInContainer(m->second->areas, static_cast<int>(params[4])) != 0;
					}
					case Color:
					{
						m->second->color = static_cast<int>(params[4]);
						update = true;
						break;
					}
					case ExtraId:
					{
						return Utility::setFirstValueInContainer(m->second->extras, static_cast<int>(params[4])) != 0;
					}
					case InteriorId:
					{
						return Utility::setFirstValueInContainer(m->second->interiors, static_cast<int>(params[4])) != 0;
					}
					case PlayerId:
					{
						return Utility::setFirstValueInContainer(m->second->players, static_cast<int>(params[4])) != 0;
					}
					case Priority:
					{
						m->second->priority = static_cast<int>(params[4]);
						return 1;
					}
					case Style:
					{
						m->second->style = static_cast<int>(params[4]);
						update = true;
						break;
					}
					case Type:
					{
						m->second->type = static_cast<int>(params[4]);
						update = true;
						break;
					}
					case WorldId:
					{
						return Utility::setFirstValueInContainer(m->second->worlds, static_cast<int>(params[4])) != 0;
					}
					default:
					{
						if (static_cast<int>(params[3]) & 0x40000000)
						{
							m->second->extraExtras[static_cast<int>(params[3]) & ~0xC0000000] = std::vector<int>(1, static_cast<int>(params[4]));
							break;
						}
						error = InvalidData;
						break;
					}
				}
				if (update)
				{
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator i = p->second.internalMapIcons.find(m->first);
						if (i != p->second.internalMapIcons.end())
						{
							ompgdk::RemovePlayerMapIcon(p->first, i->second);
							ompgdk::SetPlayerMapIcon(p->first, i->second, m->second->position[0], m->second->position[1], m->second->position[2], m->second->type, m->second->color, m->second->style);
						}
					}
				}
				return 1;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			boost::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AreaId:
					{
						return Utility::setFirstValueInContainer(t->second->areas, static_cast<int>(params[4])) != 0;
					}
					case AttachedPlayer:
					{
						if (static_cast<int>(params[4]) != INVALID_PLAYER_ID)
						{
							t->second->attach = boost::intrusive_ptr<Item::TextLabel::Attach>(new Item::TextLabel::Attach);
							t->second->attach->player = static_cast<int>(params[4]);
							t->second->attach->vehicle = INVALID_VEHICLE_ID;
							core->getStreamer()->attachedTextLabels.insert(t->second);
							update = true;
						}
						else
						{
							if (t->second->attach)
							{
								if (t->second->attach->player != INVALID_PLAYER_ID)
								{
									t->second->attach.reset();
									core->getStreamer()->attachedTextLabels.erase(t->second);
									core->getGrid()->removeTextLabel(t->second, true);
									update = true;
								}
							}
						}
						break;
					}
					case AttachedVehicle:
					{
						if (static_cast<int>(params[4]) != INVALID_VEHICLE_ID)
						{
							t->second->attach = boost::intrusive_ptr<Item::TextLabel::Attach>(new Item::TextLabel::Attach);
							t->second->attach->player = INVALID_PLAYER_ID;
							t->second->attach->vehicle = static_cast<int>(params[4]);
							core->getStreamer()->attachedTextLabels.insert(t->second);
							update = true;
						}
						else
						{
							if (t->second->attach)
							{
								if (t->second->attach->vehicle != INVALID_VEHICLE_ID)
								{
									t->second->attach.reset();
									core->getStreamer()->attachedTextLabels.erase(t->second);
									core->getGrid()->removeTextLabel(t->second, true);
									update = true;
								}
							}
						}
						break;
					}
					case Color:
					{
						t->second->color = static_cast<int>(params[4]);
						update = true;
						break;
					}
					case ExtraId:
					{
						return Utility::setFirstValueInContainer(t->second->extras, static_cast<int>(params[4])) != 0;
					}
					case InteriorId:
					{
						return Utility::setFirstValueInContainer(t->second->interiors, static_cast<int>(params[4])) != 0;
					}
					case PlayerId:
					{
						return Utility::setFirstValueInContainer(t->second->players, static_cast<int>(params[4])) != 0;
					}
					case Priority:
					{
						t->second->priority = static_cast<int>(params[4]);
						return 1;
					}
					case TestLOS:
					{
						t->second->testLOS = static_cast<int>(params[4]) != 0;
						update = true;
						break;
					}
					case WorldId:
					{
						return Utility::setFirstValueInContainer(t->second->worlds, static_cast<int>(params[4])) != 0;
					}
					default:
					{
						if (static_cast<int>(params[3]) & 0x40000000)
						{
							t->second->extraExtras[static_cast<int>(params[3]) & ~0xC0000000] = std::vector<int>(1, static_cast<int>(params[4]));
							break;
						}
						error = InvalidData;
						break;
					}
				}
				if (update)
				{
					if (t->second->attach)
					{
						if (t->second->position.cwiseAbs().maxCoeff() > 50.0f)
						{
							t->second->position.setZero();
						}
					}
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.find(t->first);
						if (i != p->second.internalTextLabels.end())
						{
							ompgdk::DeletePlayer3DTextLabel(p->first, i->second);
							i->second = ompgdk::CreatePlayer3DTextLabel(p->first, t->second->text.c_str(), t->second->color, t->second->position[0], t->second->position[1], t->second->position[2], t->second->drawDistance, t->second->attach ? t->second->attach->player : INVALID_PLAYER_ID, t->second->attach ? t->second->attach->vehicle : INVALID_VEHICLE_ID, t->second->testLOS);
						}
					}
				}
				return 1;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			boost::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachedObject:
					{
						Utility::logError("Streamer_SetIntData: Use AttachDynamicAreaToObject to adjust attached area data.");
						return 0;
					}
					case AttachedPlayer:
					{
						if (static_cast<int>(params[4]) != INVALID_PLAYER_ID)
						{
							a->second->attach = boost::intrusive_ptr<Item::Area::Attach>(new Item::Area::Attach);
							a->second->attach->object = boost::make_tuple(INVALID_STREAMER_ID, STREAMER_OBJECT_TYPE_DYNAMIC, INVALID_PLAYER_ID);
							a->second->attach->vehicle = INVALID_VEHICLE_ID;
							a->second->attach->position = a->second->position;
							a->second->attach->player = static_cast<int>(params[4]);
							core->getStreamer()->attachedAreas.insert(a->second);
							return 1;
						}
						else
						{
							if (a->second->attach)
							{
								if (a->second->attach->player != INVALID_PLAYER_ID)
								{
									a->second->attach.reset();
									core->getStreamer()->attachedAreas.erase(a->second);
									core->getGrid()->removeArea(a->second, true);
									return 1;
								}
							}
						}
						return 0;
					}
					case AttachedVehicle:
					{
						if (static_cast<int>(params[4]) != INVALID_VEHICLE_ID)
						{
							a->second->attach = boost::intrusive_ptr<Item::Area::Attach>(new Item::Area::Attach);
							a->second->attach->object = boost::make_tuple(INVALID_STREAMER_ID, STREAMER_OBJECT_TYPE_DYNAMIC, INVALID_PLAYER_ID);
							a->second->attach->player = INVALID_PLAYER_ID;
							a->second->attach->position = a->second->position;
							a->second->attach->vehicle = static_cast<int>(params[4]);
							core->getStreamer()->attachedAreas.insert(a->second);
							return 1;
						}
						else
						{
							if (a->second->attach)
							{
								if (a->second->attach->vehicle != INVALID_VEHICLE_ID)
								{
									a->second->attach.reset();
									core->getStreamer()->attachedAreas.erase(a->second);
									core->getGrid()->removeArea(a->second, true);
									return 1;
								}
							}
						}
						return 0;
					}
					case ExtraId:
					{
						return Utility::setFirstValueInContainer(a->second->extras, static_cast<int>(params[4])) != 0;
					}
					case InteriorId:
					{
						return Utility::setFirstValueInContainer(a->second->interiors, static_cast<int>(params[4])) != 0;
					}
					case PlayerId:
					{
						return Utility::setFirstValueInContainer(a->second->players, static_cast<int>(params[4])) != 0;
					}
					case Priority:
					{
						a->second->priority = static_cast<int>(params[4]);
						break;
					}
					case WorldId:
					{
						return Utility::setFirstValueInContainer(a->second->worlds, static_cast<int>(params[4])) != 0;
					}
					default:
					{
						if (static_cast<int>(params[3]) & 0x40000000)
						{
							a->second->extraExtras[static_cast<int>(params[3]) & ~0xC0000000] = std::vector<int>(1, static_cast<int>(params[4]));
							break;
						}
						error = InvalidData;
						break;
					}
				}
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		case STREAMER_TYPE_ACTOR:
		{
			boost::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(static_cast<int>(params[2]));
			if (a != core->getData()->actors.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AreaId:
					{
						return Utility::setFirstValueInContainer(a->second->areas, static_cast<int>(params[4])) != 0;
					}
					case ExtraId:
					{
						return Utility::setFirstValueInContainer(a->second->extras, static_cast<int>(params[4])) != 0;
					}
					case InteriorId:
					{
						return Utility::setFirstValueInContainer(a->second->interiors, static_cast<int>(params[4])) != 0;
					}
					case Invulnerable:
					{
						a->second->invulnerable = static_cast<int>(params[4]) != 0;
						update = true;
						break;
					}
					case ModelId:
					{
						a->second->modelId = static_cast<int>(params[4]);
						update = true;
						break;
					}
					case PlayerId:
					{
						return Utility::setFirstValueInContainer(a->second->players, static_cast<int>(params[4])) != 0;
					}
					case Priority:
					{
						a->second->priority = static_cast<int>(params[4]);
						return 1;
					}
					case WorldId:
					{
						return Utility::setFirstValueInContainer(a->second->worlds, static_cast<int>(params[4])) != 0;
					}
					default:
					{
						if (static_cast<int>(params[3]) & 0x40000000)
						{
							a->second->extraExtras[static_cast<int>(params[3]) & ~0xC0000000] = std::vector<int>(1, static_cast<int>(params[4]));
							break;
						}
						error = InvalidData;
						break;
					}
				}
				if (update)
				{
					for (boost::unordered_set<int>::const_iterator w = a->second->worlds.begin(); w != a->second->worlds.end(); ++w)
					{
						boost::unordered_map<std::pair<int, int>, int>::iterator i = core->getData()->internalActors.find(std::make_pair(a->first, *w));
						if (i != core->getData()->internalActors.end())
						{
							ompgdk::DestroyActor(i->second);
							i->second = ompgdk::CreateActor(a->second->modelId, a->second->position[0], a->second->position[1], a->second->position[2], a->second->rotation);
							ompgdk::SetActorInvulnerable(i->second, a->second->invulnerable);
							ompgdk::SetActorHealth(i->second, a->second->health);
							ompgdk::SetActorVirtualWorld(i->second, *w);
							if (a->second->anim)
							{
								ompgdk::ApplyActorAnimation(i->second, a->second->anim->lib.c_str(), a->second->anim->name.c_str(), a->second->anim->delta, a->second->anim->loop, a->second->anim->lockx, a->second->anim->locky, a->second->anim->freeze, a->second->anim->time);
							}
						}
					}
				}
				return 1;
			}
			else
			{
				error = InvalidId;
			}
			break;
		}
		default:
		{
			error = InvalidType;
			break;
		}
	}
	switch (error)
	{
		case InvalidData:
		{
			Utility::logError("Streamer_SetIntData: Invalid data specified.");
			break;
		}
		case InvalidId:
		{
			Utility::logError("Streamer_SetIntData: Invalid ID specified.");
			break;
		}
		case InvalidType:
		{
			Utility::logError("Streamer_SetIntData: Invalid type specified.");
			break;
		}
	}
	return 0;
}
