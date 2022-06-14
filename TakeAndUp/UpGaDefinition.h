#ifndef UPGADEFINITION_H
#define UPGADEFINITION_H

#include <string>

// 接口信息
struct SGAWebService
{
	// 公安接口版本，默认：1，1：V1.0，2：V2.0，3：V3.0
	int nVersion;
	// WebService地址
	CString strURL;
	// 接口序列号
	CString strIFSN;
	// 检验机构编号
	CString strStationNum;
	// 检验机构名称
	CString strStationName;
	// 检测线编号
	CString strLineNum;
	// 工位检验设备编号
	CString strPosEquNum;
	// 应用场景编号
	CString strCjsqbh;
	// 单位机构代码
	CString strDwjgdm;
	// 单位名称
	CString strDwmc;
	// 用户标识
	CString strYhbz;
	// 用户姓名
	CString strYhxm;
	// 终端标识
	CString strZdbs;
};

// 公安网返回信息
struct SUpGAMsg
{
	// 标记，1成功；小于0失败，$E为系统异常
	std::wstring code;
	// 描述信息
	std::wstring message;
	std::wstring PDALineNum;
};

// 图片上传参数
struct SUpGaPhoto
{
	// 检验流水号
	std::wstring jylsh;
	// 检验机构编号
	std::wstring jyjgbh;
	// 检测线代号
	std::wstring jcxdh;
	// 检验次数
	std::wstring jycs;
	// 号牌号码
	std::wstring hphm;
	// 号牌种类
	std::wstring hpzl;
	// 车辆识别代号
	std::wstring clsbdh;
	// 照片路径
	std::wstring zplj;
	// 拍摄时间
	std::wstring pssj;
	// 检验项目
	std::wstring jyxm;
	// 照片种类
	std::wstring zpzl;

};



#endif