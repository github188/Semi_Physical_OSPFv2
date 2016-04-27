/*
* Copyright (c) 2014,�������պ����ѧ
* All rights reserved.
*
* ϵͳ����: SPACE NETWORK SIMULATION SYSTEM
* ��    ��: ����
* ��ǰ�汾: SNS 1.0
* 
* �ļ�����: Sns_Node_Real.cpp
* ��ǰ�汾: V 1.0.0
* �ļ���ʶ: Sns_Node_Real��Դ�ļ�
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

#include "Sns_Node_Real.h"
#include "Sns_Model_NetworkIP.h"
//���ڵ�����ģ��ͷ�ļ�
//Include_ofModel//

/////////������Ϊģ�͵����Զ����� end �û���Ҫ�ӵĶ���������/////////////

/////////////////////////���캯������������/////////////////////////////////////////////

Sns_Node_Real::Sns_Node_Real()
{
	///////////���������ʼ��,ģ���Զ�����//////////

	//Stats_Variable_Init//	
	
	///////////���������ʼ��,ģ���Զ����� end//////////
}

Sns_Node_Real::~Sns_Node_Real()
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
void Sns_Node_Real::Node_init()
{

	//////////�������ļ��ж�ȡ��ʼ������,ģ�͵����Զ�����////////////////////

	char ModelName[SNS_MAX_STRING_LENGTH];  //�����ļ���ģ��ʶ���־

	char buf[SNS_MAX_STRING_LENGTH];  //��ȡ�����ļ��е��ַ���
	
	int RetArrNum;//��ȡ������������ֵ

	bool retVal = false;//��������ֵ
	
	Config_Input = new Sns_Config_Input();//����һ�������ļ��������

	sprintf(ModelName,"Sns_Node_Real[%d]",Node_id_InOnetype);

	Config_Input->SNS_Read_ModelConf(ConfFile_Path, ModelName);//��ȡ���ڵ�����ò���

	//Config_Variable_Init//
	//////////�������ļ��ж�ȡ��ʼ������,ģ�͵����Զ����� end////////////////////

	/////////////////////�������ļ��л�ȡ���ڵ������ĸ���ģ�ͼ���Ŀ/////////////////
	//Config_ModelNumInit_Add//
	/////////////////////�������ļ��л�ȡ���ڵ������ĸ���ģ�ͼ���Ŀ end//////////////
	
	//�ڵ�������ģ��������ʼ��
	Model_num_In_Node = 0;
	//Sum_ModelNum_Add//
	char paraName[SNS_MAX_STRING_LENGTH];
	bool boolBuf;
	int intBuf;
	char charBuf;
	char strBuf[SNS_MAX_STRING_LENGTH];
	numberInterfaces=1;
// 	sprintf(paraName,"int,numberInterfaces");
// 	retVal=Config_Input->SNS_ReadInt(paraName,&RetArrNum,&intBuf);
// 	if(retVal)
// 	{
// 		numberInterfaces=intBuf;
// 	}
	for(int i=0;i<numberInterfaces;i++)
	{
		sprintf(paraName,"string,[%d]InterfaceAddress",i);
		retVal=Config_Input->SNS_ReadString(paraName,&RetArrNum,strBuf);
		if(retVal)
		{
			interfaceInfo[i].address = hostBitsStr2Uint(strBuf);
		}
		else
		{
			interfaceInfo[i].address = UNKNOWNADDRESS;
		}
		sprintf(paraName,"string,[%d]InterfaceSubnetMask",i);
		retVal=Config_Input->SNS_ReadString(paraName,&RetArrNum,strBuf);
		if(retVal)
		{
			interfaceInfo[i].subnetMask = hostBitsStr2Uint(strBuf);
		}
		else
		{
			interfaceInfo[i].subnetMask=UNKNOWNADDRESS;
		}
		sprintf(paraName,"string,[%d]DstInterfaceAddress",i);
		retVal=Config_Input->SNS_ReadString(paraName,&RetArrNum,strBuf);
		if(retVal)
		{
			interfaceInfo[i].dstIntfAddr=hostBitsStr2Uint(strBuf);
		}
		else
		{
			interfaceInfo[i].dstIntfAddr=UNKNOWNADDRESS;
		}
		sprintf(paraName,"int,[%d]DstNodeId",i);
		retVal=Config_Input->SNS_ReadInt(paraName,&RetArrNum,&intBuf);
		if(retVal)
		{
			interfaceInfo[i].dstNodeId=intBuf+1+1;//��������ڵ㡢��ʵ�ڵ�
		}
		else
		{
			interfaceInfo[i].dstNodeId=UNKNOWNADDRESS;
		}
		sprintf(paraName,"int,[%d]Cost",i);
		retVal=Config_Input->SNS_ReadInt(paraName,&RetArrNum,&intBuf);
		if(retVal)
		{
			interfaceInfo[i].cost=intBuf;
		}
		else
		{
			interfaceInfo[i].cost=5;
		}
	}

	//��ʼ���ڵ��ϵĸ���ģ��
	Model_OfNode_Init();
}

//����:��ʼ�����ڵ����л���/Э��ģ��	
void Sns_Node_Real::Model_OfNode_Init()
{
	////////////*ģ�͵����Զ�����*////////////////////////

	short modelist_id = 0;
	int i;

	/////////////////////��ʼ��ģ������/////////////////////////////////
	Model_List = (Sns_base_model **)checked_pc_malloc(sizeof(Sns_base_model *) * Model_num_In_Node);// Ϊģ����������ڴ�
	
	/////////////////////��ʼ������ģ��/////////////////////////////////
	//Model_Initialization//
	
	/////////////////////��ʼ������ģ�� end/////////////////////////////////
	
	////////////*ģ�͵����Զ����� end*////////////////////////
}


