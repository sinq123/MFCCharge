#include "StdAfx.h"
#include "Standard.h"
#include <atlstr.h> 

#include <ctime>

#include "..\NHWin32Lib\NHWin32Lib.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHWin32Lib_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHWin32Lib.lib")
#endif

#include "..\NHDetCommModu\NHDetCommModu.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\NHDetCommModu_D.lib")
#else
#pragma comment(lib, "..\\Release\\NHDetCommModu.lib")
#endif

CStandard::CStandard(void)
{
}


CStandard::~CStandard(void)
{
}

// С��λ��Լ�������ٱ��໬���ƶ���·��ʹ��1λС��������ʹ��2λС��

void CStandard::GetSpeedometer(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetSpeedometer_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetSpeedometer_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetSpeedometer_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// �����ֻ�����

		// ���ٱ��������[km/h]
		sDetStandard.strSM_UpperLimit = L"30.0";
		// ���ٱ��������[km/h]
		sDetStandard.strSM_LowerLimit = L"23.6";
	}
	else 
	{
		// ���ֻ����ϻ�����

		// ���ٱ��������[km/h]
		sDetStandard.strSM_UpperLimit = L"40.0";
		// ���ٱ��������[km/h]
		sDetStandard.strSM_LowerLimit = L"32.8";
	}
}

void CStandard::GetSpeedometer_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// �����ֻ�����

		// ���ٱ��������[km/h]
		sDetStandard.strSM_UpperLimit = L"30.0";
		// ���ٱ��������[km/h]
		sDetStandard.strSM_LowerLimit = L"23.6";
	}
	else 
	{
		// ���ֻ����ϻ�����

		// ���ٱ��������[km/h]
		sDetStandard.strSM_UpperLimit = L"40";
		// ���ٱ��������[km/h]
		sDetStandard.strSM_LowerLimit = L"32.8";
	}
}

void CStandard::GetSpeedometer_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ���ٱ��������[km/h]
	sDetStandard.strSM_UpperLimit = L"40";
	// ���ٱ��������[km/h]
	sDetStandard.strSM_LowerLimit = L"32.8";
}

void CStandard::GetSideslip(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetSideslip_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetSideslip_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetSideslip_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// �����ֻ�����

		// ��ƫ��ֵ����ֵ[m/km]
		sDetStandard.strSte_Sideslip = L"10.0";
	}        
	else 
	{
		// ���ֻ����ϻ�����
		// �໬��ֵ����ֵ[m/km]
		sDetStandard.strSte_Sideslip = L"5.0";
	}
}

void CStandard::GetSideslip_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// �����ֻ�����

		// ��ƫ��ֵ����ֵ[m/km]
		sDetStandard.strSte_Sideslip = L"10.0";
	}
	else 
	{
		// ���ֻ����ϻ�����
		// �໬��ֵ����ֵ[m/km]
		sDetStandard.strSte_Sideslip = L"5.0";
	}
}

void CStandard::GetSideslip_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	sDetStandard.strSte_Sideslip = L"5.0";
}

void CStandard::GetSteerability(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// �����ֻ�����

		// ��ƫ��ֵ����ֵ[m/km]
		sDetStandard.strSte_Sideslip = L"10.0";
	}        
	else 
	{
		// ���ֻ����ϻ�����
		// �໬��ֵ����ֵ[m/km]
		if (bGB7258)
		{
			GetSideslip_7258(sVehInfo, sDetStandard);
			GetMomentum_7258(sVehInfo, sDetStandard);
			GetSteAngle_7258(sVehInfo, sDetStandard);
			GetWheAli_7258(sVehInfo, sDetStandard);
		}
		else
		{
			GetSideslip_18565(sVehInfo, sDetStandard);
			GetMomentum_18565(sVehInfo, sDetStandard);
			GetSteAngle_18565(sVehInfo, sDetStandard);
			GetWheAli_18565(sVehInfo, sDetStandard);
		}
	}
}

void CStandard::GetBrake(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
#ifdef USE_GB7258_2017
		GetBrake_7258_2017(sVehInfo, sDetStandard);
#else
		GetBrake_7258(sVehInfo, sDetStandard);
#endif
	}
	else
	{
		GetBrake_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetBrake_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// �ƶ�̤��������ѹ��
	if (std::wstring::npos != sVehInfo.strSBForceSource.find(L"Һѹ"))
	{
		// Һѹ�ƶ�
		//1�� ���ó�
		//2������������
	}
	else
	{
		// ��ѹ�ƶ�

	}
	// �����ֻ�����
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// Ħ�г�
		if (L"M11"==sVehInfo.strVehTypeCode
			|| L"M10"==sVehInfo.strVehTypeCode
			|| L"M13"==sVehInfo.strVehTypeCode
			|| L"M14"==sVehInfo.strVehTypeCode
			|| L"M15"==sVehInfo.strVehTypeCode
			|| L"M20"==sVehInfo.strVehTypeCode
			|| L"M21"==sVehInfo.strVehTypeCode)
		{
			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// �����ƶ���(��Ͳ)[%]
			sDetStandard.strBK_RearAxleSBRate = L"55.0";
			// �����ƶ���(ƽ��)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"55.0";

			// ǰ�᲻ƽ����[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"";
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode) //��ͨ������Ħ�г����������ؿ�Ħ�г����������ػ�Ħ�г�
			{
				if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"�³�"))
				{
					// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
					sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
					// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
					sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";
				}
				// ���ó���ƽ����
				else
				{
					// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
					sDetStandard.strBK_RearAxleUnbRate1 = L"30.0";
					// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
					sDetStandard.strBK_RearAxleUnbRate2 = L"10.0";
				}
			}
			else
			{
				// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
				sDetStandard.strBK_RearAxleUnbRate1 = L"";
				// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
				sDetStandard.strBK_RearAxleUnbRate2 = L"";
			}

			// פ���ƶ���[%]
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode) //��ͨ������Ħ�г����������ؿ�Ħ�г����������ػ�Ħ�г�
			{
				if (L""==sVehInfo.strMaximumTotalMass
					|| L""==sVehInfo.strUnladenMass) // ������������������ȱʧ
				{
					// פ���ƶ���[%]
					sDetStandard.strBK_PBRate = L"20.0";
				}
				else
				{
					if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // ���������ڵ�����������1.2��
					{
						// פ���ƶ���[%]
						sDetStandard.strBK_PBRate = L"20.0";
					}
					else // ������С����������1.2��
					{
						// פ���ƶ���[%] 
						sDetStandard.strBK_PBRate = L"15.0";
					}
				}
			}
			else
			{
				sDetStandard.strBK_PBRate = L"";
			}
		}
		else if (L"M12"==sVehInfo.strVehTypeCode 
			|| L"M22"==sVehInfo.strVehTypeCode)
		{
			// ���Ħ�г�

			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// �����ƶ���(��Ͳ)[%]
			sDetStandard.strBK_RearAxleSBRate = L"50.0";
			// �����ƶ���(ƽ��)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"50.0";

			// ���������ƶ���[%]
			sDetStandard.strBK_LoadAxleSBRate = L"";
			// ǰ�᲻ƽ����[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"";
			// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate1 = L"";
			// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate2 = L"";

			// פ���ƶ���[%]
			if (L"M12"==sVehInfo.strVehTypeCode) //���������Ħ�г�
			{
				if (L"" == sVehInfo.strMaximumTotalMass
					|| L"" == sVehInfo.strUnladenMass) // ������������������ȱʧ
				{
					// פ���ƶ���[%]
					sDetStandard.strBK_PBRate = L"20.0";
				}
				else
				{
					if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // ���������ڵ�����������1.2��
					{
						// פ���ƶ���[%]
						sDetStandard.strBK_PBRate = L"20.0";
					}
					else // ������С����������1.2��
					{
						// פ���ƶ���[%] 
						sDetStandard.strBK_PBRate = L"15.0";
					}
				}
			}
			else
			{
				sDetStandard.strBK_PBRate = L"";
			}
		}
		else if (L"N11"==sVehInfo.strVehTypeCode)
		{
			// ��������

			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"";
			// �����ƶ���(��Ͳ)[%]
			sDetStandard.strBK_RearAxleSBRate = L"60.0";
			// �����ƶ���(ƽ��)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"60.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_LoadAxleSBRate = L"";

			// ǰ�᲻ƽ����[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"";
			// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
			// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";

			// פ���ƶ���[%]
			if (L"" == sVehInfo.strMaximumTotalMass
				|| L"" == sVehInfo.strUnladenMass) // ������������������ȱʧ
			{
				// פ���ƶ���[%]
				sDetStandard.strBK_PBRate = L"20.0";
			}
			else
			{
				if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // ���������ڵ�����������1.2��
				{
					// פ���ƶ���[%]
					sDetStandard.strBK_PBRate = L"20.0";
				}
				else // ������С����������1.2��
				{
					// פ���ƶ���[%] 
					sDetStandard.strBK_PBRate = L"15.0";
				}
			}
		}
		// û�еĳ������͵�����ͨ����Ħ�г�
		else
		{
			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"61.0";
			// �����ƶ���(��Ͳ)[%]
			sDetStandard.strBK_RearAxleSBRate = L"56.0";
			// �����ƶ���(ƽ��)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"56.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_LoadAxleSBRate = L"";

		}
		// ������[%]
		sDetStandard.strBK_BlockRate = L"100";
	}
	else
	{
		// ���ֻ����ϻ�����
		if (L"1"==sVehInfo.strIsPassengerVeh
			&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9) // ���ó�
		{
			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"60.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"50.0";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// �����ƶ���(��Ͳ)[%]
			sDetStandard.strBK_RearAxleSBRate = L"20.0";
			// �����ƶ���(ƽ��)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"20.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_LoadAxleSBRate = L"";
		}
		else if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500) // ������������3500kg������
		{
			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"60.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"50.0";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// �����ƶ���(��Ͳ)[%]
			sDetStandard.strBK_RearAxleSBRate = L"20.0";
			// �����ƶ���(ƽ��)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"20.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_LoadAxleSBRate = L"50.0";
		}
		else // ���������������г�
		{
			if (std::wstring::npos != sVehInfo.strVehType.find(L"�½ӿͳ�") || std::wstring::npos != sVehInfo.strVehType.find(L"�����г�") ||std::wstring::npos != sVehInfo.strVehType.find(L"�½�ʽ�޹�糵") ) 
			{
				// ���������ƶ���[%]
				sDetStandard.strBK_NoLoadSBRate = L"55.0";
				// ���������ƶ���[%]
				sDetStandard.strBK_FullLoadSBRate = L"45.0";
				// ǰ���ƶ���[%]
				sDetStandard.strBK_FrontAxleSBRate = L"";
				// �����ƶ��ʣ���Ͳ��[%]
				sDetStandard.strBK_RearAxleSBRate = L"";
				// �����ƶ��ʣ�ƽ�壩[%]
				sDetStandard.strBK_RearAxleSBRateP = L"";
				// ���������ƶ���[%]
				sDetStandard.strBK_LoadAxleSBRate = L"45.0";
			}
			else
			{
				// ����������3500�Ŀͳ�
				if (L"1"==sVehInfo.strIsPassengerVeh && _wtoi(sVehInfo.strMaximumTotalMass.c_str()) > 3500)
				{
					// ���������ƶ���[%]
					sDetStandard.strBK_NoLoadSBRate = L"60.0";
					// ���������ƶ���[%]
					sDetStandard.strBK_FullLoadSBRate = L"50.0";
					// ǰ���ƶ���[%]
					sDetStandard.strBK_FrontAxleSBRate = L"60.0";
					// �����ƶ��ʣ���Ͳ��[%]
					sDetStandard.strBK_RearAxleSBRate = L"40.0";
					// �����ƶ��ʣ�ƽ�壩[%]
					sDetStandard.strBK_RearAxleSBRateP = L"30.0";
					// ���������ƶ���[%]
					sDetStandard.strBK_LoadAxleSBRate = L"50.0";
				}
				else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // ���Ͱ�ҳ�
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // ���Ͱ�ҳ�
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // ���Ͱ�ҳ�
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G1") // ����ȫ�ҳ�
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G2") // ����ȫ�ҳ�
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G3") // ����ȫ�ҳ�
					) // �ҳ�
				{
					// ���������ƶ���[%]
					sDetStandard.strBK_NoLoadSBRate = L"55.0";
					// ���������ƶ���[%]
					sDetStandard.strBK_FullLoadSBRate = L"45.0";
					// ǰ���ƶ���[%]
					sDetStandard.strBK_FrontAxleSBRate = L"";
					// �����ƶ��ʣ���Ͳ��[%]
					sDetStandard.strBK_RearAxleSBRate = L"";
					// �����ƶ��ʣ�ƽ�壩[%]
					sDetStandard.strBK_RearAxleSBRateP = L"";
					// ���������ƶ���[%]
					sDetStandard.strBK_LoadAxleSBRate = L"45.0";
				}
				// ����
				else
				{
					// ���������ƶ���[%]
					sDetStandard.strBK_NoLoadSBRate = L"60.0";
					// ���������ƶ���[%]
					sDetStandard.strBK_FullLoadSBRate = L"50.0";
					// ǰ���ƶ���[%]
					sDetStandard.strBK_FrontAxleSBRate = L"60.0";
					// �����ƶ��ʣ���Ͳ��[%]
					sDetStandard.strBK_RearAxleSBRate = L"50.0";
					// �����ƶ��ʣ�ƽ�壩[%]
					sDetStandard.strBK_RearAxleSBRateP = L"35.0";
					// ���������ƶ���[%]
					sDetStandard.strBK_LoadAxleSBRate = L"50.0";
				}
			}
		}

		// �³���ƽ����
		if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"�³�"))
		{
			// ǰ�᲻ƽ����[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"20.0";
			// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
			// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";
		}
		// ���ó���ƽ����
		else
		{
			// ǰ�᲻ƽ����[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"24.0";
			// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate1 = L"30.0";
			// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate2 = L"10.0";
		}

		// ������[%]
		sDetStandard.strBK_BlockRate = L"10.0";

		if (L""==sVehInfo.strMaximumTotalMass
			|| L""==sVehInfo.strUnladenMass) // ������������������ȱʧ
		{
			// פ���ƶ���[%]
			sDetStandard.strBK_PBRate = L"20.0";
		}
		else
		{
			if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= (_wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2)) // ���������ڵ�����������1.2��
			{
				// פ���ƶ���[%]
				sDetStandard.strBK_PBRate = L"20.0";
			}
			else // ������С����������1.2��
			{
				// פ���ƶ���[%] 
				sDetStandard.strBK_PBRate = L"15.0";
			}
		}
	}

	// �ƶ�Э��ʱ��[ms]
	if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"��ѹ"))
	{
		sDetStandard.strBK_BrakeLags = L"600";
	}
	else if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"Һѹ"))
	{
		sDetStandard.strBK_BrakeLags = L"350";
	}
	else
	{
		sDetStandard.strBK_BrakeLags = L"800";
	}
}

void CStandard::GetBrake_7258_2017(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// �ƶ�̤��������ѹ��
	if (std::wstring::npos != sVehInfo.strSBForceSource.find(L"Һѹ"))
	{
		// Һѹ�ƶ�
		//1�� ���ó�
		//2������������
	}
	else
	{
		// ��ѹ�ƶ�

	}
	// �����ֻ�����
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// Ħ�г�
		if (L"M11"==sVehInfo.strVehTypeCode
			|| L"M10"==sVehInfo.strVehTypeCode
			|| L"M13"==sVehInfo.strVehTypeCode
			|| L"M14"==sVehInfo.strVehTypeCode
			|| L"M15"==sVehInfo.strVehTypeCode
			|| L"M20"==sVehInfo.strVehTypeCode
			|| L"M21"==sVehInfo.strVehTypeCode)
		{
			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// �����ƶ���(��Ͳ)[%]
			sDetStandard.strBK_RearAxleSBRate = L"55.0";
			// �����ƶ���(ƽ��)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"55.0";

			// ǰ�᲻ƽ����[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"";
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode) //��ͨ������Ħ�г����������ؿ�Ħ�г����������ػ�Ħ�г�
			{
				if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"�³�"))
				{
					// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
					sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
					// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
					sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";
				}
				// ���ó���ƽ����
				else
				{
					// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
					sDetStandard.strBK_RearAxleUnbRate1 = L"30.0";
					// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
					sDetStandard.strBK_RearAxleUnbRate2 = L"10.0";
				}
			}
			else
			{
				// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
				sDetStandard.strBK_RearAxleUnbRate1 = L"";
				// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
				sDetStandard.strBK_RearAxleUnbRate2 = L"";
			}

			// פ���ƶ���[%]
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode) //��ͨ������Ħ�г����������ؿ�Ħ�г����������ػ�Ħ�г�
			{
				if (L""==sVehInfo.strMaximumTotalMass
					|| L""==sVehInfo.strUnladenMass) // ������������������ȱʧ
				{
					// פ���ƶ���[%]
					sDetStandard.strBK_PBRate = L"20.0";
				}
				else
				{
					if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // ���������ڵ�����������1.2��
					{
						// פ���ƶ���[%]
						sDetStandard.strBK_PBRate = L"20.0";
					}
					else // ������С����������1.2��
					{
						// פ���ƶ���[%] 
						sDetStandard.strBK_PBRate = L"15.0";
					}
				}
			}
			else
			{
				sDetStandard.strBK_PBRate = L"";
			}
		}
		else if (L"M12"==sVehInfo.strVehTypeCode 
			|| L"M22"==sVehInfo.strVehTypeCode)
		{
			// ���Ħ�г�

			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// �����ƶ���(��Ͳ)[%]
			sDetStandard.strBK_RearAxleSBRate = L"50.0";
			// �����ƶ���(ƽ��)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"50.0";

			// ���������ƶ���[%]
			sDetStandard.strBK_LoadAxleSBRate = L"";
			// ǰ�᲻ƽ����[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"";
			// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate1 = L"";
			// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate2 = L"";

			// פ���ƶ���[%]
			if (L"M12"==sVehInfo.strVehTypeCode) //���������Ħ�г�
			{
				if (L"" == sVehInfo.strMaximumTotalMass
					|| L"" == sVehInfo.strUnladenMass) // ������������������ȱʧ
				{
					// פ���ƶ���[%]
					sDetStandard.strBK_PBRate = L"20.0";
				}
				else
				{
					if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // ���������ڵ�����������1.2��
					{
						// פ���ƶ���[%]
						sDetStandard.strBK_PBRate = L"20.0";
					}
					else // ������С����������1.2��
					{
						// פ���ƶ���[%] 
						sDetStandard.strBK_PBRate = L"15.0";
					}
				}
			}
			else
			{
				sDetStandard.strBK_PBRate = L"";
			}
		}
		else if (L"N11"==sVehInfo.strVehTypeCode)
		{
			// ��������

			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"";
			// �����ƶ���(��Ͳ)[%]
			sDetStandard.strBK_RearAxleSBRate = L"60.0";
			// �����ƶ���(ƽ��)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"60.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_LoadAxleSBRate = L"";

			// ǰ�᲻ƽ����[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"";
			// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
			// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";

			// פ���ƶ���[%]
			if (L"" == sVehInfo.strMaximumTotalMass
				|| L"" == sVehInfo.strUnladenMass) // ������������������ȱʧ
			{
				// פ���ƶ���[%]
				sDetStandard.strBK_PBRate = L"20.0";
			}
			else
			{
				if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // ���������ڵ�����������1.2��
				{
					// פ���ƶ���[%]
					sDetStandard.strBK_PBRate = L"20.0";
				}
				else // ������С����������1.2��
				{
					// פ���ƶ���[%] 
					sDetStandard.strBK_PBRate = L"15.0";
				}
			}
		}
		// û�еĳ������͵�����ͨ����Ħ�г�
		else
		{
			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"61.0";
			// �����ƶ���(��Ͳ)[%]
			sDetStandard.strBK_RearAxleSBRate = L"56.0";
			// �����ƶ���(ƽ��)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"56.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_LoadAxleSBRate = L"";

		}
		// ������[%]
		sDetStandard.strBK_BlockRate = L"100";
	}
	else
	{
		// ���ֻ����ϻ�����
		if (L"1"==sVehInfo.strIsPassengerVeh
			&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9) // ���ó�
		{
			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"60.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"50.0";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// �����ƶ���(��Ͳ)[%]
			sDetStandard.strBK_RearAxleSBRate = L"20.0";
			// �����ƶ���(ƽ��)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"20.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_LoadAxleSBRate = L"";
		}
		else if (_wtoi(sVehInfo.strMaximumTotalMass.c_str())<=3500
			&& std::wstring::npos==sVehInfo.strVehType.find(L"ר����ҵ��")
			&& std::wstring::npos==sVehInfo.strVehTypeCode.find(L"B1") // ���Ͱ�ҳ�
			&& std::wstring::npos==sVehInfo.strVehTypeCode.find(L"B2") // ���Ͱ�ҳ� 
			&& std::wstring::npos==sVehInfo.strVehTypeCode.find(L"B3") // ���Ͱ�ҳ� 
			&& std::wstring::npos==sVehInfo.strVehTypeCode.find(L"G1") // ����ȫ�ҳ� 
			&& std::wstring::npos==sVehInfo.strVehTypeCode.find(L"G2") // ����ȫ�ҳ� 
			&& std::wstring::npos==sVehInfo.strVehTypeCode.find(L"G3") // ����ȫ�ҳ� 
			) // ������������3500kg������
		{
			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"60.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"50.0";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// �����ƶ���(��Ͳ)[%]
			sDetStandard.strBK_RearAxleSBRate = L"20.0";
			// �����ƶ���(ƽ��)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"20.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_LoadAxleSBRate = L"50.0";
		}
		else // ���������������г�
		{
			if (std::wstring::npos != sVehInfo.strVehType.find(L"�½ӿͳ�") || std::wstring::npos != sVehInfo.strVehType.find(L"�����г�") ||std::wstring::npos != sVehInfo.strVehType.find(L"�½�ʽ�޹�糵") ) 
			{
				// ���������ƶ���[%]
				sDetStandard.strBK_NoLoadSBRate = L"55.0";
				// ���������ƶ���[%]
				sDetStandard.strBK_FullLoadSBRate = L"45.0";
				// ǰ���ƶ���[%]
				sDetStandard.strBK_FrontAxleSBRate = L"";
				// �����ƶ��ʣ���Ͳ��[%]
				sDetStandard.strBK_RearAxleSBRate = L"";
				// �����ƶ��ʣ�ƽ�壩[%]
				sDetStandard.strBK_RearAxleSBRateP = L"";
				// ���������ƶ���[%]
				sDetStandard.strBK_LoadAxleSBRate = L"45.0";
			}
			else
			{
				// ����������3500�Ŀͳ�
				if (L"1"==sVehInfo.strIsPassengerVeh && _wtoi(sVehInfo.strMaximumTotalMass.c_str()) > 3500)
				{
					// ���������ƶ���[%]
					sDetStandard.strBK_NoLoadSBRate = L"60.0";
					// ���������ƶ���[%]
					sDetStandard.strBK_FullLoadSBRate = L"50.0";
					// ǰ���ƶ���[%]
					sDetStandard.strBK_FrontAxleSBRate = L"60.0";
					// �����ƶ��ʣ���Ͳ��[%]
					sDetStandard.strBK_RearAxleSBRate = L"40.0";
					// �����ƶ��ʣ�ƽ�壩[%]
					sDetStandard.strBK_RearAxleSBRateP = L"30.0";
					// ���������ƶ���[%]
					sDetStandard.strBK_LoadAxleSBRate = L"50.0";
				}
				else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // ���Ͱ�ҳ�
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // ���Ͱ�ҳ�
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // ���Ͱ�ҳ�
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G1") // ����ȫ�ҳ�
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G2") // ����ȫ�ҳ�
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G3") // ����ȫ�ҳ�
					) // �ҳ�
				{
					// ���������ƶ���[%]
					sDetStandard.strBK_NoLoadSBRate = L"55.0";
					// ���������ƶ���[%]
					sDetStandard.strBK_FullLoadSBRate = L"45.0";
					// ǰ���ƶ���[%]
					sDetStandard.strBK_FrontAxleSBRate = L"";
					// �����ƶ��ʣ���Ͳ��[%]
					sDetStandard.strBK_RearAxleSBRate = L"55.0";
					// �����ƶ��ʣ�ƽ�壩[%]
					sDetStandard.strBK_RearAxleSBRateP = L"";
					// ���������ƶ���[%]
					sDetStandard.strBK_LoadAxleSBRate = L"45.0";
				}
				else // ��������
				{
					if (std::wstring::npos!=sVehInfo.strVehType.find(L"ר����ҵ��")
						&& _wtoi(sVehInfo.strMaximumTotalMass.c_str())<=(_wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2))// ר����ҵ��
					{
						// ���������ƶ���[%]
						sDetStandard.strBK_NoLoadSBRate = L"50.0";
					}
					else
					{
						// ���������ƶ���[%]
						sDetStandard.strBK_NoLoadSBRate = L"60.0";
					}
					// ���������ƶ���[%]
					sDetStandard.strBK_FullLoadSBRate = L"50.0";
					// ǰ���ƶ���[%]
					sDetStandard.strBK_FrontAxleSBRate = L"60.0";
					// �����ƶ��ʣ���Ͳ��[%]
					sDetStandard.strBK_RearAxleSBRate = L"50.0";
					// �����ƶ��ʣ�ƽ�壩[%]
					sDetStandard.strBK_RearAxleSBRateP = L"35.0";
					// ���������ƶ���[%]
					sDetStandard.strBK_LoadAxleSBRate = L"50.0";
				}
			}
		}

		// �³���ƽ����
		if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"�³�"))
		{
			// ǰ�᲻ƽ����[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"20.0";
			// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
			// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";
		}
		// ���ó���ƽ����
		else
		{
			// ǰ�᲻ƽ����[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"24.0";
			// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate1 = L"30.0";
			// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate2 = L"10.0";
		}

		// ������[%]
		sDetStandard.strBK_BlockRate = L"10.0";

		if (L""==sVehInfo.strMaximumTotalMass
			|| L""==sVehInfo.strUnladenMass) // ������������������ȱʧ
		{
			// פ���ƶ���[%]
			sDetStandard.strBK_PBRate = L"20.0";
		}
		else
		{
			if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= (_wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2)) // ���������ڵ�����������1.2��
			{
				// פ���ƶ���[%]
				sDetStandard.strBK_PBRate = L"20.0";
			}
			else // ������С����������1.2��
			{
				// פ���ƶ���[%] 
				sDetStandard.strBK_PBRate = L"15.0";
			}
		}
	}

	// �ƶ�Э��ʱ��[ms]
	if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"��ѹ"))
	{
		sDetStandard.strBK_BrakeLags = L"600";
	}
	else if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"Һѹ"))
	{
		sDetStandard.strBK_BrakeLags = L"350";
	}
	else
	{
		sDetStandard.strBK_BrakeLags = L"800";
	}
}

