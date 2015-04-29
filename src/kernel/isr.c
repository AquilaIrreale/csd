#include <bsod.h>

void interrupt_routines_manager()
{

}

void isr0testc()
{
	bsod("#DE - DIVISION ERROR", "Unrecoverable error. Halting");
}


