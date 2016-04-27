/*
* Copyright (c) 2014,�������պ����ѧ
* All rights reserved.
*
* ϵͳ����: SPACE NETWORK SIMULATION SYSTEM
* ��    ��: ����
* ��ǰ�汾: SNS 1.0
* 
* �ļ�����: Sns_Node.cpp
* ��ǰ�汾: V 1.0.0
* �ļ���ʶ: Sns_Node��Դ�ļ�
* ��������: ΪЭ��/����ģ�Ϳ��������ṩ�����ڵ��֧��
* �� �� ��: 
* ��ϵ��ʽ: 
* �������: 
*
* ժ    Ҫ:
*/
//////////////////////////////////////////////////////////////////////

/////////������Ϊģ�͵����Զ�����/////////////
#include "stdafx.h"//����c++��
#include "Sns_Config_Input.h"   //ƽ̨��
#include "Sns_Message.h"//ƽ̨��

#include "Sns_Node.h"

#include "Sim_Test.h"
#include "Sns_Model_NetworkIP.h"

/////////������Ϊģ�͵����Զ����� end �û���Ҫ�ӵĶ���������/////////////

/////////////////////////���캯������������/////////////////////////////////////////////

Sns_Node::Sns_Node()
{
	
}

Sns_Node::~Sns_Node()
{

}

////////////////////////�ڵ��ʼ������///////////////////////////////////////

//����:�ڵ��ʼ������,��ȡ�ڵ��Ӧ�����ļ�,���ýڵ��ʼ�����ò���
//     Ϊ�ڵ������õ�ģ�Ͷ���ʵ����,������ģ�ͳ�ʼ��
void Sns_Node::Node_init()
{
	//////////////////////ģ�͵����Զ�����////////////////////////////
	Modelnum_In_Node = 1;

	Model_OfNode_Init();

	//////////////////////ģ�͵����Զ����� end////////////////////////////
}

//����:��ʼ�����ڵ����л���/Э��ģ��
void Sns_Node::Model_OfNode_Init()
{
	/*ģ�͵����Զ�����*/

	short modelist_id = 0;

	int i;

	/////////////////////��ʼ��ģ������/////////////////////////////////
	Model_List = (Sns_base_model **)checked_pc_malloc(sizeof(Sns_base_model *) * Modelnum_In_Node);	// Ϊģ����������ڴ�

	/////////////////////��ʼ������ģ��/////////////////////////////////
	
	Sns_Model_NetworkIP *Sns_Model_NetworkIPObj = new Sns_Model_NetworkIP();	

	for(i = 0; i < Modelnum_In_Node; i++)
	{
        Model_List[modelist_id] = (Sns_base_model *)Sns_Model_NetworkIPObj;
		
		Sns_Model_NetworkIPObj->Model_id = SNS_MODEL_NETWORKIP;                          //��ʼ��Э��ID�ţ����ڱ�ʶЭ��
		Sns_Model_NetworkIPObj->Scenarios_Data = (Sns_Scenarios *)Scenarios_Data;	//ʵ����������
		Sns_Model_NetworkIPObj->Model_Instance_id = i;								//�ڵ��и���·��Э���ʵ����־,��Ϊ�ڼ�������˿�
		Sns_Model_NetworkIPObj->Cur_Node_id = Node_id;								//Э�������ڵ�ID
		Sns_Model_NetworkIPObj->Cur_Node_id_inOneType = Node_id_InOnetype;			//Э�������ڵ�����ID
		Sns_Model_NetworkIPObj->Cur_Node_Name = "Sns_Node";						//Э�������ڵ�����
		Sns_Model_NetworkIPObj->ConfFile_Path = ConfFile_Path;					//Э�������ļ�·��
		
		if(i==0)
			Modelid_In_list[SNS_MODEL_NETWORKIP] = modelist_id;						//SNS_MAC_LINK�ڱ��ڵ�model list�е�λ��

		Sns_Model_NetworkIPObj->Model_init();										//����Э���ʼ������

		modelist_id ++;
	}
	
	/////////////////////��ʼ������ģ�� end/////////////////////////////////

	/*�Զ�����end*/
}

//����:�ڵ��ʼ����Ĵ�����,������ʱ��Ҫ���нڵ㶼��ʼ����ɲſ�ִ�еĶ���
void Sns_Node::Node_init_end()
{
	/////////////////////����init_end����/////////////////////////////////

	int i;
	short modelist_id = 0;

	Sns_Model_NetworkIP *Sns_Model_NetworkIPObj;

	for(i = 0; i < Modelnum_In_Node; i++)
	{
		Sns_Model_NetworkIPObj = (Sns_Model_NetworkIP *)Model_List[modelist_id];

		Sns_Model_NetworkIPObj->Model_init_end();						//����Э���ʼ��������Ĵ�����

		modelist_id ++;
	}

	/////////////////////����init_end���� end/////////////////////////////////

	/////////////////////���ڲ�����/////////////////////////////////

	short listnum = 0;
	listnum = Modelid_In_list[SNS_MODEL_NETWORKIP];

	Sim_Test_Result = new Sim_Test();
	Sim_Test_Result->Scenarios_Data = (Sns_Scenarios *)Scenarios_Data;//ʵ����������
	Sim_Test_Result->Cur_Node = this;              //ʵ�����ڵ���

	Sim_Test_Result->Sns_model_testObj = (Sns_Model_NetworkIP *)Model_List[listnum];  ////ʵ����ģ����

	Sim_Test_Result->Test_Run();							//����ϵͳ��ʼ���д����¼�
	/////////////////////���ڲ�����end/////////////////////////////////
}
///////////////////�ڵ���Ϣ������//////////////////////////////////////////
/*���ݽ��յ���Ϣ,�����ж������ĸ�ģ�ͣ�ģ��ID��1��ʼ����ʾ���ڵ�������ģ�ͣ���Ϊ0����ʾΪ�ڵ㱾��;
����ж��ǳ��¼��������¼����������¼���ֱ�ӵ���ģ�����¼������������ǳ��¼�������*/
//�����ֿ��Ϊģ�͵����Զ�����

//����:�ڵ����Ϣ������,���ո���ģ��/�ڵ���������¼�,
//     ����ģ��������Ϣ,����Ϣ����ģ��;���ڽڵ�������Ϣ,������Ӧ����������
//     ���������Ϣ,������Ӧ����������
void Sns_Node::SNS_Node_MsgDeal(Sns_Message *msg)
{
	Sns_Model_NetworkIP *Sns_Model_NetworkIPObj = NULL;
	short modelist_id;

	modelist_id = Modelid_In_list[SNS_MODEL_NETWORKIP] + msg->Model_Instance_id; 

	Sns_Model_NetworkIPObj = (Sns_Model_NetworkIP *)Model_List[modelist_id];

	switch(msg->Model_id) 
	{
	case -1://��ʾ�ڵ㱾�����Ϣ
		{
			switch(msg->Event_Name) 
			{

			default:

				break;
			}

			break;
		}

	case SNS_MODEL_NETWORKIP://ģ����Ϣ����
	{
		Sns_Model_NetworkIP *Sns_Model_NetworkIPObj = NULL;
		modelist_id = Modelid_In_list[SNS_MODEL_NETWORKIP] + msg->Model_Instance_id; 
		Sns_Model_NetworkIPObj = (Sns_Model_NetworkIP *)Model_List[modelist_id];

		if (msg->Event_Type==SNS_MSG_INPUT)//�����¼�
		{
			Sns_Model_NetworkIPObj->SNS_Model_MsgDeal(msg);
		}
		else//����¼�
		{
			switch(msg->Event_Name)
			{
			case Sns_Model_NetworkIP::MSG_OutEVENT_NETWORK_ToMAC:
			{
				Sim_Test_Result->Process_MSG_OutEVENT_NETWORK_ToMAC(msg);
				break;
			}
			case Sns_Model_NetworkIP::MSG_OutEVENT_NETWORK_ToTransport:
			{
				Sim_Test_Result->Process_MSG_OutEVENT_NETWORK_ToTransport(msg);
				break;
			}
			case Sns_Model_NetworkIP::MSG_OutEVENT_NETWORK_ToProtocol_OSPFv2:
			{
				Sim_Test_Result->Process_MSG_OutEVENT_NETWORK_ToProtocol_OSPFv2(msg);
				break;
			}
			//SNS_MSG_EVENT_OUT//
			default:
				break;
			}
		}
		break;
	}

	default:

		break;
	}
}

////////////////////////////�������������//////////////////////////////////////////////
//����:����ڵ�ģ���ڷ���������һЩ��,��ڵ�ģ�ͷ����������
void Sns_Node::SNS_Simulate_End_Node()
{
	int i;
	short modelist_id = 0;

	SNS_Record_Stats_Value();

	Sns_Model_NetworkIP *Sns_Model_NetworkIPObj;

	for(i = 0; i < Modelnum_In_Node; i++)
	{
		Sns_Model_NetworkIPObj = (Sns_Model_NetworkIP *)Model_List[modelist_id];
		Sns_Model_NetworkIPObj->StatsVar_Output = StatsVar_Output;
		Sns_Model_NetworkIPObj->SNS_Simulate_End_Model();						

		modelist_id ++;
	}	
}

//����:��¼��ģ�͵����״̬����ֵ��StatsVar_Output��
void Sns_Node::SNS_Record_Stats_Value()
{
	char Stats_ModelName[SNS_MAX_STRING_LENGTH]; //���ڼ�¼���״̬��������ģ������־

	sprintf(Stats_ModelName,"\n** Sns_Node_begin\n");

	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);

	sprintf(Stats_ModelName,"\n** Sns_Node_end\n");

	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);
}

//����:��һ����Ϣת������Ӧ��ģ��
//����:msg-ת������Ϣ��DestiNode--������ϢĿ�Ľڵ��ַ,ModelId--������Ϣ��ģ��ID,instanceId--����ģ��ʵ����,��ֵĬ��Ϊ0,EventName--������Ϣ�¼�����,
//     EventType--�����¼�����,TimeDelay--�����ӳ�
void Sns_Node::Send_Aexisting_Msg(Sns_Message *msg,int DestiNode,int ModelId,int instanceId,int EventName,int EventType, clocktype  TimeDelay)
{
	Sns_Scenarios *scenariosdata;

	scenariosdata = (Sns_Scenarios *)Scenarios_Data;

	msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,NULL,-1);//��Ϣ��ֵ

	scenariosdata->SNS_Msg_Send(msg,DestiNode,TimeDelay);//��Ϣ����
}

//����:����һ������Ϣ
//����:DestiNode--��ϢĿ�Ľڵ��ַ,ModelId--������Ϣ��ģ��ID,instanceId--����ģ��ʵ����,��ֵĬ��Ϊ0,EventName--��Ϣ�¼�����,
//     EventType--�¼�����,PayLoad--��Ϣ�غ�,PacketSize--��Ϣ�غɴ�С,TimeDelay--�����ӳ�
//     ���Ϳ���Ϣʱ��PayLoad=NULL��PacketSize=0
void Sns_Node::Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay)
{
	Sns_Scenarios *scenariosdata;

	scenariosdata = (Sns_Scenarios *)Scenarios_Data;

	Sns_Message *msg = new Sns_Message();

    msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,PayLoad,PacketSize);

	scenariosdata->SNS_Msg_Send(msg,DestiNode,TimeDelay);
}
