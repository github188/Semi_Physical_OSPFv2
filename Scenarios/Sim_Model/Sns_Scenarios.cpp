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
* ��������: 
* �� �� ��: 
* ��ϵ��ʽ: 
* �������: 
*
* ժ    Ҫ:
*/
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"//����c++��

#include "Sns_Message.h"//ƽ̨��
#include "Sns_Config_Input.h"//ƽ̨��
#include "Sns_Scenarios.h"
//�������ڵ�ģ��ͷ�ļ�
#include "Sns_Node_Admin.h"
#include "Sns_Node_Real.h"
#include "Sns_Node_Virtual.h"
//Include_ofModel//

Sns_Scenarios::Sns_Scenarios()
{
	Num_Nodes = 0;   

	Is_Packet_Track = false;                 //�Ƿ����ݰ����٣����ǣ�����Track_PacketId
	Track_PacketId = -1;                   //�����ٵİ�ID��
	Is_Create_Onlyone = true;             //�Ƿ��������Ψһ������һ�θ�����

	///////////���������ʼ��,ģ���Զ�����//////////
	
	//Stats_Variable_Init//

	///////////���������ʼ��,ģ���Զ����� end//////////

}

Sns_Scenarios::~Sns_Scenarios()
{
	delete(Config_Input);
	Config_Input = NULL;
	free(ConfFile_Path);
	ConfFile_Path = NULL;
	delete(StatsVar_Output);
	StatsVar_Output = NULL;
	free(StatsFile_Path);
	StatsFile_Path = NULL;
}

///////////////////////////���̳�����ʼ������///////////////////////////////////////////////
//����:������ʼ������,��ȡ�ڵ��Ӧ�����ļ�,���ó�����ʼ������
//     Ϊ���������õ��ڵ����ʵ����,�������ڵ��ʼ��
void Sns_Scenarios::SNS_Init()
{	
	//////////////////////ģ�͵����Զ�����////////////////////////////
	//////////////�������ļ��ж�ȡ��ʼ������//////////////////////////
	Is_Synchronization=true;

	char ModelName[SNS_MAX_STRING_LENGTH];  //�����ļ���ģ��ʶ���־

	char buf[SNS_MAX_STRING_LENGTH];  //��ȡ�����ļ��е��ַ���
	int buf_int = 0;		//��ȡ�����ļ���intֵ,����long,unsigned int
	double buf_double = 0;	//��ȡ�����ļ���intֵ,����float

	int RetArrNum;//��ȡ������������ֵ

	bool retVal = false;//��������ֵ
	
	Config_Input = new Sns_Config_Input();//����һ�������ļ��������

	ConfFile_Path = ".//Sns_config.ini";//���������ļ�·��

	StatsFile_Path = ".//Sns_output_statsVar.txt";//���÷������״̬�����ļ�·��

	sprintf(ModelName,"Sns_Scenarios");

	Config_Input->SNS_Read_ModelConf(ConfFile_Path, ModelName);//��ȡ�������ò���

	retVal = Config_Input->SNS_ReadString("char*,unit_Of_Aclocktype", &RetArrNum ,buf);//��ȡ������С����ʱ�䵥λ 
	if(retVal == false)
	{
		Unit_Of_Aclocktype = "MicS";			//Ĭ����Сʱ�䵥λΪ΢��
		SNS_Set_Time_Unit(Unit_Of_Aclocktype);	//���ó�����С����ʱ�䵥λ
	}
	else
	{
		Config_Var.unit_Of_Aclocktype = buf;
		Unit_Of_Aclocktype = buf;
		SNS_Set_Time_Unit(Unit_Of_Aclocktype);//���ó�����С����ʱ�䵥λ
	}
	
	retVal = Config_Input->SNS_ReadTime("clocktype,Max_Sim_Clock", &RetArrNum, &Config_Var.max_sim_clock);//��ȡ��������ʱ��
	if (retVal == false) 
	{
        Max_Sim_Clock = 1000000000000;	//Ĭ�Ϸ���ʱ��  
    }
	else
	{
		Max_Sim_Clock = Config_Var.max_sim_clock;
	}

	retVal = Config_Input->SNS_ReadInt( "int,seedVal", &RetArrNum, &Config_Var.seed_val); //��ȡ�������
	if (retVal == false) 
	{
        Config_Var.seed_val = 5;	//Ĭ���������
    }
	//Config_Variable_Init//
	/////////////////////�������ļ��ж�ȡ��ʼ������ end///////////////////////

	/////////////////////�������ļ��л�ȡ����������ڵ㼰��Ŀ/////////////////
	retVal = Config_Input->SNS_ReadInt( "int,Num_Sns_Node_Real", &RetArrNum, &Num_ofThis.Num_Sns_Node_Real);
	if (retVal == false)
	{
		Num_ofThis.Num_Sns_Node_Real = 1;
	}

	retVal = Config_Input->SNS_ReadInt( "int,Num_Sns_Node_Virtual", &RetArrNum, &Num_ofThis.Num_Sns_Node_Virtual);
	if (retVal == false)
	{
		Num_ofThis.Num_Sns_Node_Virtual = 1;
	}

	//Config_ModelNumInit_Add//
	/////////////////////�������ļ��л�ȡ����������ڵ㼰��Ŀ end//////////////
	
	//�����ڵ�������ʼ��
	Num_Nodes = Num_ofThis.Num_Sns_Node_Real + Num_ofThis.Num_Sns_Node_Virtual + 1;
	//Sum_ModelNum_Add//
	
	srand(Config_Var.seed_val);	

	//��ʼ�������ڸ��ڵ�
	All_Node_init();

	//////////////////////ģ�͵����Զ����� end////////////////////////////

}

