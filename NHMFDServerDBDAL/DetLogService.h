/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：DetLogService.h
* 文件标识：
* 描述：检测日志表数据访问层
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


#ifndef DETLOGSERVICE_H
#define DETLOGSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CDetLogService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CDetLogService(void);
	virtual ~CDetLogService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CDetLogService(const CDetLogService &);
	CDetLogService & operator =(const CDetLogService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sDetLog：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDetLog(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SDetLog &sDetLog);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsDetLog：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDetLog(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SDetLog> &lsDetLog);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sDetLog：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetLog(const _ConnectionPtr &pConnection, const SDetLog &sDetLog);
	// 写入1条数据，只写入非空的数据
	// 参数：
	// pConnection：连接指针引用
	// sDetLog：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetLog_NonEmpty(const _ConnectionPtr &pConnection, const SDetLog &sDetLog);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsDetLog：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetLog(const _ConnectionPtr &pConnection, const std::list<SDetLog> &lsDetLog);
	
public:
	// 读出检测状态
	// 参数：
	// pConnection：连接指针引用
	// strRunningNumber：检测日志编号
	// strDetStatus：检测状态
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDetLog_DetStatus(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, std::wstring &strDetStatus);
	// 写入检测状态
	// 参数：
	// pConnection：连接指针引用
	// strRunningNumber：检测日志编号
	// strDetStatus：检测状态
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetLog_DetStatus(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strDetStatus);
	// 写入主控IP
	// 参数：
	// pConnection：连接指针引用
	// strRunningNumber：检测日志编号
	// strMCSIP：主控IP
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetLog_MCSIP(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strMCSIP);
	// 读出引车员
	// 参数：
	// pConnection：连接指针引用
	// strRunningNumber：检测日志编号
	// strDriver：引车员
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDetLog_Driver(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, std::wstring &strDriver);
	// 写入引车员
	// 参数：
	// pConnection：连接指针引用
	// strRunningNumber：检测日志编号
	// strDriver：引车员
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetLog_Driver(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strDriver);
	// 读出整车判定
	// 参数：
	// pConnection：连接指针引用
	// strRunningNumber：检测日志编号
	// nVehJudge：整车判定
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDetLog_VehJudge(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, int &nVehJudge);
	// 写入整车判定
	// 参数：
	// pConnection：连接指针引用
	// strRunningNumber：检测日志编号
	// nVehJudge：整车判定
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetLog_VehJudge(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const int nVehJudge);
	// 写入上线时间
	// 参数：
	// pConnection：连接指针引用
	// strRunningNumber：检测日志编号
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetLog_OnLineTime(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber);
	// 写入下线时间
	// 参数：
	// pConnection：连接指针引用
	// strRunningNumber：检测日志编号
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetLog_OffLineTime(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber);
	// 写入检测线编号
	// 参数：
	// pConnection：连接指针引用
	// strRunningNumber：检测日志编号
	// strLineNumber：检测线编号
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetLog_LineNumber(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strLineNumber);
	// 写入检测报告编号
	// 参数：
	// pConnection：连接指针引用
	// strRunningNumber：检测日志编号
	// strReportNumber：检测报告编号
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetLog_ReportNumber(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const std::wstring &strReportNumber);
	// 读出检测周期ID
	// 参数：
	// pConnection：连接指针引用
	// strRunningNumber：检测日志编号
	// nDetPeriodID：检测周期ID
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetDetLog_DetPeriodID(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, int &nDetPeriodID);
	// 写入上传公安次数
	// 参数：
	// pConnection：连接指针引用
	// strRunningNumber：检测日志编号
	// nUploadVATimes：检测状态
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetLog_UploadVATimes(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const int &nUploadVATimes);

	// 写入上传运管次数
	// 参数：
	// pConnection：连接指针引用
	// strRunningNumber：检测日志编号
	// nUploadVATimes：检测状态
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetDetLog_UploadTMTimes(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const int &nUploadTMTimes);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sDetLog：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SDetLog &sDetLog);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sDetLog：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SDetLog &sDetLog);
	// 程序结构(Struct)到数据库字段(Field)，只写入非空的数据
	// 参数：
	// pRecordset：记录集指针应用
	// sDetLog：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SDetLog &sDetLog);
};

#endif