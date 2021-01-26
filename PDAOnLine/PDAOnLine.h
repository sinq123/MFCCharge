
// PDAOnLine.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

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
// �йش����ʵ�֣������ PDAOnLine.cpp
//

class CPDAOnLineApp : public CWinApp
{
public:
	CPDAOnLineApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

public:
	// �б�ؼ������С
	int m_nListCtrlSize;
	// �б��и�
	int m_nListRowHeight;
	// λͼ�б����������б��и�
	CImageList m_ilRowHeight;
	// �б�ؼ����壬�����б�ؼ�����ʹ�ô�����
	CFont m_fontListCtrl;
};

extern CPDAOnLineApp theApp;