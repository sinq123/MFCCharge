
// SMCIS.h : SMCIS 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号

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
// 有关此类的实现，请参阅 SMCIS.cpp
//

// 定义收费状态参数
const wchar_t * const DS_NoCharge = L"NOCHARGE";		  // 未收费
const wchar_t * const DS_Chargee = L"CHARGED";		  // 已收费
const wchar_t * const DS_Redo = L"REDO";			  // 重做
const wchar_t * const DS_CancelOfCharge = L"CANCELOFCHARGE";// 取消收费
const wchar_t * const DS_RevisionOfCharges = L"REVISIONOFCHARGES";//修改收费

class CSMCISApp : public CWinAppEx
{
public:
	CSMCISApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
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

public:
	// 操作数据库
	// 数据库是否连接成功
	bool m_bConnectDB;
	// 数据库连接
	_ConnectionPtr m_pConnection;
	// 数据源
	CString m_strDataSource;
	// 数据库名称
	CString m_strInitialCatalog;
	// 用户名
	CString m_strUserID;
	// 密码
	CString m_strPassword;
	// 打开数据库
	void OpenDB(void);
	// 关闭数据库
	void CloseDB(void);

public:
	// 获取配置参数
	void GetConfig(void);

public:
	// 获取员工信息
	SToll_Operator m_sToll_Operator;

public:
	// 生成日志文件
	void GenLogFile(void);
	CStringW m_strLogFilePath;
	CStringW m_strSQLLogFilePath;
public:
	// 收费
	CMultiDocTemplate* m_pChargeInfoView;
	// 人员管理
	CMultiDocTemplate* m_pStaffManagement;
	// 收费维护
	CMultiDocTemplate* m_pChargeMaintenance;
	// 统计
	CMultiDocTemplate* m_pDetCountStatView;
	// 统计（表格）
	CMultiDocTemplate* m_pFeeTablesView;
	// 统计
	CMultiDocTemplate* m_pDetCountStatView2;
	// 收费日志查询
	CMultiDocTemplate* m_pChargeLogMgntView;
	//记账收款
	CMultiDocTemplate* m_pBookkeepingCollectionView;
};

extern CSMCISApp theApp;
