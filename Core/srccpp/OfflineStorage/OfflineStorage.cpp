/*
 * OfflineStorage.cpp
 *
 *  Created on: 09-Feb-2023
 *      Author: MKS
 */
#include "main.h"
#include "OfflineStorage.h"
#include <stdio.h>
#include <string.h>
using namespace std;

#define MAXNOOFBLOCK 32

extern "C" {
void W25qxx_WriteSector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_SectorSize);
void W25qxx_ReadSector(uint8_t *pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_SectorSize);
void W25qxx_EraseSector(uint32_t SectorAddr);
bool W25qxx_IsEmptyBlock(uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_BlockSize);
void W25qxx_EraseBlock(uint32_t BlockAddr);
void W25qxx_EraseChip(void);
}

uint8_t ProductionSet_uintFormat[100]={0};
char ProductionSet_charFormat[100]={'\0'};
uint16_t SectorPos;

/*Data need to saved in flash*/
extern uint8_t SEQMONITOR;
extern uint16_t ProcessId_Value;
extern uint8_t updateSetData;
extern uint16_t Seq1temperature;
extern uint16_t Seq2temperature;
extern uint8_t Seq1durationHr,Seq1durationMin,Seq2durationHr,Seq2durationMin;
extern uint16_t seq1_count_inc,seq2_count_inc;
extern uint8_t Write_memory_Once;
extern uint16_t Quenching_Seconds_Cont;

/*check for change in data*/
uint8_t SEQMONITOR_K1;
uint16_t ProcessId_Value_K1;
uint16_t seq1_count_inc_K1,seq2_count_inc_K1;



OfflineStorage::OfflineStorage() {
	// TODO Auto-generated constructor stub

}

OfflineStorage::~OfflineStorage() {
	// TODO Auto-generated destructor stub
}

void OfflineStorage::run()
{
	m_writeSeqMonitor();
	m_writeHeattreatmentData();
	m_quenchCount();

}

void OfflineStorage::m_writeSeqMonitor(){
	if(SEQMONITOR == SEQMONITOR_K1){return;}
	SEQMONITOR_K1 = SEQMONITOR;
	m_writeFlashBuf[0] = SEQMONITOR;

	W25qxx_EraseSector(0);
	W25qxx_WriteSector(m_writeFlashBuf,0,0,1);
}

void OfflineStorage::m_writeHeattreatmentData(){
	if((ProcessId_Value != ProcessId_Value_K1)||(updateSetData==1))
	{
		m_writeFlashBuf[0] = (uint8_t)(ProcessId_Value && 0xff);
		m_writeFlashBuf[1] = (uint8_t)(ProcessId_Value>>8) && 0xff;
		ProcessId_Value_K1=ProcessId_Value;

		m_writeFlashBuf[2] = (uint8_t)(Seq1temperature && 0xff);
		m_writeFlashBuf[3] = (uint8_t)(Seq1temperature>>8) && 0xff;
		m_writeFlashBuf[4] = (uint8_t)(Seq2temperature && 0xff);
		m_writeFlashBuf[5] = (uint8_t)(Seq2temperature>>8) && 0xff;
		m_writeFlashBuf[6] = (uint8_t)(Seq1durationHr);
		m_writeFlashBuf[7] = (uint8_t)(Seq1durationMin);
		m_writeFlashBuf[8] = (uint8_t)(Seq2durationHr);
		m_writeFlashBuf[9] = (uint8_t)(Seq2durationMin);

		updateSetData	= 0;
		W25qxx_EraseSector(1);
		W25qxx_WriteSector(m_writeFlashBuf,1,0,10);

	}
}

void OfflineStorage::m_writeCountinc(){
	if((seq1_count_inc_K1 != seq1_count_inc) ||(seq2_count_inc_K1 != seq2_count_inc )){
		m_writeFlashBuf[0] = (uint8_t)(seq1_count_inc && 0xff);
		m_writeFlashBuf[1] = (uint8_t)(seq1_count_inc>>8) && 0xff;
		m_writeFlashBuf[2] = (uint8_t)(seq2_count_inc && 0xff);
		m_writeFlashBuf[3] = (uint8_t)(seq2_count_inc>>8) && 0xff;
		seq1_count_inc_K1 = seq1_count_inc;
		seq2_count_inc_K1 = seq2_count_inc;

		W25qxx_EraseSector(2);
		W25qxx_WriteSector(m_writeFlashBuf,2,0,4);
	}
}

void OfflineStorage::m_quenchCount(){
	if(Write_memory_Once==0){return;}
		Write_memory_Once=0;
		m_writeFlashBuf[0] = (uint8_t)(Quenching_Seconds_Cont && 0xff);
		m_writeFlashBuf[1] = (uint8_t)(Quenching_Seconds_Cont>>8) && 0xff;
		W25qxx_EraseSector(3);
		W25qxx_WriteSector(m_writeFlashBuf,3,0,2);
}

void OfflineStorage::m_readCountinc(){
	W25qxx_ReadSector(m_readFlashBuf,2,0,4);
	seq1_count_inc = (m_readFlashBuf[1]<<8 | m_readFlashBuf[0]);
	seq2_count_inc = (m_readFlashBuf[3]<<8 | m_readFlashBuf[2]);
	seq1_count_inc_K1 = seq1_count_inc;
	seq2_count_inc_K1 = seq2_count_inc;
	SEQMONITOR_K1 = SEQMONITOR;
}

void OfflineStorage::m_readSeqMonitor(){
	W25qxx_ReadSector(m_readFlashBuf,0,0,1);
	SEQMONITOR = m_readFlashBuf[0];
	SEQMONITOR_K1 = SEQMONITOR;
}

void OfflineStorage::m_readHeattreatmentData(){
	W25qxx_ReadSector(m_readFlashBuf,1,0,10);
	ProcessId_Value = 2;//(m_readFlashBuf[1]<<8 | m_readFlashBuf[0]);
	Seq1temperature = (m_readFlashBuf[3]<<8 | m_readFlashBuf[2]);
	Seq2temperature = (m_readFlashBuf[5]<<8 | m_readFlashBuf[4]);
	Seq1durationHr = m_readFlashBuf[6];
	Seq1durationMin = m_readFlashBuf[7];
	Seq2durationHr = m_readFlashBuf[8];
	Seq2durationMin = m_readFlashBuf[9];

	ProcessId_Value_K1 = ProcessId_Value;
}

void OfflineStorage::m_readquenchcount(){
	W25qxx_ReadSector(m_readFlashBuf,3,0,2);
	Quenching_Seconds_Cont =(m_readFlashBuf[1]<<8 | m_readFlashBuf[0]);
}

void OfflineStorage::ReadOfflinedataInit()
{
	m_readSeqMonitor();
	m_readHeattreatmentData();
	m_readquenchcount();
}

void OfflineStorage::ECUProductionInit(void)
{

}

