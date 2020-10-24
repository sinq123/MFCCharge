#pragma once

class CNHNetServerIMPL;

#ifndef NHNETSERVER_H
#define NHNETSERVER_H

#ifdef DLL_FILE
class _declspec(dllexport) CNHNetServer
#else
class _declspec(dllimport) CNHNetServer
#endif
{
public:
	CNHNetServer(void);
	virtual ~CNHNetServer(void);

public:
	// 运行服务
	// (in)nPort,服务器端口，范围：1～65535
	// 返回函数执行结果：
	// ture，成功
	// flase，失败
	bool Run(const unsigned int nPort);

	// 是否正在运行服务
	// 返回函数执行结果：
	// ture，是
	// flase，否
	bool IsRun(void);

	// 停止服务
	// 返回函数执行结果：
	// 无
	void Stop(void);

	// 发送数据
	// (in)pwchIP, 客户端IP地址
	// (in)pBytes, 数据
	// (in)size，数据长度
	// 返回函数执行结果：
	// 无
	void Send(const wchar_t* pwchIP, const BYTE* pBytes, const size_t size);

	// 断开客户端连接
	// (in)pwchIP, 客户端IP地址
	// 返回函数执行结果：
	// 无
	void Disconnect(const wchar_t* pwchIP);

	// 客户端是否已经连接
	// (in)pwchIP, 客户端IP地址
	// 返回函数执行结果：
	// ture，是
	// flase，否
	bool IsConnect(const wchar_t* pwchIP);

	// 设置数据返回回调函数
	// (in)函数指针
	// (out)pwchIP，客户端IP地址
	// (out)pBytes，数据
	// (out)size，数据长度
	// 返回函数执行结果：
	// 无
	void SetOnReadCallBack(void (CALLBACK* pfOnReadCallBack)(const wchar_t* pwchIP, const BYTE* pBytes, const size_t size));

	// 设置客户端连接返回回调函数
	// (in)函数指针
	// (out)pwchIP，客户端IP地址
	// 返回函数执行结果：
	// 无
	void SetOnConnectCallBack(void (CALLBACK* pfOnConnectCallBack)(const wchar_t* pwchIP));

	// 设置客户端断开连接回调函数
	// (in)函数指针
	// (out)pwchIP，客户端IP地址
	// 返回函数执行结果：
	// 无
	void SetOnDisconnectCallBack(void (CALLBACK* pfOnDisConnectCallBack)(const wchar_t* pwchIP));

private:
	CNHNetServerIMPL* m_pNHNetServerIMPLL;
};

#endif