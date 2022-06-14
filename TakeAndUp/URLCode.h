/*******************************************
* URLCode.h
******************************************/
#pragma once
#include <string>
using std::string;

class CURLCode 
{
public:
	CURLCode();
	virtual ~CURLCode();
	
public:
	static string Encode(const char* lpszData);
	static string Decode(string inTmp);
	static std::wstring EncodeW(const wchar_t* lpszData);
	static std::wstring DecodeW(std::wstring inTmp);

private:
	inline static unsigned char toHex(const unsigned char &x){ return x > 9 ? x + 55: x + 48; }
	inline static unsigned char fromHex(const unsigned char &x){ return x > 64 ? x - 55 : x - 48; }
};