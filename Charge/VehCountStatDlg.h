#pragma once

#include "ChargeDlg.h"

// CVehCountStatDlg 对话框

class CVehCountStatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVehCountStatDlg)

public:
	CVehCountStatDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVehCountStatDlg();

// 对话框数据
	enum { IDD = IDD_COUNT_STAT_VIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
private:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickedBtnStat();
	afx_msg void OnClickedBtnPrint();
	afx_msg void OnClickedBtnExport();
	
private:
	// 表格控件
	CGridCtrl* m_pGridCtrl;
	CListCtrl m_lstVehCount;

	CDateTimeCtrl m_dtcBegTime;
	CDateTimeCtrl m_dtcEndTime;
	
	CButtonST m_btnStat;
	CButtonST m_btnPrint;
	CButtonST m_btnExport;

private:
	// 初始化控件
	void InitCtrls(void);
	// 初始化表格控件
	void InitGirdCtrl(void);
	// 设置对话框字体
	void SetDlgFont(void);

private:
	// 通用对话框字体
	CFont m_fontDlgFont;
	// 通用对话框字体大小
	int m_nDlgFontSize;

private:
	void DetChargeStat(void);

	CStringW ToStatusName(const CStringW& strStatusCode);
private:
	CChargeDlg* m_pChargeDlg;

private:
	friend class CChargeDlg;
};
