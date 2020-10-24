#ifndef __XML_READER_H__
#define __XML_READER_H__

#include <string>
#include <windows.h>

#include "TinyXML/tinyxml.h"

#ifdef UNICODE
typedef std::wstring std_string;
#else
typedef std::string std_string;
#endif

//#ifdef DLL_FILE
//class _declspec(dllexport) CXmlReader
//#else
//class _declspec(dllimport) CXmlReader
//#endif
class CXmlReader
{
public:
	CXmlReader();
	~CXmlReader();
	
	bool LoadFile(LPCTSTR szXmlFile);
		
	// ����xml��
	bool Parse(LPCTSTR szXml);
	// ��xml�ڵ�	·����ʽ�����ڵ�\�ӽڵ�\��ڵ� �� ���ڵ�/�ӽڵ�/��ڵ�
	bool OpenNode(LPCTSTR szPath);

	// ��ȡ�ڵ�����
	bool GetNodeAttribute(LPCTSTR szKey, int &bValue);
	bool GetNodeAttribute(LPCTSTR szKey, bool &nValue);
	void GetNodeAttribute(LPCTSTR szKey, std_string &strValue);

	// ��ȡ�ڵ�����
	void GetNodeContent(std_string &strText);
	void GetNodeName(std_string &strName);

	// ָ���Ƶ���һ�ֵܽڵ�
	bool NextSibling();
	// ��ȡһ��Ԫ��
	//bool ReadOneElement();

	// ���뵱ǰ�ڵ�
	bool EnterNode(void);
	// �˳���ǰ�ڵ�
	bool ExitNode(void);

protected:
	TiXmlElement* _Open(LPCSTR szPath);
	TiXmlElement* _FindSiblingElement(TiXmlElement* pElement, LPCSTR szFolder);

private:
	TiXmlDocument* m_pXmlDoc;
	TiXmlElement* m_pOpenElement;

	bool          m_bFirstElement;
};

#endif