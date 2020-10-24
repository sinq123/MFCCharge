#ifndef GACONSTDEF_H
#define GACONSTDEF_H

#include <string>

#include "../NHDetCommModu/NHEngPro.h"
// 主、副灯对应外、内
const wchar_t * const GA_MAIN_LIGHT_NAME = L"外";  
const wchar_t * const GA_MINOR_LIGHT_NAME = L"内"; 
const wchar_t * const GA_LEFT_MAIN_LIGHT_CODE = L"H1";  
const wchar_t * const GA_LEFT_MINOR_LIGHT_CODE = L"H2";
const wchar_t * const GA_RIGHT_MAIN_LIGHT_CODE = L"H4";  
const wchar_t * const GA_RIGHT_MINOR_LIGHT_CODE = L"H3";  

//// 主、副灯对应内、外
//const wchar_t * const GA_MAIN_LIGHT_NAME = L"内";  
//const wchar_t * const GA_MINOR_LIGHT_NAME = L"外"; 
//const wchar_t * const GA_LEFT_MAIN_LIGHT_CODE = L"H2";  
//const wchar_t * const GA_LEFT_MINOR_LIGHT_CODE = L"H1";
//const wchar_t * const GA_RIGHT_MAIN_LIGHT_CODE = L"H3";  
//const wchar_t * const GA_RIGHT_MINOR_LIGHT_CODE = L"H4";  

// 检测项目空Str定义
const wchar_t * const DET_ITEM_NULL = L"EMP";  

typedef struct RBPD_1
{
	// 序号
	int nNum;
	// 左制动力
	int nLBrake;
	// 右制动力
	int nRBrake;

	RBPD_1(){ZeroMemory(this, sizeof(RBPD_1));}

}RollerBrakeProcessData_1,*PRollerBrakeProcessData_1;

// 公安网返回信息
struct SGAMsg
{
	// 标记，1成功；小于0失败，$E为系统异常
	std::wstring code;
	// 描述信息
	std::wstring message;
	std::wstring PDALineNum;
};

// 检验机构备案信息
struct SGAStationRecordInfo
{
	// 检验机构编号 
	std::wstring jczbh;
	// 检验机构名称 
	std::wstring jczmc;
	// 是否与公安网联网  
	std::wstring sflw;
	// 资格许可证书编号  
	std::wstring rdsbh;
	// 资格许可有效期始 
	std::wstring rdyxqs;
	// 资格许可有效期止 
	std::wstring rdyxqz;
	// 设计日检测能力(汽车辆)
	std::wstring shejirjcnl;
	// 实际日检测能力(汽车辆)
	std::wstring shijirjcnl;
	// 检测人员总数 
	std::wstring jcryzs;
	// 外检工位人数 
	std::wstring wjgwrs;
	// 录入工位人数  
	std::wstring lrgwrs;
	// 引车员人数 
	std::wstring ycyrs;
	// 底盘工位人数
	std::wstring dpgwrs;
	// 总检工位人数
	std::wstring zjgwrs;
	// 其他工位人数 
	std::wstring qtgwrs;
	// 通过省级质检部门考核人数 
	std::wstring tgszjbmkhrs;
	// 未通过省级质检部门考核人数
	std::wstring wtgszjbmkhrs;
	// 发证机关  
	std::wstring fzjg;
	// 管理部门 
	std::wstring glbm;
	// 更新日期  
	std::wstring gxrq;
	// 备注  
	std::wstring bz;
	// 设计日检测能力(摩托辆)  
	std::wstring shejirjcmtsl;
	// 实际日检测能力(摩托辆) 
	std::wstring shijirjcmtsl;
	// 审核标记  
	std::wstring shbj;
	// 使用管理部门  
	std::wstring syglbm;
	// 审核意见 
	std::wstring shyj;
	// 状态标记 
	std::wstring zt;
	// 暂停原因 
	std::wstring ztyy;
	// 单位地址  
	std::wstring dwdz;
	// 邮政编码 
	std::wstring yzbm;
	// 许可检验范围 
	std::wstring xkjyfw;
	// 资格许可发放单位
	std::wstring rdsffdw;
	// 法人代表  
	std::wstring frdb;
	// 法人代表身份证号  
	std::wstring frdbsfzh;
	// 法人代表联系电话  
	std::wstring frdblxdh;
	// 负责人  
	std::wstring fzr;
	// 负责人身份证号 
	std::wstring fzrsfzh;
	// 负责人联系电话  
	std::wstring fzrlxdh;
	// 日常联系人 
	std::wstring rclxr;
	// 日常联系人身份证号
	std::wstring rclxrsfzh;
	// 日常联系人联系电话  
	std::wstring rclxrlxdh;
};

