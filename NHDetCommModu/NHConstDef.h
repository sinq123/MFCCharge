/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：NHConstDef.h
* 文件标识：
* 描述：安综检常量定义
*
* 版本：1.0
* 日期：2011-06-xx
* 作者：Cyx
*
*
* 历史信息：
*
* 版本：1.0.0Beta1
* 日期：2011-06-xx
* 作者：Cyx
* 描述：正在开发
*/

#ifndef NHCONSTDEF_H
#define NHCONSTDEF_H

// 是否使用GB7258-2017
#ifndef USE_GB7258_2017
#define USE_GB7258_2017
#endif

#include <atlstr.h> 


// 本软件标识
//const wchar_t * const SW_NAME = L"华贝机动车综合性能检测控制管理软件";
const wchar_t * const SW_NAME = L"机动车安综检测软件";
const wchar_t * const SW_CODE = L"NHSMDS";
const wchar_t * const SW_VER = L"2.1";
const wchar_t * const SW_C01 = L"业务管理"; // 客户端1
const wchar_t * const SW_C02 = L"调度";
const wchar_t * const SW_C03 = L"工位控制";
const wchar_t * const SW_C04 = L"综检人工数据录入";
const wchar_t * const SW_C05 = L"安检人工数据录入";


// 本工程项目标识
// 见NHEngPro.h


// 数据库灯光垂直偏移固定为上负
// 国标灯光垂直偏移是否上正
const bool GB_HLVO_UP_PLUS = true;
// 数据库灯光水平偏移固定为左负
// 国标灯光水平偏移是否左负
const bool GB_HLHO_LEFT_MINUS = true;

////////////////////////////////////////////////////////// 工位工作状态定义-begin
// 一般
const wchar_t * const WPS_GEN_MAL = L"0";  // 故障
const wchar_t * const WPS_GEN_REA = L"1";  // 就绪
const wchar_t * const WPS_GEN_DEM = L"2";  // 标定
const wchar_t * const WPS_GEN_SEL = L"3";  // 自检
const wchar_t * const WPS_GEN_INI = L"4";  // 初始化
const wchar_t * const WPS_GEN_OTH = L"99";  // 其他

// 排放-ASM
const wchar_t * const WPS_EM_ASM_PRE = L"ASM0";  // 排放_ASM_准备检测
const wchar_t * const WPS_EM_ASM_ING = L"ASM1";  // 排放_ASM_正在检测
const wchar_t * const WPS_EM_ASM_FIN = L"ASM2";  // 排放_ASM_完成检测
const wchar_t * const WPS_EM_ASM_SKI = L"ASM3";  // 排放_ASM_跳过检测
const wchar_t * const WPS_EM_ASM_RET = L"ASM4";  // 排放_ASM_免除检测

// 排放-LUGDOWN
const wchar_t * const WPS_EM_LUGDOWN_PRE = L"LUGDOWN0";  // 排放_LUGDOWN_准备检测
const wchar_t * const WPS_EM_LUGDOWN_ING = L"LUGDOWN1";  // 排放_LUGDOWN_正在检测
const wchar_t * const WPS_EM_LUGDOWN_FIN = L"LUGDOWN2";  // 排放_LUGDOWN_完成检测
const wchar_t * const WPS_EM_LUGDOWN_SKI = L"LUGDOWN3";  // 排放_LUGDOWN_跳过检测
const wchar_t * const WPS_EM_LUGDOWN_RET = L"LUGDOWN4";  // 排放_LUGDOWN_免除检测

// 排放-双怠速
const wchar_t * const WPS_EM_DIS_PRE = L"DIS0";  // 排放_双怠速_准备检测
const wchar_t * const WPS_EM_DIS_HIS_ING = L"DIS1";  // 排放_双怠速_高怠速_正在检测
const wchar_t * const WPS_EM_DIS_HIS_FIN = L"DIS2";  // 排放_双怠速_高怠速_完成检测
const wchar_t * const WPS_EM_DIS_LIS_ING = L"DIS3";  // 排放_双怠速_低怠速_正在检测
const wchar_t * const WPS_EM_DIS_LIS_FIN = L"DIS4";  // 排放_双怠速_低怠速_完成检测
const wchar_t * const WPS_EM_DIS_FIN = L"DIS5";  // 排放_双怠速_完成检测
const wchar_t * const WPS_EM_DIS_SKI = L"DIS6";  // 排放_双怠速_跳过检测
const wchar_t * const WPS_EM_DIS_RET = L"DIS7";  // 排放_双怠速_免除检测

// 排放-不透光自由加速
const wchar_t * const WPS_EM_FAOPA_PRE = L"FAOPA0";  // 排放_不透光自由加速_准备检测
const wchar_t * const WPS_EM_FAOPA_ING = L"FAOPA1";  // 排放_不透光自由加速_正在检测
const wchar_t * const WPS_EM_FAOPA_FIN = L"FAOPA2";  // 排放_不透光自由加速_完成检测
const wchar_t * const WPS_EM_FAOPA_SKI = L"FAOPA3";  // 排放_不透光自由加速_跳过检测
const wchar_t * const WPS_EM_FAOPA_RET = L"FAOPA4";  // 排放_不透光自由加速_免除检测

// 排放-滤纸式自由加速
const wchar_t * const WPS_EM_FASMO_PRE = L"FASMO0";  // 排放_滤纸式自由加速_准备检测
const wchar_t * const WPS_EM_FASMO_ING = L"FASMO1";  // 排放_滤纸式自由加速_正在检测
const wchar_t * const WPS_EM_FASMO_FIN = L"FASMO2";  // 排放_滤纸式自由加速_完成检测
const wchar_t * const WPS_EM_FASMO_SKI = L"FASMO3";  // 排放_滤纸式自由加速_跳过检测
const wchar_t * const WPS_EM_FASMO_RET = L"FASMO4";  // 排放_滤纸式自由加速_免除检测

