C_SOURCES = $(wildcard Kernel/*.c Drivers/*.c)
HEADERS = $(wildcard Kernel/*.h Drivers/*.h)

OBJ = ${C_SOURCES:.c=.o}

CFLAGS = -g

os-image.bin: Boot/boot.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: Kernel/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: Kernel/kernel_entry.o ${OBJ}
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
