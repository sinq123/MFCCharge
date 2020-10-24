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
	virtual bool Work(CNetServerTask& jobTask) = 0;// ��������Ҫ���ش��麯��,����ɹ���.

protected:
	void WorkLoop(); // ����ѭ��.

private:
	std::vector<boost::shared_ptr<boost::thread>> m_Threads;
	boost::mutex m_Mutex;
	std::size_t m_MaxThreads;
	CNetServerJobQueue& m_JobQueue;
	bool m_bExitThread;
};

