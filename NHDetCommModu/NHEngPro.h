#ifndef NHENGPRO_H
#define NHENGPRO_H

// ������Ŀ��������
#ifndef ENG_PRO_STD
//#define ENG_PRO_STD
#endif

// ������Ŀ����Ħ�г�
#ifndef ENG_PRO_MOTO
#define ENG_PRO_MOTO
#endif

// ������Ŀ�����ۼ�
#ifndef ENG_PRO_MFD
//#define ENG_PRO_MFD
#endif

// ���ź�(�����ŷŲ�������־��ѯ�е����ж�)
//(NHBMS.h �� NetWorkDetectionDlg.h��NetWorkDetThread.hͬ���޸�)
// ������Ŀ�������޳�
#ifndef ENG_PRO_ARP
//#define ENG_PRO_ARP
#endif

// ������Ŀ�������ۼ����һ
#ifndef ENG_PRO_SMD
#define ENG_PRO_SMD
#endif

//#ifndef ENG_STA_JYAT
//#define ENG_STA_JYAT //����������ͨ�����⹦��(1��δ��⶯���Ի��ͺ�ʱ,NHCDS���򿪲⹦������,�Ա㲻�˳�NHCDS,��ֱ�Ӽ컷�����ؼ���;2���������ܺ�,����������Ŀ,����ǰ���˻�����̨����,�����ܺ�����̫��,���������ʱ,ǰ���ѹ���������)
//#endif

#ifndef ENG_STA_YGZST
#define ENG_STA_YGZST
#endif

//#ifndef ENG_STA_JMDQ //�������
//#define ENG_STA_JMDQ
//#endif

const wchar_t * const ENG_PRO_NAME = L"GDSTDNHSMDS";	// ������Ŀ��
const wchar_t * const ENG_PRO_NAME_EX = L"����׼��";	// ������Ŀ��
const wchar_t * const ENG_PRO_VERSION = L"2.1.0";  // ����汾

// �ۼ챨�浥���ǰ9λ
//const wchar_t * const MFD_STA_NUM = L"440605000"; // �ۼ���վǰ9λ��ţ�6λ��������+3λ����������룩
const wchar_t * const MFD_STA_NUM = L"440982"; // �ۼ���վǰ9λ��ţ�6λ��������+3λ����������룩

#endif