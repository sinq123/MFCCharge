#pragma once



// CChargeMaintenanceView 窗体视图

class CChargeMaintenanceView : public CFormView
{
	DECLARE_DYNCREATE(CChargeMaintenanceView)

protected:
	CChargeMaintenanceView();           // 动态创建所使用的受保护的构造函数
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
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
	// 设置对话框字体
	void SetDlgFont(void);

private:
	// 通用对话框字体
	CFont m_fontDlgFont;
	// 通用对话框字体大小
	int m_nDlgFontSize;

private:
	// 控件随窗口变化而变化
	// 添加控件ID
	void InitConInfo(void);
	void SetControlInfo(const WORD CtrlId);
	int m_old_cx;
	int m_old_cy;
	CDWordArray m_control_info;
	
	CPoint m_Old;//存放对话框的宽和高

public:
	
	
	afx_msg void OnBnClickedBtnMiscellaneousCharges();
	afx_msg void OnBnClickedBtnChargeDetype();
	afx_msg void OnBnClickedBtnChargeUnitMaintain();
};


