/*
* Copyright (c) 2014,北京航空航天大学
* All rights reserved.
*
* 系统名称: SPACE NETWORK SIMULATION SYSTEM
* 作    者: 张涛
* 当前版本: SNS 1.0
* 
* 文件名称: Sim_Test.cpp
* 当前版本: V 1.0.0
* 文件标识: Sim_Test类源文件
* 功能描述: 用于协议/环境模型开发测试
* 完 成 人: 
* 联系方式: 
* 完成日期: 
*
* 摘    要:
*/
//////////////////////////////////////////////////////////////////////

#include "stdafx.h" //基本c++库
#include <time.h>
#include "Sns_Message.h" //平台库
#include "Sim_Test.h"
#include "Sns_Scenarios.h"
#include "Sns_Node_Virtual.h"


Sim_Test::Sim_Test()
{
	

}

Sim_Test::~Sim_Test()
{

}

//功能:发送一个新消息
//输入:DestiNode--消息目的节点地址,ModelId--发起消息的模型ID,instanceId--发起模型实例号,EventName--消息事件名称,
//     EventType--事件类型,PayLoad--消息载荷,PacketSize--消息载荷大小,TimeDelay--发送延迟
//     发送空消息时，PayLoad=NULL，PacketSize=0
void Sim_Test::Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay)
{
	Sns_Message *msg = new Sns_Message();
	
    msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,PayLoad,PacketSize);

	Scenarios_Data->SNS_Msg_Send(msg,DestiNode,TimeDelay);
}

//功能:测试运行
void Sim_Test::Test_Run()
{
	

}

///////////////////////////////输出事件对应处理函数///////////////////////////////////////////
//Sns_Msg_In_Func//
