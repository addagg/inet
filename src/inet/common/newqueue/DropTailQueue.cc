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

#include "inet/common/newqueue/DropTailQueue.h"
#include "inet/common/Simsignals.h"

namespace inet {
namespace queue {

Define_Module(DropTailQueue);

void DropTailQueue::initialize()
{
    InfiniteQueue::initialize();
    frameCapacity = par("frameCapacity");
    byteCapacity = par("byteCapacity");
}

void DropTailQueue::pushPacket(Packet *packet)
{
    if ((frameCapacity != -1 && queue.getLength() + 1 > frameCapacity) ||
        (byteCapacity != -1 && queue.getByteLength() + packet->getByteLength() > byteCapacity))
    {
        EV_INFO << "Dropping packet " << packet->getName() << " because the queue is full." << endl;
        PacketDropDetails details;
        details.setReason(QUEUE_OVERFLOW);
        details.setLimit(frameCapacity);
        emit(packetDroppedSignal, packet, &details);
        delete packet;
    }
    else
        InfiniteQueue::pushPacket(packet);
}

} // namespace queue
} // namespace inet
