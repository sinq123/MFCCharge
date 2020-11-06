
// UpPhotoToGADlg.h : 头文件
//

#pragma once


// CUpPhotoToGADlg 对话框
class CUpPhotoToGADlg : public CDialogEx
{
// 构造
public:
	CUpPhotoToGADlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_UPPHOTOTOGA_DIALOG };

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
