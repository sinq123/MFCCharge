#pragma once



// CChargeMaintenanceView ������ͼ

class CChargeMaintenanceView : public CFormView
{
	DECLARE_DYNCREATE(CChargeMaintenanceView)

protected:
	CChargeMaintenanceView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CChargeMaintenanceView();

public:
	enum { IDD = IDD_CHARGE_MAINTENANCE_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnChargeParameterMaintenance();
	DECLARE_MESSAGE_MAP()

private:
	CButtonST m_btnChargeParameterMaintenance;
	CButtonST m_btnMiscellaneousCharges;
	CButtonST m_btnChargeDetType;
	CButtonST m_btnPayeeMaintenance;
private:
	void InitCtrls();
	// ���öԻ�������
	void SetDlgFont(void);

private:
	// ͨ�öԻ�������
	CFont m_fontDlgFont;
	// ͨ�öԻ��������С
	int m_nDlgFontSize;

private:
	// �ؼ��洰�ڱ仯���仯
	// ��ӿؼ�ID
	void InitConInfo(void);
	void SetControlInfo(const WORD CtrlId);
	int m_old_cx;
	int m_old_cy;
	CDWordArray m_control_info;
	
	CPoint m_Old;//��ŶԻ���Ŀ�͸�

public:
	
	
	afx_msg void OnBnClickedBtnMiscellaneousCharges();
	afx_msg void OnBnClickedBtnChargeDetype();
	afx_msg void OnBnClickedBtnChargeUnitMaintain();
};


