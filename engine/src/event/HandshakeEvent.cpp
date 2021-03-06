#include "HandshakeEvent.hpp"

namespace dt {

HandshakeEvent::HandshakeEvent() {}

const std::string HandshakeEvent::GetType() const {
    return "DT_HANDSHAKEEVENT";
}

Event* HandshakeEvent::Clone() const {
    return new HandshakeEvent();
}

void HandshakeEvent::Serialize(IOPacket& p) {
    // do nothing, we have no data
}

}
