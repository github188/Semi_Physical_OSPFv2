/*
* Copyright (c) 2014,北京航空航天大学
* All rights reserved.
*
* 系统名称: SPACE NETWORK SIMULATION SYSTEM
* 作    者: 张涛
* 当前版本: SNS 1.0
* 
* 文件名称: Sns_Node_Virtual.h
* 当前版本: V 1.0.0
* 文件标识: Sns_Node_Virtual类头文件
* 功能描述: 
* 完 成 人: 
* 联系方式: 
* 完成日期: 
*
* 摘    要:
*/
//////////////////////////////////////////////////////////////////////

#ifndef SNS_NODE_VIRTUAL_H
#define SNS_NODE_VIRTUAL_H

#if _MSC_VER > 1000
#pragma once
#endif

/////////////本部分为模型参数描述部分/////////////
/************************************************
***Model-Info-Begin
/************************************************
**Model_Name:Sns_Node_Virtual;             //模型名
**Model_Type:Node;                  //模型类型：场景、节点、环境、协议
**ModelState:proceeding             //模型开发状态：进行、完成、注册
**Abstract:
/***********************************************
**Standard-Environment/Protocols-Model-OfNode     //本节点上的标准环境或协议模型
/*Standard_Model_ofThis_Descri
/***********************************************
**User-Environment/Protocols-Model-OfNode     //本节点上的用户环境或协议模型
*Sns_Model_OSPFv2;			// 
*Sns_Model_NetworkIP;			// 
/*User_Model_ofThis_Descri
/***********************************************
**Config-Init-Variable:          //模型初始化配置参数
/*Config_VariableList_Descri
/***********************************************
**StatsData-Output-Variable:   //模型输出统计数据
/*Stats_VariableList_Descri
/***********************************************
**SnsMsg-Input:                  //输入事件
/*MesInputVariable_Descri
/***********************************************
**SnsMsg-Output:                 //输出事件
/*MesOutputVariable_Descri
/***********************************************
***Model-Info-End
***********************************************/

#include "Sns_Scenarios.h"

#include "list.h"
#include "GlobleStructures.h"
#include "ForwardingTable.h"
//#include "Sphere_Position.h"

class Sns_Message;

class Sns_Config_Input;

//class list;

//class ForwardingTable;

//class Sat_Id_and_IP_Relavant ;

//class  Sphere_Position ; 



#define  ANY_ADDRESS 0xffffffff
	// /**
	// CONSTANT    :: NETWORK_UNREACHABLE  :  -2
	// DESCRIPTION :: Network unreachable.
	// **/
#define NETWORK_UNREACHABLE     -2

	// /**
	// CONSTANT    :: DEFAULT_INTERFACE  : 0
	// DESCRIPTION :: Default interface index
	// **/
#define DEFAULT_INTERFACE       0
	//
	// Initial allocated entries for routing table.
	//

#define FORWARDING_TABLE_ROW_START_SIZE 8
// /**
// CONSTANT :: MAX_NW_PKT_SIZE : 2048
// DESCRIPTION ::
//      Defines the Maximum Network Packet Size which can handled by
//      the physical network. In QualNet, its value is 2048. Packet
//      larger than this will be fragmented by IP.
// **/
#define MAX_NW_PKT_SIZE       2048
class Sns_Node_Virtual : public sns_base_node  
{
public://模型导向自动生成的公有变量
	
	int Model_num_In_Node;                   //本节点中的模型个数
	Sns_base_model ** Model_List;           //节点内模型队列
	
	Sns_Config_Input * Config_Input;  		//存储配置文件内容
	char  *ConfFile_Path;                   //配置文件路径,由场景初始化后给出

	Sns_Config_Input * StatsVar_Output;  	//存储模型输出状态变量的值

	short Modelid_In_list[MAX_MODEL_NUM_INSCENA];   //某模型在本节点模型队列中的初始位置
   
public://模型导向自动生成变量

	//依附于本模型的其他模型每类模型数量变量
	struct Sns_model_Num_ofThis_str
	{
		int Num_Sns_Model_OSPFv2;	//
		int Num_Sns_Model_NetworkIP;	//
		//ModelNum_ofThisList//  
	};
	Sns_model_Num_ofThis_str Num_ofThis;//依附于本模型的其他模型每类模型数量变量结构 
   
	//模型输入初始化配置参数变量
	struct Sns_model_Config_Var_str
	{
		//Config_VariableList// 
	};
	Sns_model_Config_Var_str Config_Var;//模型输入初始化配置参数变量结构

	//模型仿真输出统计数据变量
	struct Sns_model_Stats_Var_str 
	{
		//Stats_VariableList//
	}; 
	Sns_model_Stats_Var_str Stats_Var;//模型仿真输出统计数据变量结构  

