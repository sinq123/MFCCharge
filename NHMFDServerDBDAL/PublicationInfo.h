/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�PublicationInfo.h
* �ļ���ʶ��
* ������ASM������ݱ�ģ��
*
* �汾��1.0
* ���ڣ�20xx-xx-xx
* ���ߣ�Cyx
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�Cyx
* ���������ڿ���
*/


#if !defined (NHMFDSERVERDBMODEL_PUBLICATIONINFO_H)
#define NHMFDSERVERDBMODEL_PUBLICATIONINFO_H

#include <string>

struct SPublicationInfo
{
	// �Զ����
	std::wstring strAutoID;
	// ���ƺ���
	std::wstring strCPHM;
	// ��������
	std::wstring strCPZL;
	// ������ˮ��
	std::wstring strJYLSH;
	// �����
	std::wstring strJCJG;
	// ��˽��
	std::wstring strSHJG;
	// ������Ϣ
	std::wstring strBHXX;
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
