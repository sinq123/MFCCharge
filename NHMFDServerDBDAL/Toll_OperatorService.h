











#ifndef TOLL_OPERATORSERVICE_H
#define TOLL_OPERATORSERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CTollOperatorService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CTollOperatorService(void);
	virtual ~CTollOperatorService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CTollOperatorService(const CTollOperatorService &);
	CTollOperatorService & operator =(const CTollOperatorService &);

public:
	// 读出1条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sTollOperator：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetTollOperator(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SToll_Operator &sToll_Operator);
	// 读出n条数据
	// 参数：
	// pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsTollOperator：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetTollOperator(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SToll_Operator> &lsToll_Operator);

public:
	// 写入1条数据
	// 参数：
	// pConnection：连接指针引用
	// sTollOperator：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetTollOperator(const _ConnectionPtr &pConnection, const SToll_Operator &sToll_Operator);
		// 写入1条数据，只写入非空的数据
	// 参数：
	// pConnection：连接指针引用
	// sTollOperator：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetTollOperator_NonEmpty(const _ConnectionPtr &pConnection, const SToll_Operator &sToll_Operator);
	// 写入n条数据
	// 参数：
	// pConnection：连接指针引用
	// lsTollOperator：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetTollOperator(const _ConnectionPtr &pConnection, const std::list<SToll_Operator> &lsToll_Operator);
	// 获取员工密码
	// 参数：
	// pConnection：连接指针引用
	// pwchName：用户名
	// pwchPassword：密码
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetTollOperatorPassword(const _ConnectionPtr &pConnection, const wchar_t *pwchName, std::wstring &strPassword);
	// 写入员工密码
	// 参数：
	// pConnection：连接指针引用
	// pwchName：用户名
	// pwchPassword：密码
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetTollOperatorPassword(const _ConnectionPtr &pConnection, const wchar_t *pwchName, const wchar_t *pwchPassword);
	// 获取员工权限
	// 参数：
	// pConnection：连接指针引用
	// pwchName：员工编号
	// strPerm：权限数据
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetTollOperatorPerm(const _ConnectionPtr &pConnection, const wchar_t *pwchName, std::string &strPerm);
	// 写入员工权限
	// 参数：
	// pConnection：连接指针引用
	// pwchName：用户名
	// strPerm：权限数据
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetTollOperatorPerm(const _ConnectionPtr &pConnection, const wchar_t *pwchName, const std::string &strPerm);
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
	// sTollOperator：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SToll_Operator &sToll_Operator);
	// 程序结构(Struct)到数据库字段(Field)
	// 参数：
	// pRecordset：记录集指针应用
	// sTollOperator：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SToll_Operator &sToll_Operator);
	// 程序结构(Struct)到数据库字段(Field)，只写入非空的数据
	// 参数：
	// pRecordset：记录集指针应用
	// sDetLog：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField_NonEmpty(const _RecordsetPtr &pRecordset, const SToll_Operator &sToll_Operator);

	// 写入字符串到数据库二进制
	static DWORD SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName);
	// 读出数据库二进制到字符串
	static DWORD GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName);
};

#endif