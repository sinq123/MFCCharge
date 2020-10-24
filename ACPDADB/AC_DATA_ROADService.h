/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：AC_DATA_ROADService.h
* 文件标识：
* 描述：PDA路试数据表数据访问层
*
* 版本：1.0
* 日期：2015-01-28
* 作者：Shaojm
*
*
* 历史信息：
*
* 版本：1.0.0
* 日期：2015-01-28
* 作者：Shaojm
* 描述：正在发布
*/


#if !defined(PDADBDAL_AC_DATA_ROAD_h)
#define PDADBDAL_AC_DATA_ROAD_h

#include <list>
#include "AC_DATA_ROAD.h"

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

#ifdef PDADBDAL_EXPORTS
#define PDADBDAL_API __declspec(dllexport)
#else
#define PDADBDAL_API __declspec(dllimport)
#endif

class PDADBDAL_API CAC_DATA_ROADService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CAC_DATA_ROADService(void);
	virtual ~CAC_DATA_ROADService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CAC_DATA_ROADService(const CAC_DATA_ROADService &);
	CAC_DATA_ROADService & operator =(const CAC_DATA_ROADService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sAC_DATA_ROAD：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetAC_DATA_ROAD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SAC_DATA_ROAD &sAC_DATA_ROAD);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsAC_DATA_ROAD：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetAC_DATA_ROAD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SAC_DATA_ROAD> &lsAC_DATA_ROAD);
public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sAC_DATA_ROAD：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetAC_DATA_ROAD(const _ConnectionPtr &pConnection, const SAC_DATA_ROAD &sAC_DATA_ROAD);
	// 写入1条数据，只写入非空的数据
	// 参数：
	// pConnection：连接指针引用
	// sAC_DATA_ROAD：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetAC_DATA_ROAD_NonEmpty(const _ConnectionPtr &pConnection, const SAC_DATA_ROAD &sAC_DATA_ROAD);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsAC_DATA_ROAD：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetAC_DATA_ROAD(const _ConnectionPtr &pConnection, const std::list<SAC_DATA_ROAD> &lsAC_DATA_ROAD);

public:
	// 读出flag标识
	// 参数：
	// pConnection：连接指针引用
	// strjylsh：检验流水号
	// strflag：flag标识
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetAC_DATA_ROAD_flag(const _ConnectionPtr &pConnection, const std::wstring &strjylsh, std::wstring &strflag);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sAC_DATA_ROAD：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SAC_DATA_ROAD &sAC_DATA_ROAD);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sAC_DATA_ROAD：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SAC_DATA_ROAD &sAC_DATA_ROAD);
	// 程序结构(Struct)到数据库字段(Field)，只写入非空的数据
	// 参数：
	// pRecordset：记录集指针应用
	// sAC_DATA_ROAD：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SAC_DATA_ROAD &sAC_DATA_ROAD);
};

#endif