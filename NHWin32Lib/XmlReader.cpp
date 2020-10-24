#include "stdafx.h"
#include "XmlReader.h"
#include "KPathParser.h"
#include "kutfconv.h"

CXmlReader::CXmlReader()
{
	m_pOpenElement = NULL;
	m_bFirstElement  = true;
	m_pXmlDoc = new TiXmlDocument();
}

CXmlReader::~CXmlReader()
{
	delete m_pXmlDoc;
	m_pXmlDoc = NULL;
}

bool CXmlReader::LoadFile(LPCTSTR szXmlFile)
{
	m_pXmlDoc->LoadFile(TCharToANSI(szXmlFile));
	if (m_pXmlDoc->Error()) return false;
	
	return true;
}

bool CXmlReader::Parse(LPCTSTR szXml)
{	
	m_pXmlDoc->Parse(TCharToUTF8(szXml));
	if (m_pXmlDoc->Error()) return false;
		
	return true;
}

bool CXmlReader::OpenNode(LPCTSTR szPath)
{	
	if (!szPath)
	{
		m_pOpenElement = m_pXmlDoc->RootElement();
	}
	else
	{
		m_pOpenElement = _Open(TCharToUTF8(szPath));
	}

	return m_pOpenElement != NULL;
}

TiXmlElement* CXmlReader::_Open(LPCSTR szPath)
{
	KPathParserA path;
	bool bRetCode = false;
	TiXmlElement* pTempElement = NULL;
	size_t i = 0, max_size = 0;
	
	bRetCode = path.Parse(szPath);
	if (!bRetCode) goto Exit0;

	
	max_size = path.Size();
	pTempElement = m_pXmlDoc->RootElement();
	
	for (i = 0; i < max_size; i++)
	{
		pTempElement = _FindSiblingElement(pTempElement, path.Get(i));
		if (!pTempElement) break;
		if (i != max_size - 1)
		{
			pTempElement = pTempElement->FirstChildElement();
		}
	}

Exit0:
	return pTempElement;
}

TiXmlElement* CXmlReader::_FindSiblingElement(TiXmlElement* pElement, LPCSTR szFolder)
{	
	while (pElement)
	{		
		if (lstrcmpA(pElement->Value(), szFolder) == 0)
			break;

		pElement = pElement->NextSiblingElement();
	}
	return pElement;
}

bool CXmlReader::GetNodeAttribute(LPCTSTR szKey, bool& bValue)
{
	int nValue	=	0;
	if (GetNodeAttribute(szKey, nValue))
	{
		if (nValue)
			bValue = true;
		else
			bValue = false;

		return true;

	}
	else
		return false;
}

bool CXmlReader::GetNodeAttribute(LPCTSTR szKey, int& nValue)
{
	if (!m_pOpenElement) return false;

	int nRetCode = m_pOpenElement->QueryIntAttribute(TCharToUTF8(szKey), &nValue);
	if (nRetCode != TIXML_SUCCESS) return false;

	return true;
}

void CXmlReader::GetNodeAttribute(LPCTSTR szKey, std_string &strValue)
{
	strValue.clear();

	if (m_pOpenElement) 
	{
		const char* p = m_pOpenElement->Attribute(TCharToUTF8(szKey));
		if (p != NULL)
		{
			strValue = UTF8ToTChar(p);
		}
	}
}

void CXmlReader::GetNodeContent(std_string &strText)
{
	strText.clear();
	if (m_pOpenElement)
	{
		const char* p = m_pOpenElement->GetText();
		if (p != NULL)
		{
			strText = UTF8ToTChar(p);
		}
	}
}

void CXmlReader::GetNodeName(std_string &strName)
{
	strName.clear();
	if (m_pOpenElement)
	{
		const char* p = m_pOpenElement->Value();
		if (p != NULL)
		{
			strName = UTF8ToTChar(p);
		}
	}
}

bool CXmlReader::NextSibling()
{
	if (m_pOpenElement)
	{
		if (NULL == m_pOpenElement->NextSiblingElement())
		{
			return false;
		}
		else
		{
			m_pOpenElement = m_pOpenElement->NextSiblingElement();
			return true;
		}
	}
	else
	{
		return false;
	}
}

/*
bool CXmlReader::ReadOneElement()
{
	if (!m_pOpenElement) return false;

	TiXmlElement* pItemElement = NULL;

	if (m_bFirstElement)
	{
		pItemElement = m_pOpenElement->FirstChildElement();
		if(pItemElement == NULL)
			return false;

		m_bFirstElement = false;
	}
	else
	{
		pItemElement = m_pOpenElement->NextSiblingElement();
		if(pItemElement == NULL)
			return false;
	}

	m_pOpenElement = pItemElement;

	return true;
}
*/

bool CXmlReader::EnterNode(void)
{
	if (!m_pOpenElement) 
	{
		return false;
	}

	if (m_pOpenElement->FirstChild())
	{
		m_pOpenElement = m_pOpenElement->FirstChild()->ToElement();
		return true;
	}
	else
	{
		return false;
	}
}

bool CXmlReader::ExitNode(void)
{
	if (!m_pOpenElement) 
	{
		return false;
	}

	if (m_pOpenElement->Parent())
	{
		m_pOpenElement = m_pOpenElement->Parent()->ToElement();
		return true;
	}
	else
	{
		return false;
	}
}
