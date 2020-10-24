/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：Emp_TrainingInfoService.h
* 文件标识：
* 描述：接受培训情况表数据访问层
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


#ifndef EMP_TRAININGINFOSERVICE_H
#define EMP_TRAININGINFOSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CEmp_TrainingInfoService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CEmp_TrainingInfoService(void);
	virtual ~CEmp_TrainingInfoService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CEmp_TrainingInfoService(const CEmp_TrainingInfoService &);
	CEmp_TrainingInfoService & operator =(const CEmp_TrainingInfoService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sEmp_TrainingInfo：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetEmp_TrainingInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SEmp_TrainingInfo &sEmp_TrainingInfo);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsEmp_TrainingInfo：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetEmp_TrainingInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SEmp_TrainingInfo> &lsEmp_TrainingInfo);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sEmp_TrainingInfo：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetEmp_TrainingInfo(const _ConnectionPtr &pConnection, const SEmp_TrainingInfo &sEmp_TrainingInfo);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsEmp_TrainingInfo：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetEmp_TrainingInfo(const _ConnectionPtr &pConnection, const std::list<SEmp_TrainingInfo> &lsEmp_TrainingInfo);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sEmp_TrainingInfo：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SEmp_TrainingInfo &sEmp_TrainingInfo);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sEmp_TrainingInfo：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SEmp_TrainingInfo &sEmp_TrainingInfo);
};

#endif