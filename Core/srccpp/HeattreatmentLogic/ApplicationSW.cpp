
/*
 * LpdcLogic.cpp
 *
 *  Created on: 04-Feb-2023
 *      Author: MKS
 */
extern "C"{
#include "Struct_Input_output.h"
}
#include <HeattreatmentLogic/ApplicationSW.h>
#include "main.h"
GPIO_PinState GPIO_PinStateMac;
GPIO_PinState GPIO_PinStateRej;

uint8_t MAC_A_Prod_Input1_StartTimer;
uint16_t MAC_A_Prod_Input1_CountBase;
uint16_t MAC_Gen_Prod_Input1_Production,Production_Zeit;
uint16_t MAC_Gen_Rej_Input_Production,Rejection_Zeit;
uint16_t Manual_RejectionCount;
uint8_t CurrentShift_K1;
uint8_t IsCurrentShiftUpdated;
uint8_t updateSetData;
uint8_t NewQuenchingReq;

/*Data shared btw server & client*/
//Client -server
uint8_t status_to_server;
uint16_t ProcessId_Value;
//server - client
extern uint8_t skipIdTCP;
extern uint8_t statusTCP;
extern uint16_t temperatureHighTCP,temperatureLowTCP;
extern uint8_t durationHrS1,durationMinS1,durationHrS2,durationMinS2;
extern uint16_t seq1_count_inc,seq2_count_inc;


uint16_t Seq1temperature;
uint16_t Seq2temperature;
uint8_t Seq1durationHr,Seq1durationMin,Seq2durationHr,Seq2durationMin;
uint16_t temperature_reference;

uint16_t act_temperature_c1,act_temperature_c2,act_temperature_c3,act_temperature_c4;
uint8_t SEQMONITOR;

uint8_t start_process_control_timer;
uint8_t stop_timer_count;
uint8_t process_complete;
uint16_t seq1_duration_total,seq2_duration_total;

Heattreatment::Heattreatment() {
	// TODO Auto-generated constructor stub

}

Heattreatment::~Heattreatment() {
	// TODO Auto-generated destructor stub
}

void Heattreatment::run()
{
	stateMachineProcessControl();
}

