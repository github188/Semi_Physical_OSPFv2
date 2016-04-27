/*
* Copyright (c) 2014,�������պ����ѧ
* All rights reserved.
*
* ϵͳ����: SPACE NETWORK SIMULATION SYSTEM
* ��    ��: ����
* ��ǰ�汾: SNS 1.0
* 
* �ļ�����: Sns_Scenarios.cpp
* ��ǰ�汾: V 1.0.0
* �ļ���ʶ: Sns_Scenarios��Դ�ļ�
* ��������: ΪЭ��/����ģ�Ϳ��������ṩģ��ĳ�������
* �� �� ��: 
* ��ϵ��ʽ: 
* �������: 
*
* ժ    Ҫ:
*/
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"//����c++��
#include "Sns_Config_Input.h"   //ƽ̨��
#include "Sns_Message.h"//ƽ̨��

#include "Sns_Scenarios.h"
#include "Sns_Node_Virtual.h"
#include "Sim_Test.h"

Sns_Scenarios::Sns_Scenarios()
{
	Num_Nodes = 0;   

	Is_Packet_Track = false;                 //�Ƿ����ݰ����٣����ǣ�����Track_PacketId
	Track_PacketId = -1;                   //�����ٵİ�ID��
	Is_Create_Onlyone = true;             //�Ƿ��������Ψһ������һ�θ�����  
}

Sns_Scenarios::~Sns_Scenarios()
{

}

///////////////////////////���̳�����ʼ������///////////////////////////////////////////////
//����:������ʼ������,��ȡ�ڵ��Ӧ�����ļ�,���ó�����ʼ������
//     Ϊ���������õ��ڵ����ʵ����,�������ڵ��ʼ��
void Sns_Scenarios::SNS_Init()
{	
	//////////////////////ģ�͵����Զ�����////////////////////////////

	Num_Nodes = 6;						//�����нڵ����

	//���÷���ʱ��clocktype��λ��Ĭ��ΪMicS����΢��
	Unit_Of_Aclocktype = "MicS";
	SNS_Set_Time_Unit(Unit_Of_Aclocktype);

    Max_Sim_Clock = 1000000000000;		// �������ʱ������

	ConfFile_Path = ".//Sns_config.ini";//���������ļ�·��

	StatsFile_Path = ".//Sns_output_statsVar.txt";//���÷������״̬�����ļ�·��

	All_Node_init();

	//////////////////////ģ�͵����Զ����� end////////////////////////////
}

//����:���������ļ���ʼ�����������нڵ�
void Sns_Scenarios::All_Node_init()
{
	int i = 0;                         //����ѭ���þֲ�����
	int nodelist_id = 0;

	int seedVal;						//�����ļ��в����������Seedֵ 
	seedVal = 5;
	srand(seedVal);	

	//�����нڵ��ڴ����,��ʼ���ڵ�����
	nodeData = (sns_base_node **)checked_pc_malloc(sizeof(sns_base_node *) * Num_Nodes);	// Ϊ�ڵ�����ڴ�

	/////////////*������ЩNodes,����Nodes��Ϣ*///////////////////////////////////

	sns_base_node *nextNode = NULL;

	for (i=0;i<Num_Nodes;i++)
	{
		nodeData[nodelist_id] = new Sns_Node_Virtual();
		nodeData[nodelist_id]->Node_Type = SNS_NODE_VIRTUAL;					//�ڵ�����ö��
		nextNode = Base_Node_Init(nodelist_id,i,seedVal,this,nextNode);	//�ڵ�����ʼ��
	}

    //////////////////*��ʼ������Nodes*//////////////////////
   // ���Ƕ��ڲ�ͬ���ͽڵ���Ҫ�ֱ���
	//������ʼ���ͳ�ʼ����ڵ����к���
	nextNode = firstNode;
	Sns_Node_Virtual * Sns_Node_VirtualObj =NULL;

	while (nextNode != NULL) 
	{
		switch(nextNode->Node_Type)
		{
		case SNS_NODE_VIRTUAL:
		{
			Sns_Node_VirtualObj = (Sns_Node_Virtual *) nextNode;
			Sns_Node_VirtualObj->ConfFile_Path = ConfFile_Path;
			Sns_Node_VirtualObj->Node_init();

			break;
		}
		default:
			break;
		}		
		nextNode = nextNode->nextNodeData;
	}

	//��ʼ�������к���
	nextNode = firstNode;

	while (nextNode != NULL) 
	{
		switch(nextNode->Node_Type)
		{
		case SNS_NODE_VIRTUAL:
		{
			Sns_Node_VirtualObj = (Sns_Node_Virtual *)nextNode;
			Sns_Node_VirtualObj->Node_init_end();

			break;
		}
		
		default:
			break;
		}		
		nextNode = nextNode->nextNodeData;
	}

	/////////////////////���ڲ�����/////////////////////////////////

	Sim_Test_result = new Sim_Test();
	Sim_Test_result->Scenarios_Data = this;//ʵ����������


	/////////////////////���ڲ�����end/////////////////////////////////
}

