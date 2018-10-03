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

#include "inet/common/FunctionRegistry.h"
#include "inet/common/newqueue/Scheduler.h"

namespace inet {
namespace queue {

void Scheduler::initialize()
{
    const char *schedulerClass = par("schedulerClass");
    const char *schedulerFunction = par("schedulerFunction");
    if (*schedulerClass != '\0')
        packetScheduler = check_and_cast<IPacketScheduler *>(createOne(schedulerClass));
    else if (*schedulerFunction != '\0') {
        auto function = FunctionRegistry::globalRegistry.getFunction(schedulerFunction);
        packetScheduler = new PacketScheduler((PacketSchedulerFunction)function);
    }
}

int Scheduler::schedulePacket() const
{
    return packetScheduler->schedulePacket(inputQueues);
}

} // namespace queue
} // namespace inet
