/*
 * UARTTxRxHandle.c
 *
 *  Created on: Jan 21, 2023
 *      Author: MKS
 */
 #include"main.h"
#include "dhcp.h"
 
 extern TIM_HandleTypeDef htim7;
 extern TIM_HandleTypeDef htim6;
 uint8_t Flag1MS;
 uint8_t Flag1Second;
 uint8_t Flag100milliSeconds;
 uint8_t SimCount;
 uint8_t LocCount1S;
 uint8_t CountAT_Quench;
 uint8_t Status_Quench_Duration,Write_memory_Once;
 
 extern uint8_t start_process_control_timer;
 extern uint8_t stop_timer_count;
 extern uint8_t process_complete;
 extern uint8_t NewQuenchingReq;
 extern uint8_t status_to_server;
 extern uint8_t timeQuenchStart;
 
 uint16_t seq1_count_inc,seq2_count_inc;
 uint16_t seq1_remaining_time_total_min,seq2_remaining_time_total_min;
 uint8_t seq1_remaining_time_Hr,seq1_remaining_time_min,seq2_remaining_time_Hr,seq2_remaining_time_min;
 uint16_t Read_Quench_IP_Start,Read_Quench_IP_Stop,Quenching_Seconds_Cont;
 uint8_t Seccount1,Seccount2;

 GPIO_PinState InputStart_R,InputStop_R;

 extern uint16_t ProcessTotalMin1,ProcessTotalMin2;

 void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 {
 	if(htim == &htim7)
 	{
 		Flag1MS=1;
 	}
 	if(htim == &htim6)
	{
 		Flag100milliSeconds=1;
 		if(++LocCount1S >= 10)
		{
			LocCount1S=0;
			if(++SimCount >= 20)
			{
				SimCount=0;

			}
			Flag1Second =1;
			//DHCP_time_handler( );
			if(!stop_timer_count){
				if(start_process_control_timer ==1){
					if(++Seccount1 >= 59){
						Seccount1=0;
						if(++seq1_count_inc >= ProcessTotalMin1){
							seq1_count_inc = ProcessTotalMin1;
							process_complete=1;
						}
					}
				}
				else if(start_process_control_timer == 2){
					if(++Seccount2 >=59){
						Seccount2=0;
						if(++seq2_count_inc >= ProcessTotalMin2){
							seq2_count_inc = ProcessTotalMin2;
							process_complete=2;
						}
					}
				}
			}

			seq1_remaining_time_total_min = ProcessTotalMin1-seq1_count_inc;
			seq2_remaining_time_total_min = ProcessTotalMin2-seq2_count_inc;
			seq1_remaining_time_Hr  = (seq1_remaining_time_total_min/60);
			seq1_remaining_time_min = (seq1_remaining_time_total_min%60);
			seq2_remaining_time_Hr  = (seq2_remaining_time_total_min/60);
			seq2_remaining_time_min = (seq2_remaining_time_total_min%60);

		}

		if(++CountAT_Quench > 9)
		{
			CountAT_Quench=0;
			if(timeQuenchStart==1)
			{
				Quenching_Seconds_Cont=Quenching_Seconds_Cont+1;
			}
		}
	}

 }
