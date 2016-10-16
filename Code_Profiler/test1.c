/*
 * test1.c
 *
 *  Created on: Oct 11, 2016
 *      Author: rohi2
 */
/*#include "MKL25Z4.h"
#include "math.h"
#include "stdio.h"
#include "time.h"

#define frequency 48
#define time 0.25
int q;
float TIMER=frequency*time; //mod value
int length=10,i=0;
uint8_t* source;
uint8_t* destination;
void  my_memmove(uint8_t *source,uint8_t *destination,uint32_t length);

void TPM2_IRQHandler() //TPM IRQ Handler
{
	__disable_irq();
    TPM2_BASE_PTR->SC |= TPM_SC_TOF_MASK; //Clear the timer flag
     //check for the number of times it enters the interrupt
    q++;
    __enable_irq();
}

void UART0_init(void)
 	{
 		SIM->SCGC4 |= 0x400;
 		SIM->SOPT2 |= 0x4000000;

 		UART0->C2 = 0;
 		UART0->BDH = 0x00;
 		UART0->BDL = 0x17;
 		UART0->C4 = 0x0F;
 		UART0->C1 = 0x00;
 		UART0->C2 = 0x08;

 		SIM->SCGC5 = 0x0200;
 		PORTA->PCR[2]= 0x0200;
 	}


void send_char(int c)
	{
		while(!(UART0->S1 & 0xC0))
		 {

		 }
		 UART0->D = c;

	}


void profiletimer()
{
			MCG_BASE_PTR->C1 = MCG_C1_IREFS_MASK | MCG_C1_IRCLKEN_MASK; //Selects the reference clock source for the FLL, Enables the internal reference clock for use as MCGIRCLK.
			MCG_BASE_PTR->C2 = MCG_C2_IRCS_MASK; //Select fast internal clock
			SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM2_MASK; //Enable TPM2 clock
			SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(3);//Selects the clock source for the TPM counter clock, 11 MCGIRCLK clock
			TPM2_BASE_PTR->SC = TPM_SC_CMOD(1) | TPM_SC_PS(0);//Selects the LPTPM counter clock modes. LPTPM counter increments on every LPTPM counter clock.
			TPM2_BASE_PTR->MOD = TIMER;//
			TPM2_BASE_PTR->SC |= TPM_SC_TOIE_MASK; //Timer interrupt flag
			NVIC->ISER[0] = 1 << 19; //Initialize timer interrupt
			MCG_SC &= 0xF1;// Divide factor for fast IRC clock is 1
			SIM_BASE_PTR->SCGC5|=SIM_SCGC5_PORTB_MASK; // Initialize the portB
			PORTB_BASE_PTR->PCR[18] =PORT_PCR_MUX(1);

			 //TPM Register initialization
				TPM2_SC &= 0xFFFFFFE7;//Disable clock mode CMOD
				TPM2_CNT &= 0xFFFF0000;//Initialize counter
				TPM2_SC &= 0xFFFFFFDF; //Select up counting mode
				TPM2_MOD = 0x0000000F;// Loading 9 since Period =(MOD+1) cycles in this case 10us
				TPM2_SC |= 	0x00000040;//Enable Interrupt

				TPM2_SC |= 0x0000000A;//Start Clock Timer and prescaler set to divide by 4 for 1 MHz
}

void stoptimer()
{
	TPM2_SC &= 0xFFFFFFE7;//Disable clock mode CMOD
}

int main(void)
{

	UART0_init();
	uint8_t ptr1[10]={};
	uint8_t ptr2[10]="1234";
	  int before=0,after=0,ans=0;
	  int before1=0,after1=0,ans1=0;
	  source = ptr2;
	  destination= ptr1;

				profiletimer();
				before=q;
    			 my_memmove(source,destination,length);
    			 stoptimer();
    		   	 after=q;
    		   	 ans=after-before;

  send_char(ans);

    /* Never leave main */
 /*   return 0;
}
*/


