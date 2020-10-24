#ifndef GACONSTDEF_H
#define GACONSTDEF_H

#include <string>

#include "../NHDetCommModu/NHEngPro.h"
// �������ƶ�Ӧ�⡢��
const wchar_t * const GA_MAIN_LIGHT_NAME = L"��";  
const wchar_t * const GA_MINOR_LIGHT_NAME = L"��"; 
const wchar_t * const GA_LEFT_MAIN_LIGHT_CODE = L"H1";  
const wchar_t * const GA_LEFT_MINOR_LIGHT_CODE = L"H2";
const wchar_t * const GA_RIGHT_MAIN_LIGHT_CODE = L"H4";  
const wchar_t * const GA_RIGHT_MINOR_LIGHT_CODE = L"H3";  

//// �������ƶ�Ӧ�ڡ���
//const wchar_t * const GA_MAIN_LIGHT_NAME = L"��";  
//const wchar_t * const GA_MINOR_LIGHT_NAME = L"��"; 
//const wchar_t * const GA_LEFT_MAIN_LIGHT_CODE = L"H2";  
//const wchar_t * const GA_LEFT_MINOR_LIGHT_CODE = L"H1";
//const wchar_t * const GA_RIGHT_MAIN_LIGHT_CODE = L"H3";  
//const wchar_t * const GA_RIGHT_MINOR_LIGHT_CODE = L"H4";  

// �����Ŀ��Str����
const wchar_t * const DET_ITEM_NULL = L"EMP";  

typedef struct RBPD_1
{
	// ���
	int nNum;
	// ���ƶ���
	int nLBrake;
	// ���ƶ���
	int nRBrake;

	RBPD_1(){ZeroMemory(this, sizeof(RBPD_1));}

}RollerBrakeProcessData_1,*PRollerBrakeProcessData_1;

// ������������Ϣ
struct SGAMsg
{
	// ��ǣ�1�ɹ���С��0ʧ�ܣ�$EΪϵͳ�쳣
	std::wstring code;
	// ������Ϣ
	std::wstring message;
	std::wstring PDALineNum;
};

// �������������Ϣ
struct SGAStationRecordInfo
{
	// ���������� 
	std::wstring jczbh;
	// ����������� 
	std::wstring jczmc;
	// �Ƿ��빫��������  
	std::wstring sflw;
	// �ʸ����֤����  
	std::wstring rdsbh;
	// �ʸ������Ч��ʼ 
	std::wstring rdyxqs;
	// �ʸ������Ч��ֹ 
	std::wstring rdyxqz;
	// ����ռ������(������)
	std::wstring shejirjcnl;
	// ʵ���ռ������(������)
	std::wstring shijirjcnl;
	// �����Ա���� 
	std::wstring jcryzs;
	// ��칤λ���� 
	std::wstring wjgwrs;
	// ¼�빤λ����  
	std::wstring lrgwrs;
	// ����Ա���� 
	std::wstring ycyrs;
	// ���̹�λ����
	std::wstring dpgwrs;
	// �ܼ칤λ����
	std::wstring zjgwrs;
	// ������λ���� 
	std::wstring qtgwrs;
	// ͨ��ʡ���ʼ첿�ſ������� 
	std::wstring tgszjbmkhrs;
	// δͨ��ʡ���ʼ첿�ſ�������
	std::wstring wtgszjbmkhrs;
	// ��֤����  
	std::wstring fzjg;
	// ������ 
	std::wstring glbm;
	// ��������  
	std::wstring gxrq;
	// ��ע  
	std::wstring bz;
	// ����ռ������(Ħ����)  
	std::wstring shejirjcmtsl;
	// ʵ���ռ������(Ħ����) 
	std::wstring shijirjcmtsl;
	// ��˱��  
	std::wstring shbj;
	// ʹ�ù�����  
	std::wstring syglbm;
	// ������ 
	std::wstring shyj;
	// ״̬��� 
	std::wstring zt;
	// ��ͣԭ�� 
	std::wstring ztyy;
	// ��λ��ַ  
	std::wstring dwdz;
	// �������� 
	std::wstring yzbm;
	// ��ɼ��鷶Χ 
	std::wstring xkjyfw;
	// �ʸ���ɷ��ŵ�λ
	std::wstring rdsffdw;
	// ���˴���  
	std::wstring frdb;
	// ���˴������֤��  
	std::wstring frdbsfzh;
	// ���˴�����ϵ�绰  
	std::wstring frdblxdh;
	// ������  
	std::wstring fzr;
	// ���������֤�� 
	std::wstring fzrsfzh;
	// ��������ϵ�绰  
	std::wstring fzrlxdh;
	// �ճ���ϵ�� 
	std::wstring rclxr;
	// �ճ���ϵ�����֤��
	std::wstring rclxrsfzh;
	// �ճ���ϵ����ϵ�绰  
	std::wstring rclxrlxdh;
};

