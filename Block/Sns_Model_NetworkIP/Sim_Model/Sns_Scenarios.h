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
* ��������: ΪЭ��/����ģ�Ϳ��������ṩģ��ĳ�������
* �� �� ��: 
* ��ϵ��ʽ: 
* �������: 
*
* ժ    Ҫ:
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNS_SCENARIOS_H__F1880FFC_ADC8_4973_9338_8EB70E71708C__INCLUDED_)
#define AFX_SNS_SCENARIOS_H__F1880FFC_ADC8_4973_9338_8EB70E71708C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


////////////////���඼��ģ�͵����Զ�����////////////////////////////

////////////////���������õ���Э��/����ģ��ö��////////////////////////////
enum 
{
	SNS_MODEL_NETWORKIP
};  

////////////////���������õ���Э��/����ģ��ö��end////////////////////////////

////////////////���������õ��Ľڵ�ģ��ö��////////////////////////////
enum 
{
	SNS_NODE
};  

////////////////���������õ��Ľڵ�ģ��ö��end////////////////////////////

enum										//��Ϣ���ͣ�������롢�����Ϣ
{
	SNS_MSG_INPUT,	//ģ��������Ϣ
	SNS_MSG_OUTPUT	//ģ�������Ϣ
};


#define MAX_MODEL_NUM_INSCENA 100          //�������п�֧�ֵ����Э��/����ģ��������

#include "SNS_core.h" //ƽ̨��

class Sns_Config_Input;
class Sns_Message;

class Sns_Scenarios : public sns_base_scenarios  
{
public:
	int Num_Nodes;					//�����еĽڵ���Ŀ	
	char  *ConfFile_Path;           //�����ļ�·��,��ģ�ͳ�ʼ�������
	char  *StatsFile_Path;           //���״̬�����ļ�·��

	Sns_Config_Input * StatsVar_Output;  	//�洢ģ��״̬��������

	////���ڰ�����
	bool Is_Packet_Track;                 //�Ƿ����ݰ����٣����ǣ�����Track_PacketId
	int Track_PacketId;                   //�����ٵİ�ID��
	bool Is_Create_Onlyone;               //�Ƿ��������Ψһ������һ�θ�����

public:
	Sns_Scenarios();
	virtual ~Sns_Scenarios();

	//����:������ʼ������,��ȡ�ڵ��Ӧ�����ļ�,���ó�����ʼ������
	//     Ϊ���������õ��ڵ����ʵ����,�������ڵ��ʼ��
	void SNS_Init();	

   //����:�������к�����������Ϣ����
	void SNS_Simulate_Run();

	//����:�������н�������������������һЩ��,������������
	void SNS_Simulate_End();

    //����:�����泡������Ϣ���ͺ���
	//����:SendMsg--�跢�͵���Ϣ,DestiNode--Ŀ�Ľڵ�id,TimeDelay--�����ӳ�
	void SNS_Msg_Send(Sns_Message *SendMsg, int DestiNode, clocktype  TimeDelay);  

private://ģ�͵����Զ����ɵ�˽�к���
	
	//����:��¼��ģ�͵����״̬����ֵ��StatsVar_Output��
	void SNS_Record_Stats_Value();

	//����:���������ļ���ʼ�����������нڵ�
	void All_Node_init();

};

#endif