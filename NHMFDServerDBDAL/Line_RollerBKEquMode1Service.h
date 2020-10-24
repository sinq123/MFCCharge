/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：Line_RollerBKEquMode1Service.h
* 文件标识：
* 描述：检测线_滚筒制动台制式1表数据访问层
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


#ifndef LINE_ROLLERBKEQUMODE1SERVICE_H
#define LINE_ROLLERBKEQUMODE1SERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CLine_RollerBKEquMode1Service : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CLine_RollerBKEquMode1Service(void);
	virtual ~CLine_RollerBKEquMode1Service(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CLine_RollerBKEquMode1Service(const CLine_RollerBKEquMode1Service &);
	CLine_RollerBKEquMode1Service & operator =(const CLine_RollerBKEquMode1Service &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sLine_RollerBKEquMode1：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetLine_RollerBKEquMode1(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SLine_RollerBKEquMode1 &sLine_RollerBKEquMode1);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsLine_RollerBKEquMode1：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetLine_RollerBKEquMode1(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SLine_RollerBKEquMode1> &lsLine_RollerBKEquMode1);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sLine_RollerBKEquMode1：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetLine_RollerBKEquMode1(const _ConnectionPtr &pConnection, const SLine_RollerBKEquMode1 &sLine_RollerBKEquMode1);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsLine_RollerBKEquMode1：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetLine_RollerBKEquMode1(const _ConnectionPtr &pConnection, const std::list<SLine_RollerBKEquMode1> &lsLine_RollerBKEquMode1);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sLine_RollerBKEquMode1：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SLine_RollerBKEquMode1 &sLine_RollerBKEquMode1);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sLine_RollerBKEquMode1：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SLine_RollerBKEquMode1 &sLine_RollerBKEquMode1);
};

#endif