/*
* Copyright (c) 2014,�������պ����ѧ
* All rights reserved.
*
* ϵͳ����: SPACE NETWORK SIMULATION SYSTEM
* ��    ��: ����
* ��ǰ�汾: SNS 1.0
* 
* �ļ�����: Sns_Node_Admin.h
* ��ǰ�汾: V 1.0.0
* �ļ���ʶ: Sns_Node_Admin��ͷ�ļ�
* ��������: ���ڵ�Ϊ���泡���������ڵ�,�ڵ�idΪ0,������з��涥�㴦��,������ͳ��\���ܷ�����,�Լ�������Ե�
* �� �� ��: ����
* ��ϵ��ʽ: 
* �������: 
*
* ժ    Ҫ:
*/
//////////////////////////////////////////////////////////////////////

#ifndef SNS_NODE_ADMIN_H
#define SNS_NODE_ADMIN_H

#if _MSC_VER > 1000
#pragma once
#endif

/////////////������Ϊģ�Ͳ�����������/////////////
/************************************************
***Model-Info-Begin
/************************************************
**Model_Name:ModelName;             //ģ����
**Class_Name:ClassName;             //ģ������Ӧ������
**Model_Type:Node;                  //ģ�����ͣ��������ڵ㡢������Э��
**ModelState:proceeding             //ģ�Ϳ���״̬�����С���ɡ�ע��
**Abstract:
/***********************************************
**Standard-Environment/Protocols-Model-OfNode     //���ڵ��ϵı�׼������Э��ģ��
/*Standard_Model_ofThis_Descri
/***********************************************
**User-Environment/Protocols-Model-OfNode     //���ڵ��ϵ��û�������Э��ģ��
/*User_Model_ofThis_Descri
/***********************************************
**Confi-Init-Variable:          //ģ�ͳ�ʼ�����ò���
/*Config_VariableList_Descri
/***********************************************
**StatsData-Output-Variable:   //ģ�����ͳ������
/*Stats_VariableList_Descri
/***********************************************
**SnsMsg-Input:                  //�����¼�
* Acquisition_Interval;          //��Ϣ�ɼ���ʱ�¼�
/*MesInputVariable_Descri
/***********************************************
**SnsMsg-Output:                 //����¼�
/*MesOutputVariable_Descri
/***********************************************
***Model-Info-End
***********************************************/

/////////������Ϊģ�͵����Զ�����/////////////
#include "Sns_Scenarios.h"

class Sns_Message;
class Sns_Config_Input;


/////////������Ϊģ�͵����Զ����� end �û���Ҫ�ӵĶ���������/////////////



class Sns_Node_Admin : public sns_base_node  
{
public:	//ģ�͵����Զ����ɵĹ��б���
	int Model_num_In_Node;                   //���ڵ��е�ģ�͸���
	Sns_base_model ** Model_List;           //�ڵ���ģ�Ͷ���

	Sns_Config_Input * StatsVar_Output;  	//�洢ģ�����״̬������ֵ

	Sns_Config_Input * Config_Input;  		//�洢�����ļ�����
	char  *ConfFile_Path;                   //�����ļ�·��,��ģ�ͳ�ʼ�������

	short Modelid_In_list[MAX_MODEL_NUM_INSCENA];   //ĳģ���ڱ��ڵ�ģ�Ͷ����еĳ�ʼλ��

public://ģ�͵����Զ����ɱ���

	//�����ڱ�ģ�͵�����ģ��ÿ��ģ����������
	struct Sns_model_Num_ofThis_str
	{
		//ModelNum_ofThisList//
	};
	Sns_model_Num_ofThis_str Num_ofThis;//�����ڱ�ģ�͵�����ģ��ÿ��ģ�����������ṹ 
   
	//ģ�������ʼ�����ò�������
	struct Sns_model_Config_Var_str
	{
		//Config_VariableList//  
	};
	Sns_model_Config_Var_str Config_Var;//ģ�������ʼ�����ò��������ṹ

	//ģ�ͷ������ͳ�����ݱ���
	struct Sns_model_Stats_Var_str 
	{
		//Stats_VariableList//
	}; 
	Sns_model_Stats_Var_str Stats_Var;//ģ�ͷ������ͳ�����ݱ����ṹ  

	//������Ϣ�¼�����
	enum 
	{
		MSG_InEVENT_Acquisition_Interval           //��Ϣ�ɼ���ʱ�¼�
		//MesInputVariable//
	};

	//�����Ϣ�¼�����
	enum 
	{
		//MesOutputVariable//
	};

private://�û��Զ���˽�б���


public://�û��Զ��幫�б���
	clocktype Acquisition_Interval;


public://ģ�͵����Զ����ɵĹ��к���
	Sns_Node_Admin();
	virtual ~Sns_Node_Admin();

	//����:�ڵ����Ϣ������,���ո���ģ��/�ڵ���������¼�,
	//     ����ģ��������Ϣ,����Ϣ����ģ��;���ڽڵ�������Ϣ,������Ӧ����������
	//     ���������Ϣ,������Ӧ����������
	void SNS_Node_MsgDeal(Sns_Message *msg);	

	//����:�ڵ��ʼ������,��ȡ�ڵ��Ӧ�����ļ�,���ýڵ��ʼ�����ò���
	//     Ϊ�ڵ������õ�ģ�Ͷ���ʵ����,������ģ�ͳ�ʼ��
	void Node_init();

	//����:�ڵ��ʼ����Ĵ�����,������ʱ��Ҫ���нڵ㶼��ʼ����ɲſ�ִ�еĶ���
	void Node_init_end();

	//����:����ڵ�ģ���ڷ���������һЩ��,��ڵ�ģ�ͷ����������
	void SNS_Simulate_End_Node();

public: //ģ�͵����Զ����ɺ���,�û������¼�����
  
	//����:MSG_InEVENT_Acquisition_Interval�¼�����,������ʱ�����ڲɼ�����ϵͳ��Ϣ
   void Msg_InEvent_Acquisition_Interval(Sns_Message *msg);
   //Sns_Msg_In_Func//

private://ģ�͵����Զ����ɵ�˽�к���

	//����:��¼��ģ�͵����״̬����ֵ��StatsVar_Output��
	void SNS_Record_Stats_Value();

	//����:��ʼ�����ڵ����л���/Э��ģ��
	void Model_OfNode_Init();

	//����:����һ������Ϣ
	//����:DestiNode--��ϢĿ�Ľڵ��ַ,ModelId--������Ϣ��ģ��ID,instanceId--����ģ��ʵ����,EventName--��Ϣ�¼�����,
	//     EventType--�¼�����,PayLoad--��Ϣ�غ�,PacketSize--��Ϣ�غɴ�С,TimeDelay--�����ӳ�
	//     ���Ϳ���Ϣʱ��PayLoad=NULL��PacketSize=0
	void Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay);

	//����:��һ����Ϣת������Ӧ��ģ��
	//����:msg-ת������Ϣ��DestiNode--������ϢĿ�Ľڵ��ַ,ModelId--������Ϣ��ģ��ID,instanceId--����ģ��ʵ����,EventName--������Ϣ�¼�����,
	//     EventType--�����¼�����,TimeDelay--�����ӳ�
	void Send_Aexisting_Msg(Sns_Message *msg,int DestiNode,int ModelId,int instanceId,int EventName,int EventType, clocktype  TimeDelay);


public://�û��Զ��幫�к���


private://�û��Զ���˽�к���


};

#endif
