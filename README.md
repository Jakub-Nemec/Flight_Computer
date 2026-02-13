Flight Computer Simulator

Modular C++ simulation of a small satellite flight computer.
Designed with real-time scheduling principles and embedded systems mindset.

Current Features

- Bullet points:
- High-precision scheduler (microsecond resolution)
- Overrun detection
- Bounded catch-up mechanism
- Modular architecture (Scheduler / FlightLoop separation)

Architecture Overview
main
↓
Scheduler (100 Hz)
↓
FlightLoop

Roadmap
- [x] Core scheduler
- [ ] Gyro sensor simulation
- [ ] Attitude controller (PID)
- [ ] Data logger
- [ ] Fault injection
