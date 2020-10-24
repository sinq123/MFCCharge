#pragma once

#include <string>
#include "Judge.h"
#include "NHCommFunc.h"
#include "..\NHDetCommModu\NHConstDef.h"

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

#include "..\NHMFDServerDBDAL\NHMFDServerDBDAL.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHMFDServerDBDAL_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHMFDServerDBDAL.lib")
#endif

class CFinDetBsn
{
private:
	CFinDetBsn(void);
	virtual ~CFinDetBsn(void);
	// 禁用拷贝构造函数和拷贝赋值函数
	CFinDetBsn(const CFinDetBsn &);
	CFinDetBsn & operator =(const CFinDetBsn &);

public:
	static void FinDetBsn(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, const bool bReJud);
	static void FinDetBsn(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, const bool bReJud, const bool bIsMFD);
	static void STD_FinDetBsn(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, const bool bReJud);
	static void MFD_FinDetBsn(const _ConnectionPtr &pConnection, const std::wstring &strRunNum, const bool bReJud);
};

