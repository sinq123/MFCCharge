
// PDAOnLineDlg.h : 头文件
//

#pragma once

#include "..\NHCommand\NHCommand.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHCommand_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHCommand.lib")
#endif

#include "..\NHNetLib\NHNetServer.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\MYNetLib_D.lib")
#else
#pragma comment(lib, "..\\Release\\MYNetLib.lib")
#endif

// CPDAOnLineDlg 对话框
class CPDAOnLineDlg : public CDialogEx
{
// 构造
public:
	CPDAOnLineDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CPDAOnLineDlg();
// 对话框数据
	enum { IDD = IDD_PDAONLINE_DIALOG };

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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnQuery();
private:
	// 列表LST_DET_WAITING
	CListCtrl m_lstDetWaiting;
	CListCtrl m_lstDetInspectionArea;

private:
	// 通用对话框字体
	CFont m_fontDlgFont;
	// 通用对话框字体大小
	int m_nDlgFontSize;
	bool m_bConnectDB;
	// 数据库连接
	_ConnectionPtr m_pConnection;
	// 主控IP
	CString m_strMCSIP;
	// 
	CString m_strPositionNumber;
private:
	// 初始化控件
	void InitCtrls(void);
	// 设置对话框字体
	void SetDlgFont(void);
	// 初始化检测业务列表
	void InitDetBsnList(void);
	// 读取检测参数配置
	void LoadConfig(void);

	// 打开数据库
	void OpenDB(void);
	// 关闭数据库
	void CloseDB(void);

private:
	// 控件随窗口变化而变化
	CPoint m_Old;//存放对话框的宽和高

private:
	// 网络对象
	CNHNetServer m_NHNetServer;

private:
	// 启动网络主线程
	void StartServer(void);
	// 停止网络主线程
	void StopServer(void);

private:
	// 数据处理回调函数
	static void __stdcall DataSolutionCallBack(const wchar_t* pwchIP, const BYTE* pBytes, const size_t size);

private:
	// 查询车辆信息
	void QueryWaitInfo(void);
	void QueryInspInfo(void);

	// 上线参数
	void Send_CN_Online(void);
	// 发送消息
	void SendRSDCmd(const wchar_t* pwchIP, CNHCommand& cmdRSD);
};
