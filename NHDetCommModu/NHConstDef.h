/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�NHConstDef.h
* �ļ���ʶ��
* ���������ۼ쳣������
*
* �汾��1.0
* ���ڣ�2011-06-xx
* ���ߣ�Cyx
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0Beta1
* ���ڣ�2011-06-xx
* ���ߣ�Cyx
* ���������ڿ���
*/

#ifndef NHCONSTDEF_H
#define NHCONSTDEF_H

// �Ƿ�ʹ��GB7258-2017
#ifndef USE_GB7258_2017
#define USE_GB7258_2017
#endif

#include <atlstr.h> 


// �������ʶ
//const wchar_t * const SW_NAME = L"�����������ۺ����ܼ����ƹ������";
const wchar_t * const SW_NAME = L"���������ۼ�����";
const wchar_t * const SW_CODE = L"NHSMDS";
const wchar_t * const SW_VER = L"2.1";
const wchar_t * const SW_C01 = L"ҵ�����"; // �ͻ���1
const wchar_t * const SW_C02 = L"����";
const wchar_t * const SW_C03 = L"��λ����";
const wchar_t * const SW_C04 = L"�ۼ��˹�����¼��";
const wchar_t * const SW_C05 = L"�����˹�����¼��";


// ��������Ŀ��ʶ
// ��NHEngPro.h


// ���ݿ�ƹⴹֱƫ�ƹ̶�Ϊ�ϸ�
// ����ƹⴹֱƫ���Ƿ�����
const bool GB_HLVO_UP_PLUS = true;
// ���ݿ�ƹ�ˮƽƫ�ƹ̶�Ϊ��
// ����ƹ�ˮƽƫ���Ƿ���
const bool GB_HLHO_LEFT_MINUS = true;

////////////////////////////////////////////////////////// ��λ����״̬����-begin
// һ��
const wchar_t * const WPS_GEN_MAL = L"0";  // ����
const wchar_t * const WPS_GEN_REA = L"1";  // ����
const wchar_t * const WPS_GEN_DEM = L"2";  // �궨
const wchar_t * const WPS_GEN_SEL = L"3";  // �Լ�
const wchar_t * const WPS_GEN_INI = L"4";  // ��ʼ��
const wchar_t * const WPS_GEN_OTH = L"99";  // ����

// �ŷ�-ASM
const wchar_t * const WPS_EM_ASM_PRE = L"ASM0";  // �ŷ�_ASM_׼�����
const wchar_t * const WPS_EM_ASM_ING = L"ASM1";  // �ŷ�_ASM_���ڼ��
const wchar_t * const WPS_EM_ASM_FIN = L"ASM2";  // �ŷ�_ASM_��ɼ��
const wchar_t * const WPS_EM_ASM_SKI = L"ASM3";  // �ŷ�_ASM_�������
const wchar_t * const WPS_EM_ASM_RET = L"ASM4";  // �ŷ�_ASM_������

// �ŷ�-LUGDOWN
const wchar_t * const WPS_EM_LUGDOWN_PRE = L"LUGDOWN0";  // �ŷ�_LUGDOWN_׼�����
const wchar_t * const WPS_EM_LUGDOWN_ING = L"LUGDOWN1";  // �ŷ�_LUGDOWN_���ڼ��
const wchar_t * const WPS_EM_LUGDOWN_FIN = L"LUGDOWN2";  // �ŷ�_LUGDOWN_��ɼ��
const wchar_t * const WPS_EM_LUGDOWN_SKI = L"LUGDOWN3";  // �ŷ�_LUGDOWN_�������
const wchar_t * const WPS_EM_LUGDOWN_RET = L"LUGDOWN4";  // �ŷ�_LUGDOWN_������

// �ŷ�-˫����
const wchar_t * const WPS_EM_DIS_PRE = L"DIS0";  // �ŷ�_˫����_׼�����
const wchar_t * const WPS_EM_DIS_HIS_ING = L"DIS1";  // �ŷ�_˫����_�ߵ���_���ڼ��
const wchar_t * const WPS_EM_DIS_HIS_FIN = L"DIS2";  // �ŷ�_˫����_�ߵ���_��ɼ��
const wchar_t * const WPS_EM_DIS_LIS_ING = L"DIS3";  // �ŷ�_˫����_�͵���_���ڼ��
const wchar_t * const WPS_EM_DIS_LIS_FIN = L"DIS4";  // �ŷ�_˫����_�͵���_��ɼ��
const wchar_t * const WPS_EM_DIS_FIN = L"DIS5";  // �ŷ�_˫����_��ɼ��
const wchar_t * const WPS_EM_DIS_SKI = L"DIS6";  // �ŷ�_˫����_�������
const wchar_t * const WPS_EM_DIS_RET = L"DIS7";  // �ŷ�_˫����_������

// �ŷ�-��͸�����ɼ���
const wchar_t * const WPS_EM_FAOPA_PRE = L"FAOPA0";  // �ŷ�_��͸�����ɼ���_׼�����
const wchar_t * const WPS_EM_FAOPA_ING = L"FAOPA1";  // �ŷ�_��͸�����ɼ���_���ڼ��
const wchar_t * const WPS_EM_FAOPA_FIN = L"FAOPA2";  // �ŷ�_��͸�����ɼ���_��ɼ��
const wchar_t * const WPS_EM_FAOPA_SKI = L"FAOPA3";  // �ŷ�_��͸�����ɼ���_�������
const wchar_t * const WPS_EM_FAOPA_RET = L"FAOPA4";  // �ŷ�_��͸�����ɼ���_������

// �ŷ�-��ֽʽ���ɼ���
const wchar_t * const WPS_EM_FASMO_PRE = L"FASMO0";  // �ŷ�_��ֽʽ���ɼ���_׼�����
const wchar_t * const WPS_EM_FASMO_ING = L"FASMO1";  // �ŷ�_��ֽʽ���ɼ���_���ڼ��
const wchar_t * const WPS_EM_FASMO_FIN = L"FASMO2";  // �ŷ�_��ֽʽ���ɼ���_��ɼ��
const wchar_t * const WPS_EM_FASMO_SKI = L"FASMO3";  // �ŷ�_��ֽʽ���ɼ���_�������
const wchar_t * const WPS_EM_FASMO_RET = L"FASMO4";  // �ŷ�_��ֽʽ���ɼ���_������

