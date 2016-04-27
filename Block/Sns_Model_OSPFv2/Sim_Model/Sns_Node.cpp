/*
* Copyright (c) 2014,北京航空航天大学
* All rights reserved.
*
* 系统名称: SPACE NETWORK SIMULATION SYSTEM
* 作    者: 张涛
* 当前版本: SNS 1.0
* 
* 文件名称: Sns_Node.cpp
* 当前版本: V 1.0.0
* 文件标识: Sns_Node类源文件
* 功能描述: 为协议/环境模型开发测试提供依附节点的支持
* 完 成 人: 
* 联系方式: 
* 完成日期: 
*
* 摘    要:
*/
//////////////////////////////////////////////////////////////////////

/////////本部分为模型导向自动生成/////////////
#include "stdafx.h"//基本c++库
#include "Sns_Config_Input.h"   //平台库
#include "Sns_Message.h"//平台库

#include "Sns_Node.h"

#include "Sim_Test.h"
#include "Sns_Model_OSPFv2.h"

/////////本部分为模型导向自动生成 end 用户需要加的定义在下面/////////////

/////////////////////////构造函数，析构函数/////////////////////////////////////////////

Sns_Node::Sns_Node()
{
	
}

Sns_Node::~Sns_Node()
{

}

////////////////////////节点初始化函数///////////////////////////////////////

//功能:节点初始化函数,读取节点对应配置文件,配置节点初始化配置参数
//     为节点中所用到模型对象实例化,并启动模型初始化
void Sns_Node::Node_init()
{
	//////////////////////模型导向自动生成////////////////////////////
	Modelnum_In_Node = 1;

	Model_OfNode_Init();

	//////////////////////模型导向自动生成 end////////////////////////////
}

//功能:初始化本节点所有环境/协议模型
void Sns_Node::Model_OfNode_Init()
{
	/*模型导向自动生成*/

	short modelist_id = 0;

	int i;

	/////////////////////初始化模型链表/////////////////////////////////
	Model_List = (Sns_base_model **)checked_pc_malloc(sizeof(Sns_base_model *) * Modelnum_In_Node);	// 为模型链表分配内存

	/////////////////////初始化具体模型/////////////////////////////////
	
	Sns_Model_OSPFv2 *Sns_Model_OSPFv2Obj = new Sns_Model_OSPFv2();	

	for(i = 0; i < Modelnum_In_Node; i++)
	{
        Model_List[modelist_id] = (Sns_base_model *)Sns_Model_OSPFv2Obj;
		
		Sns_Model_OSPFv2Obj->Model_id = SNS_MODEL_OSPFV2;                          //初始化协议ID号，用于标识协议
		Sns_Model_OSPFv2Obj->Scenarios_Data = (Sns_Scenarios *)Scenarios_Data;	//实例化场景类
		Sns_Model_OSPFv2Obj->Model_Instance_id = i;								//节点中该链路层协议的实例标志,即为第几个物理端口
		Sns_Model_OSPFv2Obj->Cur_Node_id = Node_id;								//协议依附节点ID
		Sns_Model_OSPFv2Obj->Cur_Node_id_inOneType = Node_id_InOnetype;			//协议依附节点类型ID
		Sns_Model_OSPFv2Obj->Cur_Node_Name = "Sns_Node";						//协议依附节点类名
		Sns_Model_OSPFv2Obj->ConfFile_Path = ConfFile_Path;					//协议配置文件路径
		
		if(i==0)
			Modelid_In_list[SNS_MODEL_OSPFV2] = modelist_id;						//SNS_MAC_LINK在本节点model list中的位置

		Sns_Model_OSPFv2Obj->Model_init();										//调用协议初始化函数

		modelist_id ++;
	}
	
	/////////////////////初始化具体模型 end/////////////////////////////////

	/*自动生成end*/
}

//功能:节点初始化后的处理函数,用于有时需要所有节点都初始化完成才可执行的动作
void Sns_Node::Node_init_end()
{
	/////////////////////运行init_end函数/////////////////////////////////

	int i;
	short modelist_id = 0;

	Sns_Model_OSPFv2 *Sns_Model_OSPFv2Obj;

	for(i = 0; i < Modelnum_In_Node; i++)
	{
		Sns_Model_OSPFv2Obj = (Sns_Model_OSPFv2 *)Model_List[modelist_id];

		Sns_Model_OSPFv2Obj->Model_init_end();						//调用协议初始化结束后的处理函数

		modelist_id ++;
	}

	/////////////////////运行init_end函数 end/////////////////////////////////

	/////////////////////关于测试类/////////////////////////////////

	short listnum = 0;
	listnum = Modelid_In_list[SNS_MODEL_OSPFV2];

	Sim_Test_Result = new Sim_Test();
	Sim_Test_Result->Scenarios_Data = (Sns_Scenarios *)Scenarios_Data;//实例化场景类
	Sim_Test_Result->Cur_Node = this;              //实例化节点类

	Sim_Test_Result->Sns_model_testObj = (Sns_Model_OSPFv2 *)Model_List[listnum];  ////实例化模型类

	Sim_Test_Result->Test_Run();							//仿真系统开始运行触发事件
	/////////////////////关于测试类end/////////////////////////////////
}
///////////////////节点消息处理函数//////////////////////////////////////////
/*根据接收的消息,首先判断属于哪个模型（模型ID从1开始，表示本节点上依附模型，若为0，表示为节点本身）;
其次判断是出事件还是入事件，若是入事件，直接调用模型入事件处理函数，若是出事件，则处理*/
//本部分框架为模型导向自动生成

