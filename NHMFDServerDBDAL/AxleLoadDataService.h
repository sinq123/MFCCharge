/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：AxleLoadDataService.h
* 文件标识：
* 描述：轴重数据表数据访问层
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


#ifndef AXLELOADDATASERVICE_H
#define AXLELOADDATASERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CAxleLoadDataService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CAxleLoadDataService(void);
	virtual ~CAxleLoadDataService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CAxleLoadDataService(const CAxleLoadDataService &);
	CAxleLoadDataService & operator =(const CAxleLoadDataService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sAxleLoadData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetAxleLoadData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SAxleLoadData &sAxleLoadData);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsAxleLoadData：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetAxleLoadData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SAxleLoadData> &lsAxleLoadData);
	
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sAxleLoadData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetAxleLoadCurveData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SAxleLoadData &sAxleLoadData);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsAxleLoadData：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetAxleLoadCurveData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SAxleLoadData> &lsAxleLoadData);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sAxleLoadData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetAxleLoadData(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);
	// 写入1条数据（仅静、动轮重）
	// 参数：
	// pConnection：连接指针引用
	// sAxleLoadData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetAxleLoadData_OnlyStaDynLoad(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);
	// 写入1条数据（仅加载轮重）
	// 参数：
	// pConnection：连接指针引用
	// sAxleLoadData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetAxleLoadData_OnlyLoadLoad(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sAxleLoadData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetAxleLoadData_NonEmpty(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsAxleLoadData：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetAxleLoadData(const _ConnectionPtr &pConnection, const std::list<SAxleLoadData> &lsAxleLoadData);

	// 写入1条数据
   // 参数：
   // pConnection：连接指针引用
	// sAxleLoadData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetAxleLoadCurveData(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);

	// 写入n条数据
   // 参数：
   // pConnection：连接指针引用
	// lsAxleLoadData：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetAxleLoadCurveData(const _ConnectionPtr &pConnection, const std::list<SAxleLoadData> &lsAxleLoadData);

	// 写入1条数据（1轴轮重）
	// 参数：
	// pConnection：连接指针引用
	// sAxleLoadData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetQX_Axle1Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);
	// 写入1条数据（2轴轮重）
	// 参数：
	// pConnection：连接指针引用
	// sAxleLoadData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetQX_Axle2Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);
	// 写入1条数据（3轴轮重）
	// 参数：
	// pConnection：连接指针引用
	// sAxleLoadData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetQX_Axle3Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);
	// 写入1条数据（4轴轮重）
	// 参数：
	// pConnection：连接指针引用
	// sAxleLoadData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetQX_Axle4Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);
	// 写入1条数据（5轴轮重）
	// 参数：
	// pConnection：连接指针引用
	// sAxleLoadData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetQX_Axle5Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);
	// 写入1条数据（6轴轮重）
	// 参数：
	// pConnection：连接指针引用
	// sAxleLoadData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetQX_Axle6Curve(const _ConnectionPtr &pConnection, const SAxleLoadData &sAxleLoadData);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sAxleLoadData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SAxleLoadData &sAxleLoadData);
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sAxleLoadData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct_Curve(const _RecordsetPtr &pRecordset, SAxleLoadData &sAxleLoadData);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sAxleLoadData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sAxleLoadData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField_OnlyStaDynLoad(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sAxleLoadData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField_OnlyLoadLoad(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	// 程序结构(Struct)到数据库字段(Field)，只写入非空的数据
	// 参数：
	// pRecordset：记录集指针应用
	// sAxleLoadData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	// 写曲线数据到数据库
	// 参数：
	// pRecordset：记录集指针应用
	// sAxleLoadData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField_Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	static DWORD StructToField_Axle1Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	static DWORD StructToField_Axle2Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	static DWORD StructToField_Axle3Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	static DWORD StructToField_Axle4Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	static DWORD StructToField_Axle5Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	static DWORD StructToField_Axle6Curve(const _RecordsetPtr &pRecordset, const SAxleLoadData &sAxleLoadData);
	
	// 写入字符串到数据库
	static DWORD SetStringToDB(_RecordsetPtr pRecordset, const SAxleLoadData &sAxleLoadData);
	// 写入字符串到数据库二进制
	static DWORD SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName);
	// 读出数据库二进制到字符串
	static DWORD GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName);
};

#endif