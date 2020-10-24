#include "StdAfx.h"
#include "NetServerSession.h"
#include "NetServerTask.h"
#include <iostream>


CNetServerSession::CNetServerSession(boost::asio::io_service& io_service, CNetServerJobQueue& jobwork)
	: m_tcpSocket(io_service)
	, m_Strand(io_service)
	, m_jobWork(jobwork)
	, m_bUsing(false)
	, m_nUsingTime(0)
	, m_pfOnDisconnectCallBack(NULL)
{
}

CNetServerSession::~CNetServerSession(void)
{
}

boost::asio::ip::tcp::socket& CNetServerSession::Socket()
{
	return m_tcpSocket;
}

bool CNetServerSession::IsUsing() 
{
	// boost::mutex::scoped_lock lock(using_mutex_);
	return m_bUsing;
};

void CNetServerSession::IsUsing(bool b)
{
	// boost::mutex::scoped_lock lock(using_mutex_);
	m_bUsing = b;
}

int CNetServerSession::GetUsingTime() 
{
	// boost::mutex::scoped_lock lock(using_mutex_);
	return m_nUsingTime;
};

void CNetServerSession::SetUsingTime()
{
	// boost::mutex::scoped_lock lock(using_mutex_);
	m_nUsingTime++;
}

void CNetServerSession::Start()
{
	IsUsing(true);

	// �������һ������ͷ�ŷ���.
	boost::asio::async_read(m_tcpSocket, boost::asio::buffer(m_netMsg.Data(), g_unNetPackHeaderSize+g_unNetPackDSSPSize),
		m_Strand.wrap(
		boost::bind(&CNetServerSession::HandleReadHead, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred)
		)
		);
}

void CNetServerSession::Write(char* data, int num)
{
	boost::asio::async_write(m_tcpSocket,
		boost::asio::buffer(data, num),
		boost::bind(&CNetServerSession::HandleWrite,shared_from_this(),
		boost::asio::placeholders::error));
}

void CNetServerSession::Close(void)
{
	// TODO: ���ϵͳ��־
	if (m_tcpSocket.is_open())
	{
		std::string strRemotePoint;
		try
		{
			strRemotePoint = m_tcpSocket.remote_endpoint().address().to_string();
			boost::system::error_code ignored_ec;
			m_tcpSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
			m_tcpSocket.close(ignored_ec);
		}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
		}
		IsUsing(false);
		wchar_t* pwchIP = ANSIToUnicode(strRemotePoint.c_str());

		if (NULL != m_pfOnDisconnectCallBack)
		{
			m_pfOnDisconnectCallBack(pwchIP);
		}

		free(pwchIP);
		pwchIP = NULL;
	}
}

void CNetServerSession::HandleReadBody(const boost::system::error_code& error,
	size_t bytes_transferred)
{
	if (!error)
	{
		// �������Ϣ
		ParseNetPack((BYTE*)m_netMsg.Body(), m_netMsg.BodyLength());

		// ������ȡ��һ�����ݰ�ͷ.
		boost::asio::async_read(m_tcpSocket, boost::asio::buffer(m_netMsg.Data(), g_unNetPackHeaderSize+g_unNetPackDSSPSize),
			m_Strand.wrap(
			boost::bind(&CNetServerSession::HandleReadHead, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred)
			)
			);
	}
	else
	{
		// �ر�����
		Close();
	}
}

void CNetServerSession::HandleReadHead(const boost::system::error_code& error,
	size_t bytes_transferred)
{
	if (!error && m_netMsg.DecodeHeader())
	{
		// �������ݰ�.
		boost::asio::async_read(m_tcpSocket, boost::asio::buffer(m_netMsg.Body(), m_netMsg.BodyLength()),
			m_Strand.wrap(
			boost::bind(&CNetServerSession::HandleReadBody, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred)
			)
			);
	}
	else
	{
		// �ر�����
		Close();
	}
}

void CNetServerSession::HandleWrite(const boost::system::error_code& error)
{
	if (!error)
	{
		// ������ɺ��ڴ˽���һЩ����...
	}
	else
	{
		// �ر�����
		Close();
	}
}

