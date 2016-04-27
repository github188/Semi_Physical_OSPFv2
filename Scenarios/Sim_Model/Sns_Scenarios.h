/*
* Copyright (c) 2014,�������պ����ѧ
* All rights reserved.
*
* ϵͳ����: SPACE NETWORK SIMULATION SYSTEM
* ��    ��: ����
* ��ǰ�汾: SNS 1.0
* 
* �ļ�����: Sns_Scenarios.h
* ��ǰ�汾: V 1.0.0
* �ļ���ʶ: Sns_Scenarios��ͷ�ļ�
* ��������: 
* �� �� ��: 
* ��ϵ��ʽ: 
* �������: 
*
* ժ    Ҫ:
*/
//////////////////////////////////////////////////////////////////////

#ifndef SNS_SCENARIOS_H
#define SNS_SCENARIOS_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////������Ϊģ�Ͳ�����������/////////////
/************************************************
***Model-Info-Begin
/************************************************
**Class_Name: Sns_Scenarios		//ģ������Ӧ������
**Model_Type: Scenarios			//ģ�����ͣ��������ڵ㡢������Э��
**Model_State:proceeding		//ģ�Ϳ���״̬�����С���ɡ�ע��
**Abstract:
/***********************************************
**Standard-Node-Model-Of-Scenarios     //�������ϵı�׼�ڵ�ģ��
/*Standard_Model_ofThis_Descri
/***********************************************
**User-Node-Model-Of-Scenarios     //�������ϵ��û��ڵ�ģ��
*Sns_Node_Real;			// 
*Sns_Node_Virtual;			// 
/*User_Model_ofThis_Descri
/***********************************************
**Config-Init-Variable:          //ģ�ͳ�ʼ�����ò���
*char*,unit_Of_Aclocktype;		//������������Сʱ�䵥λ
*clocktype,Max_Sim_Clock;		//����ʱ��
*int,seedVal;                   //�������в����������Seedֵ
/*Config_VariableList_Descri
/***********************************************
**StatsData-Output-Variable:   //ģ�����ͳ������
/*Stats_VariableList_Descri
/***********************************************
***Model-Info-End
***********************************************/


////////////////���������õ���Э��/����ģ��ö��////////////////////////////
enum 
{
	SNS_MODEL_OSPFV2,
	SNS_MODEL_NETWORKIP,
	//SNS_MODEL_ENUM//
};  

////////////////���������õ���Э��/����ģ��ö��end////////////////////////////

////////////////���������õ��Ľڵ�ģ��ö��////////////////////////////
enum 
{
	SNS_NODE_ADMIN,
	SNS_NODE_REAL,
	SNS_NODE_VIRTUAL,
	//SNS_NODE_ENUM//
};  

////////////////���������õ��Ľڵ�ģ��ö��end////////////////////////////

enum//��Ϣ���ͣ�������롢�����Ϣ
{
	SNS_MSG_INPUT,	//ģ��������Ϣ
	SNS_MSG_OUTPUT	//ģ�������Ϣ
};

#define MAX_MODEL_NUM_INSCENA 100          //�������п�֧�ֵ����Э��/����ģ��������

#include "SNS_core.h" //ƽ̨��

class Sns_Message;
class Sns_Config_Input;

class Sns_Scenarios : public sns_base_scenarios  
{
public://ģ�͵����Զ����ɵĹ��б���
	int Num_Nodes;					       //�����еĽڵ���Ŀ
	Sns_Config_Input * Config_Input;  		//�洢�����ļ�����
	char  *ConfFile_Path;                   //�����ļ�·��
	char  *StatsFile_Path;           //���״̬�����ļ�·��

	Sns_Config_Input * StatsVar_Output;  	//�洢ģ�����״̬������ֵ

	////���ڰ�����
	bool Is_Packet_Track;                 //�Ƿ����ݰ����٣����ǣ�����Track_PacketId
	int Track_PacketId;                   //�����ٵİ�ID��
	bool Is_Create_Onlyone;               //�Ƿ��������Ψһ������һ�θ�����

public://ģ�͵����Զ����ɱ���

	//�����ڱ�ģ�͵�����ģ��ÿ��ģ����������
	struct Sns_model_Num_ofThis_str
	{
		int Num_Sns_Node_Real;	//
		int Num_Sns_Node_Virtual;	//
		//ModelNum_ofThisList//
	};
	Sns_model_Num_ofThis_str Num_ofThis;//�����ڱ�ģ�͵�����ģ��ÿ��ģ�����������ṹ 
   
	//ģ�������ʼ�����ò�������
	struct Sns_model_Config_Var_str
	{
		char* unit_Of_Aclocktype;	//������������Сʱ�䵥λ
		clocktype max_sim_clock;	//����ʱ��
		int seed_val;				//�������в����������Seedֵ
		//Config_VariableList//
	};
	Sns_model_Config_Var_str Config_Var;//ģ�������ʼ�����ò��������ṹ

	//ģ�ͷ������ͳ�����ݱ���
	struct Sns_model_Stats_Var_str 
	{
		//Stats_VariableList//
	}; 
	Sns_model_Stats_Var_str Stats_Var;//ģ�ͷ������ͳ�����ݱ����ṹ  

public://�û��Զ��幫�б���

private: //�û��Զ���˽�б���
	
public://ģ�͵����Զ����ɵĹ��к���
	Sns_Scenarios();
	virtual ~Sns_Scenarios();

	//����:������ʼ������,��ȡ�ڵ��Ӧ�����ļ�,���ó�����ʼ������
	//     Ϊ���������õ��ڵ����ʵ����,�������ڵ��ʼ��
	void SNS_Init();	

   //����:�������к�����������Ϣ����
	void SNS_Simulate_Run();

	//����:�������н������������������һЩ��,������������
	void SNS_Simulate_End();

    //����:�����泡������Ϣ���ͺ���
	//����:SendMsg--�跢�͵���Ϣ,DestiNode--Ŀ�Ľڵ�id,TimeDelay--�����ӳ�
	void SNS_Msg_Send(Sns_Message *SendMsg, int DestiNode, clocktype  TimeDelay);  

private://ģ�͵����Զ����ɵ�˽�к���

	//����:��¼��ģ�͵����״̬����ֵ��StatsVar_Output��
	void SNS_Record_Stats_Value();

	//����:���������ļ���ʼ�����������нڵ�
	void All_Node_init();

	//����:����һ������Ϣ
	//����:DestiNode--��ϢĿ�Ľڵ��ַ,ModelId--������Ϣ��ģ��ID,instanceId--����ģ��ʵ����,EventName--��Ϣ�¼�����,
	//     EventType--�¼�����,PayLoad--��Ϣ�غ�,PacketSize--��Ϣ�غɴ�С,TimeDelay--�����ӳ�
	//     ���Ϳ���Ϣʱ��PayLoad=NULL��PacketSize=0
	void Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay);

	//����:��һ����Ϣת������Ӧ��ģ��
	//����:msg-ת������Ϣ��DestiNode--������ϢĿ�Ľڵ��ַ,ModelId--������Ϣ��ģ��ID,instanceId--����ģ��ʵ����,��ֵĬ��Ϊ0,EventName--������Ϣ�¼�����,
	//     EventType--�����¼�����,TimeDelay--�����ӳ�
	void Send_Aexisting_Msg(Sns_Message *msg,int DestiNode,int ModelId,int instanceId,int EventName,int EventType, clocktype  TimeDelay);

public://�û��Զ��幫�к���

            	    
private://�û��Զ���˽�к���


};

#endif
