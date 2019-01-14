#include <stdio.h>
#include <conio.h>
#include <stdint.h>

uint8_t getPointer(uint32_t num32);
typedef uint8_t (*func)(uint32_t);

main()
{
	uint32_t num32;
	printf("Input int 32 : ");
	scanf("%x", &num32);
	printf("Input :  0x%x\n", num32);
	
	func gp = getPointer;
	gp(num32);

	getch();
}


uint8_t getPointer(uint32_t num32)
{
	uint8_t input[4];
	int a=0;
	uint8_t *ptinput;
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
}
