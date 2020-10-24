/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：VMASProDataService.h
* 文件标识：
* 描述：VMASProData数据访问层
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

#ifndef VMASPRODATASERVICE_H
#define VMASPRODATASERVICE_H

#include <list>
#include "NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVMASProDataService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CVMASProDataService(void);
	virtual ~CVMASProDataService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CVMASProDataService(const CVMASProDataService &);
	CVMASProDataService & operator =(const CVMASProDataService &);

public:
	// 读出1条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD GetVMASProData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVMASProData &sVMASProData);
	// 读出n条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD GetVMASProData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVMASProData> &lsVMASProData);

public:
	// 写入1条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD SetVMASProData(const _ConnectionPtr &pConnection, const SVMASProData &sVMASProData);
	// 写入n条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD SetVMASProData(const _ConnectionPtr &pConnection, const std::list<SVMASProData> &lsVMASProData);

public:
	// 数据库字段(Field)到程序结构(Struct)
	// pConnection：连接指针引用
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVMASProData &sVMASProData);
	// 程序结构(Struct)到数据库字段(Field)
	// pConnection：连接指针引用
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVMASProData &sVMASProData);
};

#endif