	//输入消息事件名称
	enum 
	{
		//MesInputVariable//
	};

	//输出消息事件名称
	enum 
	{
		//MesOutputVariable//
	};

public://用户自定义公有变量
	
	enum NetworkRoutingProtocolType
	{
		NETWORK_PROTOCOL_IP = 0,
		NETWORK_PROTOCOL_IPV6,
		NETWORK_PROTOCOL_MOBILE_IP,
		NETWORK_PROTOCOL_NDP,
		NETWORK_PROTOCOL_SPAWAR_LINK16,
		NETWORK_PROTOCOL_ICMP,
		ROUTING_PROTOCOL_AODV,
		ROUTING_PROTOCOL_DSR,
		ROUTING_PROTOCOL_FSRL,
		ROUTING_PROTOCOL_STAR,
		ROUTING_PROTOCOL_LAR1,
		ROUTING_PROTOCOL_ODMRP,
		ROUTING_PROTOCOL_OSPF,
		ROUTING_PROTOCOL_OSPFv2,
		ROUTING_PROTOCOL_SDR,
		ROUTING_PROTOCOL_BELLMANFORD,
		ROUTING_PROTOCOL_STATIC,
		ROUTING_PROTOCOL_ICMP_REDIRECT,
		ROUTING_PROTOCOL_DEFAULT,
		ROUTING_PROTOCOL_FISHEYE,
		ROUTING_PROTOCOL_OLSR_INRIA,
		ROUTING_PROTOCOL_IGRP,
		ROUTING_PROTOCOL_EIGRP,
		ROUTING_PROTOCOL_BRP,
		//StartRIP
		ROUTING_PROTOCOL_RIP,
		//EndRIP
		//StartRIPng
		ROUTING_PROTOCOL_RIPNG,
		//EndRIPng
		//StartIARP
		ROUTING_PROTOCOL_IARP,
		//EndIARP
		//StartZRP
		ROUTING_PROTOCOL_ZRP,
		//EndZRP
		//StartIERP
		ROUTING_PROTOCOL_IERP,
		//EndIERP
		//InsertPatch ROUTING_PROTOCOL_TYPE

		EXTERIOR_GATEWAY_PROTOCOL_EBGPv4,
		EXTERIOR_GATEWAY_PROTOCOL_IBGPv4,
		EXTERIOR_GATEWAY_PROTOCOL_BGPv4_LOCAL,

		GROUP_MANAGEMENT_PROTOCOL_IGMP,
		LINK_MANAGEMENT_PROTOCOL_CBQ,

		MULTICAST_PROTOCOL_STATIC,
		MULTICAST_PROTOCOL_DVMRP,
		MULTICAST_PROTOCOL_MOSPF,
		MULTICAST_PROTOCOL_ODMRP,

		MULTICAST_PROTOCOL_PIM,

		// ADDON_MAODV
		MULTICAST_PROTOCOL_MAODV,

		NETWORK_PROTOCOL_GSM,
		NETWORK_PROTOCOL_ARP,

		ROUTING_PROTOCOL_OSPFv3,
		ROUTING_PROTOCOL_OLSRv2_NIIGATA,

		ROUTING_PROTOCOL_ALL,

		NETWORK_PROTOCOL_CELLULAR,
		
		ROUTING_PROTOCOL_AODV6,
		ROUTING_PROTOCOL_DYMO,
		ROUTING_PROTOCOL_DYMO6,
		NETWORK_ROUTE_REDISTRIBUTION,
		ROUTING_PROTOCOL_BACKPRESSURE,  //cjz
		ROUTING_PROTOCOL_ISNPRP,  //zp
		ROUTING_PROTOCOL_STANDARD,//ZP
		ROUTING_PROTOCOL_BDSAT,//zhaopei
		ROUTING_PROTOCOL_SNAPSHOT,//zhaopei



		ROUTING_PROTOCOL_NONE // this must be the last one
	};

	// /**
	// ENUM        :: NetworkRoutingAdminDistanceType
	// DESCRIPTION :: Administrative distance of different routing protocol
	// **/
	enum NetworkRoutingAdminDistanceType
	{
		ROUTING_ADMIN_DISTANCE_STATIC = 1,
		ROUTING_ADMIN_DISTANCE_EBGPv4 = 20,
		ROUTING_ADMIN_DISTANCE_IBGPv4 = 200,
		ROUTING_ADMIN_DISTANCE_BGPv4_LOCAL = 200,
		ROUTING_ADMIN_DISTANCE_OSPFv2 = 110,
		ROUTING_ADMIN_DISTANCE_IGRP = 100,
		ROUTING_ADMIN_DISTANCE_STAR,
		ROUTING_ADMIN_DISTANCE_RIPv3,
		ROUTING_ADMIN_DISTANCE_BELLMANFORD,
		ROUTING_ADMIN_DISTANCE_FISHEYE,
		ROUTING_ADMIN_DISTANCE_OLSR,
		ROUTING_ADMIN_DISTANCE_EIGRP,
		ROUTING_ADMIN_DISTANCE_BACKPRESSURE, //cjz
		ROUTING_ADMIN_DISTANCE_ISNPRP,
		ROUTING_ADMIN_DISTANCE_STANDARD,
		ROUTING_ADMIN_DISTANCE_BDSAT,
		ROUTING_ADMIN_DISTANCE_SNAPSHOT,

