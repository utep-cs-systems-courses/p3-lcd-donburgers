
# Makefile for MSP430 Project

# Variables
CC = msp430-gcc
OBJCOPY = msp430-objcopy
SIZE = msp430-size
MSPDEBUG = mspdebug
MCU = msp430g2553
CFLAGS = -mmcu=$(MCU) -Os
LDFLAGS = -mmcu=$(MCU)

# Files
SOURCES = main.c
OBJS = $(SOURCES:.c=.o)
ELF = main.elf
HEX = main.hex

# Rules
all: $(ELF)

$(ELF): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

flash: $(HEX)
	$(MSPDEBUG) rf2500 "prog $(HEX)"

size: $(ELF)
	$(SIZE) $(ELF)

clean:
	rm -f $(OBJS) $(ELF) $(HEX)

.PHONY: all flash size clean
