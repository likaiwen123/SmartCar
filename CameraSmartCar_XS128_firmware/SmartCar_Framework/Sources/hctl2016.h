#ifndef __HCTL2016_H__
#define __HCTL2016_H__

#define OEL_DDIRBIT		DDRE_DDRE2
#define OER_DDIRBIT		DDRE_DDRE3
#define	SEL_DDIRBIT		DDRH_DDRH1 
#define DATA_DDIR		  DDRA

#define OEL			      PORTE_PE2
#define OER			      PORTE_PE3
#define SEL			      PTIH_PTIH1
#define DATA		    	PORTA

#define LEFT 1
#define RIGHT 2

void HCTL2016_Initialization (void);
void HCTL2016_Delay (void);
int HCTL2016_RetrieveCounterValue (byte spec);

#endif