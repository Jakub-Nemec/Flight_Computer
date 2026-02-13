#include "Scheduler.h"
#include <chrono>
#include <thread>
#include <iostream>

Scheduler::Scheduler(std::function<void()> callback, std::chrono::microseconds period)
    : m_callback(callback), m_period(period),
      m_next_wakeup_time(std::chrono::steady_clock::now() + period) {}

void Scheduler::run() {
    // TODO: Add graceful shutdown mechanism (stop flag, signal handler)
    
    while (true) {
        auto execution_start = std::chrono::steady_clock::now();

        m_callback();

        auto execution_end = std::chrono::steady_clock::now();
        auto execution_time = std::chrono::duration_cast<std::chrono::microseconds>(execution_end - execution_start);
        
        // Overrun detection
        if (execution_time > m_period) {
            m_overrun_detected = true;
            std::cerr << "[SCHEDULER WARNING] Callback overrun detected! "
                      << "Execution time: " << execution_time.count() << "µs, "
                      << "Period: " << m_period.count() << "µs" << std::endl;
        }
        
        // Track max execution time for monitoring
        if (execution_time.count() > m_max_execution_time_ms) {
            m_max_execution_time_ms = execution_time.count();
        }
        
        // Next wakeup time pattern: increment by period regardless of execution time
        // This prevents cumulative drift even under load
        m_next_wakeup_time += m_period;
        
        // Bounded catch-up logic: Skip cycles if delay exceeds max allowed
        auto now = std::chrono::steady_clock::now();
        auto delay = now - m_next_wakeup_time;
        
        if (delay > std::chrono::microseconds(0)) {
            // We're running behind - calculate how many periods we've missed
            auto missed_periods = delay / m_period;
            
            if (missed_periods >= MAX_CATCHUP_PERIODS) {
                // Delay exceeds threshold - skip to nominal time instead of catching up
                long long periods_to_skip = (missed_periods / MAX_CATCHUP_PERIODS) * MAX_CATCHUP_PERIODS;
                m_next_wakeup_time = now + (m_period - (delay % m_period));
                
                std::cerr << "[SCHEDULER ERROR] Critical delay detected! "
                          << "Skipping " << periods_to_skip << " cycles. "
                          << "Delay: " << delay.count() << "µs" << std::endl;
            }
        }
        
        // Sleep until next scheduled time
        // If delay was small, this sleeps normally
        // If delay exceeded threshold, next_wakeup_time was reset to near-future
        std::this_thread::sleep_until(m_next_wakeup_time);
    }
}
