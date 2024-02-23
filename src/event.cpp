#include "Event.h"
#include <iostream>

void Event::innerDeserialize(Event* event, const CompoundString& compound) {
    event->setCancelled(compound.getBool("cancelled"));
}

CompoundString Event::serialize(CompoundString *compound) const {
    compound->put("cancelled", m_cancelled);
    return *compound;
}

Event* Event::deserialize(CompoundString &compound) {
    auto* pointer = static_cast<Event*>(malloc(sizeof(Event)));
    if (!pointer) {
        printf("Memory allocation of Event pointer failed using malloc\n");
        return nullptr;
    }

    Event event{};
    Event *eptr = &event;
    innerDeserialize(eptr, compound);
    *pointer = event;
    return pointer;
}

void Event::setCancelled(const bool cancelled) {
    m_cancelled = cancelled;
}

bool Event::getCancelled() const {
    return m_cancelled;
}
