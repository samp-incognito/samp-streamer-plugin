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

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/variant.hpp>

#include <Eigen/Core>

cell AMX_NATIVE_CALL Natives::CreateDynamicObjectEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(18, "CreateDynamicObjectEx");
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
	object->drawDistance = amx_ctof(params[8]);
	object->comparableStreamDistance = amx_ctof(params[9]) < STREAMER_STATIC_DISTANCE_CUTOFF ? amx_ctof(params[9]) : amx_ctof(params[9]) * amx_ctof(params[9]);
	object->streamDistance = amx_ctof(params[9]);
	Utility::convertArrayToContainer(amx, params[10], params[15], object->worlds);
	Utility::convertArrayToContainer(amx, params[11], params[16], object->interiors);
	Utility::convertArrayToContainer(amx, params[12], params[17], object->players);
	Utility::convertArrayToContainer(amx, params[13], params[18], object->areas);
	object->priority = static_cast<int>(params[14]);
	core->getGrid()->addObject(object);
	core->getData()->objects.insert(std::make_pair(objectID, object));
	return static_cast<cell>(objectID);
	return 1;
}

cell AMX_NATIVE_CALL Natives::CreateDynamicPickupEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(15, "CreateDynamicPickupEx");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_PICKUP) == core->getData()->pickups.size())
	{
		return 0;
	}
	int pickupID = Item::Pickup::identifier.get();
	Item::SharedPickup pickup(new Item::Pickup);
	pickup->amx = amx;
	pickup->pickupID = pickupID;
	pickup->originalComparableStreamDistance = -1.0f;
	pickup->modelID = static_cast<int>(params[1]);
	pickup->type = static_cast<int>(params[2]);
	pickup->position = Eigen::Vector3f(amx_ctof(params[3]), amx_ctof(params[4]), amx_ctof(params[5]));
	pickup->comparableStreamDistance = amx_ctof(params[6]) < STREAMER_STATIC_DISTANCE_CUTOFF ? amx_ctof(params[6]) : amx_ctof(params[6]) * amx_ctof(params[6]);
	pickup->streamDistance = amx_ctof(params[6]);
	Utility::convertArrayToContainer(amx, params[7], params[12], pickup->worlds);
	Utility::convertArrayToContainer(amx, params[8], params[13], pickup->interiors);
	Utility::convertArrayToContainer(amx, params[9], params[14], pickup->players);
	Utility::convertArrayToContainer(amx, params[10], params[15], pickup->areas);
	pickup->priority = static_cast<int>(params[11]);
	core->getGrid()->addPickup(pickup);
	core->getData()->pickups.insert(std::make_pair(pickupID, pickup));
	return static_cast<cell>(pickupID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCPEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(14, "CreateDynamicCPEx");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_CP) == core->getData()->checkpoints.size())
	{
		return 0;
	}
	int checkpointID = Item::Checkpoint::identifier.get();
	Item::SharedCheckpoint checkpoint(new Item::Checkpoint);
	checkpoint->amx = amx;
	checkpoint->checkpointID = checkpointID;
	checkpoint->originalComparableStreamDistance = -1.0f;
	checkpoint->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	checkpoint->size = amx_ctof(params[4]);
	checkpoint->comparableStreamDistance = amx_ctof(params[5]) < STREAMER_STATIC_DISTANCE_CUTOFF ? amx_ctof(params[5]) : amx_ctof(params[5]) * amx_ctof(params[5]);
	checkpoint->streamDistance = amx_ctof(params[5]);
	Utility::convertArrayToContainer(amx, params[6], params[11], checkpoint->worlds);
	Utility::convertArrayToContainer(amx, params[7], params[12], checkpoint->interiors);
	Utility::convertArrayToContainer(amx, params[8], params[13], checkpoint->players);
	Utility::convertArrayToContainer(amx, params[9], params[14], checkpoint->areas);
	checkpoint->priority = static_cast<int>(params[10]);
	core->getGrid()->addCheckpoint(checkpoint);
	core->getData()->checkpoints.insert(std::make_pair(checkpointID, checkpoint));
	return static_cast<cell>(checkpointID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicRaceCPEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(18, "CreateDynamicRaceCPEx");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_RACE_CP) == core->getData()->raceCheckpoints.size())
	{
		return 0;
	}
	int raceCheckpointID = Item::RaceCheckpoint::identifier.get();
	Item::SharedRaceCheckpoint raceCheckpoint(new Item::RaceCheckpoint);
	raceCheckpoint->amx = amx;
	raceCheckpoint->raceCheckpointID = raceCheckpointID;
	raceCheckpoint->originalComparableStreamDistance = -1.0f;
	raceCheckpoint->type = static_cast<int>(params[1]);
	raceCheckpoint->position = Eigen::Vector3f(amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
	raceCheckpoint->next = Eigen::Vector3f(amx_ctof(params[5]), amx_ctof(params[6]), amx_ctof(params[7]));
	raceCheckpoint->size = amx_ctof(params[8]);
	raceCheckpoint->comparableStreamDistance = amx_ctof(params[9]) < STREAMER_STATIC_DISTANCE_CUTOFF ? amx_ctof(params[9]) : amx_ctof(params[9]) * amx_ctof(params[9]);
	raceCheckpoint->streamDistance = amx_ctof(params[9]);
	Utility::convertArrayToContainer(amx, params[10], params[15], raceCheckpoint->worlds);
	Utility::convertArrayToContainer(amx, params[11], params[16], raceCheckpoint->interiors);
	Utility::convertArrayToContainer(amx, params[12], params[17], raceCheckpoint->players);
	Utility::convertArrayToContainer(amx, params[13], params[18], raceCheckpoint->areas);
	raceCheckpoint->priority = static_cast<int>(params[14]);
	core->getGrid()->addRaceCheckpoint(raceCheckpoint);
	core->getData()->raceCheckpoints.insert(std::make_pair(raceCheckpointID, raceCheckpoint));
	return static_cast<cell>(raceCheckpointID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicMapIconEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(16, "CreateDynamicMapIconEx");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_MAP_ICON) == core->getData()->mapIcons.size())
	{
		return 0;
	}
	int mapIconID = Item::MapIcon::identifier.get();
	Item::SharedMapIcon mapIcon(new Item::MapIcon);
	mapIcon->amx = amx;
	mapIcon->mapIconID = mapIconID;
	mapIcon->originalComparableStreamDistance = -1.0f;
	mapIcon->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	mapIcon->type = static_cast<int>(params[4]);
	mapIcon->color = static_cast<int>(params[5]);
	mapIcon->style = static_cast<int>(params[6]);
	mapIcon->comparableStreamDistance = amx_ctof(params[7]) < STREAMER_STATIC_DISTANCE_CUTOFF ? amx_ctof(params[7]) : amx_ctof(params[7]) * amx_ctof(params[7]);
	mapIcon->streamDistance = amx_ctof(params[7]);
	Utility::convertArrayToContainer(amx, params[8], params[13], mapIcon->worlds);
	Utility::convertArrayToContainer(amx, params[9], params[14], mapIcon->interiors);
	Utility::convertArrayToContainer(amx, params[10], params[15], mapIcon->players);
	Utility::convertArrayToContainer(amx, params[11], params[16], mapIcon->areas);
	mapIcon->priority = static_cast<int>(params[12]);
	core->getGrid()->addMapIcon(mapIcon);
	core->getData()->mapIcons.insert(std::make_pair(mapIconID, mapIcon));
	return static_cast<cell>(mapIconID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamic3DTextLabelEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(19, "CreateDynamic3DTextLabelEx");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_3D_TEXT_LABEL) == core->getData()->textLabels.size())
	{
		return 0;
	}
	int textLabelID = Item::TextLabel::identifier.get();
	Item::SharedTextLabel textLabel(new Item::TextLabel);
	textLabel->amx = amx;
	textLabel->textLabelID = textLabelID;
	textLabel->originalComparableStreamDistance = -1.0f;
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
	textLabel->comparableStreamDistance = amx_ctof(params[10]) < STREAMER_STATIC_DISTANCE_CUTOFF ? amx_ctof(params[10]) : amx_ctof(params[10]) * amx_ctof(params[10]);
	textLabel->streamDistance = amx_ctof(params[10]);
	Utility::convertArrayToContainer(amx, params[11], params[16], textLabel->worlds);
	Utility::convertArrayToContainer(amx, params[12], params[17], textLabel->interiors);
	Utility::convertArrayToContainer(amx, params[13], params[18], textLabel->players);
	Utility::convertArrayToContainer(amx, params[14], params[19], textLabel->areas);
	textLabel->priority = static_cast<int>(params[15]);
	core->getGrid()->addTextLabel(textLabel);
	core->getData()->textLabels.insert(std::make_pair(textLabelID, textLabel));
	return static_cast<cell>(textLabelID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCircleEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(9, "CreateDynamicCircleEx");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->type = STREAMER_AREA_TYPE_CIRCLE;
	area->position = Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2]));
	area->comparableSize = amx_ctof(params[3]) * amx_ctof(params[3]);
	area->size = amx_ctof(params[3]);
	Utility::convertArrayToContainer(amx, params[4], params[7], area->worlds);
	Utility::convertArrayToContainer(amx, params[5], params[8], area->interiors);
	Utility::convertArrayToContainer(amx, params[6], params[9], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCylinderEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(11, "CreateDynamicCylinderEx");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->type = STREAMER_AREA_TYPE_CYLINDER;
	area->position = Eigen::Vector2f(amx_ctof(params[1]), amx_ctof(params[2]));
	area->height = Eigen::Vector2f(amx_ctof(params[3]), amx_ctof(params[4]));
	area->comparableSize = amx_ctof(params[5]) * amx_ctof(params[5]);
	area->size = amx_ctof(params[5]);
	Utility::convertArrayToContainer(amx, params[6], params[9], area->worlds);
	Utility::convertArrayToContainer(amx, params[7], params[10], area->interiors);
	Utility::convertArrayToContainer(amx, params[8], params[11], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicSphereEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(10, "CreateDynamicSphereEx");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->type = STREAMER_AREA_TYPE_SPHERE;
	area->position = Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3]));
	area->comparableSize = amx_ctof(params[4]) * amx_ctof(params[4]);
	area->size = amx_ctof(params[4]);
	Utility::convertArrayToContainer(amx, params[5], params[8], area->worlds);
	Utility::convertArrayToContainer(amx, params[6], params[9], area->interiors);
	Utility::convertArrayToContainer(amx, params[7], params[10], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicRectangleEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(10, "CreateDynamicRectangleEx");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
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
	area->comparableSize = static_cast<float>(boost::geometry::comparable_distance(boost::get<Box2D>(area->position).min_corner(), boost::get<Box2D>(area->position).max_corner()));
	area->size = static_cast<float>(boost::geometry::distance(boost::get<Box2D>(area->position).min_corner(), boost::get<Box2D>(area->position).max_corner()));
	Utility::convertArrayToContainer(amx, params[5], params[8], area->worlds);
	Utility::convertArrayToContainer(amx, params[6], params[9], area->interiors);
	Utility::convertArrayToContainer(amx, params[7], params[10], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}

cell AMX_NATIVE_CALL Natives::CreateDynamicCuboidEx(AMX *amx, cell *params)
{
	CHECK_PARAMS(12, "CreateDynamicCuboidEx");
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->type = STREAMER_AREA_TYPE_CUBOID;
	area->position = Box3D(Eigen::Vector3f(amx_ctof(params[1]), amx_ctof(params[2]), amx_ctof(params[3])), Eigen::Vector3f(amx_ctof(params[4]), amx_ctof(params[5]), amx_ctof(params[6])));
	boost::geometry::correct(boost::get<Box3D>(area->position));
	area->comparableSize = static_cast<float>(boost::geometry::comparable_distance(Eigen::Vector2f(boost::get<Box3D>(area->position).min_corner()[0], boost::get<Box3D>(area->position).min_corner()[1]), Eigen::Vector2f(boost::get<Box3D>(area->position).max_corner()[0], boost::get<Box3D>(area->position).max_corner()[1])));
	area->size = static_cast<float>(boost::geometry::distance(Eigen::Vector2f(boost::get<Box3D>(area->position).min_corner()[0], boost::get<Box3D>(area->position).min_corner()[1]), Eigen::Vector2f(boost::get<Box3D>(area->position).max_corner()[0], boost::get<Box3D>(area->position).max_corner()[1])));
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
	if (core->getData()->getGlobalMaxItems(STREAMER_TYPE_AREA) == core->getData()->areas.size())
	{
		return 0;
	}
	if (static_cast<int>(params[4] >= 2 && static_cast<int>(params[4]) % 2))
	{
		Utility::logError("CreateDynamicPolygonEx: Number of points must be divisible by two");
	}
	int areaID = Item::Area::identifier.get();
	Item::SharedArea area(new Item::Area);
	area->amx = amx;
	area->areaID = areaID;
	area->type = STREAMER_AREA_TYPE_POLYGON;
	Utility::convertArrayToPolygon(amx, params[1], params[4], boost::get<Polygon2D>(area->position));
	area->height = Eigen::Vector2f(amx_ctof(params[2]), amx_ctof(params[3]));
	Box2D box = boost::geometry::return_envelope<Box2D>(boost::get<Polygon2D>(area->position));
	area->comparableSize = static_cast<float>(boost::geometry::comparable_distance(box.min_corner(), box.max_corner()));
	area->size = static_cast<float>(boost::geometry::distance(box.min_corner(), box.max_corner()));
	Utility::convertArrayToContainer(amx, params[5], params[8], area->worlds);
	Utility::convertArrayToContainer(amx, params[6], params[9], area->interiors);
	Utility::convertArrayToContainer(amx, params[7], params[10], area->players);
	core->getGrid()->addArea(area);
	core->getData()->areas.insert(std::make_pair(areaID, area));
	return static_cast<cell>(areaID);
}
