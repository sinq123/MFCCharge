/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：AC_DATA_WG.h
* 文件标识：
* 描述：PDA数据表模型
*
* 版本：1.0
* 日期：20xx-xx-xx
* 作者：Cyx
*
*
* 历史信息：
*
* 版本：1.0.0beta1
* 日期：20xx-xx-xx
* 作者：Shaojm
* 描述：正在开发
*/


#if !defined (AC_DATA_WG_H)
#define AC_DATA_WG_H

#include <string>

struct SAC_DATA_WG
{
	// 检验流水号
	std::wstring jylsh;
	//安检机构编号
	std::wstring jyjgbh;
	//检测线代号
	std::wstring jcxdh;
	//机动车序号
	std::wstring xh;
	//号牌种类
	std::wstring hpzl;
	//号牌号码
	std::wstring hphm;
	//车辆识别代号
	std::wstring clsbdh;
	// 发动机/电动机号码
	std::wstring fdjh;
	// 车身颜色
	std::wstring csys;
	// 使用性质
	std::wstring syxz;
	// 初次登记日期
	std::wstring ccdjrq;
	// 最近定检日期
	std::wstring jyrq;
	// 检验有效期止
	std::wstring jyyxqz;
	// 保险终止日期
	std::wstring bxzzrq;
	// 燃料种类
	std::wstring rlzl;
	// 功率
	std::wstring gl;
	// 轴数
	std::wstring zs;
	// 轴距
	std::wstring zj;
	// 前轮距
	std::wstring qlj;
	// 后轮距
	std::wstring hlj;
	// 总质量
	std::wstring zzl;
	// 整备质量
	std::wstring zbzl;
	// 出厂日期
	std::wstring ccrq;
	// 驱动形式(驱动轴位)
	std::wstring qdxs;
	// 驻车轴数
	std::wstring zczs;
	// 驻车轴位
	std::wstring zczw;
	// 主轴数
	std::wstring zzs;
	// 制动力源
	std::wstring zzly;
	// 前照灯制
	std::wstring qzdz;
	// 远光单独调整
	std::wstring  ygddtz;
	// 转向轴（前轴）悬架形式
	std::wstring zxzxjxs;
	// 里程表读数
	std::wstring lcbds;
	// 人工检测是否完成
	std::wstring flag;
	// 检验类别
	std::wstring jylb;
	// 不合格项
	std::wstring bhgx;
	// 不合格细项
	std::wstring bhgxx;
	// 初次登录时间
	std::wstring ccdlsj;
	// 登录时间
	std::wstring dlsj;
	// 检验次数
	std::wstring jycs;
	// 登录员
	std::wstring dly;
	// 引车员
	std::wstring ycy;
	// 外检员
	std::wstring wjy;
	// 动态检验员
	std::wstring dtjyy;
	// 底盘检验员
	std::wstring dpjyy;
	// 车辆品牌
	std::wstring clpp1;
	// 车辆型号
	std::wstring clxh;
	// 机动车所有人
	std::wstring syr;
	// 车辆类型
	std::wstring cllx;
	// 车外廓长
	std::wstring cwkc;
	// 车外廓宽
	std::wstring cwkk;
	// 车外廓高
	std::wstring cwkg;
	// 车辆用途
	std::wstring clyt;
	// 用途属性
	std::wstring ytsx;
	// 登录员（身份证号）
	std::wstring dlysfzh;
	// 引车员（身份证号）
	std::wstring ycysfzh;
	// 外检员（身份证号）
	std::wstring wjysfzh;
	// 动态检验员（身份证号）
	std::wstring dtjyysfzh;
	// 底盘检验员（身份证号）
	std::wstring dpjyysfzh;
	// 车辆所属类别
	std::wstring clsslb;
	// 检测线类别
	std::wstring jcxlb;
	// 送检人（姓名）
	std::wstring sjr;
	// 送检人身份证号
	std::wstring sjrsfzh;
	// 核定载客
	std::wstring hdzk;
	// 核定载质量
	std::wstring hdzzl;
	// 发证机关
	std::wstring fzjg;
	// 钢板弹簧片数
	std::wstring gbthps;
	// 轮胎规格
	std::wstring ltgg;
	// 货箱内部长度
	std::wstring hxnbcd;
	// 货箱内部宽度
	std::wstring hxnbkd;
	// 货箱内部高度
	std::wstring hxnbgd;
	// 车间的线号
	std::wstring line_no;
	// 外检线号
	std::wstring wjxh;
	// 输入的 备注信息
	std::wstring yad_bz;
	// 是否检测车场外检
	std::wstring if_check_yad;
	// 上次不合格代码
	std::wstring scbhgx;
	// 外观检验项目
	std::wstring wgjcxm;
	// 外观检验照片
	std::wstring wgjyzp;
};

#endif