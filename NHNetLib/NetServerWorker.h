#pragma once

#include "NetServerJobQueue.h"

class CNetServerWorker
{
public:
	CNetServerWorker(CNetServerJobQueue& jobQueue, std::size_t maxThreads = 1);
	virtual ~CNetServerWorker(void);

public:
	void Run();
	void Stop();
	virtual bool Work(CNetServerTask& jobTask) = 0;// 派生类需要重载此虚函数,以完成工作.

protected:
	void WorkLoop(); // 工作循环.

private:
	std::vector<boost::shared_ptr<boost::thread>> m_Threads;
	boost::mutex m_Mutex;
	std::size_t m_MaxThreads;
	CNetServerJobQueue& m_JobQueue;
	bool m_bExitThread;
};