// 检测线备案信息
struct SGALineRecordInfo
{
	// 检验机构编号    
	std::wstring jczbh;
	// 检测线代号   
	std::wstring jcxxh;
	// 检验机构名称 
	std::wstring jczmc;
	// 检测线名称  
	std::wstring jcxmc;
	// 检测线类别  
	std::wstring jcxlb;
	// 检测线控制方式  
	std::wstring jcxczfs;
	// 制动检测设备名称  
	std::wstring zdsbmc;
	// 制动检测设备型号   
	std::wstring zdsbxh;
	// 制动检测设备生产厂家  
	std::wstring zdsbsccj;
	// 制动检测最少时间 
	std::wstring zdjcsj;
	// 制动检测方式  
	std::wstring zdjcfs;
	// 平板制式  
	std::wstring pbzs;
	// 单平板长度  
	std::wstring dpbcd;
	// 平板间距  
	std::wstring pbjj;
	// 滚筒式制动台制式   
	std::wstring gtszdtzs;
	// 滚筒式制动台停机方式   
	std::wstring gtszdttjfs;
	// 制动检测设备启用时间  
	std::wstring zdsbqysj;
	// 制动检测设备检定有效期止 
	std::wstring zdsbjdyxqz;
	// 制动检测设备状态
	std::wstring zdsbzt;
	// 灯光检测设备名称 
	std::wstring dgsbmc;
	// 灯光检测设备型号  
	std::wstring dgsbxh;
	// 灯光检测设备生产厂家  
	std::wstring dgsbsccj;
	// 灯光检测最少时间   
	std::wstring dgjcsj;
	// 灯光检测方式 
	std::wstring dgjcfs;
	// 灯光检测是否有车身偏移修正功能   
	std::wstring dgcspyxz;
	// 灯光检测设备启用时间  
	std::wstring dgsbqysj;
	// 灯光检测设备检定有效期止  
	std::wstring dgsbjdyxqz;
	// 灯光检测设备状态 
	std::wstring dgsbzt;
	// 速度检测设备名称 
	std::wstring sdsbmc;
	// 速度检测设备型号  
	std::wstring sdsbxh;
	// 速度检测设备生产厂家  
	std::wstring sdsbsccj;
	// 速度检测最少时间 
	std::wstring sdjcsj;
	// 速度检测设备启用时间  
	std::wstring sdsbqysj;
	// 速度检测设备检定有效期止  
	std::wstring sdsbjdyxqz;
	// 速度检测设备状态   
	std::wstring sdsbzt;
	// 侧滑检测设备名称  
	std::wstring chsbmc;
	// 侧滑检测设备型号  
	std::wstring chsbxh;
	// 侧滑检测设备生产厂家   
	std::wstring chsbsccj;
	// 侧滑检测最少时间  
	std::wstring chjcsj;
	// 侧滑检测设备启用时间  
	std::wstring chsbqysj;
	// 侧滑检测设备检定有效期止  
	std::wstring chsbjdyxqz;
	// 侧滑检测设备状态   
	std::wstring chsbzt;
	// 称重设备名称   
	std::wstring czsbmc;
	// 称重检测设备型号    
	std::wstring czsbxh;
	// 称重检测设备生产厂家   
	std::wstring czsbsccj;
	// 称重检测最少时间  
	std::wstring czjcsj;
	// 称重范围   
	std::wstring czjb;
	// 称重检测设备检定有效期止   
	std::wstring czsbjdyxqz;
	// 称重检测设备启用时间   
	std::wstring czsbqysj;
	// 称重检测设备状态  
	std::wstring czsbzt;
	// 全线检测时间  
	std::wstring qxjcsj;
	// 工位1  
	std::wstring gw1;
	// 工位2 
	std::wstring gw2;
	// 工位3  
	std::wstring gw3;
	// 工位4  
	std::wstring gw4;
	// 工位5  
	std::wstring gw5;
	// 工位6  
	std::wstring gw6;
	// 工位7  
	std::wstring gw7;
	// 工位8  
	std::wstring gw8;
	// 工位9  
	std::wstring gw9;
	// 备注 
	std::wstring bz;
	// 发证机关  
	std::wstring fzjg;
	// 管理部门 
	std::wstring glbm;
	// 更新日期   
	std::wstring gxrq;
	// 制动检验设备编号  
	std::wstring zdsbbh;
	// 制动检验设备检定/校准证书编号   
	std::wstring zdsbjdzsbh;
	// 灯光检验设备编号 
	std::wstring dgsbbh;
	// 灯光检测设备检定/校准证书标号   
	std::wstring dgsbjdzsbh;
	// 速度检验设备编号  
	std::wstring sdsbbh;
	// 速度检验设备检定/校准证书标号  
	std::wstring sdsbjdzsbh;
	// 侧滑检验设备编号  
	std::wstring chsbbh;
	// 侧滑检验设备检定/校准证书编号  
	std::wstring chsbjdzsbh;
	// 称重检验设备编号
	std::wstring czsbbh;
	// 称重检验设备检定/校准证书编号 
	std::wstring czsbjdzsbh;
	// 状态标记  
	std::wstring zt;
	// 暂停原因  
	std::wstring ztyy;
};

// 检验业务信息系统备案信息
struct SGABISRecordInfo
{
	// 备案编号 
	std::wstring babh;
	// 检验系统名称 
	std::wstring jyxtmc;
	// 检验系统说明  
	std::wstring jyxtsm;
	// 版本编号
	std::wstring bbbh;
	// 开发单位
	std::wstring kfdw;
	// 数据库版本 
	std::wstring sjkbb;
	// 系统架构描述 
	std::wstring xtjgms;
	// 检验机构编号 
	std::wstring jczbh;
	// 检测线代号 
	std::wstring jcxxh;
	// 检测时间 
	std::wstring jcsj;
	// 验收时间 
	std::wstring yssj;
	// 使用状态 
	std::wstring syzt;
	// 暂停原因  
	std::wstring ztyy;
	// 经办人 
	std::wstring jbr;
	// 审核标记 
	std::wstring shbj;
	// 审核意见 
	std::wstring shyj;
	// 审核人 
	std::wstring shr;
	// 审核时间 
	std::wstring shsj;
	// 发证机关
	std::wstring fzjg;
	// 管理部门
	std::wstring glbm;
	// 更新日期 
	std::wstring gxsj;
	// 使用管理部门  
	std::wstring syglbm;
};

