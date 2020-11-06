







#ifndef BILL_OF_ARREARSSERVICE_H
#define BILL_OF_ARREARSSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CBillOfArrearsService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CBillOfArrearsService(void);
	virtual ~CBillOfArrearsService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CBillOfArrearsService(const CBillOfArrearsService &);
	CBillOfArrearsService & operator =(const CBillOfArrearsService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sVeh_Color：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetBillOfArrears(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SBillOfArrears &sBillOfArrears);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsVeh_Color：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetBillOfArrears(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SBillOfArrears> &lsBillOfArrears);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sVeh_Color：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetBillOfArrears(const _ConnectionPtr &pConnection, const SBillOfArrears &sBillOfArrears, const BOOL &BNoEmpty = FALSE);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsVeh_Color：数据列表引用
	// BNoEmpty 是否非空才写入 true 是非空写入， false 全部写入
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetBillOfArrears(const _ConnectionPtr &pConnection, const std::list<SBillOfArrears> &lsBillOfArrears, const BOOL &BNoEmpty = FALSE);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sVeh_Color：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SBillOfArrears &sBillOfArrears);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sVeh_Color：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SBillOfArrears &sBillOfArrears, const BOOL &BNoEmpty = FALSE);
};

#endif