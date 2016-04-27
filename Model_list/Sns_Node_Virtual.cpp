/*
* Copyright (c) 2014,�������պ����ѧ
* All rights reserved.
*
* ϵͳ����: SPACE NETWORK SIMULATION SYSTEM
* ��    ��: ����
* ��ǰ�汾: SNS 1.0
* 
* �ļ�����: Sns_Node_Virtual.cpp
* ��ǰ�汾: V 1.0.0
* �ļ���ʶ: Sns_Node_Virtual��Դ�ļ�
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

#include "Sns_Node_Virtual.h"
//���ڵ�����ģ��ͷ�ļ�
#include "Sns_Model_OSPFv2.h"
#include "Sns_Model_NetworkIP.h"
#include "Sns_Scenarios.h"
//Include_ofModel//

/////////������Ϊģ�͵����Զ����� end �û���Ҫ�ӵĶ���������/////////////

/////////////////////////���캯������������/////////////////////////////////////////////

Sns_Node_Virtual::Sns_Node_Virtual()
{
	///////////���������ʼ��,ģ���Զ�����//////////

	//Stats_Variable_Init//	
	
	///////////���������ʼ��,ģ���Զ����� end//////////
}

Sns_Node_Virtual::~Sns_Node_Virtual()
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
void Sns_Node_Virtual::Node_init()
{

	//////////�������ļ��ж�ȡ��ʼ������,ģ�͵����Զ�����////////////////////

	char ModelName[SNS_MAX_STRING_LENGTH];  //�����ļ���ģ��ʶ���־

	char buf[SNS_MAX_STRING_LENGTH];  //��ȡ�����ļ��е��ַ���
	
	int RetArrNum;//��ȡ������������ֵ

	bool retVal = false;//��������ֵ
	
	Config_Input = new Sns_Config_Input();//����һ�������ļ��������

	sprintf(ModelName,"Sns_Node_Virtual[%d]",Node_id_InOnetype);

	Config_Input->SNS_Read_ModelConf(ConfFile_Path, ModelName);//��ȡ���ڵ�����ò���

	//Config_Variable_Init//
	//////////�������ļ��ж�ȡ��ʼ������,ģ�͵����Զ����� end////////////////////

	/////////////////////�������ļ��л�ȡ���ڵ������ĸ���ģ�ͼ���Ŀ/////////////////
	retVal = Config_Input->SNS_ReadInt( "int,Num_Sns_Model_OSPFv2", &RetArrNum, &Num_ofThis.Num_Sns_Model_OSPFv2);
	if (retVal == false)
	{
		Num_ofThis.Num_Sns_Model_OSPFv2 = 1;
	}
	retVal = Config_Input->SNS_ReadInt( "int,Num_Sns_Model_NetworkIP", &RetArrNum, &Num_ofThis.Num_Sns_Model_NetworkIP);
	if (retVal == false)
	{
		Num_ofThis.Num_Sns_Model_NetworkIP = 1;
	}
	//Config_ModelNumInit_Add//
	/////////////////////�������ļ��л�ȡ���ڵ������ĸ���ģ�ͼ���Ŀ end//////////////
	
	//�ڵ�������ģ��������ʼ��
	Model_num_In_Node = Num_ofThis.Num_Sns_Model_OSPFv2 + Num_ofThis.Num_Sns_Model_NetworkIP;
	//Sum_ModelNum_Add//

	char paraName[SNS_MAX_STRING_LENGTH];
	bool boolBuf;
	int intBuf;
	char charBuf;
	char strBuf[SNS_MAX_STRING_LENGTH];
	sprintf(paraName,"int,numberInterfaces");
	retVal=Config_Input->SNS_ReadInt(paraName,&RetArrNum,&intBuf);
	if(retVal)
	{
		numberInterfaces=intBuf;
	}
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
	forwardingTable.init(numberInterfaces,interfaceInfo);

	//��ʼ���ڵ��ϵĸ���ģ��
	Model_OfNode_Init();
}

//����:��ʼ�����ڵ����л���/Э��ģ��	
void Sns_Node_Virtual::Model_OfNode_Init()
{
	////////////*ģ�͵����Զ�����*////////////////////////

	short modelist_id = 0;
	int i;

	/////////////////////��ʼ��ģ������/////////////////////////////////
	Model_List = (Sns_base_model **)checked_pc_malloc(sizeof(Sns_base_model *) * Model_num_In_Node);// Ϊģ����������ڴ�
	
	/////////////////////��ʼ������ģ��/////////////////////////////////
	Sns_Model_OSPFv2* Sns_Model_OSPFv2Obj;
	for(i = 0; i< Num_ofThis.Num_Sns_Model_OSPFv2; i++)
	{
		Model_List[modelist_id] = new Sns_Model_OSPFv2();

		Sns_Model_OSPFv2Obj = (Sns_Model_OSPFv2*)Model_List[modelist_id];

		Sns_Model_OSPFv2Obj->Model_id = SNS_MODEL_OSPFV2;			//��ʼ��Э��ID�ţ����ڱ�ʶЭ��
		Sns_Model_OSPFv2Obj->Scenarios_Data = (Sns_Scenarios *)Scenarios_Data; //ʵ����������
		Sns_Model_OSPFv2Obj->Model_Instance_id = i;			//�ڵ��и�ģ�͵�ʵ����־,����ģ���ڸýڵ���n��ʵ���еĵ�i��
		Sns_Model_OSPFv2Obj->Cur_Node_id = Node_id;			//ģ�������Ľڵ�ID
		Sns_Model_OSPFv2Obj->Cur_Node_id_inOneType = Node_id_InOnetype;	//ģ�������Ľڵ��ڸ�Э�����͵����,���������ļ�����
		Sns_Model_OSPFv2Obj->Cur_Node_Name = "Sns_Node_Virtual";		//ģ�������Ľڵ�������,���������ļ�����
		Sns_Model_OSPFv2Obj->ConfFile_Path = ConfFile_Path;		//Э�������ļ�·��

		Sns_Model_OSPFv2Obj->numberInterfaces=numberInterfaces;
		Sns_Model_OSPFv2Obj->interfaceInfo=interfaceInfo;
		Sns_Model_OSPFv2Obj->forwardingTable=&forwardingTable;

		if(i==0)
			Modelid_In_list[SNS_MODEL_OSPFV2] = modelist_id;		//ģ���ڱ��ڵ�model list�е���ʼλ��

		Sns_Model_OSPFv2Obj->Model_init();

		modelist_id ++;				//����Э���ʼ������
	}

	Sns_Model_NetworkIP* Sns_Model_NetworkIPObj;
	for(i = 0; i< Num_ofThis.Num_Sns_Model_NetworkIP; i++)
	{
		Model_List[modelist_id] = new Sns_Model_NetworkIP();

		Sns_Model_NetworkIPObj = (Sns_Model_NetworkIP*)Model_List[modelist_id];

		Sns_Model_NetworkIPObj->Model_id = SNS_MODEL_NETWORKIP;			//��ʼ��Э��ID�ţ����ڱ�ʶЭ��
		Sns_Model_NetworkIPObj->Scenarios_Data = (Sns_Scenarios *)Scenarios_Data; //ʵ����������
		Sns_Model_NetworkIPObj->Model_Instance_id = i;			//�ڵ��и�ģ�͵�ʵ����־,����ģ���ڸýڵ���n��ʵ���еĵ�i��
		Sns_Model_NetworkIPObj->Cur_Node_id = Node_id;			//ģ�������Ľڵ�ID
		Sns_Model_NetworkIPObj->Cur_Node_id_inOneType = Node_id_InOnetype;	//ģ�������Ľڵ��ڸ�Э�����͵����,���������ļ�����
		Sns_Model_NetworkIPObj->Cur_Node_Name = "Sns_Node_Virtual";		//ģ�������Ľڵ�������,���������ļ�����
		Sns_Model_NetworkIPObj->ConfFile_Path = ConfFile_Path;		//Э�������ļ�·��

		Sns_Model_NetworkIPObj->numberInterfaces=numberInterfaces;
		Sns_Model_NetworkIPObj->interfaceInfo=interfaceInfo;
		Sns_Model_NetworkIPObj->forwardingTable=&forwardingTable;

		if(i==0)
			Modelid_In_list[SNS_MODEL_NETWORKIP] = modelist_id;		//ģ���ڱ��ڵ�model list�е���ʼλ��

		Sns_Model_NetworkIPObj->Model_init();

		modelist_id ++;				//����Э���ʼ������
	}

	//Model_Initialization//
	
	/////////////////////��ʼ������ģ�� end/////////////////////////////////
	
	////////////*ģ�͵����Զ����� end*////////////////////////
}


