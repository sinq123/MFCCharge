/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：DetPeriodService.h
* 文件标识：
* 描述：检测周期表数据访问层
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


#ifndef DETPERIODSERVICE_H
#define DETPERIODSERVICE_H

#include <list>
#include <string>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CDetPeriodService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CDetPeriodService(void);
	virtual ~CDetPeriodService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CDetPeriodService(const CDetPeriodService &);
	CDetPeriodService & operator =(const CDetPeriodService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sDetPeriod：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDetPeriod(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetPeriod &sDetPeriod);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsDetPeriod：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDetPeriod(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetPeriod> &lsDetPeriod);
	// 读出DetPeriodID
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// strDetPeriodID：DetPeriodID
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDetPeriod_DetPeriodID(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::wstring &strDetPeriodID);
	// 读出ReportNumber（通过DetPeriodID）
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// strDetPeriodID：DetPeriodID
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDetPeriod_ReportNumber(const _ConnectionPtr &pConnection, const wchar_t *pwchDetPeriodID, std::wstring &strReportNumber);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sDetPeriod：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetPeriod(const _ConnectionPtr &pConnection, const SDetPeriod &sDetPeriod);
	// 写入1条数据，只写入非空的数据
	// 参数：
	// pConnection：连接指针引用
	// sDetPeriod：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetPeriod_NonEmpty(const _ConnectionPtr &pConnection, const SDetPeriod &sDetPeriod);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsDetPeriod：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetPeriod(const _ConnectionPtr &pConnection, const std::list<SDetPeriod> &lsDetPeriod);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sDetPeriod：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SDetPeriod &sDetPeriod);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sDetPeriod：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SDetPeriod &sDetPeriod);
	// 程序结构(Struct)到数据库字段(Field)，只写入非空的数据
	// 参数：
	// pRecordset：记录集指针应用
	// sDetPeriod：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SDetPeriod &sDetPeriod);
};

#endif