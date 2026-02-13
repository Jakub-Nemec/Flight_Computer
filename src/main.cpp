#include "Scheduler/Scheduler.h"
#include "FlightLoop/FlightLoop.h"

int main() {
    FlightLoop flight_loop;
    
    // Initialize scheduler with 100 Hz frequency (10 ms period)
    // Can be easily changed: 50 Hz = 20ms, 500 Hz = 2ms, etc.
    Scheduler scheduler([&flight_loop]() {
        flight_loop.tick();
    }, std::chrono::microseconds(10000));  // Using std::chrono::microseconds
    
    scheduler.run();
    return 0;
}