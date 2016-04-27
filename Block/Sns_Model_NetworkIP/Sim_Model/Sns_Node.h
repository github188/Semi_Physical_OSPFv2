/*
* Copyright (c) 2014,�������պ����ѧ
* All rights reserved.
*
* ϵͳ����: SPACE NETWORK SIMULATION SYSTEM
* ��    ��: ����
* ��ǰ�汾: SNS 1.0
* 
* �ļ�����: Sns_Node.h
* ��ǰ�汾: V 1.0.0
* �ļ���ʶ: Sns_Node��ͷ�ļ�
* ��������: ΪЭ��/����ģ�Ϳ��������ṩ�����ڵ��֧��
* �� �� ��: 
* ��ϵ��ʽ: 
* �������: 
*
* ժ    Ҫ:
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNS_NODE_H__D5C1405E_7C0F_4D30_850A_F329619CA6A1__INCLUDED_)
#define AFX_SNS_NODE_H__D5C1405E_7C0F_4D30_850A_F329619CA6A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

/////////������Ϊģ�͵����Զ�����/////////////
#include "Sns_Scenarios.h"

class Sns_Config_Input;
class Sns_Message;
class Sim_Test;

/////////������Ϊģ�͵����Զ����� end �û���Ҫ�ӵĶ���������/////////////



class Sns_Node : public sns_base_node  
{
public:	//ģ�͵����Զ����ɱ���
	int Modelnum_In_Node;                   //���ڵ��е�ģ�͸���
	Sns_base_model ** Model_List;           //�ڵ���ģ�Ͷ���
	char  *ConfFile_Path;                   //�����ļ�·��,��ģ�ͳ�ʼ�������

	Sns_Config_Input * StatsVar_Output;  	//�洢ģ��״̬��������

	short Modelid_In_list[MAX_MODEL_NUM_INSCENA];   //ĳģ���ڱ��ڵ�ģ�Ͷ����еĳ�ʼλ��
	
	//������Ϣ�¼�����
	enum 
	{

	};

	//�����Ϣ�¼�����
	enum 
	{

	};
	
private://ģ�͵����Զ����ɱ���
   Sim_Test *Sim_Test_Result;					//����Դ����

private://�û��Զ������
	

public://�û��Զ������

public://ģ�͵����Զ����ɺ���
	Sns_Node();
	virtual ~Sns_Node();

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

public://�û��Զ��庯��


private://�û��Զ��庯��


};

#endif
