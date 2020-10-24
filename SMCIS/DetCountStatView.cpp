// DetCountStatView.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "DetCountStatView.h"

#define DLG_CAPTION L"收费统计"
// CDetCountStatView

IMPLEMENT_DYNCREATE(CDetCountStatView, CFormView)

CDetCountStatView::CDetCountStatView()
	: CFormView(CDetCountStatView::IDD)
	, m_pGridCtrl(NULL)
{
	// 针对1280*1024分辨率进行开发
	int nSM_CYSCREEN = GetSystemMetrics(SM_CYSCREEN);
	// 根据分辨率Y方向进行调整
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
		L"宋体");
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


// CDetCountStatView 诊断

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


// CDetCountStatView 消息处理程序


void CDetCountStatView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	InitCtrls();
}


void CDetCountStatView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	//float fsp[2];
	//POINT Newp;//获取现在对话框的大小(VS2005中是CPOINT)
	//CRect recta;
	//GetClientRect(&recta); //取客户区大小
	//Newp.x=recta.right-recta.left;
	//Newp.y=recta.bottom-recta.top;
	//fsp[0]=(float)Newp.x/m_Old.x;
	//fsp[1]=(float)Newp.y/m_Old.y;

	//if (fsp[0] != 0 && fsp[1] != 0)
	//{
	//	CRect Rect;
	//	int woc;
	//	CPoint OldTLPoint,TLPoint; //左上角
	//	CPoint OldBRPoint,BRPoint; //右下角
	//	HWND hwndChild=::GetWindow(m_hWnd,GW_CHILD); //列出所有控件

	//	while(hwndChild)
	//	{
	//		woc=::GetDlgCtrlID(hwndChild);//取得ID
	//		GetDlgItem(woc)->GetWindowRect(Rect);
	//		ScreenToClient(Rect);
	//		OldTLPoint = Rect.TopLeft(); 
	//		TLPoint.x = long(OldTLPoint.x*fsp[0]); 
	//		TLPoint.y = long(OldTLPoint.y*fsp[1]);
	//		OldBRPoint = Rect.BottomRight();
	//		BRPoint.x = long(OldBRPoint.x *fsp[0]); 
	//		BRPoint.y = long(OldBRPoint.y *fsp[1]); //高度不可读的控件（如:combBox),不要改变此值.
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CFormView::OnTimer(nIDEvent);
}


BOOL CDetCountStatView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: 在此添加专用代码和/或调用基类
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
	m_cbStatType.AddString(L"收费类型统计");
	m_cbStatType.AddString(L"每台车统计");
	m_cbStatType.AddString(L"杂项统计");
	m_cbStatType.AddString(L"杂项/车辆统计");
	
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
		// 创建 GridCtrl 对象
		m_pGridCtrl = new CGridCtrl;
		if (!m_pGridCtrl) return;

		// 创建 Gridctrl 窗口
		CRect rect;
		GetDlgItem(IDC_LST_STAT)->GetClientRect(rect); // 得到显示区域
		m_pGridCtrl->Create(rect, &m_lstVehCount, IDC_LST_STAT);

		try 
		{
			m_pGridCtrl->SetRowCount(2); // 初始化行数
			m_pGridCtrl->SetColumnCount(3);	// 初始化列数
			m_pGridCtrl->SetFixedRowCount(2);	// 设置表头行数
			m_pGridCtrl->SetFixedColumnCount(1);// 设置表头列数
		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
			return;
		}

		// 填充每格数据
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
							Item.szText.Format(L"查询统计");
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
		// 合并单元格(行，列，行合并数，列合并数)
		m_pGridCtrl->SetFixedCellCombine(0,0,1,0);
		m_pGridCtrl->SetFixedCellCombine(0,1,0,1);
		//m_pGridCtrl->SetFixedCellCombine(1,1,0,2);

		//Item.col = 1;
		//Item.row = 1;
		//Item.szText.Format(L"总");
		//m_pGridCtrl->SetItem(&Item);
		//cellSize = pDC->GetTextExtent(L"总");
		//m_pGridCtrl->SetColumnWidth(Item.col, cellSize.cx+10);

		//m_pGridCtrl->SetFixedCellCombine(1,4,0,2);
		//Item.col=4;
		//Item.row=1;
		//Item.szText.Format(_T("初"));
		//m_pGridCtrl->SetItem(&Item);
		//cellSize=pDC->GetTextExtent(_T("初"));
		//m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);

		//m_pGridCtrl->SetFixedCellCombine(1,7,0,2);
		//Item.col=7;
		//Item.row=1;
		//Item.szText.Format(_T("复"));
		//m_pGridCtrl->SetItem(&Item);
		//cellSize=pDC->GetTextExtent(_T("复"));
		//m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);

		for (Item.col=1, Item.row=1; Item.col<=2; Item.col++)
		{
			switch(Item.col)
			{
			case 1:
				{
					Item.szText.Format(L"共收费金额");
				}
				break;
			case 2:
				{
					Item.szText.Format(L"共收费数量");
				}
				break;
			}
			m_pGridCtrl->SetItem(&Item);
			cellSize=pDC->GetTextExtent(Item.szText);
			m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
		}
	}

	// 设置行列高
	m_pGridCtrl->SetColumnWidth(0, 300);
	for (int i=1;i<=2;i++)
	{
		m_pGridCtrl->SetColumnWidth(i, 255);
	}
	//m_pGridCtrl->ExpandToFit();
}

