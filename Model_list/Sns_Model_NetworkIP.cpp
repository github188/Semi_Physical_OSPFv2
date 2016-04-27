/*
* Copyright (c) 2014,北京航空航天大学
* All rights reserved.
*
* 系统名称: SPACE NETWORK SIMULATION SYSTEM
* 作    者: 张涛
* 当前版本: SNS 1.0
* 
* 文件名称: Sns_Model_NetworkIP.cpp
* 当前版本: V 1.0.0
* 文件标识: Sns_Model_NetworkIP类源文件
* 功能描述: 
* 完 成 人: 张涛
* 联系方式: 
* 完成日期: 
*
* 摘    要:
*/
//////////////////////////////////////////////////////////////////////

////////////////本部分为模型导向自动生成////////////////

#include "StdAfx.h"              //基本c++库
#include "Sns_Config_Input.h"   //平台库
#include "Sns_Message.h"        //平台库

#include "Sns_Scenarios.h"
#include "Sns_Model_NetworkIP.h"
#include "Sns_Model_OSPFv2.h"

/////////本部分为模型导向自动生成 end 用户需要加的定义在下面/////////////


Sns_Model_NetworkIP::Sns_Model_NetworkIP()  
{  
	///////////输出参数初始化,模板自动生成////////////////////////

	Stats_Var.numPacketsSentToMac = 0;
	Stats_Var.numPacketsRoutedForOtherNodes = 0;
	Stats_Var.numPacketsDeliveredToThisNode = 0;
	Stats_Var.deliveredPacketTtlTotal = 0;
	Stats_Var.numNetworkUnreachableDrops = 0;
	Stats_Var.numTtlExpirationDrops = 0;
	//Stats_Variable_Init//		

	///////////输出参数初始化,模板自动生成 end 用户需要加的定义在下面//////////

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

//////////////////////////////////协议初始化函数/////////////////////////////////////
void Sns_Model_NetworkIP::Model_init()  
{  
	//////////从配置文件中读取初始化参数,模型导向自动生成//////////////////////////

	char ModelName[SNS_MAX_STRING_LENGTH];	//配置文件中模型识别标志
	char buf[SNS_MAX_STRING_LENGTH];		//读取配置文件中的字符串

	int RetArrNum;			//读取参数个数返回值
	bool retVal = false;	//函数返回值

	Config_Input = new Sns_Config_Input();	//声明一个配置文件处理对象

	sprintf(ModelName,"%s[%d]-Sns_Model_NetworkIP[%d]",Cur_Node_Name,Cur_Node_id_inOneType,Model_Instance_id);//表示当前节点,当前模型,模型可以是同名多个,如为0,则表示唯一
	Config_Input->SNS_Read_ModelConf(ConfFile_Path, ModelName);//读取本模型的配置参数

	//Config_Variable_Init//
	//////////从配置文件中读取初始化参数,模型导向自动生成 end 用户需要加的定义在下面////////////////////


}  

//功能:节点初始化后的处理函数,用于有时需要所有节点所有模型都初始化完成才可执行的动作
void Sns_Model_NetworkIP::Model_init_end()
{

}

////////////////////////////////////消息处理函数////////////////////////////////////
//功能:消息处理函数,接收模型输入事件,触动相应函数,并处理
void Sns_Model_NetworkIP::SNS_Model_MsgDeal(Sns_Message *msg)  
{  
	switch(msg->Event_Name) //消息事件枚举
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

////////////////////////////仿真结束处理函数//////////////////////////////////////////////
//功能:处理协议或环境模型在仿真结束后的一些事,如模型仿真结果输出等
void Sns_Model_NetworkIP::SNS_Simulate_End_Model()
{
	SNS_Record_Stats_Value();
}

//功能:记录本模型的输出状态变量值到StatsVar_Output内
void Sns_Model_NetworkIP::SNS_Record_Stats_Value()
{
	bool retVal = false;	//函数返回值
	char Stats_ModelName[SNS_MAX_STRING_LENGTH]; //用于记录输出状态变量所属模型名标志

	sprintf(Stats_ModelName,"\n** %s[%d]-Sns_Model_NetworkIP[%d]_begin\n",Cur_Node_Name,Cur_Node_id_inOneType,Model_Instance_id);//本模型输出状态变量值记录开始
	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);//将Stats_ModelName写入链表

	/////////////////////////////将本模型所有输出状态变量值写入链表//////////////////////////

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
	/////////////////////////////将本模型所有输出状态变量值写入链表//////////////////////////

	sprintf(Stats_ModelName,"\n** %s[%d]-Sns_Model_NetworkIP[%d]_end\n",Cur_Node_Name,Cur_Node_id_inOneType,Model_Instance_id);//本模型输出状态变量值记录结束
	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);//将Stats_ModelName写入链表
}

