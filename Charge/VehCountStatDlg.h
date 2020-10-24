#pragma once

#include "ChargeDlg.h"

// CVehCountStatDlg �Ի���

class CVehCountStatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVehCountStatDlg)

public:
	CVehCountStatDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVehCountStatDlg();

// �Ի�������
	enum { IDD = IDD_COUNT_STAT_VIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	// ���ؼ�
	CGridCtrl* m_pGridCtrl;
	CListCtrl m_lstVehCount;

	CDateTimeCtrl m_dtcBegTime;
	CDateTimeCtrl m_dtcEndTime;
	
	CButtonST m_btnStat;
	CButtonST m_btnPrint;
	CButtonST m_btnExport;

private:
	// ��ʼ���ؼ�
	void InitCtrls(void);
	// ��ʼ�����ؼ�
	void InitGirdCtrl(void);
	// ���öԻ�������
	void SetDlgFont(void);

private:
	// ͨ�öԻ�������
	CFont m_fontDlgFont;
	// ͨ�öԻ��������С
	int m_nDlgFontSize;

private:
	void DetChargeStat(void);

	CStringW ToStatusName(const CStringW& strStatusCode);
private:
	CChargeDlg* m_pChargeDlg;

private:
	friend class CChargeDlg;
};
