#pragma once


// CTollWindow �Ի���

class CTollWindow : public CDialogEx
{
	DECLARE_DYNAMIC(CTollWindow)

public:
	CTollWindow(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTollWindow();

// �Ի�������
	enum { IDD = IDD_CHARGEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
private:
	// ͨ�öԻ�������
	CFont m_fontDlgFont;
	// ͨ�öԻ��������С
	int m_nDlgFontSize;

private:
	// ��ʼ���ؼ�
	void InitCtrls(void);
	// ���öԻ�������
	void SetDlgFont(void);


private:
	CLabel m_lbCharge;
	CNumericEdit m_edCharge;

public:
	CString m_strCharge;
};
