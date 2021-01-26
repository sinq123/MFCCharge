
// PDAOnLineDlg.h : ͷ�ļ�
//

#pragma once

#include "..\NHCommand\NHCommand.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHCommand_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHCommand.lib")
#endif

#include "..\NHNetLib\NHNetServer.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\MYNetLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\MYNetLib.lib")
#endif

// CPDAOnLineDlg �Ի���
class CPDAOnLineDlg : public CDialogEx
{
// ����
public:
	CPDAOnLineDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CPDAOnLineDlg();
// �Ի�������
	enum { IDD = IDD_PDAONLINE_DIALOG };

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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnQuery();
private:
	// �б�LST_DET_WAITING
	CListCtrl m_lstDetWaiting;
	CListCtrl m_lstDetInspectionArea;

private:
	// ͨ�öԻ�������
	CFont m_fontDlgFont;
	// ͨ�öԻ��������С
	int m_nDlgFontSize;
	bool m_bConnectDB;
	// ���ݿ�����
	_ConnectionPtr m_pConnection;
	// ����IP
	CString m_strMCSIP;
	// 
	CString m_strPositionNumber;
private:
	// ��ʼ���ؼ�
	void InitCtrls(void);
	// ���öԻ�������
	void SetDlgFont(void);
	// ��ʼ�����ҵ���б�
	void InitDetBsnList(void);
	// ��ȡ����������
	void LoadConfig(void);

	// �����ݿ�
	void OpenDB(void);
	// �ر����ݿ�
	void CloseDB(void);

private:
	// �ؼ��洰�ڱ仯���仯
	CPoint m_Old;//��ŶԻ���Ŀ�͸�

private:
	// �������
	CNHNetServer m_NHNetServer;

private:
	// �����������߳�
	void StartServer(void);
	// ֹͣ�������߳�
	void StopServer(void);

private:
	// ���ݴ���ص�����
	static void __stdcall DataSolutionCallBack(const wchar_t* pwchIP, const BYTE* pBytes, const size_t size);

private:
	// ��ѯ������Ϣ
	void QueryWaitInfo(void);
	void QueryInspInfo(void);

	// ���߲���
	void Send_CN_Online(void);
	// ������Ϣ
	void SendRSDCmd(const wchar_t* pwchIP, CNHCommand& cmdRSD);
};
