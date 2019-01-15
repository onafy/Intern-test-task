#include <stdio.h>
#include <stdint.h>
#include "pointer.h"

uint8_t getPointerr(uint32_t num32)
{
	uint8_t input[4];
	uint8_t *ptinput;
	printf("\n\nInput :  0x%x\n", num32);
	int a=0;
	for(int i = 24; i >= 0; i--)
	{
		if(i%8==0)
		{
			input[a] = num32 >> i;
	 		printf("bg %d  :  0x%x\n", a, input[a]);
	 		a=a+1;
		}
	 	
	}
	ptinput = input;

	
	  for(int j = 0; j< sizeof(input); j++)
	{
	
	 	printf("bagian = 0x%x = %d\n", *ptinput, *ptinput);
	 	printf("alamat = %x\n\n", ptinput);
	 	ptinput++;
	}

	return *ptinput;
}
