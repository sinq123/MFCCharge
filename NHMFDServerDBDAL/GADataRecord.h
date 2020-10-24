/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�GADataRecord.h
* �ļ���ʶ��
* ������������Ƶ��¼��
*
* �汾��1.0
* ���ڣ�2015-04-11
* ���ߣ�Hyh
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0
* ���ڣ�2015-04-11
* ���ߣ�Hyh
* ��������ʽ����
*/


#if !defined (NHMFDSERVERDBMODEL_GADATARECORD_H)
#define NHMFDSERVERDBMODEL_GADATARECORD_H

#include <string>

struct SGADataRecord
{
	// �Զ����
	std::wstring strAutoID;
	// ��ˮ��
	std::wstring strRunningNumber;
	// �ֶ�����
	std::wstring strFieldName;
	// ϵͳ���
	std::wstring strXtlb;
	// �ӿ����к�
	std::wstring strJkxlh;
	// �ӿ�ID
	std::wstring strJkid;
	// Xml�ĵ�
	std::wstring strXmlDoc;
	// ��ע
	std::wstring strRemark;
	// ����1
	std::wstring strReserved1;
	// ����2
	std::wstring strReserved2;
	// ����3
	std::wstring strReserved3;
};

#endif