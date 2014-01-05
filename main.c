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
	uint8_t RxBuf[5][5] = {{0}};

	System_Init();
	printf("Rx mode test...\n\r");

	/* nRF Check */
    	while(Sta == ERROR)
    		Sta = nRF_Check();
    	
	printf("Start ...\n\r");
    	printf("============");
    	
	/*Convert to Rx */
	nRF_RX_Mode();
	
	/*Receive the data from remote quadcopter */
	while(1){
		Sta = nRF_Rx_Data(RxBuf[0]);
		printf("status = ");
		if(Sta == RX_DR) {
      	 //	 	Transport_Recv(RxBuf[0]);
      	 	 	printf("receive ! ");
     	 	}
     	 }
     	
	

}
