# ESP32 CAN/TWAI Firmware — Two-Node CAN Network (In Progress)

**Repo description (use this on GitHub, replacing the current one):**
> ESP32 CAN/TWAI firmware project progressing toward a two-node CAN network with STM32 and SN65HVD230 transceivers.

---

## 1. Overview

This project implements CAN 2.0B communication at the firmware level using the ESP32's built-in TWAI (Two-Wire Automotive Interface) controller. The current milestone is a working ESP32 loopback transmit/receive path with FreeRTOS-based frame handling. The project is being built incrementally toward acceptance filtering, a physical two-node bus with SN65HVD230 transceivers, and an STM32 firmware port.

This is an active work-in-progress, not a finished multi-node system — see **Current Status** below for exactly what's working today.

## 2. Current Status

### Implemented
- ✅ ESP32 PlatformIO project setup
- ✅ TWAI (CAN) controller initialization
- ✅ 500 kbps CAN bit-rate configuration
- ✅ CAN frame transmission
- ✅ CAN frame reception via a dedicated FreeRTOS task
- ✅ Software-level identifier filtering
- ✅ GPIO-level loopback validation (TX↔RX jumpered, no transceiver)

### Planned
- ⬜ Hardware loopback validation with SN65HVD230 transceiver
- ⬜ Hardware acceptance filtering (TWAI controller filter registers)
- ⬜ CAN error and bus-status monitoring
- ⬜ Defined CAN message protocol (IDs, payload layout)
- ⬜ PC-based CAN simulation / bus-off testing
- ⬜ STM32 firmware port
- ⬜ Physical two-node CAN bus communication

## 3. Hardware

**Current**
- ESP32 development board (loopback only — TX and RX pins jumpered directly, no physical bus yet)

**Planned**
- SN65HVD230 CAN transceiver (x2, one per node)
- Second CAN node board
- STM32-based node (target MCU TBD)
- 120Ω termination resistors at each bus end

## 4. Software

| Component        | Value                     |
|-------------------|---------------------------|
| MCU               | ESP32                     |
| CAN Controller    | TWAI (ESP32 built-in)     |
| Framework         | Arduino (via PlatformIO)  |
| Build System      | PlatformIO                |
| Language          | C/C++                     |
| RTOS              | FreeRTOS                  |
| Version Control   | Git & GitHub              |

## 5. Architecture

Current data path (loopback stage — no transceiver, no second node yet):

```
┌─────────────────────────────┐
│           ESP32              │
│                               │
│  main task ──> TWAI TX ──────┼──┐
│                               │  │  GPIO 5 (TX) ── jumper ── GPIO 4 (RX)
│  FreeRTOS RX task <── TWAI RX ┼──┘
│       │                       │
│       └─> ID filter ─> print  │
└─────────────────────────────┘
```

Once transceivers are integrated, this becomes a real differential CAN_H/CAN_L bus between two independent nodes — that step is not done yet (see Planned above).

## 6. CAN Configuration

| Parameter        | Value      |
|--------------------|-----------|
| CAN Bit Rate       | 500 kbps  |
| TX Pin             | GPIO 5    |
| RX Pin             | GPIO 4    |
| Identifier Type    | Extended  |
| Test ID            | `0x200`   |
| Filter ID          | `0x100`   |

## 7. Project Structure

Current actual layout (folders below that don't exist yet are marked *planned* — they'll be added as the corresponding work lands, not created empty in advance):

```
Two-Node-CAN-Bus-Communication/
├── README.md
├── .gitignore
└── firmware/
    └── esp32/
        ├── platformio.ini
        └── src/
            └── main.cpp

# Planned, added as each milestone is reached:
# firmware/stm32/   — STM32 port
# hardware/         — schematics, transceiver wiring
# docs/             — protocol spec, test logs
# tools/            — PC-side CAN simulation scripts
```

## 8. Testing

**Done:**
- GPIO-level loopback: ESP32 TX (GPIO 5) jumpered to ESP32 RX (GPIO 4), confirming the TWAI driver correctly transmits and receives frames, and that FreeRTOS-based reception + software ID filtering work as expected. Verified via serial monitor logging of received frame IDs and payloads.

**Not yet done:**
- No transceiver-based electrical loopback yet (SN65HVD230 not wired in)
- No two-node bus test
- No error-frame / bus-off condition testing

## 9. Roadmap

**Phase 1 — ESP32 CAN (in progress)**
- ✅ Transmission and reception
- ✅ Identifier filtering (software)
- ⬜ Hardware acceptance filtering
- ⬜ Error monitoring

**Phase 2 — CAN Protocol**
- ⬜ Message identifiers
- ⬜ Payload definitions
- ⬜ Status and control messages

**Phase 3 — Simulation**
- ⬜ CAN node simulation
- ⬜ Arbitration behavior
- ⬜ Message priority and filtering

**Phase 4 — STM32 Portability**
- ⬜ STM32 CAN peripheral configuration
- ⬜ Firmware port

**Phase 5 — Multi-Node Network**
- ⬜ SN65HVD230 transceiver integration
- ⬜ Physical bus wiring
- ⬜ Two-node validation

## Development

Build the ESP32 firmware:
```
pio run
```

Upload to the ESP32:
```
pio run -t upload
```

Open the serial monitor:
```
pio device monitor -b 115200
```

## Project Goal

Build a structured embedded CAN communication system from the ground up, demonstrating practical firmware-level knowledge of CAN 2.0B, TWAI, FreeRTOS-based I/O handling, message filtering, diagnostics, and eventual multi-MCU portability (ESP32 → STM32).

> **Current status:** Phase 1 (ESP32 CAN) in progress — GPIO loopback verified. Transceiver integration and second node are the next milestones.
