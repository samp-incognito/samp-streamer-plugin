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

#include "item.h"

#include "identifier.h"

Identifier Item::Area::identifier;
Identifier Item::Checkpoint::identifier;
Identifier Item::MapIcon::identifier;
Identifier Item::Object::identifier;
Identifier Item::Pickup::identifier;
Identifier Item::RaceCheckpoint::identifier;
Identifier Item::TextLabel::identifier;
Identifier Item::Actor::identifier;

Item::Area::Area() : references(0) {}
Item::Area::Attach::Attach() : references(0) {}
Item::Checkpoint::Checkpoint() : references(0) {}
Item::MapIcon::MapIcon() : references(0) {}
Item::Object::Object() : references(0) {}
Item::Object::Attach::Attach() : references(0) {}
Item::Object::Material::Main::Main() : references(0) {}
Item::Object::Material::Text::Text() : references(0) {}
Item::Object::Move::Move() : references(0) {}
Item::Pickup::Pickup() : references(0) {}
Item::RaceCheckpoint::RaceCheckpoint() : references(0) {}
Item::TextLabel::TextLabel() : references(0) {}
Item::TextLabel::Attach::Attach() : references(0) {}
Item::Actor::Actor() : references(0) {}
