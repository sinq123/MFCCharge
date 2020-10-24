/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：DetItemService.h
* 文件标识：
* 描述：检测项目表数据访问层
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


#ifndef DETITEMSERVICE_H
#define DETITEMSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CDetItemService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CDetItemService(void);
	virtual ~CDetItemService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CDetItemService(const CDetItemService &);
	CDetItemService & operator =(const CDetItemService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sDetItem：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDetItem(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetItem &sDetItem);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsDetItem：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDetItem(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetItem> &lsDetItem);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sDetItem：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetItem(const _ConnectionPtr &pConnection, const SDetItem &sDetItem);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsDetItem：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetItem(const _ConnectionPtr &pConnection, const std::list<SDetItem> &lsDetItem);
	//// 读出检测项目状态
	// 参数：
	// pConnection：连接指针引用
	// strRunningNumber：检测日志编号
	// strDetItem：检测项目
	// nState：状态
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDetItem_State(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strDetItem, int &nState);
	// 写入检测项目状态
	// 参数：
	// pConnection：连接指针引用
	// strRunningNumber：检测日志编号
	// strDetItem：检测项目
	// nState：状态
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetItem_State(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strDetItem, const int nState);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sDetItem：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SDetItem &sDetItem);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sDetItem：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SDetItem &sDetItem);
};

#endif