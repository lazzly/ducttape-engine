#ifndef DUCTTAPE_ENGINE_EVENT_GOODBYEEVENT
#define DUCTTAPE_ENGINE_EVENT_GOODBYEEVENT

#include "NetworkEvent.hpp"

namespace dt {

/**
  * An Event announcing the end of a Connection. Sent by the NetworkManager on disconnect.
  */
class GoodbyeEvent : public NetworkEvent {
public:
    /**
      * Advanced constructor.
      * @param reason The reason for the disconnect.
      */
    GoodbyeEvent(const std::string& reason = "");

    const std::string GetType() const;
    Event* Clone() const;
    void Serialize(IOPacket& p);

    /**
      * Returns the reason for the disconnect.
      * @returns The reason for the disconnect.
      */
    const std::string& GetReason() const;

    /**
      * Sets the reason for the disconnect.
      * @param reason The reason for the disconnect.
      */
    void SetReason(const std::string& reason);
private:
    std::string mReason;
};

}

#endif
