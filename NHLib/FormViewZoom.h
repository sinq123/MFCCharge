/*
* Copyright (c) 2010,��ɽ���ϻ��������޹�˾
* All rights reserved.
*
* �ļ����ƣ�FormViewZoom.h
* �ļ���ʶ��
* ������FormView������
*
* �汾��1.0
* ���ߣ�HuaBei
* ���ڣ�2010-XX-XX
*
* ��ʷ��Ϣ��
*
* �汾��1.0.1
* ���ڣ�2010-12-24
* ���ߣ�Raylee
* �������޸�OnSize����,��Ϊ�й�����,������󻯺���С
*
* �汾��1.0.0
* ���ڣ�2010-10-09
* ���ߣ�Lichm
* ������alpha
*/



#pragma once


#define ANCHORE_NONE    0x0001///< ���̶�(�������ƶ�����)
#define ANCHORE_LEFT	0x0002///< ��߾�̶�
#define ANCHORE_TOP		0x0004///< �ϱ߾�̶�
#define ANCHORE_RIGHT	0x0008///< �ұ߾�̶�
#define ANCHORE_BOTTOM	0x0010///< �ױ߾�̶�
#define	ANCHORE_HOR		0x0020///< ˮƽ��ȹ̶�
#define	ANCHORE_VER		0x0040///< ��ֱ�߶ȹ̶�
#define	ANCHORE_SIZE	(ANCHORE_HOR | ANCHORE_VER)///< ��С�̶�

// CFormViewZoom ������ͼ

class AFX_EXT_CLASS CFormViewZoom : public CFormView
{
	//DECLARE_DYNCREATE(CFormViewZoom)
	DECLARE_DYNAMIC(CFormViewZoom)
protected:
	CFormViewZoom(UINT nIDTemplate);           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(void);    
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	DECLARE_MESSAGE_MAP()

protected:
	CFont m_TextFont;     ///< ʹ������	
	LOGFONT m_lf;         ///< ����ṹ	 
	BOOL m_bAutoFitFont;  ///< �Ƿ��Զ����öԻ�������
	int	m_minWidth;       ///< ��С���
	int m_minHeight;      ///< ��С�߶�
	CRect m_rcLast;       ///< �����µĿͻ���
	WORD m_DefaultCtrlStyle; ///< Ĭ�Ͽ��Ʒ�ʽ
	CDWordArray	m_ItemsInfo; ///< ��¼�ؼ���Ϣ�Ŀɱ�����

protected:
	int round(double num);  ///< ��������	
	void UpdataFont();      ///< ��������

	/// @brief ��ȡȡ�ؼ�λ����ʽ
	///	
	/// @param ItemID [in]�ؼ�ID
	/// @return λ����ʽ
	WORD GetItemCtrlStyle(WORD ItemID);
	
};