void CStandard::GetBrake_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// GB18565-2001��׼
	// �ƶ�̤��������ѹ��
	if (std::wstring::npos != sVehInfo.strSBForceSource.find(L"Һѹ"))
	{
		// Һѹ�ƶ�
		//1�� ���ó�
		//2������������
	}
	else
	{
		// ��ѹ�ƶ�

	}
	// �����ֻ�����
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// Ħ�г�
		if (L"M11"==sVehInfo.strVehTypeCode
			|| L"M10"==sVehInfo.strVehTypeCode
			|| L"M13"==sVehInfo.strVehTypeCode
			|| L"M14"==sVehInfo.strVehTypeCode
			|| L"M15"==sVehInfo.strVehTypeCode
			|| L"M20"==sVehInfo.strVehTypeCode
			|| L"M21"==sVehInfo.strVehTypeCode)
		{
			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			if (L"M12"==sVehInfo.strVehTypeCode 
				|| L"M22"==sVehInfo.strVehTypeCode)
			{
				// ���Ħ�г�
				// �����ƶ���(��Ͳ)[%]
				sDetStandard.strBK_RearAxleSBRate = L"50.0";
				// �����ƶ���(ƽ��)[%]
				sDetStandard.strBK_RearAxleSBRateP = L"50.0";
			}
			else
			{
				// �����ƶ���(��Ͳ)[%]
				sDetStandard.strBK_RearAxleSBRate = L"55.0";
				// �����ƶ���(ƽ��)[%]
				sDetStandard.strBK_RearAxleSBRateP = L"55.0";
			}
			// ǰ�᲻ƽ����[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"";
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode) //��ͨ������Ħ�г����������ؿ�Ħ�г����������ػ�Ħ�г�
			{
				if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"�³�"))
				{
					// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
					sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
					// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
					sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";
				}
				// ���ó���ƽ����
				else
				{
					// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
					sDetStandard.strBK_RearAxleUnbRate1 = L"30.0";
					// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
					sDetStandard.strBK_RearAxleUnbRate2 = L"10.0";
				}
			}
			else
			{
				// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
				sDetStandard.strBK_RearAxleUnbRate1 = L"";
				// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
				sDetStandard.strBK_RearAxleUnbRate2 = L"";
			}

			// פ���ƶ���[%]
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode) //��ͨ������Ħ�г����������ؿ�Ħ�г����������ػ�Ħ�г�
			{
				if (L""==sVehInfo.strMaximumTotalMass
					|| L""==sVehInfo.strUnladenMass) // ������������������ȱʧ
				{
					// פ���ƶ���[%]
					sDetStandard.strBK_PBRate = L"20.0";
				}
				else
				{
					if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // ���������ڵ�����������1.2��
					{
						// פ���ƶ���[%]
						sDetStandard.strBK_PBRate = L"20.0";
					}
					else // ������С����������1.2��
					{
						// פ���ƶ���[%] 
						sDetStandard.strBK_PBRate = L"15.0";
					}
				}
			}
			else
			{
				sDetStandard.strBK_PBRate = L"";
			}
		}
		else if (L"M12"==sVehInfo.strVehTypeCode 
			|| L"M22"==sVehInfo.strVehTypeCode)
		{
			// ���Ħ�г�

			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// �����ƶ���(��Ͳ)[%]
			sDetStandard.strBK_RearAxleSBRate = L"50.0";
			// �����ƶ���(ƽ��)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"50.0";

			// ǰ�᲻ƽ����[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"";
			// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate1 = L"";
			// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate2 = L"";

			// פ���ƶ���[%]
			if (L"M12"==sVehInfo.strVehTypeCode) //���������Ħ�г�
			{
				if (L"" == sVehInfo.strMaximumTotalMass
					|| L"" == sVehInfo.strUnladenMass) // ������������������ȱʧ
				{
					// פ���ƶ���[%]
					sDetStandard.strBK_PBRate = L"20.0";
				}
				else
				{
					if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // ���������ڵ�����������1.2��
					{
						// פ���ƶ���[%]
						sDetStandard.strBK_PBRate = L"20.0";
					}
					else // ������С����������1.2��
					{
						// פ���ƶ���[%] 
						sDetStandard.strBK_PBRate = L"15.0";
					}
				}
			}
			else
			{
				sDetStandard.strBK_PBRate = L"";
			}
		}
		else if (L"N11"==sVehInfo.strVehTypeCode)
		{
			// ��������

			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"45";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"45";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"";
			// �����ƶ���(��Ͳ)[%]
			sDetStandard.strBK_RearAxleSBRate = L"60.0";
			// �����ƶ���(ƽ��)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"60.0";

			// ǰ�᲻ƽ����[%]
			sDetStandard.strBK_FrontAxleUnbRate = L"";
			// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
			// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
			sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";

			// פ���ƶ���[%]
			if (L"" == sVehInfo.strMaximumTotalMass
				|| L"" == sVehInfo.strUnladenMass) // ������������������ȱʧ
			{
				// פ���ƶ���[%]
				sDetStandard.strBK_PBRate = L"20.0";
			}
			else
			{
				if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // ���������ڵ�����������1.2��
				{
					// פ���ƶ���[%]
					sDetStandard.strBK_PBRate = L"20.0";
				}
				else // ������С����������1.2��
				{
					// פ���ƶ���[%] 
					sDetStandard.strBK_PBRate = L"15.0";
				}
			}
		}
		// û�еĳ������͵�����ͨ����Ħ�г�
		else
		{
			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"61.0";
			// �����ƶ���(��Ͳ)[%]
			sDetStandard.strBK_RearAxleSBRate = L"56.0";
			// �����ƶ���(ƽ��)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"56.0";

		}
		// ������[%]
		sDetStandard.strBK_BlockRate = L"100";
	}
	else
	{
		// ���ֻ����ϻ�����
		// ���������ƶ���[%]
		sDetStandard.strBK_NoLoadSBRate = L"60.0";
		// ���������ƶ���[%]
		sDetStandard.strBK_FullLoadSBRate = L"50.0";
		// ǰ���ƶ���[%]
		sDetStandard.strBK_FrontAxleSBRate = L"60.0";
		// �����ƶ���(��Ͳ)[%]
		sDetStandard.strBK_RearAxleSBRate = L"";
		// �����ƶ���(ƽ��)[%]
		sDetStandard.strBK_RearAxleSBRateP = L"";


		// ǰ�᲻ƽ����[%]
		sDetStandard.strBK_FrontAxleUnbRate = L"20.0";
		// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
		sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
		// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
		sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";

		// ������[%]
		sDetStandard.strBK_BlockRate = L"5.0";

		// פ���ƶ���[%]
		if (L""==sVehInfo.strMaximumTotalMass
			|| L""==sVehInfo.strUnladenMass) // ������������������ȱʧ
		{
			// פ���ƶ���[%]
			sDetStandard.strBK_PBRate = L"20.0";
		}
		else
		{
			if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= (_wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2)) // ���������ڵ�����������1.2��
			{
				// פ���ƶ���[%]
				sDetStandard.strBK_PBRate = L"20.0";
			}
			else // ������С����������1.2��
			{
				// פ���ƶ���[%] 
				sDetStandard.strBK_PBRate = L"15.0";
			}
		}

		// �ƶ�Э��ʱ��[ms](GB18565-2001)
		if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"��ѹ"))
		{
			sDetStandard.strBK_BrakeLags = L"560";
		}
		else if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"Һѹ"))
		{
			sDetStandard.strBK_BrakeLags = L"350";
		}
		else
		{
			sDetStandard.strBK_BrakeLags = L"800";
		}
	}

	// GB7258-2004��׼
	// �ƶ�̤��������ѹ��
	//if (std::wstring::npos != sVehInfo.strSBForceSource.find(L"Һѹ"))
	//{
	//	// Һѹ�ƶ�
	//	//1�� ���ó�
	//	//2������������
	//}
	//else
	//{
	//	// ��ѹ�ƶ�

	//}
	//// �����ֻ�����
	//if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	//{
	//	// Ħ�г�
	//	if (L"M11"==sVehInfo.strVehTypeCode
	//		|| L"M13"==sVehInfo.strVehTypeCode
	//		|| L"M14"==sVehInfo.strVehTypeCode
	//		|| L"M15"==sVehInfo.strVehTypeCode
	//		|| L"M21"==sVehInfo.strVehTypeCode)
	//	{
	//		// ���������ƶ���[%]
	//		sDetStandard.strBK_NoLoadSBRate = L"";
	//		// ���������ƶ���[%]
	//		sDetStandard.strBK_FullLoadSBRate = L"";
	//		// ǰ���ƶ���[%]
	//		sDetStandard.strBK_FrontAxleSBRate = L"60.0";
	//		if (L"M12"==sVehInfo.strVehTypeCode 
	//			|| L"M22"==sVehInfo.strVehTypeCode)
	//		{
	//			// ���Ħ�г�
	//			// �����ƶ���(��Ͳ)[%]
	//			sDetStandard.strBK_RearAxleSBRate = L"50.0";
	//			// �����ƶ���(ƽ��)[%]
	//			sDetStandard.strBK_RearAxleSBRateP = L"50.0";
	//		}
	//		else
	//		{
	//			// �����ƶ���(��Ͳ)[%]
	//			sDetStandard.strBK_RearAxleSBRate = L"55.0";
	//			// �����ƶ���(ƽ��)[%]
	//			sDetStandard.strBK_RearAxleSBRateP = L"55.0";
	//		}
	//		// ǰ�᲻ƽ����[%]
	//		sDetStandard.strBK_FrontAxleUnbRate = L"";
	//		if (L"M11"==sVehInfo.strVehTypeCode
	//			|| L"M13"==sVehInfo.strVehTypeCode
	//			|| L"M14"==sVehInfo.strVehTypeCode) //��ͨ������Ħ�г����������ؿ�Ħ�г����������ػ�Ħ�г�
	//		{
	//			if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"�³�"))
	//			{
	//				// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
	//				sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
	//				// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
	//				sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";
	//			}
	//			// ���ó���ƽ����
	//			else
	//			{
	//				// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
	//				sDetStandard.strBK_RearAxleUnbRate1 = L"30.0";
	//				// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
	//				sDetStandard.strBK_RearAxleUnbRate2 = L"10.0";
	//			}
	//		}
	//		else
	//		{
	//			// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
	//			sDetStandard.strBK_RearAxleUnbRate1 = L"";
	//			// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
	//			sDetStandard.strBK_RearAxleUnbRate2 = L"";
	//		}

	//		// פ���ƶ���[%]
	//		if (L"M11"==sVehInfo.strVehTypeCode
	//			|| L"M13"==sVehInfo.strVehTypeCode
	//			|| L"M14"==sVehInfo.strVehTypeCode) //��ͨ������Ħ�г����������ؿ�Ħ�г����������ػ�Ħ�г�
	//		{
	//			if (L""==sVehInfo.strMaximumTotalMass
	//				|| L""==sVehInfo.strUnladenMass) // ������������������ȱʧ
	//			{
	//				// פ���ƶ���[%]
	//				sDetStandard.strBK_PBRate = L"20.0";
	//			}
	//			else
	//			{
	//				if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // ���������ڵ�����������1.2��
	//				{
	//					// פ���ƶ���[%]
	//					sDetStandard.strBK_PBRate = L"20.0";
	//				}
	//				else // ������С����������1.2��
	//				{
	//					// פ���ƶ���[%] 
	//					sDetStandard.strBK_PBRate = L"15.0";
	//				}
	//			}
	//		}
	//		else
	//		{
	//			sDetStandard.strBK_PBRate = L"";
	//		}
	//	}
	//	else if (L"M12"==sVehInfo.strVehTypeCode 
	//		|| L"M22"==sVehInfo.strVehTypeCode)
	//	{
	//		// ���Ħ�г�

	//		// ���������ƶ���[%]
	//		sDetStandard.strBK_NoLoadSBRate = L"";
	//		// ���������ƶ���[%]
	//		sDetStandard.strBK_FullLoadSBRate = L"";
	//		// ǰ���ƶ���[%]
	//		sDetStandard.strBK_FrontAxleSBRate = L"60.0";
	//		// �����ƶ���(��Ͳ)[%]
	//		sDetStandard.strBK_RearAxleSBRate = L"50.0";
	//		// �����ƶ���(ƽ��)[%]
	//		sDetStandard.strBK_RearAxleSBRateP = L"50.0";

	//		// ǰ�᲻ƽ����[%]
	//		sDetStandard.strBK_FrontAxleUnbRate = L"";
	//		// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
	//		sDetStandard.strBK_RearAxleUnbRate1 = L"";
	//		// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
	//		sDetStandard.strBK_RearAxleUnbRate2 = L"";

	//		// פ���ƶ���[%]
	//		if (L"M12"==sVehInfo.strVehTypeCode) //���������Ħ�г�
	//		{
	//			if (L"" == sVehInfo.strMaximumTotalMass
	//				|| L"" == sVehInfo.strUnladenMass) // ������������������ȱʧ
	//			{
	//				// פ���ƶ���[%]
	//				sDetStandard.strBK_PBRate = L"20.0";
	//			}
	//			else
	//			{
	//				if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // ���������ڵ�����������1.2��
	//				{
	//					// פ���ƶ���[%]
	//					sDetStandard.strBK_PBRate = L"20.0";
	//				}
	//				else // ������С����������1.2��
	//				{
	//					// פ���ƶ���[%] 
	//					sDetStandard.strBK_PBRate = L"15.0";
	//				}
	//			}
	//		}
	//		else
	//		{
	//			sDetStandard.strBK_PBRate = L"";
	//		}
	//	}
	//	else if (L"N11"==sVehInfo.strVehTypeCode)
	//	{
	//		// ��������

	//		// ���������ƶ���[%]
	//		sDetStandard.strBK_NoLoadSBRate = L"45";
	//		// ���������ƶ���[%]
	//		sDetStandard.strBK_FullLoadSBRate = L"45";
	//		// ǰ���ƶ���[%]
	//		sDetStandard.strBK_FrontAxleSBRate = L"";
	//		// �����ƶ���(��Ͳ)[%]
	//		sDetStandard.strBK_RearAxleSBRate = L"60.0";
	//		// �����ƶ���(ƽ��)[%]
	//		sDetStandard.strBK_RearAxleSBRateP = L"60.0";

	//		// ǰ�᲻ƽ����[%]
	//		sDetStandard.strBK_FrontAxleUnbRate = L"";
	//		// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
	//		sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
	//		// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
	//		sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";

	//		// פ���ƶ���[%]
	//		sDetStandard.strBK_PBRate = L"";
	//	}

	//	// ������[%]
	//	sDetStandard.strBK_BlockRate = L"100";
	//}
	//else
	//{
	//	// ���ֻ����ϻ�����
	//	// ���������ƶ���[%]
	//	sDetStandard.strBK_NoLoadSBRate = L"60.0";
	//	// ���������ƶ���[%]
	//	sDetStandard.strBK_FullLoadSBRate = L"50.0";
	//	// ǰ���ƶ���[%]
	//	sDetStandard.strBK_FrontAxleSBRate = L"60.0";

	//	if (L"1"!=sVehInfo.strIsPassengerVeh
	//		&& _wtoi(sVehInfo.strMaximumVelocity.c_str()) <= 70
	//		&& _wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500) // ������������3500kg�ĵ��ٻ���
	//	{
	//		// �����ƶ���(��Ͳ)[%]
	//		sDetStandard.strBK_RearAxleSBRate = L"20";
	//		// �����ƶ���(ƽ��)[%]
	//		sDetStandard.strBK_RearAxleSBRateP = L"20";
	//	}
	//	else 
	//	{
	//		// �����ƶ���(��Ͳ)[%]
	//		sDetStandard.strBK_RearAxleSBRate = L"";
	//		// �����ƶ���(ƽ��)[%]
	//		sDetStandard.strBK_RearAxleSBRateP = L"";
	//	}

	//	// ǰ�᲻ƽ����[%]
	//	sDetStandard.strBK_FrontAxleUnbRate = L"20.0";
	//	// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
	//	sDetStandard.strBK_RearAxleUnbRate1 = L"24.0";
	//	// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
	//	sDetStandard.strBK_RearAxleUnbRate2 = L"8.0";

	//	// ������[%]
	//	sDetStandard.strBK_BlockRate = L"5.0";

	//	// פ���ƶ���[%]
	//	if (L""==sVehInfo.strMaximumTotalMass
	//		|| L""==sVehInfo.strUnladenMass) // ������������������ȱʧ
	//	{
	//		// פ���ƶ���[%]
	//		sDetStandard.strBK_PBRate = L"20.0";
	//	}
	//	else
	//	{
	//		if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= (_wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2)) // ���������ڵ�����������1.2��
	//		{
	//			// פ���ƶ���[%]
	//			sDetStandard.strBK_PBRate = L"20.0";
	//		}
	//		else // ������С����������1.2��
	//		{
	//			// פ���ƶ���[%] 
	//			sDetStandard.strBK_PBRate = L"15.0";
	//		}
	//	}

	//	// �ƶ�Э��ʱ��[ms]
	//	if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"��ѹ"))
	//	{
	//		sDetStandard.strBK_BrakeLags = L"600";
	//	}
	//	else if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"Һѹ"))
	//	{
	//		sDetStandard.strBK_BrakeLags = L"350";
	//	}
	//	else
	//	{
	//		sDetStandard.strBK_BrakeLags = L"800";
	//	}
	//}
}

void CStandard::GetBrake_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// �г��ƶ�����
	enum VehCode
	{
		M1 = 0, // M1����ó�
		M2M3, // M2��M3��ͳ�
		N1, // N1�����
		N2N3, // N2��N3�����
		Tt, // ǣ����
		DbTl, // ȫ�ҳ�
		STl, // ��ҳ�
	};
	enum VehCode vehCode(M1);
	if (CNHCommFunc::IsPasVeh(sVehInfo))
	{
		if (_wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9)
		{
			vehCode = M1;
		}
		else
		{
			vehCode = M2M3;
		}
	}
	else if (CNHCommFunc::IsGooVeh(sVehInfo))
	{
		if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500)
		{
			vehCode = N1;
		}
		else
		{
			vehCode = N2N3;
		}
	}
	else if (CNHCommFunc::IsDrawBarTl(sVehInfo))
	{
		vehCode = DbTl;
	}
	else if (CNHCommFunc::IsSemiTl(sVehInfo))
	{
		vehCode = STl;
	}
	else if (CNHCommFunc::IsTractor(sVehInfo))
	{
		vehCode = Tt;
	}
	else
	{
		// ƥ�䲻�ˣ�ִ�����ϸ��
		vehCode = N2N3;
	}
	// ����������3500�Ŀͳ�
	const bool b3500PasVeh = (CNHCommFunc::IsPasVeh(sVehInfo) && _wtoi(sVehInfo.strMaximumTotalMass.c_str()) > 3500);
	switch (vehCode)
	{
	case M1:
	case N1:
		{
			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"60.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"50.0";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// �����ƶ���(��Ͳ)[%]
			sDetStandard.strBK_RearAxleSBRate = L"20.0";
			// �����ƶ���(ƽ��)[%]
			sDetStandard.strBK_RearAxleSBRateP = L"20.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_LoadAxleSBRate = L"";
		}
		break;
	case M2M3:
	case N2N3:
		{
			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"60.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"50.0";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// �����ƶ��ʣ���Ͳ��[%]
			sDetStandard.strBK_RearAxleSBRate = L"50.0";
			// �����ƶ��ʣ�ƽ�壩[%]
			sDetStandard.strBK_RearAxleSBRateP = L"35.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_LoadAxleSBRate = L"50.0";

			// �������
			// ����������3500�Ŀͳ�
			if (b3500PasVeh)
			{
				// �����ƶ��ʣ���Ͳ��[%]
				sDetStandard.strBK_RearAxleSBRate = L"40.0";
				// �����ƶ��ʣ�ƽ�壩[%]
				sDetStandard.strBK_RearAxleSBRateP = L"30.0";
			}
		}
		break;
		//case N1:
		//	{}
		//	break;
		//case N2N3:
		//	{}
		//	break;
	case Tt:
		{
			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"60.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"50.0";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"60.0";
			// �����ƶ��ʣ���Ͳ��[%]
			sDetStandard.strBK_RearAxleSBRate = L"50.0";
			// �����ƶ��ʣ�ƽ�壩[%]
			sDetStandard.strBK_RearAxleSBRateP = L"50.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_LoadAxleSBRate = L"50.0";
		}
		break;
	case DbTl:
		{
			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"55.0";
			// �����ƶ��ʣ���Ͳ��[%]
			sDetStandard.strBK_RearAxleSBRate = L"55.0";
			// �����ƶ��ʣ�ƽ�壩[%]
			sDetStandard.strBK_RearAxleSBRateP = L"55.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_LoadAxleSBRate = L"50.0";
		}
		break;
	case STl:
		{
			// ���������ƶ���[%]
			sDetStandard.strBK_NoLoadSBRate = L"";
			// ���������ƶ���[%]
			sDetStandard.strBK_FullLoadSBRate = L"";
			// ǰ���ƶ���[%]
			sDetStandard.strBK_FrontAxleSBRate = L"";
			// �����ƶ��ʣ���Ͳ��[%]
			sDetStandard.strBK_RearAxleSBRate = L"55";
			// �����ƶ��ʣ�ƽ�壩[%]
			sDetStandard.strBK_RearAxleSBRateP = L"55.0";
			// ���������ƶ���[%]
			sDetStandard.strBK_LoadAxleSBRate = L"50.0";
		}
		break;
	default:
		{}
		break;
	}
		
	// ��ƽ����
	// ǰ�᲻ƽ����[%]
	sDetStandard.strBK_FrontAxleUnbRate = L"24.0";
	// ���᲻ƽ����1[%](�����ƶ�����С�ڸ������60%ʱ)
	sDetStandard.strBK_RearAxleUnbRate1 = L"30.0";
	// ���᲻ƽ����2[%](�����ƶ���С�ڸ������60%ʱ)
	sDetStandard.strBK_RearAxleUnbRate2 = L"10.0";

	// ������
	sDetStandard.strBK_BlockRate = L"3.5";

	// פ���ƶ���
	if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= (_wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2)) // ���������ڵ�����������1.2��
	{
		// פ���ƶ���[%]
		sDetStandard.strBK_PBRate = L"20.0";
	}
	else // ������С����������1.2��
	{
		// פ���ƶ���[%] 
		sDetStandard.strBK_PBRate = L"15.0";
	}

	// �ƶ�Э��ʱ��
	if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"��ѹ"))
	{
		sDetStandard.strBK_BrakeLags = L"600";
	}
	else if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"Һѹ"))
	{
		sDetStandard.strBK_BrakeLags = L"350";
	}
	else
	{
		sDetStandard.strBK_BrakeLags = L"800";
	}
}

void CStandard::GetHeadLight(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
#ifdef USE_GB7258_2017
		GetHeadLight_7258_2017(sVehInfo, sDetStandard);
#else
		GetHeadLight_7258(sVehInfo, sDetStandard);
#endif
	}
	else
	{
		GetHeadLight_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetHeadLight_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// Զ���ǿ
	// ��ע�ᳵ
	if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"�³�"))
	{
		// �����ֻ�����
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
		{
			// Ħ�г�
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode
				|| L"M15"==sVehInfo.strVehTypeCode
				|| L"M20"==sVehInfo.strVehTypeCode
				|| L"M21"==sVehInfo.strVehTypeCode)
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"10000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"8000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}              
			else if (L"M12"==sVehInfo.strVehTypeCode || L"M22"==sVehInfo.strVehTypeCode)// ���Ħ�г�
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"4000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"3000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}                   
			else if (L"N11"==sVehInfo.strVehTypeCode)// ��������
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"8000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"6000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			// û�еĳ������͵�����ͨ����Ħ�г�����
			else
			{
				// ��������ֵ
				sDetStandard.strHL_Intensity = L"10001";
				// �ĵ�����ֵ
				sDetStandard.strHL_Intensity4L = L"0";
			}
		}              
		else // ���ֻ����ϻ�����
		{
			// �����Ƴ���С��70km/h������
			if (_wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 0: // �޵ƣ����磬��ҳ�
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 1: // 1����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"10000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"8000";
					}
					break;
				case 4: // 4����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"10000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"8000";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}

			else // ��������
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 0: // �޵ƣ����磬��ҳ�
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 1: // 1����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"18000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"15000";
					}
					break;
				case 4: // 4����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"18000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"15000";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
		}
	}     
	else // ���ó�
	{
		// �����ֻ�����
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
		{
			// Ħ�г�
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode
				|| L"M15"==sVehInfo.strVehTypeCode
				|| L"M20"==sVehInfo.strVehTypeCode
				|| L"M21"==sVehInfo.strVehTypeCode)
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"8000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"6000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			else if (L"M12"==sVehInfo.strVehTypeCode || L"M22"==sVehInfo.strVehTypeCode)// ���Ħ�г�
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"3000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"2500";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			else if (L"N11"==sVehInfo.strVehTypeCode)// ��������
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"6000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"5000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			// û�еĳ������͵�����ͨ����Ħ�г�����
			else
			{
				// ��������ֵ
				sDetStandard.strHL_Intensity = L"8001";
				// �ĵ�����ֵ
				sDetStandard.strHL_Intensity4L = L"0";
			}
		}
		else// ���ֻ����ϻ�����
		{
			// �����Ƴ���С��70km/h������
			if (_wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 0: // �޵ƣ����磬��ҳ�
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 1: // 1����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"8000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"6000";
					}
					break;
				case 4: // 4����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"8000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"6000";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			else // ��������
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 0: // �޵ƣ����磬��ҳ�
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 1:  // 1����
					{

						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2:   // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"15000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"12000";
					}
					break;
				case 4: // 4����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"15000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"12000";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
		}
	}

	if (L"1"==sVehInfo.strIsPassengerVeh
		&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9) // ���ó�
	{
		// �������ƫ[H]
		sDetStandard.strHL_LLUpOffset = L"0.90";
		// �������ƫ[H]
		sDetStandard.strHL_LLDownOffset = L"0.70";
		// �ҽ�����ƫ[H]
		sDetStandard.strHL_RLUpOffset = L"0.90";
		// �ҽ�����ƫ[H]
		sDetStandard.strHL_RLDownOffset = L"0.70";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_LHUpOffset = L"0.95";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_LHDownOffset = L"0.85";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_RHUpOffset = L"0.95";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_RHDownOffset = L"0.85";
	}
	else // ����������
	{
		// �������ƫ[H]
		sDetStandard.strHL_LLUpOffset = L"0.80";
		// �������ƫ[H]
		sDetStandard.strHL_LLDownOffset = L"0.60";
		// �ҽ�����ƫ[H]
		sDetStandard.strHL_RLUpOffset = L"0.80";
		// �ҽ�����ƫ[H]
		sDetStandard.strHL_RLDownOffset = L"0.60";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_LHUpOffset = L"0.95";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_LHDownOffset = L"0.80";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_RHUpOffset = L"0.95";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_RHDownOffset = L"0.80";
	}
	// ˮƽƫ��
	// �ǵ���
	if (1 != _wtoi(sVehInfo.strHeadLightSystem.c_str()))
	{
		// �������ƫ[mm]
		sDetStandard.strHL_LLLeftOffset = L"170";
		// �������ƫ[mm]
		sDetStandard.strHL_LLRightOffset = L"350";
		// �ҽ�����ƫ[mm]
		sDetStandard.strHL_RLLeftOffset = L"170";
		// �ҽ�����ƫ[mm]
		sDetStandard.strHL_RLRightOffset = L"350";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_LHLeftOffset = L"170";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_LHRightOffset = L"350";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_RHLeftOffset = L"350";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_RHRightOffset = L"350";
	}

	else // ����
	{
		// �������ƫ[mm]
		sDetStandard.strHL_LLLeftOffset = L"";
		// �������ƫ[mm]
		sDetStandard.strHL_LLRightOffset = L"";
		// �ҽ�����ƫ[mm]
		sDetStandard.strHL_RLLeftOffset = L"";
		// �ҽ�����ƫ[mm]
		sDetStandard.strHL_RLRightOffset = L"";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_LHLeftOffset = L"";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_LHRightOffset = L"";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_RHLeftOffset = L"";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_RHRightOffset = L"";
	}
}

