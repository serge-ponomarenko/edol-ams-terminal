# EDOL AMS Terminal

> Smart NFC-powered terminal for managing filament spools in the EDOL ecosystem.

---

## Overview

EDOL AMS Terminal is a compact ESP32-based touchscreen device designed for fast filament spool management.

The device integrates with the EDOL backend and allows users to:

* Scan NFC filament tags
* View spool information
* Encode new NFC tags
* Erase NFC tags
* Assign spools to AMS slots
* Monitor AMS status
* Display environmental information
* Manage WiFi and EDOL AMS connection settings

The terminal is designed as a dedicated appliance for workshops, maker spaces, and 3D printing environments.

---

## Features

* ESP32-based standalone device
* Touchscreen user interface (LVGL)
* NFC spool scanning
* NFC tag encoding
* AMS slot assignment
* WiFi configuration UI
* EDOL AMS integration
* Idle screen with live AMS data
* Automatic display dimming
* Lightweight embedded firmware

---

## Compatibility

⚠️ This project works **only** with the EDOL ecosystem.

Required backend project:

* [https://github.com/serge-ponomarenko/edol](https://github.com/serge-ponomarenko/edol)

The device depends on EDOL AMS APIs for:

* spool resolution
* AMS state synchronization
* spool assignment
* environmental data

---

# Hardware

## Required Components

| Component                              | Notes                         |
| -------------------------------------- | ----------------------------- |
| ESP32-2432S028R (Cheap Yellow Display) | Main controller + touchscreen |
| PN532 NFC Module                       | NFC reader/writer             |
| NFC Tags                               | NTAG213/215/216 recommended   |
| Jumper Wires                           | Connection wiring             |
| USB-C Cable                            | Power + firmware upload       |
| 3D Printed Case                        | Optional                      |

---

## Wiring Diagram

> TODO: Add wiring image / schematic.

### Example Pin Mapping

| Component      | ESP32 Pin |
| -------------- | --------- |
| PN532 SDA / SS | TODO      |
| PN532 SCK      | TODO      |
| PN532 MOSI     | TODO      |
| PN532 MISO     | TODO      |
| PN532 RST      | TODO      |
| PN532 IRQ      | TODO      |

---

## Device Photos

> TODO: Add photos of assembled device.

### Front View

![Device Front](docs/images/device-front.jpg)

### Back View

![Device Back](docs/images/device-back.jpg)

---

## 3D Printable Case

MakerWorld links:

* TODO: Add MakerWorld link
* TODO: Add MakerWorld link

---

# Firmware

## Installing over WEB Installation (recommended)

https://serge-ponomarenko.github.io/edol-ams-terminal/

## Building from Source

### Requirements

* VSCode
* PlatformIO extension
* USB drivers for ESP32 board

### Clone Repository

```bash
git clone https://github.com/YOUR_USERNAME/edol-ams-terminal.git
cd edol-ams-terminal
```

### Build Firmware

```bash
pio run
```

### Upload Firmware

```bash
pio run --target upload
```

### Serial Monitor

```bash
pio device monitor
```

---

# Configuration

## Initial Setup

On first boot the device automatically opens the Settings screen.

Configure:

* WiFi SSID
* WiFi Password
* EDOL AMS Host
* EDOL AMS Port

After saving settings the device reboots automatically.

---

## Recovering from Invalid WiFi Settings

If the device cannot connect to WiFi:

1. Open the Settings screen using the ⚙ button on the Loading screen
2. Update WiFi credentials
3. Save settings
4. Device will reboot automatically

---

# Usage

## Home Screen

The Home Screen displays:

* AMS status
* Temperature
* Humidity
* Current staged spool
* Connection state

---

## Scanning a Spool

1. Place NFC tag near the reader
2. Device resolves spool information from EDOL
3. Spool information appears in the staging panel

---

## Assigning Spool to AMS

1. Scan spool NFC tag
2. Tap staging panel
3. Select AMS slot:
   * A1
   * A2
   * A3
   * A4
   * EXT
4. Insert spool into selected slot

---

## Encoding NFC Tags

1. Open spool details screen
2. Press ENCODE
3. Place blank NFC tag on reader
4. Wait for successful write confirmation

---

## Erasing NFC Tags

1. Open spool details screen
2. Press ERASE
3. Place NFC tag on reader
4. Device clears spool data from tag

---

# Software Architecture

## Main Technologies

* ESP32
* Arduino Framework
* LVGL
* PlatformIO
* PN532 NFC
* LittleFS

---

## Services

| Service         | Purpose                        |
| --------------- | ------------------------------ |
| WifiService     | WiFi connectivity              |
| HttpService     | HTTP requests                  |
| AmsService      | EDOL AMS state synchronization |
| NfcService      | NFC scanning and writing       |
| StagingService  | Temporary spool staging        |
| SettingsService | Persistent configuration       |

---

# Future Improvements

* OTA firmware updates
* Web installer
* Multi-language UI
* Animated UI transitions
* MQTT support
* User authentication
* Sound feedback

---

# Useful Links

## EDOL Backend

* [https://github.com/serge-ponomarenko/edol](https://github.com/serge-ponomarenko/edol)

## LVGL

* [https://lvgl.io/](https://lvgl.io/)

## PlatformIO

* [https://platformio.org/](https://platformio.org/)

## ESP32

* [https://www.espressif.com/en/products/socs/esp32](https://www.espressif.com/en/products/socs/esp32)

## PN532

* [https://www.nxp.com/products/rfid-nfc/nfc-hf/nfc-readers/pn532-c1-near-field-communication-nfc-controller:PN532](https://www.nxp.com/products/rfid-nfc/nfc-hf/nfc-readers/pn532-c1-near-field-communication-nfc-controller:PN532)

---

# License

> TODO: Add license.

---

# Acknowledgements

Special thanks to the open-source embedded and maker communities.
