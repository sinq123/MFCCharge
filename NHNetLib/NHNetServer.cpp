#include "StdAfx.h"
#include "NHNetServer.h"
#include "NetServer.h"
#include "NetServerWork.h"
#include <ctime>
#include <sys\timeb.h>

class CNHNetServerIMPL
{
public:
	CNHNetServerIMPL(void)
		: m_pListenThread(NULL)
		, m_pWorkThread(NULL)
		, m_pJobQueue(NULL)
		, m_pWork(NULL)
		, m_pServer(NULL)
		, m_bRunning(false)
	{
	}

	virtual ~CNHNetServerIMPL(void)
	{
		Stop();
	}

public:
	bool Run(const unsigned int nPort)
	{
		// 判断端口是否在[1, 65535]之间
		if ( nPort>0 && nPort<=65535)
		{
			Stop();

			m_pJobQueue = new CNetServerJobQueue();
			m_pWork = new CNetServerWork((*m_pJobQueue));
			m_pServer = new CNetServer(nPort, (*m_pJobQueue));
			m_pListenThread = new boost::thread(boost::bind(&CNHNetServerIMPL::RunListen, this));
			m_pWorkThread = new boost::thread(boost::bind(&CNHNetServerIMPL::RunWork, this));

			m_bRunning = true;

			return true;
		}
		else
		{
			return false;
		}
	}

	bool IsRun(void)
	{
		return m_bRunning;
	}

	void Stop(void)
	{
		m_bRunning = false;

		if (NULL != m_pWork)
		{
			m_pWork->SetOnReadNULL();
			m_pWork->Stop();
		}
		if (NULL != m_pServer)
		{
			m_pServer->Stop();
		}
		if (NULL != m_pJobQueue)
		{
			m_pJobQueue->Notify_All();
		}
		if (NULL != m_pListenThread)
		{
			m_pListenThread->join();
		}
		if (NULL != m_pWorkThread)
		{
			m_pWorkThread->join();
		}

		if (NULL != m_pWork)
		{
			delete m_pWork;
			m_pWork = NULL;
		}
		if (NULL != m_pServer)
		{
			delete m_pServer;
			m_pServer = NULL;
		}
		if (NULL != m_pJobQueue)
		{
			delete m_pJobQueue;
			m_pJobQueue = NULL;
		}
		if (NULL != m_pListenThread)
		{
			delete m_pListenThread;
			m_pListenThread = NULL;
		}
		if (NULL != m_pWorkThread)
		{
			delete m_pWorkThread;
			m_pWorkThread = NULL;
		}
	}

	void Send(const wchar_t* pwchIP, const BYTE* pBytes, const size_t size)
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
					char* pchIP = NULL;
					pchIP = UnicodeToANSI(pwchIP);
					msg.SetIP(pchIP);
					if (NULL != pchIP)
					{
						free(pchIP);
						pchIP = NULL;
					}
					// 发送
					if (NULL != m_pServer)
					{
						m_pServer->Send(msg);
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
					char* pchIP = NULL;
					pchIP = UnicodeToANSI(pwchIP);
					msg.SetIP(pchIP);
					if (NULL != pchIP)
					{
						free(pchIP);
						pchIP = NULL;
					}
					// 发送
					if (NULL != m_pServer)
					{
						m_pServer->Send(msg);
					}
					// 清理数据
					delete[] pByteBuf;
					pByteBuf = NULL;
				}
			}
		}
	}

	void Close(const wchar_t* pwchIP)
	{
		char* pchIP = NULL;
		pchIP = UnicodeToANSI(pwchIP);

		if (NULL != m_pServer)
		{
			m_pServer->Close(pchIP);
		}

		if (NULL != pchIP)
		{
			free(pchIP);
			pchIP = NULL;
		}
	}

	bool IsConnect(const wchar_t* pwchIP)
	{
		bool bConnect(false);
		char* pchIP = NULL;
		pchIP = UnicodeToANSI(pwchIP);

		if (NULL != m_pServer)
		{
			bConnect = m_pServer->IsConnect(pchIP);
		}

		if (NULL != pchIP)
		{
			free(pchIP);
			pchIP = NULL;
		}

		return bConnect;
	}

	void SetOnReadCallBack(void (CALLBACK* pfOnReadCallBack)(const wchar_t* pwchIP, const BYTE* pBytes, const size_t size))
	{
		if (NULL != m_pWork)
		{
			m_pWork->SetOnReadCallBack(pfOnReadCallBack);
		}
	}

	void SetOnConnectCallBack(void (CALLBACK* pfOnConnectCallBack)(const wchar_t* pwchIP))
	{
		if (NULL != m_pServer)
		{
			m_pServer->SetOnConnectCallBack(pfOnConnectCallBack);
		}
	}

	void SetOnDisconnectCallBack(void (CALLBACK* pfOnDisconnectCallBack)(const wchar_t* pwchIP))
	{
		if (NULL != m_pServer)
		{
			m_pServer->SetOnDisconnectCallBack(pfOnDisconnectCallBack);
		}
	}

