// DetCountStatView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SMCIS.h"
#include "DetCountStatView.h"

#define DLG_CAPTION L"�շ�ͳ��"
// CDetCountStatView

IMPLEMENT_DYNCREATE(CDetCountStatView, CFormView)

CDetCountStatView::CDetCountStatView()
	: CFormView(CDetCountStatView::IDD)
	, m_pGridCtrl(NULL)
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
}

CDetCountStatView::~CDetCountStatView()
{
	m_fontDlgFont.DeleteObject();

	if (m_pGridCtrl != NULL)
	{
		delete m_pGridCtrl;
		m_pGridCtrl = NULL;
	}
}

void CDetCountStatView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_STAT, m_lstVehCount);
	DDX_Control(pDX, IDC_DTP_COND_BEGIN_TIME, m_dtcBegTime);
	DDX_Control(pDX, IDC_DTP_COND_END_TIME, m_dtcEndTime);
	DDX_Control(pDX, IDC_BTN_STAT, m_btnStat);
	DDX_Control(pDX, IDC_BTN_PRINT, m_btnPrint);
	DDX_Control(pDX, IDC_BTN_EXPORT, m_btnExport);
	DDX_Control(pDX, IDC_CB_STAT_TYPE, m_cbStatType);
}

BEGIN_MESSAGE_MAP(CDetCountStatView, CFormView)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_STAT, &CDetCountStatView::OnBnClickedBtnStat)
	ON_BN_CLICKED(IDC_BTN_PRINT, &CDetCountStatView::OnBnClickedBtnPrint)
	ON_BN_CLICKED(IDC_BTN_EXPORT, &CDetCountStatView::OnBnClickedBtnExport)
END_MESSAGE_MAP()


// CDetCountStatView ���

#ifdef _DEBUG
void CDetCountStatView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDetCountStatView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDetCountStatView ��Ϣ�������


void CDetCountStatView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	InitCtrls();
}


void CDetCountStatView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	//float fsp[2];
	//POINT Newp;//��ȡ���ڶԻ���Ĵ�С(VS2005����CPOINT)
	//CRect recta;
	//GetClientRect(&recta); //ȡ�ͻ�����С
	//Newp.x=recta.right-recta.left;
	//Newp.y=recta.bottom-recta.top;
	//fsp[0]=(float)Newp.x/m_Old.x;
	//fsp[1]=(float)Newp.y/m_Old.y;

	//if (fsp[0] != 0 && fsp[1] != 0)
	//{
	//	CRect Rect;
	//	int woc;
	//	CPoint OldTLPoint,TLPoint; //���Ͻ�
	//	CPoint OldBRPoint,BRPoint; //���½�
	//	HWND hwndChild=::GetWindow(m_hWnd,GW_CHILD); //�г����пؼ�

	//	while(hwndChild)
	//	{
	//		woc=::GetDlgCtrlID(hwndChild);//ȡ��ID
	//		GetDlgItem(woc)->GetWindowRect(Rect);
	//		ScreenToClient(Rect);
	//		OldTLPoint = Rect.TopLeft(); 
	//		TLPoint.x = long(OldTLPoint.x*fsp[0]); 
	//		TLPoint.y = long(OldTLPoint.y*fsp[1]);
	//		OldBRPoint = Rect.BottomRight();
	//		BRPoint.x = long(OldBRPoint.x *fsp[0]); 
	//		BRPoint.y = long(OldBRPoint.y *fsp[1]); //�߶Ȳ��ɶ��Ŀؼ�����:combBox),��Ҫ�ı��ֵ.
	//		Rect.SetRect(TLPoint,BRPoint); 
	//		GetDlgItem(woc)->MoveWindow(Rect,TRUE);
	//		hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);
	//	}
	//	m_Old=Newp;
	//}

	if (m_pGridCtrl->GetSafeHwnd())
	{
		CRect rect;
		GetDlgItem(IDC_LST_STAT)->GetClientRect(rect);
		m_pGridCtrl->MoveWindow(rect);
	}
}


void CDetCountStatView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CFormView::OnTimer(nIDEvent);
}


