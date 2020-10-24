
/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：RatingService.h
* 文件标识：
* 描述：等级评定访问层
*
* 版本：1.0
* 日期：20xx-xx-xx
* 作者：Ljf
*
*
* 历史信息：
*
* 版本：1.0.0beta1
* 日期：20xx-xx-xx
* 作者：Ljf
* 描述：正在开发
*/


#ifndef RATINGSERVICE_H
#define RATINGSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CRatingService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CRatingService(void);
	virtual ~CRatingService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CRatingService(const CRatingService &);
	CRatingService & operator =(const CRatingService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sRating：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetRating(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SRating &sRating);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsRating：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetRating(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SRating> &lsRating);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sRating：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetRating(const _ConnectionPtr &pConnection, const SRating &sRating);
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sRating：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetRating_NonEmpty(const _ConnectionPtr &pConnection, const SRating &sRating);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsRating：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetRating(const _ConnectionPtr &pConnection, const std::list<SRating> &lsRating);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sRating：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SRating &sRating);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sRating：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SRating &sRating);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sRating：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SRating &sRating);
};

#endif