private:
	void RunListen()
	{
		if (m_pServer)
		{
			m_pServer->Run();
		}
	}

	void RunWork()
	{
		if (m_pWork)
		{
			m_pWork->Run();
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

	char * UnicodeToANSI(const wchar_t *str)
	{
		// 支持(str==NULL)的情况

		char* result(NULL);
		int textlen(0);
		textlen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
		result =(char *)malloc((textlen+1)*sizeof(char));
		memset(result, 0, sizeof(char)*(textlen+1));
		WideCharToMultiByte(CP_ACP, 0, str, -1, result, textlen, NULL, NULL);
		return result;
	}

private:
	boost::thread* m_pListenThread;
	boost::thread* m_pWorkThread;
	CNetServerJobQueue* m_pJobQueue;
	CNetServerWork* m_pWork;
	CNetServer* m_pServer;
	bool m_bRunning;
};


CNHNetServer::CNHNetServer(void)
	: m_pNHNetServerIMPLL(NULL)
{
	m_pNHNetServerIMPLL = new CNHNetServerIMPL();
}


CNHNetServer::~CNHNetServer(void)
{
	delete m_pNHNetServerIMPLL;
	m_pNHNetServerIMPLL = NULL;
}

bool CNHNetServer::Run(const unsigned int nPort)
{
	return m_pNHNetServerIMPLL->Run(nPort);
}

bool CNHNetServer::IsRun(void)
{
	return m_pNHNetServerIMPLL->IsRun();
}

void CNHNetServer::Stop(void)
{
	m_pNHNetServerIMPLL->Stop();
}

void CNHNetServer::Send(const wchar_t* pwchIP, const BYTE* pBytes, const size_t size)
{
	m_pNHNetServerIMPLL->Send(pwchIP, pBytes, size);
}

void CNHNetServer::Disconnect(const wchar_t* pwchIP)
{
	m_pNHNetServerIMPLL->Close(pwchIP);
}

bool CNHNetServer::IsConnect(const wchar_t* pwchIP)
{
	return m_pNHNetServerIMPLL->IsConnect(pwchIP);
}

void CNHNetServer::SetOnReadCallBack(void (CALLBACK* pfOnReadCallBack)(const wchar_t* pwchIP, const BYTE* pBytes, const size_t size))
{
	m_pNHNetServerIMPLL->SetOnReadCallBack(pfOnReadCallBack);
}

void CNHNetServer::SetOnConnectCallBack(void (CALLBACK* pfOnConnectCallBack)(const wchar_t* pwchIP))
{
	m_pNHNetServerIMPLL->SetOnConnectCallBack(pfOnConnectCallBack);
}

void CNHNetServer::SetOnDisconnectCallBack(void (CALLBACK* pfOnDisConnectCallBack)(const wchar_t* pwchIP))
{
	m_pNHNetServerIMPLL->SetOnDisconnectCallBack(pfOnDisConnectCallBack);
}