void CStandard::GetHeadLight_7258_2017(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// Զ���ǿ
	// ��ע�ᳵ
	if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"�³�"))
	{
		// �����ֻ�����
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
		{
			// Ħ�г�
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode
				|| L"M15"==sVehInfo.strVehTypeCode
				|| L"M20"==sVehInfo.strVehTypeCode
				|| L"M21"==sVehInfo.strVehTypeCode)
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"10000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"8000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}              
			else if (L"M12"==sVehInfo.strVehTypeCode || L"M22"==sVehInfo.strVehTypeCode)// ���Ħ�г�
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"4000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"3000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}                   
			else if (L"N11"==sVehInfo.strVehTypeCode)// ��������
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"8000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"6000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			// û�еĳ������͵�����ͨ����Ħ�г�����
			else
			{
				// ��������ֵ
				sDetStandard.strHL_Intensity = L"10001";
				// �ĵ�����ֵ
				sDetStandard.strHL_Intensity4L = L"0";
			}
		}
		else if (L"14"==sVehInfo.strPlateTypeCode || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"T"))
		{
			// �������������
			if (_wtof(sVehInfo.strRatedPower.c_str()) > 18.0f)
			{
				// ��������ֵ
				sDetStandard.strHL_Intensity = L"8000";
				// �ĵ�����ֵ
				sDetStandard.strHL_Intensity4L = L"0";
			}
			else
			{
				// ��������ֵ
				sDetStandard.strHL_Intensity = L"6000";
				// �ĵ�����ֵ
				sDetStandard.strHL_Intensity4L = L"0";
			}
		}
		else // ���ֻ����ϻ�����
		{
			// �����Ƴ���С��70km/h������
			if (_wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 0: // �޵ƣ����磬��ҳ�
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 1: // 1����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"10000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"8000";
					}
					break;
				case 4: // 4����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"10000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"8000";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}

			else // ��������
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 0: // �޵ƣ����磬��ҳ�
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 1: // 1����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"18000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"15000";
					}
					break;
				case 4: // 4����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"18000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"15000";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
		}
	}     
	else // ���ó�
	{
		// �����ֻ�����
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
		{
			// Ħ�г�
			if (L"M11"==sVehInfo.strVehTypeCode
				|| L"M10"==sVehInfo.strVehTypeCode
				|| L"M13"==sVehInfo.strVehTypeCode
				|| L"M14"==sVehInfo.strVehTypeCode
				|| L"M15"==sVehInfo.strVehTypeCode
				|| L"M20"==sVehInfo.strVehTypeCode
				|| L"M21"==sVehInfo.strVehTypeCode)
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"8000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"6000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			else if (L"M12"==sVehInfo.strVehTypeCode || L"M22"==sVehInfo.strVehTypeCode)// ���Ħ�г�
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"3000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"2500";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			else if (L"N11"==sVehInfo.strVehTypeCode)// ��������
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 1: // 1����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"6000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"5000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			// û�еĳ������͵�����ͨ����Ħ�г�����
			else
			{
				// ��������ֵ
				sDetStandard.strHL_Intensity = L"8001";
				// �ĵ�����ֵ
				sDetStandard.strHL_Intensity4L = L"0";
			}
		}
		else if (L"14"==sVehInfo.strPlateTypeCode || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"T"))
		{
			// �������������
			if (_wtof(sVehInfo.strRatedPower.c_str()) > 18.0f)
			{
				// ��������ֵ
				sDetStandard.strHL_Intensity = L"6000";
				// �ĵ�����ֵ
				sDetStandard.strHL_Intensity4L = L"0";
			}
			else
			{
				// ��������ֵ
				sDetStandard.strHL_Intensity = L"5000";
				// �ĵ�����ֵ
				sDetStandard.strHL_Intensity4L = L"0";
			}
		}
		else// ���ֻ����ϻ�����
		{
			// �����Ƴ���С��70km/h������
			if (_wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 0: // �޵ƣ����磬��ҳ�
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 1: // 1����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2: // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"8000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"6000";
					}
					break;
				case 4: // 4����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"8000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"6000";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
			else // ��������
			{
				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
				{
				case 0: // �޵ƣ����磬��ҳ�
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 1:  // 1����
					{

						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				case 2:   // 2����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"15000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"12000";
					}
					break;
				case 4: // 4����
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"15000";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"12000";
					}
					break;
				default: // ����ʶ��ĵ���
					{
						// ��������ֵ
						sDetStandard.strHL_Intensity = L"0";
						// �ĵ�����ֵ
						sDetStandard.strHL_Intensity4L = L"0";
					}
					break;
				}
			}
		}
	}

	// ��ֱƫ��
	//// ������ƫ1[mm]
	//sDetStandard.strHL_LUpOffset1 = L"50";
	//// ������ƫ1[mm]
	//sDetStandard.strHL_LDownOffset1 = L"300";
	//// ������ƫ2[mm]
	//sDetStandard.strHL_LUpOffset2 = L"100";
	//// ������ƫ2[mm]
	//sDetStandard.strHL_LDownOffset2 = L"350";
	//// Զ����ƫ1[mm]
	//sDetStandard.strHL_HUpOffset1 = L"-100";
	//// Զ����ƫ1[mm]
	//sDetStandard.strHL_HDownOffset1 = L"200";
	//// Զ����ƫ2[mm]
	//sDetStandard.strHL_HUpOffset2 = L"-100";
	//// Զ����ƫ2[mm]
	//sDetStandard.strHL_HDownOffset2 = L"200";

	// �������ƫ��[mm]
	sDetStandard.strHL_LLUpOffset_mm = L"50";
	// �������ƫ��[mm]
	sDetStandard.strHL_LLDownOffset_mm = L"300";
	// �������ƫ��[mm]
	sDetStandard.strHL_LLUpOffset_mm2 = L"100";
	// �������ƫ��[mm]
	sDetStandard.strHL_LLDownOffset_mm2 = L"350";
	// �ҽ�����ƫ��[mm]
	sDetStandard.strHL_RLUpOffset_mm = L"50";
	// �ҽ�����ƫ��[mm]
	sDetStandard.strHL_RLDownOffset_mm = L"300";
	// �ҽ�����ƫ��[mm]
	sDetStandard.strHL_RLUpOffset_mm2 = L"100";
	// �ҽ�����ƫ��[mm]
	sDetStandard.strHL_RLDownOffset_mm2 = L"350";

	// ��Զ����ƫ[H]
	sDetStandard.strHL_LHUpOffset = L"1.0";
	// ��Զ����ƫ[H]
	sDetStandard.strHL_LHDownOffset = L"0.8";
	// ��Զ����ƫ��[mm]
	sDetStandard.strHL_LHUpOffset_mm = L"-100";
	// ��Զ����ƫ��[mm]
	sDetStandard.strHL_LHDownOffset_mm = L"0";
	// ��Զ����ƫ[H]
	sDetStandard.strHL_RHUpOffset = L"1.0";
	// ��Զ����ƫ[H]
	sDetStandard.strHL_RHDownOffset = L"0.8";
	// ��Զ����ƫ��[mm]
	sDetStandard.strHL_RHUpOffset_mm = L"-100";
	// ��Զ����ƫ��[mm]
	sDetStandard.strHL_RHDownOffset_mm = L"0";

	// ˮƽƫ��
	// �ǵ���
	if (1 != _wtoi(sVehInfo.strHeadLightSystem.c_str()))
	{
		// �������ƫ[mm]
		sDetStandard.strHL_LLLeftOffset = L"170";
		// �������ƫ[mm]
		sDetStandard.strHL_LLRightOffset = L"350";
		// �ҽ�����ƫ[mm]
		sDetStandard.strHL_RLLeftOffset = L"170";
		// �ҽ�����ƫ[mm]
		sDetStandard.strHL_RLRightOffset = L"350";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_LHLeftOffset = L"170";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_LHRightOffset = L"350";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_RHLeftOffset = L"350";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_RHRightOffset = L"350";
	}

	else // ����
	{
		// �������ƫ[mm]
		sDetStandard.strHL_LLLeftOffset = L"";
		// �������ƫ[mm]
		sDetStandard.strHL_LLRightOffset = L"";
		// �ҽ�����ƫ[mm]
		sDetStandard.strHL_RLLeftOffset = L"";
		// �ҽ�����ƫ[mm]
		sDetStandard.strHL_RLRightOffset = L"";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_LHLeftOffset = L"";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_LHRightOffset = L"";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_RHLeftOffset = L"";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_RHRightOffset = L"";
	}
}

void CStandard::GetHeadLight_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// GB18565-2001��׼
	// Զ���ǿ
	switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	{
	case 0: // �޵ƣ����磬��ҳ�
		{
			// ��������ֵ
			sDetStandard.strHL_Intensity = L"0";
			// �ĵ�����ֵ
			sDetStandard.strHL_Intensity4L = L"0";
		}
		break;
	case 1: // 1����
		{
			// ��������ֵ
			sDetStandard.strHL_Intensity = L"0";
			// �ĵ�����ֵ
			sDetStandard.strHL_Intensity4L = L"0";
		}
		break;
	case 2: // 2����
		{
			// ��������ֵ
			sDetStandard.strHL_Intensity = L"12000";
			// �ĵ�����ֵ
			sDetStandard.strHL_Intensity4L = L"10000";
		}
		break;
	case 4: // 4����
		{
			// ��������ֵ
			sDetStandard.strHL_Intensity = L"12000";
			// �ĵ�����ֵ
			sDetStandard.strHL_Intensity4L = L"10000";
		}
		break;
	default: // ����ʶ��ĵ���
		{
			// ��������ֵ
			sDetStandard.strHL_Intensity = L"0";
			// �ĵ�����ֵ
			sDetStandard.strHL_Intensity4L = L"0";
		}
		break;
	}
	// ����λ��
	// �ĵ���
	if (4 == _wtoi(sVehInfo.strHeadLightSystem.c_str()))
	{
		// ��ֱƫ��
		// �������ƫ[H]
		sDetStandard.strHL_LLUpOffset = L"0.80";
		// �������ƫ[H]
		sDetStandard.strHL_LLDownOffset = L"0.60";
		// �ҽ�����ƫ[H]
		sDetStandard.strHL_RLUpOffset = L"0.80";
		// �ҽ�����ƫ[H]
		sDetStandard.strHL_RLDownOffset = L"0.60";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_LHUpOffset = L"0.90";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_LHDownOffset = L"0.85";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_RHUpOffset = L"0.90";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_RHDownOffset = L"0.85";
		// ˮƽƫ��
		// �������ƫ[mm]
		sDetStandard.strHL_LLLeftOffset = L"100";
		// �������ƫ[mm]
		sDetStandard.strHL_LLRightOffset = L"100";
		// �ҽ�����ƫ[mm]
		sDetStandard.strHL_RLLeftOffset = L"100";
		// �ҽ�����ƫ[mm]
		sDetStandard.strHL_RLRightOffset = L"100";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_LHLeftOffset = L"100";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_LHRightOffset = L"170";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_RHLeftOffset = L"170";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_RHRightOffset = L"170";
	}
	else if (2 == _wtoi(sVehInfo.strHeadLightSystem.c_str()))
	{
		// ��ֱƫ��
		// �������ƫ[H]
		sDetStandard.strHL_LLUpOffset = L"0.80";
		// �������ƫ[H]
		sDetStandard.strHL_LLDownOffset = L"0.60";
		// �ҽ�����ƫ[H]
		sDetStandard.strHL_RLUpOffset = L"0.80";
		// �ҽ�����ƫ[H]
		sDetStandard.strHL_RLDownOffset = L"0.60";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_LHUpOffset = L"0.95";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_LHDownOffset = L"0.85";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_RHUpOffset = L"0.95";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_RHDownOffset = L"0.85";
		// ˮƽƫ��
		// �������ƫ[mm]
		sDetStandard.strHL_LLLeftOffset = L"100";
		// �������ƫ[mm]
		sDetStandard.strHL_LLRightOffset = L"100";
		// �ҽ�����ƫ[mm]
		sDetStandard.strHL_RLLeftOffset = L"100";
		// �ҽ�����ƫ[mm]
		sDetStandard.strHL_RLRightOffset = L"100";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_LHLeftOffset = L"170";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_LHRightOffset = L"350";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_RHLeftOffset = L"350";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_RHRightOffset = L"350";
	}
	else if (1 == _wtoi(sVehInfo.strHeadLightSystem.c_str()))// ����
	{
		// �������ƫ[mm]
		sDetStandard.strHL_LLLeftOffset = L"";
		// �������ƫ[mm]
		sDetStandard.strHL_LLRightOffset = L"";
		// �ҽ�����ƫ[mm]
		sDetStandard.strHL_RLLeftOffset = L"";
		// �ҽ�����ƫ[mm]
		sDetStandard.strHL_RLRightOffset = L"";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_LHLeftOffset = L"";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_LHRightOffset = L"";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_RHLeftOffset = L"";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_RHRightOffset = L"";
	}
	else // Ĭ��2��
	{
		// ��ֱƫ��
		// �������ƫ[H]
		sDetStandard.strHL_LLUpOffset = L"0.80";
		// �������ƫ[H]
		sDetStandard.strHL_LLDownOffset = L"0.60";
		// �ҽ�����ƫ[H]
		sDetStandard.strHL_RLUpOffset = L"0.80";
		// �ҽ�����ƫ[H]
		sDetStandard.strHL_RLDownOffset = L"0.60";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_LHUpOffset = L"0.95";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_LHDownOffset = L"0.85";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_RHUpOffset = L"0.95";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_RHDownOffset = L"0.85";
		// ˮƽƫ��
		// �������ƫ[mm]
		sDetStandard.strHL_LLLeftOffset = L"100";
		// �������ƫ[mm]
		sDetStandard.strHL_LLRightOffset = L"100";
		// �ҽ�����ƫ[mm]
		sDetStandard.strHL_RLLeftOffset = L"100";
		// �ҽ�����ƫ[mm]
		sDetStandard.strHL_RLRightOffset = L"100";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_LHLeftOffset = L"170";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_LHRightOffset = L"350";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_RHLeftOffset = L"350";
		// ��Զ����ƫ[mm]
		sDetStandard.strHL_RHRightOffset = L"350";
	}

	//	 //GB7258-2004��׼
	//	// ��ע�ᳵ
	//	if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"�³�"))
	//	{
	//		// �����ֻ�����
	//		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	//		{
	//			// Ħ�г�
	//			if (L"M11"==sVehInfo.strVehTypeCode
	//				|| L"M13"==sVehInfo.strVehTypeCode
	//				|| L"M14"==sVehInfo.strVehTypeCode
	//				|| L"M15"==sVehInfo.strVehTypeCode
	//				|| L"M21"==sVehInfo.strVehTypeCode)
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 1: // 1����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"10000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2: // 2����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"8000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				default: // ����ʶ��ĵ���
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"0";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}              
	//			else if (L"M12"==sVehInfo.strVehTypeCode || L"M22"==sVehInfo.strVehTypeCode)// ���Ħ�г�
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 1: // 1����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"4000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2: // 2����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"3000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				default: // ����ʶ��ĵ���
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"0";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}                   
	//			else if (L"N11"==sVehInfo.strVehTypeCode)// ��������
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 1: // 1����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"8000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2: // 2����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"6000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				default: // ����ʶ��ĵ���
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"0";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}
	//		}              
	//		else // ���ֻ����ϻ�����
	//		{
	//			// �����Ƴ���С��70km/h������
	//			if (_wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 0: // �޵ƣ����磬��ҳ�
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"0";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 1: // 1����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"0";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2: // 2����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"10000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"8000";
	//					}
	//					break;
	//				case 4: // 4����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"10000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"8000";
	//					}
	//					break;
	//				default: // ����ʶ��ĵ���
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"0";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}

	//			else // ��������
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 0: // �޵ƣ����磬��ҳ�
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"0";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 1: // 1����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"0";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2: // 2����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"18000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"15000";
	//					}
	//					break;
	//				case 4: // 4����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"18000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"15000";
	//					}
	//					break;
	//				default: // ����ʶ��ĵ���
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"0";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}
	//		}
	//	}     
	//	else // ���ó�
	//	{
	//		// �����ֻ�����
	//		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	//		{
	//			// Ħ�г�
	//			if (L"M11"==sVehInfo.strVehTypeCode
	//				|| L"M13"==sVehInfo.strVehTypeCode
	//				|| L"M14"==sVehInfo.strVehTypeCode
	//				|| L"M15"==sVehInfo.strVehTypeCode
	//				|| L"M21"==sVehInfo.strVehTypeCode)
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 1: // 1����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"8000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2: // 2����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"6000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				default: // ����ʶ��ĵ���
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"0";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}
	//			else if (L"M12"==sVehInfo.strVehTypeCode || L"M22"==sVehInfo.strVehTypeCode)// ���Ħ�г�
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 1: // 1����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"3000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2: // 2����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"2500";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				default: // ����ʶ��ĵ���
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"0";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}
	//			else if (L"N11"==sVehInfo.strVehTypeCode)// ��������
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 1: // 1����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"6000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2: // 2����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"5000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				default: // ����ʶ��ĵ���
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"0";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}
	//		}
	//		else// ���ֻ����ϻ�����
	//		{
	//			// �����Ƴ���С��70km/h������
	//			if (_wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 0: // �޵ƣ����磬��ҳ�
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"0";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 1: // 1����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"0";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2: // 2����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"8000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"6000";
	//					}
	//					break;
	//				case 4: // 4����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"8000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"6000";
	//					}
	//					break;
	//				default: // ����ʶ��ĵ���
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"0";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}
	//			else // ��������
	//			{
	//				switch (_wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//				{
	//				case 0: // �޵ƣ����磬��ҳ�
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"0";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 1:  // 1����
	//					{

	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"0";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				case 2:   // 2����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"15000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"12000";
	//					}
	//					break;
	//				case 4: // 4����
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"15000";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"12000";
	//					}
	//					break;
	//				default: // ����ʶ��ĵ���
	//					{
	//						// ��������ֵ
	//						sDetStandard.strHL_Intensity = L"0";
	//						// �ĵ�����ֵ
	//						sDetStandard.strHL_Intensity4L = L"0";
	//					}
	//					break;
	//				}
	//			}
	//		}
	//	}
	//		// ��ֱƫ��
	//	if (L"1"==sVehInfo.strIsPassengerVeh
	//		&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9) // ���ó�
	//	{
	//		// �������ƫ[H]
	//		sDetStandard.strHL_LLUpOffset = L"0.90";
	//		// �������ƫ[H]
	//		sDetStandard.strHL_LLDownOffset = L"0.70";
	//		// �ҽ�����ƫ[H]
	//		sDetStandard.strHL_RLUpOffset = L"0.90";
	//		// �ҽ�����ƫ[H]
	//		sDetStandard.strHL_RLDownOffset = L"0.70";
	//		// ��Զ����ƫ[H]
	//		sDetStandard.strHL_LHUpOffset = L"1.00";
	//		// ��Զ����ƫ[H]
	//		sDetStandard.strHL_LHDownOffset = L"0.90";
	//		// ��Զ����ƫ[H]
	//		sDetStandard.strHL_RHUpOffset = L"1.00";
	//		// ��Զ����ƫ[H]
	//		sDetStandard.strHL_RHDownOffset = L"0.90";
	//	}
	//	else // ����������
	//	{
	//		// �������ƫ[H]
	//		sDetStandard.strHL_LLUpOffset = L"0.80";
	//		// �������ƫ[H]
	//		sDetStandard.strHL_LLDownOffset = L"0.60";
	//		// �ҽ�����ƫ[H]
	//		sDetStandard.strHL_RLUpOffset = L"0.80";
	//		// �ҽ�����ƫ[H]
	//		sDetStandard.strHL_RLDownOffset = L"0.60";
	//		// ��Զ����ƫ[H]
	//		sDetStandard.strHL_LHUpOffset = L"0.95";
	//		// ��Զ����ƫ[H]
	//		sDetStandard.strHL_LHDownOffset = L"0.80";
	//		// ��Զ����ƫ[H]
	//		sDetStandard.strHL_RHUpOffset = L"0.95";
	//		// ��Զ����ƫ[H]
	//		sDetStandard.strHL_RHDownOffset = L"0.80";
	//	}
	//	// ˮƽƫ��
	//	// �ǵ���
	//	if (1 != _wtoi(sVehInfo.strHeadLightSystem.c_str()))
	//	{
	//		// �������ƫ[mm]
	//		sDetStandard.strHL_LLLeftOffset = L"170";
	//		// �������ƫ[mm]
	//		sDetStandard.strHL_LLRightOffset = L"350";
	//		// �ҽ�����ƫ[mm]
	//		sDetStandard.strHL_RLLeftOffset = L"170";
	//		// �ҽ�����ƫ[mm]
	//		sDetStandard.strHL_RLRightOffset = L"350";
	//		// ��Զ����ƫ[mm]
	//		sDetStandard.strHL_LHLeftOffset = L"170";
	//		// ��Զ����ƫ[mm]
	//		sDetStandard.strHL_LHRightOffset = L"350";
	//		// ��Զ����ƫ[mm]
	//		sDetStandard.strHL_RHLeftOffset = L"350";
	//		// ��Զ����ƫ[mm]
	//		sDetStandard.strHL_RHRightOffset = L"350";
	//	}

	//	else // ����
	//	{
	//		// �������ƫ[mm]
	//		sDetStandard.strHL_LLLeftOffset = L"";
	//		// �������ƫ[mm]
	//		sDetStandard.strHL_LLRightOffset = L"";
	//		// �ҽ�����ƫ[mm]
	//		sDetStandard.strHL_RLLeftOffset = L"";
	//		// �ҽ�����ƫ[mm]
	//		sDetStandard.strHL_RLRightOffset = L"";
	//		// ��Զ����ƫ[mm]
	//		sDetStandard.strHL_LHLeftOffset = L"";
	//		// ��Զ����ƫ[mm]
	//		sDetStandard.strHL_LHRightOffset = L"";
	//		// ��Զ����ƫ[mm]
	//		sDetStandard.strHL_RHLeftOffset = L"";
	//		// ��Զ����ƫ[mm]
	//		sDetStandard.strHL_RHRightOffset = L"";
	//	}

}

void CStandard::GetHeadLight_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// Զ���ǿ
	// ��������ֵ
	sDetStandard.strHL_Intensity = L"15000";
	// �ĵ�����ֵ
	sDetStandard.strHL_Intensity4L = L"12000";

	// ��ֱƫ��
	if (L"1"==sVehInfo.strIsPassengerVeh
		&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9) // ���ó�
	{
		// �������ƫ[H]
		sDetStandard.strHL_LLUpOffset = L"0.90";
		// �������ƫ[H]
		sDetStandard.strHL_LLDownOffset = L"0.70";
		// �ҽ�����ƫ[H]
		sDetStandard.strHL_RLUpOffset = L"0.90";
		// �ҽ�����ƫ[H]
		sDetStandard.strHL_RLDownOffset = L"0.70";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_LHUpOffset = L"0.95";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_LHDownOffset = L"0.85";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_RHUpOffset = L"0.95";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_RHDownOffset = L"0.85";
	}
	else // ����������
	{
		// �������ƫ[H]
		sDetStandard.strHL_LLUpOffset = L"0.80";
		// �������ƫ[H]
		sDetStandard.strHL_LLDownOffset = L"0.60";
		// �ҽ�����ƫ[H]
		sDetStandard.strHL_RLUpOffset = L"0.80";
		// �ҽ�����ƫ[H]
		sDetStandard.strHL_RLDownOffset = L"0.60";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_LHUpOffset = L"0.95";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_LHDownOffset = L"0.80";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_RHUpOffset = L"0.95";
		// ��Զ����ƫ[H]
		sDetStandard.strHL_RHDownOffset = L"0.80";
	}

	// ˮƽƫ��
	// �������ƫ[mm]
	sDetStandard.strHL_LLLeftOffset = L"170";
	// �������ƫ[mm]
	sDetStandard.strHL_LLRightOffset = L"350";
	// �ҽ�����ƫ[mm]
	sDetStandard.strHL_RLLeftOffset = L"170";
	// �ҽ�����ƫ[mm]
	sDetStandard.strHL_RLRightOffset = L"350";
	// ��Զ����ƫ[mm]
	sDetStandard.strHL_LHLeftOffset = L"170";
	// ��Զ����ƫ[mm]
	sDetStandard.strHL_LHRightOffset = L"350";
	// ��Զ����ƫ[mm]
	sDetStandard.strHL_RHLeftOffset = L"350";
	// ��Զ����ƫ[mm]
	sDetStandard.strHL_RHRightOffset = L"350";
}

void CStandard::GetRoad(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetRoad_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetRoad_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetRoad_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// �г��ƶ�����
	// �����ֻ�����
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// Ħ�г�
		if (L"M11"==sVehInfo.strVehTypeCode
			|| L"M10"==sVehInfo.strVehTypeCode
			|| L"M13"==sVehInfo.strVehTypeCode
			|| L"M14"==sVehInfo.strVehTypeCode
			|| L"M15"==sVehInfo.strVehTypeCode
			|| L"M20"==sVehInfo.strVehTypeCode
			|| L"M21"==sVehInfo.strVehTypeCode)
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"20";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"7.0";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"";
		}
		else if (L"M12"==sVehInfo.strVehTypeCode || L"M22"==sVehInfo.strVehTypeCode)// ���Ħ�г�
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"20";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"4.0";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"";
		}
		else if (L"N11"==sVehInfo.strVehTypeCode) // ��������
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"20";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"5.0";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"3.8";
		}
		// û�еĳ������͵�����ͨ����Ħ�г�����
		else
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"21";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"2.6";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"7.1";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"";
		}
	}         
	else // ���ֻ����ϻ�����
	{
		if (L"1"==sVehInfo.strIsPassengerVeh
			&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9) // ���ó�
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"50";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"19.0";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"6.2";
		}
		else if (L"1"!=sVehInfo.strIsPassengerVeh
			&& _wtoi(sVehInfo.strMaximumVelocity.c_str()) <= 70
			&& _wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500) // ������������3500kg�ĵ��ٻ���
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"30";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"8.0";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"5.6";
		}
		else if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500) // ����������������3500kg������
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"50";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"21.0";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"5.8";
		}
		else // ���������������г�
		{
			if (std::wstring::npos != sVehInfo.strVehType.find(L"�½ӿͳ�") || std::wstring::npos != sVehInfo.strVehType.find(L"�����г�") ||std::wstring::npos != sVehInfo.strVehType.find(L"�½�ʽ�޹�糵") ) 
			{
				// ·��_���ٶ�[km/h]
				sDetStandard.strRD_InitialVelocity = L"30";
				// ·��_ͨ�����[m]
				sDetStandard.strRD_ChannelWidth = L"3.0";
				// ·��_�ƶ�����[m]
				sDetStandard.strRD_BrakeDistance = L"9.5";
				// ·��_MFDD[m/s2]
				sDetStandard.strRD_MFDD = L"5.0";
			}
			else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // ���Ͱ�ҳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // ���Ͱ�ҳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // ���Ͱ�ҳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G1") // ����ȫ�ҳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G2") // ����ȫ�ҳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G3") // ����ȫ�ҳ�
				) // �ҳ�
			{
				// ·��_���ٶ�[km/h]
				sDetStandard.strRD_InitialVelocity = L"30";
				// ·��_ͨ�����[m]
				sDetStandard.strRD_ChannelWidth = L"3.0";
				// ·��_�ƶ�����[m]
				sDetStandard.strRD_BrakeDistance = L"9.5";
				// ·��_MFDD[m/s2]
				sDetStandard.strRD_MFDD = L"5.0";
			}
			else // ��������
			{
				// ·��_���ٶ�[km/h]
				sDetStandard.strRD_InitialVelocity = L"30";
				// ·��_ͨ�����[m]
				sDetStandard.strRD_ChannelWidth = L"3.0";
				// ·��_�ƶ�����[m]
				sDetStandard.strRD_BrakeDistance = L"9.0";
				// ·��_MFDD[m/s2]
				sDetStandard.strRD_MFDD = L"5.4";
			}
		}
	}

	if (L"1"==sVehInfo.strIsPassengerVeh
		&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9) // ���ó�
	{
		// ·��_Ӧ�����ٶ�[km/h]
		sDetStandard.strRD_EmerInitVel = L"50";
		// ·��_Ӧ���ƶ�����[m]
		sDetStandard.strRD_EmerDistance = L"38.0";
		// ·��_Ӧ��MFDD[m/s2]
		sDetStandard.strRD_EmerMFDD = L"2.9";
		// ·��_Ӧ���ֲ�����[N]
		sDetStandard.strRD_EmerHandOpeForce = L"400";
		// ·��_Ӧ���Ų�����[N]
		sDetStandard.strRD_EmerFootOpeForce = L"500";
	}
	else if (L"1"==sVehInfo.strIsPassengerVeh)// �ͳ�
	{
		// ·��_Ӧ�����ٶ�[km/h]
		sDetStandard.strRD_EmerInitVel = L"30";
		// ·��_Ӧ���ƶ�����[m]
		sDetStandard.strRD_EmerDistance = L"18.0";
		// ·��_Ӧ��MFDD[m/s2]
		sDetStandard.strRD_EmerMFDD = L"2.5";
		// ·��_Ӧ���ֲ�����[N]
		sDetStandard.strRD_EmerHandOpeForce = L"600";
		// ·��_Ӧ���Ų�����[N]
		sDetStandard.strRD_EmerFootOpeForce = L"700";
	}
	else
	{
		// ·��_Ӧ�����ٶ�[km/h]
		sDetStandard.strRD_EmerInitVel = L"30";
		// ·��_Ӧ���ƶ�����[m]
		sDetStandard.strRD_EmerDistance = L"20.0";
		// ·��_Ӧ��MFDD[m/s2]
		sDetStandard.strRD_EmerMFDD = L"2.2";
		// ·��_Ӧ���ֲ�����[N]
		sDetStandard.strRD_EmerHandOpeForce = L"600";
		// ·��_Ӧ���Ų�����[N]
		sDetStandard.strRD_EmerFootOpeForce = L"700";
	}

