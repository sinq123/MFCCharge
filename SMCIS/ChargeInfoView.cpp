// ChargeInfoView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SMCIS.h"
#include "ChargeInfoView.h"
#include "TollWindowDlg.h"
#include "MiscellaneousTollWindowDlg.h"

#define DLG_CAPTION L"�շ�"

// CChargeInfoView

IMPLEMENT_DYNCREATE(CChargeInfoView, CFormView)

	CChargeInfoView::CChargeInfoView()
	: CFormView(CChargeInfoView::IDD)
	/*, m_old_cx(0)
	, m_old_cy(0)*/
	, m_lsVeh_VehType()
	, m_lsVeh_PlateType()
	, m_bListAsUnselected(true)
{
	// ���1280*1024�ֱ��ʽ��п���
	int nSM_CYSCREEN = GetSystemMetrics(SM_CYSCREEN);
	// ���ݷֱ���Y������е���
	//m_nDlgFontSize = nSM_CYSCREEN * 25 / 1024;
	m_nDlgFontSize = 16;
	m_fontDlgFont.CreateFont(m_nDlgFontSize,
		0, 
		0, 
		0, 
		FW_NORMAL,
		FALSE, 
		FALSE, 
		FALSE, 
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,
		L"����");

	// �������
	//m_control_info.RemoveAll();
}

CChargeInfoView::~CChargeInfoView()
{
	m_fontDlgFont.DeleteObject();
}

void CChargeInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT_LOG, m_reLog);
	DDX_Control(pDX, IDC_LST_DET_NOCHARGE, m_lstDetBsnNoCharge);
	DDX_Control(pDX, IDC_ED_NOCHARGE_FILTER, m_edNoChargeFilter);
	DDX_Control(pDX, IDC_DTP_NOCHARGE_START_TIME, m_dtcNoChargeStartTime);
	DDX_Control(pDX, IDC_DTP_NOCHARGE_END_TIME, m_dtcNoChargeCondEndTime);
	DDX_Control(pDX, IDC_ED_NOCHARGE_OWNER, m_edNoChargeOwner);
	DDX_Control(pDX, IDC_CB_NOCHARGE_PLATE_TYPE, m_cbNoChargePlateType);
	DDX_Control(pDX, IDC_CB_NOCHARGE_VEH_TYPE, m_cbNoChargeVehType);

	DDX_Control(pDX, IDC_LST_DET_CHARGE, m_lstDetBsnCharge);
	DDX_Control(pDX, IDC_ED_CHARGE_FILTER, m_edChargeFilter);
	DDX_Control(pDX, IDC_DTP_CHARGE_START_TIME, m_dtcChargeStartTime);
	DDX_Control(pDX, IDC_DTP_CHARGE_END_TIME, m_dtcChargeCondEndTime);
	DDX_Control(pDX, IDC_ED_CHARGE_OWNER, m_edChargeOwner);
	DDX_Control(pDX, IDC_CB_CHARGE_PLATE_TYPE, m_cbChargePlateType);
	DDX_Control(pDX, IDC_CB_CHARGE_VEH_TYPE, m_cbChargeVehType);
	DDX_Control(pDX, IDC_ED_CHARGE_CHARGE_AMOUNT, m_edChargeChargeAmount);

	DDX_Control(pDX, IDC_ST_TOTAL_AMOUNT, m_lbTotalAmount);

	DDX_Control(pDX, IDC_BTN_CHARGES, m_btnCharges);
	DDX_Control(pDX, IDC_BTN_MODIFYCHARGEAMOUNT, m_btnModifyChargeAmount);
	DDX_Control(pDX, IDC_BTN_DELETECHARGE, m_btnDeleteCharge);
	DDX_Control(pDX, IDC_BTN_WRONGANDRETURN, m_btnWrongAndRetturn);
	DDX_Control(pDX, IDC_BTN_MICELLANEOUS, m_btnMiscellaneousCharges);
	DDX_Control(pDX, IDC_BTN_DELETE_RECORD, m_btnDeleteRecord);
}

BEGIN_MESSAGE_MAP(CChargeInfoView, CFormView)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_CHARGES, &CChargeInfoView::OnBnClickedBtnCharges)
	ON_BN_CLICKED(IDC_BTN_MODIFYCHARGEAMOUNT, &CChargeInfoView::OnBnClickedBtnModifychargeamount)
	ON_BN_CLICKED(IDC_BTN_DELETECHARGE, &CChargeInfoView::OnBnClickedBtnDeletecharge)
	ON_BN_CLICKED(IDC_BTN_WRONGANDRETURN, &CChargeInfoView::OnBnClickedBtnWrongandreturn)
	ON_NOTIFY(NM_CLICK, IDC_LST_DET_NOCHARGE, &CChargeInfoView::OnLvnItemchangedLstDetNocharge)
	ON_NOTIFY(NM_CLICK, IDC_LST_DET_CHARGE, &CChargeInfoView::OnLvnItemchangedLstDetCharge)
	ON_BN_CLICKED(IDC_BTN_MICELLANEOUS, &CChargeInfoView::OnBnClickedBtnMicellaneous)
	ON_BN_CLICKED(IDC_BTN_DELETE_RECORD, &CChargeInfoView::OnBnClickedBtnDeleteRecord)
END_MESSAGE_MAP()


// CChargeInfoView ���

#ifdef _DEBUG
void CChargeInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CChargeInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CChargeInfoView ��Ϣ�������


void CChargeInfoView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���

	// ��ʼ���ؼ�
	InitCtrls();

	// �����б�
	SetTimer(1, 1500, NULL);

}


