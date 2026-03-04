# Simple ADC LCD

<img width="1127" height="758" alt="snip" src="https://github.com/user-attachments/assets/73e00980-88f3-425f-bcf8-37e36074b7a0" />

A small Arduino/PlatformIO project that reads an analog input from a potentiometer and shows both the raw ADC value and calculated voltage on a 16x2 I2C LCD.

## Quick Start (Daily Use)

Use this if you just want the fastest workflow:

```bash
# 1) Build firmware for Wokwi simulation
pio run -e uno_sim

# 2) Flash hardware Nano (parallel LCD firmware)
pio run -e nanoatmega328 -t upload
```

Optional (live serial output from Nano):

```bash
pio device monitor -b 9600
```

## What it does

- Reads analog input on `A0`.
- Converts the ADC reading (`0-1023`) to voltage using a 5V reference.
- Displays:
  - Line 1: `ADC: <value>`
  - Line 2: `Volt: <value> V`
- Blinks an LED on digital pin `8` with a delay tied to the ADC value.

## Hardware (simulated / physical)

- Arduino-compatible board (ATmega328P based)
- 16x2 I2C LCD (address `0x27` in code)
- Potentiometer
- Jumper wires

## Wiring

### Potentiometer
- `VCC` -> `5V`
- `GND` -> `GND`
- `SIG` -> `A0`

### I2C LCD1602
- `VCC` -> `5V`
- `GND` -> `GND`
- `SDA` -> `A4`
- `SCL` -> `A5`

## Project structure

- `src/sketch.ino` - main firmware logic
- `Wokwi/main_do_not_use.cpp` - parallel LCD firmware used for physical Nano target
- `platformio.ini` - PlatformIO environment + libraries
- `Wokwi/diagram.json` - simulation wiring and parts
- `Wokwi/wokwi.toml` - Wokwi firmware mapping

## Dependencies

Configured in `platformio.ini`:

- `arduino-libraries/LiquidCrystal@^1.0.7`
- `marcoschwartz/LiquidCrystal_I2C@^1.1.4`

## Build and run (PlatformIO)

### Environment mapping

- `uno_sim`:
  - Board: Arduino Uno
  - Source: `src/sketch.ino` (I2C LCD simulation firmware)
  - Used by Wokwi via `Wokwi/wokwi.toml`
- `nanoatmega328`:
  - Board: Arduino Nano (new bootloader)
  - Source: `Wokwi/main_do_not_use.cpp` (parallel LCD hardware firmware)

### Common commands

From the project root:

```bash
pio run
```

Build simulation firmware explicitly:

```bash
pio run -e uno_sim
```

Build Nano firmware explicitly:

```bash
pio run -e nanoatmega328
```

If you are using a connected board:

```bash
pio run -e nanoatmega328 -t upload
```

If you are using a Python virtual environment for PlatformIO, activate it first:

```bash
source /home/mopi5/pio-env/bin/activate
```

## Run in Wokwi

1. Build firmware first:
  - `pio run -e uno_sim`
2. Open the Wokwi project files in the `Wokwi/` folder.
3. Start simulation.

`Wokwi/wokwi.toml` points to the generated firmware:

- `../.pio/build/uno_sim/firmware.hex`
- `../.pio/build/uno_sim/firmware.elf`

## Notes

- The code currently initializes LCD at I2C address `0x27`:
  - `LiquidCrystal_I2C lcd(0x27, 16, 2);`
- If your LCD uses `0x3F`, update that constructor value in `src/sketch.ino`.
- Voltage is computed with a fixed 5V reference:
  - `voltage = adcValue * (5.0 / 1023.0)`
- Blink LED pin assignment in firmware:
  - `const int ledPin = 8;`

## Validation

The following commands were run successfully for this project today:

- `pio run -e uno_sim`
- `pio run -e nanoatmega328`
- `pio run -e nanoatmega328 -t upload`

## Troubleshooting

- LCD shows nothing:
  - Confirm `VCC`/`GND` wiring and that LCD backlight is on.
  - Verify I2C lines: `SDA -> A4`, `SCL -> A5`.
- Wrong characters or no text:
  - Check LCD I2C address in code. Try `0x27` or `0x3F` in `src/sketch.ino`.
- ADC value does not change:
  - Verify potentiometer `SIG` is connected to `A0`.
  - Confirm potentiometer ends are connected to `5V` and `GND`.
- Wokwi simulation not reflecting latest firmware:
  - Rebuild with `pio run -e uno_sim` before starting simulation.
  - Confirm `Wokwi/wokwi.toml` firmware paths point to `.pio/build/uno_sim/` outputs.
- Wokwi reports TOML parse errors (for example: unknown character at row/col):
  - Ensure `Wokwi/wokwi.toml` uses valid TOML syntax.
  - Do not use `;` style comments in this file.

## Documentation

Comprehensive project documentation is available in the following files:

- **[CONTRIBUTING.md](CONTRIBUTING.md)** - Guidelines for contributing to this project, development setup, code style, and pull request process
- **[CHANGELOG.md](CHANGELOG.md)** - Version history, release notes, and upcoming features
- **[LICENSE.md](LICENSE.md)** - MIT License details and terms of use
- **[API.md](API.md)** - Detailed API reference, function documentation, and hardware pinout

## Author

- Mohanad Sharif