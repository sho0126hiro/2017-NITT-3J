#include <3048fone.h>
#include "h8_3048fone.h"

main()
{
	int i,j;
	long int start;
	initSCI1(); /*SCI-ch1‚Ì‰Šú‰»*/
	while(1){
		start =(unsigned long int)SCI1_getInt4("start address (0xnnnnnn) =");
		SCI1_printf("memory dump 0x%05lx-0x%05lx\n",start,start+0xff);
		SCI1_printf("      +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F\n");
		for(i=0;i<16;i++) {
			SCI1_printf("%05lx",start);
			for(j=0;j<16;j++) {
				SCI1_printf(" %02x",*(unsigned char *)start);
				start++;
			}
			SCI1_printf("\n");
		}
	}
}
