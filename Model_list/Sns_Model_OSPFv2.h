/*
* Copyright (c) 2014,北京航空航天大学
* All rights reserved.
*
* 系统名称: SPACE NETWORK SIMULATION SYSTEM
* 作    者: 张涛
* 当前版本: SNS 1.0
* 
* 文件名称: Sns_Model_OSPFv2.h
* 当前版本: V 1.0.0
* 文件标识: Sns_Model_OSPFv2类头文件
* 功能描述: 
* 完 成 人: 
* 联系方式: 
* 完成日期: 
*
* 摘    要:
*/
//////////////////////////////////////////////////////////////////////

#ifndef SNS_MODEL_OSPFV2_H
#define SNS_MODEL_OSPFV2_H

#if _MSC_VER > 1000
#pragma once
#endif

/////////////本部分为模型参数描述部分/////////////
/************************************************
***Model-Info-Begin
/************************************************
**Model_Name:OSPFv2;          //模型名
**Class_Name:Sns_Model_OSPFv2;          //模型名对应的类名
**Model_Type:protocols/environment;          //模型类型：场景、节点、环境、协议
**ModelState:proceeding;         //模型开发状态：进行、完成、注册
**Abstract:
/***********************************************
**Config-Init-Variable:          //模型初始化配置参数
/*Config_VariableList_Descri
/***********************************************
**StatsData-Output-Variable:   //模型输出统计数据
/*Stats_VariableList_Descri
/************************************************
**SnsMsg-Input:                  //输入事件
*MSG_InEVENT_OspfIncrementLSAge;			//Time to increment the age of each LSA. 
*MSG_InEVENT_OspfInactivityTimer;			//Check to make sure that my neighbor is still there. 
*MSG_InEVENT_OspfRxmtTimer;			//Check to see if I need to retransmit any Packet. 
*MSG_InEVENT_OspfScheduleHello;			//Time to send out Hello packets. 
*MSG_InEVENT_OspfScheduleLSDB;			//Time to originate LSAs. 
*MSG_InEVENT_QospfScheduleLSDB;			//Q-OSPF periodic update LSA message 
*MSG_InEVENT_QospfInterfaceStatusMonitor;			//Interface status monitor message 
*MSG_InEVENT_QospfSetNewConnection;			//message for Qos application to initiate a new connection 
*MSG_InEVENT_OspfWaitTimer;			//Single Shot Wait Timer 
*MSG_InEVENT_OspfFloodTimer;			// 
*MSG_InEVENT_OspfDelayedAckTimer;			// 
*MSG_InEVENT_OspfScheduleSPF;			// 
*MSG_InEVENT_OspfNeighborEvent;			// 
*MSG_InEVENT_OspfInterfaceEvent;			// 
*MSG_InEVENT_OspfHandleRoutingProtocolPacket;			//处理接收到的数据包 
/*MesInputVariable_Descri
/************************************************
**SnsMsg-Output:                 //输出事件
*MSG_OutEVENT_OSPFv2_toNetworkIP;			//发送数据包 
/*MesOutputVariable_Descri
/***********************************************
***Model-Info-End
***********************************************/

#include "SNS_core.h" //平台库
//#include "Sns_Node_NetworkIP_OSPFv2.h"
#include "GlobleStructures.h"
#include "buffer.h"
#include "list.h"
#include "ForwardingTable.h"
// /**
// CONSTANT    :: IPTOS_PREC_INTERNETCONTROL : 0xc0
// DESCRIPTION :: IP precedence 'internet control'
// **/
#define IPTOS_PREC_INTERNETCONTROL  0xc0

// /**
// CONSTANT    :: IPPROTO_OSPF : 89
// DESCRIPTION :: IP protocol numbers for OSPF .
// **/
#define IPPROTO_OSPF            89
// /**
// CONSTANT :: ANY_INTERFACE : -1
// DESCRIPTION ::
//      This is a special addresses used in the MAC and network
//      layers. It defines any Interface.
// **/
#define ANY_INTERFACE   -1

#define OSPFv2_CURRENT_VERSION                  0x2

// Initial size of routing table maintained by OSPF.
#define OSPFv2_INITIAL_TABLE_SIZE               (10)

#define OSPFv2_LS_INFINITY                      999999

// Jitter transmissions to avoid  sychronization.
#define OSPFv2_BROADCAST_JITTER                 (40 * MILLI_SECOND)
//#define OSPFv2_BROADCAST_JITTER                 (100 * MILLI_SECOND)

// How often do we increment LS age.
// Has to be be greater than or equal to 1 second.

#define OSPFv2_LSA_INCREMENT_AGE_INTERVAL       (1 * SECOND)

// Maximum age limit for LSAs.
#define OSPFv2_LSA_MAX_AGE                      (60 * MINUTE)

// Should be based on transmission delay.  However, since
// OSPF's unit is in seconds, one second should cover most, if
// not all, transmission delays out there.
#define OSPFv2_INF_TRANS_DELAY       (1 * SECOND)

// Interval of sending hello packets (in seconds).
#define OSPFv2_HELLO_INTERVAL        (10 * SECOND)

//
#define OSPFv2_DEFAULT_OUTPUTCOST 5


// Interval to know when can we consider a routing to be dead.
#define OSPFv2_ROUTER_DEAD_INTERVAL  (4 * OSPFv2_HELLO_INTERVAL)

// Retransmission interval of sending link state request (in seconds)
#define OSPFv2_RXMT_INTERVAL         (5 * SECOND)

// How often to originate LSA.
#define OSPFv2_LS_REFRESH_TIME       (30 * MINUTE)

// Minimum time between LSA arrival.
#define OSPFv2_MIN_LS_ARRIVAL        (1 * SECOND)

// Maximum age difference to be considered more recent LSA.
#define OSPFv2_MAX_AGE_DIFF          (15 * MINUTE)

#define OSPFv2_WAIT_TIMER        OSPFv2_ROUTER_DEAD_INTERVAL

#define OSPFv2_FLOOD_TIMER       (100 * MILLI_SECOND)
//#define OSPFv2_FLOOD_TIMER       (1 * SECOND)

#define OSPFv2_MIN_LS_INTERVAL   (5 * SECOND)

#define OSPFv2_EVENT_SCHEDULING_DELAY   (1 * NANO_SECOND)

// BGP-OSPF Patch Start
// Maximum time an ASBR wait to originate AS External LSA (Injected by user)
#define OSPFv2_AS_EXTERNAL_LSA_ORIGINATION_DELAY   (2 * MINUTE)

#define OSPFv2_MAX_AS_NUMBER     65535    // maximum AS number
#define OSPFv2_MIN_AS_NUMBER     0        // minimum AS number
// BGP-OSPF Patch End

#define  OSPFv2_OPTION_EXTERNAL  0x2

#define OSPFv2_SINGLE_AREA_ID    0xFFFFFFFF
#define OSPFv2_BACKBONE_AREA     0x0
#define OSPFv2_INVALID_AREA_ID   0xFFFFFFFE

#define OSPFv2_INITIAL_SEQUENCE_NUMBER  0x80000001
#define OSPFv2_MAX_SEQUENCE_NUMBER      0x7FFFFFFF

