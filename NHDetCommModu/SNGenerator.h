#pragma once

#include <string>

#ifndef SNGENERATOR_H
#define SNGENERATOR_H

//#ifdef DLL_FILE
//class _declspec(dllexport) CSNGenerator
//#else
//class _declspec(dllimport) CSNGenerator
//#endif
class CSNGenerator
{
public:
	CSNGenerator(void);
	virtual ~CSNGenerator(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CSNGenerator(const CSNGenerator &);
	CSNGenerator & operator =(const CSNGenerator &);

public:
	// 旧接口，IP格式
	static std::wstring GenerateRunNum(void);
	// 新接口，顺序号格式
	static std::wstring GenRunNum(void);
	static std::wstring GenRepNum(void);
	static std::wstring GenRepNum_M(void);
	// 标准版使用时每一个检测站代号不一样，暂时通过配置文件来写入生成安检的17为编号和综检的21位编号
	static std::wstring GenRepNum(CStringW & strNum);
	static std::wstring GenRepNum_M(CStringW & strNum_M);
};

#endif
