#include "../core/Driver.h"
#include "../backend/SimBackend.h"
#include <thread>
#include <chrono>

int main()
{
    constexpr int jointCount = 2;  // For a 2 arm TARS

    SimBackend backend(jointCount);
    Driver driver(backend, jointCount);

    Command cmd;
    cmd.type = CommandType::POSE;
    cmd.durationMs = 1000.0f;

    driver.submitCommand(cmd);

    for (int i = 0; i < 70; ++i)
    {
        driver.update(16.0f);
        backend.dump();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}