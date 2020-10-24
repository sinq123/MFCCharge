
/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�RatingService.h
* �ļ���ʶ��
* �������ȼ��������ʲ�
*
* �汾��1.0
* ���ڣ�20xx-xx-xx
* ���ߣ�Ljf
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�Ljf
* ���������ڿ���
*/


#ifndef RATINGSERVICE_H
#define RATINGSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CRatingService : public CNHMFDServerDBService
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CRatingService(void);
	virtual ~CRatingService(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CRatingService(const CRatingService &);
	CRatingService & operator =(const CRatingService &);

public:
	// ����1������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// sRating�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetRating(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SRating &sRating);
	// ����n������
	// ������
	// pConnection������ָ������
	// pwchSql��Sql����ַ���ָ��
	// lsRating�������б�Ӧ��
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD GetRating(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SRating> &lsRating);

public:
	// д��1������
	// ������
	// pConnection������ָ������
	// sRating�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetRating(const _ConnectionPtr &pConnection, const SRating &sRating);
	// д��1������
	// ������
	// pConnection������ָ������
	// sRating�����ݽṹ����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetRating_NonEmpty(const _ConnectionPtr &pConnection, const SRating &sRating);
	// д��n������
	// ������
	// pConnection������ָ������
	// lsRating�������б�����
	// ���أ���Ӱ��������
	// ��0xFFFFFFFF����������Ӱ������
	// 0xFFFFFFFF���쳣
	static DWORD SetRating(const _ConnectionPtr &pConnection, const std::list<SRating> &lsRating);

private:
	// ���ݿ��ֶ�(Field)������ṹ(Struct)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sRating�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SRating &sRating);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sRating�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SRating &sRating);
	// ����ṹ(Struct)�����ݿ��ֶ�(Field)
	// ������
	// pRecordset����¼��ָ��Ӧ��
	// sRating�����ݽṹ����
	// ���أ��������:
	// 0x00������
	// ��0x00���쳣
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SRating &sRating);
};

#endif