#pragma once

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "NetServerJobQueue.h"
#include "NetMsg.h"

typedef void (CALLBACK * ON_DISCONNECT_CALLBACK)(const wchar_t* pwchIP);// ʵʱ��ʾ

class CNetServerSession
	: public boost::enable_shared_from_this<CNetServerSession>
{
public:
	CNetServerSession(boost::asio::io_service& io_service, CNetServerJobQueue& jobwork);
	virtual ~CNetServerSession(void);

public:
	boost::asio::ip::tcp::socket& Socket();

	bool IsUsing();
	void IsUsing(bool b);

	int GetUsingTime();
	void SetUsingTime();

	void Start();
	void Write(char* data, int num);
	void Close(void);

	void HandleReadHead(const boost::system::error_code& error, size_t bytes_transferred);
	void HandleReadBody(const boost::system::error_code& error, size_t bytes_transferred);
	void HandleWrite(const boost::system::error_code& error);

	void SetOnDisconnectCallBack(void (CALLBACK * pfOnconnectCallBack)(const wchar_t* pwchIP));

private:
	bool ParseNetPack(const BYTE *pBuf4DataSec, const size_t size);
	void CachePack(const std::string &strQN
		, const int nPCNT
		, const int nPNO
		, const BYTE *pBuf
		, const size_t size);

private:
	static wchar_t * ANSIToUnicode(const char *str);

private:
	boost::asio::ip::tcp::socket m_tcpSocket;
	CNetServerJobQueue& m_jobWork;
	boost::mutex m_sessionMutex;
	CNetMsg m_netMsg;
	bool m_bUsing; // �ñ�������Ҫ����.
	int m_nUsingTime; // �ñ�������Ҫ����.
	boost::asio::io_service::strand m_Strand;

private:
	// �ص�����ʹ��ָ�����
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

