#pragma once

class CNHCerFunc
{
public:
	CNHCerFunc(void);
	virtual ~CNHCerFunc(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CNHCerFunc(const CNHCerFunc &);
	CNHCerFunc & operator =(const CNHCerFunc &);

public:
	// ��ȡӲ�����к�
	static bool GetHddSN(CString& strHddSN);

	// ��֤Ӳ��֤��
	// strMsg �����ش���򾯸���Ϣ
	// ����ֵ ��true��֤�ɹ���false��֤ʧ��
	static bool ChkHddCer(CString& strMsg);

	// ��֤����汾
	// strMsg �����ش���򾯸���Ϣ
	// ����ֵ ��true��֤�ɹ���false��֤ʧ��
	static bool ChkProVer(CString& strMsg);
};

