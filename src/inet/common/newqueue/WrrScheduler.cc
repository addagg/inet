//
// Copyright (C) 2012 Andras Varga
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

#include "inet/common/INETUtils.h"
#include "inet/common/newqueue/WrrScheduler.h"

namespace inet {
namespace queue {

Define_Module(WrrScheduler);

WrrScheduler::~WrrScheduler()
{
    delete[] weights;
    delete[] buckets;
}

void WrrScheduler::initialize()
{
    SchedulerBase::initialize();

    weights = new int[inputQueues.size()];
    buckets = new int[inputQueues.size()];

    cStringTokenizer tokenizer(par("weights"));
    int i;
    for (i = 0; i < (int)inputQueues.size() && tokenizer.hasMoreTokens(); ++i)
        buckets[i] = weights[i] = (int)utils::atoul(tokenizer.nextToken());

    if (i < (int)inputQueues.size())
        throw cRuntimeError("Too few values given in the weights parameter.");
    if (tokenizer.hasMoreTokens())
        throw cRuntimeError("Too many values given in the weights parameter.");
}

int WrrScheduler::schedulePacket() const
{
    bool allQueueIsEmpty = true;
    for (int i = 0; i < (int)inputQueues.size(); ++i) {
        if (!inputQueues[i]->isEmpty()) {
            allQueueIsEmpty = false;
            if (buckets[i] > 0) {
                buckets[i]--;
                return i;
            }
        }
    }

    if (allQueueIsEmpty)
        return -1;

    int result = -1;
    for (int i = 0; i < (int)inputQueues.size(); ++i) {
        buckets[i] = weights[i];
        if (result == -1 && buckets[i] > 0 && !inputQueues[i]->isEmpty()) {
            buckets[i]--;
            result = i;
        }
    }
    return result;
}

Packet *WrrScheduler::getPacket(int index)
{
    throw cRuntimeError("Invalid operation");
}

} // namespace queue
} // namespace inet

