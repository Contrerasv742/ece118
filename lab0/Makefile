# Makefile for PIC32 Projects

# Project Name
PROJECT = my_project

# Microcontroller Model (change according to your specific PIC32 model)
MCU = 32MX795F512L

# Compiler and Linker
CC = xc32-gcc
BIN = xc32-bin2hex

# Include Paths - Update these with your actual paths!
XC32_DIR = /opt/microchip/xc32/v4.35
INCLUDES = -I/opt/microchip/xc32/v2.50/pic32mx/include \
           -I./include \
           -I./src

# Compiler Flags
CFLAGS = -mprocessor=$(MCU) -O1 -Wall $(INCLUDES)

# Linker Flags
LDFLAGS = -mprocessor=$(MCU) -Wl,--defsym=_min_heap_size=1024

# Source and Object Files
SRCDIR = src
OBJDIR = obj
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

# Output files
HEXFILE = $(PROJECT).hex
ELFFILE = $(PROJECT).elf

# Default target
all: directories $(HEXFILE)

# Create necessary directories
directories:
	mkdir -p $(OBJDIR)

# Rule to create hex file
$(HEXFILE): $(ELFFILE)
	$(BIN) $(ELFFILE)

# Rule to link object files
$(ELFFILE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

# Rule to compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -rf $(OBJDIR) $(HEXFILE) $(ELFFILE)

# Program the device using PICkit3 (you'll need pk2cmd installed)
# Replace with appropriate programmer command for your hardware
program: $(HEXFILE)
	pk2cmd -P PIC$(MCU) -F$(HEXFILE)

.PHONY: all clean program directories
