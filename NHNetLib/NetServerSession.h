#pragma once

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "NetServerJobQueue.h"
#include "NetMsg.h"

typedef void (CALLBACK * ON_DISCONNECT_CALLBACK)(const wchar_t* pwchIP);// 实时提示

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
	bool m_bUsing; // 该变量无需要加锁.
	int m_nUsingTime; // 该变量无需要加锁.
	boost::asio::io_service::strand m_Strand;

private:
	// 回调函数使用指针对象
	ON_DISCONNECT_CALLBACK m_pfOnDisconnectCallBack;

private:
	struct release_memory; // a functor
	struct SRequest
	{
		int nPCNT; // 总包数
		struct SPacksListNode
		{
			int nPNO; // 包号
			const BYTE *pBuf; // 数据段内容地址(包含包尾结束符 "\r\n")
			size_t iBufSize; // 数据段长度

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
		// 同一个请求编号全部数据包缓存在一个list中;
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
		BYTE *m_pBuf; // 缓冲区首地址
		BYTE *m_p; // 游标
	};
};