// 车速表
const wchar_t * const WPS_SM_PRE = L"SM0";  // 车速表_准备检测
const wchar_t * const WPS_SM_ING = L"SM1";  // 车速表_正在检测
const wchar_t * const WPS_SM_FIN = L"SM2";  // 车速表_完成检测
const wchar_t * const WPS_SM_SKI = L"SM3";  // 车速表_跳过检测
const wchar_t * const WPS_SM_RET = L"SM4";  // 车速表_免除检测

// 人工
const wchar_t * const WPS_MN_PRE = L"MN0";  // 人工_准备检测
const wchar_t * const WPS_MN_ING = L"MN1";  // 人工_正在检测
const wchar_t * const WPS_MN_FIN = L"MN2";  // 人工_完成检测
const wchar_t * const WPS_MN_SKI = L"MN4";  // 人工_跳过检测
const wchar_t * const WPS_MN_RET = L"MN5";  // 人工_免除检测

// 前照灯
const wchar_t * const WPS_HL_PRE = L"HL0";     // 前照灯_准备检测
const wchar_t * const WPS_HL_LL_ING = L"HL1";  // 前照灯_左灯_正在检测
const wchar_t * const WPS_HL_LL_FIN = L"HL2";  // 前照灯_左灯_完成检测
const wchar_t * const WPS_HL_RL_ING = L"HL3";  // 前照灯_右灯_正在检测
const wchar_t * const WPS_HL_RL_FIN = L"HL4";  // 前照灯_右灯_完成检测
const wchar_t * const WPS_HL_FIN = L"HL5";     // 前照灯_完成检测
const wchar_t * const WPS_HL_SKI = L"HL6";     // 前照灯_跳过检测
const wchar_t * const WPS_HL_RET = L"HL7";     // 前照灯_免除检测

// 侧滑
const wchar_t * const WPS_SS_PRE = L"SS0";  // 侧滑_准备检测
const wchar_t * const WPS_SS_ING = L"SS1";  // 侧滑_正在检测
const wchar_t * const WPS_SS_FIN = L"SS2";  // 侧滑_完成检测
const wchar_t * const WPS_SS_SKI = L"SS3";  // 侧滑_跳过检测
const wchar_t * const WPS_SS_RET = L"SS4";  // 侧滑_免除检测

// 轮重
const wchar_t * const WPS_AL_PRE = L"AL0";      // 轮重_准备检测
const wchar_t * const WPS_AL_A1_ING = L"AL1";   // 轮重_一轴_正在检测
const wchar_t * const WPS_AL_A1_FIN = L"AL2";   // 轮重_一轴_完成检测
const wchar_t * const WPS_AL_A2_ING = L"AL3";   // 轮重_二轴_正在检测
const wchar_t * const WPS_AL_A2_FIN = L"AL4";   // 轮重_二轴_完成检测
const wchar_t * const WPS_AL_A3_ING = L"AL5";   // 轮重_三轴_正在检测
const wchar_t * const WPS_AL_A3_FIN = L"AL6";   // 轮重_三轴_完成检测
const wchar_t * const WPS_AL_A4_ING = L"AL7";   // 轮重_四轴_正在检测
const wchar_t * const WPS_AL_A4_FIN = L"AL8";   // 轮重_四轴_完成检测
const wchar_t * const WPS_AL_A5_ING = L"AL9";   // 轮重_五轴_正在检测
const wchar_t * const WPS_AL_A5_FIN = L"AL10";  // 轮重_五轴_完成检测
const wchar_t * const WPS_AL_A6_ING = L"AL11";  // 轮重_六轴_正在检测
const wchar_t * const WPS_AL_A6_FIN = L"AL12";  // 轮重_六轴_完成检测
const wchar_t * const WPS_AL_FIN = L"AL13";     // 轮重_完成检测
const wchar_t * const WPS_AL_SKI = L"AL14";     // 轮重_跳过检测
const wchar_t * const WPS_AL_RET = L"AL15";     // 轮重_免除检测

// 制动
const wchar_t * const WPS_BK_PRE = L"BK0";        // 制动_准备检测
const wchar_t * const WPS_BK_A1SB_ING = L"BK1";   // 制动_一轴行车_正在检测
const wchar_t * const WPS_BK_A1SB_FIN = L"BK2";   // 制动_一轴行车_完成检测
const wchar_t * const WPS_BK_A1PB_ING = L"BK3";   // 制动_一轴驻车_正在检测
const wchar_t * const WPS_BK_A1PB_FIN = L"BK4";   // 制动_一轴驻车_完成检测
const wchar_t * const WPS_BK_A2SB_ING = L"BK5";   // 制动_二轴行车_正在检测
const wchar_t * const WPS_BK_A2SB_FIN = L"BK6";   // 制动_二轴行车_完成检测
const wchar_t * const WPS_BK_A2PB_ING = L"BK7";   // 制动_二轴驻车_正在检测
const wchar_t * const WPS_BK_A2PB_FIN = L"BK8";   // 制动_二轴驻车_完成检测
const wchar_t * const WPS_BK_A3SB_ING = L"BK9";   // 制动_三轴行车_正在检测
const wchar_t * const WPS_BK_A3SB_FIN = L"BK10";  // 制动_三轴行车_完成检测
const wchar_t * const WPS_BK_A3PB_ING = L"BK11";  // 制动_三轴驻车_正在检测
const wchar_t * const WPS_BK_A3PB_FIN = L"BK12";  // 制动_三轴驻车_完成检测
const wchar_t * const WPS_BK_A4SB_ING = L"BK13";  // 制动_四轴行车_正在检测
const wchar_t * const WPS_BK_A4SB_FIN = L"BK14";  // 制动_四轴行车_完成检测
const wchar_t * const WPS_BK_A4PB_ING = L"BK15";  // 制动_四轴驻车_正在检测
const wchar_t * const WPS_BK_A4PB_FIN = L"BK16";  // 制动_四轴驻车_完成检测
const wchar_t * const WPS_BK_A5SB_ING = L"BK17";  // 制动_五轴行车_正在检测
const wchar_t * const WPS_BK_A5SB_FIN = L"BK18";  // 制动_五轴行车_完成检测
const wchar_t * const WPS_BK_A5PB_ING = L"BK19";  // 制动_五轴驻车_正在检测
const wchar_t * const WPS_BK_A5PB_FIN = L"BK20";  // 制动_五轴驻车_完成检测
const wchar_t * const WPS_BK_A6SB_ING = L"BK21";  // 制动_六轴行车_正在检测
const wchar_t * const WPS_BK_A6SB_FIN = L"BK22";  // 制动_六轴行车_完成检测
const wchar_t * const WPS_BK_A6PB_ING = L"BK23";  // 制动_六轴驻车_正在检测
const wchar_t * const WPS_BK_A6PB_FIN = L"BK24";  // 制动_六轴驻车_完成检测
const wchar_t * const WPS_BK_FIN = L"BK25";       // 制动_完成检测
const wchar_t * const WPS_BK_SKI = L"BK26";       // 制动_跳过检测
const wchar_t * const WPS_BK_RET = L"BK27";       // 制动_免除检测

