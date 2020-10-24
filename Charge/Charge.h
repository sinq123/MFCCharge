
// Charge.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

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
// 有关此类的实现，请参阅 Charge.cpp
//

// 定义收费状态参数
const wchar_t * const DS_NoCharge = L"NOCHARGE";		  // 未收费
const wchar_t * const DS_Chargee = L"CHARGED";		  // 已收费
const wchar_t * const DS_Redo = L"REDO";			  // 重做
const wchar_t * const DS_CancelOfCharge = L"CANCELOFCHARGE";// 取消收费
const wchar_t * const DS_RevisionOfCharges = L"REVISIONOFCHARGES";//修改收费

class CChargeApp : public CWinApp
{
public:
	CChargeApp();

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
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
};

extern CChargeApp theApp;