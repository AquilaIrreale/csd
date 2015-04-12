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
LIBK_OBJS = memset.o

all: all-kernel all-libk

.PHONY: all all-kernel all-libk clean-all clean-kernel clean-libk

all-kernel: kernel.bin

all-libk: libk.a

kernel.bin: $(KERNEL_OBJS)

libk.a: $(LIBK_OBJS)
	cd $(LIBK_OBJP); $(AR) rvs $(PWD)/$(BINP)/libk.a $(LIBK_OBJS)

%.o: $(KERNEL_SRCP)/%.s
	$(AS) $< -o $(KERNEL_OBJP)/$@

%.o: $(KERNEL_SRCP)/%.c
	$(CC) $(KERNEL_CFLAGS) -c -o $(KERNEL_OBJP)/$@ $<

%.o: $(LIBK_SRCP)/%.c
	$(CC) $(LIBK_CFLAGS) -c -o $(LIBK_OBJP)/$@ $<

clean-all: clean-kernel clean-libk

clean-kernel:
	rm -v $(KERNEL_OBJP)/*

clean-libk:
	rm -v $(LIBK_OBJP)/*

git-push:
	git add -v .
	git commit
	git push -u origin master

