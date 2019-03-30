#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#include "setup.h"
#include "23LC1024.h"

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
		
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART2, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

void dumpsRam(uint32_t addr, uint32_t length);
void dumpsRam2(uint32_t addr, uint32_t length);

int main(void)
{
	const uint32_t ramSize = 0x1FFFF;           // 128K x 8 bit
	char *buffer = "ABCDEF";
	char *buffer2;
	Init_USART();
	Init_GPIO();
	Init_SPI1_Master();
	
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	
	printf("Ram Tests Begin.\n");
	
	/*writeBuffer_1byte(0,test);
	readBuffer_1byte(0,testnhan);
	printf("%u",testnhan);*/
	
	
	/*printf("\r\nFill Memory with 0xFF.");
	fillBytes(0,0xFF,ramSize);
	dumpsRam(0, 100);
  dumpsRam(ramSize - 100, 100);
	
	printf("\r\nFill Memory with 0xAA.");
  fillBytes(0, 0xAA, ramSize);
  dumpsRam(0, 100);
  dumpsRam(ramSize - 100, 100);
	printf("\n");
	
	printf("\r\nFill Memory with Buffer.");
  for (uint32_t x = 0; x < ramSize - (sizeof(buffer) - 1); x += sizeof(buffer) - 1) {
    writeBuffer(x, buffer, sizeof(buffer) - 1);
  }
  dumpsRam(0, 100);
  dumpsRam(ramSize - 100, 100);
	printf("\n");

  printf("\r\nRead Buffer.");
  readBuffer(0, buffer2, sizeof(buffer2) - 1);
  printf("%u",(char)buffer2);
  readBuffer(5, buffer2, sizeof(buffer2) - 1);
	printf("%u",(char)buffer2);
	printf("\n");
	
	printf("\r\nWrite byte.");
  for (uint32_t x = 0; x <= ramSize; x++){
    writeByte(x, (unsigned char)x / 10);
  }
  dumpsRam(0,100);
  dumpsRam(ramSize - 100, 100);*/
	
	printf("\r\nFill Memory with Buffer.");
	for(uint8_t i = 0; i < sizeof(buffer); i++)
    writeBuffer(i, &buffer[i], sizeof(buffer));
  //dumpsRam(0, sizeof(buffer));
  //dumpsRam(ramSize - 100, 100);
	printf("\n");

  printf("\r\nRead Buffer.\n");
  //readBuffer(0, buffer2, sizeof(buffer2));
	for(uint8_t i=0; i<sizeof(buffer); i++)
		{
			readBuffer(i,(char*)&buffer2[i],sizeof(buffer2));
			printf(" %x",(char)&buffer2[i]);
		}
	
	printf("\n");
  printf("\r\nRam Tests Finished.\n");
	while(1)
	{			
	}
}

void dumpsRam(uint32_t addr, uint32_t length)
{
  // block to 10
  addr = addr / 10 * 10;
  length = (length + 9) / 10 * 10;

  unsigned char b = readByte(addr);
  for (int i = 0; i < length; i++)
  {
    if (addr % 10 == 0)
    {
      printf("\n");
      printf("%u",addr);
      printf(":\t");
    }
    printf(" %x",b);
    b = readByte(++addr);
    printf("\t");
  }
  printf("");
}

void dumpsRam2(uint32_t addr, uint32_t length)
{
  // block to 10
  //addr = addr / 10 * 10;
  //length = (length + 9) / 10 * 10;

  char b = readByte(addr);
  for (int i = 0; i < length; i++)
  {
    if (addr % 10 == 0)
    {
      printf("/n");
      printf("%d",addr);
			printf(":\t");
    }
    printf(" %x",b);
    //b = readByte(++addr);
		printf("\t");
  }
  printf("");
}




