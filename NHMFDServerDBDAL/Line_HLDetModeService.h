/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：Line_HLDetModeService.h
* 文件标识：
* 描述：检测线_前照灯检测方式表数据访问层
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


#ifndef LINE_HLDETMODESERVICE_H
#define LINE_HLDETMODESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CLine_HLDetModeService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CLine_HLDetModeService(void);
	virtual ~CLine_HLDetModeService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CLine_HLDetModeService(const CLine_HLDetModeService &);
	CLine_HLDetModeService & operator =(const CLine_HLDetModeService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sLine_HLDetMode：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetLine_HLDetMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SLine_HLDetMode &sLine_HLDetMode);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsLine_HLDetMode：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetLine_HLDetMode(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SLine_HLDetMode> &lsLine_HLDetMode);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sLine_HLDetMode：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetLine_HLDetMode(const _ConnectionPtr &pConnection, const SLine_HLDetMode &sLine_HLDetMode);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsLine_HLDetMode：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetLine_HLDetMode(const _ConnectionPtr &pConnection, const std::list<SLine_HLDetMode> &lsLine_HLDetMode);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sLine_HLDetMode：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SLine_HLDetMode &sLine_HLDetMode);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sLine_HLDetMode：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SLine_HLDetMode &sLine_HLDetMode);
};

#endif