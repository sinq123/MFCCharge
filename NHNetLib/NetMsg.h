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
  // ���ݻ�����
  char m_chData[g_unNetPackSize];
  // ���ݶγ���
  size_t m_szBodyLength;
  // ip��������С
  const static size_t m_szIP = 16;
  // ip������
  char m_chIP[m_szIP];
};

