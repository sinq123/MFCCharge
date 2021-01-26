//Download by http://www.NewXing.com
// SreenClientDlg.h : header file
//

#if !defined(AFX_SREENCLIENTDLG_H__09B2FBE5_5D68_4561_A971_84BF26AA5688__INCLUDED_)
#define AFX_SREENCLIENTDLG_H__09B2FBE5_5D68_4561_A971_84BF26AA5688__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ClientSock.h"
/////////////////////////////////////////////////////////////////////////////
// CSreenClientDlg dialog
struct USERINFO{//�û���Ϣ
	char name[30];
	char password[20];
    int uport;
};
struct CapSreenHeader//ͼ��ͷ��Ϣ
{
	long filelength;
	int width;
	int height;
	int blocklen;
	long factlen;
};

struct MYMOUSEINFO
{
	int x;
	int y;
	int type; //1,2,3,8 ����,�Ұ���,˫��,����
	unsigned char keyct1;//��ֵ
	unsigned char keyct2;
	int keytype;//UP��DOWN 1,2
};

class CClientSock;

class CSreenClientDlg : public CDialog
{
// Construction
public:
	CSreenClientDlg(CWnd* pParent = NULL);	// standard constructor
public:
	void drawSreen();
	void initDrawParam();
	void initDrawSreen();
	void myRecvData(CClientSock *pc);
	CClientSock *pclient;

	USERINFO usrinfo;
	NETPACKAGE usrpack;//�û���Ϣ
	int pklen;//���ݳ���

	BITMAPINFOHEADER *m_pBIH;//λͼͷ
	unsigned char *m_pDibBits;//ָ���ѹ��ͼ���������
	unsigned char *m_pDib;//ͼ�����ݻ���
	long lbitsOffset;//����ͼ������ƫ��
	CapSreenHeader cheader;//ͼ��ͷ��Ϣ
	
	int scrx;//Զ����Ļˮƽ���
	int scry;//Զ����Ļ��ֱ���
	int scrxlm;//ˮƽ�ƶ����ֵ
	int scrylm;//��ֱ�ƶ����ֵ
	int capflag;//�Ƿ񲶻�ɹ�
	int m_width;//Զ����Ļ�Ŀ��
	int m_height;//Զ����Ļ�ĸ߶�
	int cwidth;//��������Ŀ��
    int cheight;////��������ĸ߶�
	int bcontrol;//������Ч

    
// Dialog Data
	//{{AFX_DATA(CSreenClientDlg)
	enum { IDD = IDD_SREENCLIENT_DIALOG };
	CScrollBar	m_hbar;
	CScrollBar	m_vbar;
	CString	m_ip;
	int		m_port;
	CString	m_usrpwd;
	CString	m_usrname;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSreenClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSreenClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonConnect();
	afx_msg void OnButtonControl();
	afx_msg void OnButtonGetcap();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnButtonKetinput();
	afx_msg void OnButtonKeyctrl();
	afx_msg void OnButtonKeyshift();
	afx_msg void OnButtonKeyenter();
	afx_msg void OnButtonKetbackspace();
	afx_msg void OnButtonKeytab();
	afx_msg void OnButtonKeycapslock();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SREENCLIENTDLG_H__09B2FBE5_5D68_4561_A971_84BF26AA5688__INCLUDED_)
