#include "eventbus.h"

#include <iostream>

EventBus::EventBus() : m_event_map({}) {}

bool EventBus::createEventId(const std::string &eventId) {
    if(m_event_map.find(eventId) != m_event_map.end()) {
        std::cerr << "Could not create event Id \"" + eventId + "\" as the event Id has already been registered" << std::endl;
        return false;
    }

    m_event_map.try_emplace(eventId, std::vector<void(*)(CompoundString*)>{});
    return true;
}

bool EventBus::addListener(const std::string& eventId, void(*listener)(CompoundString*)) {
    if(m_event_map.find(eventId) == m_event_map.end()) {
        std::cerr << "Could not add listener to event with Id \"" + eventId + "\" as the event could not be found" << std::endl;
        return false;
    }

    if(std::all_of(m_event_map.at(eventId).begin(), m_event_map.at(eventId).end(), [listener](auto f){ return listener != f; })) {
        m_event_map.at(eventId).push_back(listener);
        return true;
    }

    return false;
}

bool EventBus::post(const std::string &eventId, CompoundString* compound) {
    if(m_event_map.find(eventId) == m_event_map.end()) {
        std::cerr << "Could not post event with Id \"" + eventId + "\" as the event could not be found" << std::endl;
        return false;
    }

    for(const auto f : m_event_map.at(eventId)) {
        f(compound);
    }
    return true;
}
