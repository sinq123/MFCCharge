/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：GAVideoRecordService.h
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


#ifndef GAVIDEORECORDSERVICE_H
#define GAVIDEORECORDSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CGAVideoRecordService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CGAVideoRecordService(void);
	virtual ~CGAVideoRecordService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CGAVideoRecordService(const CGAVideoRecordService &);
	CGAVideoRecordService & operator =(const CGAVideoRecordService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sGAVideoRecord：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetGAVideoRecord(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SGAVideoRecord &sGAVideoRecord);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsGAVideoRecord：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetGAVideoRecord(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SGAVideoRecord> &lsGAVideoRecord);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sGAVideoRecord：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetGAVideoRecord(const _ConnectionPtr &pConnection, const SGAVideoRecord &sGAVideoRecord);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsGAVideoRecord：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetGAVideoRecord(const _ConnectionPtr &pConnection, const std::list<SGAVideoRecord> &lsGAVideoRecord);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sGAVideoRecord：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SGAVideoRecord &sGAVideoRecord);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sGAVideoRecord：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SGAVideoRecord &sGAVideoRecord);
};

#endif