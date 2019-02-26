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
#include "inet/common/newqueue/PacketFilter.h"

namespace inet {
namespace queue {

Define_Module(PacketFilter);

void PacketFilter::initialize(int stage)
{
    PacketFilterBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        const char *filterClass = par("filterClass");
        const char *filterFunction = par("filterFunction");
        if (*filterClass != '\0')
            packetFilterFunction = check_and_cast<IPacketFilterFunction *>(createOne(filterClass));
        else if (*filterFunction != '\0') {
            auto function = FunctionRegistry::globalRegistry.getFunction(filterFunction);
            packetFilterFunction = new CPacketFilterFunction((PacketFilterFunction)function);
        }
        else
            throw cRuntimeError("One of filterClass or filterFunction parameters must be provided");
    }
}

bool PacketFilter::filterPacket(Packet *packet)
{
    return packetFilterFunction->filterPacket(packet);
}

} // namespace queue
} // namespace inet

