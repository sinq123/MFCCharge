#pragma once
#include "NetServerWorker.h"
#include "NetServerTask.h"
#include "NetServerJobQueue.h"

typedef void (CALLBACK * ON_READ_CALLBACK)(const wchar_t* pwchIP, const BYTE* pBytes, const size_t size);

class CNetServerWork
	: public CNetServerWorker
{
public:
	CNetServerWork(CNetServerJobQueue& _jobqueue, std::size_t _maxthreads = 1);
	virtual ~CNetServerWork(void);

public:
	bool Work(CNetServerTask& task);
	void SetOnReadCallBack(void (CALLBACK * pfOnReadCallBack)(const wchar_t* pwchIP, const BYTE* pBytes, const size_t size));
	void SetOnReadNULL(void);

private:
	// 回调函数使用指针对象
	ON_READ_CALLBACK m_pfOnReadCallBack;
	//临界保护量
	CRITICAL_SECTION m_sCriticalSection;
};

