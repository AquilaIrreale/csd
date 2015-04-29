.section .text

.global load_idt
.type load_idt, @function
load_idt:
	pushl %ebp
	movl %esp, %ebp
	
	movl 8(%ebp), %eax

	cli

	lidt (%eax)

	sti

	movl %ebp, %esp
	popl %ebp
	ret
