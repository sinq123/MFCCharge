/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：VehInfoService.h
* 文件标识：
* 描述：车辆信息表数据访问层
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


#ifndef VEHINFOSERVICE_H
#define VEHINFOSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CVehInfoService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CVehInfoService(void);
	virtual ~CVehInfoService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CVehInfoService(const CVehInfoService &);
	CVehInfoService & operator =(const CVehInfoService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sVehInfo：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetVehInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SVehInfo &sVehInfo);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsVehInfo：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetVehInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SVehInfo> &lsVehInfo);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sVehInfo：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetVehInfo(const _ConnectionPtr &pConnection, const SVehInfo &sVehInfo);
	// 写入1条数据，只写入非空的数据
	// 参数：
	// pConnection：连接指针引用
	// sVehInfo：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetVehInfo_NonEmpty(const _ConnectionPtr &pConnection, const SVehInfo &sVehInfo);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsVehInfo：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetVehInfo(const _ConnectionPtr &pConnection, const std::list<SVehInfo> &lsVehInfo);

public:
	// 读出生产日期
	// 参数：
	// pConnection：连接指针引用
	// strPlateNumber：号牌号码
	// strPlateTypeCode：号牌种类代码
	// strProductionDate：生产日期，格式："yyyy-mm-dd HH:MM:SS"，空代表数据库为NULL。
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetVehInfo_ProductionDate(const _ConnectionPtr &pConnection, const std::wstring &strPlateNumber, const std::wstring &strPlateTypeCode, std::wstring &strProductionDate);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sVehInfo：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SVehInfo &sVehInfo);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sVehInfo：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SVehInfo &sVehInfo);
	// 程序结构(Struct)到数据库字段(Field)，只写入非空的数据
	// 参数：
	// pRecordset：记录集指针应用
	// sVehInfo：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SVehInfo &sVehInfo);
};

#endif