AS = i386-elf-as
LD = i386-elf-ld
CC = i386-elf-gcc
AR = i386-elf-ar
KERNEL_CFLAGS = -gdwarf-2 -std=gnu99 -ffreestanding -nostdlib -Wall -Wextra -Tlinker.ld -Isrc/kernel/include -Isrc/libk/include -Lbin
LIBK_CFLAGS = -gdwarf-2 -std=gnu99 -ffreestanding -Wall -Wextra -Isrc/libk/include
KERNEL_SRCP = src/kernel
LIBK_SRCP = src/libk
KERNEL_OBJP = bin/obj/kernel
LIBK_OBJP = bin/obj/libk
BINP = bin
KERNEL_OBJS = boot.o kmain.o gdt_asm.o gdt.o idt_asm.o idt.o isr_asm.o isr.o vga.o bsod.o
LIBK_OBJS = memset.o memcpy.o memmove.o memcmp.o memchr.o strcpy.o strncpy.o strcat.o strncat.o strlen.o strcspn.o
LIBS = -lgcc -lk

all: all-kernel all-libk

.PHONY: all all-kernel all-libk clean-all clean-kernel clean-libk

all-kernel: kernel.bin

all-libk: libk.a

kernel.bin: $(KERNEL_OBJS) libk.a
	$(CC) $(KERNEL_CFLAGS) -o $(BINP)/kernel.bin $(KERNEL_OBJP)/*.o $(LIBS)

libk.a: $(LIBK_OBJS)
	cd $(LIBK_OBJP); $(AR) rvs $(PWD)/$(BINP)/libk.a $(LIBK_OBJS)

%.o: $(KERNEL_SRCP)/%.s
	$(AS) -g $< -o $(KERNEL_OBJP)/$@

%.o: $(KERNEL_SRCP)/%.c
	$(CC) $(KERNEL_CFLAGS) -c -o $(KERNEL_OBJP)/$@ $<

%.o: $(LIBK_SRCP)/%.c
	$(CC) $(LIBK_CFLAGS) -c -o $(LIBK_OBJP)/$@ $<

csd.iso: kernel.bin
	cp -f $(BINP)/kernel.bin iso/boot/
	grub-mkrescue -o csd.iso iso/

disassembly: kernel.bin
	objdump -d $(BINP)/kernel.bin > disassembly

clean-all: clean-kernel clean-libk

clean-kernel:
	rm -v $(KERNEL_OBJP)/*

clean-libk:
	rm -v $(LIBK_OBJP)/*

