# API Reference for Simple ADC LCD

## Overview
This document serves as the detailed API reference for the Simple ADC LCD project. It provides information on the functionalities of various components within the project.

## Functions

### 1. `initialize_LCD()`
**Description:** Initializes the LCD display.

**Parameters:** None

**Returns:** None

**Usage:**
```python
initialize_LCD()
```

### 2. `read_ADC(channel)`
**Description:** Reads the analog value from the specified ADC channel.

**Parameters:**
- `channel` (int): The ADC channel number to read from.

**Returns:**
- `float`: The analog value converted to a float.

**Usage:**
```python
value = read_ADC(0)
```

### 3. `display_value(value)`
**Description:** Displays the given value on the LCD screen.

**Parameters:**
- `value` (float): The value to display.

**Returns:** None

**Usage:**
```python
display_value(3.14)
```

### 4. `clear_display()`
**Description:** Clears the LCD screen.

**Parameters:** None

**Returns:** None

**Usage:**
```python
clear_display()
```

## Error Handling
- Each function should handle errors appropriately, providing relevant feedback to the user.

## Additional Resources
- [LCD Documentation](https://example.com/lcd-docs)
- [ADC Documentation](https://example.com/adc-docs)