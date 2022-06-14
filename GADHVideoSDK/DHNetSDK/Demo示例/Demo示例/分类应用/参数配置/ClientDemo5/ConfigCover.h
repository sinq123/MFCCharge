#if !defined(AFX_CONFIGCOVER_H__426AD004_1BE9_4A91_83A7_E50A813F4900__INCLUDED_)
#define AFX_CONFIGCOVER_H__426AD004_1BE9_4A91_83A7_E50A813F4900__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigCover.h : header file
//
#include "dhnetsdk.h"

/////////////////////////////////////////////////////////////////////////////
// CConfigCover dialog

class CConfigCover : public CDialog
{
// Construction
public:
	void CleanAll();
	void InitDlgInfo(BYTE nLength);
	CConfigCover(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigCover)
	enum { IDD = IDD_CONFIG_COVER };
	CComboBox	m_ctlVideoWidget;
	CComboBox	m_ctlCoverType;
	CListCtrl	m_ctlCoverLst;
	CComboBox	m_ctlChannel;
	BOOL        m_bEncodeEnable;
	BOOL        m_bPreViewEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigCover)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigCover)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonModify();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonReadall();
	afx_msg void OnSelchangeComboChanno();
	afx_msg void OnItemchangedListCovers(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCancelMode();
//	afx_msg void OnEditchangeComboVideowidget();
	afx_msg void OnSelchangeComboVideowidget();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InsertListView(CString strID, 
		CString strLeft, CString strTop, CString strRight, CString strBottom, 
		CString strBlendMain, CString strBlendExtra1, CString strBlendExtra2, CString strBlendExtra3,CString strBlendBlendSnapshot,
		CString strFRed, CString strFGreen, CString strFBule, CString strFAlpha,
		CString strBRed, CString strBGreen, CString strBBlue, CString strBAlpha);

	void ShowVideoWidgetChannelTitle(AV_CFG_VideoWidgetChannelTitle *pChannelTitleInfo);
	void ShowVideoWidgetTimeTitle(AV_CFG_VideoWidgetTimeTitle *pTimeTitleInfo);
	void ShowVideoWidgetCover(AV_CFG_VideoWidgetCover *pVideoWidgetCover, int nNum);
	void SaveVideoWidgetChannelTitle(AV_CFG_VideoWidgetChannelTitle *pChannelTitleInfo);
	void SaveVideoWidgetTimeTitle(AV_CFG_VideoWidgetTimeTitle *pTimeTitleInfo);
	void SaveVideoWidgetCover(AV_CFG_VideoWidgetCover *pVideoWidgetCover, int *nNum);
	BOOL JudgeColor(int nColor);
	BOOL JudgeCoordinate(int nCoordinate);


	int m_nCurChannel;
	int m_nChannelCount;
	DHDEV_VIDEOCOVER_CFG m_channelCoverInfo[32];
	void SaveChannelInfo(int nNum,int nVideoWidget);
	void InitListView();
	BOOL m_bNewProtocol;//32б╥ртио
	AV_CFG_VideoWidget *m_pstVideoWidget;
	int	 m_nVideoWidget;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGCOVER_H__426AD004_1BE9_4A91_83A7_E50A813F4900__INCLUDED_)
