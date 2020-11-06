// DetCountStatView2.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "DetCountStatView2.h"

#define DLG_CAPTION L"收费统计2.0"
// CDetCountStatView2

IMPLEMENT_DYNCREATE(CDetCountStatView2, CFormView)

	CDetCountStatView2::CDetCountStatView2()
	: CFormView(CDetCountStatView2::IDD)
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

CDetCountStatView2::~CDetCountStatView2()
{
	m_fontDlgFont.DeleteObject();

	if (m_pGridCtrl != NULL)
	{
		delete m_pGridCtrl;
		m_pGridCtrl = NULL;
	}
}

void CDetCountStatView2::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_STAT, m_lstVehCount);
	DDX_Control(pDX, IDC_DTP_COND_BEGIN_TIME, m_dtcBegTime);
	DDX_Control(pDX, IDC_DTP_COND_END_TIME, m_dtcEndTime);
	DDX_Control(pDX, IDC_BTN_STAT, m_btnStat);
	DDX_Control(pDX, IDC_BTN_PRINT, m_btnPrint);
	DDX_Control(pDX, IDC_BTN_EXPORT, m_btnExport);
}

BEGIN_MESSAGE_MAP(CDetCountStatView2, CFormView)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_STAT, &CDetCountStatView2::OnBnClickedBtnStat)
	ON_BN_CLICKED(IDC_BTN_PRINT, &CDetCountStatView2::OnBnClickedBtnPrint)
	ON_BN_CLICKED(IDC_BTN_EXPORT, &CDetCountStatView2::OnBnClickedBtnExport)
END_MESSAGE_MAP()


// CDetCountStatView2 诊断

#ifdef _DEBUG
void CDetCountStatView2::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDetCountStatView2::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDetCountStatView2 消息处理程序




void CDetCountStatView2::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	InitCtrls();
}

void CDetCountStatView2::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_pGridCtrl->GetSafeHwnd())
	{
		CRect rect;
		GetDlgItem(IDC_LST_STAT)->GetClientRect(rect);
		m_pGridCtrl->MoveWindow(rect);
	}
}


void CDetCountStatView2::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CFormView::OnTimer(nIDEvent);
}


BOOL CDetCountStatView2::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (m_pGridCtrl && IsWindow(m_pGridCtrl->m_hWnd))
		if (m_pGridCtrl->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
			return TRUE;

	return CFormView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CDetCountStatView2::InitCtrls(void)
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

}

void CDetCountStatView2::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);
		pWnd = pWnd->GetNextWindow();
	}
}

