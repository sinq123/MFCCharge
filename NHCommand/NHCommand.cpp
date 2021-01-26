// NHCommand.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "NHCommand.h"
#include <algorithm>
#include <cassert>

const char * const CNHCommand::m_pchWPNHeader = {"WPN="};
const char * const CNHCommand::m_pchCNHeader = {"CN="};
const char * const CNHCommand::m_pchCPHeader = {"CP=&&"};
const char * const CNHCommand::m_pchCPTail = {"&&;"};

CNHCommand::CNHCommand(void)
	: m_strWPN("")
	, m_strCN("")
	, m_wstrErrMsg(L"")
	, m_bError(false)
	, m_pHead(NULL)
	, m_ppLastNext(&m_pHead)
{
}

CNHCommand::~CNHCommand(void)
{
	DeleteAllCPSetElem();
}

void CNHCommand::SetError(const int err, const std::string &strParam)
{
	m_bError = true;
	switch (err)
	{
	case WPN_HEADER_ERROR:
		{
			m_wstrErrMsg = L"WPN-Header error.";
		}
		break;
	case CN_HEADER_ERROR:
		{
			m_wstrErrMsg = L"CN-Header error.";
		}
		break;
	case CP_HEADER_ERROR:
		{
			m_wstrErrMsg = L"CP-Header error.";
		}
		break;
	case CP_TAIL_ERROR:
		{
			m_wstrErrMsg = L"CP-Tail error.";
		}
		break;
	case KEY_WITHOUT_VALUE:
		{
			m_wstrErrMsg = L"Key without value, around \""+s2ws(strParam)+L"\" .";
		}
		break;
	case VALUE_WITHOUT_END_SIGN:
		{
			m_wstrErrMsg = L"Value without a End-Sign(\';\'), around \""+s2ws(strParam)+L"\" .";
		}
		break;
	case KEY_REPEATED:
		{
			m_wstrErrMsg = L"Repeat insert key \""+s2ws(strParam)+L"\". ";
		}
		break;
	case KEY_EMPTY:
		{
			m_wstrErrMsg = L"Empty key.";
		}
		break;
	case VALUE_EMPTY:
		{
			m_wstrErrMsg = L"Empty value.";
		}
		break;
	case MERGE_ERROR_WPN_DISACCORD:
		{
			m_wstrErrMsg = L"Merge error: WPN disaccord.";
		}
		break;
	case MERGE_ERROR_CN_DISACCORD:
		{
			m_wstrErrMsg = L"Merge error: CN disaccord.";
		}
		break;
	default:
		{
			m_wstrErrMsg = L"Unknow error.";
		}
		break;
	}
	return;
}

bool CNHCommand::LoadKey(const char **pp, const char * const pEnd, std::string &strKey)
{
	assert(pp!=NULL && *pp!=NULL);
	if (**pp=='\0' || **pp=='&' || *pp==pEnd)
	{
		return false;
	}
	// 记住起点
	const char *pOrigin = *pp;
	int i = 0; // 计数器
	while (**pp!='=' &&  *pp!=pEnd)
	{
		if (**pp==';' || **pp==',')
		{
			// 在遇到'='之前遇到';'或','
			SetError(KEY_WITHOUT_VALUE, std::string(pOrigin, i));
			return false;
		}
		++i;
		++(*pp);
	}
	//if (i <= 0)
	//{
	//	SetError(KEY_EMPTY);
	//	return false;
	//}
	strKey.assign(pOrigin, i);
	++(*pp); // go pass the '='
	return true;
}

bool CNHCommand::LoadValue(const char **pp, const char * const pEnd, std::string &strValue, bool *pbIsMultiValue)
{
	assert(pp!=NULL && *pp!=NULL);
	if (**pp=='\0' || **pp=='&' || *pp==pEnd)
	{
		return false;
	}
	// 记住起点
	const char *pOrigin = *pp;
	int i = 0; // 计数器
	while (**pp!=';'  &&  *pp!=pEnd)
	{
		if (**pp=='=' || **pp=='&')
		{
			// 在遇到';'之前遇到'='或者'&'
			SetError(VALUE_WITHOUT_END_SIGN, std::string(pOrigin, i));
			return false;
		}
		if (**pp==',' && pbIsMultiValue!=NULL)
		{
			*pbIsMultiValue = true;
		}
		++i;
		++(*pp);
	}
	//if (i <= 0)
	//{
	//	SetError(VALUE_EMPTY);
	//	return false;
	//}
	strValue.assign(pOrigin, i);
	++(*pp); // go pass the ';'
	return true;
}

