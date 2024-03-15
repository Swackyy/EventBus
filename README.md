# EventBus
 A versatile and secure EventBus system for C++
Example usage can be found in "test/"

---

## How it works
### Registering and Posting
This is a Dynamic EventBus system, meaning event types (keyboard or mouse input, player moving, etc.) of event can be registered and posted with simple code:
```cpp
int main() {
    // First, create an eventbus, you can have multiple!
    EventBus bus{};

    // Next, register a type of event with a string key
    bus.createEventId("example");

    // Now, add listeners to the event
    bus.addListener("example", myFunction);

    // CompoundString is a useful class to allow you to serialize all data to a string,
    // this also makes it easy to pass event data along a network.
    CompoundString compound{};

    // Now, serialize the data of an event of your choice to the compound,
    // in this example we will use the TestEvent class:
    TestEvent() event;
    event.setDouble(47);
    event.serialize(&compound);

    // Finally, post the event, this will call every function supplied as a listener
    // to the event type that you registered
    bus.post("example", &compound);
}
```

Event types (Event IDs) and individual listeners can also be removed from a bus with `EventBus::removeEventId` and `EventBus::removeListener` respectively.

---

### Creating your own Events
Events are classes which inherit from the Event base class, this is an example:
```cpp
class TestEvent final : public Event {
    // Custom data that we want this event to carry
    double m_testDouble = 3;
public:
    // Override serialization to make sure that our custom data is serialized
    CompoundString serialize(CompoundString *compound) const override;

    // Override deserialization to make sure that our custom data can be retrieved
    TestEvent* deserialize(CompoundString &compound) override;

    // Basic setters and getters
    void setDouble(double value);

    [[nodiscard]] double getDouble() const;
};
```

the implementation of this code is shown below:
```cpp
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
    // - - - Mostly copy-pasted start - - - //
    auto* pointer = static_cast<TestEvent*>(malloc(sizeof(TestEvent)));
    if (!pointer) {
        printf("Memory allocation of TestEvent pointer failed using malloc\n");
        return nullptr;
    }

    TestEvent event{};
    TestEvent *eptr = &event;
    innerDeserialize(eptr, compound); // This is required to deserialize cancellation bool
    // - - - Mostly copy-pasted finish - - - //
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
```

- - -