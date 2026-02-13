#pragma once

#include <functional>
#include <chrono>

class Scheduler {
public:
    // period: Execution period (e.g., 10ms for 100 Hz)
    Scheduler(std::function<void()> callback, std::chrono::microseconds period = std::chrono::microseconds(10));
    void run();

private:
    std::function<void()> m_callback;
    std::chrono::microseconds m_period;
    std::chrono::steady_clock::time_point m_next_wakeup_time;
    
    // Overrun detection
    bool m_overrun_detected = false;
    long long m_max_execution_time_ms = 0;
    
    // Bounded catch-up: max delay before skipping cycles (default: 5 periods)
    static constexpr int MAX_CATCHUP_PERIODS = 5;
};