// ���ٱ�
const wchar_t * const WPS_SM_PRE = L"SM0";  // ���ٱ�_׼�����
const wchar_t * const WPS_SM_ING = L"SM1";  // ���ٱ�_���ڼ��
const wchar_t * const WPS_SM_FIN = L"SM2";  // ���ٱ�_��ɼ��
const wchar_t * const WPS_SM_SKI = L"SM3";  // ���ٱ�_�������
const wchar_t * const WPS_SM_RET = L"SM4";  // ���ٱ�_������

// �˹�
const wchar_t * const WPS_MN_PRE = L"MN0";  // �˹�_׼�����
const wchar_t * const WPS_MN_ING = L"MN1";  // �˹�_���ڼ��
const wchar_t * const WPS_MN_FIN = L"MN2";  // �˹�_��ɼ��
const wchar_t * const WPS_MN_SKI = L"MN4";  // �˹�_�������
const wchar_t * const WPS_MN_RET = L"MN5";  // �˹�_������

// ǰ�յ�
const wchar_t * const WPS_HL_PRE = L"HL0";     // ǰ�յ�_׼�����
const wchar_t * const WPS_HL_LL_ING = L"HL1";  // ǰ�յ�_���_���ڼ��
const wchar_t * const WPS_HL_LL_FIN = L"HL2";  // ǰ�յ�_���_��ɼ��
const wchar_t * const WPS_HL_RL_ING = L"HL3";  // ǰ�յ�_�ҵ�_���ڼ��
const wchar_t * const WPS_HL_RL_FIN = L"HL4";  // ǰ�յ�_�ҵ�_��ɼ��
const wchar_t * const WPS_HL_FIN = L"HL5";     // ǰ�յ�_��ɼ��
const wchar_t * const WPS_HL_SKI = L"HL6";     // ǰ�յ�_�������
const wchar_t * const WPS_HL_RET = L"HL7";     // ǰ�յ�_������

// �໬
const wchar_t * const WPS_SS_PRE = L"SS0";  // �໬_׼�����
const wchar_t * const WPS_SS_ING = L"SS1";  // �໬_���ڼ��
const wchar_t * const WPS_SS_FIN = L"SS2";  // �໬_��ɼ��
const wchar_t * const WPS_SS_SKI = L"SS3";  // �໬_�������
const wchar_t * const WPS_SS_RET = L"SS4";  // �໬_������

// ����
const wchar_t * const WPS_AL_PRE = L"AL0";      // ����_׼�����
const wchar_t * const WPS_AL_A1_ING = L"AL1";   // ����_һ��_���ڼ��
const wchar_t * const WPS_AL_A1_FIN = L"AL2";   // ����_һ��_��ɼ��
const wchar_t * const WPS_AL_A2_ING = L"AL3";   // ����_����_���ڼ��
const wchar_t * const WPS_AL_A2_FIN = L"AL4";   // ����_����_��ɼ��
const wchar_t * const WPS_AL_A3_ING = L"AL5";   // ����_����_���ڼ��
const wchar_t * const WPS_AL_A3_FIN = L"AL6";   // ����_����_��ɼ��
const wchar_t * const WPS_AL_A4_ING = L"AL7";   // ����_����_���ڼ��
const wchar_t * const WPS_AL_A4_FIN = L"AL8";   // ����_����_��ɼ��
const wchar_t * const WPS_AL_A5_ING = L"AL9";   // ����_����_���ڼ��
const wchar_t * const WPS_AL_A5_FIN = L"AL10";  // ����_����_��ɼ��
const wchar_t * const WPS_AL_A6_ING = L"AL11";  // ����_����_���ڼ��
const wchar_t * const WPS_AL_A6_FIN = L"AL12";  // ����_����_��ɼ��
const wchar_t * const WPS_AL_FIN = L"AL13";     // ����_��ɼ��
const wchar_t * const WPS_AL_SKI = L"AL14";     // ����_�������
const wchar_t * const WPS_AL_RET = L"AL15";     // ����_������

// �ƶ�
const wchar_t * const WPS_BK_PRE = L"BK0";        // �ƶ�_׼�����
const wchar_t * const WPS_BK_A1SB_ING = L"BK1";   // �ƶ�_һ���г�_���ڼ��
const wchar_t * const WPS_BK_A1SB_FIN = L"BK2";   // �ƶ�_һ���г�_��ɼ��
const wchar_t * const WPS_BK_A1PB_ING = L"BK3";   // �ƶ�_һ��פ��_���ڼ��
const wchar_t * const WPS_BK_A1PB_FIN = L"BK4";   // �ƶ�_һ��פ��_��ɼ��
const wchar_t * const WPS_BK_A2SB_ING = L"BK5";   // �ƶ�_�����г�_���ڼ��
const wchar_t * const WPS_BK_A2SB_FIN = L"BK6";   // �ƶ�_�����г�_��ɼ��
const wchar_t * const WPS_BK_A2PB_ING = L"BK7";   // �ƶ�_����פ��_���ڼ��
const wchar_t * const WPS_BK_A2PB_FIN = L"BK8";   // �ƶ�_����פ��_��ɼ��
const wchar_t * const WPS_BK_A3SB_ING = L"BK9";   // �ƶ�_�����г�_���ڼ��
const wchar_t * const WPS_BK_A3SB_FIN = L"BK10";  // �ƶ�_�����г�_��ɼ��
const wchar_t * const WPS_BK_A3PB_ING = L"BK11";  // �ƶ�_����פ��_���ڼ��
const wchar_t * const WPS_BK_A3PB_FIN = L"BK12";  // �ƶ�_����פ��_��ɼ��
const wchar_t * const WPS_BK_A4SB_ING = L"BK13";  // �ƶ�_�����г�_���ڼ��
const wchar_t * const WPS_BK_A4SB_FIN = L"BK14";  // �ƶ�_�����г�_��ɼ��
const wchar_t * const WPS_BK_A4PB_ING = L"BK15";  // �ƶ�_����פ��_���ڼ��
const wchar_t * const WPS_BK_A4PB_FIN = L"BK16";  // �ƶ�_����פ��_��ɼ��
const wchar_t * const WPS_BK_A5SB_ING = L"BK17";  // �ƶ�_�����г�_���ڼ��
const wchar_t * const WPS_BK_A5SB_FIN = L"BK18";  // �ƶ�_�����г�_��ɼ��
const wchar_t * const WPS_BK_A5PB_ING = L"BK19";  // �ƶ�_����פ��_���ڼ��
const wchar_t * const WPS_BK_A5PB_FIN = L"BK20";  // �ƶ�_����פ��_��ɼ��
const wchar_t * const WPS_BK_A6SB_ING = L"BK21";  // �ƶ�_�����г�_���ڼ��
const wchar_t * const WPS_BK_A6SB_FIN = L"BK22";  // �ƶ�_�����г�_��ɼ��
const wchar_t * const WPS_BK_A6PB_ING = L"BK23";  // �ƶ�_����פ��_���ڼ��
const wchar_t * const WPS_BK_A6PB_FIN = L"BK24";  // �ƶ�_����פ��_��ɼ��
const wchar_t * const WPS_BK_FIN = L"BK25";       // �ƶ�_��ɼ��
const wchar_t * const WPS_BK_SKI = L"BK26";       // �ƶ�_�������
const wchar_t * const WPS_BK_RET = L"BK27";       // �ƶ�_������

