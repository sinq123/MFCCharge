/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：NHGDIPlusInit.h
* 文件标识：
* 摘要：GDI+初始化文件
*       由以前自用类CGDIPlusInit改进而来
*       并将文件名由GDIPlusInit.h改为NHGDIPlusInit.h，以区别于GDI+库中的同名文件
*
* 当前版本：1.0
* 作者：Cui
* 完成日期：2010-01-25
*
* 历史信息：
*
*
* 当前版本：1.0.0
* 完成日期：2010-01-25
* 作者：Cui
* 描述：正式发布使用
*
* 当前版本：1.0.1
* 完成日期：2013-03-05
* 作者：Sjming
* 描述：修正字符串比较的Bug
*/


#ifndef NH_GDIPLUSINIT_H
#define NH_GDIPLUSINIT_H

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

class CNHGDIPlusInit
{
public:
	CNHGDIPlusInit() throw():m_dwToken(0)	{Init();};
	~CNHGDIPlusInit() throw()	{Exit();};

	bool Init() throw()
	{
		if (m_dwToken == 0)
		{
			Gdiplus::GdiplusStartupInput Input;
			Gdiplus::GdiplusStartupOutput Output;
			Gdiplus::Status status = Gdiplus::GdiplusStartup(&m_dwToken, &Input, &Output);
			if (status != Gdiplus::Ok) 
			{
				return false;
			}
		}
		return true;
	};

	void Exit() throw()
	{
		if (m_dwToken != 0)
		{
			Gdiplus::GdiplusShutdown(m_dwToken);
		}
	};

	// 从资源调用,需指明资源类型
	static Gdiplus::Bitmap* LoadImageFromID(UINT uImageID, LPCTSTR pResourceType, HINSTANCE m_hResource=NULL)
	{
		if (m_hResource == NULL) 
		{
			//m_hResource = AfxGetApp()->m_hInstance;
			m_hResource = AfxGetResourceHandle();
		}

		if (0 == wcscmp(pResourceType, _T("Bitmap")))
		{
			return Gdiplus::Bitmap::FromResource(m_hResource, (WCHAR*)MAKEINTRESOURCE(uImageID));
		}
		else if (0 == wcscmp(pResourceType, _T("Icon")))
		{
			HICON hIcon = ::LoadIcon(m_hResource, MAKEINTRESOURCE(uImageID));
			return Gdiplus::Bitmap::FromHICON(hIcon);
		}
		else
		{
			Gdiplus::Bitmap* pBmp = NULL;
			HRSRC hResource = ::FindResource(m_hResource, MAKEINTRESOURCE(uImageID), pResourceType);
			DWORD imageSize = ::SizeofResource(m_hResource, hResource);
			const void* pResourceData = ::LockResource(::LoadResource(m_hResource, hResource));
			HGLOBAL m_hBuffer = ::GlobalAlloc(GMEM_MOVEABLE, imageSize);
			if (m_hBuffer)
			{
				void* pBuffer = ::GlobalLock(m_hBuffer);
				if (pBuffer)
				{
					CopyMemory(pBuffer, pResourceData, imageSize);

					IStream* pStream = NULL;
					if (::CreateStreamOnHGlobal(m_hBuffer, FALSE, &pStream) == S_OK)
					{
						pBmp = Gdiplus::Bitmap::FromStream(pStream);
						pStream->Release();					
					}
					::GlobalUnlock(m_hBuffer);
				}
				::GlobalFree(m_hBuffer);
				m_hBuffer = NULL;
			}
			return pBmp;
		}
	}

	// 直接读取文件
	static Gdiplus::Bitmap* LoadImageFromFile(LPCTSTR lpszImageFile)
	{
		WCHAR wStr [256] = {0};

#ifdef _UNICODE
		_tcscpy_s(wStr, 254, lpszImageFile);
#else
		int nLen = 0;
		nLen = (int)strlen(lpszImageFile) + 1; 			
		MultiByteToWideChar(CP_ACP, 0, lpszImageFile, nLen, wStr, 256);  // 转换宽字符
#endif

		return Gdiplus::Bitmap::FromFile(wStr);
	}

private:
	ULONG_PTR m_dwToken;
};

#endif