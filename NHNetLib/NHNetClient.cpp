#include "StdAfx.h"
#include "NHNetClient.h"
#include "NetClient.h"
#include <boost/regex.hpp>
#include <ctime>
#include <sys\timeb.h>

class  CNHNetClientIMPL
{
public:
	CNHNetClientIMPL(void)
		: m_pIoSev(NULL)
		, m_pResolver(NULL)
		, m_pQuery(NULL)
		, m_pIterator(NULL)
		, m_pNetClient(NULL)
		, m_pThread(NULL)
	{
	}

	virtual ~CNHNetClientIMPL(void)
	{
		Disconnect();
	}

public:
	bool Connect(const wchar_t * pwchIPAddress, const int nPort)
	{
		// 连接前首先断开上一次的连接
		Disconnect();

		// 连接服务器
		bool bConnect(false);

		int nStrLen = wcslen(pwchIPAddress);
		// 验证IP地址长度/端口
		if (nStrLen<=15 && nPort>0 && nPort<=65535) 
		{
			int nLen = WideCharToMultiByte(CP_ACP, 0, pwchIPAddress, nStrLen, NULL, 0, NULL, NULL);
			char *pchIPAddress = new char[nLen+1]();
			WideCharToMultiByte(CP_ACP, 0, pwchIPAddress, nStrLen, pchIPAddress, nLen, NULL, NULL);

			// 验证IP地址合法
			if (IsValidIP(pchIPAddress)) 
			{
				char chPort[MAX_PATH] = "";
				_snprintf_s(chPort, MAX_PATH, _TRUNCATE, "%d", nPort);

				try
				{
					m_pIoSev = new boost::asio::io_service();
					m_pResolver = new boost::asio::ip::tcp::resolver((*m_pIoSev));
					m_pQuery = new boost::asio::ip::tcp::resolver::query(pchIPAddress, chPort);
					m_pIterator = new boost::asio::ip::tcp::resolver::iterator(m_pResolver->resolve((*m_pQuery)));
					m_pNetClient = new CNetClient((*m_pIoSev), (*m_pIterator));
					m_pThread = new boost::thread(boost::bind(&boost::asio::io_service::run, m_pIoSev));

					bConnect = true;
				}
				catch (std::exception& e)
				{
					std::cerr << "Exception: " << e.what() << "\n";
				}
			}

			delete[] pchIPAddress;
			pchIPAddress = NULL;
		}

		return bConnect;
	}

	void SetOnReadCallBack(void (CALLBACK* pfOnReadCallBack)(const BYTE* pBytes, const size_t size))
	{
		if (NULL != m_pNetClient)
		{
			m_pNetClient->SetOnReadCallback(pfOnReadCallBack);
		}
	}

	void SetOnConnectCallBack(void (CALLBACK* pfOnConnectCallBack)(const bool bSuccess))
	{
		if (NULL != m_pNetClient)
		{
			m_pNetClient->SetOnConnectCallBack(pfOnConnectCallBack);
		}
	}

	void SetOnDisconnectCallBack(void (CALLBACK* pfOnDisconnectCallBack)(void))
	{
		if (NULL != m_pNetClient)
		{
			m_pNetClient->SetOnDisconnectCallBack(pfOnDisconnectCallBack);
		}
	}

	bool IsConnect(void)
	{
		bool bConnect(false);
		if (NULL != m_pNetClient)
		{
			bConnect = m_pNetClient->IsConnect();
		}

		return bConnect;
	}

