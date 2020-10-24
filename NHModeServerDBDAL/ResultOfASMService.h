/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：ResultOfASMService.h
* 文件标识：
* 描述：ResultOfASM数据访问层
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

#ifndef RESULTOFASMSERVICE_H
#define RESULTOFASMSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CResultOfASMService : public CNHModeServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CResultOfASMService(void);
	virtual ~CResultOfASMService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CResultOfASMService(const CResultOfASMService &);
	CResultOfASMService & operator =(const CResultOfASMService &);

public:
	// 读出1条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD GetResultOfASM(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SResultOfASM &sResultOfASM);
	// 读出n条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD GetResultOfASM(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SResultOfASM> &lsResultOfASM);

public:
	// 写入1条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD SetResultOfASM(const _ConnectionPtr &pConnection, const SResultOfASM &sResultOfASM);
	// 写入n条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD SetResultOfASM(const _ConnectionPtr &pConnection, const std::list<SResultOfASM> &lsResultOfASM);

public:
	// 数据库字段(Field)到程序结构(Struct)
	// pConnection：连接指针引用
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SResultOfASM &sResultOfASM);
	// 程序结构(Struct)到数据库字段(Field)
	// pConnection：连接指针引用
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SResultOfASM &sResultOfASM);
};

#endif