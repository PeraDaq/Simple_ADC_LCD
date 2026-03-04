# API Reference - Simple ADC LCD

## Overview

This document provides detailed API documentation for the Simple ADC LCD project, including function signatures, parameters, return values, and usage examples.

## Functions

### I2C LCD Version (Wokwi Simulation)

**File**: `src/sketch.ino`

#### `void setup()`

Initializes the I2C LCD display and LED pin.

**Syntax**:
```cpp
void setup()
```

**Parameters**: None

**Returns**: void

**Behavior**:
```cpp
lcd.init();                 // Initialize I2C LCD at address 0x27
lcd.backlight();            // Turn on LCD backlight
pinMode(ledPin, OUTPUT);    // Configure pin 8 as output for LED
```

**Notes**:
- Runs once on board power-up
- I2C address (0x27) is hardcoded in setup
- Backlight is enabled by default

---

#### `void loop()`

Main program loop that reads ADC, converts to voltage, displays on LCD, and blinks LED.

**Syntax**:
```cpp
void loop()
```

**Parameters**: None

**Returns**: void

**Behavior**:
1. Read analog value from pin A0
2. Convert ADC reading to voltage
3. Blink LED with delay proportional to ADC value
4. Clear LCD and display new values
5. Wait 200ms and repeat

**Timing**:
```
Total cycle time ≈ 200ms + (2 × adcValue)ms

Example: ADC=500
- LED ON: 500ms
- LED OFF: 500ms
- Display: 200ms
- Total: 1200ms per cycle
```

**Key Variables**:
```cpp
int adcValue = analogRead(A0);           // 0-1023
float voltage = adcValue * (5.0/1023.0); // 0-5.0V
```

**LCD Output**:
```
Line 0: "ADC: " + adcValue
Line 1: "Volt: " + voltage (3 decimals) + " V"
```

---

### Parallel LCD Version (Hardware Nano)

**File**: `Wokwi/main_do_not_use.cpp`

#### `void setup()`

Initializes parallel LCD in 4-bit mode and LED pin.

**Syntax**:
```cpp
void setup()
```

**Parameters**: None

**Returns**: void

**Behavior**:
```cpp
lcd.begin(16, 2);     // Initialize parallel LCD: 16 cols × 2 rows
lcd.clear();          // Clear display
pinMode(ledPin, OUTPUT);  // Configure pin 8 for LED
```

**LCD Pin Configuration**:
```
RS=12, E=11, D4=5, D5=4, D6=3, D7=2
```

---

#### `void loop()`

Main loop with ADC averaging and parallel LCD output.

**Syntax**:
```cpp
void loop()
```

**Parameters**: None

**Returns**: void

**Unique Features**:
```cpp
// Average 10 ADC readings for noise reduction
int adcValue = 0;
for(int i = 0; i < 10; i++) {
  adcValue += analogRead(A0);
}
adcValue = adcValue / 10;
```

**Advantages over I2C version**:
- Averaging reduces noise/jitter
- Padding with spaces clears leftover characters
- More robust for physical hardware

---

## Global Variables

### I2C Version (`src/sketch.ino`)

```cpp
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C LCD at address 0x27, 16×2 display
const int adcPin = A0;                // Analog input pin (potentiometer)
const int ledPin = 8;                 // Digital output pin (LED)
```

### Parallel Version (`Wokwi/main_do_not_use.cpp`)

```cpp
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // Parallel LCD: RS, E, D4-D7
const int adcPin = A0;                   // Analog input pin
const int ledPin = 8;                    // Digital output pin
```

---

## Pin Configuration

### Simulation (Arduino Uno - I2C)

| Pin | Function | Mode | Purpose |
|-----|----------|------|---------|
| A0 | ADC Input | INPUT | Potentiometer signal |
| A4 | I2C SDA | INPUT/OUTPUT | LCD data line |
| A5 | I2C SCL | INPUT/OUTPUT | LCD clock line |
| D8 | LED Control | OUTPUT | Status LED indicator |

### Hardware (Arduino Nano - Parallel)

| Pin | Function | Mode | Purpose |
|-----|----------|------|---------|
| A0 | ADC Input | INPUT | Potentiometer signal |
| D2 | LCD D7 | OUTPUT | Data line 7 |
| D3 | LCD D6 | OUTPUT | Data line 6 |
| D4 | LCD D5 | OUTPUT | Data line 5 |
| D5 | LCD D4 | OUTPUT | Data line 4 |
| D8 | LED Control | OUTPUT | Status LED indicator |
| D11 | LCD E | OUTPUT | Enable signal |
| D12 | LCD RS | OUTPUT | Register select |

---

## ADC Specifications

### Input Characteristics

```cpp
int adcValue = analogRead(A0);  // Returns 0-1023
```

| Parameter | Value |
|-----------|-------|
| Resolution | 10-bit |
| Range | 0-1023 |
| Voltage Range | 0-5V |
| LSB (Least Significant Bit) | ~4.9mV |
| Sampling Frequency | ~9.6 kHz (default) |

### Voltage Conversion Formula

```cpp
float voltage = adcValue * (5.0 / 1023.0);
```

