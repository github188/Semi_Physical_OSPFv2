/*
* Copyright (c) 2014,�������պ����ѧ
* All rights reserved.
*
* ϵͳ����: SPACE NETWORK SIMULATION SYSTEM
* ��    ��: ����
* ��ǰ�汾: SNS 1.0
* 
* �ļ�����: Sns_Model_NetworkIP.cpp
* ��ǰ�汾: V 1.0.0
* �ļ���ʶ: Sns_Model_NetworkIP��Դ�ļ�
* ��������: 
* �� �� ��: ����
* ��ϵ��ʽ: 
* �������: 
*
* ժ    Ҫ:
*/
//////////////////////////////////////////////////////////////////////

////////////////������Ϊģ�͵����Զ�����////////////////

#include "StdAfx.h"              //����c++��
#include "Sns_Config_Input.h"   //ƽ̨��
#include "Sns_Message.h"        //ƽ̨��

#include "Sns_Scenarios.h"
#include "Sns_Model_NetworkIP.h"
#include "Sns_Model_OSPFv2.h"

/////////������Ϊģ�͵����Զ����� end �û���Ҫ�ӵĶ���������/////////////


Sns_Model_NetworkIP::Sns_Model_NetworkIP()  
{  
	///////////���������ʼ��,ģ���Զ�����////////////////////////

	Stats_Var.numPacketsSentToMac = 0;
	Stats_Var.numPacketsRoutedForOtherNodes = 0;
	Stats_Var.numPacketsDeliveredToThisNode = 0;
	Stats_Var.deliveredPacketTtlTotal = 0;
	Stats_Var.numNetworkUnreachableDrops = 0;
	Stats_Var.numTtlExpirationDrops = 0;
	//Stats_Variable_Init//		

	///////////���������ʼ��,ģ���Զ����� end �û���Ҫ�ӵĶ���������//////////

	maxPacketLength = NETWORK_IP_FRAG_UNIT;

	NetworkInitForwardingTable();

	reassemblyBufferList.firstPtr = NULL;
	reassemblyBufferList.freeListPtr = NULL;

}  

Sns_Model_NetworkIP::~Sns_Model_NetworkIP()  
{  
	xdelete(Config_Input);
	Config_Input = NULL;
	xfree(Cur_Node_Name);
	Cur_Node_Name = NULL;
	xfree(ConfFile_Path);
	ConfFile_Path = NULL;
}  

//////////////////////////////////Э���ʼ������/////////////////////////////////////
void Sns_Model_NetworkIP::Model_init()  
{  
	//////////�������ļ��ж�ȡ��ʼ������,ģ�͵����Զ�����//////////////////////////

	char ModelName[SNS_MAX_STRING_LENGTH];	//�����ļ���ģ��ʶ���־
	char buf[SNS_MAX_STRING_LENGTH];		//��ȡ�����ļ��е��ַ���

	int RetArrNum;			//��ȡ������������ֵ
	bool retVal = false;	//��������ֵ

	Config_Input = new Sns_Config_Input();	//����һ�������ļ��������

	sprintf(ModelName,"%s[%d]-Sns_Model_NetworkIP[%d]",Cur_Node_Name,Cur_Node_id_inOneType,Model_Instance_id);//��ʾ��ǰ�ڵ�,��ǰģ��,ģ�Ϳ�����ͬ�����,��Ϊ0,���ʾΨһ
	Config_Input->SNS_Read_ModelConf(ConfFile_Path, ModelName);//��ȡ��ģ�͵����ò���

	//Config_Variable_Init//
	//////////�������ļ��ж�ȡ��ʼ������,ģ�͵����Զ����� end �û���Ҫ�ӵĶ���������////////////////////


}  

//����:�ڵ��ʼ����Ĵ�����,������ʱ��Ҫ���нڵ�����ģ�Ͷ���ʼ����ɲſ�ִ�еĶ���
void Sns_Model_NetworkIP::Model_init_end()
{

}

////////////////////////////////////��Ϣ������////////////////////////////////////
//����:��Ϣ������,����ģ�������¼�,������Ӧ����,������
void Sns_Model_NetworkIP::SNS_Model_MsgDeal(Sns_Message *msg)  
{  
	switch(msg->Event_Name) //��Ϣ�¼�ö��
	{
	case MSG_InEVENT_NETWORK_FromTransport:
		{
			Msg_InEvent_NETWORK_FromTransport(msg);

			break;
		}
	case MSG_InEVENT_NETWORK_FromMAC:
		{
			Msg_InEvent_NETWORK_FromMAC(msg);

			break;
		}
	case MSG_InEVENT_NETWORK_FromOSPFv2:
		{
			Msg_InEvent_NETWORK_FromOSPFv2(msg);
			break;
		}
	case MSG_InEVENT_NETWORK_UpdateRoutable:
		{
			Msg_InEvent_NETWORK_UpdateRoutable(msg);

			break;
		}
	case MSG_InEVENT_NETWORK_IsMyIMI:
		{
			Msg_InEvent_NETWORK_isMyIMI(msg);

			break;
		}
	case MSG_InEVENT_NETWORK_NotMyIMI:
		{
			Msg_InEvent_NETWORK_notMyIMI(msg);

			break;
		}
		//SNS_MSG_EVENT_IN//
	default:

		break;
	}
}  

////////////////////////////�������������//////////////////////////////////////////////
//����:����Э��򻷾�ģ���ڷ���������һЩ��,��ģ�ͷ����������
void Sns_Model_NetworkIP::SNS_Simulate_End_Model()
{
	SNS_Record_Stats_Value();
}

