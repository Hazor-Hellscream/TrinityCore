/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MovementPackets_h__
#define MovementPackets_h__

#include "Packet.h"
#include "Object.h"
#include "Optional.h"

namespace WorldPackets
{
    namespace Movement
    {
        class TransferPending final : public ServerPacket
        {
            struct ShipTransferPending
            {
                uint32 ID = 0;              ///< gameobject_template.entry of the transport the player is teleporting on
                int32 OriginMapID = -1;     ///< Map id the player is currently on (before teleport)
            };

        public:
            TransferPending() : ServerPacket(SMSG_TRANSFER_PENDING, 12) { }

            WorldPacket const* Write() override;

            int32 MapID = -1;
            Optional<ShipTransferPending> Ship;
            Optional<int32> TransferSpellID;
        };

        class SuspendToken final : public ServerPacket
        {
        public:
            SuspendToken() : ServerPacket(SMSG_SUSPEND_TOKEN, 4 + 1) { }

            WorldPacket const* Write() override;

            uint32 SequenceIndex = 1;
            uint8 Reason = 1;
        };

        class SuspendTokenResponse final : public ClientPacket
        {
        public:
            SuspendTokenResponse(WorldPacket&& packet) : ClientPacket(CMSG_SUSPEND_TOKEN_RESPONSE, std::move(packet)) { }

            void Read() override;

            uint32 SequenceIndex = 0;
        };

        class NewWorld final : public ServerPacket
        {
        public:
            NewWorld() : ServerPacket(SMSG_NEW_WORLD, 4 + 4 + 4 + 4 + 4) { }

            WorldPacket const* Write() override;

            int32 MapID = 0;
            Position Pos;
        };

        class MoveSetCollisionHeight final : public ServerPacket
        {
        public:
            MoveSetCollisionHeight() : ServerPacket(SMSG_MOVE_SET_COLLISION_HEIGHT, 15) { }

            WorldPacket const* Write() override;

            ObjectGuid MoverGUID;
            uint32 SequenceIndex = 0;
            float Height = 1.0f;
            UpdateCollisionHeightReason Reason = UPDATE_COLLISION_HEIGHT_MOUNT;
        };
    }
}

#endif // MovementPackets_h__
