// VehCountStatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Charge.h"
#include "VehCountStatDlg.h"
#include "afxdialogex.h"


// CVehCountStatDlg �Ի���

IMPLEMENT_DYNAMIC(CVehCountStatDlg, CDialogEx)

CVehCountStatDlg::CVehCountStatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVehCountStatDlg::IDD, pParent)
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

CVehCountStatDlg::~CVehCountStatDlg()
{
	m_fontDlgFont.DeleteObject();

	if (m_pGridCtrl != NULL)
	{
		delete m_pGridCtrl;
		m_pGridCtrl = NULL;
	}
}

void CVehCountStatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_STAT, m_lstVehCount);
	DDX_Control(pDX, IDC_DTP_COND_BEGIN_TIME, m_dtcBegTime);
	DDX_Control(pDX, IDC_DTP_COND_END_TIME, m_dtcEndTime);
	DDX_Control(pDX, IDC_BTN_STAT, m_btnStat);
	DDX_Control(pDX, IDC_BTN_PRINT, m_btnPrint);
	DDX_Control(pDX, IDC_BTN_EXPORT, m_btnExport);
}


BEGIN_MESSAGE_MAP(CVehCountStatDlg, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_STAT, &CVehCountStatDlg::OnClickedBtnStat)
	ON_BN_CLICKED(IDC_BTN_PRINT, &CVehCountStatDlg::OnClickedBtnPrint)
	ON_BN_CLICKED(IDC_BTN_EXPORT, &CVehCountStatDlg::OnClickedBtnExport)
END_MESSAGE_MAP()


// CVehCountStatDlg ��Ϣ�������


BOOL CVehCountStatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowTextW(L"��ѯͳ��");
	// ��ʼ���ؼ�
	InitCtrls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CVehCountStatDlg::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (m_pGridCtrl && IsWindow(m_pGridCtrl->m_hWnd))
		if (m_pGridCtrl->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
			return TRUE;

	return CDialogEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CVehCountStatDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (m_pGridCtrl->GetSafeHwnd())
	{
		CRect rect;
		GetDlgItem(IDC_LST_STAT)->GetClientRect(rect);
		m_pGridCtrl->MoveWindow(rect);
	}
}


void CVehCountStatDlg::OnClickedBtnStat()
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
		MessageBox(L"�������ڲ������ڿ�ʼ����,����������ͳ����������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
		return;
	}

	DetChargeStat();
}


void CVehCountStatDlg::OnClickedBtnPrint()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pGridCtrl->GetSafeHwnd())
	{
		m_pGridCtrl->AutoSize();
		m_pGridCtrl->Print();
	}
}


void CVehCountStatDlg::OnClickedBtnExport()
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


void CVehCountStatDlg::InitCtrls(void)
{
	SetDlgFont();

	InitGirdCtrl();

	COleDateTime OleCurrentDate = COleDateTime::GetCurrentTime();
	m_dtcBegTime.SetRange(NULL, &OleCurrentDate);
	m_dtcEndTime.SetRange(NULL, &OleCurrentDate);
	
	m_btnStat.SetIcon(IDI_ICON_CURVE);
	m_btnStat.SetFlat(FALSE);
	m_btnPrint.SetIcon(IDI_ICON_PRINT);
	m_btnPrint.SetFlat(FALSE);
	m_btnExport.SetIcon(IDI_ICON_SAVE);
	m_btnExport.SetFlat(FALSE);
}

void CVehCountStatDlg::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);
		pWnd = pWnd->GetNextWindow();
	}
}

void CVehCountStatDlg::InitGirdCtrl(void)
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
	m_pGridCtrl->SetColumnWidth(0, 200);
	for (int i=1;i<=2;i++)
	{
		m_pGridCtrl->SetColumnWidth(i, 155);
	}
	//m_pGridCtrl->ExpandToFit();
}

void CVehCountStatDlg::DetChargeStat(void)
{
	// ��ȡͳ����ֹʱ��
	COleDateTime odtBeginTime(COleDateTime::GetCurrentTime());
	COleDateTime odtEndTime(COleDateTime::GetCurrentTime());
	m_dtcBegTime.GetTime(odtBeginTime);
	m_dtcEndTime.GetTime(odtEndTime);

	CStringW strSQL;

	strSQL.AppendFormat(L" select * ");
	strSQL.AppendFormat(L" from Charge ");
	strSQL.AppendFormat(L" where ChargeingStatus <> '%s' ", DS_NoCharge);
	strSQL.AppendFormat(L" and (ChargingTime between '%s' and '%s') ", odtBeginTime.Format(L"%Y-%m-%d 00:00:00"), odtEndTime.Format(L"%Y-%m-%d 23:59:59"));

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

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSQL))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}
	else
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
	//Item.col=1;
	//Item.row=0;
	//Item.mask = GVIF_TEXT|GVIF_FORMAT;
	//Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	//Item.szText.Format(L"%s", L"��ѯͳ��");
	//m_pGridCtrl->SetItem(&Item);

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

CStringW CVehCountStatDlg::ToStatusName(const CStringW& strStatusCode)
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