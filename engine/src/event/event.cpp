#include "event.h"

void Event::operator+=(EventHandle &handle) {
    handles.push_back(&handle);
}

void Event::operator-=(EventHandle &handle) {
    for (std::vector<EventHandle *>::iterator it = handles.begin(); it != handles.end();) {
        if (*it == &handle)
            it = handles.erase(it);
        else
            ++it;
    }
}

void Event::trigger(EventData *data) {
    EventData defaultUserData;
    if (!data)
        data = &defaultUserData;
    data->sender = this;

    for (int i = 0; i < handles.size(); i++) {
        handles[i]->onHandle(data);
    }
}
