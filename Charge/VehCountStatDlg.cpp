// VehCountStatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Charge.h"
#include "VehCountStatDlg.h"
#include "afxdialogex.h"


// CVehCountStatDlg 对话框

IMPLEMENT_DYNAMIC(CVehCountStatDlg, CDialogEx)

CVehCountStatDlg::CVehCountStatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVehCountStatDlg::IDD, pParent)
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


// CVehCountStatDlg 消息处理程序


BOOL CVehCountStatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowTextW(L"查询统计");
	// 初始化控件
	InitCtrls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CVehCountStatDlg::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (m_pGridCtrl && IsWindow(m_pGridCtrl->m_hWnd))
		if (m_pGridCtrl->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
			return TRUE;

	return CDialogEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CVehCountStatDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_pGridCtrl->GetSafeHwnd())
	{
		CRect rect;
		GetDlgItem(IDC_LST_STAT)->GetClientRect(rect);
		m_pGridCtrl->MoveWindow(rect);
	}
}


void CVehCountStatDlg::OnClickedBtnStat()
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
		MessageBox(L"结束日期不能早于开始日期,请重新输入统计日期区间!", L"查询统计", MB_OK|MB_ICONWARNING);
		return;
	}

	DetChargeStat();
}


void CVehCountStatDlg::OnClickedBtnPrint()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pGridCtrl->GetSafeHwnd())
	{
		m_pGridCtrl->AutoSize();
		m_pGridCtrl->Print();
	}
}


void CVehCountStatDlg::OnClickedBtnExport()
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
	m_pGridCtrl->SetColumnWidth(0, 200);
	for (int i=1;i<=2;i++)
	{
		m_pGridCtrl->SetColumnWidth(i, 155);
	}
	//m_pGridCtrl->ExpandToFit();
}

void CVehCountStatDlg::DetChargeStat(void)
{
	// 获取统计起止时间
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
		// 总金额
		float fAmountOfCharges;
		// 台数
		int nTotNum;

		StatStru() {ZeroMemory(this, sizeof(StatStru));}
	};
	std::map<CStringW,StatStru> mapStaResult; // 统计结果

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSQL))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
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
	//Item.col=1;
	//Item.row=0;
	//Item.mask = GVIF_TEXT|GVIF_FORMAT;
	//Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	//Item.szText.Format(L"%s", L"查询统计");
	//m_pGridCtrl->SetItem(&Item);

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

CStringW CVehCountStatDlg::ToStatusName(const CStringW& strStatusCode)
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