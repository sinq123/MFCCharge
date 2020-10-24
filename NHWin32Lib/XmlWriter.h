#ifndef __XML_WRITER_H__
#define __XML_WRITER_H__

#include <string>
#include <windows.h>

#include "TinyXML/tinyxml.h"

#ifdef UNICODE
typedef std::wstring std_string;
#else
typedef std::string std_string;
#endif

//#ifdef DLL_FILE
//class _declspec(dllexport) CXmlWriter
//#else
//class _declspec(dllimport) CXmlWriter
//#endif
class CXmlWriter
{
public:
	CXmlWriter();
	~CXmlWriter();

	bool LoadFile(LPCTSTR szXmlFile);
	bool WriteFile(LPCTSTR szXmlFile);

	// ����xml��
	bool Parse(LPCTSTR szXml);
	// ��xml�ڵ�	·����ʽ�����ڵ�\�ӽڵ�\��ڵ� �� ���ڵ�/�ӽڵ�/��ڵ�
	bool OpenNode(LPCTSTR szPath);

	// ��ȡ�ڵ�����
	bool GetNodeAttribute(LPCTSTR szKey, int &bValue);
	bool GetNodeAttribute(LPCTSTR szKey, bool &nValue);
	void GetNodeAttribute(LPCTSTR szKey, std_string &strValue);

	// ���ýڵ����ԣ�û�л���ӣ��������
	bool SetNodeAttribute(LPCTSTR szKey, int nValue);
	bool SetNodeAttribute(LPCTSTR szKey, LPCTSTR szValue);

	// ���ڽڵ����ݺ�׷��
	bool AppendNodeContent(LPCTSTR szText, bool bCDATA = false);

	// ����½ڵ�����
	bool SetNodeContent(LPCTSTR szText);

	// ����½ڵ�
	bool AddNode(LPCTSTR szNodeName);

	// ���뵱ǰ�ڵ�
	bool EnterNode(void);
	// �˳���ǰ�ڵ�
	bool ExitNode(void);

	// ָ���Ƶ���һ�ֵܽڵ�
	bool NextSibling();

	// ��ʽ��xml����
	LPCTSTR ToXml(std_string &strXml);


protected:
	TiXmlElement* _Open(LPCSTR szPath);
	TiXmlElement* _Create(TiXmlNode* pParentNode, LPCSTR szPath);
	TiXmlElement* _FindSiblingElement(TiXmlElement* pElement, LPCSTR szFolder);

private:
	TiXmlDocument* m_pXmlDoc;
	TiXmlPrinter* m_pXmlPrinter;
	TiXmlElement* m_pOpenElement;

	TiXmlElement* m_OpenParentElement;
};

#endif