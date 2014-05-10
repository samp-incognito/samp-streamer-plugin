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

#include "../natives.h"

#include "../core.h"
#include "../main.h"
#include "../utility.h"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/variant.hpp>

#include <Eigen/Core>

#include <sampgdk/core.h>

cell AMX_NATIVE_CALL Natives::CreateDynamicObjectEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(15, "CreateDynamicObjectEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_OBJECT) == core->getData()->objects.size())
	{
		return 0;
	}
	int objectID = Item::Object::identifier.get();
	Item::SharedObject object(new Item::Object);
	object->amx = amx;
	object->objectID = objectID;
	object->modelID = static_cast<int>(params[1]);
	object->position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
	object->rotation = Eigen::Vector3f(amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7]));
	object->drawDistance = amx_ctof(params[8]);
	object->streamDistance = amx_ctof(params[9]) * amx_ctof(params[9]);
	Utility::convertArrayToContainer(amx, params[10], params[13], object->worlds);
	Utility::convertArrayToContainer(amx, params[11], params[14], object->interiors);
	Utility::convertArrayToContainer(amx, params[12], params[15], object->players);
	core->getGrid()->addObject(object);
	core->getData()->objects.insert(std::make_pair(objectID, object));
	return static_cast<cell>(objectID);
	return 1;
}

