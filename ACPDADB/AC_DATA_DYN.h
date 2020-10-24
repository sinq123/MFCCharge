/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：AC_DATA_ROAD.h
* 文件标识：
* 描述：PDA动态检验数据表模型
*
* 版本：1.0
* 日期：2015-01-28
* 作者：Shaojm
*
*
* 历史信息：
*
* 版本：1.0.0
* 日期：2015-01-28
* 作者：Shaojm
* 描述：正在发布
*/


#if !defined (AC_DATA_DYN_H)
#define AC_DATA_DYN_H

#include <string>

struct SAC_DATA_DYN
{
	// 检验流水号
	std::wstring jylsh;
	// 安检机构编号
	std::wstring jyjgbh;
	// 检测线代号
	std::wstring jcxdh;
	// 检验次数
	std::wstring jycs;
	// 机动车序号
	std::wstring xh;
	// 号牌种类
	std::wstring hpzl;
	// 号牌号码
	std::wstring hphm;
	// 车辆类型
	std::wstring cllx;
	// 车辆识别代号
	std::wstring clsbdh;
	// 完成标志
	std::wstring flag;
	// 底盘动态检验员
	std::wstring dpdtjyy;
	// 不合格项
	std::wstring bhgx;
	// 备注
	std::wstring bz;
};

#endif