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

#include "inet/common/newqueue/SchedulerBase.h"

namespace inet {
namespace queue {

void SchedulerBase::initialize()
{
    PacketQueueBase::initialize();
    for (int i = 0; i < gateSize("in"); i++) {
        auto inputGate = gate("in", i);
        auto inputQueue = check_and_cast<IPacketQueue *>(inputGate->getPathStartGate()->getOwnerModule());
        inputGates.push_back(inputGate);
        inputQueues.push_back(inputQueue);
    }
    subscribe();
}

void SchedulerBase::finish()
{
    unsubscribe();
}

void SchedulerBase::subscribe()
{
    for (auto inputQueue : inputQueues) {
        auto inputQueueModule = check_and_cast<cModule *>(inputQueue);
        inputQueueModule->subscribe(IPacketQueue::packetEnqueuedSignal, this);
    }
}

void SchedulerBase::unsubscribe()
{
    for (auto inputQueue : inputQueues) {
        auto inputQueueModule = check_and_cast<cModule *>(inputQueue);
        inputQueueModule->unsubscribe(IPacketQueue::packetEnqueuedSignal, this);
    }
}

int SchedulerBase::getNumPackets()
{
    int size = 0;
    for (auto queue : inputQueues)
        size += queue->getNumPackets();
    return size;
}

Packet *SchedulerBase::popPacket()
{
    int i = schedulePacket();
    if (i == -1)
        return nullptr;
    else {
        auto packet = inputQueues[i]->popPacket();
        animateSend(packet, inputGates[i]->getPathStartGate());
        return packet;
    }
}

void SchedulerBase::removePacket(Packet *packet)
{
    for (auto queue : inputQueues) {
        for (int j = 0; j < queue->getNumPackets(); j++) {
            if (queue->getPacket(j) == packet) {
                queue->removePacket(packet);
                return;
            }
        }
    }
    throw cRuntimeError("Invalid operation");
}

void SchedulerBase::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details)
{
    if (signalID == IPacketQueue::packetEnqueuedSignal) {
        if (hasPendingRequestPacket)
            handlePendingRequestPacket();
    }
    else
        throw cRuntimeError("Unknown signal");
}

} // namespace queue
} // namespace inet