BOOL CDetCountStatView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (m_pGridCtrl && IsWindow(m_pGridCtrl->m_hWnd))
		if (m_pGridCtrl->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
			return TRUE;

	return CFormView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CDetCountStatView::InitCtrls(void)
{
	GetDocument()->SetTitle(DLG_CAPTION);

	SetDlgFont();

	InitGirdCtrl();

	COleDateTime OleCurrentDate = COleDateTime::GetCurrentTime();
	m_dtcBegTime.SetRange(NULL, &OleCurrentDate);
	m_dtcEndTime.SetRange(NULL, &OleCurrentDate);
	
	m_btnStat.SetFlat(FALSE);
	m_btnPrint.SetFlat(FALSE);
	m_btnExport.SetFlat(FALSE);


	m_cbStatType.AddString(L"");
	m_cbStatType.AddString(L"�շ�����ͳ��");
	m_cbStatType.AddString(L"ÿ̨��ͳ��");
	m_cbStatType.AddString(L"����ͳ��");
	m_cbStatType.AddString(L"����/����ͳ��");
	
}

void CDetCountStatView::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);
		pWnd = pWnd->GetNextWindow();
	}
}

void CDetCountStatView::InitGirdCtrl(void)
{
	CDC *pDC;
	if (m_pGridCtrl == NULL)
	{
		// ���� GridCtrl ����
		m_pGridCtrl = new CGridCtrl;
		if (!m_pGridCtrl) return;

		// ���� Gridctrl ����
		CRect rect;
		GetDlgItem(IDC_LST_STAT)->GetClientRect(rect); // �õ���ʾ����
		m_pGridCtrl->Create(rect, &m_lstVehCount, IDC_LST_STAT);

		try 
		{
			m_pGridCtrl->SetRowCount(2); // ��ʼ������
			m_pGridCtrl->SetColumnCount(3);	// ��ʼ������
			m_pGridCtrl->SetFixedRowCount(2);	// ���ñ�ͷ����
			m_pGridCtrl->SetFixedColumnCount(1);// ���ñ�ͷ����
		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
			return;
		}

		// ���ÿ������
		for (int nRow = 0; nRow < m_pGridCtrl->GetRowCount(); nRow++)
		{
			for (int nCol = 0; nCol < m_pGridCtrl->GetColumnCount(); nCol++)
			{
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = nRow;
				Item.col = nCol;

				if (nRow < 1)
				{
					Item.nFormat = DT_LEFT|DT_WORDBREAK;
					switch(nCol)
					{
					case 1:
						{
							Item.szText.Format(L"��ѯͳ��");
						}
						break;
					}
				}
				else if (nCol < 1)
				{
					Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					if(nRow>=2)
					{
						Item.szText.Format(_T(" %d"), nRow/*-2*/);
					}
				}
				else
				{
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					Item.szText.Format(_T(" "));
				}
				m_pGridCtrl->SetItem(&Item);
			}
		}
		m_pGridCtrl->AutoSize();
		m_pGridCtrl->SetRowHeight(0, 2*m_pGridCtrl->GetRowHeight(0));
	}

	pDC = m_pGridCtrl->GetDC();
	CSize cellSize;
	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	CRect tempRect;

	if (m_pGridCtrl->GetSafeHwnd())
	{
		// �ϲ���Ԫ��(�У��У��кϲ������кϲ���)
		m_pGridCtrl->SetFixedCellCombine(0,0,1,0);
		m_pGridCtrl->SetFixedCellCombine(0,1,0,1);
		//m_pGridCtrl->SetFixedCellCombine(1,1,0,2);

		//Item.col = 1;
		//Item.row = 1;
		//Item.szText.Format(L"��");
		//m_pGridCtrl->SetItem(&Item);
		//cellSize = pDC->GetTextExtent(L"��");
		//m_pGridCtrl->SetColumnWidth(Item.col, cellSize.cx+10);

		//m_pGridCtrl->SetFixedCellCombine(1,4,0,2);
		//Item.col=4;
		//Item.row=1;
		//Item.szText.Format(_T("��"));
		//m_pGridCtrl->SetItem(&Item);
		//cellSize=pDC->GetTextExtent(_T("��"));
		//m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);

		//m_pGridCtrl->SetFixedCellCombine(1,7,0,2);
		//Item.col=7;
		//Item.row=1;
		//Item.szText.Format(_T("��"));
		//m_pGridCtrl->SetItem(&Item);
		//cellSize=pDC->GetTextExtent(_T("��"));
		//m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);

		for (Item.col=1, Item.row=1; Item.col<=2; Item.col++)
		{
			switch(Item.col)
			{
			case 1:
				{
					Item.szText.Format(L"���շѽ��");
				}
				break;
			case 2:
				{
					Item.szText.Format(L"���շ�����");
				}
				break;
			}
			m_pGridCtrl->SetItem(&Item);
			cellSize=pDC->GetTextExtent(Item.szText);
			m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
		}
	}

	// �������и�
	m_pGridCtrl->SetColumnWidth(0, 300);
	for (int i=1;i<=2;i++)
	{
		m_pGridCtrl->SetColumnWidth(i, 255);
	}
	//m_pGridCtrl->ExpandToFit();
}

