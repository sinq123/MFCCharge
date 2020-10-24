/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：GAVideoRecord.h
* 文件标识：
* 描述：公安视频记录表
*
* 版本：1.0
* 日期：2015-04-11
* 作者：Hyh
*
*
* 历史信息：
*
* 版本：1.0.0
* 日期：2015-04-11
* 作者：Hyh
* 描述：正式发布
*/


#if !defined (NHMFDSERVERDBMODEL_GAVIDEORECORD_H)
#define NHMFDSERVERDBMODEL_GAVIDEORECORD_H

#include <string>

struct SGAVideoRecord
{
	// 自动编号
	std::wstring strAutoID;
	// 检测周期编号
	std::wstring strDetPeriodID;
	// 初检日期
	std::wstring strInitDetDate;
	// 报告编号
	std::wstring strReportNumber;
	// 录像开始时间
	std::wstring strVideoStartTime;
	// 录像结束时间
	std::wstring strVideoEndTime;
	// 录像名称（用于保存录像文件名）
	std::wstring strVideoName;
	// 视频服务器IP
	std::wstring strVR_IP;
	// 视频服务器端口
	std::wstring strVR_Port;
	// 视频服务器用户名
	std::wstring strVR_UserName;
	// 视频服务器密码
	std::wstring strVR_Password;
	// 视频服务器通道
	std::wstring strVR_Channel;
	// 备注
	std::wstring strRemark;
	// 保留1
	std::wstring strReserved1;
	// 保留2
	std::wstring strReserved2;
	// 保留3
	std::wstring strReserved3;
};

#endif