#include <iostream>

#include "TestEvent.h"
#include "../include/eventbus.h"

// Annotated example code usage of the library

// First listener
void testFunction1(CompoundString* compound) {
    // Creating event instance from argument
    TestEvent* event = TestEvent().deserialize(*compound);

    // Modifying data within the event so that after posting they will be modified
    event->setDouble(97);
    event->setCancelled(true);
    std::cout << "Listener 1 passed" << std::endl;

    // Reserialize to compound so the modified data will be passed on
    event->serialize(compound);
}

// Second listener
void testFunction2(CompoundString* compound) {
    // Creating event instance from argument
    TestEvent* event = TestEvent().deserialize(*compound);

    // Modifying data within the event so that after posting they will be modified
    event->setDouble(2897);
    std::cout << "Listener 2 passed" << std::endl;

    // Reserialize to compound so the modified data will be passed on
    event->serialize(compound);
}

int main() {
    // Different eventbuses can run different events with different IDs
    EventBus bus{};

    // Different eventIds can be used to create groups where only certain listeners are fired
    bus.createEventId("testEvent");

    // Adding both functions as listeners to the event
    bus.addListener("testEvent", testFunction1);
    bus.addListener("testEvent", testFunction2);


    CompoundString compound{};
    TestEvent().serialize(&compound);
    // Posting event with the ID created
    bus.post("testEvent", &compound);

    // Seeing if things worked
    std::cout << compound.getDouble("testDouble") << std::endl;
    std::cout << compound.getBool("cancelled") << std::endl;
}
