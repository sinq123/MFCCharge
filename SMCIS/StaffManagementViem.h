#pragma once



// CStaffManagementViem ������ͼ

class CStaffManagementViem : public CFormView
{
	DECLARE_DYNCREATE(CStaffManagementViem)

protected:
	CStaffManagementViem();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	// ��������
	CEdit m_edCondName;
	// Ա����Ϣ�б�
	CListCtrl m_lstEmployeeInfo;
	// λͼ�б����������б��и�
	CImageList m_ilRowHeight;
	// ����
	CEdit m_edName;
	// �û���
	CEdit m_edUserName;
	// ����
	CEdit m_edPassword;

	CButtonST m_btnQuery;
	CButtonST m_btnAdd;
	CButtonST m_btnModify;
	CButtonST m_btnDelete;

	//
	CComboBox m_cbAdministstors;
private:
	// ��ʼ���ؼ�
	void InitCtrls(void);
	// ���öԻ�������
	void SetDlgFont(void);

private:
	// �Զ���Ӧ�п�
	void AutoFitColumnWidth(CListCtrl &list);

private:
	// ��ʼ��Ա����Ϣ�б�
	void InitEmployeeInfoList(void);

private:
	// ͨ�öԻ�������
	CFont m_fontDlgFont;
	// ͨ�öԻ��������С
	int m_nDlgFontSize;


private:
	// �ؼ��洰�ڱ仯���仯
	// ��ӿؼ�ID
	void InitConInfo(void);
	void SetControlInfo(const WORD CtrlId);
	int m_old_cx;
	int m_old_cy;
	CDWordArray m_control_info;

private:
	// ��ȡ SQL���ݵ���Ϣ
	// ���ɲ�ѯSQL
	CString GenerateQuerySQL(void);
	// ����Ա����Ϣ����
	DWORD QueryEmployeeInfoData(void);
	// ��ȡԱ����Ϣ
	void GetEmployeeInfo(const CString& strName);
	// Ա��Ȩ����Ϣ
	std::string m_strEmployeePerm;
	// ��ʾ������Ϣ
	void ShowListToWnd(void);

};


