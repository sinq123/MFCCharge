#include "StdAfx.h"
#include "NetServerWork.h"

CNetServerWork* g_pNetServerWork = NULL;


CNetServerWork::CNetServerWork(CNetServerJobQueue& _jobqueue, std::size_t _maxthreads/* = 1*/)
	: CNetServerWorker(_jobqueue, _maxthreads)
	, m_pfOnReadCallBack(NULL)
{
	// 初始化临界保护量
	::InitializeCriticalSection(&m_sCriticalSection);

	g_pNetServerWork = this;
}


CNetServerWork::~CNetServerWork(void)
{
	// 删除临界保护量
	::DeleteCriticalSection(&m_sCriticalSection);
}

bool CNetServerWork::Work(CNetServerTask& task)       // 在些完成实际任务.
{
	// 进入临界区
	::EnterCriticalSection(&m_sCriticalSection);


	// 数据处理
	if (NULL != m_pfOnReadCallBack)
	{
		m_pfOnReadCallBack(task.GetIP(), task.Data(), task.Length());
	}

	// 离开临界区
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