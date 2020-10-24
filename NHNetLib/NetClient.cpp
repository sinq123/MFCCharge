#include "StdAfx.h"
#include "NetClient.h"

CNetClient::CNetClient(boost::asio::io_service& io_service, boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
	: m_IoService(io_service)
	, m_tcpSocket(io_service)
	, m_pfOnReadCallBack(NULL)
	, m_pfOnConnectCallBack(NULL)
	, m_pfOnDisconnectCallBack(NULL)
{
	boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
	m_tcpSocket.async_connect(endpoint,
		boost::bind(&CNetClient::HandleConnect, this,
		boost::asio::placeholders::error, ++endpoint_iterator));
}

CNetClient::~CNetClient(void)
{
}


void CNetClient::Write(const CNetMsg& msg)
{
	m_IoService.post(boost::bind(&CNetClient::DoWrite, this, msg));
}

void CNetClient::Close()
{
	m_IoService.post(boost::bind(&CNetClient::DoClose, this));
}

void CNetClient::HandleConnect(const boost::system::error_code& error, boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
	bool bSuccess(false);
	if (!error)
	{
		bSuccess = true;
		boost::asio::async_read(m_tcpSocket,
			boost::asio::buffer(m_lsReadMsg.Data(), g_unNetPackHeaderSize+g_unNetPackDSSPSize),
			boost::bind(&CNetClient::HandleReadHeader, this,
			boost::asio::placeholders::error));
	}
	else if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator())
	{
		m_tcpSocket.close();
		boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
		m_tcpSocket.async_connect(endpoint,
			boost::bind(&CNetClient::HandleConnect, this,
			boost::asio::placeholders::error, ++endpoint_iterator));
	}
	// 回调是否连接成功
	if (NULL != m_pfOnConnectCallBack)
	{
		m_pfOnConnectCallBack(bSuccess);
	}
}

void CNetClient::HandleReadHeader(const boost::system::error_code& error)
{
	if (!error && m_lsReadMsg.DecodeHeader())
	{
		boost::asio::async_read(m_tcpSocket,
			boost::asio::buffer(m_lsReadMsg.Body(), m_lsReadMsg.BodyLength()),
			boost::bind(&CNetClient::HandleReadBody, this,
			boost::asio::placeholders::error));
	}
	else
	{
		DoClose();
	}
}

void CNetClient::HandleReadBody(const boost::system::error_code& error)
{
	if (!error)
	{
		CNetMsg msg = m_lsReadMsg;
		m_IoService.post(boost::bind(&CNetClient::DoRead, this, msg));
		boost::asio::async_read(m_tcpSocket,
			boost::asio::buffer(m_lsReadMsg.Data(), g_unNetPackHeaderSize+g_unNetPackDSSPSize),
			boost::bind(&CNetClient::HandleReadHeader, this,
			boost::asio::placeholders::error));
	}
	else
	{
		DoClose();
	}
}

void CNetClient::DoRead(CNetMsg msg)
{
	ParseNetPack((BYTE*)msg.Body(), msg.BodyLength());
}

void CNetClient::DoWrite(CNetMsg msg)
{
	bool write_in_progress = !m_lsWriteMsg.empty();
	m_lsWriteMsg.push_back(msg);
	if (!write_in_progress)
	{
		boost::asio::async_write(m_tcpSocket,
			boost::asio::buffer(m_lsWriteMsg.front().Data(),
			m_lsWriteMsg.front().Length()),
			boost::bind(&CNetClient::HandleWrite, this,
			boost::asio::placeholders::error));
	}
}

void CNetClient::HandleWrite(const boost::system::error_code& error)
{
	if (!error)
	{
		m_lsWriteMsg.pop_front();
		if (!m_lsWriteMsg.empty())
		{
			boost::asio::async_write(m_tcpSocket,
				boost::asio::buffer(m_lsWriteMsg.front().Data(),
				m_lsWriteMsg.front().Length()),
				boost::bind(&CNetClient::HandleWrite, this,
				boost::asio::placeholders::error));
		}
	}
	else
	{
		DoClose();
	}
}

void CNetClient::DoClose()
{
	if (m_tcpSocket.is_open())
	{
		m_tcpSocket.close();

		if (NULL != m_pfOnDisconnectCallBack)
		{
			m_pfOnDisconnectCallBack();
		}
	}
}

bool CNetClient::IsConnect(void)
{
	return m_tcpSocket.is_open();
}

void CNetClient::SetOnReadCallback(void (CALLBACK* pfOnReadCallBack)(const BYTE* pBuf4DataSec, const size_t size))
{
	m_pfOnReadCallBack = pfOnReadCallBack;
}