// 机动车基本信息
struct SGAVehBaseInfo
{
	// 机动车序号
	std::wstring xh;
	// 号牌种类
	std::wstring hpzl;
	// 号牌号码
	std::wstring hphm;
	// 中文品牌
	std::wstring clpp1;
	// 车辆型号
	std::wstring clxh;
	// 英文品牌
	std::wstring clpp2;
	// 国产/进口
	std::wstring gcjk;
	// 制造国
	std::wstring zzg;
	// 制造厂名称
	std::wstring zzcmc;
	// 车辆识别代号
	std::wstring clsbdh;
	// 发动机号
	std::wstring fdjh;
	// 车辆类型
	std::wstring cllx;
	// 车身颜色
	std::wstring csys;
	// 使用性质
	std::wstring syxz;
	// 身份证明号码
	std::wstring sfzmhm;
	// 身份证明名称
	std::wstring sfzmmc;
	// 机动车所有人
	std::wstring syr;
	// 初次登记日期
	std::wstring ccdjrq;
	// 最近定检日期
	std::wstring djrq;
	// 检验有效期止
	std::wstring yxqz;
	// 强制报废期止
	std::wstring qzbfqz;
	// 发证机关
	std::wstring fzjg;
	// 管理部门
	std::wstring glbm;
	// 保险终止日期
	std::wstring bxzzrq;
	// 机动车状态
	std::wstring zt;
	// 抵押标记0-未抵押，1-已抵押
	std::wstring dybj;
	// 发动机型号
	std::wstring fdjxh;
	// 燃料种类
	std::wstring rlzl;
	// 排量
	std::wstring pl;
	// 功率
	std::wstring gl;
	// 转向形式
	std::wstring zxxs;
	// 车外廓长
	std::wstring cwkc;
	// 车外廓宽
	std::wstring cwkk;
	// 车外廓高
	std::wstring cwkg;
	// 货箱内部长度
	std::wstring hxnbcd;
	// 货箱内部宽度
	std::wstring hxnbkd;
	// 货箱内部高度
	std::wstring hxnbgd;
	// 钢板弹簧片数
	std::wstring gbthps;
	// 轴数
	std::wstring zs;
	// 轴距
	std::wstring zj;
	// 前轮距
	std::wstring qlj;
	// 后轮距
	std::wstring hlj;
	// 轮胎规格
	std::wstring ltgg;
	// 轮胎数
	std::wstring lts;
	// 总质量
	std::wstring zzl;
	// 整备质量
	std::wstring zbzl;
	// 核定载质量
	std::wstring hdzzl;
	// 核定载客
	std::wstring hdzk;
	// 准牵引总质量
	std::wstring zqyzl;
	// 驾驶室前排载客人数
	std::wstring qpzk;
	// 驾驶室后排载客人数
	std::wstring hpzk;
	// 环保达标情况
	std::wstring hbdbqk;
	// 出厂日期
	std::wstring ccrq;
	// 车辆用途
	std::wstring clyt;
	// 用途属性
	std::wstring ytsx;
	// 行驶证证芯编号
	std::wstring xszbh;
	// 检验合格标志
	std::wstring jyhgbzbh;
	// 管理辖区
	std::wstring xzqh;
	// 住所地址行政区划
	std::wstring zsxzqh;
	// 联系地址行政区划
	std::wstring zzxzqh;
	// 事故车损伤部位情况
	std::wstring sgcssbwqk;
	// 是否免检
	std::wstring sfmj;
	// 不免检原因
	std::wstring bmjyy;
};

// 检验机构工作人员备案信息
struct SGAStaffRecordInfo
{
	// 身份证明号码
	std::wstring sfzmhm;
	// 姓名
	std::wstring xm;
	// 人员类别
	std::wstring rylb;
	// 管理部门
	std::wstring glbm;
	// 发证机关
	std::wstring fzjg;
	// 检验机构编号
	std::wstring jczbh;
	// 更新日期
	std::wstring gxrq;
	// 备注
	std::wstring bz;
	// 审核标记
	std::wstring shbj;
	// 审核意见
	std::wstring shyj;
	// 状态标记
	std::wstring zt;
	// 上岗证编号
	std::wstring sgzbh;
	// 上岗证有效期止
	std::wstring sgzyxqz;
	// 上岗证发放单位
	std::wstring sgzffdw;
	// 使用管理部门
	std::wstring syglbm;
};