	void Disconnect(void)
	{
		try
		{
			if (NULL != m_pNetClient)
			{
				m_pNetClient->Close();
			}
			if (NULL != m_pThread)
			{
				m_pThread->join();
			}
		}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
		}
		// 删除顺序不能改变
		// m_pNetClient->m_pIoSev->m_pResolver->m_pQuery->m_pIterator->m_pThread
		if (NULL != m_pNetClient)
		{
			delete m_pNetClient;
			m_pNetClient = NULL;
		}
		if (NULL != m_pIoSev)
		{
			delete m_pIoSev;
			m_pIoSev = NULL;
		}
		if (NULL != m_pResolver)
		{
			delete m_pResolver;
			m_pResolver = NULL;
		}
		if (NULL != m_pQuery)
		{
			delete m_pQuery;
			m_pQuery = NULL;
		}
		if (NULL != m_pIterator)
		{
			delete m_pIterator;
			m_pIterator = NULL;
		}
		if (NULL != m_pThread)
		{
			delete m_pThread;
			m_pThread = NULL;
		}
	}

	void Send(const BYTE *pBytes, const size_t size)
	{
		wchar_t wchMAX_PCNT[g_unPCNTSize+1] = L"";
		for(int i=0; i<g_unPCNTSize; i++)
		{
			// 数字9
			wchMAX_PCNT[i] = 57; 
		}
		const int nPCNT = (int)ceil((double)size/g_unNetPackPayloadSize);

		// 最大容量
		if ((_wtoi(wchMAX_PCNT)*g_unNetPackPayloadSize) >= size)
		{
			const UINT unQNLength = g_unQNSize+1;
			char chQN[unQNLength] = {0};
			SetQN(chQN, unQNLength);

			char chFormat[32] = {0};
			// PCNT
			char chPCNT[ g_unPCNTSize+1] = {0};
			_snprintf_s(chFormat, _countof(chFormat), _TRUNCATE, "%%0%dd", g_unPCNTSize);
			_snprintf_s(chPCNT, g_unPCNTSize+1, _TRUNCATE, chFormat, nPCNT);

			for (int i=1; i<=nPCNT; i++)
			{
				CNetMsg msg;

				if (i < nPCNT)
				{
					// 数据段长度
					const size_t size_send = g_unNetPackPayloadSize;
					BYTE * pByteBuf = new BYTE[g_unQNSize+g_unPCNTSize+g_unPNOSize+size_send+g_unNetPackTailSize]();
					// QN
					memcpy_s(pByteBuf, g_unQNSize, chQN, g_unQNSize);
					// PCNT
					memcpy_s(pByteBuf+g_unQNSize, g_unPCNTSize, chPCNT, g_unPCNTSize);
					// PNO
					int nPNO = i;
					char chPNO[g_unPNOSize+1] = {0};
					_snprintf_s(chFormat, _countof(chFormat), _TRUNCATE, "%%0%dd", g_unPNOSize);
					_snprintf_s(chPNO, g_unPNOSize+1, _TRUNCATE, chFormat, nPNO);			
					memcpy_s(pByteBuf+g_unQNSize+g_unPCNTSize, g_unPNOSize, chPNO, g_unPNOSize);
					// Data
					memcpy_s(pByteBuf+g_unQNSize+g_unPCNTSize+g_unPNOSize, size_send, pBytes+(i-1)*g_unNetPackPayloadSize, size_send);
					// 包尾
					memcpy_s(pByteBuf+g_unQNSize+g_unPCNTSize+g_unPNOSize+size_send, g_unNetPackTailSize, g_pchNetPackTailSign, g_unNetPackTailSize);
					// 数据包
					CNetMsg msg;
					msg.BodyLength(g_unQNSize+g_unPCNTSize+g_unPNOSize+size_send+g_unNetPackTailSize);
					memcpy(msg.Body(), pByteBuf, msg.BodyLength());
					msg.EncodeHeader();
					// 发送
					if (NULL != m_pNetClient)
					{
						m_pNetClient->Write(msg);
					}
					// 清理数据
					delete[] pByteBuf;
					pByteBuf = NULL;
				}
				else
				{
					// 数据段长度
					const size_t size_send = size-(i-1)*g_unNetPackPayloadSize;
					BYTE * pByteBuf = new BYTE[g_unQNSize+g_unPCNTSize+g_unPNOSize+size_send+g_unNetPackTailSize]();
					// QN
					memcpy_s(pByteBuf, g_unQNSize, chQN, g_unQNSize);
					// PCNT
					memcpy_s(pByteBuf+g_unQNSize, g_unPCNTSize, chPCNT, g_unPCNTSize);
					// PNO
					int nPNO = i;
					char chPNO[g_unPNOSize+1] = {0};
					_snprintf_s(chFormat, _countof(chFormat), _TRUNCATE, "%%0%dd", g_unPNOSize);
					_snprintf_s(chPNO, g_unPNOSize+1, _TRUNCATE, chFormat, nPNO);
					memcpy_s(pByteBuf+g_unQNSize+g_unPCNTSize, g_unPNOSize, chPNO, g_unPNOSize);
					// Data
					memcpy_s(pByteBuf+g_unQNSize+g_unPCNTSize+g_unPNOSize, size_send, pBytes+(i-1)*g_unNetPackPayloadSize, size_send);
					// 包尾
					memcpy_s(pByteBuf+g_unQNSize+g_unPCNTSize+g_unPNOSize+size_send, g_unNetPackTailSize, g_pchNetPackTailSign, g_unNetPackTailSize);
					// 数据包
					CNetMsg msg;
					msg.BodyLength(g_unQNSize+g_unPCNTSize+g_unPNOSize+size_send+g_unNetPackTailSize);
					memcpy(msg.Body(), pByteBuf, msg.BodyLength());
					msg.EncodeHeader();
					// 发送
					if (NULL != m_pNetClient)
					{
						m_pNetClient->Write(msg);
					}
					// 清理数据
					delete[] pByteBuf;
					pByteBuf = NULL;
				}
			}
		}
	}