//����:��¼��ģ�͵����״̬����ֵ��StatsVar_Output��
void Sns_Model_NetworkIP::SNS_Record_Stats_Value()
{
	bool retVal = false;	//��������ֵ
	char Stats_ModelName[SNS_MAX_STRING_LENGTH]; //���ڼ�¼���״̬��������ģ������־

	sprintf(Stats_ModelName,"\n** %s[%d]-Sns_Model_NetworkIP[%d]_begin\n",Cur_Node_Name,Cur_Node_id_inOneType,Model_Instance_id);//��ģ�����״̬����ֵ��¼��ʼ
	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);//��Stats_ModelNameд������

	/////////////////////////////����ģ���������״̬����ֵд������//////////////////////////

	retVal = StatsVar_Output->SNS_Record_A_Int("int,numPacketsSentToMac", 1 , &Stats_Var.numPacketsSentToMac);
	assert(retVal == true);

	retVal = StatsVar_Output->SNS_Record_A_Int("int,numPacketsRoutedForOtherNodes", 1 , &Stats_Var.numPacketsRoutedForOtherNodes);
	assert(retVal == true);

	retVal = StatsVar_Output->SNS_Record_A_Int("int,numPacketsDeliveredToThisNode", 1 , &Stats_Var.numPacketsDeliveredToThisNode);
	assert(retVal == true);

	retVal = StatsVar_Output->SNS_Record_A_Int("int,deliveredPacketTtlTotal", 1 , &Stats_Var.deliveredPacketTtlTotal);
	assert(retVal == true);

	retVal = StatsVar_Output->SNS_Record_A_Int("int,numNetworkUnreachableDrops", 1 , &Stats_Var.numNetworkUnreachableDrops);
	assert(retVal == true);

	retVal = StatsVar_Output->SNS_Record_A_Int("int,numTtlExpirationDrops", 1 , &Stats_Var.numTtlExpirationDrops);
	assert(retVal == true);

	//Stats_Variable_Record//
	/////////////////////////////����ģ���������״̬����ֵд������//////////////////////////

	sprintf(Stats_ModelName,"\n** %s[%d]-Sns_Model_NetworkIP[%d]_end\n",Cur_Node_Name,Cur_Node_id_inOneType,Model_Instance_id);//��ģ�����״̬����ֵ��¼����
	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);//��Stats_ModelNameд������
}

////////////////////////////////////����һ������Ϣ////////////////////////////////////

//����:����һ������Ϣ
//����:DestiNode--��ϢĿ�Ľڵ��ַ,ProtocolId--������Ϣ��ģ��ID,EventName--��Ϣ�¼�����,
//     EventType--�¼�����,PayLoad--��Ϣ�غ�,PacketSize--��Ϣ�غɴ�С,TimeDelay--�����ӳ�
void Sns_Model_NetworkIP::Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay)
{
	Sns_Message *msg = new Sns_Message();//����һ����Ϣ����

	msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,PayLoad,PacketSize);//Ϊ��Ϣ��ֵ

	Scenarios_Data->SNS_Msg_Send(msg,DestiNode,TimeDelay);//������Ϣ
}

////////////////////////////////////////�û������¼�������//////////////////////

//����:Msg_InEvent_NETWORK_FromTransport�¼�����,�������Դ�������Ϣ������ 
void Sns_Model_NetworkIP:: Msg_InEvent_NETWORK_FromTransport(Sns_Message *msg) 
{
	TransportToNetworkInfo* info;

	info = (TransportToNetworkInfo*)msg->Info_Msg;
	Add_IpHeader(msg, interfaceInfo[0].address,info->destinationAddr, info->priority, info->Protocol_ToIP, 0);//����IP��ͷ

	RoutePacketAndSendToMac(msg);
}

//����:MSG_InEVENT_NETWORK_FromMAC�¼�����,��������·������ݰ�,������ 
void Sns_Model_NetworkIP:: Msg_InEvent_NETWORK_FromMAC(Sns_Message *msg) 
{
	IpHeaderType *ipHeader = (IpHeaderType *) msg->Pay_Load;  
	int interfaceIndex=myInterfaceNextHop(ipHeader->ip_dst);
	ipHeader->ip_ttl = ipHeader->ip_ttl - 1;

	if ((ipHeader->ip_dst == ANY_DEST) ||(ipHeader->ip_dst == OSPFv2_ALL_SPF_ROUTERS)|| isMyInterface(ipHeader->ip_dst)) //����Ǳ��ڵ�����ݰ�
	{
		bool packetIsComplete = true;
		Sns_Message* completePacket = NULL;

		if((ipHeader->ip_more_fragments == 1)||(ipHeader->ip_fragment_offset != 0))
		{ 
			ProcFragment_BuildCompPacket(msg, &packetIsComplete, &completePacket); 
			xdelete(msg);
			msg = NULL;
		} 
		else 
		{
			completePacket = msg;
		}//if// 
		if (packetIsComplete) 
		{
			ProcessPacketForMeFromMac(completePacket);
		}//if//     
	} 
	else if(interfaceIndex!=-1)
	{
		ProcessPacketForNextHop(msg,interfaceIndex);
	}
	else
	{
		ProcessPacketForAnotherFromMac(msg);
	}//if//
}

//����:MSG_InEVENT_NETWORK_UpdateRoutable�¼�����,����·�ɸ�����Ϣ,����IPЭ��·�ɱ� 
void Sns_Model_NetworkIP:: Msg_InEvent_NETWORK_UpdateRoutable(Sns_Message *msg) 
{
	NetworkForwardingTableRow * route_tablerow;
	route_tablerow = (NetworkForwardingTableRow *)msg->Pay_Load;
	NetworkUpdateForwardingTable(route_tablerow->destAddress, route_tablerow->interfaceIndex, route_tablerow->nextHopAddress);
	Print_ForwardingTable();
	xdelete(msg);
	msg = NULL;
}
//Sns_Msg_In_Func//
void Sns_Model_NetworkIP::Msg_InEvent_NETWORK_FromOSPFv2(Sns_Message* msg)
{
	Sns_Model_OSPFv2::NetworkToMACInfo* info = (Sns_Model_OSPFv2::NetworkToMACInfo*)msg->Info_Msg;
	Add_IpHeader(msg, info->srcAddr,info->dstAddr, 0,PROTOCOL_OSPFv2, 0);//����IP��ͷ
	if(info->dstAddr==ANY_DEST||info->dstAddr==OSPFv2_ALL_SPF_ROUTERS)
		Packet_SendToMacLayer(msg, info->interfaceIndex, ANY_DEST,info->srcAddr);
	else
		Packet_SendToMacLayer(msg, info->interfaceIndex, info->dstAddr,info->srcAddr);
	//RoutePacketAndSendToMac(msg);
}

