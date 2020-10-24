/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：EmployeeInfoService.h
* 文件标识：
* 描述：员工信息表数据访问层
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


#ifndef EMPLOYEEINFOSERVICE_H
#define EMPLOYEEINFOSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CEmployeeInfoService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CEmployeeInfoService(void);
	virtual ~CEmployeeInfoService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CEmployeeInfoService(const CEmployeeInfoService &);
	CEmployeeInfoService & operator =(const CEmployeeInfoService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sEmployeeInfo：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetEmployeeInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SEmployeeInfo &sEmployeeInfo);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsEmployeeInfo：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetEmployeeInfo(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SEmployeeInfo> &lsEmployeeInfo);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sEmployeeInfo：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetEmployeeInfo(const _ConnectionPtr &pConnection, const SEmployeeInfo &sEmployeeInfo);
		// 写入1条数据，只写入非空的数据
	// 参数：
	// pConnection：连接指针引用
	// sEmployeeInfo：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetEmployeeInfo_NonEmpty(const _ConnectionPtr &pConnection, const SEmployeeInfo &sEmployeeInfo);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsEmployeeInfo：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetEmployeeInfo(const _ConnectionPtr &pConnection, const std::list<SEmployeeInfo> &lsEmployeeInfo);
	// 写入员工密码
	// 参数：
	// pConnection：连接指针引用
	// pwchEmployeeNumber：员工编号
	// pwchPassword：密码
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetEmployeePassword(const _ConnectionPtr &pConnection, const wchar_t *pwchEmployeeNumber, const wchar_t *pwchPassword);
	// 获取员工照片
	// 参数：
	// pConnection：连接指针引用
	// pwchEmployeeNumber：员工编号
	// strPhoto：照片数据
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetEmployeePhoto(const _ConnectionPtr &pConnection, const wchar_t *pwchEmployeeNumber, std::string &strPhoto);
	// 写入员工照片
	// 参数：
	// pConnection：连接指针引用
	// pwchEmployeeNumber：员工编号
	// strPhoto：照片数据
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetEmployeePhoto(const _ConnectionPtr &pConnection, const wchar_t *pwchEmployeeNumber, const std::string &strPhoto);
	// 获取员工权限
	// 参数：
	// pConnection：连接指针引用
	// pwchEmployeeNumber：员工编号
	// strPerm：权限数据
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetEmployeePerm(const _ConnectionPtr &pConnection, const wchar_t *pwchEmployeeNumber, std::string &strPerm);
	// 写入员工权限
	// 参数：
	// pConnection：连接指针引用
	// pwchEmployeeNumber：员工编号
	// strPerm：权限数据
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetEmployeePerm(const _ConnectionPtr &pConnection, const wchar_t *pwchEmployeeNumber, const std::string &strPerm);
	// 写入员工身份证
	// 参数：
	// pConnection：连接指针引用
	// pwchName：员工名字
	// pwchID：身份证号
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetEmployeeID(const _ConnectionPtr &pConnection, const wchar_t *pwchName, const wchar_t *pwchID);
	// 员工编号是否存在
	// 参数：
	// pConnection：连接指针引用
	// pwchEmployeeNumber：员工编号
	// 返回：
	// 非0xFFFFFFFF：正常
	// 0x00000001：存在
	// 0xFFFFFFFF：异常
	static DWORD IsEmployeeNumberExist(const _ConnectionPtr &pConnection, const wchar_t *pwchEmployeeNumber);
	// 用户名是否存在
	// 参数：
	// pConnection：连接指针引用
	// pwchUserName：用户名
	// 返回：
	// 非0xFFFFFFFF：正常
	// 0x00000001：存在
	// 0xFFFFFFFF：异常
	static DWORD IsUserNameExist(const _ConnectionPtr &pConnection, const wchar_t *pwchUserName);

private:
	// 数据库字段(Field)到程序结构(Struct)
	// 参数：
	// pRecordset：记录集指针应用
	// sEmployeeInfo：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SEmployeeInfo &sEmployeeInfo);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sEmployeeInfo：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SEmployeeInfo &sEmployeeInfo);
	// 程序结构(Struct)到数据库字段(Field)，只写入非空的数据
	// 参数：
	// pRecordset：记录集指针应用
	// sDetLog：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SEmployeeInfo &sEmployeeInfo);

	// 写入字符串到数据库二进制
	static DWORD SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName);
	// 读出数据库二进制到字符串
	static DWORD GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName);
};

#endif