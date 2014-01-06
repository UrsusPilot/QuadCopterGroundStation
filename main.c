#include "stm32f4_system.h"
#include "main.h"
#include "stm32f4_delay.h"
#include "led.h"
#include "module_nrf24l01.h"
#include "module_rs232.h"


void System_Init(void)
{
	SystemInit();
	LED_Config();
	 //KEY_Config();
	 RS232_Config();
	 nRF24L01_Config();

	 Delay_10ms(2);
}


int main(void)
{
	uint8_t Sta = ERROR;
	uint8_t RxBuf[32]= {0};

	System_Init();
	printf("Rx mode test...\n\r");

	/* nRF Check */
    	while(Sta == ERROR)
    		Sta = nRF_Check();
    	
    	nRF_RX_Mode();
	printf("Start ...\n\r");
    	printf("============");
    
	while(1){


		Sta = nRF_Rx_Data( (uint8_t*)RxBuf);

		printf("status = ");
		if(Sta == RX_DR) {

      	 	 	printf("Get RX_DR");
     
      	 	 	if (RxBuf[0] != 0)
      	 	 		printf("%s", RxBuf);
 
     	 	}

     	 	Delay_10ms(20);

     	 }
     	
	

}
