#ifndef UPGADEFINITION_H
#define UPGADEFINITION_H

#include <string>

// �ӿ���Ϣ
struct SGAWebService
{
	// �����ӿڰ汾��Ĭ�ϣ�1��1��V1.0��2��V2.0��3��V3.0
	int nVersion;
	// WebService��ַ
	CString strURL;
	// �ӿ����к�
	CString strIFSN;
	// ����������
	CString strStationNum;
	// �����������
	CString strStationName;
	// ����߱��
	CString strLineNum;
	// ��λ�����豸���
	CString strPosEquNum;
	// Ӧ�ó������
	CString strCjsqbh;
	// ��λ��������
	CString strDwjgdm;
	// ��λ����
	CString strDwmc;
	// �û���ʶ
	CString strYhbz;
	// �û�����
	CString strYhxm;
	// �ն˱�ʶ
	CString strZdbs;
};

// ������������Ϣ
struct SUpGAMsg
{
	// ��ǣ�1�ɹ���С��0ʧ�ܣ�$EΪϵͳ�쳣
	std::wstring code;
	// ������Ϣ
	std::wstring message;
	std::wstring PDALineNum;
};

// ͼƬ�ϴ�����
struct SUpGaPhoto
{
	// ������ˮ��
	std::wstring jylsh;
	// ����������
	std::wstring jyjgbh;
	// ����ߴ���
	std::wstring jcxdh;
	// �������
	std::wstring jycs;
	// ���ƺ���
	std::wstring hphm;
	// ��������
	std::wstring hpzl;
	// ����ʶ�����
	std::wstring clsbdh;
	// ��Ƭ·��
	std::wstring zplj;
	// ����ʱ��
	std::wstring pssj;
	// ������Ŀ
	std::wstring jyxm;
	// ��Ƭ����
	std::wstring zpzl;

};



#endif