/*
* Copyright (c) 2014,北京航空航天大学
* All rights reserved.
*
* 系统名称: SPACE NETWORK SIMULATION SYSTEM
* 作    者: 张涛
* 当前版本: SNS 1.0
* 
* 文件名称: Sns_Model_NetworkIP.h
* 当前版本: V 1.0.0
* 文件标识: Sns_Model_NetworkIP类头文件
* 功能描述: 网络层IP协议模型
* 完 成 人: 张涛
* 联系方式: 
* 完成日期: 
*
* 摘    要:
*/
//////////////////////////////////////////////////////////////////////

#ifndef SNS_MODEL_NETWORK_IP_H
#define SNS_MODEL_NETWORK_IP_H

#if _MSC_VER > 1000
#pragma once
#endif

/////////////本部分为模型参数描述部分/////////////
/************************************************
***Model-Info-Begin
/************************************************
**Model_Name:Network_IP;          //模型名
**Class_Name:Sns_Model_NetworkIP;          //模型名对应的类名
**Model_Type:protocols/environment;          //模型类型：场景、节点、环境、协议
**ModelState:proceeding;         //模型开发状态：进行、完成、注册
**Abstract:
/***********************************************
**Config-Init-Variable:          //模型初始化配置参数
/*Config_VariableList_Descri
/***********************************************
**StatsData-Output-Variable:   //模型输出统计数据
*int,numPacketsSentToMac;			//发往MAC的数据包总数 
*int,numPacketsRoutedForOtherNodes;			//路由到其他节点的数据包总数 
*int,numPacketsDeliveredToThisNode;			//本节点接收的数据包总数 
*int,deliveredPacketTtlTotal;			//本节点接收的数据包总跳数 
*int,numNetworkUnreachableDrops;			//由于找不到路由而丢包总数 
*int,numTtlExpirationDrops;			//由于ttl超出而丢包总数 
/*Stats_VariableList_Descri
/************************************************
**SnsMsg-Input:                  //输入事件
*MSG_InEVENT_NETWORK_FromTransport;			//来自传输层协议的数据包 
*MSG_InEVENT_NETWORK_FromMAC;			//来自链路层协议的数据包 
*MSG_InEVENT_NETWORK_UpdateRoutable;			//路由表更新事件 
/*MesInputVariable_Descri
/************************************************
**SnsMsg-Output:                 //输出事件
*MSG_OutEVENT_NETWORK_ToMAC;			//发往链路层的数据包 
*MSG_OutEVENT_NETWORK_ToTransport;			//发往传输层的数据包 
/*MesOutputVariable_Descri
/***********************************************
***Model-Info-End
***********************************************/

#include "SNS_core.h" //平台库
#include "GlobleStructures.h"
#include "ForwardingTable.h"
#include "Sat_User_Relation.h"

class Sns_Config_Input;
class Sns_Message;
class Sns_Scenarios;

//ip 协议常量定义
#define MAX_IP_FRAGMENTS_SIMPLE_CASE        64
#define NETWORK_IP_FRAG_UNIT       2048 
#define FORWARDING_TABLE_ROW_START_SIZE 8
#define ANY_DEST 0xfffffff
#define OSPFv2_ALL_SPF_ROUTERS    0xE0000005
#define IP_MAXPACKET    65535       /* maximum packet size */
#define GET_INTERFACE_FROM_TABLE  0xFFFF
#define NETWORK_UNREACHABLE   -2
#define NETWORK_IP_REASS_BUFF_TIMER 15   //单位秒
#define SMALL_REASSEMBLY_BUFFER_SIZE  2048
#define REASSEMBLY_BUFFER_EXPANSION_MULTIPLIER  8
#define IP_MIN_HEADER_SIZE 20
#define IP_MAX_HEADER_SIZE 124
#define IPDEFTTL    64      // default ttl, from RFC 1340 
#define MAX_NW_PKT_SIZE       2048


class Sns_Model_NetworkIP : public Sns_base_model
{  
public://模型导向自动生成的公有变量

	Sns_Scenarios * Scenarios_Data;   	//该模型依附的场景
	unsigned Cur_Node_id;               //该模型依附的节点id

	/////用于模型配置文件标示和处理
	unsigned Cur_Node_id_inOneType;     //该模型依附的节点在该节点类型中的序列号
	char*  Cur_Node_Name;				//该模型依附节点类名
	Sns_Config_Input * Config_Input;  	//存储配置文件内容
	char *ConfFile_Path;                //配置文件路径,由场景初始化后给出
	/////用于模型配置文件标示和处理end

