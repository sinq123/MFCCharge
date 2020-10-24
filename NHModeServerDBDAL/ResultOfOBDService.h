/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：ResultOfVMASService.h
* 文件标识：
* 描述：ResultOfVMAS数据访问层
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

#ifndef RESULTOFOBDSERVICE_H
#define RESULTOFOBDSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CResultOfOBDService : public CNHModeServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CResultOfOBDService(void);
	virtual ~CResultOfOBDService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CResultOfOBDService(const CResultOfOBDService &);
	CResultOfOBDService & operator =(const CResultOfOBDService &);

public:
	// 读出1条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD GetResultOfOBD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SResultOfOBD &sResultOfOBD);
	// 读出n条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD GetResultOfOBD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SResultOfOBD> &lsResultOfOBD);

public:
	// 写入1条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD SetResultOfOBD(const _ConnectionPtr &pConnection, const SResultOfOBD &sResultOfOBD);
	// 写入n条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD SetResultOfOBD(const _ConnectionPtr &pConnection, const std::list<SResultOfOBD> &lsResultOfOBD);

public:
	// 数据库字段(Field)到程序结构(Struct)
	// pConnection：连接指针引用
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SResultOfOBD &sResultOfOBD);
	// 程序结构(Struct)到数据库字段(Field)
	// pConnection：连接指针引用
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SResultOfOBD &sResultOfOBD);
};

#endif