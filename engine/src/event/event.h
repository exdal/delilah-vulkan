#pragma once
#include <vector>

struct EventData {
    void *sender = nullptr;
    void *data = nullptr;
};

struct EventHandle {
    virtual void onHandle(const EventData *eventdata) = 0;
};

struct Event {
    void operator+=(EventHandle &handle);
    void operator-=(EventHandle &handle);

    void trigger(EventData *data = nullptr);

    std::vector<EventHandle *> handles;
};