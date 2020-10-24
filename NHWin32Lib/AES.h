#pragma once
#include <string>

class CAes
{
public:
	CAes(void);
	~CAes(void);

public:
	// ����
	std::string Encryption(const std::string &strPlain);
	DWORD Encryption(const BYTE *pbInString, BYTE *pbOutString, const UINT uiLength);
	// ����
	std::string Decryption(const std::string &strCipher);
	DWORD Decryption(const BYTE *pbInString, BYTE *pbOutString, const UINT uiLength);
	
private:
	BYTE *m_pbKey;
	BYTE *m_pbIV;
};

