/*
* Copyright (c) 2014,北京航空航天大学
* All rights reserved.
*
* 系统名称: SPACE NETWORK SIMULATION SYSTEM
* 作    者: 张涛
* 当前版本: SNS 1.0
* 
* 文件名称: Sns_Scenarios.cpp
* 当前版本: V 1.0.0
* 文件标识: Sns_Scenarios类源文件
* 功能描述: 
* 完 成 人: 
* 联系方式: 
* 完成日期: 
*
* 摘    要:
*/
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"//基本c++库

#include "Sns_Message.h"//平台库
#include "Sns_Config_Input.h"//平台库
#include "Sns_Scenarios.h"
//本场景节点模型头文件
#include "Sns_Node_Admin.h"
#include "Sns_Node_Real.h"
#include "Sns_Node_Virtual.h"
//Include_ofModel//

Sns_Scenarios::Sns_Scenarios()
{
	Num_Nodes = 0;   

	Is_Packet_Track = false;                 //是否数据包跟踪，若是，设置Track_PacketId
	Track_PacketId = -1;                   //被跟踪的包ID号
	Is_Create_Onlyone = true;             //是否产生的是唯一包，在一次跟踪中

	///////////输出参数初始化,模板自动生成//////////
	
	//Stats_Variable_Init//

	///////////输出参数初始化,模板自动生成 end//////////

}

Sns_Scenarios::~Sns_Scenarios()
{
	delete(Config_Input);
	Config_Input = NULL;
	free(ConfFile_Path);
	ConfFile_Path = NULL;
	delete(StatsVar_Output);
	StatsVar_Output = NULL;
	free(StatsFile_Path);
	StatsFile_Path = NULL;
}

///////////////////////////工程场景初始化函数///////////////////////////////////////////////
//功能:场景初始化函数,读取节点对应配置文件,配置场景初始化参数
//     为场景中所用到节点对象实例化,并启动节点初始化
void Sns_Scenarios::SNS_Init()
{	
	//////////////////////模型导向自动生成////////////////////////////
	//////////////从配置文件中读取初始化参数//////////////////////////
	Is_Synchronization=true;

	char ModelName[SNS_MAX_STRING_LENGTH];  //配置文件中模型识别标志

	char buf[SNS_MAX_STRING_LENGTH];  //读取配置文件中的字符串
	int buf_int = 0;		//读取配置文件的int值,用于long,unsigned int
	double buf_double = 0;	//读取配置文件的int值,用于float

	int RetArrNum;//读取参数个数返回值

	bool retVal = false;//函数返回值
	
	Config_Input = new Sns_Config_Input();//声明一个配置文件处理对象

	ConfFile_Path = ".//Sns_config.ini";//设置配置文件路径

	StatsFile_Path = ".//Sns_output_statsVar.txt";//设置仿真输出状态参数文件路径

	sprintf(ModelName,"Sns_Scenarios");

	Config_Input->SNS_Read_ModelConf(ConfFile_Path, ModelName);//读取场景配置参数

	retVal = Config_Input->SNS_ReadString("char*,unit_Of_Aclocktype", &RetArrNum ,buf);//获取场景最小仿真时间单位 
	if(retVal == false)
	{
		Unit_Of_Aclocktype = "MicS";			//默认最小时间单位为微秒
		SNS_Set_Time_Unit(Unit_Of_Aclocktype);	//设置场景最小仿真时间单位
	}
	else
	{
		Config_Var.unit_Of_Aclocktype = buf;
		Unit_Of_Aclocktype = buf;
		SNS_Set_Time_Unit(Unit_Of_Aclocktype);//设置场景最小仿真时间单位
	}
	
	retVal = Config_Input->SNS_ReadTime("clocktype,Max_Sim_Clock", &RetArrNum, &Config_Var.max_sim_clock);//获取场景仿真时间
	if (retVal == false) 
	{
        Max_Sim_Clock = 1000000000000;	//默认仿真时间  
    }
	else
	{
		Max_Sim_Clock = Config_Var.max_sim_clock;
	}

	retVal = Config_Input->SNS_ReadInt( "int,seedVal", &RetArrNum, &Config_Var.seed_val); //获取随机种子
	if (retVal == false) 
	{
        Config_Var.seed_val = 5;	//默认随机种子
    }
	//Config_Variable_Init//
	/////////////////////从配置文件中读取初始化参数 end///////////////////////

	/////////////////////从配置文件中获取本场景各类节点及数目/////////////////
	retVal = Config_Input->SNS_ReadInt( "int,Num_Sns_Node_Real", &RetArrNum, &Num_ofThis.Num_Sns_Node_Real);
	if (retVal == false)
	{
		Num_ofThis.Num_Sns_Node_Real = 1;
	}

	retVal = Config_Input->SNS_ReadInt( "int,Num_Sns_Node_Virtual", &RetArrNum, &Num_ofThis.Num_Sns_Node_Virtual);
	if (retVal == false)
	{
		Num_ofThis.Num_Sns_Node_Virtual = 1;
	}

	//Config_ModelNumInit_Add//
	/////////////////////从配置文件中获取本场景各类节点及数目 end//////////////
	
	//场景节点总数初始化
	Num_Nodes = Num_ofThis.Num_Sns_Node_Real + Num_ofThis.Num_Sns_Node_Virtual + 1;
	//Sum_ModelNum_Add//
	
	srand(Config_Var.seed_val);	

	//初始化场景内各节点
	All_Node_init();

	//////////////////////模型导向自动生成 end////////////////////////////

}

