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
	// ����NVRʱ��
	DWORD SetNVRDateTime(void);
	// ���սӿ�
	DWORD TakePhoto(const CStringW& strIP, const int& nPort, const CStringW& strUserName, const CStringW& strPassword, const int& nChannel, const CStringW& strFilePath, const int& nMaxPhotoTimes=5, const int& nPicSize = 0xff, const int& nPicQuality =0);
	// ¼��ӿ�
	DWORD TakeStartVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN,  const CStringW& strCamera, const CStringW& strDetItem);
	DWORD TakeEndVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strAreaN, const CStringW& strCamera, const CStringW& strDetItem);

	// ����
	// ����
	bool TakeSpeedPhoto(const CStringW& strRunningNumber);
	// �ƶ�
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
	// ����(ң���������봥��ʱʹ��)
	bool TakeChaPhoto(const CStringW& strRunningNumber);
	// �ƹ�
	bool TakeLeftMaHLPhoto(const CStringW& strRunningNumber, const int nMaxPhotoTimes=5);
	bool TakeLeftMiHLPhoto(const CStringW& strRunningNumber, const int nMaxPhotoTimes=5);
	bool TakeRightMaHLPhoto(const CStringW& strRunningNumber, const int nMaxPhotoTimes=5);
	bool TakeRightMiHLPhoto(const CStringW& strRunningNumber, const int nMaxPhotoTimes=5);
	// �໬
	bool TakeSideslipPhoto(const CStringW& strRunningNumber);
	// ����
	bool TakeDimensionFrontPhoto(const CStringW& strRunningNumber);
	bool TakeDimensionSidePhoto(const CStringW& strRunningNumber);
	// �������ر��浥��Ƭ
	bool TakeDimensionFrontPhotoL(const CStringW& strRunningNumber);
	bool TakeDimensionSidePhotoL(const CStringW& strRunningNumber);
	// ����
	bool TakeUnladenMassFrontPhoto(const CStringW& strRunningNumber);
	bool TakeUnladenMassRearPhoto(const CStringW& strRunningNumber);

	// ��̬����1
	bool TakeDynInPhoto(const CStringW& strRunningNumber,const CStringW& strAreaN);
	bool TakeDynOutPhoto(const CStringW& strRunningNumber,const CStringW& strAreaN);
	// ����ͨ��������ߣ�(PDA����ʱʹ��)
	bool TakeChaLPhoto(const CStringW& strRunningNumber,const CStringW& strAreaN);

	// ·���г�����1
	bool TakeRoadSBInPhoto(const CStringW& strRunningNumber, const CStringW& strAreaN);
	bool TakeRoadSBOutPhoto(const CStringW& strRunningNumber, const CStringW& strAreaN);
	// ·��פ��
	bool TakeRoadPBPhoto(const CStringW& strRunningNumber, const CStringW& strAreaN);

	// �ۼ�
	// �ƶ�
	bool TakeBKPhoto_MFD(const CStringW& strRunningNumber);
	// �ƹ�
	bool TakeHLPhoto_MFD(const CStringW& strRunningNumber);
	// �⹦
	bool TakePWPhoto_MFD(const CStringW& strRunningNumber);
	// ����
	bool TakeDCPhoto_MFD(const CStringW& strRunningNumber);
	// ¼��
	// ����
	bool TakeStartSpeedVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strAreaN);
	bool TakeEndSpeedVideo(const CStringW& strRunningNumber,  const COleDateTime& odtVideoEndTime, const CStringW& strAreaN);
	// �ƶ�
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
	// �ƹ�
	bool TakeStartLeftMaHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndLeftMaHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);

	bool TakeStartLeftMiHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndLeftMiHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);

	bool TakeStartRightMiHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndRightMiHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);

	bool TakeStartRightMaHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndRightMaHLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);
	// �໬
	bool TakeStartSideslipVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndSideslipVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);
	
	// ����
	bool TakeStartDimensionFrontVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndDimensionFrontVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);
	bool TakeStartDimensionSideVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndDimensionSideVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);
	
	// ����
	bool TakeStartUnladenMassFront45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndUnladenMassFront45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);
	bool TakeStartUnladenMassRear45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndUnladenMassRear45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);

	// �������1
	bool TakeStartAppF45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strArea);
	bool TakeEndAppF45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strArea);
	bool TakeStartAppR45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strArea);
	bool TakeEndAppR45Video(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strArea);

	// ��̬����1
	bool TakeStartDynInVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strArea);
	bool TakeEndDynInVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strArea);
	bool TakeStartDynOutVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strArea);
	bool TakeEndDynOutVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strArea);

	// ����(ң���������봥��ʱʹ��)
	bool TakeStartChaVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndChaVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strLineNumber);
	// ����ͨ��������ߣ�(PDA����ʱʹ��)
	bool TakeStartChaLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strLineNumber);
	bool TakeEndChaLVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime,const CStringW& strLineNumber);

	// ·���г�
	bool TakeStartRoadSBInVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strArea);
	bool TakeEndRoadSBInVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strArea);
	bool TakeStartRoadSBOutVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strArea);
	bool TakeEndRoadSBOutVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strArea);

	// ·��פ��
	bool TakeStartRoadPBVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoStartTime, const CStringW& strArea);
	bool TakeEndRoadPBVideo(const CStringW& strRunningNumber, const COleDateTime& odtVideoEndTime, const CStringW& strArea);

	// ������Ƶ
	bool DownloadVideo( CStringW& strIP, int& nPort, CStringW& strUserName, CStringW& strPassword, int& nChannel, const CStringW& strVideoPath, const COleDateTime& odtVideoStartTime, const COleDateTime& odtVideoEndTime);
	// ����Ŀ¼
	bool CreateMultipleDirectory(const CStringW& strPath);
	// MP4תFLV
	void MP4ToFLV(const CStringW& strSourceFile, const CStringW& strTargetFile);
private:
	// ���������ļ�
	void LoadConfig(void);
	// ������־�ļ�
	void GenLogFile(void);
	// ��ȡ������Ϣ
	void GetCameraParas(const CStringW& strCamera, CStringW& strIP, int& nPort, CStringW& strUserName, CStringW& strPassword, int& nChannel);
	// ������Ƭ�ļ�·��
	CStringW GenPhotoFilePath(const CStringW& strRunningNumber, const CStringW& strDetItem, const CStringW& strPhotoType);
	// ��ȡ������Ϣ
	void GetCameraParas_MFD(const CStringW& strCamera, CStringW& strIP, int& nPort, CStringW& strUserName, CStringW& strPassword, int& nChannel, int& nPicSize);
	// ���ɱ�����Ƭ�ļ�·��
	CStringW GenPhotoFilePath_Rep(const CStringW& strRunningNumber, const CStringW& strPhoItem);

private:
	bool m_bInitDVR;
	// ץ�ķ�ʽ 1-�豸ץ�� ����-Ԥ��ץ��
	int m_nSnapMethod;
	// ͼƬ��ʽ
	int m_nImageFormat;

private:
	// ��־�ļ�·����������
	CStringW m_strLogFilePath;
	CStringW m_strLogFilePath1;
	// ��ģ����
	CStringW m_strModName;
	// ��Ƭ·��
	CStringW m_strPhotoPath;
};

