#pragma once
#include "ToolTipListCtrl.h"

// CPayeeMaintenanceDlg 对话框

class CPayeeMaintenanceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPayeeMaintenanceDlg)

public:
	CPayeeMaintenanceDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPayeeMaintenanceDlg();

// 对话框数据
	enum { IDD = IDD_CHARGE_UNIT_MAINTAIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnDataAdd();
	afx_msg void OnBnClickedBtnDataMod();
	afx_msg void OnBnClickedBtnDataDel();
	afx_msg void OnBnClickedBtnDataUpdate();
	afx_msg void OnLvnItemchangedLsDataInfo(NMHDR *pNMHDR, LRESULT *pResult);

public:
	CString m_strTitle;

private:
	CNumericEdit m_edAmountOfArrears;
	CEdit m_edUnit_Name;
	CEdit m_edUnit_Code;
	CEdit m_edTaxpayerIdentificattonNumber;
	CEdit m_edUnit_Address;
	CEdit m_edUnit_Phone;

	CToolTipListCtrl m_lsDataInfo;
	CButtonST m_btnDataAdd;
	CButtonST m_btnDataMod;
	CButtonST m_btnDataDel;
	CButtonST m_btnDataUpdate;

private:
	// 通用对话框字体
	CFont m_fontDlgFont;
	// 通用对话框字体大小
	int m_nDlgFontSize;

private:
	void InitDataInfoLst();
	void InitCtrl();
	// 设置对话框字体
	void SetDlgFont(void);
	void UpdateDataInfoLst();
	// 清空控件
	void ClearCtrls();

private:
	// 检测输入是否合理
	bool GetCtrlValue(CString& strUnit_Name, CString& strUnit_Code, CString& strTaxpayerIdentificattonNumber, CString& strUnit_Address
		, CString& strUnit_Phone, CString& strAmountOfArrears);
public:
	
};
