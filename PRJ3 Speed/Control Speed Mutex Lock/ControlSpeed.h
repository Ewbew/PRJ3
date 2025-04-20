#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>

class SpeedController {
public:
    SpeedController(double initialSpeed);

    double getSpeed();
    void setSpeed(double newSpeed);
    void waitForSpeedChange(double targetSpeed);

private:
    double currentSpeed;
    std::mutex speedMutex;
    std::condition_variable speedChanged;
};