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

#ifndef __INET_IPACKETSINK_H
#define __INET_IPACKETSINK_H

#include "inet/common/packet/Packet.h"

namespace inet {
namespace queue {

/**
 * This class defines the interface for packet sinks.
 */
class INET_API IPacketSink
{
  public:
    virtual ~IPacketSink() {}

    /**
     * Pushes a packet into the sink. The packet must not be nullptr.
     */
    virtual void pushPacket(Packet *packet) = 0;
};

} // namespace queue
} // namespace inet

#endif // ifndef __INET_IPACKETSINK_H