// 声级
const wchar_t * const WPS_SL_PRE = L"SL0";  // 声级_准备检测
const wchar_t * const WPS_SL_ING = L"SL1";  // 声级_正在检测
const wchar_t * const WPS_SL_FIN = L"SL2";  // 声级_完成检测
const wchar_t * const WPS_SL_SKI = L"SL3";  // 声级_跳过检测
const wchar_t * const WPS_SL_RET = L"SL4";  // 声级_免除检测

// 转角
const wchar_t * const WPS_SA_PRE = L"SA0";     // 转角_准备检测
const wchar_t * const WPS_SA_LA_ING = L"SA1";  // 转角_左转角_正在检测
const wchar_t * const WPS_SA_LA_FIN = L"SA2";  // 转角_左转角_完成检测
const wchar_t * const WPS_SA_RA_ING = L"SA3";  // 转角_右转角_正在检测
const wchar_t * const WPS_SA_RA_FIN = L"SA4";  // 转角_右转角_完成检测
const wchar_t * const WPS_SA_FIN = L"SA5";     // 转角_完成检测
const wchar_t * const WPS_SA_SKI = L"SA6";     // 转角_跳过检测
const wchar_t * const WPS_SA_RET = L"SA7";     // 转角_免除检测

// 功率
const wchar_t * const WPS_PWR_PRE = L"PWR0";  // 功率_准备检测
const wchar_t * const WPS_PWR_ING = L"PWR1";  // 功率_正在检测
const wchar_t * const WPS_PWR_FIN = L"PWR2";  // 功率_完成检测
const wchar_t * const WPS_PWR_SKI = L"PWR3";  // 功率_跳过检测
const wchar_t * const WPS_PWR_RET = L"PWR4";  // 功率_免除检测

// 绝缘
const wchar_t * const WPS_INS_PRE = L"INS0";  // 绝缘_准备检测
const wchar_t * const WPS_INS_ING = L"INS1";  // 绝缘_正在检测
const wchar_t * const WPS_INS_FIN = L"INS2";  // 绝缘_完成检测
const wchar_t * const WPS_INS_SKI = L"INS3";  // 绝缘_跳过检测
const wchar_t * const WPS_INS_RET = L"INS4";  // 绝缘_免除检测

// 悬架
const wchar_t * const WPS_ST_PRE = L"ST0";     // 悬架_准备检测
const wchar_t * const WPS_ST_A1_ING = L"ST1";  // 悬架_前轴_正在检测
const wchar_t * const WPS_ST_A1_FIN = L"ST2";  // 悬架_前轴_完成检测
const wchar_t * const WPS_ST_A2_ING = L"ST3";  // 悬架_后轴_正在检测
const wchar_t * const WPS_ST_A2_FIN = L"ST4";  // 悬架_后轴_完成检测
const wchar_t * const WPS_ST_FIN = L"ST5";     // 悬架_完成检测
const wchar_t * const WPS_ST_SKI = L"ST6";     // 悬架_跳过检测
const wchar_t * const WPS_ST_RET = L"ST7";     // 悬架_免除检测

// 轮偏
const wchar_t * const WPS_WO_PRE = L"WO0";  // 轮偏_准备检测
const wchar_t * const WPS_WO_ING = L"WO1";  // 轮偏_正在检测
const wchar_t * const WPS_WO_FIN = L"WO2";  // 轮偏_完成检测
const wchar_t * const WPS_WO_SKI = L"WO3";  // 轮偏_跳过检测
const wchar_t * const WPS_WO_RET = L"WO4";  // 轮偏_免除检测

// 整备质量
const wchar_t * const WPS_UM_PRE = L"UM0";  // 整备质量_准备检测
const wchar_t * const WPS_UM_ING = L"UM1";  // 整备质量_正在检测
const wchar_t * const WPS_UM_FIN = L"UM2";  // 整备质量_完成检测
const wchar_t * const WPS_UM_SKI = L"UM3";  // 整备质量_跳过检测
const wchar_t * const WPS_UM_RET = L"UM4";  // 整备质量_免除检测

// 外廓
const wchar_t * const WPS_DIM_PRE = L"DIM0";  // 外廓_准备检测
const wchar_t * const WPS_DIM_ING = L"DIM1";  // 外廓_正在检测
const wchar_t * const WPS_DIM_FIN = L"DIM2";  // 外廓_完成检测
const wchar_t * const WPS_DIM_SKI = L"DIM3";  // 外廓_跳过检测
const wchar_t * const WPS_DIM_RET = L"DIM4";  // 外廓_免除检测

