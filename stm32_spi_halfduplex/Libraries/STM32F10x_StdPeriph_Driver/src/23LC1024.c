#include "23LC1024.h"


int8_t changeSS(void){
  uint16_t temp = ss_Pin;                  // Get current SS pin
  GPIO_SetBits(GPIOA,ss_Pin);           // Set SS pin high
  return temp;                          // Return previous SS pin
}

int8_t readByte(uint32_t address) {
  char data_byte;
	char *temp = &data_byte;
  readBuffer(address, temp, 1);
  return data_byte;
}

void writeByte(uint32_t address, char data_byte) {
	char *temp = &data_byte;
  writeBuffer(address, temp, 1);
}

void readBuffer(uint32_t address, char *buffer, uint32_t length) {
  uint32_t i;
	GPIO_ResetBits(GPIOA,ss_Pin);
  setAddressMode(address, READ);
  for (i = 0; i < length; i++) 
	{
		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}
		SPI_I2S_SendData(SPI1, 0x00);
		buffer[i] = SPI1->DR;
	}
  GPIO_SetBits(GPIOA,ss_Pin);
}

void writeBuffer(uint32_t address, char *buffer, uint32_t length) {
  uint32_t i;
	GPIO_ResetBits(GPIOA,ss_Pin);
  setAddressMode(address, WRITE);
  for (i = 0; i < length; i++)
	{
		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}
		SPI_I2S_SendData(SPI1,buffer[i]);
	}
  GPIO_SetBits(GPIOA,ss_Pin);
}

void fillBytes(uint32_t address, int8_t value, uint32_t length) {
  uint32_t i;
	GPIO_ResetBits(GPIOA,ss_Pin);
  setAddressMode(address, WRITE);
  for (i = 0; i < length; i++) 
	{
		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}
		SPI_I2S_SendData(SPI1,value);
	}
  GPIO_SetBits(GPIOA,ss_Pin);
}

void setAddressMode(uint32_t address, uint8_t mode) {
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}
  SPI_I2S_SendData(SPI1,mode);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}
  SPI_I2S_SendData(SPI1,(uint8_t)(address >> 16));
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}
  SPI_I2S_SendData(SPI1,(uint8_t)(address >> 8));
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}
  SPI_I2S_SendData(SPI1,(uint8_t)address);
}

int8_t Spi23LC1024Read8(uint32_t address)
{
    uint8_t read_byte;
    GPIO_ResetBits(GPIOA,ss_Pin); //ch?n ic này
    SPI_I2S_SendData(SPI1,READ);
    SPI_I2S_SendData(SPI1,(uint8_t)(address >> 16) & 0xff);
    SPI_I2S_SendData(SPI1,(uint8_t)(address >> 8) & 0xff);
    SPI_I2S_SendData(SPI1,(uint8_t)address);
		SPI_I2S_SendData(SPI1,0x00);
		read_byte = SPI1->DR;
    GPIO_SetBits(GPIOA,ss_Pin);
    return read_byte;
}

void Spi23LC1024Write8(uint32_t address, uint8_t data_byte)
{
    GPIO_ResetBits(GPIOA,ss_Pin); // ch?n ic này
    SPI_I2S_SendData(SPI1,WRITE);
    SPI_I2S_SendData(SPI1,(uint8_t)(address >> 16) & 0xff);
    SPI_I2S_SendData(SPI1,(uint8_t)(address >> 8) & 0xff);
    SPI_I2S_SendData(SPI1,(uint8_t)address);
    SPI_I2S_SendData(SPI1,data_byte);
    GPIO_SetBits(GPIOA,ss_Pin);
}
