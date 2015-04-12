AS = /home/simone/opt/cross/bin/i686-elf-as
LD = /home/simone/opt/cross/bin/i686-elf-ld
CC = /home/simone/opt/cross/bin/i686-elf-gcc
CFLAGS = -I.
SRCP = src
OBJP = bin/obj
EXEP = bin

all: kernel

#
#OBJ = kmain.o
#
#%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)
#

boot.o: $(SRCP)/boot.s
	$(AS) $< -o $(OBJP)/$@

gdt_loader.o: $(SRCP)/gdt_loader.s
	$(AS) $< -o $(OBJP)/$@

