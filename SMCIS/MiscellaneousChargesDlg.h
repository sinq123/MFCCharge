#pragma once

#include "ToolTipListCtrl.h"
// CMiscellaneousChargesDlg 对话框

class CMiscellaneousChargesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMiscellaneousChargesDlg)

public:
	CMiscellaneousChargesDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMiscellaneousChargesDlg();

// 对话框数据
	enum { IDD = IDD_MISCELLANEOUS_CHARGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnDataAdd();
	afx_msg void OnBnClickedBtnDataMod();
	afx_msg void OnBnClickedBtnDataDel();
	afx_msg void OnBnClickedBtnDataUpdate();
	afx_msg void OnLvnItemchangedLsDataInfo(NMHDR *pNMHDR, LRESULT *pResult);

private:
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
	// 设置对话框字体
	void SetDlgFont(void);
	void UpdateDataInfoLst();
	bool GetCtrlValue(CString& strAmountOfCharge, CString& strTypeOfCharge);
	// 清空控件
	void ClearCtrls();
	
private:
	// 通用对话框字体
	CFont m_fontDlgFont;
	// 通用对话框字体大小
	int m_nDlgFontSize;

};
