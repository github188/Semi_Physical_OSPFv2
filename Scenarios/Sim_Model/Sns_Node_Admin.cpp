/*
* Copyright (c) 2014,�������պ����ѧ
* All rights reserved.
*
* ϵͳ����: SPACE NETWORK SIMULATION SYSTEM
* ��    ��: ����
* ��ǰ�汾: SNS 1.0
* 
* �ļ�����: Sns_Node_Admin.cpp
* ��ǰ�汾: V 1.0.0
* �ļ���ʶ: Sns_Node_Admin��Դ�ļ�
* ��������: 
* �� �� ��: 
* ��ϵ��ʽ: 
* �������: 
*
* ժ    Ҫ:
*/
//////////////////////////////////////////////////////////////////////

/////////������Ϊģ�͵����Զ�����/////////////
#include "stdafx.h"//����c++��

#include "Sns_Message.h"//ƽ̨��
#include "Sns_Config_Input.h"//ƽ̨��

#include "Sns_Node_Admin.h"

//Include_ofModel//

/////////������Ϊģ�͵����Զ����� end �û���Ҫ�ӵĶ���������/////////////

/////////////////////////���캯������������/////////////////////////////////////////////

Sns_Node_Admin::Sns_Node_Admin()
{
	///////////���������ʼ��,ģ���Զ�����//////////

	//Stats_Variable_Init//
	
	///////////���������ʼ��,ģ���Զ����� end//////////
}

Sns_Node_Admin::~Sns_Node_Admin()
{
	for(int i = 0; i < Model_num_In_Node; i++)
	{
		free(Model_List[i]);
		Model_List[i] = NULL;
	}
	free(Model_List);
	Model_List = NULL;

	delete(Config_Input);
	Config_Input = NULL;
	free(ConfFile_Path);
	ConfFile_Path = NULL;
}

////////////////////////�ڵ��ʼ������///////////////////////////////////////

//����:�ڵ��ʼ������,��ȡ�ڵ��Ӧ�����ļ�,���ýڵ��ʼ�����ò���
//     Ϊ�ڵ������õ�ģ�Ͷ���ʵ����,������ģ�ͳ�ʼ��
void Sns_Node_Admin::Node_init()
{
	//////////�������ļ��ж�ȡ��ʼ������,ģ�͵����Զ�����////////////////////
	char ModelName[SNS_MAX_STRING_LENGTH];  //�����ļ���ģ��ʶ���־

	char buf[SNS_MAX_STRING_LENGTH];  //��ȡ�����ļ��е��ַ���
	int buf_int = 0;		//��ȡ�����ļ���intֵ,����long,unsigned int
	double buf_double = 0;	//��ȡ�����ļ���intֵ,����float

	int RetArrNum;//��ȡ������������ֵ

	bool retVal = false;//��������ֵ
	
	Config_Input = new Sns_Config_Input();//����һ�������ļ��������

	sprintf(ModelName,"ClassName[%d]",Node_id_InOnetype);

	Config_Input->SNS_Read_ModelConf(ConfFile_Path, ModelName);//��ȡ���ڵ�����ò���

	//Config_Variable_Init//

	//////////�������ļ��ж�ȡ��ʼ������,ģ�͵����Զ����� end////////////////////

	/////////////////////�������ļ��л�ȡ���ڵ������ĸ���ģ�ͼ���Ŀ/////////////////

	//Config_ModelNumInit_Add//

	/////////////////////�������ļ��л�ȡ���ڵ������ĸ���ģ�ͼ���Ŀ end//////////////
	//�ڵ�������ģ��������ʼ��
	Model_num_In_Node = 0;
	//Sum_ModelNum_Add//

	//��ʼ���ڵ��ϵĸ���ģ��
	Model_OfNode_Init();

}

//����:��ʼ�����ڵ����л���/Э��ģ��
void Sns_Node_Admin::Model_OfNode_Init()
{
	////////////*ģ�͵����Զ�����*////////////////////////

	short modelist_id = 0;
	int i;

	/////////////////////��ʼ��ģ������/////////////////////////////////
	Model_List = (Sns_base_model **)checked_pc_malloc(sizeof(Sns_base_model *) * Model_num_In_Node);	// Ϊģ����������ڴ�
	
	/////////////////////��ʼ������ģ��/////////////////////////////////
	//Model_Initialization//
	
	/////////////////////��ʼ������ģ�� end/////////////////////////////////

	
	////////////*ģ�͵����Զ����� end*////////////////////////
}