////////////////////////////����ϵͳ��Ϣ������//////////////////////////////////////////////
//����:�������к�����������Ϣ����
void Sns_Scenarios::SNS_Simulate_Run()
{
	while (true) 
	{
		if(!SNS_SimTime_Control())
			return;

		Sim_Test_result->Test_Run();							//����ϵͳ��ʼ���в��԰����������ڱ��β������

	/////*��������,��鵱ǰʱ���Ƿ�ԤԼ���κ���Ϣ*//////
		// ���Ƕ��ڲ�ͬ���ͽڵ���Ҫ�ֱ���
		sns_base_node *node = NULL;
		Sns_Message *msg = NULL;		
		
		if (Get_HeapSize() != 0) 
		{
			while ((node = Get_Current_Node()) !=NULL) 
			{
				msg = (Sns_Message * )Get_Current_Msg(node);
				switch(node->Node_Type)
				{
				case SNS_NODE_VIRTUAL://������Ϣ�Ľڵ�
					{
						if((msg->Model_id != -1)||(msg->Event_Type != SNS_MSG_OUTPUT))//�ڵ������¼�����
						{
							Sns_Node_Virtual *Sns_Node_VirtualObj = (Sns_Node_Virtual *) node;
							Sns_Node_VirtualObj->SNS_Node_MsgDeal(msg);  //ʱ϶���г��� 

						}
						else//�ڵ�����¼�����
						{
							switch(msg->Event_Name)
							{
							//SNS_MSG_EVENT_OUT//
							default:
								break;
							}						
						}
						break;
					}
				default:
					break ;
				}
			}
		}
	}
}

////////////////////////////�������������//////////////////////////////////////////////
//����:�������н������������������һЩ��,������������
void Sns_Scenarios::SNS_Simulate_End()
{
	sns_base_node *nextNode = NULL;

	nextNode = firstNode;
	Sns_Node_Virtual * Sns_Node_VirtualObj =NULL;

	SNS_Record_Stats_Value();

	while (nextNode != NULL) 
	{
		switch(nextNode->Node_Type)
		{
		case SNS_NODE_VIRTUAL:
		{
			Sns_Node_VirtualObj = (Sns_Node_Virtual *) nextNode;
			Sns_Node_VirtualObj->StatsVar_Output = StatsVar_Output;
			Sns_Node_VirtualObj->SNS_Simulate_End_Node();

			break;
		}
		default:
			break;
		}		
		nextNode = nextNode->nextNodeData;
	}

	StatsVar_Output->SNS_Print_InputStr(StatsFile_Path);
	delete StatsVar_Output;
}

//����:��¼��ģ�͵����״̬����ֵ��StatsVar_Output��
void Sns_Scenarios::SNS_Record_Stats_Value()
{
	char Stats_ModelName[SNS_MAX_STRING_LENGTH]; //���ڼ�¼���״̬��������ģ������־
	StatsVar_Output = new Sns_Config_Input();

	sprintf(Stats_ModelName,"\n** Sns_Scenarios_begin\n");

	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);

	sprintf(Stats_ModelName,"\n** Sns_Scenarios_end\n");

	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);
}

////////////////////////////////���ú���//////////////////////////////////////////////

//����:�����泡������Ϣ���ͺ���
//����:SendMsg--�跢�͵���Ϣ,DestiNode--Ŀ�Ľڵ�id,TimeDelay--�����ӳ�
void Sns_Scenarios::SNS_Msg_Send(Sns_Message *SendMsg, int DestiNode, clocktype  TimeDelay)  //��Ϣ���ͺ���
{
	if(Is_Packet_Track)                    //������
	{
		if(SendMsg->Track_PacketId == Track_PacketId)
		{
			int packet_dealtime = int(SimClock()-SendMsg->Message_CreationTime);
			printf("PacketId=%d; node_id=%d; mode_id=%d; event_type=%d; event_id=%d; packet_size=%d;deal_time=%d\n",
				Track_PacketId,DestiNode,SendMsg->Model_id,SendMsg->Event_Type,SendMsg->Event_Name,SendMsg->PayLoad_Size,packet_dealtime);
		}
	}

	assert(nodeData[DestiNode] != NULL);

	if(TimeDelay == 0)//���ӳٵ���Ϣ
	{	
		switch(nodeData[DestiNode]->Node_Type)
		{
		case SNS_NODE_VIRTUAL://������Ϣ�Ľڵ�
			{
				Sns_Node_Virtual * Sns_Node_VirtualObj = (Sns_Node_Virtual *)nodeData[DestiNode];
				Sns_Node_VirtualObj->SNS_Node_MsgDeal(SendMsg); 

				break;
			}
		default:

			break;
		}
	}
	else//���ӳٷ��͵���Ϣ
	{
		SNS_Msg_Insert(nodeData[DestiNode], SendMsg, TimeDelay);
	}
}

//����:����һ������Ϣ
//����:DestiNode--��ϢĿ�Ľڵ��ַ,ModelId--������Ϣ��ģ��ID,instanceId--����ģ��ʵ����,EventName--��Ϣ�¼�����,
//     EventType--�¼�����,PayLoad--��Ϣ�غ�,PacketSize--��Ϣ�غɴ�С,TimeDelay--�����ӳ�
//     ���Ϳ���Ϣʱ��PayLoad=NULL��PacketSize=0
void Sns_Scenarios::Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay)
{
	Sns_Message *msg = new Sns_Message();

	msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,PayLoad,PacketSize);

	SNS_Msg_Send(msg,DestiNode,TimeDelay);
}

//����:��һ����Ϣת������Ӧ��ģ��
//����:msg-ת������Ϣ��DestiNode--������ϢĿ�Ľڵ��ַ,ModelId--������Ϣ��ģ��ID,instanceId--����ģ��ʵ����,��ֵĬ��Ϊ0,EventName--������Ϣ�¼�����,
//     EventType--�����¼�����,TimeDelay--�����ӳ�
void Sns_Scenarios::Send_Aexisting_Msg(Sns_Message *msg,int DestiNode,int ModelId,int instanceId,int EventName,int EventType, clocktype  TimeDelay)
{
	msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,NULL,-1);//��Ϣ��ֵ

	SNS_Msg_Send(msg,DestiNode,TimeDelay);//��Ϣ����
}
