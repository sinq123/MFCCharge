/*
* Copyright (c) 佛山市南华仪器股份有限公司
* All rights reserved.
*
* 文件名称：DimensionData.h
* 文件标识：
* 描述：外廓尺寸数据表模型
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

#if !defined (NHMFDSERVERDBMODEL_DIMENSIONDATA_H)
#define NHMFDSERVERDBMODEL_DIMENSIONDATA_H

#include <string>

struct SDimensionData
{
	// 自动编号
	std::wstring strAutoID;
	// 日志编号(年月日时分秒IP)
	std::wstring strRunningNumber;
	// 检测时间起(年月日时分秒)(Det: Detect; Beg: Begin; 下同)
	std::wstring strDetBegTime;
	// 检测时间止(年月日时分秒)
	std::wstring strDetEndTime;
	// 检测线编号
	std::wstring strLineNumber;
	// 是否设备检测
	std::wstring strIsEquDet;
	// 是否需要修正
	std::wstring strIsNeedCor;
	// 栏板高度[mm]
	std::wstring strBoxHeight;
	// 栏板高度判定(0-合格,1-不合格)
	std::wstring strBoxHeightJudge;
	// 车厢长度[mm]
	std::wstring strCompartmentLength;
	// 车厢宽度[mm]
	std::wstring strCompartmentWidth;
	// 整车高度[mm]
	std::wstring strVehHeight;
	// 整车原始高度[mm]
	std::wstring strVehOrigHeight;
	// 整车高度判定(0-合格,1-不合格)
	std::wstring strVehHeightJudge;
	// 整车高更新原因
	std::wstring strVehHeightUpdateReason;
	// 整车长度[mm]
	std::wstring strVehLength;
	// 整车原始长度[mm]
	std::wstring strVehOrigLength;
	// 整车长度判定(0-合格,1-不合格)
	std::wstring strVehLengthJudge;
	// 整车长更新原因
	std::wstring strVehLengthUpdateReason;
	// 整车宽度[mm]
	std::wstring strVehWidth;
	// 整车原始宽度[mm]
	std::wstring strVehOrigWidth;
	// 整车宽度判定(0-合格,1-不合格)
	std::wstring strVehWidthJudge;
	// 整车宽更新原因
	std::wstring strVehWidthUpdateReason;
	// 判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strJudge;
	// 挂车栏板高度[mm]
	std::wstring strTlBoxHeight;
	// 挂车栏板高度判定(0-合格,1-不合格)
	std::wstring strTlBoxHeightJudge;
	// 挂车高度[mm]
	std::wstring strTlHeight;
	// 挂车原始高度[mm]
	std::wstring strTlOrigHeight;
	// 挂车高度判定(0-合格,1-不合格)
	std::wstring strTlHeightJudge;
	// 挂车高更新原因
	std::wstring strTlHeightUpdateReason;
	// 挂车长度[mm]
	std::wstring strTlLength;
	// 挂车原始长度[mm]
	std::wstring strTlOrigLength;
	// 挂车长度判定(0-合格,1-不合格)
	std::wstring strTlLengthJudge;
	// 挂车长更新原因
	std::wstring strTlLengthUpdateReason;
	// 挂车宽度[mm]
	std::wstring strTlWidth;
	// 挂车原始宽度[mm]
	std::wstring strTlOrigWidth;
	// 挂车宽度判定(0-合格,1-不合格)
	std::wstring strTlWidthJudge;
	// 挂车宽更新原因
	std::wstring strTlWidthUpdateReason;
	// 挂车判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strTlJudge;
	// 列车高度[mm]
	std::wstring strTnHeight;
	// 列车高度判定(0-合格,1-不合格)
	std::wstring strTnHeightJudge;
	// 列车长度[mm]
	std::wstring strTnLength;
	// 列车长度判定(0-合格,1-不合格)
	std::wstring strTnLengthJudge;
	// 列车宽度[mm]
	std::wstring strTnWidth;
	// 列车宽度判定(0-合格,1-不合格)
	std::wstring strTnWidthJudge;
	// 列车判定(0-合格,1-不合格,NULL-不合格)
	std::wstring strTnJudge;
	// 销轴距[mm]
	std::wstring strWheBase01;
	// 销轴距判定(0-合格,1-不合格)
	std::wstring strWheBase01Jud;
	// 12轴轴距[mm]
	std::wstring strWheBase12;
	// 12轴轴距判定(0-合格,1-不合格)
	std::wstring strWheBase12Jud;
	// 23轴轴距[mm]
	std::wstring strWheBase23;
	// 23轴轴距判定(0-合格,1-不合格)
	std::wstring strWheBase23Jud;
	// 34轴轴距3[mm]
	std::wstring strWheBase34;
	// 34轴轴距判定(0-合格,1-不合格)
	std::wstring strWheBase34Jud;
	// 45轴轴距4[mm]
	std::wstring strWheBase45;
	// 45轴轴距判定(0-合格,1-不合格)
	std::wstring strWheBase45Jud;
	// 56轴轴距5[mm]
	std::wstring strWheBase56;
	// 56轴轴距判定(0-合格,1-不合格)
	std::wstring strWheBase56Jud;
	// 轴距（含销轴距）判定
	std::wstring strWheBaseJud;
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