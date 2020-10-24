/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：GADataUploadStatus.h
* 文件标识：
* 描述：公安数据上传状态
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


#if !defined (NHMFDSERVERDBMODEL_GADATAUPLOADSTATUS_H)
#define NHMFDSERVERDBMODEL_GADATAUPLOADSTATUS_H

#include <string>

struct SGADataUploadStatus
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 检验信息登录（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strVehDetLogin;
	// 复检信息登录（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strVehReDetLogin;
	// 检验过程开始（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strDetStart;
	// 外观开始（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strStartF1;
	// 外观数据（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadF1;
	// 外观结束（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strEndF1;
	// 申请二次审核（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strDetApp2Review;
	// 底盘开始（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strStartC1;
	// 底盘数据（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadC1;
	// 底盘结束（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strEndC1;
	// 动态开始（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strStartDC;
	// 动态数据（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadDC;
	// 动态结束（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strEndDC;
	// 外廓开始（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strStartM1;
	// 外廓数据（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadM1;
	// 外廓结束（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strEndM1;
	// 路试开始（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strStartR;
	// 路试数据（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadR;
	// 路试结束（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strEndR;
	// 侧滑开始（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strStartA1;
	// 侧滑数据（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadA1;
	// 侧滑结束（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strEndA1;
	// 车速开始（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strStartS1;
	// 车速数据（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadS1;
	// 车速结束（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strEndS1;
	// 右外灯开始（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strStartH4;
	// 右外灯数据（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadH4;
	// 右外灯结束（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strEndH4;
	// 右内灯开始（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strStartH3;
	// 右内灯数据（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadH3;
	// 右内灯结束（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strEndH3;
	// 左内灯开始（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strStartH2;
	// 左内灯数据（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadH2;
	// 左内灯结束（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strEndH2;
	// 左外灯开始（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strStartH1;
	// 左外灯数据（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadH1;
	// 左外灯结束（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strEndH1;
	// 驻车制动开始（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strStartB0;
	// 驻车制动数据（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadB0;
	// 驻车制动结束（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strEndB0;
	// 五轴制动开始（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strStartB5;
	// 五轴制动数据（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadB5;
	// 五轴制动结束（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strEndB5;
	// 四轴制动开始（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strStartB4;
	// 四轴制动数据（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadB4;
	// 四轴制动结束（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strEndB4;
	// 三轴制动开始（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strStartB3;
	// 三轴制动数据（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadB3;
	// 三轴制动结束（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strEndB3;
	// 二轴制动开始（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strStartB2;
	// 二轴制动数据（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadB2;
	// 二轴制动结束（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strEndB2 ;
	// 一轴制动开始（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strStartB1;
	// 一轴制动数据（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadB1;
	// 一轴制动结束（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strEndB1;
	// 其他数据（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadOtherData;
	// 检验过程结束（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strDetEnd;
	// 判定结果（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadDetResult;
	// 保险信息（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strUploadIns;
	// 申请审核（0：写入成功，1：写入失败，NULL：未写入）
	std::wstring strDetAppReview;
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