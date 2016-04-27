#pragma once
#include "pcap.h"
#include "GlobleStructures.h"

extern CRITICAL_SECTION cs_WinPcap;
#define ETHER_ADDR_LEN 6//MAC地址长度
#define MY_LINK_TYPE 0x00aa//本软件所用协议类型标志
extern const u_char ETHER_BROADCASTHOST[ETHER_ADDR_LEN];//广播地址

class Sns_Node_Real;
class WinPcap
{
public:
	WinPcap(void);
	~WinPcap(void);
public:
	struct ether_header//以太网头部
	{
		u_char ether_dhost[ETHER_ADDR_LEN];//目的MAC地址
		u_char ether_shost[ETHER_ADDR_LEN];//源MAC地址
		u_char type[2];//协议类型——0x00aa
	};
private:
	pcap_if_t* adapter;
	pcap_t* adapterHandle;
	HANDLE hThread;
	u_char mAddrHosts[ETHER_ADDR_LEN];//自己的MAC地址
	Sns_Node_Real* pNode;
public:
	static void hex2Hosts(unsigned long long hex,u_char* hosts);//长整形转MAC地址数据
	static pcap_if_t* getAllAdapters();//获取本机所有网卡设备

	void setMyNode(Sns_Node_Real* pNode);
	void setMyAddr(unsigned long long hex);//设置源MAC地址
	bool isCurrAdapterOpen();//网卡是否打开
	bool openAdapter(int devID);//打开网卡
	void closeCurrAdapter();//关闭网卡
	bool isMyType(const u_char* packet);//收到的数据包是否是本协议包
	bool isMyMAC(const u_char* packet);//收到的数据包是否是发给本机的包

	void beginCatching();//开始捕获数据包线程
	friend unsigned _stdcall catchPacket(LPVOID pParam);//获取数据包线程

	bool sendPacket(unsigned long long dstAddrHex,u_char* data,int len);//发送数据包
};

