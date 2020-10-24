#pragma once
#include "ToolTipListCtrl.h"

// CChargeMaintenanceDlg �Ի���

class CChargeMaintenanceDlg : public CDialog
{
	DECLARE_DYNAMIC(CChargeMaintenanceDlg)

public:
	CChargeMaintenanceDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChargeMaintenanceDlg();

// �Ի�������
	enum { IDD = IDD_CHARGE_MAINTENANCE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
	// ��ʼ��������
	void InitDetType(void);
	// ���öԻ�������
	void SetDlgFont(void);
	void UpdateDataInfoLst();
	bool GetCtrlValue(CString& strDetType, CString& strDetTypeCode, CString& strAmountOfCharge, CString& strTypeOfCharge);
	// ��տؼ�
	void ClearCtrls();
	
private:
	// ͨ�öԻ�������
	CFont m_fontDlgFont;
	// ͨ�öԻ��������С
	int m_nDlgFontSize;

	// ������
	std::list<SCharge_DetType> m_lsDetType;

};
