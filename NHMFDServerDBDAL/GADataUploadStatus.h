/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�GADataUploadStatus.h
* �ļ���ʶ��
* ���������������ϴ�״̬
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


#if !defined (NHMFDSERVERDBMODEL_GADATAUPLOADSTATUS_H)
#define NHMFDSERVERDBMODEL_GADATAUPLOADSTATUS_H

#include <string>

struct SGADataUploadStatus
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// ������Ϣ��¼��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strVehDetLogin;
	// ������Ϣ��¼��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strVehReDetLogin;
	// ������̿�ʼ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strDetStart;
	// ��ۿ�ʼ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strStartF1;
	// ������ݣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadF1;
	// ��۽�����0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strEndF1;
	// ���������ˣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strDetApp2Review;
	// ���̿�ʼ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strStartC1;
	// �������ݣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadC1;
	// ���̽�����0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strEndC1;
	// ��̬��ʼ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strStartDC;
	// ��̬���ݣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadDC;
	// ��̬������0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strEndDC;
	// ������ʼ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strStartM1;
	// �������ݣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadM1;
	// ����������0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strEndM1;
	// ·�Կ�ʼ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strStartR;
	// ·�����ݣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadR;
	// ·�Խ�����0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strEndR;
	// �໬��ʼ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strStartA1;
	// �໬���ݣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadA1;
	// �໬������0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strEndA1;
	// ���ٿ�ʼ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strStartS1;
	// �������ݣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadS1;
	// ���ٽ�����0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strEndS1;
	// ����ƿ�ʼ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strStartH4;
	// ��������ݣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadH4;
	// ����ƽ�����0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strEndH4;
	// ���ڵƿ�ʼ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strStartH3;
	// ���ڵ����ݣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadH3;
	// ���ڵƽ�����0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strEndH3;
	// ���ڵƿ�ʼ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strStartH2;
	// ���ڵ����ݣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadH2;
	// ���ڵƽ�����0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strEndH2;
	// ����ƿ�ʼ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strStartH1;
	// ��������ݣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadH1;
	// ����ƽ�����0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strEndH1;
	// פ���ƶ���ʼ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strStartB0;
	// פ���ƶ����ݣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadB0;
	// פ���ƶ�������0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strEndB0;
	// �����ƶ���ʼ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strStartB5;
	// �����ƶ����ݣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadB5;
	// �����ƶ�������0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strEndB5;
	// �����ƶ���ʼ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strStartB4;
	// �����ƶ����ݣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadB4;
	// �����ƶ�������0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strEndB4;
	// �����ƶ���ʼ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strStartB3;
	// �����ƶ����ݣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadB3;
	// �����ƶ�������0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strEndB3;
	// �����ƶ���ʼ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strStartB2;
	// �����ƶ����ݣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadB2;
	// �����ƶ�������0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strEndB2 ;
	// һ���ƶ���ʼ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strStartB1;
	// һ���ƶ����ݣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadB1;
	// һ���ƶ�������0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strEndB1;
	// �������ݣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadOtherData;
	// ������̽�����0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strDetEnd;
	// �ж������0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadDetResult;
	// ������Ϣ��0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strUploadIns;
	// ������ˣ�0��д��ɹ���1��д��ʧ�ܣ�NULL��δд�룩
	std::wstring strDetAppReview;
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