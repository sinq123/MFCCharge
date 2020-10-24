/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：AC_DATA_ROAD.h
* 文件标识：
* 描述：PDA路试数据表模型
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


#if !defined (AC_DATA_ROAD_H)
#define AC_DATA_ROAD_H

#include <string>

struct SAC_DATA_ROAD
{
	// 检验流水号
	std::wstring jylsh;
	// 安检机构编号
	std::wstring jyjgbh;
	//检测线代号
	std::wstring jcxdh;
	//检验次数
	std::wstring jycs;
	//机动车序号
	std::wstring xh;
	//号牌种类
	std::wstring hpzl;
	//号牌号码
	std::wstring hphm;
	//车辆类型
	std::wstring cllx;
	//车辆识别代号
	std::wstring clsbdh;
	//完成标志
	std::wstring flag;
	//路试员姓名
	std::wstring lsy;
	//行车制动初速度
	std::wstring zdcsd;
	//行车制动协调时间
	std::wstring zdxtsj;
	//行车制动稳定性
	std::wstring zdwdx;
	//行车空载制动距离
	std::wstring xckzzdjl;
	//行车满载制动距离
	std::wstring xcmzzdjl;
	//行车空载MFDD
	std::wstring xckzmfdd;
	//行车满载MFDD
	std::wstring xcmzmfdd;
	//行车制动踏板力值
	std::wstring xczdczlz;
	//行车路试制动判定
	std::wstring lszdpd;
	//应急制动初速度
	std::wstring yjzdcsd;
	//应急空载制动距离
	std::wstring yjkzzdjl;
	//应急空载MFDD
	std::wstring yjkzmfdd;
	//应急满载制动距离
	std::wstring yjmzzdjl;
	//应急满载MFDD
	std::wstring yjmzmfdd;
	//应急操纵力方式
	std::wstring yjzdczlfs;
	//应急操纵力值
	std::wstring yjzdczlz;
	//应急路试制动判定
	std::wstring yjzdpd;
	//驻车坡度
	std::wstring zcpd;
	//路试驻车制动判定
	std::wstring lszczdpd;
	//车速表实测值
	std::wstring csdscz;
	//车速表判定
	std::wstring csbpd;
	//路试结果
	std::wstring lsjg;
};

#endif