//����:�ڵ��ʼ����Ĵ�����,������ʱ��Ҫ���нڵ㶼��ʼ����ɲſ�ִ�еĶ���
void Sns_Node_Virtual::Node_init_end()
{
	////////////*ģ�͵����Զ�����*////////////////////////

	int i;
	short modelist_id = 0;
	
	Sns_Model_OSPFv2* Sns_Model_OSPFv2Obj;
	for(i = 0;i< Num_ofThis.Num_Sns_Model_OSPFv2; i++)
	{
		Sns_Model_OSPFv2Obj = (Sns_Model_OSPFv2*)Model_List[modelist_id];

		Sns_Model_OSPFv2Obj->Model_init_end();		//����Э���ʼ������������

		modelist_id ++;
	}

	Sns_Model_NetworkIP* Sns_Model_NetworkIPObj;
	for(i = 0;i< Num_ofThis.Num_Sns_Model_NetworkIP; i++)
	{
		Sns_Model_NetworkIPObj = (Sns_Model_NetworkIP*)Model_List[modelist_id];

		Sns_Model_NetworkIPObj->Model_init_end();		//����Э���ʼ������������

		modelist_id ++;
	}

	//Model_Init_end//

	////////////*ģ�͵����Զ����� end*////////////////////////
	if(Node_id_InOnetype==5)
	{
		Send_Anew_Msg(Node_id,-1,0,0,0,NULL,0,SNS_ConvertToClock("30S"));
	}
	
}
///////////////////�ڵ���Ϣ������//////////////////////////////////////////
/*���ݽ��յ���Ϣ,�����ж������ĸ�ģ�ͣ�ģ��ID��1��ʼ����ʾ���ڵ�������ģ�ͣ���Ϊ0����ʾΪ�ڵ㱾��;
����ж��ǳ��¼��������¼����������¼���ֱ�ӵ���ģ�����¼������������ǳ��¼�������*/
//�����ֿ��Ϊģ�͵����Զ�����

//����:�ڵ����Ϣ������,���ո���ģ��/�ڵ���������¼�,
//     ����ģ��������Ϣ,����Ϣ����ģ��;���ڽڵ�������Ϣ,������Ӧ����������
//     ���������Ϣ,������Ӧ����������
void Sns_Node_Virtual::SNS_Node_MsgDeal(Sns_Message *msg)
{
	short modelist_id;
	switch(msg->Model_id) 
	{
	case -1:                            //�ڵ㱾��������¼���Ϣ
	{
		switch(msg->Event_Name) //��Ϣ�¼�ö��
		{
		//SNS_MSG_EVENT_IN//
		default:

			char* packet="hello!";
			int packetSize=sizeof("hello!");
			sendIpv4Packet(hostBitsStr2Uint("192.168.12.7"),packet,packetSize);

			break;
		}

		break;
	}

	case SNS_MODEL_OSPFV2:
	{
		Sns_Model_OSPFv2* Sns_Model_OSPFv2Obj = NULL;
		modelist_id = Modelid_In_list[SNS_MODEL_OSPFV2] + msg->Model_Instance_id;
		Sns_Model_OSPFv2Obj = (Sns_Model_OSPFv2 *)Model_List[modelist_id];

		if (msg->Event_Type==SNS_MSG_INPUT)	//ģ�������¼�����
		{
			Sns_Model_OSPFv2Obj->SNS_Model_MsgDeal(msg);
		}
		else			//ģ����������¼�
		{
			switch(msg->Event_Name)
			{
			case Sns_Model_OSPFv2::MSG_OutEVENT_OSPFv2_toNetworkIP:
				{
					Send_Aexisting_Msg(msg,Node_id,SNS_MODEL_NETWORKIP,0,Sns_Model_NetworkIP::MSG_InEVENT_NETWORK_FromOSPFv2,SNS_MSG_INPUT,0);
				}

			default:
				break;
			}
		}
		break;
	}
	case SNS_MODEL_NETWORKIP:
	{
		Sns_Model_NetworkIP* Sns_Model_NetworkIPObj = NULL;
		modelist_id = Modelid_In_list[SNS_MODEL_NETWORKIP] + msg->Model_Instance_id;
		Sns_Model_NetworkIPObj = (Sns_Model_NetworkIP *)Model_List[modelist_id];

		if (msg->Event_Type==SNS_MSG_INPUT)	//ģ�������¼�����
		{
			Sns_Model_NetworkIPObj->SNS_Model_MsgDeal(msg);
		}
		else			//ģ����������¼�
		{
			switch(msg->Event_Name)
			{
			case Sns_Model_NetworkIP::MSG_OutEVENT_NETWORK_ToMAC:
				{
					Sns_Model_NetworkIP::NetworkToMACInfo* info = (Sns_Model_NetworkIP::NetworkToMACInfo*)msg->Info_Msg;
					Sns_Model_NetworkIP::IpHeaderType* header=(Sns_Model_NetworkIP::IpHeaderType*)msg->Pay_Load;
					if(info->nexthopaddr==ANY_DEST)
					{
						int interfaceIndex=info->interfaceIndex;
						if(interfaceInfo[interfaceIndex].dstIntfAddr!=UNKNOWNADDRESS)
						{
							header->ip_src=interfaceInfo[interfaceIndex].address;
							info->nexthopaddr=interfaceInfo[interfaceIndex].dstIntfAddr;
							Send_Aexisting_Msg(msg ,interfaceInfo[info->interfaceIndex].dstNodeId,SNS_MODEL_NETWORKIP,0,Sns_Model_NetworkIP::MSG_InEVENT_NETWORK_FromMAC,SNS_MSG_INPUT,0);
						}
						else
						{
							xdelete( msg ) ;
						}
					}
					else
					{
						int dstNodeId=GetOtherNodeIdfromAddress(info->nexthopaddr);
						if(dstNodeId!=-1)
						{
							Send_Aexisting_Msg(msg ,dstNodeId,SNS_MODEL_NETWORKIP,0,Sns_Model_NetworkIP::MSG_InEVENT_NETWORK_FromMAC,SNS_MSG_INPUT,0);//��Ϣ����,����ʱ��Ϊ0
						}
// 						else if(isMyIMI(info->nexthopaddr))
// 						{
// 							int dstIMIId=getMyIMI(info->nexthopaddr);
// 
// 							printf( "Node_Id :%5d  downstream  to Node%5d \n", Node_id , dstIMIId ) ;
// 
// 							Send_Aexisting_Msg(msg ,dstIMIId,SNS_MODEL_NETWORKIP,0,Sns_Model_NetworkIP::MSG_InEVENT_NETWORK_FromMAC,SNS_MSG_INPUT,0);//��Ϣ����,����ʱ��Ϊ0
// 						}
						else
						{
							char nextHopStr[SNS_MAX_STRING_LENGTH];
							convertIpAddressToString(info->nexthopaddr,nextHopStr);
							xdelete( msg ) ;
							///////////////////////////////////
							////////��ӡ��Ϣ��
							printf( "Last_Jump_Over!!!!\n" ) ;
							printf("The packet which is from Node %u to %16s is dropped\n",Node_id,nextHopStr);
						}
					}
//						xdelete(msg);
					info=NULL;
					header=NULL;
					msg=NULL;
										
					break;
				}
			case Sns_Model_NetworkIP::MSG_OutEVENT_NETWORK_ToTransport:
				{
					char* packet=msg->Pay_Load;//��ȡ����Ϣ

					//������
					printf("\n==============================================\n");
					printf("node %u:%s\n",Node_id,packet);
					printf("\n===============================================\n");


					////****!!!!
					xdelete( msg ) ;

					break;
				}
			case Sns_Model_NetworkIP::MSG_OutEVENT_NETWORK_ToProtocol_OSPFv2:
				{
					Send_Aexisting_Msg(msg,Node_id,SNS_MODEL_OSPFV2,0,Sns_Model_OSPFv2::MSG_InEVENT_OspfHandleRoutingProtocolPacket,SNS_MSG_INPUT,0);
					break;
				}
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
void Sns_Node_Virtual::SNS_Simulate_End_Node()
{
	////////////*ģ�͵����Զ�����*////////////////////////

	int i;
	short modelist_id = 0;

	SNS_Record_Stats_Value();
	
	Sns_Model_OSPFv2* Sns_Model_OSPFv2Obj;
	for(i = 0;i< Num_ofThis.Num_Sns_Model_OSPFv2; i++)
	{
		Sns_Model_OSPFv2Obj = (Sns_Model_OSPFv2*)Model_List[modelist_id];
		Sns_Model_OSPFv2Obj->StatsVar_Output = StatsVar_Output;		//�����״̬�洢�����ݸ�ģ��
		Sns_Model_OSPFv2Obj->SNS_Simulate_End_Model();		//����Э�����н���������

		modelist_id ++;
	}

	Sns_Model_NetworkIP* Sns_Model_NetworkIPObj;
	for(i = 0;i< Num_ofThis.Num_Sns_Model_NetworkIP; i++)
	{
		Sns_Model_NetworkIPObj = (Sns_Model_NetworkIP*)Model_List[modelist_id];
		Sns_Model_NetworkIPObj->StatsVar_Output = StatsVar_Output;		//�����״̬�洢�����ݸ�ģ��
		Sns_Model_NetworkIPObj->SNS_Simulate_End_Model();		//����Э�����н���������

		modelist_id ++;
	}

	//Node_Sim_end//

	////////////*ģ�͵����Զ����� end*////////////////////////
}

//����:��¼��ģ�͵����״̬����ֵ��StatsVar_Output��
void Sns_Node_Virtual::SNS_Record_Stats_Value()
{
	bool retVal = false;	//��������ֵ
	char Stats_ModelName[SNS_MAX_STRING_LENGTH]; //���ڼ�¼���״̬��������ģ������־

	sprintf(Stats_ModelName,"\n** Sns_Node_Virtual[%d]_begin\n",Node_id_InOnetype);//��ģ�����״̬����ֵ��¼��ʼ
	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);//��Stats_ModelNameд������

	/////////////////////////////����ģ���������״̬����ֵд������//////////////////////////

	//Stats_Variable_Record//
	/////////////////////////////����ģ���������״̬����ֵд������//////////////////////////

	sprintf(Stats_ModelName,"\n** Sns_Node_Virtual[%d]_end\n",Node_id_InOnetype);//��ģ�����״̬����ֵ��¼����
	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);//��Stats_ModelNameд������
}

//����:��һ����Ϣת������Ӧ��ģ��
//����:msg-ת������Ϣ��DestiNode--������ϢĿ�Ľڵ��ַ,ModelId--������Ϣ��ģ��ID,instanceId--����ģ��ʵ����,��ֵĬ��Ϊ0,EventName--������Ϣ�¼�����,
//     EventType--�����¼�����,TimeDelay--�����ӳ�
void Sns_Node_Virtual::Send_Aexisting_Msg(Sns_Message *msg,int DestiNode,int ModelId,int instanceId,int EventName,int EventType, clocktype  TimeDelay)
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
void Sns_Node_Virtual::Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay)
{
	Sns_Scenarios *scenariosdata;

	scenariosdata = (Sns_Scenarios *)Scenarios_Data;

	Sns_Message *msg = new Sns_Message();//����һ����Ϣ����

    msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,PayLoad,PacketSize);//Ϊ��Ϣ��ֵ

	scenariosdata->SNS_Msg_Send(msg,DestiNode,TimeDelay);//������Ϣ
}


////////////////////////////////////�ڵ���Ϣ������////////////////////////////////////

//Sns_Msg_In_Func//



////////////////////////////////////�ڵ���Ϣ������ end////////////////////////////////////

int Sns_Node_Virtual::GetOtherNodeIdfromAddress(unsigned address,unsigned mask)
{
	for(int i=0;i<numberInterfaces;i++)
	{
		if(interfaceInfo[i].dstIntfAddr==address)
			return interfaceInfo[i].dstNodeId;
	}
	return -1;
}

void Sns_Node_Virtual::sendIpv4Packet(unsigned dstAddr, char* packet, int packetSize, clocktype delay)
{
	Sns_Model_NetworkIP::TransportToNetworkInfo *info = new Sns_Model_NetworkIP::TransportToNetworkInfo;//��IP��ͨ������ĸ�����Ϣ
	info->destinationAddr = dstAddr;//Ŀ�ĵ�ַ
	info->priority = 0;//���ȼ�
	info->Protocol_ToIP = Sns_Model_NetworkIP::PROTOCOL_PACKET;//������
	Sns_Message *msg = new Sns_Message();
	msg->SNS_Msg_AddInfo((char *)info, sizeof(Sns_Model_NetworkIP::TransportToNetworkInfo));
	msg->SNS_Msg_Assignment(SNS_MODEL_NETWORKIP,0,Sns_Model_NetworkIP::MSG_InEVENT_NETWORK_FromTransport,SNS_MSG_INPUT,packet,packetSize);
	//����
	Send_Aexisting_Msg(msg,Node_id,SNS_MODEL_NETWORKIP,0,Sns_Model_NetworkIP::MSG_InEVENT_NETWORK_FromTransport,SNS_MSG_INPUT, delay);
	xdelete( info );
}