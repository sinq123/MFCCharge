/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：DetAmountService.h
* 文件标识：
* 描述：检测数量(Det: Detecti; 下同)表数据访问层
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


#ifndef DETAMOUNTSERVICE_H
#define DETAMOUNTSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CDetAmountService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CDetAmountService(void);
	virtual ~CDetAmountService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CDetAmountService(const CDetAmountService &);
	CDetAmountService & operator =(const CDetAmountService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sDetAmount：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDetAmount(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetAmount &sDetAmount);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsDetAmount：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDetAmount(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetAmount> &lsDetAmount);
	// 读出1条数据
	// 参数：
	// pwchLineNumber：检测线编号
	// st：日期
	// sDetAmount：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDetAmount(const wchar_t *pwchLineNumber, const SYSTEMTIME &st, SDetAmount &sDetAmount);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sDetAmount：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetAmount(const _ConnectionPtr &pConnection, const SDetAmount &sDetAmount);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsDetAmount：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetAmount(const _ConnectionPtr &pConnection, const std::list<SDetAmount> &lsDetAmount);
	// 写入1条数据
	// 参数：
	// sDetAmount：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetAmount(const SDetAmount &sDetAmount);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sDetAmount：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SDetAmount &sDetAmount);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sDetAmount：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SDetAmount &sDetAmount);
};

#endif