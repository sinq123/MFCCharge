#pragma once

#include "ToolTipListCtrl.h"

// CBookkeepingCollectionView ������ͼ

class CBookkeepingCollectionView : public CFormView
{
	DECLARE_DYNCREATE(CBookkeepingCollectionView)

protected:
	CBookkeepingCollectionView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CBookkeepingCollectionView();

public:
	enum { IDD = IDD_BOOKKEEPING_COLLECTION_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedBtnUplis();
	afx_msg void OnBnClickedBtn();
private:
	// ͨ�öԻ�������
	CFont m_fontDlgFont;
	// ͨ�öԻ��������С
	int m_nDlgFontSize;

private:
	// ��ʼ���ؼ�
	void InitCtrls(void);
	// ���öԻ�������
	void SetDlgFont(void);
	// ��ʼ�����ҵ���б�
	void InitDetBsnList(void);

private:
	// �ؼ��洰�ڱ仯���仯
	CPoint m_Old;//��ŶԻ���Ŀ�͸�

private:
	// �ؼ�
	// �б�
	CToolTipListCtrl m_lsBookkeeping;
	// ��־
	CRichEditCtrl m_reLog;
	// �����б�
	CButtonST m_btnUplis;
	// �տ���
	CXPGroupBox m_gbAmount_Collected;
	CLabel m_lbAmount_Collected;
	CNumericEdit m_edAmount_Collected;
	CButtonST m_btnAmount_Collected;

private:
	// ������¼
	void PrintLog(LPCTSTR szFormat, ...);
private:
	// ����
	void UPLisBookkeeping(void);
private:
	// ��տؼ�����
	void ClearControl(void);
private:
	// �տ�
	bool CollectionToDB(void);
	// ���浽Charge����
	bool SaveToChargeDB(void);


};