void CChargeInfoView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if(nType==1) return;//��С����ʲô������  

	//float dx_percent = (m_old_cx == 0)? 1 : (float)((float)cx/(float)m_old_cx);
	//float dy_percent = (m_old_cy == 0)? 1 : (float)((float)cy/(float)m_old_cy);

	//if (m_old_cx && m_old_cy)
	//{
	//	CRect WndRect;
	//	CWnd* pWnd;

	//	for(int i =0; i < m_control_info.GetSize(); i++)
	//	{
	//		pWnd = GetDlgItem(m_control_info[i]);
	//		if (!pWnd)
	//		{
	//			TRACE("Control ID - %d NOT FOUND!", m_control_info[i]);
	//			continue;
	//		}

	//		pWnd->GetWindowRect(&WndRect);
	//		ScreenToClient(&WndRect);

	//		if (dx_percent != 0)
	//		{
	//			WndRect.left = (int)(WndRect.left*dx_percent);
	//			WndRect.right = (int)(WndRect.right*dx_percent);
	//		}
	//		if (dy_percent != 0)
	//		{
	//			WndRect.bottom = (int)(WndRect.bottom*dy_percent);
	//			WndRect.top = (int)(WndRect.top*dy_percent);
	//		}

	//		pWnd->MoveWindow(&WndRect);
	//	}
	//}

	//m_old_cx = cx;
	//m_old_cy = cy;

	float fsp[2];
	POINT Newp;//��ȡ���ڶԻ���Ĵ�С(VS2005����CPOINT)
	CRect recta;
	GetClientRect(&recta); //ȡ�ͻ�����С
	Newp.x=recta.right-recta.left;
	Newp.y=recta.bottom-recta.top;
	fsp[0]=(float)Newp.x/m_Old.x;
	fsp[1]=(float)Newp.y/m_Old.y;

	if (fsp[0] != 0 && fsp[1] != 0)
	{
		CRect Rect;
		int woc;
		CPoint OldTLPoint,TLPoint; //���Ͻ�
		CPoint OldBRPoint,BRPoint; //���½�
		HWND hwndChild=::GetWindow(m_hWnd,GW_CHILD); //�г����пؼ�

		while(hwndChild)
		{
			woc=::GetDlgCtrlID(hwndChild);//ȡ��ID
			GetDlgItem(woc)->GetWindowRect(Rect);
			ScreenToClient(Rect);
			OldTLPoint = Rect.TopLeft(); 
			TLPoint.x = long(OldTLPoint.x*fsp[0]); 
			TLPoint.y = long(OldTLPoint.y*fsp[1]);
			OldBRPoint = Rect.BottomRight();
			BRPoint.x = long(OldBRPoint.x *fsp[0]); 
			BRPoint.y = long(OldBRPoint.y *fsp[1]); //�߶Ȳ��ɶ��Ŀؼ�����:combBox),��Ҫ�ı��ֵ.
			Rect.SetRect(TLPoint,BRPoint); 
			GetDlgItem(woc)->MoveWindow(Rect,TRUE);
			hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);
		}
		m_Old=Newp;
	}
}


void CChargeInfoView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	switch (nIDEvent)
	{
	case 1:
		{
			NoChargeUpdateDetBsnList();
			ChargeUpdateDetBsnList();
		}
		break;

	case 2:
		{
		}
		break;

	}

	CFormView::OnTimer(nIDEvent);
}


//void CChargeInfoView::InitConInfo(void)
//{
//	SetControlInfo(IDC_ST_NO_CHARGE_LIST);
//	SetControlInfo(IDC_ST_FILTER);
//	SetControlInfo(IDC_ED_NOCHARGE_FILTER);
//	SetControlInfo(IDC_LST_DET_NOCHARGE);
//
//	SetControlInfo(IDC_ST_LIST_OF_CHARGE);
//	SetControlInfo(IDC_ST_CHARGE_FILTER);
//	SetControlInfo(IDC_ED_CHARGE_FILTER);
//	SetControlInfo(IDC_LST_DET_CHARGE);
//
//	SetControlInfo(IDC_BTN_CHARGES);
//	SetControlInfo(IDC_BTN_MODIFYCHARGEAMOUNT);
//	SetControlInfo(IDC_BTN_DELETECHARGE);
//	SetControlInfo(IDC_BTN_WRONGANDRETURN);
//	SetControlInfo(IDC_ST_TOTAL_AMOUNT_INFO);
//	SetControlInfo(IDC_ST_TOTAL_AMOUNT);
//
//	SetControlInfo(IDC_ST_LOGGING_INFO);
//	SetControlInfo(IDC_RICHEDIT_LOG);
//}
//
//void CChargeInfoView::SetControlInfo(const WORD CtrlId)
//{
//	m_control_info.Add(CtrlId);
//}

void CChargeInfoView::OnBnClickedBtnCharges()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const int nIndex = m_lstDetBsnNoCharge.GetSelectionMark();

	if (nIndex == -1)
	{
		MessageBox(L"��ѡ��δ�շ��б�ļ�¼���в���", DLG_CAPTION);
		// ��������Ϊδѡ��
		m_lstDetBsnNoCharge.SetSelectionMark(-1);
		m_lstDetBsnCharge.SetSelectionMark(-1);
		return;
	}
	CString strDetType;
	strDetType = m_lstDetBsnNoCharge.GetItemText(nIndex, 7);

	CTollWindowDlg Dlg;
	Dlg.m_nDDT = DDT_Charge;
	Dlg.m_strDetType = strDetType;
	if (IDOK == Dlg.DoModal())
	{
		CString strChargeItem, strCharge, strWhy, strIsArrears, strUnitName;
		strChargeItem = Dlg.m_strChargeItem;
		strCharge = Dlg.m_strCharge;
		strWhy = Dlg.m_strWhy;
		strIsArrears = Dlg.m_strIsArrears;
		strUnitName = Dlg.m_strUnitName;

		CString strTemp;
		CString strMsg;
		// ���ƺ���
		strTemp = m_lstDetBsnNoCharge.GetItemText(nIndex, 2);
		strMsg.AppendFormat(L"���ƣ�%s", strTemp);
		if (SaveToCharge(strChargeItem, strCharge, strWhy, strIsArrears, strUnitName))
		{
			strMsg.AppendFormat(L"�����շѼ�¼�ɹ�,");

			//��־���
			strTemp = m_lstDetBsnNoCharge.GetItemText(nIndex, 1);
			//if (ModifyStateDetLog(strTemp, L"TODET"))
			// �жϼ����Ŀ�Ƿ����, ��������ɺ������

			CString strDetStatus;
			strDetStatus = IsBsnFined(strTemp.GetString());

			// �Ƿ����µ�ȡ�ж���Ŀ���� ��ʱ����ȡ
			//if (strDetStatus.Find(DS_FinDet) != -1)
			//{
			//	CFinDetBsn::FinDetBsn(theApp.m_pConnection, strTemp.GetString(), true);
			//}

			if (CDetLogService::SetDetLog_DetStatus(theApp.m_pConnection, strTemp.GetString(), strDetStatus.GetString()) != 0xFFFFFFFF)
			{
				strMsg.AppendFormat(L"�޸ļ��״̬�ɹ�");
			}
			else
			{
				strMsg.AppendFormat(L"�޸ļ��״̬ʧ��");
			}
		}
		else
		{
			strMsg.AppendFormat(L"�����շѼ�¼ʧ��");
		}

		//PrintLog(strMsg);

		if (strIsArrears == L"1")
		{
			if (SaveArrearsToDB(strUnitName, strCharge))
			{
				strMsg.AppendFormat(L",����Ƿ�Ѽ�¼�ɹ�");
			}
			else
			{
				strMsg.AppendFormat(L",����Ƿ�Ѽ�¼ʧ��");
			}

			PrintLog(strMsg);
		}
	}
	// ��������Ϊδѡ��
	m_lstDetBsnNoCharge.SetSelectionMark(-1);
	m_lstDetBsnCharge.SetSelectionMark(-1);
}


