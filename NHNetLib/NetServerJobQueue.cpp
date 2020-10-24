#include "StdAfx.h"
#include "NetServerJobQueue.h"


CNetServerJobQueue::CNetServerJobQueue(void)
	: m_bExitWait(false)
{
}

CNetServerJobQueue::~CNetServerJobQueue(void)
{
}

void CNetServerJobQueue::SubmitJob(const CNetServerTask& job)
{
	boost::mutex::scoped_lock lock(m_Mutex);
	m_lsJob.push_back(job);
	m_WorkToBeDone.notify_all();
}

void CNetServerJobQueue::Notify_All()
{
	m_bExitWait = true;
	m_WorkToBeDone.notify_all();
}

void CNetServerJobQueue::GetJob(CNetServerTask& job)
{
	boost::mutex::scoped_lock lock(m_Mutex);
	while (m_lsJob.size()==0 && !m_bExitWait)
	{
		m_WorkToBeDone.wait(lock);
	}

	if (m_bExitWait)
	{
		return;
	}
	job = m_lsJob.front();
	m_lsJob.pop_front();
}