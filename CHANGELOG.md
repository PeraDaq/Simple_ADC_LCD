# Changelog - Simple ADC LCD

All notable changes to the Simple ADC LCD project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [Unreleased]

### Planned Features
- [ ] **ADC Calibration System** - Allow users to calibrate voltage reference and ADC offset
- [ ] **I2C Address Auto-Detection** - Automatically scan and find connected LCD module
- [ ] **Configurable Update Rate** - Make 200ms refresh interval user-adjustable
- [ ] **Serial Data Logging** - Stream ADC and voltage data to serial for data collection
- [ ] **EEPROM Storage** - Save calibration data to persistent storage
- [ ] **Multi-LCD Support** - Handle multiple I2C LCD modules on different addresses
- [ ] **Data Filtering Modes** - Add median filter, exponential filter options beyond averaging
- [ ] **Temperature Compensation** - Account for temperature drift in ADC readings
- [ ] **Noise Analysis** - Measure and report ADC noise statistics

### In Development
- Serial output option with configurable baud rate
- Dual-mode firmware (I2C and parallel in one build)
- Web dashboard for data visualization (Wokwi integration)

### Breaking Changes (None planned)

### Deprecated Features (None)

---

## [1.0.0] - 2026-03-04

**First stable release** with core functionality for Arduino ADC to LCD display.

### Added

#### Core Features
- ✅ **Analog-to-Digital Conversion** - 10-bit ADC reading from potentiometer (pin A0)
- ✅ **Voltage Calculation** - Real-time conversion of ADC values to 0-5V range
- ✅ **I2C LCD Display** - 16x2 character LCD output via I2C interface (address 0x27)
- ✅ **LED Status Indicator** - Blinking LED on pin D8 with rate proportional to ADC value
- ✅ **Dual Environment Support**:
  - Wokwi simulation environment (Arduino Uno with I2C LCD)
  - Hardware environment (Arduino Nano with parallel LCD)

#### Display Output
- Line 1: Raw ADC value (0-1023)
- Line 2: Calculated voltage with 3 decimal places (0.000-5.000V)
- Update frequency: Every 200ms base + LED blink cycle
- Clear formatting with proper alignment

#### Hardware Support
- **Arduino Uno** - Full support for Wokwi simulation
- **Arduino Nano** - Full support for physical hardware deployment
- **Potentiometer** - 10kΩ linear variable resistor for analog input
- **LCD1602** - 16x2 I2C module (0x27 default, 0x3F alternative)
- **LED** - Standard 5mm with 220Ω current limiting resistor

#### Build System (PlatformIO)
- `uno_sim` environment - Builds I2C LCD firmware for Wokwi simulation
- `nanoatmega328` environment - Builds parallel LCD firmware for hardware
- Source file filtering - Separate firmware variants per environment
- Library dependency management:
  - `arduino-libraries/LiquidCrystal@^1.0.7` - Parallel LCD support
  - `marcoschwartz/LiquidCrystal_I2C@^1.1.4` - I2C LCD support

#### Wokwi Integration
- `Wokwi/diagram.json` - Complete circuit diagram with all components
- `Wokwi/wokwi.toml` - Firmware path configuration for simulator
- Schematic includes:
  - Arduino Uno with I2C LCD1602
  - Potentiometer on A0
  - LED with current limiting resistor on D8
  - Logic analyzer for I2C signal monitoring (debug)

#### Documentation (Initial)
- README.md - Project overview and quick start
- Build and run instructions
- Wiring diagrams for I2C and parallel LCD
- Troubleshooting guide
- Pin mapping reference
- LCD address configuration notes

#### Code Quality
- Clean, readable C++ code with meaningful variable names
- Proper I2C LCD initialization sequence
- Correct voltage conversion formula with comments
- LED blinking implementation with adjustable rate

### Technical Specifications

#### ADC (Analog-to-Digital Converter)
```cpp
ADC Resolution:        10-bit (0-1023)
Input Range:           0-5V
Reference Voltage:     5V (internal)
Sample Rate:           ~9600 Hz (Arduino default)
Accuracy:              ±5mV (one LSB step)
Conversion Formula:    voltage = adcValue × (5.0 / 1023.0)