void CNetClient::SetOnConnectCallBack(void (CALLBACK* pfOnConnectCallBack)(const bool bSuccess))
{
	m_pfOnConnectCallBack = pfOnConnectCallBack;
}

void CNetClient::SetOnDisconnectCallBack(void (CALLBACK* pfOnDisconnectCallBack)(void))
{
	m_pfOnDisconnectCallBack = pfOnDisconnectCallBack;
}

bool CNetClient::ParseNetPack(const BYTE *pBuf4DataSec, const size_t size)
{
	bool bRet(true);
	assert(size > (g_unQNSize + g_unPCNTSize + g_unPNOSize)); // TODO：有何意义？
	int nPCNT = atoi(std::string((char*)pBuf4DataSec+g_unQNSize, g_unPCNTSize).c_str());
	if (1 == nPCNT)
	{
		// 总包数为1
		const int nHeaderSize = g_unQNSize + g_unPCNTSize + g_unPNOSize;
		const int nCmdSize = size - nHeaderSize - g_unNetPackTailSize;
		BYTE *pPostBuf = new BYTE[nCmdSize+1];
		memset(pPostBuf, 0, nCmdSize*sizeof(pPostBuf[0]));
		memcpy(pPostBuf, pBuf4DataSec+nHeaderSize, nCmdSize);

		if (NULL != m_pfOnReadCallBack)
		{
			m_pfOnReadCallBack(pPostBuf, nCmdSize);
		}

		delete [] pPostBuf;
		pPostBuf = NULL;
	}
	else if (nPCNT > 1)
	{
		// 组包
		std::string strQN((char*)pBuf4DataSec+8, g_unQNSize-8); // 8=>_countof("yyyymmdd")
		int nPNO = atoi(std::string((char*)pBuf4DataSec + g_unQNSize + g_unPCNTSize, g_unPNOSize).c_str());
		CachePack(strQN, nPCNT, nPNO, (BYTE*)pBuf4DataSec, size);
	}
	else
	{
		// 错误数据
		bRet = false;
	}
	return bRet;
}

void  CNetClient::CachePack(const std::string &strQN
	, const int nPCNT
	, const int nPNO
	, const BYTE *pBuf
	, const size_t size)
{
	assert (nPCNT > 1 && nPNO > 0);
	assert (pBuf != NULL && size >0);

	SRequest::SPacksListNode *pPack = new SRequest::SPacksListNode;
	pPack->nPNO = nPNO;

	BYTE *pBufPack = new BYTE[size+1]();
	memcpy_s(pBufPack, size+1, pBuf, size);
	pPack->pBuf = pBufPack;
	pPack->iBufSize = size;
	REQUESTMAP::iterator iterReq = m_RequestMap.find(strQN);
	if (iterReq == m_RequestMap.end())
	{
		SRequest *pReq = new SRequest;
		pReq->nPCNT = nPCNT;
		pReq->PacksList.push_back(pPack);
		m_RequestMap.insert(std::pair<std::string, SRequest *> (strQN, pReq));
	}
	else
	{
		SRequest *pReq = iterReq->second;
		assert(pReq != NULL);
		// 插入排序
		SRequest::PACKSLIST::reverse_iterator riterToInsert = std::find_if(pReq->PacksList.rbegin(), pReq->PacksList.rend(), pno_less(pPack->nPNO));
		pReq->PacksList.insert(riterToInsert.base(), pPack);

		if (pReq->PacksList.size() == nPCNT)
		{
			// 接收到一个请求的全部数据包
			// 组包并发送WM_NET_RECV_DATA通知
			int nReqSize(0);
			std::for_each(pReq->PacksList.begin(), pReq->PacksList.end(), count_size_to(nReqSize));
			const int nPostBufSize = nReqSize - (nPCNT * (g_unQNSize+g_unPCNTSize+g_unPNOSize+g_unNetPackTailSize));
			BYTE *pPostBuf = new BYTE[nPostBufSize];
			memset(pPostBuf, 0, nPostBufSize);
			std::for_each(pReq->PacksList.begin(), pReq->PacksList.end(), buf_copy_to(pPostBuf));

			if (NULL != m_pfOnReadCallBack)
			{
				m_pfOnReadCallBack(pPostBuf, nPostBufSize);
			}

			delete [] pPostBuf;
			pPostBuf = NULL;

			// 释放内存
			delete pReq;
			pReq = NULL;
			m_RequestMap.erase(iterReq);
		}
	}
}