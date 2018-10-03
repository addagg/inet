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

#ifndef __INET_IPACKETCLASSIFIER_H
#define __INET_IPACKETCLASSIFIER_H

#include "inet/common/packet/Packet.h"

namespace inet {
namespace queue {

typedef int (*PacketClassifierFunction)(Packet *packet);

/**
 * This class defines the interface for packet classifiers.
 */
class INET_API IPacketClassifier
{
  public:
    virtual ~IPacketClassifier() {}

    /**
     * Returns the class index of the given packet.
     */
    virtual int classifyPacket(Packet *packet) const = 0;

    /**
     * Returns a pointer to the classifier function.
     */
    virtual PacketClassifierFunction getClassifierFunction() const = 0;
};

} // namespace queue
} // namespace inet

#endif // ifndef __INET_IPACKETCLASSIFIER_H

