
// FFWDIMDlg.h : 头文件
//

#pragma once


// CFFWDIMDlg 对话框
class CFFWDIMDlg : public CDialogEx
{
// 构造
public:
	CFFWDIMDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CFFWDIMDlg();
// 对话框数据
	enum { IDD = IDD_FFWDIM_DIALOG };

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
	afx_msg void OnBnClickedBtnForward();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
// 隐藏在托盘
private:
	NOTIFYICONDATA m_nid;
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
	CEdit m_edMCSharePath;
	CEdit m_edDetSharePath;
	CButtonST m_btnForward;
	// 日志提示
	CRichEditCtrl m_reLog;
private:
	// 通用对话框字体
	CFont m_fontDlgFont;
	// 通用对话框字体大小
	int m_nDlgFontSize;

	CString m_strLogFilePath;

	bool m_bLogFile;

private:
	void LoadConfig(void);
	void SaveConfig(void);

	void Forward(void);
	// 生成日志文件
	void GenLogFile(void);
private:
	// File是否存在
	bool IsFileExist(CString& strFile);
	// 删除文件
	bool DelFile(CString& strFile);
	// 移动文件
	bool MoveFileTo(CString& strFromPath, CString& strToPath);

	// 记录开始检测车牌，限值等信息
	void RecordBegDet(void);
	// 记录结束的检测车牌和信息
	void RecordEndDet(void);

	// 写入日志信息，方便查看检测进度
	void PrintLog(LPCTSTR szFormat, ...);
};
