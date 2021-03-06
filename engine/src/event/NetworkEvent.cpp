#include "NetworkEvent.hpp"

#include "Root.hpp"

namespace dt {

NetworkEvent::NetworkEvent() {
    mIsLocalEvent = false;
    mSenderID = 0;

    ConnectionsManager* cm = Root::get_mutable_instance().GetNetworkManager()->GetConnectionsManager();
    for(Connection* c: cm->GetAllConnections()) {
        AddRecipient(cm->GetConnectionID(*c));
    }
}

bool NetworkEvent::IsNetworkEvent() const {
    return true;
}

void NetworkEvent::AddRecipient(uint16_t id) {
    mRecipients.push_back(id);
}

void NetworkEvent::RemoveRecipient(uint16_t id) {
    for(auto iter = mRecipients.begin(); iter != mRecipients.end(); ++iter) {
        if(*iter == id) {
            iter = mRecipients.erase(iter);
        }
    }
}

void NetworkEvent::ClearRecipients() {
    mRecipients.clear();
}

const std::vector<uint16_t>& NetworkEvent::GetRecipients() const {
    return mRecipients;
}

bool NetworkEvent::HasRecipient(uint16_t id) {
    for(uint16_t i: mRecipients)
        if(i == id)
            return true;
    return false;
}

bool NetworkEvent::IsLocalEvent() const {
    return mIsLocalEvent;
}

void NetworkEvent::IsLocalEvent(bool is_local_event) {
    mIsLocalEvent = is_local_event;
}

uint16_t NetworkEvent::GetSenderID() const {
    return mSenderID;
}

void NetworkEvent::SetSenderID(uint16_t id) {
    mSenderID = id;
}

}