// 油耗
const wchar_t * const WPS_FC_PRE = L"FC0";  // 油耗_准备检测
const wchar_t * const WPS_FC_ING = L"FC1";  // 油耗_正在检测
const wchar_t * const WPS_FC_FIN = L"FC2";  // 油耗_完成检测
const wchar_t * const WPS_FC_SKI = L"FC3";  // 油耗_跳过检测
const wchar_t * const WPS_FC_RET = L"FC4";  // 油耗_免除检测
////////////////////////////////////////////////////////// 工位工作状态定义-end

////////////////////////////////////////////////////////// 网络数据包格式相关常量，根据"调度软件与工位控制软件通讯协议"-begin
// 网络数据包(最大)容量[Byte]
const unsigned int g_unNetPackSize = 1024;
// 网络数据包包头大小[Byte]
const unsigned int g_unNetPackHeaderSize = 2;
// 网络数据包"数据段大小指示区(DataSecSizePointer)"大小
const unsigned int g_unNetPackDSSPSize = 4;
// 网络数据包包尾大小[Byte]
const unsigned int g_unNetPackTailSize = 2;
// 请求编号QN大小
const unsigned int g_unQNSize = 17;
// 总包数PCNT大小
const unsigned int g_unPCNTSize = 4;
// 包号PNO大小
const unsigned int g_unPNOSize = 4;
// 网络数据包各标识占用的总大小
const unsigned int g_unNetPackSignsSize = g_unNetPackHeaderSize + g_unNetPackDSSPSize + g_unNetPackTailSize + g_unQNSize + g_unPCNTSize + g_unPNOSize;
// 网络数据包(最大)负载容量
const unsigned int g_unNetPackPayloadSize = g_unNetPackSize - g_unNetPackSignsSize;
// 包头标识
const char * const g_pchNetPackHeaderSign = "##";
// 包尾标识
const char * const g_pchNetPackTailSign = "\r\n";
////////////////////////////////////////////////////////// 网络数据包格式相关常量，根据"调度软件与工位控制软件通讯协议"-end

//常用颜色表	英文代码					//形像颜色	HEX格式		RGB格式
#define COLOR_ForestGreen	0x228B22		//森林绿	#228B22 	34,139,34
#define COLOR_DarkGreen		0x006400		//深绿色	#006400 	0,100,0
#define COLOR_FireBrick		0x2222B2		//耐火砖	#B22222 	178,34,34
#define COLOR_DarkRed		0x00008B		//深红色	#8B0000 	139,0,0
#define COLOR_Black		0x000000		//黑色	#000000 	0,0,0

// 判定代码，Judge Code
const wchar_t * const JD_Lev1 = L"-1";       // -1: 一级
const wchar_t * const JD_Lev2 = L"-2";       // -2: 二级
const wchar_t * const JD_Pass = L"0";       // 0: 合格
const wchar_t * const JD_Fail = L"1";       // 1: 不合格
const wchar_t * const JD_NotJud = L"2";       // 2: 不判定、不适用
const wchar_t * const JD_NotDet = L"";       // NULL: 未检

// 检测结论
const wchar_t * const DETCON_Lev1 = L"壹级";
const wchar_t * const DETCON_Lev2 = L"贰级";
const wchar_t * const DETCON_Pass = L"合格";
const wchar_t * const DETCON_Main = L"合格(建议维护)";
const wchar_t * const DETCON_Fail = L"不合格";
const wchar_t * const DETCON_NotJud = L"不判定";
const wchar_t * const DETCON_NotDet = L"";

// 判定字体颜色
#define COLOR_Pass			COLOR_DarkGreen
#define COLOR_NotPass		COLOR_FireBrick
#define COLOR_Fail			COLOR_NotPass
#define COLOR_NotJud		COLOR_Black

// 判定符号
const wchar_t * const LV1_SIGN = L"1";
const wchar_t * const LV2_SIGN = L"2";
const wchar_t * const PASS_SIGN = L"○";
const wchar_t * const FAIL_SIGN = L"×";
const wchar_t * const NOTJUD_SIGN = L"—";
const wchar_t * const NOTDET_SIGN = L"";

// 路试制动稳定性代码，Road ServiceBrake Stability Code
const wchar_t * const RDSBS_Left = L"-1";       // -1: 左跑偏
const wchar_t * const RDSBS_Pass = L"0";        // 0: 未跑偏
const wchar_t * const RDSBS_Right = L"1";       // 1: 右跑偏

// 路试制动稳定性名称
const wchar_t * const RDSBS_LEFT = L"左跑偏";       // -1: 左跑偏
const wchar_t * const RDSBS_PASS = L"未跑偏";        // 0: 未跑偏
const wchar_t * const RDSBS_RIGHT = L"右跑偏";       // 1: 右跑偏

// 判断类别代码
enum JudgeCode
{
	JD_LEV1 = -1, // 一级
	JD_LEV2 = -2, // 二级
	JD_PASS= 0,       // 合格
	JD_FAIL = 1,       // 不合格
	JD_NOTJUD = 2,      // 不判定、不适用
};


// 等级评定
enum RatEnum
{
	Rat_NotDet = 0, // 未检（NULL）
	Rat_Lev1 = -1, // 一级
	Rat_Lev2 = -2, // 二级
	Rat_Lev3 = 2, // 不适用
	Rat_Pass = 0, // 合格
	Rat_Fail = 1, // 不合格
};

// 连接状态
enum ConnectionStatusEnum
{
	CS_Unconnected = 0, // 未连接
	CS_Connecting,      // 正在连接
	CS_Connected,       // 已连接
};

