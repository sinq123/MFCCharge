#pragma once

#include "ToolTipListCtrl.h"

// CBookkeepingCollectionView 窗体视图

class CBookkeepingCollectionView : public CFormView
{
	DECLARE_DYNCREATE(CBookkeepingCollectionView)

protected:
	CBookkeepingCollectionView();           // 动态创建所使用的受保护的构造函数
	virtual ~CBookkeepingCollectionView();

public:
	enum { IDD = IDD_BOOKKEEPING_COLLECTION_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedBtnUplis();
	afx_msg void OnBnClickedBtn();
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
	CPoint m_Old;//存放对话框的宽和高

private:
	// 控件
	// 列表
	CToolTipListCtrl m_lsBookkeeping;
	// 日志
	CRichEditCtrl m_reLog;
	// 更新列表
	CButtonST m_btnUplis;
	// 收款金额
	CXPGroupBox m_gbAmount_Collected;
	CLabel m_lbAmount_Collected;
	CNumericEdit m_edAmount_Collected;
	CButtonST m_btnAmount_Collected;

private:
	// 操作记录
	void PrintLog(LPCTSTR szFormat, ...);
private:
	// 更新
	void UPLisBookkeeping(void);
private:
	// 清空控件操作
	void ClearControl(void);
private:
	// 收款
	bool CollectionToDB(void);
	// 保存到Charge表中
	bool SaveToChargeDB(void);


};



