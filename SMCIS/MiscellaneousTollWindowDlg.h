#pragma once


// CMiscellaneousTollWindowDlg 对话框

class CMiscellaneousTollWindowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMiscellaneousTollWindowDlg)

public:
	CMiscellaneousTollWindowDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMiscellaneousTollWindowDlg();

// 对话框数据
	enum { IDD = IDD_MISCELLANEOUS_TOLL_WINDOW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCbChargeItem();

private:
	// 收费项目
	CComboBox m_cbChargeItem;
	// 收费金额
	CNumericEdit m_edCharge;
	// 收费金额
	CNumericEdit m_edChargeNumber;

private:
	// 通用对话框字体
	CFont m_fontDlgFont;
	// 通用对话框字体大小
	int m_nDlgFontSize;

private:
	// 初始化控件
	void InitCtrls(void);
	// 设置对话框字体
	void SetDlgFont(void);
	// 初始化收费项目
	bool InitChargeItem(void);

	std::list<SMiscellaneous_Charges> m_lsMiscellaneous_Charges;
public:
	CString m_strCharge;
	CString m_strChargeItem;
	CString m_strChargeNumber;
	afx_msg void OnEnChangeEdChargeNumber();
};