void Sns_Model_NetworkIP::Msg_InEvent_NETWORK_isMyIMI(Sns_Message* msg)
{
	NetworkToMACInfo* info=(NetworkToMACInfo*)msg->Info_Msg;
	IpFragmentToMacLayer(msg, info->interfaceIndex, info->nexthopaddr,info->srcAddr);
}

void Sns_Model_NetworkIP::Msg_InEvent_NETWORK_notMyIMI(Sns_Message* msg)
{
	NetworkToMACInfo* info=(NetworkToMACInfo*)msg->Info_Msg;
	msg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_OutEVENT_NETWORK_ToProtocol_LocalRoute,SNS_MSG_OUTPUT,NULL,-1);
	Scenarios_Data->SNS_Msg_Send(msg,Cur_Node_id,0);
}

////////////////////////////////////////�û������¼������� end//////////////////////

//����:Ϊһ�����ݰ�����IP��ͷ,�ú������޸�һ������MSG�ĸ���,�Լ����ش�С�Ͱ�ͷ��С3������
//����:msg:��Ҫ��ipͷ����Ϣ,Ҫ���и���;destAdd:Ŀ�ĵ�ַ;priority:���ȼ�
//     protocol:�ϲ�Ӧ��Э��;ttl:������
void Sns_Model_NetworkIP::Add_IpHeader(Sns_Message *msg, unsigned srcAddr,unsigned destAdd, unsigned priority, unsigned char protocol, unsigned ttl)
{
	IpHeaderType* ipHeader;
	int Size;

	Size = sizeof(IpHeaderType);
	ipHeader = (IpHeaderType*)malloc(Size);
	memset(ipHeader, 0, Size);

	//ip ��ͷ��ֵ
	ipHeader->ip_id = packetIdCounter;
	packetIdCounter++;
	//ipHeader->ip_src = Cur_Node_id;
	ipHeader->ip_src=srcAddr;
// 	if(interfaceIndex==-1)
// 		ipHeader->ip_src=ANY_DEST;
// 	else
// 		ipHeader->ip_src=interfaceInfo[interfaceIndex].address;
	ipHeader->ip_dst = destAdd;
	if (ttl == 0) 
	{
		ipHeader->ip_ttl = IPDEFTTL; 
	} 
	else 
	{
		ipHeader->ip_ttl = ttl;
	}
	ipHeader->ip_tos = priority;
	ipHeader->ip_p = protocol;

	assert(msg->PayLoad_Size <= IP_MAXPACKET);
	ipHeader->ip_len = msg->PayLoad_Size + Size;

	ipHeader->ip_hl = (Size) / 4; 
	assert(((Size) % 4 == 0) && (Size >= IP_MIN_HEADER_SIZE) && (Size <= IP_MAX_HEADER_SIZE));   

	//��Ӱ�ͷ
	msg->SNS_Msg_Packet_AddHeader((char*)ipHeader,Size);
	xfree(ipHeader);
	ipHeader = NULL;
}

////////////////////////////////////���ݰ���֡����,��·��ת�����͸���·�����ش���////////////////////////////////////

//����:����������·�㴦��������
void Sns_Model_NetworkIP::RoutePacketAndSendToMac(Sns_Message *msg)
{
	IpHeaderType *ipHeader = (IpHeaderType *) msg->Pay_Load;
	//
	// Check if its a broadcast.
	//
	if (ipHeader->ip_dst == ANY_DEST) //��·�㲥
	{
		Packet_SendToMacLayer(msg, -1, ANY_DEST,ipHeader->ip_src);
	} 
	else if(ipHeader->ip_dst==OSPFv2_ALL_SPF_ROUTERS)
	{
		Sns_Model_OSPFv2::NetworkToMACInfo* info=(Sns_Model_OSPFv2::NetworkToMACInfo*)msg->Info_Msg;
		Packet_SendToMacLayer(msg, info->interfaceIndex, ANY_DEST,ipHeader->ip_src);
	}
	else//�ǹ㲥 
	{
		LookupTableRoute_Packet(msg);
	}
}

//����:����Ϣ������Ӧ�˿ڵ���·��Э��,����Ϣ�ڰ���С������·��֡��С,����Ҫ���
void Sns_Model_NetworkIP::Packet_SendToMacLayer(Sns_Message *msg, short interfaceIndex, unsigned nextHop,unsigned srcAddr)
{
	IpHeaderType* ipHeader = (IpHeaderType *) msg->Pay_Load;  

	if (ipHeader->ip_len <= unsigned int(maxPacketLength)) 
	{
		IpFragmentToMacLayer(msg, interfaceIndex, nextHop,srcAddr);
	} 
	else 
	{
		int ipHeaderSize = ipHeader->ip_hl *4;
		int packetIndex = ipHeaderSize;

		//
		// Send the packet by splitting it into fragments of 
		// maximum IP fragment size.
		//        

		while (packetIndex < int(ipHeader->ip_len)) 
		{
			// 
			// Figure out the packet fragment's size and create it.

			int lastIndex;
			int fragmentSize;
			int fragmentDataSize = maxPacketLength - ipHeaderSize;
			char *fragmentpload = NULL;         
			IpHeaderType* fragIpHeader = NULL;
			Sns_Message* fragment = new Sns_Message();

			if (unsigned int(packetIndex + fragmentDataSize) >= ipHeader->ip_len) 
			{
				//
				// Its the last fragment.
				//
				lastIndex = ipHeader->ip_len - 1;
				fragmentSize = ipHeaderSize + (lastIndex - packetIndex + 1);
			} 
			else 
			{
				//
				// Shrink fragment data portion to be divisable by 8.
				//
				fragmentDataSize = ((fragmentDataSize/8) * 8);
				fragmentSize = ipHeaderSize + fragmentDataSize;
				lastIndex = packetIndex + fragmentDataSize - 1;
			}//if//

			fragmentpload = (char *)malloc(fragmentSize);

			//
			// Copy the header (same for all fragments) into the packet.
			// Then the fragment's specific data.   The set the
			// fragment's header to specify which part of the packet's
			// data it contains.
			//

			memcpy(fragmentpload, msg->Pay_Load, ipHeaderSize);

			memcpy(&(fragmentpload[ipHeaderSize]),
				&(msg->Pay_Load[packetIndex]), 
				(fragmentSize - ipHeaderSize));

			fragIpHeader = (IpHeaderType *) fragmentpload;
			fragIpHeader->ip_len = fragmentSize;
			assert(((packetIndex - ipHeaderSize) % 8 == 0) && ((packetIndex - ipHeaderSize) < IP_MAXPACKET)); 
			fragIpHeader->ip_fragment_offset = ((packetIndex - ipHeaderSize)/8);
			if (lastIndex == int(ipHeader->ip_len - 1)) 
			{
				fragIpHeader->ip_more_fragments = false; 
			} 
			else 
			{
				fragIpHeader->ip_more_fragments = true; 
			}//if//

			fragment->Pay_Load = fragmentpload;
			fragment->PayLoad_Size = fragmentSize;
			fragment->Packet_HeadSize = ipHeaderSize;
			fragment->Track_PacketId = msg->Track_PacketId; //���ڰ�����
			fragment->Message_CreationTime = msg->Message_CreationTime; //���ڰ�����

			IpFragmentToMacLayer(fragment, interfaceIndex ,nextHop,srcAddr);

			packetIndex = lastIndex + 1;
		}//while//
		xdelete(msg);
		msg = NULL;
	}//if//
}

