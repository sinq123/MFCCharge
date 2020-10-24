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
	// �ص�����ʹ��ָ�����
	ON_READ_CALLBACK m_pfOnReadCallBack;
	//�ٽ籣����
	CRITICAL_SECTION m_sCriticalSection;
};

