
// TakeAndUp.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "UpGaDefinition.h"


#include "..\NHLib\NHLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\MYLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\MYLib.lib")
#endif

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

#include "..\GAVideoSnapLib\GAVideoSnapLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\HKVidSnLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\HKVidSnLib.lib")
#endif

#include "..\GAInterfaceLib_V1.0\GAInterfaceLib_V1.0.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\GAInterfaceLib_V1.0_D.lib")
#else
#pragma comment(lib, "..\\Release\\GAInterfaceLib_V1.0.lib")
#endif

#include "..\GAInterfaceLib_V2.0\GAInterfaceLib_V2.0.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\GAInterfaceLib_V2.0_D.lib")
#else
#pragma comment(lib, "..\\Release\\GAInterfaceLib_V2.0.lib")
#endif

#include "..\GAInterfaceLib_V3.0\GAInterfaceLib_V3.0.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\GAInterfaceLib_V3.0_D.lib")
#else
#pragma comment(lib, "..\\Release\\GAInterfaceLib_V3.0.lib")
#endif

// CTakeAndUpApp:
// 有关此类的实现，请参阅 TakeAndUp.cpp
//

class CTakeAndUpApp : public CWinApp
{
public:
	CTakeAndUpApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CTakeAndUpApp theApp;