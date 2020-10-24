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

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CSNGenerator(const CSNGenerator &);
	CSNGenerator & operator =(const CSNGenerator &);

public:
	// �ɽӿڣ�IP��ʽ
	static std::wstring GenerateRunNum(void);
	// �½ӿڣ�˳��Ÿ�ʽ
	static std::wstring GenRunNum(void);
	static std::wstring GenRepNum(void);
	static std::wstring GenRepNum_M(void);
	// ��׼��ʹ��ʱÿһ�����վ���Ų�һ������ʱͨ�������ļ���д�����ɰ����17Ϊ��ź��ۼ��21λ���
	static std::wstring GenRepNum(CStringW & strNum);
	static std::wstring GenRepNum_M(CStringW & strNum_M);
};

#endif