////////////////////////////////////发送一个新消息////////////////////////////////////

//功能:发送一个新消息
//输入:DestiNode--消息目的节点地址,ProtocolId--发起消息的模型ID,EventName--消息事件名称,
//     EventType--事件类型,PayLoad--消息载荷,PacketSize--消息载荷大小,TimeDelay--发送延迟
void Sns_Model_NetworkIP::Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay)
{
	Sns_Message *msg = new Sns_Message();//声明一个消息对象

	msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,PayLoad,PacketSize);//为消息赋值

	Scenarios_Data->SNS_Msg_Send(msg,DestiNode,TimeDelay);//发送消息
}

////////////////////////////////////////用户输入事件处理函数//////////////////////

//功能:Msg_InEvent_NETWORK_FromTransport事件函数,接收来自传输层的消息并处理 
void Sns_Model_NetworkIP:: Msg_InEvent_NETWORK_FromTransport(Sns_Message *msg) 
{
	TransportToNetworkInfo* info;

	info = (TransportToNetworkInfo*)msg->Info_Msg;
	Add_IpHeader(msg, interfaceInfo[0].address,info->destinationAddr, info->priority, info->Protocol_ToIP, 0);//加上IP包头

	RoutePacketAndSendToMac(msg);
}

//功能:MSG_InEVENT_NETWORK_FromMAC事件函数,接收来链路层的数据包,并处理 
void Sns_Model_NetworkIP:: Msg_InEvent_NETWORK_FromMAC(Sns_Message *msg) 
{
	IpHeaderType *ipHeader = (IpHeaderType *) msg->Pay_Load;  
	int interfaceIndex=myInterfaceNextHop(ipHeader->ip_dst);
	ipHeader->ip_ttl = ipHeader->ip_ttl - 1;

	if ((ipHeader->ip_dst == ANY_DEST) ||(ipHeader->ip_dst == OSPFv2_ALL_SPF_ROUTERS)|| isMyInterface(ipHeader->ip_dst)) //如果是本节点的数据包
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

//功能:MSG_InEVENT_NETWORK_UpdateRoutable事件函数,接收路由更新消息,更新IP协议路由表 
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
	Add_IpHeader(msg, info->srcAddr,info->dstAddr, 0,PROTOCOL_OSPFv2, 0);//加上IP包头
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

////////////////////////////////////////用户输入事件处理函数 end//////////////////////

//功能:为一个数据包加上IP包头,该函数将修改一个已有MSG的负载,以及负载大小和包头大小3个参数
//输入:msg:需要加ip头的消息,要求有负载;destAdd:目的地址;priority:优先级
//     protocol:上层应用协议;ttl:生命期
void Sns_Model_NetworkIP::Add_IpHeader(Sns_Message *msg, unsigned srcAddr,unsigned destAdd, unsigned priority, unsigned char protocol, unsigned ttl)
{
	IpHeaderType* ipHeader;
	int Size;

	Size = sizeof(IpHeaderType);
	ipHeader = (IpHeaderType*)malloc(Size);
	memset(ipHeader, 0, Size);

	//ip 包头赋值
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

	//添加包头
	msg->SNS_Msg_Packet_AddHeader((char*)ipHeader,Size);
	xfree(ipHeader);
	ipHeader = NULL;
}

////////////////////////////////////数据包成帧处理,并路由转发发送给链路层的相关处理////////////////////////////////////

//功能:将包发到链路层处理主程序
void Sns_Model_NetworkIP::RoutePacketAndSendToMac(Sns_Message *msg)
{
	IpHeaderType *ipHeader = (IpHeaderType *) msg->Pay_Load;
	//
	// Check if its a broadcast.
	//
	if (ipHeader->ip_dst == ANY_DEST) //链路广播
	{
		Packet_SendToMacLayer(msg, -1, ANY_DEST,ipHeader->ip_src);
	} 
	else if(ipHeader->ip_dst==OSPFv2_ALL_SPF_ROUTERS)
	{
		Sns_Model_OSPFv2::NetworkToMACInfo* info=(Sns_Model_OSPFv2::NetworkToMACInfo*)msg->Info_Msg;
		Packet_SendToMacLayer(msg, info->interfaceIndex, ANY_DEST,ipHeader->ip_src);
	}
	else//非广播 
	{
		LookupTableRoute_Packet(msg);
	}
}

//功能:将消息发到对应端口的链路层协议,若消息内包大小超过链路层帧大小,则需要拆包
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
			fragment->Track_PacketId = msg->Track_PacketId; //用于包跟踪
			fragment->Message_CreationTime = msg->Message_CreationTime; //用于包跟踪

			IpFragmentToMacLayer(fragment, interfaceIndex ,nextHop,srcAddr);

			packetIndex = lastIndex + 1;
		}//while//
		xdelete(msg);
		msg = NULL;
	}//if//
}

