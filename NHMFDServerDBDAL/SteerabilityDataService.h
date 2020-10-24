/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：SteerabilityDataService.h
* 文件标识：
* 描述：转向操纵性数据表数据访问层
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


#ifndef STEERABILITYDATASERVICE_H
#define STEERABILITYDATASERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CSteerabilityDataService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CSteerabilityDataService(void);
	virtual ~CSteerabilityDataService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CSteerabilityDataService(const CSteerabilityDataService &);
	CSteerabilityDataService & operator =(const CSteerabilityDataService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sSteerabilityData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetSteerabilityData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSteerabilityData &sSteerabilityData);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsSteerabilityData：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetSteerabilityData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SSteerabilityData> &lsSteerabilityData);
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sSteerabilityData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetSideslipData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSteerabilityData &sSteerabilityData);
	// 读出1条数据（侧滑曲线）
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sSteerabilityData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetSideslipData_SideslipCurve(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SSteerabilityData &sSteerabilityData);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sSteerabilityData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetSteerabilityData(const _ConnectionPtr &pConnection, const SSteerabilityData &sSteerabilityData);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsSteerabilityData：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetSteerabilityData(const _ConnectionPtr &pConnection, const std::list<SSteerabilityData> &lsSteerabilityData);
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sSteerabilityData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetSteerabilityData_NonEmpty(const _ConnectionPtr &pConnection, const SSteerabilityData &sSteerabilityData);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsSteerabilityData：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetSteerabilityData_NonEmpty(const _ConnectionPtr &pConnection, const std::list<SSteerabilityData> &lsSteerabilityData);
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sSteerabilityData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetSideslipData(const _ConnectionPtr &pConnection, const SSteerabilityData &sSteerabilityData);
	// 写入1条数据（侧滑曲线）
	// 参数：
	// pConnection：连接指针引用
	// sSteerabilityData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetSideslipData_SideslipCurve(const _ConnectionPtr &pConnection, const SSteerabilityData &sSteerabilityData);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sSteerabilityData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SSteerabilityData &sSteerabilityData);
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sSteerabilityData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct_Sideslip(const _RecordsetPtr &pRecordset, SSteerabilityData &sSteerabilityData);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sSteerabilityData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SSteerabilityData &sSteerabilityData);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sSteerabilityData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SSteerabilityData &sSteerabilityData);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sSteerabilityData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField_Sideslip(const _RecordsetPtr &pRecordset, const SSteerabilityData &sSteerabilityData);
	
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sSteerabilityData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct_SideslipCurve(const _RecordsetPtr &pRecordset, SSteerabilityData &sSteerabilityData);
	// 程序结构(Struct)到数据库字段(Field)
    // 参数：
	// pRecordset：记录集指针应用
	// sSteerabilityData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField_SideslipCurve(const _RecordsetPtr &pRecordset, const SSteerabilityData &sSteerabilityData);
	
	// 写入字符串到数据库
	static DWORD SetStringToDB(_RecordsetPtr pRecordset, const SSteerabilityData &sSteerabilityData);
	// 写入字符串到数据库二进制
	static DWORD SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName);
	// 读出数据库二进制到字符串
	static DWORD GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName);
};

#endif