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

#include "inet/common/packet/Packet.h"
#include "TestSink.h"

namespace inet {
namespace queue {

Define_Module(TestSink);

void TestSink::handleMessage(cMessage *msg)
{
    auto packet = check_and_cast<Packet *>(msg);
    EV << "Packet received: " << packet << "\n";
    delete packet;
}

} // namespace queue
} // namespace inet

