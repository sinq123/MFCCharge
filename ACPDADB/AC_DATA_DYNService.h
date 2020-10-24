/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�AC_DATA_DYNService.h
* �ļ���ʶ��
* ������PDA���̶�̬�����ݷ��ʲ�
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


#if !defined(PDADBDAL_AC_DATA_DYN_h)
#define PDADBDAL_AC_DATA_DYN_h

#include <list>
#include "AC_DATA_DYN.h"

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

class PDADBDAL_API CAC_DATA_DYNService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CAC_DATA_DYNService(void);
	virtual ~CAC_DATA_DYNService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CAC_DATA_DYNService(const CAC_DATA_DYNService &);
	CAC_DATA_DYNService & operator =(const CAC_DATA_DYNService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sAC_DATA_DYN�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetAC_DATA_DYN(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SAC_DATA_DYN &sAC_DATA_DYN);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsAC_DATA_DYN�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetAC_DATA_DYN(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SAC_DATA_DYN> &lsAC_DATA_DYN);
public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sAC_DATA_DYN�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetAC_DATA_DYN(const _ConnectionPtr &pConnection, const SAC_DATA_DYN &sAC_DATA_DYN);
	// д��1�����ݣ�ֻд��ǿյ�����
	// ������
	// pConnection������ָ������
	// sAC_DATA_DYN�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetAC_DATA_DYN_NonEmpty(const _ConnectionPtr &pConnection, const SAC_DATA_DYN &sAC_DATA_DYN);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsAC_DATA_DYN�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetAC_DATA_DYN(const _ConnectionPtr &pConnection, const std::list<SAC_DATA_DYN> &lsAC_DATA_DYN);

public:
	// ����flag��ʶ
	// ������
	// pConnection������ָ������
	// strjylsh��������ˮ��
	// strflag��flag��ʶ
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetAC_DATA_DYN_flag(const _ConnectionPtr &pConnection, const std::wstring &strjylsh, std::wstring &strflag);

	// ����bhgx���ϸ���
	// ������
	// pConnection������ָ������
	// strjylsh��������ˮ��
	// strbhgx��bhgx���ϸ���
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetAC_DATA_DYN_bhgx(const _ConnectionPtr &pConnection, const std::wstring &strjylsh, std::wstring &strbhgx);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sAC_DATA_DYN�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SAC_DATA_DYN &sAC_DATA_DYN);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sAC_DATA_DYN�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SAC_DATA_DYN &sAC_DATA_DYN);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)��ֻд��ǿյ�����
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sAC_DATA_DYN�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SAC_DATA_DYN &sAC_DATA_DYN);
};

#endif