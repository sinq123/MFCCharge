#ifndef NHENGPRO_H
#define NHENGPRO_H

// 工程项目包含安检
#ifndef ENG_PRO_STD
//#define ENG_PRO_STD
#endif

// 工程项目包含摩托车
#ifndef ENG_PRO_MOTO
#define ENG_PRO_MOTO
#endif

// 工程项目包含综检
#ifndef ENG_PRO_MFD
//#define ENG_PRO_MFD
#endif

// 开放宏(允许排放参与检测日志查询中的总判定)
//(NHBMS.h 和 NetWorkDetectionDlg.h和NetWorkDetThread.h同步修改)
// 工程项目包含汽修厂
#ifndef ENG_PRO_ARP
//#define ENG_PRO_ARP
#endif

// 工程项目包含安综检二合一
#ifndef ENG_PRO_SMD
#define ENG_PRO_SMD
#endif

//#ifndef ENG_STA_JYAT
//#define ENG_STA_JYAT //开启揭阳安通的特殊功能(1、未检测动力性或油耗时,NHCDS不打开测功机串口,以便不退出NHCDS,可直接检环保加载减速;2、检完悬架后,如有轮重项目,增加前轴退回悬架台流程,因悬架和轮重太近,检二轴悬架时,前轴已过了轮重仪)
//#endif

#ifndef ENG_STA_YGZST
#define ENG_STA_YGZST
#endif

//#ifndef ENG_STA_JMDQ //江门深奥
//#define ENG_STA_JMDQ
//#endif

const wchar_t * const ENG_PRO_NAME = L"GDSTDNHSMDS";	// 工程项目名
const wchar_t * const ENG_PRO_NAME_EX = L"粤标准版";	// 工程项目名
const wchar_t * const ENG_PRO_VERSION = L"2.1.0";  // 程序版本

// 综检报告单编号前9位
//const wchar_t * const MFD_STA_NUM = L"440605000"; // 综检检测站前9位编号（6位地区代码+3位检验机构代码）
const wchar_t * const MFD_STA_NUM = L"440982"; // 综检检测站前9位编号（6位地区代码+3位检验机构代码）

#endif