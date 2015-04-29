.section .text

.global isr0test
isr0test:
	pushl $0
	call isr0testc
	addl $4, %esp
	iret


