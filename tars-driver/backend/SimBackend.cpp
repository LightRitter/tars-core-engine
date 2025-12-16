#include "SimBackend.h"
#include <iostream>

SimBackend::SimBackend(int jointCount) : m_joints(jointCount, 0.0f) {}

void SimBackend::setJoint(int id, float value)
{
    if (id < 0 || static_cast<size_t>(id) >= m_joints.size())
    {
        return;
    }
    
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
