/**
* @file DialogZoom.h
*
* 本文档定义了CDialogZoom这个类
*
* @author 刘宏荣
*/

////////////////////////////////////////////////////////////////
// 文件名   ：DialogZoom.h
// 版本     ：1.0                
// 主要功能 ：对话框缩放类，可根据对话大小变化改变所有控件的大小
//            和位置。
//            AutoFitFont() 自动放大/缩小字体；
//            SetDlgFont()  设置对话框字体名称和大小；
//            FreezingDlg() 冰冻对话框,屏蔽Esc；
//            SetBkTransparent() 对话框背景透明
//            SetItemCtrlStyle() 设置控件位移样式
//            SetDefaultCtrlStyle() 设置默认控件位移样式 
// 创建日期 ：2006.11.08
// 作者     ：刘宏荣
////////////////////////////////////////////////////////////////

#pragma once

#define ANCHORE_NONE    0x0001///< 不固定(按比例移动缩放)
#define ANCHORE_LEFT	0x0002///< 左边距固定
#define ANCHORE_TOP		0x0004///< 上边距固定
#define ANCHORE_RIGHT	0x0008///< 右边距固定
#define ANCHORE_BOTTOM	0x0010///< 底边距固定
#define	ANCHORE_HOR		0x0020///< 水平宽度固定
#define	ANCHORE_VER		0x0040///< 垂直高度固定
#define	ANCHORE_SIZE	(ANCHORE_HOR | ANCHORE_VER)///< 大小固定

// CDialogZoom 对话框

/**
* @brief CDialogZoom窗口缩放类
*
* 窗口缩放类，包括自动调整窗口控件大小和位置、设置窗口字体等扩展功能
*/
class AFX_EXT_CLASS CDialogZoom : public CDialog
{
	DECLARE_DYNAMIC(CDialogZoom)

public:
	/// 构造函数
	CDialogZoom(UINT nIDTemplate,CWnd* pParent = NULL);   // 标准构造函数
	/// 析构函数
	virtual ~CDialogZoom();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()



public:
	/// @brief 设置对话框字体名称和大小
	///
	/// 该函数会一次性改变所有对话框控件字体，对可自定义字体的控件同样生效，
	/// 请在自定义字体控件前使用
	/// 
	/// @param strFontName [in]字体名称
	/// @param nHeight [in]字体高度
	/// @return 无
	void SetDlgFont(CString strFontName, int nHeight); 

	/// @brief 冻结对话框
	///
	/// 屏蔽Esc等使对话框退出的快捷键
	///
	/// @paran bEnalbe [in]是否生效，TRUE：是，FALSE：否
	/// @return 无
	void FreezingDlg(BOOL bEnable = 1);

	/// @brief 自动根据对话框高度变化设置字体
	///
	/// @param void 无
	/// @return 无
	void AutoFitFont();

	/// @brief 设置对话框背景透明
	/// 
	/// @param void 无
	/// @return 无
	void SetBkTransparent();// 设置对话框背景透明

	/// @brief 设置控件位移样式
	///
	/// @param ItemID [in]控件ID
	/// @param Anchore [in]位移样式，可以是以下值：
	/// ANCHORE_NONE 不固定(按比例移动缩放)
	/// ANCHORE_LEFT 左边距固定
	/// ANCHORE_TOP 上边距固定
	/// ANCHORE_RIGHT 右边距固定
	/// ANCHORE_BOTTOM 底边距固定
	/// ANCHORE_HOR 水平宽度固定
	/// ANCHORE_VER 垂直高度固定
	/// ANCHORE_SIZE 大小固定
	/// @return 无
	void SetItemCtrlStyle(WORD ItemID,WORD Anchore);

	/// @brief 获取取控件位移样式
	///	
	/// @param ItemID [in]控件ID
	/// @return 位移样式，具体样式请看函数SetItemCtrlStyle
	WORD GetItemCtrlStyle(WORD ItemID);

	/// @brief 设置默认控件位移样式
	///
	/// @param Anchore [in]位移样式
	/// @return 无
	void SetDefaultCtrlStyle(WORD Anchore);

	/// @brief 取默认控件位移样式
	///
	/// @param void 无
	/// @retrun 默认的位移样式，具体样式请看函数SetItemCtrlStyle
	WORD GetDefaultCtrlStyle();

	/// 此函数已经弃用
	//void SetOwnerDraw(BOOL bOwnerDraw,Color Cr1,CRect rt1,Color Cr2,CRect rt2);

//protected:
//	/// @brief 显示提示信息
//	///
//	/// @param message [in]内容
//	/// @param overtime [in]倒计时
//	/// @param flashText [in]是否闪烁
//	/// @param redText [in]是否红色字体
//	/// @param Type [in]按钮类型
//	/// @param WindowPos [in]窗口位置，0:中间；1：上部；2：下部
//	int ShowMsg(CString message, int overtime=0, BOOL flashText = 0,BOOL redText = 0, UINT Type=MB_OK, int WindowPos=0);

public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* pMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);// 针对对话框
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);//针对对话框控件
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	CFont m_TextFont;     ///< 使用字体	
	LOGFONT m_lf;         ///< 字体结构	 
	CRect m_rcLast;       ///< 最后更新的客户区
	BOOL m_bIsFreezing;   ///< 是否冰冻对话框
	BOOL m_bAutoFitFont;  ///< 是否自动设置对话框字体
	BOOL m_bBkTransparent;///< 是否透明对话框背景
	int	m_minWidth;       ///< 最小宽度
	int m_minHeight;      ///< 最小高度
	CDWordArray	m_ItemsInfo; ///< 记录控件信息的可变数组
	WORD m_DefaultCtrlStyle; ///< 默认控制方式

	int round(double num);///< 四舍五入	
	void UpdataFont();///< 更新字体

	BOOL m_bOwnerDraw;    ///<自画
	CRect m_Rt1,m_Rt2;    ///<自画
	//Color m_Cr1,m_Cr2;    ///<自画
};
