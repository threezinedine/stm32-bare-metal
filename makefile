GCC 	= arm-none-eabi-gcc
ASM 	= arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
LD      = arm-none-eabi-ld
GDB     = gdb-multiarch
OPENOCD = openocd

GCC_FLAGS = -mcpu=cortex-m3 -mthumb -g -Wall 
ASM_FLAGS = 

BUILD_DIR = build
BIN_DIR   = $(BUILD_DIR)/bin
OBJ_DIR   = $(BUILD_DIR)/objects
DUMP_DIR  = $(BUILD_DIR)/dumps
MAP_DIR   = $(BUILD_DIR)/maps

TARGET_NAME = program
TARGET_ELF  = $(BIN_DIR)/$(TARGET_NAME).elf
TARGET_MAP  = $(MAP_DIR)/$(TARGET_NAME).map

C_FILES 	= $(wildcard src/*.c)
C_OBJ_FILES = $(patsubst src/%.c, $(OBJ_DIR)/%.c.o, $(C_FILES))

$(TARGET_ELF): directory $(C_OBJ_FILES)
	$(LD) -T linker.ld -Map $(TARGET_MAP) -o $@ $(C_OBJ_FILES)

$(OBJ_DIR)/%.c.o: src/%.c
	$(GCC) $(GCC_FLAGS) -c $< -o $@
	$(OBJDUMP) -D $@ > $(DUMP_DIR)/$*.c.o.dump

directory:
	@mkdir -p $(BIN_DIR) $(OBJ_DIR) $(DUMP_DIR) $(MAP_DIR)

open:
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg

write:
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program $(TARGET_ELF) verify reset exit"

open-write:
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program $(TARGET_ELF) verify reset"

gdb:
	$(GDB) $(TARGET_ELF) -ex "target remote localhost:3333" -ex "layout split"

clean:
	@rm -rf $(BUILD_DIR)