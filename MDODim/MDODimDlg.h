
// MDODimDlg.h : 头文件
//

#pragma once

// CMDODimDlg 对话框
class CMDODimDlg : public CDialogEx
{
// 构造
public:
	CMDODimDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CMDODimDlg();
// 对话框数据
	enum { IDD = IDD_MDODIM_DIALOG };

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
	afx_msg void OnEnChangeEdFilterPlatenumber();
	afx_msg void OnLvnItemchangedLstDetWaiting(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnStartDet();
	afx_msg void OnBnClickedBtnPhotoDet();
	afx_msg void OnBnClickedBtnUploadDateDet();
	afx_msg void OnBnClickedBtnEndDet();
	afx_msg void OnBnClickedBtnSignOut();
	afx_msg void OnBnClickedBtnQuery();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	// 车牌号码
	CEdit m_edFilterPlateNumber;
	// 录入长
	CEdit m_edFInputDataLength;
	// 录入宽
	CEdit m_edFInputDataWidth;
	// 录入高
	CEdit m_edFInputDataHeight;
	// 列表LST_DET_WAITING
	CListCtrl m_lstDetWaiting;

	// 开始
	CButtonST m_btnStartDet;
	// 拍照
	CButtonST m_btnPhotoDet;
	// 数据上传
	CButtonST m_btnUpLoadDataDet;
	// 结束
	CButtonST m_btnSingOut;
	// 退出
	CButtonST m_btnEndDet;
	// 查询
	CButtonST m_btnQuery;


	// STANDARD_DATA
	CLabel m_lbStandardDataLenght;
	CLabel m_lbStandardDataWidth;
	CLabel m_lbStandardDataHeight;
	// UPPER_LIMIT_DATA
	CLabel m_lbUpperLimitDataLenght;
	CLabel m_lbUpperLimitDataWidth;
	CLabel m_lbUpperLimitDataHeight;
	// LOWER_LIMIT_DATA
	CLabel m_lbLowerLimitDataLenght;
	CLabel m_lbLowerLimitDataWidth;
	CLabel m_lbLowerLimitDataHeight;
	// 引车员，外检员
	CComboBox m_cbDriver;
	CComboBox m_cbExternalInspector;

private:
	// 通用对话框字体
	CFont m_fontDlgFont;
	// 通用对话框字体大小
	int m_nDlgFontSize;
	bool m_bConnectDB;
	// 数据库连接
	_ConnectionPtr m_pConnection;
	// 日志编号
	CString m_strRunningNumber;
	SVehDimensionInfo m_sVehDimInfo;
	// 联网平台代号
	int m_nNetPlatform;
private:
	// 检测开始时间
	COleDateTime m_odtBeginTime;
	// 检测结束时间
	COleDateTime m_odtEndTime;
private:
	// 初始化控件
	void InitCtrls(void);
	// 设置对话框字体
	void SetDlgFont(void);
	// 初始化检测业务列表
	void InitDetBsnList(void);
	// 初始化引车员
	void InitGuide(void);
private:
	// 控件随窗口变化而变化
	CPoint m_Old;//存放对话框的宽和高


private:
	// 设定标准，现值控件
	// 标准 1， 上限 2， 下限 3
	void SetStaAndLimitData(const int& nLabel, const CString& strLenght=L"", const CString& strWidth=L"", const CString& strHeight=L"");

	// 打开数据库
	void OpenDB(void);
	// 关闭数据库
	void CloseDB(void);

private:
	// 查询车辆信息
	void QueryInfo(void);
	// 获取标准，限值
	void GetVehInfoAndStandard(POSITION pos);
	// 判定长宽高是否合格
	bool JudgeLenAndWidAndHei(void);
private:
	// 开始检测
	// 结束检测
	// 保存检测数据
	// 拍照
	// 
public:
	
};
