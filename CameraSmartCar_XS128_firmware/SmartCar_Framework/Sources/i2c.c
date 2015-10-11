//#include "IO_Map.h"

//#include "misc.h"
#include "stdafx.h"
#include "i2c.h"
#include "ch452cmd.h"
#include <stdtypes.h>

void I2C_Initialization (void)
{
	SCL_DDIRBIT = 1; SDA_DDIRBIT = 1;
	SCL = 1; SDA = 1;
}

void I2C_Delay (void)
{
	int index;
	for (index = 0; index < 100; index++);
}

void I2C_Start (void)
{
	SDA = 1; I2C_Delay ();
	SCL = 1; I2C_Delay ();
	SDA = 0; I2C_Delay ();
	SCL = 0; I2C_Delay ();
}

void I2C_Stop (void)
{
	SDA = 0; I2C_Delay ();
	SCL = 0; I2C_Delay ();
	SCL = 1; I2C_Delay ();
	SDA = 1; I2C_Delay ();
}

void I2C_Nack (void)
{
	SDA = 1; SCL = 1; 
	I2C_Delay (); SCL = 0;
}

void I2C_TransmitByte (byte datum)
{
	int index = 8;	
	while (index-- > 0) {
		SDA = (datum & 0x80) ? 1: 0;
		datum <<= 1; I2C_Delay (); 
		SCL = 1; I2C_Delay ();
		SCL = 0; I2C_Delay ();
	}
}

byte I2C_ReadByte (void)
{	
	int index; 
	byte datum;

	SDA_DDIRBIT = 0;
	for (index = 0; index < 8; index++)
	{
		SCL = 1; I2C_Delay ();

		datum <<= 1;
		if (SDA) datum |= 0x01;
		else datum &= ~0x01;
	
		SCL = 0; I2C_Delay ();
	}
	SDA_DDIRBIT = 1;
	return (datum);
}

void CH452_Initialization (void)
{
  CH452_Write(CH452_RESET);
	CH452_Write(CH452_SYSON2);
	CH452_Write(CH452_BCD);  
}

void CH452_Write (word command)
{
	I2C_Start ();
	I2C_TransmitByte ((byte)(command >> 7) &
	    CH452_I2C_MASK | CH452_I2C_ADDR1); 
	I2C_Nack ();
	I2C_TransmitByte ((byte)(command));
	I2C_Nack ();
	I2C_Stop ();
}

byte CH452_Read (void)
{
	byte keycode;
	I2C_Start ();
	I2C_TransmitByte ((byte)(CH452_GET_KEY >> 7) & 
	    CH452_I2C_MASK | 0x01 | CH452_I2C_ADDR1); 
	I2C_Nack ();
	keycode = I2C_ReadByte ();
	I2C_Nack ();
	I2C_Stop ();
	return (keycode);
}

void DT2_Display (int numeral)
{
	if (numeral > 0) {
		if (numeral > 9999) {
			CH452_Write (CH452_DIG7 | 0x0f);
			CH452_Write (CH452_DIG6 | 0x0f);
			CH452_Write (CH452_DIG5 | 0x0f);
			CH452_Write (CH452_DIG4 | 0x0f); }
		else {
			CH452_Write (CH452_DIG4 | (byte)(numeral % 10)); numeral /= 10;
			CH452_Write (CH452_DIG5 | (byte)(numeral % 10)); numeral /= 10;
			CH452_Write (CH452_DIG6 | (byte)(numeral % 10)); numeral /= 10;
			CH452_Write (CH452_DIG7 | (byte)(numeral % 10)); } 
	}
	else {
		CH452_Write (CH452_DIG7 | CH452_BCD_MINUS); numeral = -numeral;
		if (numeral > 999) {
			CH452_Write (CH452_DIG6 | 0x0f);
			CH452_Write (CH452_DIG5 | 0x0f);
			CH452_Write (CH452_DIG4 | 0x0f); }
		else {
			CH452_Write (CH452_DIG4 | (byte)(numeral % 10)); numeral /= 10;
			CH452_Write (CH452_DIG5 | (byte)(numeral % 10)); numeral /= 10;
			CH452_Write (CH452_DIG6 | (byte)(numeral % 10)); }	   
	}
}

void DT1_Display (int numeral)
{
	if (numeral > 0) {
		if (numeral > 9999) {
			CH452_Write (CH452_DIG3 | 0x0f);
			CH452_Write (CH452_DIG2 | 0x0f);
			CH452_Write (CH452_DIG1 | 0x0f);
			CH452_Write (CH452_DIG0 | 0x0f); }
		else {
			CH452_Write (CH452_DIG0 | (byte)(numeral % 10)); numeral /= 10;
			CH452_Write (CH452_DIG1 | (byte)(numeral % 10)); numeral /= 10;
			CH452_Write (CH452_DIG2 | (byte)(numeral % 10)); numeral /= 10;
			CH452_Write (CH452_DIG3 | (byte)(numeral % 10)); }                     
	}
	else {
		CH452_Write (CH452_DIG3 | CH452_BCD_MINUS); numeral = -numeral;
		if (numeral > 999) {
			CH452_Write (CH452_DIG2 | 0x0f);
			CH452_Write (CH452_DIG1 | 0x0f);
			CH452_Write (CH452_DIG0 | 0x0f); }
		else {
			CH452_Write (CH452_DIG0 | (byte)(numeral % 10)); numeral /= 10;
			CH452_Write (CH452_DIG1 | (byte)(numeral % 10)); numeral /= 10;
			CH452_Write (CH452_DIG2 | (byte)(numeral % 10)); }	                        
	}
}

void GPDelay (word multiplier) {
  int index = 0;
  while (multiplier--) for (index = 0; index < 1000; index++);
}