// 机动车检验审核不通过原因
struct SGAVehNoPassReason
{
	// 检验流水号 
	std::wstring jylsh;
	// 检验机构编号 
	std::wstring jyjgbh;
	// 号牌种类 
	std::wstring hpzl;
	// 号牌号码 
	std::wstring hphm;
	// 审核结果 
	std::wstring shjg;
	// 不合格查验项目
	std::wstring bhgcyxm;
	// 不合格外观检验照片  
	std::wstring bhgcyzp;
	// 不合格外观检验项目
	std::wstring bhgwgjyxm;
	// 不合格底盘检验项目
	std::wstring bhgdpjyxm;
	// 不合格底盘动态检验项目  
	std::wstring bhgdtdpjyxm;
	// 不合格检验项目  
	std::wstring bhgjyxm;
	// 不合格资料照片 
	std::wstring bhgzlzp;
	// 不合格工位照片
	std::wstring bhggwzp;
	// 审核不通过原因描述  
	std::wstring shbtgyy;
};

// 车辆所属类别对应检验项目信息
struct SGAVehTypeInfoItem
{
	// 车辆所属类别
	std::wstring clsslb;
	// 车辆所属类别名称
	std::wstring clsslbmc;
	// 须检验项目代号
	std::wstring xjyxmdh;
	// 标准依据标记
	std::wstring bzyjbj;
};

// 机动车对应需拍摄照片和人工检验项目信息
struct SGAVehPhotoAndManualItem
{
	// 检验流水号
	std::wstring jylsh;
	// 检验机构编号
	std::wstring jyjgbh;
	// 号牌号码
	std::wstring hphm;
	// 号牌种类
	std::wstring hpzl;
	// 外观检验照片
	std::wstring wgjyzp;
	// 资料照片
	std::wstring zlzp;
	// 外观检验项目
	std::wstring wgjcxm;
	// 底盘动态检验项目
	std::wstring dtdpjyxm;
	// 底盘检验项目
	std::wstring dpjyxm;
	// 判定依据
	std::wstring pdyj;
	// 仪器设备检验项目
	std::wstring yqsbjyxm;
};

struct SGAReviewNoPassReson
{
	// 检验流水号
	std::wstring jylsh;
	// 检验机构编号
	std::wstring jyjgbh;
	// 号牌种类
	std::wstring hpzl;
	// 号牌号码
	std::wstring hphm;
	// 审核结果
	std::wstring shjg;
	// 不合格外观检验照片
	std::wstring bhgcyzp;
	// 不合格外观检验项目
	std::wstring bhgwgjyxm;
	// 不合格底盘检验项目
	std::wstring bhgdpjyxm;
	// 不合格底盘动态检验项目
	std::wstring bhgdtdpjyxm;
	// 不合格检验项目
	std::wstring bhgjyxm;
	// 不合格资料照片
	std::wstring bhgzlzp;
	// 不合格工位照片
	std::wstring bhggwzp;
	// 审核不通过原因描述
	std::wstring shbtgyy;
};

// 车管业务流水号
struct SGABusinessNum
{
	// 检验监管系统流水号
	std::wstring lsh;
	// 综合应用平台车管流水号
	std::wstring cglsh;
};

// 联网待检列表信息
struct SlstNetVeh
{
	// 检验流水号
	std::wstring jylsh;
	// 号牌种类
	std::wstring hpzl;
	// 号牌号码
	std::wstring hphm;
	// 检验次数
	std::wstring jycs;
};

// 互联网检验预约信息
struct SGAIEApptInfo
{
	// 序号 
	std::wstring xh;
	// 检验机构编号 
	std::wstring jczbh;
	// 用户代号 
	std::wstring yhdh;
	// 用户类型 
	std::wstring yhlx;
	// 号牌种类 
	std::wstring hpzl;
	// 号牌号码 
	std::wstring hphm;
	// 预约人姓名 
	std::wstring xm;
	// 手机号码  
	std::wstring sjhm;
	// 预约码 
	std::wstring yym;
	// 预约日期  
	std::wstring yyrq;
	// 预约时段 
	std::wstring yysd;
	// 预约时段说明  
	std::wstring yysdsm;
	// 预约类型  
	std::wstring yylx;
	// 状态 
	std::wstring zt;
	// 发证机关 
	std::wstring fzjg;
	// 更新日期 
	std::wstring gxsj;
	// 检验标记 
	std::wstring jybj;
	// 实际检验时间 
	std::wstring sjjysj;
	// 实际检验机构 
	std::wstring sjjyjgbh;
	// 检验监管流水号  
	std::wstring lsh;
	// 操作标记 
	std::wstring czbj;
	// 预约开始时段 
	std::wstring ksjcsj;
	// 预约结束时段 
	std::wstring jsjcsj;
};

