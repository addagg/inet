//
// Copyright (C) 2012 Opensim Ltd.
// Author: Tamas Borbely
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
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef __INET_WRRSCHEDULER_H
#define __INET_WRRSCHEDULER_H

#include "inet/common/newqueue/base/SchedulerBase.h"

namespace inet {
namespace queue {

/**
 * This module implements a Weighted Round Robin Scheduler.
 */
class INET_API WrrScheduler : public SchedulerBase
{
  protected:
    int *weights = nullptr; // array of weights (has numInputs elements)
    int *buckets = nullptr; // array of tokens in buckets (has numInputs elements)

  protected:
    virtual void initialize() override;
    virtual int schedulePacket() const override;

  public:
    virtual ~WrrScheduler();

    virtual Packet *getPacket(int index) override;
};

} // namespace queue
} // namespace inet

#endif // ifndef __INET_WRRSCHEDULER_H

