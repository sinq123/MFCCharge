/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：DBVersionService.h
* 文件标识：
* 描述：数据库结构版本表数据访问层
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


#ifndef DBVERSIONSERVICE_H
#define DBVERSIONSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CDBVersionService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CDBVersionService(void);
	virtual ~CDBVersionService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CDBVersionService(const CDBVersionService &);
	CDBVersionService & operator =(const CDBVersionService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sDBVersion：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDBVersion(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDBVersion &sDBVersion);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsDBVersion：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDBVersion(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDBVersion> &lsDBVersion);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sDBVersion：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDBVersion(const _ConnectionPtr &pConnection, const SDBVersion &sDBVersion);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsDBVersion：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDBVersion(const _ConnectionPtr &pConnection, const std::list<SDBVersion> &lsDBVersion);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sDBVersion：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SDBVersion &sDBVersion);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sDBVersion：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SDBVersion &sDBVersion);

	// 写入内存缓冲区数据到数据库二进制
	static DWORD SetByteToDBImage(_RecordsetPtr pRecordset, const BYTE *pbBuf, const unsigned int nBufSize, const wchar_t* pwchFieldName);
	// 读出数据库二进制到内存缓冲区
	static DWORD GetByteFromDBImage(_RecordsetPtr pRecordset, BYTE **pbBuf, unsigned int &nBufSize, const wchar_t* pwchFieldName);
};

#endif