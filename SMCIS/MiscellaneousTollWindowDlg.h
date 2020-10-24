#pragma once


// CMiscellaneousTollWindowDlg �Ի���

class CMiscellaneousTollWindowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMiscellaneousTollWindowDlg)

public:
	CMiscellaneousTollWindowDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMiscellaneousTollWindowDlg();

// �Ի�������
	enum { IDD = IDD_MISCELLANEOUS_TOLL_WINDOW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCbChargeItem();

private:
	// �շ���Ŀ
	CComboBox m_cbChargeItem;
	// �շѽ��
	CNumericEdit m_edCharge;
	// �շѽ��
	CNumericEdit m_edChargeNumber;

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
	// ��ʼ���շ���Ŀ
	bool InitChargeItem(void);

	std::list<SMiscellaneous_Charges> m_lsMiscellaneous_Charges;
public:
	CString m_strCharge;
	CString m_strChargeItem;
	CString m_strChargeNumber;
	afx_msg void OnEnChangeEdChargeNumber();
};