void CDetCountStatView2::InitGirdCtrl(void)
{
	// 合并单元格(行，列，行合并数，列合并数)
	//m_pGridCtrl->SetFixedCellCombine(21,0,0,3);// 合并固定项
	//m_pGridCtrl->SetCellCombine(21,4,0,1);	// 合并空白项

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
			m_pGridCtrl->SetRowCount(3); // 初始化行数
			m_pGridCtrl->SetColumnCount(6);	// 初始化列数
			m_pGridCtrl->SetFixedRowCount(3);	// 设置表头行数
			m_pGridCtrl->SetFixedColumnCount(2);// 设置表头列数
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

				if (nCol == 0)
				{
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					switch(nRow)
					{
					case 0:
						{
							Item.szText.Format(L"营业表格");
						}
						break;
					case 1:
						{
							Item.szText.Format(COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d"));
						}
						break;
					case 2:
						{
							Item.szText.Format(L"检验类别");
						}
						break;
					}
				}
				if (nRow == 2)
				{
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					switch(nCol)
					{
					case 0:
						{
							Item.szText.Format(L"检验类别");
						}
						break;
					case 1:
						{
							Item.szText.Format(L"检验类别代码");
						}
						break;
					case 2:
						{
							Item.szText.Format(L"收费项目名称");
						}
						break;
					case 3:
						{
							Item.szText.Format(L"收费金额");
						}
						break;
					case 4:
						{
							Item.szText.Format(L"数量");
						}
						break;
					case 5:
						{
							Item.szText.Format(L"金额");
						}
						break;
					}
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
		m_pGridCtrl->SetFixedCellCombine(0,0,0,5);
		m_pGridCtrl->SetFixedCellCombine(1,0,0,5);

		//for (Item.col=1, Item.row=1; Item.col<=2; Item.col++)
		//{
		//	switch(Item.col)
		//	{
		//	case 1:
		//		{
		//			Item.szText.Format(L"共收费金额");
		//		}
		//		break;
		//	case 2:
		//		{
		//			Item.szText.Format(L"共收费数量");
		//		}
		//		break;
		//	}
		//	m_pGridCtrl->SetItem(&Item);
		//	cellSize=pDC->GetTextExtent(Item.szText);
		//	m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
		//}
	}

	// 设置行列高
	//m_pGridCtrl->SetColumnWidth(0, 300);
	for (int i=0;i<=5;i++)
	{
		if (i <= 2)
		{
			m_pGridCtrl->SetColumnWidth(i, 250);
		}
		else
		{
			m_pGridCtrl->SetColumnWidth(i, 100);
		}
	}
	//m_pGridCtrl->ExpandToFit();
}

void CDetCountStatView2::OnBnClickedBtnStat()
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

	// 获取检测类别
	std::list<SCharge_DetType> lsDetType;
	if (!GetDetType(lsDetType))
	{
		MessageBox(L"获取检测类别（数据库操作）", L"收费统计", MB_OK|MB_ICONWARNING);
		return;
	}

	int nRow(2);
	std::map<int,int> mapRow;

	std::list<SCharge_DetType>::const_iterator iter = lsDetType.begin();

	for ( ; iter != lsDetType.end(); iter++)
	{
		GetDetChargeStatToDetType(iter->strName.c_str(), iter->strCode.c_str(), nRow);

		mapRow[nRow] = nRow;

	}
	// 杂项
	GetChargeStatToZX(nRow);
	mapRow[nRow] = nRow;

	// 记账收费
	Bookkeeping(nRow);
	mapRow[nRow] = nRow;
	// 记录最后一行；
	int nlast(0);
	// 记录总金额；
	float fZJE(0.0f);
	std::map<int,int>::const_iterator iter_int = mapRow.begin();
	for ( ; iter_int != mapRow.end(); iter_int++)
	{
		nlast = iter_int->first;
		if (nlast != 2)
		{
			CString str;
			str = m_pGridCtrl->GetItemText(nlast, 4);
			fZJE += _wtof(str);
		}
	}

	if (fZJE >= 1.0f)
	{
		CString strTemp;
		nRow = nlast;
		nRow++;
		strTemp.Format(L"%s", L"总金额");
		m_pGridCtrl->InsertRow(strTemp);
		m_pGridCtrl->SetFixedCellCombine(nRow,0,0,1);
		m_pGridCtrl->SetCellCombine(nRow,2,0,1);
		m_pGridCtrl->SetCellCombine(nRow,4,0,1);
		strTemp.Format(L"%.2f", fZJE);
		m_pGridCtrl->SetItemText(nRow, 4, strTemp);
		m_pGridCtrl->SetItemState(nRow, 2, GVIS_READONLY);
		m_pGridCtrl->SetItemState(nRow, 4, GVIS_READONLY);
	}


	m_pGridCtrl->Invalidate(); // 刷新控件
}


void CDetCountStatView2::OnBnClickedBtnPrint()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pGridCtrl->GetSafeHwnd())
	{
		m_pGridCtrl->AutoSize();
		m_pGridCtrl->Print();
	}
}


void CDetCountStatView2::OnBnClickedBtnExport()
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

bool CDetCountStatView2::GetDetType(std::list<SCharge_DetType>& lsDetType)
{
	CString strSQL;
	strSQL.Format(L"select * from Charge_DetType order by AutoID");

	if (0xFFFFFFFF != CCharge_DetTypeService::GetCharge_DetType(theApp.m_pConnection, strSQL, lsDetType))
	{
		return true;
	}
	else
	{
		return false;
	}
}

