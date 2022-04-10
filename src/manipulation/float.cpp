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

#include "float.h"
#include "../core.h"
#include "../utility.h"

using namespace Manipulation;

int Manipulation::getFloatData(AMX *amx, cell *params)
{
	int error = -1;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			std::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachOffsetX:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->positionOffset[0]);
							return 1;
						}
						return 0;
					}
					case AttachOffsetY:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->positionOffset[1]);
							return 1;
						}
						return 0;
					}
					case AttachOffsetZ:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->positionOffset[2]);
							return 1;
						}
						return 0;
					}
					case AttachRX:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->rotation[0]);
							return 1;
						}
						return 0;
					}
					case AttachRY:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->rotation[1]);
							return 1;
						}
						return 0;
					}
					case AttachRZ:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->rotation[2]);
							return 1;
						}
						return 0;
					}
					case AttachX:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->position[0]);
							return 1;
						}
						return 0;
					}
					case AttachY:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->position[1]);
							return 1;
						}
						return 0;
					}
					case AttachZ:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->position[2]);
							return 1;
						}
						return 0;
					}
					case DrawDistance:
					{
						Utility::storeFloatInNative(amx, params[4], o->second->drawDistance);
						return 1;
					}
					case MoveSpeed:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->move->speed);
							return 1;
						}
						return 0;
					}
					case MoveRX:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], std::get<0>(o->second->move->rotation)[0]);
							return 1;
						}
						return 0;
					}
					case MoveRY:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], std::get<0>(o->second->move->rotation)[1]);
							return 1;
						}
						return 0;
					}
					case MoveRZ:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], std::get<0>(o->second->move->rotation)[2]);
							return 1;
						}
						return 0;
					}
					case MoveX:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], std::get<0>(o->second->move->position)[0]);
							return 1;
						}
						return 0;
					}
					case MoveY:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], std::get<0>(o->second->move->position)[1]);
							return 1;
						}
						return 0;
					}
					case MoveZ:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], std::get<0>(o->second->move->position)[2]);
							return 1;
						}
						return 0;
					}
					case RX:
					{
						Utility::storeFloatInNative(amx, params[4], o->second->rotation[0]);
						return 1;
					}
					case RY:
					{
						Utility::storeFloatInNative(amx, params[4], o->second->rotation[1]);
						return 1;
					}
					case RZ:
					{
						Utility::storeFloatInNative(amx, params[4], o->second->rotation[2]);
						return 1;
					}
					case StreamDistance:
					{
						Utility::storeFloatInNative(amx, params[4], o->second->streamDistance);
						return 1;
					}
					case X:
					{
						Utility::storeFloatInNative(amx, params[4], o->second->position[0]);
						return 1;
					}
					case Y:
					{
						Utility::storeFloatInNative(amx, params[4], o->second->position[1]);
						return 1;
					}
					case Z:
					{
						Utility::storeFloatInNative(amx, params[4], o->second->position[2]);
						return 1;
					}
					default:
					{
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
			std::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case StreamDistance:
					{
						Utility::storeFloatInNative(amx, params[4], p->second->streamDistance);
						return 1;
					}
					case X:
					{
						Utility::storeFloatInNative(amx, params[4], p->second->position[0]);
						return 1;
					}
					case Y:
					{
						Utility::storeFloatInNative(amx, params[4], p->second->position[1]);
						return 1;
					}
					case Z:
					{
						Utility::storeFloatInNative(amx, params[4], p->second->position[2]);
						return 1;
					}
					default:
					{
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
			std::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case Size:
					{
						Utility::storeFloatInNative(amx, params[4], c->second->size);
						return 1;
					}
					case StreamDistance:
					{
						Utility::storeFloatInNative(amx, params[4], c->second->streamDistance);
						return 1;
					}
					case X:
					{
						Utility::storeFloatInNative(amx, params[4], c->second->position[0]);
						return 1;
					}
					case Y:
					{
						Utility::storeFloatInNative(amx, params[4], c->second->position[1]);
						return 1;
					}
					case Z:
					{
						Utility::storeFloatInNative(amx, params[4], c->second->position[2]);
						return 1;
					}
					default:
					{
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
			std::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case NextX:
					{
						Utility::storeFloatInNative(amx, params[4], r->second->next[0]);
						return 1;
					}
					case NextY:
					{
						Utility::storeFloatInNative(amx, params[4], r->second->next[1]);
						return 1;
					}
					case NextZ:
					{
						Utility::storeFloatInNative(amx, params[4], r->second->next[2]);
						return 1;
					}
					case Size:
					{
						Utility::storeFloatInNative(amx, params[4], r->second->size);
						return 1;
					}
					case StreamDistance:
					{
						Utility::storeFloatInNative(amx, params[4], r->second->streamDistance);
						return 1;
					}
					case X:
					{
						Utility::storeFloatInNative(amx, params[4], r->second->position[0]);
						return 1;
					}
					case Y:
					{
						Utility::storeFloatInNative(amx, params[4], r->second->position[1]);
						return 1;
					}
					case Z:
					{
						Utility::storeFloatInNative(amx, params[4], r->second->position[2]);
						return 1;
					}
					default:
					{
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
			std::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case StreamDistance:
					{
						Utility::storeFloatInNative(amx, params[4], m->second->streamDistance);
						return 1;
					}
					case X:
					{
						Utility::storeFloatInNative(amx, params[4], m->second->position[0]);
						return 1;
					}
					case Y:
					{
						Utility::storeFloatInNative(amx, params[4], m->second->position[1]);
						return 1;
					}
					case Z:
					{
						Utility::storeFloatInNative(amx, params[4], m->second->position[2]);
						return 1;
					}
					default:
					{
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
			std::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachX:
					{
						if (t->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], t->second->attach->position[0]);
							return 1;
						}
						return 0;
					}
					case AttachY:
					{
						if (t->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], t->second->attach->position[1]);
							return 1;
						}
						return 0;
					}
					case AttachZ:
					{
						if (t->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], t->second->attach->position[2]);
							return 1;
						}
						return 0;
					}
					case DrawDistance:
					{
						Utility::storeFloatInNative(amx, params[4], t->second->drawDistance);
						return 1;
					}
					case StreamDistance:
					{
						Utility::storeFloatInNative(amx, params[4], t->second->streamDistance);
						return 1;
					}
					case AttachOffsetX:
					case X:
					{
						Utility::storeFloatInNative(amx, params[4], t->second->position[0]);
						return 1;
					}
					case AttachOffsetY:
					case Y:
					{
						Utility::storeFloatInNative(amx, params[4], t->second->position[1]);
						return 1;
					}
					case AttachOffsetZ:
					case Z:
					{
						Utility::storeFloatInNative(amx, params[4], t->second->position[2]);
						return 1;
					}
					default:
					{
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
			std::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachX:
					{
						if (a->second->attach)
						{
							switch (a->second->type)
							{
								case STREAMER_AREA_TYPE_CIRCLE:
								case STREAMER_AREA_TYPE_CYLINDER:
								{
									Utility::storeFloatInNative(amx, params[4], std::get<Eigen::Vector2f>(a->second->attach->position)[0]);
									return 1;
								}
								case STREAMER_AREA_TYPE_SPHERE:
								{
									Utility::storeFloatInNative(amx, params[4], std::get<Eigen::Vector3f>(a->second->attach->position)[0]);
									return 1;
								}
							}
						}
						return 0;
					}
					case AttachY:
					{
						if (a->second->attach)
						{
							switch (a->second->type)
							{
								case STREAMER_AREA_TYPE_CIRCLE:
								case STREAMER_AREA_TYPE_CYLINDER:
								{
									Utility::storeFloatInNative(amx, params[4], std::get<Eigen::Vector2f>(a->second->attach->position)[1]);
									return 1;
								}
								case STREAMER_AREA_TYPE_SPHERE:
								{
									Utility::storeFloatInNative(amx, params[4], std::get<Eigen::Vector3f>(a->second->attach->position)[1]);
									return 1;
								}
							}
						}
						return 0;
					}
					case AttachZ:
					{
						if (a->second->attach)
						{
							switch (a->second->type)
							{
								case STREAMER_AREA_TYPE_SPHERE:
								{
									Utility::storeFloatInNative(amx, params[4], std::get<Eigen::Vector3f>(a->second->attach->position)[2]);
									return 1;
								}
							}
						}
						return 0;
					}
					case AttachOffsetX:
					{
						if (a->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], a->second->attach->positionOffset[0]);
							return 1;
						}
						return 0;
					}
					case AttachOffsetY:
					{
						if (a->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], a->second->attach->positionOffset[1]);
							return 1;
						}
						return 0;
					}
					case AttachOffsetZ:
					{
						if (a->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], a->second->attach->positionOffset[2]);
							return 1;
						}
						return 0;
					}
					case MaxX:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								Utility::storeFloatInNative(amx, params[4], std::get<Box2d>(a->second->position).max_corner()[0]);
								return 1;
							}
							case STREAMER_AREA_TYPE_CUBOID:
							{
								Utility::storeFloatInNative(amx, params[4], std::get<Box3d>(a->second->position).max_corner()[0]);
								return 1;
							}
						}
						return 0;
					}
					case MaxY:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								Utility::storeFloatInNative(amx, params[4], std::get<Box2d>(a->second->position).max_corner()[1]);
								return 1;
							}
							case STREAMER_AREA_TYPE_CUBOID:
							{
								Utility::storeFloatInNative(amx, params[4], std::get<Box3d>(a->second->position).max_corner()[1]);
								return 1;
							}
						}
						return 0;
					}
					case MaxZ:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CUBOID:
							{
								Utility::storeFloatInNative(amx, params[4], std::get<Box3d>(a->second->position).max_corner()[2]);
								return 1;
							}
							case STREAMER_AREA_TYPE_CYLINDER:
							case STREAMER_AREA_TYPE_POLYGON:
							{
								Utility::storeFloatInNative(amx, params[4], a->second->height[1]);
								return 1;
							}
						}
						return 0;
					}
					case MinX:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								Utility::storeFloatInNative(amx, params[4], std::get<Box2d>(a->second->position).min_corner()[0]);
								return 1;
							}
							case STREAMER_AREA_TYPE_CUBOID:
							{
								Utility::storeFloatInNative(amx, params[4], std::get<Box3d>(a->second->position).min_corner()[0]);
								return 1;
							}
						}
						return 0;
					}
					case MinY:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								Utility::storeFloatInNative(amx, params[4], std::get<Box2d>(a->second->position).min_corner()[1]);
								return 1;
							}
							case STREAMER_AREA_TYPE_CUBOID:
							{
								Utility::storeFloatInNative(amx, params[4], std::get<Box3d>(a->second->position).min_corner()[1]);
								return 1;
							}
						}
						return 0;
					}
					case MinZ:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CUBOID:
							{
								Utility::storeFloatInNative(amx, params[4], std::get<Box3d>(a->second->position).min_corner()[2]);
								return 1;
							}
							case STREAMER_AREA_TYPE_CYLINDER:
							case STREAMER_AREA_TYPE_POLYGON:
							{
								Utility::storeFloatInNative(amx, params[4], a->second->height[0]);
								return 1;
							}
						}
						return 0;
					}
					case Size:
					{
						Utility::storeFloatInNative(amx, params[4], a->second->size);
						return 1;
					}
					case X:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CIRCLE:
							case STREAMER_AREA_TYPE_CYLINDER:
							{
								Utility::storeFloatInNative(amx, params[4], std::get<Eigen::Vector2f>(a->second->position)[0]);
								return 1;
							}
							case STREAMER_AREA_TYPE_SPHERE:
							{
								Utility::storeFloatInNative(amx, params[4], std::get<Eigen::Vector3f>(a->second->position)[0]);
								return 1;
							}
						}
						return 0;
					}
					case Y:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CIRCLE:
							case STREAMER_AREA_TYPE_CYLINDER:
							{
								Utility::storeFloatInNative(amx, params[4], std::get<Eigen::Vector2f>(a->second->position)[1]);
								return 1;
							}
							case STREAMER_AREA_TYPE_SPHERE:
							{
								Utility::storeFloatInNative(amx, params[4], std::get<Eigen::Vector3f>(a->second->position)[1]);
								return 1;
							}
						}
						return 0;
					}
					case Z:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_SPHERE:
							{
								Utility::storeFloatInNative(amx, params[4], std::get<Eigen::Vector3f>(a->second->position)[2]);
								return 1;
							}
						}
						return 0;
					}
					default:
					{
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
			std::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(static_cast<int>(params[2]));
			if (a != core->getData()->actors.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case Health:
					{
						Utility::storeFloatInNative(amx, params[4], a->second->health);
						return 1;
					}
					case StreamDistance:
					{
						Utility::storeFloatInNative(amx, params[4], a->second->streamDistance);
						return 1;
					}
					case Rotation:
					{
						Utility::storeFloatInNative(amx, params[4], a->second->rotation);
						return 1;
					}
					case X:
					{
						Utility::storeFloatInNative(amx, params[4], a->second->position[0]);
						return 1;
					}
					case Y:
					{
						Utility::storeFloatInNative(amx, params[4], a->second->position[1]);
						return 1;
					}
					case Z:
					{
						Utility::storeFloatInNative(amx, params[4], a->second->position[2]);
						return 1;
					}
					default:
					{
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
			Utility::logError("Streamer_GetFloatData: Invalid data specified.");
			break;
		}
		case InvalidId:
		{
			Utility::logError("Streamer_GetFloatData: Invalid ID specified.");
			break;
		}
		case InvalidType:
		{
			Utility::logError("Streamer_GetFloatData: Invalid type specified.");
			break;
		}
	}
	return 0;
}