//����:���Ѵ��������Ϣ(���������)������Ӧ�˿ڵ���·��Э��
void Sns_Model_NetworkIP::IpFragmentToMacLayer(Sns_Message *msg, short interfaceIndex, unsigned nextHop,unsigned srcAddr)
{
	//��һЩ��Ϣͨ��info����Ӧ�ò�,��Щ��Ϣ����IP,��info����
	NetworkToMACInfo *info = (NetworkToMACInfo *)malloc(sizeof(NetworkToMACInfo));

	info->interfaceIndex = interfaceIndex;
	info->nexthopaddr = nextHop;
	info->srcAddr=srcAddr;

	msg->SNS_Msg_AddInfo((char *)info, sizeof(NetworkToMACInfo));
	xfree(info); 
	info = NULL;

	Stats_Var.numPacketsSentToMac++;

	//�޸Ĳ�����Ϣ����,Ϊ��ģ������¼�,�¼���ΪMSG_OutEVENT_NETWORK_ToMAC,msg�غɲ���
	msg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_OutEVENT_NETWORK_ToMAC,SNS_MSG_OUTPUT,NULL,-1);
	Sns_Message* newMsg=msg->SNS_Msg_Copy();
	Scenarios_Data->SNS_Msg_Send(newMsg,Cur_Node_id,0);//��Ϣ����,����ʱ��Ϊ0
	xdelete(msg);
}

//����:���·��������
void Sns_Model_NetworkIP::LookupTableRoute_Packet(Sns_Message *msg)
{
	IpHeaderType *ipHeader = (IpHeaderType *) msg->Pay_Load;

	short interfaceIndex;
	unsigned nextHop;

	GetInterfAndNextH_FromFTable(ipHeader->ip_dst, &interfaceIndex, &nextHop);

	//  printf("RouteThePacketUsingLookupTable nodeAddr = %d, ipHeader->ip_dst = %d,interfaceid = %d, nexthop = %d\n",node->nodeAddr, ipHeader->ip_dst,interfaceIndex, nextHop);

	if (nextHop == NETWORK_UNREACHABLE) 
	{
		Stats_Var.numNetworkUnreachableDrops++;
		xdelete(msg);
		msg = NULL;
		return; 
	}
	Packet_SendToMacLayer(msg, interfaceIndex, nextHop,ipHeader->ip_src);
}

//����:��·�ɱ�,����Ŀ�ĵ�ַ,��ȡ��һ����ַ��ת���˿�

void Sns_Model_NetworkIP::GetInterfAndNextH_FromFTable(unsigned destAdd, short *interfaceIndex, unsigned *nextHopAdd)
{
	int i;
	ForwardingTable::NetworkForwardingTable * routingTable = forwardingTable->getForwardingTable();

	*interfaceIndex = NETWORK_UNREACHABLE;
	*nextHopAdd = NETWORK_UNREACHABLE;

	for (i=0; (i < routingTable->size); i++) 
	{
		unsigned dstMasked=destAdd&routingTable->row[i].destAddressMask;
		unsigned maskedAddress=routingTable->row[i].destAddress&routingTable->row[i].destAddressMask;
		if ((routingTable->row[i].destAddress&routingTable->row[i].destAddressMask)
			== (destAdd&routingTable->row[i].destAddressMask)) 
		{
			*interfaceIndex = routingTable->row[i].interfaceIndex;
			*nextHopAdd = routingTable->row[i].nextHopAddress;
			break;
		}
	}
}

////////////////////////////////////���ݰ���֡����,��·��ת�����͸���·�����ش��� end////////////////////////////////////

////////////////////////////////////������·������֡,��֡����////////////////////////////////////

//����:��֡������
void Sns_Model_NetworkIP::ProcFragment_BuildCompPacket(Sns_Message *msg, bool *packetIsComplete, Sns_Message **completedPacket)
{
	IpReassemblyBufferType* reassemblyBuffer = NULL;
	bool foundAnExistingBuffer;   
	*packetIsComplete = false;

	IpRBufList_FindOrCreate(&reassemblyBufferList, msg, &reassemblyBuffer, &foundAnExistingBuffer);

	if (!foundAnExistingBuffer) 
	{
		Init_ReassemblyBuf(reassemblyBuffer, msg);
		Remove_ExpiredIpRBuf(&reassemblyBufferList, SimClock());
	} 
	else 
	{
		if (!ReassemblyBuf_IsExpired(reassemblyBuffer, SimClock())) 
		{
			AddFragment_ReassemblyBuf(reassemblyBuffer, msg, packetIsComplete, completedPacket);
			if (*packetIsComplete) 
			{
				IpReassemblyBufList_Del(&reassemblyBufferList, &reassemblyBuffer);     
			}//if//
		}//if//
	}//if//
}

