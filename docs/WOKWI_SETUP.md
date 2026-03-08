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
2. Create a new file named `wokwi.toml`.
3. Paste this content exactly:

```toml
[wokwi]
firmware = "../.pio/build/uno_sim/firmware.hex"
elf = "../.pio/build/uno_sim/firmware.elf"
```

4. Save the file.

Notes:
- Keep the file name exactly `wokwi.toml`.
- Keep paths relative to the `Wokwi/` folder as shown above.

## Step 3: Verify Wokwi Firmware Mapping
Open `Wokwi/wokwi.toml` and confirm the `firmware` and `elf` paths are correct.

## Step 4: Start Simulation
1. Open the project in Wokwi.
2. Load `Wokwi/diagram.json`.
3. Press Play.

## Step 5: Test Behavior
- Rotate the potentiometer.
- Confirm LCD line 1 (`ADC`) changes from near 0 to near 1023.
- Confirm LCD line 2 (`Volt`) changes from near 0.000V to near 5.000V.
- Observe LED blink speed changing with ADC value.

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
2. Run simulation and record measured values.
3. Compare predictions with results and discuss error sources.
