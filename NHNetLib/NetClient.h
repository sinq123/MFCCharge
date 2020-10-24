#pragma once
#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "NetMsg.h"

typedef std::deque<CNetMsg> NET_MSG_QUEUE;
typedef void (CALLBACK* ON_READ_CALLBACK)(const BYTE* pBuf4DataSec, const size_t size);
typedef void (CALLBACK* ON_CONNECT_CALLBACK)(const bool bSuccess);
typedef void (CALLBACK* ON_DISCONNECT_CALLBACK)(void);

class CNetClient
{
public:
	CNetClient(boost::asio::io_service& io_service, boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
	~CNetClient(void);

public:
	bool IsConnect(void);
	void SetOnReadCallback(void (CALLBACK* pfOnReadCallBack)(const BYTE* pBuf4DataSec, const size_t size));
	void SetOnConnectCallBack(void (CALLBACK* pfOnConnectCallBack)(const bool bSuccess));
	void SetOnDisconnectCallBack(void (CALLBACK* pfOnDisconnectCallBack)(void));
	void Write(const CNetMsg& msg);
	void Close();

private:
	void HandleConnect(const boost::system::error_code& error, boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
	void HandleReadHeader(const boost::system::error_code& error);
	void HandleReadBody(const boost::system::error_code& error);
	void HandleWrite(const boost::system::error_code& error);
	void DoRead(CNetMsg msg);
	void DoWrite(CNetMsg msg);
	void DoClose();

private:
	bool  ParseNetPack(const BYTE *pBuf4DataSec, const size_t size);
	void  CachePack(const std::string &strQN
		, const int nPCNT
		, const int nPNO
		, const BYTE *pBuf
		, const size_t size);

private:
	boost::asio::io_service& m_IoService;
	boost::asio::ip::tcp::socket m_tcpSocket;
	CNetMsg m_lsReadMsg;
	NET_MSG_QUEUE m_lsWriteMsg;

	// �ص�����ʹ��ָ�����
	ON_READ_CALLBACK m_pfOnReadCallBack; 
	ON_CONNECT_CALLBACK m_pfOnConnectCallBack; 
	ON_DISCONNECT_CALLBACK m_pfOnDisconnectCallBack; 

private:
	struct release_memory; // a functor
	struct SRequest
	{
		int nPCNT; // �ܰ���
		struct SPacksListNode
		{
			int nPNO; // ����
			const BYTE *pBuf; // ���ݶ����ݵ�ַ(������β������ "\r\n")
			size_t iBufSize; // ���ݶγ���

			~SPacksListNode(void)
			{
				if (NULL != pBuf)
				{
					delete pBuf;
					pBuf = NULL;
				}
			}
		};
		typedef std::list<SPacksListNode *> PACKSLIST;
		// ͬһ��������ȫ�����ݰ�������һ��list��;
		PACKSLIST PacksList;

		// constructor & destructor
		SRequest(void) : nPCNT(0) {}
		~SRequest(void)
		{
			std::for_each(PacksList.begin(), PacksList.end(), release_memory());
		}
	};

	// DataSecMap
	typedef std::map<std::string/*QN*/, SRequest *> REQUESTMAP;
	REQUESTMAP m_RequestMap;

	// Functors
	struct pno_less
	{
		pno_less(const int pno) : m_pno(pno) {}
		bool operator () (SRequest::SPacksListNode *pNode)
		{
			return pNode->nPNO < m_pno;
		}
	private:
		int m_pno;
	};

	struct count_size_to
	{
		count_size_to(int &size) : m_nSize(size) {}
		void operator () (SRequest::SPacksListNode * pNode)
		{
			m_nSize += pNode->iBufSize;
		}
		int get_size(void) const {return m_nSize;}
	private:
		int &m_nSize;
	};

	struct release_memory
	{
		void operator () (SRequest::SPacksListNode *pNode)
		{
			if (NULL != pNode)
			{
				delete pNode;
				pNode = NULL;
			}
		}
	};

	struct buf_copy_to
	{
		buf_copy_to(BYTE *pBuf) : m_pBuf(pBuf), m_p(m_pBuf) {}
		void operator () (SRequest::SPacksListNode *pNode)
		{
			if (pNode != NULL)
			{
				int nHeaderSize = g_unQNSize + g_unPCNTSize + g_unPNOSize;
				int nDataSize = pNode->iBufSize - nHeaderSize - g_unNetPackTailSize;
				memcpy(m_p, pNode->pBuf+nHeaderSize, nDataSize);
				m_p += nDataSize;
			}
		}
	private:
		BYTE *m_pBuf; // �������׵�ַ
		BYTE *m_p; // �α�
	};
};

