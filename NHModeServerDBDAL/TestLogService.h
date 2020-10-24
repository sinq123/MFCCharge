/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：TestLogService.h
* 文件标识：
* 描述：TestLog数据访问层
*
* 版本：1.0
* 日期：20xx-xx-xx
* 作者：wuyq
*
*
* 历史信息：
*
* 版本：1.0.0beta1
* 日期：20xx-xx-xx
* 作者：wuyq
* 描述：正在开发
*/

#ifndef TESTLOGSERVICE_H
#define TESTLOGSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CTestLogService : public CNHModeServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CTestLogService(void);
	virtual ~CTestLogService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CTestLogService(const CTestLogService &);
	CTestLogService & operator =(const CTestLogService &);

public:
	// 读出1条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD GetTestLog(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, STestLog &sTestLog);
	// 读出n条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD GetTestLog(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<STestLog> &lsTestLog);

public:
	// 写入1条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD SetTestLog(const _ConnectionPtr &pConnection, const STestLog &sTestLog);
	// 写入n条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD SetTestLog(const _ConnectionPtr &pConnection, const std::list<STestLog> &lsTestLog);

public:
	// 数据库字段(Field)到程序结构(Struct)
	// pConnection：连接指针引用
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, STestLog &sTestLog);
	// 程序结构(Struct)到数据库字段(Field)
	// pConnection：连接指针引用
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const STestLog &sTestLog);
};

#endif