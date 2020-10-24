#pragma once


// CChangePasswordDlg 对话框

class CChangePasswordDlg : public CDialog
{
	DECLARE_DYNAMIC(CChangePasswordDlg)

public:
	CChangePasswordDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChangePasswordDlg();

// 对话框数据
	enum { IDD = IDD_CHANGE_PASSWORD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
