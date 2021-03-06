#include "BindingsManager.hpp"

namespace dt {

BindingsManager::BindingsManager() {}

BindingsManager::~BindingsManager() {}

void BindingsManager::Initialize() {}

void BindingsManager::Deinitialize() {}

void BindingsManager::HandleEvent(Event* e) {
    for(auto iter = mBindings.begin(); iter != mBindings.end(); ++iter) {
        iter->second->TriggerEvent(e);
    }
}

uint32_t BindingsManager::Bind(EventBinding* binding) {
    uint32_t new_id = _GetNewId();
    mBindings[new_id] = *binding;
    return new_id;
}

void BindingsManager::Unbind(uint32_t binding_id) {
    if(mBindings.count(binding_id) != 0)
        mBindings.erase(binding_id);
}

uint32_t BindingsManager::_GetNewId() {
    uint32_t i = 0;
    while(mBindings.count(i) != 0)
        ++i;
    return i;
}

}
