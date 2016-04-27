#include "StdAfx.h"
#include "WinPcap.h"
#include <process.h>
#include "Sns_Node_Real.h"

CRITICAL_SECTION cs_WinPcap;
const u_char ETHER_BROADCASTHOST[ETHER_ADDR_LEN]={0xff,0xff,0xff,0xff,0xff,0xff};
const u_char FLAG_SERVER[ETHER_ADDR_LEN]={'s','e','r','v','e','r'};
const u_char FLAG_CLIENT[ETHER_ADDR_LEN]={'c','l','i','e','n','t'};

WinPcap::WinPcap(void)
	: adapterHandle(NULL)
	, adapter(NULL)
	, hThread(NULL)
{
	InitializeCriticalSection(&cs_WinPcap);
}


WinPcap::~WinPcap(void)
{
	closeCurrAdapter();
	DeleteCriticalSection(&cs_WinPcap);
}

pcap_if_t* WinPcap::getAllAdapters()
{
	pcap_if_t* allAdapters;
	char errorBuffer[ PCAP_ERRBUF_SIZE ];//错误信息缓冲区
	if( pcap_findalldevs_ex( PCAP_SRC_IF_STRING, NULL, 
		&allAdapters, errorBuffer ) == -1 )
	{//检索机器连接的所有网络适配器
		return NULL;
	}
	return allAdapters;
}

void WinPcap::hex2Hosts(unsigned long long hex,u_char* hosts)
{
	for(int i=0;i<ETHER_ADDR_LEN;i++)
	{
		u_char AddrBit=hex%256;
		hosts[ETHER_ADDR_LEN-1-i]=AddrBit;
		hex=hex/256;
	}
}
void WinPcap::setMyNode(Sns_Node_Real* pNode)
{
	this->pNode=pNode;
}
void WinPcap::setMyAddr(unsigned long long hex)
{
	hex2Hosts(hex,mAddrHosts);
}

bool WinPcap::isCurrAdapterOpen()
{
	if(adapterHandle)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
bool WinPcap::openAdapter(int devID)
{
	pcap_if_t* allAdapters;
	char errorBuffer[ PCAP_ERRBUF_SIZE ];//错误信息缓冲区

	if(isCurrAdapterOpen())
	{
		closeCurrAdapter();
	}

	allAdapters=getAllAdapters();
	if(allAdapters==NULL)
	{
		return FALSE;
	}

	adapter=allAdapters;
	for(int i=0;i<devID;i++)
	{
		adapter=adapter->next;
	}
	// 打开指定适配器
 	adapterHandle = pcap_open( adapter->name,						// name of the adapter
 		65535,						// portion of the packet to capture
 		// 65535 guarantees that the whole 
 		// packet will be captured
 		PCAP_OPENFLAG_PROMISCUOUS,	// promiscuous mode
 		-1,						// read timeout - 1 millisecond
 		NULL,						// authentication on the remote machine
 		errorBuffer					// error buffer
 		);
	if( adapterHandle == NULL )
	{//指定适配器打开失败
		pcap_freealldevs( allAdapters );// 释放适配器列表
		return false;
	}
	struct bpf_program filter;
	char filter_app[]="ether dst 0:0:0:0:0:0 and ether proto 0xaa00";
	if(pcap_compile(adapterHandle,&filter,filter_app,0,0)==-1)
	{
		pcap_freealldevs( allAdapters );//释放适配器列表
		return false;
	}
	pcap_setfilter(adapterHandle,&filter);

	pcap_freealldevs( allAdapters );//释放适配器列表
	return true;
}

void WinPcap::closeCurrAdapter()
{
	if(isCurrAdapterOpen())
	{
		pcap_close(adapterHandle);
	}
}

bool WinPcap::isMyType(const u_char* packet)
{
	u_char type[2];
	type[0]=packet[12];
	type[1]=packet[13];
	if(type[0]==0xaa&&type[1]==0x00)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool WinPcap::isMyMAC(const u_char* packet)
{
	for(int i=0;i<ETHER_ADDR_LEN;i++)
	{
		if(packet[i]!=mAddrHosts[i]&&packet[i]!=ETHER_BROADCASTHOST[i])
		{
			return false;
		}
	}
	return true;
}

void WinPcap::beginCatching()
{
	hThread=(HANDLE)_beginthreadex(NULL,0,catchPacket,this,NULL,NULL);
}

unsigned _stdcall catchPacket(LPVOID pParam)
{
	// 开始捕获数据包
	WinPcap* caper=(WinPcap*)pParam;
	int retValue;
	pcap_pkthdr* packetHeader;
	const u_char* packetData;
	while(caper->isCurrAdapterOpen())
	{
		retValue = pcap_next_ex(caper->adapterHandle, 
			&packetHeader, 
			&packetData );
		if(retValue<0)
		{
			if(retValue==-1)
			{
				printf("Error reading the packets %s\n",pcap_geterr(caper->adapterHandle));
 				break;
			}
			else if(retValue==-2)
			{
				continue;
			}
			else
			{
				break;
			}
		}
		// timeout elapsed if we reach this point
		if( retValue == 0 )
		{
			Sleep(1);
			continue;
		}
		if(caper->isMyType(packetData)&&caper->isMyMAC(packetData))
		{
			int packetSize=packetHeader->len-sizeof(WinPcap::ether_header);
			WinPcap::ether_header* etherHeader=(WinPcap::ether_header*)packetData;
			char* data=(char*)malloc(packetSize);
			memcpy_s(data,packetSize,etherHeader+1,packetSize);
			//EnterCriticalSection(&cs_WinPcap);
			caper->pNode->ReceiveFromRealNode(data,packetSize);
			//LeaveCriticalSection(&cs_WinPcap);
			cout<<"packetHeader->caplen="<<packetHeader->caplen<<endl;
			cout<<"packetHeader->len="<<packetHeader->len<<endl;
			cout<<"sizeof(ether_header)="<<sizeof(WinPcap::ether_header)<<endl;
			cout<<"payLoadLen="<<packetSize<<endl;
		}
	}
	// if we get here, there was an error reading the packets
	return 0;
}

bool WinPcap::sendPacket(unsigned long long dstAddrHex,u_char* data,int len)
{
	u_char dstAddrHosts[ETHER_ADDR_LEN];
	hex2Hosts(dstAddrHex,dstAddrHosts);
	u_char* etherPacket=(u_char*)malloc(sizeof(ether_header)+len*sizeof(u_char));
	ether_header* etherHeader=(ether_header*)etherPacket;
	for(int i=0;i<ETHER_ADDR_LEN;i++)
	{
		etherHeader->ether_dhost[i]=dstAddrHosts[i];
		etherHeader->ether_shost[i]=mAddrHosts[i];
	}
	etherHeader->type[0]=0xaa;
	etherHeader->type[1]=0x00;
	memcpy_s(etherHeader+1,len,data,len);
	if( pcap_sendpacket( adapterHandle, // the adapter handle
		etherPacket, // the packet
		sizeof(ether_header)+len*sizeof(u_char) // the length of the packet
		) != 0 )
	{
		xdelete(etherPacket);
		return false;
	}
	xdelete(etherPacket);
	return true;
}