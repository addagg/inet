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

#ifndef __INET_PACKETDUPLICATORBASE_H
#define __INET_PACKETDUPLICATORBASE_H

#include <algorithm>
#include "inet/common/newqueue/contract/IPacketDuplicator.h"
#include "inet/common/newqueue/contract/IPacketQueueElement.h"

namespace inet {
namespace queue {

class INET_API PacketDuplicatorBase : public cSimpleModule, public IPacketDuplicator, public IPacketQueueElement, public IPacketConsumer::IListener
{
  protected:
    cGate *inputGate = nullptr;
    cGate *outputGate = nullptr;
    IPacketConsumer *consumer = nullptr;

    std::vector<IPacketConsumer::IListener *> consumerListeners;

  protected:
    virtual void initialize(int stage) override;
    virtual int getNumPacketDuplicates(Packet *packet) = 0;

  public:
    virtual IPacketConsumer *getConsumer(cGate *gate) override { return this; }

    virtual bool supportsPushPacket(cGate *gate) override { return true; }
    virtual bool supportsPopPacket(cGate *gate) override { return true; }
    virtual int getNumPushablePackets(cGate *gate) override { return -1; }
    virtual bool canPushAnyPacket(cGate *gate) override { return true; }
    virtual bool canPushPacket(Packet *packet, cGate *gate) override { return true; }
    virtual void pushPacket(Packet *packet, cGate *gate) override;

    virtual void addListener(IPacketConsumer::IListener *listener) override { consumerListeners.push_back(listener); }
    virtual void removeListener(IPacketConsumer::IListener *listener) override { consumerListeners.erase(find(consumerListeners.begin(), consumerListeners.end(), listener)); }

    virtual void notifyCanPushPacket(cGate *gate) override;
};

} // namespace queue
} // namespace inet

#endif // ifndef __INET_PACKETDUPLICATORBASE_H