void CChargeInfoView::OnBnClickedBtnModifychargeamount()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const int nIndex = m_lstDetBsnCharge.GetSelectionMark();

	if (nIndex == -1)
	{
		MessageBox(L"��ѡ�����շ��б�ļ�¼���в���", DLG_CAPTION);
		// ��������Ϊδѡ��
		m_lstDetBsnNoCharge.SetSelectionMark(-1);
		m_lstDetBsnCharge.SetSelectionMark(-1);
		return;
	}

	CString strRunNum, strPlateNum, strMsg;
	//��־���
	strRunNum = m_lstDetBsnCharge.GetItemText(nIndex, 1);
	// ���ƺ���
	strPlateNum = m_lstDetBsnCharge.GetItemText(nIndex, 2);

	if (strPlateNum.IsEmpty() || strRunNum.IsEmpty())
	{
		strMsg.Format(L"����%s������־���%s��Ϊ��, ���ܽ����޸Ĳ���", strPlateNum, strRunNum);
		MessageBox(strMsg);
		return;
	}

	CString strDetType;
	strDetType = m_lstDetBsnCharge.GetItemText(nIndex, 7);
	CTollWindowDlg Dlg;
	Dlg.m_nDDT = DDT_Modifies;
	Dlg.m_strDetType = strDetType;
	if (IDOK == Dlg.DoModal())
	{
		CString strChargeItem, strCharge, strWhy;
		strChargeItem = Dlg.m_strChargeItem;
		strCharge = Dlg.m_strCharge;
		strWhy = Dlg.m_strWhy;

		strMsg.Format(L"���ƣ�%s, �޸Ľ��ԭ��%s, ", strPlateNum, strWhy);
		if (ModifyChargeAmount(strChargeItem, strCharge, strWhy))
		{
			strMsg.AppendFormat(L"�޸��շѽ��ɹ���");
		}
		else
		{
			strMsg.AppendFormat(L"�޸��շѽ��ʧ�ܣ�");
		}
		PrintLog(strMsg);
	}

	// ��������Ϊδѡ��
	m_lstDetBsnNoCharge.SetSelectionMark(-1);
	m_lstDetBsnCharge.SetSelectionMark(-1);
}


void CChargeInfoView::OnBnClickedBtnDeletecharge()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const int nIndex = m_lstDetBsnCharge.GetSelectionMark();

	if (nIndex == -1)
	{
		MessageBox(L"��ѡ�����շ��б�ļ�¼���в���", DLG_CAPTION);
		// ��������Ϊδѡ��
		m_lstDetBsnNoCharge.SetSelectionMark(-1);
		m_lstDetBsnCharge.SetSelectionMark(-1);
		return;
	}

	CString strPlatrNum, strRunNum, strMsg;
	strPlatrNum = m_lstDetBsnCharge.GetItemText(nIndex, 2);
	strRunNum = m_lstDetBsnCharge.GetItemText(nIndex, 1);

	if (strPlatrNum.IsEmpty() || strRunNum.IsEmpty())
	{
		strMsg.Format(L"����%s������־���%��Ϊ��", strPlatrNum, strRunNum);
		MessageBox(strMsg);
		return;
	}


	CTollWindowDlg Dlg;
	Dlg.m_nDDT = DDT_Cancels;
	if (IDOK == Dlg.DoModal())
	{
		CString strWhy;
		strWhy = Dlg.m_strWhy;

		strMsg.Format(L"���ƣ�%s, �˷�/�˰�ԭ��%s, ",strPlatrNum, strWhy);
		if (CancelOfCharge(strWhy))
		{
			strMsg.AppendFormat(L"�˷�/�˰�ɹ���");
		}
		else
		{
			strMsg.AppendFormat(L"�˷�/�˰�ʧ�ܣ�");
		}
		PrintLog(strMsg);
	}

	// ��������Ϊδѡ��
	m_lstDetBsnNoCharge.SetSelectionMark(-1);
	m_lstDetBsnCharge.SetSelectionMark(-1);
}


void CChargeInfoView::OnBnClickedBtnWrongandreturn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const int nIndex = m_lstDetBsnCharge.GetSelectionMark();

	if (nIndex == -1)
	{
		MessageBox(L"��ѡ�����շ��б�ļ�¼���в���", DLG_CAPTION);
		// ��������Ϊδѡ��
		m_lstDetBsnNoCharge.SetSelectionMark(-1);
		m_lstDetBsnCharge.SetSelectionMark(-1);
		return;
	}

	CString strTemp, strRun;
	//��־���
	strRun = m_lstDetBsnCharge.GetItemText(nIndex, 1);
	std::wstring strDetStatus;
	if (CDetLogService::GetDetLog_DetStatus(theApp.m_pConnection, strRun.GetString(), strDetStatus) != 0x01)
	{
		MessageBox(L"��ȡ���״̬ʧ�ܣ��������޸ģ�", DLG_CAPTION);
		// ��������Ϊδѡ��
		m_lstDetBsnNoCharge.SetSelectionMark(-1);
		m_lstDetBsnCharge.SetSelectionMark(-1);
		return;
	}

	// ֻ���ڵȴ��������޸�
	if (strDetStatus.find(L"TODET") != std::string::npos)
	{
		CTollWindowDlg Dlg;
		Dlg.m_nDDT = DDTWrongChoice;

		if (IDOK == Dlg.DoModal())
		{
			CString strWhy, strMsg;
			strWhy = Dlg.m_strWhy;

			strTemp = m_lstDetBsnCharge.GetItemText(nIndex, 2);

			strMsg.AppendFormat(L"����:%s ", strTemp);
			strMsg.AppendFormat(L"ѡ���˻�ԭ��:%s ", strWhy);
			if (DeteleToCharge(strRun))
			{
				strMsg.AppendFormat(L"ɾ���շѼ�¼�ɹ�");
				if (ModifyStateDetLog(strRun, L"NOCHARGE"))
				{
					strMsg.AppendFormat(L"�޸ĸó�Ϊδ�շѳɹ�");
				}
				else
				{
					strMsg.AppendFormat(L"�޸ĸó�Ϊδ�շ�ʧ��");
				}
			}
			else
			{
				strMsg.AppendFormat(L"ɾ���շѼ�¼ʧ��");
			}

			PrintLog(strMsg);
		}
	}
	else
	{
		MessageBox(L"�ó����״̬���ǵȴ���⣬�������޸ģ�", DLG_CAPTION);
		// ��������Ϊδѡ��
		m_lstDetBsnNoCharge.SetSelectionMark(-1);
		m_lstDetBsnCharge.SetSelectionMark(-1);
		return;
	}


	// ��������Ϊδѡ��
	m_lstDetBsnNoCharge.SetSelectionMark(-1);
	m_lstDetBsnCharge.SetSelectionMark(-1);
}


