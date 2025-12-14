#pragma once
#include "StateMachine.h"
#include "Motion.h"
#include "Command.h"
#include "../backend/ActuatorBackend.h"
#include <vector>

class Driver
{
    public:
        Driver(ActuatorBackend& backend, int jointCount);

        void update(float deltaTimeMs);
        void submitCommand(const Command& cmd);

    private:
        void updatePose(float deltaTimeMs);

        StateMachine m_stateMachine;
        ActuatorBackend& m_actuatorBackend;
        std::vector<Joint> m_joints;

        float m_poseTime = 0.0f;
        float m_poseDuration = 0.0f;
};
