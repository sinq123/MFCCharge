
// Charge.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

#include "..\NHMFDServerDBDAL\NHMFDServerDBDAL.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHMFDServerDBDAL_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHMFDServerDBDAL.lib")
#endif

#include "..\NHLib\NHLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHLib.lib")
#endif

#include "..\NHModeServerDBDAL\NHModeServerDBDAL.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHModeServerDBDAL_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHModeServerDBDAL.lib")
#endif

#include "..\NHNetLib\NHNetLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHNetLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHNetLib.lib")
#endif

// CChargeApp:
// �йش����ʵ�֣������ Charge.cpp
//

// �����շ�״̬����
const wchar_t * const DS_NoCharge = L"NOCHARGE";		  // δ�շ�
const wchar_t * const DS_Chargee = L"CHARGED";		  // ���շ�
const wchar_t * const DS_Redo = L"REDO";			  // ����
const wchar_t * const DS_CancelOfCharge = L"CANCELOFCHARGE";// ȡ���շ�
const wchar_t * const DS_RevisionOfCharges = L"REVISIONOFCHARGES";//�޸��շ�

class CChargeApp : public CWinApp
{
public:
	CChargeApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
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

public:
	// �������ݿ�
	// ���ݿ��Ƿ����ӳɹ�
	bool m_bConnectDB;
	// ���ݿ�����
	_ConnectionPtr m_pConnection;
	// ����Դ
	CString m_strDataSource;
	// ���ݿ�����
	CString m_strInitialCatalog;
	// �û���
	CString m_strUserID;
	// ����
	CString m_strPassword;
	// �����ݿ�
	void OpenDB(void);
	// �ر����ݿ�
	void CloseDB(void);

public:
	// ��ȡ���ò���
	void GetConfig(void);
};

extern CChargeApp theApp;