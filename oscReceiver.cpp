//
// Created by David Richter on 3/30/25.
//

#include "oscReceiver.h"

#include <iostream>

MaxReceiver::MaxReceiver() = default;

MaxReceiver::~MaxReceiver() = default;

void MaxReceiver::ProcessMessage(
    const osc::ReceivedMessage& message,
    const IpEndpointName& remoteEndpoint
) {
    (void) remoteEndpoint; // suppress unused parameter warning

    auto messageTag = message.AddressPattern();

    if (std::strcmp(message.AddressPattern(), "/midi_note") == 0) {
        osc::ReceivedMessage::const_iterator args = message.ArgumentsBegin();
        auto midiNote = (args++)->AsInt32();
        std::cout << messageTag << std::endl;
        std::cout << midiNote << std::endl;
    }
}

