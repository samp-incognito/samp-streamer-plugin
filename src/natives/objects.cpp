/*
 * Copyright (C) 2016 Incognito
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

#include "../natives.h"

#include "../core.h"
#include "../utility.h"

#include <boost/chrono.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/unordered_map.hpp>

#include <Eigen/Core>

#include <limits>
#include <string>

cell AMX_NATIVE_CALL Natives::CreateDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(14, "CreateDynamicObject");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_OBJECT) == core->getData()->objects.size())
	{
		return 0;
	}
	int objectID = Item::Object::identifier.get();
	Item::SharedObject object(new Item::Object);
	object->amx = amx;
	object->objectID = objectID;
	object->noCameraCollision = false;
	object->originalComparableStreamDistance = -1.0f;
	object->modelID = static_cast<int>(params[1]);
	object->position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
	object->rotation = Eigen::Vector3f(amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7]));
	Utility::addToContainer(object->worlds, static_cast<int>(params[8]));
	Utility::addToContainer(object->interiors, static_cast<int>(params[9]));
	Utility::addToContainer(object->players, static_cast<int>(params[10]));
	object->comparableStreamDistance = amx_ctof(params[11]) < STREAMER_STATIC_DISTANCE_CUTOFF ? amx_ctof(params[11]) : amx_ctof(params[11]) * amx_ctof(params[11]);
	object->streamDistance = amx_ctof(params[11]);
	object->drawDistance = amx_ctof(params[12]);
	Utility::addToContainer(object->areas, static_cast<int>(params[13]));
	object->priority = static_cast<int>(params[14]);
	core->getGrid()->addObject(object);
	core->getData()->objects.insert(std::make_pair(objectID, object));
	return static_cast<cell>(objectID);
}

cell AMX_NATIVE_CALL Natives::DestroyDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "DestroyDynamicObject");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		Utility::destroyObject(o);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsValidDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsValidDynamicObject");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicObjectPos(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "SetDynamicObjectPos");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		Eigen::Vector3f position = o->second->position;
		o->second->position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
			if (i != p->second.internalObjects.end())
			{
				sampgdk::SetPlayerObjectPos(p->first, i->second, o->second->position[0], o->second->position[1], o->second->position[2]);
			}
		}
		if (position[0] != o->second->position[0] || position[1] != o->second->position[1])
		{
			if (o->second->cell)
			{
				core->getGrid()->removeObject(o->second, true);
			}
		}
		if (o->second->move)
		{
			o->second->move->duration = static_cast<int>((static_cast<float>(boost::geometry::distance(o->second->move->position.get<0>(), o->second->position) / o->second->move->speed) * 1000.0f));
			o->second->move->position.get<1>() = o->second->position;
			o->second->move->position.get<2>() = (o->second->move->position.get<0>() - o->second->position) / static_cast<float>(o->second->move->duration);
			if ((o->second->move->rotation.get<0>().maxCoeff() + 1000.0f) > std::numeric_limits<float>::epsilon())
			{
				o->second->move->rotation.get<1>() = o->second->rotation;
				o->second->move->rotation.get<2>() = (o->second->move->rotation.get<0>() - o->second->rotation) / static_cast<float>(o->second->move->duration);
			}
			o->second->move->time = boost::chrono::steady_clock::now();
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicObjectPos(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "GetDynamicObjectPos");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		if (o->second->move)
		{
			core->getStreamer()->processActiveItems();
		}
		Utility::storeFloatInNative(amx, params[2], o->second->position[0]);
		Utility::storeFloatInNative(amx, params[3], o->second->position[1]);
		Utility::storeFloatInNative(amx, params[4], o->second->position[2]);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicObjectRot(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "SetDynamicObjectRot");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		o->second->rotation = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
			if (i != p->second.internalObjects.end())
			{
				sampgdk::SetPlayerObjectRot(p->first, i->second, o->second->rotation[0], o->second->rotation[1], o->second->rotation[2]);
			}
		}
		if (o->second->move)
		{
			if ((o->second->move->rotation.get<0>().maxCoeff() + 1000.0f) > std::numeric_limits<float>::epsilon())
			{
				o->second->move->rotation.get<1>() = o->second->rotation;
				o->second->move->rotation.get<2>() = (o->second->move->rotation.get<0>() - o->second->rotation) / static_cast<float>(o->second->move->duration);
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicObjectRot(AMX *amx, cell *params)
{
	CHECK_PARAMS(4, "GetDynamicObjectRot");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		if (o->second->move)
		{
			core->getStreamer()->processActiveItems();
		}
		Utility::storeFloatInNative(amx, params[2], o->second->rotation[0]);
		Utility::storeFloatInNative(amx, params[3], o->second->rotation[1]);
		Utility::storeFloatInNative(amx, params[4], o->second->rotation[2]);
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicObjectNoCameraCol(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "SetDynamicObjectNoCameraCol");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		o->second->noCameraCollision = true;
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
			if (i != p->second.internalObjects.end())
			{
				sampgdk::SetPlayerObjectNoCameraCol(p->first, i->second);
			}
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicObjectNoCameraCol(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "GetDynamicObjectNoCameraCol");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		return o->second->noCameraCollision != 0;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::MoveDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(8, "MoveDynamicObject");
	if (!amx_ctof(params[5]))
	{
		return 0;
	}
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		if (o->second->attach)
		{
			Utility::logError("MoveDynamicObject: Object is currently attached and cannot be moved");
			return 0;
		}
		Eigen::Vector3f position(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
		Eigen::Vector3f rotation(amx_ctof(params[6]), amx_ctof(params[7]), amx_ctof(params[8]));
		o->second->move = boost::intrusive_ptr<Item::Object::Move>(new Item::Object::Move);
		o->second->move->duration = static_cast<int>((static_cast<float>(boost::geometry::distance(position, o->second->position) / amx_ctof(params[5])) * 1000.0f));
		o->second->move->position.get<0>() = position;
		o->second->move->position.get<1>() = o->second->position;
		o->second->move->position.get<2>() = (position - o->second->position) / static_cast<float>(o->second->move->duration);
		o->second->move->rotation.get<0>() = rotation;
		if ((o->second->move->rotation.get<0>().maxCoeff() + 1000.0f) > std::numeric_limits<float>::epsilon())
		{
			o->second->move->rotation.get<1>() = o->second->rotation;
			o->second->move->rotation.get<2>() = (rotation - o->second->rotation) / static_cast<float>(o->second->move->duration);
		}
		o->second->move->speed = amx_ctof(params[5]);
		o->second->move->time = boost::chrono::steady_clock::now();
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
			if (i != p->second.internalObjects.end())
			{
				sampgdk::StopPlayerObject(p->first, i->second);
				sampgdk::MovePlayerObject(p->first, i->second, o->second->move->position.get<0>()[0], o->second->move->position.get<0>()[1], o->second->move->position.get<0>()[2], o->second->move->speed, o->second->move->rotation.get<0>()[0], o->second->move->rotation.get<0>()[1], o->second->move->rotation.get<0>()[2]);
			}
		}
		core->getStreamer()->movingObjects.insert(o->second);
		return static_cast<cell>(o->second->move->duration);
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::StopDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "StopDynamicObject");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		if (o->second->move)
		{
			for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
			{
				boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
				if (i != p->second.internalObjects.end())
				{
					sampgdk::StopPlayerObject(p->first, i->second);
				}
			}
			o->second->move.reset();
			core->getStreamer()->movingObjects.erase(o->second);
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsDynamicObjectMoving(AMX *amx, cell *params)
{
	CHECK_PARAMS(1, "IsDynamicObjectMoving");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		if (o->second->move)
		{
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::AttachCameraToDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "AttachCameraToDynamicObject");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		int internalID = INVALID_GENERIC_ID;
		boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(static_cast<int>(params[2]));
		if (i == p->second.internalObjects.end())
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				p->second.position = Eigen::Vector3f(o->second->position[0], o->second->position[1], o->second->position[2]);
				core->getStreamer()->startManualUpdate(p->second, STREAMER_TYPE_OBJECT);
			}
			boost::unordered_map<int, int>::iterator j = p->second.internalObjects.find(static_cast<int>(params[2]));
			if (j != p->second.internalObjects.end())
			{
				internalID = j->second;
			}
		}
		else
		{
			internalID = i->second;
		}
		if (internalID != INVALID_GENERIC_ID)
		{
			sampgdk::AttachCameraToPlayerObject(p->first, internalID);
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::AttachDynamicObjectToObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(9, "AttachDynamicObjectToObject");
	if (sampgdk::FindNative("SetPlayerGravity") == NULL)
	{
		Utility::logError("AttachDynamicObjectToObject: YSF plugin must be loaded to attach objects to objects");
		return 0;
	}
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		if (o->second->move)
		{
			Utility::logError("AttachDynamicObjectToObject: Object is currently moving and must be stopped first");
			return 0;
		}
		o->second->attach = boost::intrusive_ptr<Item::Object::Attach>(new Item::Object::Attach);
		o->second->attach->player = INVALID_GENERIC_ID;
		o->second->attach->vehicle = INVALID_GENERIC_ID;
		o->second->attach->object = static_cast<int>(params[2]);
		o->second->attach->offset = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
		o->second->attach->rotation = Eigen::Vector3f(amx_ctof(params[6]), amx_ctof(params[7]), amx_ctof(params[8]));
		o->second->attach->syncRotation = static_cast<int>(params[9]) != 0;
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
			if (i != p->second.internalObjects.end())
			{
				boost::unordered_map<int, int>::iterator j = p->second.internalObjects.find(o->second->attach->object);
				if (j != p->second.internalObjects.end())
				{
					AMX_NATIVE native = sampgdk::FindNative("AttachPlayerObjectToObject");
					if (native != NULL)
					{
						sampgdk::InvokeNative(native, "dddffffffb", p->first, i->second, j->second, o->second->attach->offset[0], o->second->attach->offset[1], o->second->attach->offset[2], o->second->attach->rotation[0], o->second->attach->rotation[1], o->second->attach->rotation[2], o->second->attach->syncRotation);
					}
					for (boost::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.begin(); m != o->second->materials.end(); ++m)
					{
						if (m->second.main)
						{
							sampgdk::SetPlayerObjectMaterial(p->first, i->second, m->first, m->second.main->modelID, m->second.main->txdFileName.c_str(), m->second.main->textureName.c_str(), m->second.main->materialColor);
						}
						else if (m->second.text)
						{
							sampgdk::SetPlayerObjectMaterialText(p->first, i->second, m->second.text->materialText.c_str(), m->first, m->second.text->materialSize, m->second.text->fontFace.c_str(), m->second.text->fontSize, m->second.text->bold, m->second.text->fontColor, m->second.text->backColor, m->second.text->textAlignment);
						}
					}
				}
			}
		}
		if (static_cast<int>(params[2]) != INVALID_STREAMER_ID)
		{
			boost::unordered_map<int, Item::SharedObject>::iterator p = core->getData()->objects.find(static_cast<int>(params[2]));
			if (p != core->getData()->objects.end())
			{
				if (o->second->comparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF && p->second->comparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF)
				{
					o->second->originalComparableStreamDistance = o->second->comparableStreamDistance;
					o->second->comparableStreamDistance = p->second->comparableStreamDistance + static_cast<float>(boost::geometry::comparable_distance(o->second->position, p->second->position));
				}
			}
			core->getStreamer()->attachedObjects.insert(o->second);
		}
		else
		{
			if (o->second->originalComparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF && o->second->comparableStreamDistance > STREAMER_STATIC_DISTANCE_CUTOFF)
			{
				o->second->comparableStreamDistance = o->second->originalComparableStreamDistance;
			}
			o->second->attach.reset();
			core->getStreamer()->attachedObjects.erase(o->second);
			core->getGrid()->removeObject(o->second, true);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::AttachDynamicObjectToPlayer(AMX *amx, cell *params)
{
	CHECK_PARAMS(8, "AttachDynamicObjectToPlayer");
	if (sampgdk::FindNative("SetPlayerGravity") == NULL)
	{
		Utility::logError("AttachDynamicObjectToPlayer: YSF plugin must be loaded to attach objects to players");
		return 0;
	}
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		if (o->second->move)
		{
			Utility::logError("AttachDynamicObjectToPlayer: Object is currently moving and must be stopped first");
			return 0;
		}
		o->second->attach = boost::intrusive_ptr<Item::Object::Attach>(new Item::Object::Attach);
		o->second->attach->object = INVALID_STREAMER_ID;
		o->second->attach->vehicle = INVALID_GENERIC_ID;
		o->second->attach->player = static_cast<int>(params[2]);
		o->second->attach->offset = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
		o->second->attach->rotation = Eigen::Vector3f(amx_ctof(params[6]), amx_ctof(params[7]), amx_ctof(params[8]));
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
			if (i != p->second.internalObjects.end())
			{
				AMX_NATIVE native = sampgdk::FindNative("AttachPlayerObjectToPlayer");
				if (native != NULL)
				{
					sampgdk::InvokeNative(native, "dddffffff", p->first, i->second, o->second->attach->player, o->second->attach->offset[0], o->second->attach->offset[1], o->second->attach->offset[2], o->second->attach->rotation[0], o->second->attach->rotation[1], o->second->attach->rotation[2]);
				}
				for (boost::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.begin(); m != o->second->materials.end(); ++m)
				{
					if (m->second.main)
					{
						sampgdk::SetPlayerObjectMaterial(p->first, i->second, m->first, m->second.main->modelID, m->second.main->txdFileName.c_str(), m->second.main->textureName.c_str(), m->second.main->materialColor);
					}
					else if (m->second.text)
					{
						sampgdk::SetPlayerObjectMaterialText(p->first, i->second, m->second.text->materialText.c_str(), m->first, m->second.text->materialSize, m->second.text->fontFace.c_str(), m->second.text->fontSize, m->second.text->bold, m->second.text->fontColor, m->second.text->backColor, m->second.text->textAlignment);
					}
				}
			}
		}
		if (static_cast<int>(params[2]) != INVALID_GENERIC_ID)
		{
			core->getStreamer()->attachedObjects.insert(o->second);
		}
		else
		{
			o->second->attach.reset();
			core->getStreamer()->attachedObjects.erase(o->second);
			core->getGrid()->removeObject(o->second, true);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::AttachDynamicObjectToVehicle(AMX *amx, cell *params)
{
	CHECK_PARAMS(8, "AttachDynamicObjectToVehicle");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		if (o->second->move)
		{
			Utility::logError("AttachDynamicObjectToVehicle: Object is currently moving and must be stopped first");
			return 0;
		}
		o->second->attach = boost::intrusive_ptr<Item::Object::Attach>(new Item::Object::Attach);
		o->second->attach->object = INVALID_STREAMER_ID;
		o->second->attach->player = INVALID_GENERIC_ID;
		o->second->attach->vehicle = static_cast<int>(params[2]);
		o->second->attach->offset = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
		o->second->attach->rotation = Eigen::Vector3f(amx_ctof(params[6]), amx_ctof(params[7]), amx_ctof(params[8]));
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
			if (i != p->second.internalObjects.end())
			{
				sampgdk::AttachPlayerObjectToVehicle(p->first, i->second, o->second->attach->vehicle, o->second->attach->offset[0], o->second->attach->offset[1], o->second->attach->offset[2], o->second->attach->rotation[0], o->second->attach->rotation[1], o->second->attach->rotation[2]);
				for (boost::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.begin(); m != o->second->materials.end(); ++m)
				{
					if (m->second.main)
					{
						sampgdk::SetPlayerObjectMaterial(p->first, i->second, m->first, m->second.main->modelID, m->second.main->txdFileName.c_str(), m->second.main->textureName.c_str(), m->second.main->materialColor);
					}
					else if (m->second.text)
					{
						sampgdk::SetPlayerObjectMaterialText(p->first, i->second, m->second.text->materialText.c_str(), m->first, m->second.text->materialSize, m->second.text->fontFace.c_str(), m->second.text->fontSize, m->second.text->bold, m->second.text->fontColor, m->second.text->backColor, m->second.text->textAlignment);
					}
				}
			}
		}
		if (static_cast<int>(params[2]) != INVALID_GENERIC_ID)
		{
			core->getStreamer()->attachedObjects.insert(o->second);
		}
		else
		{
			o->second->attach.reset();
			core->getStreamer()->attachedObjects.erase(o->second);
			core->getGrid()->removeObject(o->second, true);
		}
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::EditDynamicObject(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "EditDynamicObject");
	boost::unordered_map<int, Player>::iterator p = core->getData()->players.find(static_cast<int>(params[1]));
	if (p != core->getData()->players.end())
	{
		int internalID = INVALID_GENERIC_ID;
		boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(static_cast<int>(params[2]));
		if (i == p->second.internalObjects.end())
		{
			boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[2]));
			if (o != core->getData()->objects.end())
			{
				p->second.position = Eigen::Vector3f(o->second->position[0], o->second->position[1], o->second->position[2]);
				core->getStreamer()->startManualUpdate(p->second, STREAMER_TYPE_OBJECT);
			}
			boost::unordered_map<int, int>::iterator j = p->second.internalObjects.find(static_cast<int>(params[2]));
			if (j != p->second.internalObjects.end())
			{
				internalID = j->second;
			}
		}
		else
		{
			internalID = i->second;
		}
		if (internalID != INVALID_GENERIC_ID)
		{
			sampgdk::EditPlayerObject(p->first, internalID);
			return 1;
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsDynamicObjectMaterialUsed(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "IsDynamicObjectMaterialUsed");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		boost::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.find(static_cast<int>(params[2]));
		if (m != o->second->materials.end())
		{
			if (m->second.main)
			{
				return 1;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicObjectMaterial(AMX *amx, cell *params)
{
	CHECK_PARAMS(8, "GetDynamicObjectMaterial");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		boost::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.find(static_cast<int>(params[2]));
		if (m != o->second->materials.end())
		{
			if (m->second.main)
			{
				Utility::storeIntegerInNative(amx, params[3], m->second.main->modelID);
				Utility::convertStringToNativeString(amx, params[4], params[7], m->second.main->txdFileName);
				Utility::convertStringToNativeString(amx, params[5], params[8], m->second.main->textureName);
				Utility::storeIntegerInNative(amx, params[6], m->second.main->materialColor);
				return 1;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicObjectMaterial(AMX *amx, cell *params)
{
	CHECK_PARAMS(6, "SetDynamicObjectMaterial");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		int index = static_cast<int>(params[2]);
		o->second->materials[index].main = boost::intrusive_ptr<Item::Object::Material::Main>(new Item::Object::Material::Main);
		o->second->materials[index].main->modelID = static_cast<int>(params[3]);
		o->second->materials[index].main->txdFileName = Utility::convertNativeStringToString(amx, params[4]);
		o->second->materials[index].main->textureName = Utility::convertNativeStringToString(amx, params[5]);
		o->second->materials[index].main->materialColor = static_cast<int>(params[6]);
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
			if (i != p->second.internalObjects.end())
			{
				sampgdk::SetPlayerObjectMaterial(p->first, i->second, index, o->second->materials[index].main->modelID, o->second->materials[index].main->txdFileName.c_str(), o->second->materials[index].main->textureName.c_str(), o->second->materials[index].main->materialColor);
			}
		}
		o->second->materials[index].text.reset();
		return 1;
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::IsDynamicObjectMaterialTextUsed(AMX *amx, cell *params)
{
	CHECK_PARAMS(2, "IsDynamicObjectMaterialTextUsed");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		boost::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.find(static_cast<int>(params[2]));
		if (m != o->second->materials.end())
		{
			if (m->second.text)
			{
				return 1;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::GetDynamicObjectMaterialText(AMX *amx, cell *params)
{
	CHECK_PARAMS(12, "GetDynamicObjectMaterialText");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		boost::unordered_map<int, Item::Object::Material>::iterator m = o->second->materials.find(static_cast<int>(params[2]));
		if (m != o->second->materials.end())
		{
			if (m->second.text)
			{
				Utility::convertStringToNativeString(amx, params[3], params[11], m->second.text->materialText);
				Utility::storeIntegerInNative(amx, params[4], m->second.text->materialSize);
				Utility::convertStringToNativeString(amx, params[5], params[12], m->second.text->fontFace);
				Utility::storeIntegerInNative(amx, params[6], m->second.text->fontSize);
				Utility::storeIntegerInNative(amx, params[7], m->second.text->bold != 0);
				Utility::storeIntegerInNative(amx, params[8], m->second.text->fontColor);
				Utility::storeIntegerInNative(amx, params[9], m->second.text->backColor);
				Utility::storeIntegerInNative(amx, params[10], m->second.text->textAlignment);
				return 1;
			}
		}
	}
	return 0;
}

cell AMX_NATIVE_CALL Natives::SetDynamicObjectMaterialText(AMX *amx, cell *params)
{
	CHECK_PARAMS(10, "SetDynamicObjectMaterialText");
	boost::unordered_map<int, Item::SharedObject>::iterator o = core->getData()->objects.find(static_cast<int>(params[1]));
	if (o != core->getData()->objects.end())
	{
		int index = static_cast<int>(params[2]);
		o->second->materials[index].text = boost::intrusive_ptr<Item::Object::Material::Text>(new Item::Object::Material::Text);
		o->second->materials[index].text->materialText = Utility::convertNativeStringToString(amx, params[3]);
		o->second->materials[index].text->materialSize = static_cast<int>(params[4]);
		o->second->materials[index].text->fontFace = Utility::convertNativeStringToString(amx, params[5]);
		o->second->materials[index].text->fontSize = static_cast<int>(params[6]);
		o->second->materials[index].text->bold = static_cast<int>(params[7]) != 0;
		o->second->materials[index].text->fontColor = static_cast<int>(params[8]);
		o->second->materials[index].text->backColor = static_cast<int>(params[9]);
		o->second->materials[index].text->textAlignment = static_cast<int>(params[10]);
		for (boost::unordered_map<int, Player>::iterator p = core->getData()->players.begin(); p != core->getData()->players.end(); ++p)
		{
			boost::unordered_map<int, int>::iterator i = p->second.internalObjects.find(o->first);
			if (i != p->second.internalObjects.end())
			{
				sampgdk::SetPlayerObjectMaterialText(p->first, i->second, o->second->materials[index].text->materialText.c_str(), index, o->second->materials[index].text->materialSize, o->second->materials[index].text->fontFace.c_str(), o->second->materials[index].text->fontSize, o->second->materials[index].text->bold, o->second->materials[index].text->fontColor, o->second->materials[index].text->backColor, o->second->materials[index].text->textAlignment);
			}
		}
		o->second->materials[index].main.reset();
		return 1;
	}
	return 0;
}
