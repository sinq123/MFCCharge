#include "StdAfx.h"
#include "NetServerTask.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>


CNetServerTask::CNetServerTask(void)
	: m_pBytes(NULL)
	, m_pwchIP(NULL)
	, m_szLength(0)
{
}

CNetServerTask::CNetServerTask(const CNetServerTask& task)
{
	m_szLength = task.Length();
	m_pBytes = new BYTE[m_szLength+1]();
	memcpy_s(m_pBytes, m_szLength+1, task.Data(), task.Length());
	m_pwchIP = new wchar_t[m_szIP+1]();
	memcpy_s(m_pwchIP, (m_szIP+1)*2, task.GetIP(), m_szIP*2);
}

CNetServerTask& CNetServerTask::operator =(CNetServerTask &task)
{
	m_szLength = task.Length();
	m_pBytes = new BYTE[m_szLength+1]();
	memcpy_s(m_pBytes, m_szLength+1, task.Data(), task.Length());
	m_pwchIP = new wchar_t[m_szIP+1]();
	memcpy_s(m_pwchIP, (m_szIP+1)*2, task.GetIP(), m_szIP*2);
	return (*this);
}

CNetServerTask::~CNetServerTask(void)
{
	if (NULL != m_pBytes)
	{
		delete[] m_pBytes;
		m_pBytes = NULL;
	}
	if (NULL != m_pwchIP)
	{
		delete[] m_pwchIP;
		m_pwchIP = NULL;
	}
}

const BYTE* CNetServerTask::Data(void) const
{
	return m_pBytes;
}

void CNetServerTask::Data(const BYTE* pBytes, const size_t size)
{
	m_szLength = size;
	m_pBytes = new BYTE[m_szLength+1]();
	memcpy_s(m_pBytes, m_szLength+1, pBytes, size);
}

size_t CNetServerTask::Length(void) const
{
	return m_szLength;
}

//void CNetServerTask::Length(size_t szLength)
//{
//	m_szLength = szLength;
//}

const wchar_t* CNetServerTask::GetIP(void) const
{
	return m_pwchIP;
}

bool CNetServerTask::SetIP(const wchar_t* pwchIP)
{
	m_pwchIP = new wchar_t[m_szIP+1]();
	ZeroMemory(m_pwchIP, m_szIP);
	if (wcslen(pwchIP) >= m_szIP)
	{
		return false;
	}
	else
	{
		wcsncpy_s(m_pwchIP, m_szIP, pwchIP, wcslen(pwchIP));
		return true;
	}
}