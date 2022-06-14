#pragma once

#include <memory>
#include "Windows.h"
#include <time.h>

class AFX_EXT_CLASS CGADHVideoSnapLibAPI
{
public:
	static CGADHVideoSnapLibAPI& GetInstance(void);

private:
	CGADHVideoSnapLibAPI(void);
	virtual ~CGADHVideoSnapLibAPI(void);
	CGADHVideoSnapLibAPI(const CGADHVideoSnapLibAPI &);
	CGADHVideoSnapLibAPI & operator =(const CGADHVideoSnapLibAPI &);
	friend class std::auto_ptr<CGADHVideoSnapLibAPI>;

public:
	void OnOnePicture(LONG ILoginID, BYTE *pBuf, UINT RevLen, UINT EncodeType, UINT CmdSerial);
	void WriteLoginErrorReason(int nError);
public:
	// 设置NVR时间
	DWORD SetNVRDateTime(void);
	// 拍照接口
	DWORD TakePhoto(const CStringW& strIP, const int& nPort, const CStringW& strUserName, const CStringW& strPassword, const int& nChannel, const CStringW& strFilePath, const int& nMaxPhotoTimes=5, const int& nPicSize = 0xff, const int& nPicQuality =0);
	// 录像接口
	DWORD TakeStartVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN,  const CStringW& strCamera, const CStringW& strDetItem);
	DWORD TakeEndVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN, const CStringW& strCamera, const CStringW& strDetItem);

	// 拍照
	// 车速
	bool TakeSpeedPhoto(const CStringW& strRunningNumber);
	// 制动
	bool TakeAxle1BrakePhoto(const CStringW& strRunningNumber);
	bool TakeAxle2BrakePhoto(const CStringW& strRunningNumber);
	bool TakeAxle3BrakePhoto(const CStringW& strRunningNumber);
	bool TakeAxle4BrakePhoto(const CStringW& strRunningNumber);
	bool TakeAxle5BrakePhoto(const CStringW& strRunningNumber);
	bool TakeAxle6BrakePhoto(const CStringW& strRunningNumber);
	bool TakeAxle1LoadBrakePhoto(const CStringW& strRunningNumber);
	bool TakeAxle2LoadBrakePhoto(const CStringW& strRunningNumber);
	bool TakeAxle3LoadBrakePhoto(const CStringW& strRunningNumber);
	bool TakeAxle4LoadBrakePhoto(const CStringW& strRunningNumber);
	bool TakePBPhoto(const CStringW& strRunningNumber);
	// 底盘(遥控器、条码触发时使用)
	bool TakeChaPhoto(const CStringW& strRunningNumber);
	// 灯光
	bool TakeLeftMaHLPhoto(const CStringW& strRunningNumber, const int nMaxPhotoTimes=5);
	bool TakeLeftMiHLPhoto(const CStringW& strRunningNumber, const int nMaxPhotoTimes=5);
	bool TakeRightMaHLPhoto(const CStringW& strRunningNumber, const int nMaxPhotoTimes=5);
	bool TakeRightMiHLPhoto(const CStringW& strRunningNumber, const int nMaxPhotoTimes=5);
	// 侧滑
	bool TakeSideslipPhoto(const CStringW& strRunningNumber);
	// 外廓
	bool TakeDimensionFrontPhoto(const CStringW& strRunningNumber);
	bool TakeDimensionSidePhoto(const CStringW& strRunningNumber);
	// 外廓本地报告单照片
	bool TakeDimensionFrontPhotoL(const CStringW& strRunningNumber);
	bool TakeDimensionSidePhotoL(const CStringW& strRunningNumber);
	// 整备
	bool TakeUnladenMassFrontPhoto(const CStringW& strRunningNumber);
	bool TakeUnladenMassRearPhoto(const CStringW& strRunningNumber);

	// 动态区域1
	bool TakeDynInPhoto(const CStringW& strRunningNumber,const CStringW& strAreaN);
	bool TakeDynOutPhoto(const CStringW& strRunningNumber,const CStringW& strAreaN);
	// 底盘通道（检测线）(PDA触发时使用)
	bool TakeChaLPhoto(const CStringW& strRunningNumber,const CStringW& strAreaN);

	// 路试行车区域1
	bool TakeRoadSBInPhoto(const CStringW& strRunningNumber, const CStringW& strAreaN);
	bool TakeRoadSBOutPhoto(const CStringW& strRunningNumber, const CStringW& strAreaN);
	// 路试驻车
	bool TakeRoadPBPhoto(const CStringW& strRunningNumber, const CStringW& strAreaN);

	// 综检
	// 制动
	bool TakeBKPhoto_MFD(const CStringW& strRunningNumber);
	// 灯光
	bool TakeHLPhoto_MFD(const CStringW& strRunningNumber);
	// 测功
	bool TakePWPhoto_MFD(const CStringW& strRunningNumber);
	// 地盘
	bool TakeDCPhoto_MFD(const CStringW& strRunningNumber);
	// 录像
	// 车速
	bool TakeStartSpeedVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN);
	bool TakeEndSpeedVideo(const CStringW& strRunningNumber,  const COleDateTime& odtVideoEndTime, const CStringW& strAreaN);
	// 制动
	bool TakeStartAxle1BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndAxle1BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);

	bool TakeStartAxle2BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndAxle2BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);

	bool TakeStartAxle3BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndAxle3BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);

	bool TakeStartAxle4BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndAxle4BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);

	bool TakeStartAxle5BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndAxle5BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);

	bool TakeStartAxle6BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndAxle6BrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);

	bool TakeStartAxle1LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndAxle1LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);

	bool TakeStartAxle2LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndAxle2LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);

	bool TakeStartAxle3LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndAxle3LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);

	bool TakeStartAxle4LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndAxle4LoadBrakeVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);

	bool TakeStartPBVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndPBVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);
	// 灯光
	bool TakeStartLeftMaHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndLeftMaHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);

	bool TakeStartLeftMiHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndLeftMiHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);

	bool TakeStartRightMiHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndRightMiHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);

	bool TakeStartRightMaHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndRightMaHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);
	// 侧滑
	bool TakeStartSideslipVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndSideslipVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);
	
	// 外廓
	bool TakeStartDimensionFrontVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndDimensionFrontVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);
	bool TakeStartDimensionSideVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndDimensionSideVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);
	
	// 整备
	bool TakeStartUnladenMassFront45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndUnladenMassFront45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);
	bool TakeStartUnladenMassRear45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndUnladenMassRear45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);

	// 外观区域1
	bool TakeStartAppF45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strArea);
	bool TakeEndAppF45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strArea);
	bool TakeStartAppR45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strArea);
	bool TakeEndAppR45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strArea);

	// 动态区域1
	bool TakeStartDynInVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strArea);
	bool TakeEndDynInVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strArea);
	bool TakeStartDynOutVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strArea);
	bool TakeEndDynOutVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strArea);

	// 底盘(遥控器、条码触发时使用)
	bool TakeStartChaVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndChaVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);
	// 底盘通道（检测线）(PDA触发时使用)
	bool TakeStartChaLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndChaLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime,const CStringW& strLineNumber);

	// 路试行车
	bool TakeStartRoadSBInVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strArea);
	bool TakeEndRoadSBInVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strArea);
	bool TakeStartRoadSBOutVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strArea);
	bool TakeEndRoadSBOutVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strArea);

	// 路试驻车
	bool TakeStartRoadPBVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strArea);
	bool TakeEndRoadPBVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strArea);

	// 下载视频
	bool DownloadVideo( CStringW& strIP, int& nPort, CStringW& strUserName, CStringW& strPassword, int& nChannel, const CStringW& strVideoPath, const COleDateTime& odtVideoStartTime, const COleDateTime& odtVideoEndTime);
	// 创建目录
	bool CreateMultipleDirectory(const CStringW& strPath);
	// MP4转FLV
	void MP4ToFLV(const CStringW& strSourceFile, const CStringW& strTargetFile);