#ifdef USE_GB7258_2017
	// �������2.55�׵� ͨ�����Ϊ����+0.5��
	if(_wtoi(sVehInfo.strVehWidth.c_str())>=2550)
	{
		const int nChannelWidth = _wtoi(sVehInfo.strVehWidth.c_str())+500;
		CString strChannelWidth(L"");
		strChannelWidth.Format(L"%.2f",nChannelWidth/1000.0f);
		sDetStandard.strRD_ChannelWidth = strChannelWidth.GetString();
	}
#endif

	// �ƶ�Э��ʱ��[ms]
	if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"��ѹ"))
	{
		sDetStandard.strRD_BrakeLags = L"600";
	}
	else if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"Һѹ"))
	{
		sDetStandard.strRD_BrakeLags = L"350";
	}
	else
	{
		sDetStandard.strRD_BrakeLags = L"800";
	}

	// פ���ƶ�����
	if (L""==sVehInfo.strMaximumTotalMass
		|| L""==sVehInfo.strUnladenMass) // ������������������ȱʧ
	{
		// ·��_פ���µ��¶�[%]
		sDetStandard.strRD_Slope = L"20.0";
	}
	else
	{
		if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // ���������ڵ�����������1.2��
		{
			// ·��_פ���µ��¶�[%]
			sDetStandard.strRD_Slope = L"20.0";
		}
		else // ������С����������1.2��
		{
			// ·��_פ���µ��¶�[%]
			sDetStandard.strRD_Slope = L"15.0";
		}
	}

#ifdef USE_GB7258_2017
	// ·��_פ���̶�ʱ��[min]
	sDetStandard.strRD_PBTime = L"2.0";
#else
	// ·��_פ���̶�ʱ��[min]
	sDetStandard.strRD_PBTime = L"5.0";
#endif
}

void CStandard::GetRoad_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// �г��ƶ�����
	// �����ֻ�����
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// Ħ�г�
		if (L"M11"==sVehInfo.strVehTypeCode
			|| L"M10"==sVehInfo.strVehTypeCode
			|| L"M13"==sVehInfo.strVehTypeCode
			|| L"M14"==sVehInfo.strVehTypeCode
			|| L"M15"==sVehInfo.strVehTypeCode
			|| L"M20"==sVehInfo.strVehTypeCode
			|| L"M21"==sVehInfo.strVehTypeCode)
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"20";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"7.0";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"";
		}
		else if (L"M12"==sVehInfo.strVehTypeCode || L"M22"==sVehInfo.strVehTypeCode)// ���Ħ�г�
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"20";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"4.0";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"";
		}
		else if (L"N11"==sVehInfo.strVehTypeCode) // ��������
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"20";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"5.0";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"3.8";
		}
		// û�еĳ������͵�����ͨ����Ħ�г�����
		else
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"21";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"2.6";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"7.1";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"";
		}
	}         
	else // ���ֻ����ϻ�����
	{
		if (L"1"==sVehInfo.strIsPassengerVeh
			&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9) // ���ó�
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"50";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"19.0";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"6.2";
		}
		else if (L"1"!=sVehInfo.strIsPassengerVeh
			&& _wtoi(sVehInfo.strMaximumVelocity.c_str()) <= 70
			&& _wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500) // ������������3500kg�ĵ��ٻ���
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"30";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"8.0";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"5.6";
		}
		else if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500) // ����������������3500kg������
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"50";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"21.0";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"5.8";
		}
		else if (sVehInfo.strVehType.find(L"��ҳ�") != std::wstring::npos
			|| sVehInfo.strVehType.find(L"ȫ�ҳ�") != std::wstring::npos) // �����г����ҳ�
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"30";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"3.0";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"9.5";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"5.0";
		}
		else // ��������
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"30";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"3.0";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"9.0";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"5.4";
		}
	}

	// �ƶ�Э��ʱ��[ms]
	if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"��ѹ"))
	{
		sDetStandard.strRD_BrakeLags = L"560";
	}
	else if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"Һѹ"))
	{
		sDetStandard.strRD_BrakeLags = L"350";
	}
	else
	{
		sDetStandard.strRD_BrakeLags = L"800";
	}

	// פ���ƶ�����
	if (L""==sVehInfo.strMaximumTotalMass
		|| L""==sVehInfo.strUnladenMass) // ������������������ȱʧ
	{
		// ·��_פ���µ��¶�[%]
		sDetStandard.strRD_Slope = L"20.0";
	}
	else
	{
		if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // ���������ڵ�����������1.2��
		{
			// ·��_פ���µ��¶�[%]
			sDetStandard.strRD_Slope = L"20.0";
		}
		else // ������С����������1.2��
		{
			// ·��_פ���µ��¶�[%]
			sDetStandard.strRD_Slope = L"15.0";
		}
	}
	// ·��_פ���̶�ʱ��[min]
	sDetStandard.strRD_PBTime = L"5.0";
}

void CStandard::GetRoad_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// �г��ƶ�����
	// 1��M1����ó�
	// 2��N1�����
	// 3��M2��M3��ͳ���N2��N3�����(�����ǣ����)
	// 4�������г�
	enum VehCode
	{
		M1 = 0, // M1����ó�
		N1, // N1�����
		M2M3N2N3Tt, // M2��M3��ͳ���N2��N3�����(�����ǣ����)
		Tn, // �����г�
	};
	enum VehCode vehCode(M1);
	if (CNHCommFunc::IsPasVeh(sVehInfo))
	{
		if (_wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9)
		{
			vehCode = M1;
		}
		else
		{
			vehCode = M2M3N2N3Tt;
		}
	}
	else if (CNHCommFunc::IsGooVeh(sVehInfo) || CNHCommFunc::IsTractor(sVehInfo))
	{
		if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500)
		{
			vehCode = N1;
		}
		else
		{
			vehCode = M2M3N2N3Tt;
		}
	}
	else if (CNHCommFunc::IsTrailer(sVehInfo))
	{
		// �ҳ����г�
		vehCode = Tn;
	}
	else
	{
		// ƥ�䲻�ˣ�ִ�����ϸ��
		vehCode = M2M3N2N3Tt;
	}
	switch (vehCode)
	{
	case M1:
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"50";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"19.0";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"6.2";
		}
		break;
	case N1:
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"50";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"2.5";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"21.0";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"5.8";
		}
		break;
	case M2M3N2N3Tt:
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"30";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"3.0";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"9.0";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"5.4";
		}
		break;
	case Tn:
		{
			// ·��_���ٶ�[km/h]
			sDetStandard.strRD_InitialVelocity = L"30";
			// ·��_ͨ�����[m]
			sDetStandard.strRD_ChannelWidth = L"3.0";
			// ·��_�ƶ�����[m]
			sDetStandard.strRD_BrakeDistance = L"9.5";
			// ·��_MFDD[m/s2]
			sDetStandard.strRD_MFDD = L"5.0";
		}
		break;
	default:
		{}
		break;
	}

	// �ƶ�Э��ʱ��[ms]��18565-2016��Ҫ��
	//if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"��ѹ"))
	//{
	//	sDetStandard.strRD_BrakeLags = L"600";
	//}
	//else if (std::wstring::npos!= sVehInfo.strSBForceSource.find(L"Һѹ"))
	//{
	//	sDetStandard.strRD_BrakeLags = L"350";
	//}
	//else
	//{
	//	sDetStandard.strRD_BrakeLags = L"800";
	//}

	// �ƶ�Э��ʱ��[ms]
	sDetStandard.strRD_BrakeLags = L"800";

	// פ���ƶ�����
	if (L""==sVehInfo.strMaximumTotalMass
		|| L""==sVehInfo.strUnladenMass) // ������������������ȱʧ
	{
		// ·��_פ���µ��¶�[%]
		sDetStandard.strRD_Slope = L"20.0";
	}
	else
	{
		if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) >= _wtoi(sVehInfo.strUnladenMass.c_str()) * 1.2) // ���������ڵ�����������1.2��
		{
			// ·��_פ���µ��¶�[%]
			sDetStandard.strRD_Slope = L"20.0";
		}
		else // ������С����������1.2��
		{
			// ·��_פ���µ��¶�[%]
			sDetStandard.strRD_Slope = L"15.0";
		}
	}
	// ·��_פ���̶�ʱ��[min]
	sDetStandard.strRD_PBTime = L"5.0";
}

void CStandard::GetDIS(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetDIS_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetDIS_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetDIS_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ��������
	struct tm tmTmp;  
	time_t timeProductionDate;  

	int nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d-%d-%d %d:%d:%d" ,       
		&(tmTmp.tm_year),   
		&(tmTmp.tm_mon),   
		&(tmTmp.tm_mday),  
		&(tmTmp.tm_hour),  
		&(tmTmp.tm_min),  
		&(tmTmp.tm_sec));

	if (nScanf < 6)
	{
		nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d/%d/%d %d:%d:%d" ,       
			&(tmTmp.tm_year),   
			&(tmTmp.tm_mon),   
			&(tmTmp.tm_mday),  
			&(tmTmp.tm_hour),  
			&(tmTmp.tm_min),  
			&(tmTmp.tm_sec));

		if (nScanf < 6)
		{
			nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d-%d-%d" ,       
				&(tmTmp.tm_year),   
				&(tmTmp.tm_mon),   
				&(tmTmp.tm_mday));

			if (nScanf < 3)
			{
				nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d/%d/%d" ,       
					&(tmTmp.tm_year),   
					&(tmTmp.tm_mon),   
					&(tmTmp.tm_mday));

				if (nScanf < 3)
				{

					time(&timeProductionDate);
					localtime_s(&tmTmp, &timeProductionDate);
				}
				else
				{
					tmTmp.tm_hour = 0;
					tmTmp.tm_min = 0;
					tmTmp.tm_sec = 0;
					tmTmp.tm_year -= 1900;  
					tmTmp.tm_mon --;  
					tmTmp.tm_wday = 0;  
					tmTmp.tm_yday = 0;  
					tmTmp.tm_isdst = -1;  
					timeProductionDate = mktime(&tmTmp);
				}
			}
			else
			{
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeProductionDate = mktime(&tmTmp);
			}
		}
		else
		{
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeProductionDate = mktime(&tmTmp);
		}
	}
	else
	{
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeProductionDate = mktime(&tmTmp);
	}

	// �����ֻ�����
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// Ħ�г�
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M"))
		{
			time_t timeSpan1;
			tmTmp.tm_year = 2003;
			tmTmp.tm_mon = 7;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1; 
			timeSpan1 = mktime(&tmTmp);

			// 2003 ��7 ��1 ��ǰ����
			if (timeProductionDate < timeSpan1)
			{
				// �����Ϊnull�������
				if (L"" == sVehInfo.strEngineStroke)
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"8000";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
				// �����
				else if (L"2" == sVehInfo.strEngineStroke)
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"8000";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
				// �ĳ��
				else if (L"4" == sVehInfo.strEngineStroke)
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"2200";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
				// ������̵������
				else
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"8001";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.6";
				}
			}
			else // 2003 ��7 ��1 ��������
			{
				time_t timeSpan1, timeSpan2;  

				tmTmp.tm_year = 2010;
				tmTmp.tm_mon = 7;
				tmTmp.tm_mday = 1;
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeSpan1 = mktime(&tmTmp);

				tmTmp.tm_year = 2011;
				tmTmp.tm_mon = 7;
				tmTmp.tm_mday = 1;
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeSpan2 = mktime(&tmTmp);

				// 2010 ��7 ��1 ��������������Ħ�г����������Ħ�г�
				if (timeProductionDate >= timeSpan1 
					&& (L"M20"==sVehInfo.strVehTypeCode 
					|| L"M21"==sVehInfo.strVehTypeCode 
					|| L"M22"==sVehInfo.strVehTypeCode))
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"400";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"3.0";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"400";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"3.0";
				}
				// 2011 ��7 ��1 ��������������Ħ�г����������Ħ�г�
				else if (timeProductionDate >= timeSpan2 && std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M1"))
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"400";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"3.0";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"400";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"3.0";
				}
				// 2003 ��7 ��1 ����������Ħ�г������Ħ�г�(�����)
				else if (L"2"==sVehInfo.strEngineStroke)
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"4500";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.5";
				}
				// 2003 ��7 ��1 ����������Ħ�г������Ħ�г�(�ĳ��)
				else if (L"4"==sVehInfo.strEngineStroke)
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"1200";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.5";
				}
				// �ж���ϢΪnull���жϴ���������
				else
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"401";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"3.1";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"4501";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.1";
				}

			}

		}
		// ��Ħ�г�
		else
		{
			// �ߵ���HCֵ[10-6]
			sDetStandard.strEmi_HISHC = L"401";
			// �ߵ���COֵ[%]����ȷ��0.1
			sDetStandard.strEmi_HISCO = L"3.1";
			// �͵���HCֵ[10-6] 
			sDetStandard.strEmi_LISHC = L"4501";
			// �͵���COֵ[%]����ȷ��0.1
			sDetStandard.strEmi_LISCO = L"4.1";
		}

	}
	// ���ֻ����ϻ�����
	else
	{
		if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500) // ����
		{
			if (L"1"==sVehInfo.strIsPassengerVeh
				&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 6
				&& _wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 2500) // һ������
			{
				time_t timeSpan1, timeSpan2;  

				tmTmp.tm_year = 2000;
				tmTmp.tm_mon = 7;
				tmTmp.tm_mday = 1;
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeSpan1 = mktime(&tmTmp);

				tmTmp.tm_year = 1995;
				tmTmp.tm_mon = 7;
				tmTmp.tm_mday = 1;
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeSpan2 = mktime(&tmTmp);

				if (timeProductionDate >= timeSpan1) // 2000��7��1����
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"100";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"0.30";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"150";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"0.80";
				}
				else if (timeProductionDate >= timeSpan2) // 1995��7��1����
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"900";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"3.00";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"900";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
				else // 1995��7��1��ǰ
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"900";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"3.00";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"1200";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
			}
			else // ��������
			{
				time_t timeSpan1, timeSpan2;  

				tmTmp.tm_year = 2001;
				tmTmp.tm_mon = 10;
				tmTmp.tm_mday = 1;
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeSpan1 = mktime(&tmTmp);

				tmTmp.tm_year = 1995;
				tmTmp.tm_mon = 7;
				tmTmp.tm_mday = 1;
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeSpan2 = mktime(&tmTmp);

				if (timeProductionDate >= timeSpan1) // 2001��10��1����
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"150";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"0.50";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"200";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"1.00";
				}
				else if (timeProductionDate >= timeSpan2) // 1995��7��1����
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"900";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"3.00";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"900";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
				else // 1995��7��1��ǰ
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"900";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"3.00";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"1200";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
			}
		}
		else // ����
		{
			time_t timeSpan1, timeSpan2;  

			tmTmp.tm_year = 2004;
			tmTmp.tm_mon = 9;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeSpan1 = mktime(&tmTmp);

			tmTmp.tm_year = 1995;
			tmTmp.tm_mon = 7;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeSpan2 = mktime(&tmTmp);

			if (timeProductionDate >= timeSpan1) // 2004��9��1����
			{
				// �ߵ���HCֵ[10-6]
				sDetStandard.strEmi_HISHC = L"200";
				// �ߵ���COֵ[%]����ȷ��0.1
				sDetStandard.strEmi_HISCO = L"0.7";
				// �͵���HCֵ[10-6] 
				sDetStandard.strEmi_LISHC = L"250";
				// �͵���COֵ[%]����ȷ��0.1
				sDetStandard.strEmi_LISCO = L"1.5";
			}
			else if (timeProductionDate >= timeSpan2) // 1995��7��1����
			{
				// �ߵ���HCֵ[10-6]
				sDetStandard.strEmi_HISHC = L"900";
				// �ߵ���COֵ[%]����ȷ��0.1
				sDetStandard.strEmi_HISCO = L"3.0";
				// �͵���HCֵ[10-6] 
				sDetStandard.strEmi_LISHC = L"1200";
				// �͵���COֵ[%]����ȷ��0.1
				sDetStandard.strEmi_LISCO = L"4.5";
			}
			else // 1995��7��1��ǰ
			{
				// �ߵ���HCֵ[10-6]
				sDetStandard.strEmi_HISHC = L"1200";
				// �ߵ���COֵ[%]����ȷ��0.1
				sDetStandard.strEmi_HISCO = L"3.5";
				// �͵���HCֵ[10-6] 
				sDetStandard.strEmi_LISHC = L"2000";
				// �͵���COֵ[%]����ȷ��0.1
				sDetStandard.strEmi_LISCO = L"5.0";
			}
		}

		// �ߵ��٦�ֵ���ޣ���ȷ��0.01
		sDetStandard.strEmi_HISLambda_LowerLimit = L"0.97";
		// �ߵ��٦�ֵ���ޣ���ȷ��0.01
		sDetStandard.strEmi_HISLambda_UpperLimit = L"1.03";
	}
}

void CStandard::GetDIS_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// �������ڡ���������
	struct tm tmTmp;  
	time_t timeFirstRegisterDate, timeProductionDate;  
	int nScanf;
	nScanf = swscanf_s(sVehInfo.strFirstRegisterDate.c_str(), L"%d-%d-%d %d:%d:%d" ,       
		&(tmTmp.tm_year),   
		&(tmTmp.tm_mon),   
		&(tmTmp.tm_mday),  
		&(tmTmp.tm_hour),  
		&(tmTmp.tm_min),  
		&(tmTmp.tm_sec));

	if (nScanf < 6)
	{
		nScanf = swscanf_s(sVehInfo.strFirstRegisterDate.c_str(), L"%d/%d/%d %d:%d:%d" ,       
			&(tmTmp.tm_year),   
			&(tmTmp.tm_mon),   
			&(tmTmp.tm_mday),  
			&(tmTmp.tm_hour),  
			&(tmTmp.tm_min),  
			&(tmTmp.tm_sec));

		if (nScanf < 6)
		{
			nScanf = swscanf_s(sVehInfo.strFirstRegisterDate.c_str(), L"%d-%d-%d" ,       
				&(tmTmp.tm_year),   
				&(tmTmp.tm_mon),   
				&(tmTmp.tm_mday));

			if (nScanf < 3)
			{
				nScanf = swscanf_s(sVehInfo.strFirstRegisterDate.c_str(), L"%d/%d/%d" ,       
					&(tmTmp.tm_year),   
					&(tmTmp.tm_mon),   
					&(tmTmp.tm_mday));

				if (nScanf < 3)
				{

					time(&timeFirstRegisterDate);
					localtime_s(&tmTmp, &timeFirstRegisterDate);
				}
				else
				{
					tmTmp.tm_hour = 0;
					tmTmp.tm_min = 0;
					tmTmp.tm_sec = 0;
					tmTmp.tm_year -= 1900;  
					tmTmp.tm_mon --;  
					tmTmp.tm_wday = 0;  
					tmTmp.tm_yday = 0;  
					tmTmp.tm_isdst = -1;  
					timeFirstRegisterDate = mktime(&tmTmp);
				}
			}
			else
			{
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeFirstRegisterDate = mktime(&tmTmp);
			}
		}
		else
		{
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeFirstRegisterDate = mktime(&tmTmp);
		}
	}
	else
	{
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeFirstRegisterDate = mktime(&tmTmp);
	}

	nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d-%d-%d %d:%d:%d" ,       
		&(tmTmp.tm_year),   
		&(tmTmp.tm_mon),   
		&(tmTmp.tm_mday),  
		&(tmTmp.tm_hour),  
		&(tmTmp.tm_min),  
		&(tmTmp.tm_sec));
	if (nScanf < 6)
	{
		nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d/%d/%d %d:%d:%d" ,       
			&(tmTmp.tm_year),   
			&(tmTmp.tm_mon),   
			&(tmTmp.tm_mday),  
			&(tmTmp.tm_hour),  
			&(tmTmp.tm_min),  
			&(tmTmp.tm_sec));

		if (nScanf < 6)
		{
			nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d-%d-%d" ,       
				&(tmTmp.tm_year),   
				&(tmTmp.tm_mon),   
				&(tmTmp.tm_mday));

			if (nScanf < 3)
			{
				nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d/%d/%d" ,       
					&(tmTmp.tm_year),   
					&(tmTmp.tm_mon),   
					&(tmTmp.tm_mday));

				if (nScanf < 3)
				{

					time(&timeProductionDate);
					localtime_s(&tmTmp, &timeProductionDate);
				}
				else
				{
					tmTmp.tm_hour = 0;
					tmTmp.tm_min = 0;
					tmTmp.tm_sec = 0;
					tmTmp.tm_year -= 1900;  
					tmTmp.tm_mon --;  
					tmTmp.tm_wday = 0;  
					tmTmp.tm_yday = 0;  
					tmTmp.tm_isdst = -1;  
					timeProductionDate = mktime(&tmTmp);
				}
			}
			else
			{
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeProductionDate = mktime(&tmTmp);
			}
		}
		else
		{
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeProductionDate = mktime(&tmTmp);
		}
	}
	else
	{
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeProductionDate = mktime(&tmTmp);
	}



	// �����ֻ�����
	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// Ħ�г�
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M"))
		{
			time_t timeSpan1;
			tmTmp.tm_year = 2003;
			tmTmp.tm_mon = 7;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1; 
			timeSpan1 = mktime(&tmTmp);

			// 2003 ��7 ��1 ��ǰ����
			if (timeProductionDate < timeSpan1)
			{
				// �����Ϊnull�������
				if (L"" == sVehInfo.strEngineStroke)
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"8000";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
				// �����
				else if (L"2" == sVehInfo.strEngineStroke)
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"8000";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
				// �ĳ��
				else if (L"4" == sVehInfo.strEngineStroke)
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"2200";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
				// ������̵������
				else
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"8001";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.51";
				}
			}
			else // 2003 ��7 ��1 ��������
			{
				time_t timeSpan1, timeSpan2;  

				tmTmp.tm_year = 2010;
				tmTmp.tm_mon = 7;
				tmTmp.tm_mday = 1;
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeSpan1 = mktime(&tmTmp);

				tmTmp.tm_year = 2011;
				tmTmp.tm_mon = 7;
				tmTmp.tm_mday = 1;
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeSpan2 = mktime(&tmTmp);

				// 2010 ��7 ��1 ��������������Ħ�г����������Ħ�г�
				if (timeProductionDate >= timeSpan1 
					&& (L"M20"==sVehInfo.strVehTypeCode 
					|| L"M21"==sVehInfo.strVehTypeCode 
					|| L"M22"==sVehInfo.strVehTypeCode))
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"400";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"3.0";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"400";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"3.0";
				}
				// 2011 ��7 ��1 ��������������Ħ�г����������Ħ�г�
				else if (timeProductionDate >= timeSpan2 && std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M1"))
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"400";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"3.0";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"400";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"3.0";
				}
				// 2003 ��7 ��1 ����������Ħ�г������Ħ�г�(�����)
				else if (L"2"==sVehInfo.strEngineStroke)
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"4500";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.5";
				}
				// 2003 ��7 ��1 ����������Ħ�г������Ħ�г�(�ĳ��)
				else if (L"4"==sVehInfo.strEngineStroke)
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"1200";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.5";
				}
				// �ж���ϢΪnull���жϴ���������
				else
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"401";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"3.1";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"401";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"3.1";
				}

			}

		}
		// ��Ħ�г�
		else
		{
			// �ߵ���HCֵ[10-6]
			sDetStandard.strEmi_HISHC = L"";
			// �ߵ���COֵ[%]����ȷ��0.1
			sDetStandard.strEmi_HISCO = L"";
			// �͵���HCֵ[10-6] 
			sDetStandard.strEmi_LISHC = L"";
			// �͵���COֵ[%]����ȷ��0.1
			sDetStandard.strEmi_LISCO = L"";
		}

	}
	// ���ֻ����ϻ�����
	else
	{
		time_t timeSpan1, timeSpan2; 

		tmTmp.tm_year = 2001;
		tmTmp.tm_mon = 1;
		tmTmp.tm_mday = 1;
		tmTmp.tm_hour = 0;
		tmTmp.tm_min = 0;
		tmTmp.tm_sec = 0;
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeSpan1 = mktime(&tmTmp);

		tmTmp.tm_year = 2002;
		tmTmp.tm_mon = 1;
		tmTmp.tm_mday = 1;
		tmTmp.tm_hour = 0;
		tmTmp.tm_min = 0;
		tmTmp.tm_sec = 0;
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeSpan2 = mktime(&tmTmp);

		if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 3500) // ����
		{
			if (L"1"==sVehInfo.strIsPassengerVeh
				&& _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 5
				&& _wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 2500) // һ������
			{

				if (timeFirstRegisterDate >= timeSpan1) // 2001��1��1����
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"100";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"0.30";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"150";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"0.80";
				}
				else 
				{
					// 2001��1��1����ǰ

					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"900";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"3.00";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"1200";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
			}
			else // ��������
			{

				if (timeFirstRegisterDate >= timeSpan2) // 2002��1��1����
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"150";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"0.50";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"200";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"1.00";
				}
				else // 2002��1��1��ǰ
				{
					// �ߵ���HCֵ[10-6]
					sDetStandard.strEmi_HISHC = L"900";
					// �ߵ���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_HISCO = L"3.00";
					// �͵���HCֵ[10-6] 
					sDetStandard.strEmi_LISHC = L"1200";
					// �͵���COֵ[%]����ȷ��0.1
					sDetStandard.strEmi_LISCO = L"4.50";
				}
			}
		}
		else // ����
		{
			time_t timeSpan1, timeSpan2;  

			tmTmp.tm_year = 2004;
			tmTmp.tm_mon = 9;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeSpan1 = mktime(&tmTmp);

			tmTmp.tm_year = 1995;
			tmTmp.tm_mon = 7;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeSpan2 = mktime(&tmTmp);

			if (timeProductionDate >= timeSpan1) // 2004��9��1����
			{
				// �ߵ���HCֵ[10-6]
				sDetStandard.strEmi_HISHC = L"200";
				// �ߵ���COֵ[%]����ȷ��0.1
				sDetStandard.strEmi_HISCO = L"0.7";
				// �͵���HCֵ[10-6] 
				sDetStandard.strEmi_LISHC = L"250";
				// �͵���COֵ[%]����ȷ��0.1
				sDetStandard.strEmi_LISCO = L"1.5";
			}
			else if (timeProductionDate >= timeSpan2) // 1995��7��1����
			{
				// �ߵ���HCֵ[10-6]
				sDetStandard.strEmi_HISHC = L"900";
				// �ߵ���COֵ[%]����ȷ��0.1
				sDetStandard.strEmi_HISCO = L"3.0";
				// �͵���HCֵ[10-6] 
				sDetStandard.strEmi_LISHC = L"1200";
				// �͵���COֵ[%]����ȷ��0.1
				sDetStandard.strEmi_LISCO = L"4.5";
			}
			else // 1995��7��1��ǰ
			{
				// �ߵ���HCֵ[10-6]
				sDetStandard.strEmi_HISHC = L"1200";
				// �ߵ���COֵ[%]����ȷ��0.1
				sDetStandard.strEmi_HISCO = L"3.5";
				// �͵���HCֵ[10-6] 
				sDetStandard.strEmi_LISHC = L"2000";
				// �͵���COֵ[%]����ȷ��0.1
				sDetStandard.strEmi_LISCO = L"5.0";
			}
		}

		// �ߵ��٦�ֵ���ޣ���ȷ��0.01
		sDetStandard.strEmi_HISLambda_LowerLimit = L"0.97";
		// �ߵ��٦�ֵ���ޣ���ȷ��0.01
		sDetStandard.strEmi_HISLambda_UpperLimit = L"1.03";
	}
}

void CStandard::GetDIS_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	return GetDIS_7258(sVehInfo, sDetStandard);
}

void CStandard::GetFAOPA(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258) 
	{
		GetFAOPA_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetFAOPA_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetFAOPA_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	if (std::wstring::npos!=sVehInfo.strAirIntakeMode.find(L"��Ȼ")) // ��Ȼ����
	{
		// ������ϵ��ֵ[m-1]
		sDetStandard.strEmi_K = L"2.50";
	}
	else // ������ѹ
	{
		// ������ϵ��ֵ[m-1]
		sDetStandard.strEmi_K = L"3.00";
	}
}

