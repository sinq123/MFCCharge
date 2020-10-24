#pragma once



// CDetCountStatView2 窗体视图

class CDetCountStatView2 : public CFormView
{
	DECLARE_DYNCREATE(CDetCountStatView2)

protected:
	CDetCountStatView2();           // 动态创建所使用的受保护的构造函数
	virtual ~CDetCountStatView2();

public:
	enum { IDD = IDD_FEE_TABLES_VIEW };
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
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnStat();
	afx_msg void OnBnClickedBtnPrint();
	afx_msg void OnBnClickedBtnExport();

private:
	// 通用对话框字体
	CFont m_fontDlgFont;
	// 通用对话框字体大小
	int m_nDlgFontSize;
	CPoint m_Old;//存放对话框的宽和高

private:
	// 初始化表格控件
	void InitGirdCtrl(void);
	// 初始化控件
	void InitCtrls(void);
	// 设置对话框字体
	void SetDlgFont(void);

private:
	// 表格控件
	CGridCtrl* m_pGridCtrl;
	CListCtrl m_lstVehCount;

	CDateTimeCtrl m_dtcBegTime;
	CDateTimeCtrl m_dtcEndTime;
	
	CButtonST m_btnStat;
	CButtonST m_btnPrint;
	CButtonST m_btnExport;

private:
	// 初始化检测类别
	bool GetDetType(std::list<SCharge_DetType>& lsDetType);
	// 按检测类型查询
	// 返回写过的行数
	void GetDetChargeStatToDetType(const CString& strDetType, const CString& strDetTypeCode, int& nRow);
	// 获取单价金额
	CString GetUnitValue(const CString& strDetType, const CString& strDetTypeCode, const CString& strChargeItem);
	// 获取杂项的
	void GetChargeStatToZX(int& nRow);
	// 获取杂项的单价金额
	CString GetZXUnitValue(const CString& strDetType, const CString& strDetTypeCode, const CString& strChargeItem);

};


