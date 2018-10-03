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

#ifndef __INET_INFINITEQUEUE_H
#define __INET_INFINITEQUEUE_H

#include "inet/common/newqueue/IPacketComparator.h"
#include "inet/common/newqueue/PacketQueueBase.h"

namespace inet {
namespace queue {

class INET_API InfiniteQueue : public PacketQueueBase
{
  protected:
    class INET_API PacketComparator : public IPacketComparator
    {
    protected:
      PacketComparatorFunction packetComparatorFunction;

    public:
      PacketComparator(PacketComparatorFunction packetComparatorFunction) : packetComparatorFunction(packetComparatorFunction) { }

      virtual int comparePackets(Packet *packet1, Packet *packet2) const { return packetComparatorFunction(packet1, packet2); }
      virtual PacketComparatorFunction getComparatorFunction() const { return packetComparatorFunction; }
    };

  protected:
    const char *displayStringTextFormat = nullptr;
    cPacketQueue queue;
    IPacketComparator *comparator = nullptr;

  protected:
    virtual void initialize() override;
    virtual void updateDisplayString();
    virtual b getTotalLength();

  public:
    virtual ~InfiniteQueue() { delete comparator; }
    virtual int getNumPackets() override;
    virtual Packet *getPacket(int index) override;
    virtual void pushPacket(Packet *packet) override;
    virtual Packet *popPacket() override;
    virtual void removePacket(Packet *packet) override;
};

} // namespace queue
} // namespace inet

#endif // ifndef __INET_INFINITEQUEUE_H

