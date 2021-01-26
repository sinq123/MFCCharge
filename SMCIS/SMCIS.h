
// SMCIS.h : SMCIS Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

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

#include "..\NHModeServerDBDAL\NHModeServerDBDAL.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHModeServerDBDAL_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHModeServerDBDAL.lib")
#endif

#include "..\NHNetLib\NHNetLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\MYNetLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\MYNetLib.lib")
#endif

#include "..\NHDetCommModu\NHDetCommModu.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHDetCommModu_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHDetCommModu.lib")
#endif
//
//#include "..\ACPDADB\PDADBDAL.h"
//#ifdef _DEBUG
//#pragma comment(lib, "..\\Debug\\ACPDADB_D.lib")
//#else
//#pragma comment(lib, "..\\Release\\ACPDADB.lib")
//#endif

#include "..\WebSerLib\GAWebServiceLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\WebSerLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\WebSerLib.lib")
#endif

#include "..\ACPostGetLib\ACPostGetLib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\ACPostGetLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\ACPostGetLib.lib")
#endif

// CSMCISApp:
// �йش����ʵ�֣������ SMCIS.cpp
//

// �����շ�״̬����
const wchar_t * const DS_NoCharge = L"NOCHARGE";		  // δ�շ�
const wchar_t * const DS_Chargee = L"CHARGED";		  // ���շ�
const wchar_t * const DS_Redo = L"REDO";			  // ����
const wchar_t * const DS_CancelOfCharge = L"CANCELOFCHARGE";// ȡ���շ�
const wchar_t * const DS_RevisionOfCharges = L"REVISIONOFCHARGES";//�޸��շ�

class CSMCISApp : public CWinAppEx
{
public:
	CSMCISApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
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

public:
	// ��ȡԱ����Ϣ
	SToll_Operator m_sToll_Operator;

public:
	// ������־�ļ�
	void GenLogFile(void);
	CStringW m_strLogFilePath;
	CStringW m_strSQLLogFilePath;
public:
	// �շ�
	CMultiDocTemplate* m_pChargeInfoView;
	// ��Ա����
	CMultiDocTemplate* m_pStaffManagement;
	// �շ�ά��
	CMultiDocTemplate* m_pChargeMaintenance;
	// ͳ��
	CMultiDocTemplate* m_pDetCountStatView;
	// ͳ�ƣ����
	CMultiDocTemplate* m_pFeeTablesView;
	// ͳ��
	CMultiDocTemplate* m_pDetCountStatView2;
	// �շ���־��ѯ
	CMultiDocTemplate* m_pChargeLogMgntView;
	//�����տ�
	CMultiDocTemplate* m_pBookkeepingCollectionView;
};

extern CSMCISApp theApp;
