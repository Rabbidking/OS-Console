#include "console.h"
#include "BootInfo.h"
#include "testsuite.c"

void sweet();

void clearBss(char* start, char* end) {
	//fill BSS with zeroes
	char* p = start;
	while(p != end)
	{
		*p=0;
		++p;
	}
}

void kmain(struct BootInfo* bis){

	clearBss(0, (char*) 16384);
	console_init(bis);
	clearScreen();
	
	sweet();
	asm("hlt");
}