		//StartRIP
		ROUTING_ADMIN_DISTANCE_RIP,
		//EndRIP
		//StartRIPng
		ROUTING_ADMIN_DISTANCE_RIPNG,
		//EndRIPng
		ROUTING_ADMIN_DISTANCE_SDR,


		ROUTING_ADMIN_DISTANCE_OSPFv3 = 115,

		ROUTING_ADMIN_DISTANCE_OLSRv2_NIIGATA,

		ROUTING_ADMIN_DISTANCE_FSRL = 210,
		//InsertPatch ROUTING_DISTANCE_TYPE

		// Should always have the highest adminstrative distance
		// (ie, least important).
		ROUTING_ADMIN_DISTANCE_DEFAULT = 255
	};
	//----------------------------------------------------------
	// Routing table (forwarding table)
	//----------------------------------------------------------

	// /**
	// STRUCT      :: NetworkForwardingTableRow
	// DESCRIPTION :: Structure of an entity of forwarding table.
	// **/
	typedef struct
	{
		unsigned destAddress;        // destination address
		unsigned destAddressMask;    // subnet destination Mask
		int interfaceIndex;           // index of outgoing interface
		unsigned nextHopAddress;     // next hop IP address

		int cost;

		// routing protocol type
		NetworkRoutingProtocolType protocolType;

		// administrative distance for the routing protocol
		NetworkRoutingAdminDistanceType adminDistance;

		bool interfaceIsEnabled;
	}
	NetworkForwardingTableRow;
	// /**
	// STRUCT      :: NetworkForwardingTable
	// DESCRIPTION :: Structure of forwarding table.
	// **/
	typedef	struct
	{
		int size;                        // number of entries
		int allocatedSize;
		NetworkForwardingTableRow *row;  // allocation in Init function in Ip
	}
	NetworkForwardingTable;

	int numberInterfaces;

	InterfaceInfoType interfaceInfo[MAX_NUM_INTERFACES];

	ForwardingTable forwardingTable;
private: //用户自定义私有变量
	
public://模型导向自动生成的公有函数

	Sns_Node_Virtual();
	virtual ~Sns_Node_Virtual();
	
	//功能:消息处理函数,接收模型输入事件,触动相应函数,并处理
	void SNS_Node_MsgDeal(Sns_Message *msg);
	
   //功能:模型初始化函数,读取模型对应配置文件,配置模型初始化配置参数
    void Node_init();
    
   //功能:节点初始化后的处理函数,用于有时需要所有节点都初始化完成才可执行的动作
	void Node_init_end();

	//功能:处理节点模型在仿真结束后的一些事,如节点模型仿真结果输出等
	void SNS_Simulate_End_Node();	
	
public: //模型导向自动生成函数,用户输入事件处理
	//Sns_Msg_In_Func//

private://模型导向自动生成的私有函数

	//功能:记录本模型的输出状态变量值到StatsVar_Output内
	void SNS_Record_Stats_Value();

	//功能:初始化本节点所有环境/协议模型
	void Model_OfNode_Init();

	//功能:发送一个新消息
	//输入:DestiNode--消息目的节点地址,ModelId--发起消息的模型ID,instanceId--发起模型实例号,EventName--消息事件名称,
	//     EventType--事件类型,PayLoad--消息载荷,PacketSize--消息载荷大小,TimeDelay--发送延迟
	//     发送空消息时，PayLoad=NULL，PacketSize=0
	void Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay);

	//功能:将一个消息转发给相应的模型
	//输入:msg-转发的消息，DestiNode--接收消息目的节点地址,ModelId--接收消息的模型ID,instanceId--发起模型实例号,EventName--接收消息事件名称,
	//     EventType--接收事件类型,TimeDelay--发送延迟
	void Send_Aexisting_Msg(Sns_Message *msg,int DestiNode,int ModelId,int instanceId,int EventName,int EventType, clocktype  TimeDelay);

public://用户自定义公有函数

	int GetOtherNodeIdfromAddress(unsigned address,unsigned mask=0xffffffff);

	void sendIpv4Packet(unsigned dstAddr, char* packet, int packetSize, clocktype delay = 0);
private://用户自定义私有函数

};

#endif
