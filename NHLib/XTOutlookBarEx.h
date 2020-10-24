/////////////////////////////////////////////////////////////////////////////////////
// �ļ���   ��CXTOutlookBarEx
// �汾     ��1.0                
// ��Ҫ���� ��ʵ��outlookbar����
// �������� ��2006.11.15
// ����     ���޽��

// �÷�     ����listbox�ؼ����������ΪCXTOutlookBarEx����,ע��
//            �ӶԻ���Dialog����������SetDlgSizeָ����С���������
// ʵ��     ������A�е���outlookbar
//            CXTOutlookBarEx m_OutlookBar;          �����ؼ�listbox,Ϊ����ӱ���
//            CDlg1 m_dlg1; CDlg2 m_dlg2;            ��A.h ����Ҫ���صĶԻ������
//	          m_OutlookBar.SetColors(RGB(0xff,0xff,0xff), RGB(46,134,199)); ����������ɫ,������ɫ
//	          m_OutlookBar.SetOutlookFont("����",15);                       ��������
//	          m_OutlookBar.SetIconSize(48, 48);                             ����ͼ���С
//	          m_OutlookBar.SetDlgSize(GetDlgItem(IDC_STATIC_EDGE));         ָ���ӶԻ��������С
//            m_OutlookBar.AddDialog(&m_dlg1,IDD_DIALOG1,IDI_ICON1,"���ɻ���");
//            m_OutlookBar.AddDialog(&m_dlg2,IDD_DIALOG2,IDI_ICON2,"���غɻ���");

/////////////////////////////////////////////////////////////////////////////////////

// �汾��1.0.3
// ���ڣ�2010-03-05
// ���ߣ�Cui
// �������޸Ĺ����ð�ȫ�ַ����������治��ȫ�ַ���������warning����wcscpy_s����_tcscpy

//�汾��1.0.2
//���ڣ�2010-1-13
//���ߣ�Raylee
//�������޸ĺ���SetDlgSize()��������ҳ����ʱ˳���ԭ�ؼ�����

//�汾��1.0.1 
//���ڣ�2009-10-12
//���ߣ�Raylee
//�������޸ĺ���OnVScroll��OnMouseWheel����������ʱ��˸������

#if !defined(__XTOUTLOOKBAREX_H__)
#define __XTOUTLOOKBAREX_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxtempl.h>
#define XTWM_OUTBAR_NOTIFY		(WM_USER+1019)
#define WM_ACCEPTMESSAG WM_USER+1112

/////////////////////////////////////////////////////////////////////////////
struct CHILD_DLGINFO             //��ҳ�Ի���ṹ
{
    HICON   m_hIcon;    // ͼ����
    int     m_nIndex;   // �Ի�������ID,���㿪ʼ
    CString m_strText;  // ͼ��˵��
	CWnd*	m_wnd;      // ��ҳ���ָ��
	bool    m_Selected; // �Ƿ�ѡ��
};/////////////////////////////////////////////////////////////////////////////


class AFX_EXT_CLASS CXTOutlookBarEx : public CListBox
{
    DECLARE_DYNAMIC(CXTOutlookBarEx)

public:

    CXTOutlookBarEx();

    virtual ~CXTOutlookBarEx();
///// ---------------------------------------�ڲ���Դ---------------------------------------//
protected:
	int m_nItem;                           // ��ҳ����,��ʼΪ0;
	CRect m_rcDlgs;                        // ��ҳ�Ի�������
	CWnd* m_wndDlgsRect;                   // ��ҳ����ؼ�����ָ��
	LOGFONT m_lf;                          // ����ṹ	
    CFont m_TextFont;                      // ����
protected:

	int        m_cxIcon;         // ͼ����
	int        m_cyIcon;         // ͼ��߶�
    bool       m_bHilight;       // ͼ�걻ѡ��ʱ
    bool       m_bLBDown;        // ͼ�걻����ʱ
    CPoint     m_point;          // ��ǰ��ý����ͼ������holds the cursor position
    COLORREF   m_clrBack;        // ������ɫ
    COLORREF   m_clrText;        // ������ɫ

	CList<CHILD_DLGINFO*,CHILD_DLGINFO*> m_arContentItems;
public:
    int        m_nIndex;         // ��ǰѡ�еĶԻ����ʶ

public:
	//---------------------------------�ⲿ�ӿ�----------------------------------------------//
	void SetFontSize(int nHeight);//���������С
	void SetFontName(CString strFontName);//������������
	void SetOutlookFont(CString strFontName,int nHeight);//������������,��С

	void SetColors(COLORREF clrText, COLORREF clrBack);                 // ������ɫ(clrText:������ɫ ,clrBack:������ɫ)
	void SetIconSize(int nCxIcon,int nCyIcon );                         // ����ͼ���С
	void SetDlgSize(CWnd* wdDlgs);                                      // �趨��ҳ�Ի�������
	bool AddDialog(CDialog* dlg,UINT nDlgID, UINT nIconID, CString nIconText);      // �����ҳ(dlg:��ҳ���   nDlgID:��ҳ�Ի�����ԴID  
                                                                                    //         nIconID:ͼ����ԴID   nIconText:ͼ������)

	void EnableDlg(int nPage);                                          //ʹָ��ҳ����
 	void DisableDlg(int nPage);                                         //ʹָ��ҳ������
	void DisableOtherDlg(void);                                         //ʹ����ǰҳ������ҳ�治����
    void EnableAllDlg(void);                                            //ʹ����ҳ�����
	int ShowItemDlg(int iItem);                                         // ��ʾ��ҳ(iItem:��ҳ����ID,��0��ʼ)
    void HideAllDlg(void);                                              //����������ҳ
	CString GetIconText(int nIcon);                                     //��ȡָ��ͼ��˵������
	////////////////////////////////////////////////////////////////////////////////////////////

   //---------------------------------�ڲ��ӿ�----------------------------------------------//
protected:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);               // ����outlookbar
    virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);      // �����б���߶�

	int InsertMenuItem(int iIndex, UINT nIconID, LPCTSTR lpszText); 	    // ����ͼ��(iIndex:Ҫ�����λ��, nIconID:ͼ����ԴID, lpszText:ͼ��˵��),
	                                                                        // �ɹ����ز����λ�ñ�ʶ,ʧ�ܷ���LB_ERR,���û����ؼ��������򷵻�LB_ERRSPACE

	int AddMenuItem(UINT nIconID, LPCTSTR lpszText);                        // ���ͼ��(nIconID:ͼ����ԴID, lpszText:ͼ��˵��)
	
	int LinkItemDlg(int iItem, CWnd* pDlgWnd);                              // ����ͼ������ҳ(iItem:��ҳ����ID,��0��ʼ,   pDlgWnd:��ҳ���ָ��)
	                                                                        // �ɹ�����ͼ�����ڵ�λ�ñ�ʶ,ʧ�ܷ���LB_ERR,���û����ؼ��������򷵻�LB_ERRSPACE

	
	CHILD_DLGINFO* GetMenuItem(int iItem);                             // ��ȡָ����ҳ�ṹ(iItem:Ҫ��ȡ��ҳ��������)
	                                                                        // ������ҳ�ṹָ��
	
	
	void OnNoFlickerPaint(CDC* pDC);



///------------------------------------������----------------------------------------------//
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
 	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
 
///------------------------------------�������---------------------------------------------//
	afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();

	void UpdataFont();    // ��������


	DECLARE_MESSAGE_MAP()

};


#endif // #if !defined(__XTOUTLOOKBAR_H__)