//功能:根据配置文件初始化场景内所有节点
void Sns_Scenarios::All_Node_init()
{
	int i = 0;                         //函数循环用局部变量
	int nodelist_id = 0;

	//场景中节点内存分配,初始化节点链表
	nodeData = (sns_base_node **)checked_pc_malloc(sizeof(sns_base_node *) * Num_Nodes);// 为节点分配内存

	/////////////*遍历这些Nodes,设置Nodes信息*///////////////////////////////////

	sns_base_node *nextNode = NULL;

	////////初始化管理节点
	nodeData[nodelist_id] = new Sns_Node_Admin();			
	nodeData[nodelist_id]->Node_Type = SNS_NODE_ADMIN;  //设置节点类型
	nextNode = Base_Node_Init(nodelist_id,i,Config_Var.seed_val,this,nextNode);

    ////////初始化管理节点结束
	for (i = 0;i < Num_ofThis.Num_Sns_Node_Real;i++)
	{
		nodeData[nodelist_id] = new Sns_Node_Real();
		nodeData[nodelist_id]->Node_Type = SNS_NODE_REAL;
		nextNode = Base_Node_Init(nodelist_id,i,Config_Var.seed_val,this,nextNode);
	}
	for (i = 0;i < Num_ofThis.Num_Sns_Node_Virtual;i++)
	{
		nodeData[nodelist_id] = new Sns_Node_Virtual();
		nodeData[nodelist_id]->Node_Type = SNS_NODE_VIRTUAL;
		nextNode = Base_Node_Init(nodelist_id,i,Config_Var.seed_val,this,nextNode);
	}
	//Sns_NodeList_Init//
	
    //////////////////*初始化所有Nodes*//////////////////////
   // 这是对于不同类型节点需要分别定义
	//包括初始化和初始化后节点运行函数
	nextNode = firstNode;
	Sns_Node_Admin * Sns_Node_AdminObj =NULL;

	Sns_Node_Real * Sns_Node_RealObj =NULL;
	Sns_Node_Virtual * Sns_Node_VirtualObj =NULL;
	//Sns_Node_Definition//

	while (nextNode != NULL) 
	{
		switch(nextNode->Node_Type)
		{
		case SNS_NODE_ADMIN:
		{
			Sns_Node_AdminObj = (Sns_Node_Admin *) nextNode;
			Sns_Node_AdminObj->ConfFile_Path = ConfFile_Path;//设置配置文件路径
			Sns_Node_AdminObj->Node_init();

			break;
		}
		case SNS_NODE_REAL:
		{
			Sns_Node_RealObj = (Sns_Node_Real *) nextNode;
			Sns_Node_RealObj->ConfFile_Path = ConfFile_Path;
			Sns_Node_RealObj->Node_init();

			break;
		}
		case SNS_NODE_VIRTUAL:
		{
			Sns_Node_VirtualObj = (Sns_Node_Virtual *) nextNode;
			Sns_Node_VirtualObj->ConfFile_Path = ConfFile_Path;
			Sns_Node_VirtualObj->Node_init();

			break;
		}
		//Sns_Node_Case_Init_Begin//
		default:
			break;
		}		
		nextNode = nextNode->nextNodeData;
	}

	//初始化后运行函数
	nextNode = firstNode;

	while (nextNode != NULL) 
	{
		switch(nextNode->Node_Type)
		{
		case SNS_NODE_ADMIN:
		{
			Sns_Node_AdminObj = (Sns_Node_Admin *) nextNode;
			Sns_Node_AdminObj->Node_init_end();

			break;
		}
		case SNS_NODE_REAL:
		{
			Sns_Node_RealObj = (Sns_Node_Real *) nextNode;
			Sns_Node_RealObj->Node_init_end();

			break;
		}
		case SNS_NODE_VIRTUAL:
		{
			Sns_Node_VirtualObj = (Sns_Node_Virtual *) nextNode;
			Sns_Node_VirtualObj->Node_init_end();

			break;
		}
		//Sns_Node_Case_Init_End//
		default:
			break;
		}		
		nextNode = nextNode->nextNodeData;
	}
}