//功能:将已处理过的消息(经过拆包后)发到对应端口的链路层协议
void Sns_Model_NetworkIP::IpFragmentToMacLayer(Sns_Message *msg, short interfaceIndex, unsigned nextHop,unsigned srcAddr)
{
	//将一些信息通过info传与应用层,有些信息来自IP,由info传入
	NetworkToMACInfo *info = (NetworkToMACInfo *)malloc(sizeof(NetworkToMACInfo));

	info->interfaceIndex = interfaceIndex;
	info->nexthopaddr = nextHop;
	info->srcAddr=srcAddr;

	msg->SNS_Msg_AddInfo((char *)info, sizeof(NetworkToMACInfo));
	xfree(info); 
	info = NULL;

	Stats_Var.numPacketsSentToMac++;

	//修改部分消息参数,为本模型输出事件,事件名为MSG_OutEVENT_NETWORK_ToMAC,msg载荷不变
	msg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_OutEVENT_NETWORK_ToMAC,SNS_MSG_OUTPUT,NULL,-1);
	Sns_Message* newMsg=msg->SNS_Msg_Copy();
	Scenarios_Data->SNS_Msg_Send(newMsg,Cur_Node_id,0);//消息发送,假设时延为0
	xdelete(msg);
}

//功能:查表路由主程序
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

//功能:查路由表,根据目的地址,获取下一跳地址和转发端口

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

////////////////////////////////////数据包成帧处理,并路由转发发送给链路层的相关处理 end////////////////////////////////////

////////////////////////////////////接收链路层数据帧,组帧处理////////////////////////////////////

//功能:组帧主程序
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

//功能:判断是否是某包第一个来的数据帧,是否存在前面的帧,并被存储在RBufList
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

//功能:判断两个帧是否属于同一包
bool Sns_Model_NetworkIP::IsIpFragmentOf(Sns_Message *msg1, Sns_Message *msg2)
{
	IpHeaderType* ipHeader1 = (IpHeaderType*)msg1->Pay_Load;
	IpHeaderType* ipHeader2 = (IpHeaderType*)msg2->Pay_Load;

	return ((ipHeader1->ip_id == ipHeader2->ip_id) &&
		(ipHeader1->ip_src == ipHeader2->ip_src) &&
		(ipHeader1->ip_p == ipHeader2->ip_p));
}

