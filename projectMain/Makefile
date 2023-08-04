CC = msp430-elf-gcc
CFLAGS = -mmcu=msp430g2553
OBJS = main.o
TARGET = main.elf

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $@ $^

load: $(TARGET)
    msp430loader.sh $^

clean:
    rm -f *.o *.elf