// ����߱�����Ϣ
struct SGALineRecordInfo
{
	// ����������    
	std::wstring jczbh;
	// ����ߴ���   
	std::wstring jcxxh;
	// ����������� 
	std::wstring jczmc;
	// ���������  
	std::wstring jcxmc;
	// ��������  
	std::wstring jcxlb;
	// ����߿��Ʒ�ʽ  
	std::wstring jcxczfs;
	// �ƶ�����豸����  
	std::wstring zdsbmc;
	// �ƶ�����豸�ͺ�   
	std::wstring zdsbxh;
	// �ƶ�����豸��������  
	std::wstring zdsbsccj;
	// �ƶ��������ʱ�� 
	std::wstring zdjcsj;
	// �ƶ���ⷽʽ  
	std::wstring zdjcfs;
	// ƽ����ʽ  
	std::wstring pbzs;
	// ��ƽ�峤��  
	std::wstring dpbcd;
	// ƽ����  
	std::wstring pbjj;
	// ��Ͳʽ�ƶ�̨��ʽ   
	std::wstring gtszdtzs;
	// ��Ͳʽ�ƶ�̨ͣ����ʽ   
	std::wstring gtszdttjfs;
	// �ƶ�����豸����ʱ��  
	std::wstring zdsbqysj;
	// �ƶ�����豸�춨��Ч��ֹ 
	std::wstring zdsbjdyxqz;
	// �ƶ�����豸״̬
	std::wstring zdsbzt;
	// �ƹ����豸���� 
	std::wstring dgsbmc;
	// �ƹ����豸�ͺ�  
	std::wstring dgsbxh;
	// �ƹ����豸��������  
	std::wstring dgsbsccj;
	// �ƹ�������ʱ��   
	std::wstring dgjcsj;
	// �ƹ��ⷽʽ 
	std::wstring dgjcfs;
	// �ƹ����Ƿ��г���ƫ����������   
	std::wstring dgcspyxz;
	// �ƹ����豸����ʱ��  
	std::wstring dgsbqysj;
	// �ƹ����豸�춨��Ч��ֹ  
	std::wstring dgsbjdyxqz;
	// �ƹ����豸״̬ 
	std::wstring dgsbzt;
	// �ٶȼ���豸���� 
	std::wstring sdsbmc;
	// �ٶȼ���豸�ͺ�  
	std::wstring sdsbxh;
	// �ٶȼ���豸��������  
	std::wstring sdsbsccj;
	// �ٶȼ������ʱ�� 
	std::wstring sdjcsj;
	// �ٶȼ���豸����ʱ��  
	std::wstring sdsbqysj;
	// �ٶȼ���豸�춨��Ч��ֹ  
	std::wstring sdsbjdyxqz;
	// �ٶȼ���豸״̬   
	std::wstring sdsbzt;
	// �໬����豸����  
	std::wstring chsbmc;
	// �໬����豸�ͺ�  
	std::wstring chsbxh;
	// �໬����豸��������   
	std::wstring chsbsccj;
	// �໬�������ʱ��  
	std::wstring chjcsj;
	// �໬����豸����ʱ��  
	std::wstring chsbqysj;
	// �໬����豸�춨��Ч��ֹ  
	std::wstring chsbjdyxqz;
	// �໬����豸״̬   
	std::wstring chsbzt;
	// �����豸����   
	std::wstring czsbmc;
	// ���ؼ���豸�ͺ�    
	std::wstring czsbxh;
	// ���ؼ���豸��������   
	std::wstring czsbsccj;
	// ���ؼ������ʱ��  
	std::wstring czjcsj;
	// ���ط�Χ   
	std::wstring czjb;
	// ���ؼ���豸�춨��Ч��ֹ   
	std::wstring czsbjdyxqz;
	// ���ؼ���豸����ʱ��   
	std::wstring czsbqysj;
	// ���ؼ���豸״̬  
	std::wstring czsbzt;
	// ȫ�߼��ʱ��  
	std::wstring qxjcsj;
	// ��λ1  
	std::wstring gw1;
	// ��λ2 
	std::wstring gw2;
	// ��λ3  
	std::wstring gw3;
	// ��λ4  
	std::wstring gw4;
	// ��λ5  
	std::wstring gw5;
	// ��λ6  
	std::wstring gw6;
	// ��λ7  
	std::wstring gw7;
	// ��λ8  
	std::wstring gw8;
	// ��λ9  
	std::wstring gw9;
	// ��ע 
	std::wstring bz;
	// ��֤����  
	std::wstring fzjg;
	// ������ 
	std::wstring glbm;
	// ��������   
	std::wstring gxrq;
	// �ƶ������豸���  
	std::wstring zdsbbh;
	// �ƶ������豸�춨/У׼֤����   
	std::wstring zdsbjdzsbh;
	// �ƹ�����豸��� 
	std::wstring dgsbbh;
	// �ƹ����豸�춨/У׼֤����   
	std::wstring dgsbjdzsbh;
	// �ٶȼ����豸���  
	std::wstring sdsbbh;
	// �ٶȼ����豸�춨/У׼֤����  
	std::wstring sdsbjdzsbh;
	// �໬�����豸���  
	std::wstring chsbbh;
	// �໬�����豸�춨/У׼֤����  
	std::wstring chsbjdzsbh;
	// ���ؼ����豸���
	std::wstring czsbbh;
	// ���ؼ����豸�춨/У׼֤���� 
	std::wstring czsbjdzsbh;
	// ״̬���  
	std::wstring zt;
	// ��ͣԭ��  
	std::wstring ztyy;
};

