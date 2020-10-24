#include "StdAfx.h"
#include "NetServerIoServicePool.h"

#include <boost/thread.hpp>

CNetServerIoServicePool::CNetServerIoServicePool(std::size_t pool_size)
	: m_szNextIoService(0)
{
	if (pool_size == 0)
	{
		throw std::runtime_error("CNetServerIoServicePool size is 0");
	}

	for (std::size_t i = 0; i < pool_size; ++i)
	{
		PTR_IO_SERVICE io_service(new boost::asio::io_service);
		PTR_WORK work(new boost::asio::io_service::work(*io_service));
		m_ptrIoServices.push_back(io_service);
		m_ptrWork.push_back(work);
	}
}


CNetServerIoServicePool::~CNetServerIoServicePool(void)
{
}

void CNetServerIoServicePool::Run()
{
	std::vector<boost::shared_ptr<boost::thread> > threads;
	for (std::size_t i = 0; i < m_ptrIoServices.size(); ++i)
	{
		boost::shared_ptr<boost::thread> thread(new boost::thread(
			boost::bind(&boost::asio::io_service::run, m_ptrIoServices[i])));
		threads.push_back(thread);
	}

	for (std::size_t i = 0; i < threads.size(); ++i)
	{
		threads[i]->join();
	}
}

void CNetServerIoServicePool::Stop()
{
	for (std::size_t i = 0; i < m_ptrIoServices.size(); ++i)
	{
		m_ptrIoServices[i]->stop();
	}
}

boost::asio::io_service& CNetServerIoServicePool::GetIoService()
{
	boost::asio::io_service& io_service = *m_ptrIoServices[m_szNextIoService];
	++m_szNextIoService;
	if (m_szNextIoService == m_ptrIoServices.size())
	{
		m_szNextIoService = 0;
	}
	return io_service;
}