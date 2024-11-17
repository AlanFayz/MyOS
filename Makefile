C_SOURCES   = $(wildcard Kernel/*.c    Drivers/*.c   Kernel/Interrupts/*.c    Kernel/Interrupts/Routines/*.c)
ASM_SOURCES = $(wildcard Kernel/*.asm  Drivers/*.asm Kernel/Interrupts/*.asm  Kernel/Interrupts/Routines/*.asm)
HEADERS     = $(wildcard Kernel/*.h    Drivers/*.h   Kernel/Interrupts/*.h    Kernel/Interrupts/Routines/*.h)

C_OBJ   = ${C_SOURCES:.c=.o}
ASM_OBJ = ${ASM_SOURCES:.asm=.o}
OBJ     = $(C_OBJ) $(ASM_OBJ)

INCLUDE_DIRS = Kernel Drivers
CFLAGS = -g $(foreach dir, $(INCLUDE_DIRS), -I$(dir))

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
	rm -rf Kernel/*.o Boot/*.bin Drivers/*.o Boot/*.o Kernel/Interrupts/*.o Kernel/Interrupts/Routines/*.o
