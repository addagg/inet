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

#ifndef __INET_PACKETDEMULTIPLEXER_H
#define __INET_PACKETDEMULTIPLEXER_H

#include "inet/common/newqueue/base/PacketConsumerBase.h"
#include "inet/common/newqueue/contract/IPacketProducer.h"
#include "inet/common/newqueue/contract/IPacketQueueElement.h"

namespace inet {
namespace queue {

class INET_API PacketDemultiplexer : public cSimpleModule, public PacketConsumerBase, public IPacketProducer, public IPacketQueueElement, public IPacketConsumer::IListener
{
  protected:
    std::vector<cGate *> inputGates;
    cGate *outputGate = nullptr;
    IPacketConsumer *consumer = nullptr;

  protected:
    virtual void initialize(int stage) override;

  public:
    virtual IPacketConsumer *getConsumer(cGate *gate) override { return consumer; }

    virtual bool supportsPopPacket(cGate *gate) override { return false; }
    virtual bool supportsPushPacket(cGate *gate) override;

    virtual bool canPushAnyPacket(cGate *gate) override { return consumer->canPushAnyPacket(outputGate); }
    virtual bool canPushPacket(Packet *packet, cGate *gate) override { return consumer->canPushPacket(packet, gate); }
    virtual void pushPacket(Packet *packet, cGate *gate) override;

    virtual void notifyCanPushPacket(cGate *gate) override;
};

} // namespace queue
} // namespace inet

#endif // ifndef __INET_PACKETDEMULTIPLEXER_H

