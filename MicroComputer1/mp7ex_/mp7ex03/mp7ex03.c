#include <3048fone.h>
#include "h8_3048fone.h"

main()
{
	int i,j;
	long int ptr=0;
	initSCI1(); /*SCI-ch1‚Ì‰Šú‰»*/
	
	SCI1_printf("memory dump 0x00000-0x001ff\n");
	SCI1_printf("      +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F\n");
	for(i=0;i<32;i++) {
		SCI1_printf("%05lx",ptr);
		for(j=0;j<16;j++) {
			SCI1_printf(" %02x",*(unsigned char *)ptr);
			ptr++;
		}
		SCI1_printf("\n");
	}
}
