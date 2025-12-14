#pragma once
#include "ActuatorBackend.h"
#include <vector>

class SimBackend : public ActuatorBackend
{
    public:
        explicit SimBackend(int jointCount);
        void setJoint(int id, float value) override;
        void dump() const;

    private:
        std::vector<float> m_joints;
};
