/*
* Copyright (c) 2014,�������պ����ѧ
* All rights reserved.
*
* ϵͳ����: SPACE NETWORK SIMULATION SYSTEM
* ��    ��: ����
* ��ǰ�汾: SNS 1.0
* 
* �ļ�����: Sns_Model_NetworkIP.h
* ��ǰ�汾: V 1.0.0
* �ļ���ʶ: Sns_Model_NetworkIP��ͷ�ļ�
* ��������: �����IPЭ��ģ��
* �� �� ��: ����
* ��ϵ��ʽ: 
* �������: 
*
* ժ    Ҫ:
*/
//////////////////////////////////////////////////////////////////////

#ifndef SNS_MODEL_NETWORK_IP_H
#define SNS_MODEL_NETWORK_IP_H

#if _MSC_VER > 1000
#pragma once
#endif

/////////////������Ϊģ�Ͳ�����������/////////////
/************************************************
***Model-Info-Begin
/************************************************
**Model_Name:Network_IP;          //ģ����
**Class_Name:Sns_Model_NetworkIP;          //ģ������Ӧ������
**Model_Type:protocols/environment;          //ģ�����ͣ��������ڵ㡢������Э��
**ModelState:proceeding;         //ģ�Ϳ���״̬�����С���ɡ�ע��
**Abstract:
/***********************************************
**Config-Init-Variable:          //ģ�ͳ�ʼ�����ò���
/*Config_VariableList_Descri
/***********************************************
**StatsData-Output-Variable:   //ģ�����ͳ������
*int,numPacketsSentToMac;			//����MAC�����ݰ����� 
*int,numPacketsRoutedForOtherNodes;			//·�ɵ������ڵ�����ݰ����� 
*int,numPacketsDeliveredToThisNode;			//���ڵ���յ����ݰ����� 
*int,deliveredPacketTtlTotal;			//���ڵ���յ����ݰ������� 
*int,numNetworkUnreachableDrops;			//�����Ҳ���·�ɶ��������� 
*int,numTtlExpirationDrops;			//����ttl�������������� 
/*Stats_VariableList_Descri
/************************************************
**SnsMsg-Input:                  //�����¼�
*MSG_InEVENT_NETWORK_FromTransport;			//���Դ����Э������ݰ� 
*MSG_InEVENT_NETWORK_FromMAC;			//������·��Э������ݰ� 
*MSG_InEVENT_NETWORK_UpdateRoutable;			//·�ɱ�����¼� 
/*MesInputVariable_Descri
/************************************************
**SnsMsg-Output:                 //����¼�
*MSG_OutEVENT_NETWORK_ToMAC;			//������·������ݰ� 
*MSG_OutEVENT_NETWORK_ToTransport;			//�������������ݰ� 
/*MesOutputVariable_Descri
/***********************************************
***Model-Info-End
***********************************************/

#include "SNS_core.h" //ƽ̨��
#include "GlobleStructures.h"
#include "ForwardingTable.h"
#include "Sat_User_Relation.h"

class Sns_Config_Input;
class Sns_Message;
class Sns_Scenarios;

//ip Э�鳣������
#define MAX_IP_FRAGMENTS_SIMPLE_CASE        64
#define NETWORK_IP_FRAG_UNIT       2048 
#define FORWARDING_TABLE_ROW_START_SIZE 8
#define ANY_DEST 0xfffffff
#define OSPFv2_ALL_SPF_ROUTERS    0xE0000005
#define IP_MAXPACKET    65535       /* maximum packet size */
#define GET_INTERFACE_FROM_TABLE  0xFFFF
#define NETWORK_UNREACHABLE   -2
#define NETWORK_IP_REASS_BUFF_TIMER 15   //��λ��
#define SMALL_REASSEMBLY_BUFFER_SIZE  2048
#define REASSEMBLY_BUFFER_EXPANSION_MULTIPLIER  8
#define IP_MIN_HEADER_SIZE 20
#define IP_MAX_HEADER_SIZE 124
#define IPDEFTTL    64      // default ttl, from RFC 1340 
#define MAX_NW_PKT_SIZE       2048


class Sns_Model_NetworkIP : public Sns_base_model
{  
public://ģ�͵����Զ����ɵĹ��б���

