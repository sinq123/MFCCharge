#pragma once
#include "afxwin.h"
#include "ChargeInfoView.h"

// CTollWindowDlg 对话框

class CTollWindowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTollWindowDlg)

public:
	CTollWindowDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTollWindowDlg();

// 对话框数据
	enum { IDD = IDD_TOLL_WINDOW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CString m_strDetType;
	DropWhy m_nDDT;
	// 收费项目
	std::list<SFee_Item> m_lsSFee_Items;

	CString m_strCharge;
	CString m_strWhy;
	CString m_strChargeItem;

	// 是否欠费
	CString m_strIsArrears;
	// 欠费单位
	CString m_strUnitName;
private:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCbChargeItem();
	afx_msg void OnBnClickedBtnExpressCharge1();
	afx_msg void OnBnClickedBtnExpressCharge2();
	afx_msg void OnBnClickedBtnExpressCharge3();
	afx_msg void OnBnClickedBtnExpressCharge4();

private:
	// 收费项目
	CLabel m_lbChargeItem;
	CComboBox m_cbChargeItem;
	// 收费金额
	CLabel m_lbCharge;
	CNumericEdit m_edCharge;
	// 原因
	CEdit m_edWhy;
	CLabel m_lbWhy;

	//
	CButtonST m_btnExpressCharge1;
	CButtonST m_btnExpressCharge2;
	CButtonST m_btnExpressCharge3;
	CButtonST m_btnExpressCharge4;

	CComboBox m_chUnitName;
	CButtonST m_chkIsArrears;
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

	bool VerifyEmpPerm(const SToll_Operator& sToll_Operator);
public:
	afx_msg void OnBnClickedCkIsArrears();
};