void CStandard::GetFAOPA_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ������������
	struct tm tmTmp;  
	time_t timeFirstRegisterDate;  
	int nScanf;
	nScanf = swscanf_s(sVehInfo.strFirstRegisterDate.c_str(), L"%d-%d-%d %d:%d:%d" ,       
		&(tmTmp.tm_year),   
		&(tmTmp.tm_mon),   
		&(tmTmp.tm_mday),  
		&(tmTmp.tm_hour),  
		&(tmTmp.tm_min),  
		&(tmTmp.tm_sec));

	if (nScanf < 6)
	{
		nScanf = swscanf_s(sVehInfo.strFirstRegisterDate.c_str(), L"%d/%d/%d %d:%d:%d" ,       
			&(tmTmp.tm_year),   
			&(tmTmp.tm_mon),   
			&(tmTmp.tm_mday),  
			&(tmTmp.tm_hour),  
			&(tmTmp.tm_min),  
			&(tmTmp.tm_sec));

		if (nScanf < 6)
		{
			nScanf = swscanf_s(sVehInfo.strFirstRegisterDate.c_str(), L"%d-%d-%d" ,       
				&(tmTmp.tm_year),   
				&(tmTmp.tm_mon),   
				&(tmTmp.tm_mday));

			if (nScanf < 3)
			{
				nScanf = swscanf_s(sVehInfo.strFirstRegisterDate.c_str(), L"%d/%d/%d" ,       
					&(tmTmp.tm_year),   
					&(tmTmp.tm_mon),   
					&(tmTmp.tm_mday));

				if (nScanf < 3)
				{

					time(&timeFirstRegisterDate);
					localtime_s(&tmTmp, &timeFirstRegisterDate);
				}
				else
				{
					tmTmp.tm_hour = 0;
					tmTmp.tm_min = 0;
					tmTmp.tm_sec = 0;
					tmTmp.tm_year -= 1900;  
					tmTmp.tm_mon --;  
					tmTmp.tm_wday = 0;  
					tmTmp.tm_yday = 0;  
					tmTmp.tm_isdst = -1;  
					timeFirstRegisterDate = mktime(&tmTmp);
				}
			}
			else
			{
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeFirstRegisterDate = mktime(&tmTmp);
			}
		}
		else
		{
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeFirstRegisterDate = mktime(&tmTmp);
		}
	}
	else
	{
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeFirstRegisterDate = mktime(&tmTmp);
	}
	// ��ֵʹ�����õ�ʱ��
	time_t timeSpan1; 
	tmTmp.tm_year = 2001;
	tmTmp.tm_mon = 1;
	tmTmp.tm_mday = 1;
	tmTmp.tm_hour = 0;
	tmTmp.tm_min = 0;
	tmTmp.tm_sec = 0;
	tmTmp.tm_year -= 1900;  
	tmTmp.tm_mon --;  
	tmTmp.tm_wday = 0;  
	tmTmp.tm_yday = 0;  
	tmTmp.tm_isdst = -1;  
	timeSpan1 = mktime(&tmTmp);
	timeSpan1 = mktime(&tmTmp);

	if (timeFirstRegisterDate >= timeSpan1 && std::wstring::npos!=sVehInfo.strAirIntakeMode.find(L"����"))
	{
		// ������ϵ��ֵ[m-1]
		sDetStandard.strEmi_K = L"3.00";
	}
	else if (timeFirstRegisterDate >= timeSpan1)
	{
		// ������ϵ��ֵ[m-1]
		sDetStandard.strEmi_K = L"2.50";
	}
	else
	{
		// ������ϵ��ֵ[m-1]
		sDetStandard.strEmi_K = L"3.00";
	}


}

void CStandard::GetFAOPA_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	return GetFAOPA_7258(sVehInfo, sDetStandard);
}

void CStandard::GetFASMO(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258) 
	{
		GetFASMO_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetFASMO_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetFASMO_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ��������
	struct tm tmTmp;  
	time_t timeProductionDate;

	int nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d-%d-%d %d:%d:%d" ,       
		&(tmTmp.tm_year),   
		&(tmTmp.tm_mon),   
		&(tmTmp.tm_mday),  
		&(tmTmp.tm_hour),  
		&(tmTmp.tm_min),  
		&(tmTmp.tm_sec));

	if (nScanf < 6)
	{
		nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d/%d/%d %d:%d:%d" ,       
			&(tmTmp.tm_year),   
			&(tmTmp.tm_mon),   
			&(tmTmp.tm_mday),  
			&(tmTmp.tm_hour),  
			&(tmTmp.tm_min),  
			&(tmTmp.tm_sec));

		if (nScanf < 6)
		{
			nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d-%d-%d" ,       
				&(tmTmp.tm_year),   
				&(tmTmp.tm_mon),   
				&(tmTmp.tm_mday));

			if (nScanf < 3)
			{
				nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d/%d/%d" ,       
					&(tmTmp.tm_year),   
					&(tmTmp.tm_mon),   
					&(tmTmp.tm_mday));

				if (nScanf < 3)
				{

					time(&timeProductionDate);
					localtime_s(&tmTmp, &timeProductionDate);
				}
				else
				{
					tmTmp.tm_hour = 0;
					tmTmp.tm_min = 0;
					tmTmp.tm_sec = 0;
					tmTmp.tm_year -= 1900;  
					tmTmp.tm_mon --;  
					tmTmp.tm_wday = 0;  
					tmTmp.tm_yday = 0;  
					tmTmp.tm_isdst = -1;  
					timeProductionDate = mktime(&tmTmp);
				}
			}
			else
			{
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeProductionDate = mktime(&tmTmp);
			}
		}
		else
		{
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeProductionDate = mktime(&tmTmp);
		}
	}
	else
	{
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeProductionDate = mktime(&tmTmp);
	}

	// �����ֻ�����
	if (std::wstring::npos!= sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!= sVehInfo.strVehTypeCode.find(L"N"))
	{
		// ��������
		if (L"N11"==sVehInfo.strVehTypeCode)
		{
			time_t timeSpan1,timeSpan2;  

			tmTmp.tm_year = 2002;
			tmTmp.tm_mon = 7;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeSpan1 = mktime(&tmTmp);

			tmTmp.tm_year = 2004;
			tmTmp.tm_mon = 7;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeSpan2 = mktime(&tmTmp);

			// 2002.07.01ǰ����
			if (timeProductionDate < timeSpan1)
			{
				// ������Ϊnull
				if (L"" == sVehInfo.strGearsNumber)
				{
					// �̶�ֵ[Rb]
					sDetStandard.strEmi_Smoke = L"";
				}
				// ����
				else if (L"1" == sVehInfo.strGearsNumber)
				{
					// �̶�ֵ[Rb]
					sDetStandard.strEmi_Smoke = L"6.00";
				}
				// ���
				else
				{
					// �̶�ֵ[Rb]
					sDetStandard.strEmi_Smoke = L"4.50";
				}
			}		
			else if (timeProductionDate>=timeSpan1 && timeProductionDate < timeSpan2)
			{
				// 2002.07.01-2004.06.30����

				// ������Ϊnull
				if (L"" == sVehInfo.strGearsNumber)
				{
					// �̶�ֵ[Rb]
					sDetStandard.strEmi_Smoke = L"";
				}
				// ����
				else if (L"1" == sVehInfo.strGearsNumber)
				{
					// �̶�ֵ[Rb]
					sDetStandard.strEmi_Smoke = L"5.50";
				}
				// ���
				else
				{
					// �̶�ֵ[Rb]
					sDetStandard.strEmi_Smoke = L"4.50";
				}
			}		
			else if (timeProductionDate >= timeSpan2)
			{
				// 2004.07.01������

				// ������Ϊnull
				if (L"" == sVehInfo.strGearsNumber)
				{
					// �̶�ֵ[Rb]
					sDetStandard.strEmi_Smoke = L"";
				}
				// ����
				else if (L"1" == sVehInfo.strGearsNumber)
				{
					// �̶�ֵ[Rb]
					sDetStandard.strEmi_Smoke = L"5.50";
				}
				// ���
				else
				{
					// �̶�ֵ[Rb]
					sDetStandard.strEmi_Smoke = L"4.50";
				}
			}	
			else
			{
				// �ж���ϢΪnull���жϴ���������

				// �̶�ֵ[Rb]
				sDetStandard.strEmi_Smoke = L"6.01";
			}
		}		
		else
		{
			// ����������

			// �̶�ֵ[Rb]
			sDetStandard.strEmi_Smoke = L"";
		}

	}
	else
	{
		// ���ֻ����ϻ�����

		time_t timeSpan1,timeSpan2;  

		tmTmp.tm_year = 2002;
		tmTmp.tm_mon = 7;
		tmTmp.tm_mday = 1;
		tmTmp.tm_hour = 0;
		tmTmp.tm_min = 0;
		tmTmp.tm_sec = 0;
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeSpan1 = mktime(&tmTmp);

		tmTmp.tm_year = 1995;
		tmTmp.tm_mon = 7;
		tmTmp.tm_mday = 1;
		tmTmp.tm_hour = 0;
		tmTmp.tm_min = 0;
		tmTmp.tm_sec = 0;
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeSpan2 = mktime(&tmTmp);

		// ���ٻ���(ũ�ó�)
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"H5"))
		{
			if (timeProductionDate >= timeSpan1) // 1995��7��1����
			{
				// �̶�ֵ[Rb]
				sDetStandard.strEmi_Smoke = L"5.50";
			}
			else // 1995��7��1��ǰ
			{
				// �̶�ֵ[Rb]
				sDetStandard.strEmi_Smoke = L"6.00";
			}
		}
		else
		{
			if (timeProductionDate >= timeSpan2) // 1995��7��1����
			{
				// �̶�ֵ[Rb]
				sDetStandard.strEmi_Smoke = L"4.50";
			}
			else // 1995��7��1��ǰ
			{
				// �̶�ֵ[Rb]
				sDetStandard.strEmi_Smoke = L"5.00";
			}
		}
	}
}

void CStandard::GetFASMO_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ��������
	struct tm tmTmp;  
	time_t timeProductionDate;

	int nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d-%d-%d %d:%d:%d" ,       
		&(tmTmp.tm_year),   
		&(tmTmp.tm_mon),   
		&(tmTmp.tm_mday),  
		&(tmTmp.tm_hour),  
		&(tmTmp.tm_min),  
		&(tmTmp.tm_sec));

	if (nScanf < 6)
	{
		nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d/%d/%d %d:%d:%d" ,       
			&(tmTmp.tm_year),   
			&(tmTmp.tm_mon),   
			&(tmTmp.tm_mday),  
			&(tmTmp.tm_hour),  
			&(tmTmp.tm_min),  
			&(tmTmp.tm_sec));

		if (nScanf < 6)
		{
			nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d-%d-%d" ,       
				&(tmTmp.tm_year),   
				&(tmTmp.tm_mon),   
				&(tmTmp.tm_mday));

			if (nScanf < 3)
			{
				nScanf = swscanf_s(sVehInfo.strProductionDate.c_str(), L"%d/%d/%d" ,       
					&(tmTmp.tm_year),   
					&(tmTmp.tm_mon),   
					&(tmTmp.tm_mday));

				if (nScanf < 3)
				{

					time(&timeProductionDate);
					localtime_s(&tmTmp, &timeProductionDate);
				}
				else
				{
					tmTmp.tm_hour = 0;
					tmTmp.tm_min = 0;
					tmTmp.tm_sec = 0;
					tmTmp.tm_year -= 1900;  
					tmTmp.tm_mon --;  
					tmTmp.tm_wday = 0;  
					tmTmp.tm_yday = 0;  
					tmTmp.tm_isdst = -1;  
					timeProductionDate = mktime(&tmTmp);
				}
			}
			else
			{
				tmTmp.tm_hour = 0;
				tmTmp.tm_min = 0;
				tmTmp.tm_sec = 0;
				tmTmp.tm_year -= 1900;  
				tmTmp.tm_mon --;  
				tmTmp.tm_wday = 0;  
				tmTmp.tm_yday = 0;  
				tmTmp.tm_isdst = -1;  
				timeProductionDate = mktime(&tmTmp);
			}
		}
		else
		{
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeProductionDate = mktime(&tmTmp);
		}
	}
	else
	{
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeProductionDate = mktime(&tmTmp);
	}

	// �����ֻ�����
	if (std::wstring::npos!= sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!= sVehInfo.strVehTypeCode.find(L"N"))
	{
		// ��������
		if (L"N11"==sVehInfo.strVehTypeCode)
		{
			time_t timeSpan1,timeSpan2;  

			tmTmp.tm_year = 2002;
			tmTmp.tm_mon = 7;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeSpan1 = mktime(&tmTmp);

			tmTmp.tm_year = 2004;
			tmTmp.tm_mon = 7;
			tmTmp.tm_mday = 1;
			tmTmp.tm_hour = 0;
			tmTmp.tm_min = 0;
			tmTmp.tm_sec = 0;
			tmTmp.tm_year -= 1900;  
			tmTmp.tm_mon --;  
			tmTmp.tm_wday = 0;  
			tmTmp.tm_yday = 0;  
			tmTmp.tm_isdst = -1;  
			timeSpan2 = mktime(&tmTmp);

			// 2002.07.01ǰ����
			if (timeProductionDate < timeSpan1)
			{
				// ������Ϊnull
				if (L"" == sVehInfo.strGearsNumber)
				{
					// �̶�ֵ[Rb]
					sDetStandard.strEmi_Smoke = L"";
				}
				// ����
				else if (L"1" == sVehInfo.strGearsNumber)
				{
					// �̶�ֵ[Rb]
					sDetStandard.strEmi_Smoke = L"6.00";
				}
				// ���
				else
				{
					// �̶�ֵ[Rb]
					sDetStandard.strEmi_Smoke = L"4.50";
				}
			}		
			else if (timeProductionDate>=timeSpan1 && timeProductionDate < timeSpan2)
			{
				// 2002.07.01-2004.06.30����

				// ������Ϊnull
				if (L"" == sVehInfo.strGearsNumber)
				{
					// �̶�ֵ[Rb]
					sDetStandard.strEmi_Smoke = L"";
				}
				// ����
				else if (L"1" == sVehInfo.strGearsNumber)
				{
					// �̶�ֵ[Rb]
					sDetStandard.strEmi_Smoke = L"5.50";
				}
				// ���
				else
				{
					// �̶�ֵ[Rb]
					sDetStandard.strEmi_Smoke = L"4.50";
				}
			}		
			else if (timeProductionDate >= timeSpan2)
			{
				// 2004.07.01������

				// ������Ϊnull
				if (L"" == sVehInfo.strGearsNumber)
				{
					// �̶�ֵ[Rb]
					sDetStandard.strEmi_Smoke = L"";
				}
				// ����
				else if (L"1" == sVehInfo.strGearsNumber)
				{
					// �̶�ֵ[Rb]
					sDetStandard.strEmi_Smoke = L"5.50";
				}
				// ���
				else
				{
					// �̶�ֵ[Rb]
					sDetStandard.strEmi_Smoke = L"4.50";
				}
			}	
			else
			{
				// �ж���ϢΪnull���жϴ���������

				// �̶�ֵ[Rb]
				sDetStandard.strEmi_Smoke = L"6.01";
			}
		}		
		else
		{
			// ����������

			// �̶�ֵ[Rb]
			sDetStandard.strEmi_Smoke = L"";
		}

	}
	else
	{
		// ���ֻ����ϻ�����

		time_t timeSpan1;  

		tmTmp.tm_year = 1995;
		tmTmp.tm_mon = 7;
		tmTmp.tm_mday = 1;
		tmTmp.tm_hour = 0;
		tmTmp.tm_min = 0;
		tmTmp.tm_sec = 0;
		tmTmp.tm_year -= 1900;  
		tmTmp.tm_mon --;  
		tmTmp.tm_wday = 0;  
		tmTmp.tm_yday = 0;  
		tmTmp.tm_isdst = -1;  
		timeSpan1 = mktime(&tmTmp);


		if (timeProductionDate >= timeSpan1) // 1995��7��1����
		{
			// �̶�ֵ[Rb]
			sDetStandard.strEmi_Smoke = L"4.0";
		}
		else // 1995��7��1��ǰ
		{
			// �̶�ֵ[Rb]
			sDetStandard.strEmi_Smoke = L"4.7";
		}
	}
}

void CStandard::GetFASMO_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	return GetFASMO_7258(sVehInfo, sDetStandard);
}

void CStandard::GetPowerAll(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetCoaDis_7258(sVehInfo, sDetStandard);
		GetCOP_7258(sVehInfo, sDetStandard);
		GetFuelCon_7258(sVehInfo, sDetStandard);
		GetDireGearAccTime_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetCoaDis_18565(sVehInfo, sDetStandard);
		GetCOP_18565(sVehInfo, sDetStandard);
		GetFuelCon_18565(sVehInfo, sDetStandard);
		GetDireGearAccTime_18565(sVehInfo, sDetStandard);
	}

}

void CStandard::GetPower(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ���ʱ���ֵ[%]
	sDetStandard.strPow_VelocityInRPC = L"65.0";
}

void CStandard::GetSpeaker(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258) 
	{
		GetSpeaker_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetSpeaker_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetSpeaker_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ��������_��ֵ����
	sDetStandard.strSpeaker_LowerLimit = L"90.0";
	//��������_��ֵ����
	sDetStandard.strSpeaker_UpperLimit = L"115.0";
}

void CStandard::GetSpeaker_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ��������_��ֵ����
	sDetStandard.strSpeaker_LowerLimit = L"90.0";
	//��������_��ֵ����
	sDetStandard.strSpeaker_UpperLimit = L"115.0";
}

void CStandard::GetSpeaker_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ��������_��ֵ����
	sDetStandard.strSpeaker_LowerLimit = L"90.0";
	//��������_��ֵ����
	sDetStandard.strSpeaker_UpperLimit = L"115.0";
}

void CStandard::GetSuspension(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetSuspension_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetSuspension_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetSuspension_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ��������_������[%]
	sDetStandard.strSus_AR = L"40.0";
	// ��������_����Ч��(ƽ����)[%] 
	sDetStandard.strSus_Efficiency = L"45.0";
	// ��������_�����ʲ�[%]
	sDetStandard.strSus_ARSub = L"15.0";
	// ��������_����Ч�ʲ�(ƽ����)[%]
	sDetStandard.strSus_EfficiencySub = L"20.0";
}

void CStandard::GetSuspension_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ��������_������[%]
	sDetStandard.strSus_AR = L"40.0";
	// ��������_����Ч��(ƽ����)[%] 
	sDetStandard.strSus_Efficiency = L"45.0";
	// ��������_�����ʲ�[%]
	sDetStandard.strSus_ARSub = L"15.0";
	// ��������_����Ч�ʲ�(ƽ����)[%]
	sDetStandard.strSus_EfficiencySub = L"20.0";
}

void CStandard::GetSuspension_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ��������_������[%]
	sDetStandard.strSus_AR = L"40.0";
	// ��������_����Ч��(ƽ����)[%] 
	sDetStandard.strSus_Efficiency = L"45.0";
	// ��������_�����ʲ�[%]
	sDetStandard.strSus_ARSub = L"15.0";
	// ��������_����Ч�ʲ�(ƽ����)[%]
	sDetStandard.strSus_EfficiencySub = L"20.0";
}

void CStandard::GetRPP(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// TODO : δ֪��ֵ
}

void CStandard::GetAppearance(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetAppearance_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetAppearance_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetAppearance_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	sDetStandard.strApp_LRHighSub = L"40"; // ���_�������Ҹ߶Ȳ�[mm] (VE: VehEquipment, R:right L:left Sub: subtract ��ͬ) 
	// ����������ֵΪ���1.5/1000
	unsigned int uiWheelbase = CNHCommonAPI::round((float)(_wtof(sVehInfo.strWheBase12.c_str())*1.5/1000));
	wchar_t wchBuf[1024] = {L'\0'};
	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%u", uiWheelbase);

	sDetStandard.strApp_WheBaseSub = wchBuf; // ���_��������[mm](Whe:Wheel; ��ͬ) 
	sDetStandard.strApp_VehSuspension = L"65"; // ���_��������[%](Veh: Vehicle)

	// �γ����߹ҳ�
	if (!sVehInfo.strVehTypeCode.empty()
		&& (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // ���Ͱ�ҳ�
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // ���Ͱ�ҳ�
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // ���Ͱ�ҳ�
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G1") // ����ȫ�ҳ�
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G2") // ����ȫ�ҳ�
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G3") // ����ȫ�ҳ�
		|| std::wstring::npos!=sVehInfo.strVehType.find(L"�γ�")   // �γ�
		))
	{
		sDetStandard.strApp_SteWheFigDepth = L"1.6"; // ���_ת���ֻ������[mm](Ste: steering, Whe: wheel, Fig:Figure; ��ͬ) 
		sDetStandard.strApp_OthWheFigDepth = L"1.6"; // ���_������̥�������[mm](Oth:other; ��ͬ) 
		sDetStandard.strApp_MicWheFigDepth = L"1.6"; // ���_΢�ͳ��ֻ������[mm](Mic: Micro; ��ͬ) 
	}
	else
	{
		sDetStandard.strApp_SteWheFigDepth = L"3.2"; // ���_ת���ֻ������[mm](Ste: steering, Whe: wheel, Fig:Figure; ��ͬ) 
		sDetStandard.strApp_OthWheFigDepth = L"1.6"; // ���_������̥�������[mm](Oth:other; ��ͬ) 
		sDetStandard.strApp_MicWheFigDepth = L"1.6"; // ���_΢�ͳ��ֻ������[mm](Mic: Micro; ��ͬ) 
	}

	sDetStandard.strApp_CluPedEff = L"300"; // ���_�����̤����[N](Clu: Clutch, Ped: Pedal, Eff:Effort;��ͬ) 

	// TODO : ԭ�����
	sDetStandard.strApp_CluPedFreePath = L"100"; // ���_�����̤�������г�[mm] 


	if (!sVehInfo.strIsPassengerVeh.empty() && !sVehInfo.strIsPassengerVeh.empty() && !sVehInfo.strRatedPassengerCapacity.empty() && _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9)
	{
		sDetStandard.strApp_BrakePedEff = L"500"; // ���_�ƶ�̤����[N] 
		sDetStandard.strApp_BrakePedFreePath = L"120"; // ���_�ƶ�̤�������г�[mm] 
	}
	else
	{
		sDetStandard.strApp_BrakePedEff = L"700"; // ���_�ƶ�̤����[N] 
		sDetStandard.strApp_BrakePedFreePath = L"150"; // ���_�ƶ�̤�������г�[mm] 
	}

	// TODO : ��Ӧ��������ɣ�Ӧ������̥���ܸ����ǹ涨ѹ��
	sDetStandard.strApp_TyrePressure = L"120";  // ���_��̥��ѹ[MPa] 

	//TODO : δ֪��ֵ
	sDetStandard.strApp_FLDynBal = L"10"; // ���_ǰ���ֶ�ƽ��[g��cm](FL: FrontLeft, Bal: Balance; ��ͬ) 
	sDetStandard.strApp_FRDynBal = L"10"; // ���_ǰ�ҳ��ֶ�ƽ��[g��cm](FR: FrontRight) 
	sDetStandard.strApp_RLDynBal = L"10"; // ���_�����ֶ�ƽ��[g��cm](RL: RearLeft) 
	sDetStandard.strApp_RRDynBal = L"10"; // ���_���ҳ��ֶ�ƽ��[g��cm](RR: RearRight) 
	sDetStandard.strApp_Heating = L"10"; // ���_ȡů
}

void CStandard::GetAppearance_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	sDetStandard.strApp_LRHighSub = L"40"; // ���_�������Ҹ߶Ȳ�[mm] (VE: VehEquipment, R:right L:left Sub: subtract ��ͬ) 
	// ����������ֵΪ���1.5/1000
	unsigned int uiWheelbase = CNHCommonAPI::round((float)(_wtof(sVehInfo.strWheBase12.c_str())*1.5/1000));
	wchar_t wchBuf[1024] = {L'\0'};
	_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%u", uiWheelbase);

	sDetStandard.strApp_WheBaseSub = wchBuf ; // ���_��������[mm](Whe:Wheel; ��ͬ) 
	sDetStandard.strApp_VehSuspension = L"65"; // ���_��������[%](Veh: Vehicle)

	// �γ����߹ҳ�
	if (!sVehInfo.strVehTypeCode.empty()
		&& (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // ���Ͱ�ҳ�
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // ���Ͱ�ҳ�
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // ���Ͱ�ҳ�
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G1") // ����ȫ�ҳ�
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G2") // ����ȫ�ҳ�
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G3") // ����ȫ�ҳ�
		|| std::wstring::npos!=sVehInfo.strVehType.find(L"�γ�")   // �γ�
		))
	{
		sDetStandard.strApp_SteWheFigDepth = L"1.6"; // ���_ת���ֻ������[mm](Ste: steering, Whe: wheel, Fig:Figure; ��ͬ) 
		sDetStandard.strApp_OthWheFigDepth = L"1.6"; // ���_������̥�������[mm](Oth:other; ��ͬ) 
		sDetStandard.strApp_MicWheFigDepth = L"1.6"; // ���_΢�ͳ��ֻ������[mm](Mic: Micro; ��ͬ) 
	}
	else
	{
		sDetStandard.strApp_SteWheFigDepth = L"3.2"; // ���_ת���ֻ������[mm](Ste: steering, Whe: wheel, Fig:Figure; ��ͬ) 
		sDetStandard.strApp_OthWheFigDepth = L"1.6"; // ���_������̥�������[mm](Oth:other; ��ͬ) 
		sDetStandard.strApp_MicWheFigDepth = L"1.6"; // ���_΢�ͳ��ֻ������[mm](Mic: Micro; ��ͬ) 
	}

	sDetStandard.strApp_CluPedEff = L"300"; // ���_�����̤����[N](Clu: Clutch, Ped: Pedal, Eff:Effort;��ͬ) 

	// TODO : ԭ�����
	sDetStandard.strApp_CluPedFreePath = L"100"; // ���_�����̤�������г�[mm] 


	if (!sVehInfo.strIsPassengerVeh.empty() && !sVehInfo.strIsPassengerVeh.empty() && !sVehInfo.strRatedPassengerCapacity.empty() && _wtoi(sVehInfo.strRatedPassengerCapacity.c_str()) <= 9)
	{
		sDetStandard.strApp_BrakePedEff = L"500"; // ���_�ƶ�̤����[N] 
		sDetStandard.strApp_BrakePedFreePath = L"120"; // ���_�ƶ�̤�������г�[mm] 
	}
	else
	{
		sDetStandard.strApp_BrakePedEff = L"700"; // ���_�ƶ�̤����[N] 
		sDetStandard.strApp_BrakePedFreePath = L"150"; // ���_�ƶ�̤�������г�[mm] 
	}

	// TODO : ��Ӧ��������ɣ�Ӧ������̥���ܸ����ǹ涨ѹ��
	sDetStandard.strApp_TyrePressure = L"120";  // ���_��̥��ѹ[MPa] 

	//TODO : δ֪��ֵ
	sDetStandard.strApp_FLDynBal = L"10"; // ���_ǰ���ֶ�ƽ��[g��cm](FL: FrontLeft, Bal: Balance; ��ͬ) 
	sDetStandard.strApp_FRDynBal = L"10"; // ���_ǰ�ҳ��ֶ�ƽ��[g��cm](FR: FrontRight) 
	sDetStandard.strApp_RLDynBal = L"10"; // ���_�����ֶ�ƽ��[g��cm](RL: RearLeft) 
	sDetStandard.strApp_RRDynBal = L"10"; // ���_���ҳ��ֶ�ƽ��[g��cm](RR: RearRight) 
	sDetStandard.strApp_Heating = L"10"; // ���_ȡů
}

void CStandard::GetCoaDis(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetCoaDis_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetCoaDis_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetCoaDis_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	CString strDriveAxle = sVehInfo.strDriveAxle.c_str();
	strDriveAxle.Replace(L",", L"");
	const bool bDBDrive = (strDriveAxle.GetLength() >= 2);
	// ��������Ϊ�յ���С��1000
	if (sVehInfo.strUnladenMass.empty())
	{
		// ˫������
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"104";
		}
		// ��������
		else
		{
			sDetStandard.strPow_CoaDis =  L"130";
		}
	}
	// ��������С��1000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) < 1000)
	{
		// ˫������
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis =  L"104";
		}
		// ��������
		else
		{
			sDetStandard.strPow_CoaDis =  L"130";
		}
	}
	// 1000<=��������<=4000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) <= 4000)
	{
		// ˫������
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"120";
		}
		// ��������
		else
		{
			sDetStandard.strPow_CoaDis = L"160";
		}
	}
	// 4000<��������<=5000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) <= 5000)
	{
		// ˫������
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"144";
		}
		// ��������
		else
		{
			sDetStandard.strPow_CoaDis = L"180";
		}
	}
	// 5000<��������<=8000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) <= 8000)
	{
		// ˫������
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"184";
		}
		// ��������
		else
		{
			sDetStandard.strPow_CoaDis = L"230";
		}
	}
	// 8000<��������<=11000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) <= 11000)
	{
		// ˫������
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"200";
		}
		// ��������
		else
		{
			sDetStandard.strPow_CoaDis = L"250";
		}
	}
	// ��������>11000
	else
	{
		// ˫������
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"214";
		}
		// ��������
		else
		{
			sDetStandard.strPow_CoaDis = L"270";
		}
	}

}

