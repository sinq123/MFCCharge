/*
* Copyright (c) 2010,佛山市南华仪器有限公司
* All rights reserved.
*
* 文件名称：FormViewZoom.h
* 文件标识：
* 描述：FormView的缩放
*
* 版本：1.0
* 作者：HuaBei
* 日期：2010-XX-XX
*
* 历史信息：
*
* 版本：1.0.1
* 日期：2010-12-24
* 作者：Raylee
* 描述：修改OnSize函数,因为有滚动条,所以最大化后不缩小
*
* 版本：1.0.0
* 日期：2010-10-09
* 作者：Lichm
* 描述：alpha
*/



#pragma once


#define ANCHORE_NONE    0x0001///< 不固定(按比例移动缩放)
#define ANCHORE_LEFT	0x0002///< 左边距固定
#define ANCHORE_TOP		0x0004///< 上边距固定
#define ANCHORE_RIGHT	0x0008///< 右边距固定
#define ANCHORE_BOTTOM	0x0010///< 底边距固定
#define	ANCHORE_HOR		0x0020///< 水平宽度固定
#define	ANCHORE_VER		0x0040///< 垂直高度固定
#define	ANCHORE_SIZE	(ANCHORE_HOR | ANCHORE_VER)///< 大小固定

// CFormViewZoom 窗体视图

class AFX_EXT_CLASS CFormViewZoom : public CFormView
{
	//DECLARE_DYNCREATE(CFormViewZoom)
	DECLARE_DYNAMIC(CFormViewZoom)
protected:
	CFormViewZoom(UINT nIDTemplate);           // 动态创建所使用的受保护的构造函数
	virtual ~CFormViewZoom();

//public:
	//enum { IDD = IDD_FORMVIEWZOOM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(void);    
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	DECLARE_MESSAGE_MAP()

protected:
	CFont m_TextFont;     ///< 使用字体	
	LOGFONT m_lf;         ///< 字体结构	 
	BOOL m_bAutoFitFont;  ///< 是否自动设置对话框字体
	int	m_minWidth;       ///< 最小宽度
	int m_minHeight;      ///< 最小高度
	CRect m_rcLast;       ///< 最后更新的客户区
	WORD m_DefaultCtrlStyle; ///< 默认控制方式
	CDWordArray	m_ItemsInfo; ///< 记录控件信息的可变数组

protected:
	int round(double num);  ///< 四舍五入	
	void UpdataFont();      ///< 更新字体

	/// @brief 获取取控件位移样式
	///	
	/// @param ItemID [in]控件ID
	/// @return 位移样式
	WORD GetItemCtrlStyle(WORD ItemID);
	
};


