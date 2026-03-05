# Simple ADC LCD

<img width="1127" height="758" alt="snip" src="https://github.com/user-attachments/assets/73e00980-88f3-425f-bcf8-37e36074b7a0" />

A small Arduino/PlatformIO project that reads an analog input from a potentiometer and shows both the raw ADC value and calculated voltage on a 16x2 I2C LCD display. Supports both Wokwi simulation (Arduino Uno) and physical hardware deployment (Arduino Nano).

## 🚀 Quick Start (Daily Use)

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

## 🎯 What it does

- **Reads analog input** on `A0` from potentiometer (0-5V range)
- **Converts ADC reading** (`0-1023`) to voltage using 5V reference
- **Displays on LCD**:
  - Line 1: `ADC: <0-1023>`
  - Line 2: `Volt: <0.00-5.00> V`
- **Blinks LED** on digital pin `8` with speed tied to ADC value
- **Updates display** every 200ms with ADC averaging
- **Supports dual LCD modes**: I2C (Wokwi) and Parallel (Hardware Nano)

## 📦 Prerequisites

### Hardware Requirements
- **Microcontroller**: Arduino Uno (simulation) or Arduino Nano (hardware)
- **LCD Display**: 16x2 I2C LCD Module (address 0x27 or 0x3F)
- **Potentiometer**: 10kΩ variable resistor
- **LED**: Standard 5mm LED
- **Resistor**: 220Ω for LED (optional, for current limiting)
- **Jumper Wires**: Standard breadboard wires
- **Breadboard**: For prototyping

### Software Requirements
- Python 3.7+
- PlatformIO CLI: `pip install platformio`
- VSC or Arduino IDE (optional, for standalone development)

### For Simulation
- Wokwi.com account (free)
- Modern web browser with JavaScript enabled

## 🔧 Hardware / Pin Mapping

### Potentiometer Wiring
| Pin | Connection |
|-----|-----------|
| VCC | 5V |
| GND | GND |
| SIG | A0 (analog input) |

### I2C LCD1602 Wiring
| Pin | Connection | Notes |
|-----|-----------|-------|
| VCC | 5V | Power supply |
| GND | GND | Ground |
| SDA | A4 | Serial data (I2C) |
| SCL | A5 | Serial clock (I2C) |

### LED Wiring
| Pin | Connection |
|-----|-----------|
| Anode (+) | D8 (with 220Ω resistor) |
| Cathode (-) | GND |

### Parallel LCD Wiring (Hardware Nano Only)
| LCD Pin | Arduino Nano Pin |
|---------|-----------------|
| RS | D12 |
| E | D11 |
| D4 | D5 |
| D5 | D4 |
| D6 | D3 |
| D7 | D2 |
| VCC | 5V |
| GND | GND |

## 🏗️ Project Structure

```
Simple_ADC_LCD/
├── README.md                    # Main project documentation
├── platformio.ini               # PlatformIO configuration (2 environments)
├── src/
│   └── uno_sketch.ino          # I2C LCD firmware (Wokwi simulation)
├── Wokwi/
│   ├── nano_main.cpp           # Parallel LCD firmware (Hardware Nano)
│   ├── diagram.json             # Wokwi circuit diagram
│   └── wokwi.toml               # Wokwi firmware mapping
├── docs/
│   ├── ADC_EXPLAINED.md
│   ├── I2C_PROTOCOL.md
│   └── WOKWI_SETUP.md
├── CONTRIBUTING.md              # Contribution guidelines
├── CHANGELOG.md                 # Version history
├── LICENSE.md                   # MIT License
└── API.md                       # API reference
```

## Student Learning Docs

- [ADC Explained](docs/ADC_EXPLAINED.md)
- [I2C Protocol](docs/I2C_PROTOCOL.md)
- [Wokwi Setup](docs/WOKWI_SETUP.md)

## 📚 Dependencies

Configured in `platformio.ini`:

- **arduino-libraries/LiquidCrystal@^1.0.7** - Parallel LCD control library
- **marcoschwartz/LiquidCrystal_I2C@^1.1.4** - I2C LCD control library

## 🔨 Build and Run (PlatformIO)

### Environment Mapping

**Environment 1: Wokwi Simulation (Arduino Uno with I2C LCD)**
- Board: Arduino Uno
- Source: `src/uno_sketch.ino`
- LCD Type: I2C (LiquidCrystal_I2C library)
- LCD Address: 0x27 (configurable to 0x3F)
- Use Case: Quick testing, circuit verification

**Environment 2: Hardware Nano (Physical Deployment)**
- Board: Arduino Nano (new bootloader)
- Source: `Wokwi/nano_main.cpp`
- LCD Type: Parallel (LiquidCrystal library)
- LCD Pins: RS=12, E=11, D4=5, D5=4, D6=3, D7=2
- Use Case: Real hardware deployment

### Common Commands

```bash
# Build default environment (uno_sim)
pio run

# Build Wokwi simulation firmware explicitly
pio run -e uno_sim

# Build Nano firmware explicitly
pio run -e nanoatmega328

# Upload to connected Arduino Nano
pio run -e nanoatmega328 -t upload

# Monitor serial output at 9600 baud
pio device monitor -b 9600

# Clean build artifacts
pio run --target clean
```

### Using Python Virtual Environment

If using PlatformIO in a virtual environment:

```bash
source /home/mopi5/pio-env/bin/activate
pio run -e nanoatmega328 -t upload
```

## 🎮 Run in Wokwi

### Step-by-Step Guide

