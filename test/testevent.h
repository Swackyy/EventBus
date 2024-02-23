#pragma once

#include "../src/Event.h"
class TestEvent final : public Event {
    // Custom data that we want this event to carry
    double m_testDouble = 3;
public:
    CompoundString serialize(CompoundString *compound) const override;

    TestEvent* deserialize(CompoundString &compound) override;

    void setDouble(double value);

    [[nodiscard]] double getDouble() const;
};
