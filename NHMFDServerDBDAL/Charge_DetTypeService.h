







#ifndef CHARGE_DETTYPE_H
#define CHARGE_DETTYPE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CCharge_DetTypeService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CCharge_DetTypeService(void);
	virtual ~CCharge_DetTypeService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CCharge_DetTypeService(const CCharge_DetTypeService &);
	CCharge_DetTypeService & operator =(const CCharge_DetTypeService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sVeh_Color：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetCharge_DetType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SCharge_DetType &sCharge_DetType);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsVeh_Color：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetCharge_DetType(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SCharge_DetType> &lsCharge_DetType);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sVeh_Color：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetCharge_DetType(const _ConnectionPtr &pConnection, const SCharge_DetType &sCharge_DetType);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsVeh_Color：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetCharge_DetType(const _ConnectionPtr &pConnection, const std::list<SCharge_DetType> &lsCharge_DetType);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sVeh_Color：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SCharge_DetType &sCharge_DetType);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sVeh_Color：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SCharge_DetType &sCharge_DetType);
};

#endif