
// FFWDIMDlg.h : ͷ�ļ�
//

#pragma once


// CFFWDIMDlg �Ի���
class CFFWDIMDlg : public CDialogEx
{
// ����
public:
	CFFWDIMDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CFFWDIMDlg();
// �Ի�������
	enum { IDD = IDD_FFWDIM_DIALOG };

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
	afx_msg void OnBnClickedBtnForward();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
// ����������
private:
	NOTIFYICONDATA m_nid;
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
	CEdit m_edMCSharePath;
	CEdit m_edDetSharePath;
	CButtonST m_btnForward;
	// ��־��ʾ
	CRichEditCtrl m_reLog;
private:
	// ͨ�öԻ�������
	CFont m_fontDlgFont;
	// ͨ�öԻ��������С
	int m_nDlgFontSize;

	CString m_strLogFilePath;

	bool m_bLogFile;

private:
	void LoadConfig(void);
	void SaveConfig(void);

	void Forward(void);
	// ������־�ļ�
	void GenLogFile(void);
private:
	// File�Ƿ����
	bool IsFileExist(CString& strFile);
	// ɾ���ļ�
	bool DelFile(CString& strFile);
	// �ƶ��ļ�
	bool MoveFileTo(CString& strFromPath, CString& strToPath);

	// ��¼��ʼ��⳵�ƣ���ֵ����Ϣ
	void RecordBegDet(void);
	// ��¼�����ļ�⳵�ƺ���Ϣ
	void RecordEndDet(void);

	// д����־��Ϣ������鿴������
	void PrintLog(LPCTSTR szFormat, ...);
};
