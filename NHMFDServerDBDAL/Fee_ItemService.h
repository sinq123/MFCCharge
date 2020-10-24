














#ifndef FEE_ITEMSERVICE_H
#define FEE_ITEMSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CFee_ItemService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CFee_ItemService(void);
	virtual ~CFee_ItemService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CFee_ItemService(const CFee_ItemService &);
	CFee_ItemService & operator =(const CFee_ItemService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sFee_Item：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetFee_Item(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SFee_Item &sFee_Item);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsFee_Item：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetFee_Item(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SFee_Item> &lsFee_Item);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sFee_Item：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetFee_Item(const _ConnectionPtr &pConnection, const SFee_Item &sFee_Item);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsFee_Item：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetFee_Item(const _ConnectionPtr &pConnection, const std::list<SFee_Item> &lsFee_Item);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sFee_Item：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SFee_Item &sFee_Item);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sFee_Item：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SFee_Item &sFee_Item);
};

#endif