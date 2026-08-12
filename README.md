# Two-Node CAN Bus Communication Network

An embedded CAN 2.0B communication project built around the **ESP32 TWAI controller**, with a firmware architecture designed for future STM32 portability.

## Overview

This project explores CAN communication at the firmware level, progressing from a basic ESP32 loopback implementation toward filtering, diagnostics, protocol design, simulation, and multi-node communication.

## Current Status

* [x] ESP32 PlatformIO setup
* [x] TWAI CAN initialization
* [x] 500 kbps CAN configuration
* [x] CAN frame transmission
* [x] CAN frame reception using FreeRTOS
* [x] Initial software identifier filtering
* [ ] Hardware loopback validation
* [ ] Hardware acceptance filtering
* [ ] CAN error and status monitoring
* [ ] CAN message protocol
* [ ] PC-based CAN simulation
* [ ] STM32 firmware port
* [ ] Multi-node CAN communication

## Hardware

**Current**

* ESP32 development board

**Planned**

* SN65HVD230 CAN transceiver
* Additional CAN node
* STM32-based implementation

## Technology Stack

* **MCU:** ESP32
* **CAN Controller:** TWAI
* **Framework:** Arduino
* **Build System:** PlatformIO
* **Language:** C/C++
* **RTOS:** FreeRTOS
* **Version Control:** Git & GitHub

## Repository Structure

```text
Two-Node-CAN-Bus-Communication/
├── README.md
├── .gitignore
├── firmware/
│   ├── esp32/
│   │   ├── platformio.ini
│   │   └── src/
│   │       └── main.cpp
│   └── stm32/
├── docs/
├── hardware/
└── tools/
```

## ESP32 CAN Configuration

| Parameter       | Value    |
| --------------- | -------- |
| CAN Bit Rate    | 500 kbps |
| TX Pin          | GPIO 5   |
| RX Pin          | GPIO 4   |
| Identifier Type | Extended |
| Test ID         | `0x200`  |
| Filter ID       | `0x100`  |

## Current Firmware

The ESP32 firmware uses a dedicated **FreeRTOS task** for CAN reception through the TWAI driver.

The initial loopback test connects:

```text
GPIO 5 (TX) ───────── GPIO 4 (RX)
```

The firmware transmits a test CAN frame and processes received frames using identifier-based filtering.

## Roadmap

### Phase 1 — ESP32 CAN

* Transmission and reception
* Identifier filtering
* Acceptance filtering
* Error monitoring

### Phase 2 — CAN Protocol

* Message identifiers
* Payload definitions
* Status and control messages

### Phase 3 — Simulation

* CAN node simulation
* Arbitration
* Message priority and filtering

### Phase 4 — STM32 Portability

* STM32 CAN architecture
* Peripheral configuration
* Firmware port

### Phase 5 — Multi-Node Network

* CAN transceiver integration
* Physical bus communication
* Multi-node validation

## Development

Build the ESP32 firmware:

```bash
pio run
```

Upload to the ESP32:

```bash
pio run -t upload
```

Open the serial monitor:

```bash
pio device monitor -b 115200
```

## Project Goal

The goal is to develop a structured embedded CAN communication system while demonstrating practical knowledge of **CAN 2.0B, embedded firmware, TWAI, FreeRTOS, message filtering, diagnostics, simulation, and firmware portability**.

> **Project status:** ESP32 firmware development and hardware loopback validation in progress.
