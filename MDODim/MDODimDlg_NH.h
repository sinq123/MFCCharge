#pragma once


// CMDODimDlg_NH �Ի���

struct SGTStatus
{
	//��ۼ����
	std::wstring strRunningNumber;
	//�����ƺ�
	std::wstring strPlateNumber;
	//��������
	std::wstring strPlateType;
	//״̬
	std::wstring strStatus;
	//����״̬
	std::wstring strDimStatus;
	//��������״̬
	std::wstring strUMStatus;
	//��ע˵��
	std::wstring strRemark;
	//ʱ��
	std::wstring strTimes;
};

class CMDODimDlg_NH : public CDialogEx
{
	DECLARE_DYNAMIC(CMDODimDlg_NH)

public:
	CMDODimDlg_NH(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMDODimDlg_NH();

// �Ի�������
	enum { IDD = IDD_MDODIM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	afx_msg void OnBnClickedCheIsUseStaGb1589();
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
	// ��ʾ��Ϣ
	CLabel m_lbShowInfoTest;
	// �Ƿ�ʹ��GB1589��׼
	CButtonST m_chkIsUseStaGB1589;
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
	SDetLog m_sDetLog;
	SDetTimes m_sDetTimes;
	SVehDimensionInfo m_sVehDimInfo;
	SHisVehInfo m_sHisVehInfo;
	SDetStandard m_sDetStandard;

	CString m_strRunningNumberSen;
	SDetLog m_sDetLogSen;
	SDetTimes m_sDetTimesSen;
	SVehDimensionInfo m_sVehDimInfoSen;
	SHisVehInfo m_sHisVehInfoSen;
	SDetStandard m_sDetStandardSen;
	// ����ƽ̨����
	int m_nNetPlatform;
	// �Ƿ������
	bool m_bWheelBase;
	// �Ƿ������(�³����)
	bool m_bWheelBaseNew;
	// �Ƿ��������
	bool m_bPinbase;
	// �Ƿ��������(�³����)
	bool m_bPinbaseNew;
	// �Ƿ�������άͼ
	bool m_bM2D;

	// 
	CString m_strBodyPhotoPath;
	CString m_strTopPhotoPath;
	//
	bool m_bIsUseGB1589;
private:
	// ��ʼ���ؼ�
	void InitCtrls(void);
	// ���öԻ�������
	void SetDlgFont(void);
	// ��ʼ�����ҵ���б�
	void InitDetBsnList(void);
	// ��ʼ������Ա
	void InitGuide(void);
	// ��ȡ����������
	void LoadConfig(void);

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

private:
	// �Ƿ��ȡ��������ʾ��Ϣ
	bool m_bCFG_ReadDetInfo;
	// ���ݽ����ļ���·��
	CStringW m_strDEFolderPath;
	// BegCTDet.ini·��
	CStringW m_strBegIniPath;
	// EndCTDet.ini·��
	CStringW m_strEndIniPath;
	// Display.txt·��
	CStringW m_strDisplayTxtPath;
	// 
	CStringW m_strLastLedInfo;
	// ��������
	CStringW m_strDimEqu;
	SGTStatus m_sGTStatus;
private:
	// ��⿪ʼʱ��
	COleDateTime m_odtBeginTime;
	// ������ʱ��
	COleDateTime m_odtEndTime;

private:
	// ��������
	// bIsRemDet:�Ƿ������⣬true:���,false:�����
	void ExportData(const bool bIsRemDet = false);
	// �������ݣ�����֤���ݣ�
	bool ImportData(void);
	// BegCTDet.ini�Ƿ����
	bool IsBegIniExist(void);
	// EndCTDet.ini�Ƿ����
	bool IsEndIniExist(void);
	// ɾ��BegCTDet.ini
	bool DelBegIni(void);
	// ɾ��EndCTDet.ini
	bool DelEndIni(void);
	// ��ȡ����ʾLedInfo.txt����
	bool ReadAndShowLedInfoTxt(void);
	// ��̩״̬
	void StatusConfig(void);
	// ��̩������Ϣ�ͼ��
	void CarInfoData(void);
	bool IsGZEndIniNow(const CStringW& strPath);
	void GZImportData(const CStringW& strPath, const bool& bSen=false);
	int AnalogData(const int& nUpLimit, const int& nDownLimit);
private:
	// ������Ƭ
	void SavePhoto();
	// ����������
	void SaveDetData(void);
	// ����ڶ���������
	void SaveSecVehDetData(void);

private:
	// bmpתjpg
	bool BMPTOJPG(const CString& srtBmpPath, const CString& strJpgPath);
	// jpgתbmp
	bool JPGTOBMP(const CString& strJpgPath, const CString& srtBmpPath);
	// ����ˮӡ
	void AddWatermark(const CString& strJpgPath, const CString& strFildName);
	// ͼƬ�������
	void ImageAppendText(const std::wstring& strSource, const std::wstring& strTarget, const std::wstring& strText);
	// ͼƬ�������
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

};