//功能:RBufList中增加一新链表,并分配内存
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

//功能:向RBufList的链表中加入一新的帧,并初始化
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

	reassemblyBuffer->packetUnderConstruction->Track_PacketId = msg->Track_PacketId; //用于包跟踪
	reassemblyBuffer->packetUnderConstruction->Message_CreationTime = msg->Message_CreationTime; //用于包跟踪

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

//功能:对一个新来的帧,与以前存入RBufList的链表的帧一起组帧
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

//功能:如果帧内存不够,再扩8倍
void Sns_Model_NetworkIP::ExpandReassemblyBuffer(IpReassemblyBufferType *reassemblyBuffer, int minSize)
{
	int newSize;
	Sns_Message* biggerBufferPacket = new Sns_Message();
	biggerBufferPacket->Model_id = Model_id;
	biggerBufferPacket->Event_Name = reassemblyBuffer->packetUnderConstruction->Event_Name;
	biggerBufferPacket->Event_Type = reassemblyBuffer->packetUnderConstruction->Event_Type;

	biggerBufferPacket->Track_PacketId = reassemblyBuffer->packetUnderConstruction->Track_PacketId; //用于包跟踪
	biggerBufferPacket->Message_CreationTime = reassemblyBuffer->packetUnderConstruction->Message_CreationTime;//用于包跟踪

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

//功能:判断是否已是完整数据包了
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

//功能:移去链表中已超时的IP包
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

//功能：判断是否超时
bool Sns_Model_NetworkIP::ReassemblyBuf_IsExpired(IpReassemblyBufferType *reassemblyBuf, clocktype curTime)
{
	return (reassemblyBuf->expirationDate < curTime); 
}

//功能:组帧结束后,删除链表
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

////////////////////////////////////接收链路层数据帧,组帧处理 end////////////////////////////////////

//功能:将数据包发与上层协议,包括去包头,发送到传输层等,主函数
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

//功能:去包头
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

//功能:将数据包发送到传输层
void Sns_Model_NetworkIP::IpPacketToTransport(Sns_Message *msg, unsigned priority, unsigned sourceAdd, unsigned destAdd)
{
	//将一些信息通过info传与应用层,有些信息来自IP,由info传入
	NetworkToTransportInfo *info = (NetworkToTransportInfo *)malloc(sizeof(NetworkToTransportInfo));

	info->destinationAddr = destAdd;
	info->priority = priority;
	info->sourceAddr = sourceAdd;

	msg->SNS_Msg_AddInfo((char *)info, sizeof(NetworkToTransportInfo));
	xfree(info);
	info = NULL;

	//修改部分消息参数,为本模型输出事件,事件名为MSG_OutEVENT_NETWORK_ToMAC,msg载荷不变
	msg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_OutEVENT_NETWORK_ToTransport,SNS_MSG_OUTPUT,NULL,-1);

	Scenarios_Data->SNS_Msg_Send(msg,Cur_Node_id,0);//消息发送,假设时延为0
}

//功能:将数据包路由并发送给链路层发走
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

////////////////////////////////////路由表处理////////////////////////////////////

//功能:路由表初始化
void Sns_Model_NetworkIP::NetworkInitForwardingTable()
{
	forwardTable.size = 0;
	forwardTable.allocatedSize = 0;
	forwardTable.row = NULL;
}

//功能:路由表更新
void Sns_Model_NetworkIP::NetworkUpdateForwardingTable(unsigned destAddress, short interfaceIndex, unsigned nextHopAddress)
{
	int i;

	for(i=0; ((i < forwardTable.size) && 
		(forwardTable.row[i].destAddress != destAddress)); i++)
	{
		// Nothing
	}//for//


	//如果目前的路由转发表中没有当前节点对， 则需要新添加
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

//功能:路由表打印
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

//功能:路由表打印到文件
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

////////////////////////////////////路由表处理 end////////////////////////////////////

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