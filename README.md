# Simple ADC LCD

A small Arduino/PlatformIO project that reads an analog input from a potentiometer and shows both the raw ADC value and calculated voltage on a 16x2 I2C LCD.

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
- `platformio.ini` - PlatformIO environment + libraries
- `Wokwi/diagram.json` - simulation wiring and parts
- `Wokwi/wokwi.toml` - Wokwi firmware mapping

## Dependencies

Configured in `platformio.ini`:

- `arduino-libraries/LiquidCrystal@^1.0.7`
- `marcoschwartz/LiquidCrystal_I2C@^1.1.4`

## Build and run (PlatformIO)

From the project root:

```bash
pio run
```

If you are using a connected board:

```bash
pio run -t upload
```

If you are using a Python virtual environment for PlatformIO, activate it first:

```bash
source /home/mopi5/pio-env/bin/activate
```

## Run in Wokwi

1. Build firmware first:
   - `pio run`
2. Open the Wokwi project files in the `Wokwi/` folder.
3. Start simulation.

`Wokwi/wokwi.toml` points to the generated firmware:

- `../.pio/build/nanoatmega328/firmware.hex`
- `../.pio/build/nanoatmega328/firmware.elf`

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

- `pio run`
- `pio run -t upload`

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
  - Rebuild with `pio run` before starting simulation.
  - Confirm `Wokwi/wokwi.toml` firmware paths point to `.pio/build/nanoatmega328/` outputs.

## Author

- Mohanad Sharif