//����:���������ļ���ʼ�����������нڵ�
void Sns_Scenarios::All_Node_init()
{
	int i = 0;                         //����ѭ���þֲ�����
	int nodelist_id = 0;

	//�����нڵ��ڴ����,��ʼ���ڵ�����
	nodeData = (sns_base_node **)checked_pc_malloc(sizeof(sns_base_node *) * Num_Nodes);// Ϊ�ڵ�����ڴ�

	/////////////*������ЩNodes,����Nodes��Ϣ*///////////////////////////////////

	sns_base_node *nextNode = NULL;

	////////��ʼ������ڵ�
	nodeData[nodelist_id] = new Sns_Node_Admin();			
	nodeData[nodelist_id]->Node_Type = SNS_NODE_ADMIN;  //���ýڵ�����
	nextNode = Base_Node_Init(nodelist_id,i,Config_Var.seed_val,this,nextNode);

    ////////��ʼ������ڵ����
	for (i = 0;i < Num_ofThis.Num_Sns_Node_Real;i++)
	{
		nodeData[nodelist_id] = new Sns_Node_Real();
		nodeData[nodelist_id]->Node_Type = SNS_NODE_REAL;
		nextNode = Base_Node_Init(nodelist_id,i,Config_Var.seed_val,this,nextNode);
	}
	for (i = 0;i < Num_ofThis.Num_Sns_Node_Virtual;i++)
	{
		nodeData[nodelist_id] = new Sns_Node_Virtual();
		nodeData[nodelist_id]->Node_Type = SNS_NODE_VIRTUAL;
		nextNode = Base_Node_Init(nodelist_id,i,Config_Var.seed_val,this,nextNode);
	}
	//Sns_NodeList_Init//
	
    //////////////////*��ʼ������Nodes*//////////////////////
   // ���Ƕ��ڲ�ͬ���ͽڵ���Ҫ�ֱ���
	//������ʼ���ͳ�ʼ����ڵ����к���
	nextNode = firstNode;
	Sns_Node_Admin * Sns_Node_AdminObj =NULL;

	Sns_Node_Real * Sns_Node_RealObj =NULL;
	Sns_Node_Virtual * Sns_Node_VirtualObj =NULL;
	//Sns_Node_Definition//

	while (nextNode != NULL) 
	{
		switch(nextNode->Node_Type)
		{
		case SNS_NODE_ADMIN:
		{
			Sns_Node_AdminObj = (Sns_Node_Admin *) nextNode;
			Sns_Node_AdminObj->ConfFile_Path = ConfFile_Path;//���������ļ�·��
			Sns_Node_AdminObj->Node_init();

			break;
		}
		case SNS_NODE_REAL:
		{
			Sns_Node_RealObj = (Sns_Node_Real *) nextNode;
			Sns_Node_RealObj->ConfFile_Path = ConfFile_Path;
			Sns_Node_RealObj->Node_init();

			break;
		}
		case SNS_NODE_VIRTUAL:
		{
			Sns_Node_VirtualObj = (Sns_Node_Virtual *) nextNode;
			Sns_Node_VirtualObj->ConfFile_Path = ConfFile_Path;
			Sns_Node_VirtualObj->Node_init();

			break;
		}
		//Sns_Node_Case_Init_Begin//
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
		case SNS_NODE_ADMIN:
		{
			Sns_Node_AdminObj = (Sns_Node_Admin *) nextNode;
			Sns_Node_AdminObj->Node_init_end();

			break;
		}
		case SNS_NODE_REAL:
		{
			Sns_Node_RealObj = (Sns_Node_Real *) nextNode;
			Sns_Node_RealObj->Node_init_end();

			break;
		}
		case SNS_NODE_VIRTUAL:
		{
			Sns_Node_VirtualObj = (Sns_Node_Virtual *) nextNode;
			Sns_Node_VirtualObj->Node_init_end();

			break;
		}
		//Sns_Node_Case_Init_End//
		default:
			break;
		}		
		nextNode = nextNode->nextNodeData;
	}
}

