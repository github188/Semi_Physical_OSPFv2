/*
* Copyright (c) 2014,�������պ����ѧ
* All rights reserved.
*
* ϵͳ����: SPACE NETWORK SIMULATION SYSTEM
* ��    ��: ����
* ��ǰ�汾: SNS 1.0
* 
* �ļ�����: Sns_Node_Virtual.h
* ��ǰ�汾: V 1.0.0
* �ļ���ʶ: Sns_Node_Virtual��ͷ�ļ�
* ��������: 
* �� �� ��: 
* ��ϵ��ʽ: 
* �������: 
*
* ժ    Ҫ:
*/
//////////////////////////////////////////////////////////////////////

#ifndef SNS_NODE_VIRTUAL_H
#define SNS_NODE_VIRTUAL_H

#if _MSC_VER > 1000
#pragma once
#endif

/////////////������Ϊģ�Ͳ�����������/////////////
/************************************************
***Model-Info-Begin
/************************************************
**Model_Name:Sns_Node_Virtual;             //ģ����
**Model_Type:Node;                  //ģ�����ͣ��������ڵ㡢������Э��
**ModelState:proceeding             //ģ�Ϳ���״̬�����С���ɡ�ע��
**Abstract:
/***********************************************
**Standard-Environment/Protocols-Model-OfNode     //���ڵ��ϵı�׼������Э��ģ��
/*Standard_Model_ofThis_Descri
/***********************************************
**User-Environment/Protocols-Model-OfNode     //���ڵ��ϵ��û�������Э��ģ��
*Sns_Model_OSPFv2;			// 
*Sns_Model_NetworkIP;			// 
/*User_Model_ofThis_Descri
/***********************************************
**Config-Init-Variable:          //ģ�ͳ�ʼ�����ò���
/*Config_VariableList_Descri
/***********************************************
**StatsData-Output-Variable:   //ģ�����ͳ������
/*Stats_VariableList_Descri
/***********************************************
**SnsMsg-Input:                  //�����¼�
/*MesInputVariable_Descri
/***********************************************
**SnsMsg-Output:                 //����¼�
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
public://ģ�͵����Զ����ɵĹ��б���
	
	int Model_num_In_Node;                   //���ڵ��е�ģ�͸���
	Sns_base_model ** Model_List;           //�ڵ���ģ�Ͷ���
	
	Sns_Config_Input * Config_Input;  		//�洢�����ļ�����
	char  *ConfFile_Path;                   //�����ļ�·��,�ɳ�����ʼ�������

	Sns_Config_Input * StatsVar_Output;  	//�洢ģ�����״̬������ֵ

	short Modelid_In_list[MAX_MODEL_NUM_INSCENA];   //ĳģ���ڱ��ڵ�ģ�Ͷ����еĳ�ʼλ��
   
public://ģ�͵����Զ����ɱ���

	//�����ڱ�ģ�͵�����ģ��ÿ��ģ����������
	struct Sns_model_Num_ofThis_str
	{
		int Num_Sns_Model_OSPFv2;	//
		int Num_Sns_Model_NetworkIP;	//
		//ModelNum_ofThisList//  
	};
	Sns_model_Num_ofThis_str Num_ofThis;//�����ڱ�ģ�͵�����ģ��ÿ��ģ�����������ṹ 
   
	//ģ�������ʼ�����ò�������
	struct Sns_model_Config_Var_str
	{
		//Config_VariableList// 
	};
	Sns_model_Config_Var_str Config_Var;//ģ�������ʼ�����ò��������ṹ

	//ģ�ͷ������ͳ�����ݱ���
	struct Sns_model_Stats_Var_str 
	{
		//Stats_VariableList//
	}; 
	Sns_model_Stats_Var_str Stats_Var;//ģ�ͷ������ͳ�����ݱ����ṹ  

	//������Ϣ�¼�����
	enum 
	{
		//MesInputVariable//
	};

	//�����Ϣ�¼�����
	enum 
	{
		//MesOutputVariable//
	};

public://�û��Զ��幫�б���
	
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
private: //�û��Զ���˽�б���
	
public://ģ�͵����Զ����ɵĹ��к���

	Sns_Node_Virtual();
	virtual ~Sns_Node_Virtual();
	
	//����:��Ϣ������,����ģ�������¼�,������Ӧ����,������
	void SNS_Node_MsgDeal(Sns_Message *msg);
	
   //����:ģ�ͳ�ʼ������,��ȡģ�Ͷ�Ӧ�����ļ�,����ģ�ͳ�ʼ�����ò���
    void Node_init();
    
   //����:�ڵ��ʼ����Ĵ�����,������ʱ��Ҫ���нڵ㶼��ʼ����ɲſ�ִ�еĶ���
	void Node_init_end();

	//����:����ڵ�ģ���ڷ���������һЩ��,��ڵ�ģ�ͷ����������
	void SNS_Simulate_End_Node();	
	
public: //ģ�͵����Զ����ɺ���,�û������¼�����
	//Sns_Msg_In_Func//

private://ģ�͵����Զ����ɵ�˽�к���

	//����:��¼��ģ�͵����״̬����ֵ��StatsVar_Output��
	void SNS_Record_Stats_Value();

	//����:��ʼ�����ڵ����л���/Э��ģ��
	void Model_OfNode_Init();

	//����:����һ������Ϣ
	//����:DestiNode--��ϢĿ�Ľڵ��ַ,ModelId--������Ϣ��ģ��ID,instanceId--����ģ��ʵ����,EventName--��Ϣ�¼�����,
	//     EventType--�¼�����,PayLoad--��Ϣ�غ�,PacketSize--��Ϣ�غɴ�С,TimeDelay--�����ӳ�
	//     ���Ϳ���Ϣʱ��PayLoad=NULL��PacketSize=0
	void Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay);

	//����:��һ����Ϣת������Ӧ��ģ��
	//����:msg-ת������Ϣ��DestiNode--������ϢĿ�Ľڵ��ַ,ModelId--������Ϣ��ģ��ID,instanceId--����ģ��ʵ����,EventName--������Ϣ�¼�����,
	//     EventType--�����¼�����,TimeDelay--�����ӳ�
	void Send_Aexisting_Msg(Sns_Message *msg,int DestiNode,int ModelId,int instanceId,int EventName,int EventType, clocktype  TimeDelay);

public://�û��Զ��幫�к���

	int GetOtherNodeIdfromAddress(unsigned address,unsigned mask=0xffffffff);

	void sendIpv4Packet(unsigned dstAddr, char* packet, int packetSize, clocktype delay = 0);
private://�û��Զ���˽�к���

};

#endif
