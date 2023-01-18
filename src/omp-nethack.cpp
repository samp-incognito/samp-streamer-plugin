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

#include "main.h"
#include "core.h"

#include "bitstream.hpp"

#include "omp-nethack.h"

static int GetObjectStreamerId(int playerid, int objectid)
{
    std::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
    if (p != core->getData()->players.end())
    {
        for (std::unordered_map<int, int>::iterator i = p->second.internalObjects.begin(); i != p->second.internalObjects.end(); ++i)
        {
            if (i->second == objectid)
            {
                return i->first;
            }
        }
    }
    return INVALID_STREAMER_ID;
}

static int GetObjectInternalId(int playerid, int streamerid)
{
    std::unordered_map<int, Player>::iterator p = core->getData()->players.find(playerid);
    if (p != core->getData()->players.end())
    {
        std::unordered_map<int, int>::iterator i = p->second.internalObjects.find(streamerid);
        if (i != p->second.internalObjects.end())
        {
            return i->second;
        }
    }
    return INVALID_OBJECT_ID;
}

void OMPNetHack::Process(IPlayerPool* players, IPlayer* peer, NetworkBitStream& bs)
{
    if(!peer)
    {
        return;
    }

    uint16_t playerid;
    bs.SetReadOffset(8);
    bs.readUINT16(playerid);

    IPlayer* player = players->get(playerid);
    if(!player)
    {
        return;
    }

    PlayerSurfingData surfingData = player->getSurfingData();
    if(surfingData.type != PlayerSurfingData::Type::PlayerObject)
    {
        return;
    }

    int object_streamer_id = GetObjectStreamerId(playerid, surfingData.ID);
    if(object_streamer_id == INVALID_STREAMER_ID)
    {
        return;
    }

    int player_object_id = GetObjectInternalId(peer->getID(), object_streamer_id);
    if(player_object_id == INVALID_OBJECT_ID)
    {
        return;
    }

    bool conditionalRead;
    uint16_t AnimationID;
    uint16_t AnimationFlags;

    bs.readBIT(conditionalRead);
    if(conditionalRead)
    {
        bs.IgnoreBits(16);
    }
    bs.readBIT(conditionalRead);
    if(conditionalRead)
    {
        bs.IgnoreBits(16);
    }

    bs.IgnoreBits(16 + (32*3) + ( 4 + 16*3 ) + 8 + 8 + 8);
    
    float magnitude;
    if(bs.readFLOAT(magnitude) && magnitude > 0.00001f)
    {
        bs.IgnoreBits(3*16);
    }
    
    int surfingDataWriteOffset = bs.GetReadOffset();

    bs.IgnoreBits(1);

    bs.readBIT(conditionalRead);
    if(conditionalRead)
    {
        bs.readUINT16(AnimationID);
        bs.readUINT16(AnimationFlags);
    }

    bs.SetWriteOffset(surfingDataWriteOffset);
    bs.writeBIT(true);
    bs.writeUINT16(player_object_id + VEHICLE_POOL_SIZE);
    bs.writeVEC3(surfingData.offset);
    bs.writeBIT(conditionalRead);
    if(conditionalRead)
    {
        bs.writeUINT16(AnimationID);
        bs.writeUINT16(AnimationFlags);
    }
    return;
}