CString CDetCountStatView2::GetUnitValue(const CString& strDetType, const CString& strDetTypeCode, const CString& strChargeItem)
{
	CString strRet(L"-");

	CString strSql;
	strSql.Format(L"select * from Fee_Items where TypeOfCharge = '%s' and DetType = '%s'", strChargeItem, strDetType);

	SFee_Item sFee_Item;

	if (0x01 == CFee_ItemService::GetFee_Item(theApp.m_pConnection, strSql.GetString(), sFee_Item))
	{
		strRet.Format(L"%.2f", _wtof(sFee_Item.strAmountOfCharges.c_str()));
	}
	else if (strChargeItem == L"9座以下小型客车")
	{
		strRet.Format(L"%.2f", 300.00f);
	}
	else if (strChargeItem == L"总质量4.5t以下、专业作业车")
	{
		strRet.Format(L"%.2f", 340.00f);
	}
	else if (strChargeItem == L"两检合一12t-30t重型货车")
	{
		strRet.Format(L"%.2f", 680.00f);
	}

	return strRet;
}

CString CDetCountStatView2::GetZXUnitValue(const CString& strDetType, const CString& strDetTypeCode, const CString& strChargeItem)
{
	CString strRet(L"-");

	CString strSql;
	strSql.Format(L"select * from Miscellaneous_Charges where TypeOfCharge = '%s'", strChargeItem);

	SMiscellaneous_Charges sMiscellaneous_Charges;

	if (0x01 == CMiscellaneous_ChargesService::GetMiscellaneous_Charges(theApp.m_pConnection, strSql.GetString(), sMiscellaneous_Charges))
	{


		strRet.Format(L"%.2f", _wtof(sMiscellaneous_Charges.strAmountOfCharges.c_str()));
	}


	return strRet;
}

void CDetCountStatView2::GetDetChargeStatToDetType(const CString& strDetType, const CString& strDetTypeCode, int& nRow)
{
	// 获取统计起止时间
	COleDateTime odtBeginTime(COleDateTime::GetCurrentTime());
	COleDateTime odtEndTime(COleDateTime::GetCurrentTime());
	m_dtcBegTime.GetTime(odtBeginTime);
	m_dtcEndTime.GetTime(odtEndTime);

	CString strSql;

	strSql.AppendFormat(L" select * ");
	strSql.AppendFormat(L" from Charge ");
	strSql.AppendFormat(L" where ChargeingStatus <> '%s' ", DS_NoCharge); // 不能是未收费
	strSql.AppendFormat(L" and PlateNumber <> '%s' ", L"杂项");// 不能是杂项
	strSql.AppendFormat(L" and (ChargingTime between '%s' and '%s') ", odtBeginTime.Format(L"%Y-%m-%d 00:00:00"), odtEndTime.Format(L"%Y-%m-%d 23:59:59"));
	strSql.AppendFormat(L" and DetType = '%s' ", strDetType);

	strSql.AppendFormat(L" order by AutoID");

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
		return ;
	}

	struct StatStru
	{
		// 总金额
		float fAmountOfCharges;
		// 台数
		int nTotNum;

		StatStru() {ZeroMemory(this, sizeof(StatStru));}
	};
	std::map<CStringW,StatStru> mapStaResult; // 统计结果

	CString str(L"");
	_variant_t v;

	while (!pRecordset->adoEOF)
	{
		//
		CStringW Category;
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

		// 总数量
		mapStaResult[Category].nTotNum++;
		// 总金额
		float fAmountOfCharges(0.0f);
		v.ChangeType(VT_NULL);
		CNHSQLServerDBO::GetFieldValue(pRecordset, v, _T("AmountOfCharges"));
		if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
		{
			fAmountOfCharges = static_cast<float>(v);
		}
		mapStaResult[Category].fAmountOfCharges = fAmountOfCharges + mapStaResult[Category].fAmountOfCharges;

		pRecordset->MoveNext();
	}

	float fAOC(0.0f);
	std::map<CStringW,StatStru>::iterator iter;
	for (iter=mapStaResult.begin(); iter!=mapStaResult.end(); ++iter)
	{
		CString strTemp;
		nRow++;
		m_pGridCtrl->InsertRow(strDetType);
		m_pGridCtrl->SetItemText(nRow, 1, strDetTypeCode);
		if (iter->first.IsEmpty())
		{
			m_pGridCtrl->SetItemText(nRow, 2, L"退费/退办");
		}
		else
		{
			m_pGridCtrl->SetItemText(nRow, 2, iter->first);
		}
		m_pGridCtrl->SetItemState(nRow, 2, GVIS_READONLY);
		m_pGridCtrl->SetItemText(nRow, 3, GetUnitValue(strDetType, strDetTypeCode, iter->first));
		m_pGridCtrl->SetItemState(nRow, 3, GVIS_READONLY);
		strTemp.Format(L"%d", iter->second.nTotNum);
		m_pGridCtrl->SetItemText(nRow, 4, strTemp);
		m_pGridCtrl->SetItemState(nRow, 4, GVIS_READONLY);
		strTemp.Format(L"%.2f", iter->second.fAmountOfCharges);
		m_pGridCtrl->SetItemText(nRow, 5, strTemp);
		m_pGridCtrl->SetItemState(nRow, 5, GVIS_READONLY);
		fAOC += iter->second.fAmountOfCharges;
	}

	if (mapStaResult.size() > 0)
	{
		CString strTemp;
		nRow++;
		strTemp.Format(L"%s统计", strDetType);
		m_pGridCtrl->InsertRow(strTemp);
		m_pGridCtrl->SetFixedCellCombine(nRow,0,0,1);
		m_pGridCtrl->SetCellCombine(nRow,2,0,1);
		m_pGridCtrl->SetCellCombine(nRow,4,0,1);
		strTemp.Format(L"%.2f", fAOC);
		m_pGridCtrl->SetItemText(nRow, 4, strTemp);
		m_pGridCtrl->SetItemState(nRow, 2, GVIS_READONLY);
		m_pGridCtrl->SetItemState(nRow, 4, GVIS_READONLY);
		strTemp.Format(L"%s至%s", odtBeginTime.Format(L"%Y-%m-%d"), odtEndTime.Format(L"%Y-%m-%d"));
		m_pGridCtrl->SetItemText(1, 0, strTemp);

	}
}