void CDetCountStatView::OnBnClickedBtnStat()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_pGridCtrl->GetSafeHwnd())
	{
		return;
	}
	// ɾ��֮ǰ��¼
	m_pGridCtrl->DeleteNonFixedRows();

	/// ��ȡͳ��ʱ��
	COleDateTime odtBeginTime(COleDateTime::GetCurrentTime());
	COleDateTime odtEndTime(COleDateTime::GetCurrentTime());
	m_dtcBegTime.GetTime(odtBeginTime);
	m_dtcEndTime.GetTime(odtEndTime);

	if (odtEndTime < odtBeginTime)
	{
		MessageBox(L"�������ڲ������ڿ�ʼ����,����������ͳ����������!", L"�շ�ͳ��", MB_OK|MB_ICONWARNING);
		return;
	}

	CString strStatType;
	m_cbStatType.GetWindowTextW(strStatType);

	if (strStatType.Find(L"�շ�����ͳ��") != std::string::npos)
	{
		DetChargeStat();
	}
	else if (strStatType.Find(L"ÿ̨��ͳ��") != std::string::npos)
	{
		StatisticsOfEachVehicle();
	}
	else if (strStatType.Find(L"����ͳ��") != std::string::npos)
	{
		MiscellaneousStatistics();
	}
	else if (strStatType.Find(L"����/����ͳ��") != std::string::npos)
	{
		MiscellaneousVehicleStatistics();
	}
	else
	{
		MessageBox(L"��ѡ��ͳ������", L"�շ�ͳ��", MB_OK|MB_ICONWARNING);
		m_pGridCtrl->Invalidate(); // ˢ�¿ؼ�
	}
	
}


void CDetCountStatView::OnBnClickedBtnPrint()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pGridCtrl->GetSafeHwnd())
	{
		m_pGridCtrl->AutoSize();
		m_pGridCtrl->Print();
	}
}


void CDetCountStatView::OnBnClickedBtnExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ����
	if (m_pGridCtrl->GetSafeHwnd())
	{
		GetDlgItem(IDC_BTN_EXPORT)->EnableWindow(FALSE);
		YExcel::BasicExcel excel;
		excel.New(1);
		YExcel::BasicExcelWorksheet* worksheet = excel.GetWorksheet("Sheet1");
		if (worksheet)
		{
			int nCol = 0, nRow = 0;
			for (int nRow=0; nRow<m_pGridCtrl->GetRowCount(); nRow++)
			{
				for (int nCol=0; nCol<m_pGridCtrl->GetColumnCount(); nCol++)
				{
					worksheet->Cell(nRow, nCol)->Set(m_pGridCtrl->GetItemText(nRow, nCol));
				}
			}

			// ����񱣴�
			CString strSavePath;
			CString strFileName;
			strFileName.Format(L"��ѯͳ�ƽ��%s.xls", CTime::GetCurrentTime().Format(L"%Y%m%d%H%M%S"));

			CFileDialog excelFile(FALSE, L"xls", strFileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"Excel Files (*.xls)|*.xls||", NULL, 0);

			if( excelFile.DoModal() == IDOK)
			{
				strSavePath = excelFile.GetPathName();//excelFile.GetFileName();	
				excel.SaveAs(strSavePath.GetBuffer());
				strSavePath.ReleaseBuffer();
			}
		}
		GetDlgItem(IDC_BTN_EXPORT)->EnableWindow(TRUE);
	}
}

