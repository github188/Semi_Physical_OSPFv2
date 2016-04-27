/*
* Copyright (c) 2014,�������պ����ѧ
* All rights reserved.
*
* ϵͳ����: SPACE NETWORK SIMULATION SYSTEM
* ��    ��: ����
* ��ǰ�汾: SNS 1.0
* 
* �ļ�����: Sim_Test.h
* ��ǰ�汾: V 1.0.0
* �ļ���ʶ: Sim_Test��ͷ�ļ�
* ��������: ����Э��/����ģ�Ϳ�������
* �� �� ��: 
* ��ϵ��ʽ: 
* �������: 
*
* ժ    Ҫ:
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIM_TEST_H__02205B67_2972_44B1_BED5_3778CD9A1515__INCLUDED_)
#define AFX_SIM_TEST_H__02205B67_2972_44B1_BED5_3778CD9A1515__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#include "SNS_core.h" //ƽ̨��

class Sns_Scenarios;
class Sns_Node;
class Sns_Message;
class Sns_Model_NetworkIP;


class Sim_Test
{
public://ģ�͵����Զ����ɱ���
	Sns_Scenarios * Scenarios_Data;	//��ǰ����ģ�Ͷ�Ӧ�ĳ���
	Sns_Node *Cur_Node;				//��ǰ����ģ�Ͷ�Ӧ�Ľڵ�

	//����ģ������
	Sns_Model_NetworkIP *Sns_model_testObj; //��ǰ���Ե�ģ��

private://�û��Զ�����������������ı��������ڱ�����	


public://�û��Զ������


public://ģ�͵����Զ����ɺ���

    //���캯������������
	Sim_Test();
	virtual ~Sim_Test();

	//����:��������
	void Test_Run();	

private://ģ�͵����Զ����ɺ���
	//����:����һ������Ϣ
	//����:DestiNode--��ϢĿ�Ľڵ��ַ,ProtocolId--������Ϣ��ģ��ID,EventName--��Ϣ�¼�����,
	//     EventType--�¼�����,PayLoad--��Ϣ�غ�,PacketSize--��Ϣ�غɴ�С,TimeDelay--�����ӳ�
	void Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay);


public://ģ�͵����Զ����ɺ���

/////////////////////////////////����ģ�ͳ���Ϣ������/////////////////////////////////////////
	//���ܣ�MSG_OutEVENT_NETWORK_ToMAC�¼����� 
	void  Process_MSG_OutEVENT_NETWORK_ToMAC(Sns_Message *msg); 

	//���ܣ�MSG_OutEVENT_NETWORK_ToTransport�¼����� 
	void  Process_MSG_OutEVENT_NETWORK_ToTransport(Sns_Message *msg); 

	//���ܣ�MSG_OutEVENT_NETWORK_ToProtocol_OSPFv2�¼����� 
	void  Process_MSG_OutEVENT_NETWORK_ToProtocol_OSPFv2(Sns_Message *msg); 

	//Sns_Msg_In_Func//


private://�û��Զ��庯��

	
};

#endif
