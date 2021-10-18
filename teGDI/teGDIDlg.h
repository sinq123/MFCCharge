
// teGDIDlg.h : 头文件
//

#pragma once
#include <string>



#include <gdiplus.h>             //GDI+声明，可以GDI/GDI+混合使用
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

// CteGDIDlg 对话框
class CteGDIDlg : public CDialogEx
{
// 构造
public:
	CteGDIDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CteGDIDlg();
// 对话框数据
	enum { IDD = IDD_TEGDI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


private:
	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_pGdiToken;

	// bmp转jpg
	bool BMPTOJPG(const CString& srtBmpPath, const CString& strJpgPath);
	// jpg转bmp
	bool JPGTOBMP(const CString& strJpgPath, const CString& srtBmpPath);
	// 图片添加文字
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	// 添加图片水印
	// strJpgPath 底图路径
	// strTarget 加载水印后的路径
	// 加载的字体
	void DrawWatermark(const CString& strJpgPath, const std::wstring& strTarget, const float& fLength, const float& fWidth=0.00, const float& fHeight=0.00);
	// 加载资源图片
	Gdiplus::Bitmap* LoadImageFromID(UINT uImageID, LPCTSTR pResourceType, HINSTANCE m_hResource=NULL);

	// 增加水印
	void AddWatermark(const CString& strJpgPath, const CString& strFildName);
	// 图片添加文字
	void ImageAppendText(const std::wstring& strSource, const std::wstring& strTarget, const std::wstring& strText);

	// strJpgPath 图片路径
	// 图片名称
	// fLength, fWidth, fHeight 长宽高
	void AddWatermark(const CString& strJpgPath, const CString& strFildName, 
		const float& fLength, const float& fWidth=0.00, const float& fHeight=0.00);
};