bool CDetCountStatView::QuerySqlDB(_RecordsetPtr& pRecordset, const COleDateTime& odtBeginTime, const COleDateTime& odtEndTime)
{
	CStringW strSQL;

	strSQL.AppendFormat(L" select * ");
	strSQL.AppendFormat(L" from Charge ");
	strSQL.AppendFormat(L" where ChargeingStatus <> '%s' ", DS_NoCharge);
	strSQL.AppendFormat(L" and (ChargingTime between '%s' and '%s') ", odtBeginTime.Format(L"%Y-%m-%d 00:00:00"), odtEndTime.Format(L"%Y-%m-%d 23:59:59"));

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSQL))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
		return false;
	}

	return true;
}

void CDetCountStatView::DetChargeStat(void)
{
	// ��ȡͳ����ֹʱ��
	COleDateTime odtBeginTime(COleDateTime::GetCurrentTime());
	COleDateTime odtEndTime(COleDateTime::GetCurrentTime());
	m_dtcBegTime.GetTime(odtBeginTime);
	m_dtcEndTime.GetTime(odtEndTime);

	struct StatStru
	{
		// �ܽ��
		float fAmountOfCharges;
		// ̨��
		int nTotNum;

		StatStru() {ZeroMemory(this, sizeof(StatStru));}
	};
	std::map<CStringW,StatStru> mapStaResult; // ͳ�ƽ��

	_RecordsetPtr pRecordset(NULL);
	if (CDetCountStatView::QuerySqlDB(pRecordset, odtBeginTime, odtEndTime))
	{
		CString str(L"");
		_variant_t v;

		int nTotalAmount(0);
		float fTotalQuantity(0.0f);
		while (!pRecordset->adoEOF)
		{
			CStringW Category;
			v.ChangeType(VT_NULL);
			CNHSQLServerDBO::GetFieldValue(pRecordset, v, _T("ChargeingStatus"));
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				Category = (wchar_t*)(_bstr_t)v;
			}
			else
			{
				Category = L"";
			}

			const int nCount = (int)mapStaResult.count(Category);
			if (0 == nCount)
			{
				// û�йؼ��֣��Ȳ��ֵ
				StatStru ss;
				mapStaResult[Category] = ss;
			}

			mapStaResult[Category].nTotNum++;
			nTotalAmount++;

			float fAmountOfCharges(0.0f);
			v.ChangeType(VT_NULL);
			CNHSQLServerDBO::GetFieldValue(pRecordset, v, _T("AmountOfCharges"));
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				fAmountOfCharges = static_cast<float>(v);
			}
			mapStaResult[Category].fAmountOfCharges = fAmountOfCharges + mapStaResult[Category].fAmountOfCharges;
			fTotalQuantity += fAmountOfCharges;
			pRecordset->MoveNext();
		}
		mapStaResult[L"�ܽ��"].nTotNum = nTotalAmount;
		mapStaResult[L"�ܽ��"].fAmountOfCharges = fTotalQuantity;
	}

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
	}

	// ��ͳ�ƽ����ʾ���ؼ�
	GV_ITEM Item;
	Item.col=1;
	Item.row=0;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.szText.Format(L"%s", L"�շ�����ͳ��");
	m_pGridCtrl->SetItem(&Item);

	// ����m_pGridCtrl����ͳ��ʱ��
	CString strTemp;
	strTemp.Format(L"%s��%s", odtBeginTime.Format(L"%Y-%m-%d"), odtEndTime.Format(L"%Y-%m-%d"));
	m_pGridCtrl->SetPrintStatTime(strTemp);

	int nRow(0);
	std::map<CStringW,StatStru>::iterator iter;

	for (iter=mapStaResult.begin(); iter!=mapStaResult.end(); ++iter)
	{
		nRow++;

		m_pGridCtrl->InsertRow(ToStatusName(iter->first));
		int nCol(0);
		strTemp.Format(L"%.4f", iter->second.fAmountOfCharges);
		m_pGridCtrl->SetItemText(1+nRow, ++nCol, strTemp);
		strTemp.Format(L"%d", iter->second.nTotNum);
		m_pGridCtrl->SetItemText(1+nRow, ++nCol, strTemp);
	}

	m_pGridCtrl->Invalidate(); // ˢ�¿ؼ�
}

