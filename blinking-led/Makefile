# Microcontroller and clock configuration
MCU        ?= atmega328p
F_CPU      ?= 16000000UL

# Programmer settings (default: Arduino Uno)
PROGRAMMER ?= arduino
PORT       ?= /dev/ttyUSB0
BAUD       ?= 115200

# AVR Toolchain
CC         = avr-gcc
OBJCOPY    = avr-objcopy
SIZE       = avr-size
AVRDUDE    = avrdude

# Compiler flags
CFLAGS     = -Wall -Wextra -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)

# Directories and targets
SRC_DIR    = src
BUILD_DIR  = build
TARGET     = $(BUILD_DIR)/main

SRCS       = $(wildcard $(SRC_DIR)/*.c)
OBJS       = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Default target: compile and generate hex file
all: $(TARGET).hex

# Compile C source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into an ELF binary
$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	$(SIZE) --format=avr --mcu=$(MCU) $@

# Convert ELF binary to Intel HEX format for flashing
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Create build directory if it does not exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Flash the hex file to the AVR microcontroller
flash: $(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$<:i

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all flash clean