//功能:节点的消息处理函数,接收各类模型/节点输入输出事件,
//     对于模型输入消息,将消息发给模型;对于节点输入消息,触动相应函数并处理
//     对于输出消息,触动相应函数并处理
void Sns_Node::SNS_Node_MsgDeal(Sns_Message *msg)
{
	Sns_Model_OSPFv2 *Sns_Model_OSPFv2Obj = NULL;
	short modelist_id;

	modelist_id = Modelid_In_list[SNS_MODEL_OSPFV2] + msg->Model_Instance_id; 

	Sns_Model_OSPFv2Obj = (Sns_Model_OSPFv2 *)Model_List[modelist_id];

	switch(msg->Model_id) 
	{
	case -1://表示节点本身的消息
		{
			switch(msg->Event_Name) 
			{

			default:

				break;
			}

			break;
		}

	case SNS_MODEL_OSPFV2://模型消息处理
	{
		Sns_Model_OSPFv2 *Sns_Model_OSPFv2Obj = NULL;
		modelist_id = Modelid_In_list[SNS_MODEL_OSPFV2] + msg->Model_Instance_id; 
		Sns_Model_OSPFv2Obj = (Sns_Model_OSPFv2 *)Model_List[modelist_id];

		if (msg->Event_Type==SNS_MSG_INPUT)//输入事件
		{
			Sns_Model_OSPFv2Obj->SNS_Model_MsgDeal(msg);
		}
		else//输出事件
		{
			switch(msg->Event_Name)
			{
			case Sns_Model_OSPFv2::MSG_OutEVENT_MSG_OutEVENT_Ospfv2_toNetw:
			{
				Sim_Test_Result->Process_MSG_OutEVENT_MSG_OutEVENT_Ospfv2_toNetw(msg);
				break;
			}
			//SNS_MSG_EVENT_OUT//
			default:
				break;
			}
		}
		break;
	}

	default:

		break;
	}
}

////////////////////////////仿真结束处理函数//////////////////////////////////////////////
//功能:处理节点模型在仿真结束后的一些事,如节点模型仿真结果输出等
void Sns_Node::SNS_Simulate_End_Node()
{
	int i;
	short modelist_id = 0;

	SNS_Record_Stats_Value();

	Sns_Model_OSPFv2 *Sns_Model_OSPFv2Obj;

	for(i = 0; i < Modelnum_In_Node; i++)
	{
		Sns_Model_OSPFv2Obj = (Sns_Model_OSPFv2 *)Model_List[modelist_id];
		Sns_Model_OSPFv2Obj->StatsVar_Output = StatsVar_Output;
		Sns_Model_OSPFv2Obj->SNS_Simulate_End_Model();						

		modelist_id ++;
	}	
}

//功能:记录本模型的输出状态变量值到StatsVar_Output内
void Sns_Node::SNS_Record_Stats_Value()
{
	char Stats_ModelName[SNS_MAX_STRING_LENGTH]; //用于记录输出状态变量所属模型名标志

	sprintf(Stats_ModelName,"\n** Sns_Node_begin\n");

	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);

	sprintf(Stats_ModelName,"\n** Sns_Node_end\n");

	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);
}

//功能:将一个消息转发给相应的模型
//输入:msg-转发的消息，DestiNode--接收消息目的节点地址,ModelId--接收消息的模型ID,instanceId--发起模型实例号,该值默认为0,EventName--接收消息事件名称,
//     EventType--接收事件类型,TimeDelay--发送延迟
void Sns_Node::Send_Aexisting_Msg(Sns_Message *msg,int DestiNode,int ModelId,int instanceId,int EventName,int EventType, clocktype  TimeDelay)
{
	Sns_Scenarios *scenariosdata;

	scenariosdata = (Sns_Scenarios *)Scenarios_Data;

	msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,NULL,-1);//消息赋值

	scenariosdata->SNS_Msg_Send(msg,DestiNode,TimeDelay);//消息发送
}

//功能:发送一个新消息
//输入:DestiNode--消息目的节点地址,ModelId--发起消息的模型ID,instanceId--发起模型实例号,该值默认为0,EventName--消息事件名称,
//     EventType--事件类型,PayLoad--消息载荷,PacketSize--消息载荷大小,TimeDelay--发送延迟
//     发送空消息时，PayLoad=NULL，PacketSize=0
void Sns_Node::Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay)
{
	Sns_Scenarios *scenariosdata;

	scenariosdata = (Sns_Scenarios *)Scenarios_Data;

	Sns_Message *msg = new Sns_Message();

    msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,PayLoad,PacketSize);

	scenariosdata->SNS_Msg_Send(msg,DestiNode,TimeDelay);
}