CStringW CDetCountStatView::ToStatusName(const CStringW& strStatusCode)
{
	CString strTemp;
	strTemp.Format(L"%s", strStatusCode);
	if (strStatusCode.Find(DS_NoCharge) != -1)
	{
		return L"δ�շ�";
	}
	else if (strStatusCode.Find(DS_Chargee) != -1)
	{
		return L"���շ�";
	}
	else if (strStatusCode.Find(DS_Redo) != -1)
	{
		return L"����";
	}
	else if (strStatusCode.Find(DS_CancelOfCharge) != -1)
	{
		return L"ȡ���շ�";
	}
	else if (strStatusCode.Find(DS_RevisionOfCharges) != -1)
	{
		return L"�޸��շ�";
	}
	else
	{
		return strTemp;
	}
}

void CDetCountStatView::StatisticsOfEachVehicle(void)
{
	// ��ȡͳ����ֹʱ��
	COleDateTime odtBeginTime(COleDateTime::GetCurrentTime());
	COleDateTime odtEndTime(COleDateTime::GetCurrentTime());
	m_dtcBegTime.GetTime(odtBeginTime);
	m_dtcEndTime.GetTime(odtEndTime);

	struct StatStru
	{
		// �ܽ��
		float fAmountOfCharges;
		// ̨��
		int nTotNum;

		StatStru() {ZeroMemory(this, sizeof(StatStru));}
	};
	std::map<CStringW,StatStru> mapStaResult; // ͳ�ƽ��

	_RecordsetPtr pRecordset(NULL);
	if (CDetCountStatView::QuerySqlDB(pRecordset, odtBeginTime, odtEndTime))
	{
		CString str(L"");
		_variant_t v;

		int nTotalAmount(0);
		float fTotalQuantity(0.0f);
		while (!pRecordset->adoEOF)
		{
			CStringW Category;
			v.ChangeType(VT_NULL);
			CNHSQLServerDBO::GetFieldValue(pRecordset, v, _T("PlateNumber"));
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				Category = (wchar_t*)(_bstr_t)v;
			}
			else
			{
				Category = L"";
			}

			if (Category.Find(L"����") != std::string::npos)
			{
				pRecordset->MoveNext();
				continue;
			}

			const int nCount = (int)mapStaResult.count(Category);
			if (0 == nCount)
			{
				// û�йؼ��֣��Ȳ��ֵ
				StatStru ss;
				mapStaResult[Category] = ss;
			}

			mapStaResult[Category].nTotNum++;
			nTotalAmount++;

			float fAmountOfCharges(0.0f);
			v.ChangeType(VT_NULL);
			CNHSQLServerDBO::GetFieldValue(pRecordset, v, _T("AmountOfCharges"));
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				fAmountOfCharges = static_cast<float>(v);
			}
			mapStaResult[Category].fAmountOfCharges = fAmountOfCharges + mapStaResult[Category].fAmountOfCharges;
			fTotalQuantity += fAmountOfCharges;
			pRecordset->MoveNext();
		}
		mapStaResult[L"�ܽ��"].nTotNum = nTotalAmount;
		mapStaResult[L"�ܽ��"].fAmountOfCharges = fTotalQuantity;
	}

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
	}

	// ��ͳ�ƽ����ʾ���ؼ�
	GV_ITEM Item;
	Item.col=1;
	Item.row=0;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.szText.Format(L"%s", L"ÿ̨��ͳ��");
	m_pGridCtrl->SetItem(&Item);

	// ����m_pGridCtrl����ͳ��ʱ��
	CString strTemp;
	strTemp.Format(L"%s��%s", odtBeginTime.Format(L"%Y-%m-%d"), odtEndTime.Format(L"%Y-%m-%d"));
	m_pGridCtrl->SetPrintStatTime(strTemp);

	int nRow(0);
	std::map<CStringW,StatStru>::iterator iter;

	for (iter=mapStaResult.begin(); iter!=mapStaResult.end(); ++iter)
	{
		nRow++;

		m_pGridCtrl->InsertRow(ToStatusName(iter->first));
		int nCol(0);
		strTemp.Format(L"%.4f", iter->second.fAmountOfCharges);
		m_pGridCtrl->SetItemText(1+nRow, ++nCol, strTemp);
		strTemp.Format(L"%d", iter->second.nTotNum);
		m_pGridCtrl->SetItemText(1+nRow, ++nCol, strTemp);
	}

	m_pGridCtrl->Invalidate(); // ˢ�¿ؼ�

}

