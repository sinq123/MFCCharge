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
	// ���з���
	// (in)nPort,�������˿ڣ���Χ��1��65535
	// ���غ���ִ�н����
	// ture���ɹ�
	// flase��ʧ��
	bool Run(const unsigned int nPort);

	// �Ƿ��������з���
	// ���غ���ִ�н����
	// ture����
	// flase����
	bool IsRun(void);

	// ֹͣ����
	// ���غ���ִ�н����
	// ��
	void Stop(void);

	// ��������
	// (in)pwchIP, �ͻ���IP��ַ
	// (in)pBytes, ����
	// (in)size�����ݳ���
	// ���غ���ִ�н����
	// ��
	void Send(const wchar_t* pwchIP, const BYTE* pBytes, const size_t size);

	// �Ͽ��ͻ�������
	// (in)pwchIP, �ͻ���IP��ַ
	// ���غ���ִ�н����
	// ��
	void Disconnect(const wchar_t* pwchIP);

	// �ͻ����Ƿ��Ѿ�����
	// (in)pwchIP, �ͻ���IP��ַ
	// ���غ���ִ�н����
	// ture����
	// flase����
	bool IsConnect(const wchar_t* pwchIP);

	// �������ݷ��ػص�����
	// (in)����ָ��
	// (out)pwchIP���ͻ���IP��ַ
	// (out)pBytes������
	// (out)size�����ݳ���
	// ���غ���ִ�н����
	// ��
	void SetOnReadCallBack(void (CALLBACK* pfOnReadCallBack)(const wchar_t* pwchIP, const BYTE* pBytes, const size_t size));

	// ���ÿͻ������ӷ��ػص�����
	// (in)����ָ��
	// (out)pwchIP���ͻ���IP��ַ
	// ���غ���ִ�н����
	// ��
	void SetOnConnectCallBack(void (CALLBACK* pfOnConnectCallBack)(const wchar_t* pwchIP));

	// ���ÿͻ��˶Ͽ����ӻص�����
	// (in)����ָ��
	// (out)pwchIP���ͻ���IP��ַ
	// ���غ���ִ�н����
	// ��
	void SetOnDisconnectCallBack(void (CALLBACK* pfOnDisConnectCallBack)(const wchar_t* pwchIP));

private:
	CNHNetServerIMPL* m_pNHNetServerIMPLL;
};

#endif