////////////////////////////����ϵͳ��Ϣ������//////////////////////////////////////////////
//����:�������к�����������Ϣ����
void Sns_Scenarios::SNS_Simulate_Run()
{
	while (true) 
	{
		if(!SNS_SimTime_Control())
			return;

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
				case SNS_NODE_ADMIN:                  //����ڵ���Ϣ����
				{
					if((msg->Model_id != -1)||(msg->Event_Type != SNS_MSG_OUTPUT))//�ڵ������¼�����
					{
						Sns_Node_Admin * Sns_Node_AdminObj = (Sns_Node_Admin *) node;
						Sns_Node_AdminObj->SNS_Node_MsgDeal(msg);  //�ڵ���Ϣ���� 
						
					}
					else//�ڵ�����¼�����
					{
						switch(msg->Event_Name)
						{
				
						default:
							break;
						}						
					}
					break;
				}
				case SNS_NODE_REAL:
				{
					//EnterCriticalSection(&cs_WinPcap);
					if((msg->Model_id != -1)||(msg->Event_Type != SNS_MSG_OUTPUT))
					{
						Sns_Node_Real * Sns_Node_RealObj = (Sns_Node_Real *) node;
						Sns_Node_RealObj->SNS_Node_MsgDeal(msg);
					}
					else
					{

						switch(msg->Event_Name)
						{
						case Sns_Node_Real::MSG_OutEVENT_SendToOtherNodes:
							{

							}
						case Sns_Node_Real::MSG_OutEVENT_SendToRealNode:
							{

							}

						default:

							break;
						}
					}
					//LeaveCriticalSection(&cs_WinPcap);
					break;
				}
				case SNS_NODE_VIRTUAL:
				{
					if((msg->Model_id != -1)||(msg->Event_Type != SNS_MSG_OUTPUT))
					{
						Sns_Node_Virtual * Sns_Node_VirtualObj = (Sns_Node_Virtual *) node;
						Sns_Node_VirtualObj->SNS_Node_MsgDeal(msg);
					}
					else
					{

						switch(msg->Event_Name)
						{

						default:

							break;
						}
					}
					break;
				}
				//Sns_Node_Case_Run//
				default:

					break;
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

	Sns_Node_Admin * Sns_Node_AdminObj =NULL;

	Sns_Node_Real * Sns_Node_RealObj =NULL;
	Sns_Node_Virtual * Sns_Node_VirtualObj =NULL;
	//Sns_Node_Definition//

	SNS_Record_Stats_Value();

	while (nextNode != NULL) 
	{
		switch(nextNode->Node_Type)
		{
		case SNS_NODE_ADMIN:
		{
			Sns_Node_AdminObj = (Sns_Node_Admin *) nextNode;
			Sns_Node_AdminObj->StatsVar_Output = StatsVar_Output;
			Sns_Node_AdminObj->SNS_Simulate_End_Node();

			break;
		}
		case SNS_NODE_REAL:
		{
			Sns_Node_RealObj = (Sns_Node_Real *) nextNode;
			Sns_Node_RealObj->StatsVar_Output = StatsVar_Output;
			Sns_Node_RealObj->SNS_Simulate_End_Node();

			break;
		}
		case SNS_NODE_VIRTUAL:
		{
			Sns_Node_VirtualObj = (Sns_Node_Virtual *) nextNode;
			Sns_Node_VirtualObj->StatsVar_Output = StatsVar_Output;
			Sns_Node_VirtualObj->SNS_Simulate_End_Node();

			break;
		}
		//Sns_Node_Case_Sim_End//
		default:
			break;
		}
		nextNode = nextNode->nextNodeData;
	}

	StatsVar_Output->SNS_Print_InputStr(StatsFile_Path);//��StatsVar_Output�ڴ����״̬����д��·��ΪStatsFile_Path�ļ���
}

//����:��¼��ģ�͵����״̬����ֵ��StatsVar_Output��
void Sns_Scenarios::SNS_Record_Stats_Value()
{
	bool retVal = false;	//��������ֵ
	char Stats_ModelName[SNS_MAX_STRING_LENGTH]; //���ڼ�¼���״̬��������ģ������־

	StatsVar_Output = new Sns_Config_Input();//���״̬����������ʵ����

	sprintf(Stats_ModelName,"\n** Sns_Scenarios_begin\n");//��ģ�����״̬����ֵ��¼��ʼ
	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);//��Stats_ModelNameд������

	/////////////////////////////����ģ���������״̬����ֵд������//////////////////////////

	//Stats_Variable_Record//
	/////////////////////////////����ģ���������״̬����ֵд������//////////////////////////

	sprintf(Stats_ModelName,"\n** Sns_Scenarios_end\n");//��ģ�����״̬����ֵ��¼����
	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);//��Stats_ModelNameд������
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
	if(TimeDelay == 0)
	{
		switch(nodeData[DestiNode]->Node_Type)
		{
		case SNS_NODE_ADMIN:     //��Ϣ��������ڵ�
		{
			Sns_Node_Admin * Sns_Node_AdminObj = (Sns_Node_Admin *)nodeData[DestiNode];
			Sns_Node_AdminObj->SNS_Node_MsgDeal(SendMsg); 

			break;
		}
		case SNS_NODE_REAL:
		{
			Sns_Node_Real * Sns_Node_RealObj = (Sns_Node_Real *) nodeData[DestiNode];
			Sns_Node_RealObj->SNS_Node_MsgDeal(SendMsg);
			break;
		}
		case SNS_NODE_VIRTUAL:
		{
			Sns_Node_Virtual * Sns_Node_VirtualObj = (Sns_Node_Virtual *) nodeData[DestiNode];
			Sns_Node_VirtualObj->SNS_Node_MsgDeal(SendMsg);
			break;
		}
		//Sns_Node_Msg_Send//
		default:
			break;
		}
	}
	else
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
	Sns_Message *msg = new Sns_Message();//����һ����Ϣ����
	
    msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,PayLoad,PacketSize);//Ϊ��Ϣ��ֵ

	SNS_Msg_Send(msg,DestiNode,TimeDelay);//������Ϣ
}

//����:��һ����Ϣת������Ӧ��ģ��
//����:msg-ת������Ϣ��DestiNode--������ϢĿ�Ľڵ��ַ,ModelId--������Ϣ��ģ��ID,instanceId--����ģ��ʵ����,��ֵĬ��Ϊ0,EventName--������Ϣ�¼�����,
//     EventType--�����¼�����,TimeDelay--�����ӳ�
void Sns_Scenarios::Send_Aexisting_Msg(Sns_Message *msg,int DestiNode,int ModelId,int instanceId,int EventName,int EventType, clocktype  TimeDelay)
{
	msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,NULL,-1);//��Ϣ��ֵ

	SNS_Msg_Send(msg,DestiNode,TimeDelay);//��Ϣ����
}