	Sns_Config_Input * StatsVar_Output;  	//存储模型输出状态变量的值

public: //模型导向自动生成变量

	//模型输入初始化配置参数变量
	struct Sns_model_Config_Var_str
	{
		//Config_VariableList//
	};
	Sns_model_Config_Var_str Config_Var;//模型输入初始化配置参数变量结构

	//模型仿真输出统计数据变量
	struct Sns_model_Stats_Var_str 
	{
		int numPacketsSentToMac;			//发往MAC的数据包总数
		int numPacketsRoutedForOtherNodes;			//路由到其他节点的数据包总数
		int numPacketsDeliveredToThisNode;			//本节点接收的数据包总数
		int deliveredPacketTtlTotal;			//本节点接收的数据包总跳数
		int numNetworkUnreachableDrops;			//由于找不到路由而丢包总数
		int numTtlExpirationDrops;			//由于ttl超出而丢包总数
		//Stats_VariableList//
	}; 
	Sns_model_Stats_Var_str Stats_Var;//模型仿真输出统计数据变量结构  

	//输入消息事件名称
	enum 
	{
		MSG_InEVENT_NETWORK_FromTransport,			//来自传输层协议的数据包 
		MSG_InEVENT_NETWORK_FromMAC,			//来自链路层协议的数据包 
		MSG_InEVENT_NETWORK_FromOSPFv2,			//来自OSPF协议的数据包 
		MSG_InEVENT_NETWORK_UpdateRoutable,			//路由表更新事件 
		MSG_InEVENT_NETWORK_IsMyIMI,
		MSG_InEVENT_NETWORK_NotMyIMI,
		//MesInputVariable//
	};

	//输出消息事件名称
	enum 
	{
		MSG_OutEVENT_NETWORK_ToMAC,			//发往链路层的数据包 
		MSG_OutEVENT_NETWORK_ToTransport,			//发往传输层的数据包 
		MSG_OutEVENT_NETWORK_ToProtocol_OSPFv2,			//发往OSPF路由协议的包 
		MSG_OutEVENT_NETWORK_ToProtocol_LocalRoute,
		MSG_OutEVENT_NETWORK_ISMYIMI,
		//MesOutputVariable//
	};

public://用户自定义公有变量
	enum
	{
	PROTOCOL_PACKET,
	PROTOCOL_OSPFv2,
	PROTOCOL_LOCAL_ROUTE,
	};
	typedef struct ip    //ip包头
	{
		unsigned int ip_v:3,        // version 
		ip_hl:5,       // header length 
		ip_tos:8,      // type of service 
		ip_len:16;     // total length 

				unsigned int ip_id:16,
		ip_reserved:1,
		ip_dont_fragment:1,
		ip_more_fragments:1,
		ip_fragment_offset:13;

		unsigned char  ip_ttl;      // time to live 
		unsigned char  ip_p;        // protocol 
		unsigned short ip_sum;      // checksum 
		//long ip_src,ip_dst
		unsigned    ip_src,ip_dst;      // source and dest address 

	} IpHeaderType;

	typedef struct //Network to Transport
	{
		unsigned sourceAddr;
		unsigned destinationAddr;
		unsigned priority;
	} NetworkToTransportInfo;

	typedef struct //Transport to Network
	{
		unsigned destinationAddr;
		unsigned priority;
		unsigned char Protocol_ToIP;
	} TransportToNetworkInfo;

	typedef struct //Network to MAC
	{
		unsigned srcAddr;
		unsigned nexthopaddr;
		int interfaceIndex;

	} NetworkToMACInfo;

	struct NetworkForwardingTableRow   //路由表行结构
	{
		unsigned destAddress;       /* destination address */
		short interfaceIndex;    /* right now interface Id */
		unsigned nextHopAddress;    /* next hop. */
	};

	struct NetworkForwardingTable  //路由表
	{
		int size;  /* number of entries */
		int allocatedSize;
		NetworkForwardingTableRow *row;  /* allocation in Init function in Ip */
	};

	struct IpReassemblyBufferType//组包数据结构
	{ 
		Sns_Message* packetUnderConstruction;
		int sizeLimit;
		clocktype expirationDate;
		unsigned short totalPacketLength;
		unsigned short fragmentationSize;
		unsigned char  fragmentIsHereBitTable[MAX_IP_FRAGMENTS_SIMPLE_CASE/8];
		bool endFragmentHasArrived;
		unsigned short endFragmentOffset;
	};

