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

#ifndef __INET_IPACKETSCHEDULER_H
#define __INET_IPACKETSCHEDULER_H

#include "inet/common/packet/Packet.h"

namespace inet {
namespace queue {

typedef  int (*PacketSchedulerFunction)(const std::vector<IPacketQueue *>& queues);

/**
 * This class defines the interface for packet schedulers.
 */
class INET_API IPacketScheduler
{
  public:
    virtual ~IPacketScheduler() {}

    /**
     * Returns the index of the scheduled queue.
     */
    virtual int schedulePacket(const std::vector<IPacketQueue *>& queues) const = 0;

    /**
     * Returns a pointer to the scheduler function.
     */
    virtual PacketSchedulerFunction getSchedulerFunction() const = 0;
};

} // namespace queue
} // namespace inet

#endif // ifndef __INET_IPACKETSCHEDULER_H

