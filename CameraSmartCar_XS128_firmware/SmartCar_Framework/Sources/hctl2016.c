#include "stdafx.h"

#include "hctl2016.h"

void HCTL2016_Initialization (void)
{
	OEL_DDIRBIT = 1; OER_DDIRBIT = 1;
	SEL_DDIRBIT = 1; DATA_DDIR = 0; OEL = 1; OER = 1;
}

void HCTL2016_Delay (void)
{
	_asm (nop); _asm (nop); _asm (nop);
	_asm (nop); _asm (nop); _asm (nop);
}

int HCTL2016_RetrieveCounterValue (byte spec)
{
	word temporary;
	
	SEL = 0;
	if (spec == LEFT) OEL = 0; else OER = 0;

	HCTL2016_Delay (); temporary = (byte)(DATA) << 8; 
	SEL = 1; HCTL2016_Delay (); temporary |= (byte)(DATA);

	if (spec == LEFT) OEL = 1; else OER = 1;
	
	return temporary; 
}
