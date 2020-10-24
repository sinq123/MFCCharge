#pragma once



// CChargeLogMgntView ������ͼ

class CChargeLogMgntView : public CFormView
{
	DECLARE_DYNCREATE(CChargeLogMgntView)

protected:
	CChargeLogMgntView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();

private:
	// �ؼ��洰�ڱ仯���仯
	CPoint m_Old;//��ŶԻ���Ŀ�͸�

private:
	afx_msg void OnBnClickedBtnQuery();
	afx_msg void OnBnClickedBtnPreviousPage();
	afx_msg void OnBnClickedBtnNextPage();

private:
	// ϵͳ��־��Ϣ�б�
	CListCtrl m_lstSystemLog;
	// λͼ�б����������б��и�
	CImageList m_ilRowHeight;
	// ��n��
	CStatic m_stTotalNum;
	// ��nҳ
	CStatic m_stTotalPage;
	// ��nҳ
	CStatic m_stCurrentPage;
	//��ʼʱ��
	CDateTimeCtrl m_dtBeginTime;
	//����ʱ��
	CDateTimeCtrl m_dtEndTime;
	
	CButtonST m_btnQuery;
	CButtonST m_btnPrevious;
	CButtonST m_btnNext;

private:
	// ��ʼ���ؼ�
	void InitCtrls(void);
	// ���öԻ�������
	void SetDlgFont(void);

private:
	// �Զ���Ӧ�п�
	void AutoFitColumnWidth(CListCtrl &list);

private:
	// ��ʼ��ϵͳ��־��Ϣ�б�
	void InitSystemLogList(void);

private:
	// ͨ�öԻ�������
	CFont m_fontDlgFont;
	// ͨ�öԻ��������С
	int m_nDlgFontSize;

private:
	// ���ɲ�ѯSQL
	CString GenerateQuerySQL(void);
	// ����ϵͳ��־����
	DWORD QuerySystemLogData(void);
	// ��ʾϵͳ��־��Ϣ
	void SystemLogDataToList(void);
	//��֤���ڲ�ѯ����
	bool VerifyQueryCond(void);

private:
	// ��ѯ���
	_RecordsetPtr m_pRecordset;
	// ҳ���С
	int m_nPageSize;
	// ��n��
	int m_nTotalNum;
	// ��nҳ
	int m_nTotalPage;
	// ��nҳ
	int m_nCurrentPage;
};


