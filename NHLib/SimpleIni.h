// by cui
// ini�����ļ��򵥲�����

#pragma once

class CSimpleIni
{
public:
	// ��ʼ�������ļ�
	inline CSimpleIni(void)
	{
		GetModuleFileName(NULL, m_tzFileName, MAX_PATH);
		lstrcpy(m_tzFileName + lstrlen(m_tzFileName) - 4, TEXT(".ini"));
	}

	// ��ʼ�������ļ�
	inline CSimpleIni(PCTSTR ptzFileName)
	{
		lstrcpy(m_tzFileName, ptzFileName);
	}

	~CSimpleIni(void)
	{
	}

	//// ��ȡ����
	//inline UINT GetInt(PCTSTR ptzKeyName, INT iDefault = 0, PCTSTR ptzSectionName = INI_Main)
	//{
	//	return GetPrivateProfileInt(ptzSectionName, ptzKeyName, iDefault, m_tzFileName);
	//}

	//// ��������
	//inline BOOL SetInt(PCTSTR ptzKeyName, INT iValue = 0, PCTSTR ptzSectionName = INI_Main)
	//{
	//	TCHAR tzString[16]; 
	//	wsprintf(tzString, TEXT("%d"), iValue);
	//	return WritePrivateProfileString(ptzSectionName, ptzKeyName, tzString, m_tzFileName);
	//}

	// ��ȡ�ַ���
	inline DWORD GetString(PCTSTR ptzSectionName, PCTSTR ptzKeyName, PTSTR ptzReturnedString, DWORD dwSize = MAX_PATH, PCTSTR ptzDefault = NULL)
	{
		return GetPrivateProfileString(ptzSectionName, ptzKeyName, ptzDefault, ptzReturnedString, dwSize, m_tzFileName);
	}

	// ��ȡ�ַ���
	inline CString GetString(PCTSTR ptzSectionName, PCTSTR ptzKeyName, PCTSTR ptzDefault = NULL)
	{
		CString strReturnedString(L"");
		GetPrivateProfileString(ptzSectionName, ptzKeyName, ptzDefault, strReturnedString.GetBuffer(MAX_PATH), MAX_PATH, m_tzFileName);
		strReturnedString.ReleaseBuffer();
		 return strReturnedString;
	}

	// �����ַ���
	inline BOOL SetString(PCTSTR ptzSectionName, PCTSTR ptzKeyName, PCTSTR ptzString = NULL)
	{
		return WritePrivateProfileString(ptzSectionName, ptzKeyName, ptzString, m_tzFileName);
	}

	//// �����ַ���
	//inline BOOL SetString(CString strSectionName, CString strKeyName, PCTSTR ptzString = NULL)
	//{
	//	return WritePrivateProfileString(ptzSectionName, ptzKeyName, ptzString, m_tzFileName);
	//}

	//// ��ȡ�ṹ
	//inline BOOL GetStruct(PCTSTR ptzKeyName, PVOID pvStruct, UINT uSize, PCTSTR ptzSectionName = INI_Main)
	//{
	//	return GetPrivateProfileStruct(ptzSectionName, ptzKeyName, pvStruct, uSize, m_tzFileName);
	//}

	//// ���ýṹ
	//inline BOOL SetStruct(PCTSTR ptzKeyName, PVOID pvStruct, UINT uSize, PCTSTR ptzSectionName = INI_Main)
	//{
	//	return WritePrivateProfileStruct(ptzSectionName, ptzKeyName, pvStruct, uSize, m_tzFileName);
	//}

	//// ��ȡ��
	//inline DWORD GetSection(PTSTR ptzReturnBuffer, DWORD dwSize, PCTSTR ptzSectionName = INI_Main)
	//{
	//	return GetPrivateProfileSection(ptzSectionName, ptzReturnBuffer, dwSize, m_tzFileName);
	//}

	//// ���ý�
	//inline DWORD SetSection(PCTSTR ptzString, PCTSTR ptzSectionName = INI_Main)
	//{
	//	return WritePrivateProfileSection(ptzSectionName, ptzString, m_tzFileName);
	//}

	//// ��ȡ����
	//inline DWORD GetSectionNames(PTSTR ptzReturnBuffer, DWORD dwSize)
	//{
	//	return GetPrivateProfileSectionNames(ptzReturnBuffer, dwSize, m_tzFileName);
	//}

private:    
	// INI �ļ���    
	TCHAR m_tzFileName[MAX_PATH];
};
