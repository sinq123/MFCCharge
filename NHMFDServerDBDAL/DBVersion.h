/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：DBVersion.h
* 文件标识：
* 描述：数据库结构版本表模型
*
* 版本：1.0
* 日期：20xx-xx-xx
* 作者：Cyx
*
*
* 历史信息：
*
* 版本：1.0.0beta1
* 日期：20xx-xx-xx
* 作者：Cyx
* 描述：正在开发
*/


#if !defined (NHMFDSERVERDBMODEL_DBVERSION_H)
#define NHMFDSERVERDBMODEL_DBVERSION_H

#include <string>
typedef unsigned char BYTE;

struct SDBVersion
{
	// 自动编号
	std::wstring strAutoID;
	// 版本号
	std::wstring strVersion;
	// 更新日期(年月日)
	std::wstring strUpdateDate;
	// 程序版本
	BYTE *pbProVer;
	// 备注
	std::wstring strRemark;
	// 保留1
	std::wstring strReserved1;
	// 保留2
	std::wstring strReserved2;
	// 保留3
	std::wstring strReserved3;

	// 以下字段不和数据库字段对应，指示图片缓冲区大小
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
	// 拷贝数据到Photo字段，内存动态申请，析构时自动释放
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