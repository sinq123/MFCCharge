/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�AC_DATA_ROAD.h
* �ļ���ʶ��
* ������PDA·�����ݱ�ģ��
*
* �汾��1.0
* ���ڣ�2015-01-28
* ���ߣ�Shaojm
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0
* ���ڣ�2015-01-28
* ���ߣ�Shaojm
* ���������ڷ���
*/


#if !defined (AC_DATA_ROAD_H)
#define AC_DATA_ROAD_H

#include <string>

struct SAC_DATA_ROAD
{
	// ������ˮ��
	std::wstring jylsh;
	// ����������
	std::wstring jyjgbh;
	//����ߴ���
	std::wstring jcxdh;
	//�������
	std::wstring jycs;
	//���������
	std::wstring xh;
	//��������
	std::wstring hpzl;
	//���ƺ���
	std::wstring hphm;
	//��������
	std::wstring cllx;
	//����ʶ�����
	std::wstring clsbdh;
	//��ɱ�־
	std::wstring flag;
	//·��Ա����
	std::wstring lsy;
	//�г��ƶ����ٶ�
	std::wstring zdcsd;
	//�г��ƶ�Э��ʱ��
	std::wstring zdxtsj;
	//�г��ƶ��ȶ���
	std::wstring zdwdx;
	//�г������ƶ�����
	std::wstring xckzzdjl;
	//�г������ƶ�����
	std::wstring xcmzzdjl;
	//�г�����MFDD
	std::wstring xckzmfdd;
	//�г�����MFDD
	std::wstring xcmzmfdd;
	//�г��ƶ�̤����ֵ
	std::wstring xczdczlz;
	//�г�·���ƶ��ж�
	std::wstring lszdpd;
	//Ӧ���ƶ����ٶ�
	std::wstring yjzdcsd;
	//Ӧ�������ƶ�����
	std::wstring yjkzzdjl;
	//Ӧ������MFDD
	std::wstring yjkzmfdd;
	//Ӧ�������ƶ�����
	std::wstring yjmzzdjl;
	//Ӧ������MFDD
	std::wstring yjmzmfdd;
	//Ӧ����������ʽ
	std::wstring yjzdczlfs;
	//Ӧ��������ֵ
	std::wstring yjzdczlz;
	//Ӧ��·���ƶ��ж�
	std::wstring yjzdpd;
	//פ���¶�
	std::wstring zcpd;
	//·��פ���ƶ��ж�
	std::wstring lszczdpd;
	//���ٱ�ʵ��ֵ
	std::wstring csdscz;
	//���ٱ��ж�
	std::wstring csbpd;
	//·�Խ��
	std::wstring lsjg;
};

#endif