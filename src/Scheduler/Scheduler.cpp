#include "Scheduler.h"
#include <chrono>
#include <thread>
#include <iostream>

void Scheduler::run() {
    while (true) {
        auto start = std::chrono::steady_clock::now();

        std::cout << "Flight loop tick\n";

        std::this_thread::sleep_until(
            start + std::chrono::milliseconds(10)
        );
    }
}
