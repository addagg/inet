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

#ifndef __INET_CLASSIFIER_H
#define __INET_CLASSIFIER_H

#include "inet/common/newqueue/ClassifierBase.h"
#include "inet/common/newqueue/IPacketClassifier.h"

namespace inet {
namespace queue {

class INET_API Classifier : public ClassifierBase
{
  protected:
    class INET_API PacketClassifier : public IPacketClassifier
    {
      protected:
        PacketClassifierFunction packetClassifierFunction;

      public:
        PacketClassifier(PacketClassifierFunction packetClassifierFunction) : packetClassifierFunction(packetClassifierFunction) { }

        virtual int classifyPacket(Packet *packet) const { return packetClassifierFunction(packet); }
        virtual PacketClassifierFunction getClassifierFunction() const { return packetClassifierFunction; }
    };

  protected:
    IPacketClassifier *packetClassifier;

  protected:
    virtual void initialize() override;
    virtual int classifyPacket(Packet *packet) const override;

  public:
    virtual ~Classifier() { delete packetClassifier; }
};

} // namespace queue
} // namespace inet

#endif // ifndef __INET_CLASSIFIERBASE_H