////////////////////////////仿真系统消息处理函数//////////////////////////////////////////////
//功能:仿真运行函数，处理消息队列
void Sns_Scenarios::SNS_Simulate_Run()
{
	while (true) 
	{
		if(!SNS_SimTime_Control())
			return;

	/////*仿真运行,检查当前时刻是否预约有任何消息*//////
		// 这是对于不同类型节点需要分别处理
		sns_base_node *node = NULL;		
		Sns_Message *msg = NULL;	
		
		if (Get_HeapSize() != 0) 
		{
			while ((node = Get_Current_Node()) !=NULL) 
			{			
				msg = (Sns_Message * )Get_Current_Msg(node);

				switch(node->Node_Type)
				{
				case SNS_NODE_ADMIN:                  //管理节点消息处理
				{
					if((msg->Model_id != -1)||(msg->Event_Type != SNS_MSG_OUTPUT))//节点输入事件处理
					{
						Sns_Node_Admin * Sns_Node_AdminObj = (Sns_Node_Admin *) node;
						Sns_Node_AdminObj->SNS_Node_MsgDeal(msg);  //节点消息处理 
						
					}
					else//节点输出事件处理
					{
						switch(msg->Event_Name)
						{
				
						default:
							break;
						}						
					}
					break;
				}
				case SNS_NODE_REAL:
				{
					//EnterCriticalSection(&cs_WinPcap);
					if((msg->Model_id != -1)||(msg->Event_Type != SNS_MSG_OUTPUT))
					{
						Sns_Node_Real * Sns_Node_RealObj = (Sns_Node_Real *) node;
						Sns_Node_RealObj->SNS_Node_MsgDeal(msg);
					}
					else
					{

						switch(msg->Event_Name)
						{
						case Sns_Node_Real::MSG_OutEVENT_SendToOtherNodes:
							{

							}
						case Sns_Node_Real::MSG_OutEVENT_SendToRealNode:
							{

							}

						default:

							break;
						}
					}
					//LeaveCriticalSection(&cs_WinPcap);
					break;
				}
				case SNS_NODE_VIRTUAL:
				{
					if((msg->Model_id != -1)||(msg->Event_Type != SNS_MSG_OUTPUT))
					{
						Sns_Node_Virtual * Sns_Node_VirtualObj = (Sns_Node_Virtual *) node;
						Sns_Node_VirtualObj->SNS_Node_MsgDeal(msg);
					}
					else
					{

						switch(msg->Event_Name)
						{

						default:

							break;
						}
					}
					break;
				}
				//Sns_Node_Case_Run//
				default:

					break;
				}
			}
		}
	}
}

////////////////////////////仿真结束处理函数//////////////////////////////////////////////
//功能:仿真运行结束，处理仿真结束后的一些事,如仿真结果输出等
void Sns_Scenarios::SNS_Simulate_End()
{
	sns_base_node *nextNode = NULL;

	nextNode = firstNode;

	Sns_Node_Admin * Sns_Node_AdminObj =NULL;

	Sns_Node_Real * Sns_Node_RealObj =NULL;
	Sns_Node_Virtual * Sns_Node_VirtualObj =NULL;
	//Sns_Node_Definition//

	SNS_Record_Stats_Value();

	while (nextNode != NULL) 
	{
		switch(nextNode->Node_Type)
		{
		case SNS_NODE_ADMIN:
		{
			Sns_Node_AdminObj = (Sns_Node_Admin *) nextNode;
			Sns_Node_AdminObj->StatsVar_Output = StatsVar_Output;
			Sns_Node_AdminObj->SNS_Simulate_End_Node();

			break;
		}
		case SNS_NODE_REAL:
		{
			Sns_Node_RealObj = (Sns_Node_Real *) nextNode;
			Sns_Node_RealObj->StatsVar_Output = StatsVar_Output;
			Sns_Node_RealObj->SNS_Simulate_End_Node();

			break;
		}
		case SNS_NODE_VIRTUAL:
		{
			Sns_Node_VirtualObj = (Sns_Node_Virtual *) nextNode;
			Sns_Node_VirtualObj->StatsVar_Output = StatsVar_Output;
			Sns_Node_VirtualObj->SNS_Simulate_End_Node();

			break;
		}
		//Sns_Node_Case_Sim_End//
		default:
			break;
		}
		nextNode = nextNode->nextNodeData;
	}

	StatsVar_Output->SNS_Print_InputStr(StatsFile_Path);//将StatsVar_Output内储存的状态参数写入路径为StatsFile_Path文件中
}

