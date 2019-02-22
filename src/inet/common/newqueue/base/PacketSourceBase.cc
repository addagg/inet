//
// Copyright (C) OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see http://www.gnu.org/licenses/.
//

#include "inet/common/newqueue/base/PacketSourceBase.h"

namespace inet {
namespace queue {

void PacketSourceBase::initialize()
{
    cSimpleModule::initialize();
    asynchronous = par("asynchronous");
}

void PacketSourceBase::handleMessage(cMessage *msg)
{
    throw cRuntimeError("Invalid operation");
}

void PacketSourceBase::requestPacket()
{
    ASSERT(!hasPendingRequestPacket);
    hasPendingRequestPacket = true;
    handlePendingRequestPacket();
}

void PacketSourceBase::handlePendingRequestPacket()
{
    Enter_Method_Silent();
    if (!isEmpty()) {
        send(popPacket(), "out");
        hasPendingRequestPacket = false;
    }
}

} // namespace queue
} // namespace inet
