#pragma once

#include "NetServerJobQueue.h"
#include "NetServerSession.h"
#include "NetServerIoServicePool.h"
#include "NetMsg.h"

typedef void (CALLBACK * ON_CONNECT_CALLBACK)(const wchar_t* pwchIP);

class CNetServer
{
public:
	CNetServer(short port, CNetServerJobQueue& jobwork, std::size_t io_service_pool_size = 4);
	virtual ~CNetServer(void);

	typedef boost::shared_ptr<CNetServerSession> session_ptr;

public:
	void Run();
	void Stop();
	void Send(CNetMsg& msg);
	void Close(const char* pchIP);
	bool IsConnect(const char* pchIP);
	void SetOnConnectCallBack(void (CALLBACK * pfOnConnectCallBack)(const wchar_t* pwchIP));
	void SetOnDisconnectCallBack(void (CALLBACK * pfOnconnectCallBack)(const wchar_t* pwchIP));

private:
	void HandleAccept(session_ptr new_session, const boost::system::error_code& error);
	wchar_t * ANSIToUnicode(const char *str);

private:
	CNetServerJobQueue& m_jobWork;
	CNetServerIoServicePool m_IoServicePool;
	boost::asio::ip::tcp::acceptor m_Acceptor;
	std::vector<session_ptr> m_SessionPool;

	// 回调函数使用指针对象
	ON_CONNECT_CALLBACK m_pfOnConnectCallBack;
	ON_DISCONNECT_CALLBACK m_pfOnDisconnectCallBack;
};