void CChargeInfoView::OnLvnItemchangedLstDetNocharge(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CChargeInfoView::OnLvnItemchangedLstDetCharge(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CChargeInfoView::OnBnClickedBtnMicellaneous()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMiscellaneousTollWindowDlg Dlg;

	if (IDOK == Dlg.DoModal())
	{
		CString strChargeItem, strCharge, strChargeNumber;

		strChargeItem = Dlg.m_strChargeItem;
		strCharge = Dlg.m_strCharge;
		strChargeNumber = Dlg.m_strChargeNumber;

		SCharge sCharge;

		CString strTemp;
		//��־���
		SYSTEMTIME sys_time;
		GetLocalTime(&sys_time);
		// ��ʽ YYMMDDHHMMSSmm
		strTemp.Format(L"%02d%02d%02d%02d%02d%02d%02d", sys_time.wYear%100, sys_time.wMonth, sys_time.wDay, sys_time.wHour, 
			sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds%100);
		sCharge.strRunningNumber = strTemp.GetString();
		// ���ƺ���
		strTemp.Format(L"����");
		sCharge.strPlateNumber = strTemp.GetString();
		// ��������
		sCharge.strPlateType = strTemp.GetString();
		// ��¼Ա
		sCharge.strEntryOperator = L"";
		// �շ�ʱ��
		sCharge.strChargingTime = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
		// �շѽ��
		sCharge.strAmountOfCharges = strCharge.GetString();
		// �շ�״̬
		sCharge.strChargeingStatus = DS_Chargee;
		// �շ�Ա
		sCharge.strTollCollector = theApp.m_sToll_Operator.strName.c_str();
		// ������
		sCharge.strOwner = strTemp.GetString();
		// �������
		sCharge.strVehType = strTemp.GetString();
		// ��������/������
		sCharge.strUnladenMass = L"";
		sCharge.strMaximumTotalMass = L"";
		// �������
		sCharge.strDetType = strTemp.GetString();
		// �շ���Ŀ
		sCharge.strChargeItem = strChargeItem.GetString();
		// ���ñ���1->��������
		sCharge.strReserved1 = strChargeNumber.GetString();

		if (0xFFFFFFFF == CChargeService::SetCharge(theApp.m_pConnection, sCharge))
		{
			MessageBox(L"�����շѽ��ʧ��", DLG_CAPTION);
		}
		else
		{
			MessageBox(L"�����շѽ��ɹ�", DLG_CAPTION);
		}
	}

	// ��������Ϊδѡ��
	m_lstDetBsnNoCharge.SetSelectionMark(-1);
	m_lstDetBsnCharge.SetSelectionMark(-1);
}



void CChargeInfoView::InitCtrls(void)
{
	GetDocument()->SetTitle(DLG_CAPTION);

	SetDlgFont();
	//InitConInfo();

	InitDetBsnList();

	InitPlateType();
	InitVehType();
	// �ܽ��Ϊ��
	m_lbTotalAmount.SetWindowTextW(L"");
	// �շ�
	m_btnCharges.SetFlat(FALSE);
	// �޸��շѽ��
	m_btnModifyChargeAmount.SetFlat(FALSE);
	// ȡ���շ�
	m_btnDeleteCharge.SetFlat(FALSE);
	// ѡ���˻�
	m_btnWrongAndRetturn.SetFlat(FALSE);
	// �����շ�
	m_btnMiscellaneousCharges.SetFlat(FALSE);
	// ɾ����¼
	m_btnDeleteRecord.SetFlat(FALSE);
	// ���ǹ���Ա����ʾɾ����ť
	if (!VerifyEmpPerm(theApp.m_sToll_Operator))
	{
		m_btnDeleteRecord.ShowWindow(SW_HIDE);
		m_btnModifyChargeAmount.ShowWindow(SW_HIDE);
		m_btnDeleteCharge.ShowWindow(SW_HIDE);
	}
}

void CChargeInfoView::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);
		pWnd = pWnd->GetNextWindow();
	}
}

void CChargeInfoView::InitDetBsnList(void)
{
	// δ�շ�
	m_lstDetBsnNoCharge.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	int nColumn(0);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"���", LVCFMT_LEFT, 30);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"��־���", LVCFMT_LEFT, 0);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"���ƺ���", LVCFMT_LEFT, 100);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"��������", LVCFMT_LEFT, 100);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"�������", LVCFMT_LEFT, 120);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"��������/������", LVCFMT_LEFT, 100);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"������", LVCFMT_LEFT, 100);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"�������", LVCFMT_LEFT, 100);
	m_lstDetBsnNoCharge.InsertColumn(nColumn++, L"��¼Ա", LVCFMT_LEFT, 100);

	m_lstDetBsnNoCharge.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lstDetBsnNoCharge.SetFont(&theApp.m_fontListCtrl);

	// ���շ�
	m_lstDetBsnCharge.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	nColumn = 0;
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"���", LVCFMT_LEFT, 30);
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"��־���", LVCFMT_LEFT, 0);
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"���ƺ���", LVCFMT_LEFT, 100);
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"��������", LVCFMT_LEFT, 100);
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"�������", LVCFMT_LEFT, 120);
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"��������/������", LVCFMT_LEFT, 100);
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"������", LVCFMT_LEFT, 100);
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"�������", LVCFMT_LEFT, 100);
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"�շ�Ա", LVCFMT_LEFT, 100);
	m_lstDetBsnCharge.InsertColumn(nColumn++, L"�շѽ��", LVCFMT_LEFT, 100);

	m_lstDetBsnCharge.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lstDetBsnCharge.SetFont(&theApp.m_fontListCtrl);

}

bool CChargeInfoView::InitPlateType(void)
{
	CString strSQL;
	strSQL.Format(L"select * from Veh_PlateType order by AutoID");

	if (0xFFFFFFFF != CVeh_PlateTypeService::GetVeh_PlateType(theApp.m_pConnection, strSQL, m_lsVeh_PlateType))
	{
		std::list<SVeh_PlateType>::const_iterator iter = m_lsVeh_PlateType.begin();
		for ( ; iter != m_lsVeh_PlateType.end(); iter++)
		{
			m_cbNoChargePlateType.AddString(iter->strName.c_str());
			m_cbChargePlateType.AddString(iter->strName.c_str());
		}
		return true;
	}
	else
	{
		MessageBox(L"��ȡ[��������]ʧ�ܡ�", DLG_CAPTION);
		return false;
	}
}

bool CChargeInfoView::InitVehType(void)
{
	CString strSQL;
	strSQL.Format(L"select * from Veh_VehType order by AutoID");

	if (0xFFFFFFFF != CVeh_VehTypeService::GetVeh_VehType(theApp.m_pConnection, strSQL, m_lsVeh_VehType))
	{
		std::list<SVeh_VehType>::const_iterator iter = m_lsVeh_VehType.begin();
		for ( ; iter != m_lsVeh_VehType.end(); iter++)
		{
			m_cbNoChargeVehType.AddString(iter->strName.c_str());
			m_cbChargeVehType.AddString(iter->strName.c_str());
		}
		return true;
	}
	else
	{
		MessageBox(L"��ȡ[��������]ʧ�ܡ�", DLG_CAPTION);
		return false;
	}
}

void CChargeInfoView::PrintLog(LPCTSTR szFormat, ...)
{
	//::EnterCriticalSection(&m_csLog);	// �������������̵߳ȴ�ʱ�������̲߳��ܶ�m_reLog���в���

	//m_reLog.SetSel(0, -1);
	//m_reLog.Clear();

	TCHAR szBuf[4096] = {0};
	va_list args; 
	va_start(args, szFormat); 
	_vstprintf(szBuf, szFormat, args);
	va_end(args); 

	CString strLog;
	strLog.AppendFormat(_T("[%s] [������:%s] %s\r\n"), COleDateTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S")), theApp.m_sToll_Operator.strName.c_str(), 
		szBuf);

	m_reLog.LineScroll(m_reLog.GetLineCount());
	int nLen = m_reLog.GetWindowTextLength();
	m_reLog.SetSel(nLen, nLen);
	m_reLog.ReplaceSel(strLog);


	// ��¼������¼������֮��鿴
	SCharge_Log_Record sCharge_Log_Record;
	sCharge_Log_Record.strTimes = COleDateTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"));
	sCharge_Log_Record.strDescription = strLog;

	if (CCharge_Log_RecordService::SetCharge_Log_Record(theApp.m_pConnection, sCharge_Log_Record) != 0x01)
	{
		// ����ʧ��
	}
	//::LeaveCriticalSection(&m_csLog);
}

