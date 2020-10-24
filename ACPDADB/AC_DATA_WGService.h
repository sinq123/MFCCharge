/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�AC_DATA_WGService.h
* �ļ���ʶ��
* ������PDA��۱����ݷ��ʲ�
*
* �汾��1.0
* ���ڣ�2015-01-28
* ���ߣ�Shaojm
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0
* ���ڣ�2015-01-28
* ���ߣ�Shaojm
* ���������ڷ���
*/


#if !defined(PDADBDAL_AC_DATA_WG_h)
#define PDADBDAL_AC_DATA_WG_h

#include <list>
#include "AC_DATA_WG.h"

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

#ifdef PDADBDAL_EXPORTS
#define PDADBDAL_API __declspec(dllexport)
#else
#define PDADBDAL_API __declspec(dllimport)
#endif

class PDADBDAL_API CAC_DATA_WGService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CAC_DATA_WGService(void);
	virtual ~CAC_DATA_WGService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CAC_DATA_WGService(const CAC_DATA_WGService &);
	CAC_DATA_WGService & operator =(const CAC_DATA_WGService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sAC_DATA_WG�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetAC_DATA_WG(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SAC_DATA_WG &sAC_DATA_WG);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsAC_DATA_WG�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetAC_DATA_WG(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SAC_DATA_WG> &lsAC_DATA_WG);
public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sAC_DATA_WG�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetAC_DATA_WG(const _ConnectionPtr &pConnection, const SAC_DATA_WG &sAC_DATA_WG);
	// д��1�����ݣ�ֻд��ǿյ�����
	// ������
	// pConnection������ָ������
	// sAC_DATA_WG�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetAC_DATA_WG_NonEmpty(const _ConnectionPtr &pConnection, const SAC_DATA_WG &sAC_DATA_WG);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsAC_DATA_WG�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetAC_DATA_WG(const _ConnectionPtr &pConnection, const std::list<SAC_DATA_WG> &lsAC_DATA_WG);

public:
	// ����flag��ʶ
	// ������
	// pConnection������ָ������
	// strjylsh��������ˮ��
	// strflag��flag��ʶ
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetAC_DATA_WG_flag(const _ConnectionPtr &pConnection, const std::wstring &strjylsh, std::wstring &strflag);

	// ����bhgx���ϸ���
	// ������
	// pConnection������ָ������
	// strjylsh��������ˮ��
	// strbhgx��bhgx���ϸ���
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetAC_DATA_WG_bhgx(const _ConnectionPtr &pConnection, const std::wstring &strjylsh, std::wstring &strbhgx);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sAC_DATA_WG�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SAC_DATA_WG &sAC_DATA_WG);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sAC_DATA_WG�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SAC_DATA_WG &sAC_DATA_WG);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)��ֻд��ǿյ�����
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sAC_DATA_WG�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SAC_DATA_WG &sAC_DATA_WG);
};

#endif