/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�SystemLog.h
* �ļ���ʶ��
* ������ϵͳ��־��ģ��
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


#if !defined (NHMFDSERVERDBMODEL_SYSTEMLOG_H)
#define NHMFDSERVERDBMODEL_SYSTEMLOG_H

#include <string>

struct SSystemLog
{
	// �Զ����
	std::wstring strAutoID;
	// ��־����
	std::wstring strType;
	// �����IP��ַ
	std::wstring strPCIP;
	// �����Ӳ�����к�
	std::wstring strPCHWSN;
	// ʱ��
	std::wstring strTime;
	// �ͻ���
	std::wstring strClient;
	// �û�
	std::wstring strUser;
	// ����
	std::wstring strDescription;
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