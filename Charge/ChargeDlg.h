
// ChargeDlg.h : ͷ�ļ�
//

#pragma once
#include "ToolTipListCtrl.h"

// CChargeDlg �Ի���
class CChargeDlg : public CDialogEx
{
// ����
public:
	CChargeDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CChargeDlg();

// �Ի�������
	enum { IDD = IDD_CHARGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnChangeEdNochargeFilter();
	afx_msg void OnEnChangeEdChargeFilter();
	afx_msg void OnBnClickedBtnCharges();
	afx_msg void OnLvnItemchangedLstDetNocharge(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnModifychargeamount();
	afx_msg void OnBnClickedBtnDeletecharge();
	afx_msg void OnBnClickedBtnChargestatistics();
private:
	// ��־��������
	CRichEditCtrl m_reLog;
	void PrintLog(LPCTSTR szFormat, ...);

private:
	// ��ȡ���ò���
	void GetConfig(void);
	// ��ʼ����ť����
	void InitCtrls(void);

private:
	// ��ȡ�ϻ������¼������Ϣ�����޸ļ��״̬
	void LogVehInfoToDetSta(void);

private:
	RECT m_rtLastClientRect;

private:
	// ���ҵ���б�ToolTip�ص�����
	static void __stdcall DetBsnToolTipCallBack(const CStringW &strRunNum, const int nRow, const int nCol,  CStringW &strToolTipText);

private:
	// ����ҵ��
	CToolTipListCtrl m_lstDetBsnNoCharge;
	CToolTipListCtrl m_lstDetBsnCharge;
	// ���ƺ���
	CEdit m_edNoChargeFilter;
	CEdit m_edChargeFilter;
	// ��ʼ�����ҵ���б�
	void InitDetBsnList(void);
	// ���¼��ҵ���б�
	void UpdateDetBsnList(void);

private:
	// �շ�
	CButtonST m_btnCharges;
	// ��ѯ�Ƿ�����ͬ���������
	// ��ѯCharge ��ѯ������True�� δ��ѯ����False;
	bool QuerySameVehinfo(const CString& strPlateNumber);
	// ������Charge����
	// strRunNum ��־���
	// strMsg ����ʧ����Ϣ
	// bBackOff �Ƿ��˰�������
	bool SaveDetLogToCharge(const CString& strRunNum, CString& strMsg, const bool& bBackOff=false);
	// �޸�Detlog״̬
	// strRunNum ��־���
	// strMsg ����ʧ����Ϣ
	bool ModifyStateDetLog(const CString& strRunNum, CString& strMsg, const CString& strState=L"TODET");

private:
	// �޸��շѽ��
	bool ModifyChargeAmount(CString& strMsg);

private:
	// ȡ���շ�
	bool CancelOfCharge(CString& strMsg);

private:
	friend class CVehCountStatDlg;
};
