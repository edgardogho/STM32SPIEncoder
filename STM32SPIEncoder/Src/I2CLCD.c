#include "stm32f1xx_hal.h"
#include "I2CLCD.h"

void sendNibbleCmd(I2CLCDDisplay display, uint8_t lower_nibble);
void sendNibbleData(I2CLCDDisplay display, uint8_t lower_nibble);
void sendDataByte(I2CLCDDisplay display, uint8_t byte );

#define initArraySize 13
const uint8_t initArray[initArraySize] = { 0x03, 0x03, 0x03, 0x03 , 0x02, 0x02 , 0x08 , 0x00 , 0x0F , 0x00, 0x01 , 0x00, 0x06 };

void sendNibbleCmd(I2CLCDDisplay display, uint8_t lower_nibble){
	uint8_t shifted[2];
	shifted[0] = (lower_nibble <<4);
	shifted[1] = (lower_nibble <<4);
	if (display.Backlight){
		shifted[0] |= 0x08;
		shifted[1] |= 0x08;
	}
	shifted[0] |= 0x04;
	shifted[1] &= 0xFC;
	HAL_I2C_Master_Transmit(&display.Bus,display.Address,shifted,2,10);



}
void sendNibbleData(I2CLCDDisplay display, uint8_t lower_nibble){
	uint8_t shifted[2];
	shifted[0] = (lower_nibble <<4);
	shifted[1] = (lower_nibble <<4);
	if (display.Backlight){
		shifted[0] |= 0x08;
		shifted[1] |= 0x08;
	}
	shifted[0] |= 0x05;
	shifted[1] &= 0xFC;
	HAL_I2C_Master_Transmit(&display.Bus,display.Address,shifted,2,10);



}



void I2CLCD_WriteLine(I2CLCDDisplay display, uint8_t lineNumber,char *data){
	uint8_t offset=0;
	switch (lineNumber){
	case 0:
		offset = 0;
		break;
	case 1:
		offset = 40;
		break;
	case 2:
		offset = 20;
		break;
	case 3:
		offset = 84;
		break;
	}
	offset |=0x80;
	sendNibbleCmd(display,(offset>>4));
	sendNibbleCmd(display,offset);
	uint8_t *pointer = (uint8_t*)data;
	while (*pointer != '\0'){
		sendDataByte(display,*pointer);
		pointer++;
	}

}

void sendDataByte(I2CLCDDisplay display, uint8_t byte ){
	sendNibbleData(display,(byte>>4));
	sendNibbleData(display,(byte));
}

void I2CLCD_Init(I2CLCDDisplay display ){

		for(int i=0;i<initArraySize;i++){
			sendNibbleCmd(display,initArray[i]);
			HAL_Delay(5);
		}
		/*
		sendNibbleCmd(display,0x03);
		HAL_Delay(5);
		sendNibbleCmd(display,0x03);
		HAL_Delay(5);
		sendNibbleCmd(display,0x03);
		HAL_Delay(5);
		sendNibbleCmd(display,0x03);
		HAL_Delay(5);
		sendNibbleCmd(display,0x02);
		HAL_Delay(5);
		sendNibbleCmd(display,0x02);
		HAL_Delay(5);
		sendNibbleCmd(display,0x08);
		HAL_Delay(5);
		sendNibbleCmd(display,0x00);
		HAL_Delay(5);
		sendNibbleCmd(display,0x0F);
		HAL_Delay(5);
		sendNibbleCmd(display,0x00);
		HAL_Delay(5);
		sendNibbleCmd(display,0x01);
		HAL_Delay(5);
		sendNibbleCmd(display,0x00);
		HAL_Delay(5);
		sendNibbleCmd(display,0x06);
		HAL_Delay(5);
		*/

}