//����:�ж��Ƿ���ĳ����һ����������֡,�Ƿ����ǰ���֡,�����洢��RBufList
void Sns_Model_NetworkIP::IpRBufList_FindOrCreate(IpReassemblyBufferListType *RBufList, Sns_Message *P_Fragment, IpReassemblyBufferType **FragBufferPtr, bool *Buf_isFound)
{
	IpReassemblyBufferListCellType* currentCellPtr = RBufList->firstPtr; 

	while ((currentCellPtr != NULL) &&
		(!IsIpFragmentOf(currentCellPtr->reassemblyBuffer.packetUnderConstruction, P_Fragment)))
	{
		currentCellPtr = currentCellPtr->nextPtr;
	}//while//

	if (currentCellPtr == NULL) 
	{
		*Buf_isFound = false;
		IpRBufList_AddNewBuf(RBufList, FragBufferPtr);
	} 
	else 
	{
		*Buf_isFound = true;
		(*FragBufferPtr) = &(currentCellPtr->reassemblyBuffer);
	}//if//
}

//����:�ж�����֡�Ƿ�����ͬһ��
bool Sns_Model_NetworkIP::IsIpFragmentOf(Sns_Message *msg1, Sns_Message *msg2)
{
	IpHeaderType* ipHeader1 = (IpHeaderType*)msg1->Pay_Load;
	IpHeaderType* ipHeader2 = (IpHeaderType*)msg2->Pay_Load;

	return ((ipHeader1->ip_id == ipHeader2->ip_id) &&
		(ipHeader1->ip_src == ipHeader2->ip_src) &&
		(ipHeader1->ip_p == ipHeader2->ip_p));
}

//����:RBufList������һ������,�������ڴ�
void Sns_Model_NetworkIP::IpRBufList_AddNewBuf(IpReassemblyBufferListType *RBufList, IpReassemblyBufferType **RBufPtr)
{
	IpReassemblyBufferListCellType* newCell = NULL;

	if (RBufList->freeListPtr == NULL) 
	{
		newCell = (IpReassemblyBufferListCellType*)malloc(
			sizeof(IpReassemblyBufferListCellType));
	} 
	else 
	{
		newCell = RBufList->freeListPtr;
		RBufList->freeListPtr = RBufList->freeListPtr->nextPtr;
	}//if//

	newCell->nextPtr = RBufList->firstPtr;
	RBufList->firstPtr = newCell;

	*RBufPtr = &newCell->reassemblyBuffer;
}

//����:��RBufList�������м���һ�µ�֡,����ʼ��
void Sns_Model_NetworkIP::Init_ReassemblyBuf(IpReassemblyBufferType *reassemblyBuffer, Sns_Message *msg)
{
	bool NotUsed;
	IpHeaderType* msgIpHeader = (IpHeaderType *) msg->Pay_Load;  
	int ipHeaderSize = msgIpHeader->ip_hl*4;
	IpHeaderType* bufferIpHeader = NULL;

	//
	// Allocate a message to act as a reassembly buffer.
	//
	reassemblyBuffer->sizeLimit = SMALL_REASSEMBLY_BUFFER_SIZE;

	reassemblyBuffer->packetUnderConstruction = new Sns_Message();
	reassemblyBuffer->packetUnderConstruction->Model_id = Model_id;
	reassemblyBuffer->packetUnderConstruction->Event_Name = msg->Event_Name;
	reassemblyBuffer->packetUnderConstruction->Event_Type = msg->Event_Type;

	reassemblyBuffer->packetUnderConstruction->Track_PacketId = msg->Track_PacketId; //���ڰ�����
	reassemblyBuffer->packetUnderConstruction->Message_CreationTime = msg->Message_CreationTime; //���ڰ�����

	reassemblyBuffer->packetUnderConstruction->Pay_Load = (char *)malloc(reassemblyBuffer->sizeLimit);
	reassemblyBuffer->packetUnderConstruction->PayLoad_Size = reassemblyBuffer->sizeLimit;

	//
	// Copy over the IP packet header and set the fields in the 
	// reassembly buffer to initial values including setting the
	// "fragment is here" bit table to all 0's.
	//
	memcpy(reassemblyBuffer->packetUnderConstruction->Pay_Load, 
		msg->Pay_Load, ipHeaderSize);

	bufferIpHeader = 
		(IpHeaderType*)reassemblyBuffer->packetUnderConstruction->Pay_Load;

	bufferIpHeader->ip_len = 0;
	bufferIpHeader->ip_fragment_offset = 0;
	reassemblyBuffer->fragmentationSize = 0;
	reassemblyBuffer->endFragmentHasArrived = false;
	reassemblyBuffer->endFragmentOffset = 0;

	for(int i = 0; i < (MAX_IP_FRAGMENTS_SIMPLE_CASE/8); i++) 
	{
		reassemblyBuffer->fragmentIsHereBitTable[i] = 0;
	}

	// Add the fragment's data to the reassembly buffer.

	AddFragment_ReassemblyBuf(reassemblyBuffer, msg, &NotUsed, 0);
}

