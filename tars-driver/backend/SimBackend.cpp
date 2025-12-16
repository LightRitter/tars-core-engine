#include "SimBackend.h"
#include <iostream>

SimBackend::SimBackend(int jointCount) : m_joints(jointCount, 0.0f) {}

void SimBackend::setJoint(int id, float value)
{
    m_joints[id] = value;
}

void SimBackend::dump() const
{
    for (size_t i = 0; i < m_joints.size(); ++i)
    {
         std::cout << "J" << i << ":" << m_joints[i] << " ";
    }
    std::cout << "\n";
}
