# Work Log

## 2026-03-04

- Created project-level `WORKLOG.md` using the same structure and style as `Simple_Traffic_Light/WORKLOG.md`.
- Confirmed this log is scoped only to `Simple_ADC_LCD` so project records remain repository-specific.
- Reconstructed today’s implementation timeline from repository commits:
	- `3303451` (05:33) initial project files for ADC + LCD integration.
	- `2a31599` (05:37) `.gitignore` baseline for build/config artifacts.
	- `6bce949` (15:04) initial ADC/LCD integration files from Wokwi simulation flow.
	- `749d1e9` (16:27) main ADC read + LCD display functionality update and Wokwi-side file movement to resolve simulation/library mismatch.
	- `05e3a2e` (16:32) `LiquidCrystal_I2C` dependency update and `Arduino.h` include alignment.
- Captured same-day configuration and simulation activity in this repo:
	- Wokwi assets updated (`Wokwi/diagram.json`, `Wokwi/libraries.txt`, `Wokwi/wokwi-project.txt`, `Wokwi/wokwi.toml`, `Wokwi/main_do_not_use.cpp`).
	- PlatformIO and source updates reflected in `platformio.ini` and `src/sketch.ino`.
	- Workspace/editor support files regenerated under `.vscode/`.
- Added session-level repository reporting details for completeness:
	- Confirmed commit authorship context (`Mohanad`) while reconstructing today’s timeline.
	- Included this session’s documentation actions (worklog creation, scope correction to active repo, and timeline expansion).
- Performed a final completeness pass using both `git log` and same-day file timestamp scans to reduce risk of missed activities.
- Recorded current uncommitted state snapshot for traceability: `.vscode/`, `WORKLOG.md`, `include/`, `lib/`, and `test/` are presently untracked.

### Later same-day updates (session continuation)

- Introduced a dual-environment PlatformIO workflow in `platformio.ini`:
	- `uno_sim` as default for Wokwi simulation output.
	- `nanoatmega328` for physical Nano flashing.
- Updated `Wokwi/wokwi.toml` firmware mapping to the simulation artifact path:
	- `../.pio/build/uno_sim/firmware.hex`
	- `../.pio/build/uno_sim/firmware.elf`
- Aligned hardware flashing behavior so the Nano environment builds the parallel LCD firmware source at `Wokwi/main_do_not_use.cpp` using `build_src_filter`.
- Validated both targets independently with successful builds:
	- `pio run -e uno_sim`
	- `pio run -e nanoatmega328`
- Completed successful Nano flash after clean rebuild:
	- `pio run -e nanoatmega328 -t clean`
	- `pio run -e nanoatmega328`
	- `pio run -e nanoatmega328 -t upload`
- Expanded project documentation:
	- Added a quick-start section for daily simulation/upload commands in `README.md`.
	- Added environment-mapping guidance and corrected Wokwi output paths in `README.md`.
- Resolved Wokwi TOML parse issue caused by invalid comment syntax:
	- Error observed: unknown character in `wokwi.toml`.
	- Removed/comment-normalized unsupported lines and left only valid TOML content.
