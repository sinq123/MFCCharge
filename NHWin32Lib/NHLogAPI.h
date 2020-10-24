/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�NHLogAPI.h
* �ļ���ʶ��
* ��������־��¼
*
* �汾��1.0
* ���ߣ�Raylee
* ���ڣ�2010-05-24
*
* ��ʷ��Ϣ��
*
* �汾��1.0.6
* ���ڣ�2012-09-01
* ���ߣ�Cyx
* ������1������DeleteLogEx��DeleteLog�������⣬���Ľ��������ܡ�
*       2������WriteLogEx�������⡣
*
* �汾��1.0.5
* ���ڣ�2011-11-04
* ���ߣ�Raylee
* �������������漰�ļ������ĺ�������
*
* �汾��1.0.4
* ���ڣ�2011-07-25
* ���ߣ�Raylee
* ���������DeleteLogEx�ӿڣ����Զ���·��
*
* �汾��1.0.3
* ���ڣ�2011-06-25
* ���ߣ�Raylee
* ���������WriteLogEx�ӿڣ����Զ���·��
*
* �汾��1.0.2
* ���ڣ�2010-06-18
* ���ߣ�Raylee
* ��������_wfopen_s�滻_wfopen��ȥ��warning
*
* �汾��1.0.1
* ���ڣ�2010-06-01
* ���ߣ�Raylee
* ������1������д��־�ӿ�
*		2��������־ɾ������
*
* �汾��1.0.0
* ���ڣ�2010-05-24
* ���ߣ�Raylee
* ����������ʹ�ã�һ��һ����־�ļ���������Ϊ�ļ�����һ��һ����־��¼
*/

#pragma once

#ifndef NHLOGAPI_H
#define NHLOGAPI_H

#define LOG_ERR		L"����"
#define LOG_EXP		L"�쳣"
#define LOG_MSG		L"��Ϣ"

class CNHLogAPI
{
public:
	CNHLogAPI(void);
	virtual ~CNHLogAPI(void);
	CNHLogAPI(const CNHLogAPI &);
	CNHLogAPI & operator =(const CNHLogAPI &);

public:
	// д����־
	// wchType ��־���ͣ��Ѷ��峣�ú�LOG_ERR/LOG_EXP/LOG_MSG
	// wchContent ��־���� 
	static DWORD WriteLog(const wchar_t wchType[], const wchar_t wchModule[], const wchar_t wchContent[]);
	// ��WriteLog��һ��·������
	static DWORD WriteLogEx(const wchar_t wchFilePath[], const wchar_t wchType[], const wchar_t wchModule[], const wchar_t wchContent[]);
	// ������־�ļ�������޸�ʱ�䣬ɾ��ĳʱ��֮ǰ������ʱ�̣�����־�ļ�
	static DWORD DeleteLog(const SYSTEMTIME &st);
	// ������־�ļ�������޸�ʱ�䣬ɾ��ĳʱ��֮ǰ������ʱ�̣�����־�ļ�, ��ָ����־�ļ������ļ��У��磺��D:\LOG��
	static DWORD DeleteLogEx(const wchar_t wchFileFolder[], const SYSTEMTIME &st);

	// �ٽ�����װ��
	class CSLock:public CRITICAL_SECTION
	{
	public:
		CSLock()
		{
			InitializeCriticalSection(this);
		}

		~CSLock()
		{
			DeleteCriticalSection(this);
		}

		void Enter()
		{
			EnterCriticalSection(this);
		}

		void Leave()
		{
			LeaveCriticalSection(this);
		}
	};

	// �Զ������Զ���������
	class CAutoLock
	{
	public:
		CAutoLock(CSLock& lock)
			:m_csLock(lock)
		{
			Lock();
		}
		~CAutoLock()
		{
			UnLock();
		}

	public:
		// һ�㲻�ֶ�����
		void Lock()
		{
			m_csLock.Enter();
		}

		// һ�㲻�ֶ�����
		void UnLock()
		{
			m_csLock.Leave();
		}

	private:
		CSLock& m_csLock;
	};
	
	static CSLock & GetLogLocker();
};

#endif