void CChargeInfoView::NoChargeUpdateDetBsnList(void)
{
	CString strSql;
	CStringW strNoChargeFilter, strNoChargeOwner, strNoChargePlateType, strNoChargeVehType;
	COleDateTime odtNoChargeStartTime, odtNoChargeCondEndTime;
	const int nNoChargeIndex = m_lstDetBsnNoCharge.GetSelectionMark();

	m_edNoChargeFilter.GetWindowText(strNoChargeFilter);
	m_edNoChargeOwner.GetWindowTextW(strNoChargeOwner);
	m_cbNoChargePlateType.GetWindowTextW(strNoChargePlateType);
	m_cbNoChargeVehType.GetWindowTextW(strNoChargeVehType);
	m_dtcNoChargeStartTime.GetTime(odtNoChargeStartTime);
	m_dtcNoChargeCondEndTime.GetTime(odtNoChargeCondEndTime);
	// ѡ��ʱ�������б�
	if (nNoChargeIndex != -1)
	{
		return;
	}

	strSql.AppendFormat(L" select DetLog.RunningNumber,DetLog.PlateNumber,DetLog.PlateType,EntryOperator,EntryTime,EntryPCIP,DetStatus, DetType,DetType_M,DetTimes.TotalDetTimes,DetLog.AutoID,HisVehInfo.Owner,HisVehInfo.VehType, \
						 HisVehInfo.MaximumTotalMass, HisVehInfo.UnladenMass ");
	strSql.AppendFormat(L" from DetLog left join DetTimes on DetLog.RunningNumber = DetTimes.RunningNumber ");
	strSql.AppendFormat(L" left join HisVehInfo on DetLog.RunningNumber = HisVehInfo.RunningNumber ");
	strSql.AppendFormat(L" where DetStatus = 'NOCHARGE' ");
	// ���ƺ���
	if (!strNoChargeFilter.IsEmpty())
	{
		strSql.AppendFormat(L" and (DetLog.PlateNumber like '%%%s%%') ", strNoChargeFilter);
	}
	// ������
	if (!strNoChargeOwner.IsEmpty())
	{
		strSql.AppendFormat(L" and (HisVehInfo.Owner ='%s') ", strNoChargeOwner);
	}
	// ��������
	if (!strNoChargePlateType.IsEmpty())
	{
		strSql.AppendFormat(L" and (DetLog.PlateType = '%s') ", strNoChargePlateType);
	}
	// ��������
	if (!strNoChargeVehType.IsEmpty())
	{
		strSql.AppendFormat(L" and (HisVehInfo.VehType = '%s') ", strNoChargeVehType);
	}
	// ʱ��
	strSql.AppendFormat(L" and (DetLog.EntryTime between '%s 00:00:00' and '%s 23:59:59') ", odtNoChargeStartTime.Format(L"%Y-%m-%d"), 
		odtNoChargeCondEndTime.Format(L"%Y-%m-%d"));
	strSql.AppendFormat(L" order by AutoID desc ");

	_RecordsetPtr pRecordset(NULL);
	if (0x00 == CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		m_lstDetBsnNoCharge.DeleteAllItems();
		m_lstDetBsnNoCharge.SetRedraw(FALSE);

		int nItem(0);

		try
		{
			while (!pRecordset->adoEOF)
			{
				CString str;
				_variant_t v;
				wchar_t wchBuf[256] = {L'\0'};
				int nSubItem(0);

				_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", nItem+1);
				const int nIndex = m_lstDetBsnNoCharge.InsertItem(nItem++, wchBuf);
				nSubItem++;

				// �����ˮ��(������ʱ����IP)
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"RunningNumber");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}
				m_lstDetBsnNoCharge.SetItemText(nIndex, nSubItem++, wchBuf);


				// ���ƺ���
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"PlateNumber");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}
				m_lstDetBsnNoCharge.SetItemText(nIndex, nSubItem++, wchBuf);

				// ��������
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"PlateType");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}				
				m_lstDetBsnNoCharge.SetItemText(nIndex, nSubItem++, wchBuf);

				// �������
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"VehType");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}				
				m_lstDetBsnNoCharge.SetItemText(nIndex, nSubItem++, wchBuf);

				// ��������
				str.Empty();
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"UnladenMass");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
					str.AppendFormat(L"%s/", wchBuf);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
					str.AppendFormat(L"%s/", L" ");
				}

				// ������
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"MaximumTotalMass");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
					str.AppendFormat(L"%s", wchBuf);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
					str.AppendFormat(L"%s", L" ");
				}
				m_lstDetBsnNoCharge.SetItemText(nIndex, nSubItem++, str);

				// ������
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"Owner");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}				
				m_lstDetBsnNoCharge.SetItemText(nIndex, nSubItem++, wchBuf);

				// ������
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"DetType");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}
				str = wchBuf;

				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"DetType_M");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}
				if (str.IsEmpty())
				{
					// ֻ���ۼ�
					str = wchBuf;
				}
				else
				{
					CString strMFD(wchBuf);
					if (!strMFD.IsEmpty())
					{
						str.AppendFormat(L"//%s", strMFD);
					}
				}
				m_lstDetBsnNoCharge.SetItemText(nIndex, nSubItem++, str);


				// ��¼Ա
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"EntryOperator");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}				
				m_lstDetBsnNoCharge.SetItemText(nIndex, nSubItem++, wchBuf);

				pRecordset->MoveNext();
			}
		}
		catch (_com_error& e)
		{
			CNHSQLServerDBO::OutputDBErrMsg(e);

			// �쳣����б�
			m_lstDetBsnNoCharge.DeleteAllItems();
		}


		m_lstDetBsnNoCharge.SetRedraw(TRUE);
		m_lstDetBsnNoCharge.Invalidate();
	}

}


