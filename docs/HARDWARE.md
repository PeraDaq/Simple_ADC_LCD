# Hardware Guide - Simple ADC LCD

## Bill of Materials (BOM)

### Microcontroller

|Item|Qty|Spec|Purpose|
|------|-----|------|---------|
|Arduino Uno or Nano|1|ATmega328P|Main controller|
|USB Cable|1|USB-A to Micro-B|Power & Programming|

### Display

|Item|Qty|Spec|Purpose|
|------|-----|------|---------|
|I2C LCD Module|1|16x2 Blue Backlight|Display (Wokwi simulation)|
|Parallel LCD Module|1|16x2 Character LCD|Display (Hardware Nano)|

### Sensors & Actuators

|Item|Qty|Spec|Purpose|
|------|-----|------|---------|
|Potentiometer|1|10kΩ Linear|Variable analog input|
|LED|1|5mm Red/Green|Status indicator|
|Resistor|1|220Ω 1/4W|LED current limiting|

### Passive Components

|Item|Qty|Spec|Notes|
|------|-----|------|-------|
|Breadboard|1|830 tie-points|Prototyping|
|Jumper Wires|~20|22AWG|Various colors|
|Pull-up Resistors|2|4.7kΩ (optional)|I2C line stabilization|

### Power Supply

|Item|Qty|Spec|Notes|
|------|-----|------|-------|
|USB Power|1|5V 500mA|Via Arduino board|
|Capacitor|1|100µF (optional)|Power supply smoothing|

---

## Circuit Diagrams

### Wokwi Simulation (I2C LCD)

```text

Potentiometer          Arduino Uno        I2C LCD Module
    VCC ─────────────────5V                VCC ─────────────5V
    GND ─────────────────GND               GND ─────────────GND
    OUT ─────────────────A0                SDA ─────────────A4
                                           SCL ─────────────A5

LED
    Anode (+) ─────[220Ω]─────D8
    Cathode (-) ────────────GND

```

### Hardware (Parallel LCD)

```text

Potentiometer          Arduino Nano       Parallel LCD
    VCC ─────────────────5V                VCC ─────────────5V
    GND ─────────────────GND               GND ─────────────GND
    OUT ─────────────────A0

LCD Control Pins
    RS ─────────────────D12
    E ──────────────────D11
    D4 ─────────────────D5
    D5 ─────────────────D4
    D6 ─────────────────D3
    D7 ─────────────────D2

LED
    Anode (+) ─────[220Ω]─────D8
    Cathode (-) ────────────GND

```

---

## Component Specifications

### Arduino Uno / Nano

|Parameter|Value|Notes|
|-----------|-------|-------|
|Microcontroller|ATmega328P|8-bit AVR|
|Operating Voltage|5V|Standard digital logic|
|ADC Resolution|10-bit|0-1023 values|
|ADC Channels|6 (A0-A5)|8 on Mega|
|Digital I/O Pins|14 (Uno), 14 (Nano)|6 PWM capable|
|Clock Speed|16 MHz|Default frequency|
|Flash Memory|32 KB|Program storage|
|SRAM|2 KB|Working memory|
|EEPROM|1 KB|Persistent storage|

### I2C LCD Module (16x2)

|Parameter|Value|Notes|
|-----------|-------|-------|
|LCD Type|Character LCD|16 columns × 2 rows|
|Interface|I2C|2-wire communication|
|I2C Address|0x27 (default)|Scannable address|
|Alternative Addr|0x3F|Check module documentation|
|Back Light|Blue, adjustable|Potentiometer on back|
|Operating Voltage|5V|From I2C master (Uno/Nano)|
|Current Draw|~100mA (with backlight)|Typical operation|
|Refresh Rate|60 Hz|Internal to module|

### Parallel LCD Module (16x2)

|Parameter|Value|Notes|
|-----------|-------|-------|
|LCD Type|Character LCD|16 columns × 2 rows|
|Interface|4-bit Parallel|6 pins (RS, E, D4-D7)|
|Operating Voltage|5V|From microcontroller|
|Current Draw|~50mA (without backlight)|Depends on backlight|
|Back Light|Optional|Not always included|
|Enable Pin (E)|Strobe/clock|Latches data|
|Register Select (RS)|Control vs Data|0=instruction, 1=data|

### Potentiometer (10kΩ Linear)

|Parameter|Value|Notes|
|-----------|-------|-------|
|Resistance|10kΩ ±10%|Standard value|
|Taper|Linear|Output ∝ rotation angle|
|Voltage Range|0-5V|Full ADC range|
|Power Dissipation|1/4W typical|Small signal level|
|Rotation Angle|270° typical|Full sweep|
|Adjustment|Fine-tune|Screwdriver slot|

### LED (Standard 5mm Red)

|Parameter|Value|Notes|
|-----------|-------|-------|
|Wavelength|625nm (Red)|Visible color|
|Forward Voltage|2.0V @ 20mA|Typical Vf|
|Maximum Current|30mA|Absolute max|
|Recommended Current|10-20mA|Safe operating range|
|Power Dissipation|40mW|With 20mA|

### Current-Limiting Resistor (220Ω)

**Purpose**: Limit LED current to safe level

