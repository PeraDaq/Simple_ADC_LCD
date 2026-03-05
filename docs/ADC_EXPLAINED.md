# ADC Explained (Student Guide)

## Learning Goals
- Understand what an ADC does.
- Convert raw ADC values into voltage.
- Predict how changing a potentiometer affects readings.

## What Is ADC?
ADC means Analog-to-Digital Converter.

Arduino analog pins read a continuous voltage (analog) and convert it to a number (digital).
On Uno/Nano, the ADC is 10-bit, so readings go from `0` to `1023`.

- `0` means about `0V`
- `1023` means about `5V` (default reference)

## Core Formula
Use this formula in your code:

```cpp
float voltage = adcValue * (5.0 / 1023.0);
```

Where:
- `adcValue` is `analogRead(A0)`
- `5.0` is the reference voltage
- `1023.0` is the max 10-bit value

## Quick Examples
- If ADC = `0`, Voltage is `0.000V`
- If ADC = `512`, Voltage is about `2.502V`
- If ADC = `1023`, Voltage is about `5.000V`

## In This Project
- Potentiometer center pin goes to `A0`.
- Turning the knob changes voltage at `A0`.
- LCD line 1 shows raw ADC.
- LCD line 2 shows computed voltage.

## Common Student Mistakes
- Using integer math only (loses decimals).
- Forgetting to set the analog input pin wiring correctly.
- Mixing up `1023` and `1024` in formulas.

## Mini Lab
1. Read `analogRead(A0)` once every 200 ms.
2. Print ADC and voltage to LCD.
3. Turn the potentiometer to 0%, 50%, 100%.
4. Record expected vs observed voltage.

## Check Your Understanding
1. Why is the max ADC value `1023` instead of `1024`?
2. If ADC reads `256`, what voltage do you expect?
3. What happens if Vref changes from 5V to 3.3V?
