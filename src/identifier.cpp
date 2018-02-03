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

#include "identifier.h"

#include <functional>
#include <queue>
#include <vector>

Identifier::Identifier()
{
	highestId = 0;
}

int Identifier::get()
{
	int id = 0;
	if (!removedIds.empty())
	{
		id = removedIds.top();
		removedIds.pop();
	}
	else
	{
		id = ++highestId;
	}
	return id;
}

void Identifier::remove(int id, std::size_t remaining)
{
	if (remaining > 1)
	{
		removedIds.push(id);
	}
	else
	{
		reset();
	}
}

void Identifier::reset()
{
	highestId = 0;
	removedIds = std::priority_queue<int, std::vector<int>, std::greater<int> >();
}
