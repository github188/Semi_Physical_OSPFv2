/*
* Copyright (c) 2014,北京航空航天大学
* All rights reserved.
*
* 系统名称: SPACE NETWORK SIMULATION SYSTEM
* 作    者: 张涛
* 当前版本: SNS 1.0
* 
* 文件名称: Sns_Model_OSPFv2.cpp
* 当前版本: V 1.0.0
* 文件标识: Sns_Model_OSPFv2类源文件
* 功能描述: 
* 完 成 人: 
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
#include "Sns_Model_OSPFv2.h"
#include "Sns_Model_NetworkIP.h"

/////////本部分为模型导向自动生成 end 用户需要加的定义在下面/////////////

// Added for Route-Redistribution
#define ROUTE_REDISTRIBUTE


// Enabling this might reduce some duplicate LSA transmission in a network.
// When enable this, a node wait for time [0, OSPFv2_FLOOD_TIMER] before
// sending Update in response to a Request. Thus at synchronization time
// a node send less number of Update packet in response to several duplicate
// Request from different node in the network. This intern also reduce
// number of Ack packet transmitted in the network.
#define OSPFv2_SEND_DELAYED_UPDATE 1

// Enable this if you want ABR to examine transit areas summary LSAs also
// other than examining backbone area only. This might be helpfull for
// finding routes when link to backbone faults.

#define EXAMINE_TRANSIT_AREA 1

#define OSPFv2_DEBUG_TABLE 1
#define OSPFv2_DEBUG_TABLEErr 0

#define OSPFv2_DEBUG 0
#define OSPFv2_DEBUG_SPT 0
#define OSPFv2_DEBUG_LSDB 0
#define OSPFv2_DEBUG_ISM 0
#define OSPFv2_DEBUG_SYNC 0
#define OSPFv2_DEBUG_FLOOD 0
#define OSPFv2_DEBUG_HELLO 0

#define OSPFv2_DEBUG_ERRORS 0
#define OSPFv2_DEBUG_SPTErr 0
#define OSPFv2_DEBUG_LSDBErr 0
#define OSPFv2_DEBUG_SYNCErr 0
#define OSPFv2_DEBUG_FLOODErr 0
#define OSPFv2_DEBUG_HELLOErr 0

#define OSPFv2_DEBUG_NEIGHBOR_EVENT_AND_STATE 0
#define OSPFv2_DEBUG_LINK 0
#define OSPFv2_DEBUG_EVENTS 0
Sns_Model_OSPFv2::Sns_Model_OSPFv2()  
{  
	///////////输出参数初始化,模板自动生成////////////////////////

	//Stats_Variable_Init//		

	///////////输出参数初始化,模板自动生成 end 用户需要加的定义在下面//////////

}  
  
Sns_Model_OSPFv2::~Sns_Model_OSPFv2()  
{  
	xdelete(Config_Input);
	Config_Input = NULL;
	xfree(Cur_Node_Name);
	Cur_Node_Name = NULL;
	xfree(ConfFile_Path);
	ConfFile_Path = NULL;
}  

//////////////////////////////////协议初始化函数/////////////////////////////////////
void Sns_Model_OSPFv2::Model_init()  
{  
	//////////从配置文件中读取初始化参数,模型导向自动生成//////////////////////////

	//char ModelName[SNS_MAX_STRING_LENGTH];	//配置文件中模型识别标志
	char buf[SNS_MAX_STRING_LENGTH];		//读取配置文件中的字符串

	int RetArrNum;			//读取参数个数返回值
	bool retVal = false;	//函数返回值

	Config_Input = new Sns_Config_Input();	//声明一个配置文件处理对象
	
	sprintf(modelName,"%s-Sns_Model_OSPFv2[%d]",Cur_Node_Name,Model_Instance_id);//表示当前节点,当前模型,模型可以是同名多个,如为0,则表示唯一
	Config_Input->SNS_Read_ModelConf(ConfFile_Path, modelName);//读取本模型的配置参数
	
	//Config_Variable_Init//
	//////////从配置文件中读取初始化参数,模型导向自动生成 end 用户需要加的定义在下面////////////////////


}  

//功能:节点初始化后的处理函数,用于有时需要所有节点所有模型都初始化完成才可执行的动作
void Sns_Model_OSPFv2::Model_init_end()
{
	Ospfv2Init();
}

////////////////////////////////////消息处理函数////////////////////////////////////
//功能:消息处理函数,接收模型输入事件,触动相应函数,并处理
void Sns_Model_OSPFv2::SNS_Model_MsgDeal(Sns_Message *msg)  
{  

	int  Free_Value ;
	
	if(OSPFv2_DEBUG_EVENTS)
	{
		Ospfv2PrintMsgEventName(msg,false);
	}
	switch(msg->Event_Name) //消息事件枚举
	{
	case MSG_InEVENT_OspfIncrementLSAge:
	{
		Msg_InEvent_OspfIncrementLSAge(msg);

		Free_Value = 0 ;

		
	}

	break;
	case MSG_InEVENT_OspfInactivityTimer:
	{
		Msg_InEvent_OspfInactivityTimer(msg);

		Free_Value = 0 ;

		
	}

	break;


	case MSG_InEVENT_OspfRxmtTimer:
	{
		Msg_InEvent_OspfRxmtTimer(msg);

		Free_Value = 0 ;

		
	}

	break;


	case MSG_InEVENT_OspfScheduleHello:
	{
		Msg_InEvent_OspfScheduleHello(msg);

		Free_Value = 0 ;

		
	}

	break;


	case MSG_InEVENT_OspfScheduleLSDB:
	{
		Msg_InEvent_OspfScheduleLSDB(msg);

		Free_Value = 0 ;

	}

	break;


	case MSG_InEVENT_QospfScheduleLSDB:
	{
		Msg_InEvent_QospfScheduleLSDB(msg);

		Free_Value = 0 ;

	}

	break;


	case MSG_InEVENT_QospfInterfaceStatusMonitor:
	{
		Msg_InEvent_QospfInterfaceStatusMonitor(msg);

		Free_Value = 0 ;
		
	}
	break;



	case MSG_InEVENT_QospfSetNewConnection:
	{
		Msg_InEvent_QospfSetNewConnection(msg);

		Free_Value = 0 ;
		
	}

	break;


	case MSG_InEVENT_OspfWaitTimer:
	{
		Msg_InEvent_OspfWaitTimer(msg);

		Free_Value = 0 ;

		
	}

	break;

	case MSG_InEVENT_OspfFloodTimer:
	{
		Msg_InEvent_OspfFloodTimer(msg);

		Free_Value = 0 ;

		
	}

	break;

	case MSG_InEVENT_OspfDelayedAckTimer:
	{
		Msg_InEvent_OspfDelayedAckTimer(msg);

		Free_Value = 0 ;

		
	}

	break;


	case MSG_InEVENT_OspfScheduleSPF:
	{
		Msg_InEvent_OspfScheduleSPF(msg);

		Free_Value = 0 ;

		
	}

	break;


	case MSG_InEVENT_OspfNeighborEvent:
	{
		Msg_InEvent_OspfNeighborEvent(msg);

		Free_Value = 0 ;

		
	}

	break;


	case MSG_InEVENT_OspfInterfaceEvent:
	{
		Msg_InEvent_OspfInterfaceEvent(msg);

		Free_Value = 0 ;

	}

	break;

	case MSG_InEVENT_OspfHandleRoutingProtocolPacket:
	{
		Msg_InEvent_OspfHandleRoutingProtocolPacket(msg);

		Free_Value = 0 ;

	}

	break;


	//SNS_MSG_EVENT_IN//
	default:

		break;
	}
	if(OSPFv2_DEBUG_EVENTS)
	{
		Ospfv2PrintMsgEventName(msg,true);
	}
	xdelete( msg ) ;
}  

////////////////////////////仿真结束处理函数//////////////////////////////////////////////
//功能:处理协议或环境模型在仿真结束后的一些事,如模型仿真结果输出等
void Sns_Model_OSPFv2::SNS_Simulate_End_Model()
{
	SNS_Record_Stats_Value();
}

//功能:记录本模型的输出状态变量值到StatsVar_Output内
void Sns_Model_OSPFv2::SNS_Record_Stats_Value()
{
	bool retVal = false;	//函数返回值
	char Stats_ModelName[SNS_MAX_STRING_LENGTH]; //用于记录输出状态变量所属模型名标志

	sprintf(Stats_ModelName,"\n** %s[%d]-Sns_Model_OSPFv2[%d]_begin\n",Cur_Node_Name,Cur_Node_id_inOneType,Model_Instance_id);//本模型输出状态变量值记录开始
	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);//将Stats_ModelName写入链表

	/////////////////////////////将本模型所有输出状态变量值写入链表//////////////////////////

	//Stats_Variable_Record//
	/////////////////////////////将本模型所有输出状态变量值写入链表//////////////////////////

	sprintf(Stats_ModelName,"\n** %s[%d]-Sns_Model_OSPFv2[%d]_end\n",Cur_Node_Name,Cur_Node_id_inOneType,Model_Instance_id);//本模型输出状态变量值记录结束
	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);//将Stats_ModelName写入链表
}

////////////////////////////////////发送一个新消息////////////////////////////////////

//功能:发送一个新消息
//输入:DestiNode--消息目的节点地址,ProtocolId--发起消息的模型ID,EventName--消息事件名称,
//     EventType--事件类型,PayLoad--消息载荷,PacketSize--消息载荷大小,TimeDelay--发送延迟
void Sns_Model_OSPFv2::Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay)
{
	Sns_Message *msg = new Sns_Message();//声明一个消息对象

    msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,PayLoad,PacketSize);//为消息赋值

	Scenarios_Data->SNS_Msg_Send(msg,DestiNode,TimeDelay);//发送消息
}

////////////////////////////////////////用户输入事件处理函数//////////////////////

//功能：OspfIncrementLSAge事件函数 
void Sns_Model_OSPFv2:: Msg_InEvent_OspfIncrementLSAge(Sns_Message *msg) 
{
	// Increment age of each LSA.
	Ospfv2IncrementLSAge();

	// Reschedule LSA increment interval.
	Scenarios_Data->SNS_Msg_Send(msg->SNS_Msg_Copy(),Cur_Node_id,OSPFv2_LSA_INCREMENT_AGE_INTERVAL);


	///***!!!
	//xdelete( msg ) ;

}
//功能：OspfInactivityTimer事件函数 
void Sns_Model_OSPFv2:: Msg_InEvent_OspfInactivityTimer(Sns_Message *msg) 
{
	Ospfv2TimerInfo* info =	(Ospfv2TimerInfo*) msg->Info_Msg;
	Ospfv2Neighbor* neighborInfo = NULL;
	int interfaceIndex;
	
	// Get the neighbor's information from my neighbor list.
	neighborInfo = Ospfv2GetNeighborInfoByIPAddress(info->interfaceIndex,info->neighborAddr);
	interfaceIndex = info->interfaceIndex;

	// If neighbor doesn't exist (possibly removed from
	// neighbor list).
	if (neighborInfo == NULL || interfaceIndex == -1)
	{
		return;
	}

	ERROR_Assert(interfaceIndex == -1, "No Interface for Neighbor!!\n");

	// Timer expired.
	if (info->sequenceNumber !=neighborInfo->inactivityTimerSequenceNumber)
	{
		// Timer is an old one, so just ignore.
		return;
	}

	// If this timer has not expired already.
	Ospfv2HandleNeighborEvent(interfaceIndex,neighborInfo->neighborIPAddress,S_InactivityTimer);

	if (OSPFv2_DEBUG_HELLOErr)
	{
		Ospfv2PrintNeighborList();
	}


	///***!!!
	//xdelete( msg ) ;

}
//功能：OspfRxmtTimer事件函数 
void Sns_Model_OSPFv2:: Msg_InEvent_OspfRxmtTimer(Sns_Message *msg) 
{
	Ospfv2TimerInfo* info =	(Ospfv2TimerInfo*) msg->Info_Msg;
	Ospfv2Neighbor* neighborInfo = NULL;


	neighborInfo = Ospfv2GetNeighborInfoByIPAddress(info->interfaceIndex,info->neighborAddr);

	// If neighbor doesn't exist (possibly removed from
	// neighbor list).
	if (neighborInfo == NULL)
	{
		return;
	}

	// Retransmit packet to specified neighbor.
	Ospfv2HandleRetransmitTimer(info->interfaceIndex,info->sequenceNumber,info->neighborAddr,info->advertisingRouter,info->type);

	///***!!!
	//xdelete( msg ) ;

}
//功能：OspfScheduleHello事件函数 
void Sns_Model_OSPFv2:: Msg_InEvent_OspfScheduleHello(Sns_Message *msg) 
{

	clocktype delay;
	int i;
	char* info=new char;
	memcpy(info,msg->Info_Msg,sizeof(char));
	i=(int) *info;
	xdelete(info);

	// Broadcast Hello packets to neighbors. on each interface
	Ospfv2SendHelloPacket(i);

	delay = (clocktype) (ospf->iface[i].helloInterval+ (Get_rand() *  OSPFv2_BROADCAST_JITTER));

	// Reschedule Hello packet broadcast.
	Sns_Message* newMsg=msg->SNS_Msg_Copy();
	Scenarios_Data->SNS_Msg_Send(newMsg,Cur_Node_id, delay);


	///***!!!
	//xdelete( msg ) ;

}
//功能：OspfScheduleLSDB事件函数 
void Sns_Model_OSPFv2:: Msg_InEvent_OspfScheduleLSDB(Sns_Message *msg) 
{
	Ospfv2LinkStateType lsType;
	int interfaceIndex;
	unsigned int areaId;
	bool flush = FALSE;
	char* info = NULL;

	if (msg->Info_Size == 0)
	{
		return;
	}

	info = msg->Info_Msg;
	memcpy(&lsType, info, sizeof(Ospfv2LinkStateType));
	info += sizeof(Ospfv2LinkStateType);

	if (lsType == OSPFv2_ROUTER)
	{
		memcpy(&areaId, info, sizeof(unsigned int));
		info += sizeof(unsigned int);
		memcpy(&flush, info, sizeof(bool));
		Ospfv2OriginateRouterLSAForThisArea(areaId, flush);
	}
	else if (lsType == OSPFv2_NETWORK)
	{
		int seqNum;

		memcpy(&interfaceIndex, info, sizeof(int));
		info += sizeof(int);
		memcpy(&flush, info, sizeof(bool));
		info += sizeof(bool);
		memcpy(&seqNum, info, sizeof(int));

		// If this timer has not been cancelled yet
		if (ospf->iface[interfaceIndex].networkLSTimerSeqNumber== seqNum)
		{
			Ospfv2OriginateNetworkLSA(interfaceIndex, flush);
		}
	}
	else if (lsType == OSPFv2_NETWORK_SUMMARY|| lsType == OSPFv2_ROUTER_SUMMARY)
	{
		Ospfv2RoutingTableRow advRt;
		Ospfv2RoutingTableRow* rowPtr = NULL;
		Ospfv2Area* thisArea = NULL;
		int retVal = 0;

		memset(&advRt, 0, sizeof(Ospfv2RoutingTableRow));
		memcpy(&areaId, info, sizeof(unsigned int));
		info += sizeof(unsigned int);
		memcpy(&flush, info, sizeof(bool));
		info += sizeof(bool);
		memcpy(&advRt.destAddr, info, sizeof(unsigned));
		info += sizeof(unsigned);
		memcpy(&advRt.addrMask, info, sizeof(unsigned));
		info += sizeof(unsigned);
		memcpy(&advRt.destType, info, sizeof(Ospfv2DestType));

		thisArea = Ospfv2GetArea(areaId);

		retVal = Ospfv2CheckForSummaryLSAValidity(advRt.destAddr, advRt.addrMask,advRt.destType, thisArea->areaID, &rowPtr);

		if (retVal == 1)
		{
			if (advRt.destAddr == OSPFv2_DEFAULT_DESTINATION)
			{
				ERROR_Assert(!thisArea->transitCapability,
					"Default route should be advertised in "
					"stub area\n");
				advRt.metric = thisArea->stubDefaultCost;
				advRt.flag = OSPFv2_ROUTE_NO_CHANGE;
			}
			else
			{
				advRt.metric = rowPtr->metric;
				advRt.flag = rowPtr->flag;
			}
		}
		else if (retVal == -1)
		{
			Ospfv2AreaAddressRange* addrInfo;

			addrInfo = Ospfv2GetAddrRangeInfoForAllArea(advRt.destAddr);
			ERROR_Assert(addrInfo &&
				addrInfo->address == advRt.destAddr,
				"Scheduled for wrong summary information\n");

			advRt.metric = Ospfv2GetMaxMetricForThisRange(&ospf->routingTable, addrInfo);
			advRt.flag = OSPFv2_ROUTE_NO_CHANGE;
		}
		else
		{
			return;
		}

		Ospfv2OriginateSummaryLSA(&advRt,thisArea,flush);
	}
	// BGP-OSPF Patch Start
	else if (lsType == OSPFv2_ROUTER_AS_EXTERNAL)
	{
		unsigned destAddress;
		unsigned destAddressMask;
		unsigned nextHopAddress;
		int external2Cost;

		memcpy(&destAddress, info, sizeof(unsigned));
		info += sizeof(unsigned);
		memcpy(&destAddressMask, info, sizeof(unsigned));
		info += sizeof(unsigned);
		memcpy(&nextHopAddress, info, sizeof(unsigned));
		info += sizeof(unsigned);
		memcpy(&external2Cost, info, sizeof(int));
		info += sizeof(int);
		memcpy(&flush, info, sizeof(bool));

		Ospfv2OriginateASExternalLSA(destAddress,destAddressMask,nextHopAddress,external2Cost,flush);
	}
	// BGP-OSPF Patch End

	// M-OSPF Patch Start
	else if (lsType == OSPFv2_GROUP_MEMBERSHIP)
	{
		//unsigned groupId;

		//memcpy(&areaId, info, sizeof(unsigned int));
		//info += sizeof(unsigned int);
		//memcpy(&flush, info, sizeof(bool));
		//info += sizeof(bool);
		//memcpy(&interfaceIndex, info, sizeof(int));
		//info += sizeof(int);
		//memcpy(&groupId, info, sizeof(unsigned));

		//MospfCheckLocalGroupDatabaseToOriginateGroupMembershipLSA(areaId,interfaceIndex,groupId,flush);
	}
	// M-OSPF Patch End


	///***!!!
	//xdelete( msg ) ;

}
//功能：QospfScheduleLSDB事件函数 
void Sns_Model_OSPFv2:: Msg_InEvent_QospfScheduleLSDB(Sns_Message *msg) 
{

}
//功能：QospfInterfaceStatusMonitor事件函数 
void Sns_Model_OSPFv2:: Msg_InEvent_QospfInterfaceStatusMonitor(Sns_Message *msg) 
{

}
//功能：QospfSetNewConnection事件函数 
void Sns_Model_OSPFv2:: Msg_InEvent_QospfSetNewConnection(Sns_Message *msg) 
{

}
//功能：OspfWaitTimer事件函数 
void Sns_Model_OSPFv2:: Msg_InEvent_OspfWaitTimer(Sns_Message *msg) 
{
	int interfaceIndex;

	memcpy(&interfaceIndex, msg->Info_Msg, msg->Info_Size);

	Ospfv2HandleInterfaceEvent(interfaceIndex, E_WaitTimer);


	///***!!!

	//xdelete( msg ) ;


}
//功能：OspfFloodTimer事件函数 
void Sns_Model_OSPFv2:: Msg_InEvent_OspfFloodTimer(Sns_Message *msg) 
{
	int interfaceIndex;
	unsigned nbrAddr = ANY_DEST;
	memcpy(&interfaceIndex, msg->Info_Msg, msg->Info_Size);

	if (ospf->iface[interfaceIndex].floodTimerSet == FALSE)
	{
		return;
	}

	Ospfv2SendLSUpdate(nbrAddr, interfaceIndex);

	ospf->iface[interfaceIndex].floodTimerSet = FALSE;

	///***!!!

	//xdelete( msg ) ;

}
//功能：OspfDelayedAckTimer事件函数 
void Sns_Model_OSPFv2:: Msg_InEvent_OspfDelayedAckTimer(Sns_Message *msg) 
{
	int interfaceIndex;
	Ospfv2ListItem* listItem = NULL;
	int count;
	Ospfv2LinkStateHeader* payload = NULL;
	int maxCount;

	unsigned dstAddr;

	memcpy(&interfaceIndex, msg->Info_Msg, msg->Info_Size);

	if (ospf->iface[interfaceIndex].delayedAckTimer == FALSE)
	{
		return;
	}

	// Determine Destination Address
		if ((ospf->iface[interfaceIndex].state == S_DR)|| (ospf->iface[interfaceIndex].state == S_Backup))
		{
			dstAddr = OSPFv2_ALL_SPF_ROUTERS;
		}
		else if (ospf->iface[interfaceIndex].type ==OSPFv2_BROADCAST_INTERFACE)
		{
			dstAddr = OSPFv2_ALL_D_ROUTERS;
		}
		else
		{
			dstAddr = OSPFv2_ALL_SPF_ROUTERS;
		}

		maxCount =(MAX_NW_PKT_SIZE- sizeof(IpHeaderType)- sizeof(Ospfv2LinkStateAckPacket))/ sizeof(Ospfv2LinkStateHeader);
		payload = (Ospfv2LinkStateHeader*)malloc(maxCount*  sizeof(Ospfv2LinkStateHeader));
		count = 0;

		while (!Ospfv2ListIsEmpty(ospf->iface[interfaceIndex].delayedAckList))
		{
			listItem =ospf->iface[interfaceIndex].delayedAckList->first;

			if (count == maxCount)
			{
				Ospfv2SendAckPacket((char*) payload,count,dstAddr,interfaceIndex);

				// Reset variables
				count = 0;
				continue;
			}

			memcpy(&payload[count],listItem->data,sizeof(Ospfv2LinkStateHeader));

			count++;

			// Remove item from list
			Ospfv2RemoveFromList(ospf->iface[interfaceIndex].delayedAckList,listItem,FALSE);
		}

		Ospfv2SendAckPacket((char*)payload,count,dstAddr,interfaceIndex);

		ospf->iface[interfaceIndex].delayedAckTimer = FALSE;
		xfree(payload);

		///***!!!
		//xdelete( msg ) ;

}
//功能：OspfScheduleSPF事件函数 
void Sns_Model_OSPFv2:: Msg_InEvent_OspfScheduleSPF(Sns_Message *msg) 
{
	ospf->SPFTimer = SimClock();
	Ospfv2FindShortestPath();

	// M-OSPF Patch Start
	if (ospf->isMospfEnable == TRUE)
	{
		//MospfModifyShortestPathAndForwardingTable(node) ;
	}
	// M-OSPF Patch End

	///***!!!
	//xdelete( msg ) ;
}
//功能：OspfNeighborEvent事件函数 
void Sns_Model_OSPFv2:: Msg_InEvent_OspfNeighborEvent(Sns_Message *msg) 
{
	Ospfv2NSMTimerInfo* NSMTimerInfo = (Ospfv2NSMTimerInfo*)msg->Info_Msg;

	Ospfv2HandleNeighborEvent(NSMTimerInfo->interfaceIndex,NSMTimerInfo->nbrAddr,NSMTimerInfo->nbrEvent);

	///***!!!
	//xdelete( msg ) ;

}
//功能：OspfInterfaceEvent事件函数 
void Sns_Model_OSPFv2:: Msg_InEvent_OspfInterfaceEvent(Sns_Message *msg) 
{
	Ospfv2ISMTimerInfo* ISMTimerInfo = (Ospfv2ISMTimerInfo*)msg->Info_Msg;

	Ospfv2HandleInterfaceEvent(ISMTimerInfo->interfaceIndex,ISMTimerInfo->intfEvent);

	ospf->iface[ISMTimerInfo->interfaceIndex].ISMTimer = FALSE;

	///***!!!
	//xdelete( msg ) ;

}
//功能：OspfHandleRoutingProtocolPacket事件函数 
void Sns_Model_OSPFv2:: Msg_InEvent_OspfHandleRoutingProtocolPacket(Sns_Message *msg) 
{
	Sns_Model_NetworkIP::NetworkToMACInfo* info = (Sns_Model_NetworkIP::NetworkToMACInfo*) msg->Info_Msg;
	unsigned sourceAddr=info->srcAddr;
	int interfaceIndex=Ospfv2GetInterfaceIndexFromAddress(info->nexthopaddr);
	Ospfv2Interface* thisIntf = NULL;
	Ospfv2CommonHeader* ospfHeader = NULL;

	// Make sure that ospf is running on the incoming interface.
	// If ospf is not running on the incoming interface,
	// then drop this packet.


	// Locally originated packets should not be passed on to OSPF.
	if (Ospfv2IsMyAddress(sourceAddr))
	{
		//xdelete(msg);
		return;
	}

	thisIntf = &ospf->iface[interfaceIndex];

	// Get OSPF header
	ospfHeader = (Ospfv2CommonHeader*) msg->Pay_Load;

	// Area ID specified in the header matches the
	// area ID of receiving interface
	if (ospfHeader->areaID == thisIntf->areaId)
	{
		// Make sure the packet has been sent over a single hop
		if ( thisIntf->type != OSPFv2_POINT_TO_POINT_INTERFACE && //added for virtual link support
			(sourceAddr & thisIntf->subnetMask) !=(MaskIpAddress(ospf->iface[interfaceIndex].address,ospf->iface[interfaceIndex].subnetMask)))
		{
			// NOTE:
			// Although this checking should not be performed over
			// Point-to-Point networks as the interface address of each
			// end of the link may assigned independently. However,
			// current QUALNET assign a network number on link, so we can
			// ignore this restriction unless QUALNET being capable of
			//doing so.
		}
	}

	// Area ID in packet indicate backbone
	else if (ospfHeader->areaID == 0)
	{
		// Packet has been sent over virtual link
		//TBD: Receiving router must be an ABR. Source must be
		//     other end of virtual link.
	}
	else
	{
		// Should be discarded as it comes from other area
		//xfree(msg);
		return;
	}

	// trace recd pkt

	// What type of packet did we get?
	switch (ospfHeader->packetType)
	{
		// It's a Hello packet.
	case OSPFv2_HELLO:
		{
			Ospfv2HelloPacket* helloPkt = NULL;

			ospf->stats.numHelloRecv++;

			// Get the Hello packet.
			helloPkt = (Ospfv2HelloPacket*)msg->Pay_Load;

			// Process the received Hello packet.
			Ospfv2HandleHelloPacket(helloPkt,sourceAddr,interfaceIndex);

			break;
		}

		// It's a link state update packet.
	case OSPFv2_LINK_STATE_UPDATE:
		{
			Ospfv2LinkStateUpdatePacket* updatePkt = NULL;

			ospf->stats.numLSUpdateRecv++;

			// Get update packet
			updatePkt = (Ospfv2LinkStateUpdatePacket*)msg->Pay_Load;

			// Process the Update packet.
			Ospfv2HandleUpdatePacket(msg, sourceAddr, interfaceIndex);

			break;
		}

		// It's a link state acknowledgement packet.
	case OSPFv2_LINK_STATE_ACK:
		{
			Ospfv2LinkStateAckPacket* ackPkt = NULL;

			ospf->stats.numAckRecv++;

			// Get LS Ack packet
			ackPkt = (Ospfv2LinkStateAckPacket*)msg->Pay_Load;

			// Process the ACK packet.
			Ospfv2HandleAckPacket(ackPkt, sourceAddr, interfaceIndex);

			break;
		}
		// It's a database description packet.
	case OSPFv2_DATABASE_DESCRIPTION:
		{
			Ospfv2DatabaseDescriptionPacket* dbDscrpPkt = NULL;

			dbDscrpPkt = (Ospfv2DatabaseDescriptionPacket*)msg->Pay_Load;

			ospf->stats.numDDPktRecv++;

			// Process the Database Description packet.
			Ospfv2HandleDatabaseDescriptionPacket(msg,sourceAddr,interfaceIndex);

			break;
		}

		// It's a Link State Request packet.
	case OSPFv2_LINK_STATE_REQUEST:
		{
			Ospfv2LinkStateRequestPacket* reqPkt = NULL;

			ospf->stats.numLSReqRecv++;

			// get Request packet
			reqPkt = (Ospfv2LinkStateRequestPacket*)msg->Pay_Load;

			// Process the Link State Request packet.
			Ospfv2HandleLSRequestPacket(msg,sourceAddr,interfaceIndex);

			break;
		}

	default:
		{
			ERROR_Assert(TRUE, "Packet type not indentified\n");
		}
	}

	//xdelete(msg);
}
//Sns_Msg_In_Func//


////////////////////////////////////////用户输入事件处理函数 end//////////////////////
void Sns_Model_OSPFv2::modelValsInit(int numberInterfaces,InterfaceInfoType interfaceInfo[MAX_NUM_INTERFACES])
{
	this->numberInterfaces=numberInterfaces;
	this->interfaceInfo=interfaceInfo;
}
//-------------------------------------------------------------------------//
//                             HANDLING LIST                               //
//-------------------------------------------------------------------------//

//-------------------------------------------------------------------------//
// NAME: Ospfv2InitList
// PURPOSE: Initialize a list structure.
// RETURN: None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2InitList(Ospfv2List** list)
{
	Ospfv2List* tmpList = (Ospfv2List*) malloc (sizeof(Ospfv2List));
	tmpList->size = 0;
	tmpList->first = tmpList->last = NULL;
	*list = tmpList;
}
//-------------------------------------------------------------------------//
// NAME: Ospfv2InitRoutingTable
// PURPOSE: Allocate memory for initial routing table.
// RETURN: None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2InitRoutingTable()
{
	int size = sizeof(Ospfv2RoutingTableRow) * OSPFv2_INITIAL_TABLE_SIZE;

	BUFFER_InitializeDataBuffer(&ospf->routingTable.buffer, size);
	ospf->routingTable.numRows = 0;
}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2ReadRouterInterfaceParameters()
// PURPOSE      :Read user specified interfacerelated parameters from file.
// ASSUMPTION   :None.
// RETURN VALUE :None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2ReadRouterInterfaceParameters(Ospfv2Interface* iface,int i)
{
	int retVal;
	int RetArrNum;
	bool boolBuf;
	int intBuf;
	clocktype clockBuf;
	int intArrBuf[MAX_NUM_NEIGHBORS];
	char charBuf;
	char strBuf[SNS_MAX_STRING_LENGTH];
	char paraName[SNS_MAX_STRING_LENGTH];
	sprintf(paraName,"int,[%d]INTERFACE-COST",i);
	retVal = Config_Input->SNS_ReadInt(paraName,&RetArrNum,&intBuf);
	if(retVal)
	{
		ERROR_Assert(intBuf <= 0 || intBuf > 65535,"OSPF interface Init:\nInterface output cost should be between 0 and 65535\n");
		iface->outputCost=intBuf;
	}
	else
	{
		iface->outputCost=OSPFv2_DEFAULT_OUTPUTCOST;
	}
	sprintf(paraName,"clocktype,[%d]RXMT-INTERVAL",i);
	retVal = Config_Input->SNS_ReadTime(paraName, &RetArrNum, &clockBuf);
	if(retVal)
	{
		ERROR_Assert(iface->rxmtInterval <= 0,"OSPF interface Init:\nRetransmission interval should be greater than 0\n ");
		iface->rxmtInterval=clockBuf;
	}
	else
	{
		iface->rxmtInterval=OSPFv2_RXMT_INTERVAL;
	}
	sprintf(paraName,"clocktype,[%d]INF-TRANS-DELAY",i);
	retVal = Config_Input->SNS_ReadTime(paraName, &RetArrNum, &clockBuf);
	if(retVal)
	{
		ERROR_Assert(iface->infTransDelay <= 0,"OSPF interface Init:\nInfTransDelay should be greater than 0\n");
		iface->infTransDelay=clockBuf;
	}
	else
	{
		iface->infTransDelay=OSPFv2_INF_TRANS_DELAY;
	}
	sprintf(paraName,"int,[%d]ROUTER-PRIORITY",i);
	retVal = Config_Input->SNS_ReadInt(paraName, &RetArrNum, &intBuf);
	if(retVal)
	{
		ERROR_Assert(iface->routerPriority < 0,"OSPF interface Init:\nRouter priority should be >= 0\n");
		iface->routerPriority=intBuf;
	}
	else
	{
		iface->routerPriority=0;
	}
	sprintf(paraName,"clocktype,[%d]HELLO-INTERVAL",i);
	retVal = Config_Input->SNS_ReadTime( paraName, &RetArrNum, &clockBuf);
	if(retVal)
	{
		ERROR_Assert(iface->helloInterval <= 0,"OSPF interface Init:\nHello interval should be greater than 0\n");
		iface->helloInterval=clockBuf;
	}
	else
	{
		iface->helloInterval = OSPFv2_HELLO_INTERVAL;
	}
	if (iface->helloInterval < 1 * SECOND|| iface->helloInterval > 0xffff * SECOND)
	{
		iface->helloInterval = OSPFv2_HELLO_INTERVAL;
	}
	sprintf(paraName,"clocktype,[%d]ROUTER-DEAD-INTERVAL",i);
	retVal = Config_Input->SNS_ReadTime( paraName, &RetArrNum, &clockBuf);
	if(retVal)
	{
		ERROR_Assert(iface->routerDeadInterval <= 0,"OSPF interface Init:\nRouter dead interval should be greater than 0\n");
		iface->routerDeadInterval=clockBuf;
	}
	else
	{
		iface->routerDeadInterval = OSPFv2_ROUTER_DEAD_INTERVAL;
	}
	if (iface->routerDeadInterval < 1 * SECOND|| iface->routerDeadInterval > 0xffff * SECOND)
	{
		iface->routerDeadInterval = OSPFv2_ROUTER_DEAD_INTERVAL;
	}
	sprintf(paraName,"int,[%d]INTERFACE-TYPE",i);
	retVal = Config_Input->SNS_ReadInt( paraName, &RetArrNum, &intBuf);
	switch(intBuf)
	{
	case 0:
		iface->type=OSPFv2_NON_OSPF_INTERFACE;
		break;
	case 1:
		iface->type=OSPFv2_POINT_TO_POINT_INTERFACE;
		break;
	case 2:
		iface->type=OSPFv2_BROADCAST_INTERFACE;
		break;
	case 3:
		iface->type=OSPFv2_NBMA_INTERFACE;
		break;
	case 4:
		iface->type=OSPFv2_POINT_TO_MULTIPOINT_INTERFACE;
		break;
	case 5:
		iface->type=OSPFv2_VIRTUAL_LINK_INTERFACE;
		break;
	default:
		iface->type=OSPFv2_POINT_TO_POINT_INTERFACE;
		break;
	}
// 	sprintf(paraName,"int,[%d]NEIGHBOR[%d]",i,MAX_NUM_NEIGHBORS);
// 	retVal = Config_Input->SNS_ReadInt( paraName, &RetArrNum,intArrBuf);
// 	if(retVal)
// 	{
// 		for(int i=0;i<RetArrNum;i++)
// 		{
// 			Ospfv2InsertToNonBroadcastNeighborList(iface->NonBroadcastNeighborList,intArrBuf[i]);
// 		}
// 	}
	if (iface->routerDeadInterval < iface->helloInterval)
	{
		iface->routerDeadInterval=4*iface->helloInterval;
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2GetAreaId()
// PURPOSE      :Get are id from config file for this interface
// ASSUMPTION   :None
// RETURN VALUE :NONE.
//-------------------------------------------------------------------------//

unsigned Sns_Model_OSPFv2::Ospfv2GetAreaId(int i)
{
	unsigned areaID;
	bool retVal;
	int RetArrNum;
	char paraName[SNS_MAX_STRING_LENGTH];
	char strBuf[SNS_MAX_STRING_LENGTH];
	sprintf(paraName,"string,[%d]AREA-ID",i);
	retVal=Config_Input->SNS_ReadString(paraName,&RetArrNum,strBuf);
	if(retVal)
	{
		areaID=hostBitsStr2Uint(strBuf);
		return areaID;
	}
	else
	{
		return OSPFv2_SINGLE_AREA_ID;
	}
}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2GetArea()
// PURPOSE      :Get area structure pointer by area ID.
// ASSUMPTION   :None.
// RETURN VALUE :Ospfv2Area*
//-------------------------------------------------------------------------//

Sns_Model_OSPFv2::Ospfv2Area* Sns_Model_OSPFv2::Ospfv2GetArea(unsigned areaID)
{
	Ospfv2ListItem* listItem = NULL;

	for (listItem = ospf->area->first; listItem; listItem = listItem->next)
	{
		Ospfv2Area* areaInfo = (Ospfv2Area*) listItem->data;

		if (areaInfo->areaID == areaID)
		{
			return areaInfo;
		}
	}

	return NULL;
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2InitArea()
// PURPOSE      :Initializes area data structure
// ASSUMPTION   :None.
// RETURN VALUE :None
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2 ::Ospfv2InitArea(int i,unsigned areaID)
{
	Ospfv2Area* newArea = new Ospfv2Area;

	int RetArrNum;//读取参数个数返回值
	bool retVal = false;
	bool boolBuf;
	unsigned uintBuf;
	char charBuf;
	char strBuf[SNS_MAX_STRING_LENGTH];
	char areaStr[SNS_MAX_STRING_LENGTH];
	char paraName[SNS_MAX_STRING_LENGTH];

	newArea->areaID = areaID;
	Ospfv2InitList(&newArea->areaAddrRange);
	Ospfv2InitList(&newArea->connectedInterface);
	Ospfv2InitList(&newArea->routerLSAList);
	Ospfv2InitList(&newArea->networkLSAList);
	Ospfv2InitList(&newArea->routerSummaryLSAList);
	Ospfv2InitList(&newArea->networkSummaryLSAList);
	Ospfv2InitList(&newArea->groupMembershipLSAList);

	newArea->routerLSTimer = FALSE;
	newArea->routerLSAOriginateTime = (clocktype) 0;
	newArea->groupMembershipLSTimer = FALSE;
	newArea->groupMembershipLSAOriginateTime = (clocktype) 0;

	// If entire domain defined as single area
	if (areaID == OSPFv2_SINGLE_AREA_ID)
	{
		ospf->areaBorderRouter = FALSE;
		newArea->transitCapability = TRUE;
		newArea->externalRoutingCapability = TRUE;
		newArea->stubDefaultCost = 0;

		// Make a link to connected interface structure
		Ospfv2InsertToList(newArea->connectedInterface,0,&ospf->iface[i]);

		// Insert area structure to list
		Ospfv2InsertToList(ospf->area, 0, newArea);
		return;
	}

	// By default the are has transit capability
	newArea->transitCapability = TRUE;
	newArea->externalRoutingCapability = TRUE;
	newArea->stubDefaultCost = 0;
	sprintf(paraName,"string,[%d]Area",i);
	retVal=Config_Input->SNS_ReadString(paraName,&RetArrNum,areaStr);
	sscanf(areaStr,"%*s %s %s %*s",strBuf,paraName);
	uintBuf=hostBitsStr2Uint(strBuf);
	if (uintBuf != areaID)
	{
		return;
	}
	if(strcmp(paraName,"RANGE")==0)
	{
		char* index=areaStr;
		char charMask[SNS_MAX_STRING_LENGTH];
		index=strchr(index,'{');
		while(index!=NULL)
		{
			index=strchr(index,'N');
			if(index==NULL)
			{
				break;
			}
			else
			{
				index++;
			}

			Ospfv2AreaAddressRange* newData=NULL;
			unsigned networkAddr;
			newData = new Ospfv2AreaAddressRange;
			sscanf(index,"%u",&networkAddr);
			newData->address = networkAddr;
			index=1+strchr(index,'-');
			sscanf(index,"%[^,}]",charMask);
			newData->mask=hostBitsStr2Uint(charMask);

			newData->advertise = TRUE;
			// Link back to main area structure
			newData->area = (void*) newArea;
			for (int k = 0; k < OSPFv2_MAX_ATTACHED_AREA; k++)
			{
				newData->advrtToArea[k] = FALSE;
			}
			Ospfv2InsertToList(newArea->areaAddrRange,0, newData);
		}
		index=1+strchr(areaStr,'}');
		sscanf(index,"%u",&uintBuf);
		if (uintBuf != ospf->asID)
		{
			return;
		}
	}
	else if(strcmp(paraName,"STUB")==0)
	{
		Int32 stubDefaultCost;
		sscanf(areaStr,"%*s %*u %*s %d %u",&stubDefaultCost,&uintBuf);
		if (uintBuf == ospf->asID)
		{
			newArea->transitCapability = FALSE;
			newArea->externalRoutingCapability = FALSE;
			newArea->stubDefaultCost = stubDefaultCost;
		}
	}
	//Edit end

	// Make a link to connected interface structure
	Ospfv2InsertToList(newArea->connectedInterface,0,&ospf->iface[i]);

	// Insert area structure to list
	Ospfv2InsertToList(ospf->area, 0, newArea);

	if (ospf->area->size > 1)
	{
		ospf->areaBorderRouter = TRUE;
	}
	else
	{
		ospf->areaBorderRouter = FALSE;
	}

	// If this is backbone area
	if (areaID == 0)
	{
		ospf->backboneArea = newArea;
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2AddInterfaceToArea()
// PURPOSE      :Add new interface to area structure.
// ASSUMPTION   :None.
// RETURN VALUE :None
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2AddInterfaceToArea(unsigned int areaID,int i)
{
	Ospfv2ListItem* listItem = NULL;

	for (listItem = ospf->area->first; listItem; listItem = listItem->next)
	{
		Ospfv2Area* areaInfo = (Ospfv2Area*) listItem->data;

		if (areaInfo->areaID == areaID)
		{
			// Make a link to connected interface structure
			Ospfv2InsertToList(areaInfo->connectedInterface,0,&ospf->iface[i]);

			break;
		}
	}
}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2ScheduleRouterLSA()
// PURPOSE      :Schedule router LSA origination
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2ScheduleRouterLSA(unsigned areaId,bool flush)
{
	Sns_Message* newMsg = new Sns_Message;
	clocktype delay;
	char* msgInfo = NULL;
	Ospfv2LinkStateType lsType;

	Ospfv2Area* thisArea = Ospfv2GetArea(areaId);
	ERROR_Assert(!thisArea, "Area doesn't exist\n");

	if (thisArea->routerLSTimer == TRUE)
	{
		return;
	}
	else if (thisArea->routerLSAOriginateTime == 0)
	{
		delay = (clocktype)1;
		delay += ospf->staggerStartTime;
	}
	else if ((SimClock() - thisArea->routerLSAOriginateTime) >=
		OSPFv2_MIN_LS_INTERVAL)
	{
		delay = (clocktype)	(Get_rand() * OSPFv2_BROADCAST_JITTER);
	}
	else
	{
		delay = (clocktype) (OSPFv2_MIN_LS_INTERVAL
			- (SimClock() - thisArea->routerLSAOriginateTime));
	}

	thisArea->routerLSTimer = TRUE;

	newMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_InEVENT_OspfScheduleLSDB,SNS_MSG_INPUT,NULL,0);
	lsType = OSPFv2_ROUTER;
	msgInfo=(char*)malloc(sizeof(Ospfv2LinkStateType)+ sizeof(unsigned int)+ sizeof(bool));
	char* index=msgInfo;
	memcpy(index, &lsType, sizeof(Ospfv2LinkStateType));
	index += sizeof(Ospfv2LinkStateType);
	memcpy(index, &areaId, sizeof(unsigned int));
	index += sizeof(unsigned int);
//	memcpy(index, &flush, sizeof(Ospfv2LinkStateType)+ sizeof(unsigned int)+ sizeof(bool));

	memcpy( index, &flush, sizeof(bool) ) ;
	newMsg->SNS_Msg_AddInfo(msgInfo,sizeof(Ospfv2LinkStateType)+ sizeof(unsigned int)+ sizeof(bool));
	Scenarios_Data->SNS_Msg_Send(newMsg,Cur_Node_id,delay);




	///***!!!!
	xfree( msgInfo ) ; 

	//	index -= sizeof(unsigned int); 

	//	index -= sizeof(Ospfv2LinkStateType);

//	xfree( index ) ;

//	msgInfo = ( char * )index ;

	
//	xfree( msgInfo ) ;

//	xdelete( index ) ;

}


//-------------------------------------------------------------------------//
// NAME: Ospfv2InitInterface
// PURPOSE: Initialize the available network interface.
// RETURN: None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2InitInterface()
{
	bool retVal;
	int RetArrNum;
	char paraName[SNS_MAX_STRING_LENGTH];
	bool boolBuf;
	int intBuf;
	char charBuf;
	char strBuf[SNS_MAX_STRING_LENGTH];
	list operatorList;

	int i;
	ospf->iface = (Ospfv2Interface*)malloc(sizeof(Ospfv2Interface)*numberInterfaces);
	memset(ospf->iface,0,sizeof(Ospfv2Interface)*numberInterfaces);
	for (i = 0; i <numberInterfaces; i++)
	{
		//NetworkDataIp *ip = (NetworkDataIp *) node->networkData.networkVar;
		ospf->iface[i].isVirtualInterface = FALSE;//默认不是虚链路
		// Determine network type.
		// The default operation mode of OSPF is OSPFv2_BROADCAST_INTERFACE
		// or OSPFv2_POINT_TO_POINT_INTERFACE depending on underlying
		// media type.
		ospf->iface[i].type = OSPFv2_POINT_TO_POINT_INTERFACE;
		ospf->iface[i].interfaceIndex = i;
		//ospf->iface[i].info=&interfaceInfo[i];
		ospf->iface[i].address =interfaceInfo[i].address;
		ospf->iface[i].subnetMask=interfaceInfo[i].subnetMask;
// 		sprintf(paraName,"string,[%d]InterfaceAddress",i);
// 		retVal=node->Config_Input->SNS_ReadString(paraName,&RetArrNum,strBuf);
// 		if(retVal)
// 		{
// 			ospf->iface[i].address = hostBitsStr2Uint(strBuf);
// 		}
// 		sprintf(paraName,"string,[%d]InterfaceSubnetMask",i);
// 		retVal=node->Config_Input->SNS_ReadString(paraName,&RetArrNum,strBuf);
// 		if(retVal)
// 		{
// 			ospf->iface[i].subnetMask = hostBitsStr2Uint(strBuf);
// 		}

		ospf->iface[i].helloInterval = OSPFv2_HELLO_INTERVAL;
		ospf->iface[i].routerDeadInterval = OSPFv2_ROUTER_DEAD_INTERVAL;
		ospf->iface[i].infTransDelay = OSPFv2_INF_TRANS_DELAY;

		// Set default router priority.
		ospf->iface[i].routerPriority = 1;

		ospf->iface[i].outputCost = 1;
		ospf->iface[i].rxmtInterval = OSPFv2_RXMT_INTERVAL;
		Ospfv2InitNonBroadcastNeighborList(&ospf->iface[i].NonBroadcastNeighborList);

		Ospfv2ReadRouterInterfaceParameters(&ospf->iface[i], i);

		// Initializes area data structure, if area is enabled
		if (ospf->partitionedIntoArea == TRUE)
		{
			unsigned areaID;

			// Get Area ID associated with this interface
			areaID=Ospfv2GetAreaId(i);

			ospf->iface[i].areaId = areaID;

			if (!Ospfv2GetArea(areaID))
			{
				Ospfv2InitArea(i, areaID);
			}
			else
			{
				Ospfv2AddInterfaceToArea(areaID, i);
			}
		}
		else
		{
			// Consider the routing domain as single area
			ospf->iface[i].areaId = OSPFv2_SINGLE_AREA_ID;

			if (!Ospfv2GetArea(OSPFv2_SINGLE_AREA_ID))
			{
				Ospfv2InitArea(i,OSPFv2_SINGLE_AREA_ID);
			}
			else
			{
				Ospfv2AddInterfaceToArea(OSPFv2_SINGLE_AREA_ID, i);
			}
		}

		// Set initial interface state
		sprintf(paraName,"bool,[%d]Enable",i);
		retVal=Config_Input->SNS_ReadBool(paraName,&RetArrNum,&boolBuf);
		if(retVal)
		{
			ospf->iface[i].isEnable=boolBuf;
		}
		else
		{
			ospf->iface[i].isEnable=true;
		}
		//if (NetworkIpInterfaceIsEnabled(node, i))
		if(ospf->iface[i].isEnable)
		{
			if (ospf->iface[i].type == OSPFv2_BROADCAST_INTERFACE/*|| ospf->iface[i].type == OSPFv2_ROSPF_INTERFACE*/)
			{				
				Sns_Message* waitTimerMsg=new Sns_Message;
				clocktype delay;

				ospf->iface[i].state = S_Waiting;

				// Send wait timer to self
				waitTimerMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_InEVENT_OspfWaitTimer,SNS_MSG_INPUT,NULL,0);
				char* info=(char*)malloc(sizeof(int));
				*info=i;
				waitTimerMsg->SNS_Msg_AddInfo(info,sizeof(info));
				
				// Use jitter to avoid synchrinisation
				delay = (clocktype) (Get_rand()* OSPFv2_BROADCAST_JITTER	+ OSPFv2_WAIT_TIMER);

				Scenarios_Data->SNS_Msg_Send(waitTimerMsg,Cur_Node_id,delay + ospf->staggerStartTime);

				///***!!!!
				xfree( info ) ;
			}
			else
			{
				ospf->iface[i].state = S_PointToPoint;
			}

			// We may need to produce a new instance of router LSA
			Ospfv2ScheduleRouterLSA(ospf->iface[i].areaId, FALSE);
		}
		else
		{
			ospf->iface[i].state = S_Down;
		}

		Ospfv2InitList(&ospf->iface[i].updateLSAList);
		Ospfv2InitList(&ospf->iface[i].delayedAckList);
		Ospfv2InitList(&ospf->iface[i].neighborList);

		// Q-OSPF Patch Start
		// Initialize queue status and last advertised bandwidth for Q-OSPF
		operatorList.ListInit(&ospf->iface[i].presentStatusOfQueue);
		ospf->iface[i].lastAdvtUtilizedBandwidth = 0;
		// Q-OSPF Patch End
	}
	char buf[SNS_MAX_STRING_LENGTH];
	sprintf(buf, "Node %d connected to multiple areas, must have an interface to backbone\n", Cur_Node_id);
	ERROR_Assert(ospf->partitionedIntoArea && ospf->areaBorderRouter && !ospf->backboneArea,buf);
}
//-------------------------------------------------------------------------//
// NAME: Ospfv2CompDestType()
// PURPOSE:  Compare two Dest type are same or not.
// RETURN: Return TRUE if the dest types are same otherwise FALSE.
//-------------------------------------------------------------------------//

bool Sns_Model_OSPFv2::Ospfv2CompDestType(Ospfv2DestType destType1,Ospfv2DestType destType2)
{
	if (destType1 == destType2)
	{
		return TRUE;
	}
	else if (destType1 == OSPFv2_DESTINATION_ABR_ASBR
		&& ((destType2 == OSPFv2_DESTINATION_ABR)
		|| (destType2 == OSPFv2_DESTINATION_ASBR)))
	{
		return TRUE;
	}
	else if (destType2 == OSPFv2_DESTINATION_ABR_ASBR
		&& ((destType1 == OSPFv2_DESTINATION_ABR)
		|| (destType1 == OSPFv2_DESTINATION_ASBR)))
	{
		return TRUE;
	}

	return FALSE;
}
//-------------------------------------------------------------------------//
// NAME: Ospfv2GetIntraAreaRoute()
// PURPOSE:  Get desired route from routing table
// RETURN: Route entry. NULL if route not found.
//-------------------------------------------------------------------------//

Sns_Model_OSPFv2::Ospfv2RoutingTableRow* Sns_Model_OSPFv2::Ospfv2GetIntraAreaRoute(unsigned destAddr,Ospfv2DestType destType,unsigned areaId)
{
	int i;
	Ospfv2RoutingTable* rtTable = &ospf->routingTable;
	Ospfv2RoutingTableRow* rowPtr = (Ospfv2RoutingTableRow*) BUFFER_GetData(&rtTable->buffer);

	for (i = 0; i < rtTable->numRows; i++)
	{
		if (ospf->isAdvertSelfIntf)
		{
			if ((rowPtr[i].destAddr == destAddr)
				&& Ospfv2CompDestType(rowPtr[i].destType, destType)	
				&& (rowPtr[i].pathType == OSPFv2_INTRA_AREA)
				&& (rowPtr[i].areaId == areaId))
			{
				return &rowPtr[i];
			}
		}
		else
		{
			if ((rowPtr[i].destAddr & rowPtr[i].addrMask) ==(destAddr & rowPtr[i].addrMask)
				&& Ospfv2CompDestType(rowPtr[i].destType, destType)
				&& (rowPtr[i].pathType == OSPFv2_INTRA_AREA)
				&& (rowPtr[i].areaId == areaId))
			{
				return &rowPtr[i];
			}
		}
	}

	return NULL;
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2GetRoute()
// PURPOSE:  Get desired route from routing table
// RETURN: Route entry. NULL if route not found.
//-------------------------------------------------------------------------//

Sns_Model_OSPFv2::Ospfv2RoutingTableRow* Sns_Model_OSPFv2::Ospfv2GetRoute(unsigned destAddr,Ospfv2DestType destType)
{
	int i;
	Ospfv2RoutingTable* rtTable = &ospf->routingTable;
	Ospfv2RoutingTableRow* rowPtr =	(Ospfv2RoutingTableRow*) BUFFER_GetData(&rtTable->buffer);

	for (i = 0; i < rtTable->numRows; i++)
	{
		// BGP-OSPF Patch Start
		if ((rowPtr[i].destAddr == 0) && destAddr)
		{
			continue;
		}
		// BGP-OSPF Patch End
		if (ospf->isAdvertSelfIntf)
		{
			if ((rowPtr[i].destAddr == destAddr)
				&& Ospfv2CompDestType(rowPtr[i].destType, destType))
			{
				return &rowPtr[i];
			}
		}
		else
		{
			if ((rowPtr[i].destAddr & rowPtr[i].addrMask) ==
				(destAddr & rowPtr[i].addrMask)
				&& Ospfv2CompDestType(rowPtr[i].destType, destType))
			{
				return &rowPtr[i];
			}
		}
	}

	return NULL;
}


//-------------------------------------------------------------------------//
// NAME: Ospfv2RoutesMatchSame()
// PURPOSE:  Check if two routes are identical
// RETURN: TRUE if routes are same, FALSE otherwise.
//-------------------------------------------------------------------------//

bool Sns_Model_OSPFv2::Ospfv2RoutesMatchSame(Ospfv2RoutingTableRow* newRoute,Ospfv2RoutingTableRow* oldRoute)
{
	//TBD: Need to check all next hop in case of equal cost multipath
	if ((newRoute->metric == oldRoute->metric)
		&& (newRoute->nextHop == oldRoute->nextHop))
	{
		return TRUE;
	}

	return FALSE;
}


//-------------------------------------------------------------------------//
// NAME: Ospfv2AddRoute()
// PURPOSE:  Add route to routing table
// RETURN: None
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2AddRoute(Ospfv2RoutingTableRow* newRoute)
{
	Ospfv2RoutingTable* rtTable = &ospf->routingTable;
	Ospfv2RoutingTableRow* rowPtr;

	// Get old route if any ..
	if (newRoute->destType != OSPFv2_DESTINATION_NETWORK)
	{
		rowPtr = Ospfv2GetIntraAreaRoute(newRoute->destAddr,newRoute->destType,newRoute->areaId);
	}
	else
	{
		rowPtr = Ospfv2GetRoute(newRoute->destAddr,newRoute->destType);
	}

	if (rowPtr)
	{
		if (Ospfv2RoutesMatchSame(newRoute, rowPtr))
		{
			newRoute->flag = OSPFv2_ROUTE_NO_CHANGE;
		}
		else
		{
			newRoute->flag = OSPFv2_ROUTE_CHANGED;
		}

		memcpy(rowPtr, newRoute, sizeof(Ospfv2RoutingTableRow));
	}
	else
	{
		newRoute->flag = OSPFv2_ROUTE_NEW;
		rtTable->numRows++;

		BUFFER_AddDataToDataBuffer(&rtTable->buffer,(char*) newRoute,sizeof(Ospfv2RoutingTableRow));
	}
}

// BGP-OSPF Patch Start
//-------------------------------------------------------------------------//
// NAME: Ospfv2ExternalRouteInit
// PURPOSE: Inject "External Route" into Routing Table for AS Boundary Router.
// RETURN: None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2ExternalRouteInit()
{
// 	bool retVal = true;
// 	bool boolBuf;
// 	int intBuf;
// 	char charBuf;
// 	char strBuf[SNS_MAX_STRING_LENGTH];
// 	char paraName[SNS_MAX_STRING_LENGTH];
// 	int RetArrNum;
// 
// 	for(int i=0;;i++)
// 	{
// 		sprintf(paraName,"string,[%d]ExternalRoute",i);
// 		retVal=node->Config_Input->SNS_ReadString(paraName,&RetArrNum,strBuf);
// 		if(!retVal)
// 			break;
// 
// 		char destAddressString[SNS_MAX_STRING_LENGTH];
// 		char nextHopString[SNS_MAX_STRING_LENGTH];
// 		unsigned sourceAddress;
// 		int numParameters;
// 		int cost;
// 		numParameters = sscanf(strBuf,"%u %s %s %d",&sourceAddress,destAddressString,nextHopString,&cost);
// 		ERROR_Assert((numParameters < 3) || (numParameters > 4),"OspfExternalRouting: Wrong number of addresses in external route entry.\n");
// 		if (sourceAddress == ospf->routerID)
// 		{
// 			unsigned destAddress;
// 			int destNumHostBits;
// 			unsigned nextHopAddress;
// 			int nextHopHostBits;
// 			bool isNodeId;
// 			Ospfv2RoutingTableRow newRow;
// 			int intfId;
// 			clocktype delay;
// 			
// 			char* msgInfo = NULL;
// 			bool flush = FALSE;
// 			Ospfv2LinkStateType lsType;
// 			unsigned addrMask;
// 
// 			ParseNodeIdHostOrNetworkAddress(destAddressString,destAddress,destNumHostBits);
// 			ParseNodeIdHostOrNetworkAddress(nextHopString,nextHopAddress,nextHopHostBits);
// 			ERROR_Assert(nextHopHostBits != 0,"OspfExternalRouting: Next hop address can't be a subnet\n");
// 			if(numParameters==3)
// 			{
// 				cost=1;
// 			}
// 			// Add new route
// 			newRow.destType = OSPFv2_DESTINATION_NETWORK;
// 			newRow.destAddr = destAddress;
// 			newRow.addrMask = ConvertNumHostBitsToSubnetMask(destNumHostBits);
// 			newRow.option = 0;
// 			newRow.areaId = 0;
// 			newRow.pathType = OSPFv2_TYPE2_EXTERNAL;
// 			newRow.metric = 1;
// 			newRow.type2Metric = cost;
// 			newRow.LSOrigin = NULL;
// 			newRow.advertisingRouter = ospf->routerID;
// 
// 			intfId = NetworkIpGetInterfaceIndexForNextHop(nextHopAddress);
// 			newRow.outIntf =  intfId;
// 
// 			unsigned outIntf = ospf->iface[intfId].address;
// 			if(outIntf == nextHopAddress)
// 			{
// 				nextHopAddress = 0;
// 			}
// 			newRow.nextHop = nextHopAddress;
// 
// 			Ospfv2AddRoute(&newRow);
// 			Sns_Message* newMsg = new Sns_Message;
// 			newMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_InEVENT_OspfScheduleLSDB,SNS_MSG_INPUT,NULL,0);
// 			lsType = OSPFv2_ROUTER_AS_EXTERNAL;
// 			addrMask = ConvertNumHostBitsToSubnetMask(destNumHostBits);
// 			flush = FALSE;
// 			msgInfo=(char*)malloc(2*sizeof(Ospfv2LinkStateType)+6*sizeof(unsigned)+2*sizeof(int)+sizeof(bool));
// 			char* index=msgInfo;
// 			memcpy(index, &lsType, sizeof(Ospfv2LinkStateType));
// 			index += sizeof(Ospfv2LinkStateType);
// 			memcpy(index, &destAddress, sizeof(unsigned));
// 			index += sizeof(unsigned);
// 			memcpy(index, &addrMask, sizeof(unsigned));
// 			index += sizeof(unsigned);
// 			memcpy(index, &nextHopAddress, sizeof(unsigned));
// 			index += sizeof(unsigned);
// 			memcpy(index, &cost, sizeof(int));
// 			index += sizeof(int);
// 			memcpy(index, &flush, sizeof(bool));
// 			newMsg->SNS_Msg_AddInfo(msgInfo,2*sizeof(Ospfv2LinkStateType)+6*sizeof(unsigned)+2*sizeof(int)+sizeof(bool));
// 			// Schedule for originate AS External LSA
// 			delay = (clocktype) (OSPFv2_AS_EXTERNAL_LSA_ORIGINATION_DELAY + (Get_rand() * OSPFv2_BROADCAST_JITTER));
// 			Scenarios_Data->SNS_Msg_Send(newMsg,Cur_Node_id,delay + ospf->staggerStartTime);
// 		}
// 
// 	}
}
// BGP-OSPF Patch End

//-------------------------------------------------------------------------//
// NAME: Ospfv2Init
// PURPOSE: Initialize this routing protocol
// RETURN: NONE.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2Init()
{

	printf( "Node_Id : %5u  Start!!!\n" , Cur_Node_id ) ;

	bool retVal = false;
	bool boolBuf;
	int intBuf;
	char charBuf;
	char strBuf[SNS_MAX_STRING_LENGTH];
	char paraName[SNS_MAX_STRING_LENGTH];
	int RetArrNum;
	clocktype delay;

	ospf=new Ospfv2Data();
	ospf->seed=5;

	ospf->asID=1;
	ospf->isAdvertSelfIntf=false;
	ospf->asBoundaryRouter=false;
	ospf->partitionedIntoArea = false;
	Ospfv2InitList(&ospf->area);
	ospf->backboneArea = NULL;
	ospf->staggerStartTime=(clocktype)0;
// 	// BGP-OSPF Patch Start
// 	// Read the Node's Autonomous System id.
// 	// Format is: [node] AS-NUMBER <AS ID>
// 	sprintf(paraName,"int,AS-NUMBER");
// 	retVal=node->Config_Input->SNS_ReadInt(paraName,&RetArrNum,&intBuf);
// 	if(retVal)
// 	{
// 		ERROR_Assert(intBuf > OSPFv2_MAX_AS_NUMBER || intBuf < OSPFv2_MIN_AS_NUMBER,"Autonomous System id must be less than equal to 65535 and greater than 0\n");
// 		ospf->asID=intBuf;
// 	}
// 	sprintf(paraName,"bool,OSPFv2-ADVRT-SELF-INTF");
// 	retVal=node->Config_Input->SNS_ReadBool(paraName,&RetArrNum,&boolBuf);
// 	if(retVal)
// 	{
// 		ospf->isAdvertSelfIntf=boolBuf;
// 	}
// 	// Determine whether the node is AS BOUNDARY ROUTER or not.
// 	// Format is: [node] AS-BOUNDARY-ROUTER <YES/NO>
// 	// If not specified, node is not a AS BOUNDARY ROUTER.
// 	// Here specify only the Node NOT the Network.
// 	sprintf(paraName,"bool,AS-BOUNDARY-ROUTER");
// 	retVal=node->Config_Input->SNS_ReadBool(paraName,&RetArrNum,&boolBuf);
// 	if(retVal)
// 	{
// 		ospf->asBoundaryRouter=boolBuf;
// 	}
 	Ospfv2InitList(&ospf->asExternalLSAList);
// 	// BGP-OSPF Patch End
 	ospf->collectStat = FALSE;
 	ospf->isMospfEnable = FALSE;
// 	//自治域是否分多区域Area;
// 	sprintf(paraName,"bool,OSPFv2-DEFINE-AREA");
// 	retVal = node->Config_Input->SNS_ReadBool(paraName, &RetArrNum, &boolBuf);
// 	if(retVal)
// 	{
// 		ospf->partitionedIntoArea = boolBuf;
// 		Ospfv2InitList(&ospf->area);
// 		ospf->backboneArea = NULL;
// 	}
// 
// 	sprintf(paraName,"bool,OSPFv2-STAGGER-START");
// 	retVal=node->Config_Input->SNS_ReadBool(paraName,&RetArrNum,&boolBuf);
// 	if(retVal)
// 	{
// 		if(boolBuf)
// 		{
// 			clocktype maxDelay=OSPFv2_LS_REFRESH_TIME;
// 			ospf->staggerStartTime=(clocktype)(Get_rand()*maxDelay);
// 		}
// 		else
// 		{
// 			ospf->staggerStartTime=(clocktype)0;
// 		}
// 	}
	Ospfv2InitRoutingTable();
	// All OSPF Routers should join group AllSPFRouters
	//NetworkIpAddToMulticastGroupList(node, OSPFv2_ALL_SPF_ROUTERS);
	ospf->neighborCount = 0;
	ospf->SPFTimer = (clocktype) 0;

	// Router ID is chosen to be the IP address
	// associated with the first interface.
	Ospfv2InitInterface();
	ospf->routerID = GetDefaultIPv4InterfaceAddress();
	//默认关闭Qos
	ospf->isQosEnabled = FALSE;
	ospf->numQueueAdvertisedForQos = 0;


	// Schedule for sending Hello packets
	delay = (clocktype) (Get_rand() * OSPFv2_BROADCAST_JITTER);
	for ( int index = 0; index < numberInterfaces; index++ )
	{
		Sns_Message* newMsg = new Sns_Message;
		newMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_InEVENT_OspfScheduleHello,SNS_MSG_INPUT,NULL,0);
		char* info=new char;
		*info=index;
		newMsg->SNS_Msg_AddInfo(info,sizeof(char));
		xdelete(info);
		Scenarios_Data->SNS_Msg_Send(newMsg,Cur_Node_id,delay + ospf->staggerStartTime);
	}
	// Timer to age out LSAs in LSDB.
	Sns_Message* newMsg = new Sns_Message;
	newMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_InEVENT_OspfIncrementLSAge,SNS_MSG_INPUT,NULL,0);
	Scenarios_Data->SNS_Msg_Send(newMsg,Cur_Node_id,(clocktype) OSPFv2_LSA_INCREMENT_AGE_INTERVAL+ ospf->staggerStartTime);

	//NetworkIpSetRouterFunction(node,&Ospfv2RouterFunction,interfaceIndex);

	// Set routing table update function for route redistribution
	//RouteRedistributeSetRoutingTableUpdateFunction(node,&Ospfv2HookToRedistribute,interfaceIndex);

	// Initialized the stat variables.
	//memset(&ospf->stats, 0, sizeof(Ospfv2Stats));
	
	// BGP-OSPF Patch Start
// 	if (ospf->asBoundaryRouter)
// 	{
// 		// Determine whether the user inject External Route or not.
// 		// Format is:[node] OSPF-INJECT-ROUTE
// 		// Here specify only the Node NOT the Network.
// 		sprintf(paraName,"bool,OSPFv2-INJECT-EXTERNAL-ROUTE");
// 		retVal=node->Config_Input->SNS_ReadBool(paraName,&RetArrNum,&boolBuf);
// 		if(retVal)
// 		{
// 			if(boolBuf)
// 			{
 				Ospfv2ExternalRouteInit();
// 			}
// 		}
// 	}
	// BGP-OSPF Patch End
}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2InterfaceBelongToThisArea()
// PURPOSE      :Verify if the interface belong to this area.
// ASSUMPTION   :None.
// RETURN VALUE :bool
//-------------------------------------------------------------------------//
bool Sns_Model_OSPFv2::Ospfv2InterfaceBelongToThisArea(int areaId,int interfaceIndex)
{
	Ospfv2ListItem* listItem = NULL;
	Ospfv2Interface* thisInterface = NULL;
	Ospfv2Area* thisArea = Ospfv2GetArea(areaId);
	ERROR_Assert(!thisArea, "Area doesn't exist\n");
	listItem = thisArea->connectedInterface->first;
	while (listItem)
	{
		thisInterface = (Ospfv2Interface*) listItem->data;
		if (thisInterface->address == ospf->iface[interfaceIndex].address)
		{
			return TRUE;
		}
		listItem = listItem->next;
	}
	return FALSE;
}
//-------------------------------------------------------------------------//
// NAME     :Ospfv2AddSelfRoute()
// PURPOSE  :Add self interface as type3 link.
// RETURN   :None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2AddSelfRoute(int interfaceIndex,Ospfv2LinkInfo** linkInfo)
{
	(*linkInfo)->linkID = ospf->iface[interfaceIndex].address;
	(*linkInfo)->linkData = 0xFFFFFFFF;
	(*linkInfo)->type = OSPFv2_STUB;
	(*linkInfo)->metric = 0;
	if (ospf->isQosEnabled == TRUE)
	{
		//(*linkInfo)->numTOS = (unsigned char) (2 *  ospf->numQueueAdvertisedForQos);
		//// Update the position of the working pointer
		//(*linkInfo) = (*linkInfo) + 1;
		//// To advertise the QoS related information for the Link
		//QospfGetQosInformationForTheLink(node, interfaceIndex, linkInfo);
	}
	else
	{
		// As Q-OSPF is not enabled, numTOS must be zero
		(*linkInfo)->numTOS = 0;
		// Update the position of the working pointer
		(*linkInfo) = (*linkInfo) + 1;
	}
}

//-------------------------------------------------------------------------//
// NAME     :Ospfv2AddType1Link()
// PURPOSE  :Add Point-to-Point link.
// RETURN   :None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2AddType1Link(int interfaceIndex,Ospfv2Neighbor* tempNbInfo,Ospfv2LinkInfo** linkInfo)
{
	(*linkInfo)->linkID = tempNbInfo->neighborID;
	if (ospf->iface[interfaceIndex].isVirtualInterface == TRUE)
	{
		(*linkInfo)->linkData = interfaceIndex;
	}
	else
	{
		(*linkInfo)->linkData = ospf->iface[interfaceIndex].address;
	}
	(*linkInfo)->type = OSPFv2_POINT_TO_POINT;
	(*linkInfo)->metric = (short) ospf->iface[interfaceIndex].outputCost;
	if (ospf->isQosEnabled == TRUE)
	{
		//(*linkInfo)->numTOS = (unsigned char) (2*  ospf->numQueueAdvertisedForQos);

		//// Update the position of the working pointer
		//(*linkInfo) = (*linkInfo) + 1;

		//// To advertise the QoS related information for the Link
		//QospfGetQosInformationForTheLink(node, interfaceIndex, linkInfo);
	}
	else
	{
		// As Q-OSPF is not enabled, numTOS must be zero
		(*linkInfo)->numTOS = 0;

		// Update the position of the working pointer
		(*linkInfo) = (*linkInfo) + 1;
	}
}


//-------------------------------------------------------------------------//
// NAME     :Ospfv2AddType2Link()
// PURPOSE  :Add link to transit network.
// RETURN   :None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2AddType2Link(int interfaceIndex,Ospfv2LinkInfo** linkInfo)
{
	// This broadcast network is represented by the designated router.
	(*linkInfo)->linkID = ospf->iface[interfaceIndex].designatedRouterIPAddress;
	(*linkInfo)->linkData = ospf->iface[interfaceIndex].address;
	(*linkInfo)->type = OSPFv2_TRANSIT;
	(*linkInfo)->metric = (short) ospf->iface[interfaceIndex].outputCost;
	if (ospf->isQosEnabled == TRUE)
	{
		// numTOS field is the number of QoS Metrics advertised. In our
		// consideration, we are advertising available bandwidth and
		// average delay of all queue of each interface.
		//(*linkInfo)->numTOS = (unsigned char) (2 * ospf->numQueueAdvertisedForQos);

		//// Update the position of the working pointer
		//*linkInfo = *linkInfo + 1;

		//// To advertise the QoS related information for the Link
		//QospfGetQosInformationForTheLink(node, interfaceIndex, linkInfo);
	}
	else
	{
		// As Q-OSPF is not enabled, numTOS must be zero
		(*linkInfo)->numTOS = 0;

		// Update the position of the working pointer
		*linkInfo = *linkInfo + 1;
	}
}

//-------------------------------------------------------------------------//
// NAME     :Ospfv2AddType3Link()
// PURPOSE  :Add link to stub network.
// RETURN   :None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2AddType3Link(int interfaceIndex,Ospfv2LinkInfo** linkInfo)
{
	// This stub network is represented by the IP network address.
	(*linkInfo)->linkID =ospf->iface[interfaceIndex].address;
// 	if(ospf->iface[interfaceIndex].address>=0xF0000000)
// 	{
// 		printf("Node %u's Interface 7 (%u) has been added\n",Cur_Node_id,ospf->iface[interfaceIndex].address);
// 	}
	(*linkInfo)->linkData =ospf->iface[interfaceIndex].subnetMask;
	(*linkInfo)->type = OSPFv2_STUB;
	(*linkInfo)->metric = (short) ospf->iface[interfaceIndex].outputCost;
	if (ospf->isQosEnabled == TRUE)
	{
		// numTOS field is the number of QoS Metrics advertised. In our
		// consideration, we are advertising available bandwidth and
		// average delay of all queue of each interface.
		//(*linkInfo)->numTOS = (unsigned char) (2 * ospf->numQueueAdvertisedForQos);
		//// Update the position of the working pointer
		//*linkInfo = *linkInfo + 1;
		//// To advertise the QoS related information for the Link
		//QospfGetQosInformationForTheLink(node, interfaceIndex, linkInfo);
	}
	else
	{
		// As Q-OSPF is not enabled, numTOS must be zero
		(*linkInfo)->numTOS = 0;
		// Update the position of the working pointer
		*linkInfo = *linkInfo + 1;
	}
}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2RouterFullyAdjacentWithDR()
// PURPOSE      :Verify if the router is fully adjacent with DR.
// ASSUMPTION   :None.
// RETURN VALUE :bool
//-------------------------------------------------------------------------//

bool Sns_Model_OSPFv2::Ospfv2RouterFullyAdjacentWithDR(int interfaceIndex)
{
	Ospfv2Neighbor* neighborInfo = NULL;
	Ospfv2ListItem* listItem = ospf->iface[interfaceIndex].neighborList->first;

	while (listItem)
	{
		neighborInfo = (Ospfv2Neighbor*) listItem->data;
		if (neighborInfo->neighborID ==	ospf->iface[interfaceIndex].designatedRouter&& neighborInfo->state == S_Full)
		{
			return TRUE;
		}
		listItem = listItem->next;
	}
	return FALSE;
}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2DRFullyAdjacentWithAnyRouter()
// PURPOSE      :Verify if router is fully adjacent with any of it's
//               neighbor.
// ASSUMPTION   :None.
// RETURN VALUE :bool
//-------------------------------------------------------------------------//

bool Sns_Model_OSPFv2::Ospfv2DRFullyAdjacentWithAnyRouter(int interfaceIndex)
{
	Ospfv2Neighbor* neighborInfo = NULL;
	Ospfv2ListItem* listItem = ospf->iface[interfaceIndex].neighborList->first;
	while (listItem)
	{
		neighborInfo = (Ospfv2Neighbor*) listItem->data;
		if (neighborInfo->state == S_Full)
		{
			return TRUE;
		}
		listItem = listItem->next;
	}
	return FALSE;
}

//-------------------------------------------------------------------------//
// NAME     :Ospfv2AddHostRoute()
// PURPOSE  :Add single host route.
// RETURN   :None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2AddHostRoute(int interfaceIndex,Ospfv2Neighbor* tempNbInfo,Ospfv2LinkInfo** linkInfo)
{
	(*linkInfo)->linkID = tempNbInfo->neighborIPAddress;
	(*linkInfo)->linkData = 0xFFFFFFFF;
	(*linkInfo)->type = OSPFv2_STUB;
	(*linkInfo)->metric = (short) ospf->iface[interfaceIndex].outputCost;

	if (ospf->isQosEnabled == TRUE)
	{
		//(*linkInfo)->numTOS = (unsigned char) (2 *  ospf->numQueueAdvertisedForQos);

		//// Update the position of the working pointer
		//(*linkInfo) = (*linkInfo) + 1;

		//// To advertise the QoS related information for the Link
		//QospfGetQosInformationForTheLink(node, interfaceIndex, linkInfo);
	}
	else
	{
		// As Q-OSPF is not enabled, numTOS must be zero
		(*linkInfo)->numTOS = 0;

		// Update the position of the working pointer
		(*linkInfo) = (*linkInfo) + 1;
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2LookupLSAList()
// PURPOSE      :Search for the LSA in list
// ASSUMPTION   :None
// RETURN VALUE :Ospfv2LinkStateHeader*
//-------------------------------------------------------------------------//

Sns_Model_OSPFv2::Ospfv2LinkStateHeader* Sns_Model_OSPFv2::Ospfv2LookupLSAList(Ospfv2List* list,unsigned advertisingRouter,unsigned linkStateID)
{
	Ospfv2LinkStateHeader* listLSHeader = NULL;

	Ospfv2ListItem* item = list->first;

	while (item)
	{
		// Get LS Header
		listLSHeader = (Ospfv2LinkStateHeader*) item->data;

		if (listLSHeader->advertisingRouter == advertisingRouter&& listLSHeader->linkStateID == linkStateID)
		{
			return listLSHeader;
		}

		item = item->next;
	}
	return NULL;
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2RemoveFromList
// PURPOSE: This a general list handling function. Various lists are used in
//          the OSPF structure. Removes an item from the list. "type" is used
//          to indicate whether the list item contains a Message
//          structure or not. If so, call MESSAGE_Free() instead of
//          MEM_free().
// RETURN: None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2RemoveFromList(Ospfv2List* list,Ospfv2ListItem* listItem,bool type)
{
	Ospfv2ListItem* nextListItem = NULL;

	if (list == NULL || listItem == NULL)
	{
		return;
	}

	if (list->size == 0)
	{
		return;
	}

	nextListItem = listItem->next;

	if (list->size == 1)
	{
		list->first = list->last = NULL;
	}
	else if (list->first == listItem)
	{
		list->first = listItem->next;
		list->first->prev = NULL;
	}
	else if (list->last == listItem)
	{
		list->last = listItem->prev;
		list->last->next = NULL;
	}
	else
	{
		listItem->prev->next = listItem->next;
		if (listItem->prev->next != NULL)

		{
			listItem->next->prev = listItem->prev;
		}
	}

	list->size--;

	if (listItem->data != NULL)
	{
		if (type == FALSE)
		{
			xfree (listItem->data);
		}
		else
		{
			free((Sns_Message*)listItem->data);
		}
	}

	xfree(listItem);
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2ListIsEmpty()
// PURPOSE: Check whether a list is empty.
// RETURN: bool
//-------------------------------------------------------------------------//

bool Sns_Model_OSPFv2::Ospfv2ListIsEmpty(Ospfv2List* list)
{
	return ((list->size == 0) ? TRUE : FALSE);
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2RemoveLSAFromRetxList
// PURPOSE      :Removes all LSA that corresponds to the specified
//               LSA from the retransmission list of all neighbors.
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2RemoveLSAFromRetxList(char linkStateType,unsigned linkStateID,unsigned advertisingRouter,unsigned areaId)
{
	int i;
	Ospfv2ListItem* tempListItem = NULL;
	Ospfv2ListItem* retxItem = NULL;
	Ospfv2Neighbor* nbrInfo = NULL;

	Ospfv2LinkStateHeader* LSHeader = NULL;

	// Look at each of my attached interface.
	for (i = 0; i < numberInterfaces; i++)
	{
		if (ospf->iface[i].type == OSPFv2_NON_OSPF_INTERFACE)
		{
			continue;
		}
		if(ospf->iface[i].address == UNKNOWNADDRESS)
		{
			continue;
		}
		// Skip the interface if it doesn't belong to specified area
		if (ospf->iface[i].areaId != areaId)
		{
			continue;
		}

		tempListItem = ospf->iface[i].neighborList->first;

		// Get the neighbors for each interface.
		while (tempListItem)
		{
			nbrInfo = (Ospfv2Neighbor*) tempListItem->data;
			ERROR_Assert(!nbrInfo,"Neighbor not found in the Neighbor list\n");

			retxItem = nbrInfo->linkStateRetxList->first;

			// Look for LSA in retransmission list of each neighbor.
			while (retxItem)
			{
				LSHeader = (Ospfv2LinkStateHeader*) retxItem->data;

				// If LSA exists in retransmission list, remove it.
				if ((LSHeader->linkStateType == linkStateType)	&& (LSHeader->linkStateID == linkStateID)&& (LSHeader->advertisingRouter == advertisingRouter))
				{
					Ospfv2ListItem* deleteItem = retxItem;
					retxItem = retxItem->next;

					// Remove acknowledged LSA.
					Ospfv2RemoveFromList(nbrInfo->linkStateRetxList,deleteItem,FALSE);
				}
				else
				{
					retxItem = retxItem->next;
				}
			}

			if ((Ospfv2ListIsEmpty(nbrInfo->linkStateRetxList))	&& (nbrInfo->LSRetxTimer == TRUE))
			{
				nbrInfo->LSRetxTimer = FALSE;
				nbrInfo->rxmtTimerSequenceNumber++;
			}

			tempListItem = tempListItem->next;
		}
	}
}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2SearchRequestList()
// PURPOSE      :Search for a LSA in Link State Request list
// ASSUMPTION   :None
// RETURN VALUE :Return LSA if found, otherwise return NULL
//-------------------------------------------------------------------------//

Sns_Model_OSPFv2::Ospfv2LinkStateHeader* Sns_Model_OSPFv2::Ospfv2SearchRequestList(Ospfv2List* tList,Ospfv2LinkStateHeader* LSHeader)
{
	Ospfv2ListItem* listItem = tList->first;

	while (listItem)
	{
		Ospfv2LSReqItem* itemInfo = (Ospfv2LSReqItem*) listItem->data;
		Ospfv2LinkStateHeader* listLSHeader = itemInfo->LSHeader;

		if ((LSHeader->linkStateType == listLSHeader->linkStateType)  &&(LSHeader->linkStateID == listLSHeader->linkStateID) &&	(LSHeader->advertisingRouter == listLSHeader->advertisingRouter))
		{
			return listLSHeader;
		}
		listItem = listItem->next;
	}

	return NULL;
}


//-------------------------------------------------------------------------//
// NAME         :Ospfv2CompareLSA()
// PURPOSE      :Check whether the received LSA is more recent
// ASSUMPTION   :None
// RETURN VALUE : 1 if the first LSA is more recent,
//              :-1 if the second LSA is more recent,
//              : 0 if the two LSAs are same,
//-------------------------------------------------------------------------//

int Sns_Model_OSPFv2::Ospfv2CompareLSA(Ospfv2LinkStateHeader* LSHeader,Ospfv2LinkStateHeader* oldLSHeader)
{
	// If LSA have newer sequence number
	if (LSHeader->linkStateSequenceNumber > oldLSHeader->linkStateSequenceNumber)
	{
		return 1;
	}
	else if (oldLSHeader->linkStateSequenceNumber >	LSHeader->linkStateSequenceNumber)
	{
		return -1;
	}
	// If only the new LSA have age equal to LSMaxAge
	else if ((LSHeader->linkStateAge >=	(OSPFv2_LSA_MAX_AGE / SECOND))	&& (oldLSHeader->linkStateAge <	(OSPFv2_LSA_MAX_AGE / SECOND)))
	{

		return 1;
	}
	else if ((oldLSHeader->linkStateAge >=(OSPFv2_LSA_MAX_AGE / SECOND))&& (LSHeader->linkStateAge <(OSPFv2_LSA_MAX_AGE / SECOND)))
	{
		return -1;
	}
	// If the LS age fields of two instances differ by more than MaxAgeDiff,
	// the instance having the smaller LS age is considered to be more
	// recent.
	else if ((abs(LSHeader->linkStateAge - oldLSHeader->linkStateAge) >	(OSPFv2_MAX_AGE_DIFF / SECOND))	&& (LSHeader->linkStateAge < oldLSHeader->linkStateAge))
	{
		return 1;
	}
	else if ((abs(LSHeader->linkStateAge - oldLSHeader->linkStateAge) >	(OSPFv2_MAX_AGE_DIFF / SECOND))	&& (LSHeader->linkStateAge > oldLSHeader->linkStateAge))
	{
		return -1;
	}

	return 0;
}


//-------------------------------------------------------------------------//
// NAME         :Ospfv2RemoveFromRequestList()
// PURPOSE      :Remove this LSA from Link State Request list
// ASSUMPTION   :None
// RETURN VALUE :NULL
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2RemoveFromRequestList(Ospfv2List* tlist,Ospfv2LinkStateHeader* LSHeader)
{
	Ospfv2ListItem* listItem = tlist->first;

	ERROR_Assert(tlist->size == 0, "Request list is empty\n");

	while (listItem)
	{
		Ospfv2LSReqItem* itemInfo = (Ospfv2LSReqItem*) listItem->data;
		Ospfv2LinkStateHeader* listLSHeader = itemInfo->LSHeader;

		if ((LSHeader->linkStateType == listLSHeader->linkStateType) &&	(LSHeader->linkStateID == listLSHeader->linkStateID) &&	(LSHeader->advertisingRouter == listLSHeader->advertisingRouter))
		{
			// Remove item from list
			xfree(itemInfo->LSHeader);
			Ospfv2RemoveFromList(tlist, listItem, FALSE);

			break;
		}

		listItem = listItem->next;
	}
}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2CopyLSA()
// PURPOSE      :Copy LSA.
// ASSUMPTION   :None.
// RETURN VALUE :char*
//-------------------------------------------------------------------------//

char* Sns_Model_OSPFv2::Ospfv2CopyLSA(char* LSA)
{
	Ospfv2LinkStateHeader* LSHeader =(Ospfv2LinkStateHeader*) LSA;
	char* newLSA = (char *) malloc(LSHeader->length);

	memcpy(newLSA, LSA, LSHeader->length);
	return newLSA;
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2AddToLSRetxList()
// PURPOSE      :Add LSA to retransmission list.
// ASSUMPTION   :None.
// RETURN VALUE :None
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2AddToLSRetxList(int interfaceIndex,Ospfv2Neighbor* nbrInfo,char* LSA)
{
	char* newLSA = Ospfv2CopyLSA(LSA);
	Ospfv2LinkStateHeader* newLSHeader = (Ospfv2LinkStateHeader*) newLSA;

	// Add to link state retransmission list.
	Ospfv2InsertToList(nbrInfo->linkStateRetxList,SimClock(),(void*) newLSA);

	// Set timer for possible retransmission.
	if (nbrInfo->LSRetxTimer == FALSE)
	{
		nbrInfo->rxmtTimerSequenceNumber++;
		Ospfv2SetTimer(interfaceIndex,	MSG_InEVENT_OspfRxmtTimer,nbrInfo->neighborIPAddress,ospf->iface[interfaceIndex].rxmtInterval,nbrInfo->rxmtTimerSequenceNumber,newLSHeader->advertisingRouter,OSPFv2_LINK_STATE_UPDATE);
		nbrInfo->LSRetxTimer = TRUE;
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2QueueLSAToFlood()
// PURPOSE      :Add LSA to update LSA list for flooding
// ASSUMPTION   :None.
// RETURN VALUE :None
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2QueueLSAToFlood(Ospfv2Interface* thisInterface,char* LSA)
{
	char* newLSA = NULL;
	Ospfv2LinkStateHeader* LSHeader = (Ospfv2LinkStateHeader*) LSA;
	Ospfv2ListItem* listItem = thisInterface->updateLSAList->first;

	while (listItem)
	{
		Ospfv2LinkStateHeader* listLSHeader =(Ospfv2LinkStateHeader*) listItem->data;

		// If this LSA present in list
		if (LSHeader->linkStateType == listLSHeader->linkStateType &&LSHeader->linkStateID == listLSHeader->linkStateID &&LSHeader->advertisingRouter == listLSHeader->advertisingRouter)
		{
			// If this is newer instance add this instance replacing old one
			if (Ospfv2CompareLSA(LSHeader, listLSHeader) > 0)
			{
				xfree(listItem->data);
				listItem->data = (void*) Ospfv2CopyLSA(LSA);
				listItem->timeStamp = SimClock();
			}

			return;
		}

		listItem = listItem->next;
	}

	newLSA = Ospfv2CopyLSA(LSA);

	// Add to update LSA list.
	Ospfv2InsertToList(	thisInterface->updateLSAList,SimClock(),(void*) newLSA);
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2FloodLSA
// PURPOSE      :Flood LSA throughout the area.
// ASSUMPTION   :None.
// RETURN VALUE :TRUE if LSA flooded back to receiving interface,
//               FALSE otherwise.
//-------------------------------------------------------------------------//

bool Sns_Model_OSPFv2::Ospfv2FloodLSA(int inIntf,char* LSA,unsigned sourceAddr,unsigned areaId)
{
	int i;
	Ospfv2Neighbor* tempNeighborInfo = NULL;
	Ospfv2ListItem* tempListItem = NULL;

	Ospfv2LinkStateHeader* LSHeader =(Ospfv2LinkStateHeader*) LSA;

	bool floodedBackToRecvIntf = FALSE;

	// Need to first remove LSA from all neigbhor's
	// retx list before flooding it.
	// This is because we want to use the most
	// up-to-date LSA for retransmission.

	Ospfv2RemoveLSAFromRetxList(LSHeader->linkStateType,LSHeader->linkStateID,	LSHeader->advertisingRouter,areaId);

	for (i = 0; i < numberInterfaces; i++)
	{
		bool addIntoRetxList = FALSE;

		//Since the interface is down so we cannot send any
		// Update regarding the same.
		if (/*(NetworkIpGetUnicastRoutingProtocolType(node, i) ==ROUTING_PROTOCOL_OSPFv2) &&*/ ospf->iface[i].state == S_Down)
		{
			continue;
		}

		// If this is not eligible interface, examine next interface
		if (ospf->iface[i].type == OSPFv2_NON_OSPF_INTERFACE|| (!Ospfv2InterfaceBelongToThisArea(areaId, i))
			)
		{
			continue;
		}
		if(ospf->iface[i].address == UNKNOWNADDRESS)
		{
			continue;
		}
		tempListItem = ospf->iface[i].neighborList->first;

		// Check each neighbor on this interface.
		while (tempListItem)
		{
			tempNeighborInfo = (Ospfv2Neighbor*) tempListItem->data;
			ERROR_Assert(!tempNeighborInfo,"Neighbor not found in the Neighbor list\n");

			// RFC2328, Sec-13.3.1.a
			// If neighbor is in a lesser state than exchange,
			// it does not participate in flooding
			if (tempNeighborInfo->state < S_Exchange)
			{
				tempListItem = tempListItem->next;
				continue;
			}

			// RFC2328, Sec-13.3.1.b
			// If neighbor state is Exchange or Loading
			else if (tempNeighborInfo->state != S_Full)
			{
				Ospfv2LinkStateHeader* listLSHeader =Ospfv2SearchRequestList(tempNeighborInfo->linkStateRequestList,LSHeader);

				if (listLSHeader)
				{
					int moreRecentIndicator =	Ospfv2CompareLSA(LSHeader, listLSHeader);

					// If the new LSA is less recent
					if (moreRecentIndicator < 0)
					{
						tempListItem = tempListItem->next;
						continue;
					}
					// If the two LSAs are same instances
					else if (moreRecentIndicator == 0)
					{
						Ospfv2RemoveFromRequestList(tempNeighborInfo->linkStateRequestList,listLSHeader);

						tempListItem = tempListItem->next;
						continue;
					}
					// New LSA is more recent
					else
					{
						Ospfv2RemoveFromRequestList(tempNeighborInfo->linkStateRequestList,	listLSHeader);
					}
				}
			}

			// RFC2328, Sec-13.3.1.c
			// If LSA received from this neighbor, examine next neighbor

			if (tempNeighborInfo->neighborIPAddress == sourceAddr)
			{
				tempListItem = tempListItem->next;
				continue;
			}

			// RFC2328, Sec-13.3.1.d
			// Add to Retransmission list

			Ospfv2AddToLSRetxList(i, tempNeighborInfo, LSA);

			addIntoRetxList = TRUE;
			tempListItem = tempListItem->next;
		}

		// RFC2328, Sec-13.3.2
		if (!addIntoRetxList)
		{
			continue;
		}
		if ((ospf->iface[i].type == OSPFv2_BROADCAST_INTERFACE)	&& (sourceAddr != ANY_DEST) && (i == inIntf))
		{
			// RFC2328, Sec-13.3.3
			// If the new LSA was received on this interface, and it was
			// received from either the Designated Router or the Backup
			// Designated Router, chances are that all the neighbors have
			// received the LSA already. Therefore, examine the next
			// interface.

			if ((ospf->iface[i].designatedRouterIPAddress == sourceAddr)|| (ospf->iface[i].backupDesignatedRouterIPAddress== sourceAddr))
			{
				continue;
			}

			// RFC2328, Sec-13.3.4
			// If the new LSA was received on this interface, and the
			// interface state is Backup, examine the next interface. The
			// Designated Router will do the flooding on this interface.

			if (ospf->iface[i].state == S_Backup)
			{
				continue;
			}
		}

		// Note if we flood the LSA back to receiving interface
		// then this will be used later for sending Ack.

		if ((sourceAddr != ANY_DEST) && (i == inIntf))
		{
			floodedBackToRecvIntf = TRUE;
		}

		Ospfv2QueueLSAToFlood(&ospf->iface[i], LSA);

		if (ospf->iface[i].floodTimerSet == FALSE)
		{
			Sns_Message* floodMsg=new Sns_Message;
			floodMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_InEVENT_OspfFloodTimer,SNS_MSG_INPUT,NULL,0);
			clocktype delay;
			ospf->iface[i].floodTimerSet = TRUE;
			char* msgInfo=(char*)malloc(sizeof(int));
			memcpy(msgInfo,&i,sizeof(int));
			delay = (clocktype) (Get_rand()*  OSPFv2_FLOOD_TIMER);
			floodMsg->SNS_Msg_AddInfo(msgInfo,sizeof(int));
			Scenarios_Data->SNS_Msg_Send(floodMsg, Cur_Node_id,delay);

			////****!!!!
			xfree( msgInfo ) ;

		}
	}

	return floodedBackToRecvIntf;
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2FlushLSA()
// PURPOSE      :Flush LSA from routing domain
// ASSUMPTION   :None
// RETURN VALUE :None
// NOTE         :To flush AS-External LSA call this function with areaId
//               argument as OSPFv2_INVALID_AREA_ID. This was just because
//               AS-External LSAs are particularly associated with entire
//               domain and not to any specific are. So we need to flood
//               this LSA in each attached area.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2FlushLSA(char* LSA, unsigned areaId)
{
	Ospfv2LinkStateHeader* LSHeader = (Ospfv2LinkStateHeader*) LSA;

	LSHeader->linkStateAge = (OSPFv2_LSA_MAX_AGE / SECOND);
	
	if (LSHeader->linkStateType == OSPFv2_ROUTER_AS_EXTERNAL)
	{
		Ospfv2ListItem* listItem = ospf->area->first;

		ERROR_Assert(areaId == OSPFv2_INVALID_AREA_ID,"Wrong function call\n");

		while (listItem)
		{
			Ospfv2Area* thisArea = (Ospfv2Area*) listItem->data;
			ERROR_Assert(!thisArea, "Area structure not initialized");

			Ospfv2FloodLSA(ANY_INTERFACE, LSA, ANY_DEST, thisArea->areaID);
			listItem = listItem->next;
		}
	}
	else
	{
		// Flood LSA
		Ospfv2FloodLSA(ANY_INTERFACE, LSA, ANY_DEST, areaId);
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2RemoveLSAFromList()
// PURPOSE      :Remove LSA from list
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2RemoveLSAFromList(Ospfv2List* tlist,char* LSA)
{
	Ospfv2ListItem* listItem = tlist->first;
	Ospfv2LinkStateHeader* LSHeader = (Ospfv2LinkStateHeader*) LSA;
	Ospfv2LinkStateHeader* listLSHeader = NULL;

	while (listItem)
	{
		listLSHeader = (Ospfv2LinkStateHeader*) listItem->data;

		if (listLSHeader->advertisingRouter == LSHeader->advertisingRouter	&& listLSHeader->linkStateID == LSHeader->linkStateID)
		{
			Ospfv2RemoveFromList(tlist, listItem, FALSE);
			break;
		}

		listItem = listItem->next;
	}
}


//-------------------------------------------------------------------------//
// NAME         :Ospfv2RemoveLSAFromLSDB()
// PURPOSE      :Remove LSA from LSDB
// ASSUMPTION   :None
// RETURN VALUE :None
// NOTE         :To remove AS-External LSA from LSDB call this function with
//               areaId argument as OSPFv2_INVALID_AREA_ID.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2RemoveLSAFromLSDB(char* LSA,unsigned areaId)
{
	Ospfv2LinkStateHeader* LSHeader = (Ospfv2LinkStateHeader*) LSA;
	Ospfv2Area*  thisArea = NULL;

	// BGP-OSPF Patch Start
	if (LSHeader->linkStateType != OSPFv2_ROUTER_AS_EXTERNAL)
	{
		thisArea = Ospfv2GetArea(areaId);
		ERROR_Assert(!thisArea, "Area doesn't exist\n");
	}
	// BGP-OSPF Patch End

	switch (LSHeader->linkStateType)
	{
	case OSPFv2_ROUTER:
		{
			Ospfv2RemoveLSAFromList(thisArea->routerLSAList, LSA);
			break;
		}

	case OSPFv2_NETWORK:
		{
			Ospfv2RemoveLSAFromList(thisArea->networkLSAList, LSA);
			break;
		}

	case OSPFv2_NETWORK_SUMMARY:
		{
			Ospfv2RemoveLSAFromList(thisArea->networkSummaryLSAList, LSA);
			break;
		}
		// BGP-OSPF Patch Start
	case OSPFv2_ROUTER_SUMMARY:
		{
			Ospfv2RemoveLSAFromList(thisArea->routerSummaryLSAList, LSA);

			break;
		}
	case OSPFv2_ROUTER_AS_EXTERNAL:
		{
			ERROR_Assert(areaId == OSPFv2_INVALID_AREA_ID,"Wrong function call\n");

			Ospfv2RemoveLSAFromList(ospf->asExternalLSAList, LSA);

			break;
		}
		// BGP-OSPF Patch End
	case OSPFv2_GROUP_MEMBERSHIP:
		{
			Ospfv2RemoveLSAFromList(thisArea->groupMembershipLSAList, LSA);
			break;
		}

	default:
		{
			ERROR_Assert(TRUE, "Unknow linkStateType\n");
		}
	}
}
//-------------------------------------------------------------------------//
// NAME     :Ospfv2CreateLSHeader()
// PURPOSE  :Create LS Header for newly created LSA.
// RETURN   :bool.
//-------------------------------------------------------------------------//

bool Sns_Model_OSPFv2::Ospfv2CreateLSHeader(unsigned areaId,Ospfv2LinkStateType LSType,Ospfv2LinkStateHeader* LSHeader,Ospfv2LinkStateHeader* oldLSHeader)
{
	Ospfv2Area* thisArea = NULL;

	// BGP-OSPF Patch Start
	if (LSType != OSPFv2_ROUTER_AS_EXTERNAL)
	{
		thisArea = Ospfv2GetArea(areaId);
		ERROR_Assert(!thisArea, "Area doesn't exist\n");
	}
	// BGP-OSPF Patch End

	memset(LSHeader, 0, sizeof(Ospfv2LinkStateHeader));
	LSHeader->linkStateAge = 0;

	// Set option field
	Ospfv2LinkStateHeaderSetOptions1(&(LSHeader->ospfLsh), 0);

	// BGP-OSPF Patch Start
	if (LSType == OSPFv2_ROUTER_AS_EXTERNAL ||thisArea->externalRoutingCapability == TRUE)
	{
		Ospfv2LinkStateHeaderSetExt(&(LSHeader->ospfLsh), 1);
	}
	else
	{
		Ospfv2LinkStateHeaderSetExt(&(LSHeader->ospfLsh), 0);
	}
	// BGP-OSPF Patch End

	if (ospf->isQosEnabled)
	{
		Ospfv2LinkStateHeaderSetQOS(&(LSHeader->ospfLsh), 1);
	}
	else
	{
		Ospfv2LinkStateHeaderSetQOS(&(LSHeader->ospfLsh), 0);
	}

	if (ospf->isMospfEnable == TRUE)
	{
		Ospfv2LinkStateHeaderSetMulticast(&(LSHeader->ospfLsh), 1);
	}
	else
	{
		Ospfv2LinkStateHeaderSetMulticast(&(LSHeader->ospfLsh), 0);
	}

	LSHeader->linkStateType = (char) LSType;
	LSHeader->advertisingRouter = ospf->routerID;

	if (oldLSHeader)
	{
		if (oldLSHeader->linkStateSequenceNumber ==	(signed int) OSPFv2_MAX_SEQUENCE_NUMBER)
		{
			// Sequence number reaches the maximum value. We need to
			// flush this instance first before originating any instance.

			Ospfv2FlushLSA((char*) oldLSHeader, areaId);

			//FIXME: Should remove after
			// a) It is no longer contained in any neighbors
			//      retransmission list
			// b) None of the router's neighbors are in state
			//      Exchange/Loading

			Ospfv2RemoveLSAFromLSDB((char*) oldLSHeader, areaId);

			return FALSE;
		}

		LSHeader->linkStateSequenceNumber =	oldLSHeader->linkStateSequenceNumber + 1;
	}
	else
	{
		LSHeader->linkStateSequenceNumber =	(signed int) OSPFv2_INITIAL_SEQUENCE_NUMBER;
	}

	LSHeader->linkStateCheckSum = 0x0;

	return TRUE;
}

//-------------------------------------------------------------------------//
// FUNCTION    : Ospfv2CheckRouterLSABody()
// PURPOSE     : Compare old & new LSA
// ASSUMPTION  : TOS Field remains unaltered
// RETURN VALUE: TRUE  if LSA changed
//-------------------------------------------------------------------------//

bool Sns_Model_OSPFv2::Ospfv2CheckRouterLSABody(Ospfv2RouterLSA* newRouterLSA,Ospfv2RouterLSA* oldRouterLSA)
{
	int i;
	int j;
	bool* sameLinkInfo = NULL;
	int size = oldRouterLSA->numLinks;
	Ospfv2LinkInfo* newLinkList = (Ospfv2LinkInfo*) (newRouterLSA + 1);
	Ospfv2LinkInfo* oldLinkList = (Ospfv2LinkInfo*) (oldRouterLSA + 1);

	if ((newRouterLSA->numLinks != oldRouterLSA->numLinks)
		|| (Ospfv2RouterLSAGetReserved1(newRouterLSA->ospfRouterLsa) !=
		Ospfv2RouterLSAGetReserved1(oldRouterLSA->ospfRouterLsa))
		|| (Ospfv2RouterLSAGetWCMCReceiver(newRouterLSA->ospfRouterLsa)
		!= Ospfv2RouterLSAGetWCMCReceiver(oldRouterLSA->ospfRouterLsa))
		|| (Ospfv2RouterLSAGetVirtLnkEndPt(newRouterLSA->ospfRouterLsa)
		!= Ospfv2RouterLSAGetVirtLnkEndPt(oldRouterLSA->ospfRouterLsa))
		|| (Ospfv2RouterLSAGetASBRouter(newRouterLSA->ospfRouterLsa)
		!= Ospfv2RouterLSAGetASBRouter(oldRouterLSA->ospfRouterLsa))
		|| (Ospfv2RouterLSAGetABRouter(newRouterLSA->ospfRouterLsa)
		!= Ospfv2RouterLSAGetABRouter(oldRouterLSA->ospfRouterLsa)))
	{
		return TRUE;
	}

	// Make all flags False
	sameLinkInfo = (bool*) malloc(sizeof(bool) * size);
	memset(sameLinkInfo, 0, (sizeof(bool) * size));

	for (i = 0; i < newRouterLSA->numLinks; i++)
	{
		int numTosNew = newLinkList->numTOS;

		oldLinkList = (Ospfv2LinkInfo*) (oldRouterLSA + 1);

		for (j = 0; j < oldRouterLSA->numLinks; j++)
		{
			int numTosOld = oldLinkList->numTOS;

			if (sameLinkInfo[j] != TRUE)
			{
				if ((newLinkList->linkID == oldLinkList->linkID)
					&& (newLinkList->type == oldLinkList->type))
				{
					if (newLinkList->linkData == oldLinkList->linkData)
					{
						if (newLinkList->metric == oldLinkList->metric)
						{
							sameLinkInfo[j] = TRUE;
							break;
						}   //metric
					}   //data
				}   //id
			}   //already matched

			oldLinkList = (Ospfv2LinkInfo*)	((QospfPerLinkQoSMetricInfo*)(oldLinkList + 1)	+ numTosOld);
		}   // end of for;

		newLinkList = (Ospfv2LinkInfo*)	((QospfPerLinkQoSMetricInfo*)(newLinkList + 1)	+ numTosNew);
	}   //end of for;

	// check if any link info in old LSA changed
	for (j = 0; j < oldRouterLSA->numLinks; j++)
	{
		if (sameLinkInfo[j] != TRUE)
		{
			xfree(sameLinkInfo);
			return TRUE;
		}
	}

	xfree(sameLinkInfo);
	return FALSE;
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2CheckSummaryLSABody()
// PURPOSE      :Check body of two Summary LSA for any mismatch.
// ASSUMPTION   :None
// RETURN       :TRUE if contents have been changed, FALSE otherwise.
//-------------------------------------------------------------------------//

bool Sns_Model_OSPFv2::Ospfv2CheckSummaryLSABody(Ospfv2LinkStateHeader* newLSHeader,Ospfv2LinkStateHeader* oldLSHeader)
{
	if (memcmp(newLSHeader + 1, oldLSHeader + 1, 8) != 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

// BGP-OSPF Patch Start
//-------------------------------------------------------------------------//
// NAME         :Ospfv2CheckASExternalLSABody()
// PURPOSE      :Check body of two AS External LSA for any mismatch.
// ASSUMPTION   :None
// RETURN       :TRUE if contents have been changed, FALSE otherwise.
//-------------------------------------------------------------------------//

bool Sns_Model_OSPFv2::Ospfv2CheckASExternalLSABody(Ospfv2LinkStateHeader* newLSHeader,Ospfv2LinkStateHeader* oldLSHeader)
{
	if (memcmp(newLSHeader + 1,	oldLSHeader + 1,sizeof(Ospfv2ExternalLinkInfo)) != 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
// BGP-OSPF Patch End

//-------------------------------------------------------------------------//
// FUNCTION    : Ospfv2CheckNetworkLSABody()
// PURPOSE     : Compare old & new LSA
// ASSUMPTION  : TOS Field remains unaltered
// RETURN VALUE: TRUE  if LSA changed
//-------------------------------------------------------------------------//

bool Sns_Model_OSPFv2::Ospfv2CheckNetworkLSABody(Ospfv2NetworkLSA* newNetworkLSA,Ospfv2NetworkLSA* oldNetworkLSA)
{
	int i;
	int j;
	bool* sameLinkInfo = NULL;

	unsigned* newAttachedRtr;
	unsigned* oldAttachedRtr;

	int newNumRtr = (newNetworkLSA->LSHeader.length	- sizeof(Ospfv2NetworkLSA) - 4)	/ (sizeof(unsigned));

	int oldNumRtr = (oldNetworkLSA->LSHeader.length	- sizeof(Ospfv2NetworkLSA) - 4)	/ (sizeof(unsigned));

	// If network mask or attached router has changed
	if ((memcmp(newNetworkLSA + 1, oldNetworkLSA + 1, sizeof(unsigned)) != 0)|| (newNumRtr != oldNumRtr))
	{
		return TRUE;
	}

	// Make all flags False
	sameLinkInfo = (bool*) malloc(sizeof(bool) * oldNumRtr);
	memset(sameLinkInfo, 0, sizeof(bool) * oldNumRtr);

	newAttachedRtr = (unsigned*) (newNetworkLSA + 1) + 1;
	oldAttachedRtr = (unsigned*) (oldNetworkLSA + 1) + 1;

	for (i = 0; i < newNumRtr; i++)
	{
		for (j = 0; j < oldNumRtr; j++)
		{
			if (sameLinkInfo[j] != TRUE)
			{
				if (newAttachedRtr[i] == oldAttachedRtr[j])
				{
					sameLinkInfo[j] = TRUE ;
					break;
				}   //attached router
			}   //already matched ;
		}   // end of for;
	}   //end of for;

	// check if any link info in old LSA changed
	for (j = 0; j < oldNumRtr; j++)
	{
		if (sameLinkInfo[j] != TRUE)
		{
			xfree(sameLinkInfo);
			return TRUE;
		}
	}

	xfree(sameLinkInfo);
	return FALSE;
}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2LSABodyChanged()
// PURPOSE      :Check body of two LSA for any mismatch.
// ASSUMPTION   :None
// RETURN       :TRUE if contents have been changed, FALSE otherwise.
//-------------------------------------------------------------------------//

bool Sns_Model_OSPFv2::Ospfv2LSABodyChanged(Ospfv2LinkStateHeader* newLSHeader,Ospfv2LinkStateHeader* oldLSHeader)
{
	bool retVal = FALSE;

	switch (newLSHeader->linkStateType)
	{
	case OSPFv2_ROUTER:
		{
			retVal = Ospfv2CheckRouterLSABody((Ospfv2RouterLSA*)newLSHeader,(Ospfv2RouterLSA*) oldLSHeader);
			break;
		}

	case OSPFv2_NETWORK:
		{
			retVal = Ospfv2CheckNetworkLSABody((Ospfv2NetworkLSA*) newLSHeader,(Ospfv2NetworkLSA*) oldLSHeader);
			break;
		}

	case OSPFv2_NETWORK_SUMMARY:
	case OSPFv2_ROUTER_SUMMARY:
		{
			retVal = Ospfv2CheckSummaryLSABody(newLSHeader,	oldLSHeader);
			break;
		}

		// BGP-OSPF Patch Start
	case OSPFv2_ROUTER_AS_EXTERNAL:
		{
			retVal = Ospfv2CheckASExternalLSABody(newLSHeader,oldLSHeader);
			break;
		}
		// BGP-OSPF Patch End

	case OSPFv2_GROUP_MEMBERSHIP:
		{
			//return MospfCheckGroupMembershipLSABody((MospfGroupMembershipLSA*)newLSHeader,(MospfGroupMembershipLSA*) oldLSHeader);
		}
	default:
		{
			ERROR_Assert(TRUE, "Not a valid linkStateType\n");
		}
	}

	return retVal;
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2LSAsContentsChanged()
// PURPOSE      :Check contents of two LSA for any mismatch. This is used
//               to dtermine whether we need to recalculate routing table.
// ASSUMPTION   :The body of the LSA is not checked. Always assume they
//               differ.
// RETURN       :TRUE if contents have been changed, FALSE otherwise.
//-------------------------------------------------------------------------//

bool Sns_Model_OSPFv2::Ospfv2LSAsContentsChanged(Ospfv2LinkStateHeader* newLSHeader,Ospfv2LinkStateHeader* oldLSHeader)
{
	// If LSA's option field has changed
	if ((Ospfv2LinkStateHeaderGetExt(newLSHeader->ospfLsh) !=Ospfv2LinkStateHeaderGetExt(oldLSHeader->ospfLsh)) || (Ospfv2LinkStateHeaderGetMulticast(newLSHeader->ospfLsh) !=	Ospfv2LinkStateHeaderGetMulticast(oldLSHeader->ospfLsh))/*|| (Ospfv2LinkStateHeaderGetQOS(newLSHeader->ospfLsh) !=Ospfv2LinkStateHeaderGetQOS(oldLSHeader->ospfLsh))*/)
	{
		return TRUE;
	}
	// Else if one instance has LSA age MaxAge and other does not
	else if (((newLSHeader->linkStateAge ==	(OSPFv2_LSA_MAX_AGE / SECOND))	&& (oldLSHeader->linkStateAge !=(OSPFv2_LSA_MAX_AGE / SECOND)))	|| ((oldLSHeader->linkStateAge ==(OSPFv2_LSA_MAX_AGE / SECOND))	&& (newLSHeader->linkStateAge !=(OSPFv2_LSA_MAX_AGE / SECOND))))
	{
		return TRUE;
	}
	// Else if length field has changed
	else if (newLSHeader->length != oldLSHeader->length)
	{
		return TRUE;
	}
	// The body of the LSA has changed
	else if (Ospfv2LSABodyChanged(newLSHeader, oldLSHeader))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2AssignNewLSAIntoLSOrigin()
// PURPOSE: Assign newLSA address into the LSOrigin which previously holding
//          the old LSA address.
// RETURN: None
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2AssignNewLSAIntoLSOrigin(char* LSA,char* newLSA)
{
	int i;
	Ospfv2RoutingTable* rtTable = &ospf->routingTable;
	Ospfv2RoutingTableRow* rowPtr =	(Ospfv2RoutingTableRow*) BUFFER_GetData(&rtTable->buffer);

	for (i = 0; i < rtTable->numRows; i++)
	{
		if (rowPtr[i].LSOrigin == LSA)
		{
			rowPtr[i].LSOrigin = newLSA;
			break;
		}
	}
}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2InstallLSAInLSDB()
// PURPOSE      :Installing LSAs in the database (RFC 2328, Sec-13.2).
// RETURN       :TRUE if new LSA is not same as old LSA, FALSE otherwise.
//-------------------------------------------------------------------------//

bool Sns_Model_OSPFv2::Ospfv2InstallLSAInLSDB(Ospfv2List* list,char* LSA)
{
	Ospfv2LinkStateHeader* listLSHeader = NULL;
	Ospfv2LinkStateHeader* LSHeader = (Ospfv2LinkStateHeader*) LSA;
	Ospfv2ListItem* item = list->first;
	char* newLSA = NULL;
	bool retVal = FALSE;

	while (item)
	{
		// Get LS Header
		listLSHeader = (Ospfv2LinkStateHeader*) item->data;

		if (listLSHeader->advertisingRouter == LSHeader->advertisingRouter	&& listLSHeader->linkStateID == LSHeader->linkStateID)
		{
			break;
		}

		item = item->next;
	}
	if (LSHeader->linkStateAge >= (OSPFv2_LSA_MAX_AGE / SECOND))
	{
		if (item)
		{
			Ospfv2RemoveFromList(list, item, FALSE);
			retVal = TRUE;
		}
		else
		{
			retVal = FALSE;
		}
	}
	else
	{
		// LSA found in list
		if (item != NULL)
		{
			// Check for difference between old and new instance of LSA
			retVal = Ospfv2LSAsContentsChanged(LSHeader, listLSHeader);
			item->timeStamp = SimClock();

			if (retVal)
			{
				newLSA = Ospfv2CopyLSA(LSA);
				// Update LSA in LSDB.
				item->data = (void*) newLSA;

				if ((LSHeader->linkStateType == OSPFv2_ROUTER) ||(LSHeader->linkStateType == OSPFv2_NETWORK))
				{
					// Assign newLSA address into the LSOrigin.
					Ospfv2AssignNewLSAIntoLSOrigin(	(char*)listLSHeader, newLSA);
				}

				// Free old memory
				xfree(listLSHeader);
			}
			else
			{
				memcpy(listLSHeader, LSHeader, LSHeader->length);
			}
		}
		// LSA not found in list
		else
		{
			newLSA = Ospfv2CopyLSA(LSA);
			Ospfv2InsertToList(list,SimClock(),(void*) newLSA);
			retVal = TRUE;
		}
	}

	return retVal;
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2ScheduleSPFCalculation()
// PURPOSE      :Schedule SPF calculation.
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2ScheduleSPFCalculation()
{
	Sns_Message* newMsg = new Sns_Message;
	clocktype delay;

	if (ospf->SPFTimer > SimClock())
	{
		return;
	}

	delay = (clocktype) (OSPFv2_BROADCAST_JITTER * Get_rand());

	ospf->SPFTimer = SimClock() + delay;

	newMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_InEVENT_OspfScheduleSPF,SNS_MSG_INPUT,NULL,0);
	Scenarios_Data->SNS_Msg_Send(newMsg,Cur_Node_id,(clocktype) delay);
}
//-------------------------------------------------------------------------//
// NAME     :Ospfv2OriginateRouterLSAForThisArea()
// PURPOSE  :Originate router LSA for the specified area. If areaId passed
//          :as OSPFv2_SINGLE_AREA_ID, then consider total domain as
//          :single area, and include all functional interfaces.
// RETURN: None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2OriginateRouterLSAForThisArea(unsigned areaId,bool flush)
{
	int i;
	int count = 0;
	Ospfv2ListItem* tempListItem = NULL;
	Ospfv2Neighbor* tempNeighborInfo = NULL;
	Ospfv2RouterLSA* LSA = NULL;
	Ospfv2LinkStateHeader* oldLSHeader = NULL;
	Ospfv2LinkInfo* linkList = NULL;
	Ospfv2LinkInfo* tempWorkingPointer = NULL;
	Ospfv2Area* thisArea = Ospfv2GetArea(areaId);
	int listSize;
	listSize = 2 * (ospf->neighborCount + numberInterfaces);

	int qosMetricSize;

	if (ospf->isQosEnabled == TRUE)
	{
		//qosMetricSize = listSize * 2 * ospf->numQueueAdvertisedForQos;
	}
	else
	{
		qosMetricSize = 0;
	}

	linkList = (Ospfv2LinkInfo*)malloc(sizeof(Ospfv2LinkInfo) * listSize + sizeof(QospfPerLinkQoSMetricInfo) * qosMetricSize);
	memset(linkList,0,sizeof(Ospfv2LinkInfo) * listSize + sizeof(QospfPerLinkQoSMetricInfo) * qosMetricSize);
	tempWorkingPointer = linkList;
	// Look at each of my interface...
	for (i = 0; i < numberInterfaces; i++)
	{
		if (ospf->iface[i].type == OSPFv2_NON_OSPF_INTERFACE)
		{
			continue;
		}

		// If the attached network does not belong to this area, no links are
		// added to the LSA, and the next interface should be examined.
		if ((areaId != OSPFv2_SINGLE_AREA_ID)	&& (!Ospfv2InterfaceBelongToThisArea(areaId, i)))
		{
			continue;
		}
		// If interface state is down, no link should be added
		if (ospf->iface[i].state == S_Down)
		{
			continue;
		}
		if(ospf->iface[i].address == UNKNOWNADDRESS)
		{
			continue;
		}
		//No Loopbac state in QUALNET.
		if (ospf->isAdvertSelfIntf)
		{
			Ospfv2AddSelfRoute(i, &tempWorkingPointer);

			count++;
		}

		// If interface is a broadcast network.
		if (ospf->iface[i].type == OSPFv2_BROADCAST_INTERFACE)
		{
			// If interface state is waiting add type 3 link (stub network)
			if (ospf->iface[i].state == S_Waiting)
			{
				Ospfv2AddType3Link(i, &tempWorkingPointer);
			}
			else if (((ospf->iface[i].state != S_DR)&& (Ospfv2RouterFullyAdjacentWithDR(i)))|| ((ospf->iface[i].state == S_DR)&& (Ospfv2DRFullyAdjacentWithAnyRouter(i))))
			{
				Ospfv2AddType2Link(i, &tempWorkingPointer);
			}
			else
			{
				Ospfv2AddType3Link(i, &tempWorkingPointer);
			}

			count++;
		}
		// If interface is Point-to-Multipoint
		else if (ospf->iface[i].type ==	OSPFv2_POINT_TO_MULTIPOINT_INTERFACE)
		{
			// Add a single type3 link with linkID set to router's own
			// IP interface address, linkData set to mask 0xFFFFFFFF.
			Ospfv2AddSelfRoute(i, &tempWorkingPointer);
			count++;
			// For each fully adjacent neighbor add an type1 link.
			tempListItem = ospf->iface[i].neighborList->first;
			while (tempListItem)
			{
				tempNeighborInfo = (Ospfv2Neighbor*) tempListItem->data;
				ERROR_Assert(!tempNeighborInfo,"Neighbor not found in the Neighbor list\n");

				// If neighbor is fully adjacent, add a type1 link
				if (tempNeighborInfo->state == S_Full)
				{
					Ospfv2AddType1Link(i, tempNeighborInfo, &tempWorkingPointer);

					count++;
				}

				tempListItem = tempListItem->next;
			}
		}
		// If interface is a point-to-point network.
		else
		{
			tempListItem = ospf->iface[i].neighborList->first;

			if ((!tempListItem) &&(ospf->iface[i].state == S_PointToPoint))
			{
				if (!(ospf->iface[i].isVirtualInterface	/*|| ospf->iface[i].isUnnumbered*/)/*	&& MAC_IsPointToPointNetwork(node, i)*/)
				{
					// We have a subnet address for link.
					Ospfv2AddType3Link(i, &tempWorkingPointer);
				}
				count++;
			}

			// Get all my neighbors information from my neighbor list.
			while (tempListItem)
			{
				tempNeighborInfo = (Ospfv2Neighbor*)tempListItem->data;

				//assert (tempNeighborInfo != NULL);
				ERROR_Assert(!tempNeighborInfo,"Neighbor not found in the Neighbor list\n");

				// If neighbor is fully adjacent, add a type1 link
				if (tempNeighborInfo->state == S_Full)
				{
					Ospfv2AddType1Link(i,tempNeighborInfo,	&tempWorkingPointer);
					count++;
				}

				// In addition, as long as the state of the interface is
				// Point-to-Point (and regardless of the neighboring router
				// state), a Type 3 link (stub network) should be added.
				if (ospf->iface[i].state == S_PointToPoint)
				{
					// Virtual link does't have subnet address
					if (!(ospf->iface[i].isVirtualInterface	/*|| ospf->iface[i].isUnnumbered*/)	/*&& MAC_IsPointToPointNetwork(node, i)*/)
					{
						// We have a subnet address for link.
						Ospfv2AddType3Link(i, &tempWorkingPointer);
					}
					else
					{
						// This is for wireless interface
						Ospfv2AddHostRoute(i, tempNeighborInfo, &tempWorkingPointer);
					}
					//Ospfv2AddHostRoute(
					//        node, i, tempNeighborInfo, &tempWorkingPointer);
					count++;
				}

				tempListItem = tempListItem->next;
			}
		}
	}
	ERROR_Assert(count > listSize, "Calculation of listSize is wrong\n");

	// Get old instance, if any..
	oldLSHeader = Ospfv2LookupLSAList(thisArea->routerLSAList,ospf->routerID,ospf->routerID);

	// Start constructing the Router LSA.
	LSA = (Ospfv2RouterLSA*)malloc(sizeof(Ospfv2RouterLSA)	+ (sizeof(Ospfv2LinkInfo) * count)	+ (sizeof(QospfPerLinkQoSMetricInfo)* 2 * ospf->numQueueAdvertisedForQos * count));

	if (!Ospfv2CreateLSHeader(areaId, OSPFv2_ROUTER, &LSA->LSHeader, oldLSHeader))
	{
		xfree(linkList);
		xfree(LSA);
		Ospfv2ScheduleRouterLSA(areaId, FALSE);
		return;
	}

	if (flush)
	{
		LSA->LSHeader.linkStateAge = (OSPFv2_LSA_MAX_AGE / SECOND);
	}

	LSA->LSHeader.linkStateID = ospf->routerID;

	LSA->LSHeader.length = (short) (sizeof(Ospfv2RouterLSA)+ (sizeof(Ospfv2LinkInfo) * count)+ (sizeof(QospfPerLinkQoSMetricInfo)* 2 * ospf->numQueueAdvertisedForQos * count));

	Ospfv2RouterLSASetReserved1(&(LSA->ospfRouterLsa), 0x0);
	Ospfv2RouterLSASetWCMCReceiver(&(LSA->ospfRouterLsa), 0);

	// M-OSPF Patch Start
	// modify this parameter for Inter area multicast forwarder
	if (ospf->isMospfEnable == TRUE)
	{
		//MospfData* mospf;
		//mospf = (MospfData*)ospf->multicastRoutingProtocol;

		//if (mospf->interAreaMulticastFwder == TRUE)
		//{
		//	Ospfv2RouterLSASetWCMCReceiver(&(LSA->ospfRouterLsa), 1);
		//}
	}
	// M-OSPF Patch End

	Ospfv2RouterLSASetVirtLnkEndPt(&(LSA->ospfRouterLsa), 0);
	Ospfv2RouterLSASetASBRouter(&(LSA->ospfRouterLsa), 0);

	// BGP-OSPF Patch Start
	if (ospf->asBoundaryRouter == TRUE)
	{
		Ospfv2RouterLSASetASBRouter(&(LSA->ospfRouterLsa), 1);
	}
	// BGP-OSPF Patch End

	if (ospf->areaBorderRouter == TRUE)
	{
		Ospfv2RouterLSASetABRouter(&(LSA->ospfRouterLsa), 1);
	}
	else
	{
		Ospfv2RouterLSASetABRouter(&(LSA->ospfRouterLsa), 0);
	}

	LSA->numLinks = (short) count;

	// Copy my link information into the LSA.
	memcpy(LSA + 1,	linkList,((sizeof(Ospfv2LinkInfo) * count)+ (sizeof(QospfPerLinkQoSMetricInfo)* 2 * ospf->numQueueAdvertisedForQos * count)));

	// Note LSA Origination time
	thisArea->routerLSAOriginateTime = SimClock();
	thisArea->routerLSTimer = FALSE;
	if (Ospfv2InstallLSAInLSDB(thisArea->routerLSAList, (char*) LSA))
	{
		// I need to recalculate shortest path since my LSDB changed
		Ospfv2ScheduleSPFCalculation();
	}

	// Flood LSA
	Ospfv2FloodLSA(ANY_INTERFACE,(char*) LSA,ANY_DEST,areaId);
	ospf->stats.numRtrLSAOriginate++;
	xfree(linkList);
	xfree(LSA);
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2ScheduleNetworkLSA()
// PURPOSE      :Schedule network LSA origination
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2ScheduleNetworkLSA(int interfaceIndex, bool flush)
{
	
	clocktype delay;
	char* msgInfo = NULL;
	Ospfv2LinkStateType lsType;
	Ospfv2LinkStateHeader* oldLSHeader = NULL;
	bool haveAdjNbr = FALSE;
	Ospfv2Interface* thisInterface = &ospf->iface[interfaceIndex];
	Ospfv2Area* thisArea =Ospfv2GetArea(thisInterface->areaId);

	ERROR_Assert(!thisArea, "Area not fount\n");

	// Get old instance, if any..
	oldLSHeader = Ospfv2LookupLSAList(thisArea->networkLSAList,ospf->routerID,ospf->iface[interfaceIndex].address);

	haveAdjNbr = Ospfv2DRFullyAdjacentWithAnyRouter(interfaceIndex);

	if (haveAdjNbr && !flush)
	{
		// Originate LSA
	}
	else if (oldLSHeader && (!haveAdjNbr || flush))
	{
		// Flush LSA
		flush = TRUE;
	}
	else
	{
		// Do nothing
		return;
	}
	if (thisInterface->networkLSTimer&& !flush)
	{
		return;
	}
	// We need to cancel previous timer if any
	thisInterface->networkLSTimerSeqNumber++;

	if ((thisInterface->networkLSAOriginateTime == 0)|| ((SimClock() - thisInterface->networkLSAOriginateTime) >=OSPFv2_MIN_LS_INTERVAL))
	{
		delay = (clocktype)	(Get_rand() * OSPFv2_BROADCAST_JITTER);
	}
	else
	{
		delay = (clocktype) (OSPFv2_MIN_LS_INTERVAL	- (SimClock()- thisInterface->networkLSAOriginateTime));
	}
	thisInterface->networkLSTimer = TRUE;
	Sns_Message* newMsg = new Sns_Message;
	newMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_InEVENT_OspfScheduleLSDB,SNS_MSG_INPUT,NULL,0);
	lsType = OSPFv2_NETWORK;
	msgInfo=(char*)malloc(sizeof(Ospfv2LinkStateType)+sizeof(int)+2*sizeof(bool));
	char* index=msgInfo;
	memcpy(index, &lsType, sizeof(Ospfv2LinkStateType));
	index += sizeof(Ospfv2LinkStateType);
	memcpy(index, &interfaceIndex, sizeof(int));
	index += sizeof(int);
	memcpy(index, &flush, sizeof(bool));
	index += sizeof(bool);
	memcpy(index, &thisInterface->networkLSTimerSeqNumber, sizeof(bool));
	newMsg->SNS_Msg_AddInfo(msgInfo,sizeof(Ospfv2LinkStateType)+sizeof(int)+2*sizeof(bool));
	Scenarios_Data->SNS_Msg_Send(newMsg, Cur_Node_id,(clocktype) delay);

	////****!!!!
	xfree( msgInfo ) ;
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2OriginateNetworkLSA
// PURPOSE: Originate network LSAs.
// RETURN: None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2OriginateNetworkLSA(int interfaceIndex,bool flush)
{
	int count = 0;
	Ospfv2ListItem* tempListItem = NULL;
	Ospfv2Neighbor* tempNeighborInfo = NULL;
	Ospfv2NetworkLSA* LSA = NULL;
	Ospfv2LinkStateHeader* oldLSHeader = NULL;
	unsigned* linkList = NULL;
	Ospfv2Area* thisArea =
	Ospfv2GetArea(ospf->iface[interfaceIndex].areaId);
	int numNbr = ospf->iface[interfaceIndex].neighborList->size;
	linkList = (unsigned*)malloc(sizeof(unsigned) * (numNbr + 1)+ sizeof(unsigned));

	// Include network mask
	// Include the designated router also.
	linkList[count++] =	ospf->iface[interfaceIndex].subnetMask;
	// Include the designated router also.
	linkList[count++] = ospf->routerID;
	tempListItem = ospf->iface[interfaceIndex].neighborList->first;

	// Get all my neighbors information from my neighbor list.
	while (tempListItem)
	{
		tempNeighborInfo = (Ospfv2Neighbor*) tempListItem->data;

		ERROR_Assert(!tempNeighborInfo,"Neighbor not present into the Neighbor list\n");

		// List those router that area fully adjacent to DR
		if (tempNeighborInfo->state == S_Full)
		{
			linkList[count++] = tempNeighborInfo->neighborID;
		}

		tempListItem = tempListItem->next;
	}

	// Get old instance, if any..
	oldLSHeader = Ospfv2LookupLSAList(thisArea->networkLSAList,ospf->routerID,ospf->iface[interfaceIndex].address);

	// Start constructing the LSA
	LSA = (Ospfv2NetworkLSA*)malloc(sizeof(Ospfv2NetworkLSA)+ (sizeof(unsigned) *  count));

	if (!Ospfv2CreateLSHeader(ospf->iface[interfaceIndex].areaId,OSPFv2_NETWORK,&LSA->LSHeader,oldLSHeader))
	{
		xfree(linkList);
		xfree(LSA);
		Ospfv2ScheduleNetworkLSA(interfaceIndex, FALSE);
		return;
	}

	if (flush)
	{
		LSA->LSHeader.linkStateAge = (OSPFv2_LSA_MAX_AGE / SECOND);
	}

	LSA->LSHeader.length = (short) (sizeof(Ospfv2NetworkLSA)
		+ (sizeof(unsigned) * count));

	// LSA->LSHeader.linkStateID =
	LSA->LSHeader.linkStateID = ospf->iface[interfaceIndex].address;

	// Copy my link information to the LSA.
	memcpy(LSA + 1,
		linkList,
		sizeof(unsigned) * count);

	// Note LSA Origination time
	ospf->iface[interfaceIndex].networkLSAOriginateTime =SimClock();

	ospf->iface[interfaceIndex].networkLSTimer = FALSE;
	if (Ospfv2InstallLSAInLSDB(thisArea->networkLSAList, (char*) LSA))
	{
		// I need to recalculate shortest path since my LSDB changed
		Ospfv2ScheduleSPFCalculation();
	}
	// Flood LSA
	Ospfv2FloodLSA(ANY_INTERFACE,(char*) LSA,ANY_DEST,thisArea->areaID);
	ospf->stats.numNetLSAOriginate++;

	xfree(linkList);
	xfree(LSA);
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2GetAddrRangeInfo()
// PURPOSE      :Get this address range information
// ASSUMPTION   :None
// RETURN VALUE :Ospfv2AreaAddressRange*
//-------------------------------------------------------------------------//

Sns_Model_OSPFv2::Ospfv2AreaAddressRange* Sns_Model_OSPFv2::Ospfv2GetAddrRangeInfo(unsigned areaId,unsigned destAddr)
{
	Ospfv2AreaAddressRange* addrRangeInfo = NULL;
	Ospfv2Area* area = Ospfv2GetArea(areaId);
	Ospfv2ListItem* listItem = area->areaAddrRange->first;

	while (listItem)
	{
		addrRangeInfo = (Ospfv2AreaAddressRange*) listItem->data;

		if ((addrRangeInfo->address & addrRangeInfo->mask) ==
			(destAddr & addrRangeInfo->mask))
		{
			return addrRangeInfo;
		}

		listItem = listItem->next;
	}

	return NULL;
}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2GetAddrRangeInfoForAllArea()
// PURPOSE      :Get this address range information
// ASSUMPTION   :None
// RETURN VALUE :Ospfv2AreaAddressRange*
//-------------------------------------------------------------------------//

Sns_Model_OSPFv2::Ospfv2AreaAddressRange* Sns_Model_OSPFv2::Ospfv2GetAddrRangeInfoForAllArea(unsigned destAddr)
{
	Ospfv2Area* area = NULL;
	Ospfv2AreaAddressRange* addrRangeInfo = NULL;
	Ospfv2ListItem* listItem = ospf->area->first;

	while (listItem)
	{
		area = (Ospfv2Area*) listItem->data;
		addrRangeInfo = Ospfv2GetAddrRangeInfo(area->areaID,destAddr);

		if (addrRangeInfo != NULL)
		{
			return addrRangeInfo;
		}

		listItem = listItem->next;
	}

	return NULL;
}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2CheckForSummaryLSAValidity()
//
// PURPOSE      :Check the validity of summary information. This function is
//               used to check wheather this node's routing table has valid
//               entry for the destination we want to advertise or had
//               advertised at earlier time. The areaId is the id of
//               associated area the summary information will be or had been
//               advertised.
//
// ASSUMPTION   :Default destination is always valid advertisement.
//
// RETURN VALUE :1 if we find a perfect match in routing table.
//               -1 if we find an entry aggregated within this range.
//               0 if we didn't find any matching entry.
//-------------------------------------------------------------------------//
int Sns_Model_OSPFv2::Ospfv2CheckForSummaryLSAValidity(unsigned destAddr,unsigned addrMask,Ospfv2DestType destType,unsigned int areaId,Ospfv2RoutingTableRow** matchPtr)
{
	int i;
	Ospfv2RoutingTable* rtTable = &ospf->routingTable;
	Ospfv2RoutingTableRow* rowPtr =	(Ospfv2RoutingTableRow*) BUFFER_GetData(&rtTable->buffer);
	Ospfv2AreaAddressRange* addrInfo = NULL;
	*matchPtr = NULL;

	// XXX: Assume information is valid for default destination.
	if (destAddr == OSPFv2_DEFAULT_DESTINATION	&& addrMask == OSPFv2_DEFAULT_MASK)
	{
		return 1;
	}

	for (i = 0; i < rtTable->numRows; i++)
	{
		// Do we have a perfect match?
		if ((rowPtr[i].destAddr & rowPtr[i].addrMask)
			== (destAddr & addrMask)
			&& addrMask == rowPtr[i].addrMask
			&& Ospfv2CompDestType(rowPtr[i].destType, destType)
			&& rowPtr[i].areaId != areaId
			&& rowPtr[i].flag != OSPFv2_ROUTE_INVALID)
		{
			*matchPtr = &rowPtr[i];
			return 1;
		}
	}

	// We didn't get a perfect match. So it might be an aggregated
	// advertisement which must be one of our configured area address
	// range. So search for an intra area entry contained within this range.
	for (i = 0; i < rtTable->numRows; i++)
	{
		if ((rowPtr[i].destAddr & addrMask) == (destAddr & addrMask)
			&& addrMask < rowPtr[i].addrMask
			&& rowPtr[i].pathType == OSPFv2_INTRA_AREA
			&& Ospfv2CompDestType(rowPtr[i].destType, destType)
			&& rowPtr[i].areaId != areaId
			&& rowPtr[i].flag != OSPFv2_ROUTE_INVALID)
		{
			// FIXME: Not sure wheather we require assert here
			addrInfo = Ospfv2GetAddrRangeInfoForAllArea(destAddr);

			ERROR_Assert(!addrInfo	|| addrInfo->address != destAddr /*&& addrInfo->mask == addrMask*/,"Something wrong with route suppression\n");

			*matchPtr = &rowPtr[i];
			return -1;
		}
	}

	return 0;
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2GetMaxMetricForThisRange()
// PURPOSE      :Get largest cost of any of the component networks within
//               the specified address range.
// ASSUMPTION   :None
// RETURN VALUE :Maximum cost.
//-------------------------------------------------------------------------//

Int32 Sns_Model_OSPFv2::Ospfv2GetMaxMetricForThisRange(Ospfv2RoutingTable* rtTable,Ospfv2AreaAddressRange* addrInfo)
{
	Ospfv2RoutingTableRow* rowPtr =	(Ospfv2RoutingTableRow*) BUFFER_GetData(&rtTable->buffer);
	int i;
	Int32 maxMetric = 0;
	Ospfv2Area* thisArea = (Ospfv2Area*) addrInfo->area;

	for (i = 0; i < rtTable->numRows; i++)
	{
		if (((addrInfo->address & addrInfo->mask) ==
			(rowPtr[i].destAddr & addrInfo->mask))
			&& (rowPtr[i].areaId == thisArea->areaID)
			&& (rowPtr[i].pathType == OSPFv2_INTRA_AREA)
			&& (rowPtr[i].metric > maxMetric)
			&& (rowPtr[i].flag != OSPFv2_ROUTE_INVALID))
		{
			maxMetric = rowPtr[i].metric;
		}
	}

	return maxMetric;
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2GetLSAListItem()
// PURPOSE      :Search for the LSA in list and get the item.
// ASSUMPTION   :None
// RETURN VALUE :Ospfv2ListItem*
//-------------------------------------------------------------------------//

Sns_Model_OSPFv2::Ospfv2ListItem* Sns_Model_OSPFv2::Ospfv2GetLSAListItem(Ospfv2List* tlist,unsigned advertisingRouter,unsigned linkStateID)
{
	Ospfv2LinkStateHeader* listLSHeader = NULL;

	Ospfv2ListItem* item = tlist->first;

	while (item)
	{
		// Get LS Header
		listLSHeader = (Ospfv2LinkStateHeader*) item->data;

		if (listLSHeader->advertisingRouter == advertisingRouter&& listLSHeader->linkStateID == linkStateID)
		{
			return item;
		}

		item = item->next;
	}
	return NULL;
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2ScheduleSummaryLSA()
// PURPOSE      :Schedule summary LSA origination
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2ScheduleSummaryLSA(unsigned destAddr,unsigned addrMask,Ospfv2DestType destType,unsigned int areaId,bool flush)
{
	Sns_Message* newMsg = new Sns_Message;
	
	Ospfv2LinkStateType lsType;

	Ospfv2Area* thisArea = Ospfv2GetArea(areaId);

	ERROR_Assert(!thisArea, "Area doesn't exist\n");
	newMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_InEVENT_OspfScheduleLSDB,SNS_MSG_INPUT,NULL,0);
	char* msgInfo = (char*)malloc(sizeof(Ospfv2LinkStateType) + sizeof(unsigned int)+ sizeof(bool) + sizeof(unsigned)+ sizeof(unsigned) + sizeof(Ospfv2DestType));
	if (destType == OSPFv2_DESTINATION_NETWORK)
	{
		lsType = OSPFv2_NETWORK_SUMMARY;
	}
	else
	{
		lsType = OSPFv2_ROUTER_SUMMARY;
	}
	char* index=msgInfo;
	memcpy(index, &lsType, sizeof(Ospfv2LinkStateType));
	index += sizeof(Ospfv2LinkStateType);
	memcpy(index, &areaId, sizeof(unsigned int));
	index += sizeof(unsigned int);
	memcpy(index, &flush, sizeof(bool));
	index += sizeof(bool);
	memcpy(index, &destAddr, sizeof(unsigned));
	index += sizeof(unsigned);
	memcpy(index, &addrMask, sizeof(unsigned));
	index += sizeof(unsigned);
	memcpy(index, &destType, sizeof(Ospfv2DestType));
	newMsg->SNS_Msg_AddInfo(msgInfo,sizeof(Ospfv2LinkStateType) + sizeof(unsigned int)+ sizeof(bool) + sizeof(unsigned)+ sizeof(unsigned) + sizeof(Ospfv2DestType));
	Scenarios_Data->SNS_Msg_Send(newMsg,Cur_Node_id,(clocktype) OSPFv2_MIN_LS_INTERVAL);

	///***!!!!
	xfree( msgInfo ) ;
}

//-------------------------------------------------------------------------//
// NAME     :Ospfv2OriginateSummaryLSA()
// PURPOSE  :Originate summary LSA for the specified route.
// RETURN   :None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2OriginateSummaryLSA(Ospfv2RoutingTableRow* advRt,Ospfv2Area* thisArea,bool flush)
{
	Ospfv2LinkStateHeader* oldLSHeader = NULL;
	Ospfv2ListItem* LSAItem = NULL;
	int index = 0;
	char metric1;
	char metric2;
	char metric3;
	Int32 metric;
	bool retVal = FALSE;

	char* LSA = (char*) malloc(sizeof(Ospfv2LinkStateHeader)+ sizeof(unsigned) + sizeof(int));

	Ospfv2LinkStateHeader* LSHeader = (Ospfv2LinkStateHeader*) LSA;

	// Get metric
	metric = advRt->metric;

	metric1 = (char) (metric >> 16);
	metric2 = (char) (metric >> 8);
	metric3 = (char) metric;

	if (advRt->destType == OSPFv2_DESTINATION_NETWORK)
	{
		// Get old instance, if any..
		LSAItem = Ospfv2GetLSAListItem(thisArea->networkSummaryLSAList,ospf->routerID, advRt->destAddr);

		if (LSAItem)
		{
			oldLSHeader = (Ospfv2LinkStateHeader*) LSAItem->data;
		}

		retVal = Ospfv2CreateLSHeader(thisArea->areaID,OSPFv2_NETWORK_SUMMARY,LSHeader,oldLSHeader);

		index += sizeof(Ospfv2LinkStateHeader);

		memcpy(&LSA[index], &advRt->addrMask, sizeof(unsigned));
	}
	else if (advRt->destType == OSPFv2_DESTINATION_ASBR
		|| advRt->destType == OSPFv2_DESTINATION_ABR_ASBR)
	{
		// Get old instance, if any..
		LSAItem = Ospfv2GetLSAListItem(thisArea->routerSummaryLSAList,ospf->routerID, advRt->destAddr);

		if (LSAItem)
		{
			oldLSHeader = (Ospfv2LinkStateHeader*) LSAItem->data;
		}

		retVal = Ospfv2CreateLSHeader(thisArea->areaID,OSPFv2_ROUTER_SUMMARY,LSHeader,oldLSHeader);

		index += sizeof(Ospfv2LinkStateHeader);

		memset(&LSA[index], 0, sizeof(unsigned));
	}
	else
	{
		// Shouldn't be here
		ERROR_Assert(FALSE, "Destination type is not a Network or ASBR,"
			" so it is not possible to create summary LSA\n");

	}

	if ((LSAItem && (SimClock() - LSAItem->timeStamp< OSPFv2_MIN_LS_INTERVAL))
		|| (!retVal))
	{
		xfree(LSA);
		Ospfv2ScheduleSummaryLSA(advRt->destAddr, advRt->addrMask, advRt->destType,thisArea->areaID, FALSE);
		return;
	}

	index += sizeof(unsigned);

	LSA[index++] = 0;

	// Set metric
	LSA[index++] = metric1;
	LSA[index++] = metric2;
	LSA[index++] = metric3;

	LSHeader->length = sizeof(Ospfv2LinkStateHeader)
		+ sizeof(unsigned) + sizeof(int);

	LSHeader->linkStateID = advRt->destAddr;

	// M-OSPF Patch Start
	if (ospf->isMospfEnable)
	{
		//MospfData* mospf = NULL;

		//mospf = (MospfData*) ospf->multicastRoutingProtocol;

		//if (!mospf->interAreaMulticastFwder)
		//{
		//	Ospfv2LinkStateHeaderSetMulticast(&(LSHeader->ospfLsh), 0);
		//}
	}
	// M-OSPF Patch End

	if (advRt->flag == OSPFv2_ROUTE_INVALID)
	{
		LSHeader->linkStateAge = (OSPFv2_LSA_MAX_AGE / SECOND);
	}

	ERROR_Assert(index == LSHeader->length,
		"Wrong entry into the LSHeader->linkStateAge field.");

	if (advRt->destType == OSPFv2_DESTINATION_NETWORK)
	{
		if (Ospfv2InstallLSAInLSDB(thisArea->networkSummaryLSAList,LSA))
		{
			// I need to recalculate shortest path since my LSDB changed
			Ospfv2ScheduleSPFCalculation();
		}
	}
	else
	{
		if (Ospfv2InstallLSAInLSDB(thisArea->routerSummaryLSAList,LSA))
		{
			// I need to recalculate shortest path since my LSDB changed
			//Ospfv2FindShortestPath(node);
			Ospfv2ScheduleSPFCalculation();
		}
	}

	// Flood LSA
	Ospfv2FloodLSA(ANY_INTERFACE,LSA,ANY_DEST,thisArea->areaID);

	ospf->stats.numSumLSAOriginate++;

	xfree(LSA);
}


// BGP-OSPF Patch Start
//-------------------------------------------------------------------------//
// NAME         :Ospfv2ScheduleASExternalLSA()
// PURPOSE      :Schedule AS external LSA origination
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2ScheduleASExternalLSA(unsigned destAddress,unsigned destAddressMask,unsigned nextHopAddress,int external2Cost,bool flush)

{
	Ospfv2LinkStateType lsType;
	Sns_Message* newMsg = new Sns_Message;
	newMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_InEVENT_OspfScheduleLSDB,SNS_MSG_INPUT,NULL,0);
	char* msgInfo = (char*)malloc(sizeof(Ospfv2LinkStateType) + (sizeof(unsigned) * 3)	+ sizeof(int) + sizeof(bool));
	char* index=msgInfo;
	lsType = OSPFv2_ROUTER_AS_EXTERNAL;
	memcpy(index, &lsType, sizeof(Ospfv2LinkStateType));
	index += sizeof(Ospfv2LinkStateType);
	memcpy(index, &destAddress, sizeof(unsigned));
	index += sizeof(unsigned);
	memcpy(index, &destAddressMask, sizeof(unsigned));
	index += sizeof(unsigned);
	memcpy(index, &nextHopAddress, sizeof(unsigned));
	index += sizeof(unsigned);
	memcpy(index, &external2Cost, sizeof(int));
	index += sizeof(int);
	memcpy(index, &flush, sizeof(bool));
	newMsg->SNS_Msg_AddInfo(msgInfo,sizeof(Ospfv2LinkStateType) + (sizeof(unsigned) * 3)	+ sizeof(int) + sizeof(bool));
	Scenarios_Data->SNS_Msg_Send(newMsg,Cur_Node_id, (clocktype) OSPFv2_MIN_LS_INTERVAL);

	////****!!!!
	xfree( msgInfo ) ;

}
// BGP-OSPF Patch End

//-------------------------------------------------------------------------//
// NAME         :Ospfv2FloodThroughAS
// PURPOSE      :Flood LSA throughout the autonomous system.
// ASSUMPTION   :None.
// RETURN VALUE :TRUE if LSA flooded back to receiving interface,
//               FALSE otherwise.
//-------------------------------------------------------------------------//

bool Sns_Model_OSPFv2::Ospfv2FloodThroughAS(int interfaceIndex,char* LSA,unsigned srcAddr)
{
	Ospfv2Area* thisArea = NULL;
	Ospfv2ListItem* listItem = NULL;
	bool retVal = FALSE;

	listItem = ospf->area->first;

	while (listItem)
	{
		thisArea = (Ospfv2Area*) listItem->data;

		// If this is not a Stub area, flood lsa through this area
		if (thisArea->transitCapability)
		{
			if (Ospfv2FloodLSA(interfaceIndex,LSA,srcAddr,thisArea->areaID))
			{
				retVal = TRUE;
			}
		}

		listItem = listItem->next;
	}

	return retVal;
}

//-------------------------------------------------------------------------//
// NAME     :Ospfv2OriginateASexternalLSA()
// PURPOSE  :Originate AS external LSA for the specified external route.
// RETURN   :None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2OriginateASExternalLSA(unsigned destAddress,unsigned destAddressMask,unsigned nextHopAddress,int external2Cost,bool flush)
{
	Ospfv2LinkStateHeader* oldLSHeader = NULL;
	bool retVal;

	char* LSA = (char*) malloc(sizeof(Ospfv2LinkStateHeader)+ sizeof(Ospfv2ExternalLinkInfo));

	Ospfv2LinkStateHeader* LSHeader = (Ospfv2LinkStateHeader*) LSA;

	Ospfv2ExternalLinkInfo* ospfv2ExternalLinkInfo =(Ospfv2ExternalLinkInfo*) (LSA + sizeof(Ospfv2LinkStateHeader));

	memset(LSA, 0, (sizeof(Ospfv2LinkStateHeader)+ sizeof(Ospfv2ExternalLinkInfo)));

	ERROR_Assert(!ospf->asBoundaryRouter, "Router is not an ASBR.\n");

	// Get old instance, if any..
	oldLSHeader = Ospfv2LookupLSAList(ospf->asExternalLSAList,ospf->routerID,destAddress);

	if (nextHopAddress == (unsigned) (NETWORK_UNREACHABLE))
	{
		ERROR_Assert(oldLSHeader, "This situation should not occur.\n");

		Ospfv2FlushLSA((char*) oldLSHeader, OSPFv2_INVALID_AREA_ID);

		//FIXME: Should remove after
		// a) It is no longer contained in any neighbors
		//      retransmission list
		// b) None of the router's neighbors are in state
		//      Exchange/Loading
		Ospfv2RemoveLSAFromLSDB((char*) oldLSHeader, OSPFv2_INVALID_AREA_ID);

		return;
	}

	retVal = Ospfv2CreateLSHeader(OSPFv2_INVALID_AREA_ID,OSPFv2_ROUTER_AS_EXTERNAL,LSHeader,oldLSHeader);
	if (!retVal)
	{
		xfree(LSA);
		Ospfv2ScheduleASExternalLSA(destAddress,destAddressMask,nextHopAddress,external2Cost,FALSE);
		return;
	}
	ospfv2ExternalLinkInfo->networkMask = destAddressMask;
	Ospfv2ExternalLinkSetEBit(&(ospfv2ExternalLinkInfo->ospfMetric), 1);
	Ospfv2ExternalLinkSetMetric(&(ospfv2ExternalLinkInfo->ospfMetric),external2Cost);
	ospfv2ExternalLinkInfo->forwardingAddress = 0;

	LSHeader->length = sizeof(Ospfv2LinkStateHeader)+ sizeof(Ospfv2ExternalLinkInfo);
	LSHeader->linkStateID = destAddress;
	Ospfv2LinkStateHeaderSetExt(&(LSHeader->ospfLsh), 1);

	if (Ospfv2InstallLSAInLSDB(ospf->asExternalLSAList,LSA))
	{
		// I need to recalculate shortest path since my LSDB changed
		Ospfv2ScheduleSPFCalculation();
	}
	// Flood LSA
	Ospfv2FloodThroughAS(ANY_INTERFACE, LSA, ANY_DEST);

	xfree(LSA);
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2FillNeighborField
// PURPOSE: Update Hello packet neighbor list for this node
// RETURN: Number of eligible neighbor
//-------------------------------------------------------------------------//

int Sns_Model_OSPFv2::Ospfv2FillNeighborField(unsigned** nbrList,int interfaceIndex)
{
	Ospfv2ListItem* tmpListItem = NULL;
	Ospfv2Neighbor* tmpNbInfo = NULL;
	Ospfv2Interface* thisIntf = NULL;
	int count = 0;
	int neighborCount;

	thisIntf = &ospf->iface[interfaceIndex];
	neighborCount = thisIntf->neighborList->size;

	if (neighborCount <= 0)
	{
		*nbrList = NULL;
		return 0;
	}

	*nbrList = (unsigned*) malloc(sizeof(unsigned)* neighborCount);

	tmpListItem = thisIntf->neighborList->first;

	// Get a list of all my neighbors from this interface.
	while (tmpListItem)
	{
		tmpNbInfo = (Ospfv2Neighbor*) tmpListItem->data;

		// Consider only neighbors from which Hello packet
		// have been seen recently

		if (tmpNbInfo->state >= S_Init)
		{
			// Add neighbor to the list.
			(*nbrList)[count] = tmpNbInfo->neighborID;

			count++;
		}
		tmpListItem = tmpListItem->next;
	}
	return count;
}

//-------------------------------------------------------------------------//
//                            COMMON HEADER                                //
//-------------------------------------------------------------------------//

//-------------------------------------------------------------------------//
// NAME: Ospfv2CalcCommonHeaderCheckSum
// PURPOSE: Calculate checksum for packet.
// RETURN: 0 for now.
//-------------------------------------------------------------------------//
short int Sns_Model_OSPFv2::Ospfv2CalcCommonHeaderCheckSum(Ospfv2CommonHeader* cmnHdr)
{
	return 0;
}
//-------------------------------------------------------------------------//
// NAME: Ospfv2CreateCommonHeader
// PURPOSE: Create common OSPF packet header for all packets.
// RETURN: None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2CreateCommonHeader(Ospfv2CommonHeader* commonHdr,Ospfv2PacketType pktType)
{
	commonHdr->version = OSPFv2_CURRENT_VERSION;
	commonHdr->packetType = (unsigned char) pktType;
	commonHdr->routerID = ospf->routerID;
	commonHdr->areaID = 0x0;
	commonHdr->checkSum = Ospfv2CalcCommonHeaderCheckSum(commonHdr);

	// Authentication not simulated.
	commonHdr->authenticationType = 0x0;
	commonHdr->authenticationData[0] = 0;
}


//-------------------------------------------------------------------------//
// NAME         :Ospfv2SendHelloPacket
// PURPOSE      :Creating new Hello packet and send it to all neighbors.
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2SendHelloPacket(Int32 interfaceIndex)
{
	clocktype delay;
	int numNeighbor;
	Int32 i = interfaceIndex;
	unsigned* neighborList = NULL;

	// Send Hello packet out to each interface.

	if (ospf->iface[i].type == OSPFv2_NON_OSPF_INTERFACE)
	{
		return;
	}

	// If interface state is down, no hello should be sent
	if (ospf->iface[i].state == S_Down)
	{
		return;
	}
	if(ospf->iface[i].address == UNKNOWNADDRESS)
	{
		return;
	}
	Ospfv2Area* thisArea = Ospfv2GetArea(ospf->iface[i].areaId);
	ERROR_Assert(!thisArea, "Area not identified\n");

	// Get all my neighbors that I've learned.
	numNeighbor = Ospfv2FillNeighborField(&neighborList,i);
	// Now, create the Hello packet.
	Sns_Message* helloMsg = new Sns_Message;
	char* helloPayLoad=(char*)malloc(sizeof(Ospfv2HelloPacket)+ (sizeof(unsigned) * numNeighbor));
	Ospfv2HelloPacket* helloPacket = (Ospfv2HelloPacket*)helloPayLoad;
	NetworkToMACInfo* info=new NetworkToMACInfo;
	// Options fields not used.
	helloPacket->options = 0x0;

	// Fill in the header fields for the Hello packet.
	Ospfv2CreateCommonHeader(&helloPacket->commonHeader,OSPFv2_HELLO);

	// Keep track of the Hello packet length so my neighbors can
	// determine how many neighbors are in the Hello packet.
	helloPacket->commonHeader.packetLength =(short int) (sizeof(Ospfv2HelloPacket)+ (sizeof(unsigned) *  numNeighbor));

	// Add our neighbor list at the end of the Hello packet.
	if (numNeighbor > 0)
	{
		memcpy(helloPacket + 1,	neighborList,sizeof(unsigned) * numNeighbor);
	}
	if (OSPFv2_DEBUG_HELLOErr)
	{
		Ospfv2PrintHelloPacket(helloPacket,interfaceIndex);
	}
	// Fill area ID field of header
	helloPacket->commonHeader.areaID = ospf->iface[i].areaId;

	// Set E-bit if not a stub area
	if (thisArea->transitCapability == TRUE)
	{
		helloPacket->options = OSPFv2_OPTION_EXTERNAL;
	}

	helloPacket->helloInterval = (short int)(ospf->iface[i].helloInterval / SECOND);

	helloPacket->rtrPri =(unsigned char) ospf->iface[i].routerPriority;
	helloPacket->routerDeadInterval =(int) (ospf->iface[i].routerDeadInterval / SECOND);

	// Designated router and backup Designated router is identified
	// by it's IP interface address on the network

	helloPacket->designatedRouter =ospf->iface[i].designatedRouterIPAddress;
	helloPacket->backupDesignatedRouter =ospf->iface[i].backupDesignatedRouterIPAddress;

	if(ospf->iface[i].isVirtualInterface)
	{
		helloPacket->networkMask = 0;
	}
	else
	{
		helloPacket->networkMask = ospf->iface[i].subnetMask;
	}

	// Used to jitter the Hello packet broadcast.
	delay = (clocktype) (Get_rand()	* OSPFv2_BROADCAST_JITTER);

	// Determine destination address
	//unsigned dstAddr;
	if ((ospf->iface[i].type ==OSPFv2_BROADCAST_INTERFACE) ||(ospf->iface[i].type ==OSPFv2_POINT_TO_POINT_INTERFACE))
	{
		//dstAddr  = OSPFv2_ALL_SPF_ROUTERS;
 		info->nexthopaddr=ANY_DEST;
 		info->interfaceIndex=i;
 		info->srcAddr=ospf->iface[i].address;
 		info->dstAddr=OSPFv2_ALL_SPF_ROUTERS;
		helloMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_OutEVENT_OSPFv2_toNetworkIP,SNS_MSG_OUTPUT,helloPayLoad,sizeof(Ospfv2HelloPacket)+ (sizeof(unsigned) * numNeighbor));
		helloMsg->SNS_Msg_AddInfo((char*)info,sizeof(NetworkToMACInfo));
		//helloMsg->SNS_Msg_Packet_AddHeader(msgInfo,sizeof(NetworkToMACInfo));
		Scenarios_Data->SNS_Msg_Send(helloMsg->SNS_Msg_Copy(),Cur_Node_id,delay);

		////****!!!!
		xdelete( helloMsg ) ;




		//NetworkIpSendRawMessageToMacLayerWithDelay(
		//	node,
		//	MESSAGE_Duplicate(node, helloMsg),
		//	NetworkIpGetInterfaceAddress(node, i),
		//	dstAddr,
		//	IPTOS_PREC_INTERNETCONTROL,
		//	IPPROTO_OSPF,
		//	1,
		//	i,
		//	ANY_DEST,
		//	delay);
	}
	else if (ospf->iface[i].type ==	OSPFv2_POINT_TO_MULTIPOINT_INTERFACE)
	{
		if(ospf->iface[i].NonBroadcastNeighborList->size != 0)
		{
			Ospfv2NonBroadcastNeighborListItem* tempListItem =ospf->iface[i].NonBroadcastNeighborList->first;
			while(tempListItem)
			{
				//dstAddr = tempListItem->neighborAddr;
				info->nexthopaddr=tempListItem->neighborAddr;
				info->interfaceIndex=i;
				info->srcAddr=ospf->iface[i].address;
				info->dstAddr=tempListItem->neighborAddr;
				helloMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_OutEVENT_OSPFv2_toNetworkIP,SNS_MSG_OUTPUT,helloPayLoad,sizeof(Ospfv2HelloPacket)+ (sizeof(unsigned) * numNeighbor));

				helloMsg->SNS_Msg_AddInfo((char*)info,sizeof(NetworkToMACInfo));
				Scenarios_Data->SNS_Msg_Send(helloMsg->SNS_Msg_Copy(),Cur_Node_id,delay);

				////****!!!!
				xdelete( helloMsg ) ;




				//NetworkIpSendRawMessageToMacLayerWithDelay(
				//	node,
				//	MESSAGE_Duplicate(node, helloMsg),
				//	NetworkIpGetInterfaceAddress(node, i),
				//	dstAddr,
				//	IPTOS_PREC_INTERNETCONTROL,
				//	IPPROTO_OSPF,
				//	1,
				//	i,
				//	dstAddr,
				//	delay);
				tempListItem = tempListItem->next;
			}
		}
		else
		{
			//dstAddr  = OSPFv2_ALL_SPF_ROUTERS;
			info->nexthopaddr=ANY_DEST;
			info->interfaceIndex=i;
			info->srcAddr=ospf->iface[i].address;
			info->dstAddr=OSPFv2_ALL_SPF_ROUTERS;
			helloMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_OutEVENT_OSPFv2_toNetworkIP,SNS_MSG_OUTPUT,helloPayLoad,sizeof(Ospfv2HelloPacket)+ (sizeof(unsigned) * numNeighbor));

			helloMsg->SNS_Msg_AddInfo((char*)info,sizeof(NetworkToMACInfo));
			Scenarios_Data->SNS_Msg_Send(helloMsg->SNS_Msg_Copy(),Cur_Node_id,delay);

			////****!!!!
			xdelete( helloMsg ) ;

			//NetworkIpSendRawMessageToMacLayerWithDelay(
			//	node,
			//	MESSAGE_Duplicate(node, helloMsg),
			//	NetworkIpGetInterfaceAddress(node, i),
			//	dstAddr,
			//	IPTOS_PREC_INTERNETCONTROL,
			//	IPPROTO_OSPF,
			//	1,
			//	i,
			//	ANY_DEST,
			//	delay);
		}
	}

	// TBD: Now send it out. ANY_DEST is used as the destination here
	// to make it compatible with 802.11 networks.
	// Ideally, we would use NetworkIpGetInterfaceBroadcastAddress().
	// However, 802.11 currently doesn't support this.

	xdelete(helloMsg);
	xdelete(info);

	if(numNeighbor > 0)
	{
		xfree(neighborList);
	}
	ospf->stats.numHelloSent++;

	////****!!!!
	xfree( helloPayLoad ) ;

}
int Sns_Model_OSPFv2::Ospfv2GetInterfaceIndexFromAddress(unsigned address)
{
	for(int i=0;i<numberInterfaces;i++)
	{
		if(ospf->iface[i].address==address)
			return i;
	}
	return -1;
}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2ScheduleLSA()
// PURPOSE      :Schedule LSA origination
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2ScheduleLSA(Ospfv2LinkStateHeader* LSHeader,unsigned int areaId)
{
	if (LSHeader->linkStateType == OSPFv2_ROUTER)
	{
		Ospfv2ScheduleRouterLSA(areaId, FALSE);
	}
	else if (LSHeader->linkStateType == OSPFv2_NETWORK)
	{
		int interfaceIndex = Ospfv2GetInterfaceIndexFromAddress(LSHeader->linkStateID);
		Ospfv2ScheduleNetworkLSA(interfaceIndex, FALSE);
	}
	else if (LSHeader->linkStateType == OSPFv2_NETWORK_SUMMARY)
	{
		unsigned addrMask;

		memcpy(&addrMask, LSHeader + 1, sizeof(unsigned));
		Ospfv2ScheduleSummaryLSA(LSHeader->linkStateID, addrMask,OSPFv2_DESTINATION_NETWORK, areaId, FALSE);
	}
	else if (LSHeader->linkStateType == OSPFv2_ROUTER_SUMMARY)
	{
		unsigned addrMask = 0xFFFFFFFF;

		Ospfv2ScheduleSummaryLSA(LSHeader->linkStateID, addrMask,OSPFv2_DESTINATION_ASBR, areaId, FALSE);
	}
	else if (LSHeader->linkStateType == OSPFv2_ROUTER_AS_EXTERNAL)
	{
		Ospfv2ExternalLinkInfo* ospfv2ExternalLinkInfo;

		ospfv2ExternalLinkInfo = (Ospfv2ExternalLinkInfo*) (LSHeader + 1);

		Ospfv2ScheduleASExternalLSA(LSHeader->linkStateID, ospfv2ExternalLinkInfo->networkMask,0,Ospfv2ExternalLinkGetMetric(ospfv2ExternalLinkInfo->ospfMetric),FALSE);
	}
	else
	{
		// Shouldn't reach here
		ERROR_Assert(FALSE, "Wrong LS type\n");
	}
}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2RefreshLSA()
// PURPOSE      :Refreshing LSA. The function simply increment sequence
//               number of the LSA by 1 and set the age to 0.
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2RefreshLSA(Ospfv2ListItem* LSAItem,unsigned int areaId)
{
	Ospfv2LinkStateHeader* LSHeader = (Ospfv2LinkStateHeader*) LSAItem->data;

	if (LSHeader->linkStateSequenceNumber ==
		(signed int) OSPFv2_MAX_SEQUENCE_NUMBER)
	{
		// Sequence number reaches the maximum value. We need to
		// flush this instance first before originating any instance.

		Ospfv2FlushLSA((char*) LSHeader, areaId);

		Ospfv2ScheduleLSA(LSHeader, areaId);

		//FIXME: Should remove after
		// a) It is no longer contained in any neighbors
		//      retransmission list
		// b) None of the router's neighbors are in state
		//      Exchange/Loading

		Ospfv2RemoveLSAFromLSDB((char*) LSHeader, areaId);
	}
	else
	{
		LSHeader->linkStateSequenceNumber += 1;
		LSHeader->linkStateAge = 0;
		LSAItem->timeStamp = SimClock();

		// Flood LSA
		if (LSHeader->linkStateType == OSPFv2_ROUTER_AS_EXTERNAL)
		{
			Ospfv2FloodThroughAS(ANY_INTERFACE,(char*) LSHeader,ANY_DEST);
		}
		else
		{
			Ospfv2FloodLSA(ANY_INTERFACE,(char*) LSHeader,ANY_DEST,areaId);
		}

		ospf->stats.numLSARefreshed++;
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2IncrementLSAgeInLSAList
// PURPOSE      :Increment the link state age field of LSAs stored in the
//               LSDB and handle appropriately if this age field passes
//               a maximum age limit.
// ASSUMPTION   :None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2IncrementLSAgeInLSAList(Ospfv2List* tlist,unsigned int areaId)
{
	Ospfv2ListItem* item = tlist->first;
	while (item)
	{
		short int tempAge;

		Ospfv2LinkStateHeader* LSHeader =
			(Ospfv2LinkStateHeader*) item->data;
		tempAge = (short int) (LSHeader->linkStateAge+ (OSPFv2_LSA_INCREMENT_AGE_INTERVAL / SECOND));

		if (tempAge > (OSPFv2_LSA_MAX_AGE / SECOND))
		{
			tempAge = OSPFv2_LSA_MAX_AGE / SECOND;
		}

		// Increment LS age.
		LSHeader->linkStateAge = tempAge;
		// LS Age field of Self originated LSA reaches LSRefreshTime
		if ((LSHeader->advertisingRouter == ospf->routerID)
			&& (tempAge == (OSPFv2_LS_REFRESH_TIME / SECOND)))
		{
			Ospfv2ListItem* tempItem;
			tempItem = item;
			item = item->next;
			if (LSHeader->linkStateType >= OSPFv2_ROUTER&& LSHeader->linkStateType <= OSPFv2_ROUTER_AS_EXTERNAL)
			{
				Ospfv2RefreshLSA(tempItem, areaId);
			}

			// M-OSPF Patch Start
			else if (LSHeader->linkStateType == OSPFv2_GROUP_MEMBERSHIP)
			{
				//MospfScheduleGroupMembershipLSA(node, areaId,(unsigned) ANY_INTERFACE, LSHeader->linkStateID, FALSE);
			}
			// M-OSPF Patch End
		}
		// Expired, so remove from LSDB and flood.
		else if(tempAge == (OSPFv2_LSA_MAX_AGE / SECOND))
		{
			Ospfv2ListItem* deleteItem = item;
			item = item->next;
			ospf->stats.numExpiredLSAge++;

			// Flood deleted LSA to quickly inform others of the invalid LSA.
			if (LSHeader->linkStateType == OSPFv2_ROUTER_AS_EXTERNAL)
			{
				Ospfv2FloodThroughAS(ANY_INTERFACE, (char*) LSHeader, ANY_DEST);
			}
			else
			{
				Ospfv2FloodLSA(ANY_INTERFACE, (char*) LSHeader, ANY_DEST, areaId);
			}

			// Now remove from LSDB.
			//FIXME: Must be removed immediately from the router's LSDB
			//    as soon as both
			// a) It is no longer contained in any neighbors Retx list
			// b) None of router's neighbors are in states Exchange or Loading
			Ospfv2RemoveFromList(tlist, deleteItem, FALSE);

			// Need to recalculate shortest path since topology changed.
			Ospfv2ScheduleSPFCalculation();
		}
		else
		{
			item = item->next;
		}
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2IncrementLSAge
// PURPOSE      :Increment the link state age field of LSAs stored in LSDB.
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2IncrementLSAge()
{
	Ospfv2ListItem* listItem;
	for (listItem = ospf->area->first; listItem; listItem = listItem->next)
	{
		Ospfv2Area* thisArea = (Ospfv2Area*) listItem->data;

		Ospfv2IncrementLSAgeInLSAList(thisArea->networkLSAList,thisArea->areaID);
		Ospfv2IncrementLSAgeInLSAList(thisArea->routerLSAList,thisArea->areaID);
		Ospfv2IncrementLSAgeInLSAList(thisArea->routerSummaryLSAList,thisArea->areaID);
		Ospfv2IncrementLSAgeInLSAList(thisArea->networkSummaryLSAList,thisArea->areaID);

		if (ospf->isMospfEnable == TRUE)
		{
			Ospfv2IncrementLSAgeInLSAList(thisArea->groupMembershipLSAList,thisArea->areaID);
		}
	}

	// BGP-OSPF Patch Start
	//Ospfv2IncrementLSAgeInLSAList(node, ospf->asExternalLSAList, 0);
	Ospfv2IncrementLSAgeInLSAList(ospf->asExternalLSAList, OSPFv2_INVALID_AREA_ID);
	// BGP-OSPF Patch End
}


//-------------------------------------------------------------------------//
// NAME: Ospfv2InvalidateRoutingTable
// PURPOSE: Invalidate present routing table
// RETURN: None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2InvalidateRoutingTable()
{
	int i;
	Ospfv2RoutingTableRow* rowPtr =	(Ospfv2RoutingTableRow*) BUFFER_GetData(&ospf->routingTable.buffer);

	for (i = 0; i < ospf->routingTable.numRows; i++)
	{
		// BGP-OSPF Patch Start
		if (ospf->asBoundaryRouter &&
			(rowPtr[i].pathType == OSPFv2_TYPE2_EXTERNAL))
		{
			continue;
		}
		// BGP-OSPF Patch End

		rowPtr[i].flag = OSPFv2_ROUTE_INVALID;
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2LookupLSAListByID()
// PURPOSE      :Search for the LSA in list by Link State ID
// ASSUMPTION   :None
// RETURN VALUE :Ospfv2LinkStateHeader*
//-------------------------------------------------------------------------//

Sns_Model_OSPFv2::Ospfv2LinkStateHeader* Sns_Model_OSPFv2::Ospfv2LookupLSAListByID(Ospfv2List* list,unsigned linkStateID)
{
	Ospfv2LinkStateHeader* listLSHeader = NULL;

	Ospfv2ListItem* item = list->first;

	while (item)
	{
		// Get LS Header
		listLSHeader = (Ospfv2LinkStateHeader*) item->data;

		if (listLSHeader->linkStateID == linkStateID)
		{
			return listLSHeader;
		}

		item = item->next;
	}
	return NULL;
}
//-------------------------------------------------------------------------//
//                       SHORTEST PATH CALCULATION                         //
//-------------------------------------------------------------------------//

//-------------------------------------------------------------------------//
// NAME: Ospfv2LSAHasMaxAge()
// PURPOSE: Check whether the given LSA has MaxAge
// RETURN: TRUE if age is MaxAge, FALSE otherwise
//-------------------------------------------------------------------------//
bool Sns_Model_OSPFv2::Ospfv2LSAHasMaxAge(char* LSA)
{
	Ospfv2LinkStateHeader* LSHeader = (Ospfv2LinkStateHeader*) LSA;

	if (LSHeader->linkStateAge == (OSPFv2_LSA_MAX_AGE / SECOND))
	{
		return TRUE;
	}

	return FALSE;
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2LSAHasLink()
// PURPOSE: Check whether the given LSA's have link
// RETURN: TRUE if a link is found, FALSE otherwise
//-------------------------------------------------------------------------//
bool Sns_Model_OSPFv2::Ospfv2LSAHasLink(char*  wLSA, char*  vLSA)
{
	Ospfv2LinkStateHeader* wLSHeader = (Ospfv2LinkStateHeader*) wLSA;
	Ospfv2LinkStateHeader* vLSHeader = (Ospfv2LinkStateHeader*) vLSA;

	if (wLSHeader->linkStateType == OSPFv2_ROUTER)
	{
		short int numLinks = ((Ospfv2RouterLSA*) wLSA)->numLinks;
		short int i;

		Ospfv2LinkInfo* link =(Ospfv2LinkInfo*) (wLSA + sizeof(Ospfv2RouterLSA));

		for (i = 0; i < numLinks; i++)
		{
			short int numTos;

			if (link->type == OSPFv2_POINT_TO_POINT)
			{
				if ((vLSHeader->linkStateType == OSPFv2_ROUTER)	&& (link->linkID == vLSHeader->advertisingRouter)
					)
				{
					return TRUE;
				}
			}
			else if (link->type == OSPFv2_TRANSIT)
			{
				if ((vLSHeader->linkStateType == OSPFv2_NETWORK)&& (link->linkID == vLSHeader->linkStateID))
				{
					return TRUE;
				}
			}
			numTos = link->numTOS;
			link = (Ospfv2LinkInfo*)((QospfPerLinkQoSMetricInfo*)(link + 1)	+ numTos);
		}
	}
	else if (wLSHeader->linkStateType == OSPFv2_NETWORK)
	{
		short int numLink = (short) ((wLSHeader->length	- sizeof(Ospfv2LinkStateHeader) - sizeof(unsigned))	/ sizeof(unsigned));
		short int i;
		unsigned* attachedRouter = (unsigned*) (wLSA+ sizeof(Ospfv2LinkStateHeader)	+ sizeof(unsigned));

		if (vLSHeader->linkStateType == OSPFv2_NETWORK)
		{
			return FALSE;
		}

		for (i = 0; i < numLink; i++)
		{
			if (attachedRouter[i] == vLSHeader->linkStateID)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2InShortestPathList
// PURPOSE: Determine if a node is already in the shortest path list.
// RETURN: TRUE if node is in the shortest path list, FALSE otherwise.
//-------------------------------------------------------------------------//
bool Sns_Model_OSPFv2::Ospfv2InShortestPathList(Ospfv2List* shortestPathList,Ospfv2VertexType vertexType,unsigned vertexId)
{
	Ospfv2ListItem* listItem  = shortestPathList->first;
	Ospfv2Vertex* listVertex = NULL;

	// Search through the shortest path list for the node.
	while (listItem)
	{
		listVertex = (Ospfv2Vertex*) listItem->data;

		// Found it.
		if ((listVertex->vertexType == vertexType)&& (listVertex->vertexId == vertexId))
		{
			return TRUE;
		}
		listItem = listItem->next;
	}
	return FALSE;
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2CheckRouterLSASetThisNetworkTransit()
// PURPOSE: Check whether routerLSA treated this netAddr as Transit Network.
// RETURN: TRUE if netAddr as 'Transit Network'. FALSE otherwise.
//-------------------------------------------------------------------------//
bool Sns_Model_OSPFv2::Ospfv2CheckRouterLSASetThisNetworkTransit(Ospfv2RouterLSA* routerLSA,unsigned netAddr,unsigned subnetMask)
{
	int j;
	Ospfv2LinkInfo* linkList = (Ospfv2LinkInfo*) (routerLSA + 1);

	for (j = 0; j < routerLSA->numLinks; j++)
	{
		int numTos;

		if ((linkList->linkID & subnetMask) == netAddr&& linkList->type == OSPFv2_TRANSIT)
		{
			return TRUE;
		}

		// Place the linkList pointer properly
		numTos = linkList->numTOS;
		linkList = (Ospfv2LinkInfo*)((QospfPerLinkQoSMetricInfo*)(linkList + 1) + numTos);
	}
	return FALSE;
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2IsTransitWithNetworkVertex()
// PURPOSE: Check whether the Network of this vertexId is 'Transit Network'
//          perspective to the area of this node. This means this router
//          should view the network as a 'Transit Network'.
// RETURN: TRUE if node have a Transit link. FALSE otherwise.
//-------------------------------------------------------------------------//
bool Sns_Model_OSPFv2::Ospfv2IsTransitWithNetworkVertex(Ospfv2Area* thisArea,unsigned vertexId)
{
	int i;
	Ospfv2RouterLSA* ownRouterLSA = NULL;

	ownRouterLSA = (Ospfv2RouterLSA*) Ospfv2LookupLSAList(thisArea->routerLSAList,ospf->routerID,ospf->routerID);

	if (ownRouterLSA == NULL)
	{
		return FALSE;
	}

	for (i = 0; i < numberInterfaces; i++)
	{
		unsigned subnetMask = ospf->iface[i].subnetMask;
		unsigned netAddr = ospf->iface[i].address;
		if ((vertexId & subnetMask) == netAddr	&& ospf->iface[i].state != S_Down	&& Ospfv2CheckRouterLSASetThisNetworkTransit(ownRouterLSA, netAddr, subnetMask))
		{
			return TRUE;
		}
	}
	return FALSE;
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2GetLinkDataForThisVertex()
// PURPOSE: Get link data from the associated link for this vertex.
// RETURN: None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2GetLinkDataForThisVertex(Ospfv2Vertex* vertex,Ospfv2Vertex* parent,unsigned* linkData)
{
	int i = 0;
	char assertStr[SNS_MAX_STRING_LENGTH];
	Ospfv2RouterLSA* rtrLSA = (Ospfv2RouterLSA*) parent->LSA;
	Ospfv2LinkInfo* linkList = (Ospfv2LinkInfo*) (rtrLSA + 1);

	for (i = 0; i < rtrLSA->numLinks; i++)
	{
		int numTos;

		if (linkList->linkID == vertex->vertexId&& linkList->type != OSPFv2_STUB)
		{
			*linkData = linkList->linkData;

			return;
		}

		// Place the linkList pointer properly
		numTos = linkList->numTOS;
		linkList = (Ospfv2LinkInfo*)((QospfPerLinkQoSMetricInfo*)(linkList + 1)	+ numTos);
	}

	// Shouldn't get here
	sprintf(assertStr, "Not get link data from the associated link for this vertex 0x%x\n", vertex->vertexId);
	ERROR_Assert(TRUE, assertStr);
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2GetNbrInfoOnInterface
// PURPOSE:  Get the neighbor structure from the neighbor list of specific
//           interface using the neighbor's router ID.
// RETURN: The neighbor structure we are looking for, or NULL if not found.
//-------------------------------------------------------------------------//
Sns_Model_OSPFv2::Ospfv2Neighbor* Sns_Model_OSPFv2::Ospfv2GetNbrInfoOnInterface(unsigned nbrId,int interfaceIndex)
{
	Ospfv2ListItem* listItem = NULL;
	Ospfv2Neighbor* nbrInfo = NULL;
	listItem = ospf->iface[interfaceIndex].neighborList->first;

	// Search for the neighbor in my neighbor list.
	while (listItem)
	{
		nbrInfo = (Ospfv2Neighbor*) listItem->data;

		ERROR_Assert(!nbrInfo, "Neighbor not found in the Neighbor list");

		if (nbrInfo->neighborID == nbrId)
		{
			// Found the neighbor we are looking for.
			return nbrInfo;
		}

		listItem = listItem->next;
	}

	return NULL;
}


//-------------------------------------------------------------------------//
// NAME: Ospfv2FindCandidate()
// PURPOSE: Find candidate in list
// RETURN: Pointer to candidate, NULL otherwise.
//-------------------------------------------------------------------------//
Sns_Model_OSPFv2::Ospfv2Vertex*  Sns_Model_OSPFv2::Ospfv2FindCandidate(Ospfv2List* candidateList,Ospfv2VertexType vertexType,unsigned vertexId)
{
	Ospfv2ListItem* tempItem = candidateList->first;
	// Search entire candidate list
	while (tempItem)
	{
		Ospfv2Vertex* tempEntry = (Ospfv2Vertex*) tempItem->data;
		// Candidate found.
		if ((tempEntry->vertexType == vertexType)&& (tempEntry->vertexId == vertexId))
		{
			return tempEntry;
		}
		tempItem = tempItem->next;
	}
	return NULL;
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2IsPresentInNextHopList()
// PURPOSE: Find if nextHopListItem already present in nextHopList
// RETURN: TRUE on success, FALSE otherwise
//-------------------------------------------------------------------------//
bool Sns_Model_OSPFv2::Ospfv2IsPresentInNextHopList(Ospfv2List* nextHopList,Ospfv2NextHopListItem* nextHopListItem)
{
	Ospfv2ListItem* item = NULL;
	item = nextHopList->first;

	while(item)
	{
		Ospfv2NextHopListItem* tmpItem = (Ospfv2NextHopListItem*) item->data;
		if(tmpItem->nextHop == nextHopListItem->nextHop)
		{
			return TRUE;
		}
		item = item->next;
	}
	return FALSE;
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2HaveLinkWithNetworkVertex()
// PURPOSE: Check whether the node has link with this network vertex
// RETURN: TRUE if node have link. FALSE otherwise.
//-------------------------------------------------------------------------//
bool Sns_Model_OSPFv2::Ospfv2HaveLinkWithNetworkVertex(unsigned vertexId)
{
	int i;

	for (i = 0; i < numberInterfaces; i++)
	{
		unsigned subnetMask = ospf->iface[i].subnetMask;
		unsigned netAddr = ospf->iface[i].address;

		if ((vertexId & subnetMask) == netAddr&& ospf->iface[i].state != S_Down)
		{
			return TRUE;
		}
	}
	return FALSE;
}


//-------------------------------------------------------------------------//
// NAME: Ospfv2SetNextHopForThisVertex()
// PURPOSE: Set next hop for the vertex
// RETURN: TRUE on success, FALSE otherwise
//-------------------------------------------------------------------------//
bool Sns_Model_OSPFv2::Ospfv2SetNextHopForThisVertex(Ospfv2Vertex* vertex,Ospfv2Vertex* parent)
{
	Ospfv2NextHopListItem* nextHopItem = NULL;

	// If parent is root, vertex is either directly connected router
	// or network
	if ((parent->vertexType == OSPFv2_VERTEX_ROUTER)&& (parent->vertexId == ospf->routerID))
	{
		unsigned linkData = 0;
		int interfaceIndex;

		nextHopItem = (Ospfv2NextHopListItem*)malloc(sizeof(Ospfv2NextHopListItem));
		Ospfv2GetLinkDataForThisVertex(vertex, parent, &linkData);

		interfaceIndex = Ospfv2GetInterfaceIndexFromlinkData(linkData);
		if(interfaceIndex<0)
		{
			printf("Node %u:InterfaceIndex is %d. vertex:%u, Parent :%u  linkData:%u. \n",Cur_Node_id,interfaceIndex,vertex->vertexId,  parent->vertexId ,linkData);
			Ospfv2PrintLSA(vertex->LSA);
			Ospfv2PrintNextHopList(vertex->nextHopList);
//			getchar();
			return FALSE;
		}
		nextHopItem->outIntf = interfaceIndex;

		if (ospf->iface[interfaceIndex].state == S_Down)
		{
			xfree(nextHopItem);
			return FALSE;
		}

		// Ideally this field is not required for an directly connected
		// network or router which is connected via a point-to-point link.
		// We doesn't considering the case of router connecting through a
		// poin-to-multipoint network. Still adding this field for wireless
		// network.
		if (vertex->vertexType == OSPFv2_VERTEX_ROUTER)
		{
			int interfaceIndex;
			Ospfv2Neighbor* nbrInfo = NULL;

			interfaceIndex = Ospfv2GetInterfaceIndexFromlinkData(linkData);

			nbrInfo = Ospfv2GetNbrInfoOnInterface(vertex->vertexId,interfaceIndex);

			if (nbrInfo == NULL)
			{
				// Neighbor probably removed
				xfree(nextHopItem);
				return FALSE;
			}

			nextHopItem->nextHop = nbrInfo->neighborIPAddress;
		}
		else
		{
			// Vertex is directly connected network
			nextHopItem->nextHop = 0;
		}

		if (!Ospfv2IsPresentInNextHopList(vertex->nextHopList, nextHopItem))
		{
			Ospfv2InsertToList(vertex->nextHopList,0,(void*) nextHopItem);
		}
		else
		{
			xfree(nextHopItem);
			return FALSE;
		}
	}
	// Else if parent is network that directly connects with root
	else if ((parent->vertexType == OSPFv2_VERTEX_NETWORK) &&(Ospfv2HaveLinkWithNetworkVertex(parent->vertexId)))
	{
		unsigned linkData = 0;
		int interfaceIndex;

		nextHopItem = (Ospfv2NextHopListItem*)malloc(sizeof(Ospfv2NextHopListItem));
		Ospfv2GetLinkDataForThisVertex(parent, vertex, &linkData);
		nextHopItem->nextHop = linkData;
		interfaceIndex = Ospfv2GetInterfaceForThisNeighbor(linkData);

		if (ospf->iface[interfaceIndex].state == S_Down)
		{
			xfree(nextHopItem);
			return FALSE;
		}

		nextHopItem->outIntf = interfaceIndex;

		if ( !Ospfv2IsPresentInNextHopList(vertex->nextHopList, nextHopItem) )
		{
			Ospfv2InsertToList(vertex->nextHopList,0,(void*) nextHopItem);
		}
		else
		{
			xfree(nextHopItem);
			return FALSE;
		}
	}
	else
	{
		// There should be an intervening router. So inherits the set
		// of next hops from parent
		Ospfv2ListItem* listItem = parent->nextHopList->first;
		bool inserted = FALSE;
		while (listItem)
		{
			nextHopItem = (Ospfv2NextHopListItem*)malloc(sizeof(Ospfv2NextHopListItem));

			memcpy(nextHopItem,listItem->data,sizeof(Ospfv2NextHopListItem));

			if ( !Ospfv2IsPresentInNextHopList(vertex->nextHopList, nextHopItem))
			{
				Ospfv2InsertToList(vertex->nextHopList,0,(void*) nextHopItem);

				inserted = TRUE;
			}
			else
			{
				xfree(nextHopItem);
			}
			listItem = listItem->next;
		}
		return inserted;
	}
	return TRUE;
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2UpdateCandidateListUsingNetworkLSA
// PURPOSE: Update the candidate list using only the network LSAs.
// RETURN: None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2UpdateCandidateListUsingNetworkLSA(Ospfv2Area* thisArea,Ospfv2List* candidateList,Ospfv2Vertex* v)
{
	Ospfv2NetworkLSA* vLSA = NULL;
	unsigned* attachedRouter = NULL;
	int numLink;
	char* wLSA = NULL;
	int i;

	vLSA = (Ospfv2NetworkLSA*) v->LSA;
	attachedRouter = ((unsigned*) (vLSA + 1)) + 1;
	numLink = (vLSA->LSHeader.length - sizeof(Ospfv2NetworkLSA) - 4)/ (sizeof(unsigned));

	for (i = 0; i < numLink; i++)
	{
		Ospfv2Vertex* candidateListItem = NULL;
		unsigned newVertexId;
		Ospfv2VertexType newVertexType;
		unsigned int newVertexDistance;
		Ospfv2LinkStateHeader* wLSHeader = NULL;
		wLSA = (char*) Ospfv2LookupLSAListByID(thisArea->routerLSAList,attachedRouter[i]);

		// RFC2328, Sec-16.1 (2.b & 2.c)
		if ((wLSA == NULL) || (Ospfv2LSAHasMaxAge(wLSA))|| (!Ospfv2LSAHasLink(wLSA, v->LSA))|| (Ospfv2InShortestPathList(thisArea->shortestPathList,OSPFv2_VERTEX_ROUTER,attachedRouter[i])))
		{
			continue;
		}

		// If it's directly connected network.
		if (Ospfv2IsTransitWithNetworkVertex(thisArea, v->vertexId))
		{
			// Consider only routers that are directly reachable
			unsigned linkData = 0;
			int interfaceIndex;
			Ospfv2Neighbor* nbrInfo = NULL;
			Ospfv2Vertex* root = (Ospfv2Vertex*)thisArea->shortestPathList->first->data;
			Ospfv2GetLinkDataForThisVertex(v, root, &linkData);
			interfaceIndex = Ospfv2GetInterfaceIndexFromlinkData(linkData);

			nbrInfo = Ospfv2GetNbrInfoOnInterface(attachedRouter[i], interfaceIndex);

			if (!nbrInfo)
			{
				continue;
			}
		}

		wLSHeader = (Ospfv2LinkStateHeader*) wLSA;

		newVertexType = OSPFv2_VERTEX_ROUTER;
		newVertexId = wLSHeader->linkStateID;
		newVertexDistance = v->distance;

		candidateListItem = Ospfv2FindCandidate(candidateList,newVertexType,newVertexId);

		if (candidateListItem == NULL)
		{
			// Insert new candidate
			candidateListItem = (Ospfv2Vertex*)	malloc(sizeof(Ospfv2Vertex));

			candidateListItem->vertexId = newVertexId;
			candidateListItem->vertexType = newVertexType;
			candidateListItem->LSA = wLSA;
			candidateListItem->distance = newVertexDistance;

			Ospfv2InitList(&candidateListItem->nextHopList);

			if (Ospfv2SetNextHopForThisVertex(candidateListItem, v))
			{
				Ospfv2InsertToList(candidateList,0,(void*) candidateListItem);
			}
			else
			{
				Ospfv2FreeList(candidateListItem->nextHopList,FALSE);
				xfree(candidateListItem);
			}
		}
		else if (candidateListItem->distance > newVertexDistance)
		{
			// update
			candidateListItem->distance = newVertexDistance;
			Ospfv2DeleteList(candidateListItem->nextHopList,FALSE);
			Ospfv2SetNextHopForThisVertex(candidateListItem, v);
		}
		else if (candidateListItem->distance == newVertexDistance)
		{
			// Add new set of next hop values
			Ospfv2SetNextHopForThisVertex(candidateListItem, v);
		}
		else
		{
			// Examine next link
			continue;
		}
	}
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2UpdateCandidateListUsingRouterLSA
// PURPOSE: Update the candidate list using only the router LSAs.
// RETURN: None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2UpdateCandidateListUsingRouterLSA(Ospfv2Area* thisArea,Ospfv2List* candidateList,Ospfv2Vertex* v)
{
	Ospfv2RouterLSA* vLSA = (Ospfv2RouterLSA*) v->LSA;
	char* wLSA = NULL;
	Ospfv2LinkInfo* linkList = NULL;
	Ospfv2LinkInfo* nextLink = NULL;
	int i;
	nextLink = (Ospfv2LinkInfo*) (vLSA + 1);

	// Examine vertex v's links.
 	for (i = 0; i < vLSA->numLinks; i++)
	{
		int numTos;
		Ospfv2Vertex* candidateListItem = NULL;
		unsigned newVertexId;
		Ospfv2VertexType newVertexType;
		unsigned int newVertexDistance;
		Ospfv2LinkStateHeader* wLSHeader = NULL;

		linkList = nextLink;

		// Place the linkList pointer properly
		numTos = linkList->numTOS;
		nextLink = (Ospfv2LinkInfo*)((QospfPerLinkQoSMetricInfo*)(nextLink + 1)	+ numTos);

		if (linkList->type == OSPFv2_POINT_TO_POINT)
		{
			wLSA = (char*) Ospfv2LookupLSAList(thisArea->routerLSAList,linkList->linkID,linkList->linkID);

			newVertexType = OSPFv2_VERTEX_ROUTER;
		}
		else if (linkList->type == OSPFv2_TRANSIT)
		{
			wLSA = (char*) Ospfv2LookupLSAListByID(thisArea->networkLSAList,linkList->linkID);

			newVertexType = OSPFv2_VERTEX_NETWORK;
		}
		else
		{
			// TBD: Virtual link is not considered yet
			// RFC2328, Sec-16.1 (2.a)
			continue;
		}

		// RFC2328, Sec-16.1 (2.b & 2.c)
		if ((wLSA == NULL) || (Ospfv2LSAHasMaxAge(wLSA))|| (!Ospfv2LSAHasLink(wLSA, v->LSA))|| (Ospfv2InShortestPathList(thisArea->shortestPathList,newVertexType,linkList->linkID)))
		{
			continue;
		}

		wLSHeader = (Ospfv2LinkStateHeader*) wLSA;

		newVertexId = wLSHeader->linkStateID;
		// linkList->metric is a SIGNED short, while newVertexDistance and
		// v->distance are UNSIGNED.
		newVertexDistance = v->distance + (unsigned short)linkList->metric;

		candidateListItem = Ospfv2FindCandidate(candidateList,newVertexType,newVertexId);

		if (candidateListItem == NULL)
		{
			// Insert new candidate
			candidateListItem = (Ospfv2Vertex*)malloc(sizeof(Ospfv2Vertex));

			candidateListItem->vertexId = newVertexId;
			candidateListItem->vertexType = newVertexType;
			candidateListItem->LSA = wLSA;
			candidateListItem->distance = newVertexDistance;

			Ospfv2InitList(&candidateListItem->nextHopList);

			if (Ospfv2SetNextHopForThisVertex(candidateListItem, v))
			{
				Ospfv2InsertToList(candidateList,0,(void*) candidateListItem);
			}
			else
			{
				Ospfv2FreeList(candidateListItem->nextHopList, FALSE);
				xfree(candidateListItem);
			}
		}
		else if (candidateListItem->distance > newVertexDistance)
		{
			// update
			candidateListItem->distance = newVertexDistance;
			// Free old next hop items

			Ospfv2DeleteList(candidateListItem->nextHopList, FALSE);
			Ospfv2SetNextHopForThisVertex(candidateListItem, v);
		}
		else if (candidateListItem->distance == newVertexDistance)
		{
			// Add new set of next hop values
			Ospfv2SetNextHopForThisVertex(candidateListItem, v);
		}
		else
		{
			// Examine next link
			continue;
		}
	}
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2GetValidRoute()
// PURPOSE:  Get desired route from routing table
// RETURN: Route entry. NULL if route not found.
//-------------------------------------------------------------------------//

Sns_Model_OSPFv2::Ospfv2RoutingTableRow* Sns_Model_OSPFv2::Ospfv2GetValidRoute(unsigned destAddr,Ospfv2DestType destType)
{
	int i;
	Ospfv2RoutingTable* rtTable = &ospf->routingTable;
	Ospfv2RoutingTableRow* rowPtr =(Ospfv2RoutingTableRow*) BUFFER_GetData(&rtTable->buffer);

	for (i = 0; i < rtTable->numRows; i++)
	{
		// BGP-OSPF Patch Start
		if ((rowPtr[i].destAddr == 0) && destAddr)
		{
			continue;
		}
		// BGP-OSPF Patch End

		if (ospf->isAdvertSelfIntf)
		{
			if ((rowPtr[i].destAddr == destAddr)&& Ospfv2CompDestType(rowPtr[i].destType, destType)	&& (rowPtr[i].flag != OSPFv2_ROUTE_INVALID))
			{
				return &rowPtr[i];
			}
		}
		else
		{
			if ((rowPtr[i].destAddr & rowPtr[i].addrMask) ==(destAddr & rowPtr[i].addrMask)	&& Ospfv2CompDestType(rowPtr[i].destType, destType)&& (rowPtr[i].flag != OSPFv2_ROUTE_INVALID))
			{
				return &rowPtr[i];
			}
		}
	}
	return NULL;
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2FreeRoute()
// PURPOSE:  Free desired route from routing table
// RETURN: None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2FreeRoute(Ospfv2RoutingTableRow* rowPtr)
{
	Ospfv2RoutingTable* rtTable = &ospf->routingTable;

	ERROR_Assert(!rowPtr, "this variable rowPtr is NULL\n");

	BUFFER_ClearDataFromDataBuffer(&rtTable->buffer,(char*) rowPtr,sizeof(Ospfv2RoutingTableRow),FALSE);
	rtTable->numRows--;
}


//-------------------------------------------------------------------------//
// NAME: Ospfv2UpdateIntraAreaRoute()
// PURPOSE:  Update an Intra Area Route
// RETURN: None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2UpdateIntraAreaRoute(Ospfv2Area* thisArea,Ospfv2Vertex* v)
{

	Ospfv2RoutingTableRow* rowPtr = NULL;
	Ospfv2RoutingTableRow newRow;

	//Ospfv2ListItem* listItem;
	Ospfv2NextHopListItem* nextHopItem = NULL;

	// If vertex is router
	// TBD: Need to keep all route.
	if (v->vertexType == OSPFv2_VERTEX_ROUTER)
	{
		Ospfv2RouterLSA* routerLSA = (Ospfv2RouterLSA*) v->LSA;

		if ((Ospfv2RouterLSAGetASBRouter(routerLSA->ospfRouterLsa) == 1)|| (Ospfv2RouterLSAGetABRouter(routerLSA->ospfRouterLsa) == 1))
		{
			// Add entry of vertex to routing table

			if (Ospfv2RouterLSAGetABRouter(routerLSA->ospfRouterLsa) == 1&& Ospfv2RouterLSAGetASBRouter(routerLSA->ospfRouterLsa) == 1)
			{
				newRow.destType = OSPFv2_DESTINATION_ABR_ASBR;
			}
			else if (Ospfv2RouterLSAGetABRouter(routerLSA->ospfRouterLsa) == 1)
			{
				newRow.destType = OSPFv2_DESTINATION_ABR;
			}
			else
			{
				newRow.destType = OSPFv2_DESTINATION_ASBR;
			}

			newRow.destAddr = v->vertexId;
			newRow.addrMask = 0xFFFFFFFF;

			//TBD:
			newRow.option = 0;

			newRow.areaId = thisArea->areaID;
			newRow.pathType = OSPFv2_INTRA_AREA;
			newRow.metric = v->distance;
			newRow.type2Metric = 0;
			newRow.LSOrigin = (void*) v->LSA;
			newRow.advertisingRouter = routerLSA->LSHeader.advertisingRouter;

			// TBD: consider one next hop for now
			nextHopItem = (Ospfv2NextHopListItem*)
				v->nextHopList->first->data;
			newRow.nextHop = nextHopItem->nextHop;
			newRow.outIntf = nextHopItem->outIntf;

			Ospfv2AddRoute(&newRow);
		}
	}
	// Else it must be a transit network vertex
	else
	{
		unsigned netAddr;
		unsigned netMask;
		Ospfv2NetworkLSA* networkLSA = (Ospfv2NetworkLSA*) v->LSA;

		memcpy(&netMask, networkLSA + 1, sizeof(unsigned));
		netAddr = v->vertexId & netMask;

		rowPtr = Ospfv2GetValidRoute(netAddr,OSPFv2_DESTINATION_NETWORK);

		// If the routing table entry already exists, current routing table
		// entry should be overwritten if and only if the newly found path is
		// just as short and current routing table entry's Link State Origin
		// has a smaller Link State ID than the newly added vertex' LSA.
		if (rowPtr != NULL)
		{
			unsigned linkStateID;

			linkStateID = ((Ospfv2LinkStateHeader*) rowPtr->LSOrigin)
				->linkStateID;

			if ((v->distance > (unsigned int) rowPtr->metric)
				|| (networkLSA->LSHeader.linkStateID < linkStateID))
			{
				return;
			}

			Ospfv2FreeRoute(rowPtr);
		}

		// Add route to routing table
		newRow.destType = OSPFv2_DESTINATION_NETWORK;
		newRow.destAddr = netAddr;
		newRow.addrMask = netMask;
		newRow.option = 0;
		newRow.areaId = thisArea->areaID;
		newRow.pathType = OSPFv2_INTRA_AREA;
		newRow.metric = v->distance;
		newRow.type2Metric = 0;
		newRow.LSOrigin = (void*) v->LSA;
		newRow.advertisingRouter = networkLSA->LSHeader.advertisingRouter;

		// TBD: consider one next hop for now
		nextHopItem = (Ospfv2NextHopListItem*)
			v->nextHopList->first->data;
		newRow.nextHop = nextHopItem->nextHop;
		newRow.outIntf = nextHopItem->outIntf;

		Ospfv2AddRoute(&newRow);
	}
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2UpdateCandidateList
// PURPOSE: Update the candidate list using LSDB (router and network LSAs).
// RETURN: None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2UpdateCandidateList(Ospfv2Area* thisArea,Ospfv2List* candidateList,Ospfv2Vertex* v)
{
	if (v->vertexType == OSPFv2_VERTEX_NETWORK)
	{
		Ospfv2UpdateCandidateListUsingNetworkLSA(thisArea,candidateList,v);
	}
	else
	{
		Ospfv2UpdateCandidateListUsingRouterLSA(thisArea,candidateList,v);
	}
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2UpdateShortestPathList
// PURPOSE: Add new entry to the shortest path list.
// RETURN: The just added entry.
//-------------------------------------------------------------------------//
Sns_Model_OSPFv2::Ospfv2Vertex* Sns_Model_OSPFv2::Ospfv2UpdateShortestPathList(Ospfv2Area* thisArea,Ospfv2List* candidateList)
{
	Ospfv2ListItem* candidateListItem = NULL;
	Ospfv2ListItem* listItem = NULL;

	Ospfv2Vertex* closestCandidate = NULL;
	Ospfv2Vertex* listEntry = NULL;

	Ospfv2Vertex* shortestPathListItem =(Ospfv2Vertex*) malloc(sizeof(Ospfv2Vertex));

	int lowestMetric = OSPFv2_LS_INFINITY;

	listItem = candidateList->first;

	// Get the vertex with the smallest metric from the candidate list...
	while (listItem)
	{
		listEntry = (Ospfv2Vertex*) listItem->data;

		if (listEntry->distance < (unsigned int) lowestMetric)
		{
			lowestMetric = listEntry->distance;

			// Keep track of closest vertex
			candidateListItem = listItem;
			closestCandidate = listEntry;
		}
		// Network vertex get preference over router vertex
		else if ((listEntry->distance == (unsigned int) lowestMetric)&& (candidateListItem)&& (closestCandidate->vertexType== OSPFv2_VERTEX_ROUTER)	&& (listEntry->vertexType == OSPFv2_VERTEX_NETWORK))
		{
			// Keep track of closest vertex
			candidateListItem = listItem;
			closestCandidate = listEntry;
		}

		listItem = listItem->next;
	}

	ERROR_Assert(!candidateListItem, "Candidate list is not exists.\n");

	memcpy(shortestPathListItem, closestCandidate, sizeof(Ospfv2Vertex));
	// Now insert it into the shortest path list...
	Ospfv2InsertToList(thisArea->shortestPathList,0,(void*) shortestPathListItem);
	// And remove it from the candidate list since no longer available.
	Ospfv2RemoveFromList(candidateList, candidateListItem, FALSE);
	// Update my routing table to reflect the new shortest path list.
	Ospfv2UpdateIntraAreaRoute(thisArea, shortestPathListItem);
	if(OSPFv2_DEBUG_LINK)
	{
		Ospfv2PrintLinkList(thisArea->shortestPathList);
		Ospfv2PrintNextHopList(shortestPathListItem->nextHopList);
		Ospfv2PrintAllNextHopList(thisArea->shortestPathList);
	}
	return shortestPathListItem;
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2IsMyAddress
// PURPOSE: Determine if an IP address is my own.
// RETURN: TRUE if it's my IP address, FALSE otherwise.
//-------------------------------------------------------------------------//
bool Sns_Model_OSPFv2::Ospfv2IsMyAddress(unsigned addr)
{
	int i;

	for (i = 0; i < numberInterfaces; i++)
	{
		if (addr == ospf->iface[i].address)
		{
			return TRUE;
		}
	}

	return FALSE;
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2GetValidHostRoute()
// PURPOSE:  Get desired route from routing table
// RETURN: Route entry. NULL if route not found.
//-------------------------------------------------------------------------//

Sns_Model_OSPFv2::Ospfv2RoutingTableRow* Sns_Model_OSPFv2::Ospfv2GetValidHostRoute(unsigned destAddr,Ospfv2DestType destType)
{
	int i;
	Ospfv2RoutingTable* rtTable = &ospf->routingTable;
	Ospfv2RoutingTableRow* rowPtr =(Ospfv2RoutingTableRow*) BUFFER_GetData(&rtTable->buffer);

	for (i = 0; i < rtTable->numRows; i++)
	{
		// BGP-OSPF Patch Start
		if ((rowPtr[i].destAddr == 0) && destAddr)
		{
			continue;
		}
		// BGP-OSPF Patch End

		if ((rowPtr[i].destAddr == destAddr)&& Ospfv2CompDestType(rowPtr[i].destType, destType)&& (rowPtr[i].flag != OSPFv2_ROUTE_INVALID))
		{
			return &rowPtr[i];
		}
	}
	return NULL;
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2RemoveLSAFromShortestPathList
// PURPOSE:
// RETURN:
//-------------------------------------------------------------------------//
bool Sns_Model_OSPFv2::Ospfv2RemoveLSAFromShortestPathList(Ospfv2List* shortestPathList,char* LSA)
{
	Ospfv2ListItem* listItem  = shortestPathList->first;
	Ospfv2Vertex* listVertex = NULL;

	// Search through the shortest path list for the node.
	while (listItem)
	{
		listVertex = (Ospfv2Vertex*) listItem->data;
		if (LSA == listVertex->LSA)
		{
			Ospfv2RemoveFromList(shortestPathList, listItem, FALSE);
			return TRUE;
		}
		listItem = listItem->next;
	}
	return FALSE;
}
//-------------------------------------------------------------------------//
// NAME: Ospfv2AddStubRouteToShortestPath
// PURPOSE: Add stub routes (links) to shortest path.
// RETURN: None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2AddStubRouteToShortestPath(Ospfv2Area* thisArea)
{
	int i;
	Ospfv2ListItem* listItem = NULL;

	Ospfv2Vertex* tempV = NULL;
	Ospfv2RouterLSA* listLSA = NULL;
	Ospfv2LinkInfo* linkList = NULL;
	Ospfv2LinkInfo* nextLink = NULL;

	//unsigned nextHopAddr;
	unsigned distance;
	// Check each router vertex
	listItem = thisArea->shortestPathList->first;

	while (listItem)
	{
		tempV = (Ospfv2Vertex*) listItem->data;

		// Examine router vertex only
		if (tempV->vertexType != OSPFv2_VERTEX_ROUTER)
		{
			listItem = listItem->next;
			continue;
		}

		listLSA = (Ospfv2RouterLSA*) tempV->LSA;
		// Skip LSA if max age is reached and examine the next LSA.
		if (listLSA->LSHeader.linkStateAge >=(OSPFv2_LSA_MAX_AGE / SECOND))
		{
			listItem = listItem->next;
			continue;
		}

		nextLink = (Ospfv2LinkInfo*) (listLSA + 1);

		for (i = 0; i < listLSA->numLinks; i++)
		{
			int numTos;

			linkList = nextLink;

			// Place the nextLink pointer properly
			numTos = nextLink->numTOS;
			nextLink = (Ospfv2LinkInfo*)((QospfPerLinkQoSMetricInfo*)(nextLink + 1)	+ numTos);

			// Examine stub network only
			if (linkList->type == OSPFv2_STUB)
			{
				Ospfv2RoutingTableRow* rowPtr;
				Ospfv2RoutingTableRow newRow;

				// Don't process if this indicates to my address
				if (Ospfv2IsMyAddress(linkList->linkID))
				{
					continue;
				}

				// Calculate distance from root

				// linkList->metric is a SIGNED short, while distance and
				// tempV->distance are UNSIGNED.
				distance = (unsigned short)linkList->metric + tempV->distance;

				// Get this route from routing table
				// handling for host route
				if ((unsigned int)linkList->linkData == 0xffffffff)
				{
					rowPtr = Ospfv2GetValidHostRoute(linkList->linkID,OSPFv2_DESTINATION_NETWORK);
				}
				else
				{
					rowPtr = Ospfv2GetValidRoute(linkList->linkID,OSPFv2_DESTINATION_NETWORK);
				}

				if (rowPtr != NULL)
				{
					// If the calculated distance is larger than previous,
					// examine next stub link
					//
					// TBD: If metrics are equal just add the next hop in
					//      list.
					// Do that once we able to support equal cost multipath.

					if (distance >= (unsigned int) rowPtr->metric)
					{
						continue;
					}

					Ospfv2FreeRoute(rowPtr);
				}

				// Add new route
				newRow.destType = OSPFv2_DESTINATION_NETWORK;
				newRow.destAddr = linkList->linkID;
				newRow.addrMask = linkList->linkData;
				newRow.option = 0;
				newRow.areaId = thisArea->areaID;
				newRow.pathType = OSPFv2_INTRA_AREA;
				newRow.metric = distance;
				newRow.type2Metric = 0;
				newRow.LSOrigin = (void*) tempV->LSA;
				newRow.advertisingRouter =listLSA->LSHeader.advertisingRouter;

				// TBD: consider one next hop for now
				// If stub network is part of the node's interfaces
				if (tempV->vertexId == ospf->routerID)
				{
					int intfId;

					// handling for host route
					if((unsigned int)linkList->linkData == 0xffffffff)
					{
						intfId = Ospfv2GetInterfaceForThisNeighbor(linkList->linkID);
					}
					else
					{
						intfId = NetworkIpGetInterfaceIndexForNextHop(linkList->linkID);
					}

					if (intfId == -1)
					{
						Ospfv2LinkStateHeader* LSHeader = NULL;
						LSHeader = (Ospfv2LinkStateHeader*) Ospfv2LookupLSAList(thisArea->routerLSAList,linkList->linkID,linkList->linkID);
						if(LSHeader != NULL)
						{
							Ospfv2RemoveLSAFromLSDB((char*)LSHeader,thisArea->areaID);
							Ospfv2RemoveLSAFromShortestPathList(thisArea->shortestPathList,(char*)LSHeader);
							if (OSPFv2_DEBUG_TABLEErr)
							{
								Ospfv2PrintLSDB();
							}
						}
						continue;
					}

					newRow.outIntf = intfId;
					newRow.nextHop = 0;
				}
				else
				{
					Ospfv2NextHopListItem* nextHopItem =(Ospfv2NextHopListItem*)tempV->nextHopList->first->data;
					newRow.nextHop = nextHopItem->nextHop;
					newRow.outIntf = nextHopItem->outIntf;

				}

				Ospfv2AddRoute(&newRow);
			}
		}

		listItem = listItem->next;
	}
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2FreeVertexList()
// PURPOSE: Free vertex list.
// RETURN: None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2FreeVertexList(Ospfv2List* vertexList)
{

	Ospfv2ListItem* listItem = vertexList->first;

	while (listItem)
	{
		Ospfv2Vertex* vertex = (Ospfv2Vertex*) listItem->data;

		Ospfv2FreeList(vertex->nextHopList, FALSE);
		listItem = listItem->next;
	}

	Ospfv2FreeList(vertexList, FALSE);
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2FindShortestPathForThisArea
// PURPOSE      :Calculate the shortest path to all node in an area
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2FindShortestPathForThisArea(unsigned areaId)
{
	Ospfv2List* candidateList = NULL;
	Ospfv2Vertex* tempV = NULL;

	Ospfv2Area* thisArea = Ospfv2GetArea(areaId);

	ERROR_Assert(!thisArea, "Specified Area is not found");

	Ospfv2InitList(&thisArea->shortestPathList);
	Ospfv2InitList(&candidateList);

	tempV = (Ospfv2Vertex*) malloc(sizeof(Ospfv2Vertex));
	if (OSPFv2_DEBUG_SPT)
	{
		printf("    Node %u Calculating shortest path for area %u\n",Cur_Node_id, areaId);
		Ospfv2PrintLSDB();
	}    
	// The shortest path starts with myself as the root.
	tempV->vertexId = ospf->routerID;
	tempV->vertexType = OSPFv2_VERTEX_ROUTER;
	tempV->LSA = (char*) Ospfv2LookupLSAList(thisArea->routerLSAList,ospf->routerID,ospf->routerID);

	if (tempV->LSA == NULL)
	{
		xfree(tempV);
		Ospfv2FreeList(thisArea->shortestPathList, FALSE);
		Ospfv2FreeList(candidateList, FALSE);
		return;
	}

	Ospfv2InitList(&tempV->nextHopList);
	tempV->distance = 0;

	// Insert myself (root) to the shortest path list.
	Ospfv2InsertToList(thisArea->shortestPathList,0,(void*)tempV);

	// Find candidates to be considered for the shortest path list.
	Ospfv2UpdateCandidateList(thisArea, candidateList, tempV);
	// Keep calculating shortest path until the candidate list is empty.
	while (candidateList->size > 0)
	{
		// Select the next best node in the candidate list into
		// the shortest path list.  That node is tempV.
		tempV = Ospfv2UpdateShortestPathList(thisArea,candidateList);
		// Find more candidates to be considered for the shortest path list.
		Ospfv2UpdateCandidateList(thisArea, candidateList, tempV);
	}

	// Add stub routes to the shortest path list.
	Ospfv2AddStubRouteToShortestPath(thisArea);

	Ospfv2FreeVertexList(thisArea->shortestPathList);
	Ospfv2FreeVertexList(candidateList);
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2AddInterAreaRoute()
// PURPOSE:  Add Inter Area route to routing table
// RETURN: None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2AddInterAreaRoute(Ospfv2RoutingTableRow* newRoute)
{
	Ospfv2RoutingTable* rtTable = &ospf->routingTable;

	// Get old route if any ..
	Ospfv2RoutingTableRow* rowPtr = Ospfv2GetRoute(newRoute->destAddr,newRoute->destType);

	if (rowPtr)
	{
		if (Ospfv2RoutesMatchSame(newRoute, rowPtr))
		{
			newRoute->flag = OSPFv2_ROUTE_NO_CHANGE;
		}
		else
		{
			newRoute->flag = OSPFv2_ROUTE_CHANGED;
		}

		memcpy(rowPtr, newRoute, sizeof(Ospfv2RoutingTableRow));
	}
	else
	{
		newRoute->flag = OSPFv2_ROUTE_NEW;
		rtTable->numRows++;

		BUFFER_AddDataToDataBuffer(&rtTable->buffer,(char*) newRoute,sizeof(Ospfv2RoutingTableRow));
	}
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2ExamineSummaryLSA
// PURPOSE: Examine this area's Summary LSA for inter area routes.
// RETURN: None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2ExamineSummaryLSA(Ospfv2Area* thisArea,Ospfv2LinkStateType summaryLSAType)
{
	Ospfv2RoutingTableRow* rowPtr = NULL;
	Ospfv2RoutingTableRow* oldRoute = NULL;
	Ospfv2List* list = NULL;
	Ospfv2ListItem* listItem = NULL;
	Ospfv2LinkStateHeader* LSHeader = NULL;
	char* LSABody = NULL;

	if (summaryLSAType == OSPFv2_NETWORK_SUMMARY)
	{
		list = thisArea->networkSummaryLSAList;
	}
	else if (summaryLSAType == OSPFv2_ROUTER_SUMMARY)
	{
		list = thisArea->routerSummaryLSAList;
	}
	else
	{
		ERROR_Assert(TRUE, "Invalid Summary LSA type.");
	}

	listItem = list->first;

	while (listItem)
	{
		Ospfv2RoutingTableRow newRow;
		unsigned destAddr;
		unsigned addrMask;
		unsigned borderRt;
		Int32 metric;

		unsigned char metric1;
		unsigned char metric2;
		unsigned char metric3;

		int index = 0;

		LSHeader = (Ospfv2LinkStateHeader*) listItem->data;
		LSABody = (char*) (LSHeader + 1);

		destAddr = LSHeader->linkStateID;
		memcpy(&addrMask, LSABody, sizeof(unsigned));
		index += 4;

		if (summaryLSAType == OSPFv2_NETWORK_SUMMARY)
		{
			destAddr = destAddr & addrMask;
		}

		borderRt = LSHeader->advertisingRouter;

		metric1 = LSABody[++index];
		metric2 = LSABody[++index];
		metric3 = LSABody[++index];

		metric = ((metric1 << 16) | (metric2 << 8) | (metric3)) & 0xFFFFFF;

		// If cost equal to LSInfinity or age equal to MxAge, examine next
		if ((metric == OSPFv2_LS_INFINITY)	|| (LSHeader->linkStateAge ==(OSPFv2_LSA_MAX_AGE / SECOND)))
		{
			listItem = listItem->next;
			continue;
		}

		// Don't process self originated LSA
		if (LSHeader->advertisingRouter == ospf->routerID)
		{
			listItem = listItem->next;
			continue;
		}

		// If it is a Type 3 summary-LSA, and the collection of destinations
		// described by the summary-LSA equals one of the router's configured
		// area address ranges and there are one or more reachable networks
		// contained in the area range then the summary-LSA should be ignored
		if (summaryLSAType == OSPFv2_NETWORK_SUMMARY)
		{
			Ospfv2AreaAddressRange* addrInfo =
				Ospfv2GetAddrRangeInfoForAllArea(destAddr);

			if (addrInfo != NULL)
			{
				rowPtr = Ospfv2GetValidRoute(destAddr,OSPFv2_DESTINATION_NETWORK);

				if (rowPtr != NULL)
				{
					listItem = listItem->next;
					continue;
				}
			}
		}

		// Lookup the routing table entry for border router having
		// this area as associated area
		rowPtr = Ospfv2GetIntraAreaRoute(borderRt,OSPFv2_DESTINATION_ABR,thisArea->areaID);

		if ((rowPtr == NULL) ||(rowPtr->flag == OSPFv2_ROUTE_INVALID))
		{
			listItem = listItem->next;
			continue;
		}
		newRow.destAddr = destAddr;
		newRow.option = 0;
		newRow.areaId = thisArea->areaID;
		newRow.pathType = OSPFv2_INTER_AREA;
		newRow.metric = rowPtr->metric + metric;

		// BGP-OSPF Patch Start
		if (!destAddr)
		{
			newRow.metric = metric;
		}
		// BGP-OSPF Patch End

		newRow.type2Metric = 0;
		newRow.LSOrigin = (void*) listItem->data;
		newRow.advertisingRouter = borderRt;
		newRow.nextHop = rowPtr->nextHop;
		newRow.outIntf = rowPtr->outIntf;

		if (summaryLSAType == OSPFv2_NETWORK_SUMMARY)
		{
			newRow.destType = OSPFv2_DESTINATION_NETWORK;
			newRow.addrMask = addrMask;

			oldRoute = Ospfv2GetValidRoute(destAddr,OSPFv2_DESTINATION_NETWORK);
		}
		else
		{
			newRow.destType = OSPFv2_DESTINATION_ASBR;
			newRow.addrMask = 0xFFFFFFFF;

			oldRoute = Ospfv2GetValidRoute(destAddr,OSPFv2_DESTINATION_ASBR);
		}

		if ((oldRoute == NULL)
			|| (oldRoute->pathType == OSPFv2_TYPE1_EXTERNAL)
			|| (oldRoute->pathType == OSPFv2_TYPE2_EXTERNAL))
		{
			Ospfv2AddInterAreaRoute(&newRow);
		}
		else if (oldRoute->pathType == OSPFv2_INTRA_AREA)
		{
			// Do nothing
		}
		else
		{
			// Install if new path is cheaper
			//TBD: If cost area equal, add path. Do that after enabling
			//     equal cost multipath
			if (newRow.metric < oldRoute->metric)
			{
				if (summaryLSAType != OSPFv2_NETWORK_SUMMARY
					&& rowPtr->destType == OSPFv2_DESTINATION_ABR_ASBR)
				{
					newRow.destType = OSPFv2_DESTINATION_ABR_ASBR;
				}

				Ospfv2AddInterAreaRoute(&newRow);
			}
		}

		listItem = listItem->next;

	}
}



//-------------------------------------------------------------------------//
// NAME: Ospfv2FindInterAreaPath
// PURPOSE: Calculate Inter Area paths.
// RETURN: None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2FindInterAreaPath()
{
	// Examine only Backbone Summary LSA if the router
	// has active attachment to multiple areas.

	if (ospf->areaBorderRouter == TRUE)
	{
		//assert(ospf->backboneArea);
		ERROR_Assert(!ospf->backboneArea, "Node is an ABR but not any interface belong into the backbone area\n");

		Ospfv2ExamineSummaryLSA(ospf->backboneArea,OSPFv2_NETWORK_SUMMARY);
		Ospfv2ExamineSummaryLSA(ospf->backboneArea,OSPFv2_ROUTER_SUMMARY);
		if (EXAMINE_TRANSIT_AREA)
		{
			Ospfv2ListItem* listItem = ospf->area->first;

			while (listItem)
			{
				Ospfv2Area* thisArea = (Ospfv2Area*) listItem->data;

				if (thisArea->areaID != OSPFv2_BACKBONE_AREA)
				{
					Ospfv2ExamineSummaryLSA(thisArea,OSPFv2_NETWORK_SUMMARY);
					Ospfv2ExamineSummaryLSA(thisArea,OSPFv2_ROUTER_SUMMARY);
				}

				listItem = listItem->next;
			}
		}
	}
	else
	{
		Ospfv2Area* thisArea =(Ospfv2Area*) ospf->area->first->data;

		ERROR_Assert(ospf->area->size != 1, "Node is an interior router,so it should belong into only one area.\n");

		Ospfv2ExamineSummaryLSA(thisArea,OSPFv2_NETWORK_SUMMARY);

		Ospfv2ExamineSummaryLSA(thisArea,OSPFv2_ROUTER_SUMMARY);

	}
}

// BGP-OSPF Patch Start
//-------------------------------------------------------------------------//
// NAME         :Ospfv2FindASExternalPath
// PURPOSE      :Calculate shortest path for the external route.
//               (As specified in Section 16 of RFC 2328)
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2FindASExternalPath()
{
	Ospfv2List* list = ospf->asExternalLSAList;
	Ospfv2ListItem* listItem = list->first;

	while (listItem)
	{
		Ospfv2RoutingTableRow* rowPtr = NULL;
		Ospfv2RoutingTableRow newRow;
		Int32 cost = 0;

		Ospfv2LinkStateHeader* LSHeader =(Ospfv2LinkStateHeader*) listItem->data;
		unsigned destAddr = LSHeader->linkStateID;
		unsigned asExternalRt = LSHeader->advertisingRouter;

		Ospfv2ExternalLinkInfo* LSABody =(Ospfv2ExternalLinkInfo*) (LSHeader + 1);
		unsigned addrMask = LSABody->networkMask;
		unsigned forwardingAdd = LSABody->forwardingAddress;

		destAddr = destAddr & addrMask;

		cost = Ospfv2ExternalLinkGetMetric(LSABody->ospfMetric);

		// If cost equal to LSInfinity or age equal to MxAge, examine next
		if ((cost == OSPFv2_LS_INFINITY)|| (LSHeader->linkStateAge == (OSPFv2_LSA_MAX_AGE / SECOND)))
		{
			listItem = listItem->next;
			continue;
		}

		// Don't process self originated LSA
		if (asExternalRt == ospf->routerID)
		{
			listItem = listItem->next;
			continue;
		}

		rowPtr = Ospfv2GetValidRoute(asExternalRt, OSPFv2_DESTINATION_ASBR);

		// If no entry exist for advertising Router (ASBR), do nothing.
		if (!rowPtr)
		{
			listItem = listItem->next;
			continue;
		}

		newRow.destAddr = destAddr;
		newRow.option = 0;
		newRow.areaId = 0;
		newRow.pathType = OSPFv2_TYPE2_EXTERNAL;
		newRow.type2Metric = cost;
		newRow.LSOrigin = (void*) listItem->data;
		newRow.advertisingRouter = asExternalRt;
		newRow.destType = OSPFv2_DESTINATION_NETWORK;
		newRow.addrMask = addrMask;

		if (!forwardingAdd)
		{
			newRow.metric = rowPtr->metric;
			newRow.nextHop = rowPtr->nextHop;
			newRow.outIntf = rowPtr->outIntf;
		}
		else
		{
			rowPtr = Ospfv2GetValidRoute(forwardingAdd, OSPFv2_DESTINATION_NETWORK);
			if (!rowPtr)
			{
				listItem = listItem->next;
				continue;
			}
			newRow.metric = rowPtr->metric;
			newRow.nextHop = rowPtr->nextHop;
			newRow.outIntf = rowPtr->outIntf;
		}


		rowPtr = Ospfv2GetRoute(newRow.destAddr, newRow.destType);

		//Route exist into the Routing Table.
		if (rowPtr)
		{
			//Intra-area and inter-area paths are always preferred
			//over AS external paths.
			if ((rowPtr->pathType == OSPFv2_INTRA_AREA) ||
				(rowPtr->pathType == OSPFv2_INTER_AREA))
			{
				rowPtr->flag = OSPFv2_ROUTE_NO_CHANGE;
			}
			else if (rowPtr->pathType == OSPFv2_TYPE1_EXTERNAL)
			{
				//Type 1 external paths are compared by looking at the sum
				//of the distance to the forwarding address and the
				//advertised type 1 metric (X+Y).
				if(newRow.pathType == OSPFv2_TYPE1_EXTERNAL)
				{
					if (newRow.metric >= rowPtr->metric)
					{
						rowPtr->flag = OSPFv2_ROUTE_NO_CHANGE;
					}
					else
					{
						newRow.flag = OSPFv2_ROUTE_CHANGED;
						memcpy(rowPtr,&newRow,sizeof(Ospfv2RoutingTableRow));
					}
				}
				//Type 1 external paths are always preferred over
				//type 2 external paths
				else
				{
					rowPtr->flag = OSPFv2_ROUTE_NO_CHANGE;
				}
			}
			else
			{
				//Type 1 external paths are always preferred over
				//type 2 external paths
				if (newRow.pathType == OSPFv2_TYPE1_EXTERNAL)
				{
					newRow.flag = OSPFv2_ROUTE_CHANGED;
					memcpy(rowPtr, &newRow, sizeof(Ospfv2RoutingTableRow));
				}
				else if (newRow.type2Metric > rowPtr->type2Metric)
				{
					rowPtr->flag = OSPFv2_ROUTE_NO_CHANGE;
				}
				else if (newRow.type2Metric == rowPtr->type2Metric)
				{
					if (rowPtr->metric <= newRow.metric)
					{
						rowPtr->flag = OSPFv2_ROUTE_NO_CHANGE;
					}
					else
					{
						newRow.flag = OSPFv2_ROUTE_CHANGED;
						memcpy(rowPtr, &newRow, sizeof(Ospfv2RoutingTableRow));
					}
				}
				else
				{
					newRow.flag = OSPFv2_ROUTE_CHANGED;
					memcpy(rowPtr, &newRow, sizeof(Ospfv2RoutingTableRow));
				}
			}
		}
		else
		{
			Ospfv2RoutingTable* rtTable = &ospf->routingTable;

			newRow.flag = OSPFv2_ROUTE_NEW;
			rtTable->numRows++;
			BUFFER_AddDataToDataBuffer(&rtTable->buffer,(char*) (&newRow),sizeof(Ospfv2RoutingTableRow));
		}

		listItem = listItem->next;
	}
}
// BGP-OSPF Patch End

//-------------------------------------------------------------------------//
// NAME: Ospfv2UpdateIpForwardingTable
// PURPOSE: Update IP's forwarding table so that IP knows how to route
//          packets.
// RETURN: None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2UpdateIpForwardingTable()
{
	int i;
	Ospfv2RoutingTableRow* rowPtr =(Ospfv2RoutingTableRow*) BUFFER_GetData(&ospf->routingTable.buffer);
	forwardingTable->NetworkEmptyForwardingTable(ROUTING_PROTOCOL_OSPFv2);

	for (i = 0; i < ospf->routingTable.numRows; i++)
	{
		// Avoid updating IP forwarding table for route to self and router
		if ((!Ospfv2IsMyAddress(rowPtr[i].destAddr))&&(rowPtr[i].destType == OSPFv2_DESTINATION_NETWORK)&&(rowPtr[i].flag != OSPFv2_ROUTE_INVALID))
		{
			forwardingTable->updateForwardingTable(
				rowPtr[i].destAddr,
				rowPtr[i].addrMask,
				rowPtr[i].nextHop,
				rowPtr[i].outIntf,
				rowPtr[i].metric,
				ROUTING_PROTOCOL_OSPFv2);
		}
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2ResetAdvrtToAreaFlag()
// PURPOSE      :Reset advrtToArea flag within Ospfv2AreaAddressRange struct
//               for each area.
// ASSUMPTION   :None
// RETURN VALUE :None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2ResetAdvrtToAreaFlag()
{
	Ospfv2ListItem* listItem;

	for (listItem = ospf->area->first; listItem; listItem = listItem->next)
	{
		Ospfv2Area* thisArea = (Ospfv2Area*) listItem->data;
		Ospfv2ListItem* addrListItem = thisArea->areaAddrRange->first;

		while (addrListItem)
		{
			int i;
			Ospfv2AreaAddressRange* addrInfo= (Ospfv2AreaAddressRange*) addrListItem->data;

			for (i = 0; i < OSPFv2_MAX_ATTACHED_AREA; i++)
			{
				addrInfo->advrtToArea[i] = FALSE;
			}

			addrListItem = addrListItem->next;
		}
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2NextHopBelongsToThisArea()
// PURPOSE      :Check whether the next hop belongs to this area
// ASSUMPTION   :Consider only one next hop now
// RETURN VALUE :TRUE if next hop belongs to this area, FALSE otherwise
//-------------------------------------------------------------------------//
bool Sns_Model_OSPFv2::Ospfv2NextHopBelongsToThisArea(Ospfv2RoutingTableRow* thisRoute,Ospfv2Area* area)
{
	int intfIndex = thisRoute->outIntf;
	ERROR_Assert(intfIndex == -1, "Neighbor on unknown interface\n");
	if (ospf->iface[intfIndex].areaId == area->areaID)
	{
		return TRUE;
	}
	return FALSE;
}


//-------------------------------------------------------------------------//
// NAME         :Ospfv2AdvertiseRoute()
// PURPOSE      :Advertise this route
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2AdvertiseRoute(Ospfv2RoutingTableRow* thisRoute)
{
	Ospfv2ListItem* listItem = NULL;
	Ospfv2Area* area = NULL;
	int count = 0;

	for (listItem = ospf->area->first; listItem;
		listItem = listItem->next, count++)
	{
		area = (Ospfv2Area*) listItem->data;

		// Inter-Area routes are never advertised to backbone
		if ((thisRoute->pathType == OSPFv2_INTER_AREA)
			&& (area->areaID == OSPFv2_BACKBONE_AREA))
		{
			continue;
		}

		// Do not generate Summary LSA if the area associated
		// with this set of path is the area itself
		if (thisRoute->areaId == area->areaID)
		{
			continue;
		}

		// If next hop belongs to this area ...
		if (Ospfv2NextHopBelongsToThisArea(thisRoute, area))
		{
			continue;
		}

		if (thisRoute->destType == OSPFv2_DESTINATION_ASBR|| thisRoute->destType == OSPFv2_DESTINATION_ABR_ASBR)
		{
			// TBD:
			// Should check if the routing table entry described
			// the preffered path to the AS boundary router.
			Ospfv2OriginateSummaryLSA(thisRoute, area, FALSE);
		}
		else if (thisRoute->pathType == OSPFv2_INTER_AREA)
		{
			Ospfv2OriginateSummaryLSA(thisRoute, area, FALSE);
		}
		else
		{
			// This is an Intra area route to a network which is contained
			// in one of the router's directly attached network
			Ospfv2AreaAddressRange* addrInfo = Ospfv2GetAddrRangeInfo(thisRoute->areaId,thisRoute->destAddr);

			// 1) By default, if a network is not contained in any explicitly
			//    configured address range, a Type 3 summary-LSA is generated
			//
			// 2) The backbone's configured ranges should be ignored when
			//    originating summary-LSAs into transit areas.
			//
			// 3) When range's status indicates DoNotAdvertise, the Type 3
			//    summary-LSA is suppressed and the component networks remain
			//    hidden from other areas.
			//
			// 4) At most a single type3 Summary-LSA is
			//    generated for each range

			if (!addrInfo|| ((thisRoute->areaId == OSPFv2_BACKBONE_AREA)&& (area->transitCapability == TRUE)))
			{
				Ospfv2OriginateSummaryLSA(thisRoute, area, FALSE);
			}
			else if (addrInfo->advertise == TRUE&& addrInfo->advrtToArea[count] == FALSE)
			{
				Ospfv2RoutingTableRow advRt;

				memset(&advRt, 0, sizeof(Ospfv2RoutingTableRow));

				advRt.destType = OSPFv2_DESTINATION_NETWORK;
				advRt.destAddr = addrInfo->address;
				advRt.addrMask = addrInfo->mask;
				advRt.flag = OSPFv2_ROUTE_NO_CHANGE;

				advRt.metric = Ospfv2GetMaxMetricForThisRange(&ospf->routingTable, addrInfo);

				Ospfv2OriginateSummaryLSA(&advRt, area, FALSE);
				addrInfo->advrtToArea[count] = TRUE;
			}
			else
			{
				// DO nothing.
			}
		}
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2CheckOldSummaryLSA()
// PURPOSE      :Supporting function for Ospfv2HandleRemovedOrChangedRoutes.
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2CheckOldSummaryLSA(Ospfv2Area* thisArea,Ospfv2LinkStateType lsType)
{
	Ospfv2RoutingTableRow* rowPtr = NULL;
	Ospfv2List* list = NULL;
	Ospfv2ListItem* listItem = NULL;

	if (lsType == OSPFv2_NETWORK_SUMMARY)
	{
		list = thisArea->networkSummaryLSAList;
	}
	else if (lsType == OSPFv2_ROUTER_SUMMARY)
	{
		list = thisArea->routerSummaryLSAList;
	}
	else
	{
		ERROR_Assert(TRUE, "Invalid Summary LSA type.");
	}

	listItem = list->first;

	while (listItem)
	{
		Ospfv2LinkStateHeader* LSHeader = NULL;
		char* LSABody = NULL;
		unsigned destAddr;
		unsigned addrMask;
		Ospfv2DestType destType;
		int retVal = 0;

		LSHeader = (Ospfv2LinkStateHeader*) listItem->data;
		LSABody = (char*) (LSHeader + 1);

		// Process only self originated LSA
		if (LSHeader->advertisingRouter != ospf->routerID)
		{
			listItem = listItem->next;
			continue;
		}

		destAddr = LSHeader->linkStateID;
		memcpy(&addrMask, LSABody, sizeof(unsigned));

		if (lsType == OSPFv2_NETWORK_SUMMARY)
		{
			destType = OSPFv2_DESTINATION_NETWORK;
		}
		else
		{
			destType = OSPFv2_DESTINATION_ASBR;
			addrMask = 0xFFFFFFFF;
		}

		// Lookup the routing table entry for an entry to this route
		retVal = Ospfv2CheckForSummaryLSAValidity(destAddr, addrMask, destType,thisArea->areaID, &rowPtr);

		if (!retVal)
		{
			Ospfv2FlushLSA((char*) LSHeader, thisArea->areaID);

			listItem = listItem->next;

			Ospfv2RemoveLSAFromLSDB((char*) LSHeader,thisArea->areaID);

			continue;
		}

		listItem = listItem->next;
	}
}


//-------------------------------------------------------------------------//
// NAME         :Ospfv2HandleRemovedOrChangedRoutes()
// PURPOSE      :Some old route may not be flushed by the normal procedure
//               desribed in section 12.4.3 (RFC2328). Take extra care for
//               those routes.
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2HandleRemovedOrChangedRoutes()
{
	Ospfv2ListItem* listItem = NULL;
	Ospfv2Area* area = NULL;

	for (listItem = ospf->area->first; listItem; listItem = listItem->next)
	{
		area = (Ospfv2Area*) listItem->data;

		// Examine all summary LSAs originated by me for this area.
		Ospfv2CheckOldSummaryLSA(area, OSPFv2_NETWORK_SUMMARY);
		Ospfv2CheckOldSummaryLSA(area, OSPFv2_ROUTER_SUMMARY);
	}
}

// BGP-OSPF Patch Start
//-------------------------------------------------------------------------//
// NAME     :Ospfv2OriginateDefaultSummaryLSA()
// PURPOSE  :Originate Default summary LSA for the attached STUB area.
//           This function is called from Ospfv2HandleAbrTask() when
//           routing table contains type1 or type2 external routes.
// RETURN   :None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2OriginateDefaultSummaryLSA()
{
	Ospfv2RoutingTableRow defaultRt;
	Ospfv2ListItem* listItem;

	memset(&defaultRt, 0, sizeof(Ospfv2RoutingTableRow));

	defaultRt.destType = OSPFv2_DESTINATION_NETWORK;
	defaultRt.destAddr = OSPFv2_DEFAULT_DESTINATION;
	defaultRt.addrMask = OSPFv2_DEFAULT_MASK;
	defaultRt.flag = OSPFv2_ROUTE_NO_CHANGE;

	listItem = ospf->area->first;

	while (listItem)
	{
		Ospfv2Area* thisArea = (Ospfv2Area*) listItem->data;

		if (thisArea->transitCapability == FALSE)
		{
			defaultRt.metric = thisArea->stubDefaultCost;
			Ospfv2OriginateSummaryLSA(&defaultRt, thisArea, FALSE);
		}

		listItem = listItem->next;
	}
}
// BGP-OSPF Patch End
//-------------------------------------------------------------------------//
// NAME         :Ospfv2HandleABRTask()
// PURPOSE      :Handle any responsibility occur due to become an ABR
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2HandleABRTask()
{
	int i;
	Ospfv2RoutingTableRow* rowPtr =(Ospfv2RoutingTableRow*) BUFFER_GetData(&ospf->routingTable.buffer);

	bool originateDefaultForAttachedStubArea = FALSE;

	// Check entire routing table for added, deleted or changed
	// Intra-Area or Inter-Area routes that need to be advertised

	Ospfv2ResetAdvrtToAreaFlag();

	for (i = 0; i < ospf->routingTable.numRows; i++)
	{
		// Examine next route if this have not been changed
		if (rowPtr[i].flag == OSPFv2_ROUTE_NO_CHANGE)
		{
			continue;
		}

		if (rowPtr[i].flag == OSPFv2_ROUTE_INVALID)
		{
			continue;
		}

		// Only destination of type newtwork and ASBR needs to be advertised
		if (rowPtr[i].destType == OSPFv2_DESTINATION_ABR)
		{
			continue;
		}

		// External routes area never advertised in Summary LSA
		if ((rowPtr[i].pathType == OSPFv2_TYPE1_EXTERNAL)
			|| (rowPtr[i].pathType == OSPFv2_TYPE2_EXTERNAL))
		{
			originateDefaultForAttachedStubArea = TRUE;

			continue;
		}

		// Summary LSA shouldn't be generated for a route whose
		// cost equal equal or exceed the value LSInfinity

		if (rowPtr[i].metric >= OSPFv2_LS_INFINITY)
		{
			continue;
		}

		// Advertise this route
		Ospfv2AdvertiseRoute(&rowPtr[i]);
	}

	// If the destination is still reachable, yet can no longer be
	// advertised according to the above procedure (e.g., it is now
	// an inter-area route, when it used to be an intra-area route
	// associated with some non-backbone area; it would thus no longer
	// be advertisable to the backbone), the LSA should also be flushed
	// from the routing domain.
	Ospfv2HandleRemovedOrChangedRoutes();

	if (originateDefaultForAttachedStubArea)
	{
		Ospfv2OriginateDefaultSummaryLSA();
	}
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2FreeInvalidRoute()
// PURPOSE:  Free invalid route from routing table
// RETURN: None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2FreeInvalidRoute()
{
	int i;
	Ospfv2RoutingTable* rtTable = &ospf->routingTable;
	Ospfv2RoutingTableRow* rowPtr =(Ospfv2RoutingTableRow*) BUFFER_GetData(&rtTable->buffer);

	for (i = 0; i < rtTable->numRows; i++)
	{
		if (rowPtr[i].flag == OSPFv2_ROUTE_INVALID)
		{
			Ospfv2FreeRoute(&rowPtr[i]);
			i--;
		}
	}
}


void Sns_Model_OSPFv2::Ospfv2FindShortestPath()
{
	Ospfv2ListItem* listItem = NULL;

	// Invalidate present routing table and save it so that
	// changes in routing table entries can be identified.
	Ospfv2InvalidateRoutingTable();

	// Find Intra Area route for each attached area
	for (listItem = ospf->area->first; listItem; listItem = listItem->next)
	{
		Ospfv2Area* thisArea = (Ospfv2Area*) listItem->data;

		Ospfv2FindShortestPathForThisArea(thisArea->areaID);
	}

	// Calculate Inter Area routes
	if (ospf->partitionedIntoArea == TRUE)
	{
		Ospfv2FindInterAreaPath();
	}

	// BGP-OSPF Patch Start
	// NOTE: For CES purposes, this must occur at ALL
	// routers, whether they are asBoundaryRouters or not.
	if (!ospf->asBoundaryRouter )
	{
		// QA-Review Start
		// If there exist more than one ASBR how can they find
		// others advertised routes ??
		// QA-Review End
		Ospfv2FindASExternalPath();
	}
	// BGP-OSPF Patch End

	// Update IP forwarding table using new shortest path.
	Ospfv2UpdateIpForwardingTable();

	if (OSPFv2_DEBUG_TABLE)
	{
		//forwardingTable->print(Cur_Node_id);
		Ospfv2PrintRoutingTable();
		//Ospfv2PrintNeighborState();
	}
	forwardingTable->fprint(Cur_Node_id);
	if ((ospf->partitionedIntoArea == TRUE)
		&& (ospf->areaBorderRouter == TRUE))
	{
		Ospfv2HandleABRTask();
	}

	Ospfv2FreeInvalidRoute();

}


//-------------------------------------------------------------------------//
// NAME         :Ospfv2GetTopLSAFromList()
// PURPOSE      :Get top LSA Header from DB Summary list
// ASSUMPTION   :None
// RETURN VALUE :BOOL
//-------------------------------------------------------------------------//
bool Sns_Model_OSPFv2::Ospfv2GetTopLSAFromList(Ospfv2List* list,Ospfv2LinkStateHeader* LSHeader)
{
	Ospfv2ListItem* listItem = NULL;

	if (list->first == NULL)
	{
		return FALSE;
	}

	listItem = list->first;
	memcpy(LSHeader, listItem->data, sizeof(Ospfv2LinkStateHeader));

	// Remove item from list
	Ospfv2RemoveFromList(list, listItem, FALSE);

	return TRUE;
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2SendDatabaseDescriptionPacket()
// PURPOSE      :Send database description packet
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2SendDatabaseDescriptionPacket(unsigned nbrAddr,int interfaceIndex)
{
	Ospfv2Area* thisArea =Ospfv2GetArea(ospf->iface[interfaceIndex].areaId);
	Ospfv2DatabaseDescriptionPacket* dbDscrpPkt = NULL;
	Ospfv2Neighbor* nbrInfo = NULL;
	unsigned dstAddr;
	clocktype delay;

	// Find neighbor structure
	nbrInfo = Ospfv2GetNeighborInfoByIPAddress(interfaceIndex, nbrAddr);

	ERROR_Assert(!nbrInfo, "Neighbor not found in the Neighbor list");
	
	Sns_Message* dbDscrpMsg = new Sns_Message;

	if (nbrInfo->state == S_ExStart)
	{
		dbDscrpPkt=(Ospfv2DatabaseDescriptionPacket*)malloc(sizeof(Ospfv2DatabaseDescriptionPacket));

		// Set Init, More and master-slave bit
		Ospfv2DatabaseDescriptionPacketSetInit(&(dbDscrpPkt->ospfDbDp), 0x1);
		Ospfv2DatabaseDescriptionPacketSetMore(&(dbDscrpPkt->ospfDbDp), 0x1);
		Ospfv2DatabaseDescriptionPacketSetMS(&(dbDscrpPkt->ospfDbDp), 0x1);

		dbDscrpPkt->ddSequenceNumber = nbrInfo->DDSequenceNumber;
		dbDscrpPkt->commonHeader.packetLength =	sizeof(Ospfv2DatabaseDescriptionPacket);
	}
	else if (nbrInfo->state == S_Exchange)
	{
		Ospfv2LinkStateHeader* payloadBuff;
		int maxLSAHeader =(MAX_NW_PKT_SIZE- sizeof(IpHeaderType)- sizeof(Ospfv2DatabaseDescriptionPacket))/ sizeof(Ospfv2LinkStateHeader);

		int numLSAHeader = 0;

		payloadBuff = (Ospfv2LinkStateHeader*)malloc(maxLSAHeader * sizeof(Ospfv2LinkStateHeader));

		// Get LSA Header list
		while ((numLSAHeader < maxLSAHeader)  &&Ospfv2GetTopLSAFromList(nbrInfo->DBSummaryList,&payloadBuff[numLSAHeader]))
		{
			numLSAHeader++;
		}
		dbDscrpPkt=(Ospfv2DatabaseDescriptionPacket*)malloc(sizeof(Ospfv2DatabaseDescriptionPacket)+ numLSAHeader * sizeof(Ospfv2LinkStateHeader));

		Ospfv2DatabaseDescriptionPacketSetInit(&(dbDscrpPkt->ospfDbDp), 0x0);
		if(Ospfv2ListIsEmpty(nbrInfo->DBSummaryList))
		{
			Ospfv2DatabaseDescriptionPacketSetMore(&(dbDscrpPkt->ospfDbDp),0);
		}
		else
		{
			Ospfv2DatabaseDescriptionPacketSetMore(&(dbDscrpPkt->ospfDbDp),1);
		}
		if(nbrInfo->masterSlave == T_Master)
		{
			Ospfv2DatabaseDescriptionPacketSetMS(&(dbDscrpPkt->ospfDbDp), 1);
		}
		else
		{
			Ospfv2DatabaseDescriptionPacketSetMS(&(dbDscrpPkt->ospfDbDp), 0);
		}
		dbDscrpPkt->ddSequenceNumber = nbrInfo->DDSequenceNumber;
		dbDscrpPkt->commonHeader.packetLength = (short)(sizeof(Ospfv2DatabaseDescriptionPacket)+ numLSAHeader * sizeof(Ospfv2LinkStateHeader));

		memcpy(dbDscrpPkt + 1,payloadBuff,numLSAHeader * sizeof(Ospfv2LinkStateHeader));

		xfree(payloadBuff);
	}

	// Fill in the header fields for the Database Description packet
	Ospfv2CreateCommonHeader(&dbDscrpPkt->commonHeader,OSPFv2_DATABASE_DESCRIPTION);
	dbDscrpPkt->commonHeader.areaID = ospf->iface[interfaceIndex].areaId;
	dbDscrpPkt->interfaceMtu = MAX_NW_PKT_SIZE;

	// Set E-bit if not a stub area
	if (thisArea->transitCapability == TRUE)
	{
		dbDscrpPkt->reserved1 = OSPFv2_OPTION_EXTERNAL;
	}
	else
	{
		dbDscrpPkt->reserved1 = 0x0;
	}

	Ospfv2DatabaseDescriptionPacketSetRsrvd2(&(dbDscrpPkt->ospfDbDp), 0x0);

	// Add to retransmission list
	if (nbrInfo->lastSentDDPkt != NULL)
	{
		xfree(nbrInfo->lastSentDDPkt);
	}

	// Determine destination address
	if (ospf->iface[interfaceIndex].type ==OSPFv2_POINT_TO_POINT_INTERFACE)
	{
		dstAddr = OSPFv2_ALL_SPF_ROUTERS;
	}
	else
	{
		dstAddr = nbrAddr;
	}
	dbDscrpMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_OutEVENT_OSPFv2_toNetworkIP,SNS_MSG_OUTPUT,(char*)dbDscrpPkt,dbDscrpPkt->commonHeader.packetLength);

	

	NetworkToMACInfo* info=new NetworkToMACInfo;
	info->dstAddr=dstAddr;
	info->nexthopaddr=nbrAddr;
	info->interfaceIndex=interfaceIndex;
	info->srcAddr=ospf->iface[interfaceIndex].address;
	dbDscrpMsg->SNS_Msg_AddInfo((char*)info,sizeof(NetworkToMACInfo));
	nbrInfo->lastSentDDPkt = dbDscrpMsg->SNS_Msg_Copy();
	// Now, send packet
	delay = 0;
	//Trace sending pkt
	Scenarios_Data->SNS_Msg_Send(dbDscrpMsg,Cur_Node_id,delay);
	//NetworkIpSendRawMessageToMacLayerWithDelay(
	//	node,
	//	dbDscrpMsg,
	//	NetworkIpGetInterfaceAddress(node,
	//	interfaceIndex),
	//	dstAddr,
	//	IPTOS_PREC_INTERNETCONTROL,
	//	IPPROTO_OSPF,
	//	1,
	//	interfaceIndex,
	//	nbrAddr,
	//	delay);
	xdelete(info);
	nbrInfo->lastDDPktSent = SimClock();
	ospf->stats.numDDPktSent++;

	// Set retransmission timer if this is Master
	if (nbrInfo->masterSlave == T_Master)
	{

		delay = (clocktype) (ospf->iface[interfaceIndex].rxmtInterval+ (Get_rand() * OSPFv2_BROADCAST_JITTER));

		Ospfv2SetTimer(interfaceIndex,MSG_InEVENT_OspfRxmtTimer,nbrInfo->neighborIPAddress,	delay,dbDscrpPkt->ddSequenceNumber,0,OSPFv2_DATABASE_DESCRIPTION);
	}


	////****!!!!
	xdelete( nbrInfo->lastSentDDPkt ) ;

	////****!!!!
	xfree( dbDscrpPkt ) ;

}
void Sns_Model_OSPFv2::Ospfv2AttemptAdjacency(Ospfv2Neighbor* nbrInfo,int interfaceIndex)
{

	// If this is the first time that the adjacency has been attempted,
	// the DD Sequence number should be assigned to some unique value.
	if (nbrInfo->DDSequenceNumber == 0)
	{
		nbrInfo->DDSequenceNumber = (unsigned int) (SimClock()/ SECOND);
	}
	else
	{
		nbrInfo->DDSequenceNumber++;
	}

	nbrInfo->masterSlave = T_Master;

	// Send Empty DD Packet
	Ospfv2SendDatabaseDescriptionPacket(nbrInfo->neighborIPAddress,interfaceIndex);
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2ScheduleInterfaceEvent
// PURPOSE: Schedule an interface event to be executed later. Primary
//          objective is to call Ospfv2HandleInterfaceEvent() asynchronously
// RETURN: None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2ScheduleInterfaceEvent(int interfaceIndex,Ospfv2InterfaceEvent intfEvent)
{
	clocktype delay;
	// Timer is already scheduled
	if (ospf->iface[interfaceIndex].ISMTimer)
	{
		return;
	}
	Sns_Message* newMsg=new Sns_Message;

	Ospfv2ISMTimerInfo* ISMTimerInfo = new Ospfv2ISMTimerInfo;

	ISMTimerInfo->interfaceIndex = interfaceIndex;
	ISMTimerInfo->intfEvent = intfEvent;

	newMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_InEVENT_OspfInterfaceEvent,SNS_MSG_INPUT,NULL,0);
	newMsg->SNS_Msg_AddInfo((char*)ISMTimerInfo,sizeof(Ospfv2ISMTimerInfo));
	xdelete(ISMTimerInfo);
	ospf->iface[interfaceIndex].ISMTimer = TRUE;
	delay = OSPFv2_EVENT_SCHEDULING_DELAY;

	Scenarios_Data->SNS_Msg_Send(newMsg,Cur_Node_id,delay);
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2SetNeighborState()
// PURPOSE      :Set the state of a neighbor.
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2SetNeighborState(int interfaceIndex,Ospfv2Neighbor* neighborInfo,Ospfv2NeighborState state)
{
	Ospfv2NeighborState oldState;

	ERROR_Assert(interfaceIndex == -1, "Neighbor on unknown interface\n");

	oldState = neighborInfo->state;
	neighborInfo->state = state;

	// Attempt to form adjacency if new state is S_ExStart
	if ((oldState != state) && (state == S_ExStart))
	{
		Ospfv2AttemptAdjacency(neighborInfo, interfaceIndex);
	}

	// Need to originate LSA when transitioning from/to S_Full state.
	// This is to inform other neighbors of new link.
	if ((oldState == S_Full && state != S_Full) || (oldState != S_Full && state == S_Full))
	{
		Ospfv2ScheduleRouterLSA(ospf->iface[interfaceIndex].areaId,FALSE);

		if (ospf->iface[interfaceIndex].state == S_DR)
		{
			Ospfv2ScheduleNetworkLSA(interfaceIndex, FALSE);
		}
	}

	// It may be necessary to return to DR election algorithm
	if (((oldState < S_TwoWay) && (state >= S_TwoWay))|| ((oldState >= S_TwoWay) && (state < S_TwoWay)))
	{
		Ospfv2ScheduleInterfaceEvent(interfaceIndex, E_NeighborChange);
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2AdjacencyRequire()
// PURPOSE      :Determine whether adjacency is required with this neighbor.
// ASSUMPTION   :Network type Point-to-Multipoint and
//              :Virtual link are not considered.
// RETURN VALUE :BOOL
//-------------------------------------------------------------------------//
bool Sns_Model_OSPFv2::Ospfv2AdjacencyRequire(int interfaceIndex,Ospfv2Neighbor* nbrInfo)
{
	if ((ospf->iface[interfaceIndex].type ==
		OSPFv2_POINT_TO_POINT_INTERFACE)
		||  (ospf->iface[interfaceIndex].type ==
		OSPFv2_POINT_TO_MULTIPOINT_INTERFACE)
		|| (ospf->iface[interfaceIndex].designatedRouter ==
		ospf->routerID)
		|| (ospf->iface[interfaceIndex].backupDesignatedRouter ==
		ospf->routerID)
		|| (ospf->iface[interfaceIndex].designatedRouter ==
		nbrInfo->neighborID)
		|| (ospf->iface[interfaceIndex].backupDesignatedRouter ==
		nbrInfo->neighborID))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2UpdateDBSummaryList()
// PURPOSE      :Create database summary list for this neighbor
// ASSUMPTION   :None
// RETURN VALUE :Null
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2UpdateDBSummaryList(int interfaceIndex,Ospfv2List* list,Ospfv2Neighbor* nbrInfo)
{
	Ospfv2ListItem* item = list->first;

	while (item)
	{
		Ospfv2LinkStateHeader* LSHeader = NULL;

		// Get LSA...
		Ospfv2LinkStateHeader* listLSHeader =(Ospfv2LinkStateHeader*) item->data;

		// Add to retx list if LSAge is MaxAge
		if (listLSHeader->linkStateAge ==(OSPFv2_LSA_MAX_AGE / SECOND))
		{
			Ospfv2AddToLSRetxList(interfaceIndex,nbrInfo,(char*) listLSHeader);

			item = item->next;
			continue;
		}

		// Create new item to insert to list
		LSHeader = (Ospfv2LinkStateHeader*)malloc(sizeof(Ospfv2LinkStateHeader));

		memcpy(LSHeader, listLSHeader, sizeof(Ospfv2LinkStateHeader));

		Ospfv2InsertToList(nbrInfo->DBSummaryList,0,(void*) LSHeader);

		item = item->next;
	}
}

// BGP-OSPF Patch Start
//-------------------------------------------------------------------------//
// NAME: Ospfv2NeighborIsInStubArea
// PURPOSE:  Check Neighbor is in STUB area or not.
// RETURN: If the neighbor belong into STUB area return TRUE otherwise FALSE
//-------------------------------------------------------------------------//
bool Sns_Model_OSPFv2::Ospfv2NeighborIsInStubArea(int interfaceIndex,Ospfv2Neighbor* nbrInfo)
{
	Ospfv2Area* thisArea;

	thisArea = Ospfv2GetArea(ospf->iface[interfaceIndex].areaId);

	if (thisArea->transitCapability == FALSE)
	{
		return TRUE;
	}

	return  FALSE;
}
// BGP-OSPF Patch End


//-------------------------------------------------------------------------//
// NAME         :Ospfv2CreateDBSummaryList()
// PURPOSE      :Create database summary list for this neighbor
// ASSUMPTION   :None
// RETURN VALUE :Null
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2CreateDBSummaryList(int interfaceIndex,Ospfv2Neighbor* nbrInfo)
{
	Ospfv2Area* thisArea =Ospfv2GetArea(ospf->iface[interfaceIndex].areaId);

	ERROR_Assert(interfaceIndex == -1, "Unknown Neighbor\n");
	ERROR_Assert(!thisArea, "Area doesn't exist\n");
	// Add router LSA Sumary
	Ospfv2UpdateDBSummaryList(interfaceIndex,thisArea->routerLSAList,nbrInfo);

	// Add network LSA Summary
	Ospfv2UpdateDBSummaryList(interfaceIndex,thisArea->networkLSAList,nbrInfo);

	// Add summary LSA Summary
	Ospfv2UpdateDBSummaryList(interfaceIndex,thisArea->routerSummaryLSAList,nbrInfo);
	Ospfv2UpdateDBSummaryList(interfaceIndex,thisArea->networkSummaryLSAList,nbrInfo);

	//TBD: For virtual neighbor, AS-Extarnal LSA should not be included.
	// BGP-OSPF Patch Start
	if (!Ospfv2NeighborIsInStubArea(interfaceIndex, nbrInfo))
	{
		Ospfv2UpdateDBSummaryList(interfaceIndex,ospf->asExternalLSAList,nbrInfo);
	}
	// BGP-OSPF Patch End

	if (ospf->isMospfEnable == TRUE)
	{
		// Add Group Membership LSA Summary
		Ospfv2UpdateDBSummaryList(interfaceIndex, thisArea->groupMembershipLSAList, nbrInfo);
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2CreateLSReqObject()
// PURPOSE      :Create a LS Request object from link state request list
// ASSUMPTION   :None
// RETURN VALUE :BOOL
//-------------------------------------------------------------------------//
bool Sns_Model_OSPFv2::Ospfv2CreateLSReqObject(Ospfv2Neighbor* nbrInfo,Ospfv2LSRequestInfo* LSReqObject,bool retx)
{
	Ospfv2ListItem* listItem = nbrInfo->linkStateRequestList->first;
	Ospfv2LSReqItem* itemInfo = NULL;
	Ospfv2LinkStateHeader* LSHeader = NULL;

	if (retx)
	{
		while (listItem)
		{
			itemInfo = (Ospfv2LSReqItem*) listItem->data;

			if (itemInfo->seqNumber == nbrInfo->LSReqTimerSequenceNumber)
			{
				LSHeader = itemInfo->LSHeader;
				itemInfo->seqNumber = nbrInfo->LSReqTimerSequenceNumber + 1;
				break;
			}
			listItem = listItem->next;
		}
	}
	else
	{
		while (listItem)
		{
			itemInfo = (Ospfv2LSReqItem*) listItem->data;

			if (itemInfo->seqNumber == 0)
			{
				LSHeader = itemInfo->LSHeader;
				itemInfo->seqNumber = nbrInfo->LSReqTimerSequenceNumber + 1;
				break;
			}
			listItem = listItem->next;
		}
	}

	if (LSHeader == NULL)
	{
		return FALSE;
	}
	LSReqObject->linkStateType= (Ospfv2LinkStateType) LSHeader->linkStateType;
	LSReqObject->linkStateID = LSHeader->linkStateID;
	LSReqObject->advertisingRouter = LSHeader->advertisingRouter;

	return TRUE;
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2SendLSRequestPacket()
// PURPOSE      :Send Link State Request. Parameter retx indicates whether we
//               are retransmissing the requests or seding fresh list.
// ASSUMPTION   :None
// RETURN VALUE :Null
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2SendLSRequestPacket(unsigned nbrAddr,int interfaceIndex,bool retx)
{
	
	Ospfv2Neighbor* nbrInfo = NULL;
	unsigned dstAddr;
	clocktype delay;

	Ospfv2LSRequestInfo* payloadBuff = NULL;

	int maxLSReqObject =(MAX_NW_PKT_SIZE- sizeof(IpHeaderType)- sizeof(Ospfv2LinkStateRequestPacket))/ sizeof(Ospfv2LSRequestInfo);
	int numLSReqObject;

	// Find neighbor structure
	nbrInfo = Ospfv2GetNeighborInfoByIPAddress(interfaceIndex, nbrAddr);

	ERROR_Assert(!nbrInfo, "Neighbor not found in the Neighbor list");

	payloadBuff = (Ospfv2LSRequestInfo*)malloc(maxLSReqObject* sizeof(Ospfv2LSRequestInfo));

	numLSReqObject = 0;

	// Prepare LS Request packet payload
	while ((numLSReqObject < maxLSReqObject)&& Ospfv2CreateLSReqObject(nbrInfo,&payloadBuff[numLSReqObject],retx))
	{
		numLSReqObject++;
	}

	// Create LS Request packet
	Sns_Message* reqMsg=new Sns_Message;
	Ospfv2LinkStateRequestPacket* reqPkt =(Ospfv2LinkStateRequestPacket*)malloc(sizeof(Ospfv2LinkStateRequestPacket)+numLSReqObject	* sizeof(Ospfv2LSRequestInfo));

	// Fill in the header fields for the LS Request packet
	Ospfv2CreateCommonHeader(&reqPkt->commonHeader,OSPFv2_LINK_STATE_REQUEST);

	reqPkt->commonHeader.packetLength = (short)(sizeof(Ospfv2LinkStateRequestPacket)+ numLSReqObject * sizeof(Ospfv2LSRequestInfo));
	reqPkt->commonHeader.areaID = ospf->iface[interfaceIndex].areaId;

	// Add payload
	memcpy(reqPkt + 1,payloadBuff,numLSReqObject * sizeof(Ospfv2LSRequestInfo));

	// Free payload Buffer
	xfree(payloadBuff);

	// Determine destination address
	if (ospf->iface[interfaceIndex].type ==OSPFv2_POINT_TO_POINT_INTERFACE)
	{
		dstAddr = OSPFv2_ALL_SPF_ROUTERS;
	}
	else
	{
		dstAddr = nbrAddr;
	}

	// Set retransmission timer
	Ospfv2SetTimer(interfaceIndex,MSG_InEVENT_OspfRxmtTimer,nbrInfo->neighborIPAddress,ospf->iface[interfaceIndex].rxmtInterval,++nbrInfo->LSReqTimerSequenceNumber,0,OSPFv2_LINK_STATE_REQUEST);

	//Trace sending pkt

	// Now, send packet
	NetworkToMACInfo* info=new NetworkToMACInfo;
	info->dstAddr=dstAddr;
	info->nexthopaddr=nbrAddr;
	info->interfaceIndex=interfaceIndex;
	info->srcAddr=ospf->iface[interfaceIndex].address;
	reqMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_OutEVENT_OSPFv2_toNetworkIP,SNS_MSG_OUTPUT,(char*)reqPkt,sizeof(Ospfv2LinkStateRequestPacket)+ numLSReqObject * sizeof(Ospfv2LSRequestInfo));
	reqMsg->SNS_Msg_AddInfo((char*)info,sizeof(NetworkToMACInfo));
	delay = 0;

	Scenarios_Data->SNS_Msg_Send(reqMsg,Cur_Node_id,delay);
	//NetworkIpSendRawMessageToMacLayerWithDelay(
	//	node,
	//	reqMsg,
	//	NetworkIpGetInterfaceAddress(node,
	//	interfaceIndex),
	//	dstAddr,
	//	IPTOS_PREC_INTERNETCONTROL,
	//	IPPROTO_OSPF,
	//	1,
	//	interfaceIndex,
	//	nbrAddr,
	//	delay);
	xdelete(info);
	ospf->stats.numLSReqSent++;

	////****!!!!
	xfree( reqPkt ) ;

}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2FreeRequestList
// PURPOSE      :Free Link State Request list for this neighbor.
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2FreeRequestList(Ospfv2Neighbor* nbrInfo)
{
	Ospfv2ListItem* listItem = nbrInfo->linkStateRequestList->first;

	while (listItem)
	{
		Ospfv2LSReqItem* itemInfo = (Ospfv2LSReqItem*) listItem->data;

		// Remove item from list
		xfree(itemInfo->LSHeader);

		listItem = listItem->next;
	}

	Ospfv2FreeList(nbrInfo->linkStateRequestList, FALSE);
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2DestroyAdjacency()
// PURPOSE      :Destroy possibly formed adjacency.
// ASSUMPTION   :None.
// RETURN VALUE :None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2DestroyAdjacency(Ospfv2Neighbor* nbrInfo)
{
	// Clear lists.
	Ospfv2FreeList(nbrInfo->linkStateRetxList, FALSE);
	Ospfv2FreeList(nbrInfo->DBSummaryList, FALSE);
	Ospfv2FreeRequestList(nbrInfo);

	Ospfv2InitList(&nbrInfo->linkStateRetxList);
	Ospfv2InitList(&nbrInfo->DBSummaryList);
	Ospfv2InitList(&nbrInfo->linkStateRequestList);

	nbrInfo->LSReqTimerSequenceNumber += 1;

	if (nbrInfo->lastSentDDPkt != NULL)
	{
		xfree(nbrInfo->lastSentDDPkt);
		nbrInfo->lastSentDDPkt = NULL;
	}
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2RemoveNeighborFromNeighborList
// PURPOSE:  Remove a neighbor from the neighbor list.
// RETURN: None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2RemoveNeighborFromNeighborList(int interfaceIndex,unsigned neighborAddr)
{
	Ospfv2ListItem* tempListItem =ospf->iface[interfaceIndex].neighborList->first;
	Ospfv2Neighbor* tempNeighborInfo = NULL;

	// Search for the neighbor in my neighbor list.
	while (tempListItem)
	{
		tempNeighborInfo = (Ospfv2Neighbor*) tempListItem->data;

		ERROR_Assert(!tempNeighborInfo,"Neighbor not found in the Neighbor list");

		// Found and xdelete.
		if (tempNeighborInfo->neighborIPAddress == neighborAddr)
		{
			// Clear lists.
			Ospfv2FreeList(tempNeighborInfo->linkStateRetxList,FALSE);

			Ospfv2FreeList(tempNeighborInfo->DBSummaryList,FALSE);

			Ospfv2FreeRequestList(tempNeighborInfo);

			if (tempNeighborInfo->lastSentDDPkt != NULL)
			{
				xfree(tempNeighborInfo->lastSentDDPkt);
			}

			if (tempNeighborInfo->lastReceivedDDPacket != NULL)
			{
				xfree(tempNeighborInfo->lastReceivedDDPacket);
			}

			// Then remove neighbor from neighbor list.
			Ospfv2RemoveFromList(ospf->iface[interfaceIndex].neighborList,tempListItem,FALSE);
			ospf->neighborCount--;
			return;
		}

		tempListItem = tempListItem->next;
	}

	// Neighbor info should have been found.
	ERROR_Assert(TRUE, "Neighbor not found in the Neighbor list");
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2HandleNeighborEvent()
// PURPOSE      :Handle neighbor event and change neighbor state accordingly
// ASSUMPTION   :None
// RETURN VALUE :Null
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2HandleNeighborEvent(int interfaceIndex,unsigned nbrAddr,Ospfv2NeighborEvent eventType)
{
	// Find neighbor structure
	Ospfv2Neighbor* tempNeighborInfo =Ospfv2GetNeighborInfoByIPAddress(interfaceIndex, nbrAddr);
	ERROR_Assert(!tempNeighborInfo,"Neighbor not found in the Neighbor list");
	//debug neighbor state
	if(OSPFv2_DEBUG_NEIGHBOR_EVENT_AND_STATE)
	{
		char destStr[SNS_MAX_STRING_LENGTH];
		char stateStr[SNS_MAX_STRING_LENGTH];
		char eventStr[SNS_MAX_STRING_LENGTH];
		convertIpAddressToString(tempNeighborInfo->neighborIPAddress, destStr);
		Ospfv2GetNeighborStateString(tempNeighborInfo->state, stateStr);
		Ospfv2GetIEString(eventType,eventStr);
		printf("\nneighbor: %15s\tstate:%15s\tIE:%20s\n", destStr, stateStr,eventStr);
	}

	switch (eventType)
	{
	case S_HelloReceived:
		{
			if (tempNeighborInfo->state < S_Init)
			{
				Ospfv2SetNeighborState(interfaceIndex,tempNeighborInfo,S_Init);
			}

			// Reschedule inactivity timer.
			Ospfv2SetTimer(interfaceIndex,MSG_InEVENT_OspfInactivityTimer,nbrAddr,ospf->iface[interfaceIndex].routerDeadInterval,0,0,(Ospfv2PacketType) 0);
			break;
		}

	case S_Start:
		{
			// This event will be generated for NBMA networks only.
			// Avoid this case for now
			break;
		}

	case S_TwoWayReceived:
		{
			if (tempNeighborInfo->state == S_Init)
			{
				// Determine whether adjacency is required
				if (Ospfv2AdjacencyRequire(interfaceIndex,tempNeighborInfo))
				{
					Ospfv2SetNeighborState(interfaceIndex,tempNeighborInfo,S_ExStart);
				}
				else
				{
					Ospfv2SetNeighborState(interfaceIndex,tempNeighborInfo,S_TwoWay);
				}
			}
			// No state change for neighbor state higher than S-Init
			break;
		}

	case S_NegotiationDone:
		{
			if (tempNeighborInfo->state != S_ExStart)
			{
				break;
			}

			Ospfv2SetNeighborState(interfaceIndex,tempNeighborInfo,S_Exchange);
			// List the contents of its entire area link state database
			// in the neighbor Database summary list.
			Ospfv2CreateDBSummaryList(interfaceIndex, tempNeighborInfo);
			break;
		}

	case S_ExchangeDone:
		{
			if (tempNeighborInfo->state != S_Exchange)
			{
				break;
			}

			if (Ospfv2ListIsEmpty(tempNeighborInfo->linkStateRequestList))
			{
				Ospfv2SetNeighborState(interfaceIndex,tempNeighborInfo,S_Full);
			}
			else
			{
				Ospfv2SetNeighborState(interfaceIndex,tempNeighborInfo,S_Loading);

				// Start (or continue) sending Link State Request packet
				Ospfv2SendLSRequestPacket(nbrAddr,interfaceIndex,FALSE);
			}
			break;
		}

	case S_LoadingDone:
		{
			if (tempNeighborInfo->state != S_Loading)
			{
				break;
			}
			Ospfv2SetNeighborState(interfaceIndex,tempNeighborInfo,S_Full);
			break;
		}

	case S_AdjOk:
		{
			if ((Ospfv2AdjacencyRequire(interfaceIndex,tempNeighborInfo))&& (tempNeighborInfo->state == S_TwoWay))
			{
				Ospfv2SetNeighborState(interfaceIndex,tempNeighborInfo,S_ExStart);
			}
			else if ((!Ospfv2AdjacencyRequire(interfaceIndex,tempNeighborInfo))	&& (tempNeighborInfo->state > S_TwoWay))
			{
				// Break possibly fromed adjacency
				Ospfv2DestroyAdjacency(tempNeighborInfo);
				Ospfv2SetNeighborState(interfaceIndex,tempNeighborInfo,S_TwoWay);
			}
			else
			{
				// No action required, no state change
			}

			break;
		}

	case S_BadLSReq:
		{

		}
	case S_SeqNumberMismatch:
		{
			if (tempNeighborInfo->state < S_Exchange)
			{
				break;
			}

			// Torn down possibly formed adjacency
			Ospfv2DestroyAdjacency(tempNeighborInfo);

			Ospfv2SetNeighborState(interfaceIndex,tempNeighborInfo,S_ExStart);
			break;
		}

	case S_OneWay:
		{
			if (tempNeighborInfo->state >= S_TwoWay)
			{
				Ospfv2DestroyAdjacency(tempNeighborInfo);

				Ospfv2SetNeighborState(interfaceIndex,tempNeighborInfo,S_Init);
			}
			break;
		}

	case S_InactivityTimer:
	case S_KillNbr:
	case S_LLDown:
		{

			Ospfv2SetNeighborState(interfaceIndex,tempNeighborInfo,S_NeighborDown);

			Ospfv2RemoveNeighborFromNeighborList(interfaceIndex, nbrAddr);

			break;
		}

	default:
		{
			char errorStr[SNS_MAX_STRING_LENGTH];

			sprintf(errorStr, "Node %u : Unknown neighbor event %d for "
				"neighbor (0x%x).\n",
				Cur_Node_id, eventType, nbrAddr);

			ERROR_Assert(TRUE, errorStr);
		}
	}
}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2HandleHelloPacket
// PURPOSE      :Process received hello packet
// ASSUMPTION   :None
// RETURN VALUE :None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2HandleHelloPacket(Ospfv2HelloPacket* helloPkt,unsigned sourceAddr,int interfaceIndex)
{
	Ospfv2Interface* thisIntf = NULL;
	Ospfv2Area* thisArea = NULL;
	Ospfv2Neighbor* tempNeighborInfo = NULL;
	Ospfv2ListItem* tempListItem = NULL;
	unsigned* tempNeighbor = NULL;
	bool neighborFound;
	int numNeighbor;
	int count;

	unsigned nbrPrevDR = 0;
	unsigned nbrPrevBDR = 0;
	int nbrPrevPriority = 0;

	thisIntf = &ospf->iface[interfaceIndex];

	thisArea = Ospfv2GetArea(thisIntf->areaId);
	ERROR_Assert(!thisArea, "Didn't find specified area\n");

	// The setting of the E-bit found in the Hello Packet's Options
	// field must match this area's ExternalRoutingCapability.

	if (((helloPkt->options && OSPFv2_OPTION_EXTERNAL)
		&& (thisArea->transitCapability == FALSE))
		|| (!(helloPkt->options && OSPFv2_OPTION_EXTERNAL)
		&& (thisArea->transitCapability == TRUE)))
	{
		ERROR_Assert(true,"Option field mismatch. Drop hello packet\n");
		return;
	}

	numNeighbor = (helloPkt->commonHeader.packetLength- sizeof(Ospfv2HelloPacket)) / sizeof(unsigned);

	// Get the neighbor part of the Hello packet.
	tempNeighbor = (unsigned*)(helloPkt + 1);
	ERROR_Assert(!tempNeighbor,"Neighbor part of the Hello packet is not present\n");
	if (OSPFv2_DEBUG_HELLOErr)
	{
		Ospfv2PrintHelloPacket(helloPkt,interfaceIndex);
	}
	// Update my records of my neighbor routers.
	tempListItem = thisIntf->neighborList->first;
	neighborFound = FALSE;

	while (tempListItem)
	{
		tempNeighborInfo = (Ospfv2Neighbor*) tempListItem->data;
		ERROR_Assert(!tempNeighborInfo,"Neighbor not found in the Neighbor list\n");

		if (thisIntf->type == OSPFv2_BROADCAST_INTERFACE
			|| thisIntf->type == OSPFv2_POINT_TO_MULTIPOINT_INTERFACE
			|| thisIntf->type == OSPFv2_NBMA_INTERFACE)
		{
			if (tempNeighborInfo->neighborIPAddress == sourceAddr)
			{
				// The neighbor exists in our neighbor list, so no need to add
				// this neighbor to our neighbor list.
				neighborFound = TRUE;
				break;
			}
		}
		else
		{
			if (tempNeighborInfo->neighborID == helloPkt->commonHeader.routerID)
			{
				// If a point-to-point interface receives packests from
				// two diffrent interfaces of same node which have difrent
				// IP addresses, it should process only one of them.
				// For unnumbered interfaces they would have same IP address
				// so it should treat the packet as if they are coming from
				// same interface.
				if (tempNeighborInfo->neighborIPAddress != sourceAddr)
				{
					return;
				}

				// The neighbor exists in our neighbor list, so no need to add
				// this neighbor to our neighbor list.
				neighborFound = TRUE;
				break;
			}
		}

		tempListItem = tempListItem->next;
	}

	if (neighborFound == FALSE)
	{
		// Neighbor does not exist in my neighbor list,
		// so add the neighbor into my neighbor list.
		tempNeighborInfo = (Ospfv2Neighbor*)malloc(sizeof(Ospfv2Neighbor));

		memset(tempNeighborInfo, 0, sizeof(Ospfv2Neighbor));

		tempNeighborInfo->neighborPriority = helloPkt->rtrPri;
		tempNeighborInfo->neighborID = helloPkt->commonHeader.routerID;
		tempNeighborInfo->neighborIPAddress = sourceAddr;

		// Set neighbor's view of DR and BDR
		tempNeighborInfo->neighborDesignatedRouter =helloPkt->designatedRouter;
		tempNeighborInfo->neighborBackupDesignatedRouter =helloPkt->backupDesignatedRouter;

		// Initializes different lists
		Ospfv2InitList(&tempNeighborInfo->linkStateRetxList);
		Ospfv2InitList(&tempNeighborInfo->DBSummaryList);
		Ospfv2InitList(&tempNeighborInfo->linkStateRequestList);

		Ospfv2InsertToList(thisIntf->neighborList, 0, (void*) tempNeighborInfo);

		ospf->neighborCount++;
	}


	// NBMA mode is not cosidered yet
	if (thisIntf->type == OSPFv2_BROADCAST_INTERFACE|| thisIntf->type == OSPFv2_POINT_TO_MULTIPOINT_INTERFACE)
	{
		// Note changes in field DR, BDR, router priority for
		// possible use in later step.
		nbrPrevDR = tempNeighborInfo->neighborDesignatedRouter;
		nbrPrevBDR = tempNeighborInfo->neighborBackupDesignatedRouter;
		nbrPrevPriority = tempNeighborInfo->neighborPriority;
		tempNeighborInfo->neighborDesignatedRouter= helloPkt->designatedRouter;
		tempNeighborInfo->neighborBackupDesignatedRouter =helloPkt->backupDesignatedRouter;
		tempNeighborInfo->neighborPriority = helloPkt->rtrPri;
	}
		// Handle neighbor event
		Ospfv2HandleNeighborEvent(interfaceIndex,sourceAddr,S_HelloReceived);

		// Check whether this router itself appear in the
		// list of neighbor contained in Hello packet.

		count = 0;

		while (count < numNeighbor)
		{
			unsigned ipAddr;

			memcpy(&ipAddr, (tempNeighbor + count), sizeof(unsigned));

			if (ipAddr == ospf->routerID)
			{
				// Handle neighbor event
				Ospfv2HandleNeighborEvent(interfaceIndex,sourceAddr,S_TwoWayReceived);

				break;
			}
			count++;
		}

		if (count == numNeighbor)
		{
			// Handle neighbor event : S_OneWay
			Ospfv2HandleNeighborEvent(interfaceIndex,sourceAddr,S_OneWay);

			// Stop processing packet further
			return;
		}

	// If a change in the neighbor's Router Priority field was noted,
	// the receiving interface's state machine is scheduled with
	// the event NeighborChange.
	if (nbrPrevPriority != tempNeighborInfo->neighborPriority)
	{
		Ospfv2ScheduleInterfaceEvent(interfaceIndex,E_NeighborChange);
	}

	// If the neighbor is both declaring itself to be Designated Router and
	// the Backup Designated Router field in the packet is equal to 0.0.0.0
	// and the receiving interface is in state Waiting, the receiving
	// interface's state machine is scheduled with the event BackupSeen.
	// Otherwise, if the neighbor is declaring itself to be Designated Router
	// and it had not previously, or the neighbor is not declaring itself
	// Designated Router where it had previously, the receiving interface's
	// state machine is scheduled with the event NeighborChange.

	if ((helloPkt->designatedRouter == tempNeighborInfo->neighborIPAddress)
		&& (helloPkt->backupDesignatedRouter == 0)
		&& (thisIntf->state == S_Waiting))
	{
		Ospfv2ScheduleInterfaceEvent(interfaceIndex,E_BackupSeen);
	}
	else if (((helloPkt->designatedRouter ==
		tempNeighborInfo->neighborIPAddress) &&
		(nbrPrevDR != tempNeighborInfo->neighborIPAddress)) ||
		((helloPkt->designatedRouter != tempNeighborInfo->neighborIPAddress)
		&& (nbrPrevDR == tempNeighborInfo->neighborIPAddress)))
	{
		Ospfv2ScheduleInterfaceEvent(interfaceIndex,E_NeighborChange);
	}

	// If the neighbor is declaring itself to be Backup Designated Router and
	// the receiving interface is in state Waiting, the receiving interface's
	// state machine is scheduled with the event BackupSeen. Otherwise, if
	// neighbor is declaring itself to be Backup Designated Router and it had
	// not previously, or the neighbor is not declaring itself Backup
	// Designated Router where it had previously, the receiving interface's
	// state machine is scheduled with the event NeighborChange.

	if ((helloPkt->backupDesignatedRouter ==
		tempNeighborInfo->neighborIPAddress) &&
		(thisIntf->state == S_Waiting))
	{
		Ospfv2ScheduleInterfaceEvent(interfaceIndex,E_BackupSeen);
	}
	else if (((helloPkt->backupDesignatedRouter ==
		tempNeighborInfo->neighborIPAddress)
		&& (nbrPrevBDR != tempNeighborInfo->neighborIPAddress))
		|| ((helloPkt->backupDesignatedRouter !=
		tempNeighborInfo->neighborIPAddress)
		&& (nbrPrevBDR == tempNeighborInfo->neighborIPAddress)))
	{
		Ospfv2ScheduleInterfaceEvent(interfaceIndex,E_NeighborChange);
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2LookupLSDB()
// PURPOSE      :Search for the LSA in LSDB
// ASSUMPTION   :None
// RETURN VALUE :Ospfv2LinkStateHeader*
//-------------------------------------------------------------------------//

Sns_Model_OSPFv2::Ospfv2LinkStateHeader* Sns_Model_OSPFv2::Ospfv2LookupLSDB(char linkStateType,unsigned advertisingRouter,unsigned linkStateID,int interfaceIndex)
{
	Ospfv2LinkStateHeader* LSHeader = NULL;

	Ospfv2Area* thisArea = NULL;

	// BGP-OSPF Patch Start
	if (linkStateType != OSPFv2_ROUTER_AS_EXTERNAL)
	{
		thisArea = Ospfv2GetArea(ospf->iface[interfaceIndex].areaId);
		ERROR_Assert(!thisArea, "Area doesn't exist\n");
	}
	// BGP-OSPF Patch End

	if (linkStateType == OSPFv2_ROUTER)
	{
		LSHeader =  Ospfv2LookupLSAList(thisArea->routerLSAList,advertisingRouter,linkStateID);
	}
	else if (linkStateType == OSPFv2_NETWORK)
	{
		LSHeader = Ospfv2LookupLSAList(thisArea->networkLSAList,advertisingRouter,linkStateID);
	}
	else if (linkStateType == OSPFv2_NETWORK_SUMMARY)
	{
		LSHeader = Ospfv2LookupLSAList(thisArea->networkSummaryLSAList,advertisingRouter,linkStateID);
	}
	else if (linkStateType == OSPFv2_ROUTER_SUMMARY)
	{
		LSHeader = Ospfv2LookupLSAList(thisArea->routerSummaryLSAList,advertisingRouter,linkStateID);
	}
	// BGP-OSPF Patch Start
	else if (linkStateType == OSPFv2_ROUTER_AS_EXTERNAL)
	{
		LSHeader = Ospfv2LookupLSAList(ospf->asExternalLSAList,advertisingRouter,linkStateID);
	}
	// BGP-OSPF Patch End
	else if (linkStateType == OSPFv2_GROUP_MEMBERSHIP)
	{
		LSHeader = Ospfv2LookupLSAList(thisArea->groupMembershipLSAList,advertisingRouter,linkStateID);
	}
	else
	{
		ERROR_Assert(TRUE, "Unknown LS Type\n");
	}

	return LSHeader;
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2NoNbrInStateExhangeOrLoading()
// PURPOSE      :Verify if any neighbor is in state Exchange or Loading.
// ASSUMPTION   :None.
// RETURN VALUE :BOOL
//-------------------------------------------------------------------------//

bool Sns_Model_OSPFv2::Ospfv2NoNbrInStateExhangeOrLoading(int interfaceIndex)
{
	Ospfv2Neighbor* neighborInfo = NULL;
	Ospfv2ListItem* listItem =ospf->iface[interfaceIndex].neighborList->first;

	while (listItem)
	{
		neighborInfo = (Ospfv2Neighbor*) listItem->data;

		if (neighborInfo->state == S_Exchange
			|| neighborInfo->state == S_Loading)
		{
			return FALSE;
		}
		listItem = listItem->next;
	}

	return TRUE;
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2UpdateLSAList
// PURPOSE      :Receive a LSA via flooding and LS Type has been determined.
//               Update this node's link state database, either router or
//               network or summary LSA. (determined by list that is being
//               passed in in function Ospfv2UpdateLSDB).
// ASSUMPTION   :None
// RETURN VALUE :TRUE if there was an update, FALSE otherwise.
//-------------------------------------------------------------------------//
bool Sns_Model_OSPFv2::Ospfv2UpdateLSAList(int interfaceIndex,Ospfv2List* list,char* LSA,unsigned srcAddr,unsigned int areaId)
{
	Ospfv2LinkStateHeader* listLSHeader = NULL;
	Ospfv2LinkStateHeader* LSHeader = NULL;
	Ospfv2ListItem* listItem = NULL;
	bool retVal = FALSE;
	bool floodedBackToRecvIntf = FALSE;
	LSHeader = (Ospfv2LinkStateHeader*) LSA;

	listItem = list->first;
	while (listItem)
	{
		listLSHeader = (Ospfv2LinkStateHeader*) listItem->data;

		if ((LSHeader->advertisingRouter == listLSHeader->advertisingRouter)
			&& (LSHeader->linkStateID == listLSHeader->linkStateID))
		{
			// RFC2328, Sec-13 (5.a)
			// If there is already a database copy, and if the database copy
			// was received via flooding and installed less than MinLSArrival
			// seconds ago, discard new LSA (without acknowledging it) and
			// examine the next LSA (if any).

			if ((SimClock() - listItem->timeStamp) <(OSPFv2_MIN_LS_ARRIVAL))

			{
				return FALSE;
			}

			break;
		}

		listItem = listItem->next;
	}
	bool dontFlood = FALSE;

	if (!dontFlood)
	{

		// RFC2328, Sec-13 (Bullet - 5.b) & (Bullet - 5.e)
		// Immediately Flood LSA
		if (LSHeader->linkStateType == OSPFv2_ROUTER_AS_EXTERNAL)
		{
			floodedBackToRecvIntf = Ospfv2FloodThroughAS(interfaceIndex, LSA, srcAddr);
		}
		else
		{
			floodedBackToRecvIntf = Ospfv2FloodLSA(interfaceIndex, LSA, srcAddr, areaId);
		}

		if (!floodedBackToRecvIntf)
		{
			if (ospf->iface[interfaceIndex].state == S_Backup)
			{
				if (ospf->iface[interfaceIndex].designatedRouterIPAddress ==srcAddr)
				{
					// Send Delayed Ack
					Ospfv2SendDelayedAck(interfaceIndex, LSA, srcAddr);
				}
			}
			else
			{
				// Send Delayed Ack
				Ospfv2SendDelayedAck(interfaceIndex, LSA, srcAddr);
			}
		}
	}

	// RFC2328, Sec-13 (5.d)
	// Install LSA in LSDB. this may schedule Routing table calculation.

	if (LSHeader->linkStateAge >= (OSPFv2_LSA_MAX_AGE / SECOND))
	{
		// If greater than or equal to max age, remove from LSDB.

		//FIXME: Should remove after
		// a) It is no longer contained in any neighbors
		//    retransmission list
		// b) None of the router's neighbors are in state
		//    Exchange/Loading
		Ospfv2RemoveFromList(list, listItem, FALSE);
		retVal = TRUE;
	}
	else
	{
		retVal = Ospfv2InstallLSAInLSDB(list, LSA);
	}

	return retVal;
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2UpdateLSDB
// PURPOSE      :Receive a LSA via flooding, update this node's LSDB.
// ASSUMPTION   :None.
// RETURN VALUE :TRUE if there was an update, FALSE otherwise.
//-------------------------------------------------------------------------//

bool Sns_Model_OSPFv2::Ospfv2UpdateLSDB(int interfaceIndex,char* LSA,unsigned srcAddr,unsigned areaId)
{
	Ospfv2LinkStateHeader* LSHeader = (Ospfv2LinkStateHeader*) LSA;
	Ospfv2Area* thisArea = NULL;
	bool retVal = FALSE;

	// BGP-OSPF Patch Start
	if (LSHeader->linkStateType != OSPFv2_ROUTER_AS_EXTERNAL)
	{
		thisArea = Ospfv2GetArea(areaId);
		ERROR_Assert(!thisArea, "Doesn't find the area\n");
	}
	// BGP-OSPF Patch End

	// RFC2328 (Sec-13, bullet-5.f)
	// Should take special action if this node is originator.
	if ((LSHeader->advertisingRouter == ospf->routerID)
		|| ((Ospfv2IsMyAddress(LSHeader->linkStateID))
		&& (LSHeader->linkStateType == OSPFv2_NETWORK)))
	{
		// RFC 2328, Sec - 13.4
		// Only check the following case for now:
		// 1) LSA is a summary-LSA and the router no longer has an
		//    (advertisable) route to the destination,
		// 2) LSA is a network-LSA but the router is no longer DR
		//    for the network
		bool flush = FALSE;

		switch (LSHeader->linkStateType)
		{
		case OSPFv2_NETWORK:
			{
				int interfaceIndex = Ospfv2GetInterfaceIndexFromAddress(LSHeader->linkStateID);

				if (ospf->iface[interfaceIndex].state == S_DR)
				{
					retVal = Ospfv2UpdateLSAList(interfaceIndex,thisArea->networkLSAList,LSA,srcAddr,areaId);

					Ospfv2ScheduleNetworkLSA(interfaceIndex, FALSE);
				}
				else
				{
					flush = TRUE;
				}
				break;
			}
		case OSPFv2_NETWORK_SUMMARY:
			{
				unsigned destAddr;
				unsigned addrMask;
				Ospfv2RoutingTableRow* rowPtr;
				int matchType;

				destAddr = LSHeader->linkStateID;
				memcpy(&addrMask, LSHeader + 1, sizeof(unsigned));

				matchType = Ospfv2CheckForSummaryLSAValidity(destAddr,addrMask,OSPFv2_DESTINATION_NETWORK,areaId, &rowPtr);

				if (!matchType)
				{
					flush = TRUE;
				}

				break;
			}
		case OSPFv2_ROUTER:
			{
				retVal = Ospfv2UpdateLSAList(interfaceIndex,thisArea->routerLSAList,LSA,srcAddr,areaId);

				Ospfv2ScheduleRouterLSA(thisArea->areaID, FALSE);

				break;
			}
		default:
			{
				break;
			}
		}

		if (flush)
		{
			Ospfv2FlushLSA(LSA, areaId);

			//FIXME: Should remove after
			// a) It is no longer contained in any neighbors
			// retransmission list
			// b) None of the router's neighbors are in state
			// Exchange/Loading
			Ospfv2RemoveLSAFromLSDB(LSA, areaId);
		}
	}
	else if (LSHeader->linkStateType == OSPFv2_ROUTER)
	{
		retVal = Ospfv2UpdateLSAList(interfaceIndex,thisArea->routerLSAList,LSA,srcAddr,areaId);
	}
	else if (LSHeader->linkStateType == OSPFv2_NETWORK)
	{
		retVal = Ospfv2UpdateLSAList(interfaceIndex,thisArea->networkLSAList,LSA,srcAddr,areaId);
	}
	else if (LSHeader->linkStateType == OSPFv2_NETWORK_SUMMARY)
	{
		retVal = Ospfv2UpdateLSAList(interfaceIndex,thisArea->networkSummaryLSAList,LSA,srcAddr,areaId);
	}
	else if (LSHeader->linkStateType == OSPFv2_ROUTER_SUMMARY)
	{
		retVal = Ospfv2UpdateLSAList(interfaceIndex,thisArea->routerSummaryLSAList,LSA,srcAddr,areaId);
	}
	// BGP-OSPF Patch Start
	else if (LSHeader->linkStateType == OSPFv2_ROUTER_AS_EXTERNAL)
	{
		retVal =  Ospfv2UpdateLSAList(interfaceIndex,ospf->asExternalLSAList,LSA,srcAddr,areaId);
	}
	// BGP-OSPF Patch End
	else if (LSHeader->linkStateType == OSPFv2_GROUP_MEMBERSHIP)
	{
		retVal =  Ospfv2UpdateLSAList(interfaceIndex,thisArea->groupMembershipLSAList,LSA,srcAddr,areaId);
	}
	else
	{
		ERROR_Assert(TRUE, "LS Type not known. Can't update LSDB\n");
	}

	return retVal;
}


//-------------------------------------------------------------------------//
// NAME         :Ospfv2SendDelayedAck()
// PURPOSE      :Send Delayed Ack
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2SendDelayedAck(int interfaceIndex, char* LSA, unsigned nbrAddr)
{
	Ospfv2LinkStateHeader* LSHeader = (Ospfv2LinkStateHeader*)malloc(sizeof(Ospfv2LinkStateHeader));

	memcpy(LSHeader, LSA, sizeof(Ospfv2LinkStateHeader));

	Ospfv2InsertToList(ospf->iface[interfaceIndex].delayedAckList,SimClock(),(void*) LSHeader);

	// Set Delayed Ack timer, if not set yet
	if (ospf->iface[interfaceIndex].delayedAckTimer == FALSE)
	{
		Sns_Message* delayedAckMsg = new Sns_Message;
		clocktype delay;
		delayedAckMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_InEVENT_OspfDelayedAckTimer,SNS_MSG_INPUT,NULL,0);
		delayedAckMsg->SNS_Msg_AddInfo((char*)&interfaceIndex,sizeof(int));
		ospf->iface[interfaceIndex].delayedAckTimer = TRUE;

		// Interval between delayed transmission must be less than
		// RxmtInterval
		delay = (clocktype)((Get_rand() *  OSPFv2_RXMT_INTERVAL) / 2);

		// Set Timer
		Scenarios_Data->SNS_Msg_Send(delayedAckMsg,Cur_Node_id,delay);
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2SendUpdatePacket()
// PURPOSE      :Send LS Updated packet to neighbor
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2SendUpdatePacket(unsigned dstAddr,int interfaceIndex,char* payload,int payloadSize,int LSACount)
{
	unsigned nextHop;
	Sns_Message* updateMsg=new Sns_Message;
	Ospfv2LinkStateUpdatePacket* updatePkt = (Ospfv2LinkStateUpdatePacket*)malloc(sizeof(Ospfv2LinkStateUpdatePacket)+ payloadSize);

	// Fill in the header fields for the Update packet
	Ospfv2CreateCommonHeader(&updatePkt->commonHeader,OSPFv2_LINK_STATE_UPDATE);

	updatePkt->commonHeader.packetLength = (short)(sizeof(Ospfv2LinkStateUpdatePacket)+ payloadSize);

	updatePkt->commonHeader.areaID = ospf->iface[interfaceIndex].areaId;

	updatePkt->numLSA = LSACount;

	// Add payload
	memcpy(updatePkt + 1, payload, payloadSize);

	if (dstAddr == OSPFv2_ALL_SPF_ROUTERS|| dstAddr == OSPFv2_ALL_D_ROUTERS)
	{
		nextHop = ANY_DEST;
	}
	else
	{
		// Sanity checking
		//ERROR_Assert(!NetworkIpIsMulticastAddress(node, dstAddr),"Destination address is not valid\n");
		nextHop = dstAddr;
	}

	// Send Update packet
	NetworkToMACInfo* info=new NetworkToMACInfo;
	info->dstAddr=dstAddr;
	info->nexthopaddr=nextHop;
	info->interfaceIndex=interfaceIndex;
	info->srcAddr=ospf->iface[interfaceIndex].address;
	updateMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_OutEVENT_OSPFv2_toNetworkIP,SNS_MSG_OUTPUT,(char*)updatePkt,sizeof(Ospfv2LinkStateUpdatePacket)+ payloadSize);
	updateMsg->SNS_Msg_AddInfo((char*)info,sizeof(NetworkToMACInfo));
	Scenarios_Data->SNS_Msg_Send(updateMsg,Cur_Node_id,0);
	//NetworkIpSendRawMessageToMacLayer(
	//	node,
	//	updateMsg,
	//	NetworkIpGetInterfaceAddress(node, interfaceIndex),
	//	dstAddr,
	//	IPTOS_PREC_INTERNETCONTROL,
	//	IPPROTO_OSPF,
	//	1,
	//	interfaceIndex,
	//	nextHop);
	xdelete(info);
	ospf->stats.numLSUpdateSent++;

	////****!!!!
	xfree( updatePkt ) ;


}


//-------------------------------------------------------------------------//
// NAME         :Ospfv2SendAckPacket
// PURPOSE      :Creates acknowledgement packet and send back to source.
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2SendAckPacket(char* payload,int count,unsigned dstAddr,int interfaceIndex)
{
	clocktype delay;

	int size;
	unsigned nextHop = ANY_DEST;

	if (count == 0)
	{
		return;
	}

	size = sizeof(Ospfv2LinkStateAckPacket)+ sizeof(Ospfv2LinkStateHeader)*  count;
	Sns_Message* ackMsg=new Sns_Message;
	Ospfv2LinkStateAckPacket* ackPkt = (Ospfv2LinkStateAckPacket*)malloc(size);

	// Copy LSA header to acknowledge packet.
	// This is how we acknowledged the LSA.

	memcpy(ackPkt + 1,payload,sizeof(Ospfv2LinkStateHeader) * count);

	Ospfv2CreateCommonHeader(&(ackPkt->commonHeader),OSPFv2_LINK_STATE_ACK);

	ackPkt->commonHeader.packetLength = (short) size;
	ackPkt->commonHeader.areaID = ospf->iface[interfaceIndex].areaId;

	ospf->stats.numAckSent++;

	//Trace sending pkt

	delay = 0;

	if (dstAddr == OSPFv2_ALL_SPF_ROUTERS|| dstAddr == OSPFv2_ALL_D_ROUTERS)
	{
		nextHop = ANY_DEST;
	}
	else
	{
		// Sanity checking
		//ERROR_Assert(!NetworkIpIsMulticastAddress(node, dstAddr),
		//	"Destination address is not valid\n");
		nextHop = dstAddr;
	}

	ackMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_OutEVENT_OSPFv2_toNetworkIP,SNS_MSG_OUTPUT,(char*)ackPkt,size);
	NetworkToMACInfo* info=new NetworkToMACInfo;
	info->dstAddr=dstAddr;
	info->nexthopaddr=nextHop;
	info->interfaceIndex=interfaceIndex;
	info->srcAddr=ospf->iface[interfaceIndex].address;
	ackMsg->SNS_Msg_AddInfo((char*)info,sizeof(NetworkToMACInfo));
	Scenarios_Data->SNS_Msg_Send(ackMsg,Cur_Node_id,delay);
	xdelete(info);
	// Send out the ACK
	//NetworkIpSendRawMessageToMacLayerWithDelay(
	//	node,
	//	ackMsg,
	//	NetworkIpGetInterfaceAddress(node,
	//	interfaceIndex),
	//	dstAddr,
	//	IPTOS_PREC_INTERNETCONTROL,
	//	IPPROTO_OSPF,
	//	1,
	//	interfaceIndex,
	//	nextHop,
	//	delay);

	////****!!!!

//	xfree( payload ) ;


	////****!!!!
	xfree( ackPkt ) ;


}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2SendDirectAck()
// PURPOSE      :Send Direct Ack to a neighbor
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2SendDirectAck(int interfaceIndex,Ospfv2List* ackList,unsigned nbrAddr)
{
	Ospfv2ListItem* listItem = NULL;
	int count = 0;
	Ospfv2LinkStateHeader* payload = NULL;
	int maxCount;

	//  ERROR_Assert(interfaceIndex != -1, "No Interface for Neighbor!!\n");

	maxCount =(MAX_NW_PKT_SIZE- sizeof(IpHeaderType)- sizeof(Ospfv2LinkStateAckPacket))/ sizeof(Ospfv2LinkStateHeader);

	payload = (Ospfv2LinkStateHeader*)malloc(maxCount * sizeof(Ospfv2LinkStateHeader));

	while (!Ospfv2ListIsEmpty(ackList))
	{
		listItem = ackList->first;

		if (count == maxCount)
		{
			Ospfv2SendAckPacket((char*) payload, count, nbrAddr, interfaceIndex);

			// Reset variables
			count = 0;
			continue;
		}

		memcpy(&payload[count],listItem->data,sizeof(Ospfv2LinkStateHeader));

		count++;

		// Remove item from list
		Ospfv2RemoveFromList(ackList, listItem, FALSE);
	}

	Ospfv2SendAckPacket((char*)payload,count,nbrAddr,interfaceIndex);

	xfree(payload);
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2RequestedLSAReceived()
// PURPOSE      :Check whether requested LSA(s) has been received
// ASSUMPTION   :None
// RETURN VALUE :TRUE if received, FALSE otherwise
//-------------------------------------------------------------------------//

bool Sns_Model_OSPFv2::Ospfv2RequestedLSAReceived(Ospfv2Neighbor* nbrInfo)
{
	// Requests are sent from top of the list. So it's sufficient
	// to check only first element of the list
	Ospfv2LSReqItem* itemInfo = (Ospfv2LSReqItem*)nbrInfo->linkStateRequestList->first->data;

	ERROR_Assert(itemInfo->seqNumber > nbrInfo->LSReqTimerSequenceNumber,"LS Request not handled properly\n");

	if (itemInfo->seqNumber == nbrInfo->LSReqTimerSequenceNumber)
	{
		return FALSE;
	}

	return TRUE;
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2HandleUpdatePacket
// PURPOSE      :Just received Update packet, so handle appropriately.
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2HandleUpdatePacket(Sns_Message* msg,unsigned sourceAddr,int interfaceIndex)
{
	Ospfv2Area* thisArea = Ospfv2GetArea(ospf->iface[interfaceIndex].areaId);
	Ospfv2LinkStateHeader* LSHeader = NULL;
	Ospfv2LinkStateUpdatePacket* updatePkt = NULL;
	Ospfv2Neighbor* nbrInfo = NULL;
	int count;
	bool isLSDBChanged = FALSE;
	int moreRecentIndicator = 0;
	Ospfv2List* directAckList = NULL;

	nbrInfo = Ospfv2GetNeighborInfoByIPAddress(interfaceIndex, sourceAddr);

	if (nbrInfo == NULL)
	{
		return;
	}

	if (nbrInfo->state < S_Exchange)
	{
		return;
	}
	updatePkt = (Ospfv2LinkStateUpdatePacket*) msg->Pay_Load;
	LSHeader = (Ospfv2LinkStateHeader*) (updatePkt + 1);

	Ospfv2InitList(&directAckList);

	// Execute following steps for each LSA
	for (count = 0; count < updatePkt->numLSA; count++,LSHeader = (Ospfv2LinkStateHeader*)(((char*) LSHeader) + LSHeader->length))
	{
		Ospfv2LinkStateHeader* oldLSHeader;

		// RFC 2328 Sec-13 (2): Validate LSA's LS Type
		if (LSHeader->linkStateType < OSPFv2_ROUTER
			|| LSHeader->linkStateType > OSPFv2_GROUP_MEMBERSHIP)
		{
			continue;
		}

		// RFC 2328 Sec-13 (3): AS-External LSA shouldn't flooded throughout
		// stub area
		if ((LSHeader->linkStateType == OSPFv2_ROUTER_AS_EXTERNAL)
			&& (thisArea->transitCapability == FALSE))
		{
			continue;
		}

		// Find instance of this LSA contained in local database
		oldLSHeader = Ospfv2LookupLSDB(LSHeader->linkStateType,LSHeader->advertisingRouter,LSHeader->linkStateID,interfaceIndex);

		// RFC 2328 Sec-13 (4)
		if ((LSHeader->linkStateAge == (OSPFv2_LSA_MAX_AGE / SECOND))
			&& (!oldLSHeader)
			&& (Ospfv2NoNbrInStateExhangeOrLoading(interfaceIndex)))
		{
			void* ackLSHeader = NULL;

			ackLSHeader = malloc(sizeof(Ospfv2LinkStateHeader));
			memcpy(ackLSHeader, LSHeader, sizeof(Ospfv2LinkStateHeader));
			Ospfv2InsertToList(directAckList, 0, ackLSHeader);

			continue;
		}

		if (oldLSHeader)
		{
			moreRecentIndicator = Ospfv2CompareLSA(LSHeader,oldLSHeader);
		}
		// RFC 2328 Sec-13 (5)
		if ((!oldLSHeader)
			|| (moreRecentIndicator > 0))
		{
			// Update our link state database, if applicable.
			if (Ospfv2UpdateLSDB(interfaceIndex,(char*) LSHeader,sourceAddr,thisArea->areaID))
			{
				isLSDBChanged = TRUE;
			}

			continue;
		}

		// RFC 2328 Sec-13 (6)
		if (Ospfv2SearchRequestList(nbrInfo->linkStateRequestList,LSHeader))
		{
			Ospfv2HandleNeighborEvent(interfaceIndex,nbrInfo->neighborIPAddress,S_BadLSReq);

			Ospfv2FreeList(directAckList, FALSE);

			return;
		}

		// RFC 2328 Sec-13 (7)
		if (moreRecentIndicator == 0)
		{
			Ospfv2ListItem* listItem;
			listItem = nbrInfo->linkStateRetxList->first;

			while (listItem)
			{
				Ospfv2LinkStateHeader* retxLSHeader;

				retxLSHeader = (Ospfv2LinkStateHeader*)
					listItem->data;

				// If LSA exists in retransmission list
				if ((LSHeader->linkStateType == retxLSHeader->linkStateType)
					&& (LSHeader->advertisingRouter ==retxLSHeader->advertisingRouter)
					&& (LSHeader->linkStateID == retxLSHeader->linkStateID))
				{
					break;
				}

				listItem = listItem->next;
			}

			if (listItem)
			{
				// Treat received LSA as implied Ack and
				// remove LSA From LSRetx List
				Ospfv2RemoveFromList(nbrInfo->linkStateRetxList,listItem,FALSE);

				if (Ospfv2ListIsEmpty(nbrInfo->linkStateRetxList))
				{
					nbrInfo->LSRetxTimer = FALSE;
					nbrInfo->rxmtTimerSequenceNumber++;
				}

				if ((ospf->iface[interfaceIndex].state == S_Backup)
					&& (ospf->iface[interfaceIndex].designatedRouterIPAddress == sourceAddr))
				{

					// Send Delayed ack
					Ospfv2SendDelayedAck(interfaceIndex,(char*) LSHeader,sourceAddr);
				}
			}
			else
			{
				void* ackLSHeader = malloc(sizeof(Ospfv2LinkStateHeader));
				memcpy(ackLSHeader,LSHeader,sizeof(Ospfv2LinkStateHeader));
				Ospfv2InsertToList(directAckList,0,ackLSHeader);
			}
			continue;
		}

		// RFC 2328 Sec-13 (8)
		if (moreRecentIndicator < 0)
		{
			if ((oldLSHeader->linkStateAge ==(OSPFv2_LSA_MAX_AGE / SECOND))
				&& (oldLSHeader->linkStateSequenceNumber ==(signed int) OSPFv2_MAX_SEQUENCE_NUMBER))
			{
				// Discard LSA without acknowledging
			}
			else
			{
				Ospfv2ListItem* listItem = NULL;
				Ospfv2LinkStateHeader* retxLSHeader = NULL;

				// Send Database copy to neighbor as long as it has not
				// been sent within last MinLSArrival seconds.

				listItem = nbrInfo->linkStateRetxList->first;

				while (listItem)
				{
					retxLSHeader = (Ospfv2LinkStateHeader*)
						listItem->data;

					// If LSA exists in retransmission list
					if ((LSHeader->linkStateType ==
						retxLSHeader->linkStateType) &&
						(LSHeader->advertisingRouter ==
						retxLSHeader->advertisingRouter) &&
						(LSHeader->linkStateID == retxLSHeader->linkStateID))
					{
						break;
					}

					listItem = listItem->next;
				}

				if ((listItem)&& (SimClock() - listItem->timeStamp>OSPFv2_MIN_LS_ARRIVAL))
				{
					Ospfv2SendUpdatePacket(sourceAddr,interfaceIndex,(char*) oldLSHeader,oldLSHeader->length,1);
				}
			}
		}
	}

	if (!Ospfv2ListIsEmpty(directAckList))
	{
		Ospfv2SendDirectAck(interfaceIndex, directAckList, sourceAddr);
	}

	Ospfv2FreeList(directAckList, FALSE);

	if (isLSDBChanged == TRUE)
	{
		// Calculate shortest path as contents of LSDB has changed.
		Ospfv2ScheduleSPFCalculation();
	}


	if (!Ospfv2ListIsEmpty(nbrInfo->linkStateRequestList))
	{
		// If we've got the desired LSA(s), send next request
		if (Ospfv2RequestedLSAReceived(nbrInfo))
		{
			// Send next LS request
			Ospfv2SendLSRequestPacket(sourceAddr,interfaceIndex,FALSE);
		}
	}
	else
	{
		// Cancel retransmission timer
		nbrInfo->LSReqTimerSequenceNumber += 1;

		Ospfv2HandleNeighborEvent(interfaceIndex,sourceAddr,S_LoadingDone);
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2HandleAckPacket
// PURPOSE      :Removes the LSA being acknowledged from the retx list.
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2HandleAckPacket(Ospfv2LinkStateAckPacket* ackPkt,unsigned sourceAddr,int interfaceIndex)
{
	Ospfv2ListItem* listItem = NULL;
	Ospfv2Neighbor* neighborInfo =Ospfv2GetNeighborInfoByIPAddress(interfaceIndex, sourceAddr);
	Ospfv2LinkStateHeader* LSHeader = NULL;
	int numAck;
	int count;

	// Neighbor no longer exists, so do nothing.
	if (neighborInfo == NULL)
	{
		return;
	}

	if (neighborInfo->state < S_Exchange)
	{
		return;
	}

	numAck = (ackPkt->commonHeader.packetLength	- sizeof(Ospfv2LinkStateAckPacket))	/ sizeof(Ospfv2LinkStateHeader);

	LSHeader = (Ospfv2LinkStateHeader*) (ackPkt + 1);

	for (count = 0; count < numAck; count++, LSHeader = LSHeader + 1)
	{
		listItem = neighborInfo->linkStateRetxList->first;

		while (listItem)
		{
			Ospfv2LinkStateHeader* retxLSHeader =(Ospfv2LinkStateHeader*) listItem->data;

			// If LSA exists in retransmission list
			if ((LSHeader->linkStateType == retxLSHeader->linkStateType)
				&& (LSHeader->advertisingRouter ==retxLSHeader->advertisingRouter)
				&& (LSHeader->linkStateID == retxLSHeader->linkStateID)
				&& (!Ospfv2CompareLSA(LSHeader, retxLSHeader)))
			{
				Ospfv2RemoveFromList(neighborInfo->linkStateRetxList,listItem,FALSE);
				break;
			}

			listItem = listItem->next;
		}
	}

	if ((Ospfv2ListIsEmpty(neighborInfo->linkStateRetxList))
		&& (neighborInfo->LSRetxTimer == TRUE))
	{
		neighborInfo->LSRetxTimer = FALSE;
		neighborInfo->rxmtTimerSequenceNumber++;
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2AddToRequestList()
// PURPOSE      :Add this LSA in Link State Request list
// ASSUMPTION   :None
// RETURN VALUE :NULL
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2AddToRequestList(Ospfv2List* linkStateRequestList,Ospfv2LinkStateHeader* LSHeader)
{

	Ospfv2LSReqItem* newItem = NULL;

	// Create new item to insert to list
	newItem = (Ospfv2LSReqItem *) malloc(sizeof(Ospfv2LSReqItem));

	newItem->LSHeader = (Ospfv2LinkStateHeader*)malloc(sizeof(Ospfv2LinkStateHeader));
	memcpy(newItem->LSHeader, LSHeader, sizeof(Ospfv2LinkStateHeader));

	newItem->seqNumber = 0;

	Ospfv2InsertToList(linkStateRequestList,0, (void*) newItem);
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2ScheduleNeighborEvent
// PURPOSE: Schedule a neighbor event to be executed later. Primary
//          objective is to call Ospfv2HandleNeighborEvent() asynchronously
// RETURN: None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2ScheduleNeighborEvent(int interfaceIndex,unsigned nbrAddr,Ospfv2NeighborEvent nbrEvent)
{
	Ospfv2NSMTimerInfo* NSMTimerInfo=new Ospfv2NSMTimerInfo;
	NSMTimerInfo->interfaceIndex = interfaceIndex;
	NSMTimerInfo->nbrAddr = nbrAddr;
	NSMTimerInfo->nbrEvent = nbrEvent;
	Sns_Message* newMsg=new Sns_Message;
	newMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_InEVENT_OspfNeighborEvent,SNS_MSG_INPUT,NULL,0);
	newMsg->SNS_Msg_AddInfo((char*)NSMTimerInfo,sizeof(Ospfv2NSMTimerInfo));
	clocktype delay = OSPFv2_EVENT_SCHEDULING_DELAY;
	Scenarios_Data->SNS_Msg_Send(newMsg,Cur_Node_id,delay);
	xdelete(NSMTimerInfo);
}


//-------------------------------------------------------------------------//
// NAME         :Ospfv2ProcessDatabaseDescriptionPacket()
// PURPOSE      :Process rest of the database description packet
// ASSUMPTION   :None
// RETURN VALUE :Null
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2ProcessDatabaseDescriptionPacket(Sns_Message* msg,unsigned srcAddr,int interfaceIndex)
{
	Ospfv2Area* thisArea = Ospfv2GetArea(ospf->iface[interfaceIndex].areaId);
	Ospfv2Neighbor* nbrInfo = NULL;
	Ospfv2DatabaseDescriptionPacket* dbDscrpPkt = NULL;
	Ospfv2LinkStateHeader* LSHeader = NULL;
	int size;

	// Find neighbor structure
	nbrInfo = Ospfv2GetNeighborInfoByIPAddress(interfaceIndex, srcAddr);
	ERROR_Assert(!nbrInfo, "Neighbor not found in the Neighbor list");

	dbDscrpPkt = (Ospfv2DatabaseDescriptionPacket*)msg->Pay_Load;

	LSHeader = (Ospfv2LinkStateHeader*) (dbDscrpPkt + 1);
	size = dbDscrpPkt->commonHeader.packetLength;

	// For each LSA in the packet
	for (size -= sizeof(Ospfv2DatabaseDescriptionPacket); size > 0;size -= sizeof(Ospfv2LinkStateHeader))
	{
		Ospfv2LinkStateHeader* oldLSHeader = NULL;

		// Check for the validity of LSA
		if (LSHeader->linkStateType < OSPFv2_ROUTER|| LSHeader->linkStateType > OSPFv2_GROUP_MEMBERSHIP)
		{
			// Handle neighbor event : Sequence Number Mismatch
			Ospfv2HandleNeighborEvent(interfaceIndex,srcAddr,S_SeqNumberMismatch);
			return;
		}

		// Stop processing packet if the neighbor is associated with stub
		// area and the LSA is AS-EXTERNAL-LAS

		if (LSHeader->linkStateType == OSPFv2_ROUTER_AS_EXTERNAL&& thisArea->transitCapability == FALSE)
		{
			// Handle neighbor event : Sequence Number Mismatch
			Ospfv2HandleNeighborEvent(interfaceIndex,srcAddr,S_SeqNumberMismatch);
			return;
		}

		// Looks up for the LSA in its own Database
		oldLSHeader = Ospfv2LookupLSDB(LSHeader->linkStateType,LSHeader->advertisingRouter,LSHeader->linkStateID,interfaceIndex);

		// Add to request list if the LSA doesn't exist or if
		// this instance is more recent one

		if (!oldLSHeader|| (Ospfv2CompareLSA(LSHeader, oldLSHeader) > 0))
		{
			Ospfv2AddToRequestList(nbrInfo->linkStateRequestList,LSHeader);
		}
		LSHeader += 1;
	}

	// Master
	if (nbrInfo->masterSlave == T_Master)
	{
		nbrInfo->DDSequenceNumber++;

		// If the router has already sent its entire sequence of DD packets,
		// and the just accepted packet has the more bit (M) set to 0, the
		// neighbor event ExchangeDone is generated.

		if ((Ospfv2ListIsEmpty(nbrInfo->DBSummaryList))
			&& (!Ospfv2DatabaseDescriptionPacketGetMore(dbDscrpPkt->ospfDbDp)))
		{
			Ospfv2ScheduleNeighborEvent(interfaceIndex,srcAddr,S_ExchangeDone);
		}
		// Else send new DD packet.
		else
		{
			Ospfv2SendDatabaseDescriptionPacket(srcAddr,interfaceIndex);
		}
	}
	// Slave
	else
	{
		nbrInfo->DDSequenceNumber = dbDscrpPkt->ddSequenceNumber;

		// Send DD packet
		Ospfv2SendDatabaseDescriptionPacket(srcAddr,interfaceIndex);

		if (!(Ospfv2DatabaseDescriptionPacketGetMore(dbDscrpPkt->ospfDbDp))
			&& Ospfv2ListIsEmpty(nbrInfo->DBSummaryList))
		{

			Ospfv2ScheduleNeighborEvent(interfaceIndex,srcAddr,S_ExchangeDone);
		}
	}

	// Save received DD Packet
	if (!nbrInfo->lastReceivedDDPacket)
	{
		nbrInfo->lastReceivedDDPacket = msg->SNS_Msg_Copy();
	}
	else
	{
		xfree(nbrInfo->lastReceivedDDPacket);
		nbrInfo->lastReceivedDDPacket = msg->SNS_Msg_Copy();
	}

	////****!!!!
	xdelete( nbrInfo->lastReceivedDDPacket ) ;
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2HandleDatabaseDescriptionPacket()
// PURPOSE      :Handle database description packet
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2HandleDatabaseDescriptionPacket(Sns_Message* msg,unsigned srcAddr,int interfaceIndex)
{
	Ospfv2Neighbor* nbrInfo = NULL;
	Ospfv2DatabaseDescriptionPacket* dbDscrpPkt = NULL;
	bool isDuplicate = FALSE;
	Ospfv2DatabaseDescriptionPacket* oldPkt = NULL;

	// Find neighbor structure
	nbrInfo = Ospfv2GetNeighborInfoByIPAddress(interfaceIndex, srcAddr);

	if (!nbrInfo)
	{
		return;
	}

	dbDscrpPkt = (Ospfv2DatabaseDescriptionPacket*)msg->Pay_Load;

	// Check if two consecutive DD packets are same
	if (nbrInfo->lastReceivedDDPacket != NULL)
	{
		oldPkt = (Ospfv2DatabaseDescriptionPacket*)nbrInfo->lastReceivedDDPacket->Pay_Load;

		if ((Ospfv2DatabaseDescriptionPacketGetInit(oldPkt->ospfDbDp) ==Ospfv2DatabaseDescriptionPacketGetInit(dbDscrpPkt->ospfDbDp))
			&& (Ospfv2DatabaseDescriptionPacketGetMore(oldPkt->ospfDbDp) ==Ospfv2DatabaseDescriptionPacketGetMore(dbDscrpPkt->ospfDbDp))
			&& (Ospfv2DatabaseDescriptionPacketGetMS(oldPkt->ospfDbDp) ==Ospfv2DatabaseDescriptionPacketGetMS(dbDscrpPkt->ospfDbDp))
			&& (oldPkt->ddSequenceNumber == dbDscrpPkt->ddSequenceNumber)
			&& (oldPkt->reserved1 == dbDscrpPkt->reserved1))
		{
			isDuplicate = TRUE;
		}
	}

	switch (nbrInfo->state)
	{
		// Reject packet if neighbor state is Down or Attempt or 2-Way
	case S_NeighborDown:
	case S_Attempt:
	case S_TwoWay:
		{
			break;
		}

	case S_Init:
		{

			// Handle neighbor event : 2-Way receive
			Ospfv2HandleNeighborEvent(interfaceIndex,srcAddr,S_TwoWayReceived);
			if (nbrInfo->state != S_ExStart)
			{
				break;
			}
			else
			{
				// Otherwise, falls through to case S_ExStart below
			}
		}

        case S_ExStart:
			{
					// Slave
					if ((Ospfv2DatabaseDescriptionPacketGetInit(dbDscrpPkt->ospfDbDp))
						&& (Ospfv2DatabaseDescriptionPacketGetMore(dbDscrpPkt->ospfDbDp))
						&& (Ospfv2DatabaseDescriptionPacketGetMS(dbDscrpPkt->ospfDbDp))
						&& (dbDscrpPkt->commonHeader.packetLength ==sizeof(Ospfv2DatabaseDescriptionPacket))
						&& (dbDscrpPkt->commonHeader.routerID > ospf->routerID))
					{
						nbrInfo->masterSlave = T_Slave;
						nbrInfo->DDSequenceNumber = dbDscrpPkt->ddSequenceNumber;
					}
					// Master
					else if ((!(Ospfv2DatabaseDescriptionPacketGetInit(dbDscrpPkt->ospfDbDp)))
						&& (!(Ospfv2DatabaseDescriptionPacketGetMS(dbDscrpPkt->ospfDbDp)))
						&& (dbDscrpPkt->ddSequenceNumber ==nbrInfo->DDSequenceNumber)
						&& (dbDscrpPkt->commonHeader.routerID < ospf->routerID))
					{
						nbrInfo->masterSlave = T_Master;
					}
					// Cannot determine Master or Slave, so discard packet
					else
					{
						break;
					}
				// Handle neighbor event : Negotiation Done
				Ospfv2HandleNeighborEvent(interfaceIndex,srcAddr,S_NegotiationDone);

				// Process rest of the DD packet
				Ospfv2ProcessDatabaseDescriptionPacket(msg,srcAddr,interfaceIndex);

				break;
			}

		case S_Exchange:
			{
				// Check if the packet is duplicate
				if (isDuplicate)
				{
					// Master
					if (nbrInfo->masterSlave == T_Master)
					{
						// Discard packet
					}

					// Slave
					else
					{
						ERROR_Assert(!nbrInfo->lastSentDDPkt,"No packet to retx\n");

						//Trace sending pkt

						// This packet needs to be retransmitted,
						// so send it out again.
						Scenarios_Data->SNS_Msg_Send(nbrInfo->lastSentDDPkt->SNS_Msg_Copy(),Cur_Node_id,0);

						////****!!!!

						xdelete( nbrInfo->lastSentDDPkt ) ;




						//NetworkIpSendRawMessageToMacLayer(
						//	node,
						//	MESSAGE_Duplicate(node, nbrInfo->lastSentDDPkt),
						//	NetworkIpGetInterfaceAddress(node, interfaceIndex),
						//	nbrInfo->neighborIPAddress,
						//	IPTOS_PREC_INTERNETCONTROL,
						//	IPPROTO_OSPF,
						//	1,
						//	interfaceIndex,
						//	nbrInfo->neighborIPAddress);
					}

					break;
				}

				// Check for Master-Slave mismatch
				if (((nbrInfo->masterSlave == T_Master)
					&& (Ospfv2DatabaseDescriptionPacketGetMS(dbDscrpPkt->ospfDbDp)))
					|| ((nbrInfo->masterSlave == T_Slave)
					&& (!(Ospfv2DatabaseDescriptionPacketGetMS(dbDscrpPkt->ospfDbDp)))))
				{
					// Handle neighbor event : Sequence Number Mismatch
					Ospfv2HandleNeighborEvent(interfaceIndex,srcAddr,S_SeqNumberMismatch);

					// Stop processing packet
					break;
				}

				// Check if initialization bit is set
				if ((Ospfv2DatabaseDescriptionPacketGetInit(dbDscrpPkt->ospfDbDp)))
				{
					// Handle neighbor event : Sequence Number Mismatch
					Ospfv2HandleNeighborEvent(interfaceIndex,srcAddr,S_SeqNumberMismatch);

					// Stop processing packet
					break;
				}

				// If neighbor option have been changed.
				if ((oldPkt) && (dbDscrpPkt->reserved1 != oldPkt->reserved1))
				{
					// Handle neighbor event : Sequence Number Mismatch
					Ospfv2HandleNeighborEvent(interfaceIndex,srcAddr,S_SeqNumberMismatch);

					// Stop processing packet
					break;
				}

				// Check DD Sequence number
				if (((nbrInfo->masterSlave == T_Master)
					&& (dbDscrpPkt->ddSequenceNumber !=	nbrInfo->DDSequenceNumber))
					|| ((nbrInfo->masterSlave == T_Slave)
					&& (dbDscrpPkt->ddSequenceNumber !=	nbrInfo->DDSequenceNumber + 1)))
				{
					// Handle neighbor event : Sequence Number Mismatch
					Ospfv2HandleNeighborEvent(interfaceIndex,srcAddr,S_SeqNumberMismatch);

					// Stop processing packet
					break;
				}

				// Process rest of the packet
				Ospfv2ProcessDatabaseDescriptionPacket(msg,srcAddr,interfaceIndex);

				break;
			}

		case S_Loading:
		case S_Full:
			{
				if (isDuplicate)
				{
					// Master discards duplicate packet
					if (nbrInfo->masterSlave == T_Master)
					{
						// Discard packet
						break;
					}
					else
					{
						// In states Loading and Full the slave must resend its
						// last Database Description packet in response to
						// duplicate Database Description packets received from
						// the master.For this reason the slave must wait
						// RouterDeadInterval seconds before freeing the last
						// Database Description packet. Reception of a Database
						// Description packet from the master after this interval
						// will generate a SeqNumberMismatch neighbor event.

						if (SimClock() - nbrInfo->lastDDPktSent <ospf->iface[interfaceIndex].routerDeadInterval)
						{
							ERROR_Assert(!nbrInfo->lastSentDDPkt,"No packet to retx\n");

							// Retransmit packet
							Scenarios_Data->SNS_Msg_Send(nbrInfo->lastSentDDPkt->SNS_Msg_Copy(),Cur_Node_id,0);

							////****!!!!
							xdelete( nbrInfo->lastSentDDPkt ) ;

							//NetworkIpSendRawMessageToMacLayer(
							//	node,
							//	MESSAGE_Duplicate(node, nbrInfo->lastSentDDPkt),
							//	NetworkIpGetInterfaceAddress(node,
							//	interfaceIndex),
							//	nbrInfo->neighborIPAddress,
							//	IPTOS_PREC_INTERNETCONTROL,
							//	IPPROTO_OSPF,
							//	1,
							//	interfaceIndex,
							//	nbrInfo->neighborIPAddress);

							break;
						}
					}
				}

				// Handle neighbor event : Sequence Number Mismatch
				Ospfv2HandleNeighborEvent(interfaceIndex,srcAddr,S_SeqNumberMismatch);
				break;
			}

		default:
			{
				ERROR_Assert(TRUE, "Unknown neighbor state\n");
			}
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2SendLSUpdate()
// PURPOSE      :Send Updated LSA to neighbor
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2SendLSUpdate(unsigned nbrAddr, int interfaceIndex)
{
	Ospfv2Interface* thisInterface = &ospf->iface[interfaceIndex];

	Ospfv2ListItem* listItem = NULL;
	Ospfv2LinkStateHeader* LSHeader = NULL;
	unsigned dstAddr;

	char* payloadBuff = NULL;
	int maxPayloadSize;
	int payloadSize;
	int count;

	if (Ospfv2ListIsEmpty(thisInterface->updateLSAList))
	{
		return;
	}

	// Determine Destination Address
		if ((thisInterface->state == S_DR) || (thisInterface->state == S_Backup))
		{
			dstAddr = OSPFv2_ALL_SPF_ROUTERS;
		}
		else if (thisInterface->type == OSPFv2_BROADCAST_INTERFACE)
		{
			dstAddr = OSPFv2_ALL_D_ROUTERS;
		}
		else if (thisInterface->type == OSPFv2_POINT_TO_POINT_INTERFACE)
		{
			dstAddr = OSPFv2_ALL_SPF_ROUTERS;
		}
		else
		{
			dstAddr = nbrAddr;
		}

		// Determine maximum payload size of update packet
		maxPayloadSize =(MAX_NW_PKT_SIZE- sizeof(IpHeaderType)- sizeof(Ospfv2LinkStateUpdatePacket));

		payloadBuff = (char*) malloc(maxPayloadSize);

		payloadSize = 0;
		count = 0;

		// Prepare LS Update packet payload
		while (!Ospfv2ListIsEmpty(thisInterface->updateLSAList))
		{
			listItem = thisInterface->updateLSAList->first;
			LSHeader = (Ospfv2LinkStateHeader*) listItem->data;

			if (payloadSize == 0 && LSHeader->length > maxPayloadSize)
			{
				xfree(payloadBuff);
				payloadBuff = (char*) malloc(LSHeader->length);
			}
			else if(payloadSize + LSHeader->length > maxPayloadSize)
			{
				Ospfv2SendUpdatePacket(dstAddr,interfaceIndex,payloadBuff,payloadSize,count);

				// Reset variables
				payloadSize = 0;
				count = 0;
				continue;
			}

			// Incrememnt LS age transmission delay (in seconds).
			LSHeader->linkStateAge = (short int) (LSHeader->linkStateAge +((thisInterface->infTransDelay / SECOND)));

			// LS age has a maximum age limit.
			if (LSHeader->linkStateAge >(OSPFv2_LSA_MAX_AGE / SECOND))
			{
				LSHeader->linkStateAge =OSPFv2_LSA_MAX_AGE / SECOND;
			}

			memcpy(&payloadBuff[payloadSize], listItem->data, LSHeader->length);
			payloadSize += LSHeader->length;
			count++;

			// Remove item from list
			Ospfv2RemoveFromList(thisInterface->updateLSAList,listItem,FALSE);
		}

		Ospfv2SendUpdatePacket(dstAddr,interfaceIndex,payloadBuff,payloadSize,count);

		xfree(payloadBuff);
}


//-------------------------------------------------------------------------//
// NAME         :Ospfv2HandleLSRequestPacket()
// PURPOSE      :Handle Link State Request packet
// ASSUMPTION   :None
// RETURN VALUE :Null
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2HandleLSRequestPacket(Sns_Message* msg,unsigned srcAddr,int interfaceIndex)
{
	Ospfv2Interface* thisInterface = &ospf->iface[interfaceIndex];
	Ospfv2LinkStateRequestPacket* reqPkt = NULL;
	int numLSReqObject;
	Ospfv2LSRequestInfo* LSReqObject = NULL;
	int i;

	// Find neighbor structure
	Ospfv2Neighbor* nbrInfo =Ospfv2GetNeighborInfoByIPAddress(interfaceIndex, srcAddr);

	if (!nbrInfo)
	{
		return;
	}

	// Neighbor state should be exchange or later
	if (nbrInfo->state < S_Exchange)
	{
		return;
	}

	reqPkt = (Ospfv2LinkStateRequestPacket*)msg->Pay_Load;

	numLSReqObject = (reqPkt->commonHeader.packetLength	- sizeof(Ospfv2LinkStateRequestPacket))	/ sizeof(Ospfv2LSRequestInfo);

	LSReqObject = (Ospfv2LSRequestInfo*) (reqPkt + 1);

	for (i = 0; i < numLSReqObject; i++)
	{
		Ospfv2LinkStateHeader* LSHeader = NULL;

		// Stop processing packet if requested LSA type is not identified
		if (LSReqObject->linkStateType < OSPFv2_ROUTER|| LSReqObject->linkStateType > OSPFv2_GROUP_MEMBERSHIP)
		{
			// Handle neighbor event : Bad LS Request
			Ospfv2HandleNeighborEvent(interfaceIndex,srcAddr,S_BadLSReq);
			return;
		}

		// Find LSA in my own LSDB
		LSHeader = Ospfv2LookupLSDB((char) LSReqObject->linkStateType,LSReqObject->advertisingRouter,LSReqObject->linkStateID,interfaceIndex);

		// Stop processing packet if LSA is not found in my database
		if (LSHeader == NULL)
		{
			// Handle neighbor event : Bad LS Request
			Ospfv2HandleNeighborEvent(interfaceIndex,srcAddr,S_BadLSReq);
			return;
		}

		// Add LSA to send this neighbor
		Ospfv2QueueLSAToFlood(thisInterface, (char*) LSHeader);
		LSReqObject += 1;

		if (OSPFv2_SEND_DELAYED_UPDATE)
		{

			if (!thisInterface->floodTimerSet)
			{
				thisInterface->floodTimerSet = TRUE;
				// Set Timer

				Sns_Message* floodMsg=new Sns_Message;
				floodMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_InEVENT_OspfFloodTimer,SNS_MSG_INPUT,NULL,0);
				floodMsg->SNS_Msg_AddInfo((char*)&interfaceIndex,sizeof(int));

				clocktype delay = (clocktype)(Get_rand() * OSPFv2_FLOOD_TIMER);
				Scenarios_Data->SNS_Msg_Send(floodMsg,Cur_Node_id,delay);
			}
		}
	}

	if (!OSPFv2_SEND_DELAYED_UPDATE)
	{
		Ospfv2SendLSUpdate(nbrInfo->neighborIPAddress, interfaceIndex);
	}
}


//-------------------------------------------------------------------------//
// NAME         :Ospfv2RetransmitLSA()
// PURPOSE      :Retransmit LSAs
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2RetransmitLSA(Ospfv2Neighbor* nbrInfo,int interfaceIndex)
{
	Ospfv2ListItem* listItem = NULL;
	Ospfv2LinkStateHeader* LSHeader = NULL;

	char* payloadBuff = NULL;
	int maxPayloadSize;
	int payloadSize;
	int count;

	if (Ospfv2ListIsEmpty(nbrInfo->linkStateRetxList))
	{
		nbrInfo->LSRetxTimer = FALSE;
		nbrInfo->rxmtTimerSequenceNumber++;
		return;
	}

	// Determine maximum payload size of update packet
	maxPayloadSize =MAX_NW_PKT_SIZE	- sizeof(IpHeaderType)- sizeof(Ospfv2LinkStateUpdatePacket);

	payloadBuff = (char*) malloc(maxPayloadSize);

	payloadSize = 0;
	count = 0;

	listItem = nbrInfo->linkStateRetxList->first;

	// Prepare LS Update packet payload
	while (listItem)
	{
		LSHeader = (Ospfv2LinkStateHeader*) listItem->data;

		if (payloadSize + LSHeader->length > maxPayloadSize)
		{
			break;
		}

		// Incrememnt LS age transmission delay (in seconds).
		LSHeader->linkStateAge = (short int) (LSHeader->linkStateAge +((ospf->iface[interfaceIndex].infTransDelay/ SECOND)));

		// LS age has a maximum age limit.
		if (LSHeader->linkStateAge >(OSPFv2_LSA_MAX_AGE / SECOND))
		{
			LSHeader->linkStateAge =OSPFv2_LSA_MAX_AGE / SECOND;
		}

		memcpy(&payloadBuff[payloadSize], listItem->data, LSHeader->length);
		payloadSize += LSHeader->length;
		count++;

		listItem = listItem->next;
	}

	Ospfv2SendUpdatePacket(nbrInfo->neighborIPAddress,interfaceIndex,payloadBuff,payloadSize,count);


	ospf->stats.numLSUpdateRxmt++;
	nbrInfo->rxmtTimerSequenceNumber++;

	// If LSA stil exist in retx list, start timer again
	if (!Ospfv2ListIsEmpty(nbrInfo->linkStateRetxList))
	{
		Ospfv2SetTimer(interfaceIndex,	MSG_InEVENT_OspfRxmtTimer,nbrInfo->neighborIPAddress,ospf->iface[interfaceIndex].rxmtInterval,nbrInfo->rxmtTimerSequenceNumber,0,OSPFv2_LINK_STATE_UPDATE);

		nbrInfo->LSRetxTimer = TRUE;
	}
	else
	{
		nbrInfo->LSRetxTimer = FALSE;
	}

	xfree(payloadBuff);
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2HandleRetransmitTimer
// PURPOSE      :Retransmission timer expired, so may need
//               to retransmit packet.
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2HandleRetransmitTimer(int interfaceIndex,unsigned int sequenceNumber,unsigned neighborAddr,unsigned advertisingRouter,Ospfv2PacketType type)
{
	Ospfv2Neighbor* nbrInfo =Ospfv2GetNeighborInfoByIPAddress(interfaceIndex, neighborAddr);
	Sns_Message* msg=NULL;
	bool foundPacket = FALSE;
	clocktype delay;

	ERROR_Assert(!nbrInfo, "Neighbor not found in the Neighbor list");

	ERROR_Assert(interfaceIndex == -1,"Not found any interface on which this neighbor is attached");

	switch (type)
	{
	case OSPFv2_LINK_STATE_UPDATE:
		{
			// Timer expired.
			if (sequenceNumber != nbrInfo->rxmtTimerSequenceNumber)
			{
				if (OSPFv2_DEBUG_FLOODErr)
				{
					printf("    Old timer\n");
				}

				// Timer is an old one, so just ignore.
				break;
			}

			Ospfv2RetransmitLSA(nbrInfo, interfaceIndex);

			break;
		}

	case OSPFv2_DATABASE_DESCRIPTION:
		{
			Ospfv2DatabaseDescriptionPacket* dbDscrpPkt = NULL;

			msg = nbrInfo->lastSentDDPkt;

			// Old Timer
			if (nbrInfo->masterSlave != T_Master)
			{
				break;
			}
			if (msg == NULL)
			{
				// No packet to retransmit
				break;
			}

			dbDscrpPkt = (Ospfv2DatabaseDescriptionPacket*)	msg->Pay_Load;

			// Send only database description packets that the
			// rmxtTimer indicates.
			if ((dbDscrpPkt->ddSequenceNumber == nbrInfo->DDSequenceNumber)	&& (dbDscrpPkt->ddSequenceNumber == sequenceNumber))
			{
				foundPacket = TRUE;

				// Packet is retransmitted at the end of function.
				ospf->stats.numDDPktRxmt++;

				// Set retransmission timer again if Master.
				if (nbrInfo->masterSlave == T_Master)
				{
					clocktype delay;

 					delay = (clocktype)(ospf->iface[interfaceIndex].rxmtInterval+ (Get_rand()* OSPFv2_BROADCAST_JITTER));

					Ospfv2SetTimer(interfaceIndex,MSG_InEVENT_OspfRxmtTimer,nbrInfo->neighborIPAddress,delay,dbDscrpPkt->ddSequenceNumber,0,OSPFv2_DATABASE_DESCRIPTION);
				}
			}
			break;
		}

	case OSPFv2_LINK_STATE_REQUEST:
		{
			if (nbrInfo->LSReqTimerSequenceNumber != sequenceNumber)
			{
				// No packet to retransmit
				break;
			}

			Ospfv2SendLSRequestPacket(neighborAddr,interfaceIndex,TRUE);

			ospf->stats.numLSReqRxmt++;

			break;
		}
	default:
		{
			ERROR_Assert(TRUE, "Unknown packet type");
		}
	}

	if (foundPacket)
	{

		//Trace sending pkt

		// Found packet to retransmit, so done...
		delay = 0;

		// This packet needs to be retransmitted, so send it out again.
		Sns_Message* newMsg=msg->SNS_Msg_Copy();
		NetworkToMACInfo* info=(NetworkToMACInfo*)newMsg->Pay_Load;
		info->srcAddr=ospf->iface[interfaceIndex].address;
		info->dstAddr=nbrInfo->neighborIPAddress;
		info->nexthopaddr=nbrInfo->neighborIPAddress;
		info->interfaceIndex=interfaceIndex;
		Scenarios_Data->SNS_Msg_Send(newMsg,Cur_Node_id,delay);

		////****!!!!
		xdelete( msg ) ;


		//NetworkIpSendRawMessageToMacLayerWithDelay(
		//	node,
		//	MESSAGE_Duplicate(node, msg),
		//	NetworkIpGetInterfaceAddress(node, interfaceIndex),
		//	nbrInfo->neighborIPAddress,
		//	IPTOS_PREC_INTERNETCONTROL,
		//	IPPROTO_OSPF,
		//	1,
		//	interfaceIndex,
		//	nbrInfo->neighborIPAddress,
		//	delay);
	}
}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2ListDREligibleRouters()
// PURPOSE      :Make list of DR eligible routers.
// ASSUMPTION   :None
// RETURN VALUE :Null
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2ListDREligibleRouters(Ospfv2List* nbrList,Ospfv2List* eligibleRoutersList,int interfaceIndex)
{
	Ospfv2ListItem* listItem = NULL;
	Ospfv2Neighbor* nbrInfo = NULL;
	Ospfv2DREligibleRouter* newRouter = NULL;

	// Calculating router itself is considered to be on the list
	if (ospf->iface[interfaceIndex].routerPriority > 0)
	{
		newRouter= (Ospfv2DREligibleRouter *)malloc(sizeof(Ospfv2DREligibleRouter));

		newRouter->routerID = ospf->routerID;
		newRouter->routerPriority =ospf->iface[interfaceIndex].routerPriority;
		newRouter->routerIPAddress =ospf->iface[interfaceIndex].address;
		newRouter->routerOptions = 0;
		newRouter->DesignatedRouter =ospf->iface[interfaceIndex].designatedRouterIPAddress;
		newRouter->BackupDesignatedRouter =ospf->iface[interfaceIndex].backupDesignatedRouterIPAddress;

		Ospfv2InsertToList(eligibleRoutersList,0,(void*) newRouter);
	}

	listItem = nbrList->first;

	while (listItem)
	{
		nbrInfo = (Ospfv2Neighbor*) listItem->data;

		// Consider only neighbors having established bidirectional
		// communication with this router and have rtrPriority > 0

		if (nbrInfo->state >= S_TwoWay && nbrInfo->neighborPriority > 0)
		{
			newRouter= (Ospfv2DREligibleRouter *)malloc(sizeof(Ospfv2DREligibleRouter));

			newRouter->routerID = nbrInfo->neighborID;
			newRouter->routerPriority = nbrInfo->neighborPriority;
			newRouter->routerIPAddress = nbrInfo->neighborIPAddress;
			newRouter->routerOptions = nbrInfo->neighborOptions;
			newRouter->DesignatedRouter = nbrInfo->neighborDesignatedRouter;
			newRouter->BackupDesignatedRouter =
				nbrInfo->neighborBackupDesignatedRouter;

			Ospfv2InsertToList(eligibleRoutersList,0,(void*) newRouter);
		}

		listItem = listItem->next;
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2ElectBDR()
// PURPOSE      :Elect BDR for desired interface.
// ASSUMPTION   :None
// RETURN VALUE :Null
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2ElectBDR(Ospfv2List* eligibleRoutersList,int interfaceIndex)
{
	Ospfv2ListItem* listItem = NULL;
	Ospfv2DREligibleRouter* routerInfo = NULL;
	Ospfv2DREligibleRouter* tempBDR = NULL;
	bool flag = FALSE;

	for (listItem = eligibleRoutersList->first; listItem;listItem = listItem->next)
	{
		routerInfo = (Ospfv2DREligibleRouter*) listItem->data;

		// If the router declared itself to be DR
		// it is not eligible to become BDR

		if (routerInfo->routerIPAddress == routerInfo->DesignatedRouter)
		{
			continue;
		}

		// If neighbor declared itself to be BDR
		if (routerInfo->routerIPAddress ==routerInfo->BackupDesignatedRouter)
		{
			if ((flag) && (tempBDR) &&
				((tempBDR->routerPriority > routerInfo->routerPriority) ||
				((tempBDR->routerPriority == routerInfo->routerPriority) &&
				(tempBDR->routerID > routerInfo->routerID))))
			{
				// do nothing
			}
			else
			{
				tempBDR = routerInfo;
				flag = TRUE;
			}
		}
		else if (!flag)
		{
			if ((tempBDR) &&
				((tempBDR->routerPriority > routerInfo->routerPriority) ||
				((tempBDR->routerPriority == routerInfo->routerPriority) &&
				(tempBDR->routerID > routerInfo->routerID))))
			{
				// do nothing
			}
			else
			{
				tempBDR = routerInfo;
			}
		}
	}

	// Set BDR to this iface
	if (tempBDR)
	{
		ospf->iface[interfaceIndex].backupDesignatedRouter =tempBDR->routerID;
		ospf->iface[interfaceIndex].backupDesignatedRouterIPAddress =tempBDR->routerIPAddress;
	}
	else
	{
		ospf->iface[interfaceIndex].backupDesignatedRouter = 0;
		ospf->iface[interfaceIndex].backupDesignatedRouterIPAddress = 0;
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2ElectDR()
// PURPOSE      :Elect DR for desired interface.
// ASSUMPTION   :None
// RETURN VALUE :Ospfv2InterfaceState
//-------------------------------------------------------------------------//
Sns_Model_OSPFv2::Ospfv2InterfaceState Sns_Model_OSPFv2::Ospfv2ElectDR(Ospfv2List* eligibleRoutersList,int interfaceIndex)
{
	Ospfv2ListItem* listItem = NULL;
	Ospfv2DREligibleRouter* routerInfo = NULL;
	Ospfv2DREligibleRouter* tempDR = NULL;

	for (listItem = eligibleRoutersList->first; listItem;listItem = listItem->next)
	{
		routerInfo = (Ospfv2DREligibleRouter*) listItem->data;

		// If router declared itself to be DR
		if (routerInfo->routerIPAddress == routerInfo->DesignatedRouter)
		{
			if ((tempDR) &&
				((tempDR->routerPriority > routerInfo->routerPriority) ||
				((tempDR->routerPriority == routerInfo->routerPriority) &&
				(tempDR->routerID > routerInfo->routerID))))
			{
				// do nothing
			}
			else
			{
				tempDR = routerInfo;
			}
		}
	}

	if (tempDR)
	{
		ospf->iface[interfaceIndex].designatedRouter = tempDR->routerID;
		ospf->iface[interfaceIndex].designatedRouterIPAddress =tempDR->routerIPAddress;
	}
	else
	{
		ospf->iface[interfaceIndex].designatedRouter =ospf->iface[interfaceIndex].backupDesignatedRouter;
		ospf->iface[interfaceIndex].designatedRouterIPAddress =ospf->iface[interfaceIndex].backupDesignatedRouterIPAddress;
	}

	// Return new interface state
	if (ospf->iface[interfaceIndex].designatedRouter == ospf->routerID)
	{
		return S_DR;
	}
	else if (ospf->iface[interfaceIndex].backupDesignatedRouter ==ospf->routerID)
	{
		return S_Backup;
	}
	else if (ospf->iface[interfaceIndex].designatedRouter != 0)
	{
		return S_DROther;
	}
	else
	{
		return S_Waiting;
	}
}


//-------------------------------------------------------------------------//
// NAME         :Ospfv2DRElection()
// PURPOSE      :Elect DR and BDR for desired network.
// ASSUMPTION   :None
// RETURN VALUE :Ospfv2InterfaceState
//-------------------------------------------------------------------------//
Sns_Model_OSPFv2::Ospfv2InterfaceState Sns_Model_OSPFv2::Ospfv2DRElection(int interfaceIndex)
{
	Ospfv2List* eligibleRoutersList = NULL;
	unsigned oldDR;
	unsigned oldBDR;
	Ospfv2InterfaceState oldState;
	Ospfv2InterfaceState newState;

	//Make a list of eligible routers that will participate in DR election
	Ospfv2InitList(&eligibleRoutersList);

	Ospfv2ListDREligibleRouters(ospf->iface[interfaceIndex].neighborList,eligibleRoutersList,interfaceIndex);

	// RFC-2328, Section: 9.4.1
	// Note current values for the network's DR and BDR

	oldDR = ospf->iface[interfaceIndex].designatedRouter;
	oldBDR = ospf->iface[interfaceIndex].backupDesignatedRouter;

	// Note interface state
	oldState = ospf->iface[interfaceIndex].state;

	// RFC-2328, Section: 9.4.2 & 9.4.3
	// First election of DR and BDR
	Ospfv2ElectBDR(eligibleRoutersList, interfaceIndex);
	newState = Ospfv2ElectDR(eligibleRoutersList,interfaceIndex);
	Ospfv2FreeList(eligibleRoutersList, FALSE);

	// RFC-2328, Section: 9.4.4
	// If Router X is now newly the Designated Router or newly the Backup
	// Designated Router, or is now no longer the Designated Router or no
	// longer the Backup Designated Router, repeat steps 2 and 3, and then
	// proceed to step 5.
	if ((newState != oldState) &&((newState != S_DROther) || (oldState > S_DROther)))
	{
		Ospfv2InitList(&eligibleRoutersList);
		Ospfv2ListDREligibleRouters(ospf->iface[interfaceIndex].neighborList,eligibleRoutersList,interfaceIndex);

		Ospfv2ElectBDR(eligibleRoutersList, interfaceIndex);
		newState = Ospfv2ElectDR(eligibleRoutersList,interfaceIndex);
		Ospfv2FreeList(eligibleRoutersList, FALSE);
	}

	//if (((newState == S_DR) || (newState == S_Backup))
	//	&& ((oldState != S_DR) && (oldState != S_Backup)))
	//{
	//	NetworkIpAddToMulticastGroupList(OSPFv2_ALL_D_ROUTERS);
	//}
	//else if (((newState != S_DR) && (newState != S_Backup))
	//	&& ((oldState == S_DR) || (oldState == S_Backup)))
	//{
	//	NetworkIpRemoveFromMulticastGroupList(OSPFv2_ALL_D_ROUTERS);
	//}

	// RFC-2328, Section: 9.4.7
	// If the above calculations have caused the identity of either the
	// Designated Router or Backup Designated Router to change, the set
	// of adjacencies associated with this interface will need to be
	// modified.

	if ((oldDR != ospf->iface[interfaceIndex].designatedRouter) ||
		(oldBDR != ospf->iface[interfaceIndex].backupDesignatedRouter))
	{
		Ospfv2ListItem* listItem = NULL;
		Ospfv2Neighbor* nbrInfo = NULL;

		for (listItem = ospf->iface[interfaceIndex].neighborList->first;
			listItem; listItem = listItem->next)
		{
			nbrInfo = (Ospfv2Neighbor*) listItem->data;

			if (nbrInfo->state >= S_TwoWay)
			{
				Ospfv2ScheduleNeighborEvent(interfaceIndex,	nbrInfo->neighborIPAddress,S_AdjOk);
			}
		}
	}
	return newState;
}


//-------------------------------------------------------------------------//
// NAME         :Ospfv2SetInterfaceState()
// PURPOSE      :Set the state of a interface.
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2SetInterfaceState(int interfaceIndex,Ospfv2InterfaceState newState)
{
	Ospfv2InterfaceState oldState = ospf->iface[interfaceIndex].state;

	ospf->iface[interfaceIndex].state = newState;

	// We may need to produce a new instance of router LSA
	Ospfv2ScheduleRouterLSA(ospf->iface[interfaceIndex].areaId, FALSE);

	// If I'm new DR the produce network LSA for this network
	if (oldState != S_DR && newState == S_DR)
	{
		Ospfv2ScheduleNetworkLSA(interfaceIndex, FALSE);

		// M-OSPF Patch start
		if (ospf->isMospfEnable)
		{
			// Generate GroupMembershipLSA for group present in this network
			//MospfScheduleGroupMembershipLSA(ospf->iface[interfaceIndex].areaId,(unsigned) interfaceIndex, (unsigned) ANY_GROUP, FALSE);
		}
		// M-Ospf Patch end
	}

	// Else if I'm no longer the DR, flush previously
	// originated network LSA
	else if (oldState == S_DR && newState != S_DR)
	{
		// Flush previously originated network LSA from routing domain
		Ospfv2ScheduleNetworkLSA(interfaceIndex, TRUE);

		// M-OSPF Patch start
		if (ospf->isMospfEnable)
		{
			// Flush previously originated GroupMembershipLSA for this area
			//MospfScheduleGroupMembershipLSA(ospf->iface[interfaceIndex].areaId,(unsigned) interfaceIndex, (unsigned) ANY_GROUP, TRUE);
		}
		// M-Ospf Patch end
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2HandleInterfaceEvent()
// PURPOSE      :Handle interface event and change interface state
//               accordingly
// ASSUMPTION   :None
// RETURN VALUE :Null
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2HandleInterfaceEvent(int interfaceIndex,Ospfv2InterfaceEvent eventType)
{
	Ospfv2InterfaceState newState = S_Down;
	// Copy old state information
	Ospfv2InterfaceState oldState = ospf->iface[interfaceIndex].state;

	switch (eventType)
	{
	case E_InterfaceUp:
		{
			if (ospf->iface[interfaceIndex].state != S_Down)
			{
				newState = oldState;
				break;
			}

			// Start Hello timer & enabling periodic sending of Hello packet
			if ((ospf->iface[interfaceIndex].type ==OSPFv2_POINT_TO_POINT_INTERFACE)
				|| (ospf->iface[interfaceIndex].type ==OSPFv2_POINT_TO_MULTIPOINT_INTERFACE)
				|| (ospf->iface[interfaceIndex].type ==OSPFv2_VIRTUAL_LINK_INTERFACE))
			{
				newState = S_PointToPoint;
			}
			else if (ospf->iface[interfaceIndex].routerPriority == 0)
			{
				newState = S_DROther;
			}
			else
				{
					Sns_Message* waitTimerMsg = NULL;

					newState = S_Waiting;

					waitTimerMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,MSG_InEVENT_OspfWaitTimer,SNS_MSG_INPUT,NULL,0);
					waitTimerMsg->SNS_Msg_AddInfo((char*)&interfaceIndex,sizeof(int));

					////****!!!!
//					xfree( interfaceIndex ) ;

					// Send wait timer to self
					Scenarios_Data->SNS_Msg_Send(waitTimerMsg,Cur_Node_id,OSPFv2_WAIT_TIMER);
				}

				break;
		}

	case E_WaitTimer:
	case E_BackupSeen:
	case E_NeighborChange:
		{
			if (((eventType == E_BackupSeen || eventType == E_WaitTimer)&& (ospf->iface[interfaceIndex].state != S_Waiting))
				|| ((eventType == E_NeighborChange)	&& (ospf->iface[interfaceIndex].state != S_DROther&& ospf->iface[interfaceIndex].state != S_Backup&& ospf->iface[interfaceIndex].state != S_DR)))
			{
				newState = oldState;
				break;
			}
			newState = Ospfv2DRElection(interfaceIndex);
			break;
		}

	case E_LoopInd:
	case E_UnloopInd:
		{
			// These 2 events are not used in simulation
			break;
		}

	case E_InterfaceDown:
		{
			// 1) Reset all interface variables
			// 2) Disable timers associated with this interface
			// 3) Generate S_KillNbr event to destry all neighbor
			//      associated with this interface
			Ospfv2ListItem* listItem =
				ospf->iface[interfaceIndex].neighborList->first;

			while (listItem)
			{
				Ospfv2Neighbor* nbrInfo =(Ospfv2Neighbor*) listItem->data;
				listItem = listItem->next;

				//FIXME: Schedule the event or execute from here?
				Ospfv2HandleNeighborEvent(interfaceIndex,nbrInfo->neighborIPAddress,S_KillNbr);
			}

			ospf->iface[interfaceIndex].designatedRouter = 0;
			ospf->iface[interfaceIndex].designatedRouterIPAddress = 0;

			ospf->iface[interfaceIndex].backupDesignatedRouter = 0;
			ospf->iface[interfaceIndex].backupDesignatedRouterIPAddress	= 0;

			//ospf->iface[interfaceIndex].networkLSTimer = FALSE;
			//ospf->iface[interfaceIndex].networkLSAOriginateTime = 0;
			ospf->iface[interfaceIndex].floodTimerSet = FALSE;
			ospf->iface[interfaceIndex].delayedAckTimer = FALSE;
			Ospfv2FreeList(ospf->iface[interfaceIndex].updateLSAList, FALSE);
			Ospfv2FreeList(ospf->iface[interfaceIndex].delayedAckList, FALSE);
			Ospfv2InitList(&ospf->iface[interfaceIndex].updateLSAList);
			Ospfv2InitList(&ospf->iface[interfaceIndex].delayedAckList);

			newState = S_Down;
			break;
		}

	default:
		{
			ERROR_Assert(TRUE, "Unknown interface event!\n");
		}
	}

	if (oldState != newState)
	{
		Ospfv2SetInterfaceState(interfaceIndex, newState);
	}
}


// unsigned Sns_Model_OSPFv2::hostBitsStr2Uint(char* hostBitsStr)
// {
// 	unsigned mask=0;
// 	int num[4];
// 	int retNum;
// 	retNum=sscanf(hostBitsStr,"%d.%d.%d.%d",&num[0],&num[1],&num[2],&num[3]);
// 	ERROR_Assert(retNum!=4,"hostBits is not available!\n");
// 	mask=num[0]*256*256*256+num[1]*256*256+num[2]*256+num[3];
// 	return mask;
// }

unsigned Sns_Model_OSPFv2::ConvertNumHostBitsToSubnetMask(int hostbits)
{
	unsigned maskArr[4];
	unsigned mask;
	hostbits<<=1;
	hostbits>>=1;
	for(int i=3;i>=0;i--)
	{
		int maskItem=hostbits%256;
		maskArr[i]=255-maskItem;
		hostbits/=256;
	}
	mask=maskArr[0]*256*256*256+maskArr[1]*256*256+maskArr[2]*256+maskArr[3];
	return mask;
}

void Sns_Model_OSPFv2::Ospfv2InitNonBroadcastNeighborList(Ospfv2NonBroadcastNeighborList** list)
{
	Ospfv2NonBroadcastNeighborList* tmpList = (Ospfv2NonBroadcastNeighborList*)malloc(sizeof(Ospfv2NonBroadcastNeighborList));

	tmpList->size = 0;
	tmpList->first = tmpList->last = NULL;
	*list = tmpList;
}

void Sns_Model_OSPFv2::Ospfv2InsertToNonBroadcastNeighborList(Ospfv2NonBroadcastNeighborList* list,unsigned addr)
{
	Ospfv2NonBroadcastNeighborListItem* listItem =(Ospfv2NonBroadcastNeighborListItem*)malloc(sizeof(Ospfv2NonBroadcastNeighborListItem));
	listItem->neighborAddr = addr;
	listItem->next = NULL;
	if (list->size == 0)
	{
		listItem->prev = NULL;
		list->last = listItem;
		list->first = list->last;
	}
	else
	{
		// Insert at end of list.
		listItem->prev = list->last;
		list->last->next = listItem;
		list->last = listItem;
	}
	list->size++;
}


//-------------------------------------------------------------------------//
// NAME: Ospfv2InsertToList
// PURPOSE: Inserts an item to a list
// RETURN: None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2InsertToList(Ospfv2List* list,clocktype timeStamp,void* data)
{
	Ospfv2ListItem* listItem = (Ospfv2ListItem*)malloc(sizeof(Ospfv2ListItem));

	listItem->data = data;
	listItem->timeStamp = timeStamp;

	listItem->next = NULL;

	if (list->size == 0)
	{
		// Only item in the list.
		listItem->prev = NULL;
		list->last = listItem;
		list->first = list->last;
	}
	else
	{
		// Insert at end of list.
		listItem->prev = list->last;
		list->last->next = listItem;
		list->last = listItem;
	}

	list->size++;
}
// -------------------------------------------------------------------------
// API :: GetDefaultIPv4InterfaceAddress
// PURPOSE :: Returns Default ipv4 Interface address
// PARAMETERS ::
// + node : Node* : Pointer to the Node
// RETURN :: unsigned
// ------------------------------------------------------------------------
unsigned Sns_Model_OSPFv2::GetDefaultIPv4InterfaceAddress()
{
	return ospf->iface[0].address;
}
//-------------------------------------------------------------------------//
// NAME:    Ospfv2RouterFunction
// PURPOSE: Address of this function is assigned in the IP structure
//          during initialization. IP forwards packet by getting the nextHop
//          from this function. This fuction will be called via a pointer,
//          RouterFunction, in the IP structure, from function RoutePacket
//          AndSendToMac() in nwip.pc.
// RETURN:  None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2RouterFunction(Sns_Node_NetworkIP_OSPFv2* node,Sns_Message* msg,unsigned destAddr,unsigned prevHopAddr,bool* packetWasRouted)
{
	// Let IP do the forwarding.
	*packetWasRouted = FALSE;
	return;
}

//格式：str="192.168.0.1:255.255.255.0"
void Sns_Model_OSPFv2::ParseNodeIdHostOrNetworkAddress(char str[SNS_MAX_STRING_LENGTH],unsigned& addr,int& numhostbits)
{
	char* index1=strchr(str,':');
	char* index2=strchr(str,'\0');
	if(!index1)
	{
		assert(str);
		return;
	}
	char addrStr[SNS_MAX_STRING_LENGTH];
	char hostbitsStr[SNS_MAX_STRING_LENGTH];
	strncpy(addrStr,str,index1-str);
	index1++;
	strncpy(hostbitsStr,index1,index2-index1);
	addr=hostBitsStr2Uint(addrStr);
	numberInterfaces=hostBitsStr2Uint(hostbitsStr);
}

//-----------------------------------------------------------------------------
// FUNCTION     NetworkIpGetInterfaceIndexForNextHop()
// PURPOSE      This function looks at the network address of each of a
//              node's network interfaces.  When nextHopAddress is
//              matched to a network, the interface index corresponding
//              to the network is returned.
//              (used by NetworkUpdateForwardingTable() and ospfv2.pc)
// PARAMETERS   Node *node
//                  Pointer to node.
//              unsigned nextHopAddress
//                  IP address
//
// RETURN       Index of outgoing interface, if nextHopAddress is on a
//              directly connected network.
//              -1, otherwise.
//-----------------------------------------------------------------------------

int	Sns_Model_OSPFv2::NetworkIpGetInterfaceIndexForNextHop(unsigned nextHopAddress)
{
	int i;

	if (nextHopAddress == (unsigned) NETWORK_UNREACHABLE)
	{
		// Return bad value early if the IP address is NETWORK_UNREACHABLE.

		return -1;
	}

	// Given a next hop IP address, return the index of the corresponding
	// outgoing interface.

	for (int i = 0; i < numberInterfaces; i++)
	{
		unsigned subnetMask = ospf->iface[i].subnetMask;
		unsigned maskedAddress = MaskIpAddress(nextHopAddress, subnetMask);
		unsigned interfaceNetworkAddress =MaskIpAddress(ospf->iface[i].address, subnetMask);
		if (maskedAddress == interfaceNetworkAddress)
		{
			return i;
		}
	}

	// Couldn't find IP address on a directly connected network, so
	// return -1 as the interface index.

	return -1;
}
// /**
// API         :: MaskIpAddress
// LAYER       :: Network
// PURPOSE     :: To mask a ip address.
// PARAMETERS  ::
// + address    : unsigned : address of a node
// + mask       : unsigned : mask of subnet.
// RETURN      :: unsigned : masked node address.
// **/
unsigned Sns_Model_OSPFv2::MaskIpAddress(unsigned address, unsigned mask)
{
	return (address & mask);
}

// /**
// FUNCTION     :: Ospfv2LinkStateHeaderSetOptions1()
// LAYER        :: NETWORK
// PURPOSE      :: Set the value of options1 for Ospfv2LinkStateHeader
// PARAMETERS   ::
// + ospfLsh    : unsigned char* : The variable containing the value of qos,
//                                 external,multicast and options1
// + options1    : unsigned char :Input value for set operation
// RETURN       :: void : NULL
// **/
void Sns_Model_OSPFv2::Ospfv2LinkStateHeaderSetOptions1(unsigned char *ospfLsh,unsigned char options1)
{
	//masks options1 within boundry range
	options1 = options1 & maskChar(4, 8);

	//clears the last five bits
	*ospfLsh = *ospfLsh & maskChar(1, 3);

	//setting the value of reserved in ospfLsh
	*ospfLsh = *ospfLsh | options1;
}
// /**
// FUNCTION     :: Ospfv2LinkStateHeaderSetExt()
// LAYER        :: NETWORK
// PURPOSE      :: Set the value of external for Ospfv2LinkStateHeader
// PARAMETERS   ::
// + ospfLsh    : unsigned char* : The variable containing the value of qos,
//                                 external,multicast and options1
// + external   : bool :Input value for set operation
// RETURN       :: void : NULL
// **/
void Sns_Model_OSPFv2::Ospfv2LinkStateHeaderSetExt(unsigned char *ospfLsh,bool external)
{
	unsigned char x = (unsigned char)external;

	//masks external within boundry range
	x = x & maskChar(8, 8);

	//clears the second bit
	*ospfLsh = *ospfLsh & (~(maskChar(2, 2)));

	//setting the value of x in ospfLsh
	*ospfLsh = *ospfLsh | LshiftChar(x, 2);
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2GetNeighborInfoByIPAddress
// PURPOSE:  Get the neighbor structure from the neighbor list using the
//           neighbor's IP address.
// RETURN: The neighbor structure we are looking for, or NULL if not found.
//-------------------------------------------------------------------------//

Sns_Model_OSPFv2::Ospfv2Neighbor* Sns_Model_OSPFv2::Ospfv2GetNeighborInfoByIPAddress(int interfaceIndex,unsigned neighborAddr)
{
	Ospfv2ListItem* tempListItem = NULL;
	Ospfv2Neighbor* tempNeighborInfo = NULL;

	//we should search for only this interface neighbors
	//therefore this code is been commented during virtual link support
	//for (i = 0; i < numberInterfaces; i++)
	//{
	//    if (ospf->iface[i].type == OSPFv2_NON_OSPF_INTERFACE)
	//    {
	//        continue;
	//    }
	//    tempListItem = ospf->iface[i].neighborList->first;

	tempListItem = ospf->iface[interfaceIndex].neighborList->first;

	// Search for the neighbor in my neighbor list.
	while (tempListItem)
	{
		tempNeighborInfo = (Ospfv2Neighbor*) tempListItem->data;

		ERROR_Assert(!tempNeighborInfo,"Neighbor not found in the Neighbor list");

		if (tempNeighborInfo->neighborIPAddress == neighborAddr)
		{
			// Found the neighbor we are looking for.
			return tempNeighborInfo;
		}

		tempListItem = tempListItem->next;
	}
	//   }

	return NULL;
}



//-------------------------------------------------------------------------//
// NAME: Ospfv2SetTimer
// PURPOSE: Set timers of various types.
// RETURN: None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2SetTimer(int interfaceIndex,int eventType,unsigned neighborAddr,clocktype timerDelay,unsigned sequenceNumber,unsigned advertisingRouter,Ospfv2PacketType type)
{
	Ospfv2TimerInfo* info = new Ospfv2TimerInfo;
	Sns_Message* newMsg =new Sns_Message;
	info->neighborAddr = neighborAddr;
	info->interfaceIndex = interfaceIndex;
	switch (eventType)
	{
	case MSG_InEVENT_OspfInactivityTimer:
		{
			Ospfv2Neighbor* neighborInfo =Ospfv2GetNeighborInfoByIPAddress(interfaceIndex,neighborAddr);

			ERROR_Assert(!neighborInfo, "Neighbor Info not found");

			char nbrStr[SNS_MAX_STRING_LENGTH];
			convertIpAddressToString(neighborInfo->neighborID, nbrStr);

			info->sequenceNumber =	++neighborInfo->inactivityTimerSequenceNumber;

			break;
		}
	case MSG_InEVENT_OspfRxmtTimer:
		{
			info->sequenceNumber = sequenceNumber;
			info->advertisingRouter = advertisingRouter;
			info->type = type;
			break;
		}
	default:
		// Shouldn't get here.
		ERROR_Assert(TRUE, "Invalid Timer EventType\n");
	}
	newMsg->SNS_Msg_Assignment(Model_id,Model_Instance_id,eventType,SNS_MSG_INPUT,NULL,0);
	newMsg->SNS_Msg_AddInfo((char*)info,sizeof(Ospfv2TimerInfo));
	Scenarios_Data->SNS_Msg_Send(newMsg, Cur_Node_id,timerDelay);
	xdelete(info);
}

// /**
// FUNCTION     :: Ospfv2RouterLSASetReserved1()
// LAYER        :: NETWORK
// PURPOSE      :: Set the value of reserved1 for Ospfv2RouterLSA
// PARAMETERS   ::
// + ospfRouterLsa : unsigned char* : The variable containing the value of ,
//                                    areaBorderRouter,ASBoundaryRouter,
//                                    virtualLinkEndpoint,
//                                    wildCardMulticastReceiver and reserved1
// + reserved    : unsigned char : Input value for set operation
// RETURN       :: void : NULL
// **/
void Sns_Model_OSPFv2::Ospfv2RouterLSASetReserved1(unsigned char *ospfRouterLsa,unsigned char reserved)
{
	//masks reserved within boundry range
	reserved = reserved & maskChar(5, 8);

	//clears the last four bits
	*ospfRouterLsa = *ospfRouterLsa & maskChar(1, 4);

	//setting the value of reserved in ospfRouterLsa
	*ospfRouterLsa = *ospfRouterLsa | reserved;
}


// /**
// FUNCTION     :: Ospfv2RouterLSASetWCMCReceiver()
// LAYER        :: NETWORK
// PURPOSE      :: Set the value of wildCardMulticastReceiver for
//                Ospfv2RouterLSA
// PARAMETERS   ::
// + ospfRouterLsa : unsigned char* : The variable containing the value of ,
//                                    areaBorderRouter,ASBoundaryRouter,
//                                    virtualLinkEndpoint,
//                                    wildCardMulticastReceiver and reserved1
// + wcmr          : bool : Input value for set operation
// RETURN       :: void : NULL
// **/
void Sns_Model_OSPFv2::Ospfv2RouterLSASetWCMCReceiver(unsigned char *ospfRouterLsa,bool wcmr)
{
	unsigned char x = (unsigned char)wcmr;

	//masks wcmr within boundry range
	x = x & maskChar(8, 8);

	//clears the fourth bit
	*ospfRouterLsa = *ospfRouterLsa & (~(maskChar(4, 4)));

	//setting the value of x in ospfRouterLsa
	*ospfRouterLsa = *ospfRouterLsa | LshiftChar(x, 4);
}


// /**
// FUNCTION     :: Ospfv2RouterLSASetVirtLnkEndPt()
// LAYER        :: NETWORK
// PURPOSE      :: Set the value of virtualLinkEndpoint for
//                Ospfv2RouterLSA
// PARAMETERS   ::
// + ospfRouterLsa : unsigned char* : The variable containing the value of ,
//                                    areaBorderRouter,ASBoundaryRouter,
//                                    virtualLinkEndpoint,
//                                    wildCardMulticastReceiver and reserved1
// + vlep          : bool : Input value for set operation
// RETURN       :: void : NULL
// **/
void Sns_Model_OSPFv2::Ospfv2RouterLSASetVirtLnkEndPt(unsigned char *ospfRouterLsa,bool vlep)
{
	unsigned char x = (unsigned char)vlep;

	//masks vlep within boundry range
	x = x & maskChar(8, 8);

	//clears the third bit
	*ospfRouterLsa = *ospfRouterLsa & (~(maskChar(3, 3)));

	//setting the value of x in ospfRouterLsa
	*ospfRouterLsa = *ospfRouterLsa | LshiftChar(x, 3);
}
// /**
// FUNCTION     :: Ospfv2RouterLSASetASBRouter()
// LAYER        :: NETWORK
// PURPOSE      :: Set the value of ASBoundaryRouter for
//                Ospfv2RouterLSA
// PARAMETERS   ::
// + ospfRouterLsa : unsigned char* : The variable containing the value of ,
//                                    areaBorderRouter,ASBoundaryRouter,
//                                    virtualLinkEndpoint,
//                                    wildCardMulticastReceiver and reserved1
// + asbr          : bool : Input value for set operation
// RETURN       :: void : NULL
// **/
void Sns_Model_OSPFv2::Ospfv2RouterLSASetASBRouter(unsigned char *ospfRouterLsa,bool asbr)
{
	unsigned char x = (unsigned char)asbr;

	//masks asbr within boundry range
	x = x & maskChar(8, 8);

	//clears the second bit
	*ospfRouterLsa = *ospfRouterLsa & (~(maskChar(2, 2)));

	//setting the value of x in ospfRouterLsa
	*ospfRouterLsa = *ospfRouterLsa | LshiftChar(x, 2);
}
// /**
// FUNCTION     :: Ospfv2RouterLSASetABRouter()
// LAYER        :: NETWORK
// PURPOSE      :: Set the value of areaBorderRouter for Ospfv2RouterLSA
// PARAMETERS   ::
// + ospfRouterLsa : unsigned char* : The variable containing the value of ,
//                                    areaBorderRouter,ASBoundaryRouter,
//                                    virtualLinkEndpoint,
//                                    wildCardMulticastReceiver and reserved1
// + abr           : bool : Input value for set operation
// RETURN       :: void : NULL
// **/
void Sns_Model_OSPFv2::Ospfv2RouterLSASetABRouter(unsigned char *ospfRouterLsa,bool abr)
{
	unsigned char x = (unsigned char)abr;

	//masks abr within boundry range
	x = x & maskChar(8, 8);

	//clears the first bit
	*ospfRouterLsa = *ospfRouterLsa & (~(maskChar(1, 1)));

	//setting the value of x in ospfRouterLsa
	*ospfRouterLsa = *ospfRouterLsa | LshiftChar(x, 1);
}


// /**
// FUNCTION     :: Ospfv2LinkStateHeaderGetExt()
// LAYER        :: NETWORK
// PURPOSE      :: Returns the value of external for Ospfv2LinkStateHeader
// PARAMETERS   ::
// + ospfLsh    : unsigned char : The variable containing the value of qos,
//                                 external,multicast and options1
// RETURN       :: bool
// **/
bool Sns_Model_OSPFv2::Ospfv2LinkStateHeaderGetExt(unsigned char ospfLsh)
{
	unsigned char external = ospfLsh;

	//clears all the bits except second bit
	external = external & maskChar(2, 2);

	//Right shifts so that last bit represents external
	external = RshiftChar(external, 2);

	return (bool)external;
}

// /**
// FUNCTION     :: Ospfv2LinkStateHeaderGetMulticast()
// LAYER        :: NETWORK
// PURPOSE      :: Returns the value of multicast for Ospfv2LinkStateHeader
// PARAMETERS   ::
// + ospfLsh    : unsigned char : The variable containing the value of qos,
//                                 external,multicast and options1
// RETURN       :: bool
// **/
bool Sns_Model_OSPFv2::Ospfv2LinkStateHeaderGetMulticast(unsigned char ospfLsh)
{
	unsigned char multicast = ospfLsh;

	//clears all the bits except third bit
	multicast = multicast & maskChar(3, 3);

	//Right shifts so that last bit represents multicast
	multicast = RshiftChar(multicast, 3);

	return (bool)multicast;
}

// /**
// FUNCTION     :: Ospfv2LinkStateHeaderSetQOS()
// LAYER        :: NETWORK
// PURPOSE      :: Set the value of qos for Ospfv2LinkStateHeader
// PARAMETERS   ::
// + ospfLsh    : unsigned char* : The variable containing the value of qos,
//                                 external,multicast and options1
// + qos        : bool :Input value for set operation
// RETURN       :: void : NULL
// **/
void Sns_Model_OSPFv2::Ospfv2LinkStateHeaderSetQOS(unsigned char *ospfLsh, bool qos)
{
	unsigned char x = (unsigned char)qos;

	//masks qos within boundry range
	x = x & maskChar(8, 8);

	//clears the first bit
	*ospfLsh = *ospfLsh & (~(maskChar(1, 1)));

	//setting the value of x in ospfLsh
	*ospfLsh = *ospfLsh | LshiftChar(x, 1);
}

// /**
// FUNCTION     :: Ospfv2LinkStateHeaderSetMulticast()
// LAYER        :: NETWORK
// PURPOSE      :: Set the value of multicast for Ospfv2LinkStateHeader
// PARAMETERS   ::
// + ospfLsh    : unsigned char* : The variable containing the value of qos,
//                                 external,multicast and options1
// + multicast  : bool :Input value for set operation
// RETURN       :: void : NULL
// **/
void Sns_Model_OSPFv2::Ospfv2LinkStateHeaderSetMulticast(unsigned char *ospfLsh,bool multicast)
{
	unsigned char x = (unsigned char)multicast;

	//masks multicast within boundry range
	x = x & maskChar(8, 8);

	//clears the first bit
	*ospfLsh = *ospfLsh & (~(maskChar(3, 3)));

	//setting the value of x in ospfLsh
	*ospfLsh = *ospfLsh | LshiftChar(x, 3);
}

// /**
// FUNCTION     :: Ospfv2RouterLSAGetReserved1()
// LAYER        :: NETWORK
// PURPOSE      :: Returns the value of reserved1 for Ospfv2RouterLSA
// PARAMETERS   ::
// + ospfRouterLsa : unsigned char : The variable containing the value of ,
//                                    areaBorderRouter,ASBoundaryRouter,
//                                    virtualLinkEndpoint,
//                                    wildCardMulticastReceiver and reserved1
// RETURN       :: unsigned char
// **/
unsigned char Sns_Model_OSPFv2::Ospfv2RouterLSAGetReserved1(unsigned char ospfRouterLsa)
{
	unsigned char reserved = ospfRouterLsa;

	//clears the first four bits
	reserved = reserved & maskChar(5, 8);

	return reserved;
}

// /**
// FUNCTION     :: Ospfv2RouterLSAGetWCMCReceiver()
// LAYER        :: NETWORK
// PURPOSE      :: Returns the value of wcmr for Ospfv2RouterLSA
// PARAMETERS   ::
// + ospfRouterLsa : unsigned char : The variable containing the value of ,
//                                    areaBorderRouter,ASBoundaryRouter,
//                                    virtualLinkEndpoint,
//                                    wildCardMulticastReceiver and reserved1
// RETURN       :: bool
// **/
bool Sns_Model_OSPFv2::Ospfv2RouterLSAGetWCMCReceiver(unsigned char ospfRouterLsa)
{
	unsigned char wcmr = ospfRouterLsa;

	//clears all the bits except fourth bit
	wcmr = wcmr & maskChar(4, 4);

	//Right shifts so that last bit represents wildCardMulticastReceiver
	wcmr = RshiftChar(wcmr, 4);

	return (bool)wcmr;
}

// /**
// FUNCTION     :: Ospfv2RouterLSAGetVirtLnkEndPt()
// LAYER        :: NETWORK
// PURPOSE      :: Returns the value of vlep for Ospfv2RouterLSA
// PARAMETERS   ::
// + ospfRouterLsa : unsigned char : The variable containing the value of ,
//                                    areaBorderRouter,ASBoundaryRouter,
//                                    virtualLinkEndpoint,
//                                    wildCardMulticastReceiver and reserved1
// RETURN       :: bool
// **/
bool Sns_Model_OSPFv2::Ospfv2RouterLSAGetVirtLnkEndPt(unsigned char ospfRouterLsa)
{
	unsigned char vlep = ospfRouterLsa;

	//clears all the bits except third bit
	vlep = vlep & maskChar(3, 3);

	//Right shifts so that last bit represents virtualLinkEndpoint
	vlep = RshiftChar(vlep, 3);

	return (bool)vlep;
}

// /**
// FUNCTION     :: Ospfv2RouterLSAGetASBRouter()
// LAYER        :: NETWORK
// PURPOSE      :: Returns the value of asbr for Ospfv2RouterLSA
// PARAMETERS   ::
// + ospfRouterLsa : unsigned char : The variable containing the value of ,
//                                    areaBorderRouter,ASBoundaryRouter,
//                                    virtualLinkEndpoint,
//                                    wildCardMulticastReceiver and reserved1
// RETURN       :: bool
// **/
bool Sns_Model_OSPFv2::Ospfv2RouterLSAGetASBRouter(unsigned char ospfRouterLsa)
{
	unsigned char asbr = ospfRouterLsa;

	//clears all the bits except second bit
	asbr = asbr & maskChar(2, 2);

	//Right shifts so that last bit represents ASBoundaryRouter
	asbr = RshiftChar(asbr, 2);

	return (bool)asbr;
}

// /**
// FUNCTION     :: Ospfv2RouterLSAGetABRouter()
// LAYER        :: NETWORK
// PURPOSE      :: Returns the value of abr for Ospfv2RouterLSA
// PARAMETERS   ::
// + ospfRouterLsa : unsigned char : The variable containing the value of ,
//                                    areaBorderRouter,ASBoundaryRouter,
//                                    virtualLinkEndpoint,
//                                    wildCardMulticastReceiver and reserved1
// RETURN       :: bool
// **/
bool Sns_Model_OSPFv2::Ospfv2RouterLSAGetABRouter(unsigned char ospfRouterLsa)
{
	unsigned char abr = ospfRouterLsa;

	//clears all the bits except first bit
	abr = abr & maskChar(1, 1);

	//Right shifts so that last bit represents areaBorderRouter
	abr = RshiftChar(abr, 1);

	return (bool)abr;
}

// /**
// FUNCTION     :: Ospfv2ExternalLinkSetEBit()
// LAYER        :: NETWORK
// PURPOSE      :: Set the value of eBit for Ospfv2ExternalLinkInfo
// PARAMETERS   ::
// + ospfMetric : UInt32* : The variable containing the value of metric,
//                          reserved and eBit
// + eBit       : bool : Input value for set operation
// RETURN       :: void : NULL
// **/
void Sns_Model_OSPFv2::Ospfv2ExternalLinkSetEBit(UInt32 *ospfMetric, bool eBit)
{
	UInt32 x = eBit;

	//masks eBit within boundry range
	x = x & maskInt(32, 32);

	//clears the 32nd bit
	*ospfMetric = *ospfMetric & (~(maskInt(32, 32)));

	//setting the value of x in ospfMetric
	*ospfMetric = *ospfMetric | x;
}

// /**
// FUNCTION     :: Ospfv2ExternalLinkSetMetric()
// LAYER        :: NETWORK
// PURPOSE      :: Set the value of metric for Ospfv2ExternalLinkInfo
// PARAMETERS   ::
// + ospfMetric : UInt32* : The variable containing the value of metric,
//                          reserved and eBit
// + metric     :UInt32 : Input value for set operation
// RETURN       :: void : NULL
// **/
void Sns_Model_OSPFv2::Ospfv2ExternalLinkSetMetric(UInt32 *ospfMetric, UInt32 metric)
{
	//masks metric within boundry range
	metric = metric & maskInt(9, 32);

	//clears first 24 bits
	*ospfMetric = *ospfMetric & maskInt(25, 32);

	//setting the value of metric in ospfMetric
	*ospfMetric = *ospfMetric | LshiftInt(metric, 24);
}

// /**
// FUNCTION     :: Ospfv2ExternalLinkGetMetric()
// LAYER        :: NETWORK
// PURPOSE      :: Returns the value of metric for Ospfv2ExternalLinkInfo
// PARAMETERS   ::
// + ospfMetric : UInt32: The variable containing the value of metric,
//                        reserved and eBit
// RETURN       :: UInt32
// **/
UInt32 Sns_Model_OSPFv2::Ospfv2ExternalLinkGetMetric(UInt32 ospfMetric)
{
	UInt32 metric = ospfMetric;

	//clears the last 8 bits
	metric = metric & maskInt(1, 24);

	//right shift 8 bits so that last 24 bits represent metric
	metric = RshiftInt(metric, 24);

	return metric;
}


//-------------------------------------------------------------------------//
// NAME: Ospfv2FreeList
// PURPOSE: Free list and its allocated memory.  "type" is used
//          to indicate whether the list contains a Message
//          structure or not.  If so, call MESSAGE_Free() instead of
//          MEM_free().
// RETURN: None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2FreeList(Ospfv2List* list, bool type)
{
	Ospfv2ListItem* item = NULL;
	Ospfv2ListItem* tempItem = NULL;

	item = list->first;

	while (item)
	{
		tempItem = item;
		item = item->next;

		if (type == FALSE)
		{
			xfree(tempItem->data);
		}
		else
		{
			delete((Sns_Message*)tempItem->data);
		}

		xfree(tempItem);
	}

	xfree(list);
}

//-------------------------------------------------------------------------//
// NAME     : Ospfv2GetInterfaceIndexFromlinkData
// PURPOSE  : to get interface index from linkData
// RETURN   : interface index.
//-------------------------------------------------------------------------//
int Sns_Model_OSPFv2::Ospfv2GetInterfaceIndexFromlinkData(unsigned linkData)
{
	unsigned int i;

	for (i = 0; i < (UInt32) numberInterfaces; i++)
	{
		if (ospf->iface[i].isVirtualInterface/*|| ip->interfaceInfo[i]->isUnnumbered*/)
		{
			if((UInt32)i == linkData)
			{
				return i;
			}
		}
		else  if (ospf->iface[i].address == linkData)
		{
			return i;
		}
	}

	return -1;
}

//-------------------------------------------------------------------------//
// NAME     : Ospfv2GetInterfaceForThisNeighbor
// PURPOSE  : Get interface on which this neighbor is attached.
// RETURN   : The interface index we are looking for, or -1 if not found.
//-------------------------------------------------------------------------//
int Sns_Model_OSPFv2::Ospfv2GetInterfaceForThisNeighbor(unsigned neighborAddr)
{
	int i;
	Ospfv2ListItem* tempListItem = NULL;
	Ospfv2Neighbor* tempNeighborInfo = NULL;
	for (i = 0; i < numberInterfaces; i++)
	{
		if (ospf->iface[i].type == OSPFv2_NON_OSPF_INTERFACE)
		{
			continue;
		}
		if(ospf->iface[i].address == UNKNOWNADDRESS)
		{
			continue;
		}
		tempListItem = ospf->iface[i].neighborList->first;

		// Search for the neighbor in my neighbor list.
		while (tempListItem)
		{
			tempNeighborInfo = (Ospfv2Neighbor*) tempListItem->data;

			ERROR_Assert(!tempNeighborInfo,"Neighbor not found in the Neighbor list");

			if (tempNeighborInfo->neighborIPAddress == neighborAddr)
			{
				// Found the neighbor we are looking for.
				return i;
			}

			tempListItem = tempListItem->next;
		}
	}

	return -1;
}


//-------------------------------------------------------------------------//
// NAME     : Ospfv2DeleteList
// PURPOSE  : Free all items of list but doesn't xfree list.  "type" is used
//            to indicate whether the list contains a Message
//            structure or not.  If so, call MESSAGE_Free() instead of
//            MEM_free().
// RETURN: None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2DeleteList(Ospfv2List* list, bool type)
{
	Ospfv2ListItem* item = NULL;
	Ospfv2ListItem* tempItem = NULL;

	item = list->first;

	while (item)
	{
		tempItem = item;
		item = item->next;

		if (type == FALSE)
		{
			xfree(tempItem->data);
		}
		else
		{
			delete((Sns_Message*) tempItem->data);
		}

		xfree(tempItem);
		list->size--;
	}

	ERROR_Assert(list->size != 0, "List is being deleted!! Size must be 0\n");
	memset(list, 0, sizeof(Ospfv2List));

}

// /**
// FUNCTION     :: Ospfv2DatabaseDescriptionPacketSetInit()
// LAYER        :: NETWORK
// PURPOSE      :: Set the value of init for Ospfv2DatabaseDescriptionPacket
// PARAMETERS   ::
// + ospfDbDp   : unsigned char* : The variable containing the value of
//                                 masterSlave,more,init and reserved2
// + init       : BOOL : Input value for set operation
// RETURN       ::  void : NULL
// **/
void Sns_Model_OSPFv2::Ospfv2DatabaseDescriptionPacketSetInit(unsigned char *ospfDbDp,bool init)
{
	unsigned char x = (unsigned char)init;

	//masks init within boundry range
	x = x & maskChar(8, 8);

	//clears the first bit
	*ospfDbDp = *ospfDbDp & (~(maskChar(3, 3)));

	//setting the value of x in ospfDbDp
	*ospfDbDp = *ospfDbDp | LshiftChar(x, 3);
}

// /**
// FUNCTION     :: Ospfv2DatabaseDescriptionPacketSetMore()
// LAYER        :: NETWORK
// PURPOSE      :: Set the value of more for Ospfv2DatabaseDescriptionPacket
// PARAMETERS   ::
// + ospfDbDp   : unsigned char* : The variable containing the value of
//                                 masterSlave,more,init and reserved2
// + more       : BOOL : Input value for set operation
// RETURN       ::  void : NULL
// **/
void Sns_Model_OSPFv2::Ospfv2DatabaseDescriptionPacketSetMore(unsigned char *ospfDbDp,bool more)
{
	unsigned char x = (unsigned char)more;

	//masks more within boundry range
	x = x & maskChar(8, 8);

	//clears the second bit
	*ospfDbDp = *ospfDbDp & (~(maskChar(2, 2)));

	//setting the value of x in ospfDbDp
	*ospfDbDp = *ospfDbDp | LshiftChar(x, 2);
}

// /**
// FUNCTION     :: Ospfv2DatabaseDescriptionPacketSetMS()
// LAYER        :: NETWORK
// PURPOSE      :: Set the value of ms for Ospfv2DatabaseDescriptionPacket
// PARAMETERS   ::
// + ospfDbDp   : unsigned char* : The variable containing the value of
//                                 masterSlave,more,init and reserved2
// + ms         : BOOL : Input value for set operation
// RETURN       ::  void : NULL
void Sns_Model_OSPFv2::Ospfv2DatabaseDescriptionPacketSetMS(unsigned char *ospfDbDp,bool ms)
{
	unsigned char x = (unsigned char)ms;

	//masks ms within boundry range
	x = x & maskChar(8, 8);

	//clears the first bit
	*ospfDbDp = *ospfDbDp & (~(maskChar(1, 1)));

	//setting the value of x in ospfDbDp
	*ospfDbDp = *ospfDbDp | LshiftChar(x, 1);
}

// /**
// FUNCTION     :: Ospfv2DatabaseDescriptionPacketSetRsrvd2()
// LAYER        :: NETWORK
// PURPOSE      :: Set the value of reserved2 for
//                Ospfv2DatabaseDescriptionPacket
// PARAMETERS   ::
// + ospfDbDp   : unsigned char* : The variable containing the value of
//                                 masterSlave,more,init and reserved2
// + reserved2  : BOOL : Input value for set operation
// RETURN      :: void : NULL
// **/
void Sns_Model_OSPFv2::Ospfv2DatabaseDescriptionPacketSetRsrvd2(unsigned char *ospfDbDp,unsigned char reserved2)
{
	//masks reserved within boundry range
	reserved2 = reserved2 & maskChar(4, 8);

	//clears the last five bits
	*ospfDbDp = *ospfDbDp & maskChar(1, 3);

	//setting the value of reserved2 in ospfDbDp
	*ospfDbDp = *ospfDbDp | reserved2;
}

// /**
// FUNCTION     :: Ospfv2DatabaseDescriptionPacketGetInit()
// LAYER        :: NETWORK
// PURPOSE      :: Returns the value of init for
//                Ospfv2DatabaseDescriptionPacket
// PARAMETERS   ::
// + ospfDbDp   : unsigned char : The variable containing the value of
//                                masterSlave,more,init and reserved2
// RETURN VALUE :: BOOL
// **/
bool Sns_Model_OSPFv2::Ospfv2DatabaseDescriptionPacketGetInit(unsigned char ospfDbDp)
{
	unsigned char init = ospfDbDp;

	//clears all the bits except third bit
	init = init & maskChar(3, 3);

	//Right shifts so that last bit represents init
	init = RshiftChar(init, 3);

	return (bool)init;
}

// /**
// FUNCTION     :: Ospfv2DatabaseDescriptionPacketGetMore()
// LAYER        :: NETWORK
// PURPOSE      :: Returns the value of more for
//                Ospfv2DatabaseDescriptionPacket
// PARAMETERS   ::
// + ospfDbDp   : unsigned char : The variable containing the value of
//                                masterSlave,more,init and reserved2
// RETURN       :: BOOL
// **/
bool Sns_Model_OSPFv2::Ospfv2DatabaseDescriptionPacketGetMore(unsigned char ospfDbDp)
{
	unsigned char more = ospfDbDp;

	//clears all the bits except second bit
	more = more & maskChar(2, 2);

	//Right shifts so that last bit represents more
	more = RshiftChar(more, 2);

	return (bool)more;
}

// /**
// FUNCTION     :: Ospfv2DatabaseDescriptionPacketGetMS()
// LAYER        :: NETWORK
// PURPOSE      :: Returns the value of ms for
//                 Ospfv2DatabaseDescriptionPacket
// PARAMETERS   ::
// + ospfDbDp   : unsigned char : The variable containing the value of
//                                masterSlave,more,init and reserved2
// RETURN       :: BOOL
// **/
bool Sns_Model_OSPFv2::Ospfv2DatabaseDescriptionPacketGetMS(unsigned char ospfDbDp)
{
	unsigned char ms = ospfDbDp;

	//clears all the bits except first bit
	ms = ms & maskChar(1, 1);

	//Right shifts so that last bit represents masterSlave
	ms = RshiftChar(ms, 1);

	return (bool)ms;
}

void Sns_Model_OSPFv2::convertIpAddressToString(unsigned address,char addrStr[SNS_MAX_STRING_LENGTH])
{
	unsigned tempArry[4];
	for(int i=0;i<4;i++)
	{
		tempArry[3-i]=address%256;
		address/=256;
	}
	sprintf(addrStr,"%u.%u.%u.%u\0",tempArry[0],tempArry[1],tempArry[2],tempArry[3]);
}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2PrintRoutingTable
// PURPOSE      :Prints routing table to the screen
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2PrintRoutingTable()
{
	int i;
	Ospfv2RoutingTableRow* rowPtr = (Ospfv2RoutingTableRow*)BUFFER_GetData(&ospf->routingTable.buffer);
	printf("\nSimClock:%.2f\n",SNS_Clock_ConvertToSecond(SimClock()));

	printf("\n        Routing table for node %u at time %.2f\n",Cur_Node_id, SNS_Clock_ConvertToSecond(SimClock()));
	printf("   ---------------------------------------------------------------------------------------------------------\n");
	printf("   destination           mask            nextHop     metric   destType       pathType    areaId  type2Metric\n");
	printf("   ---------------------------------------------------------------------------------------------------------\n");

	for (i = 0; i < ospf->routingTable.numRows; i++)
	{
		char destStr[SNS_MAX_STRING_LENGTH];
		char maskStr[SNS_MAX_STRING_LENGTH];
		char nextHopStr[SNS_MAX_STRING_LENGTH];
		char destTypeStr[100];
		char pathTypeStr[100];

		if (rowPtr[i].flag == OSPFv2_ROUTE_INVALID)
		{
			continue;
		}

		convertIpAddressToString(rowPtr[i].destAddr, destStr);
		convertIpAddressToString(rowPtr[i].addrMask, maskStr);
		convertIpAddressToString(rowPtr[i].nextHop, nextHopStr);

		if (rowPtr[i].destType == OSPFv2_DESTINATION_NETWORK)
		{
			strcpy(destTypeStr, "NETWORK");
		}
		else
		{
			strcpy(destTypeStr, "ROUTER");
		}

		if (rowPtr[i].pathType == OSPFv2_INTRA_AREA)
		{
			strcpy(pathTypeStr, "INTRA-AREA");
		}
		else if (rowPtr[i].pathType == OSPFv2_INTER_AREA)
		{
			strcpy(pathTypeStr, "INTER-AREA");
		}
		else if (rowPtr[i].pathType == OSPFv2_TYPE1_EXTERNAL)
		{
			strcpy(pathTypeStr, "TYPE1-EXTERNAL");
		}
		else if (rowPtr[i].pathType == OSPFv2_TYPE2_EXTERNAL)
		{
			strcpy(pathTypeStr, "TYPE2-EXTERNAL");
		}
		else
		{
			ERROR_Assert(FALSE, "Unknown path type in routing table\n");
		}

		printf("  %15s  %15s  %15s  %4d  %10s  %15s",destStr,maskStr,nextHopStr,rowPtr[i].metric,destTypeStr,pathTypeStr);

		if (rowPtr[i].pathType == OSPFv2_TYPE2_EXTERNAL	|| rowPtr[i].pathType == OSPFv2_TYPE1_EXTERNAL)
		{
			printf("    ***   %4d\n", rowPtr[i].type2Metric);
		}
		else
		{
			printf("     %u\n", rowPtr[i].areaId);
		}
	}

	printf("\n");

}

//-------------------------------------------------------------------------//
// NAME: Ospfv2PrintHelloPacket
// PURPOSE: Print out the content of the Hello packet.
// RETURN: None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2PrintHelloPacket(Ospfv2HelloPacket* helloPkt,int interfaceIndex)
{
	int i;
	int numNeighbor;
	unsigned* tempNeighbor = NULL;
	char nbrAddrStr[SNS_MAX_STRING_LENGTH];

	numNeighbor = (helloPkt->commonHeader.packetLength- sizeof(Ospfv2HelloPacket)) / sizeof(unsigned);

	tempNeighbor = (unsigned*)(helloPkt + 1);

	ERROR_Assert(!tempNeighbor,"Neighbor not found in the Neighbor list\n");

	printf("Node %u(%d): Hello packet content:\n", Cur_Node_id,interfaceIndex);

	printf("    number of neighbor = %d\n", numNeighbor);

	for (i = 0; i < numNeighbor; i++)
	{
		convertIpAddressToString(tempNeighbor[i], nbrAddrStr);
		printf("    neighbor[%d] = %15s\n", i + 1, nbrAddrStr);
	}
}

//-------------------------------------------------------------------------//
// NAME: Ospfv2PrintNeighborList
// PURPOSE:  Print out this node's neighbor list.
// RETURN: None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2PrintNeighborList()
{
	int i;
	Ospfv2Neighbor* tempNeighborInfo = NULL;
	Ospfv2ListItem* tempListItem = NULL;

	printf("Neighbor list for node %u\n", Cur_Node_id);
	printf("    number of interfaces = %d\n", numberInterfaces);
	printf("    size is %d\n", ospf->neighborCount);

	for (i = 0; i < numberInterfaces; i++)
	{
		int j = 1;
		char addrStr[SNS_MAX_STRING_LENGTH];
		char nbrStr[SNS_MAX_STRING_LENGTH];

		if (ospf->iface[i].type == OSPFv2_NON_OSPF_INTERFACE)
		{
			continue;
		}
		convertIpAddressToString(ospf->iface[i].address, addrStr);
		printf("    neighbors on interface %15s\n", addrStr);

		tempListItem = ospf->iface[i].neighborList->first;

		// Print out each of our neighbors in our neighbor list.
		while (tempListItem)
		{
			tempNeighborInfo = (Ospfv2Neighbor*) tempListItem->data;
			ERROR_Assert(tempNeighborInfo, "Neighbor data not found\n");
			convertIpAddressToString(tempNeighborInfo->neighborID, nbrStr);

			printf("        neighbor[%d] = %15s\n", j, nbrStr);

			tempListItem = tempListItem->next;
			j += 1;
		}
	}
}
//-------------------------------------------------------------------------//
// NAME         :Ospfv2PrintLSA
// PURPOSE      :Print out the content of an LSA.
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2PrintLSA(char* LSA)
{
	Ospfv2LinkStateHeader* LSHeader = (Ospfv2LinkStateHeader*) LSA;
	char advRt[20];
	int i;

	convertIpAddressToString(LSHeader->advertisingRouter, advRt);

	// LSA is a router LSA.
	if (LSHeader->linkStateType == OSPFv2_ROUTER)
	{
		Ospfv2RouterLSA* routerLSA = (Ospfv2RouterLSA*) LSA;
		Ospfv2LinkInfo* linkList = (Ospfv2LinkInfo*) (routerLSA + 1);

		printf("    LSA is a router LSA\n");
		printf("    LSA from node %s contains:\n", advRt);

		for (i = 0; i < routerLSA->numLinks; i++)
		{
			int numTos;
			char linkID[20];
			char linkData[20];

			convertIpAddressToString(linkList->linkID, linkID);
			convertIpAddressToString(linkList->linkData, linkData);

			printf("    linkID = %15s, linkData = %15s, metric = %d, type = %d\n",linkID, linkData,linkList->metric, linkList->type);

			// Place the linkList pointer properly
			numTos = linkList->numTOS;
			linkList = (Ospfv2LinkInfo*)((QospfPerLinkQoSMetricInfo*)(linkList + 1) + numTos);
		}
	}
	// LSA is a network LSA.
	else if (LSHeader->linkStateType == OSPFv2_NETWORK)
	{
		int numLink;
		unsigned netMask;
		char netMaskStr[SNS_MAX_STRING_LENGTH];
		char rtrAddrStr[SNS_MAX_STRING_LENGTH];

		Ospfv2NetworkLSA* networkLSA = (Ospfv2NetworkLSA*) LSA;

		unsigned* rtrAddr = ((unsigned*) (networkLSA + 1)) + 1;

		memcpy(&netMask, networkLSA + 1, sizeof(unsigned));
		convertIpAddressToString(netMask, netMaskStr);

		printf("    LSA is a network LSA\n");
		printf("    LSA from node %s contains:\n", advRt);

		numLink = (networkLSA->LSHeader.length- sizeof(Ospfv2NetworkLSA) - 4)/ (sizeof(unsigned));

		printf("    LSA contains %d links\n", numLink);
		printf("    Network Mask = %15s\n", netMaskStr);

		for (i = 0; i < numLink; i++)
		{
			convertIpAddressToString(rtrAddr[i], rtrAddrStr);
			printf("    Attached router = %15s\n", rtrAddrStr);
		}
	}
	else if ((LSHeader->linkStateType == OSPFv2_NETWORK_SUMMARY)|| (LSHeader->linkStateType == OSPFv2_ROUTER_SUMMARY))
	{
		char destAddr[20];

		convertIpAddressToString(LSHeader->linkStateID, destAddr);

		printf("    LSA is Type %d Summary LSA\n", LSHeader->linkStateType);
		printf("    Advertising Router = %s\n", advRt);
		printf("    Dest = %s\n", destAddr);
		printf("    linkStateAge %d\n", LSHeader->linkStateAge);
	}
	// BGP-OSPF Patch Start
	else if (LSHeader->linkStateType == OSPFv2_ROUTER_AS_EXTERNAL)
	{
		Ospfv2ExternalLinkInfo* linkInfo;
		char netStr[100];
		char maskStr[100];

		linkInfo = (Ospfv2ExternalLinkInfo*) (LSHeader + 1);
		convertIpAddressToString(LSHeader->linkStateID, netStr);
		convertIpAddressToString(linkInfo->networkMask, maskStr);
		printf("    LSA is AS External LSA\n");
		printf("    Advertising Router = %15s\n", advRt);
		printf("    Dest = %15s\n", netStr);
		printf("    DestMask = %15s\n", maskStr);
	}
	// BGP-OSPF Patch End

	// M-OSPF Patch Start
	else if (LSHeader->linkStateType == OSPFv2_GROUP_MEMBERSHIP)
	{
		//char linkStateID[100];
		//char vertexID[100];

		//MospfGroupMembershipLSA* groupMembershipLSA =
		//	(MospfGroupMembershipLSA*)LSA;

		//MospfGroupMembershipInfo* grpMemberList =
		//	(MospfGroupMembershipInfo*)(groupMembershipLSA + 1);

		//int numLinks = (groupMembershipLSA->LSHeader.length
		//	-  (sizeof(MospfGroupMembershipLSA)))
		//	/ (sizeof(MospfGroupMembershipInfo));

		//IO_ConvertIpAddressToString(LSHeader->linkStateID,
		//	linkStateID);

		//printf ("   %8s  %10s   %4d     %2d    %2d \n",
		//	advRt, linkStateID, LSHeader->linkStateAge,
		//	LSHeader->linkStateSequenceNumber, numLinks);

		//for (i = 0; i < numLinks; i++)
		//{
		//	IO_ConvertIpAddressToString(grpMemberList[i].vertexID,
		//		vertexID);

		//	printf("    %55d  %10s\n", grpMemberList[i].vertexType,
		//		vertexID);
		//}
		//printf("\n\n");
	}
	// M-OSPF Patch End
	else
	{
		if (OSPFv2_DEBUG_LSDB)
		{
			printf("    No valid LSA \n");
		}
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2PrintRouterLSAListForThisArea()
// PURPOSE      :Print the content of the Router LSA list for this area
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2PrintRouterLSAListForThisArea(Ospfv2Area* thisArea)
{
	Ospfv2ListItem* item = NULL;

	printf("    Router LSAs for node %u, area 0x%x\n",
		Cur_Node_id, thisArea->areaID);
	printf("    size is %d\n", thisArea->routerLSAList->size);

	item = thisArea->routerLSAList->first;

	// Print each link state information that we have in our
	// link state database.
	while (item)
	{
		Ospfv2PrintLSA((char*) item->data);

		item = item->next;
	}
}


//-------------------------------------------------------------------------//
// NAME         :Ospfv2PrintNetworkLSAListForThisArea()
// PURPOSE      :Print the content of the Network LSA list for this area.
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2PrintNetworkLSAListForThisArea(Ospfv2Area* thisArea)
{
	Ospfv2ListItem* item = NULL;

	printf("    Network LSAs for node %u, area 0x%x\n",
		Cur_Node_id, thisArea->areaID);
	printf("    size is %d\n", thisArea->networkLSAList->size);

	item = thisArea->networkLSAList->first;

	// Print each link state information that we have in our
	// link state database.
	while (item)
	{
		Ospfv2PrintLSA((char*) item->data);
		item = item->next;
	}
}


//-------------------------------------------------------------------------//
// NAME         :Ospfv2PrintSummaryLSAListForThisArea()
// PURPOSE      :Print the content of the Router and Network Summary
//               LSA list for this area
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2PrintSummaryLSAListForThisArea(Ospfv2Area* thisArea)
{
	Ospfv2ListItem* item = NULL;

	printf("    Router Summary LSAs for node %u, area 0x%x\n",
		Cur_Node_id, thisArea->areaID);
	printf("    size is %d\n", thisArea->routerSummaryLSAList->size);

	item = thisArea->routerSummaryLSAList->first;

	// Print each link state information that we have in our
	// link state database.
	while (item)
	{
		Ospfv2PrintLSA((char*) item->data);
		item = item->next;
	}

	printf("    Network Summary LSAs for node %u, area 0x%x\n",
		Cur_Node_id, thisArea->areaID);
	printf("    size is %d\n", thisArea->networkSummaryLSAList->size);

	item = thisArea->networkSummaryLSAList->first;

	// Print each link state information that we have in our
	// link state database.
	while (item)
	{
		Ospfv2PrintLSA((char*) item->data);
		item = item->next;
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2PrintRouterLSAList()
// PURPOSE      :Print the content of the Router LSA list.
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2PrintRouterLSAList()
{
	Ospfv2ListItem* item = NULL;

	printf("Router LSAs for node %u\n", Cur_Node_id);

	for (item = ospf->area->first; item; item = item->next)
	{
		Ospfv2Area* thisArea = (Ospfv2Area*) item->data;

		Ospfv2PrintRouterLSAListForThisArea(thisArea);
	}
}


//-------------------------------------------------------------------------//
// NAME         :Ospfv2PrintNetworkLSAList
// PURPOSE      :Print the content of the Network LSA list.
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2PrintNetworkLSAList()
{
	Ospfv2ListItem* item = NULL;

	printf("Network LSAs for node %u\n", Cur_Node_id);

	for (item = ospf->area->first; item; item = item->next)
	{
		Ospfv2Area* thisArea = (Ospfv2Area*) item->data;

		Ospfv2PrintNetworkLSAListForThisArea(thisArea);
	}
}


//-------------------------------------------------------------------------//
// NAME         :Ospfv2PrintSummaryLSAList()
// PURPOSE      :Print the content of the Router and Network Summary
//               LSA list.
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2PrintSummaryLSAList()
{
	Ospfv2ListItem* item = NULL;

	printf("Summary LSAs for node %u\n", Cur_Node_id);

	for (item = ospf->area->first; item; item = item->next)
	{
		Ospfv2Area* thisArea = (Ospfv2Area*) item->data;

		Ospfv2PrintSummaryLSAListForThisArea(thisArea);
	}
}
// BGP-OSPF Patch Start
//-------------------------------------------------------------------------//
// NAME         :Ospfv2PrintASExternalLSA()
// PURPOSE      :Print the content of the AS External LSA list for this node.
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2PrintASExternalLSA()
{
	Ospfv2ListItem* item;

	if (!ospf->asExternalLSAList)
	{
		return;
	}
	item = ospf->asExternalLSAList->first;

	printf("AS External LSA list for node %u\n", Cur_Node_id);
	printf("Size is = %d\n", ospf->asExternalLSAList->size);

	// Print each link state information that we have in our
	// link state database.
	while (item)
	{
		Ospfv2PrintLSA((char*) item->data);
		item = item->next;
	}
	printf("\n");
}
// BGP-OSPF Patch End


//-------------------------------------------------------------------------//
// NAME         :Ospfv2PrintLSDB()
// PURPOSE      :Print the content of entire LSDB of a node.
// ASSUMPTION   :None.
// RETURN VALUE :None.
//-------------------------------------------------------------------------//
void Sns_Model_OSPFv2::Ospfv2PrintLSDB()
{
	char timeStringInSecond[SNS_MAX_STRING_LENGTH];

	printf("SimClock:%.2f\n",SNS_Clock_ConvertToSecond(SimClock()));
	printf("---------------------------------------------------\n");
	printf("        LSDB OF NODE %u at time %15s\n",
		Cur_Node_id, timeStringInSecond);
	Ospfv2PrintRouterLSAList();
	Ospfv2PrintNetworkLSAList();
	Ospfv2PrintSummaryLSAList();
	Ospfv2PrintASExternalLSA();
	printf("---------------------------------------------------\n");
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2GetNeighborStateString()
// PURPOSE      :Based on eighbor state value get correct string.
// ASSUMPTION   :None
// RETURN VALUE :None
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2GetNeighborStateString(Ospfv2NeighborState state,char* str)
{
	if (state == S_NeighborDown)
	{
		strcpy(str, "S_NeighborDown");
	}
	else if (state == S_Attempt)
	{
		strcpy(str, "S_Attempt");
	}
	else if (state == S_Init)
	{
		strcpy(str, "S_Init");
	}
	else if (state == S_TwoWay)
	{
		strcpy(str, "S_TwoWay");
	}
	else if (state == S_ExStart)
	{
		strcpy(str, "S_ExStart");
	}
	else if (state == S_Exchange)
	{
		strcpy(str, "S_Exchange");
	}
	else if (state == S_Loading)
	{
		strcpy(str, "S_Loading");
	}
	else if (state == S_Full)
	{
		strcpy(str, "S_Full");
	}
	else
	{
		strcpy(str, "Unknown");
	}
}
void Sns_Model_OSPFv2::Ospfv2GetIEString(Ospfv2NeighborEvent eventType,char* str)
{
	switch(eventType)
	{
		case S_HelloReceived:
			strcpy(str,"HelloReceived");
			break;
		case S_Start:
			strcpy(str,"Start");
			break;
		case S_TwoWayReceived:
			strcpy(str,"TwoWayReceived");
			break;
		case S_NegotiationDone:
			strcpy(str,"NegotiationDone");
			break;
		case S_ExchangeDone:
			strcpy(str,"ExchangeDone");
			break;
		case S_BadLSReq:
			strcpy(str,"BadLSReq");
			break;
		case S_LoadingDone:
			strcpy(str,"LoadingDone");
			break;
		case S_AdjOk:
			strcpy(str,"AdjOk");
			break;
		case S_SeqNumberMismatch:
			strcpy(str,"SeqNumberMismatch");
			break;
		case S_OneWay:
			strcpy(str,"OneWay");
			break;
		case S_KillNbr:
			strcpy(str,"KillNbr");
			break;
		case S_InactivityTimer:
			strcpy(str,"InactivityTimer");
			break;
		case S_LLDown:
			strcpy(str,"LLDown");
			break;
		default:
			str="Unknown";
			break;
	}
}

//-------------------------------------------------------------------------//
// NAME         :Ospfv2PrintNeighborState()
// PURPOSE      :Print the current state of each neighbor.
// ASSUMPTION   :None
// RETURN VALUE :NULL
//-------------------------------------------------------------------------//

void Sns_Model_OSPFv2::Ospfv2PrintNeighborState()
{
	int i;

	printf("\n\n      Neighbor state for Node %u:\n", Cur_Node_id);

	for (i = 0; i < numberInterfaces; i++)
	{
		Ospfv2ListItem* listItem = NULL;
		Ospfv2Neighbor* nbrInfo = NULL;

		if (ospf->iface[i].type == OSPFv2_NON_OSPF_INTERFACE)
		{
			continue;
		}
		listItem = ospf->iface[i].neighborList->first;

		while (listItem)
		{
			char destStr[SNS_MAX_STRING_LENGTH];
			char stateStr[20];
			nbrInfo = (Ospfv2Neighbor*) listItem->data;

			convertIpAddressToString(nbrInfo->neighborIPAddress, destStr);
			Ospfv2GetNeighborStateString(nbrInfo->state, stateStr);

			printf("\nState of neighbor %15s : %15s\n", destStr, stateStr);

			listItem = listItem->next;
		}
	}
}

void Sns_Model_OSPFv2::Ospfv2PrintLinkList(Ospfv2List* shortestPathList)
{
	char vertexIdStr[SNS_MAX_STRING_LENGTH];
	Ospfv2ListItem* listItem=shortestPathList->first;
	printf("\nNode%d's ShortestPathList:",Cur_Node_id);
	for(int i=0;i<shortestPathList->size;i++)
	{
		Ospfv2Vertex* listEntry=(Ospfv2Vertex*)listItem->data;
		convertIpAddressToString(listEntry->vertexId, vertexIdStr);
		printf("%16s ",vertexIdStr);
		listItem=listItem->next;
	}
	printf("\n");
}

void Sns_Model_OSPFv2::Ospfv2PrintNextHopList(Ospfv2List* nextHopList)
{
	char nextHopStr[SNS_MAX_STRING_LENGTH];
	Ospfv2ListItem* listItem=nextHopList->first;
	printf("nextHopList:");
	for(int i=0;i<nextHopList->size;i++)
	{
		Ospfv2NextHopListItem* listEntry=(Ospfv2NextHopListItem*)listItem->data;
		convertIpAddressToString(listEntry->nextHop, nextHopStr);
		printf("%16s ",nextHopStr);
		listItem=listItem->next;
	}
	printf("\n");
}

void Sns_Model_OSPFv2::Ospfv2PrintAllNextHopList(Ospfv2List* shortestPathList)
{
	char vertexIdStr[SNS_MAX_STRING_LENGTH];
	char nextHopStr[SNS_MAX_STRING_LENGTH];
	Ospfv2ListItem* listItem=shortestPathList->first;
	printf("nextHopList:\n");
	for(int i=0;i<shortestPathList->size;i++)
	{
		Ospfv2Vertex* listEntry=(Ospfv2Vertex*)listItem->data;
		Ospfv2ListItem* vertexItem=listEntry->nextHopList->first;
		convertIpAddressToString(listEntry->vertexId, vertexIdStr);
		printf("%16s: ",vertexIdStr);
		for(int j=0;j<listEntry->nextHopList->size;j++)
		{
			Ospfv2NextHopListItem* vertexEntry=(Ospfv2NextHopListItem*)vertexItem->data;
			convertIpAddressToString(vertexEntry->nextHop, nextHopStr);
			printf("%16s ",nextHopStr);
			vertexItem=vertexItem->next;
		}
		printf("\n");
		listItem=listItem->next;
	}
}
void Sns_Model_OSPFv2::Ospfv2PrintMsgEventName(Sns_Message* msg,bool isDone)
{

	char EVENT_NAME[][SNS_MAX_STRING_LENGTH]={"MSG_InEVENT_OspfIncrementLSAge",
		"MSG_InEVENT_OspfInactivityTimer",
		"MSG_InEVENT_OspfRxmtTimer",
		"MSG_InEVENT_OspfScheduleHello",
		"MSG_InEVENT_OspfScheduleLSDB",
		"MSG_InEVENT_QospfScheduleLSDB",
		"MSG_InEVENT_QospfInterfaceStatusMonitor",
		"MSG_InEVENT_QospfSetNewConnection",
		"MSG_InEVENT_OspfWaitTimer",
		"MSG_InEVENT_OspfFloodTimer",
		"MSG_InEVENT_OspfDelayedAckTimer",
		"MSG_InEVENT_OspfScheduleSPF",
		"MSG_InEVENT_OspfNeighborEvent",
		"MSG_InEVENT_OspfInterfaceEvent",
		"MSG_InEVENT_OspfHandleRoutingProtocolPacket"};
	char *EVENT_DONE;
	if(isDone)
	{
		EVENT_DONE="has been done";
	}
	else
	{
		EVENT_DONE="start";
	}
	printf("Node %u 's msgEvent: %s %s\n",Cur_Node_id,EVENT_NAME[msg->Event_Name],EVENT_DONE);
}

//

void Sns_Model_OSPFv2::Ospfv2ManuallyScheduleRouterLSA(InterfaceInfoType* info)
{
	for(int i=0;i<numberInterfaces;i++)
	{
		if(ospf->iface[i].address!=info[i].address)
		{
			ospf->iface[i].address=info[i].address;
			ospf->iface[i].subnetMask=info[i].subnetMask;
			Ospfv2ScheduleRouterLSA(ospf->iface[i].areaId, FALSE);

//			printf( "                                            Test_Memory!!!\n" ) ;

		}
	}
}