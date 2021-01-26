/*
 * Copyright (c) 佛山市南华仪器股份有限公司
 * All rights reserved.
 *
 * 文件名称：NHCommand.h
 * 文件标识：
 * 描述：封装通讯命令
 *
 * 版本：1.0
 * 日期：2011-06-xx
 * 作者：
 *
 *
 * 历史信息：
 *
 * 版本：1.0.0Beta1
 * 日期：2011-06-xx
 * 作者：
 * 描述：正在开发
 */
#pragma once
#include <set>
#include <string>

/*
 * 通讯命令
 */
//class AFX_EXT_CLASS CNHCommand
class CNHCommand
{
public:
	CNHCommand(void);
	~CNHCommand(void);
private:
	// NO COPY
	CNHCommand(const CNHCommand&);
	CNHCommand& operator = (const CNHCommand&);

public:
	// 装载数据
	// 装载数据后请检测错误标志和错误信息
	void Load(const char *pchBuf, const int iSize);
	// 装载数据(空结束字符流)
	void Load(const char *pchBuf);
	// 返回错误标志
	bool Error(void) const { return m_bError; }
	// 返回(Last)错误信息
	std::wstring GetErrMsg(void) { m_bError = false; return m_wstrErrMsg; }
	// 打印到字符串(ANSI字符串)
	void PrintToString(std::string &strCmd);
	// 打印到缓冲区(ANSI字符串)
	// 执行空调用(pBuf=NULL)时, size为输出参数, 返回所需的缓冲区大小
	// pBuf!=NULL时, size为输入参数, 执行打印操作.
	void PrintToBuffer(PBYTE pBuf, size_t &size);
	// 取WPN
	std::wstring GetWPN(void) const;
	// 设WPN
	void SetWPN(const std::wstring &wstrWPN);
	// 取CN
	int GetCN(void) const;
	std::wstring GetCNStr(void) const;
	// 设CN
	void SetCN(const int iCN);
	void SetCNStr(const std::wstring &wstrCN);
	// 取CP
	// 当CP字段为"Key1=Value1,Value2,...,ValueN;"形式时,
	// 取得的CP字段的strValue值为"Value1,Value2,...,ValueN".
	bool GetCP(const std::wstring &wstrKey, std::wstring &wstrValue, bool *pbIsMultiValue=NULL) const;
	bool GetCP(const std::wstring &wstrKey, std::string &strValue, bool *pbIsMultiValue=NULL) const;
	// 设CP
	void SetCP(const std::wstring &wstrKey, const std::wstring &wstrValue);
	void SetCP(const std::wstring &wstrKey, const wchar_t *pwchValue);
	void SetCP(const std::wstring &wstrKey, const bool bValue);
	void SetCP(const std::wstring &wstrKey, const int iValue);
	void SetCP(const std::wstring &wstrKey, const float fValue, const int iDecimalPlace = 2); // 默认保留两位小数
	//// 合并CP
	//// cmd的CP字段均移动至this
	//void MergeCP(CNHCommand& cmd);
	
private:
	// 字符流中读一个键
	bool LoadKey(const char **pp, const char * const pEnd, std::string &strkey);
	// 字符流中读一个值
	bool LoadValue(const char **pp, const char * const pEnd, std::string &strValue, bool *pbIsMultiValue=NULL);
	// 设置错误信息
	void SetError(const int err, const std::string &strParam = "");
	// 删除CP Set 中的全部元素
	inline void DeleteAllCPSetElem(void);
	// 打印所需缓冲区大小
	size_t PrintBufferSize(void);

private:
	std::string ws2s(const std::wstring &wstr) const;
	std::wstring s2ws(const std::string& str) const;

private:
	/*-------------------命令格式常量定义----------------------*/
	// WPN 头标识
	static const char * const m_pchWPNHeader;
	// CN 头标识
	static const char * const m_pchCNHeader;
	// CP 头标识
	static const char * const m_pchCPHeader;
	// CP 尾标识
	static const char * const m_pchCPTail;

	/*------------------------------------------------------*/

	// 工位编号(WPN)
	std::string m_strWPN;
	// 命令编号(CN)
	std::string m_strCN;
	// 错误信息
	std::wstring m_wstrErrMsg;
	// 错误标志
	bool m_bError;
	// 错误代码定义
	enum ErrorCodeEnum
	{
		WPN_HEADER_ERROR,           // WPN标志错误
		CN_HEADER_ERROR,            // CN标志错误
		CP_HEADER_ERROR,            // CP头标志错误
		CP_TAIL_ERROR,              // CP尾标志错误
		KEY_WITHOUT_VALUE,          // 键缺少一个值
		VALUE_WITHOUT_END_SIGN,     // 值缺少一个结束符号 (';')
		KEY_REPEATED,               // 出现重复的键
		KEY_EMPTY,                  // 出现"空键"
		VALUE_EMPTY,                // 出现"空值"
		
		MERGE_ERROR_WPN_DISACCORD,  // 合并错误, WPN不一致
		MERGE_ERROR_CN_DISACCORD    // 合并错误, CN不一致
	};
	// 命令参数节点
	struct CPNode
	{
		std::string strKey;     // 参数键
		std::string strValue;   // 参数值
		bool bIsMultiValue;     // 多个值(Value1,Value2,...)
		CPNode *pNext;	// 用作保存插入顺序
		CPNode(void): strKey(""), strValue(""), bIsMultiValue(false), pNext(NULL){}
		~CPNode(void){}
	};
	// CPS头节点
	CPNode *m_pHead;
	// 保存CPS尾节点的Next指针地址
	CPNode **m_ppLastNext;
	class my_less
	{
	public:
		bool operator () (const CPNode *pN1, const CPNode *pN2) const
		{
			return pN1->strKey.compare(pN2->strKey)<0;
		}
	};
	typedef std::set<CPNode *, my_less> CPSET; // TODO：用地址作为键？！
	// 命令参数(CP)
	CPSET m_setCPS;
};

