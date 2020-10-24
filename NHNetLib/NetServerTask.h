#pragma once


class CNetServerTask
{
public:
	CNetServerTask(void);
	CNetServerTask(const CNetServerTask& task);
	CNetServerTask& operator =(CNetServerTask &task);
	virtual ~CNetServerTask(void);

public:
	const BYTE* Data(void) const;
	void Data(const BYTE* pBytes, const size_t size);

	size_t Length(void) const;
	//void Length(size_t szLength);

	const wchar_t* GetIP(void) const;
	bool SetIP(const wchar_t* pwchIP);

private:
	BYTE* m_pBytes;
	size_t m_szLength;
	// ip缓冲区大小
	const static size_t m_szIP = 16;
	// ip缓冲区
	wchar_t* m_pwchIP;
};

