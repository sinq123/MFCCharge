#include "StdAfx.h"
#include "NetServer.h"
#include <iostream>

CNetServer::CNetServer(short port, CNetServerJobQueue& jobwork, std::size_t io_service_pool_size/* = 4*/)
	: m_IoServicePool(io_service_pool_size)
	, m_jobWork(jobwork)
	, m_Acceptor(m_IoServicePool.GetIoService(), boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
	, m_pfOnConnectCallBack(NULL)
	, m_pfOnDisconnectCallBack(NULL)
{
	session_ptr new_session(new CNetServerSession(m_IoServicePool.GetIoService(), m_jobWork));
	m_SessionPool.push_back(new_session);

	m_Acceptor.async_accept(new_session->Socket(),
		boost::bind(&CNetServer::HandleAccept, this, new_session,
		boost::asio::placeholders::error));
}


CNetServer::~CNetServer(void)
{
}

void CNetServer::Run()
{
	m_IoServicePool.Run();
}

void CNetServer::Stop()
{
	m_IoServicePool.Stop();
}

void CNetServer::Send(CNetMsg& msg)
{
	try
	{
		std::vector<session_ptr>::iterator i;
		// 尝试在session池寻找一个没有使用的session.
		for(i = m_SessionPool.begin(); i != m_SessionPool.end(); i++)
		{
			if ((*i)->IsUsing() && (msg.GetIP()==(*i)->Socket().remote_endpoint().address().to_string()))
			{
				(*i)->Write(msg.Data(), msg.Length());
			}
		}
	}
	catch (boost::system::system_error & e)
	{
		std::cerr << e.what() << std::endl;
	}
}


void CNetServer::Close(const char* pchIP)
{
	try
	{
		std::vector<session_ptr>::iterator i;
		// 尝试在session池寻找一个没有使用的session.
		for(i = m_SessionPool.begin(); i != m_SessionPool.end(); i++)
		{
			if ((*i)->IsUsing() && (pchIP==(*i)->Socket().remote_endpoint().address().to_string()))
			{
				(*i)->Close();
			}
		}
	}
	catch (boost::system::system_error & e)
	{
		std::cerr << e.what() << std::endl;
	}
}

bool CNetServer::IsConnect(const char* pchIP)
{
	bool bConnect(false);
	try
	{
		std::vector<session_ptr>::iterator i;
		// 尝试在session池寻找一个没有使用的session.
		for(i = m_SessionPool.begin(); i != m_SessionPool.end(); i++)
		{
			if ((*i)->IsUsing() && (pchIP==(*i)->Socket().remote_endpoint().address().to_string()))
			{
				bConnect = (*i)->Socket().is_open();
			}
		}
	}
	catch (boost::system::system_error & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return bConnect;
}

void CNetServer::HandleAccept(session_ptr new_session,
	const boost::system::error_code& error)
{
	if (!error)
	{
		try
		{
			new_session->Start();

			// 连接回调
			if (NULL != m_pfOnConnectCallBack)
			{
				wchar_t* pwchIP = NULL;
				pwchIP = ANSIToUnicode(new_session->Socket().remote_endpoint().address().to_string().c_str());

				m_pfOnConnectCallBack(pwchIP);

				free(pwchIP);
				pwchIP = NULL;
			}

			// 设置断开连接回调
			new_session->SetOnDisconnectCallBack(m_pfOnDisconnectCallBack);

			std::vector<session_ptr>::iterator i;
			// 尝试在session池寻找一个没有使用的session.
			for(i = m_SessionPool.begin(); i != m_SessionPool.end(); i++)
			{
				if (!(*i)->IsUsing())
				{
					new_session = *i;
					(*i)->SetUsingTime();
					break;
				}
			}
			// 没找到将插入一个新的session到池中.
			if (i == m_SessionPool.end())
			{
				new_session.reset(new CNetServerSession(m_IoServicePool.GetIoService(), m_jobWork));
				m_SessionPool.push_back(new_session);
			}

			m_Acceptor.async_accept(new_session->Socket(),
				boost::bind(&CNetServer::HandleAccept, this, new_session,
				boost::asio::placeholders::error));
		}
		catch (boost::system::system_error & e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}

void CNetServer::SetOnConnectCallBack(void (CALLBACK * pfOnConnectCallBack)(const wchar_t* pwchIP))
{
	m_pfOnConnectCallBack = pfOnConnectCallBack;
}

wchar_t * CNetServer::ANSIToUnicode(const char *str)
{
	// 支持(str==NULL)的情况

	int textlen(0);
	wchar_t *result(NULL);
	textlen = MultiByteToWideChar(CP_ACP, 0, str,-1, NULL, 0); 
	result = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t)); 
	memset(result, 0, (textlen+1)*sizeof(wchar_t)); 
	MultiByteToWideChar(CP_ACP, 0, str, -1, (LPWSTR)result,textlen); 
	return result;
}

void CNetServer::SetOnDisconnectCallBack(void (CALLBACK * pfOnDisconnectCallBack)(const wchar_t* pwchIP))
{
	m_pfOnDisconnectCallBack = pfOnDisconnectCallBack;
}