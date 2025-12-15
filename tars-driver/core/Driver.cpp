#include "Driver.h"

Driver::Driver(ActuatorBackend& backend, int jointCount) : m_actuatorBackend(backend), m_joints(jointCount)
{
    m_stateMachine.transition(DriverState::IDLE);
}

void Driver::submitCommand(const Command& cmd)
{
    if (cmd.type == CommandType::RESET)
    {
        m_pendingCommand = cmd;
        m_stateMachine.transition(DriverState::INITIALIZE);
        return;
    }

    if (m_stateMachine.current() != DriverState::IDLE)
    {
        return;
    }

    m_pendingCommand = cmd;
    m_stateMachine.transition(DriverState::VALIDATING_COMMAND);
}

void Driver::update(float deltaTimeMs)
{
    switch (m_stateMachine.current())
    {
        case DriverState::INITIALIZE:
            processReset();
            break;

        case DriverState::IDLE:
            processIdle();
            break;

        case DriverState::VALIDATING_COMMAND:
            processValidation();
            break;

        case DriverState::PREPARING_POSE:
            processPreparation();
            break;

        case DriverState::EXECUTING_POSE:
            processExecution(deltaTimeMs);
            break;

        case DriverState::HOLDING_POSE:
            // Do nothing (at least for now), and wait for next command
            break;

        case DriverState::ERROR:
            // Wait for reset
            break;
    }

    for (size_t i = 0; i < m_joints.size(); ++i)
    {
        m_actuatorBackend.setJoint(i, m_joints[i].position);
    }
}

void Driver::processExecution(float deltaTimeMs)
{
    m_poseTime += deltaTimeMs;
    float t = m_poseTime / m_poseDuration;

    if (t >= 1.0f)
    {
        m_stateMachine.transition(DriverState::HOLDING_POSE);
        return;
    }

    for (auto& j : m_joints)
    {
        j.position += (j.target - j.position) * t;
    }
}

void Driver::processReset()
{
    for (auto& j : m_joints)
    {
        j.position = 0.0f;
        j.target = 0.0f;
        j.velocity = 0.0f;
    }

    m_poseTime = 0.0f;
    m_poseDuration = 0.0f;

    m_stateMachine.transition(DriverState::IDLE);
}

void Driver::processValidation()
{
    if (m_pendingCommand.type == CommandType::POSE &&
        m_pendingCommand.durationMs > 0.0f)
    {
        m_stateMachine.transition(DriverState::PREPARING_POSE);
    }
    else
    {
        m_stateMachine.transition(DriverState::ERROR);
    }
}

void Driver::processPreparation()
{
    for (auto& j : m_joints)
    {
        j.target = j.position;  // placeholder
    }

    m_poseTime = 0.0f;
    m_poseDuration = m_pendingCommand.durationMs;

    m_stateMachine.transition(DriverState::EXECUTING_POSE);
}