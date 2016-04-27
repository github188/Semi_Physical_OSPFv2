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
* 功能描述: 为协议/环境模型开发测试提供模拟的场景设置
* 完 成 人: 
* 联系方式: 
* 完成日期: 
*
* 摘    要:
*/
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"//基本c++库
#include "Sns_Config_Input.h"   //平台库
#include "Sns_Message.h"//平台库

#include "Sns_Scenarios.h"
#include "Sns_Node_Virtual.h"
#include "Sim_Test.h"

Sns_Scenarios::Sns_Scenarios()
{
	Num_Nodes = 0;   

	Is_Packet_Track = false;                 //是否数据包跟踪，若是，设置Track_PacketId
	Track_PacketId = -1;                   //被跟踪的包ID号
	Is_Create_Onlyone = true;             //是否产生的是唯一包，在一次跟踪中  
}

Sns_Scenarios::~Sns_Scenarios()
{

}

///////////////////////////工程场景初始化函数///////////////////////////////////////////////
//功能:场景初始化函数,读取节点对应配置文件,配置场景初始化参数
//     为场景中所用到节点对象实例化,并启动节点初始化
void Sns_Scenarios::SNS_Init()
{	
	//////////////////////模型导向自动生成////////////////////////////

	Num_Nodes = 6;						//场景中节点个数

	//设置仿真时间clocktype单位，默认为MicS，即微秒
	Unit_Of_Aclocktype = "MicS";
	SNS_Set_Time_Unit(Unit_Of_Aclocktype);

    Max_Sim_Clock = 1000000000000;		// 处理仿真时间设置

	ConfFile_Path = ".//Sns_config.ini";//设置配置文件路径

	StatsFile_Path = ".//Sns_output_statsVar.txt";//设置仿真输出状态参数文件路径

	All_Node_init();

	//////////////////////模型导向自动生成 end////////////////////////////
}

//功能:根据配置文件初始化场景内所有节点
void Sns_Scenarios::All_Node_init()
{
	int i = 0;                         //函数循环用局部变量
	int nodelist_id = 0;

	int seedVal;						//配置文件中产生随机数的Seed值 
	seedVal = 5;
	srand(seedVal);	

	//场景中节点内存分配,初始化节点链表
	nodeData = (sns_base_node **)checked_pc_malloc(sizeof(sns_base_node *) * Num_Nodes);	// 为节点分配内存

	/////////////*遍历这些Nodes,设置Nodes信息*///////////////////////////////////

	sns_base_node *nextNode = NULL;

	for (i=0;i<Num_Nodes;i++)
	{
		nodeData[nodelist_id] = new Sns_Node_Virtual();
		nodeData[nodelist_id]->Node_Type = SNS_NODE_VIRTUAL;					//节点类型枚举
		nextNode = Base_Node_Init(nodelist_id,i,seedVal,this,nextNode);	//节点基类初始化
	}

    //////////////////*初始化所有Nodes*//////////////////////
   // 这是对于不同类型节点需要分别定义
	//包括初始化和初始化后节点运行函数
	nextNode = firstNode;
	Sns_Node_Virtual * Sns_Node_VirtualObj =NULL;

	while (nextNode != NULL) 
	{
		switch(nextNode->Node_Type)
		{
		case SNS_NODE_VIRTUAL:
		{
			Sns_Node_VirtualObj = (Sns_Node_Virtual *) nextNode;
			Sns_Node_VirtualObj->ConfFile_Path = ConfFile_Path;
			Sns_Node_VirtualObj->Node_init();

			break;
		}
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
		case SNS_NODE_VIRTUAL:
		{
			Sns_Node_VirtualObj = (Sns_Node_Virtual *)nextNode;
			Sns_Node_VirtualObj->Node_init_end();

			break;
		}
		
		default:
			break;
		}		
		nextNode = nextNode->nextNodeData;
	}

	/////////////////////关于测试类/////////////////////////////////

	Sim_Test_result = new Sim_Test();
	Sim_Test_result->Scenarios_Data = this;//实例化场景类


	/////////////////////关于测试类end/////////////////////////////////
}

////////////////////////////仿真系统消息处理函数//////////////////////////////////////////////
//功能:仿真运行函数，处理消息队列
void Sns_Scenarios::SNS_Simulate_Run()
{
	while (true) 
	{
		if(!SNS_SimTime_Control())
			return;

		Sim_Test_result->Test_Run();							//仿真系统开始运行测试案例，仅用于本次测试设计

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
				case SNS_NODE_VIRTUAL://接收消息的节点
					{
						if((msg->Model_id != -1)||(msg->Event_Type != SNS_MSG_OUTPUT))//节点输入事件处理
						{
							Sns_Node_Virtual *Sns_Node_VirtualObj = (Sns_Node_Virtual *) node;
							Sns_Node_VirtualObj->SNS_Node_MsgDeal(msg);  //时隙队列出口 

						}
						else//节点输出事件处理
						{
							switch(msg->Event_Name)
							{
							//SNS_MSG_EVENT_OUT//
							default:
								break;
							}						
						}
						break;
					}
				default:
					break ;
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
	Sns_Node_Virtual * Sns_Node_VirtualObj =NULL;

	SNS_Record_Stats_Value();

	while (nextNode != NULL) 
	{
		switch(nextNode->Node_Type)
		{
		case SNS_NODE_VIRTUAL:
		{
			Sns_Node_VirtualObj = (Sns_Node_Virtual *) nextNode;
			Sns_Node_VirtualObj->StatsVar_Output = StatsVar_Output;
			Sns_Node_VirtualObj->SNS_Simulate_End_Node();

			break;
		}
		default:
			break;
		}		
		nextNode = nextNode->nextNodeData;
	}

	StatsVar_Output->SNS_Print_InputStr(StatsFile_Path);
	delete StatsVar_Output;
}

//功能:记录本模型的输出状态变量值到StatsVar_Output内
void Sns_Scenarios::SNS_Record_Stats_Value()
{
	char Stats_ModelName[SNS_MAX_STRING_LENGTH]; //用于记录输出状态变量所属模型名标志
	StatsVar_Output = new Sns_Config_Input();

	sprintf(Stats_ModelName,"\n** Sns_Scenarios_begin\n");

	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);

	sprintf(Stats_ModelName,"\n** Sns_Scenarios_end\n");

	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);
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

	if(TimeDelay == 0)//不延迟的消息
	{	
		switch(nodeData[DestiNode]->Node_Type)
		{
		case SNS_NODE_VIRTUAL://接收消息的节点
			{
				Sns_Node_Virtual * Sns_Node_VirtualObj = (Sns_Node_Virtual *)nodeData[DestiNode];
				Sns_Node_VirtualObj->SNS_Node_MsgDeal(SendMsg); 

				break;
			}
		default:

			break;
		}
	}
	else//需延迟发送的消息
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
	Sns_Message *msg = new Sns_Message();

	msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,PayLoad,PacketSize);

	SNS_Msg_Send(msg,DestiNode,TimeDelay);
}

//功能:将一个消息转发给相应的模型
//输入:msg-转发的消息，DestiNode--接收消息目的节点地址,ModelId--接收消息的模型ID,instanceId--发起模型实例号,该值默认为0,EventName--接收消息事件名称,
//     EventType--接收事件类型,TimeDelay--发送延迟
void Sns_Scenarios::Send_Aexisting_Msg(Sns_Message *msg,int DestiNode,int ModelId,int instanceId,int EventName,int EventType, clocktype  TimeDelay)
{
	msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,NULL,-1);//消息赋值

	SNS_Msg_Send(msg,DestiNode,TimeDelay);//消息发送
}
