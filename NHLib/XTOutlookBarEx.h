/////////////////////////////////////////////////////////////////////////////////////
// 文件名   ：CXTOutlookBarEx
// 版本     ：1.0                
// 主要功能 ：实现outlookbar界面
// 创建日期 ：2006.11.15
// 作者     ：罗金成

// 用法     ：拉listbox控件设置其变量为CXTOutlookBarEx类型,注：
//            子对话框（Dialog）必须先用SetDlgSize指定大小，才能添加
// 实例     ：在类A中调用outlookbar
//            CXTOutlookBarEx m_OutlookBar;          新增控件listbox,为其添加变量
//            CDlg1 m_dlg1; CDlg2 m_dlg2;            在A.h 建立要加载的对话框对象
//	          m_OutlookBar.SetColors(RGB(0xff,0xff,0xff), RGB(46,134,199)); 设置字体颜色,背景颜色
//	          m_OutlookBar.SetOutlookFont("宋体",15);                       设置字体
//	          m_OutlookBar.SetIconSize(48, 48);                             设置图标大小
//	          m_OutlookBar.SetDlgSize(GetDlgItem(IDC_STATIC_EDGE));         指定子对话框区域大小
//            m_OutlookBar.AddDialog(&m_dlg1,IDD_DIALOG1,IDI_ICON1,"自由滑行");
//            m_OutlookBar.AddDialog(&m_dlg2,IDD_DIALOG2,IDI_ICON2,"定载荷滑行");

/////////////////////////////////////////////////////////////////////////////////////

// 版本：1.0.3
// 日期：2010-03-05
// 作者：Cui
// 描述：修改关于用安全字符串函数代替不安全字符串函数的warning：用wcscpy_s代替_tcscpy

//版本：1.0.2
//日期：2010-1-13
//作者：Raylee
//描述：修改函数SetDlgSize()，设置子页区域时顺便把原控件隐藏

//版本：1.0.1 
//日期：2009-10-12
//作者：Raylee
//描述：修改函数OnVScroll和OnMouseWheel，消除滚动时闪烁的问题

#if !defined(__XTOUTLOOKBAREX_H__)
#define __XTOUTLOOKBAREX_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxtempl.h>
#define XTWM_OUTBAR_NOTIFY		(WM_USER+1019)
#define WM_ACCEPTMESSAG WM_USER+1112

/////////////////////////////////////////////////////////////////////////////
struct CHILD_DLGINFO             //子页对话框结构
{
    HICON   m_hIcon;    // 图标句柄
    int     m_nIndex;   // 对话框索引ID,从零开始
    CString m_strText;  // 图标说明
	CWnd*	m_wnd;      // 子页句柄指针
	bool    m_Selected; // 是否被选中
};/////////////////////////////////////////////////////////////////////////////


class AFX_EXT_CLASS CXTOutlookBarEx : public CListBox
{
    DECLARE_DYNAMIC(CXTOutlookBarEx)

public:

    CXTOutlookBarEx();

    virtual ~CXTOutlookBarEx();
///// ---------------------------------------内部资源---------------------------------------//
protected:
	int m_nItem;                           // 子页个数,初始为0;
	CRect m_rcDlgs;                        // 子页对话框区域
	CWnd* m_wndDlgsRect;                   // 子页区域控件窗口指针
	LOGFONT m_lf;                          // 字体结构	
    CFont m_TextFont;                      // 字体
protected:

	int        m_cxIcon;         // 图标宽度
	int        m_cyIcon;         // 图标高度
    bool       m_bHilight;       // 图标被选中时
    bool       m_bLBDown;        // 图标被按下时
    CPoint     m_point;          // 当前获得焦点的图标坐标holds the cursor position
    COLORREF   m_clrBack;        // 背景颜色
    COLORREF   m_clrText;        // 文字颜色

	CList<CHILD_DLGINFO*,CHILD_DLGINFO*> m_arContentItems;
public:
    int        m_nIndex;         // 当前选中的对话框标识

public:
	//---------------------------------外部接口----------------------------------------------//
	void SetFontSize(int nHeight);//设置字体大小
	void SetFontName(CString strFontName);//设置字体名称
	void SetOutlookFont(CString strFontName,int nHeight);//设置字体名称,大小

	void SetColors(COLORREF clrText, COLORREF clrBack);                 // 设置颜色(clrText:文字颜色 ,clrBack:背景颜色)
	void SetIconSize(int nCxIcon,int nCyIcon );                         // 设置图标大小
	void SetDlgSize(CWnd* wdDlgs);                                      // 设定子页对话框区域
	bool AddDialog(CDialog* dlg,UINT nDlgID, UINT nIconID, CString nIconText);      // 添加子页(dlg:子页句柄   nDlgID:子页对话框资源ID  
                                                                                    //         nIconID:图标资源ID   nIconText:图标描述)

	void EnableDlg(int nPage);                                          //使指定页可用
 	void DisableDlg(int nPage);                                         //使指定页不可用
	void DisableOtherDlg(void);                                         //使除当前页的其它页面不可用
    void EnableAllDlg(void);                                            //使所有页面可用
	int ShowItemDlg(int iItem);                                         // 显示子页(iItem:子页索引ID,从0开始)
    void HideAllDlg(void);                                              //隐藏所有子页
	CString GetIconText(int nIcon);                                     //获取指定图标说明文字
	////////////////////////////////////////////////////////////////////////////////////////////

   //---------------------------------内部接口----------------------------------------------//
protected:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);               // 绘制outlookbar
    virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);      // 设置列表项高度

	int InsertMenuItem(int iIndex, UINT nIconID, LPCTSTR lpszText); 	    // 插入图标(iIndex:要插入的位置, nIconID:图标资源ID, lpszText:图标说明),
	                                                                        // 成功返回插入的位置标识,失败返回LB_ERR,如果没多余控件供插入则返回LB_ERRSPACE

	int AddMenuItem(UINT nIconID, LPCTSTR lpszText);                        // 添加图标(nIconID:图标资源ID, lpszText:图标说明)
	
	int LinkItemDlg(int iItem, CWnd* pDlgWnd);                              // 关联图标与子页(iItem:子页索引ID,从0开始,   pDlgWnd:子页句柄指针)
	                                                                        // 成功返回图标所在的位置标识,失败返回LB_ERR,如果没多余控件供插入则返回LB_ERRSPACE

	
	CHILD_DLGINFO* GetMenuItem(int iItem);                             // 获取指定子页结构(iItem:要获取子页的索引号)
	                                                                        // 返回子页结构指针
	
	
	void OnNoFlickerPaint(CDC* pDC);



///------------------------------------鼠标操作----------------------------------------------//
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
 	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
 
///------------------------------------界面绘制---------------------------------------------//
	afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();

	void UpdataFont();    // 更新字体


	DECLARE_MESSAGE_MAP()

};


#endif // #if !defined(__XTOUTLOOKBAR_H__)

