#pragma once
#include "pcap.h"
#include "GlobleStructures.h"

extern CRITICAL_SECTION cs_WinPcap;
#define ETHER_ADDR_LEN 6//MAC��ַ����
#define MY_LINK_TYPE 0x00aa//���������Э�����ͱ�־
extern const u_char ETHER_BROADCASTHOST[ETHER_ADDR_LEN];//�㲥��ַ

class Sns_Node_Real;
class WinPcap
{
public:
	WinPcap(void);
	~WinPcap(void);
public:
	struct ether_header//��̫��ͷ��
	{
		u_char ether_dhost[ETHER_ADDR_LEN];//Ŀ��MAC��ַ
		u_char ether_shost[ETHER_ADDR_LEN];//ԴMAC��ַ
		u_char type[2];//Э�����͡���0x00aa
	};
private:
	pcap_if_t* adapter;
	pcap_t* adapterHandle;
	HANDLE hThread;
	u_char mAddrHosts[ETHER_ADDR_LEN];//�Լ���MAC��ַ
	Sns_Node_Real* pNode;
public:
	static void hex2Hosts(unsigned long long hex,u_char* hosts);//������תMAC��ַ����
	static pcap_if_t* getAllAdapters();//��ȡ�������������豸

	void setMyNode(Sns_Node_Real* pNode);
	void setMyAddr(unsigned long long hex);//����ԴMAC��ַ
	bool isCurrAdapterOpen();//�����Ƿ��
	bool openAdapter(int devID);//������
	void closeCurrAdapter();//�ر�����
	bool isMyType(const u_char* packet);//�յ������ݰ��Ƿ��Ǳ�Э���
	bool isMyMAC(const u_char* packet);//�յ������ݰ��Ƿ��Ƿ��������İ�

	void beginCatching();//��ʼ�������ݰ��߳�
	friend unsigned _stdcall catchPacket(LPVOID pParam);//��ȡ���ݰ��߳�

	bool sendPacket(unsigned long long dstAddrHex,u_char* data,int len);//�������ݰ�
};

