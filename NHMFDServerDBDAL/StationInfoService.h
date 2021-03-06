/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：StationInfoService.h
* 文件标识：
* 描述：检测站信息表数据访问层
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


#ifndef STATIONINFOSERVICE_H
#define STATIONINFOSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CStationInfoService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CStationInfoService(void);
	virtual ~CStationInfoService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CStationInfoService(const CStationInfoService &);
	CStationInfoService & operator =(const CStationInfoService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sStationInfo：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetStationInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SStationInfo &sStationInfo);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsStationInfo：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetStationInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SStationInfo> &lsStationInfo);
	// 读取证书
	static DWORD GetCertificateAuthentication(const _ConnectionPtr &pConnection, std::string &str);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sStationInfo：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetStationInfo(const _ConnectionPtr &pConnection, const SStationInfo &sStationInfo);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsStationInfo：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetStationInfo(const _ConnectionPtr &pConnection, const std::list<SStationInfo> &lsStationInfo);
	// 写入证书
	static DWORD SetCertificateAuthentication(const _ConnectionPtr &pConnection, std::string &str);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sStationInfo：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SStationInfo &sStationInfo);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sStationInfo：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SStationInfo &sStationInfo);
	// 读出数据库二进制到字符串
	static DWORD GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName);
	// 写入字符串到数据库二进制
	static DWORD SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName);
};

#endif