	Sns_Scenarios * Scenarios_Data;   	//��ģ�������ĳ���
	unsigned Cur_Node_id;               //��ģ�������Ľڵ�id

	/////����ģ�������ļ���ʾ�ʹ���
	unsigned Cur_Node_id_inOneType;     //��ģ�������Ľڵ��ڸýڵ������е����к�
	char*  Cur_Node_Name;				//��ģ�������ڵ�����
	Sns_Config_Input * Config_Input;  	//�洢�����ļ�����
	char *ConfFile_Path;                //�����ļ�·��,�ɳ�����ʼ�������
	/////����ģ�������ļ���ʾ�ʹ���end

	Sns_Config_Input * StatsVar_Output;  	//�洢ģ�����״̬������ֵ

public: //ģ�͵����Զ����ɱ���

	//ģ�������ʼ�����ò�������
	struct Sns_model_Config_Var_str
	{
		//Config_VariableList//
	};
	Sns_model_Config_Var_str Config_Var;//ģ�������ʼ�����ò��������ṹ

	//ģ�ͷ������ͳ�����ݱ���
	struct Sns_model_Stats_Var_str 
	{
		int numPacketsSentToMac;			//����MAC�����ݰ�����
		int numPacketsRoutedForOtherNodes;			//·�ɵ������ڵ�����ݰ�����
		int numPacketsDeliveredToThisNode;			//���ڵ���յ����ݰ�����
		int deliveredPacketTtlTotal;			//���ڵ���յ����ݰ�������
		int numNetworkUnreachableDrops;			//�����Ҳ���·�ɶ���������
		int numTtlExpirationDrops;			//����ttl��������������
		//Stats_VariableList//
	}; 
	Sns_model_Stats_Var_str Stats_Var;//ģ�ͷ������ͳ�����ݱ����ṹ  

	//������Ϣ�¼�����
	enum 
	{
		MSG_InEVENT_NETWORK_FromTransport,			//���Դ����Э������ݰ� 
		MSG_InEVENT_NETWORK_FromMAC,			//������·��Э������ݰ� 
		MSG_InEVENT_NETWORK_FromOSPFv2,			//����OSPFЭ������ݰ� 
		MSG_InEVENT_NETWORK_UpdateRoutable,			//·�ɱ�����¼� 
		MSG_InEVENT_NETWORK_IsMyIMI,
		MSG_InEVENT_NETWORK_NotMyIMI,
		//MesInputVariable//
	};

	//�����Ϣ�¼�����
	enum 
	{
		MSG_OutEVENT_NETWORK_ToMAC,			//������·������ݰ� 
		MSG_OutEVENT_NETWORK_ToTransport,			//�������������ݰ� 
		MSG_OutEVENT_NETWORK_ToProtocol_OSPFv2,			//����OSPF·��Э��İ� 
		MSG_OutEVENT_NETWORK_ToProtocol_LocalRoute,
		MSG_OutEVENT_NETWORK_ISMYIMI,
		//MesOutputVariable//
	};

public://�û��Զ��幫�б���
	enum
	{
	PROTOCOL_PACKET,
	PROTOCOL_OSPFv2,
	PROTOCOL_LOCAL_ROUTE,
	};
	typedef struct ip    //ip��ͷ
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

	struct NetworkForwardingTableRow   //·�ɱ��нṹ
	{
		unsigned destAddress;       /* destination address */
		short interfaceIndex;    /* right now interface Id */
		unsigned nextHopAddress;    /* next hop. */
	};

	struct NetworkForwardingTable  //·�ɱ�
	{
		int size;  /* number of entries */
		int allocatedSize;
		NetworkForwardingTableRow *row;  /* allocation in Init function in Ip */
	};

	struct IpReassemblyBufferType//������ݽṹ
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

	int maxPacketLength;     //��ģ�ʹ������������
	NetworkForwardingTable     forwardTable;    //·�ɱ�

	IpReassemblyBufferListType reassemblyBufferList;   //��֡����

	int numberInterfaces;
	InterfaceInfoType* interfaceInfo;
	ForwardingTable* forwardingTable;
private://�û��Զ���˽�б���
	unsigned short    packetIdCounter; // ���ڵ������IP����ˮ�� 

public://ģ�͵����Զ����ɹ��к���

	Sns_Model_NetworkIP();  
	~Sns_Model_NetworkIP(); 

	//����:ģ�ͳ�ʼ������,��ȡģ�Ͷ�Ӧ�����ļ�,����ģ�ͳ�ʼ�����ò���
	void Model_init();

	//����:�ڵ��ʼ����Ĵ�����,������ʱ��Ҫ���нڵ�����ģ�Ͷ���ʼ����ɲſ�ִ�еĶ���
	void Model_init_end();

	//����:����Э��򻷾�ģ���ڷ���������һЩ��,��ģ�ͷ����������
	void SNS_Simulate_End_Model();

	//����:��Ϣ������,����ģ�������¼�,������Ӧ����,������
	void SNS_Model_MsgDeal(Sns_Message *msg);								

public://ģ�͵����Զ����ɺ���,�û������¼�����

	//����:Msg_InEvent_NETWORK_FromTransport�¼�����,�������Դ�������Ϣ������ 
	void Msg_InEvent_NETWORK_FromTransport(Sns_Message *msg); 

	//����:MSG_InEVENT_NETWORK_FromMAC�¼�����,��������·������ݰ�,������ 
	void Msg_InEvent_NETWORK_FromMAC(Sns_Message *msg); 

	//����:MSG_InEVENT_NETWORK_UpdateRoutable�¼�����,����·�ɸ�����Ϣ,����IPЭ��·�ɱ� 
	void Msg_InEvent_NETWORK_UpdateRoutable(Sns_Message *msg); 

	void Msg_InEvent_NETWORK_FromOSPFv2(Sns_Message* msg);

	void Msg_InEvent_NETWORK_isMyIMI(Sns_Message* msg);

	void Msg_InEvent_NETWORK_notMyIMI(Sns_Message* msg);
	//Sns_Msg_In_Func//

private://ģ�͵����Զ�����˽�к���

	//����:��¼��ģ�͵����״̬����ֵ��StatsVar_Output��
	void SNS_Record_Stats_Value();

	//����:����һ������Ϣ
	//����:DestiNode--��ϢĿ�Ľڵ��ַ,ProtocolId--������Ϣ��ģ��ID,EventName--��Ϣ�¼�����,
	//     EventType--�¼�����,PayLoad--��Ϣ�غ�,PacketSize--��Ϣ�غɴ�С,TimeDelay--�����ӳ�
	void Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay);


public://�û��Զ��幫�к���


private://�û��Զ���˽�к���
#define SetBit(BitVector, Index)  BitVector[(Index)/8] |= (1 << ((Index) % 8))
#define BitIsSet(BitVector, Index)  ((BitVector[(Index)/8] & (1 << ((Index) % 8))) != 0)

	//����:Ϊһ�����ݰ�����IP��ͷ,�ú������޸�һ������MSG�ĸ���,�Լ����ش�С�Ͱ�ͷ��С3������
	//����:msg:��Ҫ��ipͷ����Ϣ,Ҫ���и���;destAdd:Ŀ�ĵ�ַ;priority:���ȼ�
	//     protocol:�ϲ�Ӧ��Э��;ttl:������
	void Add_IpHeader(Sns_Message *msg, unsigned srcAddr,unsigned destAdd, unsigned priority, unsigned char protocol, unsigned ttl);

	////////////////////////////////////���ݰ���֡����,��·��ת�����͸���·�����ش���////////////////////////////////////

	//����:����������·�㴦��������
	void RoutePacketAndSendToMac(Sns_Message *msg);

	//����:����Ϣ������Ӧ�˿ڵ���·��Э��,����Ϣ�ڰ���С������·��֡��С,����Ҫ���
	void Packet_SendToMacLayer(Sns_Message *msg, short interfaceIndex, unsigned nextHop,unsigned srcAddr);

	//����:���Ѵ��������Ϣ(���������)������Ӧ�˿ڵ���·��Э��
	void IpFragmentToMacLayer(Sns_Message *msg, short interfaceIndex, unsigned nextHop,unsigned srcAddr);

	//����:���·��������
	void LookupTableRoute_Packet(Sns_Message *msg);

	//����:��·�ɱ�,����Ŀ�ĵ�ַ,��ȡ��һ����ַ��ת���˿�
	void GetInterfAndNextH_FromFTable(unsigned destAdd, short *interfaceIndex, unsigned *nextHopAdd);

	////////////////////////////////////���ݰ���֡����,��·��ת�����͸���·�����ش��� end////////////////////////////////////

	////////////////////////////////////������·������֡,��֡����////////////////////////////////////

	//����:��֡������
	void ProcFragment_BuildCompPacket(Sns_Message *msg, bool *packetIsComplete, Sns_Message **completedPacket);

	//����:�ж��Ƿ���ĳ����һ����������֡,�Ƿ����ǰ���֡,�����洢��RBufList
	void IpRBufList_FindOrCreate(IpReassemblyBufferListType *RBufList, Sns_Message *P_Fragment, IpReassemblyBufferType **FragBufferPtr, bool *Buf_isFound);

	//����:�ж�����֡�Ƿ�����ͬһ��
	bool IsIpFragmentOf(Sns_Message *msg1, Sns_Message *msg2);

	//����:RBufList������һ������,�������ڴ�
	void IpRBufList_AddNewBuf(IpReassemblyBufferListType *RBufList, IpReassemblyBufferType **RBufPtr);

	//����:��RBufList�������м���һ�µ�֡,����ʼ��
	void Init_ReassemblyBuf(IpReassemblyBufferType *reassemblyBuffer, Sns_Message *msg);

	//����:��һ��������֡,����ǰ����RBufList�������֡һ����֡
	void AddFragment_ReassemblyBuf(IpReassemblyBufferType *reassemblyBuffer, Sns_Message *msg, bool *packetIsComplete, Sns_Message **completedPacket);

	//����:���֡�ڴ治��,����8��
	void ExpandReassemblyBuffer(IpReassemblyBufferType *reassemblyBuffer, int minSize);

	//����:�ж��Ƿ������������ݰ���
	void Check_BufIsCompletion(IpReassemblyBufferType *reassemblyBuffer, bool *packetIsComplete);

	//����:��֡������,��ȥ�����е��ڴ�
	void Remove_ExpiredIpRBuf(IpReassemblyBufferListType *reassemblyBufferList, clocktype currentTime);

	bool ReassemblyBuf_IsExpired(IpReassemblyBufferType *reassemblyBuf, clocktype curTime);

	//����:��֡������,ɾ������
	void IpReassemblyBufList_Del(IpReassemblyBufferListType *reassemblyBufferList, IpReassemblyBufferType **reassemblyBufferPtr);

	////////////////////////////////////������·������֡,��֡���� end////////////////////////////////////

	//����:�����ݰ������ϲ�Э��,����ȥ��ͷ,���͵�������,������
	void ProcessPacketForMeFromMac(Sns_Message *msg);

	//����:ȥ��ͷ
	void Remove_IpHeader(Sns_Message *msg, unsigned *sourceAdd, unsigned *destAdd, unsigned *priority, unsigned char *protocol, unsigned int *ttl);

	//����:�����ݰ����͵������
	void IpPacketToTransport(Sns_Message *msg, unsigned priority, unsigned sourceAdd, unsigned destAdd);

	//����:�����ݰ�·�ɲ����͸���·�㷢��
	void ProcessPacketForAnotherFromMac(Sns_Message *msg);

	////////////////////////////////////·�ɱ���////////////////////////////////////

	//����:·�ɱ��ʼ��
	void NetworkInitForwardingTable();

	//����:·�ɱ����
	void NetworkUpdateForwardingTable(unsigned destAddress, short interfaceIndex, unsigned nextHopAddress);

	//����:·�ɱ��ӡ
	void Print_ForwardingTable();

	//����:·�ɱ��ӡ���ļ�
	void fPrint_ForwardingTable(FILE *out_file);

	////////////////////////////////////·�ɱ���////////////////////////////////////

	void ProcessPacketForNextHop(Sns_Message* msg,int interfaceIndex);
	void ProcessPacketForOspfv2(Sns_Message* msg,unsigned srcAddr,unsigned dstAddr);
	void ProcessPacketForLocalRoute(Sns_Message* msg,unsigned srcAddr,unsigned dstAddr);
	void initVals(int numberInterfaces,InterfaceInfoType* interfaceInfo);
	bool isMyInterface(unsigned address);
	int myInterfaceNextHop(unsigned address);
};  
#endif 