// 机动车公告技术参数文本信息
struct SGAVehTecParaTxtInfo
{
	// 整车公告编号 
	std::wstring veh_bh;
	// 车辆品牌(中文) 
	std::wstring veh_clpp1;
	// 车辆品牌(英文) 
	std::wstring veh_clpp2;
	// 车辆型号 
	std::wstring veh_clxh;
	// 企业ID 
	std::wstring veh_qyid;
	// 生产地址 
	std::wstring veh_scdz;
	// 发动机型号  
	std::wstring veh_fdjxh;
	// 识别代号序列 
	std::wstring veh_sbdhxl;
	// 车辆类型 
	std::wstring veh_cllx;
	// 制造国 
	std::wstring veh_zzg;
	// 转向形式 
	std::wstring veh_zxxs;
	// 燃料种类 
	std::wstring veh_rlzl;
	// 排量 
	std::wstring veh_pl;
	// 功率 
	std::wstring veh_gl;
	// 车外廓长
	std::wstring veh_cwkc;
	// 车外廓宽 
	std::wstring veh_cwkk;
	// 车外廓高
	std::wstring veh_cwkg;
	// 货箱内部长度 
	std::wstring veh_hxnbcd;
	// 货箱内部宽度 
	std::wstring veh_hxnbkd;
	// 货箱内部高度  
	std::wstring veh_hxnbgd;
	// 钢板弹簧片数
	std::wstring veh_gbthps;
	// 轴数  
	std::wstring veh_zs;
	// 轴距 
	std::wstring veh_zj;
	// 前轮距 
	std::wstring veh_qlj;
	// 后轮距 
	std::wstring veh_hlj;
	// 轮胎数 
	std::wstring veh_lts;
	// 轮胎规格 
	std::wstring veh_ltgg;
	// 总质量 
	std::wstring veh_zzl;
	// 整备质量 
	std::wstring veh_zbzl;
	// 额定载质量 
	std::wstring veh_hdzzl;
	// 准牵引总质量 
	std::wstring veh_zqyzl;
	// 额定载客 
	std::wstring veh_hdzk;
	// 驾驶室前排人数 
	std::wstring veh_qpzk;
	// 驾驶室后排人数 
	std::wstring veh_hpzk;
	// 批次
	std::wstring veh_pc;
	// 底盘ID 
	std::wstring veh_dpid;
	// 环保达标情况
	std::wstring veh_hbdbqk;
	// 公告发布类型 
	std::wstring veh_cslx;
	// 更新日期 
	std::wstring veh_gxrq;
	// 备注 
	std::wstring veh_bz;
	// 车辆制造企业 
	std::wstring veh_zzcmc;
	// 公告发布日期
	std::wstring veh_ggrq;
	// 免检标记
	std::wstring veh_sfmj;
	// 撤销生效日期
	std::wstring veh_cxsxrq;
	// 底盘企业及型号
	std::wstring veh_dpqyxh;
	// 产品类别 
	std::wstring veh_cplb;
	// 车型公告编号 
	std::wstring veh_clggbh;
	// 是否允许注册 
	std::wstring veh_sfyxzc;
	// 公告生效日期 
	std::wstring veh_ggsxrq;
	// 公告有效期标记
	std::wstring veh_ggyxqbj;
	// 撤销公告批次
	std::wstring veh_cxggpc;
	// 撤销公告发布日期 
	std::wstring veh_cxggrq;
	// 停止生产日期 
	std::wstring veh_tzscrq;
	// 有效期描述 
	std::wstring veh_yxqms;
	// 照片数 
	std::wstring veh_zps;
	// 免检有效期止 
	std::wstring veh_mjyxqz;
	// 反光标识型号
	std::wstring veh_fgbsxh;
	// 反光标识商标
	std::wstring veh_fgbssb;
	// 反光标识企业
	std::wstring veh_fgbsqy;
	// 轴荷
	std::wstring veh_zh;
	// 载质量利用系数 
	std::wstring veh_zzllyxs;
	// 半挂鞍座最大允许总质量 
	std::wstring veh_bgazzdyxzzl;
	// 接近离去角
	std::wstring veh_jjlqj;
	// 前悬后悬 
	std::wstring veh_qxhx;
	// 驾驶室类型  
	std::wstring veh_jsslx;
	// 传动型式 
	std::wstring veh_cdxs;
	// 最高车速
	std::wstring veh_zgcs;
	// 油耗 
	std::wstring veh_yh;
	// 前制动方式 
	std::wstring veh_qzdfs;
	// 后制动方式
	std::wstring veh_hzdfs;
	// 前制动操作方式 
	std::wstring veh_qzdczfs;
	// 后制动操作方式 
	std::wstring veh_hzdczfs;
	// 发动机企业 
	std::wstring veh_fdjqy;
	// 发动机商标 
	std::wstring veh_fdjsb;
	// 是否带防抱死系统 
	std::wstring veh_ywabs;
	// 车辆名称 
	std::wstring veh_clmc;
	// 企业代码 
	std::wstring veh_qydm;
	// 公告标记 
	std::wstring veh_ggbj;
	// 备用1 
	std::wstring veh_by1;
	// 备用2 
	std::wstring veh_by2;
	// 备用3 
	std::wstring veh_by3;
	// 备用4 
	std::wstring veh_by4;
	// 备用5 
	std::wstring veh_by5;

