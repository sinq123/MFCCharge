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
		
	// 分析xml串
	bool Parse(LPCTSTR szXml);
	// 打开xml节点	路径格式：根节点\子节点\孙节点 或 根节点/子节点/孙节点
	bool OpenNode(LPCTSTR szPath);

	// 获取节点属性
	bool GetNodeAttribute(LPCTSTR szKey, int &bValue);
	bool GetNodeAttribute(LPCTSTR szKey, bool &nValue);
	void GetNodeAttribute(LPCTSTR szKey, std_string &strValue);

	// 获取节点内容
	void GetNodeContent(std_string &strText);
	void GetNodeName(std_string &strName);

	// 指针移到下一兄弟节点
	bool NextSibling();
	// 读取一个元素
	//bool ReadOneElement();

	// 进入当前节点
	bool EnterNode(void);
	// 退出当前节点
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