cell AMX_NATIVE_CALL Natives::CreateDynamicPickupEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(12, "CreateDynamicPickupEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_PICKUP) == core->getData()->pickups.size())
	{
		return 0;
	}
	int pickupID = Item::Pickup::identifier.get();
	Item::SharedPickup pickup(new Item::Pickup);
	pickup->amx = amx;
	pickup->pickupID = pickupID;
	pickup->modelID = static_cast<int>(params[1]);
	pickup->type = static_cast<int>(params[2]);
	pickup->position = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
	pickup->streamDistance = amx_ctof(params[6]) * amx_ctof(params[6]);
	Utility::convertArrayToContainer(amx, params[7], params[10], pickup->worlds);
	Utility::convertArrayToContainer(amx, params[8], params[11], pickup->interiors);
	Utility::convertArrayToContainer(amx, params[9], params[12], pickup->players);
	core->getGrid()->addPickup(pickup);
	core->getData()->pickups.insert(std::make_pair(pickupID, pickup));
	return static_cast<cell>(pickupID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCPEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(11, "CreateDynamicCPEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_CP) == core->getData()->checkpoints.size())
	{
		return 0;
	}
	int checkpointID = Item::Checkpoint::identifier.get();
	Item::SharedCheckpoint checkpoint(new Item::Checkpoint);
	checkpoint->amx = amx;
	checkpoint->checkpointID = checkpointID;
	checkpoint->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	checkpoint->size = amx_ctof(params[4]);
	checkpoint->streamDistance = amx_ctof(params[5]) * amx_ctof(params[5]);
	Utility::convertArrayToContainer(amx, params[6], params[9], checkpoint->worlds);
	Utility::convertArrayToContainer(amx, params[7], params[10], checkpoint->interiors);
	Utility::convertArrayToContainer(amx, params[8], params[11], checkpoint->players);
	core->getGrid()->addCheckpoint(checkpoint);
	core->getData()->checkpoints.insert(std::make_pair(checkpointID, checkpoint));
	return static_cast<cell>(checkpointID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicRaceCPEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(15, "CreateDynamicRaceCPEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_RACE_CP) == core->getData()->raceCheckpoints.size())
	{
		return 0;
	}
	int raceCheckpointID = Item::RaceCheckpoint::identifier.get();
	Item::SharedRaceCheckpoint raceCheckpoint(new Item::RaceCheckpoint);
	raceCheckpoint->amx = amx;
	raceCheckpoint->raceCheckpointID = raceCheckpointID;
	raceCheckpoint->type = static_cast<int>(params[1]);
	raceCheckpoint->position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
	raceCheckpoint->next = Eigen::Vector3f(amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7]));
	raceCheckpoint->size = amx_ctof(params[8]);
	raceCheckpoint->streamDistance = amx_ctof(params[9]) * amx_ctof(params[9]);
	Utility::convertArrayToContainer(amx, params[10], params[13], raceCheckpoint->worlds);
	Utility::convertArrayToContainer(amx, params[11], params[14], raceCheckpoint->interiors);
	Utility::convertArrayToContainer(amx, params[12], params[15], raceCheckpoint->players);
	core->getGrid()->addRaceCheckpoint(raceCheckpoint);
	core->getData()->raceCheckpoints.insert(std::make_pair(raceCheckpointID, raceCheckpoint));
	return static_cast<cell>(raceCheckpointID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicMapIconEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(13, "CreateDynamicMapIconEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_MAP_ICON) == core->getData()->mapIcons.size())
	{
		return 0;
	}
	int mapIconID = Item::MapIcon::identifier.get();
	Item::SharedMapIcon mapIcon(new Item::MapIcon);
	mapIcon->amx = amx;
	mapIcon->mapIconID = mapIconID;
	mapIcon->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	mapIcon->type = static_cast<int>(params[4]);
	mapIcon->color = static_cast<int>(params[5]);
	mapIcon->style = static_cast<int>(params[6]);
	mapIcon->streamDistance = amx_ctof(params[7]) * amx_ctof(params[7]);
	Utility::convertArrayToContainer(amx, params[8], params[11], mapIcon->worlds);
	Utility::convertArrayToContainer(amx, params[9], params[12], mapIcon->interiors);
	Utility::convertArrayToContainer(amx, params[10], params[13], mapIcon->players);
	core->getGrid()->addMapIcon(mapIcon);
	core->getData()->mapIcons.insert(std::make_pair(mapIconID, mapIcon));
	return static_cast<cell>(mapIconID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamic3DTextLabelEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(16, "CreateDynamic3DTextLabelEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_3D_TEXT_LABEL) == core->getData()->textLabels.size())
	{
		return 0;
	}
	int textLabelID = Item::TextLabel::identifier.get();
	Item::SharedTextLabel textLabel(new Item::TextLabel);
	textLabel->amx = amx;
	textLabel->textLabelID = textLabelID;
	textLabel->text = Utility::convertNativeStringToString(amx, params[1]);
	textLabel->color = static_cast<int>(params[2]);
	textLabel->position = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
	textLabel->drawDistance = amx_ctof(params[6]);
	if (static_cast<int>(params[7]) != INVALID_GENERIC_ID || static_cast<int>(params[8]) != INVALID_GENERIC_ID)
	{
		textLabel->attach = boost::intrusive_ptr<Item::TextLabel::Attach>(new Item::TextLabel::Attach);
		textLabel->attach->player = static_cast<int>(params[7]);
		textLabel->attach->vehicle = static_cast<int>(params[8]);
		if (textLabel->position.cwiseAbs().maxCoeff() > 50.0f)
		{
			textLabel->position.setZero();
		}
		core->getStreamer()->attachedTextLabels.insert(textLabel);
	}
	textLabel->testLOS = static_cast<int>(params[9]) != 0;
	textLabel->streamDistance = amx_ctof(params[10]) * amx_ctof(params[10]);
	Utility::convertArrayToContainer(amx, params[11], params[14], textLabel->worlds);
	Utility::convertArrayToContainer(amx, params[12], params[15], textLabel->interiors);
	Utility::convertArrayToContainer(amx, params[13], params[16], textLabel->players);
	core->getGrid()->addTextLabel(textLabel);
	core->getData()->textLabels.insert(std::make_pair(textLabelID, textLabel));
	return static_cast<cell>(textLabelID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCircleEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(9, "CreateDynamicCircleEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->type = STREAMER_AREA_TYPE_CIRCLE;
	area->position = Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2]));
	area->size = amx_ctof(params[3]) * amx_ctof(params[3]);
	Utility::convertArrayToContainer(amx, params[4], params[7], area->worlds);
	Utility::convertArrayToContainer(amx, params[5], params[8], area->interiors);
	Utility::convertArrayToContainer(amx, params[6], params[9], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicRectangleEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(10, "CreateDynamicRectangleEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->type = STREAMER_AREA_TYPE_RECTANGLE;
	area->position = Box2D(Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2])), Eigen::Vector2f(amx_ctof(params[3]), amx_ctof(params[4])));
	boost::geometry::correct(boost::get<Box2D>(area->position));
	area->size = static_cast<float>(boost::geometry::comparable_distance(boost::get<Box2D>(area->position).min_corner(), boost::get<Box2D>(area->position).max_corner()));
	Utility::convertArrayToContainer(amx, params[5], params[8], area->worlds);
	Utility::convertArrayToContainer(amx, params[6], params[9], area->interiors);
	Utility::convertArrayToContainer(amx, params[7], params[10], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicSphereEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(10, "CreateDynamicSphereEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->type = STREAMER_AREA_TYPE_SPHERE;
	area->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	area->size = amx_ctof(params[4]) * amx_ctof(params[4]);
	Utility::convertArrayToContainer(amx, params[5], params[8], area->worlds);
	Utility::convertArrayToContainer(amx, params[6], params[9], area->interiors);
	Utility::convertArrayToContainer(amx, params[7], params[10], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCubeEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(12, "CreateDynamicCubeEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->type = STREAMER_AREA_TYPE_CUBE;
	area->position = Box3D(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), Eigen::Vector3f(amx_ctof(params[4]), amx_ctof(params[5]), amx_ctof(params[6])));
	boost::geometry::correct(boost::get<Box3D>(area->position));
	area->size = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(boost::get<Box3D>(area->position).min_corner()[0], boost::get<Box3D>(area->position).min_corner()[1]), Eigen::Vector2f(boost::get<Box3D>(area->position).max_corner()[0], boost::get<Box3D>(area->position).max_corner()[1])));
	Utility::convertArrayToContainer(amx, params[7], params[10], area->worlds);
	Utility::convertArrayToContainer(amx, params[8], params[11], area->interiors);
	Utility::convertArrayToContainer(amx, params[9], params[12], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicPolygonEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(10, "CreateDynamicPolygonEx");
	if (core->getData()->getMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	if (static_cast<int>(params[4] >= 2 && static_cast<int>(params[4]) % 2))
	{
		sampgdk_logprintf("*** CreateDynamicPolygonEx: Number of points must be divisible by two");
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->type = STREAMER_AREA_TYPE_POLYGON;
	Utility::convertArrayToPolygon(amx, params[1], params[4], boost::get<Polygon2D>(area->position));
	Box2D box = boost::geometry::return_envelope<Box2D>(boost::get<Polygon2D>(area->position).get<0>());
	area->size = static_cast<float>(boost::geometry::comparable_distance(box.min_corner(), box.max_corner()));
	boost::get<Polygon2D>(area->position).get<1>() = Eigen::Vector2f(amx_ctof(params[2]), amx_ctof(params[3]));
	Utility::convertArrayToContainer(amx, params[5], params[8], area->worlds);
	Utility::convertArrayToContainer(amx, params[6], params[9], area->interiors);
	Utility::convertArrayToContainer(amx, params[7], params[10], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}