void CNHCommand::DeleteAllCPSetElem(void)
{
	CPNode *pNode = m_pHead;
	CPNode *tmp(NULL);
	while(NULL != pNode)
	{
		tmp = pNode->pNext;
		delete pNode;
		pNode = tmp;
	}
	return;
}

void CNHCommand::Load(const char *pchBuf, const int iSize)
{
	assert((pchBuf!=NULL) && (iSize>0));
	const char *p = pchBuf;	// 游标
	const char * const pEnd = p + iSize;
	std::string str("");
	// WPN
	if (str.assign(p, strlen(m_pchWPNHeader)) != m_pchWPNHeader)
	{
		SetError(WPN_HEADER_ERROR);
		return;
	}
	p += strlen(m_pchWPNHeader); // go pass the WPN-Header
	if (!LoadValue(&p, pEnd, m_strWPN))
	{
		return;
	}
	//str.assign(p, s_kiWPNSize);
	//auto iter = std::find_if(str.begin(), str.end()
	//	, [](char ch){return ch!=s_kchPlaceHolder;}); // google C++0x
	//m_strWPN.assign(iter, str.end());
	//p += s_kiWPNSize;

	// CN
	if (str.assign(p, strlen(m_pchCNHeader)) != m_pchCNHeader)
	{
		SetError(WPN_HEADER_ERROR);
		return;
	}
	p += strlen(m_pchCNHeader); // go pass the CN-Header
	if (!LoadValue(&p, pEnd, m_strCN))
	{
		return;
	}
	//m_strCN.assign(p, s_kiCNSize);
	//p += s_kiCNSize;

	// CP-Header
	if (str.assign(p, strlen(m_pchCPHeader)) != m_pchCPHeader)
	{
		SetError(CP_HEADER_ERROR);
		return;
	}
	p += strlen(m_pchCPHeader); // go pass the CP-Header
	
	// CPS
	CPNode *pNode = new CPNode;
	m_pHead = pNode; // 设置链表头节点指针
	bool bErr(false);
	while (true)
	{
		if (!LoadKey(&p, pEnd, pNode->strKey))
		{
			if (m_bError)
			{
				// 错误返回
				bErr = true;
				break;
			}
			// 正常返回
			break;
		}
		if (!LoadValue(&p, pEnd, pNode->strValue, &pNode->bIsMultiValue))
		{
			// 错误返回
			bErr = true;
			break;
		}
		std::pair<CPSET::iterator, bool> pair = m_setCPS.insert(pNode);
		if (!pair.second)
		{
			bErr = true;
			SetError(KEY_REPEATED, pNode->strKey);
			break;
		}
		// 按插入顺序连成链表
		pNode->pNext = new CPNode;
		m_ppLastNext = &(pNode->pNext);
		pNode = *m_ppLastNext;
	}
	if (*m_ppLastNext == m_pHead) //CP段为空
	{
		m_pHead = NULL;
	}
	else
	{
		*m_ppLastNext = NULL;
	}
	if (NULL != pNode)
	{
		delete pNode;
		pNode = NULL;
	}
	if (bErr)
	{
		return;
	}
	
	// CP-Tail
	if (str.assign(p, strlen(m_pchCPTail)) != m_pchCPTail)
	{
		SetError(CP_TAIL_ERROR);
	}
	return;
}

void CNHCommand::Load(const char *pchBuf)
{
	assert(pchBuf != NULL);
	return Load(pchBuf, strlen(pchBuf));
}

std::wstring CNHCommand::GetWPN(void) const
{
	return s2ws(m_strWPN);
}

void CNHCommand::SetWPN(const std::wstring &wstrWPN)
{
	m_strWPN = ws2s(wstrWPN);
	return;
}

int CNHCommand::GetCN(void) const
{
	return atoi(m_strCN.c_str());
}

std::wstring CNHCommand::GetCNStr(void) const
{
	return s2ws(m_strCN);
}

