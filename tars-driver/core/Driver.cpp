#include "Driver.h"

Driver::Driver(ActuatorBackend& backend, int jointCount) : m_actuatorBackend(backend), m_joints(jointCount)
{
    m_stateMachine.transition(DriverState::IDLE);
}

void Driver::submitCommand(const Command& cmd)
{
    if (cmd.type == CommandType::POSE &&
        m_stateMachine.current() == DriverState::IDLE)
    {
        for (size_t i = 0; i < m_joints.size(); ++i)
        {
            m_joints[i].target = m_joints[i].position; // placeholder
        }

        m_poseTime = 0.0f;
        m_poseDuration = cmd.durationMs;
        m_stateMachine.transition(DriverState::EXECUTING_POSE);
    }
}

void Driver::update(float deltaTimeMs)
{
    if (m_stateMachine.current() == DriverState::EXECUTING_POSE)
    {
        updatePose(deltaTimeMs);
    }

    for (size_t i = 0; i < m_joints.size(); ++i)
    {
        m_actuatorBackend.setJoint(i, m_joints[i].position);
    }
}

void Driver::updatePose(float deltaTimeMs)
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