/*
协议包发送时有三个地址：
点对点网络，目的地址为多播地址 ALLSPFRouters   224.0.0.5
在其他网络包括虚拟链路上，大多数ospf包以单播方式发起，目的地址为邻居IP
其它路由器（非DR,BDR）发送链路更新报文目的地址为ALLDRouters
*/
#define OSPFv2_ALL_SPF_ROUTERS    0xE0000005
#define OSPFv2_ALL_D_ROUTERS      0xE0000006
// /**
// CONSTANT :: ANY_DEST : 0xffffffff
// DESCRIPTION ::
//      This is a special addresses used in the MAC and network
//      layers. It defines any destination.
// **/

#define OSPFv2_DEFAULT_DESTINATION  0
#define OSPFv2_DEFAULT_MASK         0

// Cisco specifies to maximize stability, one router should not be in more
// than three areas. However, users are free to change this value.
// Ref - http://www.cisco.com/univercd/cc/td/doc/cisintwk/idg4/nd2003.htm
// [Section - OSPF Network Topology]
#define OSPFv2_MAX_ATTACHED_AREA    3

class Sns_Config_Input;
class Sns_Message;
class Sns_Scenarios;
class Sns_Node_NetworkIP_OSPFv2;
class list;

class Sns_Model_OSPFv2 : public Sns_base_model
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
		//Stats_VariableList//
	}; 
	Sns_model_Stats_Var_str Stats_Var;//模型仿真输出统计数据变量结构  

	//输入消息事件名称
	enum 
	{
		MSG_InEVENT_OspfIncrementLSAge,			//增加LSA的Age属性 
		MSG_InEVENT_OspfInactivityTimer,			//用于检查邻居是否处于活动状态的定时器 
		MSG_InEVENT_OspfRxmtTimer,			//用于重传的定时器 
		MSG_InEVENT_OspfScheduleHello,			//发送Hello包 
		MSG_InEVENT_OspfScheduleLSDB,			//产生LSDB 
		MSG_InEVENT_QospfScheduleLSDB,			// 
		MSG_InEVENT_QospfInterfaceStatusMonitor,			// 
		MSG_InEVENT_QospfSetNewConnection,			// 
		MSG_InEVENT_OspfWaitTimer,			// 
		MSG_InEVENT_OspfFloodTimer,			//洪泛定时器 
		MSG_InEVENT_OspfDelayedAckTimer,			//延迟应答定时器 
		MSG_InEVENT_OspfScheduleSPF,			//计算最短路 
		MSG_InEVENT_OspfNeighborEvent,			//处理邻居事件 
		MSG_InEVENT_OspfInterfaceEvent,			//处理端口事件 
		MSG_InEVENT_OspfHandleRoutingProtocolPacket,			//处理接收到的OSPF数据包 
		//MesInputVariable//
	};

	//输出消息事件名称
	enum 
	{
		MSG_OutEVENT_OSPFv2_toNetworkIP,			//向IP层传送数据包 
		//MesOutputVariable//
	};

