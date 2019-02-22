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

#ifndef __INET_IPACKETSOURCE_H
#define __INET_IPACKETSOURCE_H

#include "inet/common/packet/Packet.h"

namespace inet {
namespace queue {

/**
 * This class defines the interface for packet sources.
 */
class INET_API IPacketSource
{
  public:
    virtual ~IPacketSource() {}

    /**
     * Returns the number of available packets in the source.
     */
    virtual int getNumPackets() = 0;

    /**
     * Returns the packet at the given index.
     */
    virtual Packet *getPacket(int index) = 0;

    /**
     * Returns true if there are no packets available in the source.
     */
    virtual bool isEmpty() = 0;

    /**
     * Pops a packet from the source. The source must not be empty.
     */
    virtual Packet *popPacket() = 0;

    /**
     * Removes a packet from the source. The source must contain the packet.
     */
    virtual void removePacket(Packet *packet) = 0;

    /**
     * Requests the source to send out a packet. If a packet is readily available,
     * then it is sent out immediately. Otherwise, as soon as a packet becomes
     * available, it is sent out.
     */
    virtual void requestPacket() = 0;
};

} // namespace queue
} // namespace inet

#endif // ifndef __INET_IPACKETSOURCE_H