int Manipulation::setFloatData(AMX *amx, cell *params)
{
	int error = -1;
	bool reassign = false, update = false;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			std::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachOffsetX:
					{
						if (o->second->attach)
						{
							o->second->attach->positionOffset[0] = amx_ctof(params[4]);
							update = true;
						}
						break;
					}
					case AttachOffsetY:
					{
						if (o->second->attach)
						{
							o->second->attach->positionOffset[1] = amx_ctof(params[4]);
							update = true;
						}
						break;
					}
					case AttachOffsetZ:
					{
						if (o->second->attach)
						{
							o->second->attach->positionOffset[2] = amx_ctof(params[4]);
							update = true;
						}
						break;
					}
					case AttachRX:
					{
						if (o->second->attach)
						{
							o->second->attach->rotation[0] = amx_ctof(params[4]);
							update = true;
						}
						break;
					}
					case AttachRY:
					{
						if (o->second->attach)
						{
							o->second->attach->rotation[1] = amx_ctof(params[4]);
							update = true;
						}
						break;
					}
					case AttachRZ:
					{
						if (o->second->attach)
						{
							o->second->attach->rotation[2] = amx_ctof(params[4]);
							update = true;
						}
						break;
					}
					case DrawDistance:
					{
						o->second->drawDistance = amx_ctof(params[4]);
						update = true;
						break;
					}
					case MoveRX:
					case MoveRY:
					case MoveRZ:
					case MoveSpeed:
					case MoveX:
					case MoveY:
					case MoveZ:
					{
						Utility::logError("Streamer_SetFloatData: Use MoveDynamicObject to adjust moving object data.");
						return 0;
					}
					case RX:
					{
						o->second->rotation[0] = amx_ctof(params[4]);
						update = true;
						break;
					}
					case RY:
					{
						o->second->rotation[1] = amx_ctof(params[4]);
						update = true;
						break;
					}
					case RZ:
					{
						o->second->rotation[2] = amx_ctof(params[4]);
						update = true;
						break;
					}
					case StreamDistance:
					{
						o->second->comparableStreamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						o->second->streamDistance = amx_ctof(params[4]);
						reassign = true;
						break;
					}
					case X:
					{
						if (o->second->move)
						{
							Utility::logError("Streamer_SetFloatData: Object is currently moving and must be stopped first.");
							return 0;
						}
						o->second->position[0] = amx_ctof(params[4]);
						if (o->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Y:
					{
						if (o->second->move)
						{
							Utility::logError("Streamer_SetFloatData: Object is currently moving and must be stopped first.");
							return 0;
						}
						o->second->position[1] = amx_ctof(params[4]);
						if (o->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Z:
					{
						if (o->second->move)
						{
							Utility::logError("Streamer_SetFloatData: Object is currently moving and must be stopped first.");
							return 0;
						}
						o->second->position[2] = amx_ctof(params[4]);
						update = true;
						break;
					}
					default:
					{
						error = InvalidData;
						break;
					}
				}
				if (reassign)
				{
					core->getGrid()->removeObject(o->second, true);
				}
				if (update)
				{
					for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						std::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
						if (i != p->second.internalObjects.end())
						{
							sampgdk::DestroyPlayerObject(p->first, i->second);
							i->second = sampgdk::CreatePlayerObject(p->first, o->second->modelId, o->second->position[0], o->second->position[1], o->second->position[2], o->second->rotation[0], o->second->rotation[1], o->second->rotation[2], o->second->drawDistance);
							if (o->second->attach)
							{
								if (o->second->attach->object != INVALID_STREAMER_ID)
								{
									std::unordered_map<int, int>::iterator j = p->second.internalObjects.find(o->second->attach->object);
									if (j != p->second.internalObjects.end())
									{
										static AMX_NATIVE native = sampgdk::FindNative("AttachPlayerObjectToObject");
										if (native != NULL)
										{
											sampgdk::InvokeNative(native, "dddffffffb", p->first, i->second, j->second, o->second->attach->positionOffset[0], o->second->attach->positionOffset[1], o->second->attach->positionOffset[2], o->second->attach->rotation[0], o->second->attach->rotation[1], o->second->attach->rotation[2], o->second->attach->syncRotation);
										}
									}
								}
								else if (o->second->attach->player != INVALID_PLAYER_ID)
								{
									static AMX_NATIVE native = sampgdk::FindNative("AttachPlayerObjectToPlayer");
									if (native != NULL)
									{
										sampgdk::InvokeNative(native, "dddffffffd", p->first, i->second, o->second->attach->player, o->second->attach->positionOffset[0], o->second->attach->positionOffset[1], o->second->attach->positionOffset[2], o->second->attach->rotation[0], o->second->attach->rotation[1], o->second->attach->rotation[2], 1);
									}
								}
								else if (o->second->attach->vehicle != INVALID_VEHICLE_ID)
								{
									sampgdk::AttachPlayerObjectToVehicle(p->first, i->second, o->second->attach->vehicle, o->second->attach->positionOffset[0], o->second->attach->positionOffset[1], o->second->attach->positionOffset[2], o->second->attach->rotation[0], o->second->attach->rotation[1], o->second->attach->rotation[2]);
								}
							}
							else if (o->second->move)
							{
								sampgdk::MovePlayerObject(p->first, i->second, std::get<0>(o->second->move->position)[0], std::get<0>(o->second->move->position)[1], std::get<0>(o->second->move->position)[2], o->second->move->speed, std::get<0>(o->second->move->rotation)[0], std::get<0>(o->second->move->rotation)[1], std::get<0>(o->second->move->rotation)[2]);
							}
							for (std::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.begin(); m != o->second->materials.end(); ++m)
							{
								if (m->second.main)
								{
									sampgdk::SetPlayerObjectMaterial(p->first, i->second, m->first, m->second.main->modelId, m->second.main->txdFileName.c_str(), m->second.main->textureName.c_str(), m->second.main->materialColor);
								}
								else if (m->second.text)
								{
									sampgdk::SetPlayerObjectMaterialText(p->first, i->second, m->second.text->materialText.c_str(), m->first, m->second.text->materialSize, m->second.text->fontFace.c_str(), m->second.text->fontSize, m->second.text->bold, m->second.text->fontColor, m->second.text->backColor, m->second.text->textAlignment);
								}
							}
							if (o->second->noCameraCollision)
							{
								sampgdk::SetPlayerObjectNoCameraCol(p->first, i->second);
							}
						}
					}
				}
				if (reassign || update)
				{
					return 1;
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
			std::unordered_map<int, Item::SharedPickup>::iterator p = core->getData()->pickups.find(static_cast<int>(params[2]));
			if (p != core->getData()->pickups.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case StreamDistance:
					{
						p->second->comparableStreamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						p->second->streamDistance = amx_ctof(params[4]);
						reassign = true;
						break;
					}
					case X:
					{
						p->second->position[0] = amx_ctof(params[4]);
						if (p->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Y:
					{
						p->second->position[1] = amx_ctof(params[4]);
						if (p->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Z:
					{
						p->second->position[2] = amx_ctof(params[4]);
						update = true;
						break;
					}
					default:
					{
						error = InvalidData;
						break;
					}
				}
				if (reassign)
				{
					core->getGrid()->removePickup(p->second, true);
				}
				if (update)
				{
					for (std::unordered_set<int>::const_iterator w = p->second->worlds.begin(); w != p->second->worlds.end(); ++w)
					{
						std::unordered_map<std::pair<int, int>, int, pair_hash>::iterator i = core->getData()->internalPickups.find(std::make_pair(p->first, *w));
						if (i != core->getData()->internalPickups.end())
						{
							sampgdk::DestroyPickup(i->second);
							i->second = sampgdk::CreatePickup(p->second->modelId, p->second->type, p->second->position[0], p->second->position[1], p->second->position[2], *w);
						}
					}
				}
				if (reassign || update)
				{
					return 1;
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
			std::unordered_map<int, Item::SharedCheckpoint>::iterator c = core->getData()->checkpoints.find(static_cast<int>(params[2]));
			if (c != core->getData()->checkpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case Size:
					{
						c->second->size = amx_ctof(params[4]);
						update = true;
						break;
					}
					case StreamDistance:
					{
						c->second->comparableStreamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						c->second->streamDistance = amx_ctof(params[4]);
						reassign = true;
						break;
					}
					case X:
					{
						c->second->position[0] = amx_ctof(params[4]);
						if (c->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Y:
					{
						c->second->position[1] = amx_ctof(params[4]);
						if (c->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Z:
					{
						c->second->position[2] = amx_ctof(params[4]);
						update = true;
						break;
					}
					default:
					{
						error = InvalidData;
						break;
					}
				}
				if (reassign)
				{
					core->getGrid()->removeCheckpoint(c->second, true);
				}
				if (update)
				{
					for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						if (p->second.visibleCheckpoint == c->first)
						{
							sampgdk::DisablePlayerCheckpoint(p->first);
							p->second.activeCheckpoint = 0;
							p->second.visibleCheckpoint = 0;
						}
					}
				}
				if (reassign || update)
				{
					return 1;
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
			std::unordered_map<int, Item::SharedRaceCheckpoint>::iterator r = core->getData()->raceCheckpoints.find(static_cast<int>(params[2]));
			if (r != core->getData()->raceCheckpoints.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case NextX:
					{
						r->second->next[0] = amx_ctof(params[4]);
						update = true;
						break;
					}
					case NextY:
					{
						r->second->next[1] = amx_ctof(params[4]);
						update = true;
						break;
					}
					case NextZ:
					{
						r->second->next[2] = amx_ctof(params[4]);
						update = true;
						break;
					}
					case Size:
					{
						r->second->size = amx_ctof(params[4]);
						update = true;
						break;
					}
					case StreamDistance:
					{
						r->second->comparableStreamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						r->second->streamDistance = amx_ctof(params[4]);
						reassign = true;
						break;
					}
					case X:
					{
						r->second->position[0] = amx_ctof(params[4]);
						if (r->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Y:
					{
						r->second->position[1] = amx_ctof(params[4]);
						if (r->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Z:
					{
						r->second->position[2] = amx_ctof(params[4]);
						update = true;
						break;
					}
					default:
					{
						error = InvalidData;
						break;
					}
				}
				if (reassign)
				{
					core->getGrid()->removeRaceCheckpoint(r->second, true);
				}
				if (update)
				{
					for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						if (p->second.visibleRaceCheckpoint == r->first)
						{
							sampgdk::DisablePlayerRaceCheckpoint(p->first);
							p->second.activeRaceCheckpoint = 0;
							p->second.visibleRaceCheckpoint = 0;
						}
					}
				}
				if (reassign || update)
				{
					return 1;
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
			std::unordered_map<int, Item::SharedMapIcon>::iterator m = core->getData()->mapIcons.find(static_cast<int>(params[2]));
			if (m != core->getData()->mapIcons.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case StreamDistance:
					{
						m->second->comparableStreamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						m->second->streamDistance = amx_ctof(params[4]);
						reassign = true;
						break;
					}
					case X:
					{
						m->second->position[0] = amx_ctof(params[4]);
						if (m->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Y:
					{
						m->second->position[1] = amx_ctof(params[4]);
						if (m->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Z:
					{
						m->second->position[2] = amx_ctof(params[4]);
						update = true;
						break;
					}
					default:
					{
						error = InvalidData;
						break;
					}
				}
				if (reassign)
				{
					core->getGrid()->removeMapIcon(m->second, true);
				}
				if (update)
				{
					for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						std::unordered_map<int, int>::iterator i = p->second.internalMapIcons.find(m->first);
						if (i != p->second.internalMapIcons.end())
						{
							sampgdk::RemovePlayerMapIcon(p->first, i->second);
							sampgdk::SetPlayerMapIcon(p->first, i->second, m->second->position[0], m->second->position[1], m->second->position[2], m->second->type, m->second->color, m->second->style);
						}
					}
				}
				if (reassign || update)
				{
					return 1;
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
			std::unordered_map<int, Item::SharedTextLabel>::iterator t = core->getData()->textLabels.find(static_cast<int>(params[2]));
			if (t != core->getData()->textLabels.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case DrawDistance:
					{
						t->second->drawDistance = amx_ctof(params[4]);
						update = true;
						break;
					}
					case StreamDistance:
					{
						t->second->comparableStreamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						t->second->streamDistance = amx_ctof(params[4]);
						reassign = true;
						break;
					}
					case AttachOffsetX:
					case X:
					{
						t->second->position[0] = amx_ctof(params[4]);
						if (t->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case AttachOffsetY:
					case Y:
					{
						t->second->position[1] = amx_ctof(params[4]);
						if (t->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case AttachOffsetZ:
					case Z:
					{
						t->second->position[2] = amx_ctof(params[4]);
						update = true;
						break;
					}
					default:
					{
						error = InvalidData;
						break;
					}
				}
				if (reassign)
				{
					core->getGrid()->removeTextLabel(t->second, true);
				}
				if (update)
				{
					for (std::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						std::unordered_map<int, int>::iterator i = p->second.internalTextLabels.find(t->first);
						if (i != p->second.internalTextLabels.end())
						{
							sampgdk::DeletePlayer3DTextLabel(p->first, i->second);
							i->second = sampgdk::CreatePlayer3DTextLabel(p->first, t->second->text.c_str(), t->second->color, t->second->position[0], t->second->position[1], t->second->position[2], t->second->drawDistance, t->second->attach ? t->second->attach->player : INVALID_PLAYER_ID, t->second->attach ? t->second->attach->vehicle : INVALID_VEHICLE_ID, t->second->testLOS);
						}
					}
				}
				if (reassign || update)
				{
					return 1;
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
			std::unordered_map<int, Item::SharedArea>::iterator a = core->getData()->areas.find(static_cast<int>(params[2]));
			if (a != core->getData()->areas.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachOffsetX:
					{
						if (a->second->attach)
						{
							a->second->attach->positionOffset[0] = amx_ctof(params[4]);
						}
						break;
					}
					case AttachOffsetY:
					{
						if (a->second->attach)
						{
							a->second->attach->positionOffset[1] = amx_ctof(params[4]);
						}
						break;
					}
					case AttachOffsetZ:
					{
						if (a->second->attach)
						{
							a->second->attach->positionOffset[2] = amx_ctof(params[4]);
						}
						break;
					}
					case MaxX:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								std::get<Box2d>(a->second->position).max_corner()[0] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
							case STREAMER_AREA_TYPE_CUBOID:
							{
								std::get<Box3d>(a->second->position).max_corner()[0] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
						}
						break;
					}
					case MaxY:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								std::get<Box2d>(a->second->position).max_corner()[1] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
							case STREAMER_AREA_TYPE_CUBOID:
							{
								std::get<Box3d>(a->second->position).max_corner()[1] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
						}
						break;
					}
					case MaxZ:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CUBOID:
							{
								std::get<Box3d>(a->second->position).max_corner()[2] = amx_ctof(params[4]);
								return 1;
							}
							case STREAMER_AREA_TYPE_CYLINDER:
							case STREAMER_AREA_TYPE_POLYGON:
							{
								a->second->height[1] = amx_ctof(params[4]);
								return 0;
							}
						}
						return 0;
					}
					case MinX:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								std::get<Box2d>(a->second->position).min_corner()[0] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
							case STREAMER_AREA_TYPE_CUBOID:
							{
								std::get<Box3d>(a->second->position).min_corner()[0] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
						}
						break;
					}
					case MinY:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								std::get<Box2d>(a->second->position).min_corner()[1] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
							case STREAMER_AREA_TYPE_CUBOID:
							{
								std::get<Box3d>(a->second->position).min_corner()[1] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
						}
						break;
					}
					case MinZ:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CUBOID:
							{
								std::get<Box3d>(a->second->position).min_corner()[2] = amx_ctof(params[4]);
								return 1;
							}
							case STREAMER_AREA_TYPE_CYLINDER:
							case STREAMER_AREA_TYPE_POLYGON:
							{
								a->second->height[0] = amx_ctof(params[4]);
								return 1;
							}
						}
						return 0;
					}
					case Size:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CIRCLE:
							case STREAMER_AREA_TYPE_CYLINDER:
							case STREAMER_AREA_TYPE_SPHERE:
							{
								a->second->comparableSize = amx_ctof(params[4]) * amx_ctof(params[4]);
								a->second->size = amx_ctof(params[4]);
								reassign = true;
								break;
							}
						}
						break;
					}
					case X:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CIRCLE:
							case STREAMER_AREA_TYPE_CYLINDER:
							{
								std::get<Eigen::Vector2f>(a->second->position)[0] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
							case STREAMER_AREA_TYPE_SPHERE:
							{
								std::get<Eigen::Vector3f>(a->second->position)[0] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
						}
						break;
					}
					case Y:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CIRCLE:
							case STREAMER_AREA_TYPE_CYLINDER:
							{
								std::get<Eigen::Vector2f>(a->second->position)[1] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
							case STREAMER_AREA_TYPE_SPHERE:
							{
								std::get<Eigen::Vector3f>(a->second->position)[1] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
						}
						break;
					}
					case Z:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_SPHERE:
							{
								std::get<Eigen::Vector3f>(a->second->position)[2] = amx_ctof(params[4]);
								return 1;
							}
						}
						return 0;
					}
					default:
					{
						error = InvalidData;
						break;
					}
				}
				if (reassign)
				{
					switch (a->second->type)
					{
						case STREAMER_AREA_TYPE_RECTANGLE:
						{
							boost::geometry::correct(std::get<Box2d>(a->second->position));
							a->second->comparableSize = static_cast<float>(boost::geometry::comparable_distance(std::get<Box2d>(a->second->position).min_corner(), std::get<Box2d>(a->second->position).max_corner()));
							a->second->size = static_cast<float>(boost::geometry::distance(std::get<Box2d>(a->second->position).min_corner(), std::get<Box2d>(a->second->position).max_corner()));
							break;
						}
						case STREAMER_AREA_TYPE_CUBOID:
						{
							boost::geometry::correct(std::get<Box3d>(a->second->position));
							a->second->comparableSize = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(std::get<Box3d>(a->second->position).min_corner()[0], std::get<Box3d>(a->second->position).min_corner()[1]), Eigen::Vector2f(std::get<Box3d>(a->second->position).max_corner()[0], std::get<Box3d>(a->second->position).max_corner()[1])));
							a->second->size = static_cast<float>(boost::geometry::distance(Eigen::Vector2f(std::get<Box3d>(a->second->position).min_corner()[0], std::get<Box3d>(a->second->position).min_corner()[1]), Eigen::Vector2f(std::get<Box3d>(a->second->position).max_corner()[0], std::get<Box3d>(a->second->position).max_corner()[1])));
							break;
						}
					}
					core->getGrid()->removeArea(a->second, true);
				}
				if (reassign)
				{
					return 1;
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
			std::unordered_map<int, Item::SharedActor>::iterator a = core->getData()->actors.find(static_cast<int>(params[2]));
			if (a != core->getData()->actors.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case Health:
					{
						a->second->health = amx_ctof(params[4]);
						update = true;
						break;
					}
					case StreamDistance:
					{
						a->second->comparableStreamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						a->second->streamDistance = amx_ctof(params[4]);
						reassign = true;
						break;
					}
					case Rotation:
					{
						a->second->rotation = amx_ctof(params[4]);
						update = true;
						break;
					}
					case X:
					{
						a->second->position[0] = amx_ctof(params[4]);
						if (a->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Y:
					{
						a->second->position[1] = amx_ctof(params[4]);
						if (a->second->cell)
						{
							reassign = true;
						}
						update = true;
						break;
					}
					case Z:
					{
						a->second->position[2] = amx_ctof(params[4]);
						update = true;
						break;
					}
					default:
					{
						error = InvalidData;
						break;
					}
				}
				if (reassign)
				{
					core->getGrid()->removeActor(a->second, true);
				}
				if (update)
				{
					for (std::unordered_set<int>::const_iterator w = a->second->worlds.begin(); w != a->second->worlds.end(); ++w)
					{
						std::unordered_map<std::pair<int, int>, int, pair_hash>::iterator i = core->getData()->internalActors.find(std::make_pair(a->first, *w));
						if (i != core->getData()->internalActors.end())
						{
							sampgdk::DestroyActor(i->second);
							i->second = sampgdk::CreateActor(a->second->modelId, a->second->position[0], a->second->position[1], a->second->position[2], a->second->rotation);
							sampgdk::SetActorInvulnerable(i->second, a->second->invulnerable);
							sampgdk::SetActorHealth(i->second, a->second->health);
							sampgdk::SetActorVirtualWorld(i->second, *w);
							if (a->second->anim)
							{
								sampgdk::ApplyActorAnimation(i->second, a->second->anim->lib.c_str(), a->second->anim->name.c_str(), a->second->anim->delta, a->second->anim->loop, a->second->anim->lockx, a->second->anim->locky, a->second->anim->freeze, a->second->anim->time);
							}
						}
					}
				}
				if (reassign || update)
				{
					return 1;
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
			Utility::logError("Streamer_SetFloatData: Invalid data specified.");
			break;
		}
		case InvalidId:
		{
			Utility::logError("Streamer_SetFloatData: Invalid ID specified.");
			break;
		}
		case InvalidType:
		{
			Utility::logError("Streamer_SetFloatData: Invalid type specified.");
			break;
		}
	}
	return 0;
}
