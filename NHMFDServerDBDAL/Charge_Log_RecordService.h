






#ifndef CHARGELOGRECORDSERVICE_H
#define CHARGELOGRECORDSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CCharge_Log_RecordService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CCharge_Log_RecordService(void);
	virtual ~CCharge_Log_RecordService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CCharge_Log_RecordService(const CCharge_Log_RecordService &);
	CCharge_Log_RecordService & operator =(const CCharge_Log_RecordService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sCharge_Log_Record：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetCharge_Log_Record(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SCharge_Log_Record &sCharge_Log_Record);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsCharge_Log_Record：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetCharge_Log_Record(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SCharge_Log_Record> &lsCharge_Log_Record);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sCharge_Log_Record：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetCharge_Log_Record(const _ConnectionPtr &pConnection, const SCharge_Log_Record &sCharge_Log_Record);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsCharge_Log_Record：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetCharge_Log_Record(const _ConnectionPtr &pConnection, const std::list<SCharge_Log_Record> &lsCharge_Log_Record);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sCharge_Log_Record：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SCharge_Log_Record &sCharge_Log_Record);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sCharge_Log_Record：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SCharge_Log_Record &sCharge_Log_Record);
};

#endif