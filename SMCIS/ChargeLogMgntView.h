#pragma once



// CChargeLogMgntView 窗体视图

class CChargeLogMgntView : public CFormView
{
	DECLARE_DYNCREATE(CChargeLogMgntView)

protected:
	CChargeLogMgntView();           // 动态创建所使用的受保护的构造函数
	virtual ~CChargeLogMgntView();

public:
	enum { IDD = IDD_CHARGE_LOG_MGNT_VIEW };
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

private:
	// 控件随窗口变化而变化
	CPoint m_Old;//存放对话框的宽和高

private:
	afx_msg void OnBnClickedBtnQuery();
	afx_msg void OnBnClickedBtnPreviousPage();
	afx_msg void OnBnClickedBtnNextPage();

private:
	// 系统日志信息列表
	CListCtrl m_lstSystemLog;
	// 位图列表，用于设置列表行高
	CImageList m_ilRowHeight;
	// 共n条
	CStatic m_stTotalNum;
	// 共n页
	CStatic m_stTotalPage;
	// 第n页
	CStatic m_stCurrentPage;
	//开始时间
	CDateTimeCtrl m_dtBeginTime;
	//结束时间
	CDateTimeCtrl m_dtEndTime;
	
	CButtonST m_btnQuery;
	CButtonST m_btnPrevious;
	CButtonST m_btnNext;

private:
	// 初始化控件
	void InitCtrls(void);
	// 设置对话框字体
	void SetDlgFont(void);

private:
	// 自动适应列宽
	void AutoFitColumnWidth(CListCtrl &list);

private:
	// 初始化系统日志信息列表
	void InitSystemLogList(void);

private:
	// 通用对话框字体
	CFont m_fontDlgFont;
	// 通用对话框字体大小
	int m_nDlgFontSize;

private:
	// 生成查询SQL
	CString GenerateQuerySQL(void);
	// 查找系统日志数据
	DWORD QuerySystemLogData(void);
	// 显示系统日志信息
	void SystemLogDataToList(void);
	//验证日期查询条件
	bool VerifyQueryCond(void);

private:
	// 查询结果
	_RecordsetPtr m_pRecordset;
	// 页面大小
	int m_nPageSize;
	// 共n条
	int m_nTotalNum;
	// 共n页
	int m_nTotalPage;
	// 第n页
	int m_nCurrentPage;
};