**Calculation**:
- ADC = 0 → Voltage = 0.000V
- ADC = 256 → Voltage = 1.251V
- ADC = 512 → Voltage = 2.500V
- ADC = 768 → Voltage = 3.749V
- ADC = 1023 → Voltage = 4.995V

### Accuracy

- **Theoretical Accuracy**: ±5mV (one LSB step)
- **Practical Accuracy**: ±10-20mV (with noise)
- **Averaging** (hardware version): Improves by √10 ≈ 3.16× (±3-6mV)

---

## LCD Display Specifications

### I2C Version (Wokwi)

```cpp
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Address: 0x27 (configurable to 0x3F)
// Columns: 16
// Rows: 2
```

**Display Commands**:

```cpp
lcd.init();              // Initialize I2C connection
lcd.backlight();         // Enable backlight
lcd.noBacklight();       // Disable backlight
lcd.clear();             // Clear display
lcd.setCursor(col, row); // Set cursor position (0-15 col, 0-1 row)
lcd.print(value);        // Print text/number
```

**Output Format**:

```
[0]: "ADC: " + value (0-1023)
[1]: "Volt: " + voltage (3 decimals) + " V"

Example:
Line 0: "ADC: 512        "
Line 1: "Volt: 2.500 V   "
```

### Parallel Version (Hardware Nano)

```cpp
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// 4-bit mode: RS=12, E=11, D4=5, D5=4, D6=3, D7=2
// Columns: 16
// Rows: 2
```

**Additional Features**:
- Padding with spaces to clear leftover characters
- 10-sample averaging for noise reduction

---

## LED Blinking Behavior

The LED blinks with a frequency tied to the ADC value:

```cpp
digitalWrite(ledPin, HIGH);    // LED ON
delay(adcValue);               // Delay = ADC value (0-1023ms)
digitalWrite(ledPin, LOW);     // LED OFF
delay(adcValue);               // Delay = ADC value (0-1023ms)
```

**Blink Rate Table**:

| ADC Value | On Time | Off Time | Frequency |
|-----------|---------|----------|-----------|
| 100 | 100ms | 100ms | 5 Hz |
| 256 | 256ms | 256ms | 1.95 Hz |
| 512 | 512ms | 512ms | 0.98 Hz |
| 1023 | 1023ms | 1023ms | 0.49 Hz |

---

## Update Frequency

**I2C Version**:
```
Cycle Time = 200ms + (2 × adcValue)ms
Minimum: 200ms (adcValue=0) → 5 Hz
Maximum: 2246ms (adcValue=1023) → 0.44 Hz
```

**Parallel Version**:
- Same timing, plus averaging overhead (~50µs negligible)

---

## Serial Output

No serial output by default, but can be added:

```cpp
void setup() {
  Serial.begin(9600);
  Serial.println("ADC LCD Ready");
}

void loop() {
  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" Volt: ");
  Serial.println(voltage, 3);
  // ... rest of code
}
```

**Monitor with**: `pio device monitor -b 9600`

---

## Error Handling

**Current Implementation**: None explicit error checking

**Recommended Additions**:
```cpp
// I2C address detection
if (!lcd.init()) {
  Serial.println("LCD initialization failed");
  // Handle error
}

// Bounds checking
if (adcValue < 0 || adcValue > 1023) {
  // Handle out-of-range ADC value
}
```

---

## Performance Characteristics

| Metric | Value | Notes |
|--------|-------|-------|
| ADC Sampling Rate | ~9.6 kHz | Arduino default |
| LCD Update Rate | 0.44-5 Hz | Depends on ADC value |
| I2C Clock Speed | 100 kHz | Standard mode |
| Memory Usage (I2C) | ~2.5 KB | With libraries |
| Memory Usage (Parallel) | ~2.3 KB | Fewer I2C libraries |
| Power Consumption | ~50-100mA | Depends on LED state |

---

## Known Limitations

1. **No ADC Error Handling**: Out-of-range values not checked
2. **Fixed Voltage Reference**: 5V hardcoded (not AREF compatible)
3. **No Calibration**: Uses internal reference (±2-3% error possible)
4. **Blocking Delays**: `delay()` blocks entire program
5. **No Interrupt-Driven I2C**: Uses blocking I2C read/write
6. **Limited Update Rate**: Slow when ADC value is high

---

## Compatibility

### Microcontroller Support

| Board | Status | Notes |
|-------|--------|-------|
| Arduino Uno | ✅ Tested (Wokwi) | Default simulation |
| Arduino Nano | ✅ Tested (Hardware) | Parallel LCD version |
| Arduino Pro Mini | ✅ Compatible | Same pins as Uno |
| Arduino Mega | ✅ Compatible | Use any 2 I2C-capable pins |
| Arduino Leonardo | ⚠️ Partial | Different I2C pins (SDA=2, SCL=3) |

### LCD Module Support

| Type | Address | Status |
|------|---------|--------|
| 16x2 I2C | 0x27 | ✅ Default |
| 16x2 I2C | 0x3F | ✅ Changeable |
| 20x4 I2C | 0x27 | ✅ Update constructor |
| 16x2 Parallel | N/A | ✅ Hardware version |
| Character LCD | Any | ⚠️ May need adjustment |
