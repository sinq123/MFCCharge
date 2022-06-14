
// TakeAndUpDlg.h : 头文件
//

#pragma once

#include "URLCode.h"
#include "ZBase64.h"

// CTakeAndUpDlg 对话框
class CTakeAndUpDlg : public CDialogZoom
{
// 构造
public:
	CTakeAndUpDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TAKEANDUP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	// 车牌
	CEdit m_edPlateNumber;
	// 号牌种类
	CComboBox m_cbPlateType;
	// 检测次数
	CComboBox m_cbTotaldetTimes;
	// 报告单编码
	CEdit m_edReportNumber;
	// 照片种类
	CComboBox m_cbPhotosType;
	// VIN
	CEdit m_edPlateVIN;
	// 检验项目
	CComboBox m_cbDetItem;
	// IP
	CEdit m_edVideoIP;
	// 端口
	CEdit m_edVideoPort;
	// 通道
	CEdit m_edVideoChanner;
	// 用户名
	CEdit m_edVideoUserName;
	// 密码
	CEdit m_edVideoPassword;
	// 路径
	CEdit m_edVideoPath;

	// 号牌种类说明
	CLabel m_lbPlateTypeExplain;
	// 照片种类说明
	CLabel m_lbPhotosTypeExplain;
	// 检验项目种类说明
	CLabel m_lbDetItemExplain;

private:
	// 通用对话框字体
	CFont m_fontDlgFont;
	// 通用对话框字体大小
	int m_nDlgFontSize;

private:

	CString m_strVideoIP;
	CString m_strVideoPort;
	CString m_strVideoUserName;
	CString m_strVideoPassword;
	CString m_strVideoChanner;
	CString m_strVideoPath;


private:
	// 初始化控件
	void InitCtrls(void);
	// 设置对话框字体
	void SetDlgFont(void);
	// 读取检测参数配置
	void LoadConfig(void);
	// 写入检测参数配置
	void SaveConfig(void);
	// 创建目录
	bool CreateMultipleDirectory(const CStringW& strPath);

private:
	// 获取说明
	CString GetExPlain(const int& nCode, const CString& strCode);
	void  PhotosToDetItem(const CString& strItem);
	void DetItemToPhotos(const CString& strPhotos);

private:
	// 拍照
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