void Heattreatment::stateMachineProcessControl(void){
	switch(SEQMONITOR)
	{
		case 10:
			if((SEQMONITOR==21)||(SEQMONITOR==100)||(SEQMONITOR==101)||(SEQMONITOR==103)||(SEQMONITOR==22)||(SEQMONITOR==23)
			||(SEQMONITOR==24)||(SEQMONITOR==25)||(SEQMONITOR==20))
			{
				SEQMONITOR=SEQMONITOR+0;
			}
			else
			{
				SEQMONITOR= 20;		 //Initialization
			}
		break;
		case 20:
			m_simEndProcess= HAL_GPIO_ReadPin(GPIOC,InputMachine1_Pin);
			if((m_simEndProcess ==GPIO_PIN_SET )||(skipIdTCP==0x01))
			{
				SEQMONITOR=21;
				status_to_server=1;
				seq1_count_inc  = 0;
				seq2_count_inc  = 0;
			}
			else if(m_simEndProcess ==GPIO_PIN_RESET)
			{
				status_to_server=30;
			}
		break;
		case 21:
				ProcessId_Value = ProcessId_Value+1;
				SEQMONITOR	= 100; //wait for server ack
				status_to_server= 1;
		break;
		case 100:	//Status_Http(from server)
				SEQMONITOR=101;
				status_to_server = 1;
		break;
		case 101:
				if(statusTCP == 11)
				{
					if(temperatureHighTCP !=0){
						Seq1temperature = temperatureHighTCP;
					}
					if(temperatureLowTCP !=0){
						Seq2temperature = temperatureLowTCP;
					}
					if(durationHrS1!= Seq1durationHr)
					{
						Seq1durationHr = durationHrS1;
						seq1_duration_total = (Seq1durationHr*60)+Seq1durationMin;
					}
					if(durationMinS1!= Seq1durationMin)
					{
						Seq1durationMin = durationMinS1;
						seq1_duration_total = (Seq1durationHr*60)+Seq1durationMin;
					}
					if(durationHrS2!= Seq2durationHr)
					{
						Seq2durationHr = durationHrS2;
						seq2_duration_total = (Seq2durationHr*60)+Seq2durationMin;
					}
					if(durationMinS2!= Seq2durationMin)
					{
						Seq2durationMin = durationMinS2;
						seq2_duration_total = (Seq2durationHr*60)+Seq2durationMin;
					}
					updateSetData		= 1;
					status_to_server 	= 20;
					SEQMONITOR			=103;
				}
				else{
					status_to_server=1;
				}
		break;
		case 103:
				if(statusTCP ==20){
					status_to_server=20;
					SEQMONITOR=22;
				}
				else{
					status_to_server=20;
					SEQMONITOR=103;
				}
		break;
		case 22:
				temperature_reference = Seq1temperature;
				m_temeperatureUpperBound = Seq1temperature+3;
				m_temperatureLowerBound  = Seq1temperature-3;
				if((act_temperature_c1 >= m_temperatureLowerBound)&&(act_temperature_c1 <= m_temeperatureUpperBound)
				&&(act_temperature_c2 >= m_temperatureLowerBound)&&(act_temperature_c2 <= m_temeperatureUpperBound)
				&&(act_temperature_c3 >= m_temperatureLowerBound)&&(act_temperature_c3 <= m_temeperatureUpperBound)
				&&(act_temperature_c4 >= m_temperatureLowerBound)&&(act_temperature_c4 <= m_temeperatureUpperBound))
				{
					SEQMONITOR=23;
				}
				else{
					SEQMONITOR=22;
				}
				status_to_server=20;
		break;
		case 23:
			temperature_reference = Seq1temperature;
			m_temeperatureUpperBound = Seq1temperature+5;
			m_temperatureLowerBound  = Seq1temperature-5;
			if(!start_process_control_timer)
			{
				start_process_control_timer=1;
			}
			if(((act_temperature_c1 >= m_temperatureLowerBound)&&(act_temperature_c1 <=m_temeperatureUpperBound))
			||((act_temperature_c2 >= m_temperatureLowerBound)&&(act_temperature_c2 <=m_temeperatureUpperBound))
			||((act_temperature_c3 >= m_temperatureLowerBound)&&(act_temperature_c3 <=m_temeperatureUpperBound))
			||((act_temperature_c4 >= m_temperatureLowerBound)&&(act_temperature_c4 <=m_temeperatureUpperBound)))
			{
				stop_timer_count = 0;
			}
			else
			{
				stop_timer_count = 1;
			}
			if(process_complete==1){
				process_complete = 0;
				start_process_control_timer=0;
				SEQMONITOR = 24;
				NewQuenchingReq=1;

			}
			else{
				SEQMONITOR = 23;
			}
			status_to_server=21;
		 break;
		case 24:
				temperature_reference = Seq2temperature;
				m_temeperatureUpperBound = Seq2temperature+3;
				m_temperatureLowerBound  = Seq2temperature-3;
				if((act_temperature_c1 >= m_temperatureLowerBound)&&(act_temperature_c1 <= m_temeperatureUpperBound)
				&&(act_temperature_c2 >= m_temperatureLowerBound)&&(act_temperature_c2 <= m_temeperatureUpperBound)
				&&(act_temperature_c3 >= m_temperatureLowerBound)&&(act_temperature_c3 <= m_temeperatureUpperBound)
				&&(act_temperature_c4 >= m_temperatureLowerBound)&&(act_temperature_c4 <= m_temeperatureUpperBound))
				{
					SEQMONITOR=25;
				}
				else{
					SEQMONITOR=24;
				}
				status_to_server=22;
		break;
		case 25:
				temperature_reference = Seq2temperature;
				m_temeperatureUpperBound = Seq2temperature+5;
				m_temperatureLowerBound  = Seq2temperature-5;
				if(!start_process_control_timer)
				{
					start_process_control_timer=2;
				}
				if(((act_temperature_c1 >= m_temperatureLowerBound)&&(act_temperature_c1 <=m_temeperatureUpperBound))
				||((act_temperature_c2 >= m_temperatureLowerBound)&&(act_temperature_c2 <=m_temeperatureUpperBound))
				||((act_temperature_c3 >= m_temperatureLowerBound)&&(act_temperature_c3 <=m_temeperatureUpperBound))
				||((act_temperature_c4 >= m_temperatureLowerBound)&&(act_temperature_c4 <=m_temeperatureUpperBound)))
				{
					stop_timer_count = 0;
				}
				else
				{
					stop_timer_count = 1;
				}
				if(process_complete==2){
					process_complete = 0;
					start_process_control_timer=0;
					SEQMONITOR = 24;
				}
				else{
					SEQMONITOR = 25;
				}
				status_to_server=23;
			 break;
		case 26:
			status_to_server=30;
			SEQMONITOR   = 20;
			temperature_reference = 32;
		break;
		default:
			SEQMONITOR   = 10;
		break;
	}
	if((skipIdTCP==10)&&(SEQMONITOR!=26))
	{
		SEQMONITOR = 26;
	}
}
