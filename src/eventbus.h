#pragma once

#include <string>
#include <functional>

#include "compoundstring.h"

class EventBus {
    std::unordered_map<std::string, std::vector<void(*)(CompoundString*)>> m_event_map;

public:
    EventBus();

    bool createEventId(const std::string& eventId);

    bool addListener(const std::string& eventId, void(*listener)(CompoundString*));

    bool post(const std::string& eventId, CompoundString* compound);
};

