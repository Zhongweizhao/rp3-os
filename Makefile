CC = aarch64-linux-gnu-gcc
LD = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy

all: kernel8.img

CFLAGS = -g -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only -MMD
ASMFLAGS = -Iinclude -MMD

BUILD = build
SRC = src

CFILES = $(wildcard $(SRC)/*.c)
ASMFILES = $(wildcard $(SRC)/*.S)

COBJECTS = $(subst $(SRC), $(BUILD), $(CFILES:.c=.o))
ASMOBJECTS = $(subst $(SRC), $(BUILD), $(ASMFILES:.S=.o))

OBJECTS = $(COBJECTS) $(ASMOBJECTS)
DEPENDS = $(OBJECTS:%.o=%.d)
-include $(DEPENDS)

DIR_GUARD = @mkdir -p $(@D)

$(COBJECTS) : $(BUILD)/%.o : $(SRC)/%.c
	$(DIR_GUARD)
	$(CC) $(CFLAGS) -o $@ -c $<

$(ASMOBJECTS) : $(BUILD)/%.o : $(SRC)/%.S
	$(DIR_GUARD)
	$(CC) $(ASMFLAGS) -o $@ -c $<

kernel8.img: $(SRC)/linker.ld $(OBJECTS)
	$(LD) -T $(SRC)/linker.ld -o $(BUILD)/kernel8.elf $(OBJECTS)
	$(OBJCOPY) $(BUILD)/kernel8.elf -O binary kernel8.img

clean:
	rm -rf $(BUILD) *.img

