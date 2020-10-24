/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�GAVideoRecord.h
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


#if !defined (NHMFDSERVERDBMODEL_GAVIDEORECORD_H)
#define NHMFDSERVERDBMODEL_GAVIDEORECORD_H

#include <string>

struct SGAVideoRecord
{
	// �Զ����
	std::wstring strAutoID;
	// ������ڱ��
	std::wstring strDetPeriodID;
	// ��������
	std::wstring strInitDetDate;
	// ������
	std::wstring strReportNumber;
	// ¼��ʼʱ��
	std::wstring strVideoStartTime;
	// ¼�����ʱ��
	std::wstring strVideoEndTime;
	// ¼�����ƣ����ڱ���¼���ļ�����
	std::wstring strVideoName;
	// ��Ƶ������IP
	std::wstring strVR_IP;
	// ��Ƶ�������˿�
	std::wstring strVR_Port;
	// ��Ƶ�������û���
	std::wstring strVR_UserName;
	// ��Ƶ����������
	std::wstring strVR_Password;
	// ��Ƶ������ͨ��
	std::wstring strVR_Channel;
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