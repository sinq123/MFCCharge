
// MDODimDlg.h : ͷ�ļ�
//

#pragma once

// CMDODimDlg �Ի���
class CMDODimDlg : public CDialogEx
{
// ����
public:
	CMDODimDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CMDODimDlg();
// �Ի�������
	enum { IDD = IDD_MDODIM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	afx_msg void OnEnChangeEdFilterPlatenumber();
	afx_msg void OnLvnItemchangedLstDetWaiting(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnStartDet();
	afx_msg void OnBnClickedBtnPhotoDet();
	afx_msg void OnBnClickedBtnUploadDateDet();
	afx_msg void OnBnClickedBtnEndDet();
	afx_msg void OnBnClickedBtnSignOut();
	afx_msg void OnBnClickedBtnQuery();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	// ���ƺ���
	CEdit m_edFilterPlateNumber;
	// ¼�볤
	CEdit m_edFInputDataLength;
	// ¼���
	CEdit m_edFInputDataWidth;
	// ¼���
	CEdit m_edFInputDataHeight;
	// �б�LST_DET_WAITING
	CListCtrl m_lstDetWaiting;

	// ��ʼ
	CButtonST m_btnStartDet;
	// ����
	CButtonST m_btnPhotoDet;
	// �����ϴ�
	CButtonST m_btnUpLoadDataDet;
	// ����
	CButtonST m_btnSingOut;
	// �˳�
	CButtonST m_btnEndDet;
	// ��ѯ
	CButtonST m_btnQuery;


	// STANDARD_DATA
	CLabel m_lbStandardDataLenght;
	CLabel m_lbStandardDataWidth;
	CLabel m_lbStandardDataHeight;
	// UPPER_LIMIT_DATA
	CLabel m_lbUpperLimitDataLenght;
	CLabel m_lbUpperLimitDataWidth;
	CLabel m_lbUpperLimitDataHeight;
	// LOWER_LIMIT_DATA
	CLabel m_lbLowerLimitDataLenght;
	CLabel m_lbLowerLimitDataWidth;
	CLabel m_lbLowerLimitDataHeight;
	// ����Ա�����Ա
	CComboBox m_cbDriver;
	CComboBox m_cbExternalInspector;

private:
	// ͨ�öԻ�������
	CFont m_fontDlgFont;
	// ͨ�öԻ��������С
	int m_nDlgFontSize;
	bool m_bConnectDB;
	// ���ݿ�����
	_ConnectionPtr m_pConnection;
	// ��־���
	CString m_strRunningNumber;
	SVehDimensionInfo m_sVehDimInfo;
	// ����ƽ̨����
	int m_nNetPlatform;
private:
	// ��⿪ʼʱ��
	COleDateTime m_odtBeginTime;
	// ������ʱ��
	COleDateTime m_odtEndTime;
private:
	// ��ʼ���ؼ�
	void InitCtrls(void);
	// ���öԻ�������
	void SetDlgFont(void);
	// ��ʼ�����ҵ���б�
	void InitDetBsnList(void);
	// ��ʼ������Ա
	void InitGuide(void);
private:
	// �ؼ��洰�ڱ仯���仯
	CPoint m_Old;//��ŶԻ���Ŀ�͸�


private:
	// �趨��׼����ֵ�ؼ�
	// ��׼ 1�� ���� 2�� ���� 3
	void SetStaAndLimitData(const int& nLabel, const CString& strLenght=L"", const CString& strWidth=L"", const CString& strHeight=L"");

	// �����ݿ�
	void OpenDB(void);
	// �ر����ݿ�
	void CloseDB(void);

private:
	// ��ѯ������Ϣ
	void QueryInfo(void);
	// ��ȡ��׼����ֵ
	void GetVehInfoAndStandard(POSITION pos);
	// �ж�������Ƿ�ϸ�
	bool JudgeLenAndWidAndHei(void);
private:
	// ��ʼ���
	// �������
	// ����������
	// ����
	// 
public:
	
};
