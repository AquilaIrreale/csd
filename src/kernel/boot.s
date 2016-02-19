# Multiboot header
.set ALIGN,	1<<0
.set MEMINFO,	1<<1
.set FLAGS,	ALIGN | MEMINFO
.set MAGIC,	0x1BADB002
.set CHECKSUM,	-(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Temporary stack
.section .tempstack, "aw", @nobits
stack_bottom:
.skip 16384
stack_top:

# Start of kernel code
.section .text
.global _start
.type _start, @function
_start:
	# Set up temporary stack
	movl $stack_top, %esp

	# Disable interrupts
	cli

	# Start kernel main
	call kmain

	# Dead code
	# Should never get to be executed
	# Still it's here for safety reasons
	cli
	hlt
.Lhang:
	nop
	jmp .Lhang
