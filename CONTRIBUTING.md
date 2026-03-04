# Contributing to Simple ADC LCD

## Code of Conduct

We are committed to providing a welcoming and inclusive environment for everyone. Please be respectful and constructive.

## How to Contribute

### 1. Fork the Repository

```bash
# Click "Fork" button on GitHub
# Then clone your fork:
git clone https://github.com/YOUR_USERNAME/Simple_ADC_LCD.git
cd Simple_ADC_LCD
```

### 2. Create a Feature Branch

```bash
git checkout -b feature/your-feature-name
```

Use descriptive names:
- `feature/add-calibration`
- `fix/lcd-address-detection`
- `docs/improve-wokwi-guide`

### 3. Make Your Changes

#### Code Style Guidelines

**C/C++ Code**:
```cpp
// Use meaningful variable names
const int LED_PIN = 8;        // Not: int x = 8;

// Clear comments for complex logic
float voltage = adcValue * (5.0 / 1023.0);  // Convert 10-bit ADC to 0-5V

// Function names should describe action
void blinkLED();              // Not: void func();

// Constants in UPPER_CASE
#define BUFFER_SIZE 256
const int DEFAULT_ADDRESS = 0x27;

// Indentation: 2 spaces (no tabs)
for (int i = 0; i < 10; i++) {
  adcValue += analogRead(A0);
}
```

**Markdown Documentation**:
- Use ATX-style headers (`#`, `##`, `###`)
- Code blocks with syntax highlighting
- Link to related documentation
- Include examples where helpful

### 4. Test Your Changes

#### Build Tests

```bash
# Build Wokwi simulation
pio run -e uno_sim

# Build hardware version
pio run -e nanoatmega328

# Should complete without errors
```

#### Functional Tests

- [ ] Compile without warnings
- [ ] ADC reads correct values (0-1023)
- [ ] Voltage calculation correct (0-5V)
- [ ] LCD displays properly formatted output
- [ ] LED blinks at expected rate
- [ ] Serial output (if added) formats correctly
- [ ] Wokwi simulation functions
- [ ] Hardware upload works
- [ ] No floating point exceptions
- [ ] No buffer overflows

#### Hardware Testing (if possible)

```bash
# Monitor real hardware
pio device monitor -b 9600

# Verify output:
# ADC: 512         
# Volt: 2.500 V    
```

### 5. Commit Your Changes

```bash
git add src/sketch.ino docs/API.md
git commit -m "Add ADC averaging feature for noise reduction

- Implement 10-sample rolling average
- Reduces noise from ~5mV to ~1.5mV
- Minimal performance impact (200µs per cycle)

Fixes #42"
```

**Commit Message Format**:
- First line: Concise summary (50 chars max)
- Blank line
- Detailed explanation (72 chars per line)
- Reference issues: `Fixes #123` or `Related to #456`

### 6. Push and Open Pull Request

```bash
git push origin feature/your-feature-name
```

Then create PR on GitHub with:
- Clear title and description
- Link to related issues
- Screenshots (if UI changes)
- Summary of changes

---

## Types of Contributions

### 🐛 Bug Fixes

Example: "Fix I2C address not updating when changed in code"

```cpp
// Before
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Hardcoded

// After
#define LCD_ADDRESS 0x27
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);
```

### ✨ Features

Example: "Add ADC averaging to reduce noise"

Must include:
- [ ] Updated API.md
- [ ] Updated CHANGELOG.md
- [ ] Test cases
- [ ] Documentation

### 📚 Documentation

Example: "Improve Wokwi setup guide with screenshots"

- Fix typos
- Add missing sections
- Improve clarity
- Add examples
- Update diagrams

### 🔧 Refactoring

Example: "Extract LCD initialization to function"

- Keep same functionality
- Improve readability
- Reduce code duplication
- Update comments

---

## Development Workflow

### Environment Setup

```bash
# Install PlatformIO
pip install platformio

# Clone and setup
git clone https://github.com/YOUR_USERNAME/Simple_ADC_LCD.git
cd Simple_ADC_LCD

# Install dependencies
pio lib install

# Verify setup
pio run -e uno_sim
```

### Daily Workflow

```bash
# Start feature branch
git checkout -b feature/my-change

# Make changes
# ... edit files ...

# Build frequently
pio run -e uno_sim

# Commit progress
git add .
git commit -m "WIP: Feature under development"

# When complete: test thoroughly
pio run -e uno_sim
pio run -e nanoatmega328
pio device monitor -b 9600

# Final commit
git commit --amend -m "Complete feature description"

# Push to GitHub
git push origin feature/my-change

# Open pull request
```

---

## Testing Checklist

Before submitting PR:

### Code Quality
- [ ] No compiler warnings
- [ ] No `TODO` comments without issues
- [ ] Consistent code style
- [ ] Meaningful variable names
- [ ] Functions under 50 lines (where possible)

### Functionality
- [ ] Feature works as described
- [ ] No regression (existing features still work)
- [ ] Edge cases handled (ADC=0, ADC=1023, etc.)
- [ ] No infinite loops or blocking calls (except necessary delays)
- [ ] Serial output (if added) is helpful, not spammy

### Documentation
- [ ] Code comments explain "why", not "what"
- [ ] Function signatures documented
- [ ] README updated (if user-facing change)
- [ ] API.md updated (if function changes)
- [ ] CHANGELOG.md updated
- [ ] Examples provided (if new feature)

### Hardware Compatibility
- [ ] Tested on Arduino Uno (Wokwi)
- [ ] Tested on Arduino Nano (if possible)
- [ ] Pin assignments verified
- [ ] No architecture-specific code (unless documented)

---

## Pull Request Review Process

### Automated Checks
- Build passes on both environments
- No compiler warnings
- Code style consistent

### Manual Review
- Maintainer reviews code logic
- Maintainer tests functionality
- Documentation is clear and correct

### Approval
- Minimum 1 approval from maintainer
- All automated checks passing
- All requested changes addressed

### Merge
- Squash commits (if multiple small commits)
- Merge to main branch
- Close associated issues
- Add to CHANGELOG.md

---

## Common Issues & Solutions

### Build Fails: Library Not Found

```bash
# Solution: Reinstall libraries
pio lib update
pio run -e uno_sim
```

### Merge Conflicts

```bash
# Solution: Rebase on latest main
git fetch origin
git rebase origin/main
# Resolve conflicts in editor
git add .
git rebase --continue
git push --force-with-lease
```

### Wokwi Shows Old Firmware

```bash
# Solution: Rebuild and clear cache
pio run -e uno_sim
pio run --target clean

# Then hard refresh Wokwi (Ctrl+Shift+R)
# And restart simulation
```

### ADC Values Noisy

```cpp
// Solution: Add averaging
int adcValue = 0;
for(int i = 0; i < 10; i++) {
  adcValue += analogRead(A0);
}
adcValue = adcValue / 10;
```

---

## Getting Help

- **General Questions**: Open an Issue with label `question`
- **Bug Reports**: Provide minimal reproducible example
- **Feature Requests**: Explain use case and desired behavior
- **Code Review**: Ask for feedback in PR discussion
- **Documentation**: Suggest improvements in Issues

---

## Recognition

Contributors will be recognized in:
- Git commit history
- CHANGELOG.md (for major changes)
- GitHub contributors page (automatic)

---

## License

By contributing, you agree that your contributions will be licensed under the MIT License.
