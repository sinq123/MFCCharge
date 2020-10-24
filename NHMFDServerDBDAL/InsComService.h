/*
* Copyright (c) 佛山市南华仪器股份有限公司
	* All rights reserved.
*
* 文件名称：InsComService.h
* 文件标识：
* 描述：保险公司表数据访问层
*
* 版本：1.0
* 日期：20xx-xx-xx
* 作者：Ljf
*
*
* 历史信息：
*
*/


#ifndef INSCOMSERVICE_H
#define INSCOMSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CInsComService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CInsComService(void);
	virtual ~CInsComService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CInsComService(const CInsComService &);
	CInsComService & operator =(const CInsComService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sInsCom：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetInsCom(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SInsCom &sInsCom);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsInsCom：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetInsCom(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SInsCom> &lsInsCom);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sInsCom：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetInsCom(const _ConnectionPtr &pConnection, const SInsCom &sInsCom);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsInsCom：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetInsCom(const _ConnectionPtr &pConnection, const std::list<SInsCom> &lsInsCom);

    // 更新一条数据
	// 参数：
	// pConnection：连接指针引用
	// sInsCom：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
    static DWORD UpdateInsCom(const _ConnectionPtr &pConnection, const SInsCom &sInsCom);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sInsCom：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SInsCom &sInsCom);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sInsCom：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SInsCom &sInsCom);
};

#endif