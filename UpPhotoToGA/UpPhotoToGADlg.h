
// UpPhotoToGADlg.h : ͷ�ļ�
//

#pragma once


// CUpPhotoToGADlg �Ի���
class CUpPhotoToGADlg : public CDialogEx
{
// ����
public:
	CUpPhotoToGADlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UPPHOTOTOGA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


private:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
	CEdit m_edPlateNumber;
	CEdit m_edTotalDetTimes;
	CEdit m_edPlateType;
	CEdit m_edPhotoType;
	CEdit m_edDetItem;
	CEdit m_edReportNumber;
	CEdit m_edVIN;
	CEdit m_edPhotPath;

private:
	bool IsGetEdit(SDetLog& sDetLog, SDetTimes& sDetTimes, SHisVehInfo& sHisVehInfo, CStringW& strPhotoPath, CStringW& strDetItem, CStringW& strPhotoType);
};
