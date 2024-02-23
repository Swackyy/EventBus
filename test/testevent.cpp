#include "testevent.h"

// Annotated example code usage of the library to create

// Serializing additional data to compound
CompoundString TestEvent::serialize(CompoundString* compound) const {
    // Always do this so the "cancellable" boolean is serialized
    Event::serialize(compound);

    // Put data onto tag
    compound->put("testDouble", m_testDouble);
    return *compound;
}

TestEvent* TestEvent::deserialize(CompoundString& compound) {
    auto* pointer = static_cast<TestEvent*>(malloc(sizeof(TestEvent)));
    if (!pointer) {
        printf("Memory allocation of TestEvent pointer failed using malloc\n");
        return nullptr;
    }

    TestEvent event{};
    TestEvent *eptr = &event;
    innerDeserialize(eptr, compound); // This is required to deserialize cancellation
    // Setting data in class to data stored in the tag
    eptr->setDouble(compound.getDouble("testDouble"));
    *pointer = event;
    return pointer;
}

// Basic setters and getters
void TestEvent::setDouble(const double value) {
    m_testDouble = value;
}

double TestEvent::getDouble() const {
    return m_testDouble;
}