bool CNetServerSession::ParseNetPack(const BYTE *pBuf4DataSec, const size_t size)
{
	bool bRet(true);
	assert(size > (g_unQNSize + g_unPCNTSize + g_unPNOSize)); // TODO���к����壿
	int nPCNT = atoi(std::string((char*)pBuf4DataSec+g_unQNSize, g_unPCNTSize).c_str());
	if (1 == nPCNT)
	{
		// �ܰ���Ϊ1
		const int nHeaderSize = g_unQNSize + g_unPCNTSize + g_unPNOSize;
		const int nCmdSize = size - nHeaderSize - g_unNetPackTailSize;
		BYTE *pPostBuf = new BYTE[nCmdSize+1];
		memset(pPostBuf, 0, nCmdSize*sizeof(pPostBuf[0]));
		memcpy(pPostBuf, pBuf4DataSec+nHeaderSize, nCmdSize);

		wchar_t* pwchIP = NULL;
		pwchIP = ANSIToUnicode(m_tcpSocket.remote_endpoint().address().to_string().c_str());

		CNetServerTask task;
		task.Data(pPostBuf, nCmdSize);
		task.SetIP(pwchIP);
		// �������ύ����������.
		m_jobWork.SubmitJob(task);

		if (NULL != pwchIP)
		{
			free(pwchIP);
			pwchIP=NULL;
		}

		delete [] pPostBuf;
		pPostBuf = NULL;
	}
	else if (nPCNT > 1)
	{
		// ���
		std::string strQN((char*)pBuf4DataSec+8, g_unQNSize-8); // 8=>_countof("yyyymmdd")
		int nPNO = atoi(std::string((char*)pBuf4DataSec + g_unQNSize + g_unPCNTSize, g_unPNOSize).c_str());
		CachePack(strQN, nPCNT, nPNO, (BYTE*)pBuf4DataSec, size);
	}
	else
	{
		// ��������
		bRet = false;
	}
	return bRet;
}

void CNetServerSession::CachePack(const std::string &strQN
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
		// ��������
		SRequest::PACKSLIST::reverse_iterator riterToInsert = std::find_if(pReq->PacksList.rbegin(), pReq->PacksList.rend(), pno_less(pPack->nPNO));
		pReq->PacksList.insert(riterToInsert.base(), pPack);

		if (pReq->PacksList.size() == nPCNT)
		{
			// ���յ�һ�������ȫ�����ݰ�
			// ���������WM_NET_RECV_DATA֪ͨ
			int nReqSize(0);
			std::for_each(pReq->PacksList.begin(), pReq->PacksList.end(), count_size_to(nReqSize));
			const int nPostBufSize = nReqSize - (nPCNT * (g_unQNSize+g_unPCNTSize+g_unPNOSize+g_unNetPackTailSize));
			BYTE *pPostBuf = new BYTE[nPostBufSize];
			memset(pPostBuf, 0, nPostBufSize);
			std::for_each(pReq->PacksList.begin(), pReq->PacksList.end(), buf_copy_to(pPostBuf));

			wchar_t* pwchIP = NULL;
			pwchIP = ANSIToUnicode(m_tcpSocket.remote_endpoint().address().to_string().c_str());

			CNetServerTask task;
			task.Data(pPostBuf, nPostBufSize);
			task.SetIP(pwchIP);
			// �������ύ����������.
			m_jobWork.SubmitJob(task);

			if (NULL != pwchIP)
			{
				free(pwchIP);
				pwchIP=NULL;
			}

			delete [] pPostBuf;
			pPostBuf = NULL;

			// �ͷ��ڴ�
			delete pReq;
			pReq = NULL;
			m_RequestMap.erase(iterReq);
		}
	}
}

wchar_t * CNetServerSession::ANSIToUnicode(const char *str)
{
	// ֧��(str==NULL)�����

	int textlen(0);
	wchar_t *result(NULL);
	textlen = MultiByteToWideChar(CP_ACP, 0, str,-1, NULL, 0); 
	result = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t)); 
	memset(result, 0, (textlen+1)*sizeof(wchar_t)); 
	MultiByteToWideChar(CP_ACP, 0, str, -1, (LPWSTR)result,textlen); 
	return result;
}

void CNetServerSession::SetOnDisconnectCallBack(void (CALLBACK * pfOnDisconnectCallBack)(const wchar_t* pwchIP))
{
	m_pfOnDisconnectCallBack = pfOnDisconnectCallBack;
}