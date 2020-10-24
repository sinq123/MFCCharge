#pragma once



// CDetCountStatView 窗体视图

class CDetCountStatView : public CFormView
{
	DECLARE_DYNCREATE(CDetCountStatView)

protected:
	CDetCountStatView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDetCountStatView();

public:
	enum { IDD = IDD_COUNT_STAT_VIEW };
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
public:
	

private:
	// 表格控件
	CGridCtrl* m_pGridCtrl;
	CListCtrl m_lstVehCount;

	CDateTimeCtrl m_dtcBegTime;
	CDateTimeCtrl m_dtcEndTime;
	
	CButtonST m_btnStat;
	CButtonST m_btnPrint;
	CButtonST m_btnExport;
	CComboBox m_cbStatType;

private:
	bool QuerySqlDB(_RecordsetPtr& pRecordset, const COleDateTime& odtBeginTime, const COleDateTime& odtEndTime);
	void DetChargeStat(void);
	CStringW ToStatusName(const CStringW& strStatusCode);

	void StatisticsOfEachVehicle(void);
	void MiscellaneousStatistics(void);
	void MiscellaneousVehicleStatistics(void);
};


