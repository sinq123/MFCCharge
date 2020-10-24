#pragma once

class CNHNetClientIMPL;

#ifndef NHNETCLIENT_H
#define NHNETCLIENT_H

#ifdef DLL_FILE
class _declspec(dllexport) CNHNetClient
#else
class _declspec(dllimport) CNHNetClient
#endif
{
public:
	CNHNetClient(void);
	virtual ~CNHNetClient(void);

public:
	// 连接服务器
	// (in)pwchIPAddress, 服务器IP地址，格式:xxx.xxx.xxx.xxx
	// (in)nPort,服务器端口，范围：1～65535
	// 返回函数执行结果：
	// ture，成功
	// flase，失败
	bool Connect(const wchar_t * pwchIPAddress, const int nPort);

	// 是否已经服务器连接
	// 返回函数执行结果：
	// ture，是
	// flase，否
	bool IsConnect(void);

	// 断开与服务器连接
	// 返回函数执行结果：
	// 无
	void Disconnect(void);

	// 发送数据
	// (in)pBytes, 数据
	// (in)size，数据长度
	// 返回函数执行结果：
	// 无
	void Send(const BYTE *pBytes, const size_t size);

	// 设置数据返回回调函数
	// (in)函数指针
	// (out)pBytes，数据
	// (out)size，数据长度
	// 返回函数执行结果：
	// 无
	void SetOnReadCallBack(void (CALLBACK* pfOnReadCallBack)(const BYTE* pBytes, const size_t size));

	// 设置连接返回回调函数
	// (in)函数指针
	// (out)bSuccess，连接是否成功，true：成功，false：失败
	// 返回函数执行结果：
	// 无
	void SetOnConnectCallBack(void (CALLBACK* pfOnConnectCallBack)(const bool bSuccess));

	// 设置断开连接回调函数
	// (in)函数指针
	// 返回函数执行结果：
	// 无
	void SetOnDisconnectCallBack(void (CALLBACK* pfOnDisConnectCallBack)(void));

private:
	CNHNetClientIMPL* m_pNHNetClientIMPL;
};

#endif