const wchar_t * const CN_ST = L"ST"; // 同步时间
const wchar_t * const CN_GS = L"GS"; // 获取状态
const wchar_t * const CN_SS = L"SS"; // 发送状态
const wchar_t * const CN_EP = L"EP"; // 进入工位
const wchar_t * const CN_LP = L"LP"; // 离开工位
const wchar_t * const CN_RP = L"RP"; // 重置工位
const wchar_t * const CN_OL = L"OL"; // 逐步下线
const wchar_t * const CN_NL = L"NL"; // 车辆上线
const wchar_t * const CN_EC = L"EC"; // 执行命令行
const wchar_t * const CN_LI = L"LI"; // 点阵屏信息

// 检测项目代码
enum DetectItemEnum
{
	DI_NULL = 0,                // 空
	DI_Emission = 1,            // 排放检测
	DI_Speedometer = 2,         // 车速表检测
	DI_Manual = 3,              // 人工检测
	DI_HeadLight = 4,           // 前照灯检测
	DI_Sideslip = 5,            // 侧滑检测
	DI_AxleLoad = 6,            // 轮重检测
	DI_Brake = 7,               // 制动检测
	DI_Power = 8,               // 功率检测
	DI_SoundLevel = 9,          // 声级检测
	DI_SteeringAngle = 10,      // 转角检测
	DI_Suspension = 11,         // 悬架检测
	DI_WheelOffset = 12,        // 轮偏检测
	DI_Insulation = 13,         // 绝缘检测
	DI_Momentum = 14,           // 自由转动量检测
	DI_FuelCon = 15,            // 油耗检测
	DI_UM = 16,                 // 整备质量检测
	DI_Dimension = 17,          // 外廓检测
	DI_END = DI_Dimension,      // 结束
};

// 检验项目代码
enum InspectionItemEnum
{
	II_NULL = 0,				// 空
	II_NetQuery,				// 联网查询
	II_MD_Item1,				// 人工项目
	II_MD_Item2,				// 人工项目
	II_MD_Item3,				// 人工项目
	II_MD_Item4,				// 人工项目
	II_MD_Item5,				// 人工项目
	II_MD_Item6,				// 人工项目
	II_DI = II_MD_Item6,		// 外廓尺寸检测
	II_MD_Item7,				// 人工项目
	II_MD_Item8,				// 人工项目
	II_UM = II_MD_Item8,		// 整备质量检测
	II_MD_Item9,				// 人工项目
	II_MD_Item10,				// 人工项目
	II_MD_Item11,				// 人工项目
	II_MD_Item12,				// 人工项目
	II_MD_Item13,				// 人工项目
	II_MD_Item14,				// 人工项目
	II_MD_Item15,				// 人工项目
	II_MD_Item16,				// 人工项目
	II_MD_Item17,				// 人工项目
	II_MD_Item18,				// 人工项目
	II_MD_Item19,				// 人工项目
	II_MD_Item20,				// 人工项目
	II_MD_Item21,				// 人工项目
	II_MD_Item22,				// 人工项目
	II_MD_Item23,				// 人工项目
	II_MD_Item24,				// 人工项目
	II_MD_Item25,				// 人工项目
	II_MD_Item26,				// 人工项目
	II_MD_Item27,				// 人工项目
	II_MD_Item28,				// 人工项目
	II_MD_Item29,				// 人工项目
	II_MD_Item30,				// 人工项目
	II_MD_Item31,				// 人工项目
	II_MD_Item32,				// 人工项目
	II_MD_Item33,				// 人工项目
	II_MD_Item34,				// 人工项目
	II_MD_Item35,				// 人工项目
	II_MD_Item36,				// 人工项目
	II_MD_Item37,				// 人工项目
	II_MD_Item38,				// 人工项目
	II_MD_Item39,				// 人工项目
	II_MD_Item40,				// 人工项目
	II_MD_Item41,				// 人工项目
	II_MD_Item42,				// 人工项目
	II_MD_Item43,				// 人工项目
	II_MD_Item44,				// 人工项目
	II_MD_Item45,				// 人工项目
	II_MD_Item46,				// 人工项目
	II_MD_Item47,				// 人工项目
	II_MD_Item48,				// 人工项目
	II_MD_Item49,				// 人工项目
	II_MD_Item50,				// 人工项目
	II_BK_SBRate,				// 空载行车制动率
	II_BK_UnbRate,              // 空载制动不平衡率
	II_BK_Load_SBRate,			// 加载行车制动率
	II_BK_Load_UnbRate,         // 加载制动不平衡率
	II_BK_PBRate,				// 驻车制动率
	II_HL_INT,					// 前照灯光强
	II_HL_VO,					// 前照灯垂直偏移
	II_ED_DIS,					// 排放检测
	II_ED_FAOPA,				// 排放检测
	II_ED_FASMO,				// 排放检测
	II_SM,						// 车速表检测
	II_SS,						// 侧滑检测
};

// 排放检测项目代码
enum EmissionDetectItemEnum
{
	EDI_ERR = 0,       // 错误代码
	EDI_ASM = 1,       // 稳态
	EDI_VMAS = 2,      // 简易瞬态
	EDI_LUGDOWN = 3,   //加载减速
	EDI_DIS = 4,       // 双怠速
	EDI_FAOPA = 5,     // 不透光自由加速
	EDI_FASMO = 6,     // 滤纸式自由加速
	EDI_AVFASMO = 7,   // 农用车自由加速
	EDI_MIS = 8,       // 摩托车怠速
	EDI_MDIS = 9,      // 摩托车双怠速
};

// 人工检测项目代码
enum ManualDetectItemEnum
{
	MDI_ERR = 0,        // 错误代码
	MDI_Appearance = 1, // 外观
	MDI_Dynamic = 2,    // 动态
	MDI_Chassis = 3,    // 底盘
};