	typedef struct IpReassemblyBufferListCellStruct 
	{
		struct IpReassemblyBufferListCellStruct* nextPtr;
		IpReassemblyBufferType reassemblyBuffer;
	} IpReassemblyBufferListCellType;


	typedef struct 
	{
		IpReassemblyBufferListCellType* firstPtr;
		IpReassemblyBufferListCellType* freeListPtr;
	} IpReassemblyBufferListType;

	typedef struct
	{
		int size;
		unsigned int dstNodeAddr;
	} LocalRouteHeader;

	int maxPacketLength;     //本模型处理的最大包长度
	NetworkForwardingTable     forwardTable;    //路由表

	IpReassemblyBufferListType reassemblyBufferList;   //组帧链表

	int numberInterfaces;
	InterfaceInfoType* interfaceInfo;
	ForwardingTable* forwardingTable;
private://用户自定义私有变量
	unsigned short    packetIdCounter; // 本节点产生的IP包流水号 

public://模型导向自动生成公有函数

	Sns_Model_NetworkIP();  
	~Sns_Model_NetworkIP(); 

	//功能:模型初始化函数,读取模型对应配置文件,配置模型初始化配置参数
	void Model_init();

	//功能:节点初始化后的处理函数,用于有时需要所有节点所有模型都初始化完成才可执行的动作
	void Model_init_end();

	//功能:处理协议或环境模型在仿真结束后的一些事,如模型仿真结果输出等
	void SNS_Simulate_End_Model();

	//功能:消息处理函数,接收模型输入事件,触动相应函数,并处理
	void SNS_Model_MsgDeal(Sns_Message *msg);								

public://模型导向自动生成函数,用户输入事件处理

	//功能:Msg_InEvent_NETWORK_FromTransport事件函数,接收来自传输层的消息并处理 
	void Msg_InEvent_NETWORK_FromTransport(Sns_Message *msg); 

	//功能:MSG_InEVENT_NETWORK_FromMAC事件函数,接收来链路层的数据包,并处理 
	void Msg_InEvent_NETWORK_FromMAC(Sns_Message *msg); 

	//功能:MSG_InEVENT_NETWORK_UpdateRoutable事件函数,接收路由更新消息,更新IP协议路由表 
	void Msg_InEvent_NETWORK_UpdateRoutable(Sns_Message *msg); 

	void Msg_InEvent_NETWORK_FromOSPFv2(Sns_Message* msg);

	void Msg_InEvent_NETWORK_isMyIMI(Sns_Message* msg);

	void Msg_InEvent_NETWORK_notMyIMI(Sns_Message* msg);
	//Sns_Msg_In_Func//

private://模型导向自动生成私有函数

	//功能:记录本模型的输出状态变量值到StatsVar_Output内
	void SNS_Record_Stats_Value();

	//功能:发送一个新消息
	//输入:DestiNode--消息目的节点地址,ProtocolId--发起消息的模型ID,EventName--消息事件名称,
	//     EventType--事件类型,PayLoad--消息载荷,PacketSize--消息载荷大小,TimeDelay--发送延迟
	void Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay);


public://用户自定义公有函数


