C_SOURCES   = $(wildcard Kernel/*.c Drivers/*.c Kernel/Interrupts/*.c)
ASM_SOURCES = $(wildcard Kernel/*.asm Drivers/*.asm Kernel/Interrupts/*.asm)
HEADERS     = $(wildcard Kernel/*.h Drivers/*.h Kernel/Interrupts/*.h)

INCLUDE_DIRS = Kernel Drivers

C_OBJ   = ${C_SOURCES:.c=.o}
ASM_OBJ = ${ASM_SOURCES:.asm=.o}

OBJ = ${C_OBJ} ${ASM_OBJ}

CFLAGS = -g -ffreestanding $(foreach dir, $(INCLUDE_DIRS), -I$(dir))

CFLAGS_ISR = -g -ffreestanding $(foreach dir, $(INCLUDE_DIRS), -I$(dir)) -mgeneral-regs-only

os-image.bin: Boot/boot.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: Boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: Boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^

run: os-image.bin
	qemu-system-i386 -fda os-image.bin

debug: os-image.bin kernel.elf
	qemu-system-i386 -kernel kernel.elf -S -s

%.o: %.c ${HEADERS}
	i386-elf-gcc ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf Kernel/*.o Boot/*.bin Drivers/*.o Boot/*.o
