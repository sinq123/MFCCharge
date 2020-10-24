/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：PublicationInfo.h
* 文件标识：
* 描述：ASM结果数据表模型
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
* 作者：Cyx
* 描述：正在开发
*/


#if !defined (NHMFDSERVERDBMODEL_PUBLICATIONINFO_H)
#define NHMFDSERVERDBMODEL_PUBLICATIONINFO_H

#include <string>

struct SPublicationInfo
{
	// 自动编号
	std::wstring strAutoID;
	// 车牌号码
	std::wstring strCPHM;
	// 车牌种类
	std::wstring strCPZL;
	// 检验流水号
	std::wstring strJYLSH;
	// 检测结果
	std::wstring strJCJG;
	// 审核结果
	std::wstring strSHJG;
	// 驳回信息
	std::wstring strBHXX;
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