// ����ҵ����Ϣϵͳ������Ϣ
struct SGABISRecordInfo
{
	// ������� 
	std::wstring babh;
	// ����ϵͳ���� 
	std::wstring jyxtmc;
	// ����ϵͳ˵��  
	std::wstring jyxtsm;
	// �汾���
	std::wstring bbbh;
	// ������λ
	std::wstring kfdw;
	// ���ݿ�汾 
	std::wstring sjkbb;
	// ϵͳ�ܹ����� 
	std::wstring xtjgms;
	// ���������� 
	std::wstring jczbh;
	// ����ߴ��� 
	std::wstring jcxxh;
	// ���ʱ�� 
	std::wstring jcsj;
	// ����ʱ�� 
	std::wstring yssj;
	// ʹ��״̬ 
	std::wstring syzt;
	// ��ͣԭ��  
	std::wstring ztyy;
	// ������ 
	std::wstring jbr;
	// ��˱�� 
	std::wstring shbj;
	// ������ 
	std::wstring shyj;
	// ����� 
	std::wstring shr;
	// ���ʱ�� 
	std::wstring shsj;
	// ��֤����
	std::wstring fzjg;
	// ������
	std::wstring glbm;
	// �������� 
	std::wstring gxsj;
	// ʹ�ù�����  
	std::wstring syglbm;
};

// ������������Ϣ
struct SGAVehBaseInfo
{
	// ���������
	std::wstring xh;
	// ��������
	std::wstring hpzl;
	// ���ƺ���
	std::wstring hphm;
	// ����Ʒ��
	std::wstring clpp1;
	// �����ͺ�
	std::wstring clxh;
	// Ӣ��Ʒ��
	std::wstring clpp2;
	// ����/����
	std::wstring gcjk;
	// �����
	std::wstring zzg;
	// ���쳧����
	std::wstring zzcmc;
	// ����ʶ�����
	std::wstring clsbdh;
	// ��������
	std::wstring fdjh;
	// ��������
	std::wstring cllx;
	// ������ɫ
	std::wstring csys;
	// ʹ������
	std::wstring syxz;
	// ���֤������
	std::wstring sfzmhm;
	// ���֤������
	std::wstring sfzmmc;
	// ������������
	std::wstring syr;
	// ���εǼ�����
	std::wstring ccdjrq;
	// �����������
	std::wstring djrq;
	// ������Ч��ֹ
	std::wstring yxqz;
	// ǿ�Ʊ�����ֹ
	std::wstring qzbfqz;
	// ��֤����
	std::wstring fzjg;
	// ������
	std::wstring glbm;
	// ������ֹ����
	std::wstring bxzzrq;
	// ������״̬
	std::wstring zt;
	// ��Ѻ���0-δ��Ѻ��1-�ѵ�Ѻ
	std::wstring dybj;
	// �������ͺ�
	std::wstring fdjxh;
	// ȼ������
	std::wstring rlzl;
	// ����
	std::wstring pl;
	// ����
	std::wstring gl;
	// ת����ʽ
	std::wstring zxxs;
	// ��������
	std::wstring cwkc;
	// ��������
	std::wstring cwkk;
	// ��������
	std::wstring cwkg;
	// �����ڲ�����
	std::wstring hxnbcd;
	// �����ڲ����
	std::wstring hxnbkd;
	// �����ڲ��߶�
	std::wstring hxnbgd;
	// �ְ嵯��Ƭ��
	std::wstring gbthps;
	// ����
	std::wstring zs;
	// ���
	std::wstring zj;
	// ǰ�־�
	std::wstring qlj;
	// ���־�
	std::wstring hlj;
	// ��̥���
	std::wstring ltgg;
	// ��̥��
	std::wstring lts;
	// ������
	std::wstring zzl;
	// ��������
	std::wstring zbzl;
	// �˶�������
	std::wstring hdzzl;
	// �˶��ؿ�
	std::wstring hdzk;
	// ׼ǣ��������
	std::wstring zqyzl;
	// ��ʻ��ǰ���ؿ�����
	std::wstring qpzk;
	// ��ʻ�Һ����ؿ�����
	std::wstring hpzk;
	// ����������
	std::wstring hbdbqk;
	// ��������
	std::wstring ccrq;
	// ������;
	std::wstring clyt;
	// ��;����
	std::wstring ytsx;
	// ��ʻ֤֤о���
	std::wstring xszbh;
	// ����ϸ��־
	std::wstring jyhgbzbh;
	// ����Ͻ��
	std::wstring xzqh;
	// ס����ַ��������
	std::wstring zsxzqh;
	// ��ϵ��ַ��������
	std::wstring zzxzqh;
	// �¹ʳ����˲�λ���
	std::wstring sgcssbwqk;
	// �Ƿ����
	std::wstring sfmj;
	// �����ԭ��
	std::wstring bmjyy;
};

// �������������Ա������Ϣ
struct SGAStaffRecordInfo
{
	// ���֤������
	std::wstring sfzmhm;
	// ����
	std::wstring xm;
	// ��Ա���
	std::wstring rylb;
	// ������
	std::wstring glbm;
	// ��֤����
	std::wstring fzjg;
	// ����������
	std::wstring jczbh;
	// ��������
	std::wstring gxrq;
	// ��ע
	std::wstring bz;
	// ��˱��
	std::wstring shbj;
	// ������
	std::wstring shyj;
	// ״̬���
	std::wstring zt;
	// �ϸ�֤���
	std::wstring sgzbh;
	// �ϸ�֤��Ч��ֹ
	std::wstring sgzyxqz;
	// �ϸ�֤���ŵ�λ
	std::wstring sgzffdw;
	// ʹ�ù�����
	std::wstring syglbm;
};

