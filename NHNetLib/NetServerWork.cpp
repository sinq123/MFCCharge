#include "StdAfx.h"
#include "NetServerWork.h"

CNetServerWork* g_pNetServerWork = NULL;


CNetServerWork::CNetServerWork(CNetServerJobQueue& _jobqueue, std::size_t _maxthreads/* = 1*/)
	: CNetServerWorker(_jobqueue, _maxthreads)
	, m_pfOnReadCallBack(NULL)
{
	// ��ʼ���ٽ籣����
	::InitializeCriticalSection(&m_sCriticalSection);

	g_pNetServerWork = this;
}


CNetServerWork::~CNetServerWork(void)
{
	// ɾ���ٽ籣����
	::DeleteCriticalSection(&m_sCriticalSection);
}

bool CNetServerWork::Work(CNetServerTask& task)       // ��Щ���ʵ������.
{
	// �����ٽ���
	::EnterCriticalSection(&m_sCriticalSection);


	// ���ݴ���
	if (NULL != m_pfOnReadCallBack)
	{
		m_pfOnReadCallBack(task.GetIP(), task.Data(), task.Length());
	}

	// �뿪�ٽ���
	::LeaveCriticalSection(&m_sCriticalSection);

	return true;
}

void CNetServerWork::SetOnReadCallBack(void (CALLBACK * pfOnReadCallBack)(const wchar_t* pwchIP, const BYTE* pBytes, const size_t size))
{
	m_pfOnReadCallBack = pfOnReadCallBack;
}

void CNetServerWork::SetOnReadNULL(void)
{
	m_pfOnReadCallBack = NULL;
}