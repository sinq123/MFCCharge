#include "stdafx.h"
#include "XmlWriter.h"
#include "KPathParser.h"
#include "kutfconv.h"

CXmlWriter::CXmlWriter()
{
	m_pOpenElement = NULL;
	m_pXmlDoc = new TiXmlDocument();
	m_pXmlPrinter = new TiXmlPrinter();
}

CXmlWriter::~CXmlWriter()
{
	delete m_pXmlPrinter;
	m_pXmlPrinter = NULL;

	delete m_pXmlDoc;
	m_pXmlDoc = NULL;
}

bool CXmlWriter::LoadFile(LPCTSTR szXmlFile)
{
	m_pXmlDoc->LoadFile(TCharToANSI(szXmlFile));
	if (m_pXmlDoc->Error()) return false;

	return true;
}

bool CXmlWriter::WriteFile(LPCTSTR szXmlFile)
{
	return m_pXmlDoc->SaveFile(TCharToANSI(szXmlFile));
}

bool CXmlWriter::Parse(LPCTSTR szXml)
{
	m_pXmlDoc->Parse(TCharToUTF8(szXml));
	if (m_pXmlDoc->Error()) return false;

	return true;
}

TiXmlElement* CXmlWriter::_Open(LPCSTR szPath)
{
	KPathParserA path;
	bool bRetCode = false;
	TiXmlDocument* pDocument = NULL;
	TiXmlElement* pParentElement = NULL;
	TiXmlElement* pTempElement = NULL;

	path.Parse(szPath);
	if (!path.Size()) goto Exit0;

	pDocument = m_pXmlDoc->GetDocument();
	pParentElement = m_pXmlDoc->RootElement();
	if (!pParentElement)
	{
		TiXmlDeclaration* pDeclar = new TiXmlDeclaration("1.0", "UTF-8", "no");
		pDocument->LinkEndChild(pDeclar);
		pTempElement = _Create(pDocument, szPath);
		goto Exit0;
	}

	pTempElement = _FindSiblingElement(pParentElement, path.Get(0));
	if (!pTempElement)
	{
		pTempElement = _Create(pDocument, szPath);
		goto Exit0;
	}

	pParentElement = pTempElement;
	pTempElement = pParentElement->FirstChildElement();
	for (size_t i = 1; i < path.Size(); i++)
	{
		pTempElement = _FindSiblingElement(pTempElement, path.Get(i));
		if (!pTempElement)
		{
			std::string strPath;
			for (size_t j = i; j < path.Size(); j++)
			{
				strPath += path.Get(j);
				strPath += "\\";
			}
			pTempElement = _Create(pParentElement, strPath.c_str());
			goto Exit0;
		}
		if (i != path.Size() - 1)
		{
			pParentElement = pTempElement;
			pTempElement = pParentElement->FirstChildElement();
		}
	}

Exit0:
	return pTempElement;
}

TiXmlElement* CXmlWriter::_FindSiblingElement(TiXmlElement* pElement, LPCSTR szFolder)
{	
	while (pElement)
	{		
		if (lstrcmpA(pElement->Value(), szFolder) == 0)
			break;

		pElement = pElement->NextSiblingElement();
	}
	return pElement;
}

TiXmlElement* CXmlWriter::_Create(TiXmlNode* pParentNode, LPCSTR szPath)
{
	KPathParserA path;
	TiXmlElement* pRetElement = NULL;

	path.Parse(szPath);
	if (!path.Size()) goto Exit0;

	for (size_t i = 0; i < path.Size(); i++)
	{
		pRetElement = new TiXmlElement(path.Get(i));
		pParentNode->LinkEndChild(pRetElement);
		pParentNode = pRetElement;
	}

Exit0:
	return pRetElement;
}

bool CXmlWriter::OpenNode(LPCTSTR szPath)
{
	if (!szPath)
	{
		m_pOpenElement = m_pXmlDoc->RootElement();
	}
	else
	{
		m_pOpenElement = _Open(TCharToUTF8(szPath));
	}

	if(m_pOpenElement)
		m_OpenParentElement = m_pOpenElement;

	return m_pOpenElement != NULL;
}

