
#include "ControlSpeed.h"
#include <iostream>

SpeedController::SpeedController(double initialSpeed) : currentSpeed(initialSpeed) {}

double SpeedController::getSpeed() {
    std::lock_guard<std::mutex> lock(speedMutex);
    return currentSpeed;
}

void SpeedController::setSpeed(double newSpeed) {
    std::unique_lock<std::mutex> lock(speedMutex);
    currentSpeed = newSpeed;
    speedChanged.notify_all();
}

void SpeedController::waitForSpeedChange(double targetSpeed) {
    std::unique_lock<std::mutex> lock(speedMutex);
    speedChanged.wait(lock, [this, targetSpeed] { return currentSpeed == targetSpeed; });
    std::cout << "Target speed reached: " << targetSpeed << std::endl;
}