// ����
const wchar_t * const WPS_SL_PRE = L"SL0";  // ����_׼�����
const wchar_t * const WPS_SL_ING = L"SL1";  // ����_���ڼ��
const wchar_t * const WPS_SL_FIN = L"SL2";  // ����_��ɼ��
const wchar_t * const WPS_SL_SKI = L"SL3";  // ����_�������
const wchar_t * const WPS_SL_RET = L"SL4";  // ����_������

// ת��
const wchar_t * const WPS_SA_PRE = L"SA0";     // ת��_׼�����
const wchar_t * const WPS_SA_LA_ING = L"SA1";  // ת��_��ת��_���ڼ��
const wchar_t * const WPS_SA_LA_FIN = L"SA2";  // ת��_��ת��_��ɼ��
const wchar_t * const WPS_SA_RA_ING = L"SA3";  // ת��_��ת��_���ڼ��
const wchar_t * const WPS_SA_RA_FIN = L"SA4";  // ת��_��ת��_��ɼ��
const wchar_t * const WPS_SA_FIN = L"SA5";     // ת��_��ɼ��
const wchar_t * const WPS_SA_SKI = L"SA6";     // ת��_�������
const wchar_t * const WPS_SA_RET = L"SA7";     // ת��_������

// ����
const wchar_t * const WPS_PWR_PRE = L"PWR0";  // ����_׼�����
const wchar_t * const WPS_PWR_ING = L"PWR1";  // ����_���ڼ��
const wchar_t * const WPS_PWR_FIN = L"PWR2";  // ����_��ɼ��
const wchar_t * const WPS_PWR_SKI = L"PWR3";  // ����_�������
const wchar_t * const WPS_PWR_RET = L"PWR4";  // ����_������

// ��Ե
const wchar_t * const WPS_INS_PRE = L"INS0";  // ��Ե_׼�����
const wchar_t * const WPS_INS_ING = L"INS1";  // ��Ե_���ڼ��
const wchar_t * const WPS_INS_FIN = L"INS2";  // ��Ե_��ɼ��
const wchar_t * const WPS_INS_SKI = L"INS3";  // ��Ե_�������
const wchar_t * const WPS_INS_RET = L"INS4";  // ��Ե_������

// ����
const wchar_t * const WPS_ST_PRE = L"ST0";     // ����_׼�����
const wchar_t * const WPS_ST_A1_ING = L"ST1";  // ����_ǰ��_���ڼ��
const wchar_t * const WPS_ST_A1_FIN = L"ST2";  // ����_ǰ��_��ɼ��
const wchar_t * const WPS_ST_A2_ING = L"ST3";  // ����_����_���ڼ��
const wchar_t * const WPS_ST_A2_FIN = L"ST4";  // ����_����_��ɼ��
const wchar_t * const WPS_ST_FIN = L"ST5";     // ����_��ɼ��
const wchar_t * const WPS_ST_SKI = L"ST6";     // ����_�������
const wchar_t * const WPS_ST_RET = L"ST7";     // ����_������

// ��ƫ
const wchar_t * const WPS_WO_PRE = L"WO0";  // ��ƫ_׼�����
const wchar_t * const WPS_WO_ING = L"WO1";  // ��ƫ_���ڼ��
const wchar_t * const WPS_WO_FIN = L"WO2";  // ��ƫ_��ɼ��
const wchar_t * const WPS_WO_SKI = L"WO3";  // ��ƫ_�������
const wchar_t * const WPS_WO_RET = L"WO4";  // ��ƫ_������

// ��������
const wchar_t * const WPS_UM_PRE = L"UM0";  // ��������_׼�����
const wchar_t * const WPS_UM_ING = L"UM1";  // ��������_���ڼ��
const wchar_t * const WPS_UM_FIN = L"UM2";  // ��������_��ɼ��
const wchar_t * const WPS_UM_SKI = L"UM3";  // ��������_�������
const wchar_t * const WPS_UM_RET = L"UM4";  // ��������_������

// ����
const wchar_t * const WPS_DIM_PRE = L"DIM0";  // ����_׼�����
const wchar_t * const WPS_DIM_ING = L"DIM1";  // ����_���ڼ��
const wchar_t * const WPS_DIM_FIN = L"DIM2";  // ����_��ɼ��
const wchar_t * const WPS_DIM_SKI = L"DIM3";  // ����_�������
const wchar_t * const WPS_DIM_RET = L"DIM4";  // ����_������

// �ͺ�
const wchar_t * const WPS_FC_PRE = L"FC0";  // �ͺ�_׼�����
const wchar_t * const WPS_FC_ING = L"FC1";  // �ͺ�_���ڼ��
const wchar_t * const WPS_FC_FIN = L"FC2";  // �ͺ�_��ɼ��
const wchar_t * const WPS_FC_SKI = L"FC3";  // �ͺ�_�������
const wchar_t * const WPS_FC_RET = L"FC4";  // �ͺ�_������
////////////////////////////////////////////////////////// ��λ����״̬����-end

////////////////////////////////////////////////////////// �������ݰ���ʽ��س���������"��������빤λ�������ͨѶЭ��"-begin
// �������ݰ�(���)����[Byte]
const unsigned int g_unNetPackSize = 1024;
// �������ݰ���ͷ��С[Byte]
const unsigned int g_unNetPackHeaderSize = 2;
// �������ݰ�"���ݶδ�Сָʾ��(DataSecSizePointer)"��С
const unsigned int g_unNetPackDSSPSize = 4;
// �������ݰ���β��С[Byte]
const unsigned int g_unNetPackTailSize = 2;
// ������QN��С
const unsigned int g_unQNSize = 17;
// �ܰ���PCNT��С
const unsigned int g_unPCNTSize = 4;
// ����PNO��С
const unsigned int g_unPNOSize = 4;
// �������ݰ�����ʶռ�õ��ܴ�С
const unsigned int g_unNetPackSignsSize = g_unNetPackHeaderSize + g_unNetPackDSSPSize + g_unNetPackTailSize + g_unQNSize + g_unPCNTSize + g_unPNOSize;
// �������ݰ�(���)��������
const unsigned int g_unNetPackPayloadSize = g_unNetPackSize - g_unNetPackSignsSize;
// ��ͷ��ʶ
const char * const g_pchNetPackHeaderSign = "##";
// ��β��ʶ
const char * const g_pchNetPackTailSign = "\r\n";
////////////////////////////////////////////////////////// �������ݰ���ʽ��س���������"��������빤λ�������ͨѶЭ��"-end

//������ɫ��	Ӣ�Ĵ���					//������ɫ	HEX��ʽ		RGB��ʽ
#define COLOR_ForestGreen	0x228B22		//ɭ����	#228B22 	34,139,34
#define COLOR_DarkGreen		0x006400		//����ɫ	#006400 	0,100,0
#define COLOR_FireBrick		0x2222B2		//�ͻ�ש	#B22222 	178,34,34
#define COLOR_DarkRed		0x00008B		//���ɫ	#8B0000 	139,0,0
#define COLOR_Black		0x000000		//��ɫ	#000000 	0,0,0

// �ж����룬Judge Code
const wchar_t * const JD_Lev1 = L"-1";       // -1: һ��
const wchar_t * const JD_Lev2 = L"-2";       // -2: ����
const wchar_t * const JD_Pass = L"0";       // 0: �ϸ�
const wchar_t * const JD_Fail = L"1";       // 1: ���ϸ�
const wchar_t * const JD_NotJud = L"2";       // 2: ���ж���������
const wchar_t * const JD_NotDet = L"";       // NULL: δ��

// ������
const wchar_t * const DETCON_Lev1 = L"Ҽ��";
const wchar_t * const DETCON_Lev2 = L"����";
const wchar_t * const DETCON_Pass = L"�ϸ�";
const wchar_t * const DETCON_Main = L"�ϸ�(����ά��)";
const wchar_t * const DETCON_Fail = L"���ϸ�";
const wchar_t * const DETCON_NotJud = L"���ж�";
const wchar_t * const DETCON_NotDet = L"";

// �ж�������ɫ
#define COLOR_Pass			COLOR_DarkGreen
#define COLOR_NotPass		COLOR_FireBrick
#define COLOR_Fail			COLOR_NotPass
#define COLOR_NotJud		COLOR_Black

// �ж�����
const wchar_t * const LV1_SIGN = L"1";
const wchar_t * const LV2_SIGN = L"2";
const wchar_t * const PASS_SIGN = L"��";
const wchar_t * const FAIL_SIGN = L"��";
const wchar_t * const NOTJUD_SIGN = L"��";
const wchar_t * const NOTDET_SIGN = L"";

// ·���ƶ��ȶ��Դ��룬Road ServiceBrake Stability Code
const wchar_t * const RDSBS_Left = L"-1";       // -1: ����ƫ
const wchar_t * const RDSBS_Pass = L"0";        // 0: δ��ƫ
const wchar_t * const RDSBS_Right = L"1";       // 1: ����ƫ

// ·���ƶ��ȶ�������
const wchar_t * const RDSBS_LEFT = L"����ƫ";       // -1: ����ƫ
const wchar_t * const RDSBS_PASS = L"δ��ƫ";        // 0: δ��ƫ
const wchar_t * const RDSBS_RIGHT = L"����ƫ";       // 1: ����ƫ

// �ж�������
enum JudgeCode
{
	JD_LEV1 = -1, // һ��
	JD_LEV2 = -2, // ����
	JD_PASS= 0,       // �ϸ�
	JD_FAIL = 1,       // ���ϸ�
	JD_NOTJUD = 2,      // ���ж���������
};


// �ȼ�����
enum RatEnum
{
	Rat_NotDet = 0, // δ�죨NULL��
	Rat_Lev1 = -1, // һ��
	Rat_Lev2 = -2, // ����
	Rat_Lev3 = 2, // ������
	Rat_Pass = 0, // �ϸ�
	Rat_Fail = 1, // ���ϸ�
};

// ����״̬
enum ConnectionStatusEnum
{
	CS_Unconnected = 0, // δ����
	CS_Connecting,      // ��������
	CS_Connected,       // ������
};

const wchar_t * const CN_ST = L"ST"; // ͬ��ʱ��
const wchar_t * const CN_GS = L"GS"; // ��ȡ״̬
const wchar_t * const CN_SS = L"SS"; // ����״̬
const wchar_t * const CN_EP = L"EP"; // ���빤λ
const wchar_t * const CN_LP = L"LP"; // �뿪��λ
const wchar_t * const CN_RP = L"RP"; // ���ù�λ
const wchar_t * const CN_OL = L"OL"; // ������
const wchar_t * const CN_NL = L"NL"; // ��������
const wchar_t * const CN_EC = L"EC"; // ִ��������
const wchar_t * const CN_LI = L"LI"; // ��������Ϣ

