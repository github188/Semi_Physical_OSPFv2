/*
* Copyright (c) 2014,北京航空航天大学
* All rights reserved.
*
* 系统名称: SPACE NETWORK SIMULATION SYSTEM
* 作    者: 张涛
* 当前版本: SNS 1.0
* 
* 文件名称: Sns_Node.h
* 当前版本: V 1.0.0
* 文件标识: Sns_Node类头文件
* 功能描述: 为协议/环境模型开发测试提供依附节点的支持
* 完 成 人: 
* 联系方式: 
* 完成日期: 
*
* 摘    要:
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNS_NODE_H__D5C1405E_7C0F_4D30_850A_F329619CA6A1__INCLUDED_)
#define AFX_SNS_NODE_H__D5C1405E_7C0F_4D30_850A_F329619CA6A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

/////////本部分为模型导向自动生成/////////////
#include "Sns_Scenarios.h"

class Sns_Config_Input;
class Sns_Message;
class Sim_Test;

/////////本部分为模型导向自动生成 end 用户需要加的定义在下面/////////////



class Sns_Node : public sns_base_node  
{
public:	//模型导向自动生成变量
	int Modelnum_In_Node;                   //本节点中的模型个数
	Sns_base_model ** Model_List;           //节点内模型队列
	char  *ConfFile_Path;                   //配置文件路径,由模型初始化后给出

	Sns_Config_Input * StatsVar_Output;  	//存储模型状态变量内容

	short Modelid_In_list[MAX_MODEL_NUM_INSCENA];   //某模型在本节点模型队列中的初始位置
	
	//输入消息事件名称
	enum 
	{

	};

	//输出消息事件名称
	enum 
	{

	};
	
private://模型导向自动生成变量
   Sim_Test *Sim_Test_Result;					//测试源对象

private://用户自定义变量
	

public://用户自定义变量

public://模型导向自动生成函数
	Sns_Node();
	virtual ~Sns_Node();

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

public://用户自定义函数


private://用户自定义函数


};

#endif
