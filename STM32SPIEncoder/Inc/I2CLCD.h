
#ifndef I2CLCD_H_
#define I2CLCD_H_
#include "stm32f1xx_hal.h"

typedef struct I2CLCDDisplay {
	uint8_t Address;
	uint8_t Backlight;
	I2C_HandleTypeDef Bus;
}I2CLCDDisplay;

void I2CLCD_WriteLine(I2CLCDDisplay display, uint8_t lineNumber,char *data);


void I2CLCD_Init(I2CLCDDisplay );


#endif
