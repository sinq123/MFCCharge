#include "StdAfx.h"
#include "NetMsg.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

CNetMsg::CNetMsg(void)
	: m_szBodyLength(0)
{
}


CNetMsg::~CNetMsg(void)
{
}

const char* CNetMsg::Data() const
{
	return m_chData;
}

char* CNetMsg::Data()
{
	return m_chData;
}

size_t CNetMsg::Length() const
{
	return g_unNetPackHeaderSize + g_unNetPackDSSPSize + m_szBodyLength;
}

const char* CNetMsg::Body() const
{
	return m_chData + g_unNetPackHeaderSize + g_unNetPackDSSPSize;
}

char* CNetMsg::Body()
{
	return m_chData + g_unNetPackHeaderSize + g_unNetPackDSSPSize;
}

size_t CNetMsg::BodyLength() const
{
	return m_szBodyLength;
}

void CNetMsg::BodyLength(size_t szLength)
{
	m_szBodyLength = szLength;
	if (m_szBodyLength > g_unQNSize+g_unPCNTSize+g_unPNOSize+g_unNetPackPayloadSize+g_unNetPackTailSize)
	{
		m_szBodyLength = g_unQNSize+g_unPCNTSize+g_unPNOSize+g_unNetPackPayloadSize+g_unNetPackTailSize;
	}
}

const char* CNetMsg::GetIP() const
{
	return m_chIP;
}

bool CNetMsg::SetIP(const char* pchIP)
{
	ZeroMemory(m_chIP, sizeof(m_chIP));
	if (strlen(pchIP) >= m_szIP)
	{
		return false;
	}
	else
	{
		strncpy_s(m_chIP, _countof(m_chIP), pchIP, strlen(pchIP));
		return true;
	}
}

  bool CNetMsg::DecodeHeader()
  {
    using namespace std; // For strncat and atoi.
    char header[g_unNetPackHeaderSize + g_unNetPackDSSPSize + 1] = "";
    strncat_s(header, m_chData, g_unNetPackHeaderSize + g_unNetPackDSSPSize);

	char headerbody[g_unNetPackDSSPSize + 1] = "";

	for (int i=0; i<g_unNetPackDSSPSize; i++)
	{
		headerbody[i] = header[g_unNetPackHeaderSize + i];
	}
    m_szBodyLength = atoi(headerbody) + g_unNetPackTailSize;
    if (m_szBodyLength > g_unQNSize+g_unPCNTSize+g_unPNOSize+g_unNetPackPayloadSize+g_unNetPackTailSize)
    {
      m_szBodyLength = 0;
      return false;
    }

    return true;
  }

  void CNetMsg::EncodeHeader()
  {
	  using namespace std; // For sprintf and memcpy.
	  char header[g_unNetPackHeaderSize + g_unNetPackDSSPSize + 1] = "";

	  char headerbody[g_unNetPackDSSPSize + 1] = "";
	  _snprintf_s(headerbody, g_unNetPackDSSPSize + 1,  _TRUNCATE, "%04d", m_szBodyLength- g_unNetPackTailSize);

	  strncpy_s(header, g_pchNetPackHeaderSign, g_unNetPackHeaderSize + g_unNetPackDSSPSize +1);
	  strncat_s(header, headerbody, g_unNetPackHeaderSize + g_unNetPackDSSPSize +1);
	  memcpy(m_chData, header, g_unNetPackHeaderSize + g_unNetPackDSSPSize);
  }