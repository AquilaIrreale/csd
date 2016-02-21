.section .text

.global load_idt
.type load_idt, @function
load_idt:
	# Set up stack frame
	pushl %ebp
	movl %esp, %ebp
	
	# Retrieve idt descriptor pointer
	movl 8(%ebp), %eax
	
	# Push %eflags to get state
	# information about interrupts
	pushfl
	popl %edx
	andl $0x200, %edx	# 0x200 is IF

	# Disable interrupts
	cli

	# Load idt
	lidt (%eax)

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