public://用户自定义公有变量
	// Structure for each item of a list.
	typedef struct struct_Ospfv2_ListItem
	{
		void* data;
		clocktype timeStamp;
		struct struct_Ospfv2_ListItem* prev;
		struct struct_Ospfv2_ListItem* next;
	} Ospfv2ListItem;

	// A list that stores different types of structures.
	typedef struct struct_Ospfv2_List
	{
		int size;

		struct struct_Ospfv2_ListItem* first;       // First item in list.
		struct struct_Ospfv2_ListItem* last;        // Last item in list.
	} Ospfv2List;

	typedef struct struct_Ospfv2_NonBroadcastNeighborListItem
	{
		unsigned neighborAddr;
		struct struct_Ospfv2_NonBroadcastNeighborListItem* prev;
		struct struct_Ospfv2_NonBroadcastNeighborListItem* next;
	} Ospfv2NonBroadcastNeighborListItem;

	typedef struct struct_Ospfv2_NonBroadcastNeighborList
	{
		int size;
		struct struct_Ospfv2_NonBroadcastNeighborListItem* first;
		struct struct_Ospfv2_NonBroadcastNeighborListItem* last;
	} Ospfv2NonBroadcastNeighborList;

	// Type of nodes.
	typedef enum
	{
		OSPFv2_ROUTER_TYPE,
		OSPFv2_HOST_TYPE
	} Ospfv2RouterType;

	// Used to calculate shortest path.
	typedef enum
	{
		OSPFv2_VERTEX_ROUTER,
		OSPFv2_VERTEX_NETWORK
	} Ospfv2VertexType;

	typedef struct
	{
		unsigned outIntf;//interfaceIndex
		unsigned nextHop;
	} Ospfv2NextHopListItem;

	typedef struct
	{
		unsigned             vertexId;
		Ospfv2VertexType vertexType;
		char*                   LSA;
		Ospfv2List*      nextHopList;
		unsigned int            distance;
	} Ospfv2Vertex;


	//-------------------------------------------------------------------------//
	//                                 LSA FORMAT                              //
	//-------------------------------------------------------------------------//
	// Type of LSA.
	typedef enum
	{
		OSPFv2_ROUTER               = 1,
		OSPFv2_NETWORK              = 2,
		OSPFv2_NETWORK_SUMMARY      = 3,
		OSPFv2_ROUTER_SUMMARY       = 4,
		OSPFv2_ROUTER_AS_EXTERNAL   = 5,
		OSPFv2_GROUP_MEMBERSHIP      = 6
	} Ospfv2LinkStateType;

	// Type of link.
	typedef enum
	{
		OSPFv2_POINT_TO_POINT       = 1,
		OSPFv2_TRANSIT              = 2,
		OSPFv2_STUB                 = 3,
		OSPFv2_VIRTUAL              = 4
	} Ospfv2LinkType;

	typedef struct
	{
		short int linkStateAge;

		unsigned char ospfLsh;//qos:1, external:1, multicast:1, options1:5;

		char linkStateType;
		unsigned linkStateID;
		unsigned advertisingRouter;
		int linkStateSequenceNumber;
		short int linkStateCheckSum;
		short int length;
	} Ospfv2LinkStateHeader;

	// Each link of router LSA.
	typedef struct
	{
		unsigned linkID;
		int linkData;
		unsigned char type;
		unsigned char numTOS;
		short int metric;
	} Ospfv2LinkInfo;

	// Structure of network LSA.
	typedef struct
	{
		Ospfv2LinkStateHeader LSHeader;

		// Dynamically allocating next part.
	} Ospfv2NetworkLSA;

	// Structure of summary LSA
	typedef struct
	{
		Ospfv2LinkStateHeader LSHeader;

		// Dynamically allocate this part
	} Ospfv2SummaryLSA;

	// BGP-OSPF Patch Start
	// External link info for AS external LSA.
	typedef struct
	{
		unsigned networkMask;
		UInt32 ospfMetric;//metric:24, reserved1:7, eBit:1;
		unsigned forwardingAddress;
		unsigned externalRouterTag;
	} Ospfv2ExternalLinkInfo;

	// Structure of router LSA.
	typedef struct
	{
		Ospfv2LinkStateHeader LSHeader;

		unsigned char ospfRouterLsa;//areaBorderRouter:1, ASBoundaryRouter:1,
		//virtualLinkEndpoint:1, wildCardMulticastReceiver:1, reserved1:4;

		unsigned char reserved2;
		short int numLinks;

		// Dynamically allocating next part.
	} Ospfv2RouterLSA;

	// Structure of AS external LSA
	typedef struct
	{
		Ospfv2LinkStateHeader LSHeader;

		// Dynamically allocate this part
	} Ospfv2ASexternalLSA;
	// BGP-OSPF Patch End

	//-------------------------------------------------------------------------//
	//                         OSPFv2 PACKET FORMAT                            //
	//-------------------------------------------------------------------------//
	// Packet Type Consants //
	typedef enum
	{
		OSPFv2_HELLO = 1,
		OSPFv2_DATABASE_DESCRIPTION = 2,
		OSPFv2_LINK_STATE_REQUEST = 3,
		OSPFv2_LINK_STATE_UPDATE = 4,
		OSPFv2_LINK_STATE_ACK = 5,
		OSPFv2_UPDATE_ROUTABLE
	} Ospfv2PacketType;

	// 24 byte common header. //
	typedef struct
	{
		unsigned char version;
		unsigned char packetType;
		short int packetLength;
		unsigned routerID;
		unsigned int areaID;
		short int checkSum;            // Not used in simulation.
		short int authenticationType;  // Not used in simulation.
		char authenticationData[8];    // Not used in simulation.
	} Ospfv2CommonHeader;
	// Hello packet structure.
	typedef struct
	{
		Ospfv2CommonHeader commonHeader;
		int networkMask;

		short int helloInterval;        // In seconds.

		unsigned char options;          // Options field

		unsigned char rtrPri;

		int routerDeadInterval;         // In seconds.

		unsigned designatedRouter;
		unsigned backupDesignatedRouter;

		// Neighbors will be dynamically allocated.
	} Ospfv2HelloPacket;

	// Update packet structure.
	typedef struct
	{
		Ospfv2CommonHeader commonHeader;
		int numLSA;

		// List of LSA (allocated dynamically).
	} Ospfv2LinkStateUpdatePacket;


	// Database Description packet structure
	typedef struct
	{
		Ospfv2CommonHeader commonHeader;
		unsigned short interfaceMtu;
		unsigned char reserved1;
		unsigned char ospfDbDp;//masterSlave:1, more:1, init:1, reserved2:5;
		unsigned int ddSequenceNumber;

		// List of LSA Header (allocated dynamically)
	} Ospfv2DatabaseDescriptionPacket;

	// Item for Link State Request packet
	typedef struct
	{
		Ospfv2LinkStateType linkStateType;
		unsigned linkStateID;
		unsigned advertisingRouter;
	} Ospfv2LSRequestInfo;

	// Link State Request packet structure
	typedef struct
	{
		Ospfv2CommonHeader commonHeader;

		// This part will be allocated dynamically
	} Ospfv2LinkStateRequestPacket;

	// Ack packet structure.
	typedef struct
	{
		Ospfv2CommonHeader commonHeader;

		// List of LSA Header (allocated dynamically)
	} Ospfv2LinkStateAckPacket;


	//-------------------------------------------------------------------------//
	//                       INTERFACE DATA STRUCTURE                          //
	//-------------------------------------------------------------------------//

	// Possible interface types.
	typedef enum
	{
		OSPFv2_NON_OSPF_INTERFACE,
		OSPFv2_POINT_TO_POINT_INTERFACE,
		OSPFv2_BROADCAST_INTERFACE,
		OSPFv2_NBMA_INTERFACE,
		OSPFv2_POINT_TO_MULTIPOINT_INTERFACE,
		OSPFv2_VIRTUAL_LINK_INTERFACE
	} Ospfv2InterfaceType;

	// Different interface state.
	typedef enum
	{
		S_Down,
		S_Loopback,
		S_Waiting,
		S_PointToPoint,
		S_DROther,
		S_Backup,
		S_DR
	} Ospfv2InterfaceState;

	// Event that cause interface state change.
	typedef enum
	{
		E_InterfaceUp,
		E_WaitTimer,
		E_BackupSeen,
		E_NeighborChange,
		E_LoopInd,
		E_UnloopInd,
		E_InterfaceDown
	} Ospfv2InterfaceEvent;


	// To keep available bandwidth and average delay for a queue.
	// This information is required for Q-OSPF.
	typedef struct
	{
		unsigned char queueNo;
		int           linkBandwidth;
		int           utilizedBandwidth;
		int           availableBandwidth;

		int           propDelay;
		int           qDelay;
	} Ospfv2StatusOfQueue;

	// Various values kept for each interface.
	typedef struct
	{
		Ospfv2InterfaceType type;
		Ospfv2InterfaceState state;

		int interfaceIndex;
		//InterfaceInfoType* info;
		unsigned address;
		unsigned subnetMask;

		//virtual Link support
		bool isVirtualInterface;

		unsigned int areaId;

		clocktype helloInterval;
		clocktype routerDeadInterval;
		clocktype infTransDelay;

		int routerPriority;

		bool floodTimerSet;
		Ospfv2List* updateLSAList;

		bool delayedAckTimer;
		Ospfv2List* delayedAckList;

		clocktype networkLSAOriginateTime;  // Used only if DR on interface.
		bool networkLSTimer;                // Used only if DR on interface.
		int networkLSTimerSeqNumber;        // Used only if DR on interface.

		bool ISMTimer;

		unsigned designatedRouter;
		unsigned designatedRouterIPAddress;

		unsigned backupDesignatedRouter;
		unsigned backupDesignatedRouterIPAddress;

		int outputCost;

		clocktype rxmtInterval;

		// Not used in simulation.
		int AuType;
		char* authenticationKey;

		// This field is required for Q-OSPF, as the available
		// bandwidth and average delay for each queue of a interface is
		// required for the advertisement.Each item of the list contains
		// Ospfv2StatusOfQueue structure.
		list::LinkedList* presentStatusOfQueue;
		int  lastAdvtUtilizedBandwidth;

		Ospfv2List* neighborList;

		Ospfv2NonBroadcastNeighborList* NonBroadcastNeighborList;

		bool isEnable;

	} Ospfv2Interface;


	//-------------------------------------------------------------------------//
	//                        NEIGHBOR DATA STRUCTURE                          //
	//-------------------------------------------------------------------------//

	typedef enum
	{
		S_NeighborDown,
		S_Attempt,
		S_Init,
		S_TwoWay,
		S_ExStart,
		S_Exchange,
		S_Loading,
		S_Full
	} Ospfv2NeighborState;

	typedef enum
	{
		S_HelloReceived,
		S_Start,
		S_TwoWayReceived,
		S_NegotiationDone,
		S_ExchangeDone,
		S_BadLSReq,
		S_LoadingDone,
		S_AdjOk,
		S_SeqNumberMismatch,
		S_OneWay,
		S_KillNbr,
		S_InactivityTimer,
		S_LLDown
	} Ospfv2NeighborEvent;

	typedef enum
	{
		T_Master,
		T_Slave
	} Ospfv2MasterSlaveType;

	typedef struct
	{
		Ospfv2LinkStateHeader* LSHeader;
		unsigned int seqNumber;
	} Ospfv2LSReqItem;

	// Information needed for each neighbor.
	typedef struct
	{
		Ospfv2NeighborState state;

		// Indicates that no Hello packet has been
		// seen from this neighbor recently.
		unsigned int inactivityTimerSequenceNumber;

		// Indicates that no ACK packet is received
		// for LSA sent out.
		unsigned int rxmtTimerSequenceNumber;

		Ospfv2MasterSlaveType masterSlave;
		unsigned int DDSequenceNumber;
		Sns_Message* lastReceivedDDPacket;
		unsigned neighborID;
		int neighborPriority;
		unsigned neighborIPAddress;
		int neighborOptions;
		unsigned neighborDesignatedRouter;
		unsigned neighborBackupDesignatedRouter;

		// Lists of LSA Update packets.
		Ospfv2List* linkStateRetxList;
		bool LSRetxTimer;

		Ospfv2List* DBSummaryList;
		Ospfv2List* linkStateRequestList;

		// Retransmission purpose
		clocktype lastDDPktSent;
		Sns_Message* lastSentDDPkt;
		unsigned int LSReqTimerSequenceNumber;
	} Ospfv2Neighbor;

	typedef struct
	{
		unsigned     routerID;
		int             routerPriority;
		unsigned     routerIPAddress;
		int             routerOptions;
		unsigned     DesignatedRouter;
		unsigned     BackupDesignatedRouter;
	} Ospfv2DREligibleRouter;


	//-------------------------------------------------------------------------//
	//                      ROUTING TABLE STRUCTURE                            //
	//-------------------------------------------------------------------------//

	typedef enum
	{
		OSPFv2_DESTINATION_ABR,
		OSPFv2_DESTINATION_ASBR,
		OSPFv2_DESTINATION_ABR_ASBR,
		OSPFv2_DESTINATION_NETWORK,
		OSPFv2_DESTINATION_ROUTER
	} Ospfv2DestType;

	typedef enum
	{
		OSPFv2_INTRA_AREA,
		OSPFv2_INTER_AREA,
		OSPFv2_TYPE1_EXTERNAL,
		OSPFv2_TYPE2_EXTERNAL
	} Ospfv2PathType;

	typedef enum
	{
		OSPFv2_ROUTE_INVALID,
		OSPFv2_ROUTE_CHANGED,
		OSPFv2_ROUTE_NO_CHANGE,
		OSPFv2_ROUTE_NEW
	} Ospfv2Flag;

	// A row struct for routing table
	typedef struct
	{
		// Type of destination, either network or router
		Ospfv2DestType           destType;

		// Router ID for router or IP Address for network
		unsigned                     destAddr;

		// Only defined for network
		unsigned                     addrMask;

		// Optional capabilities
		char                            option;

		// Area whose LS info has led to this entry
		unsigned                     areaId;

		// Type of path to destination
		Ospfv2PathType           pathType;

		// Cost to destination
		Int32                           metric;

		// Only for Type 2 cost
		Int32                           type2Metric;

		// Valid only for Intra-Area paths
		void*                            LSOrigin;

		// Next hop router address
		// TBD: Enable equal cost multipath later
		unsigned                     nextHop;
		unsigned                     outIntf;

		// Valid only for intra-area and AS-External path
		unsigned                     advertisingRouter;

		Ospfv2Flag               flag;
	} Ospfv2RoutingTableRow;

	// Routing table kept by ospf.
	typedef struct
	{
		int         numRows;
		DataBuffer  buffer;
	} Ospfv2RoutingTable;


	//-------------------------------------------------------------------------//
	//                   STATISTICS COLLECTED BY PROTOCOL                      //
	//-------------------------------------------------------------------------//

	// Statistics structure
	typedef struct
	{
		int numHelloSent;
		int numHelloRecv;

		int numLSUpdateSent;
		int numLSUpdateRecv;

		int numAckSent;
		int numAckRecv;

		int numLSUpdateRxmt;
		int numExpiredLSAge;

		int numDDPktSent;
		int numDDPktRecv;
		int numDDPktRxmt;

		int numLSReqSent;
		int numLSReqRecv;
		int numLSReqRxmt;

		int numRtrLSAOriginate;
		int numNetLSAOriginate;
		int numSumLSAOriginate;

		int numLSARefreshed;

		bool alreadyPrinted;
	}
	Ospfv2Stats;


	//-------------------------------------------------------------------------//
	//                            AREA DATA STRUCTURE                          //
	//-------------------------------------------------------------------------//

	typedef struct
	{
		unsigned int    address;
		unsigned int    mask;
		bool            advertise;
		bool            advrtToArea[OSPFv2_MAX_ATTACHED_AREA];

		void*           area;
	} Ospfv2AreaAddressRange;

	typedef struct
	{
		unsigned int        areaID;
		Ospfv2List*   areaAddrRange;

		Ospfv2List*   connectedInterface;

		// LSDB for the area
		Ospfv2List*   routerLSAList;
		Ospfv2List*   networkLSAList;
		Ospfv2List*   routerSummaryLSAList;
		Ospfv2List*   networkSummaryLSAList;

		// Timer associated with self originated LSAs
		bool                routerLSTimer;
		clocktype           routerLSAOriginateTime;

		// for group membership LSA
		Ospfv2List*   groupMembershipLSAList;

		// Timer associated with self originated LSAs
		bool                groupMembershipLSTimer;
		clocktype           groupMembershipLSAOriginateTime;

		bool                transitCapability;
		bool                externalRoutingCapability;

		// Shortest path tree of this area
		Ospfv2List*   shortestPathList;

		Int32                stubDefaultCost;
	} Ospfv2Area;


	//-------------------------------------------------------------------------//
	//                   PROTOCOL DATA STRUCTURE                               //
	//-------------------------------------------------------------------------//

	// OSPFv2 Layer structure for node
	typedef struct
	{
		unsigned int asID;

		unsigned routerID;

		Ospfv2List* area;
		bool partitionedIntoArea;
		bool areaBorderRouter;

		// Backbone kept seperately from other areas
		Ospfv2Area* backboneArea;
		clocktype SPFTimer;

		// Virtual link not considered yet

		// BGP-OSPF Patch Start
		// Only in ASBR
		Ospfv2List* asExternalLSAList;
		bool asBoundaryRouter;
		// BGP-OSPF Patch End
		bool isAdvertSelfIntf;
		bool collectStat;
		Ospfv2Stats stats;

		Ospfv2RoutingTable routingTable;

		Ospfv2Interface* iface;

		int neighborCount;

		// parameter used to check multicast capability of a node
		bool isMospfEnable;

		// pointer used to indicate the type of multicast routing protocol used
		void * multicastRoutingProtocol;

		// whether qos is enabled in this node
		bool isQosEnabled;

		// This pointer will hold layer structure of Q-OSPF if QOS is required
		void* qosRoutingProtocol;

		// number of queue advertisement
		int numQueueAdvertisedForQos;

		// holding delayed start time of ospf process.
		clocktype staggerStartTime;

		// random seed for use with broadcast jitter, flood timers, etc.
		int seed;
	} Ospfv2Data;


	//-------------------------------------------------------------------------//
	//                         VARIOUS TIMER INFORMATION                       //
	//-------------------------------------------------------------------------//
	// Information about various timers being triggered.
	typedef struct
	{
		unsigned sequenceNumber;
		unsigned neighborAddr;
		int interfaceIndex;
		// For retransmission timer.
		unsigned advertisingRouter;

		Ospfv2PacketType type;
	} Ospfv2TimerInfo;

	typedef struct
	{
		int interfaceIndex;
		unsigned nbrAddr;
		Ospfv2NeighborEvent nbrEvent;
	} Ospfv2NSMTimerInfo;

	typedef struct
	{
		int interfaceIndex;
		Ospfv2InterfaceEvent intfEvent;
	} Ospfv2ISMTimerInfo;

	//Qospf
	typedef struct struct_qospf_per_link_qos_metric_info
	{
		// Eight bits are given to encode the type of service
		// (i.e. delay, bandwidth etc) and actually five bits are used
		// to encode a Qos parameter. the remaining three bits are used
		// to identify the queue no.
		unsigned char  queueNumber:3,qos:5;

		// This is actually reserved field in router LSA (according to RFC 2328)
		// But we are using this field to identify index of the interface from
		// where the link originates.
		unsigned char  interfaceIndex;

		// To encode Qos metric value, this 16 bits are given. As
		// bandwidth value is high exponential coding is chosen
		unsigned short qosMetricExponentPart:3,qosMetricMantissaPart:13;
	} QospfPerLinkQoSMetricInfo;
	//Network
	typedef struct //Network to MAC
	{
		unsigned nexthopaddr;
		int interfaceIndex;
		unsigned srcAddr;
		unsigned dstAddr;
		unsigned interfaceMaskedAddr;
	} NetworkToMACInfo;

	// /**
	// STRUCT      :: IpHeaderType
	// DESCRIPTION :: IpHeaderType is 20 bytes,just like in the BSD code.
	// **/

	struct IpHeaderType
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

	};
	InterfaceInfoType *interfaceInfo;