void CDetCountStatView2::GetChargeStatToZX(int& nRow)
{
	// 获取统计起止时间
	COleDateTime odtBeginTime(COleDateTime::GetCurrentTime());
	COleDateTime odtEndTime(COleDateTime::GetCurrentTime());
	m_dtcBegTime.GetTime(odtBeginTime);
	m_dtcEndTime.GetTime(odtEndTime);

	CString strSql;

	strSql.AppendFormat(L" select * ");
	strSql.AppendFormat(L" from Charge ");
	strSql.AppendFormat(L" where ChargeingStatus <> '%s' ", DS_NoCharge); // 不能是未收费
	strSql.AppendFormat(L" and PlateNumber = '%s' ", L"杂项");// 杂项
	strSql.AppendFormat(L" and (ChargingTime between '%s' and '%s') ", odtBeginTime.Format(L"%Y-%m-%d 00:00:00"), odtEndTime.Format(L"%Y-%m-%d 23:59:59"));

	strSql.AppendFormat(L" order by AutoID");

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
		return ;
	}
	
	struct StatStru
	{
		// 总金额
		float fAmountOfCharges;
		// 台数
		int nTotNum;

		StatStru() {ZeroMemory(this, sizeof(StatStru));}
	};
	std::map<CStringW,StatStru> mapStaResult; // 统计结果

	CString str(L"");
	_variant_t v;

	while (!pRecordset->adoEOF)
	{
		//
		CStringW Category;
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

		// 总数量
		mapStaResult[Category].nTotNum++;
		// 总金额
		float fAmountOfCharges(0.0f);
		v.ChangeType(VT_NULL);
		CNHSQLServerDBO::GetFieldValue(pRecordset, v, _T("AmountOfCharges"));
		if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
		{
			fAmountOfCharges = static_cast<float>(v);
		}
		mapStaResult[Category].fAmountOfCharges = fAmountOfCharges + mapStaResult[Category].fAmountOfCharges;

		// 杂项数量
		CString strZXNumber;
		v.ChangeType(VT_NULL);
		CNHSQLServerDBO::GetFieldValue(pRecordset, v, _T("Reserved1"));
		if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
		{
			strZXNumber.Format(L"%s", (wchar_t*)(_bstr_t)v);
		}
		int nZXNumber = _wtoi(strZXNumber);

		if (nZXNumber > 1)
		{
			for (int i=0; i < nZXNumber-1; i++)
			{
				mapStaResult[Category].nTotNum++;
			}
		}

		pRecordset->MoveNext();
	}

	float fAOC(0.0f);
	std::map<CStringW,StatStru>::iterator iter;
	for (iter=mapStaResult.begin(); iter!=mapStaResult.end(); ++iter)
	{
		CString strTemp;
		nRow++;
		m_pGridCtrl->InsertRow(L"杂项");
		m_pGridCtrl->SetItemText(nRow, 1, L"杂项");
		if (iter->first.IsEmpty())
		{
			m_pGridCtrl->SetItemText(nRow, 2, L"退费/退办");
		}
		else
		{
			m_pGridCtrl->SetItemText(nRow, 2, iter->first);
		}
		m_pGridCtrl->SetItemState(nRow, 2, GVIS_READONLY);
		m_pGridCtrl->SetItemText(nRow, 3, GetZXUnitValue(L"杂项", L"杂项", iter->first));
		m_pGridCtrl->SetItemState(nRow, 3, GVIS_READONLY);
		strTemp.Format(L"%d", iter->second.nTotNum);
		m_pGridCtrl->SetItemText(nRow, 4, strTemp);
		m_pGridCtrl->SetItemState(nRow, 4, GVIS_READONLY);
		strTemp.Format(L"%.2f", iter->second.fAmountOfCharges);
		m_pGridCtrl->SetItemText(nRow, 5, strTemp);
		m_pGridCtrl->SetItemState(nRow, 5, GVIS_READONLY);
		fAOC += iter->second.fAmountOfCharges;
	}

	if (mapStaResult.size() > 0)
	{
		CString strTemp;
		nRow++;
		strTemp.Format(L"%s统计", L"杂项");
		m_pGridCtrl->InsertRow(strTemp);
		m_pGridCtrl->SetFixedCellCombine(nRow,0,0,1);
		m_pGridCtrl->SetCellCombine(nRow,2,0,1);
		m_pGridCtrl->SetCellCombine(nRow,4,0,1);
		strTemp.Format(L"%.2f", fAOC);
		m_pGridCtrl->SetItemText(nRow, 4, strTemp);
		m_pGridCtrl->SetItemState(nRow, 2, GVIS_READONLY);
		m_pGridCtrl->SetItemState(nRow, 4, GVIS_READONLY);
		strTemp.Format(L"%s至%s", odtBeginTime.Format(L"%Y-%m-%d"), odtEndTime.Format(L"%Y-%m-%d"));
		m_pGridCtrl->SetItemText(1, 0, strTemp);

	}

}

