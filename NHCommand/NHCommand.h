/*
 * Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
 * All rights reserved.
 *
 * �ļ����ƣ�NHCommand.h
 * �ļ���ʶ��
 * ��������װͨѶ����
 *
 * �汾��1.0
 * ���ڣ�2011-06-xx
 * ���ߣ�
 *
 *
 * ��ʷ��Ϣ��
 *
 * �汾��1.0.0Beta1
 * ���ڣ�2011-06-xx
 * ���ߣ�
 * ���������ڿ���
 */
#pragma once
#include <set>
#include <string>

/*
 * ͨѶ����
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
	// װ������
	// װ�����ݺ���������־�ʹ�����Ϣ
	void Load(const char *pchBuf, const int iSize);
	// װ������(�ս����ַ���)
	void Load(const char *pchBuf);
	// ���ش����־
	bool Error(void) const { return m_bError; }
	// ����(Last)������Ϣ
	std::wstring GetErrMsg(void) { m_bError = false; return m_wstrErrMsg; }
	// ��ӡ���ַ���(ANSI�ַ���)
	void PrintToString(std::string &strCmd);
	// ��ӡ��������(ANSI�ַ���)
	// ִ�пյ���(pBuf=NULL)ʱ, sizeΪ�������, ��������Ļ�������С
	// pBuf!=NULLʱ, sizeΪ�������, ִ�д�ӡ����.
	void PrintToBuffer(PBYTE pBuf, size_t &size);
	// ȡWPN
	std::wstring GetWPN(void) const;
	// ��WPN
	void SetWPN(const std::wstring &wstrWPN);
	// ȡCN
	int GetCN(void) const;
	std::wstring GetCNStr(void) const;
	// ��CN
	void SetCN(const int iCN);
	void SetCNStr(const std::wstring &wstrCN);
	// ȡCP
	// ��CP�ֶ�Ϊ"Key1=Value1,Value2,...,ValueN;"��ʽʱ,
	// ȡ�õ�CP�ֶε�strValueֵΪ"Value1,Value2,...,ValueN".
	bool GetCP(const std::wstring &wstrKey, std::wstring &wstrValue, bool *pbIsMultiValue=NULL) const;
	bool GetCP(const std::wstring &wstrKey, std::string &strValue, bool *pbIsMultiValue=NULL) const;
	// ��CP
	void SetCP(const std::wstring &wstrKey, const std::wstring &wstrValue);
	void SetCP(const std::wstring &wstrKey, const wchar_t *pwchValue);
	void SetCP(const std::wstring &wstrKey, const bool bValue);
	void SetCP(const std::wstring &wstrKey, const int iValue);
	void SetCP(const std::wstring &wstrKey, const float fValue, const int iDecimalPlace = 2); // Ĭ�ϱ�����λС��
	//// �ϲ�CP
	//// cmd��CP�ֶξ��ƶ���this
	//void MergeCP(CNHCommand& cmd);
	
private:
	// �ַ����ж�һ����
	bool LoadKey(const char **pp, const char * const pEnd, std::string &strkey);
	// �ַ����ж�һ��ֵ
	bool LoadValue(const char **pp, const char * const pEnd, std::string &strValue, bool *pbIsMultiValue=NULL);
	// ���ô�����Ϣ
	void SetError(const int err, const std::string &strParam = "");
	// ɾ��CP Set �е�ȫ��Ԫ��
	inline void DeleteAllCPSetElem(void);
	// ��ӡ���軺������С
	size_t PrintBufferSize(void);

private:
	std::string ws2s(const std::wstring &wstr) const;
	std::wstring s2ws(const std::string& str) const;

private:
	/*-------------------�����ʽ��������----------------------*/
	// WPN ͷ��ʶ
	static const char * const m_pchWPNHeader;
	// CN ͷ��ʶ
	static const char * const m_pchCNHeader;
	// CP ͷ��ʶ
	static const char * const m_pchCPHeader;
	// CP β��ʶ
	static const char * const m_pchCPTail;

	/*------------------------------------------------------*/

	// ��λ���(WPN)
	std::string m_strWPN;
	// ������(CN)
	std::string m_strCN;
	// ������Ϣ
	std::wstring m_wstrErrMsg;
	// �����־
	bool m_bError;
	// ������붨��
	enum ErrorCodeEnum
	{
		WPN_HEADER_ERROR,           // WPN��־����
		CN_HEADER_ERROR,            // CN��־����
		CP_HEADER_ERROR,            // CPͷ��־����
		CP_TAIL_ERROR,              // CPβ��־����
		KEY_WITHOUT_VALUE,          // ��ȱ��һ��ֵ
		VALUE_WITHOUT_END_SIGN,     // ֵȱ��һ���������� (';')
		KEY_REPEATED,               // �����ظ��ļ�
		KEY_EMPTY,                  // ����"�ռ�"
		VALUE_EMPTY,                // ����"��ֵ"
		
		MERGE_ERROR_WPN_DISACCORD,  // �ϲ�����, WPN��һ��
		MERGE_ERROR_CN_DISACCORD    // �ϲ�����, CN��һ��
	};
	// ��������ڵ�
	struct CPNode
	{
		std::string strKey;     // ������
		std::string strValue;   // ����ֵ
		bool bIsMultiValue;     // ���ֵ(Value1,Value2,...)
		CPNode *pNext;	// �����������˳��
		CPNode(void): strKey(""), strValue(""), bIsMultiValue(false), pNext(NULL){}
		~CPNode(void){}
	};
	// CPSͷ�ڵ�
	CPNode *m_pHead;
	// ����CPSβ�ڵ��Nextָ���ַ
	CPNode **m_ppLastNext;
	class my_less
	{
	public:
		bool operator () (const CPNode *pN1, const CPNode *pN2) const
		{
			return pN1->strKey.compare(pN2->strKey)<0;
		}
	};
	typedef std::set<CPNode *, my_less> CPSET; // TODO���õ�ַ��Ϊ������
	// �������(CP)
	CPSET m_setCPS;
};

