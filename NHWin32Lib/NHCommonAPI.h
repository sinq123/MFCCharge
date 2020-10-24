/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�NHCommonAPI.h
* �ļ���ʶ��
* ������ͨ�ýӿں���
*
* �汾��1.0
* ���ߣ�Hyh��Cyx
* ���ڣ�2010-09-03
*
* ��ʷ��Ϣ��
*
* �汾��1.0.2
* ���ڣ�2011-11-04
* ���ߣ�Raylee
* ��������������Unicode�ļ�����û���ж��Ƿ���ļ��ɹ���bug
*
* �汾��1.0.1
* ���ڣ�2011-07-26
* ���ߣ�Cyx
* ������1������������뺯��
*       2������µĻ�ȡ�ļ�·������
*       3����Ӵ���Unicode�ļ�����
*
* �汾��1.0.0
* ���ڣ�2010-09-03
* ���ߣ�Hyh��Cyx
* ������1������ַ�����ת������
*       2������汾��Ϣ
*       3����ʽ����ʹ��
*/

#pragma once

#ifndef NHCOMMONAPI_H
#define NHCOMMONAPI_H

//#ifdef DLL_FILE
//class _declspec(dllexport) CNHCommonAPI
//#else
//class _declspec(dllimport) CNHCommonAPI
//#endif
class CNHCommonAPI
{
public:
	CNHCommonAPI(void);
	virtual ~CNHCommonAPI(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CNHCommonAPI(const CNHCommonAPI &);
	CNHCommonAPI & operator =(const CNHCommonAPI &);

public:
	// ��ȡ�ļ�·��
	// (in)chFileFolder:�ļ���
	// (in)chFileName:�ļ���
	// (out)chFilePath:�ļ�·��
	// (in)bCreateFile:���ļ�������ʱ���Ƿ񴴽��ļ�
	// (return)�������:
	// 0x00:������
	// ��0x00:�쳣(0x01:�����ļ���ʧ��,0x02:�ļ�������,0x03:�����ļ�ʧ��)
	// ע��: �ļ��������ļ���ǰ�߲���Ҫ��"\\"
	// ����: <L"Config"> �� <L"NHModeServerDB.ini">
	static DWORD GetFilePathEx(const wchar_t wchFileFolder[MAX_PATH], const wchar_t wchFileName[MAX_PATH], wchar_t wchFilePath[MAX_PATH], const bool bCreateFile = false);

	// �ַ�����ת������
	static wchar_t * ANSIToUnicode(const char *str);
	static char * UnicodeToANSI(const wchar_t *str);
	static wchar_t * UTF8ToUnicode(const char *str);
	static char * UnicodeToUTF8(const wchar_t *str);
	static char * ANSIToUTF8(const char *str);
	static char * UTF8ToANSI(const char *str);

	// ��������
	static int round(const float f);
	static int round(const double d);

	// ��ȡ�ļ�·��
	// ��ǰĿ¼��CD=Current Directory
	// �ϼ�Ŀ¼��HLD=Higher Level Directory
	// �¼�Ŀ¼��LLD=Lower Level Directory
	// ������
	// pwchFileFolder:�ļ�����
	// pwchFileName:�ļ���
	// pwchFilePath:�ļ�·��
	// bCreateFile:���ļ�������ʱ���Ƿ񴴽��ļ�
	// ���أ��������:
	// 0x00:������
	// ��0x00:�쳣(0x01:�����ļ���ʧ��,0x02:�ļ�������,0x03:�����ļ�ʧ��)
	// ע��: �ļ��������ļ���ǰ�߲���Ҫ��"\\"
	// ����: <L"Config"> �� <L"NHModeServerDB.ini">
	static DWORD GetCDFilePath(const wchar_t *const pwchFileName, wchar_t *const pwchFilePath, const bool bCreateFile = false);
	static DWORD GetHLDFilePath(const wchar_t *const pwchFileFolder, const wchar_t *const pwchFileName, wchar_t *const pwchFilePath, const bool bCreateFile = false);
	static DWORD GetLLDFilePath(const wchar_t *const pwchFileFolder, const wchar_t *const pwchFileName, wchar_t *const pwchFilePath, const bool bCreateFile = false);

	// ����Unicode�ļ�
	// ������
	// pwchFilePath:�ļ�·��
	// ���أ��������:
	// 0x00:������
	// ��0x00:�쳣
	static DWORD CreateUnicodeFile(const wchar_t *const pwchFilePath);
};

#endif