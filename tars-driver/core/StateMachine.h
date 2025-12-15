#pragma once

enum class DriverState
{
    INITIALIZE,
    IDLE,
    VALIDATING_COMMAND,
    PREPARING_POSE,
    EXECUTING_POSE,
    HOLDING_POSE,
    ERROR
};

class StateMachine
{
    public:
        void transition(DriverState next);
        DriverState current() const;
        bool isError() const;

    private:
        DriverState m_state = DriverState::INITIALIZE;
};
