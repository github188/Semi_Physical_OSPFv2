/*
* Copyright (c) 2014,北京航空航天大学
* All rights reserved.
*
* 系统名称: SPACE NETWORK SIMULATION SYSTEM
* 作    者: 张涛
* 当前版本: SNS 1.0
* 
* 文件名称: Sns_Scenarios.h
* 当前版本: V 1.0.0
* 文件标识: Sns_Scenarios类头文件
* 功能描述: 
* 完 成 人: 
* 联系方式: 
* 完成日期: 
*
* 摘    要:
*/
//////////////////////////////////////////////////////////////////////

#ifndef SNS_SCENARIOS_H
#define SNS_SCENARIOS_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////本部分为模型参数描述部分/////////////
/************************************************
***Model-Info-Begin
/************************************************
**Class_Name: Sns_Scenarios		//模型名对应的类名
**Model_Type: Scenarios			//模型类型：场景、节点、环境、协议
**Model_State:proceeding		//模型开发状态：进行、完成、注册
**Abstract:
/***********************************************
**Standard-Node-Model-Of-Scenarios     //本场景上的标准节点模型
/*Standard_Model_ofThis_Descri
/***********************************************
**User-Node-Model-Of-Scenarios     //本场景上的用户节点模型
*Sns_Node_Real;			// 
*Sns_Node_Virtual;			// 
/*User_Model_ofThis_Descri
/***********************************************
**Config-Init-Variable:          //模型初始化配置参数
*char*,unit_Of_Aclocktype;		//本场景仿真最小时间单位
*clocktype,Max_Sim_Clock;		//仿真时间
*int,seedVal;                   //本场景中产生随机数的Seed值
/*Config_VariableList_Descri
/***********************************************
**StatsData-Output-Variable:   //模型输出统计数据
/*Stats_VariableList_Descri
/***********************************************
***Model-Info-End
***********************************************/


////////////////本场景所用到的协议/环境模型枚举////////////////////////////
enum 
{
	SNS_MODEL_OSPFV2,
	SNS_MODEL_NETWORKIP,
	//SNS_MODEL_ENUM//
};  

////////////////本场景所用到的协议/环境模型枚举end////////////////////////////

////////////////本场景所用到的节点模型枚举////////////////////////////
enum 
{
	SNS_NODE_ADMIN,
	SNS_NODE_REAL,
	SNS_NODE_VIRTUAL,
	//SNS_NODE_ENUM//
};  

////////////////本场景所用到的节点模型枚举end////////////////////////////

enum//消息类型，标记输入、输出消息
{
	SNS_MSG_INPUT,	//模型输入消息
	SNS_MSG_OUTPUT	//模型输出消息
};

#define MAX_MODEL_NUM_INSCENA 100          //本场景中可支持的最大协议/环境模型类型数

#include "SNS_core.h" //平台库

class Sns_Message;
class Sns_Config_Input;

class Sns_Scenarios : public sns_base_scenarios  
{
public://模型导向自动生成的公有变量
	int Num_Nodes;					       //仿真中的节点数目
	Sns_Config_Input * Config_Input;  		//存储配置文件内容
	char  *ConfFile_Path;                   //配置文件路径
	char  *StatsFile_Path;           //输出状态变量文件路径

	Sns_Config_Input * StatsVar_Output;  	//存储模型输出状态变量的值

	////用于包跟踪
	bool Is_Packet_Track;                 //是否数据包跟踪，若是，设置Track_PacketId
	int Track_PacketId;                   //被跟踪的包ID号
	bool Is_Create_Onlyone;               //是否产生的是唯一包，在一次跟踪中

public://模型导向自动生成变量

	//依附于本模型的其他模型每类模型数量变量
	struct Sns_model_Num_ofThis_str
	{
		int Num_Sns_Node_Real;	//
		int Num_Sns_Node_Virtual;	//
		//ModelNum_ofThisList//
	};
	Sns_model_Num_ofThis_str Num_ofThis;//依附于本模型的其他模型每类模型数量变量结构 
   
	//模型输入初始化配置参数变量
	struct Sns_model_Config_Var_str
	{
		char* unit_Of_Aclocktype;	//本场景仿真最小时间单位
		clocktype max_sim_clock;	//仿真时间
		int seed_val;				//本场景中产生随机数的Seed值
		//Config_VariableList//
	};
	Sns_model_Config_Var_str Config_Var;//模型输入初始化配置参数变量结构

	//模型仿真输出统计数据变量
	struct Sns_model_Stats_Var_str 
	{
		//Stats_VariableList//
	}; 
	Sns_model_Stats_Var_str Stats_Var;//模型仿真输出统计数据变量结构  

public://用户自定义公有变量

private: //用户自定义私有变量
	
public://模型导向自动生成的公有函数
	Sns_Scenarios();
	virtual ~Sns_Scenarios();

	//功能:场景初始化函数,读取节点对应配置文件,配置场景初始化参数
	//     为场景中所用到节点对象实例化,并启动节点初始化
	void SNS_Init();	

   //功能:仿真运行函数，处理消息队列
	void SNS_Simulate_Run();

	//功能:仿真运行结束，处理仿真结束后的一些事,如仿真结果输出等
	void SNS_Simulate_End();

    //功能:本仿真场景中消息发送函数
	//输入:SendMsg--需发送的消息,DestiNode--目的节点id,TimeDelay--发送延迟
	void SNS_Msg_Send(Sns_Message *SendMsg, int DestiNode, clocktype  TimeDelay);  

private://模型导向自动生成的私有函数

	//功能:记录本模型的输出状态变量值到StatsVar_Output内
	void SNS_Record_Stats_Value();

	//功能:根据配置文件初始化场景内所有节点
	void All_Node_init();

	//功能:发送一个新消息
	//输入:DestiNode--消息目的节点地址,ModelId--发起消息的模型ID,instanceId--发起模型实例号,EventName--消息事件名称,
	//     EventType--事件类型,PayLoad--消息载荷,PacketSize--消息载荷大小,TimeDelay--发送延迟
	//     发送空消息时，PayLoad=NULL，PacketSize=0
	void Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay);

	//功能:将一个消息转发给相应的模型
	//输入:msg-转发的消息，DestiNode--接收消息目的节点地址,ModelId--接收消息的模型ID,instanceId--发起模型实例号,该值默认为0,EventName--接收消息事件名称,
	//     EventType--接收事件类型,TimeDelay--发送延迟
	void Send_Aexisting_Msg(Sns_Message *msg,int DestiNode,int ModelId,int instanceId,int EventName,int EventType, clocktype  TimeDelay);

public://用户自定义公有函数

            	    
private://用户自定义私有函数


};

#endif
