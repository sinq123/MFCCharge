#pragma once


// CMDODimDlg_NH 对话框

struct SGTStatus
{
	//外观检验号
	std::wstring strRunningNumber;
	//车辆牌号
	std::wstring strPlateNumber;
	//号牌种类
	std::wstring strPlateType;
	//状态
	std::wstring strStatus;
	//外廓状态
	std::wstring strDimStatus;
	//整备质量状态
	std::wstring strUMStatus;
	//备注说明
	std::wstring strRemark;
	//时间
	std::wstring strTimes;
};

class CMDODimDlg_NH : public CDialogEx
{
	DECLARE_DYNAMIC(CMDODimDlg_NH)

public:
	CMDODimDlg_NH(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMDODimDlg_NH();

// 对话框数据
	enum { IDD = IDD_MDODIM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	afx_msg void OnBnClickedCheIsUseStaGb1589();
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
	// 显示信息
	CLabel m_lbShowInfoTest;
	// 是否使用GB1589标准
	CButtonST m_chkIsUseStaGB1589;
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
	SDetLog m_sDetLog;
	SDetTimes m_sDetTimes;
	SVehDimensionInfo m_sVehDimInfo;
	SHisVehInfo m_sHisVehInfo;
	SDetStandard m_sDetStandard;

	CString m_strRunningNumberSen;
	SDetLog m_sDetLogSen;
	SDetTimes m_sDetTimesSen;
	SVehDimensionInfo m_sVehDimInfoSen;
	SHisVehInfo m_sHisVehInfoSen;
	SDetStandard m_sDetStandardSen;
	// 联网平台代号
	int m_nNetPlatform;
	// 是否检测轴距
	bool m_bWheelBase;
	// 是否检测轴距(新车检测)
	bool m_bWheelBaseNew;
	// 是否检测销轴距
	bool m_bPinbase;
	// 是否检测销轴距(新车检测)
	bool m_bPinbaseNew;
	// 是否修正二维图
	bool m_bM2D;

	// 
	CString m_strBodyPhotoPath;
	CString m_strTopPhotoPath;
	//
	bool m_bIsUseGB1589;
private:
	// 初始化控件
	void InitCtrls(void);
	// 设置对话框字体
	void SetDlgFont(void);
	// 初始化检测业务列表
	void InitDetBsnList(void);
	// 初始化引车员
	void InitGuide(void);
	// 读取检测参数配置
	void LoadConfig(void);

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

private:
	// 是否读取检测过程提示信息
	bool m_bCFG_ReadDetInfo;
	// 数据交换文件夹路径
	CStringW m_strDEFolderPath;
	// BegCTDet.ini路径
	CStringW m_strBegIniPath;
	// EndCTDet.ini路径
	CStringW m_strEndIniPath;
	// Display.txt路径
	CStringW m_strDisplayTxtPath;
	// 
	CStringW m_strLastLedInfo;
	// 厂家类型
	CStringW m_strDimEqu;
	SGTStatus m_sGTStatus;
private:
	// 检测开始时间
	COleDateTime m_odtBeginTime;
	// 检测结束时间
	COleDateTime m_odtEndTime;

private:
	// 导出数据
	// bIsRemDet:是否免除检测，true:免除,false:不免除
	void ExportData(const bool bIsRemDet = false);
	// 导入数据（并验证数据）
	bool ImportData(void);
	// BegCTDet.ini是否存在
	bool IsBegIniExist(void);
	// EndCTDet.ini是否存在
	bool IsEndIniExist(void);
	// 删除BegCTDet.ini
	bool DelBegIni(void);
	// 删除EndCTDet.ini
	bool DelEndIni(void);
	// 读取并显示LedInfo.txt内容
	bool ReadAndShowLedInfoTxt(void);
	// 广泰状态
	void StatusConfig(void);
	// 广泰车辆信息和检测
	void CarInfoData(void);
	bool IsGZEndIniNow(const CStringW& strPath);
	void GZImportData(const CStringW& strPath, const bool& bSen=false);
	int AnalogData(const int& nUpLimit, const int& nDownLimit);
private:
	// 保存照片
	void SavePhoto();
	// 保存检测数据
	void SaveDetData(void);
	// 保存第二辆车数据
	void SaveSecVehDetData(void);

private:
	// bmp转jpg
	bool BMPTOJPG(const CString& srtBmpPath, const CString& strJpgPath);
	// jpg转bmp
	bool JPGTOBMP(const CString& strJpgPath, const CString& srtBmpPath);
	// 增加水印
	void AddWatermark(const CString& strJpgPath, const CString& strFildName);
	// 图片添加文字
	void ImageAppendText(const std::wstring& strSource, const std::wstring& strTarget, const std::wstring& strText);
	// 图片添加文字
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

};
