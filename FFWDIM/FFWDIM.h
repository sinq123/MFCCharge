
// FFWDIM.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

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
// �йش����ʵ�֣������ FFWDIM.cpp
//

class CFFWDIMApp : public CWinApp
{
public:
	CFFWDIMApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFFWDIMApp theApp;