//����:��һ��������֡,����ǰ����RBufList�������֡һ����֡
void Sns_Model_NetworkIP::AddFragment_ReassemblyBuf(IpReassemblyBufferType *reassemblyBuffer, Sns_Message *msg, bool *packetIsComplete, Sns_Message **completedPacket)
{
	// 
	// Determine the length and where the fragment's data should go.
	// Expand the reassembly buffer if the packet is too large.
	//

	Sns_Message* bufferPacket = NULL;
	IpHeaderType* ipHeader = (IpHeaderType*)msg->Pay_Load;
	int ipHeaderSize = ipHeader->ip_hl*4;

	int fragmentOffset = ipHeader->ip_fragment_offset * 8;
	int fragmentDataLength = ipHeader->ip_len - ipHeaderSize;
	char* fragmentData = msg->Pay_Load + ipHeader->ip_hl*4;
	int packetLengthSoFar = ipHeaderSize + fragmentOffset + fragmentDataLength;

	*packetIsComplete = false;
	clocktype reass_buff_timer = SNS_Second_ConvertToClock(NETWORK_IP_REASS_BUFF_TIMER);
	reassemblyBuffer->expirationDate = SimClock() + reass_buff_timer;

	if (packetLengthSoFar > reassemblyBuffer->sizeLimit) 
	{
		ExpandReassemblyBuffer(reassemblyBuffer, packetLengthSoFar);
	}//if//

	//
	// Copy in the fragment's data into the reassembly buffer.  Then
	// set the bit in the table to says that the fragment has arrived.
	// Currently one bit for each equally sized fragment (except last).
	// Its not totally general, but probably is good enough.
	//                                                      

	bufferPacket = reassemblyBuffer->packetUnderConstruction;

	memcpy(&(bufferPacket->Pay_Load[ipHeaderSize + fragmentOffset]),
		fragmentData, fragmentDataLength);

	bufferPacket->PayLoad_Size = packetLengthSoFar;

	if (ipHeader->ip_more_fragments == 0) 
	{
		reassemblyBuffer->endFragmentHasArrived = true;
		reassemblyBuffer->endFragmentOffset = fragmentOffset;
	} 
	else 
	{
		int fragmentIndex;
		if (reassemblyBuffer->fragmentationSize == 0) 
		{
			reassemblyBuffer->fragmentationSize = fragmentDataLength;
		}//if//

		// Only simple same sized fragments implemented.

		assert(fragmentDataLength == reassemblyBuffer->fragmentationSize);

		fragmentIndex = fragmentOffset / reassemblyBuffer->fragmentationSize;

		assert(fragmentIndex < MAX_IP_FRAGMENTS_SIMPLE_CASE);

		SetBit(reassemblyBuffer->fragmentIsHereBitTable, fragmentIndex);
	}//if//   

	//
	// Check to see if all fragments have arrived and the packet is complete.
	//

	if ((reassemblyBuffer->endFragmentHasArrived) && 
		(reassemblyBuffer->fragmentationSize != 0)) 
	{
		Check_BufIsCompletion(reassemblyBuffer, packetIsComplete);
		if (*packetIsComplete) 
		{
			*completedPacket = reassemblyBuffer->packetUnderConstruction;
			reassemblyBuffer->packetUnderConstruction = NULL;
		}//if// 
	}//if//
}

//����:���֡�ڴ治��,����8��
void Sns_Model_NetworkIP::ExpandReassemblyBuffer(IpReassemblyBufferType *reassemblyBuffer, int minSize)
{
	int newSize;
	Sns_Message* biggerBufferPacket = new Sns_Message();
	biggerBufferPacket->Model_id = Model_id;
	biggerBufferPacket->Event_Name = reassemblyBuffer->packetUnderConstruction->Event_Name;
	biggerBufferPacket->Event_Type = reassemblyBuffer->packetUnderConstruction->Event_Type;

	biggerBufferPacket->Track_PacketId = reassemblyBuffer->packetUnderConstruction->Track_PacketId; //���ڰ�����
	biggerBufferPacket->Message_CreationTime = reassemblyBuffer->packetUnderConstruction->Message_CreationTime;//���ڰ�����

	newSize= (reassemblyBuffer->sizeLimit * REASSEMBLY_BUFFER_EXPANSION_MULTIPLIER);

	if (newSize < minSize) 
	{
		assert(minSize <= IP_MAXPACKET);
		newSize = minSize;
	}//if//

	if (newSize > IP_MAXPACKET) 
	{
		newSize = IP_MAXPACKET;
	}//if//

	biggerBufferPacket->Pay_Load = (char *)malloc(newSize);
	biggerBufferPacket->PayLoad_Size = newSize;

	memcpy(biggerBufferPacket->Pay_Load, 
		reassemblyBuffer->packetUnderConstruction->Pay_Load,
		reassemblyBuffer->sizeLimit);

	reassemblyBuffer->sizeLimit = newSize;

	xdelete(reassemblyBuffer->packetUnderConstruction);
	reassemblyBuffer->packetUnderConstruction = NULL;
	reassemblyBuffer->packetUnderConstruction = biggerBufferPacket;
}

//����:�ж��Ƿ������������ݰ���
void Sns_Model_NetworkIP::Check_BufIsCompletion(IpReassemblyBufferType *reassemblyBuffer, bool *packetIsComplete)
{
	int i;
	int lastIndex = reassemblyBuffer->endFragmentOffset / reassemblyBuffer->fragmentationSize;

	// Set the extra bits in the end char in the bit vector, if they
	// have not already been set.

	if (!BitIsSet(reassemblyBuffer->fragmentIsHereBitTable, lastIndex)) 
	{
		for(i = lastIndex; (i < ((lastIndex/8) + 1) * 8); i++) 
		{
			SetBit(reassemblyBuffer->fragmentIsHereBitTable, i);
		}//for//
	}//if//

	// Super fast byte comparison.  All the bits of the bit vector must
	// be 1.

	for(i = 0; (i < ((lastIndex/8) + 1)); i++) 
	{
		if (reassemblyBuffer->fragmentIsHereBitTable[i] != 0xFF) 
		{
			*packetIsComplete = false;
			return;
		}//if//
	}//for//
	*packetIsComplete = true;
}

//����:��ȥ�������ѳ�ʱ��IP��
void Sns_Model_NetworkIP::Remove_ExpiredIpRBuf(IpReassemblyBufferListType *reassemblyBufferList, clocktype currentTime)
{
	IpReassemblyBufferListCellType* previousCellPtr = NULL;    
	IpReassemblyBufferListCellType* currentCellPtr = reassemblyBufferList->firstPtr; 

	while (currentCellPtr != NULL) 
	{
		if (ReassemblyBuf_IsExpired(&(currentCellPtr->reassemblyBuffer), currentTime)) 
		{
			IpReassemblyBufferListCellType* nextCellPtr = currentCellPtr->nextPtr;

			//
			// Unlink the cell.
			//

			if (previousCellPtr == NULL) 
			{
				reassemblyBufferList->firstPtr = currentCellPtr->nextPtr;
			} 
			else 
			{
				previousCellPtr->nextPtr = currentCellPtr->nextPtr;
			}//if//
			//
			// Put the cell on Free List.
			//
			currentCellPtr->nextPtr =  reassemblyBufferList->freeListPtr;
			reassemblyBufferList->freeListPtr = currentCellPtr;

			xdelete(currentCellPtr->reassemblyBuffer.packetUnderConstruction);
			currentCellPtr->reassemblyBuffer.packetUnderConstruction = NULL;

			currentCellPtr = nextCellPtr;         
		} 
		else 
		{
			previousCellPtr = currentCellPtr;
			currentCellPtr = currentCellPtr->nextPtr;
		}//if//
	}//while//
}