bool CXmlWriter::SetNodeAttribute(LPCTSTR szKey, int nValue)
{
	if (!m_pOpenElement) return false;

	m_pOpenElement->SetAttribute(TCharToUTF8(szKey), nValue);

	return true;
}

bool CXmlWriter::SetNodeAttribute(LPCTSTR szKey, LPCTSTR szValue)
{
	if (!m_pOpenElement || !szValue) return false;

	m_pOpenElement->SetAttribute(TCharToUTF8(szKey), TCharToUTF8(szValue));

	return true;
}

bool CXmlWriter::AppendNodeContent(LPCTSTR szText, bool bCDATA)
{
	if (!m_pOpenElement || !szText) return false;

	TiXmlText *pXmlText = new TiXmlText(TCharToUTF8(szText));
	pXmlText->SetCDATA(bCDATA);
	m_pOpenElement->LinkEndChild(pXmlText);

	return true;
}

bool CXmlWriter::SetNodeContent(LPCTSTR szText)
{
	if (!m_pOpenElement || !szText) return false;

	TiXmlText *pXmlText = new TiXmlText((LPCSTR)TCharToUTF8(szText));

	m_pOpenElement->Clear();
	m_pOpenElement->LinkEndChild(pXmlText);

	return true;
}

LPCTSTR CXmlWriter::ToXml(std_string &strXml)
{
	strXml.clear();
	m_pXmlDoc->Accept(m_pXmlPrinter);
	strXml = UTF8ToTChar(m_pXmlPrinter->CStr());
	//LPCTSTR p = UTF8ToTChar(m_pXmlPrinter->CStr());
	//if (p != NULL)
	//{
	//	strXml = p;
	//}
	return strXml.c_str();
}

bool CXmlWriter::AddNode(LPCTSTR szNodeName)
{
	if (!m_OpenParentElement || !szNodeName) return false;

	TiXmlElement* pItemElement = new TiXmlElement(TCharToUTF8(szNodeName));
	m_OpenParentElement->LinkEndChild(pItemElement);

	m_pOpenElement = pItemElement;

	return m_pOpenElement != NULL;
}

bool CXmlWriter::EnterNode(void)
{
	if (m_pOpenElement->FirstChild())
	{
		m_pOpenElement = m_pOpenElement->FirstChild()->ToElement();
		m_OpenParentElement = m_pOpenElement;
		return true;
	}
	else
	{
		return false;
	}

	//if (!m_pOpenElement) return false;

	//m_OpenParentElement = m_pOpenElement;

	//return m_pOpenElement != NULL;
}

bool CXmlWriter::ExitNode(void)
{
	if (!m_pOpenElement) 
	{
		return false;
	}

	if (m_pOpenElement->Parent())
	{
		m_pOpenElement = m_pOpenElement->Parent()->ToElement();
		m_OpenParentElement = m_pOpenElement->Parent()->ToElement();
		return true;
	}
	else
	{
		return false;
	}

	//if (!m_pOpenElement) return false;
	//
	//if (m_pOpenElement->Parent())
	//{
	//	m_pOpenElement = m_pOpenElement->Parent()->ToElement();

	//	if (m_OpenParentElement)
	//	{
	//		m_OpenParentElement = m_pOpenElement->Parent()->ToElement();
	//	}
	//}

	//return m_pOpenElement != NULL;
}

bool CXmlWriter::NextSibling()
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

bool CXmlWriter::GetNodeAttribute(LPCTSTR szKey, bool& bValue)
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

bool CXmlWriter::GetNodeAttribute(LPCTSTR szKey, int& nValue)
{
	if (!m_pOpenElement) return false;

	int nRetCode = m_pOpenElement->QueryIntAttribute(TCharToUTF8(szKey), &nValue);
	if (nRetCode != TIXML_SUCCESS) return false;

	return true;
}

void CXmlWriter::GetNodeAttribute(LPCTSTR szKey, std_string &strValue)
{
	strValue.clear();

	if (m_pOpenElement) 
	{
		LPCTSTR p = UTF8ToTChar(m_pOpenElement->Attribute(TCharToUTF8(szKey)));
		if (p != NULL)
		{
			strValue = p;
		}
	}
}