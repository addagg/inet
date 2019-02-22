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

#ifndef __INET_SCHEDULER_H
#define __INET_SCHEDULER_H

#include "inet/common/newqueue/base/SchedulerBase.h"
#include "inet/common/newqueue/contract/IPacketScheduler.h"

namespace inet {
namespace queue {

class INET_API Scheduler : public SchedulerBase
{
  protected:
    class INET_API PacketScheduler : public IPacketScheduler
    {
      protected:
        PacketSchedulerFunction packetSchedulerFunction;

      public:
        PacketScheduler(PacketSchedulerFunction packetSchedulerFunction) : packetSchedulerFunction(packetSchedulerFunction) { }

        virtual int schedulePacket(const std::vector<IPacketSource *>& queues) const { return packetSchedulerFunction(queues); }
        virtual PacketSchedulerFunction getSchedulerFunction() const { return packetSchedulerFunction; }
    };

  protected:
    IPacketScheduler *packetScheduler;

  protected:
    virtual void initialize() override;
    virtual int schedulePacket() const override;

  public:
    virtual ~Scheduler() { delete packetScheduler; }
};

} // namespace queue
} // namespace inet

#endif // ifndef __INET_SCHEDULERBASE_H

