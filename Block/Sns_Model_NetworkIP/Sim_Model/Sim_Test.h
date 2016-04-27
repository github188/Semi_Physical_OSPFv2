/*
* Copyright (c) 2014,北京航空航天大学
* All rights reserved.
*
* 系统名称: SPACE NETWORK SIMULATION SYSTEM
* 作    者: 张涛
* 当前版本: SNS 1.0
* 
* 文件名称: Sim_Test.h
* 当前版本: V 1.0.0
* 文件标识: Sim_Test类头文件
* 功能描述: 用于协议/环境模型开发测试
* 完 成 人: 
* 联系方式: 
* 完成日期: 
*
* 摘    要:
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIM_TEST_H__02205B67_2972_44B1_BED5_3778CD9A1515__INCLUDED_)
#define AFX_SIM_TEST_H__02205B67_2972_44B1_BED5_3778CD9A1515__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#include "SNS_core.h" //平台库

class Sns_Scenarios;
class Sns_Node;
class Sns_Message;
class Sns_Model_NetworkIP;


class Sim_Test
{
public://模型导向自动生成变量
	Sns_Scenarios * Scenarios_Data;	//当前测试模型对应的场景
	Sns_Node *Cur_Node;				//当前测试模型对应的节点

	//被测模型申明
	Sns_Model_NetworkIP *Sns_model_testObj; //当前测试的模型

private://用户自定义变量，本处给出的变量仅用于本例子	


public://用户自定义变量


public://模型导向自动生成函数

    //构造函数，析构函数
	Sim_Test();
	virtual ~Sim_Test();

	//功能:测试运行
	void Test_Run();	

private://模型导向自动生成函数
	//功能:发送一个新消息
	//输入:DestiNode--消息目的节点地址,ProtocolId--发起消息的模型ID,EventName--消息事件名称,
	//     EventType--事件类型,PayLoad--消息载荷,PacketSize--消息载荷大小,TimeDelay--发送延迟
	void Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay);


public://模型导向自动生成函数

/////////////////////////////////被测模型出消息处理函数/////////////////////////////////////////
	//功能：MSG_OutEVENT_NETWORK_ToMAC事件函数 
	void  Process_MSG_OutEVENT_NETWORK_ToMAC(Sns_Message *msg); 

	//功能：MSG_OutEVENT_NETWORK_ToTransport事件函数 
	void  Process_MSG_OutEVENT_NETWORK_ToTransport(Sns_Message *msg); 

	//功能：MSG_OutEVENT_NETWORK_ToProtocol_OSPFv2事件函数 
	void  Process_MSG_OutEVENT_NETWORK_ToProtocol_OSPFv2(Sns_Message *msg); 

	//Sns_Msg_In_Func//


private://用户自定义函数

	
};

#endif
