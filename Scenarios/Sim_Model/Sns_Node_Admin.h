/*
* Copyright (c) 2014,北京航空航天大学
* All rights reserved.
*
* 系统名称: SPACE NETWORK SIMULATION SYSTEM
* 作    者: 张涛
* 当前版本: SNS 1.0
* 
* 文件名称: Sns_Node_Admin.h
* 当前版本: V 1.0.0
* 文件标识: Sns_Node_Admin类头文件
* 功能描述: 本节点为仿真场景顶层管理节点,节点id为0,负责进行仿真顶层处理,如数据统计\性能分析等,以及仿真测试等
* 完 成 人: 张涛
* 联系方式: 
* 完成日期: 
*
* 摘    要:
*/
//////////////////////////////////////////////////////////////////////

#ifndef SNS_NODE_ADMIN_H
#define SNS_NODE_ADMIN_H

#if _MSC_VER > 1000
#pragma once
#endif

/////////////本部分为模型参数描述部分/////////////
/************************************************
***Model-Info-Begin
/************************************************
**Model_Name:ModelName;             //模型名
**Class_Name:ClassName;             //模型名对应的类名
**Model_Type:Node;                  //模型类型：场景、节点、环境、协议
**ModelState:proceeding             //模型开发状态：进行、完成、注册
**Abstract:
/***********************************************
**Standard-Environment/Protocols-Model-OfNode     //本节点上的标准环境或协议模型
/*Standard_Model_ofThis_Descri
/***********************************************
**User-Environment/Protocols-Model-OfNode     //本节点上的用户环境或协议模型
/*User_Model_ofThis_Descri
/***********************************************
**Confi-Init-Variable:          //模型初始化配置参数
/*Config_VariableList_Descri
/***********************************************
**StatsData-Output-Variable:   //模型输出统计数据
/*Stats_VariableList_Descri
/***********************************************
**SnsMsg-Input:                  //输入事件
* Acquisition_Interval;          //信息采集定时事件
/*MesInputVariable_Descri
/***********************************************
**SnsMsg-Output:                 //输出事件
/*MesOutputVariable_Descri
/***********************************************
***Model-Info-End
***********************************************/

/////////本部分为模型导向自动生成/////////////
#include "Sns_Scenarios.h"

class Sns_Message;
class Sns_Config_Input;


/////////本部分为模型导向自动生成 end 用户需要加的定义在下面/////////////



class Sns_Node_Admin : public sns_base_node  
{
public:	//模型导向自动生成的公有变量
	int Model_num_In_Node;                   //本节点中的模型个数
	Sns_base_model ** Model_List;           //节点内模型队列

	Sns_Config_Input * StatsVar_Output;  	//存储模型输出状态变量的值

	Sns_Config_Input * Config_Input;  		//存储配置文件内容
	char  *ConfFile_Path;                   //配置文件路径,由模型初始化后给出

	short Modelid_In_list[MAX_MODEL_NUM_INSCENA];   //某模型在本节点模型队列中的初始位置

public://模型导向自动生成变量

	//依附于本模型的其他模型每类模型数量变量
	struct Sns_model_Num_ofThis_str
	{
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
		MSG_InEVENT_Acquisition_Interval           //信息采集定时事件
		//MesInputVariable//
	};

	//输出消息事件名称
	enum 
	{
		//MesOutputVariable//
	};

private://用户自定义私有变量


public://用户自定义公有变量
	clocktype Acquisition_Interval;


public://模型导向自动生成的公有函数
	Sns_Node_Admin();
	virtual ~Sns_Node_Admin();

	//功能:节点的消息处理函数,接收各类模型/节点输入输出事件,
	//     对于模型输入消息,将消息发给模型;对于节点输入消息,触动相应函数并处理
	//     对于输出消息,触动相应函数并处理
	void SNS_Node_MsgDeal(Sns_Message *msg);	

	//功能:节点初始化函数,读取节点对应配置文件,配置节点初始化配置参数
	//     为节点中所用到模型对象实例化,并启动模型初始化
	void Node_init();

	//功能:节点初始化后的处理函数,用于有时需要所有节点都初始化完成才可执行的动作
	void Node_init_end();

	//功能:处理节点模型在仿真结束后的一些事,如节点模型仿真结果输出等
	void SNS_Simulate_End_Node();

public: //模型导向自动生成函数,用户输入事件处理
  
	//功能:MSG_InEVENT_Acquisition_Interval事件函数,产生定时，用于采集仿真系统信息
   void Msg_InEvent_Acquisition_Interval(Sns_Message *msg);
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


private://用户自定义私有函数


};

#endif