private:
	bool IsValidIP(const char * pchIPAdr)
	{
		boost::regex ex;
		ex = "^(25[0-5]|2[0-4][0-9]|[0-1]{1}[0-9]{2}|[1-9]{1}[0-9]{1}|[1-9])\\.(25[0-5]|2[0-4][0-9]|[0-1]{1}[0-9]{2}|[1-9]{1}[0-9]{1}|[1-9]|0)\\.(25[0-5]|2[0-4][0-9]|[0-1]{1}[0-9]{2}|[1-9]{1}[0-9]{1}|[1-9]|0)\\.(25[0-5]|2[0-4][0-9]|[0-1]{1}[0-9]{2}|[1-9]{1}[0-9]{1}|[0-9])$";

		if(boost::regex_match(pchIPAdr, ex))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	const char * SetQN(char *const pchQN, const UINT unLength)
	{
		assert(NULL != pchQN);
		assert(0 != unLength);

		_timeb now;
		_ftime_s(&now);
		tm t;
		localtime_s(&t, &now.time);
		_snprintf_s(pchQN, unLength, _TRUNCATE, "%04d%02d%02d%02d%02d%02d%03d"
			, t.tm_year+1900, t.tm_mon+1, t.tm_mday
			, t.tm_hour, t.tm_min, t.tm_sec, now.millitm);
		return pchQN;
	}

private:
	boost::asio::io_service* m_pIoSev;
	boost::asio::ip::tcp::resolver* m_pResolver;
	boost::asio::ip::tcp::resolver::query* m_pQuery;
	boost::asio::ip::tcp::resolver::iterator* m_pIterator;
	CNetClient* m_pNetClient;
	boost::thread* m_pThread;
};


CNHNetClient::CNHNetClient(void)
	: m_pNHNetClientIMPL(NULL)
{
	m_pNHNetClientIMPL = new CNHNetClientIMPL();
}

CNHNetClient::~CNHNetClient(void)
{
	if (NULL != m_pNHNetClientIMPL)
	{
		delete m_pNHNetClientIMPL;
		m_pNHNetClientIMPL = NULL;
	}
}

bool CNHNetClient::Connect(const wchar_t * pwchIPAddress, const int nPort)
{
	return m_pNHNetClientIMPL->Connect(pwchIPAddress, nPort);
}

void CNHNetClient::SetOnReadCallBack(void (CALLBACK* pfOnReadCallBack)(const BYTE* pBytes, const size_t size))
{
	m_pNHNetClientIMPL->SetOnReadCallBack(pfOnReadCallBack);
}

void CNHNetClient::Disconnect(void)
{
	m_pNHNetClientIMPL->Disconnect();
}

bool CNHNetClient::IsConnect(void)
{
	return m_pNHNetClientIMPL->IsConnect();
}

void CNHNetClient::Send(const BYTE *pBytes, const size_t size)
{
	m_pNHNetClientIMPL->Send(pBytes, size);
}

void CNHNetClient::SetOnConnectCallBack(void (CALLBACK* pfOnConnectCallBack)(const bool bSuccess))
{
	m_pNHNetClientIMPL->SetOnConnectCallBack(pfOnConnectCallBack);
}

void CNHNetClient::SetOnDisconnectCallBack(void (CALLBACK* pfOnDisConnectCallBack)(void))
{
	m_pNHNetClientIMPL->SetOnDisconnectCallBack(pfOnDisConnectCallBack);
}