public:
	char modelName[SNS_MAX_STRING_LENGTH];
	Ospfv2Data* ospf;
	int numberInterfaces;
	ForwardingTable* forwardingTable;
private://用户自定义私有变量


public://模型导向自动生成公有函数

    Sns_Model_OSPFv2();  
    ~Sns_Model_OSPFv2(); 
    
    //功能:模型初始化函数,读取模型对应配置文件,配置模型初始化配置参数
    void Model_init();
    	
    //功能:节点初始化后的处理函数,用于有时需要所有节点所有模型都初始化完成才可执行的动作
	 void Model_init_end();

	//功能:处理协议或环境模型在仿真结束后的一些事,如模型仿真结果输出等
	void SNS_Simulate_End_Model();

    //功能:消息处理函数,接收模型输入事件,触动相应函数,并处理
    void SNS_Model_MsgDeal(Sns_Message *msg);								

public://模型导向自动生成函数,用户输入事件处理
	
	//功能：OspfIncrementLSAge事件函数 
	void Msg_InEvent_OspfIncrementLSAge(Sns_Message *msg); 

	//功能：OspfInactivityTimer事件函数 
	void Msg_InEvent_OspfInactivityTimer(Sns_Message *msg); 

	//功能：OspfRxmtTimer事件函数 
	void Msg_InEvent_OspfRxmtTimer(Sns_Message *msg); 

	//功能：OspfScheduleHello事件函数 
	void Msg_InEvent_OspfScheduleHello(Sns_Message *msg); 

	//功能：OspfScheduleLSDB事件函数 
	void Msg_InEvent_OspfScheduleLSDB(Sns_Message *msg); 

	//功能：QospfScheduleLSDB事件函数 
	void Msg_InEvent_QospfScheduleLSDB(Sns_Message *msg); 

	//功能：QospfInterfaceStatusMonitor事件函数 
	void Msg_InEvent_QospfInterfaceStatusMonitor(Sns_Message *msg); 

	//功能：QospfSetNewConnection事件函数 
	void Msg_InEvent_QospfSetNewConnection(Sns_Message *msg); 

	//功能：OspfWaitTimer事件函数 
	void Msg_InEvent_OspfWaitTimer(Sns_Message *msg); 

	//功能：OspfFloodTimer事件函数 
	void Msg_InEvent_OspfFloodTimer(Sns_Message *msg); 

	//功能：OspfDelayedAckTimer事件函数 
	void Msg_InEvent_OspfDelayedAckTimer(Sns_Message *msg); 

	//功能：OspfScheduleSPF事件函数 
	void Msg_InEvent_OspfScheduleSPF(Sns_Message *msg); 

	//功能：OspfNeighborEvent事件函数 
	void Msg_InEvent_OspfNeighborEvent(Sns_Message *msg); 

	//功能：OspfInterfaceEvent事件函数 
	void Msg_InEvent_OspfInterfaceEvent(Sns_Message *msg); 

	//功能：OspfHandleRoutingProtocolPacket事件函数 
	void Msg_InEvent_OspfHandleRoutingProtocolPacket(Sns_Message *msg); 

	//Sns_Msg_In_Func//
    