	// 底盘公告编号   
	std::wstring cha_bh;
	// 底盘ID   
	std::wstring cha_dpid;
	// 企业ID  
	std::wstring cha_qyid;
	// 生产地址
	std::wstring cha_scdz;
	// 底盘型号 
	std::wstring cha_dpxh;
	// 底盘类别 
	std::wstring cha_dplb;
	// 产品名称 
	std::wstring cha_cpmc;
	// 产品商标  
	std::wstring cha_cpsb;
	// 外廓长  
	std::wstring cha_c;
	// 外廓宽   
	std::wstring cha_k;
	// 外廓高  
	std::wstring cha_g;
	// 燃料种类 
	std::wstring cha_rlzl;
	// 依据标准  
	std::wstring cha_yjbz;
	// 转向形式   
	std::wstring cha_zxxs;
	// 轴数  
	std::wstring cha_zs;
	// 轴距   
	std::wstring cha_zj;
	// 钢板弹簧片数
	std::wstring cha_gbthps;
	// 轮胎数 
	std::wstring cha_lts;
	// 轮胎规格  
	std::wstring cha_ltgg;
	// 前轮距  
	std::wstring cha_qlj;
	// 后轮距  
	std::wstring cha_hlj;
	// 总质量  
	std::wstring cha_zzl;
	// 整备质量 
	std::wstring cha_zbzl;
	// 准牵引总质量 
	std::wstring cha_zqyzl;
	// 发动机型号 
	std::wstring cha_fdjxh;
	// 排量  
	std::wstring cha_pl;
	// 功率  
	std::wstring cha_gl;
	// 识别代号序列 
	std::wstring cha_sbdh;
	// 批次  
	std::wstring cha_pc;
	// 公告发布类型  
	std::wstring cha_cslx;
	// 更新日期 
	std::wstring cha_gxrq;
	// 备注  
	std::wstring cha_bz;
	// 车辆制造企业 
	std::wstring cha_zzcmc;
	// 公告发布日期 
	std::wstring cha_ggrq;
	// 撤销生效日期 
	std::wstring cha_cxsxrq;
	// 驾驶室前排人数 
	std::wstring cha_qpzk;
	// 驾驶室后排人数 
	std::wstring cha_hpzk;
	// 公告生效日期  
	std::wstring cha_ggsxrq;
	// 公告有效期标记
	std::wstring cha_ggyxqbj;
	// 撤销公告批次 
	std::wstring cha_cxggpc;
	// 撤销公告发布日期 
	std::wstring cha_cxggrq;
	// 停止生产日期 
	std::wstring cha_tzscrq;
	// 有效期描述 
	std::wstring cha_yxqms;
	// 发动机企业 
	std::wstring cha_fdjqy;
	// 发动机商标   
	std::wstring cha_fdjsb;
	// 接近离去角 
	std::wstring cha_jjlqj;
	// 前悬后悬  
	std::wstring cha_qxhx;
	// 轴荷 
	std::wstring cha_zh;
	// 最高车速  
	std::wstring cha_zgcs;
	// 是否带防抱死系统   
	std::wstring cha_ywabs;
	// 企业代码 
	std::wstring cha_qydm;
	// 公告标记 
	std::wstring cha_ggbj;
	// 备用1  
	std::wstring cha_by1;
	// 备用2 
	std::wstring cha_by2;
	// 备用3  
	std::wstring cha_by3;
	// 备用4  
	std::wstring cha_by4;
	// 备用5   
	std::wstring cha_by5;

	// 整车公告编号   
	std::wstring pho_bh;
	// 车型公告编号  
	std::wstring pho_clggbh;
	// 顺序号  
	std::wstring pho_sxh;
	// 批次   
	std::wstring pho_pc;
	// 公告发布日期  
	std::wstring pho_ggrq;
	// 照片编号  
	std::wstring pho_zpbh;
	// 更新日期 
	std::wstring pho_gxrq;
};

// 机动车公告技术参数图片信息
struct SGAVehTecParaPhoInfo
{
	// 照片编号 
	std::wstring zpbh;
	// 照片 
	std::wstring zp;
	// 更新日期 
	std::wstring gxrq;
};

// 读取机动车交强险（含车船税）信息查询接口
struct SGAVehComIns
{
	// 保险单号
	std::wstring bxdh;
	// 保险公司代码
	std::wstring bxgsdm;
	// 保险公司名称
	std::wstring bxgs;
	// 号牌种类
	std::wstring hpzl;
	// 号牌号码
	std::wstring hphm;
	// 车辆识别代号
	std::wstring clsbdh;
	// 生效日期
	std::wstring sxrq;
	// 终止日期
	std::wstring zzrq;
	// 被保险人名称
	std::wstring bbxr;
	// 被保险人身份证明号码
	std::wstring bbxrsfzmhm;
	// 交强险投保状态
	std::wstring jqxtbzt;
	// 车船税完税/免税凭证号码
	std::wstring wspzhm;
	// 车船税纳税情况
	std::wstring ccsnsqk;
	// 车船税纳税金额
	std::wstring ccsnsje;
	// 车船税完税/免税凭证号码
	std::wstring wspzhm2;
	// 车船税纳税人识别号
	std::wstring nsrsbh;
	// 车船税纳税日期
	std::wstring ccsnsrq;
	// 车船税纳税所属时期起始日期
	std::wstring ccsnsqsrq;
	// 车船税纳税所属时期终止日期
	std::wstring ccsnszzrq;
};

