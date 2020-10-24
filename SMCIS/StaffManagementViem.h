#pragma once



// CStaffManagementViem 窗体视图

class CStaffManagementViem : public CFormView
{
	DECLARE_DYNCREATE(CStaffManagementViem)

protected:
	CStaffManagementViem();           // 动态创建所使用的受保护的构造函数
	virtual ~CStaffManagementViem();

public:
	enum { IDD = IDD_STATFF_MANAGEMENT_VIEM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

private:
	afx_msg void OnBnClickedBtnQuery();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnModify();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnLvnItemchangedLstEmployeeInfo(NMHDR *pNMHDR, LRESULT *pResult);
private:
	// 条件姓名
	CEdit m_edCondName;
	// 员工信息列表
	CListCtrl m_lstEmployeeInfo;
	// 位图列表，用于设置列表行高
	CImageList m_ilRowHeight;
	// 姓名
	CEdit m_edName;
	// 用户名
	CEdit m_edUserName;
	// 密码
	CEdit m_edPassword;

	CButtonST m_btnQuery;
	CButtonST m_btnAdd;
	CButtonST m_btnModify;
	CButtonST m_btnDelete;

	//
	CComboBox m_cbAdministstors;
private:
	// 初始化控件
	void InitCtrls(void);
	// 设置对话框字体
	void SetDlgFont(void);

private:
	// 自动适应列宽
	void AutoFitColumnWidth(CListCtrl &list);

private:
	// 初始化员工信息列表
	void InitEmployeeInfoList(void);

private:
	// 通用对话框字体
	CFont m_fontDlgFont;
	// 通用对话框字体大小
	int m_nDlgFontSize;


private:
	// 控件随窗口变化而变化
	// 添加控件ID
	void InitConInfo(void);
	void SetControlInfo(const WORD CtrlId);
	int m_old_cx;
	int m_old_cy;
	CDWordArray m_control_info;

private:
	// 获取 SQL数据的信息
	// 生成查询SQL
	CString GenerateQuerySQL(void);
	// 查找员工信息数据
	DWORD QueryEmployeeInfoData(void);
	// 获取员工信息
	void GetEmployeeInfo(const CString& strName);
	// 员工权限信息
	std::string m_strEmployeePerm;
	// 显示界面信息
	void ShowListToWnd(void);

};


