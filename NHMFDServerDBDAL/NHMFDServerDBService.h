/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：NHMFDServerDBService.h
* 文件标识：
* 描述：NHMFDServerDB数据库数据访问层
*
* 版本：1.0
* 作者：Cyx
* 日期：20xx-xx-xx
*
*
* 历史信息：
*
* 版本：1.0.0beta1
* 日期：20xx-xx-xx
* 作者：Cyx
* 描述：正在开发
*/

#pragma once

#ifndef NHMFDSERVERDBSERVICE_H
#define NHMFDSERVERDBSERVICE_H

#include <string>

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

class CNHMFDServerDBService
{
public:
	CNHMFDServerDBService(void);
	virtual ~CNHMFDServerDBService(void);

private:
	// 禁用拷贝构造函数和拷贝赋值函数
	CNHMFDServerDBService(const CNHMFDServerDBService &);
	CNHMFDServerDBService & operator =(const CNHMFDServerDBService &);

public:
	// 获取连接参数
	// 参数：
	// pwchDataSource:数据源字符串指针
	// pwchInitialCatalog:数据库名称字符串指针
	// pwchUserID:用户名字符串指针
	// pwchPassword:密码字符串指针
	// 返回：错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD GetConnectionParams(wchar_t *const pwchDataSource, wchar_t *const pwchInitialCatalog, wchar_t *const pwchUserID, wchar_t *const pwchPassword);
	// 打开数据库
	// 参数：
	// pConnection:连接指针引用
	// 返回：错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD OpenDB(_ConnectionPtr &pConnection);
	// 关闭数据库
	// 参数：
	// pConnection:连接指针引用
	// 返回：错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD CloseDB(_ConnectionPtr &pConnection);
	// 打开查询
	// 参数：
	// pConnection:连接指针引用
	// pRecordset:记录集指针应用
	// pwchSQL:查询语句字符串指针
	// 返回：错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD OpenQuery(const _ConnectionPtr &pConnection, _RecordsetPtr &pRecordset, const wchar_t *const pwchSQL);
	// 关闭查询
	// 参数：
	// pRecordset:记录集指针应用
	// 返回：错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD CloseQuery(_RecordsetPtr &pRecordset);
	// 获取字段值
	// 参数：
	// pRecordset:记录集指针应用
	// vFieldValue:字段值引用
	// pwchFieldName:字段名字符串指针
	// 返回：错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD GetFieldValue(const _RecordsetPtr &pRecordset, _variant_t &vFieldValue, const wchar_t *const pwchFieldName);
	static DWORD GetFieldValue(const _RecordsetPtr &pRecordset, std::string &strValue, const wchar_t *const pwchFieldName);
	// 设置字段值
	// 参数：
	// pRecordset:记录集指针应用
	// vFieldValue:字段值引用
	// pwchFieldName:字段名字符串指针
	// 返回：错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD PutFieldValue(const _RecordsetPtr &pRecordset, const _variant_t &vFieldValue, const wchar_t *const pwchFieldName);
	static DWORD PutFieldValue(const _RecordsetPtr &pRecordset, const std::string &strValue, const wchar_t *const pwchFieldName);
	// 执行DML
	// 参数：
	// pConnection:连接指针引用
	// pwchSQL:DML语句字符串指针
	// pnRowsInvolved：受影响的行的数目指针，可以为NULL
	// 返回：错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD ExecuteDML(const _ConnectionPtr &pConnection, const wchar_t *const pwchSQL, int *const pnRowsInvolved=NULL);
	// 输出数据库错误信息（输出到输出窗口和日志文件）
	// 参数：
	// e:异常对象
	// (return)无
	static void OutputDBErrMsg(const _com_error& e);

protected:
	// 使写入字符串长度适合数据库字段长度（针对nvarchar属性字段）
	// 参数：
	// pRecordset:记录集指针应用
	// pwchFieldName:字段名字符串指针
	// strFieldValueWritten:要写入的字段值
	// 返回：错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD FitFieldLength(const _RecordsetPtr &pRecordset, const wchar_t *const pwchFieldName, std::wstring &strFieldValueWritten);
};

#endif