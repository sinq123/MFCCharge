/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�AC_DATA_ROADService.h
* �ļ���ʶ��
* ������PDA·�����ݱ����ݷ��ʲ�
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


#if !defined(PDADBDAL_AC_DATA_ROAD_h)
#define PDADBDAL_AC_DATA_ROAD_h

#include <list>
#include "AC_DATA_ROAD.h"

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

class PDADBDAL_API CAC_DATA_ROADService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CAC_DATA_ROADService(void);
	virtual ~CAC_DATA_ROADService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CAC_DATA_ROADService(const CAC_DATA_ROADService &);
	CAC_DATA_ROADService & operator =(const CAC_DATA_ROADService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sAC_DATA_ROAD�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetAC_DATA_ROAD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SAC_DATA_ROAD &sAC_DATA_ROAD);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsAC_DATA_ROAD�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetAC_DATA_ROAD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SAC_DATA_ROAD> &lsAC_DATA_ROAD);
public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sAC_DATA_ROAD�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetAC_DATA_ROAD(const _ConnectionPtr &pConnection, const SAC_DATA_ROAD &sAC_DATA_ROAD);
	// д��1�����ݣ�ֻд��ǿյ�����
	// ������
	// pConnection������ָ������
	// sAC_DATA_ROAD�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetAC_DATA_ROAD_NonEmpty(const _ConnectionPtr &pConnection, const SAC_DATA_ROAD &sAC_DATA_ROAD);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsAC_DATA_ROAD�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetAC_DATA_ROAD(const _ConnectionPtr &pConnection, const std::list<SAC_DATA_ROAD> &lsAC_DATA_ROAD);

public:
	// ����flag��ʶ
	// ������
	// pConnection������ָ������
	// strjylsh��������ˮ��
	// strflag��flag��ʶ
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetAC_DATA_ROAD_flag(const _ConnectionPtr &pConnection, const std::wstring &strjylsh, std::wstring &strflag);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sAC_DATA_ROAD�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SAC_DATA_ROAD &sAC_DATA_ROAD);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sAC_DATA_ROAD�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SAC_DATA_ROAD &sAC_DATA_ROAD);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)��ֻд��ǿյ�����
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sAC_DATA_ROAD�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SAC_DATA_ROAD &sAC_DATA_ROAD);
};

#endif