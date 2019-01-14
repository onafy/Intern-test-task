#include <stdio.h>
#include <conio.h>
#include <stdint.h>
main()
{
	uint32_t num32 = 0xdeadbeef;
	uint8_t input[4];
	int a=0;
	uint8_t *ptinput;
	printf("Input :  0x%x\n", num32);
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
	

	
/*	
	uint8_t a = num32 >> 0;  // 0xef
	uint8_t b = num32 >> 8;  // 0xbe
	uint8_t c = num32 >> 16; // 0xad 
	uint8_t d = num32 >> 24; // 0xde 
	printf("ini char 0x%x\n", d);
	printf("ini char 0x%x\n", c);
	printf("ini char 0x%x\n", b);
	printf("ini char 0x%x\n", a); */
	

	getch();
}