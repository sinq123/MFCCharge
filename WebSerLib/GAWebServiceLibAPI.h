#pragma once

#include <memory>
#include <string>
#include <list>
#include <vector>

#include "..\GAConstDef\GAConstDef.h"

#include "..\NHMFDServerDBDAL\NHMFDServerDBDAL.h"
#ifdef _DEBUG
#pragma comment( lib, "..\\Debug\\NHMFDServerDBDAL_D.lib" )
#else
#pragma comment( lib, "..\\Release\\NHMFDServerDBDAL.lib" )
#endif

class AFX_EXT_CLASS CGAWebServiceLibAPI
{
public:
	static CGAWebServiceLibAPI& GetInstance(void);

private:
	CGAWebServiceLibAPI(void);
	virtual ~CGAWebServiceLibAPI(void);
	CGAWebServiceLibAPI(const CGAWebServiceLibAPI &);
	CGAWebServiceLibAPI & operator =(const CGAWebServiceLibAPI &);
	friend class std::auto_ptr<CGAWebServiceLibAPI>;

public:
	// ����WebService��ַ
	void SetURL(const CStringW& strURL);
	CStringW GetURL(void);
	// ���ýӿ����к�
	void SetIFSN(const CStringW& strIFSN);
	CStringW GetIFSN(void);
	// ���ü���������
	void SetStationNum(const CStringW& strStationNum);
	CStringW GetStationNum(void);
	// ���ü���߱��
	void SetLineNum(const CStringW& strLineNum);
	CStringW GetLineNum(void);
	// ���ù�λ�����豸���
	void SetPosEquNum(const CStringW& strPosEquNum);
	CStringW GetPosEquNum(void);

	// �������
	CStringW HandlePlaNum(const SDetLog &sDetLog);
	// ������ֵ
	// pwchNumStr����ֵ�ַ���ָ��
	// nNumPlaces����ֵ��λ��
	// nDecPlaces��С��λ��
	CStringW HandleNumber(const wchar_t *pwchNumStr, const int nNumPlaces, const int nDecPlaces);
	// �����ж�
	CStringW HandleJudge(const wchar_t *pwchJudge);
	// �����ж�
	CStringW HandleJudge_EmpRetZero(const wchar_t *pwchJudge);
	
