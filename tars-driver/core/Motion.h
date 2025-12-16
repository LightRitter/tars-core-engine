#pragma once
#include <vector>

struct Joint
{
    float position = 0.0f;
    float target = 0.0f;
    float velocity = 0.0f;
    float start = 0.0f;  // initial position before any motion
    float maxLimit = 0.0f;
    float minLimit = 0.0f;
};

struct Pose
{
    std::vector<float> jointTargets;
};
