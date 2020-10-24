/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：RealTimeDataOfASM_ZipService.h
* 文件标识：
* 描述：RealTimeDataOfASM_Zip数据访问层
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

#ifndef REALTIMEDATAOFASM_ZIPSERVICE_H
#define REALTIMEDATAOFASM_ZIPSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CRealTimeDataOfASM_ZipService : public CNHModeServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CRealTimeDataOfASM_ZipService(void);
	virtual ~CRealTimeDataOfASM_ZipService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CRealTimeDataOfASM_ZipService(const CRealTimeDataOfASM_ZipService &);
	CRealTimeDataOfASM_ZipService & operator =(const CRealTimeDataOfASM_ZipService &);

public:
	// 读出1条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD GetRealTimeDataOfASM_Zip(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SRealTimeDataOfASM_Zip &sRealTimeDataOfASM_Zip);
	// 读出n条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD GetRealTimeDataOfASM_Zip(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SRealTimeDataOfASM_Zip> &lsRealTimeDataOfASM_Zip);

public:
	// 写入1条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD SetRealTimeDataOfASM_Zip(const _ConnectionPtr &pConnection, const SRealTimeDataOfASM_Zip &sRealTimeDataOfASM_Zip);
	// 写入n条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD SetRealTimeDataOfASM_Zip(const _ConnectionPtr &pConnection, const std::list<SRealTimeDataOfASM_Zip> &lsRealTimeDataOfASM_Zip);

public:
	// 数据库字段(Field)到程序结构(Struct)
	// pConnection：连接指针引用
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SRealTimeDataOfASM_Zip &sRealTimeDataOfASM_Zip);
	// 程序结构(Struct)到数据库字段(Field)
	// pConnection：连接指针引用
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SRealTimeDataOfASM_Zip &sRealTimeDataOfASM_Zip);
};

#endif