#pragma once

#include "NHNetConstDef.h"

class CNetMsg
{
public:
	CNetMsg(void);
	virtual ~CNetMsg(void);

public:
  const char* Data() const;
  char* Data();

  size_t Length() const;

  const char* Body() const;
  char* Body();

  size_t BodyLength() const;
  void BodyLength(size_t szLength);

  bool SetIP(const char* pchIP);
  const char* GetIP() const;

  bool DecodeHeader();
  void EncodeHeader();

private:
  // 数据缓冲区
  char m_chData[g_unNetPackSize];
  // 数据段长度
  size_t m_szBodyLength;
  // ip缓冲区大小
  const static size_t m_szIP = 16;
  // ip缓冲区
  char m_chIP[m_szIP];
};

