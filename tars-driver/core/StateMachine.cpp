#include "StateMachine.h"
#include <iostream>
#include <String>

const char* toString(DriverState driverState);

void StateMachine::transition(DriverState next)
{
    std::cout << "[State] " << toString(m_state) << " -> " << toString(next) << "\n";
    m_state = next;
}

DriverState StateMachine::current() const
{
    return m_state;
}

bool StateMachine::isError() const
{
    return m_state == DriverState::ERROR;
}

const char* toString(DriverState driverState)
{
    switch(driverState)
    {
        case DriverState::INITIALIZE: return "INITIALIZE";
        case DriverState::IDLE: return "IDLE";
        case DriverState::VALIDATING_COMMAND: return "VALIDATING_COMMAND";
        case DriverState::PREPARING_POSE: return "PREPARING_POSE";
        case DriverState::EXECUTING_POSE: return "EXECUTING_POSE";
        case DriverState::HOLDING_POSE: return "HOLDING_POSE";
        case DriverState::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}