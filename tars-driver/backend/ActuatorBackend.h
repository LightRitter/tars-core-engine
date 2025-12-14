#pragma once

class ActuatorBackend
{
    public:
        virtual ~ActuatorBackend() = default;
        virtual void setJoint(int id, float value) = 0;
};