// ������������˲�ͨ��ԭ��
struct SGAVehNoPassReason
{
	// ������ˮ�� 
	std::wstring jylsh;
	// ���������� 
	std::wstring jyjgbh;
	// �������� 
	std::wstring hpzl;
	// ���ƺ��� 
	std::wstring hphm;
	// ��˽�� 
	std::wstring shjg;
	// ���ϸ������Ŀ
	std::wstring bhgcyxm;
	// ���ϸ���ۼ�����Ƭ  
	std::wstring bhgcyzp;
	// ���ϸ���ۼ�����Ŀ
	std::wstring bhgwgjyxm;
	// ���ϸ���̼�����Ŀ
	std::wstring bhgdpjyxm;
	// ���ϸ���̶�̬������Ŀ  
	std::wstring bhgdtdpjyxm;
	// ���ϸ������Ŀ  
	std::wstring bhgjyxm;
	// ���ϸ�������Ƭ 
	std::wstring bhgzlzp;
	// ���ϸ�λ��Ƭ
	std::wstring bhggwzp;
	// ��˲�ͨ��ԭ������  
	std::wstring shbtgyy;
};

// ������������Ӧ������Ŀ��Ϣ
struct SGAVehTypeInfoItem
{
	// �����������
	std::wstring clsslb;
	// ���������������
	std::wstring clsslbmc;
	// �������Ŀ����
	std::wstring xjyxmdh;
	// ��׼���ݱ��
	std::wstring bzyjbj;
};

// ��������Ӧ��������Ƭ���˹�������Ŀ��Ϣ
struct SGAVehPhotoAndManualItem
{
	// ������ˮ��
	std::wstring jylsh;
	// ����������
	std::wstring jyjgbh;
	// ���ƺ���
	std::wstring hphm;
	// ��������
	std::wstring hpzl;
	// ��ۼ�����Ƭ
	std::wstring wgjyzp;
	// ������Ƭ
	std::wstring zlzp;
	// ��ۼ�����Ŀ
	std::wstring wgjcxm;
	// ���̶�̬������Ŀ
	std::wstring dtdpjyxm;
	// ���̼�����Ŀ
	std::wstring dpjyxm;
	// �ж�����
	std::wstring pdyj;
	// �����豸������Ŀ
	std::wstring yqsbjyxm;
};

struct SGAReviewNoPassReson
{
	// ������ˮ��
	std::wstring jylsh;
	// ����������
	std::wstring jyjgbh;
	// ��������
	std::wstring hpzl;
	// ���ƺ���
	std::wstring hphm;
	// ��˽��
	std::wstring shjg;
	// ���ϸ���ۼ�����Ƭ
	std::wstring bhgcyzp;
	// ���ϸ���ۼ�����Ŀ
	std::wstring bhgwgjyxm;
	// ���ϸ���̼�����Ŀ
	std::wstring bhgdpjyxm;
	// ���ϸ���̶�̬������Ŀ
	std::wstring bhgdtdpjyxm;
	// ���ϸ������Ŀ
	std::wstring bhgjyxm;
	// ���ϸ�������Ƭ
	std::wstring bhgzlzp;
	// ���ϸ�λ��Ƭ
	std::wstring bhggwzp;
	// ��˲�ͨ��ԭ������
	std::wstring shbtgyy;
};

// ����ҵ����ˮ��
struct SGABusinessNum
{
	// ������ϵͳ��ˮ��
	std::wstring lsh;
	// �ۺ�Ӧ��ƽ̨������ˮ��
	std::wstring cglsh;
};

// ���������б���Ϣ
struct SlstNetVeh
{
	// ������ˮ��
	std::wstring jylsh;
	// ��������
	std::wstring hpzl;
	// ���ƺ���
	std::wstring hphm;
	// �������
	std::wstring jycs;
};

// ����������ԤԼ��Ϣ
struct SGAIEApptInfo
{
	// ��� 
	std::wstring xh;
	// ���������� 
	std::wstring jczbh;
	// �û����� 
	std::wstring yhdh;
	// �û����� 
	std::wstring yhlx;
	// �������� 
	std::wstring hpzl;
	// ���ƺ��� 
	std::wstring hphm;
	// ԤԼ������ 
	std::wstring xm;
	// �ֻ�����  
	std::wstring sjhm;
	// ԤԼ�� 
	std::wstring yym;
	// ԤԼ����  
	std::wstring yyrq;
	// ԤԼʱ�� 
	std::wstring yysd;
	// ԤԼʱ��˵��  
	std::wstring yysdsm;
	// ԤԼ����  
	std::wstring yylx;
	// ״̬ 
	std::wstring zt;
	// ��֤���� 
	std::wstring fzjg;
	// �������� 
	std::wstring gxsj;
	// ������ 
	std::wstring jybj;
	// ʵ�ʼ���ʱ�� 
	std::wstring sjjysj;
	// ʵ�ʼ������ 
	std::wstring sjjyjgbh;
	// ��������ˮ��  
	std::wstring lsh;
	// ������� 
	std::wstring czbj;
	// ԤԼ��ʼʱ�� 
	std::wstring ksjcsj;
	// ԤԼ����ʱ�� 
	std::wstring jsjcsj;
};

