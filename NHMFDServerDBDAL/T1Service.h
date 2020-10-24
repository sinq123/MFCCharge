/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：T1Service.h
* 文件标识：
* 描述：白名单表数据访问层
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


#ifndef T1SERVICE_H
#define T1SERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CT1Service : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CT1Service(void);
	virtual ~CT1Service(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CT1Service(const CT1Service &);
	CT1Service & operator =(const CT1Service &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sT1：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetT1(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, ST1 &sT1);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsT1：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetT1(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<ST1> &lsT1);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sT1：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetT1(const _ConnectionPtr &pConnection, const ST1 &sT1);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsT1：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetT1(const _ConnectionPtr &pConnection, const std::list<ST1> &lsT1);

public:
	// 是否白名单
	// 参数：
	// pConnection：连接指针引用
	// pwchPlateNumber：号牌号码
	// pwchPlateTypeCode：号牌种类代码
	// 返回：
	// true：是
	// false：否
	static bool IsWhiteList(const _ConnectionPtr &pConnection, const wchar_t *pwchPlateNumber, const wchar_t *pwchPlateTypeCode);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sT1：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, ST1 &sT1);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sT1：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const ST1 &sT1);
};

#endif