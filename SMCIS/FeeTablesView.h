#pragma once



// CFeeTablesView ������ͼ

class CFeeTablesView : public CFormView
{
	DECLARE_DYNCREATE(CFeeTablesView)

protected:
	CFeeTablesView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFeeTablesView();

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
	int m_nTotNum;
	float m_fAmountOfCharges;

private:
	CString GetSQL(void);
	float m_fTotalAmount;
	// �������ܽ��
	// ���ó����飨���죩
	// �����ȼ�����
	// ���ó����飨���죩//�����ȼ�����
	// ע��ǼǼ���
	// ע��ǼǼ���//�����ȼ�����
	// ���ó����飨�Ƕ���)
	// ��ʱ����
	// ����
	void TotalAmountOfTestCategory(const int& nDetType, const float& fTotalAmount);

	// ���ó�
	// strSQL:���ݿ����
	// ũ��(�綯�����䳵
	void DetTypeRIVehATVeh(const CString& strSQL);
	// �ͳ���9������
	// strSQL:���ݿ����
	// nNumber:Ĭ�ϲο�����
	// 1.9������
	// 2.10-19
	// 3.20����
	void DetTypeRIVehPCar(const CString& strSQL, const int& nNumber);
	// У�� 
	// strSQL:���ݿ����
	// nNumber:Ĭ�ϲο�����
	// 1.10-19
	// 2.20����
	void DetTypeRIVehSchbus(const CString& strSQL, const int& nNumber);
	// ���� Σ��
	// strSQL:���ݿ����
	// nTonnage:��λ
	// bDANGER:�Ƿ����
	// 1.������4.5t����
	// 2.������4.5-12t
	// 3.������12-30t
	// 4.������30t����
	void DetTypeRIVehTruck(const CString& strSQL, const int& nTonnage, const bool& bDANGER=false);
	// �ҳ� Trailer
	// strSQL:���ݿ����
	// bDANGER:�Ƿ����
	void DetTypeRIVehTrailer(const CString& strSQL,/* const int& nTonnage,*/ const bool& bDANGER=false);
	// ר����ҵ�� Special Operation Vehicle
	// strSQL:���ݿ����
	void DetTypeRIVehSOVeh(const CString& strSQL);

	// �����ȼ�����
	// ����������С�ͳ���
	void TGECoachLeaseSmallVeh(const CString& strSQL);
	// �ͳ���9������
	// strSQL:���ݿ����
	// nNumber:Ĭ�ϲο�����
	// 1.10-19
	// 2.20����
	void TGERIVehPCar(const CString& strSQL, const int& nNumber);
	// ���� Σ��
	// strSQL:���ݿ����
	// nTonnage:��λ
	// bDANGER:�Ƿ����
	// 1.������4.5t����
	// 2.������4.5-12t
	// 3.������12-30t
	// 4.������30t����
	void TGERIVehTruck(const CString& strSQL, const int& nTonnage, const bool& bDANGER=false);

	// �����һ
	// ����������С�ͳ���
	void TheToOneCoachLeaseSmallVeh(const CString& strSQL);
	// �ͳ���9������
	// strSQL:���ݿ����
	// nNumber:Ĭ�ϲο�����
	// 1.10-19
	// 2.20����
	void TheToOneRIVehPCar(const CString& strSQL, const int& nNumber);
	// ���� Σ��
	// strSQL:���ݿ����
	// nTonnage:��λ
	// bDANGER:�Ƿ����
	// 1.������4.5t����
	// 2.������4.5-12t
	// 3.������12-30t
	// 4.������30t����
	void TheToOneRIVehTruck(const CString& strSQL, const int& nTonnage, const bool& bDANGER=false);

	// ע��Ǽ�
	// С�Ϳͳ�
	void RegistrationRIVehPCar(const CString& strSQL);
	// ����
	// strSQL:���ݿ����
	// nTonnage:��λ
	// bDANGER:�Ƿ����
	// 1.������3.5t����
	// 2.������3.5-4.5t
	// 3.������4.5t-31t����
	void RegistrationRIVehTruck(const CString& strSQL, const int& nTonnage);
	// ר����ҵ�� Special Operation Vehicle
	// strSQL:���ݿ����
	void RegistrationRIVehSOVeh(const CString& strSQL);

	// �����һ(�³�)
	void NewTheToOneRIVehTruck(const CString& strSQL);

	// �Ƕ���
	void NoFixedCheck(const CString& strSQL);

	// ��ʱ����Temporary inspection
	// 1.����
	// 2.ת��
	// 3.ת��
	void TemIns(const CString& strSQL, const int& nTonnage);

	// ���� Miscellaneous
	// 1.A
	// 2.B
	// 3.Ħ�г�
	// 4.����Ĥ
	// 5.���Ǿ�����
	// 6.�����
	// 7.����
	// 8.Ԥ����
	void Mis(const int& nTonnage);
};


