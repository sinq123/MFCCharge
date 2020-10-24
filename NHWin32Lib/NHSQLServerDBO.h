/*
* Copyright (c) 2010,佛山市南华仪器有限公司
* All rights reserved.
*
* 文件名称：NHSQLServerDBO.h
* 文件标识：
* 描述：SQLServer数据库操作
*
* 版本：1.0
* 作者：Cui
* 日期：2011-03-16
*
* 历史信息：
*
* 版本：1.0.5
* 日期：2012-09-01
* 作者：Cyx
* 描述：增加详细日志输出功能。
*
* 版本：1.0.4
* 日期：2012-04-27
* 作者：Raylee
* 描述：取消导入“msado15.dll”，改为导入“msado60_Backcompat_i386.tlb”
*
* 版本：1.0.3
* 日期：2011-11-24
* 作者：Cyx
* 描述：1）增加Debug状态下的调试输出信息。
*       2）其它细节改进。
*
* 版本：1.0.2
* 日期：2011-04-25
* 作者：Raylee
* 描述：注释数据库超时设置，使用ADO默认设置
*
* 版本：1.0.1
* 日期：2011-04-23
* 作者：Qin
* 描述：1）添加OpenDBOfOrcale函数(用于鞍山环保联网的数据同步器中)
*
* 版本：1.0.0
* 日期：2011-03-16
* 作者：Cui
* 描述：1）取消对NHLog的引用
*       2）取消函数CloseDB、CloseQuery的assert断定
*       3）正式发布使用
*/

#ifndef NH_SQLSERVER_DBO_H
#define NH_SQLSERVER_DBO_H

#import "msado60_Backcompat_i386.tlb" no_namespace rename("EOF","adoEOF")
#include <string>

class CNHSQLServerDBO
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CNHSQLServerDBO(void);
	virtual ~CNHSQLServerDBO(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CNHSQLServerDBO(const CNHSQLServerDBO &);
	CNHSQLServerDBO & operator =(const CNHSQLServerDBO &);

public:
	// 打开数据库(默认连接信息)
	// (in&out)pConnection:连接指针引用
	// (return)错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD OpenDB(_ConnectionPtr &pConnection);
	// 打开数据库(指定连接信息)
	// (in&out)pConnection:连接指针引用
	// (in)pwchSource:数据源
	// (in)pwchCatalog:数据库名称
	// (in)pwchUserID:用户名
	// (in)pwchPassword:密码
	// (return)错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD OpenDB(_ConnectionPtr &pConnectionconst,
		const wchar_t *const pwchDataSource,
		const wchar_t *const pwchInitialCatalog,
		const wchar_t *const pwchUserID,
		const wchar_t *const pwchPassword);
	// 打开数据库(SQL的Windows验证)
	// (in&out)pConnection:连接指针引用
	// (in)pwchSource:数据源
	// (in)pwchCatalog:数据库名称
	// (return)错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD OpenDB(_ConnectionPtr &pConnectionconst,
		const wchar_t *const pwchDataSource,
		const wchar_t *const pwchInitialCatalog);
	// 打开Oracle数据库(指定连接信息)
	// (in&out)pConnection:连接指针引用
	// (in)pwchSource:数据源
	// (in)pwchUserID:用户名
	// (in)pwchPassword:密码
	// (return)错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD OpenDBOfOrcale(_ConnectionPtr &pConnectionconst,
		const wchar_t *const pwchDataSource,
		const wchar_t *const pwchUserID,
		const wchar_t *const pwchPassword);
	// 关闭数据库
	// (in&out)pConnection:连接指针引用
	// (return)错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD CloseDB(_ConnectionPtr &pConnection);
	// 打开查询
	// (in)pConnection:连接指针引用
	// (in&out)pRecordset:记录集指针应用
	// (in)pwchSQL:查询语句字符串指针
	// (return)错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD OpenQuery(const _ConnectionPtr &pConnection, _RecordsetPtr &pRecordset, const wchar_t *const pwchSQL);
	// 关闭查询
	// (in&out)pRecordset:记录集指针应用
	// (return)错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD CloseQuery(_RecordsetPtr &pRecordset);
	// 获取字段值
	// (in&out)pRecordset:记录集指针应用
	// (out)vFieldValue:字段值引用
	// (in)pwchFieldName:字段名字符串指针
	// (return)错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD GetFieldValue(const _RecordsetPtr &pRecordset, _variant_t &vFieldValue, const wchar_t *const pwchFieldName);
	static DWORD GetFieldValue(const _RecordsetPtr &pRecordset, std::string &strValue, const wchar_t *const pwchFieldName);
	// 设置字段值
	// (in&out)pRecordset:记录集指针应用
	// (out)vFieldValue:字段值引用
	// (in)pwchFieldName:字段名字符串指针
	// (return)错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD PutFieldValue(const _RecordsetPtr &pRecordset, const _variant_t &vFieldValue, const wchar_t *const pwchFieldName);
	static DWORD PutFieldValue(const _RecordsetPtr &pRecordset, const std::string &strValue, const wchar_t *const pwchFieldName);
	// 执行DML
	// (in&out)pConnection:连接指针引用
	// (in)pwchSQL:DML语句字符串指针
	// (out)pnRowsInvolved：受影响的行的数目指针，可以为NULL
	// (return)错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD ExecuteDML(const _ConnectionPtr &pConnection, const wchar_t *const pwchSQL, int *const pnRowsInvolved=NULL);
	// 执行Count
	// (in&out)pConnection:连接指针引用
	// (in)pwchSQL:Count语句字符串指针, 一定要COUNT(*) AS CountNum
	// (out)pnCountNum：Count的数目指针，可以为NULL
	// (return)错误代码:
	// 0x00:正常
	// 非0x00:异常
	static DWORD ExecuteCount(const _ConnectionPtr &pConnection, const wchar_t *const pwchSQL, int *const pnCountNum);
	// 同步数据库时间
	static void SynchronizeDBTime(void);
	// 输出数据库错误信息（输出到输出窗口和日志文件）
	// (in&out)e:异常对象
	// (return)无
	static void OutputDBErrMsg(const _com_error& e);
	// 设置日志文件路径
	// (in&out)e:异常对象
	// (return)无
	static void SetLogFilePath(const wchar_t *const pFilePath);

private:
	// 日志文件路径
	static wchar_t m_wchLogFilePath[MAX_PATH];
};

#endif