void CDetCountStatView::OnBnClickedBtnStat()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_pGridCtrl->GetSafeHwnd())
	{
		return;
	}
	// 删除之前记录
	m_pGridCtrl->DeleteNonFixedRows();

	/// 获取统计时间
	COleDateTime odtBeginTime(COleDateTime::GetCurrentTime());
	COleDateTime odtEndTime(COleDateTime::GetCurrentTime());
	m_dtcBegTime.GetTime(odtBeginTime);
	m_dtcEndTime.GetTime(odtEndTime);

	if (odtEndTime < odtBeginTime)
	{
		MessageBox(L"结束日期不能早于开始日期,请重新输入统计日期区间!", L"收费统计", MB_OK|MB_ICONWARNING);
		return;
	}

	CString strStatType;
	m_cbStatType.GetWindowTextW(strStatType);

	if (strStatType.Find(L"收费类型统计") != std::string::npos)
	{
		DetChargeStat();
	}
	else if (strStatType.Find(L"每台车统计") != std::string::npos)
	{
		StatisticsOfEachVehicle();
	}
	else if (strStatType.Find(L"杂项统计") != std::string::npos)
	{
		MiscellaneousStatistics();
	}
	else if (strStatType.Find(L"杂项/车辆统计") != std::string::npos)
	{
		MiscellaneousVehicleStatistics();
	}
	else
	{
		MessageBox(L"请选择统计类型", L"收费统计", MB_OK|MB_ICONWARNING);
		m_pGridCtrl->Invalidate(); // 刷新控件
	}
	
}


void CDetCountStatView::OnBnClickedBtnPrint()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pGridCtrl->GetSafeHwnd())
	{
		m_pGridCtrl->AutoSize();
		m_pGridCtrl->Print();
	}
}


void CDetCountStatView::OnBnClickedBtnExport()
{
	// TODO: 在此添加控件通知处理程序代码
	// 导出
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

			// 将表格保存
			CString strSavePath;
			CString strFileName;
			strFileName.Format(L"查询统计结果%s.xls", CTime::GetCurrentTime().Format(L"%Y%m%d%H%M%S"));

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
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
		return false;
	}

	return true;
}

void CDetCountStatView::DetChargeStat(void)
{
	// 获取统计起止时间
	COleDateTime odtBeginTime(COleDateTime::GetCurrentTime());
	COleDateTime odtEndTime(COleDateTime::GetCurrentTime());
	m_dtcBegTime.GetTime(odtBeginTime);
	m_dtcEndTime.GetTime(odtEndTime);

	struct StatStru
	{
		// 总金额
		float fAmountOfCharges;
		// 台数
		int nTotNum;

		StatStru() {ZeroMemory(this, sizeof(StatStru));}
	};
	std::map<CStringW,StatStru> mapStaResult; // 统计结果

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
				// 没有关键字，先插空值
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
		mapStaResult[L"总金额"].nTotNum = nTotalAmount;
		mapStaResult[L"总金额"].fAmountOfCharges = fTotalQuantity;
	}

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}

	// 将统计结果显示到控件
	GV_ITEM Item;
	Item.col=1;
	Item.row=0;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.szText.Format(L"%s", L"收费类型统计");
	m_pGridCtrl->SetItem(&Item);

	// 设置m_pGridCtrl对象统计时间
	CString strTemp;
	strTemp.Format(L"%s～%s", odtBeginTime.Format(L"%Y-%m-%d"), odtEndTime.Format(L"%Y-%m-%d"));
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

	m_pGridCtrl->Invalidate(); // 刷新控件
}

CStringW CDetCountStatView::ToStatusName(const CStringW& strStatusCode)
{
	CString strTemp;
	strTemp.Format(L"%s", strStatusCode);
	if (strStatusCode.Find(DS_NoCharge) != -1)
	{
		return L"未收费";
	}
	else if (strStatusCode.Find(DS_Chargee) != -1)
	{
		return L"已收费";
	}
	else if (strStatusCode.Find(DS_Redo) != -1)
	{
		return L"重做";
	}
	else if (strStatusCode.Find(DS_CancelOfCharge) != -1)
	{
		return L"取消收费";
	}
	else if (strStatusCode.Find(DS_RevisionOfCharges) != -1)
	{
		return L"修改收费";
	}
	else
	{
		return strTemp;
	}
}