	// ������־�ļ�
	void GenLogFile(void);

public:
	// 18C55-������������Ŀ��ʼ��Ϣ
	bool DetItemStart(const CStringW& strRunningNumber, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool DetItemStart(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool UploadDimensionData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool UploadDimensionData(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SDimensionData& sDimensionData, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool UpEndDimensionData(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	// 18C58-������������Ŀ������Ϣ
	bool DetItemEnd(const CStringW& strRunningNumber, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool DetItemEnd(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const CStringW& strDetItem, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	// 18C63-������������Ƭ��������Ƭ��Ϣ
	bool UploadPhoto(const CStringW& strRunningNumber, const CStringW& strPhotoPath, const CStringW& strDetItem, const CStringW& strPhotoType, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool UploadPhoto(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, 
	const CStringW& strPhotoPath, const CStringW& strDetItem, const CStringW& strPhotoType, SGAMsg& sMsg);
	// 18C72-����������ҵ���˰�
	bool BusinessBack(const CStringW& strRunningNumber, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool BusinessBack(const SDetLog &sDetLog, SGAMsg& sMsg);
	// 18C21-��ȡ����ҵ����ˮ��
	bool GetBusinessNum(const CStringW& strReportNumber, SGABusinessNum &sGABusinessNum, SGAMsg& sMsg);
	// �����ӿڿ�ʼ
	// 18S01-��ȡ������ˮ��
	bool ACGetNetReportNumber(const SDetLog& sDetLog, const SHisVehInfo& sHisVehInfo, std::wstring &strRunNum, SGAMsg& sMsg);
	// ������Ŀ���գ�18S04
	bool ACVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strPhotoCode, SGAMsg& sMsg, const CStringW& strLineNumber=L"1", _ConnectionPtr pConnection = NULL);
	bool ACVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, const CStringW& strPhotoCode,  SGAMsg& sMsg, const CStringW& strLineNumber=L"1");
	// �����ӿڽ���
	// ���ɽӿڿ�ʼ
	// 18J11-��⹤λ��ʼ
	bool HCTestItemStart(const CStringW& strRunningNumber, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool HCTestItemStart(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, SGAMsg& sMsg);
	// 18J31-��Ŀ���մ���
	bool HCVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strPhotoCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool HCVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, 
		const CStringW& strPhotoCode, SGAMsg& sMsg);
	// 18J12-��⹤λ����
	bool HCTestItemEnd(const CStringW& strRunningNumber, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool HCTestItemEnd(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, SGAMsg& sMsg);
	// 18C99-������������ά����Ƭ�ϴ�
	bool HCDim2DPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, 
		const CStringW& strPhotoCode, const CStringW& strPhotoPath, const SGABusinessNum& sGABusinessNum, SGAMsg& sMsg);
	// CHK10
	bool HCTestItemStartCHK10(const CStringW& strRunningNumber, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool HCTestItemStartCHK10(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, SGAMsg& sMsg);
	// CHK11
	bool HCTestItemEndCHK11(const CStringW& strRunningNumber, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool HCTestItemEndCHK11(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, SGAMsg& sMsg);
	// ���ɽӿڽ���
	// ��ͨ�Ƽ��ӿڿ�ʼ
	// 3.4.4 18M14-������Ŀ����
	bool CTKJVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strPhotoCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool CTKJVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, 
		const CStringW& strPhotoCode, SGAMsg& sMsg);
	// ��ͨ�Ƽ��ӿڽ���
	// ��֮���ӿڿ�ʼ
	// 2.1.��Ƶ��ȡ�ӿ�
	bool AZCVehVideo(const CStringW& strRunningNumber, const CStringW& strBeginTimes, const CStringW& strEndTimes, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool AZCVehVideo(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strBeginTimes, 
		const CStringW& strEndTimes, const CStringW& strItemCode, SGAMsg& sMsg);
	// 2.2.��λ��ͼ�ӿ�
	bool AZCVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strPhotoCode,  SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool AZCVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes,  const CStringW& strItemCode, const CStringW& strPhotoCode, SGAMsg& sMsg);
	// 
	// ��֮���ӿڽ���
	// ����ӿڿ�ʼ
	// 2.7.1.18W55-��ʼ¼��
	bool HYTestItemStart(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strVideoItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool HYTestItemStart(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, const CStringW& strVideoItemCode, SGAMsg& sMsg);
	// 2.7.3.18N63-��ȡ����ͷץ����Ƭ
	bool HYVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strPhotoCode, const CStringW& strVideoItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool HYVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, 
		const CStringW& strPhotoCode, const CStringW& strVideoItemCode, SGAMsg& sMsg);
	// 2.7.2.18W58-����¼��
	bool HYTestItemEnd(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strVideoItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool HYTestItemEnd(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, const CStringW& strVideoItemCode, SGAMsg& sMsg);
	// ����ӿڽ���
	// ������Ԫ��ʼ
	// ����JW006(ǣ��ͬ�죬��ˮ�Ų�һ�����⴦��)
	bool HGBYTakePhotos(const CStringW& strRunningNumber, const CStringW& strDetItem, const CStringW& strPssk, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool HGBYTakePhotos(const SDetLog& sDetLog, const SDetTimes& sDetTimes, const SHisVehInfo& sHisVehInfo, const CStringW& strDetItem, const CStringW& strPssk, SGAMsg& sMsg);
	// ������Ԫ����
	// �Ĵ��Ƕܿ�ʼ
	// 2.1.3.3.1.1.�����ߴ����ݲ�ѯ��18J17��
	bool SCXDGetDimData(const CStringW& strReportNumber,SGAMsg& sMsg);
	// 2.1.3.3.2.1.��⹤λ¼��ʼ��18J11��
	bool SCXDTestItemStart(const CStringW& strRunningNumber, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool SCXDTestItemStart(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, SGAMsg& sMsg);
	// 2.1.3.3.2.2.��⹤λ¼�������18J12��
	bool SCXDTestItemEnd(const CStringW& strRunningNumber, const CStringW& strItemCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool SCXDTestItemEnd(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, SGAMsg& sMsg);
	// 2.1.3.3.2.4.��⹤λ����ͷ���մ�����18J31��
	bool SCXDVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strPhotoCode, SGAMsg& sMsg, _ConnectionPtr pConnection = NULL);
	bool SCXDVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, 
		const CStringW& strPhotoCode, SGAMsg& sMsg);
	// �Ĵ��Ƕܽ���
	// ̫ԭ��˹��ʼ
	bool TYSSVehPhoto(const CStringW& strRunningNumber, const CStringW& strItemCode, const CStringW& strPhotoCode, SGAMsg& sMsg, const CStringW& strLineNumber=L"1", _ConnectionPtr pConnection = NULL);
	bool TYSSVehPhoto(const SDetLog &sDetLog, const SHisVehInfo &sHisVehInfo, const SDetTimes &sDetTimes, const CStringW& strItemCode, const CStringW& strPhotoCode,  SGAMsg& sMsg, const CStringW& strLineNumber=L"1");
	// ̫ԭ��˹����

public:
	// �����������
	inline CString GetStationName() {
		return m_strStationName;
	}
	// Ӧ�ó������
	inline CString GetCjsqbh() {
		return m_strCjsqbh;
	}
	// ��λ��������
	inline CString GetDwjgdm() {
		return m_strDwjgdm;
	}
	// ��λ����
	inline CString GetDwmc() {
		return m_strDwmc;
	}
	// �û���ʶ
	inline CString GetYhbz() {
		return m_strYhbz;
	}
	// �û�����
	inline CString GetYhxm() {
		return m_strYhxm;
	}
	// �ն˱�ʶ
	inline CString GetZdbs() {
		return m_strZdbs;
	}
	// �ӿڰ汾
	inline int GetNetPlatform() {
		return m_nNetPlatform;
	}
	// �Ƿ������
	inline bool GetWheelBase() {
		return m_bWheelBase;
	}
	// �Ƿ������(�³����)
	inline bool GetWheelBaseNew() {
		return m_bWheelBaseNew;
	}
	// �Ƿ��������
	inline bool GetPinbase() {
		return m_bPinbase;
	}
	// �Ƿ��������(�³����)
	inline bool GetPinbaseNew() {
		return m_bPinbaseNew;
	}
	// �Ƿ�������άͼ
	inline bool GetM2D() {
		return m_bM2D;
	}

private:
	// ���������ļ�
	void LoadConfig(void);
	// ��ʼ��xml����
	void InitXmlCfg(void);
	// ��ʼ������
	void InitData(void);
	// ��ȡ�����Ŀ����
	CStringW GetDetItem(const SHisVehInfo& sHisVehInfo, const SDetItem& sDetItem);
	const wchar_t * JudgeTranslate(LPCTSTR szJudge);
	// ��ʽ���ƶ�����
	std::wstring BrakeCurveFormat(const std::string& strCurve);
	// ���Ҷ�Ӧ����Ƭ���
	CStringW GetGAPhotoNumByType(const CStringW &strPhotoType);
	// ����GADataRecord
	bool SaveGADataRecord(_ConnectionPtr pConnection, const SGADataRecord &sGADataRecord, SGAMsg& sMsg);

private:
	CString DecodeURI(LPCSTR szURIString);
	CString DecodeURI(LPCWSTR szURIString);
	std::string Base64Encode(LPBYTE pBindryBuf, UINT nBufLen);
	void Base64Encode(LPBYTE pBindryBuf, UINT nBufLen, std::string &strCliper);
	std::string Base64Encode(LPCTSTR szFilePath);
	std::string Base64EncodeRaw(LPCTSTR szFilePath);
	void Base64Encode(LPCTSTR szFilePath, std::string &strCliper);
	void Base64EncodeRaw(LPCTSTR szFilePath, std::string &strCliper);
	CString UrlCodeOrNot(const wchar_t * const pwch);
	// ��С����  
	std::string ReducedCurveData(LPCSTR szCurveData);

private:
	// ��־�ļ�·����������
	CStringW m_strLogFilePath;
	// ��ģ����
	CStringW m_strModName;

private:
	// �Ƿ������
	bool m_bWheelBase;
	// �Ƿ������(�³����)
	bool m_bWheelBaseNew;
	// �Ƿ��������
	bool m_bPinbase;
	// �Ƿ��������(�³����)
	bool m_bPinbaseNew;
	// �Ƿ�������άͼ
	bool m_bM2D;

	// �ӿڰ汾
	int m_nNetPlatform;
	// �����ӿڰ汾
	int m_nGAVersion;
	// WebService��ַ
	CStringW m_strURL;
	char* m_pchURL;
	// �ӿ����к�
	CStringW m_strIFSN;

	// WebService��ַ Teo
	CStringW m_strURL_Two;
	char* m_pchURL_Two;
	// �ӿ����к� Two
	CStringW m_strIFSN_Two;

	// WebService��ַ Three
	CStringW m_strURL_Three;
	char* m_pchURL_Three;
	// �ӿ����к� Two
	CStringW m_strIFSN_Three;

	// ����������
	CStringW m_strStationNum;
	// �����������
	CStringW m_strStationName;
	// ����߱��
	CStringW m_strLineNum;
	// ��λ�����豸���
	CStringW m_strPosEquNum;

	//Ӧ�ó������
	CStringW m_strCjsqbh;
	//��λ��������
	CStringW m_strDwjgdm;
	//��λ����
	CStringW m_strDwmc;
	//�û���ʶ
	CStringW m_strYhbz;
	//�û�����
	CStringW m_strYhxm;
	//�ն˱�ʶ
	CStringW m_strZdbs;
	//ϵͳ���
	CStringW m_strSysType;
private:
	// ��ѯXMLͷ
	CStringW strQueryHead;
	// ��ѯXMLδ
	CStringW strQueryTail;
	// д��XMLͷ
	CStringW strWriteHead;
	// д��XMLδ
	CStringW strWriteTail;

private:
	// ��������
	std::list<SVeh_PlateType> m_lsVeh_PlateType;
	// ��������
	std::list<SVeh_VehType> m_lsVeh_VehType;
	// ������ɫ
	std::list<SVeh_Color> m_lsVeh_Color;
	// ʹ������
	std::list<SVeh_UseCharacter> m_lsVeh_UseCharacter;
	// ȼ�����
	std::list<SVeh_FuelType> m_lsVeh_FuelType;
	// ������ַ
	std::list<SVeh_Address> m_lsVeh_Address;

};