// �����Ŀ����
enum DetectItemEnum
{
	DI_NULL = 0,                // ��
	DI_Emission = 1,            // �ŷż��
	DI_Speedometer = 2,         // ���ٱ���
	DI_Manual = 3,              // �˹����
	DI_HeadLight = 4,           // ǰ�յƼ��
	DI_Sideslip = 5,            // �໬���
	DI_AxleLoad = 6,            // ���ؼ��
	DI_Brake = 7,               // �ƶ����
	DI_Power = 8,               // ���ʼ��
	DI_SoundLevel = 9,          // �������
	DI_SteeringAngle = 10,      // ת�Ǽ��
	DI_Suspension = 11,         // ���ܼ��
	DI_WheelOffset = 12,        // ��ƫ���
	DI_Insulation = 13,         // ��Ե���
	DI_Momentum = 14,           // ����ת�������
	DI_FuelCon = 15,            // �ͺļ��
	DI_UM = 16,                 // �����������
	DI_Dimension = 17,          // �������
	DI_END = DI_Dimension,      // ����
};

// ������Ŀ����
enum InspectionItemEnum
{
	II_NULL = 0,				// ��
	II_NetQuery,				// ������ѯ
	II_MD_Item1,				// �˹���Ŀ
	II_MD_Item2,				// �˹���Ŀ
	II_MD_Item3,				// �˹���Ŀ
	II_MD_Item4,				// �˹���Ŀ
	II_MD_Item5,				// �˹���Ŀ
	II_MD_Item6,				// �˹���Ŀ
	II_DI = II_MD_Item6,		// �����ߴ���
	II_MD_Item7,				// �˹���Ŀ
	II_MD_Item8,				// �˹���Ŀ
	II_UM = II_MD_Item8,		// �����������
	II_MD_Item9,				// �˹���Ŀ
	II_MD_Item10,				// �˹���Ŀ
	II_MD_Item11,				// �˹���Ŀ
	II_MD_Item12,				// �˹���Ŀ
	II_MD_Item13,				// �˹���Ŀ
	II_MD_Item14,				// �˹���Ŀ
	II_MD_Item15,				// �˹���Ŀ
	II_MD_Item16,				// �˹���Ŀ
	II_MD_Item17,				// �˹���Ŀ
	II_MD_Item18,				// �˹���Ŀ
	II_MD_Item19,				// �˹���Ŀ
	II_MD_Item20,				// �˹���Ŀ
	II_MD_Item21,				// �˹���Ŀ
	II_MD_Item22,				// �˹���Ŀ
	II_MD_Item23,				// �˹���Ŀ
	II_MD_Item24,				// �˹���Ŀ
	II_MD_Item25,				// �˹���Ŀ
	II_MD_Item26,				// �˹���Ŀ
	II_MD_Item27,				// �˹���Ŀ
	II_MD_Item28,				// �˹���Ŀ
	II_MD_Item29,				// �˹���Ŀ
	II_MD_Item30,				// �˹���Ŀ
	II_MD_Item31,				// �˹���Ŀ
	II_MD_Item32,				// �˹���Ŀ
	II_MD_Item33,				// �˹���Ŀ
	II_MD_Item34,				// �˹���Ŀ
	II_MD_Item35,				// �˹���Ŀ
	II_MD_Item36,				// �˹���Ŀ
	II_MD_Item37,				// �˹���Ŀ
	II_MD_Item38,				// �˹���Ŀ
	II_MD_Item39,				// �˹���Ŀ
	II_MD_Item40,				// �˹���Ŀ
	II_MD_Item41,				// �˹���Ŀ
	II_MD_Item42,				// �˹���Ŀ
	II_MD_Item43,				// �˹���Ŀ
	II_MD_Item44,				// �˹���Ŀ
	II_MD_Item45,				// �˹���Ŀ
	II_MD_Item46,				// �˹���Ŀ
	II_MD_Item47,				// �˹���Ŀ
	II_MD_Item48,				// �˹���Ŀ
	II_MD_Item49,				// �˹���Ŀ
	II_MD_Item50,				// �˹���Ŀ
	II_BK_SBRate,				// �����г��ƶ���
	II_BK_UnbRate,              // �����ƶ���ƽ����
	II_BK_Load_SBRate,			// �����г��ƶ���
	II_BK_Load_UnbRate,         // �����ƶ���ƽ����
	II_BK_PBRate,				// פ���ƶ���
	II_HL_INT,					// ǰ�յƹ�ǿ
	II_HL_VO,					// ǰ�յƴ�ֱƫ��
	II_ED_DIS,					// �ŷż��
	II_ED_FAOPA,				// �ŷż��
	II_ED_FASMO,				// �ŷż��
	II_SM,						// ���ٱ���
	II_SS,						// �໬���
};

// �ŷż����Ŀ����
enum EmissionDetectItemEnum
{
	EDI_ERR = 0,       // �������
	EDI_ASM = 1,       // ��̬
	EDI_VMAS = 2,      // ����˲̬
	EDI_LUGDOWN = 3,   //���ؼ���
	EDI_DIS = 4,       // ˫����
	EDI_FAOPA = 5,     // ��͸�����ɼ���
	EDI_FASMO = 6,     // ��ֽʽ���ɼ���
	EDI_AVFASMO = 7,   // ũ�ó����ɼ���
	EDI_MIS = 8,       // Ħ�г�����
	EDI_MDIS = 9,      // Ħ�г�˫����
};

// �˹������Ŀ����
enum ManualDetectItemEnum
{
	MDI_ERR = 0,        // �������
	MDI_Appearance = 1, // ���
	MDI_Dynamic = 2,    // ��̬
	MDI_Chassis = 3,    // ����
};

