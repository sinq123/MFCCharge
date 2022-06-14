// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A42990E7_D06C_4F9F_BA2E_5A2CEFE35AB1__INCLUDED_)
#define AFX_STDAFX_H__A42990E7_D06C_4F9F_BA2E_5A2CEFE35AB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "include/dhnetsdk.h"
#include "include/dhconfigsdk.h"
#pragma comment(lib, "include/dhnetsdk.lib")
#pragma comment(lib, "include/dhconfigsdk.lib")

///////////////////////////////////////////////////////
// �궨��
#define SAFE_DELETE(p) if(0!=p) {delete p;p=0;}
#define SAFE_DELETE_A(p) if(0!=p) {delete[] p;p=0;}

///////////////////////////////////////////////////////
// ȥ��STL����
#pragma warning(disable:4786)// ��ʶ�����ȳ���256���ַ�

///////////////////////////////////////////////////////
// ȫ�ֺ���
void ClearComboBox(CComboBox &stComboBox);

CString ConvertString(CString strText);

void g_SetWndStaticText(CWnd * pWnd);

#define AfxMessageBox(S) ::MessageBox(NULL, S,ConvertString("Prompt"), 0);

#include "vld/vld.h"

// ��ö������䶯����dhnetsdk.h��ҲӦ����Ӧ�䶯 linjy-2006-12-16
enum DhServerType
{
	DH_PRODUCT_NONE = 0,
		DH_DVR_NONREALTIME_MACE,	// ��ʵʱMACE
		DH_DVR_NONREALTIME,			// ��ʵʱ
		DH_NVS_MPEG1,				// ������Ƶ������
		DH_DVR_MPEG1_2,				// MPEG1��·¼���
		DH_DVR_MPEG1_8,				// MPEG1��·¼���
		DH_DVR_MPEG4_8,				// MPEG4��·¼���
		DH_DVR_MPEG4_16,			// MPEG4ʮ��·¼���
		DH_DVR_MPEG4_SX2,			// MPEG4����ʮ��·¼���
		DH_DVR_MEPG4_ST2,			// MPEG4��ͨ¼���
		DH_DVR_MEPG4_SH2,			// MPEG4�Ӻ�¼���
		DH_DVR_MPEG4_GBE,			// MPEG4��ͨ������ǿ��¼���
		DH_DVR_MPEG4_NVSII,			// MPEG4������Ƶ������II��
		DH_DVR_STD_NEW,				// �±�׼����Э��
		DH_DVR_DDNS,				// DDNS������
		DH_DVR_ATM,					// ATM��
		DH_NB_SERIAL,				// ������ʵʱNBϵ�л���
		DH_LN_SERIAL,				// LNϵ�в�Ʒ
		DH_BAV_SERIAL,				// BAVϵ�в�Ʒ
		DH_SDIP_SERIAL,				// SDIPϵ�в�Ʒ
		DH_IPC_SERIAL,				// IPCϵ�в�Ʒ
		DH_NVS_B,					// NVS Bϵ��
		DH_NVS_C,					// NVS Hϵ��
		DH_NVS_S,					// NVS Sϵ��
		DH_NVS_E,					// NVS Eϵ��
		DH_DVR_NEW_PROTOCOL,		// ��Э��
		DH_NVD_SERIAL,				// ������
		DH_DVR_N5,					// N5
		DH_DVR_MIX_DVR,				// ���DVR
		DH_SVR_SERIAL,				// SVR
		DH_SVR_BS,					// SVR-BS
		DH_NVR_SERIAL,				// NVR
		DH_DVR_N51,                 // N51
		DH_ITSE_SERIAL,				// ITSE ���ܷ�����
		DH_ITC_SERIAL,              // ���ܽ�ͨ����豸
		DH_ITC_HWS,                 // �״������HWS
		DH_PVR_SERIAL,              // ��Яʽ����Ƶ¼���
		DH_IVS_SERIAL,              // IVS��������Ƶ������ϵ�У�
		DH_IVS_B,                   // ͨ��������Ƶ��������
		DH_IVS_F,                   // ����ʶ�������
		DH_IVS_V,                   // ��Ƶ������Ϸ�����	
		DH_MATRIX_SERIAL,			// ����
		DH_DVR_N52,					// N52
		DH_DVR_N56,                 // n56
		DH_ESS_SERIAL,              // ESS
		DH_IVS_PC,                  // ���ܽ�ͨ����ͳ�Ʒ�����
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A42990E7_D06C_4F9F_BA2E_5A2CEFE35AB1__INCLUDED_)
