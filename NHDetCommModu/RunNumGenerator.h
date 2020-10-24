#pragma once

#include <string>

#ifndef RUNNUMGENERATOR_H
#define RUNNUMGENERATOR_H

//#ifdef DLL_FILE
//class _declspec(dllexport) CRunNumGenerator
//#else
//class _declspec(dllimport) CRunNumGenerator
//#endif
class CRunNumGenerator
{
public:
	CRunNumGenerator(void);
	virtual ~CRunNumGenerator(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CRunNumGenerator(const CRunNumGenerator &);
	CRunNumGenerator & operator =(const CRunNumGenerator &);

public:
	static std::wstring GenerateRunNum(void);
};

#endif
