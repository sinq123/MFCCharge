// ChangePasswordDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "ChangePasswordDlg.h"
#include "afxdialogex.h"


// CChangePasswordDlg 对话框

IMPLEMENT_DYNAMIC(CChangePasswordDlg, CDialog)

CChangePasswordDlg::CChangePasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangePasswordDlg::IDD, pParent)
{

}

CChangePasswordDlg::~CChangePasswordDlg()
{
}

void CChangePasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChangePasswordDlg, CDialog)
END_MESSAGE_MAP()


// CChangePasswordDlg 消息处理程序