//功能:记录本模型的输出状态变量值到StatsVar_Output内
void Sns_Scenarios::SNS_Record_Stats_Value()
{
	bool retVal = false;	//函数返回值
	char Stats_ModelName[SNS_MAX_STRING_LENGTH]; //用于记录输出状态变量所属模型名标志

	StatsVar_Output = new Sns_Config_Input();//输出状态参数处理类实例化

	sprintf(Stats_ModelName,"\n** Sns_Scenarios_begin\n");//本模型输出状态变量值记录开始
	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);//将Stats_ModelName写入链表

	/////////////////////////////将本模型所有输出状态变量值写入链表//////////////////////////

	//Stats_Variable_Record//
	/////////////////////////////将本模型所有输出状态变量值写入链表//////////////////////////

	sprintf(Stats_ModelName,"\n** Sns_Scenarios_end\n");//本模型输出状态变量值记录结束
	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);//将Stats_ModelName写入链表
}

////////////////////////////////公用函数//////////////////////////////////////////////

//功能:本仿真场景中消息发送函数
//输入:SendMsg--需发送的消息,DestiNode--目的节点id,TimeDelay--发送延迟
void Sns_Scenarios::SNS_Msg_Send(Sns_Message *SendMsg, int DestiNode, clocktype  TimeDelay)  //消息发送函数
{
	if(Is_Packet_Track)                    //包跟踪
	{
		if(SendMsg->Track_PacketId == Track_PacketId)
		{
			int packet_dealtime = int(SimClock()-SendMsg->Message_CreationTime);
			printf("PacketId=%d; node_id=%d; mode_id=%d; event_type=%d; event_id=%d; packet_size=%d;deal_time=%d\n",
				Track_PacketId,DestiNode,SendMsg->Model_id,SendMsg->Event_Type,SendMsg->Event_Name,SendMsg->PayLoad_Size,packet_dealtime);
		}
	}

	assert(nodeData[DestiNode] != NULL);
	if(TimeDelay == 0)
	{
		switch(nodeData[DestiNode]->Node_Type)
		{
		case SNS_NODE_ADMIN:     //消息发往管理节点
		{
			Sns_Node_Admin * Sns_Node_AdminObj = (Sns_Node_Admin *)nodeData[DestiNode];
			Sns_Node_AdminObj->SNS_Node_MsgDeal(SendMsg); 

			break;
		}
		case SNS_NODE_REAL:
		{
			Sns_Node_Real * Sns_Node_RealObj = (Sns_Node_Real *) nodeData[DestiNode];
			Sns_Node_RealObj->SNS_Node_MsgDeal(SendMsg);
			break;
		}
		case SNS_NODE_VIRTUAL:
		{
			Sns_Node_Virtual * Sns_Node_VirtualObj = (Sns_Node_Virtual *) nodeData[DestiNode];
			Sns_Node_VirtualObj->SNS_Node_MsgDeal(SendMsg);
			break;
		}
		//Sns_Node_Msg_Send//
		default:
			break;
		}
	}
	else
	{
        SNS_Msg_Insert(nodeData[DestiNode], SendMsg, TimeDelay);
	}
}

//功能:发送一个新消息
//输入:DestiNode--消息目的节点地址,ModelId--发起消息的模型ID,instanceId--发起模型实例号,EventName--消息事件名称,
//     EventType--事件类型,PayLoad--消息载荷,PacketSize--消息载荷大小,TimeDelay--发送延迟
//     发送空消息时，PayLoad=NULL，PacketSize=0
void Sns_Scenarios::Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay)
{
	Sns_Message *msg = new Sns_Message();//声明一个消息对象
	
    msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,PayLoad,PacketSize);//为消息赋值

	SNS_Msg_Send(msg,DestiNode,TimeDelay);//发送消息
}

//功能:将一个消息转发给相应的模型
//输入:msg-转发的消息，DestiNode--接收消息目的节点地址,ModelId--接收消息的模型ID,instanceId--发起模型实例号,该值默认为0,EventName--接收消息事件名称,
//     EventType--接收事件类型,TimeDelay--发送延迟
void Sns_Scenarios::Send_Aexisting_Msg(Sns_Message *msg,int DestiNode,int ModelId,int instanceId,int EventName,int EventType, clocktype  TimeDelay)
{
	msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,NULL,-1);//消息赋值

	SNS_Msg_Send(msg,DestiNode,TimeDelay);//消息发送
}
