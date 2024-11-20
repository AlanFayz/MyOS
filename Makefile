C_SOURCES   = $(wildcard Source/Kernel/*.c  Source/Boot/*.c Source/Common/*.c)
ASM_SOURCES = $(wildcard Source/Kernel/*.s  Source/Boot/*.s Source/Common/*.s)
HEADERS     = $(wildcard Source/Kernel/*.h  Source/Boot/*.h Source/Common/*.h)

C_OBJ   = ${C_SOURCES:.c=.o}
ASM_OBJ = ${ASM_SOURCES:.s=.o}
OBJ     = $(C_OBJ) $(ASM_OBJ)

INCLUDE_DIRS = Source 
CFLAGS     = -g -ffreestanding -fno-stack-protector -fno-builtin $(addprefix -I, $(INCLUDE_DIRS))
ASM_FLAGS  = -f elf32
LINK_FLAGS = -T linker.ld 

%.o: %.c ${HEADERS}
	i386-elf-gcc ${CFLAGS} -c $< -o $@

%.o: %.s
	nasm $< ${ASM_FLAGS} -o $@

Output/boot/kernel: ${OBJ}
	i386-elf-ld ${LINK_FLAGS} -o $@ ${OBJ}

Output/boot/MyOS.iso: Output/boot/kernel  
	grub-mkrescue /usr/lib/grub/i386-pc -o $@ Output

run: Output/boot/MyOS.iso 
	qemu-system-i386  Output/boot/MyOS.iso 

clean: 
	rm -rf *.bin *.dis *.o *.elf
	rm -rf ${OBJ}
	rm Output/boot/kernel 
	rm Output/boot/MyOS.iso 

run_and_clean: run clean
