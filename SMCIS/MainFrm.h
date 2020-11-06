
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	//CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
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
	// ͨ�öԻ�������
	CFont m_fontDlgFont;
	// ͨ�öԻ��������С
	int m_nDlgFontSize;
	// ϵͳ�˵�
	CMenu *m_pMenu;
	// ��ʼ���˵�
	void InitMenu(void);

private:
	// �Ƿ���ر���ͼƬ
	bool m_bLoadTitleBmp;
	// ����ͼƬ
	CBitmap m_bmpTitle;
	// ����ͼƬBITMAP
	BITMAP m_hBmpTitle;
	// ״̬����ťͼƬ
	CBitmap m_bmpStatusBarIcon;
	// ��ʾ����ͼƬ
	void ShowBackGroundBitmap(void);


private:
	// ��ȡ�ϻ������¼������Ϣ�����޸ļ��״̬
	// nDetType == 1 �����һ
	// nDetType == 2 ����
	// nDetType == 3 �ۼ�
	void LogVehInfoToDetSta(const int& nDetType);

public:
	// ��֤�û�Ȩ��
	bool VerifyEmpPerm(const SToll_Operator& sToll_Operator);
	
};