// ���������漼�������ı���Ϣ
struct SGAVehTecParaTxtInfo
{
	// ���������� 
	std::wstring veh_bh;
	// ����Ʒ��(����) 
	std::wstring veh_clpp1;
	// ����Ʒ��(Ӣ��) 
	std::wstring veh_clpp2;
	// �����ͺ� 
	std::wstring veh_clxh;
	// ��ҵID 
	std::wstring veh_qyid;
	// ������ַ 
	std::wstring veh_scdz;
	// �������ͺ�  
	std::wstring veh_fdjxh;
	// ʶ��������� 
	std::wstring veh_sbdhxl;
	// �������� 
	std::wstring veh_cllx;
	// ����� 
	std::wstring veh_zzg;
	// ת����ʽ 
	std::wstring veh_zxxs;
	// ȼ������ 
	std::wstring veh_rlzl;
	// ���� 
	std::wstring veh_pl;
	// ���� 
	std::wstring veh_gl;
	// ��������
	std::wstring veh_cwkc;
	// �������� 
	std::wstring veh_cwkk;
	// ��������
	std::wstring veh_cwkg;
	// �����ڲ����� 
	std::wstring veh_hxnbcd;
	// �����ڲ���� 
	std::wstring veh_hxnbkd;
	// �����ڲ��߶�  
	std::wstring veh_hxnbgd;
	// �ְ嵯��Ƭ��
	std::wstring veh_gbthps;
	// ����  
	std::wstring veh_zs;
	// ��� 
	std::wstring veh_zj;
	// ǰ�־� 
	std::wstring veh_qlj;
	// ���־� 
	std::wstring veh_hlj;
	// ��̥�� 
	std::wstring veh_lts;
	// ��̥��� 
	std::wstring veh_ltgg;
	// ������ 
	std::wstring veh_zzl;
	// �������� 
	std::wstring veh_zbzl;
	// ������� 
	std::wstring veh_hdzzl;
	// ׼ǣ�������� 
	std::wstring veh_zqyzl;
	// ��ؿ� 
	std::wstring veh_hdzk;
	// ��ʻ��ǰ������ 
	std::wstring veh_qpzk;
	// ��ʻ�Һ������� 
	std::wstring veh_hpzk;
	// ����
	std::wstring veh_pc;
	// ����ID 
	std::wstring veh_dpid;
	// ����������
	std::wstring veh_hbdbqk;
	// ���淢������ 
	std::wstring veh_cslx;
	// �������� 
	std::wstring veh_gxrq;
	// ��ע 
	std::wstring veh_bz;
	// ����������ҵ 
	std::wstring veh_zzcmc;
	// ���淢������
	std::wstring veh_ggrq;
	// �����
	std::wstring veh_sfmj;
	// ������Ч����
	std::wstring veh_cxsxrq;
	// ������ҵ���ͺ�
	std::wstring veh_dpqyxh;
	// ��Ʒ��� 
	std::wstring veh_cplb;
	// ���͹����� 
	std::wstring veh_clggbh;
	// �Ƿ�����ע�� 
	std::wstring veh_sfyxzc;
	// ������Ч���� 
	std::wstring veh_ggsxrq;
	// ������Ч�ڱ��
	std::wstring veh_ggyxqbj;
	// ������������
	std::wstring veh_cxggpc;
	// �������淢������ 
	std::wstring veh_cxggrq;
	// ֹͣ�������� 
	std::wstring veh_tzscrq;
	// ��Ч������ 
	std::wstring veh_yxqms;
	// ��Ƭ�� 
	std::wstring veh_zps;
	// �����Ч��ֹ 
	std::wstring veh_mjyxqz;
	// �����ʶ�ͺ�
	std::wstring veh_fgbsxh;
	// �����ʶ�̱�
	std::wstring veh_fgbssb;
	// �����ʶ��ҵ
	std::wstring veh_fgbsqy;
	// ���
	std::wstring veh_zh;
	// ����������ϵ�� 
	std::wstring veh_zzllyxs;
	// ��Ұ���������������� 
	std::wstring veh_bgazzdyxzzl;
	// �ӽ���ȥ��
	std::wstring veh_jjlqj;
	// ǰ������ 
	std::wstring veh_qxhx;
	// ��ʻ������  
	std::wstring veh_jsslx;
	// ������ʽ 
	std::wstring veh_cdxs;
	// ��߳���
	std::wstring veh_zgcs;
	// �ͺ� 
	std::wstring veh_yh;
	// ǰ�ƶ���ʽ 
	std::wstring veh_qzdfs;
	// ���ƶ���ʽ
	std::wstring veh_hzdfs;
	// ǰ�ƶ�������ʽ 
	std::wstring veh_qzdczfs;
	// ���ƶ�������ʽ 
	std::wstring veh_hzdczfs;
	// ��������ҵ 
	std::wstring veh_fdjqy;
	// �������̱� 
	std::wstring veh_fdjsb;
	// �Ƿ��������ϵͳ 
	std::wstring veh_ywabs;
	// �������� 
	std::wstring veh_clmc;
	// ��ҵ���� 
	std::wstring veh_qydm;
	// ������ 
	std::wstring veh_ggbj;
	// ����1 
	std::wstring veh_by1;
	// ����2 
	std::wstring veh_by2;
	// ����3 
	std::wstring veh_by3;
	// ����4 
	std::wstring veh_by4;
	// ����5 
	std::wstring veh_by5;

