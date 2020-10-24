/*
* Copyright (c) 佛山市南华仪器股份有限公司
	* All rights reserved.
*
* 文件名称：MainCorpService.h
* 文件标识：
* 描述：维修单位表数据访问层
*
* 版本：1.0
* 日期：20xx-xx-xx
* 作者：Ljf
*
*
* 历史信息：
*
* 版本：1.0.0beta1
* 日期：20xx-xx-xx
* 作者：Ljf
* 描述：正在开发
*/


#ifndef MAINCORPSERVICE_H
#define MAINCORPSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CMainCorpService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CMainCorpService(void);
	virtual ~CMainCorpService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CMainCorpService(const CMainCorpService &);
	CMainCorpService & operator =(const CMainCorpService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sMainCorp：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetMainCorp(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SMainCorp &sMainCorp);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsMainCorp：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetMainCorp(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SMainCorp> &lsMainCorp);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sMainCorp：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetMainCorp(const _ConnectionPtr &pConnection, const SMainCorp &sMainCorp);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsMainCorp：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetMainCorp(const _ConnectionPtr &pConnection, const std::list<SMainCorp> &lsMainCorp);

    // 更新一条数据
	// 参数：
	// pConnection：连接指针引用
	// sMainCorp：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
    static DWORD UpdateMainCorp(const _ConnectionPtr &pConnection, const SMainCorp &sMainCorp);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sMainCorp：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SMainCorp &sMainCorp);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sMainCorp：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SMainCorp &sMainCorp);
};

#endif