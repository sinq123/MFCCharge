/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：SuspensionDataService.h
* 文件标识：
* 描述：悬架特性数据表数据访问层
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


#ifndef SUSPENSIONDATASERVICE_H
#define SUSPENSIONDATASERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CSuspensionDataService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CSuspensionDataService(void);
	virtual ~CSuspensionDataService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CSuspensionDataService(const CSuspensionDataService &);
	CSuspensionDataService & operator =(const CSuspensionDataService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sSuspensionData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetSuspensionData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSuspensionData &sSuspensionData);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsSuspensionData：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetSuspensionData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SSuspensionData> &lsSuspensionData);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sSuspensionData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetSuspensionData(const _ConnectionPtr &pConnection, const SSuspensionData &sSuspensionData);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsSuspensionData：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetSuspensionData(const _ConnectionPtr &pConnection, const std::list<SSuspensionData> &lsSuspensionData);
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sSuspensionData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetSuspensionData_NotEmpty(const _ConnectionPtr &pConnection, const SSuspensionData &sSuspensionData);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sSuspensionData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SSuspensionData &sSuspensionData);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sSuspensionData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SSuspensionData &sSuspensionData);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sSuspensionData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField_NotEmpty(const _RecordsetPtr &pRecordset, const SSuspensionData &sSuspensionData);
	// 写入字符串到数据库二进制
	static DWORD SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName);
	// 读出数据库二进制到字符串
	static DWORD GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName);
};

#endif