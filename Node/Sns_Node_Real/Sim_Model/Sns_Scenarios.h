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
* 功能描述: 为协议/环境模型开发测试提供模拟的场景设置
* 完 成 人: 
* 联系方式: 
* 完成日期: 
*
* 摘    要:
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNS_SCENARIOS_H__F1880FFC_ADC8_4973_9338_8EB70E71708C__INCLUDED_)
#define AFX_SNS_SCENARIOS_H__F1880FFC_ADC8_4973_9338_8EB70E71708C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

////////////////本类都由模型导向自动生成////////////////////////////

////////////////本场景所用到的协议/环境模型枚举////////////////////////////
enum 
{
	//SNS_MODEL_ENUM//
};  

////////////////本场景所用到的协议/环境模型枚举end////////////////////////////

////////////////本场景所用到的节点模型枚举////////////////////////////
enum 
{
	SNS_NODE_REAL
};  

////////////////本场景所用到的节点模型枚举end////////////////////////////

enum										//消息类型，标记输入、输出消息
{
	SNS_MSG_INPUT,	//模型输入消息
	SNS_MSG_OUTPUT	//模型输出消息
};

#define MAX_MODEL_NUM_INSCENA 100          //本场景中可支持的最大协议/环境模型类型数

#include "SNS_core.h" //平台库

class Sim_Test;
class Sns_Message;
class Sns_Config_Input;

class Sns_Scenarios : public sns_base_scenarios  
{
public:
	int Num_Nodes;					//仿真中的节点数目
	Sim_Test *Sim_Test_result;		//测试源对象
	char  *ConfFile_Path;           //配置文件路径,由模型初始化后给出
	char  *StatsFile_Path;           //输出状态变量文件路径

	Sns_Config_Input * StatsVar_Output;  	//存储模型状态变量内容

	////用于包跟踪
	bool Is_Packet_Track;                 //是否数据包跟踪，若是，设置Track_PacketId
	int Track_PacketId;                   //被跟踪的包ID号
	bool Is_Create_Onlyone;               //是否产生的是唯一包，在一次跟踪中
	
public:
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

private:

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
};

#endif
