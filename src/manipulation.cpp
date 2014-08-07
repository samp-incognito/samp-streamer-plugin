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

#include "manipulation.h"

#include "core.h"
#include "main.h"
#include "utility.h"

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
#include <cmath>

using namespace Manipulation;

int Manipulation::getFloatData(AMX *amx, cell *params)
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
					case AttachOffsetX:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->offset[0]);
							return 1;
						}
						return 0;
					}
					case AttachOffsetY:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->offset[1]);
							return 1;
						}
						return 0;
					}
					case AttachOffsetZ:
					{
						if (o->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->attach->offset[2]);
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
							Utility::storeFloatInNative(amx, params[4], o->second->move->rotation.get<0>()[0]);
							return 1;
						}
						return 0;
					}
					case MoveRY:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->move->rotation.get<0>()[1]);
							return 1;
						}
						return 0;
					}
					case MoveRZ:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->move->rotation.get<0>()[2]);
							return 1;
						}
						return 0;
					}
					case MoveX:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->move->position.get<0>()[0]);
							return 1;
						}
						return 0;
					}
					case MoveY:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->move->position.get<0>()[1]);
							return 1;
						}
						return 0;
					}
					case MoveZ:
					{
						if (o->second->move)
						{
							Utility::storeFloatInNative(amx, params[4], o->second->move->position.get<0>()[2]);
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
						Utility::storeFloatInNative(amx, params[4], std::sqrt(o->second->streamDistance));
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
				error = InvalidID;
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
					case StreamDistance:
					{
						Utility::storeFloatInNative(amx, params[4], std::sqrt(p->second->streamDistance));
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
				error = InvalidID;
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
					case Size:
					{
						Utility::storeFloatInNative(amx, params[4], c->second->size);
						return 1;
					}
					case StreamDistance:
					{
						Utility::storeFloatInNative(amx, params[4], std::sqrt(c->second->streamDistance));
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
				error = InvalidID;
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
						Utility::storeFloatInNative(amx, params[4], std::sqrt(r->second->streamDistance));
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
				error = InvalidID;
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
					case StreamDistance:
					{
						Utility::storeFloatInNative(amx, params[4], std::sqrt(m->second->streamDistance));
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
				error = InvalidID;
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
						Utility::storeFloatInNative(amx, params[4], std::sqrt(t->second->streamDistance));
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
				error = InvalidID;
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
					case AttachX:
					{
						if (a->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], a->second->attach->position[0]);
							return 1;
						}
						return 0;
					}
					case AttachY:
					{
						if (a->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], a->second->attach->position[1]);
							return 1;
						}
						return 0;
					}
					case AttachZ:
					{
						if (a->second->attach)
						{
							Utility::storeFloatInNative(amx, params[4], a->second->attach->position[2]);
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
								Utility::storeFloatInNative(amx, params[4], boost::get<Box2D>(a->second->position).max_corner()[0]);
								return 1;
							}
							case STREAMER_AREA_TYPE_CUBOID:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Box3D>(a->second->position).max_corner()[0]);
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
								Utility::storeFloatInNative(amx, params[4], boost::get<Box2D>(a->second->position).max_corner()[1]);
								return 1;
							}
							case STREAMER_AREA_TYPE_CUBOID:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Box3D>(a->second->position).max_corner()[1]);
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
								Utility::storeFloatInNative(amx, params[4], boost::get<Box3D>(a->second->position).max_corner()[2]);
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
								Utility::storeFloatInNative(amx, params[4], boost::get<Box2D>(a->second->position).min_corner()[0]);
								return 1;
							}
							case STREAMER_AREA_TYPE_CUBOID:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Box3D>(a->second->position).min_corner()[0]);
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
								Utility::storeFloatInNative(amx, params[4], boost::get<Box2D>(a->second->position).min_corner()[1]);
								return 1;
							}
							case STREAMER_AREA_TYPE_CUBOID:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Box3D>(a->second->position).min_corner()[1]);
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
								Utility::storeFloatInNative(amx, params[4], boost::get<Box3D>(a->second->position).min_corner()[2]);
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
						Utility::storeFloatInNative(amx, params[4], std::sqrt(a->second->size));
						return 1;
					}
					case X:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_CIRCLE:
							case STREAMER_AREA_TYPE_CYLINDER:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Eigen::Vector2f>(a->second->position)[0]);
								return 1;
							}
							case STREAMER_AREA_TYPE_SPHERE:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Eigen::Vector3f>(a->second->position)[0]);
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
								Utility::storeFloatInNative(amx, params[4], boost::get<Eigen::Vector2f>(a->second->position)[1]);
								return 1;
							}
							case STREAMER_AREA_TYPE_SPHERE:
							{
								Utility::storeFloatInNative(amx, params[4], boost::get<Eigen::Vector3f>(a->second->position)[1]);
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
								Utility::storeFloatInNative(amx, params[4], boost::get<Eigen::Vector3f>(a->second->position)[2]);
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
				error = InvalidID;
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
			sampgdk::logprintf("*** Streamer_GetFloatData: Invalid data specified");
			break;
		}
		case InvalidID:
		{
			sampgdk::logprintf("*** Streamer_GetFloatData: Invalid ID specified");
			break;
		}
		case InvalidType:
		{
			sampgdk::logprintf("*** Streamer_GetFloatData: Invalid type specified");
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
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				switch (static_cast<int>(params[3]))
				{
					case AttachOffsetX:
					{
						if (o->second->attach)
						{
							o->second->attach->offset[0] = amx_ctof(params[4]);
							update = true;
						}
						break;
					}
					case AttachOffsetY:
					{
						if (o->second->attach)
						{
							o->second->attach->offset[1] = amx_ctof(params[4]);
							update = true;
						}
						break;
					}
					case AttachOffsetZ:
					{
						if (o->second->attach)
						{
							o->second->attach->offset[2] = amx_ctof(params[4]);
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
						sampgdk::logprintf("*** Streamer_SetFloatData: Use MoveDynamicObject to adjust moving object data");
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
						o->second->streamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
						reassign = true;
						break;
					}
					case X:
					{
						if (o->second->move)
						{
							sampgdk::logprintf("*** Streamer_SetFloatData: Object must be stopped first");
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
							sampgdk::logprintf("*** Streamer_SetFloatData: Object must be stopped first");
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
							sampgdk::logprintf("*** Streamer_SetFloatData: Object must be stopped first");
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
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
						if (i != p->second.internalObjects.end())
						{
							DestroyPlayerObject(p->first, i->second);
							i->second = CreatePlayerObject(p->first, o->second->modelID, o->second->position[0], o->second->position[1], o->second->position[2], o->second->rotation[0], o->second->rotation[1], o->second->rotation[2], o->second->drawDistance);
							if (o->second->attach)
							{
								AttachPlayerObjectToVehicle(p->first, i->second, o->second->attach->vehicle, o->second->attach->offset[0], o->second->attach->offset[1], o->second->attach->offset[2], o->second->attach->rotation[0], o->second->attach->rotation[1], o->second->attach->rotation[2]);		
							}
							else if (o->second->move)
							{
								MovePlayerObject(p->first, i->second, o->second->move->position.get<0>()[0], o->second->move->position.get<0>()[1], o->second->move->position.get<0>()[2], o->second->move->speed, o->second->move->rotation.get<0>()[0], o->second->move->rotation.get<0>()[1], o->second->move->rotation.get<0>()[2]);
							}
							for (boost::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.begin(); m != o->second->materials.end(); ++m)
							{
								if (m->second.main)
								{
									SetPlayerObjectMaterial(p->first, i->second, m->first, m->second.main->modelID, m->second.main->txdFileName.c_str(), m->second.main->textureName.c_str(), m->second.main->materialColor);
								}
								else if (m->second.text)
								{
									SetPlayerObjectMaterialText(p->first, i->second, m->second.text->materialText.c_str(), m->first, m->second.text->materialSize, m->second.text->fontFace.c_str(), m->second.text->fontSize, m->second.text->bold, m->second.text->fontColor, m->second.text->backColor, m->second.text->textAlignment);
								}
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
				error = InvalidID;
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
					case StreamDistance:
					{
						p->second->streamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
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
					boost::unordered_map<int, int>::iterator i = core->getStreamer()->internalPickups.find(p->first);
					if (i != core->getStreamer()->internalPickups.end())
					{
						DestroyPickup(i->second);
						i->second = CreatePickup(p->second->modelID, p->second->type, p->second->position[0], p->second->position[1], p->second->position[2], p->second->worldID);
					}
				}
				if (reassign || update)
				{
					return 1;
				}
			}
			else
			{
				error = InvalidID;
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
					case Size:
					{
						c->second->size = amx_ctof(params[4]);
						update = true;
						break;
					}
					case StreamDistance:
					{
						c->second->streamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
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
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						if (p->second.visibleCheckpoint == c->first)
						{
							DisablePlayerCheckpoint(p->first);
							SetPlayerCheckpoint(p->first, c->second->position[0], c->second->position[1], c->second->position[2], c->second->size);
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
				error = InvalidID;
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
						r->second->streamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
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
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						if (p->second.visibleRaceCheckpoint == r->first)
						{
							DisablePlayerRaceCheckpoint(p->first);
							SetPlayerRaceCheckpoint(p->first, r->second->type, r->second->position[0], r->second->position[1], r->second->position[2], r->second->next[0], r->second->next[1], r->second->next[2], r->second->size);
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
				error = InvalidID;
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
					case StreamDistance:
					{
						m->second->streamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
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
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator i = p->second.internalMapIcons.find(m->first);
						if (i != p->second.internalMapIcons.end())
						{
							RemovePlayerMapIcon(p->first, i->second);
							SetPlayerMapIcon(p->first, i->second, m->second->position[0], m->second->position[1], m->second->position[2], m->second->type, m->second->color, m->second->style);
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
				error = InvalidID;
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
					case DrawDistance:
					{
						t->second->drawDistance = amx_ctof(params[4]);
						update = true;
						break;
					}
					case StreamDistance:
					{
						t->second->streamDistance = amx_ctof(params[4]) * amx_ctof(params[4]);
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
					for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
					{
						boost::unordered_map<int, int>::iterator i = p->second.internalTextLabels.find(t->first);
						if (i != p->second.internalTextLabels.end())
						{
							DeletePlayer3DTextLabel(p->first, i->second);
							i->second = CreatePlayer3DTextLabel(p->first, t->second->text.c_str(), t->second->color, t->second->position[0], t->second->position[1], t->second->position[2], t->second->drawDistance, t->second->attach ? t->second->attach->player : INVALID_GENERIC_ID, t->second->attach ? t->second->attach->vehicle : INVALID_GENERIC_ID, t->second->testLOS);
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
				error = InvalidID;
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
					case MaxX:
					{
						switch (a->second->type)
						{
							case STREAMER_AREA_TYPE_RECTANGLE:
							{
								boost::get<Box2D>(a->second->position).max_corner()[0] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
							case STREAMER_AREA_TYPE_CUBOID:
							{
								boost::get<Box3D>(a->second->position).max_corner()[0] = amx_ctof(params[4]);
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
								boost::get<Box2D>(a->second->position).max_corner()[1] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
							case STREAMER_AREA_TYPE_CUBOID:
							{
								boost::get<Box3D>(a->second->position).max_corner()[1] = amx_ctof(params[4]);
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
								boost::get<Box3D>(a->second->position).max_corner()[2] = amx_ctof(params[4]);
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
								boost::get<Box2D>(a->second->position).min_corner()[0] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
							case STREAMER_AREA_TYPE_CUBOID:
							{
								boost::get<Box3D>(a->second->position).min_corner()[0] = amx_ctof(params[4]);
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
								boost::get<Box2D>(a->second->position).min_corner()[1] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
							case STREAMER_AREA_TYPE_CUBOID:
							{
								boost::get<Box3D>(a->second->position).min_corner()[1] = amx_ctof(params[4]);
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
								boost::get<Box3D>(a->second->position).min_corner()[2] = amx_ctof(params[4]);
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
								a->second->size = amx_ctof(params[4]) * amx_ctof(params[4]);
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
								boost::get<Eigen::Vector2f>(a->second->position)[0] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
							case STREAMER_AREA_TYPE_SPHERE:
							{
								boost::get<Eigen::Vector3f>(a->second->position)[0] = amx_ctof(params[4]);
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
								boost::get<Eigen::Vector2f>(a->second->position)[1] = amx_ctof(params[4]);
								reassign = true;
								break;
							}
							case STREAMER_AREA_TYPE_SPHERE:
							{
								boost::get<Eigen::Vector3f>(a->second->position)[1] = amx_ctof(params[4]);
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
								boost::get<Eigen::Vector3f>(a->second->position)[2] = amx_ctof(params[4]);
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
							boost::geometry::correct(boost::get<Box2D>(a->second->position));
							a->second->size = static_cast<float>(boost::geometry::comparable_distance(boost::get<Box2D>(a->second->position).min_corner(), boost::get<Box2D>(a->second->position).max_corner()));
							break;
						}
						case STREAMER_AREA_TYPE_CUBOID:
						{
							boost::geometry::correct(boost::get<Box3D>(a->second->position));
							a->second->size = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(boost::get<Box3D>(a->second->position).min_corner()[0], boost::get<Box3D>(a->second->position).min_corner()[1]), Eigen::Vector2f(boost::get<Box3D>(a->second->position).max_corner()[0], boost::get<Box3D>(a->second->position).max_corner()[1])));
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
				error = InvalidID;
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
			sampgdk::logprintf("*** Streamer_SetFloatData: Invalid data specified");
			break;
		}
		case InvalidID:
		{
			sampgdk::logprintf("*** Streamer_SetFloatData: Invalid ID specified");
			break;
		}
		case InvalidType:
		{
			sampgdk::logprintf("*** Streamer_SetFloatData: Invalid type specified");
			break;
		}
	}
	return 0;
}

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
					case AttachedVehicle:
					{
						if (o->second->attach)
						{
							return o->second->attach->vehicle;
						}
						return INVALID_GENERIC_ID;
					}
					case ExtraID:
					{
						return Utility::getFirstValueInContainer(o->second->extras);
					}
					case InteriorID:
					{
						return Utility::getFirstValueInContainer(o->second->interiors);
					}
					case ModelID:
					{
						return o->second->modelID;
					}
					case PlayerID:
					{
						return Utility::getFirstValueInContainer(o->second->players);
					}
					case WorldID:
					{
						return Utility::getFirstValueInContainer(o->second->worlds);
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
				error = InvalidID;
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
					case ExtraID:
					{
						return Utility::getFirstValueInContainer(p->second->extras);
					}
					case InteriorID:
					{
						return Utility::getFirstValueInContainer(p->second->interiors);
					}
					case ModelID:
					{
						return p->second->modelID;
					}
					case PlayerID:
					{
						return Utility::getFirstValueInContainer(p->second->players);
					}
					case Type:
					{
						return p->second->type;
					}
					case WorldID:
					{
						return Utility::getFirstValueInContainer(p->second->worlds);
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
				error = InvalidID;
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
					case ExtraID:
					{
						return Utility::getFirstValueInContainer(c->second->extras);
					}
					case InteriorID:
					{
						return Utility::getFirstValueInContainer(c->second->interiors);
					}
					case PlayerID:
					{
						return Utility::getFirstValueInContainer(c->second->players);
					}
					case WorldID:
					{
						return Utility::getFirstValueInContainer(c->second->worlds);
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
				error = InvalidID;
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
					case ExtraID:
					{
						return Utility::getFirstValueInContainer(r->second->extras);
					}
					case InteriorID:
					{
						return Utility::getFirstValueInContainer(r->second->interiors);
					}
					case PlayerID:
					{
						return Utility::getFirstValueInContainer(r->second->players);
					}
					case Type:
					{
						return r->second->type;
					}
					case WorldID:
					{
						return Utility::getFirstValueInContainer(r->second->worlds);
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
				error = InvalidID;
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
					case Color:
					{
						return m->second->color;
					}
					case ExtraID:
					{
						return Utility::getFirstValueInContainer(m->second->extras);
					}
					case InteriorID:
					{
						return Utility::getFirstValueInContainer(m->second->interiors);
					}
					case PlayerID:
					{
						return Utility::getFirstValueInContainer(m->second->players);
					}
					case Style:
					{
						return m->second->style;
					}
					case Type:
					{
						return m->second->type;
					}
					case WorldID:
					{
						return Utility::getFirstValueInContainer(m->second->worlds);
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
				error = InvalidID;
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
					case AttachedPlayer:
					{
						if (t->second->attach)
						{
							return t->second->attach->player;
						}
						return INVALID_GENERIC_ID;
					}
					case AttachedVehicle:
					{
						if (t->second->attach)
						{
							return t->second->attach->vehicle;
						}
						return INVALID_GENERIC_ID;
					}
					case Color:
					{
						return t->second->color;
					}
					case ExtraID:
					{
						return Utility::getFirstValueInContainer(t->second->extras);
					}
					case InteriorID:
					{
						return Utility::getFirstValueInContainer(t->second->interiors);
					}
					case PlayerID:
					{
						return Utility::getFirstValueInContainer(t->second->players);
					}
					case TestLOS:
					{
						return t->second->testLOS;
					}
					case WorldID:
					{
						return Utility::getFirstValueInContainer(t->second->worlds);
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
				error = InvalidID;
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
						return INVALID_GENERIC_ID;
					}
					case AttachedPlayer:
					{
						if (a->second->attach)
						{
							return a->second->attach->player;
						}
						return INVALID_GENERIC_ID;
					}
					case AttachedVehicle:
					{
						if (a->second->attach)
						{
							return a->second->attach->vehicle;
						}
						return INVALID_GENERIC_ID;
					}
					case ExtraID:
					{
						return Utility::getFirstValueInContainer(a->second->extras);
					}
					case InteriorID:
					{
						return Utility::getFirstValueInContainer(a->second->interiors);
					}
					case PlayerID:
					{
						return Utility::getFirstValueInContainer(a->second->players);
					}
					case Type:
					{
						return a->second->type;
					}
					case WorldID:
					{
						return Utility::getFirstValueInContainer(a->second->worlds);
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
				error = InvalidID;
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
			sampgdk::logprintf("*** Streamer_GetIntData: Invalid data specified");
			break;
		}
		case InvalidID:
		{
			sampgdk::logprintf("*** Streamer_GetIntData: Invalid ID specified");
			break;
		}
		case InvalidType:
		{
			sampgdk::logprintf("*** Streamer_GetIntData: Invalid type specified");
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
					case AttachedVehicle:
					{
						if (static_cast<int>(params[4]) != INVALID_GENERIC_ID)
						{
							o->second->attach = boost::intrusive_ptr<Item::Object::Attach>(new Item::Object::Attach);
							o->second->attach->vehicle = static_cast<int>(params[4]);
							o->second->attach->offset.setZero();
							o->second->attach->rotation.setZero();
							core->getStreamer()->attachedObjects.insert(o->second);
							update = true;
						}
						else
						{
							if (o->second->attach)
							{
								if (o->second->attach->vehicle != INVALID_GENERIC_ID)
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
					case ExtraID:
					{
						return Utility::setFirstValueInContainer(o->second->extras, static_cast<int>(params[4])) != 0;
					}
					case InteriorID:
					{
						return Utility::setFirstValueInContainer(o->second->interiors, static_cast<int>(params[4])) != 0;
					}
					case ModelID:
					{
						o->second->modelID = static_cast<int>(params[4]);
						update = true;
						break;
					}
					case PlayerID:
					{
						return Utility::setFirstValueInContainer(o->second->players, static_cast<int>(params[4])) != 0;
					}
					case WorldID:
					{
						return Utility::setFirstValueInContainer(o->second->worlds, static_cast<int>(params[4])) != 0;
					}
					default:
					{
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
							DestroyPlayerObject(p->first, i->second);
							i->second = CreatePlayerObject(p->first, o->second->modelID, o->second->position[0], o->second->position[1], o->second->position[2], o->second->rotation[0], o->second->rotation[1], o->second->rotation[2], o->second->drawDistance);
							if (o->second->attach)
							{
								AttachPlayerObjectToVehicle(p->first, i->second, o->second->attach->vehicle, o->second->attach->offset[0], o->second->attach->offset[1], o->second->attach->offset[2], o->second->attach->rotation[0], o->second->attach->rotation[1], o->second->attach->rotation[2]);
							}
							else if (o->second->move)
							{
								MovePlayerObject(p->first, i->second, o->second->move->position.get<0>()[0], o->second->move->position.get<0>()[1], o->second->move->position.get<0>()[2], o->second->move->speed, o->second->move->rotation.get<0>()[0], o->second->move->rotation.get<0>()[1], o->second->move->rotation.get<0>()[2]);
							}
							for (boost::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.begin(); m != o->second->materials.end(); ++m)
							{
								if (m->second.main)
								{
									SetPlayerObjectMaterial(p->first, i->second, m->first, m->second.main->modelID, m->second.main->txdFileName.c_str(), m->second.main->textureName.c_str(), m->second.main->materialColor);
								}
								else if (m->second.text)
								{
									SetPlayerObjectMaterialText(p->first, i->second, m->second.text->materialText.c_str(), m->first, m->second.text->materialSize, m->second.text->fontFace.c_str(), m->second.text->fontSize, m->second.text->bold, m->second.text->fontColor, m->second.text->backColor, m->second.text->textAlignment);
								}
							}
						}
					}
					if (update)
					{
						return 1;
					}
				}
			}
			else
			{
				error = InvalidID;
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
					case ExtraID:
					{
						return Utility::setFirstValueInContainer(p->second->extras, static_cast<int>(params[4])) != 0;
					}
					case InteriorID:
					{
						return Utility::setFirstValueInContainer(p->second->interiors, static_cast<int>(params[4])) != 0;
					}
					case ModelID:
					{
						p->second->modelID = static_cast<int>(params[4]);
						update = true;
						break;
					}
					case PlayerID:
					{
						return Utility::setFirstValueInContainer(p->second->players, static_cast<int>(params[4])) != 0;
					}
					case Type:
					{
						p->second->type = static_cast<int>(params[4]);
						update = true;
						break;
					}
					case WorldID:
					{
						return Utility::setFirstValueInContainer(p->second->worlds, static_cast<int>(params[4])) != 0;
					}
					default:
					{
						error = InvalidData;
						break;
					}
				}
				if (update)
				{
					boost::unordered_map<int, int>::iterator i = core->getStreamer()->internalPickups.find(p->first);
					if (i != core->getStreamer()->internalPickups.end())
					{
						DestroyPickup(i->second);
						i->second = CreatePickup(p->second->modelID, p->second->type, p->second->position[0], p->second->position[1], p->second->position[2], p->second->worldID);
					}
				}
				if (update)
				{
					return 1;
				}
			}
			else
			{
				error = InvalidID;
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
					case ExtraID:
					{
						return Utility::setFirstValueInContainer(c->second->extras, static_cast<int>(params[4])) != 0;
					}
					case InteriorID:
					{
						return Utility::setFirstValueInContainer(c->second->interiors, static_cast<int>(params[4])) != 0;
						update = true;
						break;
					}
					case PlayerID:
					{
						return Utility::setFirstValueInContainer(c->second->players, static_cast<int>(params[4])) != 0;
					}
					case WorldID:
					{
						return Utility::setFirstValueInContainer(c->second->worlds, static_cast<int>(params[4])) != 0;
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
				error = InvalidID;
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
					case ExtraID:
					{
						return Utility::setFirstValueInContainer(r->second->extras, static_cast<int>(params[4])) != 0;
					}
					case InteriorID:
					{
						return Utility::setFirstValueInContainer(r->second->interiors, static_cast<int>(params[4])) != 0;
					}
					case PlayerID:
					{
						return Utility::setFirstValueInContainer(r->second->players, static_cast<int>(params[4])) != 0;
					}
					case Type:
					{
						r->second->type = static_cast<int>(params[4]);
						update = true;
						break;
					}
					case WorldID:
					{
						return Utility::setFirstValueInContainer(r->second->worlds, static_cast<int>(params[4])) != 0;
					}
					default:
					{
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
							DisablePlayerRaceCheckpoint(p->first);
							SetPlayerRaceCheckpoint(p->first, r->second->type, r->second->position[0], r->second->position[1], r->second->position[2], r->second->next[0], r->second->next[1], r->second->next[2], r->second->size);
						}
					}
				}
				if (update)
				{
					return 1;
				}
			}
			else
			{
				error = InvalidID;
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
					case Color:
					{
						m->second->color = static_cast<int>(params[4]);
						update = true;
						break;
					}
					case ExtraID:
					{
						return Utility::setFirstValueInContainer(m->second->extras, static_cast<int>(params[4])) != 0;
					}
					case InteriorID:
					{
						return Utility::setFirstValueInContainer(m->second->interiors, static_cast<int>(params[4])) != 0;
					}
					case PlayerID:
					{
						return Utility::setFirstValueInContainer(m->second->players, static_cast<int>(params[4])) != 0;
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
					case WorldID:
					{
						return Utility::setFirstValueInContainer(m->second->worlds, static_cast<int>(params[4])) != 0;
					}
					default:
					{
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
							RemovePlayerMapIcon(p->first, i->second);
							SetPlayerMapIcon(p->first, i->second, m->second->position[0], m->second->position[1], m->second->position[2], m->second->type, m->second->color, m->second->style);
						}
					}
				}
				if (update)
				{
					return 1;
				}
			}
			else
			{
				error = InvalidID;
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
					case AttachedPlayer:
					{
						if (static_cast<int>(params[4]) != INVALID_GENERIC_ID)
						{
							t->second->attach = boost::intrusive_ptr<Item::TextLabel::Attach>(new Item::TextLabel::Attach);
							t->second->attach->player = static_cast<int>(params[4]);
							t->second->attach->vehicle = INVALID_GENERIC_ID;
							core->getStreamer()->attachedTextLabels.insert(t->second);
							update = true;
						}
						else
						{
							if (t->second->attach)
							{
								if (t->second->attach->player != INVALID_GENERIC_ID)
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
						if (static_cast<int>(params[4]) != INVALID_GENERIC_ID)
						{
							t->second->attach = boost::intrusive_ptr<Item::TextLabel::Attach>(new Item::TextLabel::Attach);
							t->second->attach->player = INVALID_GENERIC_ID;
							t->second->attach->vehicle = static_cast<int>(params[4]);
							core->getStreamer()->attachedTextLabels.insert(t->second);
							update = true;
						}
						else
						{
							if (t->second->attach)
							{
								if (t->second->attach->vehicle != INVALID_GENERIC_ID)
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
					case ExtraID:
					{
						return Utility::setFirstValueInContainer(t->second->extras, static_cast<int>(params[4])) != 0;
					}
					case InteriorID:
					{
						return Utility::setFirstValueInContainer(t->second->interiors, static_cast<int>(params[4])) != 0;
					}
					case PlayerID:
					{
						return Utility::setFirstValueInContainer(t->second->players, static_cast<int>(params[4])) != 0;
					}
					case TestLOS:
					{
						t->second->testLOS = static_cast<int>(params[4]) != 0;
						update = true;
						break;
					}
					case WorldID:
					{
						return Utility::setFirstValueInContainer(t->second->worlds, static_cast<int>(params[4])) != 0;
					}
					default:
					{
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
							DeletePlayer3DTextLabel(p->first, i->second);
							i->second = CreatePlayer3DTextLabel(p->first, t->second->text.c_str(), t->second->color, t->second->position[0], t->second->position[1], t->second->position[2], t->second->drawDistance, t->second->attach ? t->second->attach->player : INVALID_GENERIC_ID, t->second->attach ? t->second->attach->vehicle : INVALID_GENERIC_ID, t->second->testLOS);
						}
					}
				}
				if (update)
				{
					return 1;
				}
			}
			else
			{
				error = InvalidID;
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
						sampgdk::logprintf("*** Streamer_SetFloatData: Use AttachDynamicAreaToObject to adjust attached area data");
						return 0;
					}
					case AttachedPlayer:
					{
						if (static_cast<int>(params[4]) != INVALID_GENERIC_ID)
						{
							a->second->attach = boost::intrusive_ptr<Item::Area::Attach>(new Item::Area::Attach);
							a->second->attach->object.get<0>() = INVALID_GENERIC_ID;
							a->second->attach->player = static_cast<int>(params[4]);
							a->second->attach->vehicle = INVALID_GENERIC_ID;
							core->getStreamer()->attachedAreas.insert(a->second);
							return 1;
						}
						else
						{
							if (a->second->attach)
							{
								if (a->second->attach->player != INVALID_GENERIC_ID)
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
						if (static_cast<int>(params[4]) != INVALID_GENERIC_ID)
						{
							a->second->attach = boost::intrusive_ptr<Item::Area::Attach>(new Item::Area::Attach);
							a->second->attach->object.get<0>() = INVALID_GENERIC_ID;
							a->second->attach->player = INVALID_GENERIC_ID;
							a->second->attach->vehicle = static_cast<int>(params[4]);
							core->getStreamer()->attachedAreas.insert(a->second);
							return 1;
						}
						else
						{
							if (a->second->attach)
							{
								if (a->second->attach->vehicle != INVALID_GENERIC_ID)
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
					case ExtraID:
					{
						return Utility::setFirstValueInContainer(a->second->extras, static_cast<int>(params[4])) != 0;
					}
					case InteriorID:
					{
						return Utility::setFirstValueInContainer(a->second->interiors, static_cast<int>(params[4])) != 0;
					}
					case PlayerID:
					{
						return Utility::setFirstValueInContainer(a->second->players, static_cast<int>(params[4])) != 0;
					}
					case WorldID:
					{
						return Utility::setFirstValueInContainer(a->second->worlds, static_cast<int>(params[4])) != 0;
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
				error = InvalidID;
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
			sampgdk::logprintf("*** Streamer_SetIntData: Invalid data specified");
			break;
		}
		case InvalidID:
		{
			sampgdk::logprintf("*** Streamer_SetIntData: Invalid ID specified");
			break;
		}
		case InvalidType:
		{
			sampgdk::logprintf("*** Streamer_SetIntData: Invalid type specified");
			break;
		}
	}
	return 0;
}

int Manipulation::getArrayData(AMX *amx, cell *params)
{
	int error = -1, result = 0;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			result = getArrayDataForItem(core->getData()->objects, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			result = getArrayDataForItem(core->getData()->pickups, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_CP:
		{
			result = getArrayDataForItem(core->getData()->checkpoints, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			result = getArrayDataForItem(core->getData()->raceCheckpoints, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			result = getArrayDataForItem(core->getData()->mapIcons, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			result = getArrayDataForItem(core->getData()->textLabels, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			result = getArrayDataForItem(core->getData()->areas, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
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
			sampgdk::logprintf("*** Streamer_GetArrayData: Invalid data specified");
			break;
		}
		case InvalidID:
		{
			sampgdk::logprintf("*** Streamer_GetArrayData: Invalid ID specified");
			break;
		}
		case InvalidType:
		{
			sampgdk::logprintf("*** Streamer_GetArrayData: Invalid type specified");
			break;
		}
		default:
		{
			return result;
		}
	}
	return 0;
}

int Manipulation::setArrayData(AMX *amx, cell *params)
{
	int error = -1, result = 0;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			result = setArrayDataForItem(core->getData()->objects, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			result = setArrayDataForItem(core->getData()->pickups, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_CP:
		{
			result = setArrayDataForItem(core->getData()->checkpoints, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			result = setArrayDataForItem(core->getData()->raceCheckpoints, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			result = setArrayDataForItem(core->getData()->mapIcons, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			result = setArrayDataForItem(core->getData()->textLabels, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			result = setArrayDataForItem(core->getData()->areas, amx, static_cast<int>(params[2]), static_cast<int>(params[3]), params[4], params[5], error);
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
			sampgdk::logprintf("*** Streamer_SetArrayData: Invalid data specified");
			break;
		}
		case InvalidID:
		{
			sampgdk::logprintf("*** Streamer_SetArrayData: Invalid ID specified");
			break;
		}
		case InvalidType:
		{
			sampgdk::logprintf("*** Streamer_SetArrayData: Invalid type specified");
			break;
		}
		default:
		{
			return result;
		}
	}
	return 0;
}

int Manipulation::isInArrayData(AMX *amx, cell *params)
{
	int error = -1, result = 0;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			result = isInArrayDataForItem(core->getData()->objects, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			result = isInArrayDataForItem(core->getData()->pickups, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_CP:
		{
			result = isInArrayDataForItem(core->getData()->checkpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			result = isInArrayDataForItem(core->getData()->raceCheckpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			result = isInArrayDataForItem(core->getData()->mapIcons, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			result = isInArrayDataForItem(core->getData()->textLabels, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			result = isInArrayDataForItem(core->getData()->areas, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
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
			sampgdk::logprintf("*** Streamer_IsInArrayData: Invalid data specified");
			break;
		}
		case InvalidID:
		{
			sampgdk::logprintf("*** Streamer_IsInArrayData: Invalid ID specified");
			break;
		}
		case InvalidType:
		{
			sampgdk::logprintf("*** Streamer_IsInArrayData: Invalid type specified");
			break;
		}
		default:
		{
			return result;
		}
	}
	return 0;
}

int Manipulation::appendArrayData(AMX *amx, cell *params)
{
	int error = -1, result = 0;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			result = appendArrayDataForItem(core->getData()->objects, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			result = appendArrayDataForItem(core->getData()->pickups, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_CP:
		{
			result = appendArrayDataForItem(core->getData()->checkpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			result = appendArrayDataForItem(core->getData()->raceCheckpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			result = appendArrayDataForItem(core->getData()->mapIcons, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			result = appendArrayDataForItem(core->getData()->textLabels, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			result = appendArrayDataForItem(core->getData()->areas, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
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
			sampgdk::logprintf("*** Streamer_AppendArrayData: Invalid data specified");
			break;
		}
		case InvalidID:
		{
			sampgdk::logprintf("*** Streamer_AppendArrayData: Invalid ID specified");
			break;
		}
		case InvalidType:
		{
			sampgdk::logprintf("*** Streamer_AppendArrayData: Invalid type specified");
			break;
		}
		default:
		{
			return result;
		}
	}
	return 0;
}

int Manipulation::removeArrayData(AMX *amx, cell *params)
{
	int error = -1, result = 0;
	switch (static_cast<int>(params[1]))
	{
		case STREAMER_TYPE_OBJECT:
		{
			result = removeArrayDataForItem(core->getData()->objects, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_PICKUP:
		{
			result = removeArrayDataForItem(core->getData()->pickups, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_CP:
		{
			result = removeArrayDataForItem(core->getData()->checkpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_RACE_CP:
		{
			result = removeArrayDataForItem(core->getData()->raceCheckpoints, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_MAP_ICON:
		{
			result = removeArrayDataForItem(core->getData()->mapIcons, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_3D_TEXT_LABEL:
		{
			result = removeArrayDataForItem(core->getData()->textLabels, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
			break;
		}
		case STREAMER_TYPE_AREA:
		{
			result = removeArrayDataForItem(core->getData()->areas, static_cast<int>(params[2]), static_cast<int>(params[3]), static_cast<int>(params[4]), error);
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
			sampgdk::logprintf("*** Streamer_RemoveArrayData: Invalid data specified");
			break;
		}
		case InvalidID:
		{
			sampgdk::logprintf("*** Streamer_RemoveArrayData: Invalid ID specified");
			break;
		}
		case InvalidType:
		{
			sampgdk::logprintf("*** Streamer_RemoveArrayData: Invalid type specified");
			break;
		}
		default:
		{
			return result;
		}
	}
	return 0;
}
