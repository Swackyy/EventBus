#pragma once

#include "compoundstring.h"

class Event {
    bool m_cancelled = false;
protected:
    ~Event() = default;

    static void innerDeserialize(Event* event, const CompoundString& compound);
public:
    Event() = default;

    virtual CompoundString serialize(CompoundString* compound) const;

    virtual Event* deserialize(CompoundString& compound);

    void setCancelled(bool cancelled);

    [[nodiscard]] bool getCancelled() const;
};
