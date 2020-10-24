#include "StdAfx.h"
#include "NetServerWorker.h"
#include <iostream>

CNetServerWorker::CNetServerWorker(CNetServerJobQueue& jobQueue, std::size_t maxThreads/* = 1*/)
	: m_JobQueue(jobQueue),
	m_MaxThreads(maxThreads),
	m_bExitThread(false)
{
}

CNetServerWorker::~CNetServerWorker(void)
{
}

void CNetServerWorker::Run()
{
	try
	{
		for (std::size_t i = 0; i < m_MaxThreads; ++i) 
		{
			boost::shared_ptr<boost::thread> _thread(new boost::thread(
				boost::bind(&CNetServerWorker::WorkLoop, this)));
			m_Threads.push_back(_thread);
		}

		for (std::size_t i = 0; i < m_MaxThreads; ++i) 
		{
			m_Threads[i]->join();
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "ERROR INFO:" << e.what() << std::endl;
	}
}

void CNetServerWorker::Stop()
{
	m_bExitThread = true;
	m_JobQueue.Notify_All();
}

void CNetServerWorker::WorkLoop()               // 所有工作在些完成.
{
	do 
	{
		CNetServerTask task;
		m_JobQueue.GetJob(task);

		if (Work(task))
		{
			continue;
		}
		else
		{
			break;
		}
	} 
	while (!m_bExitThread);
}