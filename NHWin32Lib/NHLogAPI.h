/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：NHLogAPI.h
* 文件标识：
* 描述：日志记录
*
* 版本：1.0
* 作者：Raylee
* 日期：2010-05-24
*
* 历史信息：
*
* 版本：1.0.6
* 日期：2012-09-01
* 作者：Cyx
* 描述：1）修正DeleteLogEx和DeleteLog函数问题，并改进函数功能。
*       2）修正WriteLogEx乱码问题。
*
* 版本：1.0.5
* 日期：2011-11-04
* 作者：Raylee
* 描述：对所有涉及文件操作的函数加锁
*
* 版本：1.0.4
* 日期：2011-07-25
* 作者：Raylee
* 描述：添加DeleteLogEx接口，可自定义路径
*
* 版本：1.0.3
* 日期：2011-06-25
* 作者：Raylee
* 描述：添加WriteLogEx接口，可自定义路径
*
* 版本：1.0.2
* 日期：2010-06-18
* 作者：Raylee
* 描述：用_wfopen_s替换_wfopen，去掉warning
*
* 版本：1.0.1
* 日期：2010-06-01
* 作者：Raylee
* 描述：1、改良写日志接口
*		2、增加日志删除功能
*
* 版本：1.0.0
* 日期：2010-05-24
* 作者：Raylee
* 描述：发布使用，一天一个日志文件，以日期为文件名，一行一条日志记录
*/

#pragma once

#ifndef NHLOGAPI_H
#define NHLOGAPI_H

#define LOG_ERR		L"错误"
#define LOG_EXP		L"异常"
#define LOG_MSG		L"信息"

class CNHLogAPI
{
public:
	CNHLogAPI(void);
	virtual ~CNHLogAPI(void);
	CNHLogAPI(const CNHLogAPI &);
	CNHLogAPI & operator =(const CNHLogAPI &);

public:
	// 写入日志
	// wchType 日志类型，已定义常用宏LOG_ERR/LOG_EXP/LOG_MSG
	// wchContent 日志内容 
	static DWORD WriteLog(const wchar_t wchType[], const wchar_t wchModule[], const wchar_t wchContent[]);
	// 比WriteLog多一个路径参数
	static DWORD WriteLogEx(const wchar_t wchFilePath[], const wchar_t wchType[], const wchar_t wchModule[], const wchar_t wchContent[]);
	// 根据日志文件的最近修改时间，删除某时刻之前（含该时刻）的日志文件
	static DWORD DeleteLog(const SYSTEMTIME &st);
	// 根据日志文件的最近修改时间，删除某时刻之前（含该时刻）的日志文件, 需指定日志文件所在文件夹，如：“D:\LOG”
	static DWORD DeleteLogEx(const wchar_t wchFileFolder[], const SYSTEMTIME &st);

	// 临界区封装类
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

	// 自动锁，自动落锁解锁
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
		// 一般不手动调用
		void Lock()
		{
			m_csLock.Enter();
		}

		// 一般不手动调用
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