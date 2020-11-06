#pragma once
#include "afxwin.h"
#include "ChargeInfoView.h"

// CTollWindowDlg �Ի���

class CTollWindowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTollWindowDlg)

public:
	CTollWindowDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTollWindowDlg();

// �Ի�������
	enum { IDD = IDD_TOLL_WINDOW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	CString m_strDetType;
	DropWhy m_nDDT;
	// �շ���Ŀ
	std::list<SFee_Item> m_lsSFee_Items;

	CString m_strCharge;
	CString m_strWhy;
	CString m_strChargeItem;

	// �Ƿ�Ƿ��
	CString m_strIsArrears;
	// Ƿ�ѵ�λ
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
	// �շ���Ŀ
	CLabel m_lbChargeItem;
	CComboBox m_cbChargeItem;
	// �շѽ��
	CLabel m_lbCharge;
	CNumericEdit m_edCharge;
	// ԭ��
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

	bool VerifyEmpPerm(const SToll_Operator& sToll_Operator);
public:
	afx_msg void OnBnClickedCkIsArrears();
};
