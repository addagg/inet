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
#include "inet/common/newqueue/PacketClassifier.h"

namespace inet {
namespace queue {

Define_Module(PacketClassifier);

void PacketClassifier::initialize(int stage)
{
    PacketClassifierBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        const char *classifierClass = par("classifierClass");
        const char *classifierFunction = par("classifierFunction");
        if (*classifierClass != '\0')
            packetClassifierFunction = check_and_cast<IPacketClassifierFunction *>(createOne(classifierClass));
        else if (*classifierFunction != '\0') {
            auto function = FunctionRegistry::globalRegistry.getFunction(classifierFunction);
            packetClassifierFunction = new CPacketClassifierFunction((PacketClassifierFunction)function);
        }
        else
            throw cRuntimeError("One of classifierClass or classifierFunction parameters must be provided");
    }
}

int PacketClassifier::classifyPacket(Packet *packet) const
{
    return packetClassifierFunction->classifyPacket(packet);
}

} // namespace queue
} // namespace inet