void CChargeInfoView::ChargeUpdateDetBsnList(void)
{
	CString strSql;
	CStringW strChargeFilter, strChargeOwner, strChargePlateType, strChargeVehType, strChargeChargeAmount;
	COleDateTime odtChargeStartTime, odtChargeCondEndTime;
	const int nChargeIndex = m_lstDetBsnCharge.GetSelectionMark();

	m_edChargeFilter.GetWindowText(strChargeFilter);
	m_edChargeOwner.GetWindowTextW(strChargeOwner);
	m_cbChargePlateType.GetWindowTextW(strChargePlateType);
	m_cbChargeVehType.GetWindowTextW(strChargeVehType);
	m_edChargeChargeAmount.GetWindowTextW(strChargeChargeAmount);
	m_dtcChargeStartTime.GetTime(odtChargeStartTime);
	m_dtcChargeCondEndTime.GetTime(odtChargeCondEndTime);
	// ѡ��ʱ�������б�
	if (nChargeIndex != -1)
	{
		return;
	}

	strSql.AppendFormat(L" select Charge.AutoID, Charge.RunningNumber, Charge.PlateNumber , Charge.PlateType, Charge.EntryOperator,Charge.TotalDetTimes, Charge.AmountOfCharges, Charge.ChargingTime,\
						 Charge.ChargeingStatus, Charge.TollCollector, Charge.Owner, Charge.VehType, Charge.UnladenMass, Charge.MaximumTotalMass, Charge.DetType, Charge.OperationalOfReason ");
	strSql.AppendFormat(L" from Charge");
	// ʱ��
	strSql.AppendFormat(L" where (Charge.ChargingTime between '%s 00:00:00' and '%s 23:59:59')", odtChargeStartTime.Format(L"%Y-%m-%d"), 
		odtChargeCondEndTime.Format(L"%Y-%m-%d"));
	strSql.AppendFormat(L" and Charge.ChargeingStatus <> '%s'", DS_CancelOfCharge);
	// ���ƺ���
	if (!strChargeFilter.IsEmpty())
	{
		strSql.AppendFormat(L" and (Charge.PlateNumber like '%%%s%%') ", strChargeFilter);
	}
	// ������
	if (!strChargeOwner.IsEmpty())
	{
		strSql.AppendFormat(L" and (Charge.Owner ='%s') ", strChargeOwner);
	}
	// ��������
	if (!strChargePlateType.IsEmpty())
	{
		strSql.AppendFormat(L" and (Charge.PlateType = '%s') ", strChargePlateType);
	}
	// ��������
	if (!strChargeVehType.IsEmpty())
	{
		strSql.AppendFormat(L" and (Charge.VehType = '%s') ", strChargeVehType);
	}
	// �շѽ��
	if (!strChargeChargeAmount.IsEmpty())
	{
		strSql.AppendFormat(L" and (Charge.AmountOfCharges like '%%%s%%') ", strChargeChargeAmount);
	}
	strSql.AppendFormat(L" order by AutoID desc ");

	_RecordsetPtr pRecordset(NULL);
	if (0x00 == CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		m_lstDetBsnCharge.DeleteAllItems();
		m_lstDetBsnCharge.SetRedraw(FALSE);

		int nItem(0);

		try
		{
			float fTotalAmount(0.0f);
			while (!pRecordset->adoEOF)
			{
				CString str;
				_variant_t v;
				wchar_t wchBuf[256] = {L'\0'};
				int nSubItem(0);

				_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%d", nItem+1);
				const int nIndex = m_lstDetBsnCharge.InsertItem(nItem++, wchBuf);
				nSubItem++;

				// �����ˮ��(������ʱ����IP)
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"RunningNumber");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}
				m_lstDetBsnCharge.SetItemText(nIndex, nSubItem++, wchBuf);


				// ���ƺ���
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"PlateNumber");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}
				m_lstDetBsnCharge.SetItemText(nIndex, nSubItem++, wchBuf);

				// ��������
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"PlateType");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}				
				m_lstDetBsnCharge.SetItemText(nIndex, nSubItem++, wchBuf);

				// �������
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"VehType");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}				
				m_lstDetBsnCharge.SetItemText(nIndex, nSubItem++, wchBuf);

				// ��������
				str.Empty();
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"UnladenMass");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
					str.AppendFormat(L"%s/", wchBuf);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
					str.AppendFormat(L"%s/", L" ");
				}

				// ������
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"MaximumTotalMass");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
					str.AppendFormat(L"%s", wchBuf);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
					str.AppendFormat(L"%s", L" ");
				}
				m_lstDetBsnCharge.SetItemText(nIndex, nSubItem++, str);

				// ������
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"Owner");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}				
				m_lstDetBsnCharge.SetItemText(nIndex, nSubItem++, wchBuf);

				// �������
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"DetType");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}				
				m_lstDetBsnCharge.SetItemText(nIndex, nSubItem++, wchBuf);

				// �շ�Ա
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"TollCollector");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}				
				m_lstDetBsnCharge.SetItemText(nIndex, nSubItem++, wchBuf);

				// �շѽ��
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(pRecordset, v, L"AmountOfCharges");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%.4f", static_cast<float>(v));
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}				
				m_lstDetBsnCharge.SetItemText(nIndex, nSubItem++, wchBuf);
				fTotalAmount += _wtof(wchBuf);

				pRecordset->MoveNext();
			}

			CString str;
			str.Format(L"%.4f", fTotalAmount);
			m_lbTotalAmount.SetWindowTextW(str);
		}
		catch (_com_error& e)
		{
			CNHSQLServerDBO::OutputDBErrMsg(e);

			// �쳣����б�
			m_lstDetBsnCharge.DeleteAllItems();
		}


		m_lstDetBsnCharge.SetRedraw(TRUE);
		m_lstDetBsnCharge.Invalidate();
	}
}


bool CChargeInfoView::SaveToCharge(const CString& strChargeItem, const CString& strCharge, const CString& strWhy, const CString& strIsArrears, const CString& strUnitName)
{

	const int nIndex = m_lstDetBsnNoCharge.GetSelectionMark();

	if (nIndex == -1)
	{
		return false;
	}

	SCharge sCharge;

	CString strTemp;
	//��־���
	strTemp = m_lstDetBsnNoCharge.GetItemText(nIndex, 1);
	sCharge.strRunningNumber = strTemp.GetString();
	// ���ƺ���
	strTemp = m_lstDetBsnNoCharge.GetItemText(nIndex, 2);
	sCharge.strPlateNumber = strTemp.GetString();
	// ��������
	strTemp = m_lstDetBsnNoCharge.GetItemText(nIndex, 3);
	sCharge.strPlateType = strTemp.GetString();
	// ��¼Ա
	strTemp = m_lstDetBsnNoCharge.GetItemText(nIndex, 8);
	sCharge.strEntryOperator = strTemp.GetString();
	// �շ�ʱ��
	sCharge.strChargingTime = COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S");
	// �շѽ��
	sCharge.strAmountOfCharges = strCharge.GetString();
	// �շ�״̬
	sCharge.strChargeingStatus = DS_Chargee;
	// �շ�Ա
	sCharge.strTollCollector = theApp.m_sToll_Operator.strName.c_str();
	// ������
	strTemp = m_lstDetBsnNoCharge.GetItemText(nIndex, 6);
	sCharge.strOwner = strTemp.GetString();
	// �������
	strTemp = m_lstDetBsnNoCharge.GetItemText(nIndex, 4);
	sCharge.strVehType = strTemp.GetString();
	// ��������/������
	strTemp = m_lstDetBsnNoCharge.GetItemText(nIndex, 5);
	CString str;
	const int nPos = strTemp.Find(L"/");
	str = strTemp.Left(nPos);
	sCharge.strUnladenMass = str.GetString();
	str = strTemp.Right(nPos);
	sCharge.strMaximumTotalMass = str.GetString();
	// �������
	strTemp = m_lstDetBsnNoCharge.GetItemText(nIndex, 7);
	sCharge.strDetType = strTemp.GetString();
	// �շ���Ŀ
	sCharge.strChargeItem = strChargeItem.GetString();
	// ԭ��
	if (!strWhy.IsEmpty())
	{
		sCharge.strOperationalOfReason = strWhy.GetString();
	}

	if (!strIsArrears.IsEmpty())
	{
		sCharge.strIsArrears = strIsArrears.GetString();
		sCharge.strUnitName = strUnitName.GetString();
		// Ƿ�����ʱ���շѽ������Ϊ��
		sCharge.strAmountOfCharges = L"0";
	}

	if (0xFFFFFFFF == CChargeService::SetCharge(theApp.m_pConnection, sCharge))
	{
		MessageBox(L"�����շѽ��ʧ��", DLG_CAPTION);
		return false;
	}
	else
	{
		MessageBox(L"�����շѽ��ɹ�", DLG_CAPTION);
	}

	return true;

}