void CDetCountStatView::MiscellaneousStatistics(void)
{
	// ��ȡͳ����ֹʱ��
	COleDateTime odtBeginTime(COleDateTime::GetCurrentTime());
	COleDateTime odtEndTime(COleDateTime::GetCurrentTime());
	m_dtcBegTime.GetTime(odtBeginTime);
	m_dtcEndTime.GetTime(odtEndTime);

	struct StatStru
	{
		// �ܽ��
		float fAmountOfCharges;
		// ̨��
		int nTotNum;

		StatStru() {ZeroMemory(this, sizeof(StatStru));}
	};
	std::map<CStringW,StatStru> mapStaResult; // ͳ�ƽ��

	_RecordsetPtr pRecordset(NULL);
	if (CDetCountStatView::QuerySqlDB(pRecordset, odtBeginTime, odtEndTime))
	{
		CString str(L"");
		_variant_t v;

		int nTotalAmount(0);
		float fTotalQuantity(0.0f);
		while (!pRecordset->adoEOF)
		{
			CStringW Category, strPlateNumber;
			v.ChangeType(VT_NULL);
			CNHSQLServerDBO::GetFieldValue(pRecordset, v, _T("PlateNumber"));
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				strPlateNumber = (wchar_t*)(_bstr_t)v;
			}
			else
			{
				strPlateNumber = L"";
			}

			if (strPlateNumber.Find(L"����") == std::string::npos)
			{
				pRecordset->MoveNext();
				continue;
			}

			// ChargeItem
			v.ChangeType(VT_NULL);
			CNHSQLServerDBO::GetFieldValue(pRecordset, v, _T("ChargeItem"));
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				Category = (wchar_t*)(_bstr_t)v;
			}
			else
			{
				Category = L"";
			}

			const int nCount = (int)mapStaResult.count(Category);
			if (0 == nCount)
			{
				// û�йؼ��֣��Ȳ��ֵ
				StatStru ss;
				mapStaResult[Category] = ss;
			}

			mapStaResult[Category].nTotNum++;
			nTotalAmount++;

			float fAmountOfCharges(0.0f);
			v.ChangeType(VT_NULL);
			CNHSQLServerDBO::GetFieldValue(pRecordset, v, _T("AmountOfCharges"));
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				fAmountOfCharges = static_cast<float>(v);
			}
			mapStaResult[Category].fAmountOfCharges = fAmountOfCharges + mapStaResult[Category].fAmountOfCharges;
			fTotalQuantity += fAmountOfCharges;
			pRecordset->MoveNext();
		}
		mapStaResult[L"�ܽ��"].nTotNum = nTotalAmount;
		mapStaResult[L"�ܽ��"].fAmountOfCharges = fTotalQuantity;
	}

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
	}

	// ��ͳ�ƽ����ʾ���ؼ�
	GV_ITEM Item;
	Item.col=1;
	Item.row=0;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.szText.Format(L"%s", L"ÿ̨��ͳ��");
	m_pGridCtrl->SetItem(&Item);

	// ����m_pGridCtrl����ͳ��ʱ��
	CString strTemp;
	strTemp.Format(L"%s��%s", odtBeginTime.Format(L"%Y-%m-%d"), odtEndTime.Format(L"%Y-%m-%d"));
	m_pGridCtrl->SetPrintStatTime(strTemp);

	int nRow(0);
	std::map<CStringW,StatStru>::iterator iter;

	for (iter=mapStaResult.begin(); iter!=mapStaResult.end(); ++iter)
	{
		nRow++;

		m_pGridCtrl->InsertRow(ToStatusName(iter->first));
		int nCol(0);
		strTemp.Format(L"%.4f", iter->second.fAmountOfCharges);
		m_pGridCtrl->SetItemText(1+nRow, ++nCol, strTemp);
		strTemp.Format(L"%d", iter->second.nTotNum);
		m_pGridCtrl->SetItemText(1+nRow, ++nCol, strTemp);
	}

	m_pGridCtrl->Invalidate(); // ˢ�¿ؼ�
}

