/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：GADataRecordService.h
* 文件标识：
* 描述：
*
* 版本：1.0
* 日期：20xx-xx-xx
* 作者：
*
*
* 历史信息：
*
* 版本：1.0.0beta1
* 日期：20xx-xx-xx
* 作者：
* 描述：正在开发
*/


#ifndef GADATARECORDSERVICE_H
#define GADATARECORDSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CGADataRecordService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CGADataRecordService(void);
	virtual ~CGADataRecordService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CGADataRecordService(const CGADataRecordService &);
	CGADataRecordService & operator =(const CGADataRecordService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sGADataRecord：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetGADataRecord(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SGADataRecord &sGADataRecord);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsGADataRecord：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetGADataRecord(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SGADataRecord> &lsGADataRecord);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sGADataRecord：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetGADataRecord(const _ConnectionPtr &pConnection, const SGADataRecord &sGADataRecord);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsGADataRecord：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetGADataRecord(const _ConnectionPtr &pConnection, const std::list<SGADataRecord> &lsGADataRecord);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sGADataRecord：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SGADataRecord &sGADataRecord);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sGADataRecord：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SGADataRecord &sGADataRecord);
};

#endif