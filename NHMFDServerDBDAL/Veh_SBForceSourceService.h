/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：Veh_SBForceSourceService.h
* 文件标识：
* 描述：制动力源表数据访问层
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


#ifndef VEH_SBFORCESOURCESERVICE_H
#define VEH_SBFORCESOURCESERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVeh_SBForceSourceService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CVeh_SBForceSourceService(void);
	virtual ~CVeh_SBForceSourceService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CVeh_SBForceSourceService(const CVeh_SBForceSourceService &);
	CVeh_SBForceSourceService & operator =(const CVeh_SBForceSourceService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sVeh_SBForceSource：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetVeh_SBForceSource(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVeh_SBForceSource &sVeh_SBForceSource);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsVeh_SBForceSource：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetVeh_SBForceSource(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVeh_SBForceSource> &lsVeh_SBForceSource);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sVeh_SBForceSource：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetVeh_SBForceSource(const _ConnectionPtr &pConnection, const SVeh_SBForceSource &sVeh_SBForceSource);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsVeh_SBForceSource：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetVeh_SBForceSource(const _ConnectionPtr &pConnection, const std::list<SVeh_SBForceSource> &lsVeh_SBForceSource);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sVeh_SBForceSource：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVeh_SBForceSource &sVeh_SBForceSource);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sVeh_SBForceSource：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVeh_SBForceSource &sVeh_SBForceSource);
};

#endif