#pragma once

#include "ToolTipListCtrl.h"

// CChargeInfoView 窗体视图
enum DropWhy
{
	DDT_Charge = 0,		// 收费
	DDT_Cancels,		// 取消
	DDT_Modifies,		// 修改
	DDTWrongChoice,		// 选错
};

class CChargeInfoView : public CFormView
{
	DECLARE_DYNCREATE(CChargeInfoView)

protected:
	CChargeInfoView();           // 动态创建所使用的受保护的构造函数
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	// 待检业务
	CToolTipListCtrl m_lstDetBsnNoCharge;
	CToolTipListCtrl m_lstDetBsnCharge;
	// 车牌号码
	CEdit m_edNoChargeFilter;
	CEdit m_edChargeFilter;
	// 开始时间
	CDateTimeCtrl m_dtcNoChargeStartTime;
	CDateTimeCtrl m_dtcChargeStartTime;
	// 结束时间
	CDateTimeCtrl m_dtcNoChargeCondEndTime;
	CDateTimeCtrl m_dtcChargeCondEndTime;
	// 所有人
	CEdit m_edNoChargeOwner;
	CEdit m_edChargeOwner;
	// 号牌种类
	CComboBox m_cbNoChargePlateType;
	CComboBox m_cbChargePlateType;
	// 车辆类型
	CComboBox m_cbNoChargeVehType;
	CComboBox m_cbChargeVehType;
	// 收费金额
	CEdit m_edChargeChargeAmount;
	// 总金额
	CLabel m_lbTotalAmount;
	// 日志
	CRichEditCtrl m_reLog;
	// 收费
	CButtonST m_btnCharges;
	// 修改收费金额
	CButtonST m_btnModifyChargeAmount;
	// 取消收费
	CButtonST m_btnDeleteCharge;
	// 选错退回
	CButtonST m_btnWrongAndRetturn;
	// 杂项收费
	CButtonST m_btnMiscellaneousCharges;
	// 删除记录
	CButtonST m_btnDeleteRecord;
private:
	// 通用对话框字体
	CFont m_fontDlgFont;
	// 通用对话框字体大小
	int m_nDlgFontSize;

private:
	// 初始化控件
	void InitCtrls(void);
	// 设置对话框字体
	void SetDlgFont(void);
	// 初始化检测业务列表
	void InitDetBsnList(void);

private:
	// 控件随窗口变化而变化
	//// 添加控件ID
	//void InitConInfo(void);
	//void SetControlInfo(const WORD CtrlId);
	//int m_old_cx;
	//int m_old_cy;
	//CDWordArray m_control_info;
	CPoint m_Old;//存放对话框的宽和高

private:
	// 定时设置列表为未选择
	bool m_bListAsUnselected;

private:
	// 号牌种类
	std::list<SVeh_PlateType> m_lsVeh_PlateType;
	// 车辆类型
	std::list<SVeh_VehType> m_lsVeh_VehType;
	// 初始化号牌种类
	bool InitPlateType(void);
	// 初始化车辆类型
	bool InitVehType(void);

private:
	// 操作记录
	void PrintLog(LPCTSTR szFormat, ...);

private:
	// 更新
	// 未收费列表
	void NoChargeUpdateDetBsnList(void);
	// 已收费列表
	void ChargeUpdateDetBsnList(void);

private:
	bool SaveToCharge(const CString& strChargeItem, const CString& strCharge, const CString& strWhy, const CString& strIsArrears, const CString& strUnitName);
	// 修改Detlog状态
	// strRunNum 日志编号
	// strMsg 返回失败信息
	bool ModifyStateDetLog(const CString& strRunNum, const CString& strState=L"TODET");
	// 删除收费记录
	bool DeteleToCharge(const  CString& strRunNum);

private:
	// 修改收费金额
	bool ModifyChargeAmount(const CString& strChargeItem, const CString& strCharge, const CString& strWhy);
	// 取消收费
	bool CancelOfCharge(const CString& strWhy);

private:
	// 判断是否全部项目检测完成
	CString IsBsnFined(const std::wstring& strRunNum);

public:
	afx_msg void OnBnClickedBtnDeleteRecord();
	bool VerifyEmpPerm(const SToll_Operator& sToll_Operator);

private:
	// 欠款保存
	// strUnitName 欠款单位
	// strCharge 欠款(收费)金额
	bool SaveArrearsToDB(const CString& strUnitName, const CString& strCharge);
};