// �����Ŀ���ȱ�ʶ
enum DetectionProgressEnum
{
	DP_RemDet = 0,  // ������
	DP_ToDet = 1,   // �ȴ����
	DP_PreDet = 2,  // ׼�����
	DP_Deting = 3,  // ���ڼ��
	DP_FinDet = 4,  // ������
};

// ����������
enum CommandErrCodeEnum
{
	CEC_Normal,     // ����
	CEC_Exception,  // �쳣
};

// �ƶ�̨����
enum BrakeTesterType // TODO����Enum
{
	BTT_Roller,			// ��Ͳ
	BTT_Platform,		// ƽ��
};
// ����̨����
enum SpeedTesterType // TODO���޸�ΪSpeedometerTester����Enum
{
	STT_SpeedometerTester,		// ����̨
	STT_Dynamometer,			// �⹦��
};

// �ۼ��˹���Ŀ����
enum  ManualItemAttEnum
{
	MIA_Key_Items ,		// �ؼ���
	MIA_Gen_Items ,		// һ����
	MIA_Rank_Item ,		// �ּ���
	MIA_VerEva_Item,    // �˲�������
};
// ���ҵ��״̬����
// Business Status
// ���� "NHSTDCMS��������ȫ�����ƹ���ϵͳ�����.doc, �������״̬���� ����"

const wchar_t * const DS_ToDet = L"TODET";           // �ȴ����
const wchar_t * const DS_PreDet = L"PREDET";         // ׼�����
const wchar_t * const DS_Deting = L"DETING";         // ���ڼ��
const wchar_t * const DS_FinDet = L"FINDET";         // ������
const wchar_t * const DS_CanDet = L"CANDET";         // ���ȡ��
const wchar_t * const DS_DIS = L"DIS";               // ���ڼ��˫����
const wchar_t * const DS_FAOPA = L"FAOPA";           // ���ڼ�ⲻ͸��
const wchar_t * const DS_FASMO= L"FASMO";            // ���ڼ����ֽʽ
const wchar_t * const DS_SM = L"SM";                 // ���ڼ�⳵�ٱ�
const wchar_t * const DS_APP = L"APP";               // ���ڼ�����
const wchar_t * const DS_DYN = L"DYN";               // ���ڼ�⶯̬
const wchar_t * const DS_CHA = L"CHS";               // ���ڼ�����
const wchar_t * const DS_HL = L"HL";                 // ���ڼ��ǰ�յ�
const wchar_t * const DS_HLL = L"HLL";               // ���ڼ�����
const wchar_t * const DS_HLR = L"HLR";               // ���ڼ���ҵ�
const wchar_t * const DS_SS = L"SS";                 // ���ڼ��໬
const wchar_t * const DS_AL = L"AL";                 // ���ڼ������
const wchar_t * const DS_AL1 = L"AL1";               // ���ڼ��һ������
const wchar_t * const DS_AL2 = L"AL2";               // ���ڼ���������
const wchar_t * const DS_AL3 = L"AL3";               // ���ڼ����������
const wchar_t * const DS_AL4 = L"AL4";               // ���ڼ����������
const wchar_t * const DS_SB = L"SB";                 // ���ڼ���г��ƶ�
const wchar_t * const DS_SB1 = L"SB1";               // ���ڼ��һ���г��ƶ�
const wchar_t * const DS_SB2 = L"SB2";               // ���ڼ������г��ƶ�
const wchar_t * const DS_SB3 = L"SB3";               // ���ڼ�������г��ƶ�
const wchar_t * const DS_SB4 = L"SB4";               // ���ڼ�������г��ƶ�
const wchar_t * const DS_PB = L"PB";                 // ���ڼ��פ���ƶ�
const wchar_t * const DS_SL = L"SL";                 // ���ڼ������
const wchar_t * const DS_SA = L"SA";                 // ���ڼ��ת��
const wchar_t * const DS_SAL = L"SAL";               // ���ڼ����ת��
const wchar_t * const DS_SAR = L"SAR";               // ���ڼ����ת��
const wchar_t * const DS_INS = L"INS";               // ���ڼ���Ե
const wchar_t * const DS_UM = L"UM";                 // ���ڼ����������
const wchar_t * const DS_FC = L"FC";                 // ���ڼ���ͺ�

// �����˺�
const wchar_t * const BUILT_IN_USER = L"NH@"; // �����û�
const wchar_t * const BUILT_IN_PWD = L"$%PKU%$"; // ��������

// ���ں�
const wchar_t * const COM_PORT_LED		= L"1";             // ���������ں�
const wchar_t * const COM_PORT_ANA		= L"2";             // �����Ǵ��ں�
const wchar_t * const COM_PORT_OPA		= L"3";             // ��͸�⴮�ں�
const wchar_t * const COM_PORT_SMO		= L"4";             // �̶ȼƴ��ں�
const wchar_t * const COM_PORT_SMT		= L"5";             // ����̨���ں�
const wchar_t * const COM_PORT_HLT_L	= L"6";             // �ƹ���(��)���ں�
const wchar_t * const COM_PORT_HLT_R	= L"7";             // �ƹ���(��)���ں�
const wchar_t * const COM_PORT_SST		= L"8";             // �໬̨���ں�
const wchar_t * const COM_PORT_ALS		= L"9";             // �����Ǵ��ں�
const wchar_t * const COM_PORT_RBT		= L"10";            // ��Ͳ�ƶ�̨���ں�
const wchar_t * const COM_PORT_PBT		= L"11";            // ƽ���ƶ�̨���ں�
const wchar_t * const COM_PORT_PS		= L"12";            // ���俪�ش��ں�
const wchar_t * const COM_PORT_BS_MT	= L"13";            // ɨ��ǹ(�˹�)���ں�
const wchar_t * const COM_PORT_BS_OL	= L"14";            // ɨ��ǹ(����)���ں�
const wchar_t * const COM_PORT_SLM		= L"15";            // �����ƴ��ں�
const wchar_t * const COM_PORT_MFT		= L"16";            // ̤�����������ƴ��ں�
const wchar_t * const COM_PORT_SAT		= L"17";            // ת��̨���ں�
const wchar_t * const COM_PORT_INS		= L"18";            // ��Ե�Ǵ��ں�
const wchar_t * const COM_PORT_TAC		= L"19";            // ת�ټƴ��ں�
const wchar_t * const COM_PORT_ST		= L"20";            // ����̨���ں�
const wchar_t * const COM_PORT_DYN		= L"21";            // �⹦�����ں�
const wchar_t * const COM_PORT_WOT		= L"22";            // ��ƫ̨���ں�
const wchar_t * const COM_PORT_FCM		= L"23";            // �ͺ��Ǵ��ں�

