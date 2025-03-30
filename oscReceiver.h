//
// Created by David Richter on 3/30/25.
//

#include "oscpack/osc/OscReceivedElements.h"
#include "oscpack/osc/OscPacketListener.h"
#include "oscpack/ip/UdpSocket.h"

class MaxReceiver : public osc::OscPacketListener {
public:
    MaxReceiver();
    ~MaxReceiver();

protected:
    virtual void ProcessMessage(
        const osc::ReceivedMessage& message,
        const IpEndpointName& remoteEndpoint
    );
};