void CStandard::GetCoaDis_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	//const bool bDBDrive = (1 == _wtoi(sVehInfo.strDBDrive.c_str()));
	CString strDriveAxle = sVehInfo.strDriveAxle.c_str();
	strDriveAxle.Replace(L",", L"");
	const bool bDBDrive = (strDriveAxle.GetLength() >= 2);
	// ��������Ϊ�յ���С��1000
	if (sVehInfo.strUnladenMass.empty())
	{
		// ˫������
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"104";
		}
		// ��������
		else
		{
			sDetStandard.strPow_CoaDis =  L"130";
		}
	}
	// ��������С��1000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) < 1000)
	{
		// ˫������
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis =  L"104";
		}
		// ��������
		else
		{
			sDetStandard.strPow_CoaDis =  L"130";
		}
	}
	// 1000<=��������<=4000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) <= 4000)
	{
		// ˫������
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"120";
		}
		// ��������
		else
		{
			sDetStandard.strPow_CoaDis = L"160";
		}
	}
	// 4000<��������<=5000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) <= 5000)
	{
		// ˫������
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"144";
		}
		// ��������
		else
		{
			sDetStandard.strPow_CoaDis = L"180";
		}
	}
	// 5000<��������<=8000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) <= 8000)
	{
		// ˫������
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"184";
		}
		// ��������
		else
		{
			sDetStandard.strPow_CoaDis = L"230";
		}
	}
	// 8000<��������<=11000
	else if (_wtoi(sVehInfo.strUnladenMass.c_str()) <= 11000)
	{
		// ˫������
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"200";
		}
		// ��������
		else
		{
			sDetStandard.strPow_CoaDis = L"250";
		}
	}
	// ��������>11000
	else
	{
		// ˫������
		if (bDBDrive)
		{
			sDetStandard.strPow_CoaDis = L"214";
		}
		// ��������
		else
		{
			sDetStandard.strPow_CoaDis = L"270";
		}
	}

}

void CStandard::GetCOP(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetCOP_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetCOP_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetCOP_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	const std:: wstring strDefaultPow_VelocityInRTC = L"55";
	const std:: wstring strDefaultPow_PPInRTC = L"50";
	const std:: wstring strDefaultPow_VelocityInRPC = L"55";
	const std:: wstring strDefaultPow_PPInRPC = L"50";
	const std:: wstring strDefaultPow_RPPInRTC = L"60";
	const std:: wstring strDefaultPow_RPPInRPC = L"60";
	std:: wstring strModel = sVehInfo.strModel;
	int n = strModel.length();
	if(strModel.empty() || n<5)
	{
		sDetStandard.strPow_VelocityInRTC = strDefaultPow_VelocityInRTC;
		sDetStandard.strPow_PPInRTC = strDefaultPow_PPInRTC;
		sDetStandard.strPow_VelocityInRPC = strDefaultPow_VelocityInRPC;
		sDetStandard.strPow_PPInRPC = strDefaultPow_PPInRPC;
		sDetStandard.strPow_RPPInRTC = strDefaultPow_RPPInRTC;
		sDetStandard.strPow_RPPInRPC = strDefaultPow_RPPInRPC;
	}
	else
	{
		// �������ʹ���
		int typeCode = 0;
		// ��Ҫ����
		int mainParam = 0;

		typeCode = _wtoi(strModel.substr(2,1).c_str());
		mainParam = _wtoi(strModel.substr(3,2).c_str());
		// �ػ�����
		if (typeCode == 1)
		{
			// 1010, 1020ϵ��
			if (mainParam > 0 && mainParam < 3)
			{
				// Ŀ�공��
				sDetStandard.strPow_VelocityInRTC = L"60";
				sDetStandard.strPow_VelocityInRPC = L"90";
				// ����ֵ
				sDetStandard.strPow_PPInRTC = L"50";
				sDetStandard.strPow_PPInRPC = L"40";
				// �ֵ
				sDetStandard.strPow_RPPInRTC = L"75";
				sDetStandard.strPow_RPPInRPC = L"65";
			}
			// 1030, 1040ϵ��
			else if (mainParam > 2 && mainParam < 5)
			{
				// ����
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
				{
					sDetStandard.strPow_VelocityInRTC = L"55";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"90";
					sDetStandard.strPow_PPInRPC = L"45";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"70";
				}
				// ����ȼ�ϵ����ʹ���
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"60";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"90";
					sDetStandard.strPow_PPInRPC = L"40";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"65";
				}
			}
			// 1050, 1060ϵ��
			else if (mainParam > 4 && mainParam < 7)
			{
				// ����
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
				{
					sDetStandard.strPow_VelocityInRTC = L"50";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"45";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"70";
				}
				// ����ȼ�ϵ����ʹ���
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"60";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"90";
					sDetStandard.strPow_PPInRPC = L"40";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"65";
				}
			}
			// 1070, 1080ϵ��
			else if (mainParam > 6 && mainParam < 9)
			{
				sDetStandard.strPow_VelocityInRTC = L"50";
				sDetStandard.strPow_PPInRTC = L"50";
				sDetStandard.strPow_VelocityInRPC = L"80";
				sDetStandard.strPow_PPInRPC = L"45";
				sDetStandard.strPow_RPPInRTC = L"75";
				sDetStandard.strPow_RPPInRPC = L"70";
			}
			// 1090ϵ��
			else if (mainParam > 8 && mainParam < 10)
			{
				// ����
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
				{
					sDetStandard.strPow_VelocityInRTC = L"55";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"45";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"70";
				}
				// ����ȼ�ϵ����ʹ���
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"40";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"45";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"70";
				}
			}
			// 1100, 1110, 1120, 1130ϵ��
			else if (mainParam > 9 && mainParam < 14)
			{
				sDetStandard.strPow_VelocityInRTC = L"50";
				sDetStandard.strPow_PPInRTC = L"45";
				sDetStandard.strPow_VelocityInRPC = L"80";
				sDetStandard.strPow_PPInRPC = L"40";
				sDetStandard.strPow_RPPInRTC = L"75";
				sDetStandard.strPow_RPPInRPC = L"65";
			}
			// 1140, 1150, 1160ϵ��
			else if (mainParam > 13 && mainParam < 17)
			{
				sDetStandard.strPow_VelocityInRTC = L"50";
				sDetStandard.strPow_PPInRTC = L"50";
				sDetStandard.strPow_VelocityInRPC = L"80";
				sDetStandard.strPow_PPInRPC = L"40";
				sDetStandard.strPow_RPPInRTC = L"75";
				sDetStandard.strPow_RPPInRPC = L"65";
			}
			// 1170, 1190ϵ��
			else if (mainParam == 17 || mainParam < 19)
			{
				sDetStandard.strPow_VelocityInRTC = L"55";
				sDetStandard.strPow_PPInRTC = L"50";
				sDetStandard.strPow_VelocityInRPC = L"80";
				sDetStandard.strPow_PPInRPC = L"40";
				sDetStandard.strPow_RPPInRTC = L"75";
				sDetStandard.strPow_RPPInRPC = L"65";
			}
			else
			{
				sDetStandard.strPow_VelocityInRTC = strDefaultPow_VelocityInRTC;
				sDetStandard.strPow_PPInRTC = strDefaultPow_PPInRTC;
				sDetStandard.strPow_VelocityInRPC = strDefaultPow_VelocityInRPC;
				sDetStandard.strPow_PPInRPC = strDefaultPow_PPInRPC;
				sDetStandard.strPow_RPPInRTC = strDefaultPow_RPPInRTC;
				sDetStandard.strPow_RPPInRPC = strDefaultPow_RPPInRPC;
			}
		}

		// ר������
		else if (typeCode == 5)
		{
			// 5010, 5020ϵ��
			if (mainParam > 0 && mainParam < 3)
			{
				sDetStandard.strPow_VelocityInRTC = L"60";
				sDetStandard.strPow_PPInRTC = L"58";
				sDetStandard.strPow_VelocityInRPC = L"90";
				sDetStandard.strPow_PPInRPC = L"38";
				sDetStandard.strPow_RPPInRTC = L"75";
				sDetStandard.strPow_RPPInRPC = L"65";
			}
			// 5030, 5040ϵ��
			else if (mainParam > 2 && mainParam < 5)
			{
				// ����
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
				{
					sDetStandard.strPow_VelocityInRTC = L"55";
					sDetStandard.strPow_PPInRTC = L"48";
					sDetStandard.strPow_VelocityInRPC = L"90";
					sDetStandard.strPow_PPInRPC = L"43";
					sDetStandard.strPow_RPPInRTC = L"73";
					sDetStandard.strPow_RPPInRPC = L"64";
				}
				// ����ȼ�ϵ����ʹ���
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"60";
					sDetStandard.strPow_PPInRTC = L"48";
					sDetStandard.strPow_VelocityInRPC = L"90";
					sDetStandard.strPow_PPInRPC = L"38";
					sDetStandard.strPow_RPPInRTC = L"72";
					sDetStandard.strPow_RPPInRPC = L"63";
				}
			}
			// 5050, 5060ϵ��
			else if (mainParam > 4 && mainParam < 7)
			{
				// ����
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
				{
					sDetStandard.strPow_VelocityInRTC = L"50";
					sDetStandard.strPow_PPInRTC = L"46";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"41";
					sDetStandard.strPow_RPPInRTC = L"72";
					sDetStandard.strPow_RPPInRPC = L"63";
				}
				// ����ȼ�ϵ����ʹ���
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"60";
					sDetStandard.strPow_PPInRTC = L"46";
					sDetStandard.strPow_VelocityInRPC = L"90";
					sDetStandard.strPow_PPInRPC = L"36";
					sDetStandard.strPow_RPPInRTC = L"72";
					sDetStandard.strPow_RPPInRPC = L"63";
				}
			}
			// 5070, 5080ϵ��
			else if (mainParam > 6 && mainParam < 9)
			{
				sDetStandard.strPow_VelocityInRTC = L"50";
				sDetStandard.strPow_PPInRTC = L"46";
				sDetStandard.strPow_VelocityInRPC = L"80";
				sDetStandard.strPow_PPInRPC = L"41";
				sDetStandard.strPow_RPPInRTC = L"72";
				sDetStandard.strPow_RPPInRPC = L"63";
			}
			// 5090ϵ��
			else if (mainParam > 8 && mainParam < 10)
			{
				// ����
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
				{
					sDetStandard.strPow_VelocityInRTC = L"55";
					sDetStandard.strPow_PPInRTC = L"46";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"41";
					sDetStandard.strPow_RPPInRTC = L"72";
					sDetStandard.strPow_RPPInRPC = L"63";
				}
				// ����ȼ�ϵ����ʹ���
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"40";
					sDetStandard.strPow_PPInRTC = L"46";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"41";
					sDetStandard.strPow_RPPInRTC = L"72";
					sDetStandard.strPow_RPPInRPC = L"63";
				}
			}
			// 5100, 5110, 5120, 5130ϵ��
			else if (mainParam > 9 && mainParam < 14)
			{
				sDetStandard.strPow_VelocityInRTC = L"50";
				sDetStandard.strPow_PPInRTC = L"41";
				sDetStandard.strPow_VelocityInRPC = L"80";
				sDetStandard.strPow_PPInRPC = L"36";
				sDetStandard.strPow_RPPInRTC = L"72";
				sDetStandard.strPow_RPPInRPC = L"63";
			}
			// 5140, 5150, 5160ϵ��
			else if (mainParam > 13 && mainParam < 17)
			{
				sDetStandard.strPow_VelocityInRTC = L"50";
				sDetStandard.strPow_PPInRTC = L"46";
				sDetStandard.strPow_VelocityInRPC = L"80";
				sDetStandard.strPow_PPInRPC = L"36";
				sDetStandard.strPow_RPPInRTC = L"72";
				sDetStandard.strPow_RPPInRPC = L"63";
			}
			// 5170, 5190ϵ��
			else if (mainParam == 17 || mainParam < 19)
			{
				sDetStandard.strPow_VelocityInRTC = L"55";
				sDetStandard.strPow_PPInRTC = L"46";
				sDetStandard.strPow_VelocityInRPC = L"80";
				sDetStandard.strPow_PPInRPC = L"36";
				sDetStandard.strPow_RPPInRTC = L"72";
				sDetStandard.strPow_RPPInRPC = L"63";
			}
			else
			{
				sDetStandard.strPow_VelocityInRTC = strDefaultPow_VelocityInRTC;
				sDetStandard.strPow_PPInRTC = strDefaultPow_PPInRTC;
				sDetStandard.strPow_VelocityInRPC = strDefaultPow_VelocityInRPC;
				sDetStandard.strPow_PPInRPC = strDefaultPow_PPInRPC;
				sDetStandard.strPow_RPPInRTC = strDefaultPow_RPPInRTC;
				sDetStandard.strPow_RPPInRPC = strDefaultPow_RPPInRPC;
			}
		}

		// �ؿ�����
		else if (typeCode == 6)
		{
			// 6600ϵ��
			if (mainParam == 60)
			{
				// ����
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
				{
					sDetStandard.strPow_VelocityInRTC = L"45";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"70";
					sDetStandard.strPow_PPInRPC = L"40";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"65";
				}
				// ����ȼ�ϵ����ʹ���
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"60";
					sDetStandard.strPow_PPInRTC = L"45";
					sDetStandard.strPow_VelocityInRPC = L"85";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"70";
					sDetStandard.strPow_RPPInRPC = L"60";
				}
			}
			// 6700ϵ��
			else if (mainParam == 70)
			{
				// ����
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
				{
					sDetStandard.strPow_VelocityInRTC = L"55";
					sDetStandard.strPow_PPInRTC = L"45";
					sDetStandard.strPow_VelocityInRPC = L"75";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"70";
					sDetStandard.strPow_RPPInRPC = L"60";
				}
				// ����ȼ�ϵ����ʹ���
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"50";
					sDetStandard.strPow_PPInRTC = L"40";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"65";
					sDetStandard.strPow_RPPInRPC = L"60";
				}
			}
			// 6800ϵ��
			else if (mainParam == 80)
			{
				// ����
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
				{
					sDetStandard.strPow_VelocityInRTC = L"45";
					sDetStandard.strPow_PPInRTC = L"45";
					sDetStandard.strPow_VelocityInRPC = L"75";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"70";
					sDetStandard.strPow_RPPInRPC = L"60";

				}
				// ����ȼ�ϵ����ʹ���
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"40";
					sDetStandard.strPow_PPInRTC = L"40";
					sDetStandard.strPow_VelocityInRPC = L"85";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"65";
					sDetStandard.strPow_RPPInRPC = L"60";

				}
			}
			// 6900ϵ��
			else if (mainParam == 90)
			{
				// ����
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
				{
					sDetStandard.strPow_VelocityInRTC = L"60";
					sDetStandard.strPow_PPInRTC = L"45";
					sDetStandard.strPow_VelocityInRPC = L"85";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"70";
					sDetStandard.strPow_RPPInRPC = L"60";
				}
				// ����ȼ�ϵ����ʹ���
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"40";
					sDetStandard.strPow_PPInRTC = L"40";
					sDetStandard.strPow_VelocityInRPC = L"85";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"65";
					sDetStandard.strPow_RPPInRPC = L"60";
				}
			}
			// 6100ϵ��
			else if (mainParam == 10)
			{
				// ����
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
				{
					sDetStandard.strPow_VelocityInRTC = L"40";
					sDetStandard.strPow_PPInRTC = L"45";
					sDetStandard.strPow_VelocityInRPC = L"85";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"70";
					sDetStandard.strPow_RPPInRPC = L"60";
				}
				// ����ȼ�ϵ����ʹ���
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"40";
					sDetStandard.strPow_PPInRTC = L"40";
					sDetStandard.strPow_VelocityInRPC = L"85";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"65";
					sDetStandard.strPow_RPPInRPC = L"60";
				}
			}
			// 6110ϵ��
			else if (mainParam == 11)
			{
				// ����
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
				{
					sDetStandard.strPow_VelocityInRTC = L"55";
					sDetStandard.strPow_PPInRTC = L"45";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"70";
					sDetStandard.strPow_RPPInRPC = L"60";
				}
				// ����ȼ�ϵ����ʹ���
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"40";
					sDetStandard.strPow_PPInRTC = L"40";
					sDetStandard.strPow_VelocityInRPC = L"85";
					sDetStandard.strPow_PPInRPC = L"35";
					sDetStandard.strPow_RPPInRTC = L"65";
					sDetStandard.strPow_RPPInRPC = L"60";
				}
			}
			// 6120ϵ��
			else if (mainParam == 12)
			{
				sDetStandard.strPow_VelocityInRTC = L"60";
				sDetStandard.strPow_PPInRTC = L"40";
				sDetStandard.strPow_VelocityInRPC = L"90";
				sDetStandard.strPow_PPInRPC = L"35";
				sDetStandard.strPow_RPPInRTC = L"65";
				sDetStandard.strPow_RPPInRPC = L"60";
			}
			else
			{
				sDetStandard.strPow_VelocityInRTC = strDefaultPow_VelocityInRTC;
				sDetStandard.strPow_PPInRTC = strDefaultPow_PPInRTC;
				sDetStandard.strPow_VelocityInRPC = strDefaultPow_VelocityInRPC;
				sDetStandard.strPow_PPInRPC = strDefaultPow_PPInRPC;
				sDetStandard.strPow_RPPInRTC = strDefaultPow_RPPInRTC;
				sDetStandard.strPow_RPPInRPC = strDefaultPow_RPPInRPC;
			}
		}

		// �γ�
		else if (typeCode == 7)
		{
			// �������߸���
			if (std::wstring::npos!= sVehInfo.strBrand.find(L"����")|| std::wstring::npos!= sVehInfo.strBrand.find(L"����"))
			{
				sDetStandard.strPow_VelocityInRTC = L"65";
				sDetStandard.strPow_PPInRTC = L"35";
				sDetStandard.strPow_VelocityInRPC = L"";
				sDetStandard.strPow_PPInRPC = L"";
				sDetStandard.strPow_RPPInRTC = L"60";
			}
			// ɣ����
			else if (std::wstring::npos!= sVehInfo.strBrand.find(L"ɣ����"))
			{
				sDetStandard.strPow_VelocityInRTC = L"65";
				sDetStandard.strPow_PPInRTC = L"40";
				sDetStandard.strPow_VelocityInRPC = L"";
				sDetStandard.strPow_PPInRPC = L"";
				sDetStandard.strPow_RPPInRTC = L"65";
			}
			else
			{
				sDetStandard.strPow_VelocityInRTC = strDefaultPow_VelocityInRTC;
				sDetStandard.strPow_PPInRTC = strDefaultPow_PPInRTC;
				sDetStandard.strPow_VelocityInRPC = strDefaultPow_VelocityInRPC;
				sDetStandard.strPow_PPInRPC = strDefaultPow_PPInRPC;
				sDetStandard.strPow_RPPInRTC = strDefaultPow_RPPInRTC;
				sDetStandard.strPow_RPPInRPC = strDefaultPow_RPPInRPC;
			}
		}

		//��ҳ�
		else if (typeCode == 9)
		{
			// ����Ϊ�յ�10t����
			if (sVehInfo.strRatedLoadingMass.empty())
			{
				// ����
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
				{
					sDetStandard.strPow_VelocityInRTC = L"50";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"45";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"70";
				}
				// ����ȼ�ϵ����ʹ���
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"40";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"45";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"70";
				}
			}
			// 10t
			else if (_wtoi(sVehInfo.strRatedLoadingMass.c_str()) <= 10000)
			{
				// ����
				if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
					std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
				{
					sDetStandard.strPow_VelocityInRTC = L"50";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"45";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"70";
				}
				// ����ȼ�ϵ����ʹ���
				else
				{
					sDetStandard.strPow_VelocityInRTC = L"40";
					sDetStandard.strPow_PPInRTC = L"50";
					sDetStandard.strPow_VelocityInRPC = L"80";
					sDetStandard.strPow_PPInRPC = L"45";
					sDetStandard.strPow_RPPInRTC = L"75";
					sDetStandard.strPow_RPPInRPC = L"70";
				}
			}
			// 15t, 20t
			else if (_wtoi(sVehInfo.strRatedLoadingMass.c_str()) <= 20000)
			{
				sDetStandard.strPow_VelocityInRTC = L"45";
				sDetStandard.strPow_PPInRTC = L"45";
				sDetStandard.strPow_VelocityInRPC = L"70";
				sDetStandard.strPow_PPInRPC = L"40";
				sDetStandard.strPow_RPPInRTC = L"70";
				sDetStandard.strPow_RPPInRPC = L"65";
			}
			// 25t
			else
			{
				sDetStandard.strPow_VelocityInRTC = L"45";
				sDetStandard.strPow_PPInRTC = L"50";
				sDetStandard.strPow_VelocityInRPC = L"75";
				sDetStandard.strPow_PPInRPC = L"40";
				sDetStandard.strPow_RPPInRTC = L"75";
				sDetStandard.strPow_RPPInRPC = L"65";
			}
		}
		else
		{
			sDetStandard.strPow_VelocityInRTC = strDefaultPow_VelocityInRTC;
			sDetStandard.strPow_PPInRTC = strDefaultPow_PPInRTC;
			sDetStandard.strPow_VelocityInRPC = strDefaultPow_VelocityInRPC;
			sDetStandard.strPow_PPInRPC = strDefaultPow_PPInRPC;
			sDetStandard.strPow_RPPInRTC = strDefaultPow_RPPInRTC;
			sDetStandard.strPow_RPPInRPC = strDefaultPow_RPPInRPC;
		}
	}

}