	// ���̹�����   
	std::wstring cha_bh;
	// ����ID   
	std::wstring cha_dpid;
	// ��ҵID  
	std::wstring cha_qyid;
	// ������ַ
	std::wstring cha_scdz;
	// �����ͺ� 
	std::wstring cha_dpxh;
	// ������� 
	std::wstring cha_dplb;
	// ��Ʒ���� 
	std::wstring cha_cpmc;
	// ��Ʒ�̱�  
	std::wstring cha_cpsb;
	// ������  
	std::wstring cha_c;
	// ������   
	std::wstring cha_k;
	// ������  
	std::wstring cha_g;
	// ȼ������ 
	std::wstring cha_rlzl;
	// ���ݱ�׼  
	std::wstring cha_yjbz;
	// ת����ʽ   
	std::wstring cha_zxxs;
	// ����  
	std::wstring cha_zs;
	// ���   
	std::wstring cha_zj;
	// �ְ嵯��Ƭ��
	std::wstring cha_gbthps;
	// ��̥�� 
	std::wstring cha_lts;
	// ��̥���  
	std::wstring cha_ltgg;
	// ǰ�־�  
	std::wstring cha_qlj;
	// ���־�  
	std::wstring cha_hlj;
	// ������  
	std::wstring cha_zzl;
	// �������� 
	std::wstring cha_zbzl;
	// ׼ǣ�������� 
	std::wstring cha_zqyzl;
	// �������ͺ� 
	std::wstring cha_fdjxh;
	// ����  
	std::wstring cha_pl;
	// ����  
	std::wstring cha_gl;
	// ʶ��������� 
	std::wstring cha_sbdh;
	// ����  
	std::wstring cha_pc;
	// ���淢������  
	std::wstring cha_cslx;
	// �������� 
	std::wstring cha_gxrq;
	// ��ע  
	std::wstring cha_bz;
	// ����������ҵ 
	std::wstring cha_zzcmc;
	// ���淢������ 
	std::wstring cha_ggrq;
	// ������Ч���� 
	std::wstring cha_cxsxrq;
	// ��ʻ��ǰ������ 
	std::wstring cha_qpzk;
	// ��ʻ�Һ������� 
	std::wstring cha_hpzk;
	// ������Ч����  
	std::wstring cha_ggsxrq;
	// ������Ч�ڱ��
	std::wstring cha_ggyxqbj;
	// ������������ 
	std::wstring cha_cxggpc;
	// �������淢������ 
	std::wstring cha_cxggrq;
	// ֹͣ�������� 
	std::wstring cha_tzscrq;
	// ��Ч������ 
	std::wstring cha_yxqms;
	// ��������ҵ 
	std::wstring cha_fdjqy;
	// �������̱�   
	std::wstring cha_fdjsb;
	// �ӽ���ȥ�� 
	std::wstring cha_jjlqj;
	// ǰ������  
	std::wstring cha_qxhx;
	// ��� 
	std::wstring cha_zh;
	// ��߳���  
	std::wstring cha_zgcs;
	// �Ƿ��������ϵͳ   
	std::wstring cha_ywabs;
	// ��ҵ���� 
	std::wstring cha_qydm;
	// ������ 
	std::wstring cha_ggbj;
	// ����1  
	std::wstring cha_by1;
	// ����2 
	std::wstring cha_by2;
	// ����3  
	std::wstring cha_by3;
	// ����4  
	std::wstring cha_by4;
	// ����5   
	std::wstring cha_by5;

	// ����������   
	std::wstring pho_bh;
	// ���͹�����  
	std::wstring pho_clggbh;
	// ˳���  
	std::wstring pho_sxh;
	// ����   
	std::wstring pho_pc;
	// ���淢������  
	std::wstring pho_ggrq;
	// ��Ƭ���  
	std::wstring pho_zpbh;
	// �������� 
	std::wstring pho_gxrq;
};

// ���������漼������ͼƬ��Ϣ
struct SGAVehTecParaPhoInfo
{
	// ��Ƭ��� 
	std::wstring zpbh;
	// ��Ƭ 
	std::wstring zp;
	// �������� 
	std::wstring gxrq;
};

// ��ȡ��������ǿ�գ�������˰����Ϣ��ѯ�ӿ�
struct SGAVehComIns
{
	// ���յ���
	std::wstring bxdh;
	// ���չ�˾����
	std::wstring bxgsdm;
	// ���չ�˾����
	std::wstring bxgs;
	// ��������
	std::wstring hpzl;
	// ���ƺ���
	std::wstring hphm;
	// ����ʶ�����
	std::wstring clsbdh;
	// ��Ч����
	std::wstring sxrq;
	// ��ֹ����
	std::wstring zzrq;
	// ������������
	std::wstring bbxr;
	// �����������֤������
	std::wstring bbxrsfzmhm;
	// ��ǿ��Ͷ��״̬
	std::wstring jqxtbzt;
	// ����˰��˰/��˰ƾ֤����
	std::wstring wspzhm;
	// ����˰��˰���
	std::wstring ccsnsqk;
	// ����˰��˰���
	std::wstring ccsnsje;
	// ����˰��˰/��˰ƾ֤����
	std::wstring wspzhm2;
	// ����˰��˰��ʶ���
	std::wstring nsrsbh;
	// ����˰��˰����
	std::wstring ccsnsrq;
	// ����˰��˰����ʱ����ʼ����
	std::wstring ccsnsqsrq;
	// ����˰��˰����ʱ����ֹ����
	std::wstring ccsnszzrq;
};

