#pragma once

#include "ToolTipListCtrl.h"

// CChargeInfoView ������ͼ
enum DropWhy
{
	DDT_Charge = 0,		// �շ�
	DDT_Cancels,		// ȡ��
	DDT_Modifies,		// �޸�
	DDTWrongChoice,		// ѡ��
};

class CChargeInfoView : public CFormView
{
	DECLARE_DYNCREATE(CChargeInfoView)

protected:
	CChargeInfoView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CChargeInfoView();

public:
	enum { IDD = IDD_CHARGE_INFO_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnCharges();
	afx_msg void OnBnClickedBtnModifychargeamount();
	afx_msg void OnBnClickedBtnDeletecharge();
	afx_msg void OnBnClickedBtnWrongandreturn();
	afx_msg void OnLvnItemchangedLstDetNocharge(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedLstDetCharge(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnMicellaneous();
private:
	// ����ҵ��
	CToolTipListCtrl m_lstDetBsnNoCharge;
	CToolTipListCtrl m_lstDetBsnCharge;
	// ���ƺ���
	CEdit m_edNoChargeFilter;
	CEdit m_edChargeFilter;
	// ��ʼʱ��
	CDateTimeCtrl m_dtcNoChargeStartTime;
	CDateTimeCtrl m_dtcChargeStartTime;
	// ����ʱ��
	CDateTimeCtrl m_dtcNoChargeCondEndTime;
	CDateTimeCtrl m_dtcChargeCondEndTime;
	// ������
	CEdit m_edNoChargeOwner;
	CEdit m_edChargeOwner;
	// ��������
	CComboBox m_cbNoChargePlateType;
	CComboBox m_cbChargePlateType;
	// ��������
	CComboBox m_cbNoChargeVehType;
	CComboBox m_cbChargeVehType;
	// �շѽ��
	CEdit m_edChargeChargeAmount;
	// �ܽ��
	CLabel m_lbTotalAmount;
	// ��־
	CRichEditCtrl m_reLog;
	// �շ�
	CButtonST m_btnCharges;
	// �޸��շѽ��
	CButtonST m_btnModifyChargeAmount;
	// ȡ���շ�
	CButtonST m_btnDeleteCharge;
	// ѡ���˻�
	CButtonST m_btnWrongAndRetturn;
	// �����շ�
	CButtonST m_btnMiscellaneousCharges;
	// ɾ����¼
	CButtonST m_btnDeleteRecord;
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
	// ��ʼ�����ҵ���б�
	void InitDetBsnList(void);

private:
	// �ؼ��洰�ڱ仯���仯
	//// ��ӿؼ�ID
	//void InitConInfo(void);
	//void SetControlInfo(const WORD CtrlId);
	//int m_old_cx;
	//int m_old_cy;
	//CDWordArray m_control_info;
	CPoint m_Old;//��ŶԻ���Ŀ�͸�

private:
	// ��ʱ�����б�Ϊδѡ��
	bool m_bListAsUnselected;

private:
	// ��������
	std::list<SVeh_PlateType> m_lsVeh_PlateType;
	// ��������
	std::list<SVeh_VehType> m_lsVeh_VehType;
	// ��ʼ����������
	bool InitPlateType(void);
	// ��ʼ����������
	bool InitVehType(void);

private:
	// ������¼
	void PrintLog(LPCTSTR szFormat, ...);

private:
	// ����
	// δ�շ��б�
	void NoChargeUpdateDetBsnList(void);
	// ���շ��б�
	void ChargeUpdateDetBsnList(void);

private:
	bool SaveToCharge(const CString& strChargeItem, const CString& strCharge, const CString& strWhy, const CString& strIsArrears, const CString& strUnitName);
	// �޸�Detlog״̬
	// strRunNum ��־���
	// strMsg ����ʧ����Ϣ
	bool ModifyStateDetLog(const CString& strRunNum, const CString& strState=L"TODET");
	// ɾ���շѼ�¼
	bool DeteleToCharge(const  CString& strRunNum);

private:
	// �޸��շѽ��
	bool ModifyChargeAmount(const CString& strChargeItem, const CString& strCharge, const CString& strWhy);
	// ȡ���շ�
	bool CancelOfCharge(const CString& strWhy);

private:
	// �ж��Ƿ�ȫ����Ŀ������
	CString IsBsnFined(const std::wstring& strRunNum);

public:
	afx_msg void OnBnClickedBtnDeleteRecord();
	bool VerifyEmpPerm(const SToll_Operator& sToll_Operator);

private:
	// Ƿ���
	// strUnitName Ƿ�λ
	// strCharge Ƿ��(�շ�)���
	bool SaveArrearsToDB(const CString& strUnitName, const CString& strCharge);
};


