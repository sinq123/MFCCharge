#pragma once



// CDetCountStatView ������ͼ

class CDetCountStatView : public CFormView
{
	DECLARE_DYNCREATE(CDetCountStatView)

protected:
	CDetCountStatView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	// ͨ�öԻ�������
	CFont m_fontDlgFont;
	// ͨ�öԻ��������С
	int m_nDlgFontSize;
	CPoint m_Old;//��ŶԻ���Ŀ�͸�

private:
	// ��ʼ�����ؼ�
	void InitGirdCtrl(void);
	// ��ʼ���ؼ�
	void InitCtrls(void);
	// ���öԻ�������
	void SetDlgFont(void);
public:
	

private:
	// ���ؼ�
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