// ��ȡ������������Ƭ���ȶ���Ϣ��ѯ�ӿ�
// ���������鳵��������Ϣ
struct SGAVehTInfo
{
	// ��ˮ��
	std::wstring lsh;
	// ������ˮ��
	std::wstring jylsh;
	// ����������
	std::wstring jyjgbh;
	// ��������
	std::wstring hpzl;
	// ���ƺ���
	std::wstring hphm;
	// ����ʶ�����
	std::wstring clsbdh;
	// ������������
	std::wstring syr;
	// ������Ч����
	std::wstring sxrq;
	// ������ֹ����
	std::wstring zzrq;
	// ��������
	std::wstring cllx;
	// ʹ������
	std::wstring syxz;
	// ��������
	std::wstring zbzl;
	// ������̿�ʼʱ��
	std::wstring kssj;
	// ������̽���ʱ��
	std::wstring jssj;
	// ������/�綯������
	std::wstring fdjh;
	// ����Ʒ��
	std::wstring clpp1;
	// �����ͺ�
	std::wstring clxh;
	// ���εǼ�����
	std::wstring ccdjrq;
	// ��������
	std::wstring ccrq;
	// ������ۼ������Ա
	std::wstring wgjcjyy;
	// ��Ҫ�ȶԵ���Ƭ����
	std::wstring zpzs;
	// ��Ҫ�ȶԵ���Ƶ����
	std::wstring spzs;
	// �������
	std::wstring jylb;
	// ��ʻ֤֤о���
	std::wstring xszbh;
	// ȼ������
	std::wstring rlzl;
	// ����ʻ֤����
	std::wstring fzrq;
	// ������ɫ
	std::wstring csys;
	// ����
	std::wstring pl;
	// ����
	std::wstring gl;
	// ת����ʽ
	std::wstring zxxs;
	// ��������
	std::wstring cwkc;
	// ��������
	std::wstring cwkk;
	// ��������
	std::wstring cwkg;
	// �����ڲ�����
	std::wstring hxnbcd;
	// �����ڲ����
	std::wstring hxnbkd;
	// �����ڲ��߶�
	std::wstring hxnbgd;
	// �ְ嵯��Ƭ��
	std::wstring gbthps;
	// ����
	std::wstring zs;
	// ���
	std::wstring zj;
	// ǰ�־�
	std::wstring qlj;
	// ���־�
	std::wstring hlj;
	// ��̥���
	std::wstring ltgg;
	// ��̥��
	std::wstring lts;
	// zzl	������
	std::wstring zzl;
	// hdzzl	�˶�������
	std::wstring hdzzl;
	// hdzk	�˶��ؿ�
	std::wstring hdzk;
	// zqyzl	׼ǣ��������
	std::wstring zqyzl;
	// qpzk	��ʻ��ǰ���ؿ�����
	std::wstring qpzk;
	// hpzk	��ʻ�Һ����ؿ�����
	std::wstring hpzk;
	// clyt	������;
	std::wstring clyt;
	// ytsx	��;����
	std::wstring ytsx;
	// sfxny	�Ƿ�����Դ���� 
	std::wstring sfxny;
	// xnyzl	����Դ��������
	std::wstring xnyzl;
	// clpp2	Ӣ��Ʒ��
	std::wstring clpp2;
	// gcjk	����/����
	std::wstring gcjk;
	// zzg	�����
	std::wstring zzg;
	// zzcmc	���쳧����
	std::wstring zzcmc;
	// djrq	�����������
	std::wstring djrq;
	// yxqz	������Ч��ֹ
	std::wstring yxqz;
	// qzbfqz	ǿ�Ʊ�����ֹ
	std::wstring qzbfqz;
	// fzjg	��֤����
	std::wstring fzjg;
	// glbm	������
	std::wstring glbm;
	// zt	������״̬
	std::wstring zt;
	// dybj	��Ѻ���
	std::wstring dybj;
	// fdjxh	�������ͺ�
	std::wstring fdjxh;
	// hbdbqk	����������
	std::wstring hbdbqk;
	// jyhgbzbh	����ϸ��־
	std::wstring jyhgbzbh;
	// xzqh	����Ͻ��
	std::wstring xzqh;
	// zsxzqh	ס����������
	std::wstring zsxzqh;
	// zzxzqh	��ס��������
	std::wstring zzxzqh;
	// sgcssbwqk	�¹ʳ����˲�λ���
	std::wstring sgcssbwqk;
	// sfmj	�Ƿ����
	std::wstring sfmj;
	// bmjyy	�����ԭ��
	std::wstring bmjyy;
};
// ������������Ƭ��Ϣ
struct SGAVehTPhoInfo
{
	//zpzl	��Ƭ����
	std::wstring zpzl;
	//zpurl	��Ƭ·����ַ
	std::wstring zpurl;
};
// ������������Ƭ��Ϣ
struct SGAVehTecParaPhoInfo2
{
	//lb	��Ƭ���
	std::wstring lb;
	// zpurl	��Ƭ·����ַ
	std::wstring zpurl;
};

