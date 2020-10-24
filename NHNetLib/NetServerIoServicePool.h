#pragma once

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

class CNetServerIoServicePool
	: private boost::noncopyable
{
public:
	CNetServerIoServicePool(std::size_t pool_size);
	virtual ~CNetServerIoServicePool(void);

public:
	void Run();
	void Stop();

	boost::asio::io_service& GetIoService();

private:
	typedef boost::shared_ptr<boost::asio::io_service> PTR_IO_SERVICE;
	typedef boost::shared_ptr<boost::asio::io_service::work> PTR_WORK;

	std::vector<PTR_IO_SERVICE> m_ptrIoServices;
	std::vector<PTR_WORK> m_ptrWork;
	std::size_t m_szNextIoService;
};

