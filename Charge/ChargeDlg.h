
// ChargeDlg.h : 头文件
//

#pragma once
#include "ToolTipListCtrl.h"

// CChargeDlg 对话框
class CChargeDlg : public CDialogEx
{
// 构造
public:
	CChargeDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CChargeDlg();

// 对话框数据
	enum { IDD = IDD_CHARGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	// 日志操作函数
	CRichEditCtrl m_reLog;
	void PrintLog(LPCTSTR szFormat, ...);

private:
	// 获取配置参数
	void GetConfig(void);
	// 初始化按钮隐藏
	void InitCtrls(void);

private:
	// 获取南华初检登录车辆信息，并修改检测状态
	void LogVehInfoToDetSta(void);

private:
	RECT m_rtLastClientRect;

private:
	// 检测业务列表ToolTip回调函数
	static void __stdcall DetBsnToolTipCallBack(const CStringW &strRunNum, const int nRow, const int nCol,  CStringW &strToolTipText);

private:
	// 待检业务
	CToolTipListCtrl m_lstDetBsnNoCharge;
	CToolTipListCtrl m_lstDetBsnCharge;
	// 车牌号码
	CEdit m_edNoChargeFilter;
	CEdit m_edChargeFilter;
	// 初始化检测业务列表
	void InitDetBsnList(void);
	// 更新检测业务列表
	void UpdateDetBsnList(void);

private:
	// 收费
	CButtonST m_btnCharges;
	// 查询是否有相同车辆的情况
	// 查询Charge 查询到返回True， 未查询返回False;
	bool QuerySameVehinfo(const CString& strPlateNumber);
	// 保存在Charge表中
	// strRunNum 日志编号
	// strMsg 返回失败信息
	// bBackOff 是否退办重做？
	bool SaveDetLogToCharge(const CString& strRunNum, CString& strMsg, const bool& bBackOff=false);
	// 修改Detlog状态
	// strRunNum 日志编号
	// strMsg 返回失败信息
	bool ModifyStateDetLog(const CString& strRunNum, CString& strMsg, const CString& strState=L"TODET");

private:
	// 修改收费金额
	bool ModifyChargeAmount(CString& strMsg);

private:
	// 取消收费
	bool CancelOfCharge(CString& strMsg);

private:
	friend class CVehCountStatDlg;
};