1. **Build firmware** for Wokwi:
   ```bash
   pio run -e uno_sim
   ```
   This generates `.pio/build/uno_sim/firmware.hex` and `.firmware.elf`

2. **Open Wokwi project**:
   - Go to [Wokwi.com](https://wokwi.com)
   - Create new project or open from `Wokwi/` folder
   - Verify `Wokwi/diagram.json` contains correct circuit

3. **Configure firmware path** in `Wokwi/wokwi.toml`:
   ```toml
   [wokwi]
   firmware = "../.pio/build/uno_sim/firmware.hex"
   elf = "../.pio/build/uno_sim/firmware.elf"
   ```

4. **Start simulation**:
   - Click "Play" button in Wokwi
   - Rotate potentiometer to see ADC/voltage change
   - Observe LED blinking speed tied to potentiometer value

5. **Debug serial output** (if needed):
   - Open browser DevTools (F12)
   - Watch UART output for debugging

### Firmware Paths

The simulation uses these generated files:
- `.pio/build/uno_sim/firmware.hex` - Hex firmware file
- `.pio/build/uno_sim/firmware.elf` - ELF debug symbols

If simulation shows outdated behavior:
- Rebuild with `pio run -e uno_sim`
- Verify paths in `wokwi.toml`
- Clear browser cache (Wokwi sometimes caches firmware)

## 🔍 Technical Details

### ADC Conversion

The project converts analog voltage to digital values:

```cpp
int adcValue = analogRead(A0);        // Raw ADC: 0-1023
float voltage = adcValue * (5.0/1023.0);  // Voltage: 0-5V
```

**ADC Specifications**:
- Resolution: 10-bit (0-1023 values)
- Reference Voltage: 5V (internal)
- Input Range: 0-5V
- Accuracy: ~5mV per step (5V / 1024 steps)

### LCD Display Output

**Line 1 Format**: `ADC: XXXX` (right-padded to 16 chars)
**Line 2 Format**: `Volt: X.XXX V` (with 3 decimal places)

Example output:
```
ADC: 512         
Volt: 2.500 V    
```

### Update Frequency

- **ADC Sampling**: 200ms + 2 x delay(adcValue) milliseconds
- **Display Refresh**: Every 200ms cycle
- **Effective Rate**: ~5Hz (varies with potentiometer position)

### I2C Address Configuration

Default I2C address: **0x27**

If LCD doesn't respond:
1. Scan for address with I2C scanner sketch
2. Common addresses: 0x27, 0x3F, 0x20, 0x38
3. Update in code: `LiquidCrystal_I2C lcd(0x3F, 16, 2);`

## 🐛 Troubleshooting

### LCD shows nothing
- **Check Power**: Verify VCC/GND connections
- **Backlight**: Adjust potentiometer on LCD module back
- **I2C Lines**: Ensure SDA (A4) and SCL (A5) are connected
- **I2C Address**: Try both 0x27 and 0x3F in code

### Wrong characters or corrupted display
- **LCD Address**: Check I2C address in code
- **LCD Type**: Verify 16x2 module (some use different formats)
- **Power Supply**: Weak power can cause display corruption
- **Cable Length**: Long I2C cables can cause signal issues

### ADC value doesn't change
- **Potentiometer Connection**: Verify SIG → A0
- **Potentiometer Range**: Confirm it sweeps full 5V range
- **Loose Connections**: Check breadboard contacts
- **Bad Potentiometer**: Test with known working part

### LED blinks too fast/slow
- **ADC Reading**: LED delay = ADC value in milliseconds
- **Potentiometer Position**: Turn to middle for moderate speed
- **LED Brightness**: Adjust resistor if too dim (use 120-470Ω)

### Wokwi simulation not updating
- **Rebuild Firmware**: Run `pio run -e uno_sim`
- **Clear Cache**: Hard refresh browser (Ctrl+Shift+R)
- **Check wokwi.toml**: Verify firmware path is correct
- **Restart Simulation**: Stop and start simulator again

### Build errors
- **Library Missing**: Run `pio lib install` automatically
- **Wrong Board**: Verify `board = uno` in platformio.ini
- **Path Issues**: Ensure file paths don't have spaces

## ✅ Validation

The following commands were tested successfully:

```
✓ pio run -e uno_sim              (Wokwi firmware build)
✓ pio run -e nanoatmega328        (Hardware firmware build)
✓ pio run -e nanoatmega328 -t upload  (Hardware upload)
✓ pio device monitor -b 9600      (Serial monitoring)
```

## 📖 Documentation

Comprehensive documentation is available:

- **[API.md](API.md)** - Function reference, parameters, and return values
- **[GETTING_STARTED.md](GETTING_STARTED.md)** - Setup guide for beginners
- **[HARDWARE.md](HARDWARE.md)** - Detailed hardware specifications and circuit diagrams
- **[ARCHITECTURE.md](ARCHITECTURE.md)** - Code architecture and design patterns
- **[CONTRIBUTING.md](CONTRIBUTING.md)** - Development guidelines and contribution process
- **[CHANGELOG.md](CHANGELOG.md)** - Version history and release notes
- **[LICENSE.md](LICENSE.md)** - MIT License terms
- **docs/ADC_EXPLAINED.md** - ADC conversion theory and calibration
- **docs/I2C_PROTOCOL.md** - I2C communication details
- **docs/WOKWI_SETUP.md** - Wokwi simulation guide

## 👤 Author

- Mohanad Sharif

## 📄 License

MIT License - See [LICENSE.md](LICENSE.md)