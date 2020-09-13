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

#ifndef MANIPULATION_INT_H
#define MANIPULATION_INT_H

#include "../manipulation.h"

namespace Manipulation
{
	int getIntData(AMX *amx, cell *params);
	int setIntData(AMX *amx, cell *params);
	int removeIntData(AMX *amx, cell *params);
	int hasIntData(AMX *amx, cell *params);
}

#endif