// ������
const wchar_t * const BAUD_RATE_LED		= L"19200";         // ������������
const wchar_t * const BAUD_RATE_ANA		= L"9600";          // �����ǲ�����
const wchar_t * const BAUD_RATE_OPA		= L"9600";          // ��͸�Ⲩ����
const wchar_t * const BAUD_RATE_SMO		= L"2400";          // �̶ȼƲ�����
const wchar_t * const BAUD_RATE_SMT		= L"38400";         // ����̨������
const wchar_t * const BAUD_RATE_HLT_L	= L"2400";          // �ƹ���(��)������
const wchar_t * const BAUD_RATE_HLT_R	= L"2400";          // �ƹ���(��)������
const wchar_t * const BAUD_RATE_SST		= L"38400";         // �໬̨������
const wchar_t * const BAUD_RATE_ALS		= L"38400";         // �����ǲ�����
const wchar_t * const BAUD_RATE_RBT		= L"38400";         // ��Ͳ�ƶ�̨������
const wchar_t * const BAUD_RATE_PBT		= L"38400";         // ƽ���ƶ�̨������
const wchar_t * const BAUD_RATE_PS		= L"38400";         // ���俪�ز�����
const wchar_t * const BAUD_RATE_BS_MT	= L"9600";          // ɨ��ǹ(�˹�)������
const wchar_t * const BAUD_RATE_BS_OL	= L"9600";          // ɨ��ǹ(����)������
const wchar_t * const BAUD_RATE_SLM		= L"9600";          // �����Ʋ�����
const wchar_t * const BAUD_RATE_MFT		= L"9600";          // ̤�����������Ʋ�����
const wchar_t * const BAUD_RATE_SAT		= L"38400";         // ת��̨������
const wchar_t * const BAUD_RATE_INS		= L"9600";          // ��Ե�ǲ�����
const wchar_t * const BAUD_RATE_TAC		= L"9600";          // ת�ټƲ�����
const wchar_t * const BAUD_RATE_ST		= L"38400";          // ����̨������
const wchar_t * const BAUD_RATE_WOT		= L"38400";          // ��ƫ̨������
const wchar_t * const BAUD_RATE_FCM		= L"9600";           // �ͺ��ǲ�����

// ͨѶЭ��
const wchar_t * const PROTOCOL_LED		= L"NH50R";			// ������ͨѶЭ��
const wchar_t * const PROTOCOL_ANA		= L"503V";			// ������ͨѶЭ��
const wchar_t * const PROTOCOL_OPA		= L"NHT6";			// ��͸��ͨѶЭ��
const wchar_t * const PROTOCOL_SMO		= L"YD";			// �̶ȼ�ͨѶЭ��
const wchar_t * const PROTOCOL_SMT		= L"NHM10";			// ����̨ͨѶЭ��
const wchar_t * const PROTOCOL_HLT_L	= L"NHD6108";		// �ƹ���(��)ͨѶЭ��
const wchar_t * const PROTOCOL_HLT_R	= L"NHD6108";		// �ƹ���(��)ͨѶЭ��
const wchar_t * const PROTOCOL_SST		= L"NHS10";			// �໬̨ͨѶЭ��
const wchar_t * const PROTOCOL_ALS		= L"NHW10";			// ������ͨѶЭ��
const wchar_t * const PROTOCOL_RBT		= L"NHZ10";			// ��Ͳ�ƶ�̨ͨѶЭ��
const wchar_t * const PROTOCOL_PBT		= L"NHPZ10";		// ƽ���ƶ�̨ͨѶЭ��
const wchar_t * const PROTOCOL_PS		= L"";				// ���俪��ͨѶЭ��
const wchar_t * const PROTOCOL_BS_MT	= L"";				// ɨ��ǹ(�˹�)ͨѶЭ��
const wchar_t * const PROTOCOL_BS_OL	= L"";				// ɨ��ǹ(����)ͨѶЭ��
const wchar_t * const PROTOCOL_SLM		= L"HY114";			// ������ͨѶЭ��
const wchar_t * const PROTOCOL_MFT		= L"SG210";			// ̤������������ͨѶЭ��
const wchar_t * const PROTOCOL_SAT		= L"NHZJ10";		// ת��̨ͨѶЭ��
const wchar_t * const PROTOCOL_INS		= L"YD9850A";		// ��Ե��ͨѶЭ��
const wchar_t * const PROTOCOL_TAC		= L"NHRPM5300";		// ת�ټ�ͨѶЭ��
const wchar_t * const PROTOCOL_ST		= L"NHXJ";			// ����̨ͨѶЭ��
const wchar_t * const PROTOCOL_DYN		= L"NANHUA";		// �⹦��ͨѶЭ��
const wchar_t * const PROTOCOL_WOT		= L"NHLP";			// ��ƫ̨ͨѶЭ��
const wchar_t * const PROTOCOL_FCM		= L"NHTY1";			// �ͺ���ͨѶЭ��

//��������˵��
const CStringW g_strDimFeature[][2] =
{
	{L"01", L"�����÷�����ת���ɴ����ᴫ�ݶ��������м�ʻ���Ҽ�ʻԱ���κ��������Ʒ���ÿռ�ʱ���������������ߵ���ֵ�ֱ�Ϊ5200mm��1800mm��2200 mm"}, 
	{L"02", L"������ֵ�������ڲ�������ΪĿ�ĵ�ר����ҵ��"}, 
	{L"03", L"������������������26000kg���������ػ��ĳ�����ֵΪ13000mm"}, 
	{L"04", L"���������ʻ�ҷ����һ���Ϊ������ʽʱ��������ֵ����1000mm"}, 
	{L"05", L"���ڻ���Ϊ������ʽ����ʽ����(�һ������ʻ�ҷ���)��������ʽ��ʽ��ҳ���������ʽ��ʽ�����г����Լ���������11000mm�Ŀͳ������������ֵΪ2550mm"}, 
	{L"06", L"������ʻ��˫��ͳ����������ֵΪ4200mm"}, 
	{L"07", L"���Ͳ��ɲ������ĵ�ƽ��ר�ð�ҳ�������ֵ3000mm"}, 
	{L"08", L"������ֵ�����������Ͳ��ɲ������ĵ�ƽ��ר�ð�ҳ������ͳ�����ר�ð�ҳ�(����ǣ������ɵ��г���������ϱ���׼�涨)�����͵��䳤�ȴ���12.2m(40Ӣ��)��װ��Ŀ��ʽ��װ���ҳ�"}, 
	{L"09", L"����������ʽ��ʽ��ҳ�����װ���ҳ����Լ�������������г��Ĺ�ʽ��ҳ������������ֵΪ13000mm"}, 
	{L"10", L"��2008��1��1�����ڸߵȼ���·��ʹ�õ�������ʽ��ʽ��ҳ������������ֵΪ14600mm"}, 
	{L"11", L"���Ͳ��ɲ������ĵ�ƽ���г������͵��䳤�ȴ���12.2m(40Ӣ��)��װ��Ŀ��ʽ��װ���г����⣻��2008��1��1������������ʽ��ʽ��ҳ���ɵĽ½��г��ڸߵȼ���·��ʹ��ʱ�����������ֵΪ18100mm"}, 
	{L"12", L"���Ͳ��ɲ������ĵ�ƽ��ҳ��г�������ֵ3000mm"}, 
	{L"13", L"���ڼ�װ��ҳ��г�ָװ���ռ�װ��ʱ�ĸ߶ȡ�2007��1��1����ǰ����װ��ҳ��г��ĳ��������ֵΪ4200mm"},
};

//�ŷż��ⷽ��
const CStringW g_strEmiDetType[10] = {
	L"" 
	, L"��̬" 
	, L"����˲̬"
	, L"���ؼ���"
	, L"˫����"
	, L"��͸�����ɼ���"
	, L"��ֽʽ���ɼ���"
	, L"ũ�ó����ɼ���"
	, L"Ħ�г�����"
	, L"Ħ�г�˫����"
};

// kg->daN
#define KG2DAN 0.98f

// ����߶Ⱦ������
const unsigned int g_unBoxHeiAE = 50;
// ����߶�������
const unsigned int g_unBoxHeiRE = 2;
// �ҳ����������ֵ
const unsigned int g_unTlDimAE = 100;
// �ҳ���������ֵ
const unsigned int g_unTlDimRE = 2;
// ��ҳ�������
const unsigned int g_unHalfTlLen_UpperLimit = 13750;
// ȫ�ҳ�������
const unsigned int g_unFullTlLen_UpperLimit = 12000;
// ���ó��г���������
const unsigned int g_unPasVehTnLen_UpperLimit = 14500;
// �����г���������
const unsigned int g_unGooVehTnLen_UpperLimit = 20000;
// �����г���������(������ҳ�)
const unsigned int g_unGooVehMidTnLen_UpperLimit = 22000;
// �½��г���������
const unsigned int g_unArtiVehTnLen_UpperLimit = 17100;
// �ҳ�&�г���������
const unsigned int g_unWid_UpperLimit = 2550;
// �ҳ�&�г���������
const unsigned int g_unHei_UpperLimit = 4000;

struct SVehDimensionInfo
{
	// ����������λ��mm
	int nVehLength;
	// ��������λ��mm
	int nVehWidth;
	// �����ߣ���λ��mm
	int nVehHeight;
	// ����ߣ���λ��mm
	int nBoxHeight;
	// ���䳤����λ��mm
	int nCompartmentLength;

	// �������ж�
	bool bVehLengthJudge;
	// �������ж�
	bool bVehWidthJudge;
	// �������ж�
	bool bVehHeightJudge;
	// ������ж�
	bool bBoxHeightJudge;
	// ���䳤�ж�
	bool bCompartmentLengthJudge;

	// ����࣬��λ��mm
	int nWheBase01;
	// 12���[mm]
	int nWheBase12;
	// 23���[mm]
	int nWheBase23;
	// 34���[mm]
	int nWheBase34;
	// 45���[mm]
	int nWheBase45;
	// 56���[mm]
	int nWheBase56;

	// ������ж�
	bool bWheBase01Jud;
	// 12����ж�
	bool bWheBase12Jud;
	// 23����ж�
	bool bWheBase23Jud;
	// 34����ж�
	bool bWheBase34Jud;
	// 45����ж�
	bool bWheBase45Jud;
	// 56����ж�
	bool bWheBase56Jud;
	// ��ࣨ������ࣩ�ж� 
	bool bWheBaseJud;

	// ����ԭʼ������λ��mm
	int nVehOrigLength;
	// ����ԭʼ����λ��mm
	int nVehOrigWidth;
	// ����ԭʼ�ߣ���λ��mm
	int nVehOrigHeight;

	// ����������ԭ��
	CString strVehLengthUpdateReason;
	// ���������ԭ��
	CString strVehWidthUpdateReason;
	// ����ԭʼ�ߣ���λ��mm
	CString strVehHeightUpdateReason;

	// ��������ֵ����λ��mm
	int nVehLengthUpLimit;
	int nVehLengthLoLimit;
	// ��������ֵ����λ��mm
	int nVehWidthUpLimit;
	int nVehWidthLoLimit;
	// ��������ֵ����λ��mm
	int nVehHeightUpLimit;
	int nVehHeightLoLimit;
	// �������ֵ����λ��mm
	int nBoxHeightUpLimit;
	int nBoxHeightLoLimit;
	// ���䳤��ֵ����λ��mm
	int nCompartmentLengthUpLimit;
	int nCompartmentLengthLoLimit;
	// ����Ƿ�ͨ��
	bool bIsDetPass;
};

#endif