void CStandard::GetCOP_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	const std:: wstring strDefaultPow_VelocityInRTC = L"55";
	const std:: wstring strDefaultPow_PPInRTC = L"50";
	const std:: wstring strDefaultPow_VelocityInRPC = L"55";
	const std:: wstring strDefaultPow_PPInRPC = L"50";
	const std:: wstring strDefaultPow_RPPInRTC = L"60";
	const std:: wstring strDefaultPow_RPPInRPC = L"60";
	if (std::wstring::npos != sVehInfo.strVehSeries.find(L"1010") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1020"))
	{
		// Ŀ�공��
		sDetStandard.strPow_VelocityInRTC = L"60";
		sDetStandard.strPow_VelocityInRPC = L"90";
		// ����ֵ
		sDetStandard.strPow_PPInRTC = L"50";
		sDetStandard.strPow_PPInRPC = L"40";
		// �ֵ
		sDetStandard.strPow_RPPInRTC = L"75";
		sDetStandard.strPow_RPPInRPC = L"65";
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"1030") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1040"))
	{
		// ����
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
		{
			sDetStandard.strPow_VelocityInRTC = L"55";
			sDetStandard.strPow_PPInRTC = L"50";
			sDetStandard.strPow_VelocityInRPC = L"90";
			sDetStandard.strPow_PPInRPC = L"45";
			sDetStandard.strPow_RPPInRTC = L"75";
			sDetStandard.strPow_RPPInRPC = L"70";
		}
		// ����ȼ�ϵ����ʹ���
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"60";
			sDetStandard.strPow_PPInRTC = L"50";
			sDetStandard.strPow_VelocityInRPC = L"90";
			sDetStandard.strPow_PPInRPC = L"40";
			sDetStandard.strPow_RPPInRTC = L"75";
			sDetStandard.strPow_RPPInRPC = L"65";
		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"1050") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1060"))
	{
		// ����
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
		{
			sDetStandard.strPow_VelocityInRTC = L"50";
			sDetStandard.strPow_PPInRTC = L"50";
			sDetStandard.strPow_VelocityInRPC = L"80";
			sDetStandard.strPow_PPInRPC = L"45";
			sDetStandard.strPow_RPPInRTC = L"75";
			sDetStandard.strPow_RPPInRPC = L"70";
		}
		// ����ȼ�ϵ����ʹ���
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"60";
			sDetStandard.strPow_PPInRTC = L"50";
			sDetStandard.strPow_VelocityInRPC = L"90";
			sDetStandard.strPow_PPInRPC = L"40";
			sDetStandard.strPow_RPPInRTC = L"75";
			sDetStandard.strPow_RPPInRPC = L"65";
		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"1070") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1080"))
	{
		sDetStandard.strPow_VelocityInRTC = L"50";
		sDetStandard.strPow_PPInRTC = L"50";
		sDetStandard.strPow_VelocityInRPC = L"80";
		sDetStandard.strPow_PPInRPC = L"45";
		sDetStandard.strPow_RPPInRTC = L"75";
		sDetStandard.strPow_RPPInRPC = L"70";
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"1090"))
	{
		// ����
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
		{
			sDetStandard.strPow_VelocityInRTC = L"55";
			sDetStandard.strPow_PPInRTC = L"50";
			sDetStandard.strPow_VelocityInRPC = L"80";
			sDetStandard.strPow_PPInRPC = L"45";
			sDetStandard.strPow_RPPInRTC = L"75";
			sDetStandard.strPow_RPPInRPC = L"70";
		}
		// ����ȼ�ϵ����ʹ���
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"40";
			sDetStandard.strPow_PPInRTC = L"50";
			sDetStandard.strPow_VelocityInRPC = L"80";
			sDetStandard.strPow_PPInRPC = L"45";
			sDetStandard.strPow_RPPInRTC = L"75";
			sDetStandard.strPow_RPPInRPC = L"70";
		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"1100") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1110") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1120") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1130"))
	{
		// 1100, 1110, 1120, 1130ϵ��
		sDetStandard.strPow_VelocityInRTC = L"50";
		sDetStandard.strPow_PPInRTC = L"45";
		sDetStandard.strPow_VelocityInRPC = L"80";
		sDetStandard.strPow_PPInRPC = L"40";
		sDetStandard.strPow_RPPInRTC = L"75";
		sDetStandard.strPow_RPPInRPC = L"65";
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"1140") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1150") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1160"))
	{
		// 1140, 1150, 1160ϵ��
		sDetStandard.strPow_VelocityInRTC = L"50";
		sDetStandard.strPow_PPInRTC = L"50";
		sDetStandard.strPow_VelocityInRPC = L"80";
		sDetStandard.strPow_PPInRPC = L"40";
		sDetStandard.strPow_RPPInRTC = L"75";
		sDetStandard.strPow_RPPInRPC = L"65";
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"1170") || std::wstring::npos != sVehInfo.strVehSeries.find(L"1190"))
	{
		// 1170, 1190ϵ��
		sDetStandard.strPow_VelocityInRTC = L"55";
		sDetStandard.strPow_PPInRTC = L"50";
		sDetStandard.strPow_VelocityInRPC = L"80";
		sDetStandard.strPow_PPInRPC = L"40";
		sDetStandard.strPow_RPPInRTC = L"75";
		sDetStandard.strPow_RPPInRPC = L"65";
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"10t����г�"))
	{
		// ����
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
		{
			sDetStandard.strPow_VelocityInRTC = L"50";
			sDetStandard.strPow_PPInRTC = L"50";
			sDetStandard.strPow_VelocityInRPC = L"80";
			sDetStandard.strPow_PPInRPC = L"45";
			sDetStandard.strPow_RPPInRTC = L"75";
			sDetStandard.strPow_RPPInRPC = L"70";
		}
		// ����ȼ�ϵ����ʹ���
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"40";
			sDetStandard.strPow_PPInRTC = L"50";
			sDetStandard.strPow_VelocityInRPC = L"80";
			sDetStandard.strPow_PPInRPC = L"45";
			sDetStandard.strPow_RPPInRTC = L"75";
			sDetStandard.strPow_RPPInRPC = L"70";
		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"15t����г�") || std::wstring::npos != sVehInfo.strVehSeries.find(L"20t����г�"))
	{
		sDetStandard.strPow_VelocityInRTC = L"45";
		sDetStandard.strPow_PPInRTC = L"45";
		sDetStandard.strPow_VelocityInRPC = L"70";
		sDetStandard.strPow_PPInRPC = L"40";
		sDetStandard.strPow_RPPInRTC = L"70";
		sDetStandard.strPow_RPPInRPC = L"65";
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"25t����г�"))
	{
		sDetStandard.strPow_VelocityInRTC = L"45";
		sDetStandard.strPow_PPInRTC = L"50";
		sDetStandard.strPow_VelocityInRPC = L"75";
		sDetStandard.strPow_PPInRPC = L"40";
		sDetStandard.strPow_RPPInRTC = L"75";
		sDetStandard.strPow_RPPInRPC = L"65";
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"6600"))
	{
		// ����
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
		{
			sDetStandard.strPow_VelocityInRTC = L"45";
			sDetStandard.strPow_PPInRTC = L"50";
			sDetStandard.strPow_VelocityInRPC = L"70";
			sDetStandard.strPow_PPInRPC = L"40";
			sDetStandard.strPow_RPPInRTC = L"75";
			sDetStandard.strPow_RPPInRPC = L"65";
		}
		// ����ȼ�ϵ����ʹ���
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"60";
			sDetStandard.strPow_PPInRTC = L"45";
			sDetStandard.strPow_VelocityInRPC = L"85";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"70";
			sDetStandard.strPow_RPPInRPC = L"60";
		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"6700"))
	{
		// ����
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
		{
			sDetStandard.strPow_VelocityInRTC = L"55";
			sDetStandard.strPow_PPInRTC = L"45";
			sDetStandard.strPow_VelocityInRPC = L"75";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"70";
			sDetStandard.strPow_RPPInRPC = L"60";
		}
		// ����ȼ�ϵ����ʹ���
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"50";
			sDetStandard.strPow_PPInRTC = L"40";
			sDetStandard.strPow_VelocityInRPC = L"80";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"65";
			sDetStandard.strPow_RPPInRPC = L"60";
		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"6800"))
	{
		// ����
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
		{
			sDetStandard.strPow_VelocityInRTC = L"45";
			sDetStandard.strPow_PPInRTC = L"45";
			sDetStandard.strPow_VelocityInRPC = L"75";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"70";
			sDetStandard.strPow_RPPInRPC = L"60";

		}
		// ����ȼ�ϵ����ʹ���
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"40";
			sDetStandard.strPow_PPInRTC = L"40";
			sDetStandard.strPow_VelocityInRPC = L"85";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"65";
			sDetStandard.strPow_RPPInRPC = L"60";

		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"6900"))
	{
		// ����
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
		{
			sDetStandard.strPow_VelocityInRTC = L"60";
			sDetStandard.strPow_PPInRTC = L"45";
			sDetStandard.strPow_VelocityInRPC = L"85";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"70";
			sDetStandard.strPow_RPPInRPC = L"60";
		}
		// ����ȼ�ϵ����ʹ���
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"40";
			sDetStandard.strPow_PPInRTC = L"40";
			sDetStandard.strPow_VelocityInRPC = L"85";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"65";
			sDetStandard.strPow_RPPInRPC = L"60";
		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"6100"))
	{
		// ����
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
		{
			sDetStandard.strPow_VelocityInRTC = L"40";
			sDetStandard.strPow_PPInRTC = L"45";
			sDetStandard.strPow_VelocityInRPC = L"85";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"70";
			sDetStandard.strPow_RPPInRPC = L"60";
		}
		// ����ȼ�ϵ����ʹ���
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"40";
			sDetStandard.strPow_PPInRTC = L"40";
			sDetStandard.strPow_VelocityInRPC = L"85";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"65";
			sDetStandard.strPow_RPPInRPC = L"60";
		}

	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"6110"))
	{
		// ����
		if (std::wstring::npos != sVehInfo.strFuelTypeCode.find(L"B") ||
			std::wstring::npos != sVehInfo.strFuelType.find(L"����"))
		{
			sDetStandard.strPow_VelocityInRTC = L"55";
			sDetStandard.strPow_PPInRTC = L"45";
			sDetStandard.strPow_VelocityInRPC = L"80";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"70";
			sDetStandard.strPow_RPPInRPC = L"60";
		}
		// ����ȼ�ϵ����ʹ���
		else
		{
			sDetStandard.strPow_VelocityInRTC = L"40";
			sDetStandard.strPow_PPInRTC = L"40";
			sDetStandard.strPow_VelocityInRPC = L"85";
			sDetStandard.strPow_PPInRPC = L"35";
			sDetStandard.strPow_RPPInRTC = L"65";
			sDetStandard.strPow_RPPInRPC = L"60";
		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"6120"))
	{
		sDetStandard.strPow_VelocityInRTC = L"60";
		sDetStandard.strPow_PPInRTC = L"40";
		sDetStandard.strPow_VelocityInRPC = L"90";
		sDetStandard.strPow_PPInRPC = L"35";
		sDetStandard.strPow_RPPInRTC = L"65";
		sDetStandard.strPow_RPPInRPC = L"60";
	}
	// �γ�
	else if (std::wstring::npos != sVehInfo.strVehType.find(L"K33") || std::wstring::npos != sVehInfo.strVehType.find(L"�γ�"))
	{
		// �������߸���
		if (std::wstring::npos!= sVehInfo.strBrand.find(L"����")|| std::wstring::npos!= sVehInfo.strBrand.find(L"����"))
		{
			sDetStandard.strPow_VelocityInRTC = L"65";
			sDetStandard.strPow_PPInRTC = L"35";
			sDetStandard.strPow_VelocityInRPC = L"";
			sDetStandard.strPow_PPInRPC = L"";
			sDetStandard.strPow_RPPInRTC = L"60";
		}
		// ɣ����
		else if (std::wstring::npos!= sVehInfo.strBrand.find(L"ɣ����"))
		{
			sDetStandard.strPow_VelocityInRTC = L"65";
			sDetStandard.strPow_PPInRTC = L"40";
			sDetStandard.strPow_VelocityInRPC = L"";
			sDetStandard.strPow_PPInRPC = L"";
			sDetStandard.strPow_RPPInRTC = L"65";
		}
		else
		{
			sDetStandard.strPow_VelocityInRTC = strDefaultPow_VelocityInRTC;
			sDetStandard.strPow_PPInRTC = strDefaultPow_PPInRTC;
			sDetStandard.strPow_VelocityInRPC = strDefaultPow_VelocityInRPC;
			sDetStandard.strPow_PPInRPC = strDefaultPow_PPInRPC;
			sDetStandard.strPow_RPPInRTC = strDefaultPow_RPPInRTC;
			sDetStandard.strPow_RPPInRPC = strDefaultPow_RPPInRPC;
		}
	}
	else if (std::wstring::npos != sVehInfo.strVehSeries.find(L"5010") || std::wstring::npos != sVehInfo.strVehSeries.find(L"5020") || std::wstring::npos != sVehInfo.strVehSeries.find(L"5030") || std::wstring::npos != sVehInfo.strVehSeries.find(L"5040"))
	{
		sDetStandard.strPow_VelocityInRTC = L"60";
		sDetStandard.strPow_PPInRTC = L"40";
		sDetStandard.strPow_VelocityInRPC = L"90";
		sDetStandard.strPow_PPInRPC = L"35";
		sDetStandard.strPow_RPPInRTC = L"65";
		sDetStandard.strPow_RPPInRPC = L"60";
	}
	else
	{
		sDetStandard.strPow_VelocityInRTC = strDefaultPow_VelocityInRTC;
		sDetStandard.strPow_PPInRTC = strDefaultPow_PPInRTC;
		sDetStandard.strPow_VelocityInRPC = strDefaultPow_VelocityInRPC;
		sDetStandard.strPow_PPInRPC = strDefaultPow_PPInRPC;
		sDetStandard.strPow_RPPInRTC = strDefaultPow_RPPInRTC;
		sDetStandard.strPow_RPPInRPC = strDefaultPow_RPPInRPC;
	}
}

void CStandard::GetEngine(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// TODO : δ֪��ֵ
	// ����_����������[kW]
	sDetStandard.strPow_EnginePower = L"";
	// ����_����ת��[r/min]
	sDetStandard.strPow_IdleRev = L"";
	// ����_����ѹ��[MPa]
	sDetStandard.strPow_OP = L"";
}

void CStandard::GetFuelCon(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetFuelCon_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetFuelCon_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetFuelCon_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ԭ���涨110%
	// ����_�ٹ����ͺ�[L/100km]
	sDetStandard.strPow_FuelCon = L"7.0";
}

void CStandard::GetFuelCon_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ԭ���涨110%
	// ����_�ٹ����ͺ�[L/100km]
	sDetStandard.strPow_FuelCon = L"7.0";
}

void CStandard::GetFuelCon_18566(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	const CString strVehType = sVehInfo.strVehType.c_str();
	const CString strVehTypeCode = sVehInfo.strVehTypeCode.c_str();
	const int nVehMass = _wtoi(sVehInfo.strMaximumTotalMass.c_str());
	const int nVehLen = _wtoi(sVehInfo.strVehLength.c_str());
	const bool bIsGasCar = std::wstring::npos != sVehInfo.strFuelType.find(L"����");
	const bool bIsPassengerCar = L"1"==sVehInfo.strIsPassengerVeh;
	const bool bIsAdvancedPassenger = std::wstring::npos != sVehInfo.strPasVehTypeClass.find(L"�߼�");
	CString strFuelConStd(L"");
	if(bIsPassengerCar) // �ͳ�
	{
		if(12000<nVehLen)
		{
			strFuelConStd = bIsAdvancedPassenger? L"22.3":L"20.3";
		}
		else if(11000<nVehLen)
		{
			strFuelConStd = bIsAdvancedPassenger? L"20.1":L"18.3";
		}
		else if(10000<nVehLen)
		{
			strFuelConStd = bIsAdvancedPassenger? L"19.4":L"17.6";
		}
		else if(9000<nVehLen)
		{
			strFuelConStd = bIsAdvancedPassenger? L"17.8":L"16.7";
		}
		else if(8000<nVehLen)
		{
			strFuelConStd = bIsAdvancedPassenger? L"16.4":L"15.5";
		}
		else if(7000<nVehLen)
		{
			strFuelConStd = bIsAdvancedPassenger? L"15.3":L"14.1";
		}
		else if(6000<nVehLen)
		{
			strFuelConStd = bIsAdvancedPassenger? L"13.1":L"11.5";
		}
		else
		{
			strFuelConStd = bIsAdvancedPassenger? L"11.3":L"9.5";
		}
	}
	else // �������ҳ�
	{
		if(-1 != strVehType.Find(L"���") && -1 == strVehTypeCode.Find(L"Q"))	 //�ų������ǣ����
		{
			if(27000>=nVehMass)
			{
				strFuelConStd = L"42.9";
			}
			else if(35000>=nVehMass)
			{
				strFuelConStd = L"43.9";
			}
			else if(43000>=nVehMass)
			{
				strFuelConStd = L"46.2";
			}
			else if(49000>=nVehMass)
			{
				strFuelConStd = L"47.3";
			}
		}
		else
		{
			if(3500>=nVehMass || 31000<nVehMass)
			{
				// ��������ֵ
				strFuelConStd = L"";
			}
			else if(4000>=nVehMass)
			{
				strFuelConStd = L"10.6";
			}
			else if(5000>=nVehMass)
			{
				strFuelConStd = L"11.3";
			}
			else if(6000>=nVehMass)
			{
				strFuelConStd = L"12.6";
			}
			else if(7000>=nVehMass)
			{
				strFuelConStd = L"13.5";
			}
			else if(8000>=nVehMass)
			{
				strFuelConStd = L"14.9";
			}
			else if(9000>=nVehMass)
			{
				strFuelConStd = L"16.1";
			}
			else if(10000>=nVehMass)
			{
				strFuelConStd = L"16.9";
			}
			else if(11000>=nVehMass)
			{
				strFuelConStd = L"18.0";
			}
			else if(12000>=nVehMass)
			{
				strFuelConStd = L"19.1";
			}
			else if(13000>=nVehMass)
			{
				strFuelConStd = L"20.0";
			}
			else if(14000>=nVehMass)
			{
				strFuelConStd = L"20.9";
			}
			else if(15000>=nVehMass)
			{
				strFuelConStd = L"21.6";
			}
			else if(16000>=nVehMass)
			{
				strFuelConStd = L"22.7";
			}
			else if(17000>=nVehMass)
			{
				strFuelConStd = L"23.6";
			}
			else if(18000>=nVehMass)
			{
				strFuelConStd = L"24.4";
			}
			else if(19000>=nVehMass)
			{
				strFuelConStd = L"25.4";
			}
			else if(20000>=nVehMass)
			{
				strFuelConStd = L"26.1";
			}
			else if(21000>=nVehMass)
			{
				strFuelConStd = L"27.0";
			}
			else if(22000>=nVehMass)
			{
				strFuelConStd = L"27.7";
			}
			else if(23000>=nVehMass)
			{
				strFuelConStd = L"28.2";
			}
			else if(24000>=nVehMass)
			{
				strFuelConStd = L"28.8";
			}
			else if(25000>=nVehMass)
			{
				strFuelConStd = L"29.5";
			}
			else if(26000>=nVehMass)
			{
				strFuelConStd = L"30.1";
			}
			else if(27000>=nVehMass)
			{
				strFuelConStd = L"30.8";
			}
			else if(28000>=nVehMass)
			{
				strFuelConStd = L"31.7";
			}
			else if(29000>=nVehMass)
			{
				strFuelConStd = L"32.6";
			}
			else if(30000>=nVehMass)
			{
				strFuelConStd = L"33.7";
			}
			else if(31000>=nVehMass)
			{
				strFuelConStd = L"34.6";
			}
		}
	}

	// ���ͳ���ֵ�ǲ��ͳ�1.15��(ȡֵ����������Բ����С�����һλ)��
	if(bIsGasCar)
	{
		if(L"" != strFuelConStd)
		{
			float fFuelConStd((float)_wtof(strFuelConStd));
			fFuelConStd *= 1.15f;
			fFuelConStd =  CNHCommonAPI::round(fFuelConStd * 10.0f) / 10.0f;
			strFuelConStd.Format(L"%.1f", fFuelConStd);
		}
	}
	sDetStandard.strPow_FuelCon = strFuelConStd;
	sDetStandard.strPow_FuelConV = bIsAdvancedPassenger?L"60.0":L"50.0";
}

void CStandard::GetDireGearAccTime(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetDireGearAccTime_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetDireGearAccTime_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetDireGearAccTime_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ����_ֱ�ӵ�����ʱ��[ms]
	sDetStandard.strPow_DireGearAccTime = L"";
}

void CStandard::GetDireGearAccTime_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ����_ֱ�ӵ�����ʱ��[ms]
	sDetStandard.strPow_DireGearAccTime = L"";
}

void CStandard::GetMomentum(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetMomentum_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetMomentum_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetMomentum_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ת��������ת������ֵ[o](��ʱ��GB7258-2012��ֵҪ��

	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// �����ֻ�����
		sDetStandard.strSte_Momentum = L"35.0";
	} 
	else if (!sVehInfo.strMaximumVelocity.empty() && _wtoi(sVehInfo.strMaximumVelocity.c_str()) < 100)//�����С��100kw/h
	{
		sDetStandard.strSte_Momentum =L"25.0";
	}       
	else //����ٴ��ڵ���100kw/h������������
	{
		sDetStandard.strSte_Momentum = L"15.0";
	}
	// ת���̲�����[N]
	sDetStandard.strSte_HandWheCtrlForce = L"150";
}

void CStandard::GetMomentum_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ת��������ת������ֵ[o](��ʱ��GB18565-2001��ֵҪ��

	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
	{
		// �����ֻ�����
		sDetStandard.strSte_Momentum = L"45.0";
	}
	else if (!sVehInfo.strMaximumVelocity.empty() && _wtoi(sVehInfo.strMaximumVelocity.c_str()) < 100)//�����С��100kw/h
	{
		sDetStandard.strSte_Momentum =L"30.0";
	}
	else //����ٴ��ڵ���100kw/h������������
	{
		sDetStandard.strSte_Momentum = L"20.0";
	}
	// ת���̲�����[N]
	sDetStandard.strSte_HandWheCtrlForce = L"150";
}

void CStandard::GetMomentum_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	if (_wtoi(sVehInfo.strMaximumVelocity.c_str()) < 100) // �����С��100km/h
	{
		sDetStandard.strSte_Momentum =L"25.0";
	}
	else
	{
		sDetStandard.strSte_Momentum = L"15.0";
	}
}

void CStandard::GetWheAli(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetWheAli_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetWheAli_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetWheAli_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ����ǰ����ֵ[mm]
	sDetStandard.strSte_ToeIn = L"5.0";
	// ������������[o](��)
	sDetStandard.strSte_Camber = L"30.0";
	// ����������ֵ[o](��)
	sDetStandard.strSte_KPI = L"10.0";
	// ����������ֵ[o](��)
	sDetStandard.strSte_Caster = L"10.0";
}

void CStandard::GetWheAli_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ����ǰ����ֵ[mm]
	sDetStandard.strSte_ToeIn = L"5.0";
	// ������������[o](��)
	sDetStandard.strSte_Camber = L"30.0";
	// ����������ֵ[o](��)
	sDetStandard.strSte_KPI = L"10.0";
	// ����������ֵ[o](��)
	sDetStandard.strSte_Caster = L"10.0";
}

void CStandard::GetSteAngle(const SVehInfo& sVehInfo, SDetStandard& sDetStandard, const bool bGB7258)
{
	if (bGB7258)
	{
		GetSteAngle_7258(sVehInfo, sDetStandard);
	}
	else
	{
		GetSteAngle_18565(sVehInfo, sDetStandard);
	}
}

void CStandard::GetSteAngle_7258(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ������ת��[o](��)
	sDetStandard.strSte_LWheLSteAngle = L"20.0";
	// ������ת��[o](��)
	sDetStandard.strSte_LWheRSteAngle = L"20.0";
	// ������ת��[o](��)
	sDetStandard.strSte_RWheLSteAngle = L"20.0";
	// ������ת��[o](��)
	sDetStandard.strSte_RWheRSteAngle = L"20.0";
}

void CStandard::GetSteAngle_18565(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ������ת��[o](��)
	sDetStandard.strSte_LWheLSteAngle = L"20.0";
	// ������ת��[o](��)
	sDetStandard.strSte_LWheRSteAngle = L"20.0";
	// ������ת��[o](��)
	sDetStandard.strSte_RWheLSteAngle = L"20.0";
	// ������ת��[o](��)
	sDetStandard.strSte_RWheRSteAngle = L"20.0";
}

