
// PDAOnLine.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

#include "..\NHMFDServerDBDAL\NHMFDServerDBDAL.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHMFDServerDBDAL_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHMFDServerDBDAL.lib")
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

#include "..\NHDetCommModu\NHDetCommModu.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHDetCommModu_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHDetCommModu.lib")
#endif


// CPDAOnLineApp:
// 有关此类的实现，请参阅 PDAOnLine.cpp
//

class CPDAOnLineApp : public CWinApp
{
public:
	CPDAOnLineApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()

public:
	// 列表控件字体大小
	int m_nListCtrlSize;
	// 列表行高
	int m_nListRowHeight;
	// 位图列表，用于设置列表行高
	CImageList m_ilRowHeight;
	// 列表控件字体，所有列表控件尽量使用此字体
	CFont m_fontListCtrl;
};

extern CPDAOnLineApp theApp;