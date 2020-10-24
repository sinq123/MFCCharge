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
	// ���ӷ�����
	// (in)pwchIPAddress, ������IP��ַ����ʽ:xxx.xxx.xxx.xxx
	// (in)nPort,�������˿ڣ���Χ��1��65535
	// ���غ���ִ�н����
	// ture���ɹ�
	// flase��ʧ��
	bool Connect(const wchar_t * pwchIPAddress, const int nPort);

	// �Ƿ��Ѿ�����������
	// ���غ���ִ�н����
	// ture����
	// flase����
	bool IsConnect(void);

	// �Ͽ������������
	// ���غ���ִ�н����
	// ��
	void Disconnect(void);

	// ��������
	// (in)pBytes, ����
	// (in)size�����ݳ���
	// ���غ���ִ�н����
	// ��
	void Send(const BYTE *pBytes, const size_t size);

	// �������ݷ��ػص�����
	// (in)����ָ��
	// (out)pBytes������
	// (out)size�����ݳ���
	// ���غ���ִ�н����
	// ��
	void SetOnReadCallBack(void (CALLBACK* pfOnReadCallBack)(const BYTE* pBytes, const size_t size));

	// �������ӷ��ػص�����
	// (in)����ָ��
	// (out)bSuccess�������Ƿ�ɹ���true���ɹ���false��ʧ��
	// ���غ���ִ�н����
	// ��
	void SetOnConnectCallBack(void (CALLBACK* pfOnConnectCallBack)(const bool bSuccess));

	// ���öϿ����ӻص�����
	// (in)����ָ��
	// ���غ���ִ�н����
	// ��
	void SetOnDisconnectCallBack(void (CALLBACK* pfOnDisConnectCallBack)(void));

private:
	CNHNetClientIMPL* m_pNHNetClientIMPL;
};

#endif
