/*
 * OfflineStorage.h
 *
 *  Created on: 09-Feb-2023
 *      Author: MKS
 */

#ifndef SRCCPP_OFFLINESTORAGE_OFFLINESTORAGE_H_
#define SRCCPP_OFFLINESTORAGE_OFFLINESTORAGE_H_

class OfflineStorage {
public:
	OfflineStorage();
	virtual ~OfflineStorage();
	void run();
	void ReadOfflinedataInit();
	void ECUProductionInit(void);
private:
	void m_writeSeqMonitor();
	void m_readSeqMonitor();
	void m_writeHeattreatmentData(void);
	void m_quenchCount();
	void m_readHeattreatmentData(void);
	void m_writeCountinc();
	void m_readCountinc();
	void m_readquenchcount();
	void m_writeWifidata();
	void m_readWifiData();
	uint8_t m_writeFlashBuf[30];
	uint8_t m_readFlashBuf[20];
	uint8_t m_readFlashheatBuf[20];
	uint8_t m_readFlashwifiBuf[32];
};

#endif /* SRCCPP_OFFLINESTORAGE_OFFLINESTORAGE_H_ */
