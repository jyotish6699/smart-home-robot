# Aegis

Aegis is an ESP32-based smart home robot designed to evolve from a manually controlled mobile robot into a fully autonomous indoor robotic platform.

The project follows an incremental milestone-based development process where every version introduces a stable and tested feature set.

Current Version: **v0.0.6**

---

## Features

### Firmware

* ESP32 bring-up
* Wi-Fi connectivity
* Multi-network Wi-Fi failover
* OTA firmware updates
* Telnet logging
* mDNS hostname (`aegis.local`)
* HTTP web server
* LittleFS web assets
* Web-based remote control dashboard
* Motor driver abstraction
* Modular firmware architecture

---

## Repository Structure

```
smart-home-robot/

├── docs/
│   ├── milestone.md
│   └── roadmap.md
│
├── firmware/
│   └── robot-firmware/
│       ├── include/
│       ├── lib/
│       ├── src/
│       ├── data/
│       ├── test/
│       └── platformio.ini
│
├── hardware/
│   └── components.md
│
└── README.md
```

---

## Current Capabilities

* Manual remote driving through browser
* Automatic Wi-Fi network selection
* OTA firmware update
* Real-time Telnet logging
* mDNS hostname support
* Mobile browser support
* Laptop browser support

---

## Current Hardware

* ESP32 Dev Module
* L298N Motor Driver
* 4 DC Geared Motors
* 3S Lithium Battery Pack
* Robot Chassis
* Wheels

---

## Roadmap

Current milestone:

**v0.0.6 — Web-based Remote Control**

Upcoming milestone:

**v0.0.7 — Advanced Robot Dashboard & Diagnostics**

---

## Development Philosophy

Aegis is developed incrementally.

Each milestone introduces a fully working subsystem before moving to the next stage.

This ensures maintainability, easier debugging, and reproducible development.