// 读取机动车检验照片待比对信息查询接口
// 机动车检验车辆基本信息
struct SGAVehTInfo
{
	// 流水号
	std::wstring lsh;
	// 检验流水号
	std::wstring jylsh;
	// 检验机构编号
	std::wstring jyjgbh;
	// 号牌种类
	std::wstring hpzl;
	// 号牌号码
	std::wstring hphm;
	// 车辆识别代号
	std::wstring clsbdh;
	// 机动车所有人
	std::wstring syr;
	// 保险生效日期
	std::wstring sxrq;
	// 保险终止日期
	std::wstring zzrq;
	// 车辆类型
	std::wstring cllx;
	// 使用性质
	std::wstring syxz;
	// 整备质量
	std::wstring zbzl;
	// 检验过程开始时间
	std::wstring kssj;
	// 检验过程结束时间
	std::wstring jssj;
	// 发动机/电动机号码
	std::wstring fdjh;
	// 车辆品牌
	std::wstring clpp1;
	// 车辆型号
	std::wstring clxh;
	// 初次登记日期
	std::wstring ccdjrq;
	// 出厂日期
	std::wstring ccrq;
	// 车辆外观检验检验员
	std::wstring wgjcjyy;
	// 需要比对的照片总数
	std::wstring zpzs;
	// 需要比对的视频总数
	std::wstring spzs;
	// 检验类别
	std::wstring jylb;
	// 行驶证证芯编号
	std::wstring xszbh;
	// 燃料种类
	std::wstring rlzl;
	// 发行驶证日期
	std::wstring fzrq;
	// 车身颜色
	std::wstring csys;
	// 排量
	std::wstring pl;
	// 功率
	std::wstring gl;
	// 转向形式
	std::wstring zxxs;
	// 车外廓长
	std::wstring cwkc;
	// 车外廓宽
	std::wstring cwkk;
	// 车外廓高
	std::wstring cwkg;
	// 货箱内部长度
	std::wstring hxnbcd;
	// 货箱内部宽度
	std::wstring hxnbkd;
	// 货箱内部高度
	std::wstring hxnbgd;
	// 钢板弹簧片数
	std::wstring gbthps;
	// 轴数
	std::wstring zs;
	// 轴距
	std::wstring zj;
	// 前轮距
	std::wstring qlj;
	// 后轮距
	std::wstring hlj;
	// 轮胎规格
	std::wstring ltgg;
	// 轮胎数
	std::wstring lts;
	// zzl	总质量
	std::wstring zzl;
	// hdzzl	核定载质量
	std::wstring hdzzl;
	// hdzk	核定载客
	std::wstring hdzk;
	// zqyzl	准牵引总质量
	std::wstring zqyzl;
	// qpzk	驾驶室前排载客人数
	std::wstring qpzk;
	// hpzk	驾驶室后排载客人数
	std::wstring hpzk;
	// clyt	车辆用途
	std::wstring clyt;
	// ytsx	用途属性
	std::wstring ytsx;
	// sfxny	是否新能源汽车 
	std::wstring sfxny;
	// xnyzl	新能源汽车种类
	std::wstring xnyzl;
	// clpp2	英文品牌
	std::wstring clpp2;
	// gcjk	国产/进口
	std::wstring gcjk;
	// zzg	制造国
	std::wstring zzg;
	// zzcmc	制造厂名称
	std::wstring zzcmc;
	// djrq	最近定检日期
	std::wstring djrq;
	// yxqz	检验有效期止
	std::wstring yxqz;
	// qzbfqz	强制报废期止
	std::wstring qzbfqz;
	// fzjg	发证机关
	std::wstring fzjg;
	// glbm	管理部门
	std::wstring glbm;
	// zt	机动车状态
	std::wstring zt;
	// dybj	抵押标记
	std::wstring dybj;
	// fdjxh	发动机型号
	std::wstring fdjxh;
	// hbdbqk	环保达标情况
	std::wstring hbdbqk;
	// jyhgbzbh	检验合格标志
	std::wstring jyhgbzbh;
	// xzqh	管理辖区
	std::wstring xzqh;
	// zsxzqh	住所行政区划
	std::wstring zsxzqh;
	// zzxzqh	暂住行政区划
	std::wstring zzxzqh;
	// sgcssbwqk	事故车损伤部位情况
	std::wstring sgcssbwqk;
	// sfmj	是否免检
	std::wstring sfmj;
	// bmjyy	不免检原因
	std::wstring bmjyy;
};
// 机动车检验照片信息
struct SGAVehTPhoInfo
{
	//zpzl	照片种类
	std::wstring zpzl;
	//zpurl	照片路径地址
	std::wstring zpurl;
};
// 机动车档案照片信息
struct SGAVehTecParaPhoInfo2
{
	//lb	照片类别
	std::wstring lb;
	// zpurl	照片路径地址
	std::wstring zpurl;
};

