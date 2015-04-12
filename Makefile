AS = /home/simone/opt/cross/bin/i686-elf-as
LD = /home/simone/opt/cross/bin/i686-elf-ld
CC = /home/simone/opt/cross/bin/i686-elf-gcc
AR = /home/simone/opt/cross/bin/i686-elf-ar
KERNEL_CFLAGS = -std=gnu99 -ffreestanding -Wall -Wextra -Isrc/kernel/include -Isrc/libk/include
LIBK_CFLAGS = -std=gnu99 -ffreestanding -Wall -Wextra -Isrc/libk/include
KERNEL_SRCP = src/kernel
LIBK_SRCP = src/libk
KERNEL_OBJP = bin/obj/kernel
LIBK_OBJP = bin/obj/libk
BINP = bin
KERNEL_OBJS = boot.o kmain.o gdt_loader.o gdt.o 
LIBK_OBJS = string.o

all: kernel libk

.PHONY: kernel libk

kernel: $(KERNEL_OBJS)

libk: $(LIBK_OBJS)
	cd $(LIBK_OBJP)
	$(AR) rvs $(PWD)/$(BINP)/libk.a $(LIBK_OBJS)

%.o: $(KERNEL_SRCP)/%.s
	$(AS) $< -o $(KERNEL_OBJP)/$@

%.o: $(KERNEL_SRCP)/%.c
	$(CC) $(KERNEL_CFLAGS) -c -o $(KERNEL_OBJP)/$@ $<

%.o: $(LIBK_SRCP)/%.c
	$(CC) $(LIBK_CFLAGS) -c -o $(LIBK_OBJP)/$@ $<


