// by cui
// ini配置文件简单操作类

#pragma once

class CSimpleIni
{
public:
	// 初始化配置文件
	inline CSimpleIni(void)
	{
		GetModuleFileName(NULL, m_tzFileName, MAX_PATH);
		lstrcpy(m_tzFileName + lstrlen(m_tzFileName) - 4, TEXT(".ini"));
	}

	// 初始化配置文件
	inline CSimpleIni(PCTSTR ptzFileName)
	{
		lstrcpy(m_tzFileName, ptzFileName);
	}

	~CSimpleIni(void)
	{
	}

	//// 获取整数
	//inline UINT GetInt(PCTSTR ptzKeyName, INT iDefault = 0, PCTSTR ptzSectionName = INI_Main)
	//{
	//	return GetPrivateProfileInt(ptzSectionName, ptzKeyName, iDefault, m_tzFileName);
	//}

	//// 设置整数
	//inline BOOL SetInt(PCTSTR ptzKeyName, INT iValue = 0, PCTSTR ptzSectionName = INI_Main)
	//{
	//	TCHAR tzString[16]; 
	//	wsprintf(tzString, TEXT("%d"), iValue);
	//	return WritePrivateProfileString(ptzSectionName, ptzKeyName, tzString, m_tzFileName);
	//}

	// 获取字符串
	inline DWORD GetString(PCTSTR ptzSectionName, PCTSTR ptzKeyName, PTSTR ptzReturnedString, DWORD dwSize = MAX_PATH, PCTSTR ptzDefault = NULL)
	{
		return GetPrivateProfileString(ptzSectionName, ptzKeyName, ptzDefault, ptzReturnedString, dwSize, m_tzFileName);
	}

	// 获取字符串
	inline CString GetString(PCTSTR ptzSectionName, PCTSTR ptzKeyName, PCTSTR ptzDefault = NULL)
	{
		CString strReturnedString(L"");
		GetPrivateProfileString(ptzSectionName, ptzKeyName, ptzDefault, strReturnedString.GetBuffer(MAX_PATH), MAX_PATH, m_tzFileName);
		strReturnedString.ReleaseBuffer();
		 return strReturnedString;
	}

	// 设置字符串
	inline BOOL SetString(PCTSTR ptzSectionName, PCTSTR ptzKeyName, PCTSTR ptzString = NULL)
	{
		return WritePrivateProfileString(ptzSectionName, ptzKeyName, ptzString, m_tzFileName);
	}

	//// 设置字符串
	//inline BOOL SetString(CString strSectionName, CString strKeyName, PCTSTR ptzString = NULL)
	//{
	//	return WritePrivateProfileString(ptzSectionName, ptzKeyName, ptzString, m_tzFileName);
	//}

	//// 获取结构
	//inline BOOL GetStruct(PCTSTR ptzKeyName, PVOID pvStruct, UINT uSize, PCTSTR ptzSectionName = INI_Main)
	//{
	//	return GetPrivateProfileStruct(ptzSectionName, ptzKeyName, pvStruct, uSize, m_tzFileName);
	//}

	//// 设置结构
	//inline BOOL SetStruct(PCTSTR ptzKeyName, PVOID pvStruct, UINT uSize, PCTSTR ptzSectionName = INI_Main)
	//{
	//	return WritePrivateProfileStruct(ptzSectionName, ptzKeyName, pvStruct, uSize, m_tzFileName);
	//}

	//// 获取节
	//inline DWORD GetSection(PTSTR ptzReturnBuffer, DWORD dwSize, PCTSTR ptzSectionName = INI_Main)
	//{
	//	return GetPrivateProfileSection(ptzSectionName, ptzReturnBuffer, dwSize, m_tzFileName);
	//}

	//// 设置节
	//inline DWORD SetSection(PCTSTR ptzString, PCTSTR ptzSectionName = INI_Main)
	//{
	//	return WritePrivateProfileSection(ptzSectionName, ptzString, m_tzFileName);
	//}

	//// 获取节名
	//inline DWORD GetSectionNames(PTSTR ptzReturnBuffer, DWORD dwSize)
	//{
	//	return GetPrivateProfileSectionNames(ptzReturnBuffer, dwSize, m_tzFileName);
	//}

private:    
	// INI 文件名    
	TCHAR m_tzFileName[MAX_PATH];
};