// 检测项目进度标识
enum DetectionProgressEnum
{
	DP_RemDet = 0,  // 免除检测
	DP_ToDet = 1,   // 等待检测
	DP_PreDet = 2,  // 准备检测
	DP_Deting = 3,  // 正在检测
	DP_FinDet = 4,  // 检测完成
};

// 命令错误代码
enum CommandErrCodeEnum
{
	CEC_Normal,     // 正常
	CEC_Exception,  // 异常
};

// 制动台类型
enum BrakeTesterType // TODO：加Enum
{
	BTT_Roller,			// 滚筒
	BTT_Platform,		// 平板
};
// 车速台类型
enum SpeedTesterType // TODO：修改为SpeedometerTester并加Enum
{
	STT_SpeedometerTester,		// 车速台
	STT_Dynamometer,			// 测功机
};

// 综检人工项目属性
enum  ManualItemAttEnum
{
	MIA_Key_Items ,		// 关键项
	MIA_Gen_Items ,		// 一般项
	MIA_Rank_Item ,		// 分级项
	MIA_VerEva_Item,    // 核查评定项
};
// 检测业务状态代码
// Business Status
// 参照 "NHSTDCMS机动车安全检测控制管理系统代码表.doc, 车辆检测状态代码 部分"

const wchar_t * const DS_ToDet = L"TODET";           // 等待检测
const wchar_t * const DS_PreDet = L"PREDET";         // 准备检测
const wchar_t * const DS_Deting = L"DETING";         // 正在检测
const wchar_t * const DS_FinDet = L"FINDET";         // 检测完成
const wchar_t * const DS_CanDet = L"CANDET";         // 检测取消
const wchar_t * const DS_DIS = L"DIS";               // 正在检测双怠速
const wchar_t * const DS_FAOPA = L"FAOPA";           // 正在检测不透光
const wchar_t * const DS_FASMO= L"FASMO";            // 正在检测滤纸式
const wchar_t * const DS_SM = L"SM";                 // 正在检测车速表
const wchar_t * const DS_APP = L"APP";               // 正在检测外观
const wchar_t * const DS_DYN = L"DYN";               // 正在检测动态
const wchar_t * const DS_CHA = L"CHS";               // 正在检测底盘
const wchar_t * const DS_HL = L"HL";                 // 正在检测前照灯
const wchar_t * const DS_HLL = L"HLL";               // 正在检测左灯
const wchar_t * const DS_HLR = L"HLR";               // 正在检测右灯
const wchar_t * const DS_SS = L"SS";                 // 正在检测侧滑
const wchar_t * const DS_AL = L"AL";                 // 正在检测轮重
const wchar_t * const DS_AL1 = L"AL1";               // 正在检测一轴轮重
const wchar_t * const DS_AL2 = L"AL2";               // 正在检测二轴轮重
const wchar_t * const DS_AL3 = L"AL3";               // 正在检测三轴轮重
const wchar_t * const DS_AL4 = L"AL4";               // 正在检测四轴轮重
const wchar_t * const DS_SB = L"SB";                 // 正在检测行车制动
const wchar_t * const DS_SB1 = L"SB1";               // 正在检测一轴行车制动
const wchar_t * const DS_SB2 = L"SB2";               // 正在检测二轴行车制动
const wchar_t * const DS_SB3 = L"SB3";               // 正在检测三轴行车制动
const wchar_t * const DS_SB4 = L"SB4";               // 正在检测四轴行车制动
const wchar_t * const DS_PB = L"PB";                 // 正在检测驻车制动
const wchar_t * const DS_SL = L"SL";                 // 正在检测声级
const wchar_t * const DS_SA = L"SA";                 // 正在检测转角
const wchar_t * const DS_SAL = L"SAL";               // 正在检测左转角
const wchar_t * const DS_SAR = L"SAR";               // 正在检测右转角
const wchar_t * const DS_INS = L"INS";               // 正在检测绝缘
const wchar_t * const DS_UM = L"UM";                 // 正在检测整备质量
const wchar_t * const DS_FC = L"FC";                 // 正在检测油耗

// 内置账号
const wchar_t * const BUILT_IN_USER = L"NH@"; // 内置用户
const wchar_t * const BUILT_IN_PWD = L"$%PKU%$"; // 内置密码

// 串口号
const wchar_t * const COM_PORT_LED		= L"1";             // 点阵屏串口号
const wchar_t * const COM_PORT_ANA		= L"2";             // 分析仪串口号
const wchar_t * const COM_PORT_OPA		= L"3";             // 不透光串口号
const wchar_t * const COM_PORT_SMO		= L"4";             // 烟度计串口号
const wchar_t * const COM_PORT_SMT		= L"5";             // 车速台串口号
const wchar_t * const COM_PORT_HLT_L	= L"6";             // 灯光仪(左)串口号
const wchar_t * const COM_PORT_HLT_R	= L"7";             // 灯光仪(右)串口号
const wchar_t * const COM_PORT_SST		= L"8";             // 侧滑台串口号
const wchar_t * const COM_PORT_ALS		= L"9";             // 轮重仪串口号
const wchar_t * const COM_PORT_RBT		= L"10";            // 滚筒制动台串口号
const wchar_t * const COM_PORT_PBT		= L"11";            // 平板制动台串口号
const wchar_t * const COM_PORT_PS		= L"12";            // 对射开关串口号
const wchar_t * const COM_PORT_BS_MT	= L"13";            // 扫描枪(人工)串口号
const wchar_t * const COM_PORT_BS_OL	= L"14";            // 扫描枪(上线)串口号
const wchar_t * const COM_PORT_SLM		= L"15";            // 声级计串口号
const wchar_t * const COM_PORT_MFT		= L"16";            // 踏板力手拉力计串口号
const wchar_t * const COM_PORT_SAT		= L"17";            // 转角台串口号
const wchar_t * const COM_PORT_INS		= L"18";            // 绝缘仪串口号
const wchar_t * const COM_PORT_TAC		= L"19";            // 转速计串口号
const wchar_t * const COM_PORT_ST		= L"20";            // 悬架台串口号
const wchar_t * const COM_PORT_DYN		= L"21";            // 测功机串口号
const wchar_t * const COM_PORT_WOT		= L"22";            // 轮偏台串口号
const wchar_t * const COM_PORT_FCM		= L"23";            // 油耗仪串口号