// ������Ƭ����
// ��1ά�����
// ��2ά����Ƭ����
// ����ά����Ƭ����
const int g_nGAPhotoAmount = 66;
const CStringW g_strGAPhotoDef[][3] =
{
	{L"1", L"0201", L"��������ʻ֤"}, // 1
	{L"2", L"0202", L"��������֤�����"}, // 2
	{L"3", L"0203", L"��������ͨ�¹�����ǿ�Ʊ���ƾ֤"}, // 3
	{L"4", L"0204", L"��������ȫ�������鱨�浥"}, // 4
	{L"5", L"0205", L"�����������¼��"}, // 5
	{L"6", L"0206", L"����˰��˰������˰֤��"}, // 6
	{L"7", L"0207", L"ί�к˷�����ϸ��־֪ͨ��"}, // 7
	{L"8", L"0208", L"��������Ȩ��"}, // 8
	{L"9", L"0211", L"�������������������ϸ�֤�͵��̺ϸ�֤"}, // 9
	{L"10", L"0257", L"·�Լ����¼"}, // 10
	{L"11", L"0111", L"������ǰ��б��45����Ƭ"}, // 11
	{L"12", L"0112", L"�����Һ�б��45����Ƭ"}, // 12
	{L"13", L"0113", L"����ʶ�������Ƭ"}, // 13
	{L"14", L"0119", L"�������Ż����Ա�ǩ"}, // 14
	{L"15", L"0115", L"�����ڲ���Ƭ"}, // 15
	{L"16", L"0158", L"����������Ƭ"}, // 16
	{L"17", L"0116", L"�������Ƭ"}, // 17
	{L"18", L"0117", L"Ӧ������Ƭ"}, // 18
	{L"19", L"0127", L"������"}, // 19
	{L"20", L"0118", L"��ʻ��¼װ����Ƭ"}, // 20
	{L"21", L"0157", L"��ʻ������������ȫ��"}, // 21
	{L"22", L"0134", L"�������ƶ�װ���Լ�״̬��"}, // 22
	{L"23", L"0132", L"���������Զ����װ��"}, // 23
	{L"24", L"0130", L"�����ƶ�װ��"}, // 24
	{L"25", L"0133", L"ǰ����ʽ�ƶ���"}, // 25
	{L"26", L"0136", L"��ǰ��̥����ͺ�"}, // 26
	{L"27", L"0154", L"��ǰ��̥����ͺ�"}, // 27
	{L"28", L"0155", L"�����̥����ͺ�"}, // 28
	{L"29", L"0156", L"�Һ���̥����ͺ�"}, // 29
	{L"30", L"0135", L"�м������ݸ���װ��"}, // 30
	{L"31", L"0140", L"���������ƶ�̤��"}, // 31
	{L"32", L"0163", L"Σ�ջ������䳵��־"}, // 32
	{L"33", L"0126", L"У��ͣ��ָʾ��־����Ƭ"}, // 33
	{L"34", L"0128", L"У����־����Ƭ"}, // 34
	{L"35", L"0138", L"У�������̿ͳ��ĳ�����¼����ϵͳ"}, // 35
	{L"36", L"0139", L"У���ĸ�������װ��"}, // 36
	{L"37", L"0159", L"У�����ƣ�ǰ��������Ƭ"}, // 37
	{L"38", L"0160", L"У�����ƣ�ǰ��������Ƭ"}, // 38
	{L"39", L"0161", L"У�����ƣ���������Ƭ"}, // 39
	{L"40", L"0321", L"��ƹ⹤λ��Ƭ"}, // 40
	{L"41", L"0352", L"�ҵƹ⹤λ��Ƭ"}, // 41
	{L"42", L"0322", L"һ���ƶ���λ��Ƭ"}, // 42
	{L"43", L"0348", L"�����ƶ���λ��Ƭ"}, // 43
	{L"44", L"0349", L"�����ƶ���λ��Ƭ"}, // 44
	{L"45", L"0350", L"�����ƶ���λ��Ƭ"}, // 45
	{L"46", L"0354", L"�����ƶ���λ��Ƭ"}, // 46
	{L"47", L"0355", L"�����ƶ���λ��Ƭ"}, // 47
	{L"48", L"0351", L"פ���ƶ���λ��Ƭ"}, // 48
	{L"49", L"0347", L"���ٱ�λ��Ƭ"}, // 49
	{L"50", L"0353", L"�໬��λ��Ƭ"}, // 50
	{L"51", L"0341", L"·���г��ƶ���ʼ��Ƭ"}, // 51
	{L"52", L"0343", L"·���г��ƶ�������Ƭ"}, // 52
	{L"53", L"0345", L"·���¶�פ���ƶ���Ƭ"}, // 53
	{L"54", L"0344", L"���̶�̬���鿪ʼ��Ƭ"}, // 54
	{L"55", L"0342", L"���̶�̬���������Ƭ"}, // 55
	{L"56", L"0323", L"���̼�����Ƭ"}, // 56
	{L"57", L"0356", L"һ������ƶ���λ��Ƭ"}, // 57
	{L"58", L"0357", L"��������ƶ���λ��Ƭ"}, // 58
	{L"59", L"0358", L"��������ƶ���λ��Ƭ"}, // 59
	{L"60", L"0359", L"��������ƶ���λ��Ƭ"}, // 60
	{L"61", L"0360", L"�����ߴ��Զ�����ǰ����Ƭ"}, // 61
	{L"62", L"0361", L"�����ߴ��Զ�����������Ƭ"}, // 62
	{L"63", L"0362", L"��������������ǰ45����Ƭ"}, // 63
	{L"64", L"0363", L"�������������Һ�45����Ƭ"}, // 64
	{L"65", L"0164", L"�����ж�װ��"}, // 65
	{L"66", L"0114", L"����������Ƭ"}, // 66
	//
};

// �ط�������Ƭ����
// ��1ά�����
// ��2ά����Ƭ����
// ��3ά����Ƭ����
#ifdef ENG_STA_JMDQ
const int g_nOthGAPhoAmount = 3;
const CStringW g_strOthGAPhoDef[][3] =
{
	//{L"1", L"", L""}, // ������ӵط�������Ƭʱ������ɾ��

	{L"1", L"0296", L"��·���䳵�����Ƕ�λװ�ð�װ֤��"}, // 1
	{L"2", L"0297", L"�������鱨���"}, // 2
	{L"3", L"0298", L"��������ʻ֤������֤����"}, // 3
};
#else
const int g_nOthGAPhoAmount = 1;
const CStringW g_strOthGAPhoDef[][3] =
{
	//{L"1", L"", L""}, // ������ӵط�������Ƭʱ������ɾ��
	{L"1", L"0209", L"�ŷż��鱨��"}, // 67
	//{L"1", L"0296", L"��·���䳵�����Ƕ�λװ�ð�װ֤��"}, // 1
	//{L"2", L"0297", L"�������鱨���"}, // 2
	//{L"3", L"0298", L"��������ʻ֤������֤����"}, // 3
};
#endif

#endif