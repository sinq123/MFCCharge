/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：DetTypeService.h
* 文件标识：
* 描述：检测类别表数据访问层
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


#ifndef DETTYPESERVICE_H
#define DETTYPESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CDetTypeService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CDetTypeService(void);
	virtual ~CDetTypeService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CDetTypeService(const CDetTypeService &);
	CDetTypeService & operator =(const CDetTypeService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sDetType：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDetType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetType &sDetType);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsDetType：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDetType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetType> &lsDetType);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sDetType：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetType(const _ConnectionPtr &pConnection, const SDetType &sDetType);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsDetType：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetType(const _ConnectionPtr &pConnection, const std::list<SDetType> &lsDetType);
	// 更新一条数据
	// 参数：
	// pConnection：连接指针引用
	// sDetType：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
    static DWORD UpdateDetType(const _ConnectionPtr &pConnection, const SDetType &sDetType);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sDetType：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SDetType &sDetType);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sDetType：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SDetType &sDetType);
};

#endif