// 波特率
const wchar_t * const BAUD_RATE_LED		= L"19200";         // 点阵屏波特率
const wchar_t * const BAUD_RATE_ANA		= L"9600";          // 分析仪波特率
const wchar_t * const BAUD_RATE_OPA		= L"9600";          // 不透光波特率
const wchar_t * const BAUD_RATE_SMO		= L"2400";          // 烟度计波特率
const wchar_t * const BAUD_RATE_SMT		= L"38400";         // 车速台波特率
const wchar_t * const BAUD_RATE_HLT_L	= L"2400";          // 灯光仪(左)波特率
const wchar_t * const BAUD_RATE_HLT_R	= L"2400";          // 灯光仪(右)波特率
const wchar_t * const BAUD_RATE_SST		= L"38400";         // 侧滑台波特率
const wchar_t * const BAUD_RATE_ALS		= L"38400";         // 轮重仪波特率
const wchar_t * const BAUD_RATE_RBT		= L"38400";         // 滚筒制动台波特率
const wchar_t * const BAUD_RATE_PBT		= L"38400";         // 平板制动台波特率
const wchar_t * const BAUD_RATE_PS		= L"38400";         // 对射开关波特率
const wchar_t * const BAUD_RATE_BS_MT	= L"9600";          // 扫描枪(人工)波特率
const wchar_t * const BAUD_RATE_BS_OL	= L"9600";          // 扫描枪(上线)波特率
const wchar_t * const BAUD_RATE_SLM		= L"9600";          // 声级计波特率
const wchar_t * const BAUD_RATE_MFT		= L"9600";          // 踏板力手拉力计波特率
const wchar_t * const BAUD_RATE_SAT		= L"38400";         // 转角台波特率
const wchar_t * const BAUD_RATE_INS		= L"9600";          // 绝缘仪波特率
const wchar_t * const BAUD_RATE_TAC		= L"9600";          // 转速计波特率
const wchar_t * const BAUD_RATE_ST		= L"38400";          // 悬架台波特率
const wchar_t * const BAUD_RATE_WOT		= L"38400";          // 轮偏台波特率
const wchar_t * const BAUD_RATE_FCM		= L"9600";           // 油耗仪波特率

// 通讯协议
const wchar_t * const PROTOCOL_LED		= L"NH50R";			// 点阵屏通讯协议
const wchar_t * const PROTOCOL_ANA		= L"503V";			// 分析仪通讯协议
const wchar_t * const PROTOCOL_OPA		= L"NHT6";			// 不透光通讯协议
const wchar_t * const PROTOCOL_SMO		= L"YD";			// 烟度计通讯协议
const wchar_t * const PROTOCOL_SMT		= L"NHM10";			// 车速台通讯协议
const wchar_t * const PROTOCOL_HLT_L	= L"NHD6108";		// 灯光仪(左)通讯协议
const wchar_t * const PROTOCOL_HLT_R	= L"NHD6108";		// 灯光仪(右)通讯协议
const wchar_t * const PROTOCOL_SST		= L"NHS10";			// 侧滑台通讯协议
const wchar_t * const PROTOCOL_ALS		= L"NHW10";			// 轮重仪通讯协议
const wchar_t * const PROTOCOL_RBT		= L"NHZ10";			// 滚筒制动台通讯协议
const wchar_t * const PROTOCOL_PBT		= L"NHPZ10";		// 平板制动台通讯协议
const wchar_t * const PROTOCOL_PS		= L"";				// 对射开关通讯协议
const wchar_t * const PROTOCOL_BS_MT	= L"";				// 扫描枪(人工)通讯协议
const wchar_t * const PROTOCOL_BS_OL	= L"";				// 扫描枪(上线)通讯协议
const wchar_t * const PROTOCOL_SLM		= L"HY114";			// 声级计通讯协议
const wchar_t * const PROTOCOL_MFT		= L"SG210";			// 踏板力手拉力计通讯协议
const wchar_t * const PROTOCOL_SAT		= L"NHZJ10";		// 转角台通讯协议
const wchar_t * const PROTOCOL_INS		= L"YD9850A";		// 绝缘仪通讯协议
const wchar_t * const PROTOCOL_TAC		= L"NHRPM5300";		// 转速计通讯协议
const wchar_t * const PROTOCOL_ST		= L"NHXJ";			// 悬架台通讯协议
const wchar_t * const PROTOCOL_DYN		= L"NANHUA";		// 测功机通讯协议
const wchar_t * const PROTOCOL_WOT		= L"NHLP";			// 轮偏台通讯协议
const wchar_t * const PROTOCOL_FCM		= L"NHTY1";			// 油耗仪通讯协议