private://模型导向自动生成私有函数
	
	//功能:记录本模型的输出状态变量值到StatsVar_Output内
	void SNS_Record_Stats_Value();

	//功能:发送一个新消息
	//输入:DestiNode--消息目的节点地址,ProtocolId--发起消息的模型ID,EventName--消息事件名称,
	//     EventType--事件类型,PayLoad--消息载荷,PacketSize--消息载荷大小,TimeDelay--发送延迟
	void Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay);


public://用户自定义公有函数
	void modelValsInit(int numberInterfaces,InterfaceInfoType interfaceInfo[MAX_NUM_INTERFACES]);
	void Ospfv2InitList(Ospfv2List** list);
	void Ospfv2InitRoutingTable();
	void Ospfv2InitInterface();
	unsigned Ospfv2GetAreaId(int interfaceIndex);
	Ospfv2Area* Ospfv2GetArea(unsigned areaID);
	void Ospfv2InitArea(int i,unsigned areaID);
	void Ospfv2AddInterfaceToArea(unsigned int areaID,int i);
	void Ospfv2ScheduleRouterLSA(unsigned areaId,bool flush);
	void Ospfv2ReadRouterInterfaceParameters(Ospfv2Interface* iface,int interfaceIndex);
	bool Ospfv2CompDestType(Ospfv2DestType destType1,Ospfv2DestType destType2);
	Ospfv2RoutingTableRow* Ospfv2GetIntraAreaRoute(unsigned destAddr,Ospfv2DestType destType,unsigned areaId);
	Ospfv2RoutingTableRow* Ospfv2GetRoute(unsigned destAddr,Ospfv2DestType destType);
	bool Ospfv2RoutesMatchSame(Ospfv2RoutingTableRow* newRoute,Ospfv2RoutingTableRow* oldRoute);
	void Ospfv2AddRoute(Ospfv2RoutingTableRow* newRoute);
	void Ospfv2ExternalRouteInit();
	void Ospfv2Init();
	bool Ospfv2InterfaceBelongToThisArea(int areaId,int interfaceIndex);
	void Ospfv2AddSelfRoute(int interfaceIndex,Ospfv2LinkInfo** linkInfo);
	void Ospfv2AddType1Link(int interfaceIndex,Ospfv2Neighbor* tempNbInfo,Ospfv2LinkInfo** linkInfo);
	void Ospfv2AddType2Link(int interfaceIndex,Ospfv2LinkInfo** linkInfo);
	void Ospfv2AddType3Link(int interfaceIndex,Ospfv2LinkInfo** linkInfo);
	bool Ospfv2RouterFullyAdjacentWithDR(int interfaceIndex);
	bool Ospfv2DRFullyAdjacentWithAnyRouter(int interfaceIndex);
	void Ospfv2AddHostRoute(int interfaceIndex,Ospfv2Neighbor* tempNbInfo,Ospfv2LinkInfo** linkInfo);
	Ospfv2LinkStateHeader* Ospfv2LookupLSAList(Ospfv2List* list,unsigned advertisingRouter,unsigned linkStateID);
	void Ospfv2RemoveFromList(Ospfv2List* list,Ospfv2ListItem* listItem,bool type);
	bool Ospfv2ListIsEmpty(Ospfv2List* list);
	void Ospfv2RemoveLSAFromRetxList(char linkStateType,unsigned linkStateID,unsigned advertisingRouter,unsigned areaId);
	Ospfv2LinkStateHeader* Ospfv2SearchRequestList(Ospfv2List* tList,Ospfv2LinkStateHeader* LSHeader);
	int Ospfv2CompareLSA(Ospfv2LinkStateHeader* LSHeader,Ospfv2LinkStateHeader* oldLSHeader);
	void Ospfv2RemoveFromRequestList(Ospfv2List* tlist,Ospfv2LinkStateHeader* LSHeader);
	char* Ospfv2CopyLSA(char* LSA);
	void Ospfv2AddToLSRetxList(int interfaceIndex,Ospfv2Neighbor* nbrInfo,char* LSA);
	void Ospfv2QueueLSAToFlood(Ospfv2Interface* thisInterface,char* LSA);
	bool Ospfv2FloodLSA(int inIntf,char* LSA,unsigned sourceAddr,unsigned areaId);
	void Ospfv2FlushLSA(char* LSA, unsigned areaId);
	void Ospfv2RemoveLSAFromList(Ospfv2List* list,char* LSA);
	void Ospfv2RemoveLSAFromLSDB(char* LSA,unsigned areaId);
	bool Ospfv2CreateLSHeader(unsigned areaId,Ospfv2LinkStateType LSType,Ospfv2LinkStateHeader* LSHeader,Ospfv2LinkStateHeader* oldLSHeader);
	bool Ospfv2CheckRouterLSABody(Ospfv2RouterLSA* newRouterLSA,Ospfv2RouterLSA* oldRouterLSA);
	bool Ospfv2CheckSummaryLSABody(Ospfv2LinkStateHeader* newLSHeader,Ospfv2LinkStateHeader* oldLSHeader);
	bool Ospfv2CheckASExternalLSABody(Ospfv2LinkStateHeader* newLSHeader,Ospfv2LinkStateHeader* oldLSHeader);
	bool Ospfv2CheckNetworkLSABody(Ospfv2NetworkLSA* newNetworkLSA,Ospfv2NetworkLSA* oldNetworkLSA);
	bool Ospfv2LSABodyChanged(Ospfv2LinkStateHeader* newLSHeader,Ospfv2LinkStateHeader* oldLSHeader);
	bool Ospfv2LSAsContentsChanged(Ospfv2LinkStateHeader* newLSHeader,Ospfv2LinkStateHeader* oldLSHeader);
	void Ospfv2AssignNewLSAIntoLSOrigin(char* LSA,char* newLSA);
	bool Ospfv2InstallLSAInLSDB(Ospfv2List* list,char* LSA);
	void Ospfv2ScheduleSPFCalculation();
	void Ospfv2OriginateRouterLSAForThisArea(unsigned areaId,bool flush);
	void Ospfv2ScheduleNetworkLSA(int interfaceIndex, bool flush);
	void Ospfv2OriginateNetworkLSA(int interfaceIndex,bool flush);
	Ospfv2AreaAddressRange*  Ospfv2GetAddrRangeInfo(unsigned areaId,unsigned destAddr);
	Ospfv2AreaAddressRange* Ospfv2GetAddrRangeInfoForAllArea(unsigned destAddr);
	int Ospfv2CheckForSummaryLSAValidity(unsigned destAddr,unsigned addrMask,Ospfv2DestType destType,unsigned int areaId,Ospfv2RoutingTableRow** matchPtr);
	Int32 Ospfv2GetMaxMetricForThisRange(Ospfv2RoutingTable* rtTable,Ospfv2AreaAddressRange* addrInfo);
	Ospfv2ListItem* Ospfv2GetLSAListItem(Ospfv2List* list,unsigned advertisingRouter,unsigned linkStateID);
	void Ospfv2ScheduleSummaryLSA(unsigned destAddr,unsigned addrMask,Ospfv2DestType destType,unsigned int areaId,bool flush);
	void Ospfv2OriginateSummaryLSA(Ospfv2RoutingTableRow* advRt,Ospfv2Area* thisArea,bool flush);
	void Ospfv2ScheduleASExternalLSA(unsigned destAddress,unsigned destAddressMask,unsigned nextHopAddress,int external2Cost,bool flush);
	bool Ospfv2FloodThroughAS(int interfaceIndex,char* LSA,unsigned srcAddr);
	void Ospfv2OriginateASExternalLSA(unsigned destAddress,unsigned destAddressMask,unsigned nextHopAddress,int external2Cost,bool flush);
	short int Ospfv2CalcCommonHeaderCheckSum(Ospfv2CommonHeader* cmnHdr);
	void Ospfv2CreateCommonHeader(Ospfv2CommonHeader* commonHdr,Ospfv2PacketType pktType);
	int Ospfv2FillNeighborField(unsigned** nbrList,int interfaceIndex);
	void Ospfv2SendHelloPacket(Int32 interfaceIndex);
	int Ospfv2GetInterfaceIndexFromAddress(unsigned address);
	void Ospfv2ScheduleLSA(Ospfv2LinkStateHeader* LSHeader,unsigned int areaId);
	void Ospfv2RefreshLSA(Ospfv2ListItem* LSAItem,unsigned int areaId);
	void Ospfv2IncrementLSAgeInLSAList(Ospfv2List* tlist,unsigned int areaId);
	void Ospfv2IncrementLSAge();
	Ospfv2LinkStateHeader* Ospfv2LookupLSAListByID(Ospfv2List* list,unsigned linkStateID);
	bool Ospfv2LSAHasMaxAge(char* LSA);
	bool Ospfv2LSAHasLink(char*  wLSA, char*  vLSA);
	bool Ospfv2InShortestPathList(Ospfv2List* shortestPathList,Ospfv2VertexType vertexType,unsigned vertexId);
	bool Ospfv2CheckRouterLSASetThisNetworkTransit(Ospfv2RouterLSA* routerLSA,unsigned netAddr,unsigned subnetMask);
	bool Ospfv2IsTransitWithNetworkVertex(Ospfv2Area* thisArea,unsigned vertexId);
	void Ospfv2GetLinkDataForThisVertex(Ospfv2Vertex* vertex,Ospfv2Vertex* parent,unsigned* linkData);
	Ospfv2Neighbor* Ospfv2GetNbrInfoOnInterface(unsigned nbrId,int interfaceIndex);
	Ospfv2Vertex*  Ospfv2FindCandidate(Ospfv2List* candidateList,Ospfv2VertexType vertexType,unsigned vertexId);
	bool Ospfv2IsPresentInNextHopList(Ospfv2List* nextHopList,Ospfv2NextHopListItem* nextHopListItem);
	bool Ospfv2HaveLinkWithNetworkVertex(unsigned vertexId);
	bool Ospfv2SetNextHopForThisVertex(Ospfv2Vertex* vertex,Ospfv2Vertex* parent);
	void Ospfv2UpdateCandidateListUsingNetworkLSA(Ospfv2Area* thisArea,Ospfv2List* candidateList,Ospfv2Vertex* v);
	void Ospfv2UpdateCandidateListUsingRouterLSA(Ospfv2Area* thisArea,Ospfv2List* candidateList,Ospfv2Vertex* v);
	void Ospfv2UpdateCandidateList(Ospfv2Area* thisArea,Ospfv2List* candidateList,Ospfv2Vertex* v);
	Ospfv2RoutingTableRow* Ospfv2GetValidRoute(unsigned destAddr,Ospfv2DestType destType);
	void Ospfv2FreeRoute(Ospfv2RoutingTableRow* rowPtr);
	void Ospfv2UpdateIntraAreaRoute(Ospfv2Area* thisArea,Ospfv2Vertex* v);
	Ospfv2Vertex* Ospfv2UpdateShortestPathList(Ospfv2Area* thisArea,Ospfv2List* candidateList);
	bool Ospfv2IsMyAddress(unsigned addr);
	Ospfv2RoutingTableRow* Ospfv2GetValidHostRoute(unsigned destAddr,Ospfv2DestType destType);
	bool Ospfv2RemoveLSAFromShortestPathList(Ospfv2List* shortestPathList,char* LSA);
	void Ospfv2AddStubRouteToShortestPath(Ospfv2Area* thisArea);
	void Ospfv2FreeVertexList(Ospfv2List* vertexList);
	void Ospfv2FindShortestPathForThisArea(unsigned areaId);
	void Ospfv2FindInterAreaPath();
	void Ospfv2InvalidateRoutingTable();
	void Ospfv2AddInterAreaRoute(Ospfv2RoutingTableRow* newRoute);
	void Ospfv2ExamineSummaryLSA(Ospfv2Area* thisArea,Ospfv2LinkStateType summaryLSAType);
	void Ospfv2FindASExternalPath();
	void Ospfv2UpdateIpForwardingTable();
	void Ospfv2ResetAdvrtToAreaFlag();
	bool Ospfv2NextHopBelongsToThisArea(Ospfv2RoutingTableRow* thisRoute,Ospfv2Area* area);
	void Ospfv2AdvertiseRoute(Ospfv2RoutingTableRow* thisRoute);
	void Ospfv2CheckOldSummaryLSA(Ospfv2Area* thisArea,Ospfv2LinkStateType lsType);
	void Ospfv2HandleRemovedOrChangedRoutes();
	void Ospfv2OriginateDefaultSummaryLSA();
	void Ospfv2HandleABRTask();
	void Ospfv2FreeInvalidRoute();
	void Ospfv2FindShortestPath();
	bool Ospfv2GetTopLSAFromList(Ospfv2List* list,Ospfv2LinkStateHeader* LSHeader);
	void Ospfv2SendDatabaseDescriptionPacket(unsigned nbrAddr,int interfaceIndex);
	void Ospfv2AttemptAdjacency(Ospfv2Neighbor* nbrInfo,int interfaceIndex);
	void Ospfv2ScheduleInterfaceEvent(int interfaceIndex,Ospfv2InterfaceEvent intfEvent);
	void Ospfv2SetNeighborState(int interfaceIndex,Ospfv2Neighbor* neighborInfo,Ospfv2NeighborState state);
	bool Ospfv2AdjacencyRequire(int interfaceIndex,Ospfv2Neighbor* nbrInfo);
	void Ospfv2UpdateDBSummaryList(int interfaceIndex,Ospfv2List* list,Ospfv2Neighbor* nbrInfo);
	bool Ospfv2NeighborIsInStubArea(int interfaceIndex,Ospfv2Neighbor* nbrInfo);
	void Ospfv2CreateDBSummaryList(int interfaceIndex,Ospfv2Neighbor* nbrInfo);
	bool Ospfv2CreateLSReqObject(Ospfv2Neighbor* nbrInfo,Ospfv2LSRequestInfo* LSReqObject,bool retx);
	void Ospfv2SendLSRequestPacket(unsigned nbrAddr,int interfaceIndex,bool retx);
	void Ospfv2FreeRequestList(Ospfv2Neighbor* nbrInfo);
	void Ospfv2DestroyAdjacency(Ospfv2Neighbor* nbrInfo);
	void Ospfv2RemoveNeighborFromNeighborList(int interfaceIndex,unsigned neighborAddr);
	void Ospfv2HandleNeighborEvent(int interfaceIndex,unsigned nbrAddr,Ospfv2NeighborEvent eventType);
	void Ospfv2HandleHelloPacket(Ospfv2HelloPacket* helloPkt,unsigned sourceAddr,int interfaceIndex);
	Ospfv2LinkStateHeader* Ospfv2LookupLSDB(char linkStateType,unsigned advertisingRouter,unsigned linkStateID,int interfaceIndex);
	bool Ospfv2NoNbrInStateExhangeOrLoading(int interfaceIndex);
	bool Ospfv2UpdateLSAList(int interfaceIndex,Ospfv2List* list,char* LSA,unsigned srcAddr,unsigned int areaId);
	bool Ospfv2UpdateLSDB(int interfaceIndex,char* LSA,unsigned srcAddr,unsigned areaId);
	void Ospfv2SendDelayedAck(int interfaceIndex, char* LSA, unsigned nbrAddr);
	void Ospfv2SendUpdatePacket(unsigned dstAddr,int interfaceIndex,char* payload,int payloadSize,int LSACount);
	void Ospfv2SendAckPacket(char* payload,int count,unsigned dstAddr,int interfaceIndex);
	void Ospfv2SendDirectAck(int interfaceIndex,Ospfv2List* ackList,unsigned nbrAddr);
	bool Ospfv2RequestedLSAReceived(Ospfv2Neighbor* nbrInfo);
	void Ospfv2HandleUpdatePacket(Sns_Message* msg,unsigned sourceAddr,int interfaceIndex);
	void Ospfv2HandleAckPacket(Ospfv2LinkStateAckPacket* ackPkt,unsigned sourceAddr,int interfaceIndex);
	void Ospfv2AddToRequestList(Ospfv2List* linkStateRequestList,Ospfv2LinkStateHeader* LSHeader);
	void Ospfv2ScheduleNeighborEvent(int interfaceIndex,unsigned nbrAddr,Ospfv2NeighborEvent nbrEvent);
	void Ospfv2ProcessDatabaseDescriptionPacket(Sns_Message* msg,unsigned srcAddr,int interfaceIndex);
	void Ospfv2HandleDatabaseDescriptionPacket(Sns_Message* msg,unsigned srcAddr,int interfaceIndex);
	void Ospfv2SendLSUpdate(unsigned nbrAddr, int interfaceIndex);
	void Ospfv2HandleLSRequestPacket(Sns_Message* msg,unsigned srcAddr,int interfaceIndex);
	void Ospfv2RetransmitLSA(Ospfv2Neighbor* nbrInfo,int interfaceIndex);
	void Ospfv2HandleRetransmitTimer(int interfaceIndex,unsigned int sequenceNumber,unsigned neighborAddr,unsigned advertisingRouter,Ospfv2PacketType type);
	void Ospfv2ListDREligibleRouters(Ospfv2List* nbrList,Ospfv2List* eligibleRoutersList,int interfaceIndex);
	void Ospfv2ElectBDR(Ospfv2List* eligibleRoutersList,int interfaceIndex);
	Ospfv2InterfaceState Ospfv2ElectDR(Ospfv2List* eligibleRoutersList,int interfaceIndex);
	Ospfv2InterfaceState Ospfv2DRElection(int interfaceIndex);
	void Ospfv2SetInterfaceState(int interfaceIndex,Ospfv2InterfaceState newState);
	void Ospfv2HandleInterfaceEvent(int interfaceIndex,Ospfv2InterfaceEvent eventType);
	//unsigned hostBitsStr2Uint(char* hostBitsStr);
	unsigned ConvertNumHostBitsToSubnetMask(int hostbits);
	void Ospfv2InitNonBroadcastNeighborList(Ospfv2NonBroadcastNeighborList** list);
	void Ospfv2InsertToNonBroadcastNeighborList(Ospfv2NonBroadcastNeighborList* list,unsigned addr);
	void Ospfv2InsertToList(Ospfv2List* list,clocktype timeStamp,void* data);
	unsigned GetDefaultIPv4InterfaceAddress();
	void Ospfv2RouterFunction(Sns_Node_NetworkIP_OSPFv2* node,Sns_Message* msg,unsigned destAddr,unsigned prevHopAddr,bool* packetWasRouted);
	void ParseNodeIdHostOrNetworkAddress(char str[SNS_MAX_STRING_LENGTH],unsigned& addr,int& numhostbits);
	int	NetworkIpGetInterfaceIndexForNextHop(unsigned nextHopAddress);
	unsigned MaskIpAddress(unsigned address, unsigned mask);
	void Ospfv2LinkStateHeaderSetOptions1(unsigned char *ospfLsh,unsigned char options1);
	void Ospfv2LinkStateHeaderSetExt(unsigned char *ospfLsh,bool external);
	Ospfv2Neighbor* Ospfv2GetNeighborInfoByIPAddress(int interfaceIndex,unsigned neighborAddr);
	void Ospfv2SetTimer(int interfaceIndex,int eventType,unsigned neighborAddr,clocktype timerDelay,unsigned sequenceNumber,unsigned advertisingRouter,Ospfv2PacketType type);
	void Ospfv2RouterLSASetReserved1(unsigned char *ospfRouterLsa,unsigned char reserved);
	void Ospfv2RouterLSASetWCMCReceiver(unsigned char *ospfRouterLsa,bool wcmr);
	void Ospfv2RouterLSASetVirtLnkEndPt(unsigned char *ospfRouterLsa,bool vlep);
	void Ospfv2RouterLSASetASBRouter(unsigned char *ospfRouterLsa,bool asbr);
	void Ospfv2RouterLSASetABRouter(unsigned char *ospfRouterLsa,bool abr);
	bool Ospfv2LinkStateHeaderGetExt(unsigned char ospfLsh);
	bool Ospfv2LinkStateHeaderGetMulticast(unsigned char ospfLsh);
	void Ospfv2LinkStateHeaderSetQOS(unsigned char *ospfLsh, bool qos);
	void Ospfv2LinkStateHeaderSetMulticast(unsigned char *ospfLsh,bool multicast);
	unsigned char Ospfv2RouterLSAGetReserved1(unsigned char ospfRouterLsa);
	bool Ospfv2RouterLSAGetWCMCReceiver(unsigned char ospfRouterLsa);
	bool Ospfv2RouterLSAGetVirtLnkEndPt(unsigned char ospfRouterLsa);
	bool Ospfv2RouterLSAGetASBRouter(unsigned char ospfRouterLsa);
	bool Ospfv2RouterLSAGetABRouter(unsigned char ospfRouterLsa);
	void Ospfv2ExternalLinkSetEBit(UInt32 *ospfMetric, bool eBit);
	void Ospfv2ExternalLinkSetMetric(UInt32 *ospfMetric, UInt32 metric);
	UInt32 Ospfv2ExternalLinkGetMetric(UInt32 ospfMetric);
	void Ospfv2FreeList(Ospfv2List* list, bool type);
	int Ospfv2GetInterfaceIndexFromlinkData(unsigned linkData);
	int Ospfv2GetInterfaceForThisNeighbor(unsigned neighborAddr);
	void Ospfv2DeleteList(Ospfv2List* list, bool type);
	void Ospfv2DatabaseDescriptionPacketSetInit(unsigned char *ospfDbDp,bool init);
	void Ospfv2DatabaseDescriptionPacketSetMore(unsigned char *ospfDbDp,bool more);
	void Ospfv2DatabaseDescriptionPacketSetMS(unsigned char *ospfDbDp,bool ms);
	void Ospfv2DatabaseDescriptionPacketSetRsrvd2(unsigned char *ospfDbDp,unsigned char reserved2);
	bool Ospfv2DatabaseDescriptionPacketGetInit(unsigned char ospfDbDp);
	bool Ospfv2DatabaseDescriptionPacketGetMore(unsigned char ospfDbDp);
	bool Ospfv2DatabaseDescriptionPacketGetMS(unsigned char ospfDbDp);
	void convertIpAddressToString(unsigned address,char addrStr[SNS_MAX_STRING_LENGTH]);
	void Ospfv2PrintRoutingTable();
	void Ospfv2PrintHelloPacket(Ospfv2HelloPacket* helloPkt,int interfaceIndex);
	void Ospfv2PrintNeighborList();
	void Ospfv2PrintLSA(char* LSA);
	void Ospfv2PrintRouterLSAListForThisArea(Ospfv2Area* thisArea);
	void Ospfv2PrintNetworkLSAListForThisArea(Ospfv2Area* thisArea);
	void Ospfv2PrintSummaryLSAListForThisArea(Ospfv2Area* thisArea);
	void Ospfv2PrintRouterLSAList();
	void Ospfv2PrintNetworkLSAList();
	void Ospfv2PrintSummaryLSAList();
	void Ospfv2PrintASExternalLSA();
	void Ospfv2PrintLSDB();
	void Ospfv2GetNeighborStateString(Ospfv2NeighborState state,char* str);
	void Ospfv2GetIEString(Ospfv2NeighborEvent eventType,char* str);
	void Ospfv2PrintNeighborState();
	void Ospfv2PrintLinkList(Ospfv2List* shortestPathList);
	void Ospfv2PrintNextHopList(Ospfv2List* nextHopList);
	void Ospfv2PrintAllNextHopList(Ospfv2List* shortestPathList);
	void Ospfv2PrintMsgEventName(Sns_Message* msg,bool isDone);

	void Ospfv2ManuallyScheduleRouterLSA(InterfaceInfoType* info);
private://用户自定义私有函数


};  
#endif 