void CDetCountStatView::MiscellaneousVehicleStatistics(void)
{
	// ��ȡͳ����ֹʱ��
	COleDateTime odtBeginTime(COleDateTime::GetCurrentTime());
	COleDateTime odtEndTime(COleDateTime::GetCurrentTime());
	m_dtcBegTime.GetTime(odtBeginTime);
	m_dtcEndTime.GetTime(odtEndTime);

	struct StatStru
	{
		// �ܽ��
		float fAmountOfCharges;
		// ̨��
		int nTotNum;

		StatStru() {ZeroMemory(this, sizeof(StatStru));}
	};
	std::map<CStringW,StatStru> mapStaResult; // ͳ�ƽ��

	_RecordsetPtr pRecordset(NULL);
	if (CDetCountStatView::QuerySqlDB(pRecordset, odtBeginTime, odtEndTime))
	{
		CString str(L"");
		_variant_t v;

		int nTotalAmount(0);
		float fTotalQuantity(0.0f);
		while (!pRecordset->adoEOF)
		{
			CStringW Category;
			v.ChangeType(VT_NULL);
			CNHSQLServerDBO::GetFieldValue(pRecordset, v, _T("PlateNumber"));
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				Category = (wchar_t*)(_bstr_t)v;
			}
			else
			{
				Category = L"";
			}

			if (Category.Find(L"����") == std::string::npos)
			{
				Category = L"����";
			}
			else
			{
				Category = L"����";
			}

			const int nCount = (int)mapStaResult.count(Category);
			if (0 == nCount)
			{
				// û�йؼ��֣��Ȳ��ֵ
				StatStru ss;
				mapStaResult[Category] = ss;
			}

			mapStaResult[Category].nTotNum++;
			nTotalAmount++;

			float fAmountOfCharges(0.0f);
			v.ChangeType(VT_NULL);
			CNHSQLServerDBO::GetFieldValue(pRecordset, v, _T("AmountOfCharges"));
			if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
			{
				fAmountOfCharges = static_cast<float>(v);
			}
			mapStaResult[Category].fAmountOfCharges = fAmountOfCharges + mapStaResult[Category].fAmountOfCharges;
			fTotalQuantity += fAmountOfCharges;
			pRecordset->MoveNext();
		}
		mapStaResult[L"�ܽ��"].nTotNum = nTotalAmount;
		mapStaResult[L"�ܽ��"].fAmountOfCharges = fTotalQuantity;
	}

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
	}

	// ��ͳ�ƽ����ʾ���ؼ�
	GV_ITEM Item;
	Item.col=1;
	Item.row=0;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.szText.Format(L"%s", L"ÿ̨��ͳ��");
	m_pGridCtrl->SetItem(&Item);

	// ����m_pGridCtrl����ͳ��ʱ��
	CString strTemp;
	strTemp.Format(L"%s��%s", odtBeginTime.Format(L"%Y-%m-%d"), odtEndTime.Format(L"%Y-%m-%d"));
	m_pGridCtrl->SetPrintStatTime(strTemp);

	int nRow(0);
	std::map<CStringW,StatStru>::iterator iter;

	for (iter=mapStaResult.begin(); iter!=mapStaResult.end(); ++iter)
	{
		nRow++;

		m_pGridCtrl->InsertRow(ToStatusName(iter->first));
		int nCol(0);
		strTemp.Format(L"%.4f", iter->second.fAmountOfCharges);
		m_pGridCtrl->SetItemText(1+nRow, ++nCol, strTemp);
		strTemp.Format(L"%d", iter->second.nTotNum);
		m_pGridCtrl->SetItemText(1+nRow, ++nCol, strTemp);
	}

	m_pGridCtrl->Invalidate(); // ˢ�¿ؼ�
}