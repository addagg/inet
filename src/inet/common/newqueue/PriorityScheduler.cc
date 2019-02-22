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

#include "inet/common/newqueue/PriorityScheduler.h"

namespace inet {
namespace queue {

Define_Module(PriorityScheduler);

void PriorityScheduler::handlePendingRequestPacket()
{
    if (asynchronous) {
        Enter_Method_Silent();
        for (auto queue : inputQueues) {
            if (!queue->isEmpty()) {
                queue->requestPacket();
                hasPendingRequestPacket = false;
                break;
            }
        }
    }
    else
        PacketSourceBase::handlePendingRequestPacket();
}

int PriorityScheduler::schedulePacket() const
{
    for (int i = 0; i < (int)inputQueues.size(); i++) {
        auto queue = inputQueues[i];
        if (!queue->isEmpty())
            return i;
    }
    return -1;
}

Packet *PriorityScheduler::getPacket(int index)
{
    for (auto queue : inputQueues) {
        auto numPackets = queue->getNumPackets();
        if (index < numPackets)
            return queue->getPacket(index);
        else
            index -= numPackets;
    }
    throw cRuntimeError("Invalid operation");
}

} // namespace queue
} // namespace inet
