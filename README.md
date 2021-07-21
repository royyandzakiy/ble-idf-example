# BLE IDF Example

This project gives an example of usage of simple BLE Server

## Getting Started
- Prepare ESP-IDF extension on VSCode

## How this project was made
- Clone the [arduino-espidf-bareminimum](https://github.com/royyandzakiy/espidf-arduino-bareminimum) as base project
- Do `git submodule update --init --recursive` to clone all submodules in the folder `components`
- Change the `components/arduino-esp32/CMakeLists.txt` with `arduino-esp32-replace-CMakeLists.txt`
- Open SDK Configuration editor
    - Check [v] `Bluetooth`
    - Under `Bluetooth` Change `Bluetooth Controller Mode` to `BLE Only`
    - Under `Coexistence Bluetooth Side Options` Change Bluetooth Host to `Bluedroid - Dual-mode`
    - Go to `TLS Key Exchange Methods` and Check [v] `Enable pre-shared-key ciphersuites`