void CNHCommand::SetCN(const int iCN)
{
	assert(iCN>0 && iCN<100);
	//char chFormat[32] = {0};
	//_snprintf_s(chFormat, sizeof(chFormat), _TRUNCATE, "%%0%dd", s_kiCNSize);
	char chCN[8] = {0};
	_snprintf_s(chCN, sizeof(chCN), _TRUNCATE, "%d", iCN);
	m_strCN.assign(chCN);
	return;
}

void CNHCommand::SetCNStr(const std::wstring &wstrCN)
{
	assert(L"" != wstrCN);
	m_strCN = ws2s(wstrCN);
	return;
}

bool CNHCommand::GetCP(const std::wstring &wstrKey, std::string &strValue, bool *pbIsMultiValue) const
{
	bool bFound = false;
	CPNode node;
	node.strKey = ws2s(wstrKey);
	CPSET::const_iterator iter = m_setCPS.find(&node);
	if(m_setCPS.end() != iter)
	{
		bFound = true;
		strValue = (*iter)->strValue;
		if (pbIsMultiValue)
		{
			*pbIsMultiValue = (*iter)->bIsMultiValue;
		}
	}
	return bFound;
}

bool CNHCommand::GetCP(const std::wstring &wstrKey, std::wstring &wstrValue, bool *pbIsMultiValue) const
{
	bool bFount = false;
	std::string strValue;
	bFount = GetCP(wstrKey, strValue, pbIsMultiValue);
	if (bFount)
	{
		wstrValue = s2ws(strValue);
	}
	return bFount;
}

void CNHCommand::SetCP(const std::wstring& wstrKey, const std::wstring& wstrValue)
{
	std::string strKey(ws2s(wstrKey));
	std::string strValue(ws2s(wstrValue));
	CPNode node;
	node.strKey = strKey;
	CPSET::const_iterator iter = m_setCPS.find(&node);
	if (m_setCPS.end() != iter)
	{
		// 修改
		(*iter)->strValue = strValue;
	}
	else
	{
		// 插入
		CPNode *pNode = new CPNode;
		pNode->strKey = strKey;
		pNode->strValue = strValue;
		*m_ppLastNext = pNode;
		m_ppLastNext = &pNode->pNext;
		m_setCPS.insert(pNode);
	}
	return;
}

void CNHCommand::SetCP(const std::wstring& wstrKey, const wchar_t *pwchValue)
{
	std::wstring wstrValue(pwchValue);
	return SetCP(wstrKey, wstrValue);
}

void CNHCommand::SetCP(const std::wstring &wstrKey, const bool bValue)
{
	std::wstring wstrValue(L"");
	if (bValue)
	{
		wstrValue = L"1";
	}
	else
	{
		wstrValue = L"0";
	}
	return SetCP(wstrKey, wstrValue);
}

void CNHCommand::SetCP(const std::wstring &wstrKey, const int iValue)
{
	wchar_t wchBuf[64] = {0};
	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", iValue);
	std::wstring wstrValue(wchBuf);
	return SetCP(wstrKey, wstrValue);
}

void CNHCommand::SetCP(const std::wstring &wstrKey, const float fValue, const int iDecimalPlace)
{
	wchar_t wchFormat[64] = {0};
	_snwprintf_s(wchFormat, _countof(wchFormat), _TRUNCATE, L"%%.%df", iDecimalPlace);
	wchar_t wchBuf[64] = {0};
	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, wchFormat, fValue);
	std::wstring wstrValue(wchBuf);
	return SetCP(wstrKey, wstrValue);
}

void CNHCommand::PrintToString(std::string &strCmd)
{
	strCmd.assign(m_pchWPNHeader);
	strCmd += m_strWPN;
	strCmd += ";";
	strCmd += m_pchCNHeader;
	strCmd += m_strCN;
	strCmd += ";";
	strCmd += m_pchCPHeader;
	CPNode *pNode = m_pHead;
	while(NULL != pNode)
	{
		strCmd += pNode->strKey;
		strCmd += "=";
		strCmd += pNode->strValue;
		strCmd += ";";
		pNode = pNode->pNext;
	}
	strCmd += m_pchCPTail;
	return;
}

