//23LC1024 setup

#ifndef _23LC1024_
#define _23LC1024_

#include "main.h"


//SRAM opcodes
#define RDSR 5
#define WRSR 1
#define READ 3
#define WRITE 2

// SRAM modes
#define BYTE_MODE       0x00
#define PAGE_MODE       0x80
#define SEQUENTIAL_MODE 0x40

#define ss_Pin GPIO_Pin_4

    // Initialize and specify the SS pin	
    
    // Change SS pin (used in multi SRAM chip)
    int8_t changeSS(void);
    
    // Read a single byte from address
    int8_t readByte   (uint32_t address);
    
    // Write a single byte to address
    void writeByte  (uint32_t address, char data_byte);
    
    // Read several bytes starting at address and of length into a char buffer
    void readBuffer (uint32_t address, char *buffer, uint32_t length);
    
    // Write several bytes starting at address and of length from a char buffer
    void writeBuffer(uint32_t address, char *buffer, uint32_t length);
    
    // Write several bytes of value, starting at address and of length
    void fillBytes  (uint32_t address, int8_t value, uint32_t length);
		
		void setAddressMode(uint32_t address, uint8_t mode);
	
		int8_t Spi23LC1024Read8(uint32_t address);
		
		void Spi23LC1024Write8(uint32_t address, uint8_t data_byte);
  
    void writeBuffer_1byte(uint32_t address, char buffer);
		
		void readBuffer_1byte(uint32_t address, char buffer);
#endif