bool CChargeInfoView::ModifyStateDetLog(const CString& strRunNum, const CString& strState/*=L"TODET"*/)
{
	bool bRet(false);

	CString strSql;

	strSql.AppendFormat(L" update DetLog ");
	strSql.AppendFormat(L" set DetLog.DetStatus = '%s', DetLog.UpdateStatusTime = '%s' ", strState, COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d %H:%M:%S"));
	strSql.AppendFormat(L" from DetLog ");
	//strSql.AppendFormat(L" where DetLog.DetStatus = 'NOCHARGE' ");
	//strSql.AppendFormat(L" and DetLog.RunningNumber = '%s' ", strRunNum);
	strSql.AppendFormat(L" where DetLog.RunningNumber = '%s' ", strRunNum);

	int nRowsInvolved(0);
	if (0x00 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSql, &nRowsInvolved))
	{
		bRet = true;
	}
	else
	{
		bRet = false;
	}

	return bRet;
}


bool CChargeInfoView::DeteleToCharge(const  CString& strRunNum)
{
	bool bRet(false);
	CString strSql;

	strSql.AppendFormat(L" delete ");
	strSql.AppendFormat(L" Charge ");
	strSql.AppendFormat(L" where RunningNumber = '%s'", strRunNum);

	int nRowsInvolved(0);
	if (0x00 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSql, &nRowsInvolved))
	{
		bRet = true;
	}
	else
	{
		bRet = false;
	}

	return bRet;
}


bool CChargeInfoView::ModifyChargeAmount(const CString& strChargeItem, const CString& strCharge, const CString& strWhy)
{
	const int nIndex = m_lstDetBsnCharge.GetSelectionMark();

	CString strRunNum, strPlateNum;
	//��־���
	strRunNum = m_lstDetBsnCharge.GetItemText(nIndex, 1);
	// ���ƺ���
	strPlateNum = m_lstDetBsnCharge.GetItemText(nIndex, 2);

	CString strSql;
	strSql.AppendFormat(L" update Charge ");
	strSql.AppendFormat(L" set AmountOfCharges = '%s', ChargeingStatus = '%s', ChargeItem = '%s', OperationalOfReason = '%s'", 
		strCharge, DS_RevisionOfCharges, strChargeItem, strWhy);
	strSql.AppendFormat(L" where RunningNumber = '%s' ", strRunNum);

	if (0x00 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSql))
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool CChargeInfoView::CancelOfCharge(const CString& strWhy)
{
	const int nIndex = m_lstDetBsnCharge.GetSelectionMark();

	CString strRunNum, strPlateNum;
	//��־���
	strRunNum = m_lstDetBsnCharge.GetItemText(nIndex, 1);
	// ���ƺ���
	strPlateNum = m_lstDetBsnCharge.GetItemText(nIndex, 2);

	CString strSql;
	// �ȴ����ϻ���Detlog���ƽ̨
	strSql.Format(L"select top(1) * from DetLog where RunningNumber = '%s' order by AutoID desc", strRunNum);
	SDetLog sDetLog;
	if (0xFFFFFFFF != CDetLogService::GetDetLog(theApp.m_pConnection, strSql, sDetLog))
	{
		// ƽ̨�˰�
		SGAMsg sMsg;
		CGAWebServiceLibAPI::GetInstance().BusinessBack(sDetLog, sMsg);

		if (sMsg.code.find(L"1") != -1)
		{
			//_ConnectionPtr pConnection(NULL);

			//// ɾ��PDA������
			//wchar_t wchFilePath[MAX_PATH];
			//ZeroMemory(wchFilePath, sizeof(wchFilePath));
			//if (0x00 == CNHCommonAPI::GetHLDFilePath(L"Config", L"GAWebServiceLib.ini", wchFilePath))
			//{
			//}
			//CSimpleIni si(wchFilePath);
			//// ���ݿ���Ϣ
			//CString strDataSource = si.GetString(L"PDADB", L"DataSource", L"(local)");
			//CString strInitialCatalog = si.GetString(L"PDADB", L"InitialCatalog", L"PDA_DB");
			//CString strUserID = si.GetString(L"PDADB", L"UserID", L"sa");
			//CString strPassword = si.GetString(L"PDADB", L"Password", L"anche@123");

			//if (0x00 == CNHSQLServerDBO::OpenDB(pConnection, strDataSource, strInitialCatalog, strUserID, strPassword))
			//{
			//	int nInvolved(0);
			//	CString strSQL;
			//	strSQL.Format(L"delete from AC_DATA_WG where jylsh=\'%s\';", sDetLog.strReportNumber.c_str());
			//	CNHSQLServerDBO::ExecuteDML(pConnection, strSQL, &nInvolved);
			//	strSQL.Format(L"delete from AC_DATA_DYN where jylsh=\'%s\';", sDetLog.strReportNumber.c_str());
			//	CNHSQLServerDBO::ExecuteDML(pConnection, strSQL, &nInvolved);
			//	strSQL.Format(L"delete from AC_DATA_ROAD where jylsh=\'%s\';", sDetLog.strReportNumber.c_str());
			//	CNHSQLServerDBO::ExecuteDML(pConnection, strSQL, &nInvolved);
			//}

			//CNHSQLServerDBO::CloseDB(pConnection);

			SACMsg sAcMsg;
			CACPostGetLibAPI::GetInstance().DeleteVehDetWJ(strRunNum, sAcMsg);
			if (sAcMsg.code == L"1")
			{
				
			}
		}

		// �ϻ�ȡ�����
		strSql.Format(L"Update DetLog set DetStatus=\'%s\',CancelReason=\'%s\' where DetPeriodID=\'%s\'", 
			L"CANDET",
			L"����־��������ˮ�˰�",
			sDetLog.strDetPeriodID.c_str()
			);
		int nRowsInvolved(0);
		CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSql, &nRowsInvolved);
	}
	// �շѱ���
	strSql.AppendFormat(L" update Charge ");
	strSql.AppendFormat(L" set AmountOfCharges = '%s', ChargeingStatus = '%s', ChargeItem = '%s', OperationalOfReason = '%s' ",
		L"0", DS_CancelOfCharge, L"", strWhy);
	strSql.AppendFormat(L" where RunningNumber = '%s' ", strRunNum);

	if (0x00 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSql))
	{
		return true;
	}
	else
	{
		return false;
	}

}

