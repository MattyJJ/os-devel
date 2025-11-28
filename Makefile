SRC_DIR := src
BIN_DIR := bin
ISO_DIR := iso
ISO     := os.iso
GRUB    := grub.cfg
LINKER  := linker.ld

ASM_SRCS := $(shell find $(SRC_DIR) -name '*.s')
C_SRCS   := $(shell find $(SRC_DIR) -name '*.c')
OBJS     := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(C_SRCS))
OBJS     += $(patsubst $(SRC_DIR)/%.s,$(BIN_DIR)/%.o,$(ASM_SRCS))

KERNEL_ELF := $(BIN_DIR)/kernel.elf
OS_BIN     := $(BIN_DIR)/os.bin

CC  := i686-elf-gcc
AS  := i686-elf-as
LD  := i686-elf-gcc
OC  := i686-elf-objcopy

CFLAGS  := -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(SRC_DIR)
ASFLAGS := --32 
LDFLAGS := -T $(LINKER) -nostdlib -lgcc

all: $(KERNEL_ELF) $(OS_BIN)

$(KERNEL_ELF): $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

$(OS_BIN): $(KERNEL_ELF)
	$(OC) -O binary $< $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@) 
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.s
	mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

iso: $(KERNEL_ELF)  
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(GRUB) $(ISO_DIR)/boot/grub
	cp $(KERNEL_ELF) $(ISO_DIR)/boot/
	grub-mkrescue -o $(ISO) $(ISO_DIR)

run: iso  
	qemu-system-i386 -cdrom $(ISO) -serial stdio -m 512M -no-reboot

run-raw: $(OS_BIN) 
	qemu-system-i386 -fda $(OS_BIN) -serial stdio -m 512M

clean:
	rm -rf $(BIN_DIR) *.iso
	rm -rf $(ISO_DIR)

.PHONY: all iso run run-raw clean
