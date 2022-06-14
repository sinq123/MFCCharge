
// TakeAndUpDlg.h : ͷ�ļ�
//

#pragma once

#include "URLCode.h"
#include "ZBase64.h"

// CTakeAndUpDlg �Ի���
class CTakeAndUpDlg : public CDialogZoom
{
// ����
public:
	CTakeAndUpDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TAKEANDUP_DIALOG };

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
	afx_msg void OnBnClickedBtnTake();
	afx_msg void OnBnClickedBtnPreviewPhotos();
	afx_msg void OnBnClickedBtnTakeUp();
	afx_msg void OnCbnSelchangeCb();

private:
	// ����
	CEdit m_edPlateNumber;
	// ��������
	CComboBox m_cbPlateType;
	// ������
	CComboBox m_cbTotaldetTimes;
	// ���浥����
	CEdit m_edReportNumber;
	// ��Ƭ����
	CComboBox m_cbPhotosType;
	// VIN
	CEdit m_edPlateVIN;
	// ������Ŀ
	CComboBox m_cbDetItem;
	// IP
	CEdit m_edVideoIP;
	// �˿�
	CEdit m_edVideoPort;
	// ͨ��
	CEdit m_edVideoChanner;
	// �û���
	CEdit m_edVideoUserName;
	// ����
	CEdit m_edVideoPassword;
	// ·��
	CEdit m_edVideoPath;

	// ��������˵��
	CLabel m_lbPlateTypeExplain;
	// ��Ƭ����˵��
	CLabel m_lbPhotosTypeExplain;
	// ������Ŀ����˵��
	CLabel m_lbDetItemExplain;

private:
	// ͨ�öԻ�������
	CFont m_fontDlgFont;
	// ͨ�öԻ��������С
	int m_nDlgFontSize;

private:

	CString m_strVideoIP;
	CString m_strVideoPort;
	CString m_strVideoUserName;
	CString m_strVideoPassword;
	CString m_strVideoChanner;
	CString m_strVideoPath;


private:
	// ��ʼ���ؼ�
	void InitCtrls(void);
	// ���öԻ�������
	void SetDlgFont(void);
	// ��ȡ����������
	void LoadConfig(void);
	// д�����������
	void SaveConfig(void);
	// ����Ŀ¼
	bool CreateMultipleDirectory(const CStringW& strPath);

private:
	// ��ȡ˵��
	CString GetExPlain(const int& nCode, const CString& strCode);
	void  PhotosToDetItem(const CString& strItem);
	void DetItemToPhotos(const CString& strPhotos);

private:
	// ����
	bool TakePhoto(CString& strPhotoPath, const CString& strPhotoName=L"");

	bool UploadPhoto(SUpGAMsg& sUpGAMsg);
	bool UploadPhoto(const SUpGaPhoto& sUpGaPhoto, const SGAWebService& sGAWebService, SUpGAMsg& sUpGAMsg);


private:
	CString UrlCodeOrNot(const wchar_t * const pwch);
	CString DecodeURI(LPCSTR szURIString);
	CString DecodeURI(LPCWSTR szURIString);
	void Base64EncodeRaw(LPCTSTR szFilePath, std::string &strCliper);
	void Base64Encode(LPCTSTR szFilePath, std::string &strCliper);
	std::string Base64EncodeRaw(LPCTSTR szFilePath);
	std::string Base64Encode(LPCTSTR szFilePath);
};
