#pragma once

#include "ToolTipListCtrl.h"
// CMiscellaneousChargesDlg �Ի���

class CMiscellaneousChargesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMiscellaneousChargesDlg)

public:
	CMiscellaneousChargesDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMiscellaneousChargesDlg();

// �Ի�������
	enum { IDD = IDD_MISCELLANEOUS_CHARGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	// ���öԻ�������
	void SetDlgFont(void);
	void UpdateDataInfoLst();
	bool GetCtrlValue(CString& strAmountOfCharge, CString& strTypeOfCharge);
	// ��տؼ�
	void ClearCtrls();
	
private:
	// ͨ�öԻ�������
	CFont m_fontDlgFont;
	// ͨ�öԻ��������С
	int m_nDlgFontSize;

};
