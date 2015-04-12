.section .text

# Function: load_gdt
# Takes a gdt descriptor structure pointer
# as parameter and loads it with lgdt.
# Then loads the kernel code/data selectors
# whose are assumed to be entries the second
# and the third entries of the gdt
.global load_gdt
.type load_gdt, @function
load_gdt:
	# Set up stack frame
	pushl %ebp
	movl %esp, %ebp
	
	# Retrieve gdt descriptor pointer
	movl 8(%ebp), %eax

	# Push %eflags to get state
	# information about interrupts
	pushfl
	popl %edx
	andl $0x200, %edx	# 0x200 is interrupts flag

	# Disable interrupts
	cli

	# Load gdt
	lgdt (%eax)

	# Load kernel selectors
	mov 0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	ljmp $0x08, $.Lload_cs
	.Lload_cs:

	# If interrupts were enabled
	# re-enable them
	testl %edx, %edx
	jz .Lskip_sti
	sti
	.Lskip_sti:

	# Return
	movl %ebp, %esp
	popl %ebp
	ret
