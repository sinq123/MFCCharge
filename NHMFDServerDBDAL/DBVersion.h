/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�DBVersion.h
* �ļ���ʶ��
* ���������ݿ�ṹ�汾��ģ��
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


#if !defined (NHMFDSERVERDBMODEL_DBVERSION_H)
#define NHMFDSERVERDBMODEL_DBVERSION_H

#include <string>
typedef unsigned char BYTE;

struct SDBVersion
{
	// �Զ����
	std::wstring strAutoID;
	// �汾��
	std::wstring strVersion;
	// ��������(������)
	std::wstring strUpdateDate;
	// ����汾
	BYTE *pbProVer;
	// ��ע
	std::wstring strRemark;
	// ����1
	std::wstring strReserved1;
	// ����2
	std::wstring strReserved2;
	// ����3
	std::wstring strReserved3;

	// �����ֶβ������ݿ��ֶζ�Ӧ��ָʾͼƬ��������С
	unsigned int nProVerSize;

	SDBVersion()
	{
		pbProVer = NULL;

		nProVerSize = 0;
	}
	
	~SDBVersion()
	{
		if (pbProVer != NULL)
		{
			delete pbProVer;
			pbProVer = NULL;
		}
	}

	void SetProVerData(const BYTE *pbPhotoData ,const unsigned int nSize)
	{
		SetPhotoData(&pbProVer, pbPhotoData, nSize);
		nProVerSize = nSize;
	}

private:
	// �������ݵ�Photo�ֶΣ��ڴ涯̬���룬����ʱ�Զ��ͷ�
	inline void SetPhotoData(BYTE **pbPhotoBuf, const BYTE *pbPhotoData, const unsigned int nSize)
	{
		if (nSize != 0)
		{
			if (*pbPhotoBuf != NULL)
			{
				delete *pbPhotoBuf;
				*pbPhotoBuf = NULL;
			}
			*pbPhotoBuf = new BYTE[nSize];
			memset(*pbPhotoBuf, 0, nSize);
			memcpy(*pbPhotoBuf, pbPhotoData, nSize);
		}
	}
};

#endif