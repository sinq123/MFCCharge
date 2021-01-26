#pragma once

#include <string>



class CRJYZ
{
public:
	CRJYZ();
	virtual ~CRJYZ();

private:
	CRJYZ(const CRJYZ &);
	CRJYZ & operator =(const CRJYZ &);

public:
	static bool IsYZ(std::wstring &strMsg, std::wstring &strDLMM );
};