//���ܣ��ж��Ƿ�ʱ
bool Sns_Model_NetworkIP::ReassemblyBuf_IsExpired(IpReassemblyBufferType *reassemblyBuf, clocktype curTime)
{
	return (reassemblyBuf->expirationDate < curTime); 
}

//����:��֡������,ɾ������
void Sns_Model_NetworkIP::IpReassemblyBufList_Del(IpReassemblyBufferListType *reassemblyBufferList, IpReassemblyBufferType **reassemblyBufferPtr)
{
	//
	// Find the reassembly buffer in the list.
	//
	IpReassemblyBufferListCellType* previousCellPtr = NULL;    
	IpReassemblyBufferListCellType* currentCellPtr = reassemblyBufferList->firstPtr; 

	while ((currentCellPtr != NULL) && 
		(currentCellPtr->reassemblyBuffer.packetUnderConstruction !=
		(*reassemblyBufferPtr)->packetUnderConstruction))
	{
		previousCellPtr = currentCellPtr;
		currentCellPtr = currentCellPtr->nextPtr;
	}//while//

	assert(currentCellPtr != NULL);
	//
	// Unlink the cell.
	//
	if (previousCellPtr == NULL) 
	{
		reassemblyBufferList->firstPtr = currentCellPtr->nextPtr;
	} 
	else 
	{
		previousCellPtr->nextPtr = currentCellPtr->nextPtr;
	}//if//
	//
	// Put the cell on Free List.
	//
	currentCellPtr->nextPtr =  reassemblyBufferList->freeListPtr;
	reassemblyBufferList->freeListPtr = currentCellPtr;
	(*reassemblyBufferPtr) = NULL;
}

////////////////////////////////////������·������֡,��֡���� end////////////////////////////////////

//����:�����ݰ������ϲ�Э��,����ȥ��ͷ,���͵�������,������
void Sns_Model_NetworkIP::ProcessPacketForMeFromMac(Sns_Message *msg)
{
	unsigned sourceAddress;
	unsigned destinationAddress;
	unsigned char IpProtocol;
	unsigned int ttl;
	unsigned priority;

	Remove_IpHeader(msg, &sourceAddress, &destinationAddress, &priority, &IpProtocol, &ttl);

	Stats_Var.numPacketsDeliveredToThisNode++;
	Stats_Var.deliveredPacketTtlTotal += ttl;

	switch(IpProtocol)
	{
	case PROTOCOL_PACKET:
		{
			IpPacketToTransport(msg, priority, sourceAddress, destinationAddress);
		}
		break;

	case PROTOCOL_OSPFv2:
		{
			ProcessPacketForOspfv2(msg,sourceAddress,destinationAddress);
		}
		break;

	case PROTOCOL_LOCAL_ROUTE:
		{
			ProcessPacketForLocalRoute(msg,sourceAddress,destinationAddress);
		}
		break;

	default:
		break;
	}
}

//����:ȥ��ͷ
void Sns_Model_NetworkIP::Remove_IpHeader(Sns_Message *msg, unsigned *sourceAdd, unsigned *destAdd, unsigned *priority, unsigned char *protocol, unsigned int *ttl)
{
	IpHeaderType *ipHeader = (IpHeaderType *)msg->Pay_Load;
	*priority = ipHeader->ip_tos;
	*ttl = ipHeader->ip_ttl;
	*protocol = ipHeader->ip_p;
	*sourceAdd = ipHeader->ip_src;
	*destAdd = ipHeader->ip_dst;
	char * msghesd;
	msghesd = msg->SNS_Msg_Packet_RemoveHeader(ipHeader->ip_hl*4);
	xfree(msghesd);
	msghesd = NULL;
}

//����:�����ݰ����͵������
void Sns_Model_NetworkIP::IpPacketToTransport(Sns_Message *msg, unsigned priority, unsigned sourceAdd, unsigned destAdd)
{
	//��һЩ��Ϣͨ��info����Ӧ�ò�,��Щ��Ϣ����IP,��info����
	NetworkToTransportInfo *info = (NetworkToTransportInfo *)malloc(sizeof(NetworkToTransportInfo));

	info->destinationAddr = destAdd;
	info->priority = priority;
	info->sourceAddr = sourceAdd;

	msg->SNS_Msg_AddInfo((char *)info, sizeof(NetworkToTransportInfo));
	xfree(info);
	info = NULL;

	//�޸Ĳ�����Ϣ����,Ϊ��ģ������¼�,�¼���ΪMSG_OutEVENT_NETWORK_ToMAC,msg�غɲ���
	msg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_OutEVENT_NETWORK_ToTransport,SNS_MSG_OUTPUT,NULL,-1);

	Scenarios_Data->SNS_Msg_Send(msg,Cur_Node_id,0);//��Ϣ����,����ʱ��Ϊ0
}

//����:�����ݰ�·�ɲ����͸���·�㷢��
void Sns_Model_NetworkIP::ProcessPacketForAnotherFromMac(Sns_Message *msg)
{
	IpHeaderType *ipHeader = (IpHeaderType *) msg->Pay_Load;  

	Stats_Var.numPacketsRoutedForOtherNodes++;

	if (ipHeader->ip_ttl == 0) 
	{
		// Has transversed max. number of hops so drop it.

		Stats_Var.numTtlExpirationDrops++;
		xdelete(msg);
		msg = NULL;
	} 
	else 
	{
		RoutePacketAndSendToMac(msg);
	}//if//
}

////////////////////////////////////·�ɱ���////////////////////////////////////

//����:·�ɱ��ʼ��
void Sns_Model_NetworkIP::NetworkInitForwardingTable()
{
	forwardTable.size = 0;
	forwardTable.allocatedSize = 0;
	forwardTable.row = NULL;
}

