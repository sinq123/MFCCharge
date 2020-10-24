/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：VMASDataService.h
* 文件标识：
* 描述：VMASData数据访问层
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

#ifndef VMASDATASERVICE_H
#define VMASDATASERVICE_H

#include <list>
#include "NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVMASDataService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CVMASDataService(void);
	virtual ~CVMASDataService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CVMASDataService(const CVMASDataService &);
	CVMASDataService & operator =(const CVMASDataService &);

public:
	// 读出1条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD GetVMASData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVMASData &sVMASData);
	// 读出n条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD GetVMASData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVMASData> &lsVMASData);

public:
	// 写入1条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD SetVMASData(const _ConnectionPtr &pConnection, const SVMASData &sVMASData);
	// 写入n条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD SetVMASData(const _ConnectionPtr &pConnection, const std::list<SVMASData> &lsVMASData);

public:
	// 数据库字段(Field)到程序结构(Struct)
	// pConnection：连接指针引用
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVMASData &sVMASData);
	// 程序结构(Struct)到数据库字段(Field)
	// pConnection：连接指针引用
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVMASData &sVMASData);
};

#endif