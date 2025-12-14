#pragma once

enum class DriverState
{
    INITIALIZE,
    IDLE,
    EXECUTING_POSE,
    HOLDING_POSE,
    ERROR
};

class StateMachine
{
    public:
        void transition(DriverState next);
        DriverState current() const;

    private:
        DriverState m_state = DriverState::INITIALIZE;
};
