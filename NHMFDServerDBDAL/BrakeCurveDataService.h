/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：BrakeCurveDataService.h
* 文件标识：
* 描述：制动曲线数据(BK: Brake; 下同)表数据访问层
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


#ifndef BRAKECURVEDATASERVICE_H
#define BRAKECURVEDATASERVICE_H

#include <list>
#include "..\NHMFDServerDBDAL\NHMFDServerDBModel.h"
#include "NHMFDServerDBService.h"

class CBrakeCurveDataService : public CNHMFDServerDBService
{
	// 禁用构造函数和析构函数(禁止生成对象)
private:
	CBrakeCurveDataService(void);
	virtual ~CBrakeCurveDataService(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CBrakeCurveDataService(const CBrakeCurveDataService &);
	CBrakeCurveDataService & operator =(const CBrakeCurveDataService &);

public:
	// 读出1条数据
   // 参数：
   // pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// sBrakeCurveData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetBrakeCurveData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, SBrakeCurveData &sBrakeCurveData);
	// 读出n条数据
   // 参数：
   // pConnection：连接指针引用
	// pwchSql：Sql语句字符串指针
	// lsBrakeCurveData：数据列表应用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD GetBrakeCurveData(const _ConnectionPtr &pConnection, const wchar_t *pwchSql, std::list<SBrakeCurveData> &lsBrakeCurveData);

public:
	// 写入1条数据
   // 参数：
   // pConnection：连接指针引用
	// sBrakeCurveData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetBrakeCurveData(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// 写入n条数据
   // 参数：
   // pConnection：连接指针引用
	// lsBrakeCurveData：数据列表引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetBrakeCurveData(const _ConnectionPtr &pConnection, const std::list<SBrakeCurveData> &lsBrakeCurveData);
	// 写入1条数据（1轴行车）
	// 参数：
	// pConnection：连接指针引用
	// sBrakeCurveData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetQX_Axle1Curve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// 写入1条数据（2轴行车）
	// 参数：
	// pConnection：连接指针引用
	// sBrakeCurveData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetQX_Axle2Curve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// 写入1条数据（3轴行车）
	// 参数：
	// pConnection：连接指针引用
	// sBrakeCurveData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetQX_Axle3Curve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// 写入1条数据（4轴行车）
	// 参数：
	// pConnection：连接指针引用
	// sBrakeCurveData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetQX_Axle4Curve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// 写入1条数据（5轴行车）
	// 参数：
	// pConnection：连接指针引用
	// sBrakeCurveData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetQX_Axle5Curve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// 写入1条数据（6轴行车）
	// 参数：
	// pConnection：连接指针引用
	// sBrakeCurveData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetQX_Axle6Curve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// 写入1条数据（1轴行车加载）
	// 参数：
	// pConnection：连接指针引用
	// sBrakeCurveData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetQX_Axle1LoadCurve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// 写入1条数据（2轴行车加载）
	// 参数：
	// pConnection：连接指针引用
	// sBrakeCurveData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetQX_Axle2LoadCurve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// 写入1条数据（3轴行车加载）
	// 参数：
	// pConnection：连接指针引用
	// sBrakeCurveData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetQX_Axle3LoadCurve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// 写入1条数据（4轴行车加载）
	// 参数：
	// pConnection：连接指针引用
	// sBrakeCurveData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetQX_Axle4LoadCurve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// 写入1条数据（5轴行车加载）
	// 参数：
	// pConnection：连接指针引用
	// sBrakeCurveData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetQX_Axle5LoadCurve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);
	// 写入1条数据（6轴行车加载）
	// 参数：
	// pConnection：连接指针引用
	// sBrakeCurveData：数据结构引用
	// 返回：受影响行数：
	// 非0xFFFFFFFF：正常，受影响行数
	// 0xFFFFFFFF：异常
	static DWORD SetQX_Axle6LoadCurve(const _ConnectionPtr &pConnection, const SBrakeCurveData &sBrakeCurveData);

private:
	// 数据库字段(Field)到程序结构(Struct)
   // 参数：
	// pRecordset：记录集指针应用
	// sBrakeCurveData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD FieldToStruct(const _RecordsetPtr &pRecordset, SBrakeCurveData &sBrakeCurveData);
	// 程序结构(Struct)到数据库字段(Field)
   // 参数：
	// pRecordset：记录集指针应用
	// sBrakeCurveData：数据结构引用
	// 返回：错误代码:
	// 0x00：正常
	// 非0x00：异常
	static DWORD StructToField(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData);
	static DWORD StructToField_Axle1Curve(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData);
	static DWORD StructToField_Axle2Curve(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData);
	static DWORD StructToField_Axle3Curve(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData);
	static DWORD StructToField_Axle4Curve(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData);
	static DWORD StructToField_Axle5Curve(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData);
	static DWORD StructToField_Axle6Curve(const _RecordsetPtr &pRecordset, const SBrakeCurveData &sBrakeCurveData);
	// 写入字符串到数据库
	static DWORD SetStringToDB(_RecordsetPtr pRecordset, const SBrakeCurveData &sBrakeCurveData);
	// 写入字符串到数据库二进制
	static DWORD SetStringToDBImage(_RecordsetPtr pRecordset, const std::string &str, const wchar_t* pwchFieldName);
	// 读出数据库二进制到字符串
	static DWORD GetStringFromDBImage(_RecordsetPtr pRecordset, std::string &str, const wchar_t* pwchFieldName);
};

#endif