CString CDetCountStatView2::GetUnit_Outstanding_Amount(const CString& strUnitName)
{
	CString strRet(L"-");

	CString strSql;
	strSql.Format(L"SELECT * FROM Bill_Of_Arrears WHERE Unit_Name = '%s'", strUnitName);

	SBillOfArrears sBillOfArrears;
	if (0x01 == CBillOfArrearsService::GetBillOfArrears(theApp.m_pConnection, strSql.GetString(), sBillOfArrears))
	{
		strRet.Format(L"%.2f", _wtof(sBillOfArrears.strOutstanding_Amount.c_str()));
	}

	return strRet;
}

void CDetCountStatView2::Bookkeeping(int& nRow)
{
	// 获取统计起止时间
	COleDateTime odtBeginTime(COleDateTime::GetCurrentTime());
	COleDateTime odtEndTime(COleDateTime::GetCurrentTime());
	m_dtcBegTime.GetTime(odtBeginTime);
	m_dtcEndTime.GetTime(odtEndTime);

	CString strSql;

	strSql.AppendFormat(L" select * ");
	strSql.AppendFormat(L" from Charge ");
	strSql.AppendFormat(L" where ChargeingStatus <> '%s' ", DS_NoCharge); // 不能是未收费
	strSql.AppendFormat(L" and PlateNumber = '%s' ", L"记账收费");// 记账收费
	strSql.AppendFormat(L" and (ChargingTime between '%s' and '%s') ", odtBeginTime.Format(L"%Y-%m-%d 00:00:00"), odtEndTime.Format(L"%Y-%m-%d 23:59:59"));

	strSql.AppendFormat(L" order by AutoID");

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
		return ;
	}

	struct StatStru
	{
		// 该单位收款总金额
		float fAmountOfCharges;
		// 该单位收款次数
		int nTotNum;
		// 该单位未收取金额
		float fOutstanding_Amount;

		StatStru() {ZeroMemory(this, sizeof(StatStru));}
	};
	std::map<CStringW,StatStru> mapStaResult; // 统计结果

	CString str(L"");
	_variant_t v;

	while (!pRecordset->adoEOF)
	{
		//
		CStringW Category;
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

		// 该单位收款次数
		mapStaResult[Category].nTotNum++;
		// 该单位收款总金额
		float fAmountOfCharges(0.0f);
		v.ChangeType(VT_NULL);
		CNHSQLServerDBO::GetFieldValue(pRecordset, v, _T("AmountOfCharges"));
		if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
		{
			fAmountOfCharges = static_cast<float>(v);
		}
		mapStaResult[Category].fAmountOfCharges = fAmountOfCharges + mapStaResult[Category].fAmountOfCharges;

		pRecordset->MoveNext();
	}

	// 获取实收到账金额
	//float fAmountReceived(0.0f);
	//std::map<CStringW,StatStru>::iterator iter;
	//for (iter=mapStaResult.begin(); iter!=mapStaResult.end(); ++iter)
	//{
	//	// 获取该单位欠款金额
	//	iter->second.fOutstanding_Amount = GetUnit_Outstanding_Amount(iter->first);
	//}

	float fAOC(0.0f);
	std::map<CStringW,StatStru>::iterator iter;
	for (iter=mapStaResult.begin(); iter!=mapStaResult.end(); ++iter)
	{
		CString strTemp;
		nRow++;
		m_pGridCtrl->InsertRow(L"记账收费");
		m_pGridCtrl->SetItemText(nRow, 1, L"记账收费");
		m_pGridCtrl->SetItemText(nRow, 2, iter->first);
		m_pGridCtrl->SetItemState(nRow, 2, GVIS_READONLY);
		m_pGridCtrl->SetItemText(nRow, 3, L"-");
		m_pGridCtrl->SetItemState(nRow, 3, GVIS_READONLY);
		strTemp.Format(L"%d", iter->second.nTotNum);
		m_pGridCtrl->SetItemText(nRow, 4, L"-");
		m_pGridCtrl->SetItemState(nRow, 4, GVIS_READONLY);
		strTemp.Format(L"%.2f", iter->second.fAmountOfCharges);
		m_pGridCtrl->SetItemText(nRow, 5, strTemp);
		m_pGridCtrl->SetItemState(nRow, 5, GVIS_READONLY);
		fAOC += iter->second.fAmountOfCharges;
	}

	if (mapStaResult.size() > 0)
	{
		CString strTemp;
		nRow++;
		strTemp.Format(L"%s统计", L"记账收费");
		m_pGridCtrl->InsertRow(strTemp);
		m_pGridCtrl->SetFixedCellCombine(nRow,0,0,1);
		m_pGridCtrl->SetCellCombine(nRow,2,0,1);
		m_pGridCtrl->SetCellCombine(nRow,4,0,1);
		strTemp.Format(L"%.2f", fAOC);
		m_pGridCtrl->SetItemText(nRow, 4, strTemp);
		m_pGridCtrl->SetItemState(nRow, 2, GVIS_READONLY);
		m_pGridCtrl->SetItemState(nRow, 4, GVIS_READONLY);
		strTemp.Format(L"%s至%s", odtBeginTime.Format(L"%Y-%m-%d"), odtEndTime.Format(L"%Y-%m-%d"));
		m_pGridCtrl->SetItemText(1, 0, strTemp);

	}
}