void CNHCommand::PrintToBuffer(PBYTE pBuf, size_t &size)
{
	if (pBuf == NULL)
	{
		size = PrintBufferSize();
		return;
	}
	int nIndex = 0, nStep = 0;
	// wpn
	nStep = strlen(m_pchWPNHeader);
	memcpy(&pBuf[nIndex], m_pchWPNHeader, nStep);
	nIndex += nStep;
	nStep = m_strWPN.size();
	memcpy(&pBuf[nIndex], m_strWPN.c_str(), nStep);
	nIndex += nStep;
	memset(&pBuf[nIndex], ';', 1);
	++nIndex;
	// cn
	nStep = strlen(m_pchCNHeader);
	memcpy(&pBuf[nIndex], m_pchCNHeader, nStep);
	nIndex += nStep;
	nStep = m_strCN.size();
	memcpy(&pBuf[nIndex], m_strCN.c_str(), nStep);
	nIndex += nStep;
	memset(&pBuf[nIndex], ';', 1);
	++nIndex;
	// cp
	nStep = strlen(m_pchCPHeader);
	memcpy(&pBuf[nIndex], m_pchCPHeader, nStep);
	nIndex += nStep;
	CPNode* pNode = m_pHead;
	while (pNode != NULL)
	{
		nStep = pNode->strKey.size();
		memcpy(&pBuf[nIndex], pNode->strKey.c_str(), nStep);
		nIndex += nStep;
		memset(&pBuf[nIndex], '=', 1);
		++nIndex;
		nStep = pNode->strValue.size();
		memcpy(&pBuf[nIndex], pNode->strValue.c_str(), nStep);
		nIndex += nStep;
		memset(&pBuf[nIndex], ';', 1);
		++nIndex;
		pNode = pNode->pNext;
	}
	nStep = strlen(m_pchCPTail);
	memcpy(&pBuf[nIndex], m_pchCPTail, nStep);
	//nIndex += nStep;
	return;
}

size_t CNHCommand::PrintBufferSize(void)
{
	size_t size = 0;
	// WPN
	size += (m_strWPN.size() + strlen(m_pchWPNHeader)) + 1; // +1 for ";"
	// CN
	size += (m_strCN.size() + strlen(m_pchCNHeader)) + 1;
	// CP
	size += (strlen(m_pchCPHeader) + strlen(m_pchCPTail)); // m_pchCPTail 包含了 ";"
	// counting-size functor
	struct count_cp_size
	{
		count_cp_size(size_t &size) : m_size(size) {}
		void operator () (CPNode *node)
		{
			m_size += node->strKey.size();
			m_size += node->strValue.size();
			m_size += 2; // =>strlen("=;")
			return;
		}
	private:
		size_t &m_size;
	};
	std::for_each(m_setCPS.begin(), m_setCPS.end(), count_cp_size(size));
	
	return size;
}

//namespace nhstd_hf
//{
	std::string CNHCommand::ws2s(const std::wstring &wstr) const
	{
		std::string curLocale = setlocale(LC_ALL, NULL);	// curLocale = "C"
		setlocale(LC_ALL, "chs");
		const wchar_t *pwchSource = wstr.c_str();
		size_t sizeDest = sizeof(wchar_t) * (wstr.size() + 1);
		char *pchDest = new char[sizeDest];
		memset(pchDest, 0, sizeDest);
		size_t sizeTran(0);
		wcstombs_s(&sizeTran, pchDest, sizeDest, pwchSource, _TRUNCATE);
		std::string strResult = pchDest;
		delete []pchDest;
		setlocale(LC_ALL, curLocale.c_str());
		return strResult;
	}
	
	std::wstring CNHCommand::s2ws(const std::string& str) const
	{
		std::string curLocale = setlocale(LC_ALL, NULL);
		setlocale(LC_ALL, "chs");
		const char *pchSource = str.c_str();
		size_t sizeDest = str.size() + 1;
		wchar_t *pwchDest = new wchar_t[sizeDest];
		wmemset(pwchDest, 0, sizeDest);
		size_t sizeTran(0);
		mbstowcs_s(&sizeTran, pwchDest, sizeDest, pchSource, _TRUNCATE);
		std::wstring wstrResult = pwchDest;
		delete []pwchDest;
		setlocale(LC_ALL, curLocale.c_str());
		return wstrResult;
	}
//};