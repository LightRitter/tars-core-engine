#include "../core/Driver.h"
#include "../backend/SimBackend.h"
#include <thread>
#include <chrono>

int main()
{
    SimBackend backend(4);
    Driver driver(backend, 4);

    Command cmd;
    cmd.type = CommandType::POSE;
    cmd.poseId = "TEST";
    cmd.durationMs = 1000;

    driver.submitCommand(cmd);

    for (int i = 0; i < 100; ++i)
    {
        driver.update(10.0f);
        backend.dump();
         std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}
