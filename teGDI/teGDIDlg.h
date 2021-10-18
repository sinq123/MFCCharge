
// teGDIDlg.h : ͷ�ļ�
//

#pragma once
#include <string>



#include <gdiplus.h>             //GDI+����������GDI/GDI+���ʹ��
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

// CteGDIDlg �Ի���
class CteGDIDlg : public CDialogEx
{
// ����
public:
	CteGDIDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CteGDIDlg();
// �Ի�������
	enum { IDD = IDD_TEGDI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


private:
	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_pGdiToken;

	// bmpתjpg
	bool BMPTOJPG(const CString& srtBmpPath, const CString& strJpgPath);
	// jpgתbmp
	bool JPGTOBMP(const CString& strJpgPath, const CString& srtBmpPath);
	// ͼƬ�������
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	// ���ͼƬˮӡ
	// strJpgPath ��ͼ·��
	// strTarget ����ˮӡ���·��
	// ���ص�����
	void DrawWatermark(const CString& strJpgPath, const std::wstring& strTarget, const float& fLength, const float& fWidth=0.00, const float& fHeight=0.00);
	// ������ԴͼƬ
	Gdiplus::Bitmap* LoadImageFromID(UINT uImageID, LPCTSTR pResourceType, HINSTANCE m_hResource=NULL);

	// ����ˮӡ
	void AddWatermark(const CString& strJpgPath, const CString& strFildName);
	// ͼƬ�������
	void ImageAppendText(const std::wstring& strSource, const std::wstring& strTarget, const std::wstring& strText);

	// strJpgPath ͼƬ·��
	// ͼƬ����
	// fLength, fWidth, fHeight �����
	void AddWatermark(const CString& strJpgPath, const CString& strFildName, 
		const float& fLength, const float& fWidth=0.00, const float& fHeight=0.00);
};
