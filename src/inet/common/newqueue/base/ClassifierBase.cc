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

#include "inet/common/newqueue/base/ClassifierBase.h"
#include "inet/common/newqueue/QueueUtils.h"

namespace inet {
namespace queue {

void ClassifierBase::initialize()
{
    for (int i = 0; i < gateSize("out"); i++) {
        auto outputGate = gate("out", i);
        auto outputQueue = check_and_cast<IPacketSink *>(outputGate->getPathEndGate()->getOwnerModule());
        outputGates.push_back(outputGate);
        outputQueues.push_back(outputQueue);
    }
}

void ClassifierBase::pushPacket(Packet *packet)
{
    int index = classifyPacket(packet);
    animateSend(packet, outputGates[index]);
    outputQueues[index]->pushPacket(packet);
}

} // namespace queue
} // namespace inet
