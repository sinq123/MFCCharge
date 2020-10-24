#pragma once


// CTollWindow 对话框

class CTollWindow : public CDialogEx
{
	DECLARE_DYNAMIC(CTollWindow)

public:
	CTollWindow(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTollWindow();

// 对话框数据
	enum { IDD = IDD_CHARGEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
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


private:
	CLabel m_lbCharge;
	CNumericEdit m_edCharge;

public:
	CString m_strCharge;
};
