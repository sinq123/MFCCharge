
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar;
	//CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

private:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnPaint();
	afx_msg void OnUpdateStatusPane1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStatusPane2(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
	afx_msg void OnChangePassword();
	afx_msg void OnCharge();
	afx_msg void OnStaffManagement();
	afx_msg void OnChargeMaintenance();
	afx_msg void OnChargeStatistics();
	afx_msg void OnQuery();
	afx_msg void OnFeeTables();
	afx_msg void OnChargeStatistics2();
	afx_msg void OnBookkeepingCollection();
private:
	void DrawTitleBmp(CDC *pDC);

private:
	// 通用对话框字体
	CFont m_fontDlgFont;
	// 通用对话框字体大小
	int m_nDlgFontSize;
	// 系统菜单
	CMenu *m_pMenu;
	// 初始化菜单
	void InitMenu(void);

private:
	// 是否加载标题图片
	bool m_bLoadTitleBmp;
	// 标题图片
	CBitmap m_bmpTitle;
	// 标题图片BITMAP
	BITMAP m_hBmpTitle;
	// 状态栏按钮图片
	CBitmap m_bmpStatusBarIcon;
	// 显示背景图片
	void ShowBackGroundBitmap(void);


private:
	// 获取南华初检登录车辆信息，并修改检测状态
	// nDetType == 1 两检合一
	// nDetType == 2 安检
	// nDetType == 3 综检
	void LogVehInfoToDetSta(const int& nDetType);

public:
	// 验证用户权限
	bool VerifyEmpPerm(const SToll_Operator& sToll_Operator);
	
};


