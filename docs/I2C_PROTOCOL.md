# I2C Protocol (Student Guide)

## Learning Goals

- Understand how I2C communication works.
- Identify SDA and SCL roles.
- Explain how Arduino talks to the LCD via I2C.

## What Is I2C?

I2C (Inter-Integrated Circuit) is a two-wire communication bus.

It uses:

- `SDA`: serial data line
- `SCL`: serial clock line

On Arduino Uno/Nano:

- `SDA` is `A4`
- `SCL` is `A5`

## Why I2C Is Useful

Compared to parallel LCD wiring, I2C needs fewer wires.
That makes circuits cleaner and easier for beginners.

## I2C Communication Flow

A typical I2C message includes:

1. START condition
2. 7-bit device address + read/write bit
3. ACK from receiver
4. Data byte(s) + ACK/NACK
5. STOP condition

## LCD Address in This Project

The I2C LCD backpack usually uses address `0x27`.
Some modules use `0x3F`.

Code example:

```cpp
LiquidCrystal_I2C lcd(0x27, 16, 2);
```

If LCD does not respond, try `0x3F`.

## Pull-up Resistors

I2C lines are open-drain, so SDA/SCL need pull-ups.
Many LCD I2C backpacks already include pull-up resistors.

## In This Project

- Arduino reads ADC value from `A0`.
- Arduino sends characters over I2C.
- LCD displays ADC and voltage in real time.

## Troubleshooting Checklist

- SDA and SCL not swapped.
- LCD has correct power (`5V` and `GND`).
- Correct I2C address (`0x27` or `0x3F`).
- Shared ground between all modules.

## Check Your Understanding

1. What are the two I2C wires called?
2. Why is I2C often easier than parallel LCD wiring?
3. What does ACK mean in I2C communication?
