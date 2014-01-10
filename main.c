#include "stm32f4_system.h"
#include "main.h"
#include "stm32f4_delay.h"
#include "led.h"
#include "module_nrf24l01.h"
#include "module_rs232.h"
typedef struct nrf_package{

	int16_t roll, pitch, yaw;
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
	memcpy( &(package->roll), &buf[0], sizeof(int16_t) );
	memcpy( &(package->pitch), &buf[2], sizeof(int16_t) );
	memcpy( &(package->yaw), &buf[4], sizeof(int16_t) );
	memcpy( &(package->acc_x), &buf[6], sizeof(int16_t) );
	memcpy( &(package->acc_y), &buf[8], sizeof(int16_t) );
	memcpy( &(package->acc_z), &buf[10], sizeof(int16_t) );
	memcpy( &(package->gyro_x), &buf[12], sizeof(int16_t) );
	memcpy( &(package->gyro_y), &buf[14], sizeof(int16_t) );
	memcpy( &(package->gyro_z), &buf[16], sizeof(int16_t) );

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
			parse_nrf_package( &package, RxBuf);
			printf("{'Roll':'%f','Pitch':'%f','Yaw':'%f',",
                        package.roll/100.0,
                        package.pitch/100.0,
                        package.yaw/100.0);

                	printf("'Acc_x':'%d','Acc_y':'%d','Acc_z':'%d',",
                        package.acc_x, package.acc_y, package.acc_z);

                	printf("'Gyro_x':'%d','Gyro_y':'%d','Gyro_z':'%d'}\r\n",
                        package.gyro_x, package.gyro_y, package.gyro_z);
 
     	 	}
     	 	Delay_10ms(2);

     	 	

     	 }
     	
	

}
