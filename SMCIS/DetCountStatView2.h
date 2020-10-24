#pragma once



// CDetCountStatView2 ������ͼ

class CDetCountStatView2 : public CFormView
{
	DECLARE_DYNCREATE(CDetCountStatView2)

protected:
	CDetCountStatView2();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

private:
	// ���ؼ�
	CGridCtrl* m_pGridCtrl;
	CListCtrl m_lstVehCount;

	CDateTimeCtrl m_dtcBegTime;
	CDateTimeCtrl m_dtcEndTime;
	
	CButtonST m_btnStat;
	CButtonST m_btnPrint;
	CButtonST m_btnExport;

private:
	// ��ʼ��������
	bool GetDetType(std::list<SCharge_DetType>& lsDetType);
	// ��������Ͳ�ѯ
	// ����д��������
	void GetDetChargeStatToDetType(const CString& strDetType, const CString& strDetTypeCode, int& nRow);
	// ��ȡ���۽��
	CString GetUnitValue(const CString& strDetType, const CString& strDetTypeCode, const CString& strChargeItem);
	// ��ȡ�����
	void GetChargeStatToZX(int& nRow);
	// ��ȡ����ĵ��۽��
	CString GetZXUnitValue(const CString& strDetType, const CString& strDetTypeCode, const CString& strChargeItem);

};


