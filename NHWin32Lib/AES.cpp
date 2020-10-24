#include "StdAfx.h"
#include "AES.h"

#include "D:/TPL/CryptoppLib/osrng.h"
#include "D:/TPL/CryptoppLib/modes.h"

#ifdef _DEBUG
#pragma comment(lib, "D:/TPL/CryptoppLib/DLib/cryptlib.lib")
#else
#pragma comment(lib, "D:/TPL/CryptoppLib/RLib/cryptlib.lib")
#endif

CAes::CAes(void)
{
	m_pbKey = new BYTE[CryptoPP::AES::DEFAULT_KEYLENGTH]();
	m_pbIV = new BYTE[CryptoPP::AES::BLOCKSIZE]();

	//memcpy(m_pbKey, "Nanhua.Co.,Ltd.", CryptoPP::AES::DEFAULT_KEYLENGTH);
	//memcpy(m_pbIV, "Huabei.Co.,Ltd.", CryptoPP::AES::BLOCKSIZE);
	//	// 升级为5x版本
	memcpy(m_pbKey, "Foshan&Nanhua.,", CryptoPP::AES::DEFAULT_KEYLENGTH);
	memcpy(m_pbIV, "Foshan&Huabei.,", CryptoPP::AES::BLOCKSIZE);
}


CAes::~CAes(void)
{
	delete m_pbKey;
	delete m_pbIV;
}


DWORD CAes::Encryption(const BYTE *pbInString, BYTE *pbOutString, const UINT uiLength)
{
	assert(pbInString != NULL);
	assert(pbOutString != NULL);
	assert(uiLength >= 0);
	
	CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cfbEncryption(m_pbKey, CryptoPP::AES::DEFAULT_KEYLENGTH, m_pbIV);
	cfbEncryption.ProcessData(pbOutString, pbInString, uiLength);

	return 0x00;
}

DWORD CAes::Decryption(const BYTE *pbInString, BYTE *pbOutString, const UINT uiLength)
{
	assert(pbInString != NULL);
	assert(pbOutString != NULL);
	assert(uiLength >= 0);
	
	CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption cfbDecryption(m_pbKey, CryptoPP::AES::DEFAULT_KEYLENGTH, m_pbIV);
	cfbDecryption.ProcessData(pbOutString, pbInString, uiLength);

	return 0x00;
}

// 加密
std::string CAes::Encryption(const std::string &strPlain)
{
	UINT uiLength = strPlain.size();
	std::auto_ptr<BYTE> pCipherBuf(new BYTE[uiLength]());

	CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cfbEncryption(m_pbKey, CryptoPP::AES::DEFAULT_KEYLENGTH, m_pbIV);
	cfbEncryption.ProcessData(pCipherBuf.get(), (BYTE *)strPlain.data(), uiLength);
	
	return std::string((const char *)pCipherBuf.get(), uiLength);
}

// 解密
std::string CAes::Decryption(const std::string &strCipher)
{
	UINT uiLength = strCipher.size();
	std::auto_ptr<BYTE> pPlainBuf(new BYTE[uiLength]());

	CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption cfbDecryption(m_pbKey, CryptoPP::AES::DEFAULT_KEYLENGTH, m_pbIV);
	cfbDecryption.ProcessData(pPlainBuf.get(), (BYTE *)strCipher.data(), uiLength);
	
	return std::string((const char *)pPlainBuf.get(), uiLength);
}