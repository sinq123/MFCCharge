#pragma once


// CChangePasswordDlg �Ի���

class CChangePasswordDlg : public CDialog
{
	DECLARE_DYNAMIC(CChangePasswordDlg)

public:
	CChangePasswordDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChangePasswordDlg();

// �Ի�������
	enum { IDD = IDD_CHANGE_PASSWORD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
