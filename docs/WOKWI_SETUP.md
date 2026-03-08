# Wokwi Setup (Student Guide)

## Learning Goals


- Build firmware with PlatformIO.
- Run the circuit in Wokwi.
- Verify that potentiometer changes ADC and voltage.

## Files Used


- `Wokwi/uno_main.cpp`: simulation firmware source
- `Wokwi/diagram.json`: virtual circuit layout
- `Wokwi/wokwi.toml`: firmware path mapping

## Step 1: Build Simulation Firmware

From project root:

```bash

pio run -e uno_sim

```

Expected outputs:

- `.pio/build/uno_sim/firmware.hex`
- `.pio/build/uno_sim/firmware.elf`

## Step 2: Create `wokwi.toml` From Scratch

If `Wokwi/wokwi.toml` does not exist yet, create it manually.

1. In your project, open the `Wokwi/` folder.
1. Create a new file named `wokwi.toml`.
1. Paste this content exactly:

```toml

[wokwi]
firmware = "../.pio/build/uno_sim/firmware.hex"
elf = "../.pio/build/uno_sim/firmware.elf"

```

1. Save the file.

Notes:

- Keep the file name exactly `wokwi.toml`.
- Keep paths relative to the `Wokwi/` folder as shown above.

## Step 3: Verify Wokwi Firmware Mapping

Open `Wokwi/wokwi.toml` and confirm the `firmware` and `elf` paths are correct.

## Step 4: Start Simulation


1. Open the project in Wokwi.
1. Load `Wokwi/diagram.json`.
1. Press Play.

## Step 5: Test Behavior


- Rotate the potentiometer.
- Confirm LCD line 1 (`ADC`) changes from near 0 to near 1023.
- Confirm LCD line 2 (`Volt`) changes from near 0.000V to near 5.000V.
- Observe LED blink speed changing with ADC value.

## Step 6: Monitor with Teleplot (Serial)

The firmware emits Teleplot serial lines at `9600` baud:

- `>adc:<value>`
- `>volt:<value>`

Notes:

- The `>` prefix is required by Teleplot serial parsing.
- For hardware Nano, use `pio device monitor -b 9600` for a quick sanity check.

## Step 7: Inspect Waveforms with VaporView

1. Ensure Logic Analyzer is present in `Wokwi/diagram.json`.
1. Run and stop simulation to export `Wokwi/wokwi.vcd`.
1. Open `Wokwi/wokwi.vcd` in VaporView.

I2C check:

- START condition is valid when `SDA` goes low while `SCL` stays high.

Optional label cleanup:

- Set Logic Analyzer `channelNames` in `Wokwi/diagram.json` for readable signal names.

## Common Issues


- Firmware not rebuilt after code edits.
- Wrong firmware path in `wokwi.toml`.
- Browser cache showing old behavior.

## Quick Fixes


```bash

pio run -e uno_sim

```

Then refresh Wokwi and run again.

## Classroom Activity


1. Predict LCD values at 25%, 50%, and 75% potentiometer position.
1. Run simulation and record measured values.
1. Compare predictions with results and discuss error sources.
