
// FFWDIM.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

#include "..\CerVerInfo\CerVerInfo.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\CerVerInfo_D.lib")
#else
#pragma comment(lib, "..\\Release\\CerVerInfo.lib")
#endif

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

// CFFWDIMApp:
// 有关此类的实现，请参阅 FFWDIM.cpp
//

class CFFWDIMApp : public CWinApp
{
public:
	CFFWDIMApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CFFWDIMApp theApp;