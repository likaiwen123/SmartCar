#ifndef __IIC_H__
#define __IIC_H__

#define SCL_DDIRBIT	DDRT_DDRT0
#define SDA_DDIRBIT	DDRT_DDRT1
#define SCL		PTT_PTT0
#define SDA		PTT_PTT1

void I2C_Initialization (void);
void I2C_Delay (void);
void I2C_Start (void);
void I2C_Stop (void);
void I2C_Nack (void);
void I2C_TransmitByte (byte datum);
byte I2C_ReadByte (void);

void CH452_Initialization (void);
void CH452_Write (word command);
byte CH452_Read (void);
void DT1_Display (int numeral);
void DT2_Display (int numeral);
void GPDelay (word multiplier);
#endif




