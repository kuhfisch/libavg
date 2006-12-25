#ifndef _CursorEvent_h_
#define _CursorEvent_h_

#include "Event.h"
#include "Node.h"

#include "../graphics/Point.h"

namespace avg{
class CursorEvent: public Event {
    public:
        CursorEvent(int id, Type eventType, IntPoint Position);
        virtual ~CursorEvent();
        virtual Event* cloneAs(Type EventType);
        int getXPosition() const;
        int getYPosition() const;
        int getCursorID() const;

    protected:
        IntPoint m_Position;
        int m_ID;
};
}

#endif
