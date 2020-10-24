#pragma once

#include <list>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include "NetServerTask.h"

class CNetServerJobQueue
{
public:
	CNetServerJobQueue(void);
	virtual ~CNetServerJobQueue(void);

public:
	void SubmitJob(const CNetServerTask& job);
	void GetJob(CNetServerTask& job);
	void Notify_All();

private:
	bool m_bExitWait;
	std::list<CNetServerTask> m_lsJob;
	boost::mutex m_Mutex;
	boost::condition m_WorkToBeDone;
};