CString CChargeInfoView::IsBsnFined(const std::wstring& strRunNum)
{
	CString strDetSta;

	CString strSql;
	SDetLog sDetLogToUpdate;
	strSql.Format(L"SELECT * FROM DetLog WHERE RunningNumber = '%s'", strRunNum.c_str());
	CDetLogService::GetDetLog(theApp.m_pConnection, strSql.GetString(), sDetLogToUpdate);

	SDetPeriod sDetPerToUpdate;
	strSql.Format(L"SELECT * FROM DetPeriod WHERE DetPeriodID = '%s'", sDetLogToUpdate.strDetPeriodID.c_str());
	CDetPeriodService::GetDetPeriod(theApp.m_pConnection, strSql.GetString(), sDetPerToUpdate);

	const bool bFined = CJudge::MFD_GetHasDetItem(theApp.m_pConnection, strRunNum, sDetPerToUpdate);

	if (!bFined)
	{
		strDetSta = DS_ToDet;
	}
	else
	{
		strDetSta = DS_FinDet;
	}

	return strDetSta;
}

void CChargeInfoView::OnBnClickedBtnDeleteRecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const int nIndex = m_lstDetBsnCharge.GetSelectionMark();

	if (nIndex == -1)
	{
		MessageBox(L"��ѡ�����շ��б�ļ�¼���в���", DLG_CAPTION);
		// ��������Ϊδѡ��
		m_lstDetBsnNoCharge.SetSelectionMark(-1);
		m_lstDetBsnCharge.SetSelectionMark(-1);
		return;
	}

	CString strTemp;
	//��־���
	strTemp = m_lstDetBsnCharge.GetItemText(nIndex, 1);

	SCharge sCharge;
	CString strSql;
	strSql.Format(L"SELECT * FROM Charge WHERE RunningNumber = '%s'", strTemp);
	if (0x01 !=CChargeService::GetCharge(theApp.m_pConnection, strSql, sCharge))
	{
		MessageBox(L"��ȡ�շ�ʧ��", DLG_CAPTION);
		// ��������Ϊδѡ��
		m_lstDetBsnNoCharge.SetSelectionMark(-1);
		m_lstDetBsnCharge.SetSelectionMark(-1);
		return;
	}

	COleDateTime otdTotal, otdChargeTime;
	otdTotal = COleDateTime::GetCurrentTime();
	if (!otdChargeTime.ParseDateTime(sCharge.strChargingTime.c_str()))
	{
		MessageBox(L"��ȡ�շ�ʱ��ʧ��", DLG_CAPTION);
		// ��������Ϊδѡ��
		m_lstDetBsnNoCharge.SetSelectionMark(-1);
		m_lstDetBsnCharge.SetSelectionMark(-1);
		return;
	}

	int nYTotal(0), nMTotal(0), nDTotal(0);
	int nYChargeTime(0), nMChargeTime(0), nDChargeTime(0);
	nYTotal = otdTotal.GetYear();
	nMTotal = otdTotal.GetMonth();
	nDTotal = otdTotal.GetDay();
	nYChargeTime = otdChargeTime.GetYear();
	nMChargeTime = otdChargeTime.GetMonth();
	nDChargeTime = otdChargeTime.GetDay();

	if (nYTotal == nYChargeTime 
		&& nMTotal == nMChargeTime
		&& nDTotal == nDChargeTime)
	{
		MessageBox(L"����ɾ������ļ�¼", DLG_CAPTION);
		// ��������Ϊδѡ��
		m_lstDetBsnNoCharge.SetSelectionMark(-1);
		m_lstDetBsnCharge.SetSelectionMark(-1);
		return;
	}
	CString strMsg;
	strMsg.AppendFormat(L"���ƣ�%s, ��־��ţ�%s;", sCharge.strPlateNumber.c_str(), sCharge.strRunningNumber.c_str());
	if (DeteleToCharge(strTemp))
	{
		strMsg.AppendFormat(L"ɾ����¼�ɹ�");
		MessageBox(L"ɾ����¼�ɹ�", DLG_CAPTION);
	}
	else
	{
		strMsg.AppendFormat(L"ɾ����¼ʧ��");
		MessageBox(L"ɾ����¼ʧ��", DLG_CAPTION);
	}
	PrintLog(strMsg);
	// ��������Ϊδѡ��
	m_lstDetBsnNoCharge.SetSelectionMark(-1);
	m_lstDetBsnCharge.SetSelectionMark(-1);
}

bool CChargeInfoView::VerifyEmpPerm(const SToll_Operator& sToll_Operator)
{
	std::string strDBPerm("");
	if (0xFFFFFFFF == CTollOperatorService::GetTollOperatorPerm(theApp.m_pConnection, sToll_Operator.strName.c_str(), strDBPerm))
	{
		return false;
	}

	// It's the administrator
	if (strDBPerm.find("It's the administrator") != std::string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool CChargeInfoView::SaveArrearsToDB(const CString& strUnitName, const CString& strCharge)
{

	const int nIndex = m_lstDetBsnNoCharge.GetSelectionMark();

	if (nIndex == -1)
	{
		return false;
	}

	SBillOfArrears sBillOfArrears;

	// �Ȼ�ȡ֮ǰ������
	CString strSql;
	strSql.Format(L"SELECT * FROM Bill_Of_Arrears WHERE Unit_Name = '%s'", strUnitName);

	CBillOfArrearsService::GetBillOfArrears(theApp.m_pConnection, strSql, sBillOfArrears);

	// ��δ��ȡ���
	float fOutstanding_Amount = _wtof(sBillOfArrears.strOutstanding_Amount.c_str()) + _wtof(strCharge);
	// ������ȡ���
	float fAmount_Received = _wtof(sBillOfArrears.strAmount_Received.c_str());
	// �ܽ��
	float fTotal_Amount = fOutstanding_Amount + fAmount_Received;

	CString strTemp;
	sBillOfArrears.strUnit_Name = strUnitName.GetString();
	strTemp.Format(L"%.4f", fOutstanding_Amount);
	sBillOfArrears.strOutstanding_Amount = strTemp.GetString();
	strTemp.Format(L"%.4f", fAmount_Received);
	sBillOfArrears.strAmount_Received = strTemp.GetString();
	strTemp.Format(L"%.4f", fTotal_Amount);
	sBillOfArrears.strTotal_Amount = strTemp.GetString();
	sBillOfArrears.strUpdate_Time = COleDateTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S")).GetString();

	if (0xFFFFFFFF == CBillOfArrearsService::SetBillOfArrears(theApp.m_pConnection, sBillOfArrears))
	{
		return false;
	}
	else
	{
	}


	return true;
}
