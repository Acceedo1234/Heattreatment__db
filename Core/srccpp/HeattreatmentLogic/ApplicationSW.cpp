
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

extern uint16_t Temperature_High_Http,R_Temperature_Low_Http,Temperature_Low_Http;
extern uint8_t Sequence1_hour_http,Sequence1_minute_http,R_Sequence1_hour_http,R_Sequence1_minute_http;
extern uint8_t R_Sequence2_hour_http,R_Sequence2_minute_http,Sequence2_hour_http,Sequence2_minute_http;
extern uint8_t TypeofProcess,No_of_temp_Controller,Type_of_temp_Controller,Type_of_powermeter;
extern uint8_t Status_Http,IDGen_Skip_Http;
extern uint16_t R_Temperature_High_Http;


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
uint8_t H_Timer01HrValue,H_Timer01MinValue,H_Timer02HrValue,H_Timer02MinValue;
uint16_t ProcessTotalMin1,ProcessTotalMin2;
uint16_t Rise_Sequence1_temp,Rise_Sequence2_temp;
uint8_t Rise_Sequence1_Hour,Rise_Sequence1_Minute,Rise_Sequence2_Hour,Rise_Sequence2_Minute;
uint16_t Temp_Rising_Reference;
uint8_t TimeReference_Hr,TimeReference_Min,Time_Rising_Ref_Hr,Time_Rising_Ref_Min;


Heattreatment::Heattreatment() {
	// TODO Auto-generated constructor stub

}

Heattreatment::~Heattreatment() {
	// TODO Auto-generated destructor stub
}

void Heattreatment::run()
{
	stateMachineProcessControl();
	specialHandler();
}

