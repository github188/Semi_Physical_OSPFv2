/*
* Copyright (c) 2014,�������պ����ѧ
* All rights reserved.
*
* ϵͳ����: SPACE NETWORK SIMULATION SYSTEM
* ��    ��: ����
* ��ǰ�汾: SNS 1.0
* 
* �ļ�����: Sim_Model.cpp
* ��ǰ�汾: V 1.0.0
* �ļ���ʶ: �����������main()����
* ��������: ΪЭ��/����ģ�Ϳ��������ṩ�����ڵ��֧��
* �� �� ��: 
* ��ϵ��ʽ: 
* �������: 
*
* ժ    Ҫ:
*/
//////////////////////////////////////////////////////////////////////



#include "stdafx.h"
#include <malloc.h>
#include <TIME.H>
#include "Sns_Scenarios.h"

static void Sns_main();

int main(int argc, char* argv[])
{

	Sns_main();

	return 0;
}

void Sns_main()
{
	Sns_Scenarios *ScenariosData;
	ScenariosData = new Sns_Scenarios();

	ScenariosData->SNS_Init();			//���л�����ʼ��	
	ScenariosData->SNS_Simulate_Run();	//�����¼�������
	ScenariosData->SNS_Simulate_End();	//�����������ض�������
	system("pause");
}