void CDetCountStatView::StatisticsOfEachVehicle(void)
{
	// 获取统计起止时间
	COleDateTime odtBeginTime(COleDateTime::GetCurrentTime());
	COleDateTime odtEndTime(COleDateTime::GetCurrentTime());
	m_dtcBegTime.GetTime(odtBeginTime);
	m_dtcEndTime.GetTime(odtEndTime);

	struct StatStru
	{
		// 总金额
		float fAmountOfCharges;
		// 台数
		int nTotNum;

		StatStru() {ZeroMemory(this, sizeof(StatStru));}
	};
	std::map<CStringW,StatStru> mapStaResult; // 统计结果

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

			if (Category.Find(L"杂项") != std::string::npos)
			{
				pRecordset->MoveNext();
				continue;
			}

			const int nCount = (int)mapStaResult.count(Category);
			if (0 == nCount)
			{
				// 没有关键字，先插空值
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
		mapStaResult[L"总金额"].nTotNum = nTotalAmount;
		mapStaResult[L"总金额"].fAmountOfCharges = fTotalQuantity;
	}

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}

	// 将统计结果显示到控件
	GV_ITEM Item;
	Item.col=1;
	Item.row=0;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.szText.Format(L"%s", L"每台车统计");
	m_pGridCtrl->SetItem(&Item);

	// 设置m_pGridCtrl对象统计时间
	CString strTemp;
	strTemp.Format(L"%s～%s", odtBeginTime.Format(L"%Y-%m-%d"), odtEndTime.Format(L"%Y-%m-%d"));
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

	m_pGridCtrl->Invalidate(); // 刷新控件

}

void CDetCountStatView::MiscellaneousStatistics(void)
{
	// 获取统计起止时间
	COleDateTime odtBeginTime(COleDateTime::GetCurrentTime());
	COleDateTime odtEndTime(COleDateTime::GetCurrentTime());
	m_dtcBegTime.GetTime(odtBeginTime);
	m_dtcEndTime.GetTime(odtEndTime);

	struct StatStru
	{
		// 总金额
		float fAmountOfCharges;
		// 台数
		int nTotNum;

		StatStru() {ZeroMemory(this, sizeof(StatStru));}
	};
	std::map<CStringW,StatStru> mapStaResult; // 统计结果

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

			if (strPlateNumber.Find(L"杂项") == std::string::npos)
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
				// 没有关键字，先插空值
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
		mapStaResult[L"总金额"].nTotNum = nTotalAmount;
		mapStaResult[L"总金额"].fAmountOfCharges = fTotalQuantity;
	}

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}

	// 将统计结果显示到控件
	GV_ITEM Item;
	Item.col=1;
	Item.row=0;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.szText.Format(L"%s", L"每台车统计");
	m_pGridCtrl->SetItem(&Item);

	// 设置m_pGridCtrl对象统计时间
	CString strTemp;
	strTemp.Format(L"%s～%s", odtBeginTime.Format(L"%Y-%m-%d"), odtEndTime.Format(L"%Y-%m-%d"));
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

	m_pGridCtrl->Invalidate(); // 刷新控件
}

void CDetCountStatView::MiscellaneousVehicleStatistics(void)
{
	// 获取统计起止时间
	COleDateTime odtBeginTime(COleDateTime::GetCurrentTime());
	COleDateTime odtEndTime(COleDateTime::GetCurrentTime());
	m_dtcBegTime.GetTime(odtBeginTime);
	m_dtcEndTime.GetTime(odtEndTime);

	struct StatStru
	{
		// 总金额
		float fAmountOfCharges;
		// 台数
		int nTotNum;

		StatStru() {ZeroMemory(this, sizeof(StatStru));}
	};
	std::map<CStringW,StatStru> mapStaResult; // 统计结果

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

			if (Category.Find(L"杂项") == std::string::npos)
			{
				Category = L"车辆";
			}
			else
			{
				Category = L"杂项";
			}

			const int nCount = (int)mapStaResult.count(Category);
			if (0 == nCount)
			{
				// 没有关键字，先插空值
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
		mapStaResult[L"总金额"].nTotNum = nTotalAmount;
		mapStaResult[L"总金额"].fAmountOfCharges = fTotalQuantity;
	}

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}

	// 将统计结果显示到控件
	GV_ITEM Item;
	Item.col=1;
	Item.row=0;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.szText.Format(L"%s", L"每台车统计");
	m_pGridCtrl->SetItem(&Item);

	// 设置m_pGridCtrl对象统计时间
	CString strTemp;
	strTemp.Format(L"%s～%s", odtBeginTime.Format(L"%Y-%m-%d"), odtEndTime.Format(L"%Y-%m-%d"));
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

	m_pGridCtrl->Invalidate(); // 刷新控件
}