void Heattreatment::sim()
{
	if((SEQMONITOR ==22)||(SEQMONITOR==23))
		{
			if(Data1_RxData  >=  Seq1temperature)
			{

			}
			else
			{
			   Data1_RxData=Data1_RxData+1;
			}
		}
		else if((SEQMONITOR ==24)||(SEQMONITOR==25))
		{
			if(Data1_RxData  >  Seq2temperature)
			{
			   Data1_RxData=Data1_RxData-1;
			}
			else if(Data1_RxData  <  Seq2temperature)
			{
			   Data1_RxData=Data1_RxData+1;
			}
			else
			{
			   Data1_RxData=  Seq2temperature*1;
			}
		}
		else
		{
		   Data1_RxData=32;
		}
		act_temperature_c1 = Data1_RxData;
		act_temperature_c2 = Data1_RxData;
		act_temperature_c3 = Data1_RxData;
		act_temperature_c4 = Data1_RxData;
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
			//m_simEndProcess= HAL_GPIO_ReadPin(GPIOC,InputMachine1_Pin);
			if((m_simEndProcess ==GPIO_PIN_SET )||(IDGen_Skip_Http==0x01))
			{
				SEQMONITOR=21;
				status_to_server=1;
				seq1_count_inc  = 0;
				seq2_count_inc  = 0;
			}
			else if((m_simEndProcess ==GPIO_PIN_RESET)||(IDGen_Skip_Http==0x00))
			{
				status_to_server=30;
			}
		break;
		case 21:
				ProcessId_Value = ProcessId_Value+1;
				seq1_count_inc  = 0;
				seq2_count_inc  = 0;
				SEQMONITOR	= 100; //wait for server ack
				status_to_server= 1;
		break;
		case 100:	//Status_Http(from server)
				SEQMONITOR=101;
				status_to_server = 1;
		break;
		case 101:
				if(Status_Http == 11)
				{
					if(Temperature_High_Http!=0)
					{
						if(Seq1temperature!=Temperature_High_Http)
						{
							Seq1temperature= Temperature_High_Http;
						}
					}
					if(Temperature_Low_Http!=0)
					{
						if(Seq2temperature!=Temperature_Low_Http)
						{
							Seq2temperature= Temperature_Low_Http;
						}
					}
					if(H_Timer01HrValue!=Sequence1_hour_http)
					{
						H_Timer01HrValue= Sequence1_hour_http;
						ProcessTotalMin1 	=  (H_Timer01HrValue*60)+  H_Timer01MinValue;
					}
					if(H_Timer01MinValue!=Sequence1_minute_http)
					{
						H_Timer01MinValue= Sequence1_minute_http;
						ProcessTotalMin1 	=  (H_Timer01HrValue*60)+  H_Timer01MinValue;
					}
					if(H_Timer02HrValue!=Sequence2_hour_http)
					{
						H_Timer02HrValue= Sequence2_hour_http;
					}
					if(H_Timer02MinValue!=Sequence2_minute_http)
					{
						H_Timer02MinValue= Sequence2_minute_http;
						ProcessTotalMin2   =  (H_Timer02HrValue*60)+  H_Timer02MinValue;
					}
					if(R_Temperature_High_Http!=   Rise_Sequence1_temp)
					{
						Rise_Sequence1_temp = R_Temperature_High_Http;
					}
					if(R_Temperature_Low_Http!=   Rise_Sequence2_temp)
					{
						Rise_Sequence2_temp = R_Temperature_Low_Http;
					}
					if(R_Sequence1_hour_http!=   Rise_Sequence1_Hour)
					{
						Rise_Sequence1_Hour = R_Sequence1_hour_http;
					}
					if(R_Sequence1_minute_http!=   Rise_Sequence1_Minute)
					{
						Rise_Sequence1_Minute = R_Sequence1_minute_http;
					}

					if(R_Sequence2_hour_http!=   Rise_Sequence2_Hour)
					{
						Rise_Sequence2_Hour = R_Sequence2_hour_http;
					}

					if(R_Sequence2_minute_http!=   Rise_Sequence2_Minute)
					{
						Rise_Sequence2_Minute = R_Sequence2_minute_http;
					}
					status_to_server = 20;
					SEQMONITOR=103;
					updateSetData=1;
				}
				else
				{
					status_to_server=1;
				}
		break;
		case 103:
				if(Status_Http ==20){
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
				Temp_Rising_Reference   = Rise_Sequence1_temp;
				TimeReference_Hr		= (unsigned char)H_Timer01HrValue;
				TimeReference_Min		= (unsigned char)H_Timer01MinValue;
				Time_Rising_Ref_Hr		= (unsigned char)Rise_Sequence1_Hour;
				Time_Rising_Ref_Min		= (unsigned char)Rise_Sequence1_Minute;
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
			Temp_Rising_Reference   = Rise_Sequence1_temp;
			TimeReference_Hr		= (unsigned char)H_Timer01HrValue;
			TimeReference_Min		= (unsigned char)H_Timer01MinValue;
			Time_Rising_Ref_Hr		= (unsigned char)Rise_Sequence1_Hour;
			Time_Rising_Ref_Min		= (unsigned char)Rise_Sequence1_Minute;
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
				Temp_Rising_Reference   = Rise_Sequence2_temp;
				TimeReference_Hr		= (unsigned char)H_Timer02HrValue;
				TimeReference_Min		= (unsigned char)H_Timer02MinValue;
				Time_Rising_Ref_Hr		= (unsigned char)Rise_Sequence2_Hour;
				Time_Rising_Ref_Min		= (unsigned char)Rise_Sequence2_Minute;
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
				Temp_Rising_Reference   = Rise_Sequence2_temp;
				TimeReference_Hr		= (unsigned char)H_Timer02HrValue;
				TimeReference_Min		= (unsigned char)H_Timer02MinValue;
				Time_Rising_Ref_Hr		= (unsigned char)Rise_Sequence2_Hour;
				Time_Rising_Ref_Min		= (unsigned char)Rise_Sequence2_Minute;
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
					SEQMONITOR = 26;
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
	if((IDGen_Skip_Http==10)&&(SEQMONITOR!=26))
	{
		SEQMONITOR = 26;
	}
}

void Heattreatment::specialHandler(void)
{
 if(Status_Http!=11){return;}
	if(Status_Http==11)
	{
		if(Temperature_High_Http!=0)
		{
			if(Seq1temperature!=Temperature_High_Http)
			{
				Seq1temperature= Temperature_High_Http;
				updateSetData=1;
			}
		}
		if(Temperature_Low_Http!=0)
		{
			if(Seq2temperature!=Temperature_Low_Http)
			{
				Seq2temperature= Temperature_Low_Http;
				updateSetData=1;
			}
		}
		if(H_Timer01HrValue!=Sequence1_hour_http)
		{
			H_Timer01HrValue= Sequence1_hour_http;
			ProcessTotalMin1 	=  (H_Timer01HrValue*60)+  H_Timer01MinValue;
			updateSetData=1;
		}
		if(H_Timer01MinValue!=Sequence1_minute_http)
		{
			H_Timer01MinValue= Sequence1_minute_http;
			ProcessTotalMin1 	=  (H_Timer01HrValue*60)+  H_Timer01MinValue;
			updateSetData=1;
		}
		if(H_Timer02HrValue!=Sequence2_hour_http)
		{
			H_Timer02HrValue= Sequence2_hour_http;
			ProcessTotalMin2   =  (H_Timer02HrValue*60)+  H_Timer02MinValue;
			updateSetData=1;
		}
		if(H_Timer02MinValue!=Sequence2_minute_http)
		{
			H_Timer02MinValue= Sequence2_minute_http;
			ProcessTotalMin2   =  (H_Timer02HrValue*60)+  H_Timer02MinValue;
			updateSetData=1;
		}
		if(R_Sequence1_hour_http!=   Rise_Sequence1_Hour)
		{
			Rise_Sequence1_Hour = R_Sequence1_hour_http;
			updateSetData=1;
		}
		if(R_Sequence1_minute_http!=   Rise_Sequence1_Minute)
		{
			Rise_Sequence1_Hour = R_Sequence1_minute_http;
			updateSetData=1;
		}

		if(R_Sequence2_hour_http!=   Rise_Sequence2_Hour)
		{
			Rise_Sequence2_Hour = R_Sequence2_hour_http;
			updateSetData=1;
		}

		if(R_Sequence2_minute_http!=   Rise_Sequence2_Minute)
		{
			Rise_Sequence2_Minute = R_Sequence2_minute_http;
			updateSetData=1;
		}
	}
}