//����:�ڵ��ʼ����Ĵ�����,������ʱ��Ҫ���нڵ㶼��ʼ����ɲſ�ִ�еĶ���
void Sns_Node_Real::Node_init_end()
{
	////////////*ģ�͵����Զ�����*////////////////////////

	int i;
	short modelist_id = 0;
	
	//Model_Init_end//

	////////////*ģ�͵����Զ����� end*////////////////////////

	//ƽ̨addr=0x0���ڵ�addr=0xf
	caper.setMyNode(this);
	caper.setMyAddr(0x0);
	//������=1
	caper.openAdapter(1);
	caper.beginCatching();
	
}
///////////////////�ڵ���Ϣ������//////////////////////////////////////////
/*���ݽ��յ���Ϣ,�����ж������ĸ�ģ�ͣ�ģ��ID��1��ʼ����ʾ���ڵ�������ģ�ͣ���Ϊ0����ʾΪ�ڵ㱾��;
����ж��ǳ��¼��������¼����������¼���ֱ�ӵ���ģ�����¼������������ǳ��¼�������*/
//�����ֿ��Ϊģ�͵����Զ�����

//����:�ڵ����Ϣ������,���ո���ģ��/�ڵ���������¼�,
//     ����ģ��������Ϣ,����Ϣ����ģ��;���ڽڵ�������Ϣ,������Ӧ����������
//     ���������Ϣ,������Ӧ����������
void Sns_Node_Real::SNS_Node_MsgDeal(Sns_Message *msg)
{
	short modelist_id;
	switch(msg->Model_id) 
	{
	case -1:                            //�ڵ㱾��������¼���Ϣ
	{
		switch(msg->Event_Name) //��Ϣ�¼�ö��
		{
		case MSG_InEVENT_ReceiveFromOtherNodes:
		{
			Process_MSG_InEVENT_ReceiveFromOtherNodes(msg);

			break;
		}
		case MSG_InEVENT_ReceiveFromRealNode:
		{
			Process_MSG_InEVENT_ReceiveFromRealNode(msg);

			break;
		}
		//SNS_MSG_EVENT_IN//
		default:
		
			break;
		}

		break;
	}
	case SNS_MODEL_NETWORKIP:
		{
			if (msg->Event_Type==SNS_MSG_INPUT)	//ģ�������¼�����
			{
				switch(msg->Event_Name) //��Ϣ�¼�ö��
				{
				case Sns_Model_NetworkIP::MSG_InEVENT_NETWORK_FromMAC:
					{
						int packetSize=msg->PayLoad_Size;
						char* packet=(char*)malloc(packetSize);
						memcpy_s(packet,packetSize,msg->Pay_Load,packetSize);
						caper.sendPacket(0xf,(unsigned char*)packet,packetSize);
						xfree(packet);
						xdelete(msg);
						break;
					}
					//SNS_MSG_EVENT_IN//
				default:

					break;
				}
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
void Sns_Node_Real::SNS_Simulate_End_Node()
{
	////////////*ģ�͵����Զ�����*////////////////////////

	int i;
	short modelist_id = 0;

	SNS_Record_Stats_Value();
	
	//Node_Sim_end//

	////////////*ģ�͵����Զ����� end*////////////////////////

	caper.closeCurrAdapter();
}

//����:��¼��ģ�͵����״̬����ֵ��StatsVar_Output��
void Sns_Node_Real::SNS_Record_Stats_Value()
{
	bool retVal = false;	//��������ֵ
	char Stats_ModelName[SNS_MAX_STRING_LENGTH]; //���ڼ�¼���״̬��������ģ������־

	sprintf(Stats_ModelName,"\n** Sns_Node_Real[%d]_begin\n",Node_id_InOnetype);//��ģ�����״̬����ֵ��¼��ʼ
	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);//��Stats_ModelNameд������

	/////////////////////////////����ģ���������״̬����ֵд������//////////////////////////

	//Stats_Variable_Record//
	/////////////////////////////����ģ���������״̬����ֵд������//////////////////////////

	sprintf(Stats_ModelName,"\n** Sns_Node_Real[%d]_end\n",Node_id_InOnetype);//��ģ�����״̬����ֵ��¼����
	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);//��Stats_ModelNameд������
}

//����:��һ����Ϣת������Ӧ��ģ��
//����:msg-ת������Ϣ��DestiNode--������ϢĿ�Ľڵ��ַ,ModelId--������Ϣ��ģ��ID,instanceId--����ģ��ʵ����,��ֵĬ��Ϊ0,EventName--������Ϣ�¼�����,
//     EventType--�����¼�����,TimeDelay--�����ӳ�
void Sns_Node_Real::Send_Aexisting_Msg(Sns_Message *msg,int DestiNode,int ModelId,int instanceId,int EventName,int EventType, clocktype  TimeDelay)
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
void Sns_Node_Real::Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay)
{
	Sns_Scenarios *scenariosdata;

	scenariosdata = (Sns_Scenarios *)Scenarios_Data;

	Sns_Message *msg = new Sns_Message();//����һ����Ϣ����

    msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,PayLoad,PacketSize);//Ϊ��Ϣ��ֵ

	scenariosdata->SNS_Msg_Send(msg,DestiNode,TimeDelay);//������Ϣ
}