//����:�ڵ��ʼ����Ĵ�����,������ʱ��Ҫ���нڵ㶼��ʼ����ɲſ�ִ�еĶ���
void Sns_Node_Admin::Node_init_end()
{
	////////////*ģ�͵����Զ�����*////////////////////////
	
	int i;
	short modelist_id = 0;
	
	//Model_Init_end//
	
	////////////*ģ�͵����Զ����� end*////////////////////////


	Acquisition_Interval = 1000000;
	
	Send_Anew_Msg(Node_id,-1,0,MSG_InEVENT_Acquisition_Interval,SNS_MSG_INPUT, NULL , 0 , Acquisition_Interval);

}

///////////////////�ڵ���Ϣ������//////////////////////////////////////////
/*���ݽ��յ���Ϣ,�����ж������ĸ�ģ�ͣ�ģ��ID��1��ʼ����ʾ���ڵ�������ģ�ͣ���Ϊ0����ʾΪ�ڵ㱾��;
����ж��ǳ��¼��������¼����������¼���ֱ�ӵ���ģ�����¼������������ǳ��¼�������*/
//�����ֿ��Ϊģ�͵����Զ�����

//����:�ڵ����Ϣ������,���ո���ģ��/�ڵ���������¼�,
//     ����ģ��������Ϣ,����Ϣ����ģ��;���ڽڵ�������Ϣ,������Ӧ����������
//     ���������Ϣ,������Ӧ����������
void Sns_Node_Admin::SNS_Node_MsgDeal(Sns_Message *msg)
{
	switch(msg->Model_id) 
	{
	case -1:                            //��ʾ�ڵ㱾�����Ϣ
	{
		switch(msg->Event_Name)//��Ϣ�¼�ö�� 
		{
		case MSG_InEVENT_Acquisition_Interval:
		{
			Msg_InEvent_Acquisition_Interval(msg);
		}
		default:
		
			break;
		}

		break;
	}
	//Model_Switch_deal//
	default:

		break;
	}
}

////////////////////////////�������������//////////////////////////////////////////////
//����:����ڵ�ģ���ڷ���������һЩ��,��ڵ�ģ�ͷ����������
void Sns_Node_Admin::SNS_Simulate_End_Node()
{
	////////////*ģ�͵����Զ�����*////////////////////////

	int i;
	short modelist_id = 0;
	
	SNS_Record_Stats_Value();

	//Node_Sim_end//

	////////////*ģ�͵����Զ����� end*////////////////////////
}

//����:��¼��ģ�͵����״̬����ֵ��StatsVar_Output��
void Sns_Node_Admin::SNS_Record_Stats_Value()
{
	char Stats_ModelName[SNS_MAX_STRING_LENGTH]; //���ڼ�¼���״̬��������ģ������־

	sprintf(Stats_ModelName,"\n** Sns_Node_Admin[0]_begin\n");//��ģ�����״̬����ֵ��¼��ʼ
	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);//��Stats_ModelNameд������

	/////////////////////////////����ģ���������״̬����ֵд������//////////////////////////

	//Stats_Variable_Record//
	/////////////////////////////����ģ���������״̬����ֵд������//////////////////////////

	sprintf(Stats_ModelName,"\n** Sns_Node_Admin[0]_end\n");//��ģ�����״̬����ֵ��¼����
	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);//��Stats_ModelNameд������
}

//����:��һ����Ϣת������Ӧ��ģ��
//����:msg-ת������Ϣ��DestiNode--������ϢĿ�Ľڵ��ַ,ModelId--������Ϣ��ģ��ID,instanceId--����ģ��ʵ����,��ֵĬ��Ϊ0,EventName--������Ϣ�¼�����,
//     EventType--�����¼�����,TimeDelay--�����ӳ�
void Sns_Node_Admin::Send_Aexisting_Msg(Sns_Message *msg,int DestiNode,int ModelId,int instanceId,int EventName,int EventType, clocktype  TimeDelay)
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
void Sns_Node_Admin::Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay)
{
	Sns_Scenarios *scenariosdata;

	scenariosdata = (Sns_Scenarios *)Scenarios_Data;

	Sns_Message *msg = new Sns_Message();//����һ����Ϣ����

    msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,PayLoad,PacketSize);//Ϊ��Ϣ��ֵ

	scenariosdata->SNS_Msg_Send(msg,DestiNode,TimeDelay);//������Ϣ
}

////////////////////////////////////�ڵ���Ϣ������////////////////////////////////////

//����:MSG_InEVENT_Acquisition_Interval�¼�����,������ʱ�����ڲɼ�����ϵͳ��Ϣ
void Sns_Node_Admin::Msg_InEvent_Acquisition_Interval(Sns_Message *msg)
{
	delete(msg);
	msg = NULL;

	Send_Anew_Msg(Node_id,-1,0,MSG_InEVENT_Acquisition_Interval,SNS_MSG_INPUT, NULL , 0 , Acquisition_Interval);
		
}

//Sns_Msg_In_Func//

////////////////////////////////////�ڵ���Ϣ������ end////////////////////////////////////