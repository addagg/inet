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

#ifndef __INET_PACKETPROVIDER_H
#define __INET_PACKETPROVIDER_H

#include "inet/common/newqueue/base/PacketProviderBase.h"
#include "inet/common/newqueue/contract/IPacketQueueElement.h"

namespace inet {
namespace queue {

class INET_API PacketProvider : public cSimpleModule, public PacketProviderBase, public IPacketQueueElement
{
  protected:
    cGate *outputGate = nullptr;
    const char *packetNameFormat = nullptr;
    int numPacket = 0;
    b totalLength = b(0);
    Packet *nextPacket = nullptr;

  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *message) override;

    virtual Packet *createPacket();

  public:
    virtual ~PacketProvider() { delete nextPacket; }

    virtual bool supportsPushPacket(cGate* gate) override { return false; }
    virtual bool supportsPopPacket(cGate* gate) override { return outputGate == gate; }

    virtual Packet *canPopPacket(cGate *gate) override;
    virtual Packet *popPacket(cGate *gate) override;
};

} // namespace queue
} // namespace inet

#endif // ifndef __INET_PACKETPROVIDER_H

