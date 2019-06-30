# STM32SPIEncoder
STM32F103 reading linear scales with slave SPI and I2C alphanumeric display

This is a fairly simple project that uses a BluePill (STM32F103) board to read 2 linear scales (using the TIM2 and TIM3 encoder interface).
The values read are displayed on a 16x2 alphanumeric display and can be also accessed using SPI.
The EXTi4 is used to latch the encoder values for SPI TX.
Also 2 buttons will reset the encoder values.
The linear scales are 200mm in length so using 16 bits per encoder.
I2C for the display is used on blocking mode but most of the rest is using interrupts so main loop can wait for the I2C display.