**Calculation**:

```text

V_resistor = V_supply - V_led
I_desired = 10-20mA (safe for LED)
R = V_resistor / I_desired

Example:
R = (5V - 2V) / 0.015A = 200Ω
Use 220Ω standard resistor (closest E12 value)

```

**Actual Current**:

```text

I = (5V - 2V) / 220Ω = 13.6mA ✓ (safe range)

```

---

## Connection Checklist

### I2C LCD Setup

- [ ] VCC → 5V (LCD power)
- [ ] GND → GND (LCD ground)
- [ ] SDA → A4 (Arduino data line)
- [ ] SCL → A5 (Arduino clock line)
- [ ] Backlight adjustment (if available)
- [ ] All connections secure
- [ ] No loose wires

### Parallel LCD Setup

- [ ] VCC → 5V (LCD power)
- [ ] GND → GND (LCD ground)
- [ ] RS → D12
- [ ] E → D11
- [ ] D4 → D5
- [ ] D5 → D4
- [ ] D6 → D3
- [ ] D7 → D2
- [ ] Contrast adjustment (if available)
- [ ] All connections secure

### Potentiometer Setup

- [ ] VCC → 5V
- [ ] GND → GND
- [ ] SIG → A0
- [ ] Potentiometer rotates smoothly
- [ ] No crackle when turning
- [ ] All connections secure

### LED Setup

- [ ] Anode (+, longer lead) → [220Ω] → D8
- [ ] Cathode (-, shorter lead) → GND
- [ ] Resistor color bands (Red-Red-Brown) or marked clearly
- [ ] LED brightness reasonable

---

## Troubleshooting Hardware

### LCD Display Issues

**Problem**: Display blank/no response

- **Check Power**: Measure 5V on VCC, GND on GND
- **Check I2C Lines**: A4 (SDA) and A5 (SCL) connected?
- **Check Address**: Is it 0x27 or 0x3F? Scan with I2C scanner
- **Check Contrast**: Adjust potentiometer on LCD back
- **Check Backlight**: May need adjustment potentiometer

**Problem**: Garbled/corrupted characters

- **Power Issues**: Use separate power supply if current is high
- **Cable Length**: I2C works up to ~1m at standard speed
- **Pull-up Resistors**: Add 4.7kΩ to SDA/SCL if needed
- **EMI**: Keep away from high-current circuits

### Potentiometer Issues

**Problem**: ADC value doesn't change

- **Connection**: Verify A0 connection to center pin
- **Power Supply**: Check VCC and GND connections
- **Dirty Contacts**: Clean potentiometer with isopropyl alcohol
- **Broken Potentiometer**: Test with another one

**Problem**: ADC value jumps around

- **Loose Connection**: Check breadboard contacts
- **Noise**: Add 100nF capacitor across potentiometer
- **Grounding**: Ensure good ground connection
- **Cable**: Use short, shielded cables if possible

### LED Issues

**Problem**: LED doesn't light

- **Polarity**: Check anode (+) to D8, cathode (-) to GND
- **Resistor**: Verify 220Ω resistor is in series
- **Pin**: Confirm D8 is correct Arduino pin
- **LED Dead**: Test with known working LED

**Problem**: LED too dim

- **Resistor Too High**: Use 100-150Ω instead
- **LED Old**: May have degraded brightness
- **Supply Voltage**: Check 5V is stable

**Problem**: LED too bright

- **Resistor Too Low**: Increase to 330-470Ω
- **Excessive Current**: May damage LED (limit to 30mA)
- **Heat**: Feel if LED gets warm

---

## Power Supply Considerations

### Current Draw Estimate

```text

Arduino Board:     ~50mA
I2C LCD Module:    ~100mA (with backlight)
Potentiometer:     ~1mA
LED:               ~20mA
─────────────────────────
Total:             ~170mA (worst case)

```

### USB Power

- USB 2.0: 500mA available → **Sufficient** ✓
- USB 3.0: 900mA available → **Sufficient** ✓
- Raspberry Pi GPIO: 50mA max → **NOT sufficient** ✗

### External Power Supply

If using external supply:

- Voltage: Exactly 5V (Arduino has voltage regulator)
- Current: ≥500mA recommended
- Connector: 2.1mm barrel jack or USB
- Ground: Must be connected to USB ground if using USB programming

---

## Layout Best Practices

1. **Keep Potentiometer Accessible**: Easy to rotate during testing
2. **LED Visible**: Position where brightness changes are visible
3. **LCD Readable**: Angle display perpendicular to view
4. **Cable Management**: Group I2C wires together (twist if long)
5. **Power Distribution**: 5V and GND rails on breadboard edges
6. **Decoupling**: Optional 100µF capacitor near power entry
7. **Spacing**: Keep high-current (LED) away from sensitive I2C signals

---

## Safety Considerations

- **Voltage**: 5V is safe to handle (no shock hazard)
- **Current**: LEDs are low-current, no burn hazard
- **Temperature**: Monitor components for excessive heat
- **ESD**: Avoid static discharge to Arduino board
- **USB Port**: Don't force USB connector
- **Breadboard**: Ensure secure connections (loose wires can short)
