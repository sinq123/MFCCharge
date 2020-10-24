/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ImageWnd.h
* �ļ���ʶ��
* ժҪ��ͼƬ��ʾ��,������CWnd��,ʹ��GDI+��ͼ,֧��PNG,jpg��ͼƬ��ʽ,ͼƬ�ɴ�ֱ�Ӷ�ȡ�ļ������Դ����
*
* ��ǰ�汾��1.0
* ���ߣ�Cui
* ������ڣ�2010-01-25
*
* ��ʷ��Ϣ��
*
*
* ��ǰ�汾:1.0.2
* �������:2010-01-25
* ����:Cui
* ����: 1)void SetImage(UINT uImageID, LPCTSTR pResourceType = L"Bitmap", HINSTANCE m_hResource=NULL)
*         �Ļ�
*         void SetImage(UINT uImageID, LPCTSTR pResourceType = L"Bitmap") 
*         ����ɾ�� HINSTANCE m_hResource
*
* ��ǰ�汾:1.0.1
* �������:2009-12-26
* ����:hyh
* ����: 1)void SetImage(UINT uImageID, LPCTSTR pResourceType = L"Bitmap") ������� HINSTANCE m_hResource
*       ����Ϊ:
*       void SetImage(UINT uImageID, LPCTSTR pResourceType = L"Bitmap", HINSTANCE m_hResource=NULL);
*	    ��DLL��Դ����,DLL��ԴҪ����Դ�ſ�����������
*
* ��ǰ�汾��1.0.0
* ������ڣ�20xx-xx-xx
* ���ߣ�HB
* ��������ʽ����ʹ��
*/


/**
* @file ImageWnd.h
*
* ���ĵ�������CImageWnd��
*
* @author HuaBei
*/


#pragma once
// ͼƬ��ʾ��,������CWnd��,ʹ��GDI+��ͼ,֧��PNG,jpg��ͼƬ��ʽ,ͼƬ�ɴ�ֱ�Ӷ�ȡ�ļ������Դ����

// CImageWnd

/**
* @brief ͼƬ��ʾ��,������CWnd��,ʹ��GDI+��ͼ,֧��PNG,jpg��ͼƬ��ʽ,ͼƬ�ɴ�ֱ�Ӷ�ȡ�ļ������Դ����
*/

#include "NHGDIPlusInit.h"

class AFX_EXT_CLASS CImageWnd : public CWnd
{
	DECLARE_DYNAMIC(CImageWnd)

public:
	/// ���캯��
	CImageWnd();
	/// ��������
	virtual ~CImageWnd();

public:
	afx_msg void OnPaint();

	/// @brief ֱ�Ӷ�ȡ�ļ�
	///
	/// @param lpszImageFile [in]ͼƬ�ļ����ַ���ָ��
	/// @return ��
	void SetImage(LPCTSTR lpszImageFile);

	/// @brief ����Դ����,��ָ����Դ����
	/// 
	/// @param uImageID [in]ͼƬ��ԴID
	/// @param pResourceType [in]ͼƬ��Դ�����ַ���ָ��
	void SetImage(UINT uImageID, LPCTSTR pResourceType = L"Bitmap");

protected:
	DECLARE_MESSAGE_MAP()

private:
	/// GdiPlus��ͼƬָ��
	Gdiplus::Bitmap* m_pBitmap;
};