void CStandard::GetDimension(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// ��ע�ᳵ
	if (std::wstring::npos!=sVehInfo.strUsePhase.find(L"�³�"))
	{
		sDetStandard.strApp_DimRE = L"1";
		sDetStandard.strApp_DimAE = L"50";
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M") || std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
		{
			// �����ֻ�����
			sDetStandard.strApp_DimRE = L"3";
			sDetStandard.strApp_DimAE = L"50";
		} 
	}
	else
	{
		sDetStandard.strApp_DimRE = L"2";
		sDetStandard.strApp_DimAE = L"100";
	}

	COleDateTime odtProductionDate;
	odtProductionDate.ParseDateTime(sVehInfo.strProductionDate.c_str());
	const COleDateTime odtGB1589_2004(2004, 10, 1, 0, 0, 0);
	const COleDateTime odtGB1589_2016(2017, 1, 1, 0, 0, 0);

	//if (odtProductionDate < odtGB1589_2004)
	//{
	//	// ����ΪGB1589-1989��׼
	//	sDetStandard.strApp_DimWid_UpperLimit = L"2500";
	//	sDetStandard.strApp_DimHei_UpperLimit = L"4000";

	//	if (std::wstring::npos!=sVehInfo.strVehType.find(L"����")
	//		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"H")
	//		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K"))
	//	{
	//		sDetStandard.strApp_DimLen_UpperLimit = L"12000";
	//	}
	//	else if (std::wstring::npos!=sVehInfo.strVehType.find(L"���½�"))
	//	{
	//		sDetStandard.strApp_DimLen_UpperLimit = L"18000";
	//	}
	//	else if (std::wstring::npos!=sVehInfo.strVehType.find(L"˫�½�"))
	//	{
	//		sDetStandard.strApp_DimLen_UpperLimit = L"23000";
	//	}
	//	else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B"))
	//	{
	//		sDetStandard.strApp_DimLen_UpperLimit = L"16500";
	//	}
	//	else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G"))
	//	{
	//		sDetStandard.strApp_DimLen_UpperLimit = L"20000";
	//	}
	//	else
	//	{
	//		sDetStandard.strApp_DimLen_UpperLimit = L"12000";
	//	}
	//}
	//else if (odtProductionDate < odtGB1589_2016)
	sDetStandard.strApp_DimWid_UpperLimit = L"2550";
	sDetStandard.strApp_DimHei_UpperLimit = L"4000";

	if (odtProductionDate < odtGB1589_2016)
	{
		// ����ΪGB1589-2004, GB7258-2004��׼
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M"))
		{
			// Ħ�г�
			if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M21"))
			{
				// ��ͨ����Ħ�г�
				sDetStandard.strApp_DimLen_UpperLimit = L"2500";
				sDetStandard.strApp_DimWid_UpperLimit = L"1000";
				sDetStandard.strApp_DimHei_UpperLimit = L"1400";
			}
			else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M15"))
			{
				// ������Ħ�г�
				sDetStandard.strApp_DimLen_UpperLimit = L"2700";
				sDetStandard.strApp_DimWid_UpperLimit = L"1750";
				sDetStandard.strApp_DimHei_UpperLimit = L"1400";
			}
			else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M11")
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M13")
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M14"))
			{
				// ������Ħ�г�
				sDetStandard.strApp_DimLen_UpperLimit = L"3500";
				sDetStandard.strApp_DimWid_UpperLimit = L"1500";
				sDetStandard.strApp_DimHei_UpperLimit = L"2000";
			}
			else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M22"))
			{
				// ������Ħ�г�
				sDetStandard.strApp_DimLen_UpperLimit = L"2000";
				sDetStandard.strApp_DimWid_UpperLimit = L"800";
				sDetStandard.strApp_DimHei_UpperLimit = L"1100";
			}
			else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M12"))
			{
				// ���������Ħ�г�
				sDetStandard.strApp_DimLen_UpperLimit = L"2000";
				sDetStandard.strApp_DimWid_UpperLimit = L"1000";
				sDetStandard.strApp_DimHei_UpperLimit = L"1100";
			}
			else
			{
				// ȱʧ
				sDetStandard.strApp_DimLen_UpperLimit = L"2500";
				sDetStandard.strApp_DimWid_UpperLimit = L"1000";
				sDetStandard.strApp_DimHei_UpperLimit = L"1400";
			}
		}
		else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
		{
			// ��������
			sDetStandard.strApp_DimLen_UpperLimit = L"4600";
			sDetStandard.strApp_DimWid_UpperLimit = L"1600";
			sDetStandard.strApp_DimHei_UpperLimit = L"2000";

			if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"01"))
			{
				sDetStandard.strApp_DimLen_UpperLimit = L"5200";
				sDetStandard.strApp_DimWid_UpperLimit = L"1800";
				sDetStandard.strApp_DimHei_UpperLimit = L"2200";
			}
		}
		else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"T"))
		{
			// �������������
			if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"T11")
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"T21"))
			{
				// ��ʽ�������������
				sDetStandard.strApp_DimLen_UpperLimit = L"10000";
				sDetStandard.strApp_DimWid_UpperLimit = L"2500";
				sDetStandard.strApp_DimHei_UpperLimit = L"3000";
				if (_wtoi(sVehInfo.strRatedPower.c_str()) >= 58)
				{
					// ����ʴ���58kw����ʽ������������
					sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					sDetStandard.strApp_DimHei_UpperLimit = L"3500";
				}
			}
			else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"T22")
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"T23"))
			{
				// �ַ��������������
				sDetStandard.strApp_DimLen_UpperLimit = L"5000";
				sDetStandard.strApp_DimWid_UpperLimit = L"1700";
				sDetStandard.strApp_DimHei_UpperLimit = L"2200";
			}
			else
			{
				// ȱʧ
				sDetStandard.strApp_DimLen_UpperLimit = L"10000";
				sDetStandard.strApp_DimWid_UpperLimit = L"2500";
				sDetStandard.strApp_DimHei_UpperLimit = L"3000";
			}
		}
		else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // ���Ͱ�ҳ�
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // ���Ͱ�ҳ�
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // ���Ͱ�ҳ�
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G1") // ����ȫ�ҳ�
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G2") // ����ȫ�ҳ�
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G3") // ����ȫ�ҳ�
			)
		{
			// �ҳ�
			if (std::wstring::npos!=sVehInfo.strVehType.find(L"������"))
			{
				// ������ҳ�
				sDetStandard.strApp_DimLen_UpperLimit = L"8000";
				sDetStandard.strApp_DimWid_UpperLimit = L"2500";
				sDetStandard.strApp_DimHei_UpperLimit = L"4000";
			}
			else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // ���Ͱ�ҳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // ���Ͱ�ҳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // ���Ͱ�ҳ�
				)
			{
				// ��ҳ�
				if (sVehInfo.strAxleNumber == L"1")
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"8600";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				else if (sVehInfo.strAxleNumber == L"2")
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"10000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";

					if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"09")
						|| std::wstring::npos!=sVehInfo.strVehType.find(L"��װ��")
						|| std::wstring::npos!=sVehInfo.strVehType.find(L"��ʽ")
						|| std::wstring::npos!=sVehInfo.strVehType.find(L"��ʽ"))
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"13000";
					}
				}
				else if (sVehInfo.strAxleNumber == L"3")
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"13000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";

					if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"10"))
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"14600";
					}
				}
				else
				{
					// �����ҳ�
					if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 10000)
					{
						// ��������������10000kg 
						sDetStandard.strApp_DimLen_UpperLimit = L"7000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2500";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
					else
					{
						// ������������>10000kg 
						sDetStandard.strApp_DimLen_UpperLimit = L"8000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2500";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
				}

				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"07"))
				{
					if (sVehInfo.strAxleNumber == L"1" || sVehInfo.strAxleNumber == L"2" || sVehInfo.strAxleNumber == L"3")
					{
						sDetStandard.strApp_DimWid_UpperLimit = L"3000";
					}
				}
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"08"))
				{
					//������
					if (sVehInfo.strAxleNumber == L"1" || sVehInfo.strAxleNumber == L"2" || sVehInfo.strAxleNumber == L"3")
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"";
					}
				}
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"12"))
				{
					if (sVehInfo.strAxleNumber == L"1" || sVehInfo.strAxleNumber == L"2" || sVehInfo.strAxleNumber == L"3")
					{
						sDetStandard.strApp_DimWid_UpperLimit = L"3000";
					}
				}
			}
			else
			{
				// �����ҳ�
				if (_wtoi(sVehInfo.strMaximumTotalMass.c_str()) <= 10000)
				{
					// ��������������10000kg 
					sDetStandard.strApp_DimLen_UpperLimit = L"7000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				else
				{
					// ������������>10000kg 
					sDetStandard.strApp_DimLen_UpperLimit = L"8000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
			}
		}
		else
		{
			if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K1")	  // ���Ϳͳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K2")// ���Ϳͳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K3")// С�Ϳͳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K4")// ΢�Ϳͳ�
				)
			{
				// �ͳ�
				if ((L"1"==sVehInfo.strIsPassengerVeh && _wtoi(sVehInfo.strRatedPassengerCapacity.c_str())<=9)
					|| _wtoi(sVehInfo.strAxleNumber.c_str())==2)
				{
					// ���ó�������ͳ�
					sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				else if (sVehInfo.strAxleNumber == L"3")
				{
					// ����ͳ�
					sDetStandard.strApp_DimLen_UpperLimit = L"13700";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				else
				{
					// ���½ӿͳ�
					sDetStandard.strApp_DimLen_UpperLimit = L"18000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}

				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"06"))
				{
					sDetStandard.strApp_DimHei_UpperLimit = L"4200";
				}
			}
			else if (std::wstring::npos!=sVehInfo.strVehType.find(L"���ٻ���")
				|| _wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
			{
				// �����Ƴ���С��70km/h�Ļ���
				sDetStandard.strApp_DimLen_UpperLimit = L"6000";
				sDetStandard.strApp_DimWid_UpperLimit = L"2000";
				sDetStandard.strApp_DimHei_UpperLimit = L"2500";
			}
			else
			{
				// �������������ǣ����
				const int nMaximumTotalMass = _wtoi(sVehInfo.strMaximumTotalMass.c_str());
				if (_wtoi(sVehInfo.strAxleNumber.c_str()) == 2)
				{
					// ����
					if (nMaximumTotalMass <= 3500)
					{
						// ��������������3500kg 
						sDetStandard.strApp_DimLen_UpperLimit = L"6000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2500";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
					else if (nMaximumTotalMass>3500 && nMaximumTotalMass<=8000)
					{
						// ������������ >3500kg���ҡ�8000kg 
						sDetStandard.strApp_DimLen_UpperLimit = L"7000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2500";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";

						if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"04"))
						{
							CString strTemp;
							strTemp.Format(L"%d",_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) + 1000);
							sDetStandard.strApp_DimLen_UpperLimit = strTemp;
						}
					}
					else if (nMaximumTotalMass>8000 && nMaximumTotalMass<=12000)
					{
						// ������������ >8000kg���ҡ�12000kg 
						sDetStandard.strApp_DimLen_UpperLimit = L"8000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2500";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";

						if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"04"))
						{
							CString strTemp;
							strTemp.Format(L"%d",_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) + 1000);
							sDetStandard.strApp_DimLen_UpperLimit = strTemp;
						}
					}
					else
					{
						// ������������ >12000kg 
						sDetStandard.strApp_DimLen_UpperLimit = L"9000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2500";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";

						if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"04"))
						{
							CString strTemp;
							strTemp.Format(L"%d",_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) + 1000);
							sDetStandard.strApp_DimLen_UpperLimit = strTemp;
						}
					}
				}
				else if (sVehInfo.strAxleNumber == L"3")
				{
					// ����
					if (nMaximumTotalMass <= 20000)
					{
						// ��������������20000kg
						sDetStandard.strApp_DimLen_UpperLimit = L"11000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2500";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
					else
					{
						// ������������ >20000kg
						sDetStandard.strApp_DimLen_UpperLimit = L"12000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2500";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
				}
				else if (sVehInfo.strAxleNumber == L"4")
				{
					// ����
					sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";

					if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"06"))
					{
						sDetStandard.strApp_DimHei_UpperLimit = L"4200";
					}
				}
				else
				{
					// ȱʧ
					sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2500";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}

				//��������
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"02"))
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"";//���վҪ���޳��������޵ĳ�������Ϊ��
				}
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"03"))
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"13000";
				}
				
			}
		}
		//��������,2017��01��01��ǰ
		/*if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"04"))
		{
			CString strTemp;
			strTemp.Format(L"%d",_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) + 1000);
			sDetStandard.strApp_DimLen_UpperLimit = strTemp;
		}*/
		/*if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"01"))
		{
			if(_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) < 5200)
			{
				sDetStandard.strApp_DimLen_UpperLimit = L"5200";
			}
			if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 1800)
			{
				sDetStandard.strApp_DimWid_UpperLimit = L"1800";
			}
			if(_wtoi(sDetStandard.strApp_DimHei_UpperLimit.c_str()) < 2200)
			{
				sDetStandard.strApp_DimHei_UpperLimit = L"2200";
			}
		}*/
		//if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"02"))
		//{
		//	//������
		//	//sDetStandard.strApp_DimLen_UpperLimit = L"22000";  //���վҪ���޳��������޵ĳ�������Ϊ22000	 change by pqw 20180314
		//	sDetStandard.strApp_DimLen_UpperLimit = L"";	//���վҪ���޳��������޵ĳ�������Ϊ��	 change by ZhongMH 20180321
		//}
		//if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"03"))
		//{
		//	if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 2600)
		//	{
		//		sDetStandard.strApp_DimWid_UpperLimit = L"2600";
		//	}
		//}
		if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"05"))
		{
			if((std::wstring::npos!=sVehInfo.strVehType.find(L"���ٻ���")
				|| _wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
			{
			}
			else
			{
				sDetStandard.strApp_DimWid_UpperLimit = L"2550";
			}
		}
		/*if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"07"))
		{
			{
				sDetStandard.strApp_DimWid_UpperLimit = L"3000";
			}
		}*/
		//if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"08"))
		//{
		//	//������
		//	//sDetStandard.strApp_DimLen_UpperLimit = L"22000";	//���վҪ���޳��������޵ĳ�������Ϊ22000	 change by pqw 20180314
		//	sDetStandard.strApp_DimLen_UpperLimit = L"";	//���վҪ���޳��������޵ĳ�������Ϊ��	 change by ZhongMH 20180321
		//}
		/*if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"09"))
		{
			if(_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) < 13000)
			{
				sDetStandard.strApp_DimLen_UpperLimit = L"13000";
			}
		}*/
		/*if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"10"))
		{
			if(_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) < 14600)
			{
				sDetStandard.strApp_DimLen_UpperLimit = L"14600";
			}
		}*/
		/*if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"11"))
		{
			if(_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) < 18100)
			{
				sDetStandard.strApp_DimLen_UpperLimit = L"18100";
			}
		}*/
		/*if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"12"))
		{
			if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 3000)
			{
				sDetStandard.strApp_DimWid_UpperLimit = L"3000";
			}
		}*/
		/*if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"13"))
		{
			if(_wtoi(sDetStandard.strApp_DimHei_UpperLimit.c_str()) < 4200)
			{
				sDetStandard.strApp_DimHei_UpperLimit = L"4200";
			}
		}*/
		/*if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"14"))
		{
			if(_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) < 13950)
			{
				sDetStandard.strApp_DimLen_UpperLimit = L"13950";
			}
		}*/
	}
	else
	{
		// ��դʽ������ʽ��ƽ��ʽ����жʽ����
		const bool bSpecialTruck = (std::wstring::npos!=sVehInfo.strVehType.find(L"����")
			&& (std::wstring::npos!=sVehInfo.strVehType.find(L"��դ")
			|| std::wstring::npos!=sVehInfo.strVehType.find(L"��")
			|| std::wstring::npos!=sVehInfo.strVehType.find(L"��ж")));
		// ��դʽ������ʽ��ƽ��ʽ����жʽ��ҳ�
		const bool bSpecialTractor = (std::wstring::npos!=sVehInfo.strVehType.find(L"��ҳ�")
			&& (std::wstring::npos!=sVehInfo.strVehType.find(L"��դ")
			|| std::wstring::npos!=sVehInfo.strVehType.find(L"��")
			|| std::wstring::npos!=sVehInfo.strVehType.find(L"��ж"))
			&& std::wstring::npos==sVehInfo.strVehType.find(L"��ƽ��")); //��ƽ���ҳ�����Ϊ������ҳ�
		if(bSpecialTruck || bSpecialTractor) // ִ��GB1589-2016������1��ֵ
		{
			sDetStandard.strApp_DimWid_UpperLimit = L"2550";
			sDetStandard.strApp_DimHei_UpperLimit = L"4000";
			if(bSpecialTruck)
			{
				const int nMaximumTotalMass = _wtoi(sVehInfo.strMaximumTotalMass.c_str());
				switch(_wtoi(sVehInfo.strAxleNumber.c_str()))
				{
				case 2:
					{
						if(3500>=nMaximumTotalMass)
						{
							sDetStandard.strApp_DimLen_UpperLimit = L"6000";
						}
						else if(8000>=nMaximumTotalMass)
						{
							sDetStandard.strApp_DimLen_UpperLimit = L"7000";
						}
						else if(12000>=nMaximumTotalMass)
						{
							sDetStandard.strApp_DimLen_UpperLimit = L"8000";
						}
						else
						{
							sDetStandard.strApp_DimLen_UpperLimit = L"9000";
						}
					}
					break;
				case 3:
					{
						if(20000>=nMaximumTotalMass)
						{
							sDetStandard.strApp_DimLen_UpperLimit = L"11000";
						}
						else
						{
							sDetStandard.strApp_DimLen_UpperLimit = L"12000";
						}
					}
					break;
				case 4:
					{
						if(L"2"==sVehInfo.strFrontAxleNumber || L"2"==sVehInfo.strSteShaftNumber)
						{
							sDetStandard.strApp_DimLen_UpperLimit = L"12000";
						}
						else
						{
							// ȱʡ
							//sDetStandard.strApp_DimLen_UpperLimit = L"";
							//sDetStandard.strApp_DimWid_UpperLimit = L"";
							//sDetStandard.strApp_DimHei_UpperLimit = L"";
							sDetStandard.strApp_DimLen_UpperLimit = L"12000";//4���ƽ�����Ӧ�ö���˫ת���(һ����ת������),ȱʡ��ҲĬ��12000
						}
					}
					break;
				default:
					{
						// ȱʡ
						sDetStandard.strApp_DimLen_UpperLimit = L"";
						sDetStandard.strApp_DimWid_UpperLimit = L"";
						sDetStandard.strApp_DimHei_UpperLimit = L"";
					}
					break;
				}
			}

			if(bSpecialTractor)
			{
				switch(_wtoi(sVehInfo.strAxleNumber.c_str()))
				{
				case 1: 
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"8600";
					}
					break;
				case 2: 
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"10000";
					}
					break;
				case 3: 
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"13000";
					}
					break;
				default:
					{
						// ȱʡ
						sDetStandard.strApp_DimLen_UpperLimit = L"";
						sDetStandard.strApp_DimWid_UpperLimit = L"";
						sDetStandard.strApp_DimHei_UpperLimit = L"";
					}
					break;
				}

			}
		}
		else // ִ��GB1589-2016������2��ֵ
		{
			if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
			{
				// ��������
				sDetStandard.strApp_DimLen_UpperLimit = L"4600";
				sDetStandard.strApp_DimWid_UpperLimit = L"1600";
				sDetStandard.strApp_DimHei_UpperLimit = L"2000";
				// �����÷�����ת���ɴ����ᴫ�ݶ��������м�ʻ���Ҽ�ʻԱ���κ��������Ʒ���ÿռ�ʱ���������������ߵ���ֵ�ֱ�Ϊ5200mm��1800mm��2200 mm
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"20"))
				{
					if(_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) < 5200)
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"5200";
					}
					if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 1800)
					{
						sDetStandard.strApp_DimWid_UpperLimit = L"1800";
					}
					if(_wtoi(sDetStandard.strApp_DimHei_UpperLimit.c_str()) < 2200)
					{
						sDetStandard.strApp_DimHei_UpperLimit = L"2200";
					}
				}
			}
			else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // ���Ͱ�ҳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // ���Ͱ�ҳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // ���Ͱ�ҳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G1") // ����ȫ�ҳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G2") // ����ȫ�ҳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G3") // ����ȫ�ҳ�
				)
			{
				// �ҳ�
				if (std::wstring::npos!=sVehInfo.strVehType.find(L"������"))
				{
					// ������ҳ�
					sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2550";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // ���Ͱ�ҳ�
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // ���Ͱ�ҳ�
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // ���Ͱ�ҳ�
					)
				{

					sDetStandard.strApp_DimLen_UpperLimit = L"13750";
					sDetStandard.strApp_DimWid_UpperLimit = L"2550";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				else
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2550";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				// ��س���������ֵΪ26000mm
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"18"))
				{
					if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 2600)
					{
						sDetStandard.strApp_DimWid_UpperLimit = L"2600";
					}
				}

				//����45 ft ��װ��İ�ҳ����������ֵΪ13 950 mm
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"14"))
				{
					if(_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) < 13950)
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"13950";
					}
				}

				//1589-2016 �� 4. 7.1 ��ƽ��ר�ð�ҳ���Ҫ��
				//��ƽ��ר�ð�ҳ�Ӧ����4.1��4.6 ��Ҫ�󣬵�������������ֵΪ3 000 mm
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"15"))
				{
					if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 3000)
					{
						sDetStandard.strApp_DimWid_UpperLimit = L"3000";
					}
				}
			}
			else
			{
				if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K1")	  // ���Ϳͳ�
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K2")// ���Ϳͳ�
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K3")// С�Ϳͳ�
					|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K4")// ΢�Ϳͳ�
					)
				{
					// �ͳ�
					if ((L"1"==sVehInfo.strIsPassengerVeh && _wtoi(sVehInfo.strRatedPassengerCapacity.c_str())<=9)
						|| _wtoi(sVehInfo.strAxleNumber.c_str())==2)
					{
						// ���ó�������ͳ�
						sDetStandard.strApp_DimLen_UpperLimit = L"12000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2550";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
					else if (sVehInfo.strAxleNumber == L"3")
					{
						// ����ͳ�
						sDetStandard.strApp_DimLen_UpperLimit = L"13700";
						sDetStandard.strApp_DimWid_UpperLimit = L"2550";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
					else
					{
						// ���½ӿͳ�
						sDetStandard.strApp_DimLen_UpperLimit = L"18000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2550";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
					// ������ʻ��˫��ͳ����������ֵΪ4200mm
					if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"21"))
					{
						if(_wtoi(sDetStandard.strApp_DimHei_UpperLimit.c_str()) < 4200)
						{
							sDetStandard.strApp_DimHei_UpperLimit = L"4200";
						}
					}
				}
				else if (std::wstring::npos!=sVehInfo.strVehType.find(L"���ٻ���")
					|| _wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
				{
					// �����Ƴ���С��70km/h�Ļ���
					sDetStandard.strApp_DimLen_UpperLimit = L"6000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2000";
					sDetStandard.strApp_DimHei_UpperLimit = L"2500";
				}
				else if (std::wstring::npos!=sVehInfo.strVehType.find(L"����")
					|| std::wstring::npos!=sVehInfo.strVehType.find(L"���ǣ��")
					|| std::wstring::npos!=sVehInfo.strVehType.find(L"�������䳵"))//�������䳵
				{
					// ���������ǣ����
					sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2550";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					// ��س���������ֵΪ26000mm
					if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"18"))
					{
						if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 2600)
						{
							sDetStandard.strApp_DimWid_UpperLimit = L"2600";
						}
					}
					
					if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"19"))
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"";//ר����ҵ������������ֵҪ�����ã���Ӧ������ر�׼Ҫ��
					}
				}
				else
				{
					// ȱʡ
					sDetStandard.strApp_DimLen_UpperLimit = L"";
					sDetStandard.strApp_DimWid_UpperLimit = L"";
					sDetStandard.strApp_DimHei_UpperLimit = L"";

					// �����г�
					if (std::wstring::npos!=sVehInfo.strVehType.find(L"���ó��г�"))
					{
						// ���������ǣ����
						sDetStandard.strApp_DimLen_UpperLimit = L"14500";
						sDetStandard.strApp_DimWid_UpperLimit = L"2550";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
					if (std::wstring::npos!=sVehInfo.strVehType.find(L"�½��г�"))
					{
						// ���������ǣ����
						sDetStandard.strApp_DimLen_UpperLimit = L"17100";
						sDetStandard.strApp_DimWid_UpperLimit = L"2550";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
					if (std::wstring::npos!=sVehInfo.strVehType.find(L"�����г�"))
					{
						// ���������ǣ����
						sDetStandard.strApp_DimLen_UpperLimit = L"20000";
						sDetStandard.strApp_DimWid_UpperLimit = L"2550";
						sDetStandard.strApp_DimHei_UpperLimit = L"4000";
					}
					// ��س���������ֵΪ2600mm
					if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"18"))
					{
						if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 2600)
						{
							sDetStandard.strApp_DimWid_UpperLimit = L"2600";
						}
					}
				}
			}
		}

		//4.7.2�����������ϳ����������ó����������ػ�������ר��ΰҵ�ҵ�Ҫ��
		//1589-2016	4.7.2.1 ��5Ҫ��
		if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"16"))
		{
			if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 2550)
			{
				sDetStandard.strApp_DimWid_UpperLimit= L"2550";
			}	

			if(_wtoi(sDetStandard.strApp_DimHei_UpperLimit.c_str()) < 4000)
			{
				sDetStandard.strApp_DimHei_UpperLimit= L"4000";
			}	
		}

		if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"17"))
		{
			if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 3000)
			{
				sDetStandard.strApp_DimWid_UpperLimit= L"3000";
			}	

			if(_wtoi(sDetStandard.strApp_DimHei_UpperLimit.c_str()) < 4000)
			{
				sDetStandard.strApp_DimHei_UpperLimit= L"4000";
			}	
		}

	}
}

void CStandard::GetDimension_18565_2016(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	sDetStandard.strApp_DimRE = L"2";
	sDetStandard.strApp_DimAE = L"100";


	// ���������ֵ
	sDetStandard.strApp_DimWid_UpperLimit = L"2550";
	sDetStandard.strApp_DimHei_UpperLimit = L"4000";
	// ��դʽ������ʽ��ƽ��ʽ����жʽ����
	const bool bSpecialTruck = (std::wstring::npos!=sVehInfo.strVehType.find(L"����")
		&& (std::wstring::npos!=sVehInfo.strVehType.find(L"��դ")
		|| std::wstring::npos!=sVehInfo.strVehType.find(L"��")
		|| std::wstring::npos!=sVehInfo.strVehType.find(L"��ж")));
	// ��դʽ������ʽ��ƽ��ʽ����жʽ��ҳ�
	const bool bSpecialTractor = (std::wstring::npos!=sVehInfo.strVehType.find(L"��ҳ�")
		&& (std::wstring::npos!=sVehInfo.strVehType.find(L"��դ")
		|| std::wstring::npos!=sVehInfo.strVehType.find(L"��")
		|| std::wstring::npos!=sVehInfo.strVehType.find(L"��ж"))
		&& std::wstring::npos==sVehInfo.strVehType.find(L"��ƽ��")); //��ƽ���ҳ�����Ϊ������ҳ�
	if(bSpecialTruck || bSpecialTractor) // ִ��GB1589-2016������1��ֵ
	{
		sDetStandard.strApp_DimWid_UpperLimit = L"2550";
		sDetStandard.strApp_DimHei_UpperLimit = L"4000";
		if(bSpecialTruck)
		{
			const int nMaximumTotalMass = _wtoi(sVehInfo.strMaximumTotalMass.c_str());
			switch(_wtoi(sVehInfo.strAxleNumber.c_str()))
			{
			case 2:
				{
					if(3500>=nMaximumTotalMass)
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"6000";
					}
					else if(8000>=nMaximumTotalMass)
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"7000";
					}
					else if(12000>=nMaximumTotalMass)
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"8000";
					}
					else
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"9000";
					}
				}
				break;
			case 3:
				{
					if(20000>=nMaximumTotalMass)
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"11000";
					}
					else
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					}
				}
				break;
			case 4:
				{
					if(L"2"==sVehInfo.strSteShaftNumber)
					{
						sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					}
					else
					{
						// ȱʡ
						sDetStandard.strApp_DimLen_UpperLimit = L"";
						sDetStandard.strApp_DimWid_UpperLimit = L"";
						sDetStandard.strApp_DimHei_UpperLimit = L"";
					}
				}
				break;
			default:
				{
					// ȱʡ
					sDetStandard.strApp_DimLen_UpperLimit = L"";
					sDetStandard.strApp_DimWid_UpperLimit = L"";
					sDetStandard.strApp_DimHei_UpperLimit = L"";
				}
				break;
			}
		}

		if(bSpecialTractor)
		{
			switch(_wtoi(sVehInfo.strAxleNumber.c_str()))
			{
			case 1: 
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"8600";
				}
				break;
			case 2: 
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"10000";
				}
				break;
			case 3: 
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"13000";
				}
				break;
			default:
				{
					// ȱʡ
					sDetStandard.strApp_DimLen_UpperLimit = L"";
					sDetStandard.strApp_DimWid_UpperLimit = L"";
					sDetStandard.strApp_DimHei_UpperLimit = L"";
				}
				break;
			}
		}
	}
	else // ִ��GB1589-2016������2��ֵ
	{
		if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N"))
		{
			// ��������
			sDetStandard.strApp_DimLen_UpperLimit = L"4600";
			sDetStandard.strApp_DimWid_UpperLimit = L"1600";
			sDetStandard.strApp_DimHei_UpperLimit = L"2000";
			// �����÷�����ת���ɴ����ᴫ�ݶ��������м�ʻ���Ҽ�ʻԱ���κ��������Ʒ���ÿռ�ʱ���������������ߵ���ֵ�ֱ�Ϊ5200mm��1800mm��2200 mm
			if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"01"))
			{
				if(_wtoi(sDetStandard.strApp_DimLen_UpperLimit.c_str()) < 5200)
				{
					sDetStandard.strApp_DimLen_UpperLimit = L"5200";
				}
				if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 1800)
				{
					sDetStandard.strApp_DimWid_UpperLimit = L"1800";
				}
				if(_wtoi(sDetStandard.strApp_DimHei_UpperLimit.c_str()) < 2200)
				{
					sDetStandard.strApp_DimHei_UpperLimit = L"2200";
				}
			}
		}
		else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // ���Ͱ�ҳ�
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // ���Ͱ�ҳ�
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // ���Ͱ�ҳ�
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G1") // ����ȫ�ҳ�
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G2") // ����ȫ�ҳ�
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G3") // ����ȫ�ҳ�
			)
		{
			// �ҳ�
			if (std::wstring::npos!=sVehInfo.strVehType.find(L"������"))
			{
				// ������ҳ�
				sDetStandard.strApp_DimLen_UpperLimit = L"12000";
				sDetStandard.strApp_DimWid_UpperLimit = L"2550";
				sDetStandard.strApp_DimHei_UpperLimit = L"4000";
			}
			else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // ���Ͱ�ҳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // ���Ͱ�ҳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // ���Ͱ�ҳ�
				)
			{

				sDetStandard.strApp_DimLen_UpperLimit = L"13750";
				sDetStandard.strApp_DimWid_UpperLimit = L"2550";
				sDetStandard.strApp_DimHei_UpperLimit = L"4000";
			}
			else
			{
				sDetStandard.strApp_DimLen_UpperLimit = L"8000";
				sDetStandard.strApp_DimWid_UpperLimit = L"2550";
				sDetStandard.strApp_DimHei_UpperLimit = L"4000";
			}
			// ��س���������ֵΪ26000mm
			if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"03"))
			{
				if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 2600)
				{
					sDetStandard.strApp_DimWid_UpperLimit = L"2600";
				}
			}
			//1589-2016 �� 4. 7.1 ��ƽ��ר�ð�ҳ���Ҫ��
			//��ƽ��ר�ð�ҳ�Ӧ����4.1��4.6 ��Ҫ�󣬵�������������ֵΪ3 000 mm
			if(std::wstring::npos!=sVehInfo.strVehType.find(L"��ƽ��") && std::wstring::npos!=sVehInfo.strVehType.find(L"��ҳ�") && std::wstring::npos!=sVehInfo.strDimFeature.find(L"15"))
			{
				if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 3000)
				{
					sDetStandard.strApp_DimWid_UpperLimit = L"3000";
				}
			}
		}
		else
		{
			if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K1")	  // ���Ϳͳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K2")// ���Ϳͳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K3")// С�Ϳͳ�
				|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"K4")// ΢�Ϳͳ�
				)
			{
				// �ͳ�
				if ((L"1"==sVehInfo.strIsPassengerVeh && _wtoi(sVehInfo.strRatedPassengerCapacity.c_str())<=9)
					|| _wtoi(sVehInfo.strAxleNumber.c_str())==2)
				{
					// ���ó�������ͳ�
					sDetStandard.strApp_DimLen_UpperLimit = L"12000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2550";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				else if (sVehInfo.strAxleNumber == L"3")
				{
					// ����ͳ�
					sDetStandard.strApp_DimLen_UpperLimit = L"13700";
					sDetStandard.strApp_DimWid_UpperLimit = L"2550";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				else
				{
					// ���½ӿͳ�
					sDetStandard.strApp_DimLen_UpperLimit = L"18000";
					sDetStandard.strApp_DimWid_UpperLimit = L"2550";
					sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				}
				// ������ʻ��˫��ͳ����������ֵΪ4200mm
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"06"))
				{
					if(_wtoi(sDetStandard.strApp_DimHei_UpperLimit.c_str()) < 4200)
					{
						sDetStandard.strApp_DimHei_UpperLimit = L"4200";
					}
				}
			}
			else if (std::wstring::npos!=sVehInfo.strVehType.find(L"���ٻ���")
				|| _wtoi(sVehInfo.strMaximumVelocity.c_str()) < 70)
			{
				// �����Ƴ���С��70km/h�Ļ���
				sDetStandard.strApp_DimLen_UpperLimit = L"6000";
				sDetStandard.strApp_DimWid_UpperLimit = L"2000";
				sDetStandard.strApp_DimHei_UpperLimit = L"2500";
			}
			else if (std::wstring::npos!=sVehInfo.strVehType.find(L"����")
				|| std::wstring::npos!=sVehInfo.strVehType.find(L"���ǣ��"))
			{
				// ���������ǣ����
				sDetStandard.strApp_DimLen_UpperLimit = L"12000";
				sDetStandard.strApp_DimWid_UpperLimit = L"2550";
				sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				// ��س���������ֵΪ26000mm
				if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"03"))
				{
					if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 2600)
					{
						sDetStandard.strApp_DimWid_UpperLimit = L"2600";
					}
				}
			}
			else
			{
				// ȱʡ
				sDetStandard.strApp_DimLen_UpperLimit = L"";
				sDetStandard.strApp_DimWid_UpperLimit = L"";
				sDetStandard.strApp_DimHei_UpperLimit = L"";
				//// �����г�
				//if (std::wstring::npos!=sVehInfo.strVehType.find(L"���ó��г�"))
				//{
				//	// ���������ǣ����
				//	sDetStandard.strApp_DimLen_UpperLimit = L"14500";
				//	sDetStandard.strApp_DimWid_UpperLimit = L"2550";
				//	sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				//}
				//if (std::wstring::npos!=sVehInfo.strVehType.find(L"�½��г�"))
				//{
				//	// ���������ǣ����
				//	sDetStandard.strApp_DimLen_UpperLimit = L"17100";
				//	sDetStandard.strApp_DimWid_UpperLimit = L"2550";
				//	sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				//}
				//if (std::wstring::npos!=sVehInfo.strVehType.find(L"�����г�"))
				//{
				//	// ���������ǣ����
				//	sDetStandard.strApp_DimLen_UpperLimit = L"20000";
				//	sDetStandard.strApp_DimWid_UpperLimit = L"2550";
				//	sDetStandard.strApp_DimHei_UpperLimit = L"4000";
				//}
				//// ��س���������ֵΪ26000mm
				//if(std::wstring::npos!=sVehInfo.strDimFeature.find(L"03"))
				//{
				//	if(_wtoi(sDetStandard.strApp_DimWid_UpperLimit.c_str()) < 2600)
				//	{
				//		sDetStandard.strApp_DimWid_UpperLimit = L"2600";
				//	}
				//}
			}
		}
	}
}

void CStandard::GetUnladenMass(const SVehInfo& sVehInfo, SDetStandard& sDetStandard)
{
	// Ĭ��ֵ
	sDetStandard.strUM_RE = L"5";
	sDetStandard.strUM_AE = L"500";

	if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"H1")		// ���ͻ�����	
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"H2")	// ���ͻ�����
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B1") // ���Ͱ�ҳ�
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B2") // ���Ͱ�ҳ�
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"B3") // ���Ͱ�ҳ�
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G1") // ����ȫ�ҳ�
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G2") // ����ȫ�ҳ�
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"G3") // ����ȫ�ҳ�
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"Z1")	// ����ר����ҵ��
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"Z2")	// ����ר����ҵ��
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"Z5")	// ����ר����ҵ��
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"Q1")	// ����ǣ����
		|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"Q2")	// ����ǣ����
		)
	{
		sDetStandard.strUM_RE = L"3";
		sDetStandard.strUM_AE = L"500";
	}
	else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"H3")		// ���ͻ���
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"H4")		// ΢�ͻ���
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"H5")		// ���ٻ���
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"Q3")	// ����ǣ����
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"Z3")	// С��ר����ҵ��
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"Z4")	// ΢��ר����ҵ��
			|| std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"Z7")	// ����ר����ҵ��
			)
	{
		sDetStandard.strUM_RE = L"3";
		sDetStandard.strUM_AE = L"100";
	}
	else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"N11"))		// ��������
	{
		sDetStandard.strUM_RE = L"5";
		sDetStandard.strUM_AE = L"100";
	}
	else if (std::wstring::npos!=sVehInfo.strVehTypeCode.find(L"M"))		// Ħ�г�
	{
		sDetStandard.strUM_RE = L"0";
		sDetStandard.strUM_AE = L"10";
	}
}