// 公安照片定义
// 第1维：序号
// 第2维：照片种类
// 第三维：照片名称
const int g_nGAPhotoAmount = 66;
const CStringW g_strGAPhotoDef[][3] =
{
	{L"1", L"0201", L"机动车行驶证"}, // 1
	{L"2", L"0202", L"机动车牌证申请表"}, // 2
	{L"3", L"0203", L"机动车交通事故责任强制保险凭证"}, // 3
	{L"4", L"0204", L"机动车安全技术检验报告单"}, // 4
	{L"5", L"0205", L"机动车查验记录表"}, // 5
	{L"6", L"0206", L"车船税纳税或者免税证明"}, // 6
	{L"7", L"0207", L"委托核发检验合格标志通知书"}, // 7
	{L"8", L"0208", L"代理人授权书"}, // 8
	{L"9", L"0211", L"国产机动车整车出厂合格证和底盘合格证"}, // 9
	{L"10", L"0257", L"路试检验记录"}, // 10
	{L"11", L"0111", L"车辆左前方斜视45度照片"}, // 11
	{L"12", L"0112", L"车辆右后方斜视45度照片"}, // 12
	{L"13", L"0113", L"车辆识别代号照片"}, // 13
	{L"14", L"0119", L"发动机号或柔性标签"}, // 14
	{L"15", L"0115", L"车厢内部照片"}, // 15
	{L"16", L"0158", L"车辆正后方照片"}, // 16
	{L"17", L"0116", L"灭火器照片"}, // 17
	{L"18", L"0117", L"应急锤照片"}, // 18
	{L"19", L"0127", L"急救箱"}, // 19
	{L"20", L"0118", L"行驶记录装置照片"}, // 20
	{L"21", L"0157", L"驾驶人座椅汽车安全带"}, // 21
	{L"22", L"0134", L"防抱死制动装置自检状态灯"}, // 22
	{L"23", L"0132", L"发动机舱自动灭火装置"}, // 23
	{L"24", L"0130", L"辅助制动装置"}, // 24
	{L"25", L"0133", L"前轮盘式制动器"}, // 25
	{L"26", L"0136", L"左前轮胎规格型号"}, // 26
	{L"27", L"0154", L"右前轮胎规格型号"}, // 27
	{L"28", L"0155", L"左后轮胎规格型号"}, // 28
	{L"29", L"0156", L"右后轮胎规格型号"}, // 29
	{L"30", L"0135", L"残疾车操纵辅助装置"}, // 30
	{L"31", L"0140", L"教练车副制动踏板"}, // 31
	{L"32", L"0163", L"危险货物运输车标志"}, // 32
	{L"33", L"0126", L"校车停车指示标志牌照片"}, // 33
	{L"34", L"0128", L"校车标志灯照片"}, // 34
	{L"35", L"0138", L"校车、卧铺客车的车内外录像监控系统"}, // 35
	{L"36", L"0139", L"校车的辅助倒车装置"}, // 36
	{L"37", L"0159", L"校车标牌（前）正面照片"}, // 37
	{L"38", L"0160", L"校车标牌（前）反面照片"}, // 38
	{L"39", L"0161", L"校车标牌（后）正面照片"}, // 39
	{L"40", L"0321", L"左灯光工位照片"}, // 40
	{L"41", L"0352", L"右灯光工位照片"}, // 41
	{L"42", L"0322", L"一轴制动工位照片"}, // 42
	{L"43", L"0348", L"二轴制动工位照片"}, // 43
	{L"44", L"0349", L"三轴制动工位照片"}, // 44
	{L"45", L"0350", L"四轴制动工位照片"}, // 45
	{L"46", L"0354", L"五轴制动工位照片"}, // 46
	{L"47", L"0355", L"六轴制动工位照片"}, // 47
	{L"48", L"0351", L"驻车制动工位照片"}, // 48
	{L"49", L"0347", L"车速表工位照片"}, // 49
	{L"50", L"0353", L"侧滑工位照片"}, // 50
	{L"51", L"0341", L"路试行车制动开始照片"}, // 51
	{L"52", L"0343", L"路试行车制动结束照片"}, // 52
	{L"53", L"0345", L"路试坡度驻车制动照片"}, // 53
	{L"54", L"0344", L"底盘动态检验开始照片"}, // 54
	{L"55", L"0342", L"底盘动态检验结束照片"}, // 55
	{L"56", L"0323", L"底盘检验照片"}, // 56
	{L"57", L"0356", L"一轴加载制动工位照片"}, // 57
	{L"58", L"0357", L"二轴加载制动工位照片"}, // 58
	{L"59", L"0358", L"三轴加载制动工位照片"}, // 59
	{L"60", L"0359", L"四轴加载制动工位照片"}, // 60
	{L"61", L"0360", L"外廓尺寸自动测量前面照片"}, // 61
	{L"62", L"0361", L"外廓尺寸自动测量侧面照片"}, // 62
	{L"63", L"0362", L"整备质量测量左前45度照片"}, // 63
	{L"64", L"0363", L"整备质量测量右后45度照片"}, // 64
	{L"65", L"0164", L"紧急切断装置"}, // 65
	{L"66", L"0114", L"车辆铭牌照片"}, // 66
	//
};

// 地方公安照片定义
// 第1维：序号
// 第2维：照片种类
// 第3维：照片名称
#ifdef ENG_STA_JMDQ
const int g_nOthGAPhoAmount = 3;
const CStringW g_strOthGAPhoDef[][3] =
{
	//{L"1", L"", L""}, // 真正添加地方公安照片时，本行删除

	{L"1", L"0296", L"道路运输车辆卫星定位装置安装证明"}, // 1
	{L"2", L"0297", L"环保检验报告表"}, // 2
	{L"3", L"0298", L"机动车行驶证正、副证背面"}, // 3
};
#else
const int g_nOthGAPhoAmount = 1;
const CStringW g_strOthGAPhoDef[][3] =
{
	//{L"1", L"", L""}, // 真正添加地方公安照片时，本行删除
	{L"1", L"0209", L"排放检验报告"}, // 67
	//{L"1", L"0296", L"道路运输车辆卫星定位装置安装证明"}, // 1
	//{L"2", L"0297", L"环保检验报告表"}, // 2
	//{L"3", L"0298", L"机动车行驶证正、副证背面"}, // 3
};
#endif

#endif