private://用户自定义私有函数
#define SetBit(BitVector, Index)  BitVector[(Index)/8] |= (1 << ((Index) % 8))
#define BitIsSet(BitVector, Index)  ((BitVector[(Index)/8] & (1 << ((Index) % 8))) != 0)

	//功能:为一个数据包加上IP包头,该函数将修改一个已有MSG的负载,以及负载大小和包头大小3个参数
	//输入:msg:需要加ip头的消息,要求有负载;destAdd:目的地址;priority:优先级
	//     protocol:上层应用协议;ttl:生命期
	void Add_IpHeader(Sns_Message *msg, unsigned srcAddr,unsigned destAdd, unsigned priority, unsigned char protocol, unsigned ttl);

	////////////////////////////////////数据包成帧处理,并路由转发发送给链路层的相关处理////////////////////////////////////

	//功能:将包发到链路层处理主程序
	void RoutePacketAndSendToMac(Sns_Message *msg);

	//功能:将消息发到对应端口的链路层协议,若消息内包大小超过链路层帧大小,则需要拆包
	void Packet_SendToMacLayer(Sns_Message *msg, short interfaceIndex, unsigned nextHop,unsigned srcAddr);

	//功能:将已处理过的消息(经过拆包后)发到对应端口的链路层协议
	void IpFragmentToMacLayer(Sns_Message *msg, short interfaceIndex, unsigned nextHop,unsigned srcAddr);

	//功能:查表路由主程序
	void LookupTableRoute_Packet(Sns_Message *msg);

	//功能:查路由表,根据目的地址,获取下一跳地址和转发端口
	void GetInterfAndNextH_FromFTable(unsigned destAdd, short *interfaceIndex, unsigned *nextHopAdd);

	////////////////////////////////////数据包成帧处理,并路由转发发送给链路层的相关处理 end////////////////////////////////////

	////////////////////////////////////接收链路层数据帧,组帧处理////////////////////////////////////

	//功能:组帧主程序
	void ProcFragment_BuildCompPacket(Sns_Message *msg, bool *packetIsComplete, Sns_Message **completedPacket);

	//功能:判断是否是某包第一个来的数据帧,是否存在前面的帧,并被存储在RBufList
	void IpRBufList_FindOrCreate(IpReassemblyBufferListType *RBufList, Sns_Message *P_Fragment, IpReassemblyBufferType **FragBufferPtr, bool *Buf_isFound);

	//功能:判断两个帧是否属于同一包
	bool IsIpFragmentOf(Sns_Message *msg1, Sns_Message *msg2);

	//功能:RBufList中增加一新链表,并分配内存
	void IpRBufList_AddNewBuf(IpReassemblyBufferListType *RBufList, IpReassemblyBufferType **RBufPtr);

	//功能:向RBufList的链表中加入一新的帧,并初始化
	void Init_ReassemblyBuf(IpReassemblyBufferType *reassemblyBuffer, Sns_Message *msg);

	//功能:对一个新来的帧,与以前存入RBufList的链表的帧一起组帧
	void AddFragment_ReassemblyBuf(IpReassemblyBufferType *reassemblyBuffer, Sns_Message *msg, bool *packetIsComplete, Sns_Message **completedPacket);

	//功能:如果帧内存不够,再扩8倍
	void ExpandReassemblyBuffer(IpReassemblyBufferType *reassemblyBuffer, int minSize);

	//功能:判断是否已是完整数据包了
	void Check_BufIsCompletion(IpReassemblyBufferType *reassemblyBuffer, bool *packetIsComplete);

	//功能:组帧结束后,移去链表中的内存
	void Remove_ExpiredIpRBuf(IpReassemblyBufferListType *reassemblyBufferList, clocktype currentTime);

	bool ReassemblyBuf_IsExpired(IpReassemblyBufferType *reassemblyBuf, clocktype curTime);

	//功能:组帧结束后,删除链表
	void IpReassemblyBufList_Del(IpReassemblyBufferListType *reassemblyBufferList, IpReassemblyBufferType **reassemblyBufferPtr);

	////////////////////////////////////接收链路层数据帧,组帧处理 end////////////////////////////////////

	//功能:将数据包发与上层协议,包括去包头,发送到传输层等,主函数
	void ProcessPacketForMeFromMac(Sns_Message *msg);

	//功能:去包头
	void Remove_IpHeader(Sns_Message *msg, unsigned *sourceAdd, unsigned *destAdd, unsigned *priority, unsigned char *protocol, unsigned int *ttl);

	//功能:将数据包发送到传输层
	void IpPacketToTransport(Sns_Message *msg, unsigned priority, unsigned sourceAdd, unsigned destAdd);

	//功能:将数据包路由并发送给链路层发走
	void ProcessPacketForAnotherFromMac(Sns_Message *msg);

	////////////////////////////////////路由表处理////////////////////////////////////

	//功能:路由表初始化
	void NetworkInitForwardingTable();

	//功能:路由表更新
	void NetworkUpdateForwardingTable(unsigned destAddress, short interfaceIndex, unsigned nextHopAddress);

	//功能:路由表打印
	void Print_ForwardingTable();

	//功能:路由表打印到文件
	void fPrint_ForwardingTable(FILE *out_file);

	////////////////////////////////////路由表处理////////////////////////////////////

	void ProcessPacketForNextHop(Sns_Message* msg,int interfaceIndex);
	void ProcessPacketForOspfv2(Sns_Message* msg,unsigned srcAddr,unsigned dstAddr);
	void ProcessPacketForLocalRoute(Sns_Message* msg,unsigned srcAddr,unsigned dstAddr);
	void initVals(int numberInterfaces,InterfaceInfoType* interfaceInfo);
	bool isMyInterface(unsigned address);
	int myInterfaceNextHop(unsigned address);
};  
#endif 
