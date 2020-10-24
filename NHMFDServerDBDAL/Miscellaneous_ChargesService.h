














#ifndef MISCELLANEOUS_CHARGESSERVICE_H
#define MISCELLANEOUS_CHARGESSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CMiscellaneous_ChargesService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CMiscellaneous_ChargesService(void);
	virtual ~CMiscellaneous_ChargesService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CMiscellaneous_ChargesService(const CMiscellaneous_ChargesService &);
	CMiscellaneous_ChargesService & operator =(const CMiscellaneous_ChargesService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sMiscellaneous_Charges：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetMiscellaneous_Charges(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SMiscellaneous_Charges &sMiscellaneous_Charges);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsMiscellaneous_Charges：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetMiscellaneous_Charges(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SMiscellaneous_Charges> &lsMiscellaneous_Charges);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sMiscellaneous_Charges：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetMiscellaneous_Charges(const _ConnectionPtr &pConnection, const SMiscellaneous_Charges &sMiscellaneous_Charges);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsMiscellaneous_Charges：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetMiscellaneous_Charges(const _ConnectionPtr &pConnection, const std::list<SMiscellaneous_Charges> &lsMiscellaneous_Charges);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sMiscellaneous_Charges：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SMiscellaneous_Charges &sMiscellaneous_Charges);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sMiscellaneous_Charges：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SMiscellaneous_Charges &sMiscellaneous_Charges);
};

#endif