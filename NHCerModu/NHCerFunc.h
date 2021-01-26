#pragma once

class CNHCerFunc
{
public:
	CNHCerFunc(void);
	virtual ~CNHCerFunc(void);

	// 禁用拷贝构造函数和拷贝赋值函数
private:
	CNHCerFunc(const CNHCerFunc &);
	CNHCerFunc & operator =(const CNHCerFunc &);

public:
	// 获取硬盘序列号
	static bool GetHddSN(CString& strHddSN);

	// 验证硬盘证书
	// strMsg ：返回错误或警告信息
	// 返回值 ：true认证成功，false认证失败
	static bool ChkHddCer(CString& strMsg);

	// 验证程序版本
	// strMsg ：返回错误或警告信息
	// 返回值 ：true认证成功，false认证失败
	static bool ChkProVer(CString& strMsg);
};