private:
	// 加载配置文件
	void LoadConfig(void);
	// 生成日志文件
	void GenLogFile(void);
	// 获取配置信息
	void GetCameraParas(const CStringW& strCamera, CStringW& strIP, int& nPort, CStringW& strUserName, CStringW& strPassword, int& nChannel);
	// 生成照片文件路径
	CStringW GenPhotoFilePath(const CStringW& strRunningNumber, const CStringW& strDetItem, const CStringW& strPhotoType);
	// 获取配置信息
	void GetCameraParas_MFD(const CStringW& strCamera, CStringW& strIP, int& nPort, CStringW& strUserName, CStringW& strPassword, int& nChannel, int& nPicSize);
	// 生成本地照片文件路径
	CStringW GenPhotoFilePath_Rep(const CStringW& strRunningNumber, const CStringW& strPhoItem);

private:
	bool m_bInitDVR;
	// 抓拍方式 1-设备抓拍 其它-预览抓拍
	int m_nSnapMethod;
	// 图片格式
	int m_nImageFormat;

private:
	// 日志文件路径（主程序）
	CStringW m_strLogFilePath;
	CStringW m_strLogFilePath1;
	// 本模块名
	CStringW m_strModName;
	// 照片路径
	CStringW m_strPhotoPath;
};

