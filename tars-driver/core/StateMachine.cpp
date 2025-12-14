#include "StateMachine.h"

void StateMachine::transition(DriverState next)
{
    m_state = next;
}

DriverState StateMachine::current() const
{
    return m_state;
}