//特征参数说明
const CStringW g_strDimFeature[][2] =
{
	{L"01", L"当采用方向盘转向、由传动轴传递动力、具有驾驶室且驾驶员座椅后设计有物品放置空间时，车长、车宽、车高的限值分别为5200mm、1800mm、2200 mm"}, 
	{L"02", L"车长限值不适用于不以运输为目的的专用作业车"}, 
	{L"03", L"最大设计总质量不超过26000kg的汽车起重机的车长限值为13000mm"}, 
	{L"04", L"当货厢与驾驶室分离且货厢为整体封闭式时，车长限值增加1000mm"}, 
	{L"05", L"对于货厢为整体封闭式的厢式货车(且货厢与驾驶室分离)、整体封闭式厢式半挂车及整体封闭式厢式汽车列车，以及车长大于11000mm的客车，车宽最大限值为2550mm"}, 
	{L"06", L"定线行驶的双层客车车高最大限值为4200mm"}, 
	{L"07", L"运送不可拆解物体的低平板专用半挂车车宽限值3000mm"}, 
	{L"08", L"车长限值不适用于运送不可拆解物体的低平板专用半挂车、运送车辆的专用半挂车(但与牵引车组成的列车长度需符合本标准规定)和运送单箱长度大于12.2m(40英尺)集装箱的框架式集装箱半挂车"}, 
	{L"09", L"对于整体封闭式厢式半挂车、集装箱半挂车，以及组成五轴汽车列车的罐式半挂车，车长最大限值为13000mm"}, 
	{L"10", L"自2008年1月1日起，在高等级公路上使用的整体封闭式厢式半挂车，车长最大限值为14600mm"}, 
	{L"11", L"运送不可拆解物体的低平板列车和运送单箱长度大于12.2m(40英尺)集装箱的框架式集装箱列车除外；自2008年1月1日起，与整体封闭式厢式半挂车组成的铰接列车在高等级公路上使用时，车长最大限值为18100mm"}, 
	{L"12", L"运送不可拆解物体的低平板挂车列车车宽限值3000mm"}, 
	{L"13", L"对于集装箱挂车列车指装备空集装箱时的高度。2007年1月1日以前，集装箱挂车列车的车高最大限值为4200mm"},
};

//排放检检测方法
const CStringW g_strEmiDetType[10] = {
	L"" 
	, L"稳态" 
	, L"简易瞬态"
	, L"加载减速"
	, L"双怠速"
	, L"不透光自由加速"
	, L"滤纸式自由加速"
	, L"农用车自由加速"
	, L"摩托车怠速"
	, L"摩托车双怠速"
};

// kg->daN
#define KG2DAN 0.98f

// 栏板高度绝对误差
const unsigned int g_unBoxHeiAE = 50;
// 栏板高度相对误差
const unsigned int g_unBoxHeiRE = 2;
// 挂车绝对误差限值
const unsigned int g_unTlDimAE = 100;
// 挂车相对误差限值
const unsigned int g_unTlDimRE = 2;
// 半挂车长上限
const unsigned int g_unHalfTlLen_UpperLimit = 13750;
// 全挂车长上限
const unsigned int g_unFullTlLen_UpperLimit = 12000;
// 乘用车列车车长上限
const unsigned int g_unPasVehTnLen_UpperLimit = 14500;
// 货车列车车长上限
const unsigned int g_unGooVehTnLen_UpperLimit = 20000;
// 货车列车车长上限(中置轴挂车)
const unsigned int g_unGooVehMidTnLen_UpperLimit = 22000;
// 铰接列车车长上限
const unsigned int g_unArtiVehTnLen_UpperLimit = 17100;
// 挂车&列车车宽上限
const unsigned int g_unWid_UpperLimit = 2550;
// 挂车&列车车高上限
const unsigned int g_unHei_UpperLimit = 4000;

struct SVehDimensionInfo
{
	// 整车长，单位：mm
	int nVehLength;
	// 整车宽，单位：mm
	int nVehWidth;
	// 整车高，单位：mm
	int nVehHeight;
	// 栏板高，单位：mm
	int nBoxHeight;
	// 车箱长，单位：mm
	int nCompartmentLength;

	// 整车长判定
	bool bVehLengthJudge;
	// 整车宽判定
	bool bVehWidthJudge;
	// 整车高判定
	bool bVehHeightJudge;
	// 栏板高判定
	bool bBoxHeightJudge;
	// 车箱长判定
	bool bCompartmentLengthJudge;

	// 销轴距，单位：mm
	int nWheBase01;
	// 12轴距[mm]
	int nWheBase12;
	// 23轴距[mm]
	int nWheBase23;
	// 34轴距[mm]
	int nWheBase34;
	// 45轴距[mm]
	int nWheBase45;
	// 56轴距[mm]
	int nWheBase56;

	// 销轴距判定
	bool bWheBase01Jud;
	// 12轴距判定
	bool bWheBase12Jud;
	// 23轴距判定
	bool bWheBase23Jud;
	// 34轴距判定
	bool bWheBase34Jud;
	// 45轴距判定
	bool bWheBase45Jud;
	// 56轴距判定
	bool bWheBase56Jud;
	// 轴距（含销轴距）判定 
	bool bWheBaseJud;

	// 整车原始长，单位：mm
	int nVehOrigLength;
	// 整车原始宽，单位：mm
	int nVehOrigWidth;
	// 整车原始高，单位：mm
	int nVehOrigHeight;

	// 整车长更新原因
	CString strVehLengthUpdateReason;
	// 整车宽更新原因
	CString strVehWidthUpdateReason;
	// 整车原始高，单位：mm
	CString strVehHeightUpdateReason;

	// 整车长限值，单位：mm
	int nVehLengthUpLimit;
	int nVehLengthLoLimit;
	// 整车宽限值，单位：mm
	int nVehWidthUpLimit;
	int nVehWidthLoLimit;
	// 整车高限值，单位：mm
	int nVehHeightUpLimit;
	int nVehHeightLoLimit;
	// 栏板高限值，单位：mm
	int nBoxHeightUpLimit;
	int nBoxHeightLoLimit;
	// 车箱长限值，单位：mm
	int nCompartmentLengthUpLimit;
	int nCompartmentLengthLoLimit;
	// 检测是否通过
	bool bIsDetPass;
};

#endif