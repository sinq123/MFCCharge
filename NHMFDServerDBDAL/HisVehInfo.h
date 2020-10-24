/*
* Copyright (c) ��ɽ���ϻ������ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�HisVehInfo.h
* �ļ���ʶ��
* ��������ʷ������Ϣ��ģ��
*
* �汾��1.0
* ���ڣ�20xx-xx-xx
* ���ߣ�Cyx
*
*
* ��ʷ��Ϣ��
*
* �汾��1.0.0beta1
* ���ڣ�20xx-xx-xx
* ���ߣ�Cyx
* ���������ڿ���
*/


#if !defined (NHMFDSERVERDBMODEL_HISVEHINFO_H)
#define NHMFDSERVERDBMODEL_HISVEHINFO_H

#include <string>
#include "VehInfo.h"

struct SHisVehInfo
{
	// �Զ����
	std::wstring strAutoID;
	// ��־���(������ʱ����IP)
	std::wstring strRunningNumber;
	// ���������(Veh: Vehicle; ��ͬ)
	std::wstring strVehSN;
	// ���ƺ���
	std::wstring strPlateNumber;
	// �����������
	std::wstring strPlateTypeCode;
	// ��������
	std::wstring strPlateType;
	// ������ɫ
	std::wstring strPlateColour;
	// �������ʹ���
	std::wstring strVehTypeCode;
	// ��������
	std::wstring strVehType;
	// ����������
	std::wstring strOwner;
	// ����������
	std::wstring strOwnerCharacter;
	// �����˵�ַ
	std::wstring strOwnerAddress;
	// �����˵绰
	std::wstring strOwnerPhone;
	// �ʱ�
	std::wstring strPostCode;
	// �ͼ쵥λ
	std::wstring strInspectionUnit;
	// Ͻ��
	std::wstring strJurisdiction;
	// ʹ�����ʴ���
	std::wstring strUseCharacterCode;
	// ʹ������
	std::wstring strUseCharacter;
	// ʹ�ý׶�
	std::wstring strUsePhase;
	// �����������
	std::wstring strVehClass;
	// ��������������
	std::wstring strVehClassCode;
	// ������״̬����
	std::wstring strVehStatusCode;
	// ������״̬
	std::wstring strVehStatus;
	// ����ʶ�����
	std::wstring strVIN;
	// �����
	std::wstring strManufactureCountry;
	// ���쳧��
	std::wstring strManufacturer;
	// Ʒ��
	std::wstring strBrand;
	// �ͺ�
	std::wstring strModel;
	// ���ô���
	std::wstring strConfigCode;
	// �Ƿ�Ħ�г�
	std::wstring strIsMoto;
	// ���޼�ʻ��
	std::wstring strHasCab;
	// ������ɫ����
	std::wstring strColorCode;
	// ������ɫ
	std::wstring strColor;
	// �����������
	std::wstring strRecentDetDate;
	// �����Ч����
	std::wstring strValidityBegDate;
	// �����Ч��ֹ
	std::wstring strValidityEndDate;
	// ������Ч����
	std::wstring strRatingBegDate;
	// ������Ч��ֹ
	std::wstring strRatingEndDate;
	// �����ȼ�(NULL��δ�죬1��һ����2��������3��������4���ϸ�5�����ϸ�)
	std::wstring strTecRat;
	// ����ά����Ч����
	std::wstring strLev2BegDate;
	// ����ά����Ч��ֹ
	std::wstring strLev2EndDate;
	// ����ƾ֤��
	std::wstring strInsuranceNumber;
	// ���ս��
	std::wstring strInsuranceMoney;
	// ���չ�˾
	std::wstring strInsuranceCompany;
	// ������Ч����
	std::wstring strInsuranceBegDate;
	// ������ֹ����
	std::wstring strInsuranceEndDate;
	// ��������
	std::wstring strProductionDate;
	// ��֤����
	std::wstring strCertificationDate;
	// ���εǼ�����
	std::wstring strFirstRegisterDate;
	// ǿ�Ʊ�����ֹ
	std::wstring strScrappedDate;
	// �����ͺ�
	std::wstring strChassisModel;
	// ���������쳧��
	std::wstring strEngineManufacturer;
	// �������ͺ�
	std::wstring strEngineModel;
	// ����������
	std::wstring strEngineNumber;
	// �����������
	std::wstring strEngineStroke;
	// ����[ml]
	std::wstring strDisplacement;
	// �����[kW]
	std::wstring strRatedPower;
	// �Ť�ع���[kW](CTP: RatedTorquePower)
	std::wstring strRTP;
	// ��󾻹���[kW]
	std::wstring strMaximumNetPower;
	// �ת��[r/min]
	std::wstring strRatedRev;
	// �Ť��ת��[r/min]
	std::wstring strRatedTorqueRev;
	// ������
	std::wstring strCylinderNumber;
	// ȼ�ͱ���ʽ
	std::wstring strFuelPumpMode;
	// ���޴߻�ת����
	std::wstring strHasCatalyticConverter;
	// ���ͷ�ʽ(Sup: supply;)
	std::wstring strOilSupMode;
	// ������ʽ
	std::wstring strAirIntakeMode;
	// ȼ��������1
	std::wstring strFuelTypeCode;
	// ȼ�����1
	std::wstring strFuelType;
	// ȼ�Ϲ��1
	std::wstring strFuelMark;
	// ȼ��������2
	std::wstring strFuelTypeCode2;
	// ȼ�����2
	std::wstring strFuelType2;
	// ȼ�Ϲ��2
	std::wstring strFuelMark2;
	// ȼ��������3
	std::wstring strFuelTypeCode3;
	// ȼ�����3
	std::wstring strFuelType3;
	// ȼ�Ϲ��3
	std::wstring strFuelMark3;
	// �ٹ����ͺ�����ֵ[L/100km](Con: Consumption; ��ͬ)
	std::wstring strFuelConValue;
	// ������[kg]
	std::wstring strMaximumTotalMass;
	// ��������[kg]
	std::wstring strUnladenMass;
	// �˶�������[kg]
	std::wstring strRatedLoadingMass;
	// ׼ǣ��������[kg]
	std::wstring strPermittedTowingMass;
	// �˶��ؿ�
	std::wstring strRatedPassengerCapacity;
	// ��ʻ�ҹ���
	std::wstring strCabAltogetherRides;
	// ǰ�־�[mm]
	std::wstring strFrontTread;
	// ���־�[mm]
	std::wstring strRearTread;
	//// ���[mm]�����ϣ�
	//std::wstring strWheelbase;
	// �����[mm]
	std::wstring strWheBase01;
	// 12���[mm]
	std::wstring strWheBase12;
	// 23���[mm]
	std::wstring strWheBase23;
	// 34���[mm]
	std::wstring strWheBase34;
	// 45���[mm]
	std::wstring strWheBase45;
	// 56���[mm]
	std::wstring strWheBase56;
	// ����
	std::wstring strAxleNumber;
	// ������ʽ
	std::wstring strDriveType;
	// ��������
	std::wstring strDriveAxleNumber;
	// ������λ(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	std::wstring strDriveAxle;
	// �������������[kg]
	std::wstring strDriveAxleEmpMass;
	//// ˫ǰ��
	//std::wstring strDBFrontAxle;
	//// ˫ת����(DB: double, Ste: Steering)
	//std::wstring strDBSteShaft;
	//// ˫������
	//std::wstring strDBDrive;
	// ǰ����
	std::wstring strFrontAxleNumber;
	// ת������
	std::wstring strSteShaftNumber;
	// פ����
	std::wstring strPBNumber;
	// פ����λ(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
	std::wstring strPBAxle;
	// ��װ����
	std::wstring strCloseAxleNumber;
	// ��װ����ʽ
	std::wstring strCloseAxleType;
	// ��������ʽ
	std::wstring strGearBoxType;
	// ��λ��
	std::wstring strGearsNumber;
	// ��߳���[km]
	std::wstring strMaximumVelocity;
	// �Ƿ��������(True-��������,False-�Ƕ�������)
	std::wstring strIsIndependentSuspension;
	// ����ְ嵯��Ƭ��
	std::wstring strRearAxleSpringPieces;
	// ת����ʽ����
	std::wstring strSteeringTypeCode;
	// ת����ʽ
	std::wstring strSteeringType;
	// ��̥��
	std::wstring strTyreNumber;
	// ��̥���
	std::wstring strTyreSpecification;
	// ��̥��ѹ[mPa]
	std::wstring strTyrePressure;
	// ��̥��������(�����ߡ�б����)
	std::wstring strTyreCordArrange;
	// �ƶ���Դ(��ѹ�ƶ�,Һѹ�ƶ�)
	std::wstring strSBForceSource;
	// ǰ�յ��ƣ�0-��,1-һ��,2-����,4-�ĵƣ�
	std::wstring strHeadLightSystem;
	// ǰ�յƸ߶�[mm]
	std::wstring strLightHigh;
	// Զ���ܷ񵥶�����(Ind :Individually;)
	std::wstring strHLCanIndAdjusted;
	// ��̱����[km]
	std::wstring strTravelledDistance;
	// ����߶�[mm]
	std::wstring strBoxHeight;
	// ���䳤��[mm]
	std::wstring strCompartmentLength;
	// ������[mm]
	std::wstring strCompartmentWidth;
	// ����߶�[mm]
	std::wstring strCompartmentHeight;
	// �����߶�[mm]
	std::wstring strVehHeight;
	// ��������[mm]
	std::wstring strVehLength;
	// �������[mm]
	std::wstring strVehWidth;
	// �����ߴ�����
	std::wstring strDimFeature;
	// ������־
	std::wstring strEPSign;
	// �ϸ�֤����
	std::wstring strCertificateNumber;
	// ��������
	std::wstring strExhaPipeNum;
	// ǣ��������ϵͳ(0-��,1-��ժ��,2-����ժ��)
	std::wstring strTCS;
	// �Ƿ��ؿͳ�(true-��,�������-��)
	std::wstring strIsPassengerVeh;
	// �ŷű�׼
	std::wstring strEmiStandard;
	// �������[��]
	std::wstring strAnnualDetPeriod;
	// �������ϵͳ(OBD)
	std::wstring strOBD;
	// �����ƶ�ϵͳ(ABS)
	std::wstring strABS;
	// �Ť��[Nm]
	std::wstring strRatedTorque;
	// �Ť�س���[km/h]
	std::wstring strRatedTorqueVelocity;
	// �Ť�ع��ʱ�[%]
	std::wstring strRatedTorquePowerRto;
	// ����ʱ�[%]
	std::wstring strRatedPowerRto;
	// Ӫ��֤��
	std::wstring strOperationCerNumber;
	// ����ϵ��
	std::wstring strVehSeries; 
	// ��ת������ת��[��]
	std::wstring strLWheLSteAng; 
	// ��ת������ת��[��]
	std::wstring strRWheLSteAng; 
	// ��ת������ת��[��]
	std::wstring strLWheRSteAng; 
	// ��ת������ת��[��]
	std::wstring strRWheRSteAng; 
	// ������;
	std::wstring strVehUse; 
	// ��;����
	std::wstring strUseProperty; 
	// �ͳ����͵ȼ�
	std::wstring strPasVehTypeClass;
	// ����������ʽ
	std::wstring strGooVehBodyType;
	// ǣ��������������[kg]
	std::wstring strTtFullTotalMass;
	// ���ص���50km/h�ͺ�[L/100km]
	std::wstring strFlCsFc50;
	// ���ص���60km/h�ͺ�[L/100km]
	std::wstring strFlCsFc60;
	// �ҳ�����
	std::wstring strTlPlateNumber;
	// �ҳ�������
	std::wstring strTlOwner;
	// �ҳ�����ʶ�����
	std::wstring strTlVIN;
	// �ҳ��������ʹ���
	std::wstring strTlVehTypeCode;
	// �ҳ���������
	std::wstring strTlVehType;
	// �ҳ�Ʒ��
	std::wstring strTlBrand;
	// �ҳ��ͺ�
	std::wstring strTlModel;
	// �ҳ�Ӫ��֤��
	std::wstring strTlOperationCerNumber;
	// �ҳ���ʻ֤��
	std::wstring strTlTraCred;
	// �ҳ���ʼ�Ǽ�����
	std::wstring strTlFirstRegisterDate;
	// �ҳ���������
	std::wstring strTlProductionDate;
	// �ҳ�����߶�[mm]
	std::wstring strTlBoxHeight;
	// �ҳ��߶�[mm]
	std::wstring strTlHeight;
	// �ҳ�����[mm]
	std::wstring strTlLength;
	// �ҳ����[mm]
	std::wstring strTlWidth;
	// �ҳ�����
	std::wstring strTlAxleNumber;
	// �ҳ���װ����
	std::wstring strTlCloseAxleNumber;
	// �������ʱ��(������ʱ����)
	std::wstring strUpdateTime;
	// ��Ա�����¹�
	std::wstring strHasAccident;
	// �˿�վ����
	std::wstring strHasStandingArea;
	// �м�����װ��
	std::wstring strHasAssistant;
	// ����������
	std::wstring strIsRearEngine;
	// �ܱոֻ�����
	std::wstring strIsTemperingGlass;
	// ��ע
	std::wstring strRemark;
	// ����1
	std::wstring strReserved1;
	// ����2
	std::wstring strReserved2;
	// ����3
	std::wstring strReserved3;

public:
	SHisVehInfo& operator=(const SVehInfo& sData)
	{
		// �Զ����
		//this->strAutoID = sData.strAutoID;
		// ��־���(������ʱ����IP)
		//this->strRunningNumber = sData.strRunningNumber;
		// ���������(Veh: Vehicle; ��ͬ)
		this->strVehSN = sData.strVehSN;
		// ���ƺ���
		this->strPlateNumber = sData.strPlateNumber;
		// �����������
		this->strPlateTypeCode = sData.strPlateTypeCode;
		// ��������
		this->strPlateType = sData.strPlateType;
		// ��������
		this->strPlateColour = sData.strPlateColour;
		// �������ʹ���
		this->strVehTypeCode = sData.strVehTypeCode;
		// ��������
		this->strVehType = sData.strVehType;
		// ����������
		this->strOwner = sData.strOwner;
		// ����������
		this->strOwnerCharacter = sData.strOwnerCharacter;
		// �����˵�ַ
		this->strOwnerAddress = sData.strOwnerAddress;
		// �����˵绰
		this->strOwnerPhone = sData.strOwnerPhone;
		// �ͼ쵥λ
		this->strInspectionUnit = sData.strInspectionUnit;
		// Ͻ��
		this->strJurisdiction = sData.strJurisdiction;
		// ʹ�����ʴ���
		this->strUseCharacterCode = sData.strUseCharacterCode;
		// ʹ������
		this->strUseCharacter = sData.strUseCharacter;
		// ʹ�ý׶�
		this->strUsePhase = sData.strUsePhase;
		// �����������
		this->strVehClass = sData.strVehClass;
		// ��������������
		this->strVehClassCode = sData.strVehClassCode;
		// ������״̬����
		this->strVehStatusCode = sData.strVehStatusCode;
		// ������״̬
		this->strVehStatus = sData.strVehStatus;
		// ����ʶ�����
		this->strVIN = sData.strVIN;
		// �����
		this->strManufactureCountry = sData.strManufactureCountry;
		// ���쳧��
		this->strManufacturer = sData.strManufacturer;
		// Ʒ��
		this->strBrand = sData.strBrand;
		// �ͺ�
		this->strModel = sData.strModel;
		// ���ô���
		this->strConfigCode = sData.strConfigCode;
		// �Ƿ�Ħ�г�
		this->strIsMoto = sData.strIsMoto;
		// ���޼�ʻ��
		this->strHasCab = sData.strHasCab;
		// ������ɫ����
		this->strColorCode = sData.strColorCode;
		// ������ɫ
		this->strColor = sData.strColor;
		// �����������
		this->strRecentDetDate = sData.strRecentDetDate;
		// �����Ч����
		this->strValidityBegDate = sData.strValidityBegDate;
		// �����Ч��ֹ
		this->strValidityEndDate = sData.strValidityEndDate;
		// ������Ч����
		this->strRatingBegDate = sData.strRatingBegDate;
		// ������Ч��ֹ
		this->strRatingEndDate = sData.strRatingEndDate;
		// �����ȼ�(NULL��δ�죬1��һ����2��������3��������4���ϸ�5�����ϸ�)
		this->strTecRat = sData.strTecRat;
		// ����ά����Ч����
		this->strLev2BegDate = sData.strLev2BegDate;
		// ����ά����Ч��ֹ
		this->strLev2EndDate = sData.strLev2EndDate;
		// ����ƾ֤��
		this->strInsuranceNumber = sData.strInsuranceNumber;
		// ���ս��
		this->strInsuranceMoney = sData.strInsuranceMoney;
		// ���չ�˾
		this->strInsuranceCompany = sData.strInsuranceCompany;
		// ������Ч
		this->strInsuranceBegDate = sData.strInsuranceBegDate;
		// ������ֹ����
		this->strInsuranceEndDate = sData.strInsuranceEndDate;
		// ��������
		this->strProductionDate = sData.strProductionDate;
		// ��֤����
		this->strCertificationDate = sData.strCertificationDate;
		// ���εǼ�����
		this->strFirstRegisterDate = sData.strFirstRegisterDate;
		// ǿ�Ʊ�����ֹ
		this->strScrappedDate = sData.strScrappedDate;
		// �����ͺ�
		this->strChassisModel = sData.strChassisModel;
		// ���������쳧��
		this->strEngineManufacturer = sData.strEngineManufacturer;
		// �������ͺ�
		this->strEngineModel = sData.strEngineModel;
		// ����������
		this->strEngineNumber = sData.strEngineNumber;
		// �����������
		this->strEngineStroke = sData.strEngineStroke;
		// ����[ml]
		this->strDisplacement = sData.strDisplacement;
		// �����[kW]
		this->strRatedPower = sData.strRatedPower;
		// �Ť�ع���[kW](CTP: RatedTorquePower)
		this->strRTP = sData.strRTP;
		// ��󾻹���[kW]
		this->strMaximumNetPower = sData.strMaximumNetPower;
		// �ת��[r/min]
		this->strRatedRev = sData.strRatedRev;
		// �Ť��ת��[r/min]
		this->strRatedTorqueRev = sData.strRatedTorqueRev;
		// ������
		this->strCylinderNumber = sData.strCylinderNumber;
		// ȼ�ͱ���ʽ
		this->strFuelPumpMode = sData.strFuelPumpMode;
		// ���޴߻�ת����
		this->strHasCatalyticConverter = sData.strHasCatalyticConverter;
		// ���ͷ�ʽ(Sup: supply;)
		this->strOilSupMode = sData.strOilSupMode;
		// ������ʽ
		this->strAirIntakeMode = sData.strAirIntakeMode;
		// ȼ��������1
		this->strFuelTypeCode = sData.strFuelTypeCode;
		// ȼ�����1
		this->strFuelType = sData.strFuelType;
		// ȼ�Ϲ��1
		this->strFuelMark = sData.strFuelMark;
		// ȼ��������2
		this->strFuelTypeCode2 = sData.strFuelTypeCode2;
		// ȼ�����2
		this->strFuelType2 = sData.strFuelType2;
		// ȼ�Ϲ��2
		this->strFuelMark2 = sData.strFuelMark2;
		// ȼ��������3
		this->strFuelTypeCode3 = sData.strFuelTypeCode3;
		// ȼ�����3
		this->strFuelType3 = sData.strFuelType3;
		// ȼ�Ϲ��3
		this->strFuelMark3 = sData.strFuelMark3;
		// �ٹ����ͺ�����ֵ[L/100km](Con: Consumption; ��ͬ)
		this->strFuelConValue = sData.strFuelConValue;
		// ������[kg]
		this->strMaximumTotalMass = sData.strMaximumTotalMass;
		// ��������[kg]
		this->strUnladenMass = sData.strUnladenMass;
		// �˶�������[kg]
		this->strRatedLoadingMass = sData.strRatedLoadingMass;
		// ׼ǣ��������[kg]
		this->strPermittedTowingMass = sData.strPermittedTowingMass;
		// �˶��ؿ�
		this->strRatedPassengerCapacity = sData.strRatedPassengerCapacity;
		// ��ʻ�ҹ���
		this->strCabAltogetherRides = sData.strCabAltogetherRides;
		// ǰ�־�[mm]
		this->strFrontTread = sData.strFrontTread;
		// ���־�[mm]
		this->strRearTread = sData.strRearTread;
		//// ���[mm]
		//this->strWheelbase = sData.strWheelbase;
		// �����[mm]
		this->strWheBase01 = sData.strWheBase01;
		// 12���[mm]
		this->strWheBase12 = sData.strWheBase12;
		// 23���[mm]
		this->strWheBase23 = sData.strWheBase23;
		// 34���[mm]
		this->strWheBase34 = sData.strWheBase34;
		// 45���[mm]
		this->strWheBase45 = sData.strWheBase45;
		// 56���[mm]
		this->strWheBase56 = sData.strWheBase56;
		// ����
		this->strAxleNumber = sData.strAxleNumber;
		// ������ʽ
		this->strDriveType = sData.strDriveType;
		// ��������
		this->strDriveAxleNumber = sData.strDriveAxleNumber;
		// ������λ(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
		this->strDriveAxle = sData.strDriveAxle;
		// �������������[kg]
		this->strDriveAxleEmpMass = sData.strDriveAxleEmpMass;
		//// ˫ǰ��
		//this->strDBFrontAxle = sData.strDBFrontAxle;
		//// ˫ת����(DB: double, Ste: Steering)
		//this->strDBSteShaft = sData.strDBSteShaft;
		//// ˫������
		//this->strDBDrive = sData.strDBDrive;
		// ǰ������
		this->strFrontAxleNumber = sData.strFrontAxleNumber;
		// ת������
		this->strSteShaftNumber = sData.strSteShaftNumber;
		// פ����
		this->strPBNumber = sData.strPBNumber;
		// פ����λ(��Ӣ�Ķ��ŷָ�,���һ��ü�Ӣ�Ķ���)
		this->strPBAxle = sData.strPBAxle;
		// ��װ����
		this->strCloseAxleNumber = sData.strCloseAxleNumber;
		// ��װ����ʽ
		this->strCloseAxleType = sData.strCloseAxleType;
		// ��������ʽ
		this->strGearBoxType = sData.strGearBoxType;
		// ��λ��
		this->strGearsNumber = sData.strGearsNumber;
		// ��߳���[km]
		this->strMaximumVelocity = sData.strMaximumVelocity;
		// �Ƿ��������(True-��������,False-�Ƕ�������)
		this->strIsIndependentSuspension = sData.strIsIndependentSuspension;
		// ����ְ嵯��Ƭ��
		this->strRearAxleSpringPieces = sData.strRearAxleSpringPieces;
		// ת����ʽ����
		this->strSteeringTypeCode = sData.strSteeringTypeCode;
		// ת����ʽ
		this->strSteeringType = sData.strSteeringType;
		// ��̥��
		this->strTyreNumber = sData.strTyreNumber;
		// ��̥���
		this->strTyreSpecification = sData.strTyreSpecification;
		// ��̥��ѹ[mPa]
		this->strTyrePressure = sData.strTyrePressure;
		// ��̥��������(�����ߡ�б����)
		this->strTyreCordArrange = sData.strTyreCordArrange;
		// �ƶ���Դ(��ѹ�ƶ�,Һѹ�ƶ�)
		this->strSBForceSource = sData.strSBForceSource;
		// ǰ�յ��ƣ�0-��,1-һ��,2-����,4-�ĵƣ�
		this->strHeadLightSystem = sData.strHeadLightSystem;
		// ǰ�յƸ߶�[mm]
		this->strLightHigh = sData.strLightHigh;
		// Զ���ܷ񵥶�����(Ind :Individually;)
		this->strHLCanIndAdjusted = sData.strHLCanIndAdjusted;
		// ��̱����[km]
		this->strTravelledDistance = sData.strTravelledDistance;
		// ����߶�[mm]
		this->strBoxHeight = sData.strBoxHeight;
		// ���䳤��[mm]
		this->strCompartmentLength = sData.strCompartmentLength;
		// ������[mm]
		this->strCompartmentWidth = sData.strCompartmentWidth;
		// ����߶�[mm]
		this->strCompartmentHeight = sData.strCompartmentHeight;
		// �����߶�[mm]
		this->strVehHeight = sData.strVehHeight;
		// ��������[mm]
		this->strVehLength = sData.strVehLength;
		// �������[mm]
		this->strVehWidth = sData.strVehWidth;
		// �����ߴ�����
		this->strDimFeature = sData.strDimFeature;
		// ������־
		this->strEPSign = sData.strEPSign;
		// �ϸ�֤����
		this->strCertificateNumber = sData.strCertificateNumber;
		// ��������
		this->strExhaPipeNum = sData.strExhaPipeNum;
		// ǣ��������ϵͳ(0-��,1-��ժ��,2-����ժ��)
		this->strTCS = sData.strTCS;
		// �Ƿ��ؿͳ�(true-��,�������-��)
		this->strIsPassengerVeh = sData.strIsPassengerVeh;
		// �ŷű�׼
		this->strEmiStandard = sData.strEmiStandard;
		// �������[��]
		this->strAnnualDetPeriod = sData.strAnnualDetPeriod;
		// �������ϵͳ(OBD)
		this->strOBD = sData.strOBD;
		// �����ƶ�ϵͳ(ABS)
		this->strABS = sData.strABS;
		// �Ť��[Nm]
		this->strRatedTorque = sData.strRatedTorque;
		// �Ť�س���[km/h]
		this->strRatedTorqueVelocity = sData.strRatedTorqueVelocity;
		// �Ť�ع��ʱ�[%]
		this->strRatedTorquePowerRto = sData.strRatedTorquePowerRto;
		// ����ʱ�[%]
		this->strRatedPowerRto = sData.strRatedPowerRto;
		// Ӫ��֤��
		this->strOperationCerNumber = sData.strOperationCerNumber;
		// ����ϵ��
		this->strVehSeries = sData.strVehSeries; 
		// ��ת������ת��[��]
		this->strLWheLSteAng = sData.strLWheLSteAng; 
		// ��ת������ת��[��]
		this->strRWheLSteAng = sData.strRWheLSteAng; 
		// ��ת������ת��[��]
		this->strLWheRSteAng = sData.strLWheRSteAng; 
		// ��ת������ת��[��]
		this->strRWheRSteAng = sData.strRWheRSteAng; 
		// ������;
		this->strVehUse = sData.strVehUse; 
		// ��;����
		this->strUseProperty = sData.strUseProperty; 
		// �ͳ����͵ȼ�
		this->strPasVehTypeClass = sData.strPasVehTypeClass;
		// ����������ʽ
		this->strGooVehBodyType = sData.strGooVehBodyType;
		// ǣ��������������[kg]
		this->strTtFullTotalMass = sData.strTtFullTotalMass;
		// ���ص���50km/h�ͺ�[L/100km]
		this->strFlCsFc50 = sData.strFlCsFc50;
		// ���ص���60km/h�ͺ�[L/100km]
		this->strFlCsFc60 = sData.strFlCsFc60;
		// �ҳ�����
		this->strTlPlateNumber = sData.strTlPlateNumber;
		// �ҳ�������
		this->strTlOwner = sData.strTlOwner;
		// �ҳ�����ʶ�����
		this->strTlVIN = sData.strTlVIN;
		// �ҳ���������
		this->strTlVehType = sData.strTlVehType;
		// �ҳ�Ʒ��
		this->strTlBrand = sData.strTlBrand;
		// �ҳ��ͺ�
		this->strTlModel = sData.strTlModel;
		// �ҳ�Ӫ��֤��
		this->strTlOperationCerNumber = sData.strTlOperationCerNumber;
		// �ҳ���ʻ֤��
		this->strTlTraCred = sData.strTlTraCred;
		// �ҳ���ʼ�Ǽ�����
		this->strTlFirstRegisterDate = sData.strTlFirstRegisterDate;
		// �ҳ���������
		this->strTlProductionDate = sData.strTlProductionDate;
		// �ҳ�����߶�[mm]
		this->strTlBoxHeight = sData.strTlBoxHeight;
		// �ҳ��߶�[mm]
		this->strTlHeight = sData.strTlHeight;
		// �ҳ�����[mm]
		this->strTlLength = sData.strTlLength;
		// �ҳ����[mm]
		this->strTlWidth = sData.strTlWidth;
		// �ҳ�����
		this->strTlAxleNumber = sData.strTlAxleNumber;
		// �ҳ���װ����
		this->strTlCloseAxleNumber = sData.strTlCloseAxleNumber;
		// �������ʱ��(������ʱ����)
		this->strUpdateTime = sData.strUpdateTime;
		// ��Ա�����¹�
		this->strHasAccident = sData.strHasAccident;
		// �˿�վ����
		this->strHasStandingArea = sData.strHasStandingArea;
		// �м�����װ��
		this->strHasAssistant = sData.strHasAssistant;
		// ����������
		this->strIsRearEngine = sData.strIsRearEngine;
		// �ܱոֻ�����
		this->strIsTemperingGlass = sData.strIsTemperingGlass;
		// ��ע
		this->strRemark = sData.strRemark;
		// ����1
		this->strReserved1 = sData.strReserved1;
		// ����2
		this->strReserved2 = sData.strReserved2;
		// ����3
		this->strReserved3 = sData.strReserved3;

		return *this;
	}
};

#endif