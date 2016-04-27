/*
* Copyright (c) 2014,北京航空航天大学
* All rights reserved.
*
* 系统名称: SPACE NETWORK SIMULATION SYSTEM
* 作    者: 张涛
* 当前版本: SNS 1.0
* 
* 文件名称: Sns_Node_Real.h
* 当前版本: V 1.0.0
* 文件标识: Sns_Node_Real类头文件
* 功能描述: 
* 完 成 人: 
* 联系方式: 
* 完成日期: 
*
* 摘    要:
*/
//////////////////////////////////////////////////////////////////////

#ifndef SNS_NODE_REAL_H
#define SNS_NODE_REAL_H

#if _MSC_VER > 1000
#pragma once
#endif

/////////////本部分为模型参数描述部分/////////////
/************************************************
***Model-Info-Begin
/************************************************
**Model_Name:Sns_Node_Real;             //模型名
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
**Config-Init-Variable:          //模型初始化配置参数
/*Config_VariableList_Descri
/***********************************************
**StatsData-Output-Variable:   //模型输出统计数据
/*Stats_VariableList_Descri
/***********************************************
**SnsMsg-Input:                  //输入事件
*MSG_InEVENT_ReceiveFromOtherNodes;			// 
*MSG_InEVENT_ReceiveFromRealNode;			// 
/*MesInputVariable_Descri
/***********************************************
**SnsMsg-Output:                 //输出事件
*MSG_OutEVENT_SendToOtherNodes;			// 
*MSG_OutEVENT_SendToRealNode;			// 
/*MesOutputVariable_Descri
/***********************************************
***Model-Info-End
***********************************************/

#include "Sns_Scenarios.h"
#include "GlobleStructures.h"
#include "WinPcap.h"

class Sns_Message;
class Sns_Config_Input;

class Sns_Node_Real : public sns_base_node  
{
public://模型导向自动生成的公有变量
	
	int Model_num_In_Node;                   //本节点中的模型个数
	Sns_base_model ** Model_List;           //节点内模型队列
	
	Sns_Config_Input * Config_Input;  		//存储配置文件内容
	char  *ConfFile_Path;                   //配置文件路径,由场景初始化后给出

	Sns_Config_Input * StatsVar_Output;  	//存储模型输出状态变量的值

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
		MSG_InEVENT_ReceiveFromOtherNodes,			// 
		MSG_InEVENT_ReceiveFromRealNode,			// 
		//MesInputVariable//
	};

	//输出消息事件名称
	enum 
	{
		MSG_OutEVENT_SendToOtherNodes,			// 
		MSG_OutEVENT_SendToRealNode,			// 
		//MesOutputVariable//
	};

public://用户自定义公有变量
	int numberInterfaces;
	InterfaceInfoType interfaceInfo[MAX_NUM_INTERFACES];
	WinPcap caper;
private: //用户自定义私有变量
	
public://模型导向自动生成的公有函数

	Sns_Node_Real();
	virtual ~Sns_Node_Real();
	
	//功能:消息处理函数,接收模型输入事件,触动相应函数,并处理
	void SNS_Node_MsgDeal(Sns_Message *msg);
	
   //功能:模型初始化函数,读取模型对应配置文件,配置模型初始化配置参数
    void Node_init();
    
   //功能:节点初始化后的处理函数,用于有时需要所有节点都初始化完成才可执行的动作
	void Node_init_end();

	//功能:处理节点模型在仿真结束后的一些事,如节点模型仿真结果输出等
	void SNS_Simulate_End_Node();	
	
public: //模型导向自动生成函数,用户输入事件处理
	//功能：MSG_InEVENT_ReceiveFromOtherNodes事件函数 
	void Process_MSG_InEVENT_ReceiveFromOtherNodes(Sns_Message *msg); 

	//功能：MSG_InEVENT_ReceiveFromRealNode事件函数 
	void Process_MSG_InEVENT_ReceiveFromRealNode(Sns_Message *msg); 

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
	void ReceiveFromRealNode(char* packet, int packetSize);
            	    
private://用户自定义私有函数

};

#endif
