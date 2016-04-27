/*
* Copyright (c) 2014,北京航空航天大学
* All rights reserved.
*
* 系统名称: SPACE NETWORK SIMULATION SYSTEM
* 作    者: 张涛
* 当前版本: SNS 1.0
* 
* 文件名称: Sim_Model.cpp
* 当前版本: V 1.0.0
* 文件标识: 工程运行入口main()函数
* 功能描述: 为模型开发测试提供依附节点的支持
* 完 成 人: 
* 联系方式: 
* 完成日期: 
*
* 摘    要:
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

	ScenariosData->SNS_Init();			//运行环境初始化	
	ScenariosData->SNS_Simulate_Run();	//仿真事件处理函数
	ScenariosData->SNS_Simulate_End();	//仿真结束后相关动作处理
	system("pause");
}