////////////////////////////////////�ڵ���Ϣ������////////////////////////////////////

//���ܣ�MSG_InEVENT_ReceiveFromOtherNodes�¼����� 
void Sns_Node_Real:: Process_MSG_InEVENT_ReceiveFromOtherNodes(Sns_Message *msg) 
{

}
//���ܣ�MSG_InEVENT_ReceiveFromRealNode�¼����� 
void Sns_Node_Real:: Process_MSG_InEVENT_ReceiveFromRealNode(Sns_Message *msg) 
{

}
//Sns_Msg_In_Func//



////////////////////////////////////�ڵ���Ϣ������ end////////////////////////////////////
void Sns_Node_Real::ReceiveFromRealNode(char* packet, int packetSize)
{
	clocktype delay=0;
	Sns_Model_NetworkIP::NetworkToMACInfo* info=(Sns_Model_NetworkIP::NetworkToMACInfo*)malloc(sizeof(Sns_Model_NetworkIP::NetworkToMACInfo));
	memset(info,0,sizeof(Sns_Model_NetworkIP::NetworkToMACInfo));
	info->interfaceIndex=0;
	info->nexthopaddr=interfaceInfo[info->interfaceIndex].dstIntfAddr;
	info->srcAddr=interfaceInfo[info->interfaceIndex].address;

	Sns_Message* msg=new Sns_Message;
	msg->SNS_Msg_Assignment(SNS_MODEL_NETWORKIP,0,Sns_Model_NetworkIP::MSG_InEVENT_NETWORK_FromMAC,SNS_MSG_INPUT,packet,packetSize);
	msg->SNS_Msg_AddInfo((char*)info,sizeof(Sns_Model_NetworkIP::NetworkToMACInfo));
	((Sns_Scenarios*)Scenarios_Data)->SNS_Msg_Send(msg,interfaceInfo[0].dstNodeId,delay);

	xfree(packet);
}
