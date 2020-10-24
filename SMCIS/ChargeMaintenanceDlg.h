#pragma once
#include "ToolTipListCtrl.h"

// CChargeMaintenanceDlg 对话框

class CChargeMaintenanceDlg : public CDialog
{
	DECLARE_DYNAMIC(CChargeMaintenanceDlg)

public:
	CChargeMaintenanceDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChargeMaintenanceDlg();

// 对话框数据
	enum { IDD = IDD_CHARGE_MAINTENANCE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual	 BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedLsDataInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnDataAdd();
	afx_msg void OnBnClickedBtnDataMod();
	afx_msg void OnBnClickedBtnDataDel();
	afx_msg void OnBnClickedBtnDataUpdate();
	afx_msg void OnCbnSelchangeCbDettype();
	afx_msg void OnCbnSelchangeCbDettypecode();
	DECLARE_MESSAGE_MAP()

public:
	CString m_strTitle;

private:
	//
	CComboBox m_cbDetType;
	CComboBox m_cbDetTypeCode;

	CNumericEdit m_edAmountOfCharge;
	CEdit m_edTypeOfCharge;

	CToolTipListCtrl m_lsDataInfo;
	CButtonST m_btnDataAdd;
	CButtonST m_btnDataMod;
	CButtonST m_btnDataDel;
	CButtonST m_btnDataUpdate;
private:
	void InitDataInfoLst();
	void InitCtrl();
	// 初始化检测类别
	void InitDetType(void);
	// 设置对话框字体
	void SetDlgFont(void);
	void UpdateDataInfoLst();
	bool GetCtrlValue(CString& strDetType, CString& strDetTypeCode, CString& strAmountOfCharge, CString& strTypeOfCharge);
	// 清空控件
	void ClearCtrls();
	
private:
	// 通用对话框字体
	CFont m_fontDlgFont;
	// 通用对话框字体大小
	int m_nDlgFontSize;

	// 检测类别
	std::list<SCharge_DetType> m_lsDetType;

};
