#pragma once



// CFeeTablesView 窗体视图

class CFeeTablesView : public CFormView
{
	DECLARE_DYNCREATE(CFeeTablesView)

protected:
	CFeeTablesView();           // 动态创建所使用的受保护的构造函数
	virtual ~CFeeTablesView();

public:
	enum { IDD = IDD_FEE_TABLES_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	virtual void OnInitialUpdate();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnStat();
	afx_msg void OnBnClickedBtnPrint();
	afx_msg void OnBnClickedBtnExport();

private:
	// 通用对话框字体
	CFont m_fontDlgFont;
	// 通用对话框字体大小
	int m_nDlgFontSize;
	CPoint m_Old;//存放对话框的宽和高

private:
	// 初始化表格控件
	void InitGirdCtrl(void);
	// 初始化控件
	void InitCtrls(void);
	// 设置对话框字体
	void SetDlgFont(void);

private:
	// 表格控件
	CGridCtrl* m_pGridCtrl;
	CListCtrl m_lstVehCount;

	CDateTimeCtrl m_dtcBegTime;
	CDateTimeCtrl m_dtcEndTime;
	
	CButtonST m_btnStat;
	CButtonST m_btnPrint;
	CButtonST m_btnExport;

private:
	int m_nTotNum;
	float m_fAmountOfCharges;

private:
	CString GetSQL(void);
	float m_fTotalAmount;
	// 检测类别总金额
	// 在用车检验（定检）
	// 技术等级评定
	// 在用车检验（定检）//技术等级评定
	// 注册登记检验
	// 注册登记检验//技术等级评定
	// 在用车检验（非定检)
	// 临时检验
	// 杂项
	void TotalAmountOfTestCategory(const int& nDetType, const float& fTotalAmount);

	// 在用车
	// strSQL:数据库参数
	// 农用(电动）运输车
	void DetTypeRIVehATVeh(const CString& strSQL);
	// 客车：9人以下
	// strSQL:数据库参数
	// nNumber:默认参考下面
	// 1.9人以下
	// 2.10-19
	// 3.20以上
	void DetTypeRIVehPCar(const CString& strSQL, const int& nNumber);
	// 校车 
	// strSQL:数据库参数
	// nNumber:默认参考下面
	// 1.10-19
	// 2.20以上
	void DetTypeRIVehSchbus(const CString& strSQL, const int& nNumber);
	// 货车 危险
	// strSQL:数据库参数
	// nTonnage:吨位
	// bDANGER:是否货运
	// 1.总质量4.5t以下
	// 2.总质量4.5-12t
	// 3.总质量12-30t
	// 4.总质量30t以上
	void DetTypeRIVehTruck(const CString& strSQL, const int& nTonnage, const bool& bDANGER=false);
	// 挂车 Trailer
	// strSQL:数据库参数
	// bDANGER:是否货运
	void DetTypeRIVehTrailer(const CString& strSQL,/* const int& nTonnage,*/ const bool& bDANGER=false);
	// 专项作业车 Special Operation Vehicle
	// strSQL:数据库参数
	void DetTypeRIVehSOVeh(const CString& strSQL);

	// 技术等级评定
	// 教练、租赁小型车辆
	void TGECoachLeaseSmallVeh(const CString& strSQL);
	// 客车：9人以下
	// strSQL:数据库参数
	// nNumber:默认参考下面
	// 1.10-19
	// 2.20以上
	void TGERIVehPCar(const CString& strSQL, const int& nNumber);
	// 货车 危险
	// strSQL:数据库参数
	// nTonnage:吨位
	// bDANGER:是否货运
	// 1.总质量4.5t以下
	// 2.总质量4.5-12t
	// 3.总质量12-30t
	// 4.总质量30t以上
	void TGERIVehTruck(const CString& strSQL, const int& nTonnage, const bool& bDANGER=false);

	// 三检合一
	// 教练、租赁小型车辆
	void TheToOneCoachLeaseSmallVeh(const CString& strSQL);
	// 客车：9人以下
	// strSQL:数据库参数
	// nNumber:默认参考下面
	// 1.10-19
	// 2.20以上
	void TheToOneRIVehPCar(const CString& strSQL, const int& nNumber);
	// 货车 危险
	// strSQL:数据库参数
	// nTonnage:吨位
	// bDANGER:是否货运
	// 1.总质量4.5t以下
	// 2.总质量4.5-12t
	// 3.总质量12-30t
	// 4.总质量30t以上
	void TheToOneRIVehTruck(const CString& strSQL, const int& nTonnage, const bool& bDANGER=false);

	// 注册登记
	// 小型客车
	void RegistrationRIVehPCar(const CString& strSQL);
	// 货车
	// strSQL:数据库参数
	// nTonnage:吨位
	// bDANGER:是否货运
	// 1.总质量3.5t以下
	// 2.总质量3.5-4.5t
	// 3.总质量4.5t-31t以上
	void RegistrationRIVehTruck(const CString& strSQL, const int& nTonnage);
	// 专项作业车 Special Operation Vehicle
	// strSQL:数据库参数
	void RegistrationRIVehSOVeh(const CString& strSQL);

	// 三检合一(新车)
	void NewTheToOneRIVehTruck(const CString& strSQL);

	// 非定检
	void NoFixedCheck(const CString& strSQL);

	// 临时检验Temporary inspection
	// 1.过户
	// 2.转出
	// 3.转入
	void TemIns(const CString& strSQL, const int& nTonnage);

	// 杂项 Miscellaneous
	// 1.A
	// 2.B
	// 3.摩托车
	// 4.反光膜
	// 5.三角警告牌
	// 6.灭火器
	// 7.照相
	// 8.预留项
	void Mis(const int& nTonnage);
};


