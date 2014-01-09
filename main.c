#include "stm32f4_system.h"
#include "main.h"
#include "stm32f4_delay.h"
#include "led.h"
#include "module_nrf24l01.h"
#include "module_rs232.h"
typedef struct nrf_package{

	float roll, pitch, yaw;
	int16_t acc_x, acc_y, acc_z;
	int16_t gyro_x, gyro_y, gyro_z;

} nrf_package;

void System_Init(void)
{
	SystemInit();
	LED_Config();
	 //KEY_Config();
	 RS232_Config();
	 nRF24L01_Config();

	 Delay_10ms(2);
}

void parse_nrf_package( nrf_package* package, uint8_t* buf)
{
	memcpy( &(package->roll), &buf[0], sizeof(uint16_t) );
	memcpy( &(package->pitch), &buf[2], sizeof(uint16_t) );
	memcpy( &(package->yaw), &buf[4], sizeof(uint16_t) );
	memcpy( &(package->acc_x), &buf[6], sizeof(uint16_t) );
	memcpy( &(package->acc_y), &buf[8], sizeof(uint16_t) );
	memcpy( &(package->acc_z), &buf[10], sizeof(uint16_t) );
	memcpy( &(package->gyro_x), &buf[12], sizeof(uint16_t) );
	memcpy( &(package->gyro_y), &buf[14], sizeof(uint16_t) );
	memcpy( &(package->gyro_z), &buf[16], sizeof(uint16_t) );
	package->roll = package->roll/100;
	package->pitch = package->pitch/100;
	package->yaw = package->yaw/100;

}
int main(void)
{
	uint8_t Sta = ERROR;
	uint8_t RxBuf[32]= {0};
	nrf_package package;
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

		if(Sta == RX_DR) {
			int i = 0;
			for ( i = 0; i<32 ; i++ ){
				if ( RxBuf[i] != 0){
					USART_SendData(USART3, (uint16_t)RxBuf[i]);
					while (USART_GetFlagStatus(USART3,
					 USART_FLAG_TC) == RESET);
				}
			}
 
     	 	}

     	 	

     	 }
     	
	

}
