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

#include "inet/common/newqueue/base/PacketSchedulerBase.h"
#include "inet/common/newqueue/QueueUtils.h"
#include "inet/common/Simsignals.h"

namespace inet {
namespace queue {

void PacketSchedulerBase::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        outputGate = gate("out");
        for (int i = 0; i < gateSize("in"); i++) {
            auto inputGate = gate("in", i);
            inputGates.push_back(inputGate);
            auto inputProvider = dynamic_cast<IPacketProvider *>(inputGate->getPathStartGate()->getOwnerModule());
            inputProviders.push_back(inputProvider);
            if (inputProvider != nullptr)
                inputProvider->addListener(this);
        }
    }
    else if (stage == INITSTAGE_LAST) {
        for (auto inputGate : inputGates)
            checkPopPacketSupport(inputGate);
        checkPopPacketSupport(outputGate);
    }
}

void PacketSchedulerBase::finish()
{
    for (auto inputProvider : inputProviders)
        if (inputProvider != nullptr)
            inputProvider->removeListener(this);
}

bool PacketSchedulerBase::canPopSomePacket(cGate *gate)
{
    for (int i = 0; i < gateSize("in"); i++) {
        auto inputProvider = inputProviders[i];
        if (inputProvider->canPopSomePacket(inputGates[i]->getPathStartGate()))
            return true;
    }
    return false;
}

Packet *PacketSchedulerBase::popPacket(cGate *gate)
{
    int i = schedulePacket();
    if (i == -1)
        return nullptr;
    else {
        auto packet = inputProviders[i]->popPacket(inputGates[i]->getPathStartGate());
        EV_INFO << "Scheduling packet " << packet->getName() << ".\n";
        animateSend(packet, outputGate);
        return packet;
    }
}

void PacketSchedulerBase::notifyCanPopPacket(cGate *gate)
{
    for (auto listener : listeners)
        listener->notifyCanPopPacket(outputGate);
}

} // namespace queue
} // namespace inet

