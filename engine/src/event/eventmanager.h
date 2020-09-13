#pragma once
#include "event.h"

struct Events {
    Event onEngineInit;
    Event onEngineDeinit;
    Event onBeginRender;
    Event onEndRender;
    Event onUpdate;

    Event onLoseFocus;
    Event onGainFocus;

    Event onMousePressed;
    Event onMouseMoved;
    Event onMouseReleased;
    Event onMouseScrolled;
    Event onKeyPressed;
    Event onKeyReleased;
};

struct EventManager {
    static Events callBack;
};

namespace event {
    void EventInit();
    void EventDeinit();
}