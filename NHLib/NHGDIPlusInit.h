/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�NHGDIPlusInit.h
* �ļ���ʶ��
* ժҪ��GDI+��ʼ���ļ�
*       ����ǰ������CGDIPlusInit�Ľ�����
*       �����ļ�����GDIPlusInit.h��ΪNHGDIPlusInit.h����������GDI+���е�ͬ���ļ�
*
* ��ǰ�汾��1.0
* ���ߣ�Cui
* ������ڣ�2010-01-25
*
* ��ʷ��Ϣ��
*
*
* ��ǰ�汾��1.0.0
* ������ڣ�2010-01-25
* ���ߣ�Cui
* ��������ʽ����ʹ��
*
* ��ǰ�汾��1.0.1
* ������ڣ�2013-03-05
* ���ߣ�Sjming
* �����������ַ����Ƚϵ�Bug
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

	// ����Դ����,��ָ����Դ����
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

	// ֱ�Ӷ�ȡ�ļ�
	static Gdiplus::Bitmap* LoadImageFromFile(LPCTSTR lpszImageFile)
	{
		WCHAR wStr [256] = {0};

#ifdef _UNICODE
		_tcscpy_s(wStr, 254, lpszImageFile);
#else
		int nLen = 0;
		nLen = (int)strlen(lpszImageFile) + 1; 			
		MultiByteToWideChar(CP_ACP, 0, lpszImageFile, nLen, wStr, 256);  // ת�����ַ�
#endif

		return Gdiplus::Bitmap::FromFile(wStr);
	}

private:
	ULONG_PTR m_dwToken;
};

#endif