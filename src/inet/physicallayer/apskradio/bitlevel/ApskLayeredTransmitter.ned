//
// Copyright (C) 2014 OpenSim Ltd
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

package inet.physicallayer.apskradio.bitlevel;

import inet.physicallayer.contract.packetlevel.ITransmitter;
import inet.physicallayer.contract.bitlevel.IDigitalAnalogConverter;
import inet.physicallayer.contract.bitlevel.IEncoder;
import inet.physicallayer.contract.bitlevel.IModulator;
import inet.physicallayer.contract.bitlevel.IPulseShaper;

//
// This transmitter model is part of a simple hypothetical layered radio. It
// produces detailed transmissions that have separate representation for
// all simulated domains. The levelOfDetail parameter controls which domains
// are actually simulated, but all parameters relevant to the error model are
// always set on the transmission.
//
// With the highest level of detail, the produced transmission contains the
// following:
//  - a separate packet to represent the PHY frame
//  - precise bit representation of the whole packet
//  - precise bit representation after scrambling, fec encoding, and interleaving
//  - precise symbol representation of the whole packet including physical header
//  - narrowband analog representation using scalar transmission power
//
// NOTE: the current implementation doesn't support pulse shaping and digital
// analog conversion.
//
// This transmitter model supports scrambling, convolutional coding, interleaving,
// and modulating various amplitude and phase-shift modulations. The main purpose
// of this model is to provide a basic infrastructure for further development and
// experimentation.
//
// See also ~ApskEncoder, ~ApskModulator, and ~ApskLayeredReceiver.
//
module ApskLayeredTransmitter like ITransmitter
{
    parameters:
        string levelOfDetail @enum("packet", "bit", "symbol", "sample") = default("symbol");
        double bitrate @unit(bps); // net bitrate of the transmitter
        double power @unit(W); // scalar transmission power for the whole signal duration
        double carrierFrequency @unit(Hz); // center frequency of the narrowband carrier signal
        double bandwidth @unit(Hz); // bandwidth
        @display("i=block/wtx");
        @class(ApskLayeredTransmitter);

    submodules:
        encoder: <default("ApskEncoder")> like IEncoder if typename != "" {
            @display("p=100,100");
        }
        modulator: <default("ApskModulator")> like IModulator {
            @display("p=100,200");
        }
        pulseShaper: <default("")> like IPulseShaper if typename != "" {
            @display("p=100,300");
        }
        digitalAnalogConverter: <default("")> like IDigitalAnalogConverter if typename != "" {
            @display("p=100,400");
        }
}

