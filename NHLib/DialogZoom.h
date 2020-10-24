/**
* @file DialogZoom.h
*
* ���ĵ�������CDialogZoom�����
*
* @author ������
*/

////////////////////////////////////////////////////////////////
// �ļ���   ��DialogZoom.h
// �汾     ��1.0                
// ��Ҫ���� ���Ի��������࣬�ɸ��ݶԻ���С�仯�ı����пؼ��Ĵ�С
//            ��λ�á�
//            AutoFitFont() �Զ��Ŵ�/��С���壻
//            SetDlgFont()  ���öԻ����������ƺʹ�С��
//            FreezingDlg() �����Ի���,����Esc��
//            SetBkTransparent() �Ի��򱳾�͸��
//            SetItemCtrlStyle() ���ÿؼ�λ����ʽ
//            SetDefaultCtrlStyle() ����Ĭ�Ͽؼ�λ����ʽ 
// �������� ��2006.11.08
// ����     ��������
////////////////////////////////////////////////////////////////

#pragma once

#define ANCHORE_NONE    0x0001///< ���̶�(�������ƶ�����)
#define ANCHORE_LEFT	0x0002///< ��߾�̶�
#define ANCHORE_TOP		0x0004///< �ϱ߾�̶�
#define ANCHORE_RIGHT	0x0008///< �ұ߾�̶�
#define ANCHORE_BOTTOM	0x0010///< �ױ߾�̶�
#define	ANCHORE_HOR		0x0020///< ˮƽ��ȹ̶�
#define	ANCHORE_VER		0x0040///< ��ֱ�߶ȹ̶�
#define	ANCHORE_SIZE	(ANCHORE_HOR | ANCHORE_VER)///< ��С�̶�

// CDialogZoom �Ի���

/**
* @brief CDialogZoom����������
*
* ���������࣬�����Զ��������ڿؼ���С��λ�á����ô����������չ����
*/
class AFX_EXT_CLASS CDialogZoom : public CDialog
{
	DECLARE_DYNAMIC(CDialogZoom)

public:
	/// ���캯��
	CDialogZoom(UINT nIDTemplate,CWnd* pParent = NULL);   // ��׼���캯��
	/// ��������
	virtual ~CDialogZoom();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()



public:
	/// @brief ���öԻ����������ƺʹ�С
	///
	/// �ú�����һ���Ըı����жԻ���ؼ����壬�Կ��Զ�������Ŀؼ�ͬ����Ч��
	/// �����Զ�������ؼ�ǰʹ��
	/// 
	/// @param strFontName [in]��������
	/// @param nHeight [in]����߶�
	/// @return ��
	void SetDlgFont(CString strFontName, int nHeight); 

	/// @brief ����Ի���
	///
	/// ����Esc��ʹ�Ի����˳��Ŀ�ݼ�
	///
	/// @paran bEnalbe [in]�Ƿ���Ч��TRUE���ǣ�FALSE����
	/// @return ��
	void FreezingDlg(BOOL bEnable = 1);

	/// @brief �Զ����ݶԻ���߶ȱ仯��������
	///
	/// @param void ��
	/// @return ��
	void AutoFitFont();

	/// @brief ���öԻ��򱳾�͸��
	/// 
	/// @param void ��
	/// @return ��
	void SetBkTransparent();// ���öԻ��򱳾�͸��

	/// @brief ���ÿؼ�λ����ʽ
	///
	/// @param ItemID [in]�ؼ�ID
	/// @param Anchore [in]λ����ʽ������������ֵ��
	/// ANCHORE_NONE ���̶�(�������ƶ�����)
	/// ANCHORE_LEFT ��߾�̶�
	/// ANCHORE_TOP �ϱ߾�̶�
	/// ANCHORE_RIGHT �ұ߾�̶�
	/// ANCHORE_BOTTOM �ױ߾�̶�
	/// ANCHORE_HOR ˮƽ��ȹ̶�
	/// ANCHORE_VER ��ֱ�߶ȹ̶�
	/// ANCHORE_SIZE ��С�̶�
	/// @return ��
	void SetItemCtrlStyle(WORD ItemID,WORD Anchore);

	/// @brief ��ȡȡ�ؼ�λ����ʽ
	///	
	/// @param ItemID [in]�ؼ�ID
	/// @return λ����ʽ��������ʽ�뿴����SetItemCtrlStyle
	WORD GetItemCtrlStyle(WORD ItemID);

	/// @brief ����Ĭ�Ͽؼ�λ����ʽ
	///
	/// @param Anchore [in]λ����ʽ
	/// @return ��
	void SetDefaultCtrlStyle(WORD Anchore);

	/// @brief ȡĬ�Ͽؼ�λ����ʽ
	///
	/// @param void ��
	/// @retrun Ĭ�ϵ�λ����ʽ��������ʽ�뿴����SetItemCtrlStyle
	WORD GetDefaultCtrlStyle();

	/// �˺����Ѿ�����
	//void SetOwnerDraw(BOOL bOwnerDraw,Color Cr1,CRect rt1,Color Cr2,CRect rt2);

//protected:
//	/// @brief ��ʾ��ʾ��Ϣ
//	///
//	/// @param message [in]����
//	/// @param overtime [in]����ʱ
//	/// @param flashText [in]�Ƿ���˸
//	/// @param redText [in]�Ƿ��ɫ����
//	/// @param Type [in]��ť����
//	/// @param WindowPos [in]����λ�ã�0:�м䣻1���ϲ���2���²�
//	int ShowMsg(CString message, int overtime=0, BOOL flashText = 0,BOOL redText = 0, UINT Type=MB_OK, int WindowPos=0);

public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* pMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);// ��ԶԻ���
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);//��ԶԻ���ؼ�
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	CFont m_TextFont;     ///< ʹ������	
	LOGFONT m_lf;         ///< ����ṹ	 
	CRect m_rcLast;       ///< �����µĿͻ���
	BOOL m_bIsFreezing;   ///< �Ƿ�����Ի���
	BOOL m_bAutoFitFont;  ///< �Ƿ��Զ����öԻ�������
	BOOL m_bBkTransparent;///< �Ƿ�͸���Ի��򱳾�
	int	m_minWidth;       ///< ��С���
	int m_minHeight;      ///< ��С�߶�
	CDWordArray	m_ItemsInfo; ///< ��¼�ؼ���Ϣ�Ŀɱ�����
	WORD m_DefaultCtrlStyle; ///< Ĭ�Ͽ��Ʒ�ʽ

	int round(double num);///< ��������	
	void UpdataFont();///< ��������

	BOOL m_bOwnerDraw;    ///<�Ի�
	CRect m_Rt1,m_Rt2;    ///<�Ի�
	//Color m_Cr1,m_Cr2;    ///<�Ի�
};
