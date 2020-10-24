#ifndef OTHERDATASERVICE_H
#define OTHERDATASERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class COtherDataService : public CNHMFDServerDBService
{
public:
	COtherDataService(void);
	virtual ~COtherDataService(void);

private:
	COtherDataService(const COtherDataService &);
	COtherDataService & operator =(const COtherDataService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sOtherData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetOtherData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SOtherData &sOtherData);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsOtherData：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetOtherData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SOtherData> &lsOtherData);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sOtherData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetOtherData(const _ConnectionPtr &pConnection, const SOtherData &sOtherData);
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sOtherData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetOtherData_NonEmpty(const _ConnectionPtr &pConnection, const SOtherData &sOtherData);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsOtherData：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetOtherData(const _ConnectionPtr &pConnection, const std::list<SOtherData> &lsOtherData);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sOtherData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SOtherData &sOtherData);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sOtherData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SOtherData &sOtherData);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sOtherData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SOtherData &sOtherData);

private:
	// 写入字符串到数据库二进制
	static DWORD SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName);
	// 读出数据库二进制到字符串
	static DWORD GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName);
};
#endif