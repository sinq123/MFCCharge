/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：RealTimeDataOfDIS_ZipService.h
* 文件标识：
* 描述：RealTimeDataOfDIS_Zip数据访问层
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

#ifndef REALTIMEDATAOFDIS_ZIPSERVICE_H
#define REALTIMEDATAOFDIS_ZIPSERVICE_H

#include <list>
#include "NHModeServerDBModel.h"
#include "NHModeServerDBService.h"

class CRealTimeDataOfDIS_ZipService : public CNHModeServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CRealTimeDataOfDIS_ZipService(void);
	virtual ~CRealTimeDataOfDIS_ZipService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CRealTimeDataOfDIS_ZipService(const CRealTimeDataOfDIS_ZipService &);
	CRealTimeDataOfDIS_ZipService & operator =(const CRealTimeDataOfDIS_ZipService &);

public:
	// 读出1条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD GetRealTimeDataOfDIS_Zip(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SRealTimeDataOfDIS_Zip &sRealTimeDataOfDIS_Zip);
	// 读出n条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD GetRealTimeDataOfDIS_Zip(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SRealTimeDataOfDIS_Zip> &lsRealTimeDataOfDIS_Zip);

public:
	// 写入1条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD SetRealTimeDataOfDIS_Zip(const _ConnectionPtr &pConnection, const SRealTimeDataOfDIS_Zip &sRealTimeDataOfDIS_Zip);
	// 写入n条数据
	// pConnection：连接指针引用
	// 返回：受影响行数：
	static DWORD SetRealTimeDataOfDIS_Zip(const _ConnectionPtr &pConnection, const std::list<SRealTimeDataOfDIS_Zip> &lsRealTimeDataOfDIS_Zip);

public:
	// 数据库字段(Field)到程序结构(Struct)
	// pConnection：连接指针引用
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SRealTimeDataOfDIS_Zip &sRealTimeDataOfDIS_Zip);
	// 程序结构(Struct)到数据库字段(Field)
	// pConnection：连接指针引用
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SRealTimeDataOfDIS_Zip &sRealTimeDataOfDIS_Zip);
};

#endif