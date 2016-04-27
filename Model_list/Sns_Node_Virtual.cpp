/*
* Copyright (c) 2014,北京航空航天大学
* All rights reserved.
*
* 系统名称: SPACE NETWORK SIMULATION SYSTEM
* 作    者: 张涛
* 当前版本: SNS 1.0
* 
* 文件名称: Sns_Node_Virtual.cpp
* 当前版本: V 1.0.0
* 文件标识: Sns_Node_Virtual类源文件
* 功能描述: 
* 完 成 人: 
* 联系方式: 
* 完成日期: 
*
* 摘    要:
*/
//////////////////////////////////////////////////////////////////////

/////////本部分为模型导向自动生成/////////////
#include "stdafx.h"//基本c++库

#include "Sns_Message.h"//平台库
#include "Sns_Config_Input.h"//平台库

#include "Sns_Node_Virtual.h"
//本节点依附模型头文件
#include "Sns_Model_OSPFv2.h"
#include "Sns_Model_NetworkIP.h"
#include "Sns_Scenarios.h"
//Include_ofModel//

/////////本部分为模型导向自动生成 end 用户需要加的定义在下面/////////////

/////////////////////////构造函数，析构函数/////////////////////////////////////////////

Sns_Node_Virtual::Sns_Node_Virtual()
{
	///////////输出参数初始化,模板自动生成//////////

	//Stats_Variable_Init//	
	
	///////////输出参数初始化,模板自动生成 end//////////
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

////////////////////////节点初始化函数///////////////////////////////////////

//功能:节点初始化函数,读取节点对应配置文件,配置节点初始化配置参数
//     为节点中所用到模型对象实例化,并启动模型初始化
void Sns_Node_Virtual::Node_init()
{

	//////////从配置文件中读取初始化参数,模型导向自动生成////////////////////

	char ModelName[SNS_MAX_STRING_LENGTH];  //配置文件中模型识别标志

	char buf[SNS_MAX_STRING_LENGTH];  //读取配置文件中的字符串
	
	int RetArrNum;//读取参数个数返回值

	bool retVal = false;//函数返回值
	
	Config_Input = new Sns_Config_Input();//声明一个配置文件处理对象

	sprintf(ModelName,"Sns_Node_Virtual[%d]",Node_id_InOnetype);

	Config_Input->SNS_Read_ModelConf(ConfFile_Path, ModelName);//读取本节点的配置参数

	//Config_Variable_Init//
	//////////从配置文件中读取初始化参数,模型导向自动生成 end////////////////////

	/////////////////////从配置文件中获取本节点依附的各类模型及数目/////////////////
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
	/////////////////////从配置文件中获取本节点依附的各类模型及数目 end//////////////
	
	//节点依附的模型总数初始化
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
			interfaceInfo[i].dstNodeId=intBuf+1+1;//跳过管理节点、真实节点
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

	//初始化节点上的各类模型
	Model_OfNode_Init();
}

//功能:初始化本节点所有环境/协议模型	
void Sns_Node_Virtual::Model_OfNode_Init()
{
	////////////*模型导向自动生成*////////////////////////

	short modelist_id = 0;
	int i;

	/////////////////////初始化模型链表/////////////////////////////////
	Model_List = (Sns_base_model **)checked_pc_malloc(sizeof(Sns_base_model *) * Model_num_In_Node);// 为模型链表分配内存
	
	/////////////////////初始化具体模型/////////////////////////////////
	Sns_Model_OSPFv2* Sns_Model_OSPFv2Obj;
	for(i = 0; i< Num_ofThis.Num_Sns_Model_OSPFv2; i++)
	{
		Model_List[modelist_id] = new Sns_Model_OSPFv2();

		Sns_Model_OSPFv2Obj = (Sns_Model_OSPFv2*)Model_List[modelist_id];

		Sns_Model_OSPFv2Obj->Model_id = SNS_MODEL_OSPFV2;			//初始化协议ID号，用于标识协议
		Sns_Model_OSPFv2Obj->Scenarios_Data = (Sns_Scenarios *)Scenarios_Data; //实例化场景类
		Sns_Model_OSPFv2Obj->Model_Instance_id = i;			//节点中该模型的实例标志,即本模型在该节点内n个实例中的第i个
		Sns_Model_OSPFv2Obj->Cur_Node_id = Node_id;			//模型依附的节点ID
		Sns_Model_OSPFv2Obj->Cur_Node_id_inOneType = Node_id_InOnetype;	//模型依附的节点在该协议类型的序号,用于配置文件设置
		Sns_Model_OSPFv2Obj->Cur_Node_Name = "Sns_Node_Virtual";		//模型依附的节点类名称,用于配置文件设置
		Sns_Model_OSPFv2Obj->ConfFile_Path = ConfFile_Path;		//协议配置文件路径

		Sns_Model_OSPFv2Obj->numberInterfaces=numberInterfaces;
		Sns_Model_OSPFv2Obj->interfaceInfo=interfaceInfo;
		Sns_Model_OSPFv2Obj->forwardingTable=&forwardingTable;

		if(i==0)
			Modelid_In_list[SNS_MODEL_OSPFV2] = modelist_id;		//模型在本节点model list中的起始位置

		Sns_Model_OSPFv2Obj->Model_init();

		modelist_id ++;				//调用协议初始化函数
	}

	Sns_Model_NetworkIP* Sns_Model_NetworkIPObj;
	for(i = 0; i< Num_ofThis.Num_Sns_Model_NetworkIP; i++)
	{
		Model_List[modelist_id] = new Sns_Model_NetworkIP();

		Sns_Model_NetworkIPObj = (Sns_Model_NetworkIP*)Model_List[modelist_id];

		Sns_Model_NetworkIPObj->Model_id = SNS_MODEL_NETWORKIP;			//初始化协议ID号，用于标识协议
		Sns_Model_NetworkIPObj->Scenarios_Data = (Sns_Scenarios *)Scenarios_Data; //实例化场景类
		Sns_Model_NetworkIPObj->Model_Instance_id = i;			//节点中该模型的实例标志,即本模型在该节点内n个实例中的第i个
		Sns_Model_NetworkIPObj->Cur_Node_id = Node_id;			//模型依附的节点ID
		Sns_Model_NetworkIPObj->Cur_Node_id_inOneType = Node_id_InOnetype;	//模型依附的节点在该协议类型的序号,用于配置文件设置
		Sns_Model_NetworkIPObj->Cur_Node_Name = "Sns_Node_Virtual";		//模型依附的节点类名称,用于配置文件设置
		Sns_Model_NetworkIPObj->ConfFile_Path = ConfFile_Path;		//协议配置文件路径

		Sns_Model_NetworkIPObj->numberInterfaces=numberInterfaces;
		Sns_Model_NetworkIPObj->interfaceInfo=interfaceInfo;
		Sns_Model_NetworkIPObj->forwardingTable=&forwardingTable;

		if(i==0)
			Modelid_In_list[SNS_MODEL_NETWORKIP] = modelist_id;		//模型在本节点model list中的起始位置

		Sns_Model_NetworkIPObj->Model_init();

		modelist_id ++;				//调用协议初始化函数
	}

	//Model_Initialization//
	
	/////////////////////初始化具体模型 end/////////////////////////////////
	
	////////////*模型导向自动生成 end*////////////////////////
}


//功能:节点初始化后的处理函数,用于有时需要所有节点都初始化完成才可执行的动作
void Sns_Node_Virtual::Node_init_end()
{
	////////////*模型导向自动生成*////////////////////////

	int i;
	short modelist_id = 0;
	
	Sns_Model_OSPFv2* Sns_Model_OSPFv2Obj;
	for(i = 0;i< Num_ofThis.Num_Sns_Model_OSPFv2; i++)
	{
		Sns_Model_OSPFv2Obj = (Sns_Model_OSPFv2*)Model_List[modelist_id];

		Sns_Model_OSPFv2Obj->Model_init_end();		//调用协议初始化结束处理函数

		modelist_id ++;
	}

	Sns_Model_NetworkIP* Sns_Model_NetworkIPObj;
	for(i = 0;i< Num_ofThis.Num_Sns_Model_NetworkIP; i++)
	{
		Sns_Model_NetworkIPObj = (Sns_Model_NetworkIP*)Model_List[modelist_id];

		Sns_Model_NetworkIPObj->Model_init_end();		//调用协议初始化结束处理函数

		modelist_id ++;
	}

	//Model_Init_end//

	////////////*模型导向自动生成 end*////////////////////////
	if(Node_id_InOnetype==5)
	{
		Send_Anew_Msg(Node_id,-1,0,0,0,NULL,0,SNS_ConvertToClock("30S"));
	}
	
}
///////////////////节点消息处理函数//////////////////////////////////////////
/*根据接收的消息,首先判断属于哪个模型（模型ID从1开始，表示本节点上依附模型，若为0，表示为节点本身）;
其次判断是出事件还是入事件，若是入事件，直接调用模型入事件处理函数，若是出事件，则处理*/
//本部分框架为模型导向自动生成

//功能:节点的消息处理函数,接收各类模型/节点输入输出事件,
//     对于模型输入消息,将消息发给模型;对于节点输入消息,触动相应函数并处理
//     对于输出消息,触动相应函数并处理
void Sns_Node_Virtual::SNS_Node_MsgDeal(Sns_Message *msg)
{
	short modelist_id;
	switch(msg->Model_id) 
	{
	case -1:                            //节点本身的输入事件消息
	{
		switch(msg->Event_Name) //消息事件枚举
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

		if (msg->Event_Type==SNS_MSG_INPUT)	//模型输入事件处理
		{
			Sns_Model_OSPFv2Obj->SNS_Model_MsgDeal(msg);
		}
		else			//模型输出处理事件
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

		if (msg->Event_Type==SNS_MSG_INPUT)	//模型输入事件处理
		{
			Sns_Model_NetworkIPObj->SNS_Model_MsgDeal(msg);
		}
		else			//模型输出处理事件
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
							Send_Aexisting_Msg(msg ,dstNodeId,SNS_MODEL_NETWORKIP,0,Sns_Model_NetworkIP::MSG_InEVENT_NETWORK_FromMAC,SNS_MSG_INPUT,0);//消息发送,假设时延为0
						}
// 						else if(isMyIMI(info->nexthopaddr))
// 						{
// 							int dstIMIId=getMyIMI(info->nexthopaddr);
// 
// 							printf( "Node_Id :%5d  downstream  to Node%5d \n", Node_id , dstIMIId ) ;
// 
// 							Send_Aexisting_Msg(msg ,dstIMIId,SNS_MODEL_NETWORKIP,0,Sns_Model_NetworkIP::MSG_InEVENT_NETWORK_FromMAC,SNS_MSG_INPUT,0);//消息发送,假设时延为0
// 						}
						else
						{
							char nextHopStr[SNS_MAX_STRING_LENGTH];
							convertIpAddressToString(info->nexthopaddr,nextHopStr);
							xdelete( msg ) ;
							///////////////////////////////////
							////////打印消息：
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
					char* packet=msg->Pay_Load;//获取包信息

					//包处理
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

////////////////////////////仿真结束处理函数//////////////////////////////////////////////
//功能:处理节点模型在仿真结束后的一些事,如节点模型仿真结果输出等
void Sns_Node_Virtual::SNS_Simulate_End_Node()
{
	////////////*模型导向自动生成*////////////////////////

	int i;
	short modelist_id = 0;

	SNS_Record_Stats_Value();
	
	Sns_Model_OSPFv2* Sns_Model_OSPFv2Obj;
	for(i = 0;i< Num_ofThis.Num_Sns_Model_OSPFv2; i++)
	{
		Sns_Model_OSPFv2Obj = (Sns_Model_OSPFv2*)Model_List[modelist_id];
		Sns_Model_OSPFv2Obj->StatsVar_Output = StatsVar_Output;		//将输出状态存储链表传递给模型
		Sns_Model_OSPFv2Obj->SNS_Simulate_End_Model();		//调用协议运行结束处理函数

		modelist_id ++;
	}

	Sns_Model_NetworkIP* Sns_Model_NetworkIPObj;
	for(i = 0;i< Num_ofThis.Num_Sns_Model_NetworkIP; i++)
	{
		Sns_Model_NetworkIPObj = (Sns_Model_NetworkIP*)Model_List[modelist_id];
		Sns_Model_NetworkIPObj->StatsVar_Output = StatsVar_Output;		//将输出状态存储链表传递给模型
		Sns_Model_NetworkIPObj->SNS_Simulate_End_Model();		//调用协议运行结束处理函数

		modelist_id ++;
	}

	//Node_Sim_end//

	////////////*模型导向自动生成 end*////////////////////////
}

//功能:记录本模型的输出状态变量值到StatsVar_Output内
void Sns_Node_Virtual::SNS_Record_Stats_Value()
{
	bool retVal = false;	//函数返回值
	char Stats_ModelName[SNS_MAX_STRING_LENGTH]; //用于记录输出状态变量所属模型名标志

	sprintf(Stats_ModelName,"\n** Sns_Node_Virtual[%d]_begin\n",Node_id_InOnetype);//本模型输出状态变量值记录开始
	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);//将Stats_ModelName写入链表

	/////////////////////////////将本模型所有输出状态变量值写入链表//////////////////////////

	//Stats_Variable_Record//
	/////////////////////////////将本模型所有输出状态变量值写入链表//////////////////////////

	sprintf(Stats_ModelName,"\n** Sns_Node_Virtual[%d]_end\n",Node_id_InOnetype);//本模型输出状态变量值记录结束
	StatsVar_Output->SNS_Read_Str_In(Stats_ModelName);//将Stats_ModelName写入链表
}

//功能:将一个消息转发给相应的模型
//输入:msg-转发的消息，DestiNode--接收消息目的节点地址,ModelId--接收消息的模型ID,instanceId--发起模型实例号,该值默认为0,EventName--接收消息事件名称,
//     EventType--接收事件类型,TimeDelay--发送延迟
void Sns_Node_Virtual::Send_Aexisting_Msg(Sns_Message *msg,int DestiNode,int ModelId,int instanceId,int EventName,int EventType, clocktype  TimeDelay)
{
	Sns_Scenarios *scenariosdata;

	scenariosdata = (Sns_Scenarios *)Scenarios_Data;

	msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,NULL,-1);//消息赋值

	scenariosdata->SNS_Msg_Send(msg,DestiNode,TimeDelay);//消息发送
}

//功能:发送一个新消息
//输入:DestiNode--消息目的节点地址,ModelId--发起消息的模型ID,instanceId--发起模型实例号,该值默认为0,EventName--消息事件名称,
//     EventType--事件类型,PayLoad--消息载荷,PacketSize--消息载荷大小,TimeDelay--发送延迟
//     发送空消息时，PayLoad=NULL，PacketSize=0
void Sns_Node_Virtual::Send_Anew_Msg(int DestiNode,int ModelId,int instanceId,int EventName,int EventType, char *PayLoad , int PacketSize , clocktype TimeDelay)
{
	Sns_Scenarios *scenariosdata;

	scenariosdata = (Sns_Scenarios *)Scenarios_Data;

	Sns_Message *msg = new Sns_Message();//声明一个消息对象

    msg->SNS_Msg_Assignment(ModelId,instanceId,EventName,EventType,PayLoad,PacketSize);//为消息赋值

	scenariosdata->SNS_Msg_Send(msg,DestiNode,TimeDelay);//发送消息
}


////////////////////////////////////节点消息处理函数////////////////////////////////////

//Sns_Msg_In_Func//



////////////////////////////////////节点消息处理函数 end////////////////////////////////////

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
	Sns_Model_NetworkIP::TransportToNetworkInfo *info = new Sns_Model_NetworkIP::TransportToNetworkInfo;//与IP层通信所需的附加信息
	info->destinationAddr = dstAddr;//目的地址
	info->priority = 0;//优先级
	info->Protocol_ToIP = Sns_Model_NetworkIP::PROTOCOL_PACKET;//包类型
	Sns_Message *msg = new Sns_Message();
	msg->SNS_Msg_AddInfo((char *)info, sizeof(Sns_Model_NetworkIP::TransportToNetworkInfo));
	msg->SNS_Msg_Assignment(SNS_MODEL_NETWORKIP,0,Sns_Model_NetworkIP::MSG_InEVENT_NETWORK_FromTransport,SNS_MSG_INPUT,packet,packetSize);
	//发送
	Send_Aexisting_Msg(msg,Node_id,SNS_MODEL_NETWORKIP,0,Sns_Model_NetworkIP::MSG_InEVENT_NETWORK_FromTransport,SNS_MSG_INPUT, delay);
	xdelete( info );
}