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

	// 分析xml串
	bool Parse(LPCTSTR szXml);
	// 打开xml节点	路径格式：根节点\子节点\孙节点 或 根节点/子节点/孙节点
	bool OpenNode(LPCTSTR szPath);

	// 获取节点属性
	bool GetNodeAttribute(LPCTSTR szKey, int &bValue);
	bool GetNodeAttribute(LPCTSTR szKey, bool &nValue);
	void GetNodeAttribute(LPCTSTR szKey, std_string &strValue);

	// 设置节点属性，没有会添加，有则更新
	bool SetNodeAttribute(LPCTSTR szKey, int nValue);
	bool SetNodeAttribute(LPCTSTR szKey, LPCTSTR szValue);

	// 会在节点数据后追加
	bool AppendNodeContent(LPCTSTR szText, bool bCDATA = false);

	// 会更新节点数据
	bool SetNodeContent(LPCTSTR szText);

	// 添加新节点
	bool AddNode(LPCTSTR szNodeName);

	// 进入当前节点
	bool EnterNode(void);
	// 退出当前节点
	bool ExitNode(void);

	// 指针移到下一兄弟节点
	bool NextSibling();

	// 格式化xml数据
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