//����:·�ɱ����
void Sns_Model_NetworkIP::NetworkUpdateForwardingTable(unsigned destAddress, short interfaceIndex, unsigned nextHopAddress)
{
	int i;

	for(i=0; ((i < forwardTable.size) && 
		(forwardTable.row[i].destAddress != destAddress)); i++)
	{
		// Nothing
	}//for//


	//���Ŀǰ��·��ת������û�е�ǰ�ڵ�ԣ� ����Ҫ�����
	if (i == forwardTable.size) 
	{
		forwardTable.size++;
		//        assert (routingTable->size <= node->numNodes);
		if (forwardTable.size > forwardTable.allocatedSize) 
		{
			if (forwardTable.allocatedSize == 0) 
			{
				forwardTable.allocatedSize = FORWARDING_TABLE_ROW_START_SIZE;
				forwardTable.row = (NetworkForwardingTableRow*)
					malloc(forwardTable.allocatedSize * sizeof(NetworkForwardingTableRow));
			} 
			else 
			{
				int newSize = (forwardTable.allocatedSize * 2);
				NetworkForwardingTableRow* newTableRow = (NetworkForwardingTableRow*)malloc(
					newSize * sizeof(NetworkForwardingTableRow));

				memcpy(newTableRow, forwardTable.row, (forwardTable.allocatedSize * 
					sizeof(NetworkForwardingTableRow)));

				xfree(forwardTable.row);
				forwardTable.row = newTableRow;
				forwardTable.allocatedSize = newSize;
			}
		}
	}

	forwardTable.row[i].destAddress = destAddress;
	forwardTable.row[i].interfaceIndex = interfaceIndex;
	forwardTable.row[i].nextHopAddress = nextHopAddress;
}

//����:·�ɱ��ӡ
void Sns_Model_NetworkIP::Print_ForwardingTable()
{

	printf ("Forwarding Table for node %u\n", Cur_Node_id);
	printf("Table size = %d \n", forwardTable.size);

	for (int i = 0; i< forwardTable.size; i++) 
	{
		printf ("destAddress %u interfaceIndex %u nextHop %u\n",
			forwardTable.row[i].destAddress, forwardTable.row[i].interfaceIndex,
			forwardTable.row[i].nextHopAddress);
	}
	printf ("\n");
}

//����:·�ɱ��ӡ���ļ�
void Sns_Model_NetworkIP::fPrint_ForwardingTable(FILE *out_file)
{
	fprintf (out_file, "Forwarding Table for node %u\n", Cur_Node_id);
	fprintf(out_file, "Table size = %d \n", forwardTable.size);

	for (int i = 0; i< forwardTable.size; i++) 
	{
		fprintf (out_file, "destAddress %u interfaceIndex %u nextHop %u\n",
			forwardTable.row[i].destAddress, forwardTable.row[i].interfaceIndex,
			forwardTable.row[i].nextHopAddress);
	}
	fprintf (out_file, "\n");
}

////////////////////////////////////·�ɱ��� end////////////////////////////////////

void Sns_Model_NetworkIP::ProcessPacketForNextHop(Sns_Message* msg,int interfaceIndex)
{
	IpHeaderType *ipHeader = (IpHeaderType *) msg->Pay_Load;  

	Stats_Var.numPacketsRoutedForOtherNodes++;

	if (ipHeader->ip_ttl == 0) 
	{
		// Has transversed max. number of hops so drop it.

		Stats_Var.numTtlExpirationDrops++;
		xdelete(msg);
		msg = NULL;
	} 
	else if(interfaceIndex==BROADCAST_INTERFACE_INDEX)
	{
		NetworkToMACInfo* info=new NetworkToMACInfo;
		info->interfaceIndex=interfaceIndex;
		info->srcAddr=ipHeader->ip_src;
		info->nexthopaddr=ipHeader->ip_dst;
		msg->SNS_Msg_AddInfo((char*)info,sizeof(NetworkToMACInfo));
		msg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_OutEVENT_NETWORK_ISMYIMI,SNS_MSG_OUTPUT,NULL,-1);
		Scenarios_Data->SNS_Msg_Send(msg,Cur_Node_id,0);
		xdelete(info);
	}
	else
	{
		Packet_SendToMacLayer(msg, interfaceIndex, ipHeader->ip_dst,ipHeader->ip_src);
	}//if//
}

void Sns_Model_NetworkIP::ProcessPacketForOspfv2(Sns_Message* msg,unsigned srcAddr,unsigned dstAddr)
{
	msg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_OutEVENT_NETWORK_ToProtocol_OSPFv2,SNS_MSG_OUTPUT,NULL,-1);
	NetworkToMACInfo* info=(NetworkToMACInfo*)msg->Info_Msg;
	info->srcAddr=srcAddr;
	Scenarios_Data->SNS_Msg_Send(msg,Cur_Node_id,0);
}

void Sns_Model_NetworkIP::ProcessPacketForLocalRoute(Sns_Message* msg,unsigned srcAddr,unsigned dstAddr)
{
	LocalRouteHeader* header=(LocalRouteHeader*)msg->Pay_Load;
	header=(LocalRouteHeader*)msg->SNS_Msg_Packet_RemoveHeader(header->size);
	IpFragmentToMacLayer(msg, BROADCAST_INTERFACE_INDEX, header->dstNodeAddr,interfaceInfo[BROADCAST_INTERFACE_INDEX].address);
	xdelete(header);
}

void Sns_Model_NetworkIP::initVals(int numberInterfaces,InterfaceInfoType* interfaceInfo)
{
	this->numberInterfaces=numberInterfaces;
	this->interfaceInfo=interfaceInfo;
}

bool Sns_Model_NetworkIP::isMyInterface(unsigned address)
{
	for(int i=0;i<numberInterfaces;i++)
	{
		if(address==interfaceInfo[i].address)
			return true;
	}
	return false;
}

int Sns_Model_NetworkIP::myInterfaceNextHop(unsigned address)
{
	for(int i=0;i<numberInterfaces;i++)
	{
		unsigned maskedDstAddr=address&interfaceInfo[i].subnetMask;
		unsigned maskedIntfAddr=interfaceInfo[i].address&interfaceInfo[i].subnetMask;
		if(maskedDstAddr==maskedIntfAddr)
			return i;
	}
	return -1;
}