/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：ManualData_MFDService.h
* 文件标识：
* 描述：人工数据表(安检)数据访问层
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


#ifndef MANUALDATA_MFDSERVICE_H
#define MANUALDATA_MFDSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CManualData_MFDService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CManualData_MFDService(void);
	virtual ~CManualData_MFDService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CManualData_MFDService(const CManualData_MFDService &);
	CManualData_MFDService & operator =(const CManualData_MFDService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sManualData_MFD：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetManualData_MFD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SManualData_MFD &sManualData_MFD);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsManualData_MFD：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetManualData_MFD(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SManualData_MFD> &lsManualData_MFD);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sManualData_MFD：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetManualData_MFD(const _ConnectionPtr &pConnection, const SManualData_MFD &sManualData_MFD);

	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsManualData_MFD：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetManualData_MFD(const _ConnectionPtr &pConnection, const std::list<SManualData_MFD> &lsManualData_MFD);

	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sManualData_MFD：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetManualData_MFD_NonEmpty(const _ConnectionPtr &pConnection, const SManualData_MFD &sManualData_MFD);	

	// 只写入人工不合格汇总信息
	// 参数：
	// pConnection：连接指针引用
	// sManualData_MFD：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetManualData_MFD_OnlyNoPassCol(const _ConnectionPtr &pConnection, const SManualData_MFD &sManualData_MFD);

	// 写入检测项目状态
	// 参数：
	// pConnection：连接指针引用
	// strRunningNumber：检测日志编号
	// nDetItemID：检测项目序号,如项目1只填1即可
	// nState：状态（0-合格.1-不合格.2-不适用）
	// strItemDes：项目说明
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetManualData_MFD_ItemState(const _ConnectionPtr &pConnection, const std::wstring &strRunningNumber, const int nDetItemID, const int nState, const std::wstring &strItemDes);

	// 清空ManualData_MFD所有数据
	// sManualData_MFD：数据结构引用
	void Clear(SManualData_MFD &sManualData_MFD);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sManualData_MFD：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SManualData_MFD &sManualData_MFD);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sManualData_MFD：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SManualData_MFD &sManualData_MFD);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sManualData_MFD：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SManualData_MFD &sManualData_MFD);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sManualData_MFD：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField_OnlyNoPassCol(const _RecordsetPtr &pRecordset, const SManualData_MFD &sManualData_MFD);
};

#endif