/*
* Copyright (c) 2014,�������պ����ѧ
* All rights reserved.
*
* ϵͳ����: SPACE NETWORK SIMULATION SYSTEM
* ��    ��: ����
* ��ǰ�汾: SNS 1.0
* 
* �ļ�����: Sim_Test.cpp
* ��ǰ�汾: V 1.0.0
* �ļ���ʶ: Sim_Test��Դ�ļ�
* ��������: ����Э��/����ģ�Ϳ�������
* �� �� ��: 
* ��ϵ��ʽ: 
* �������: 
*
* ժ    Ҫ:
*/
//////////////////////////////////////////////////////////////////////

#include "stdafx.h" //����c++��
#include <time.h>
#include "Sns_Message.h" //ƽ̨��
#include "Sim_Test.h"
#include "Sns_Scenarios.h"
#include "Sns_Node_Real.h"


Sim_Test::Sim_Test()
{
	

}

Sim_Test::~Sim_Test()
{

}

//����:����һ������Ϣ
//����:DestiNode--��ϢĿ�Ľڵ��ַ,ModelId--������Ϣ��ģ��ID,instanceId--����ģ��ʵ����,EventName--��Ϣ�¼�����,
//     EventType--�¼�����,PayLoad--��Ϣ�غ�,PacketSize--��Ϣ�غɴ�С,TimeDelay--�����ӳ�
//     ���Ϳ���Ϣʱ��PayLoad=NULL��PacketSize=0
void Sim_Test::Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay)
{
	Sns_Message *msg = new Sns_Message();
	
    msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,PayLoad,PacketSize);

	Scenarios_Data->SNS_Msg_Send(msg,DestiNode,TimeDelay);
}

//����:��������
void Sim_Test::Test_Run()
{
	

}

///////////////////////////////����¼���Ӧ������///////////////////////////////////////////
//���ܣ�MSG_OutEVENT_SendToOtherNodes�¼����� 
void Sim_Test:: Process_MSG_OutEVENT_SendToOtherNodes(Sns_Message *msg) 
{
}
//���ܣ�MSG_OutEVENT_SendToRealNode�¼����� 
void Sim_Test:: Process_MSG_OutEVENT_SendToRealNode(Sns_Message *msg) 
{
}
//Sns_Msg_In_Func//
