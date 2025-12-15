#pragma once
#include <iomanip>
#include <string>

enum class CommandType
{
    NONE,
    POSE,
    RESET
};

struct Command
{
    CommandType type = CommandType::NONE;
    std::string poseId;
    float durationMs = 0.0f;
};