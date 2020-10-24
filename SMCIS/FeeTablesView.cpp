// FeeTablesView.cpp : 实现文件
//

#include "stdafx.h"
#include "SMCIS.h"
#include "FeeTablesView.h"

#define DLG_CAPTION L"收费统计表格"
// CFeeTablesView

IMPLEMENT_DYNCREATE(CFeeTablesView, CFormView)

	CFeeTablesView::CFeeTablesView()
	: CFormView(CFeeTablesView::IDD)
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

CFeeTablesView::~CFeeTablesView()
{
	m_fontDlgFont.DeleteObject();

	if (m_pGridCtrl != NULL)
	{
		delete m_pGridCtrl;
		m_pGridCtrl = NULL;
	}
}

void CFeeTablesView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_STAT, m_lstVehCount);
	DDX_Control(pDX, IDC_DTP_COND_BEGIN_TIME, m_dtcBegTime);
	DDX_Control(pDX, IDC_DTP_COND_END_TIME, m_dtcEndTime);
	DDX_Control(pDX, IDC_BTN_STAT, m_btnStat);
	DDX_Control(pDX, IDC_BTN_PRINT, m_btnPrint);
	DDX_Control(pDX, IDC_BTN_EXPORT, m_btnExport);
}

BEGIN_MESSAGE_MAP(CFeeTablesView, CFormView)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_STAT, &CFeeTablesView::OnBnClickedBtnStat)
	ON_BN_CLICKED(IDC_BTN_PRINT, &CFeeTablesView::OnBnClickedBtnPrint)
	ON_BN_CLICKED(IDC_BTN_EXPORT, &CFeeTablesView::OnBnClickedBtnExport)
END_MESSAGE_MAP()


// CFeeTablesView 诊断

#ifdef _DEBUG
void CFeeTablesView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFeeTablesView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFeeTablesView 消息处理程序


void CFeeTablesView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	InitCtrls();
}

void CFeeTablesView::OnSize(UINT nType, int cx, int cy)
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


void CFeeTablesView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CFormView::OnTimer(nIDEvent);
}


BOOL CFeeTablesView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (m_pGridCtrl && IsWindow(m_pGridCtrl->m_hWnd))
		if (m_pGridCtrl->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
			return TRUE;

	return CFormView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CFeeTablesView::InitCtrls(void)
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

void CFeeTablesView::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);
		pWnd = pWnd->GetNextWindow();
	}
}

//void CFeeTablesView::InitGirdCtrl(void)
//{
//	CDC *pDC;
//	if (m_pGridCtrl == NULL)
//	{
//		// 创建 GridCtrl 对象
//		m_pGridCtrl = new CGridCtrl;
//		if (!m_pGridCtrl) return;
//
//		// 创建 Gridctrl 窗口
//		CRect rect;
//		GetDlgItem(IDC_LST_STAT)->GetClientRect(rect); // 得到显示区域
//		m_pGridCtrl->Create(rect, &m_lstVehCount, IDC_LST_STAT);
//
//		try 
//		{
//			m_pGridCtrl->SetRowCount(43); // 初始化行数
//			m_pGridCtrl->SetColumnCount(5);	// 初始化列数
//			m_pGridCtrl->SetFixedRowCount(3);	// //固定行
//			m_pGridCtrl->SetFixedColumnCount(2);// 固定列
//		}
//		catch (CMemoryException* e)
//		{
//			e->ReportError();
//			e->Delete();
//			return;
//		}
//
//		// 填充每格数据
//		for (int nRow = 0; nRow < m_pGridCtrl->GetRowCount(); nRow++)
//		{
//			for (int nCol = 0; nCol < m_pGridCtrl->GetColumnCount(); nCol++)
//			{
//				GV_ITEM Item;
//				Item.mask = GVIF_TEXT|GVIF_FORMAT;
//				Item.row = nRow;
//				Item.col = nCol;
//
//				// 设定固定参数(列设定行)
//				if (nCol < 1)
//				{
//					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
//					switch(nRow)
//					{
//					case 0:
//						{
//							Item.szText.Format(L"营业日表格");
//						}
//						break;
//					case 1:
//						{
//							Item.szText.Format(COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d"));
//						}
//						break;
//					case 2:
//						{
//							Item.szText.Format(L"项目");
//						}
//						break;
//					case 3:
//						{
//							Item.szText.Format(L"农用(电动)运输车");
//						}
//						break;
//					case 4:
//						{
//							Item.szText.Format(L"小车");
//						}
//						break;
//					case 5:
//						{
//							Item.szText.Format(L"校车");
//						}
//						break;
//					case 6:
//						{
//							Item.szText.Format(L"客车（20人）");
//						}
//						break;
//					case 7:
//						{
//							Item.szText.Format(L"货车4.5吨以下");
//						}
//						break;
//					case 8:
//						{
//							Item.szText.Format(L"货车(4.5-12吨)");
//						}
//						break;
//					case 9:
//						{
//							Item.szText.Format(L"货车(12-30吨)");
//						}
//						break;
//					case 10:
//						{
//							Item.szText.Format(L"货车(30-45吨)");
//						}
//						break;
//					case 11:
//						{
//							Item.szText.Format(L"挂车");
//						}
//						break;
//					case 12:
//						{
//							Item.szText.Format(L"挂车(危货)");
//						}
//						break;
//					case 13:
//						{
//							Item.szText.Format(L"特种车辆");
//						}
//						break;
//					case 14:
//						{
//							Item.szText.Format(L"两检合一");
//						}
//						break;
//					case 21:
//						{
//							Item.szText.Format(L"安检合计");
//						}
//						break;
//					case 22:
//					case 23:
//					case 24:
//					case 25:
//						{
//							Item.szText.Format(L"等级评定");
//						}
//						break;
//					case 26:
//						{
//							Item.szText.Format(L"综检合计");
//						}
//						break;
//					case 27:
//					case 28:
//					case 29:
//					case 30:
//					case 31:
//						{
//							Item.szText.Format(L"新车检测");
//						}
//						break;
//					case 32:
//						{
//							Item.szText.Format(L"新车合计");
//						}
//						break;
//					case 33:
//						{
//							Item.szText.Format(L"过磅");
//						}
//						break;
//					case 34:
//						{
//							Item.szText.Format(L"外廓");
//						}
//						break;
//					case 35:
//						{
//							Item.szText.Format(L"A");
//						}
//						break;
//					case 36:
//						{
//							Item.szText.Format(L"B");
//						}
//						break;
//					case 37:
//						{
//							Item.szText.Format(L"车管货车业务合计");
//						}
//						break;
//					case 38:
//						{
//							Item.szText.Format(L"摩托车");
//						}
//						break;
//					case 39:
//						{
//							Item.szText.Format(L"外检");
//						}
//						break;
//					case 40:
//						{
//							Item.szText.Format(L"照相");
//						}
//						break;
//					case 41:
//						{
//							Item.szText.Format(L"其他合计");
//						}
//						break;
//					case 42:
//						{
//							Item.szText.Format(L"累计");
//						}
//						break;
//					}
//				}
//				else if (nCol == 1)
//				{
//					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
//					switch(nRow)
//					{
//					case 14:
//						{
//							Item.szText.Format(L"教练、4.5t");
//						}
//						break;
//					case 15:
//						{
//							Item.szText.Format(L"客车(10-19)");
//						}
//						break;
//					case 16:
//						{
//							Item.szText.Format(L"客车20人");
//						}
//						break;
//					case 17:
//						{
//							Item.szText.Format(L"货车4.5-12吨");
//						}
//						break;
//					case 18:
//						{
//							Item.szText.Format(L"危货4.5-12吨");
//						}
//						break;
//					case 19:
//						{
//							Item.szText.Format(L"货车12吨以上");
//						}
//						break;
//					case 20:
//						{
//							Item.szText.Format(L"危货12吨以上");
//						}
//						break;
//					}
//				}
//				else
//				{
//					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
//					Item.szText.Format(_T(" "));
//				}
//
//				// 设定固定参数(行设定列)
//				if (nRow == 2)
//				{
//					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
//					switch(nCol)
//					{
//					case 2:
//						{
//							Item.szText.Format(L"数量");
//						}
//						break;
//					case 3:
//						{
//							Item.szText.Format(L"单价");
//						}
//						break;
//					case 4:
//						{
//							Item.szText.Format(L"金额");
//						}
//						break;
//					}
//				}
//
//				m_pGridCtrl->SetItem(&Item);
//			}
//		}
//		m_pGridCtrl->AutoSize();
//		m_pGridCtrl->SetRowHeight(0, 2*m_pGridCtrl->GetRowHeight(0));
//	}
//
//	pDC = m_pGridCtrl->GetDC();
//	CSize cellSize;
//	GV_ITEM Item;
//	Item.mask = GVIF_TEXT|GVIF_FORMAT;
//	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
//	CRect tempRect;
//
//	if (m_pGridCtrl->GetSafeHwnd())
//	{
//		// 合并单元格(行，列，行合并数，列合并数)
//		m_pGridCtrl->SetFixedCellCombine(0,0,0,4);
//		m_pGridCtrl->SetFixedCellCombine(1,0,0,4);
//		for (int i=2;i<14;i++)
//		{
//			m_pGridCtrl->SetFixedCellCombine(i,0,0,1);
//		}
//		for (int i=21;i<45;i++)
//		{
//			m_pGridCtrl->SetFixedCellCombine(i,0,0,1);
//		}
//		m_pGridCtrl->SetFixedCellCombine(14,0,6,0);
//		//m_pGridCtrl->SetFixedCellCombine(1,1,0,2);
//
//		for(int i=3;i<43;i++)
//		{
//			switch(i)
//			{
//			case 3:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"200");
//				}
//				break;
//			case 4:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"300");
//				}
//				break;
//			case 5:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"440");
//				}
//				break;
//			case 6:
//			case 8:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"400");
//				}
//				break;
//			case 7:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"340");
//				}
//				break;
//			case 9:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"500");
//				}
//				break;
//			case 10:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"680");
//				}
//				break;
//			case 11:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"540");
//				}
//				break;
//			case 12:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"640");
//				}
//				break;
//			case 13:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"1000");
//				}
//				break;
//			case 14:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"460");
//				}
//				break;
//			case 15:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"540");
//				}
//				break;
//			case 16:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"660");
//				}
//				break;
//			case 17:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"520");
//				}
//				break;
//			case 18:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"620");
//				}
//				break;
//			case 19:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"680");
//				}
//				break;
//			case 20:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"780");
//				}
//				break;
//			case 22:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"200");
//				}
//				break;
//			case 23:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"260");
//				}
//				break;
//			case 24:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"360");
//				}
//				break;
//			case 25:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"540");
//				}
//				break;
//			case 27:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"300");
//				}
//				break;
//			case 28:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"380");
//				}
//				break;
//			case 29:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"680");
//				}
//				break;
//			case 30:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"500");
//				}
//				break;
//			case 31:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"1000");
//				}
//				break;
//			case 33:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"100");
//				}
//				break;
//			case 34:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"100");
//				}
//				break;
//			case 35:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"300");
//				}
//				break;
//			case 36:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"500");
//				}
//				break;
//			case 38:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"100");
//				}
//				break;
//			case 39:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"0");
//				}
//				break;
//			case 40:
//				{
//					m_pGridCtrl->SetItemText(i, 3, L"25");
//				}
//				break;
//			}
//		}
//
//	}
//
//	// 设置行列高
//	m_pGridCtrl->SetColumnWidth(0, 60);
//	for (int i=1;i<=4;i++)
//	{
//		m_pGridCtrl->SetColumnWidth(i, 155);
//	}
//	//m_pGridCtrl->ExpandToFit();
//}

void CFeeTablesView::InitGirdCtrl(void)
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
			m_pGridCtrl->SetRowCount(68); // 初始化行数
			m_pGridCtrl->SetColumnCount(6);	// 初始化列数
			m_pGridCtrl->SetFixedRowCount(3);	// //固定行
			m_pGridCtrl->SetFixedColumnCount(4);// 固定列
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

				// 设定固定参数(列设定行)
				if (nCol < 1)
				{
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					switch(nRow)
					{
					case 0:
						{
							Item.szText.Format(L"营业日表格");
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
					case 3:
						{
							Item.szText.Format(L"在用车检验（定检）");
						}
						break;
					case 21:
						{
							Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
							Item.szText.Format(L"在用车安检（定检）合计：");
						}
						break;
					case 22:
						{
							Item.szText.Format(L"技术等级评定");
						}
						break;
					case 31:
						{
							Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
							Item.szText.Format(L"在技术等级评定统计：");
						}
						break;
					case 32:
						{
							Item.szText.Format(L"在用车检验（定检）//技术等级评定");
						}
						break;
					case 41:
						{
							Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
							Item.szText.Format(L"在用车三检合一统计：");
						}
						break;
					case 42:
						{
							Item.szText.Format(L"注册登记检验");
						}
						break;
					case 48:
						{
							Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
							Item.szText.Format(L"注册登记检验统计：");
						}
						break;
					case 49:
						{
							Item.szText.Format(L"注册登记检验//技术等级评定");
						}
						break;
					case 51:
						{
							Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
							Item.szText.Format(L"注册登记三检合一统计：");
						}
						break;
					case 52:
						{
							Item.szText.Format(L"在用车检验（非定检）");
						}
						break;
					case 53:
						{
							Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
							Item.szText.Format(L"在用车检验（非定检）统计：");
						}
						break;
					case 54:
						{
							Item.szText.Format(L"临时检验");
						}
						break;
					case 57:
						{
							Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
							Item.szText.Format(L"临时检验统计：");
						}
						break;
					case 58:
						{
							Item.szText.Format(L"杂项");
						}
						break;
					case 66:
						{
							Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
							Item.szText.Format(L"杂项统计：");
						}
						break;
					case 67:
						{
							Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
							Item.szText.Format(L"累计：");
						}
						break;
					}
				}
				else if (nCol == 1)
				{
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					switch(nRow)
					{
					case 3:
						{
							Item.szText.Format(L"01");
						}
						break;
					case 22:
						{
							Item.szText.Format(L"技术等级评定");
						}
						break;
					case 32:
						{
							Item.szText.Format(L"在用车检验（定检）//技术等级评定");
						}
						break;
					case 42:
						{
							Item.szText.Format(L"00");
						}
						break;
					case 49:
						{
							Item.szText.Format(L"注册登记检验//技术等级评定");
						}
						break;
					case 52:
						{
							Item.szText.Format(L"04");
						}
						break;
					case 54:
						{
							Item.szText.Format(L"02");
						}
						break;
					case 58:
						{
							Item.szText.Format(L"杂项");
						}
						break;
					}
				}
				else if (nCol == 2)
				{
					Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					switch(nRow)
					{
					case 3:
						{
							Item.szText.Format(L"农用(电动）运输车");
						}
						break;
					case 4:
						{
							Item.szText.Format(L"非营运客车：9人以下");
						}
						break;
					case 5:
						{
							Item.szText.Format(L"中型客车：10-19人");
						}
						break;
					case 6:
						{
							Item.szText.Format(L"大型客车：20人及以上");
						}
						break;
					case 7:
						{
							Item.szText.Format(L"校车：10-19人");
						}
						break;
					case 8:
						{
							Item.szText.Format(L"校车：20人及以上");
						}
						break;
					case 9:
						{
							Item.szText.Format(L"货车：总质量4.5t以下");
						}
						break;
					case 10:
						{
							Item.szText.Format(L"货车：总质量4.5-12t");
						}
						break;
					case 11:
						{
							Item.szText.Format(L"货车：总质量12-30t");
						}
						break;
					case 12:
						{
							Item.szText.Format(L"货车：总质量30t以上");
						}
						break;
					case 13:
						{
							Item.szText.Format(L"货车（危货）：总质量4.5t以下");
						}
						break;
					case 14:
						{
							Item.szText.Format(L"货车（危货）：总质量4.5-12t");
						}
						break;
					case 15:
						{
							Item.szText.Format(L"货车（危货）：总质量12-30t");
						}
						break;
					case 16:
						{
							Item.szText.Format(L"货车（危货）：总质量30t以上");
						}
						break;
					case 17:
						{
							Item.szText.Format(L"挂车：30t以上");
						}
						break;
					case 18:
						{
							Item.szText.Format(L"挂车(危货）：30t以上");
						}
						break;
					case 19:
						{
							Item.szText.Format(L"专项作业车：整备质量30t以上");
						}
						break;
					case 20:
						{
							Item.szText.Format(L"预留项");
						}
						break;
					case 22:
						{
							Item.szText.Format(L"教练、租赁小型车辆");
						}
						break;
					case 23:
						{
							Item.szText.Format(L"中型客车：10-19人");
						}
						break;
					case 24:
						{
							Item.szText.Format(L"大型客车：20人及以上");
						}
						break;
					case 25:
						{
							Item.szText.Format(L"货车：总质量4.5-12t");
						}
						break;
					case 26:
						{
							Item.szText.Format(L"货车：总质量12t以上");
						}
						break;
					case 27:
						{
							Item.szText.Format(L"危货：总质量4.5t以下");
						}
						break;
					case 28:
						{
							Item.szText.Format(L"危货：总质量4.5-12t");
						}
						break;
					case 29:
						{
							Item.szText.Format(L"危货：总质量12t以上");
						}
						break;
					case 30:
						{
							Item.szText.Format(L"预留项");
						}
						break;
					case 32:
						{
							Item.szText.Format(L"教练、租赁小型车辆");
						}
						break;
					case 33:
						{
							Item.szText.Format(L"中型客车：10-19人");
						}
						break;
					case 34:
						{
							Item.szText.Format(L"大型客车：20人及以上");
						}
						break;
					case 35:
						{
							Item.szText.Format(L"货车：总质量4.5-12t");
						}
						break;
					case 36:
						{
							Item.szText.Format(L"货车：总质量12t以上");
						}
						break;
					case 37:
						{
							Item.szText.Format(L"危货：总质量4.5t以下");
						}
						break;
					case 38:
						{
							Item.szText.Format(L"危货：总质量4.5-12t");
						}
						break;
					case 39:
						{
							Item.szText.Format(L"危货：总质量12t以上");
						}
						break;
					case 40:
						{
							Item.szText.Format(L"预留项");
						}
						break;
					case 42:
						{
							Item.szText.Format(L"非免检小型客车");
						}
						break;
					case 43:
						{
							Item.szText.Format(L"货车：总质量3.5t以下");
						}
						break;
					case 44:
						{
							Item.szText.Format(L"货车：总质量3.5-4.5t");
						}
						break;
					case 45:
						{
							Item.szText.Format(L"货车：总质量4.5-31t");
						}
						break;
					case 46:
						{
							Item.szText.Format(L"专项作业车：整备质量30t以上");
						}
						break;
					case 47:
						{
							Item.szText.Format(L"预留项");
						}
						break;
					case 49:
						{
							Item.szText.Format(L"货车：总质量4.5-31t");
						}
						break;
					case 50:
						{
							Item.szText.Format(L"预留项");
						}
						break;
					case 52:
						{
							Item.szText.Format(L"根据实际情况填写费用");
						}
						break;
					case 54:
						{
							Item.szText.Format(L"过户");
						}
						break;
					case 55:
						{
							Item.szText.Format(L"转出");
						}
						break;
					case 56:
						{
							Item.szText.Format(L"转入");
						}
						break;
					case 58:
						{
							Item.szText.Format(L"A");
						}
						break;
					case 59:
						{
							Item.szText.Format(L"B");
						}
						break;
					case 60:
						{
							Item.szText.Format(L"摩托车");
						}
						break;
					case 61:
						{
							Item.szText.Format(L"反光膜");
						}
						break;
					case 62:
						{
							Item.szText.Format(L"三角警告牌");
						}
						break;
					case 63:
						{
							Item.szText.Format(L"灭火器");
						}
						break;
					case 64:
						{
							Item.szText.Format(L"照相");
						}
						break;
					case 65:
						{
							Item.szText.Format(L"预留项");
						}
						break;
					}
				}
				else if (nCol == 3)
				{
					Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					switch(nRow)
					{
					case 3:
						{
							Item.szText.Format(L"200");
						}
						break;
					case 4:
						{
							Item.szText.Format(L"300");
						}
						break;
					case 5:
						{
							Item.szText.Format(L"340");
						}
						break;
					case 6:
						{
							Item.szText.Format(L"400");
						}
						break;
					case 7:
						{
							Item.szText.Format(L"440");
						}
						break;
					case 8:
						{
							Item.szText.Format(L"500");
						}
						break;
					case 9:
						{
							Item.szText.Format(L"340");
						}
						break;
					case 10:
						{
							Item.szText.Format(L"400");
						}
						break;
					case 11:
						{
							Item.szText.Format(L"500");
						}
						break;
					case 12:
						{
							Item.szText.Format(L"680");
						}
						break;
					case 13:
						{
							Item.szText.Format(L"440");
						}
						break;
					case 14:
						{
							Item.szText.Format(L"500");
						}
						break;
					case 15:
						{
							Item.szText.Format(L"600");
						}
						break;
					case 16:
						{
							Item.szText.Format(L"780");
						}
						break;
					case 17:
						{
							Item.szText.Format(L"540");
						}
						break;
					case 18:
						{
							Item.szText.Format(L"640");
						}
						break;
					case 19:
						{
							Item.szText.Format(L"1000");
						}
						break;
					case 20:
						{
							Item.szText.Format(L"0");
						}
						break;
					case 22:
						{
							Item.szText.Format(L"160");
						}
						break;
					case 23:
						{
							Item.szText.Format(L"200");
						}
						break;
					case 24:
						{
							Item.szText.Format(L"260");
						}
						break;
					case 25:
						{
							Item.szText.Format(L"360");
						}
						break;
					case 26:
						{
							Item.szText.Format(L"540");
						}
						break;
					case 27:
						{
							Item.szText.Format(L"360");
						}
						break;
					case 28:
						{
							Item.szText.Format(L"460");
						}
						break;
					case 29:
						{
							Item.szText.Format(L"640");
						}
						break;
					case 30:
						{
							Item.szText.Format(L"0");
						}
						break;
					case 32:
						{
							Item.szText.Format(L"460");
						}
						break;
					case 33:
						{
							Item.szText.Format(L"540");
						}
						break;
					case 34:
						{
							Item.szText.Format(L"660");
						}
						break;
					case 35:
						{
							Item.szText.Format(L"520");
						}
						break;
					case 36:
						{
							Item.szText.Format(L"680");
						}
						break;
					case 37:
						{
							Item.szText.Format(L"560");
						}
						break;
					case 38:
						{
							Item.szText.Format(L"620");
						}
						break;
					case 39:
						{
							Item.szText.Format(L"780");
						}
						break;
					case 40:
						{
							Item.szText.Format(L"0");
						}
						break;
					case 42:
						{
							Item.szText.Format(L"300");
						}
						break;
					case 43:
						{
							Item.szText.Format(L"300");
						}
						break;
					case 44:
						{
							Item.szText.Format(L"380");
						}
						break;
					case 45:
						{
							Item.szText.Format(L"500");
						}
						break;
					case 46:
						{
							Item.szText.Format(L"1000");
						}
						break;
					case 47:
						{
							Item.szText.Format(L"0");
						}
						break;
					case 49:
						{
							Item.szText.Format(L"680");
						}
						break;
					case 50:
						{
							Item.szText.Format(L"0");
						}
						break;
					case 52:
						{
							Item.szText.Format(L"300");
						}
						break;
					case 54:
						{
							Item.szText.Format(L"100");
						}
						break;
					case 55:
						{
							Item.szText.Format(L"100");
						}
						break;
					case 56:
						{
							Item.szText.Format(L"200");
						}
						break;
					case 58:
						{
							Item.szText.Format(L"300");
						}
						break;
					case 59:
						{
							Item.szText.Format(L"500");
						}
						break;
					case 60:
						{
							Item.szText.Format(L"100");
						}
						break;
					case 61:
						{
							Item.szText.Format(L"4");
						}
						break;
					case 62:
						{
							Item.szText.Format(L"20");
						}
						break;
					case 63:
						{
							Item.szText.Format(L"40");
						}
						break;
					case 64:
						{
							Item.szText.Format(L"25");
						}
						break;
					case 65:
						{
							Item.szText.Format(L"0");
						}
						break;
					}
				}
				else
				{
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					Item.szText.Format(_T(" "));
				}

				// 设定固定参数(行设定列)
				if (nRow == 2)
				{
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					switch(nCol)
					{
					case 1:
						{
							Item.szText.Format(L"检验类别代码");
						}
						break;
					case 2:
						{
							Item.szText.Format(L"项目");
						}
						break;
					case 3:
						{
							Item.szText.Format(L"单价");
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
		m_pGridCtrl->SetFixedCellCombine(3,0,17,0);
		m_pGridCtrl->SetFixedCellCombine(3,1,17,0);
		m_pGridCtrl->SetFixedCellCombine(21,0,0,3);
		m_pGridCtrl->SetCellCombine(21,4,0,1);
		m_pGridCtrl->SetFixedCellCombine(22,0,8,0);
		m_pGridCtrl->SetFixedCellCombine(22,1,8,0);
		m_pGridCtrl->SetFixedCellCombine(31,0,0,3);
		m_pGridCtrl->SetCellCombine(31,4,0,1);
		m_pGridCtrl->SetFixedCellCombine(32,0,8,0);
		m_pGridCtrl->SetFixedCellCombine(32,1,8,0);
		m_pGridCtrl->SetFixedCellCombine(41,0,0,3);
		m_pGridCtrl->SetCellCombine(41,4,0,1);
		m_pGridCtrl->SetFixedCellCombine(42,0,5,0);
		m_pGridCtrl->SetFixedCellCombine(42,1,5,0);
		m_pGridCtrl->SetFixedCellCombine(48,0,0,3);
		m_pGridCtrl->SetCellCombine(48,4,0,1);
		m_pGridCtrl->SetFixedCellCombine(49,0,1,0);
		m_pGridCtrl->SetFixedCellCombine(49,1,1,0);
		m_pGridCtrl->SetFixedCellCombine(51,0,0,3);
		m_pGridCtrl->SetCellCombine(51,4,0,1);
		m_pGridCtrl->SetFixedCellCombine(53,0,0,3);
		m_pGridCtrl->SetCellCombine(53,4,0,1);
		m_pGridCtrl->SetFixedCellCombine(54,0,2,0);
		m_pGridCtrl->SetFixedCellCombine(54,1,2,0);
		m_pGridCtrl->SetFixedCellCombine(57,0,0,3);
		m_pGridCtrl->SetCellCombine(57,4,0,1);
		m_pGridCtrl->SetFixedCellCombine(58,0,7,0);
		m_pGridCtrl->SetFixedCellCombine(58,1,7,0);
		m_pGridCtrl->SetFixedCellCombine(66,0,0,3);
		m_pGridCtrl->SetCellCombine(66,4,0,1);
		m_pGridCtrl->SetFixedCellCombine(67,0,0,3);
		m_pGridCtrl->SetCellCombine(67,4,0,1);
	}

	// 设置行列高
	m_pGridCtrl->SetColumnWidth(0, 300);
	m_pGridCtrl->SetColumnWidth(1, 300);
	m_pGridCtrl->SetColumnWidth(2, 200);
	for (int i=3;i<=5;i++)
	{
		m_pGridCtrl->SetColumnWidth(i, 75);
	}
	//m_pGridCtrl->ExpandToFit();
}

void CFeeTablesView::OnBnClickedBtnStat()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_pGridCtrl->GetSafeHwnd())
	{
		return;
	}
	// 删除之前记录
	//m_pGridCtrl->DeleteAllItems();

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
	m_nTotNum = 0;
	m_fAmountOfCharges = 0.0f;

	CString strSql;
	strSql = GetSQL();
	// 先确定检测类型是综检，安检，两检合一在分检测类型
	m_fTotalAmount = 0.0f;
	// 农用(电动）运输车
	DetTypeRIVehATVeh(strSql);
	// 客车：9人以下
	DetTypeRIVehPCar(strSql, 1);
	DetTypeRIVehPCar(strSql, 2);
	DetTypeRIVehPCar(strSql, 3);
	// 校车
	DetTypeRIVehSchbus(strSql, 1);
	DetTypeRIVehSchbus(strSql, 2);
	// 货车
	for (int i=1; i<5;i++)
	{
		DetTypeRIVehTruck(strSql, i, false);
		DetTypeRIVehTruck(strSql, i, true);
	}
	// 挂车
	DetTypeRIVehTrailer(strSql, false);
	DetTypeRIVehTrailer(strSql, true);
	// 专项作业车
	DetTypeRIVehSOVeh(strSql);
	// 在用车总金额
	TotalAmountOfTestCategory(1, m_fTotalAmount);

	// 技术等级评定
	m_fTotalAmount = 0.0f;
	// 小型汽车
	TGECoachLeaseSmallVeh(strSql);
	TGERIVehPCar(strSql, 1);
	TGERIVehPCar(strSql, 2);
	TGERIVehTruck(strSql, 1, true);
	TGERIVehTruck(strSql, 2, true);
	TGERIVehTruck(strSql, 2, false);
	TGERIVehTruck(strSql, 3, true);
	TGERIVehTruck(strSql, 3, false);
	TotalAmountOfTestCategory(2, m_fTotalAmount);

	// 三检合一
	m_fTotalAmount = 0.0f;
	// 小型汽车
	TheToOneCoachLeaseSmallVeh(strSql);
	TheToOneRIVehPCar(strSql, 1);
	TheToOneRIVehPCar(strSql, 2);
	TheToOneRIVehTruck(strSql, 1, true);
	TheToOneRIVehTruck(strSql, 2, true);
	TheToOneRIVehTruck(strSql, 2, false);
	TheToOneRIVehTruck(strSql, 3, true);
	TheToOneRIVehTruck(strSql, 3, false);
	TotalAmountOfTestCategory(3, m_fTotalAmount);

	// 注册登记
	m_fTotalAmount = 0.0f;
	RegistrationRIVehPCar(strSql);
	RegistrationRIVehTruck(strSql, 1);
	RegistrationRIVehTruck(strSql, 2);
	RegistrationRIVehTruck(strSql, 3);
	RegistrationRIVehSOVeh(strSql);
	TotalAmountOfTestCategory(4, m_fTotalAmount);

	// 三检合一 (新车)
	m_fTotalAmount = 0.0f;
	NewTheToOneRIVehTruck(strSql);
	TotalAmountOfTestCategory(5, m_fTotalAmount);

	// 非定检
	m_fTotalAmount = 0.0f;
	NoFixedCheck(strSql);
	TotalAmountOfTestCategory(6, m_fTotalAmount);

	// 临时检测
	m_fTotalAmount = 0.0f;
	TemIns(strSql, 1);
	TemIns(strSql, 2);
	TemIns(strSql, 3);
	TotalAmountOfTestCategory(7, m_fTotalAmount);
	
	// 杂项
	m_fTotalAmount = 0.0f;
	for (int i =0;i<8; i++)
	{
		Mis(i+1);
	}
	TotalAmountOfTestCategory(8, m_fTotalAmount);

	// 累加

	TotalAmountOfTestCategory(9, 0.0f);

	//// 安检
	//strSql.AppendFormat(L"and (DetLog.DetType_M is NULL and DetLog.DetType is not NULL) ");
	//// 综检
	//strSql.AppendFormat(L"and (DetLog.DetType_M is not NULL and DetLog.DetType is NULL) ");
	//// 两检合一
	//strSql.AppendFormat(L"and (DetLog.DetType_M is not NULL and DetLog.DetType is not NULL) ");

	m_pGridCtrl->Invalidate(); // 刷新控件
}


void CFeeTablesView::OnBnClickedBtnPrint()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pGridCtrl->GetSafeHwnd())
	{
		m_pGridCtrl->AutoSize();
		m_pGridCtrl->Print();
	}
}


void CFeeTablesView::OnBnClickedBtnExport()
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

CString CFeeTablesView::GetSQL(void)
{
	/*
	共同的语句踩统一写，其他的分开
	*/
	COleDateTime odtBeginTime(COleDateTime::GetCurrentTime());
	COleDateTime odtEndTime(COleDateTime::GetCurrentTime());
	m_dtcBegTime.GetTime(odtBeginTime);
	m_dtcEndTime.GetTime(odtEndTime);

	CString strSql;
	strSql.AppendFormat(L"select * ");
	// 多重关联 DetLog和Charge、DetPeriod、HisVehInfo关联
	strSql.AppendFormat(L"from DetLog ");
	strSql.AppendFormat(L"INNER Join Charge ON Charge.RunningNumber = DetLog.RunningNumber ");
	strSql.AppendFormat(L"INNER Join DetPeriod ON  DetPeriod.DetPeriodID = DetLog.DetPeriodID ");
	strSql.AppendFormat(L"INNER Join HisVehInfo ON HisVehInfo.RunningNumber = DetLog.RunningNumber ");
	strSql.AppendFormat(L"where ");
	// 不能是取消检测
	strSql.AppendFormat(L"(DetLog.DetStatus != 'CANDET') ");
	// 是否要完成检测 暂时不要
	//strSql.AppendFormat(L"and (DetLog.DetStatus = 'FINDET') ");
	// 登陆时间
	strSql.AppendFormat(L"and (DetLog.EntryTime between '%s 00:00:00' and '%s 23:59:59') ", odtBeginTime.Format(L"%Y-%m-%d"),  odtEndTime.Format(L"%Y-%m-%d"));


	return strSql;
}

void CFeeTablesView::TotalAmountOfTestCategory(const int& nDetType, const float& fTotalAmount)
{
	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	switch (nDetType)
	{
	case 1:{Item.col = 4;Item.row = 21;Item.szText.Format(L"%.1f", fTotalAmount);m_pGridCtrl->SetItem(&Item);}break;
	case 2:{Item.col = 4;Item.row = 31;Item.szText.Format(L"%.1f", fTotalAmount);m_pGridCtrl->SetItem(&Item);}break;
	case 3:{Item.col = 4;Item.row = 41;Item.szText.Format(L"%.1f", fTotalAmount);m_pGridCtrl->SetItem(&Item);}break;
	case 4:{Item.col = 4;Item.row = 48;Item.szText.Format(L"%.1f", fTotalAmount);m_pGridCtrl->SetItem(&Item);}break;
	case 5:{Item.col = 4;Item.row = 51;Item.szText.Format(L"%.1f", fTotalAmount);m_pGridCtrl->SetItem(&Item);}break;
	case 6:{Item.col = 4;Item.row = 53;Item.szText.Format(L"%.1f", fTotalAmount);m_pGridCtrl->SetItem(&Item);}break;
	case 7:{Item.col = 4;Item.row = 57;Item.szText.Format(L"%.1f", fTotalAmount);m_pGridCtrl->SetItem(&Item);}break;
	case 8:{Item.col = 4;Item.row = 66;Item.szText.Format(L"%.1f", fTotalAmount);m_pGridCtrl->SetItem(&Item);}break;
	case 9:
		{
			float fLJ(0.0f);
			for (int i=1; i<9; i++)
			{
				CString str;
				float fCharge(0.0f);
				switch(i)
				{
				case 1:{str = m_pGridCtrl->GetItemText(21,4);fCharge = _wtof(str);fLJ += fCharge;}break;
				case 2:{str = m_pGridCtrl->GetItemText(31,4);fCharge = _wtof(str);fLJ += fCharge;}break;
				case 3:{str = m_pGridCtrl->GetItemText(41,4);fCharge = _wtof(str);fLJ += fCharge;}break;
				case 4:{str = m_pGridCtrl->GetItemText(48,4);fCharge = _wtof(str);fLJ += fCharge;}break;
				case 5:{str = m_pGridCtrl->GetItemText(51,4);fCharge = _wtof(str);fLJ += fCharge;}break;
				case 6:{str = m_pGridCtrl->GetItemText(53,4);fCharge = _wtof(str);fLJ += fCharge;}break;
				case 7:{str = m_pGridCtrl->GetItemText(57,4);fCharge = _wtof(str);fLJ += fCharge;}break;
				case 8:{str = m_pGridCtrl->GetItemText(66,4);fCharge = _wtof(str);fLJ += fCharge;}break;
				}
			}
			Item.col = 4;Item.row = 67;Item.szText.Format(L"%.1f", fLJ);m_pGridCtrl->SetItem(&Item);
		}
		break;
	}
}

void CFeeTablesView::DetTypeRIVehATVeh(const CString& strSQL)
{
	CString strSql(strSQL);
	strSql.AppendFormat(L"and (DetLog.DetType_M is NULL and DetLog.DetType is not NULL) ");
	// 定义检测类型
	strSql.AppendFormat(L"and DetLog.DetType  = '在用车检验（定检）' ");
	// 农用(电动）运输车
	strSql.AppendFormat(L"and (HisVehInfo.FuelType like '%%电%%'  or DetLog.PlateType like '%%农用%%' or DetLog.PlateType like '%%拖拉%%') ");

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}


	CString str;
	str = m_pGridCtrl->GetItemText(3,3);
	float fCharge;
	fCharge = _wtof(str);


	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}
	GV_ITEM Item;
	//Item.col = 0;
	//Item.row = 0;
	//Item.mask = GVIF_TEXT|GVIF_FORMAT;
	//Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	//Item.szText.Format(L"营业日表格");
	//m_pGridCtrl->SetItem(&Item);

	str.Format(L"%d", nTotalAmount);
	m_pGridCtrl->SetItemText(3, 4, str);
	str.Format(L"%.1f", fCharge);
	m_pGridCtrl->SetItemText(3, 5, str);
	m_fTotalAmount += fCharge;
}

void CFeeTablesView::DetTypeRIVehPCar(const CString& strSQL, const int& nNumber)
{
	CString strSql(strSQL);
	strSql.AppendFormat(L"and (DetLog.DetType_M is NULL and DetLog.DetType is not NULL) ");
	// 定义检测类型
	strSql.AppendFormat(L"and DetLog.DetType  = '在用车检验（定检）' ");
	// 不能农用(电动）运输车
	strSql.AppendFormat(L"and (HisVehInfo.FuelType not like '%%电%%'  or DetLog.PlateType not like '%%农用%%' or DetLog.PlateType not like '%%拖拉%%') ");
	// 客车 校车分开算
	strSql.AppendFormat(L"and HisVehInfo.VehType not like ('%%货车%%') and HisVehInfo.VehType not like ('%%挂车%%') \
						 and HisVehInfo.VehType not like ('%%作业车%%') and HisVehInfo.VehType not like ('%%牵引车%%') \
						 and HisVehInfo.VehType not like ('%%校车%%') ");
	if (nNumber == 1)
	{
		// 小于等于9座
		strSql.AppendFormat(L"and HisVehInfo.RatedPassengerCapacity <= 9 ");
	}
	else if (nNumber == 2)
	{
		// 10-19人
		strSql.AppendFormat(L"and (HisVehInfo.RatedPassengerCapacity >= 10 and  HisVehInfo.RatedPassengerCapacity <= 19) ");
	}
	else
	{
		// 20人及以上
		strSql.AppendFormat(L"and HisVehInfo.RatedPassengerCapacity >= 20 ");
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}


	CString str;
	if (nNumber == 1)
	{
		str = m_pGridCtrl->GetItemText(4,3);
	}
	else if (nNumber == 2)
	{
		str = m_pGridCtrl->GetItemText(5,3);
	}
	else
	{
		str = m_pGridCtrl->GetItemText(6,3);
	}
	float fCharge;
	fCharge = _wtof(str);


	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}
	GV_ITEM Item;
	//Item.col = 0;
	//Item.row = 0;
	//Item.mask = GVIF_TEXT|GVIF_FORMAT;
	//Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	//Item.szText.Format(L"营业日表格");
	//m_pGridCtrl->SetItem(&Item);
	if (nNumber == 1)
	{
		str.Format(L"%d", nTotalAmount);
		m_pGridCtrl->SetItemText(4, 4, str);
		str.Format(L"%.1f", fCharge);
		m_pGridCtrl->SetItemText(4, 5, str);
	}
	else if (nNumber == 2)
	{
		str.Format(L"%d", nTotalAmount);
		m_pGridCtrl->SetItemText(5, 4, str);
		str.Format(L"%.1f", fCharge);
		m_pGridCtrl->SetItemText(5, 5, str);
	}
	else
	{
		str.Format(L"%d", nTotalAmount);
		m_pGridCtrl->SetItemText(6, 4, str);
		str.Format(L"%.1f", fCharge);
		m_pGridCtrl->SetItemText(6, 5, str);
	}
	m_fTotalAmount += fCharge;
}

void CFeeTablesView::DetTypeRIVehSchbus(const CString& strSQL, const int& nNumber)
{
	CString strSql(strSQL);
	strSql.AppendFormat(L"and (DetLog.DetType_M is NULL and DetLog.DetType is not NULL) ");
	// 定义检测类型
	strSql.AppendFormat(L"and DetLog.DetType  = '在用车检验（定检）' ");
	// 不能农用(电动）运输车
	strSql.AppendFormat(L"and (HisVehInfo.FuelType not like ('%%电%%')  or DetLog.PlateType not like ('%%农用%%') or DetLog.PlateType not like ('%%拖拉%%')) ");
	// 校车
	strSql.AppendFormat(L"and HisVehInfo.VehType like ('%%校车%%') ");
	if (nNumber == 1)
	{
		// 10-19人
		strSql.AppendFormat(L"and (HisVehInfo.RatedPassengerCapacity >= 10 and  HisVehInfo.RatedPassengerCapacity <= 19) ");
	}
	else
	{
		// 20人及以上
		strSql.AppendFormat(L"and HisVehInfo.RatedPassengerCapacity >= 20 ");
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}


	CString str;
	if (nNumber == 1)
	{
		str = m_pGridCtrl->GetItemText(7,3);
	}
	else
	{
		str = m_pGridCtrl->GetItemText(8,3);
	}
	float fCharge;
	fCharge = _wtof(str);


	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}

	if (nNumber == 1)
	{
		str.Format(L"%d", nTotalAmount);
		m_pGridCtrl->SetItemText(7, 4, str);
		str.Format(L"%.1f", fCharge);
		m_pGridCtrl->SetItemText(7, 5, str);
	}
	else
	{
		str.Format(L"%d", nTotalAmount);
		m_pGridCtrl->SetItemText(8, 4, str);
		str.Format(L"%.1f", fCharge);
		m_pGridCtrl->SetItemText(8, 5, str);
	}
	m_fTotalAmount += fCharge;
}

void CFeeTablesView::DetTypeRIVehTruck(const CString& strSQL, const int& nTonnage, const bool& bDANGER/*=false*/)
{
	CString strSql(strSQL);
	strSql.AppendFormat(L"and (DetLog.DetType_M is NULL and DetLog.DetType is not NULL) ");
	// 定义检测类型
	strSql.AppendFormat(L"and DetLog.DetType  = '在用车检验（定检）' ");
	// 不能农用(电动）运输车
	strSql.AppendFormat(L"and (HisVehInfo.FuelType not like ('%%电%%')  or DetLog.PlateType not like ('%%农用%%') or DetLog.PlateType not like ('%%拖拉%%')) ");
	// 货车或牵引车
	strSql.AppendFormat(L"and (HisVehInfo.VehType like ('%%货车%%') or HisVehInfo.VehType like ('%%牵引车%%')) ");
	// 是否危险运输车
	strSql.AppendFormat(L"and HisVehInfo.UseCharacter ");
	if (!bDANGER)
	{
		strSql.AppendFormat(L"not ");
	}
	strSql.AppendFormat(L"like ('%%危%%') ");
	// 吨位 //牵引车按总质量30t以上收费
	// 1.总质量4.5t以下
	// 2.总质量4.5-12t
	// 3.总质量12-30t
	// 4.总质量30t以上
	if (nTonnage == 1)
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass < 4500 and HisVehInfo.VehType not like ('%%牵引车%%') ");
	}
	else if (nTonnage == 2)
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass > 4500 and HisVehInfo.MaximumTotalMass < 12000 and HisVehInfo.VehType not like ('%%牵引车%%') ");
	}
	else if (nTonnage == 3)
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass > 12000 and HisVehInfo.MaximumTotalMass < 30000 and HisVehInfo.VehType not like ('%%牵引车%%') ");
	}
	else 
	{
		strSql.AppendFormat(L"and (HisVehInfo.MaximumTotalMass > 30000 or HisVehInfo.VehType like ('%%牵引车%%')) ");
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}

	CString str;
	if (bDANGER)
	{
		switch(nTonnage)
		{
		case 1:{str = m_pGridCtrl->GetItemText(13,3);}break;
		case 2:{str = m_pGridCtrl->GetItemText(14,3);}break;
		case 3:{str = m_pGridCtrl->GetItemText(15,3);}break;
		case 4:{str = m_pGridCtrl->GetItemText(16,3);}break;
		}
	}
	else
	{
		switch(nTonnage)
		{
		case 1:{str = m_pGridCtrl->GetItemText(9,3);}break;
		case 2:{str = m_pGridCtrl->GetItemText(10,3);}break;
		case 3:{str = m_pGridCtrl->GetItemText(11,3);}break;
		case 4:{str = m_pGridCtrl->GetItemText(12,3);}break;
		}
	}
	float fCharge;
	fCharge = _wtof(str);

	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}

	if (bDANGER)
	{
		switch(nTonnage)
		{
		case 1:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(13, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(13, 5, str);}break;
		case 2:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(14, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(14, 5, str);}break;
		case 3:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(15, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(15, 5, str);}break;
		case 4:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(16, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(16, 5, str);}break;
		}
	}
	else
	{
		switch(nTonnage)
		{
		case 1:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(9, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(9, 5, str);}break;
		case 2:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(10, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(10, 5, str);}break;
		case 3:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(11, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(11, 5, str);}break;
		case 4:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(12, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(12, 5, str);}break;
		}
	}

	m_fTotalAmount += fCharge;
}

void CFeeTablesView::DetTypeRIVehTrailer(const CString& strSQL,/* const int& nTonnage,*/ const bool& bDANGER/*=false*/)
{
	CString strSql(strSQL);
	strSql.AppendFormat(L"and (DetLog.DetType_M is NULL and DetLog.DetType is not NULL) ");
	// 定义检测类型
	strSql.AppendFormat(L"and DetLog.DetType  = '在用车检验（定检）' ");
	// 不能农用(电动）运输车
	strSql.AppendFormat(L"and (HisVehInfo.FuelType not like ('%%电%%')  or DetLog.PlateType not like ('%%农用%%') or DetLog.PlateType not like ('%%拖拉%%')) ");
	// 挂车
	strSql.AppendFormat(L"and (HisVehInfo.PlateType like ('%%挂%%')) ");
	// 是否危险运输车
	strSql.AppendFormat(L"and HisVehInfo.UseCharacter ");
	if (!bDANGER)
	{
		strSql.AppendFormat(L"not ");
	}
	strSql.AppendFormat(L"like ('%%危%%') ");

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}

	CString str;
	if (bDANGER)
	{
		str = m_pGridCtrl->GetItemText(18,3);
	}
	else
	{
		str = m_pGridCtrl->GetItemText(17,3);
	}
	float fCharge;
	fCharge = _wtof(str);

	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}

	if (bDANGER)
	{
		str.Format(L"%d", nTotalAmount);
		m_pGridCtrl->SetItemText(18, 4, str);
		str.Format(L"%.1f", fCharge);
		m_pGridCtrl->SetItemText(18, 5, str);
	}
	else
	{
		str.Format(L"%d", nTotalAmount);
		m_pGridCtrl->SetItemText(17, 4, str);
		str.Format(L"%.1f", fCharge);
		m_pGridCtrl->SetItemText(17, 5, str);
	}

	m_fTotalAmount += fCharge;
}

void CFeeTablesView::DetTypeRIVehSOVeh(const CString& strSQL)
{
	CString strSql(strSQL);
	strSql.AppendFormat(L"and (DetLog.DetType_M is NULL and DetLog.DetType is not NULL) ");
	// 定义检测类型
	strSql.AppendFormat(L"and DetLog.DetType  = '在用车检验（定检）' ");
	// 不能农用(电动）运输车
	strSql.AppendFormat(L"and (HisVehInfo.FuelType not like ('%%电%%')  or DetLog.PlateType not like ('%%农用%%') or DetLog.PlateType not like ('%%拖拉%%')) ");
	// 专项作业车
	strSql.AppendFormat(L"and (HisVehInfo.VehType like ('%%专项作业%%')) ");

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}

	CString str;
	str = m_pGridCtrl->GetItemText(19,3);

	float fCharge;
	fCharge = _wtof(str);

	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}

	str.Format(L"%d", nTotalAmount);
	m_pGridCtrl->SetItemText(19, 4, str);
	str.Format(L"%.1f", fCharge);
	m_pGridCtrl->SetItemText(19, 5, str);

	m_fTotalAmount += fCharge;
}

void CFeeTablesView::TGECoachLeaseSmallVeh(const CString& strSQL)
{
	CString strSql(strSQL);
	strSql.AppendFormat(L"and (DetLog.DetType_M is not NULL and DetLog.DetType is NULL) ");
	// 定义检测类型
	strSql.AppendFormat(L"and DetLog.DetType_M  = '技术等级评定' ");
	// 定义是小型汽车 货车小于4.5，客车座位小于10
	strSql.AppendFormat(L"and (HisVehInfo.MaximumTotalMass < 4500 and HisVehInfo.RatedPassengerCapacity < 10)" );


	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}

	CString str;
	str = m_pGridCtrl->GetItemText(22,3);

	float fCharge;
	fCharge = _wtof(str);

	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}

	str.Format(L"%d", nTotalAmount);
	m_pGridCtrl->SetItemText(22, 4, str);
	str.Format(L"%.1f", fCharge);
	m_pGridCtrl->SetItemText(22, 5, str);

	m_fTotalAmount += fCharge;
}

void CFeeTablesView::TGERIVehPCar(const CString& strSQL, const int& nNumber)
{
	CString strSql(strSQL);
	strSql.AppendFormat(L"and (DetLog.DetType_M is not NULL and DetLog.DetType is NULL) ");
	// 定义检测类型
	strSql.AppendFormat(L"and DetLog.DetType_M  = '技术等级评定' ");
	// 客车
	strSql.AppendFormat(L"and HisVehInfo.VehType not like ('%%货车%%') and HisVehInfo.VehType not like ('%%挂车%%') \
						 and HisVehInfo.VehType not like ('%%作业车%%') and HisVehInfo.VehType not like ('%%牵引车%%') ");
	if (nNumber == 1)
	{
		// 10-19人
		strSql.AppendFormat(L"and (HisVehInfo.RatedPassengerCapacity >= 10 and  HisVehInfo.RatedPassengerCapacity <= 19) ");
	}
	else
	{
		// 20人及以上
		strSql.AppendFormat(L"and HisVehInfo.RatedPassengerCapacity >= 20 ");
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}


	CString str;
	if (nNumber == 1)
	{
		str = m_pGridCtrl->GetItemText(23,3);
	}
	else
	{
		str = m_pGridCtrl->GetItemText(24,3);
	}
	float fCharge;
	fCharge = _wtof(str);


	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}
	GV_ITEM Item;
	//Item.col = 0;
	//Item.row = 0;
	//Item.mask = GVIF_TEXT|GVIF_FORMAT;
	//Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	//Item.szText.Format(L"营业日表格");
	//m_pGridCtrl->SetItem(&Item);
	if (nNumber == 1)
	{
		str.Format(L"%d", nTotalAmount);
		m_pGridCtrl->SetItemText(23, 4, str);
		str.Format(L"%.1f", fCharge);
		m_pGridCtrl->SetItemText(23, 5, str);
	}
	else
	{
		str.Format(L"%d", nTotalAmount);
		m_pGridCtrl->SetItemText(24, 4, str);
		str.Format(L"%.1f", fCharge);
		m_pGridCtrl->SetItemText(24, 5, str);
	}
	m_fTotalAmount += fCharge;
}

void CFeeTablesView::TGERIVehTruck(const CString& strSQL, const int& nTonnage, const bool& bDANGER/*=false*/)
{
	CString strSql(strSQL);
	strSql.AppendFormat(L"and (DetLog.DetType_M is not NULL and DetLog.DetType is NULL) ");
	// 定义检测类型
	strSql.AppendFormat(L"and DetLog.DetType_M  = '技术等级评定' ");
	// 货车或牵引车
	strSql.AppendFormat(L"and (HisVehInfo.VehType like ('%%货车%%') or HisVehInfo.VehType like ('%%牵引车%%')) ");
	// 是否危险运输车
	strSql.AppendFormat(L"and HisVehInfo.UseCharacter ");
	if (!bDANGER)
	{
		strSql.AppendFormat(L"not ");
	}
	strSql.AppendFormat(L"like ('%%危%%') ");
	// 吨位 //牵引车按总质量30t以上收费
	// 1.总质量4.5t以下
	// 2.总质量4.5-12t
	// 3.总质量12-30t
	// 4.总质量30t以上
	if (nTonnage == 1 && bDANGER)
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass < 4500 and HisVehInfo.VehType not like ('%%牵引车%%') ");
	}
	else if (nTonnage == 2 )
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass > 4500 and HisVehInfo.MaximumTotalMass < 12000 and HisVehInfo.VehType not like ('%%牵引车%%') ");
	}
	else 
	{
		strSql.AppendFormat(L"and (HisVehInfo.MaximumTotalMass > 12000 or HisVehInfo.VehType like ('%%牵引车%%')) ");
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}

	CString str;
	if (bDANGER)
	{
		switch(nTonnage)
		{
		case 1:{str = m_pGridCtrl->GetItemText(27,3);}break;
		case 2:{str = m_pGridCtrl->GetItemText(28,3);}break;
		case 3:{str = m_pGridCtrl->GetItemText(29,3);}break;
		}
	}
	else
	{
		switch(nTonnage)
		{
			//case 1:{str = m_pGridCtrl->GetItemText(,3);}break;
		case 2:{str = m_pGridCtrl->GetItemText(25,3);}break;
		case 3:{str = m_pGridCtrl->GetItemText(26,3);}break;
		}
	}
	float fCharge;
	fCharge = _wtof(str);

	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}

	if (bDANGER)
	{
		switch(nTonnage)
		{
		case 1:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(27, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(27, 5, str);}break;
		case 2:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(28, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(28, 5, str);}break;
		case 3:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(29, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(29, 5, str);}break;
		}
	}
	else
	{
		switch(nTonnage)
		{
			//case 1:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(9, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(9, 5, str);}break;
		case 2:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(25, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(25, 5, str);}break;
		case 3:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(26, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(26, 5, str);}break;
		}
	}

	m_fTotalAmount += fCharge;
}

void CFeeTablesView::TheToOneCoachLeaseSmallVeh(const CString& strSQL)
{
	CString strSql(strSQL);
	strSql.AppendFormat(L"and (DetLog.DetType_M is not NULL and DetLog.DetType is not NULL) ");
	// 定义检测类型
	strSql.AppendFormat(L"and DetLog.DetType_M  = '技术等级评定' and DetLog.DetType  = '在用车检验（定检）' ");
	// 定义是小型汽车 货车小于4.5，客车座位小于10
	strSql.AppendFormat(L"and (HisVehInfo.MaximumTotalMass < 4500 and HisVehInfo.RatedPassengerCapacity < 10)" );


	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}

	CString str;
	str = m_pGridCtrl->GetItemText(32,3);

	float fCharge;
	fCharge = _wtof(str);

	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}

	str.Format(L"%d", nTotalAmount);
	m_pGridCtrl->SetItemText(32, 4, str);
	str.Format(L"%.1f", fCharge);
	m_pGridCtrl->SetItemText(32, 5, str);

	m_fTotalAmount += fCharge;
}

void CFeeTablesView::TheToOneRIVehPCar(const CString& strSQL, const int& nNumber)
{
	CString strSql(strSQL);
	strSql.AppendFormat(L"and (DetLog.DetType_M is not NULL and DetLog.DetType is not NULL) ");
	// 定义检测类型
	strSql.AppendFormat(L"and DetLog.DetType_M  = '技术等级评定' and DetLog.DetType  = '在用车检验（定检）' ");
	// 客车
	strSql.AppendFormat(L"and HisVehInfo.VehType not like ('%%货车%%') and HisVehInfo.VehType not like ('%%挂车%%') \
						 and HisVehInfo.VehType not like ('%%作业车%%') and HisVehInfo.VehType not like ('%%牵引车%%') ");
	if (nNumber == 1)
	{
		// 10-19人
		strSql.AppendFormat(L"and (HisVehInfo.RatedPassengerCapacity >= 10 and  HisVehInfo.RatedPassengerCapacity <= 19) ");
	}
	else
	{
		// 20人及以上
		strSql.AppendFormat(L"and HisVehInfo.RatedPassengerCapacity >= 20 ");
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}


	CString str;
	if (nNumber == 1)
	{
		str = m_pGridCtrl->GetItemText(33,3);
	}
	else
	{
		str = m_pGridCtrl->GetItemText(34,3);
	}
	float fCharge;
	fCharge = _wtof(str);


	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}
	GV_ITEM Item;
	//Item.col = 0;
	//Item.row = 0;
	//Item.mask = GVIF_TEXT|GVIF_FORMAT;
	//Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	//Item.szText.Format(L"营业日表格");
	//m_pGridCtrl->SetItem(&Item);
	if (nNumber == 1)
	{
		str.Format(L"%d", nTotalAmount);
		m_pGridCtrl->SetItemText(33, 4, str);
		str.Format(L"%.1f", fCharge);
		m_pGridCtrl->SetItemText(33, 5, str);
	}
	else
	{
		str.Format(L"%d", nTotalAmount);
		m_pGridCtrl->SetItemText(34, 4, str);
		str.Format(L"%.1f", fCharge);
		m_pGridCtrl->SetItemText(34, 5, str);
	}
	m_fTotalAmount += fCharge;
}

void CFeeTablesView::TheToOneRIVehTruck(const CString& strSQL, const int& nTonnage, const bool& bDANGER/*=false*/)
{
	CString strSql(strSQL);
	strSql.AppendFormat(L"and (DetLog.DetType_M is not NULL and DetLog.DetType is not NULL) ");
	// 定义检测类型
	strSql.AppendFormat(L"and DetLog.DetType_M  = '技术等级评定' and DetLog.DetType  = '在用车检验（定检）' ");
	// 货车或牵引车
	strSql.AppendFormat(L"and (HisVehInfo.VehType like ('%%货车%%') or HisVehInfo.VehType like ('%%牵引车%%')) ");
	// 是否危险运输车
	strSql.AppendFormat(L"and HisVehInfo.UseCharacter ");
	if (!bDANGER)
	{
		strSql.AppendFormat(L"not ");
	}
	strSql.AppendFormat(L"like ('%%危%%') ");
	// 吨位 //牵引车按总质量30t以上收费
	// 1.总质量4.5t以下
	// 2.总质量4.5-12t
	// 3.总质量12-30t
	// 4.总质量30t以上
	if (nTonnage == 1 && bDANGER)
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass < 4500 and HisVehInfo.VehType not like ('%%牵引车%%') ");
	}
	else if (nTonnage == 2 )
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass > 4500 and HisVehInfo.MaximumTotalMass < 12000 and HisVehInfo.VehType not like ('%%牵引车%%') ");
	}
	else 
	{
		strSql.AppendFormat(L"and (HisVehInfo.MaximumTotalMass > 12000 or HisVehInfo.VehType like ('%%牵引车%%')) ");
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}

	CString str;
	if (bDANGER)
	{
		switch(nTonnage)
		{
		case 1:{str = m_pGridCtrl->GetItemText(37,3);}break;
		case 2:{str = m_pGridCtrl->GetItemText(38,3);}break;
		case 3:{str = m_pGridCtrl->GetItemText(39,3);}break;
		}
	}
	else
	{
		switch(nTonnage)
		{
			//case 1:{str = m_pGridCtrl->GetItemText(,3);}break;
		case 2:{str = m_pGridCtrl->GetItemText(35,3);}break;
		case 3:{str = m_pGridCtrl->GetItemText(36,3);}break;
		}
	}
	float fCharge;
	fCharge = _wtof(str);

	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}

	if (bDANGER)
	{
		switch(nTonnage)
		{
		case 1:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(37, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(37, 5, str);}break;
		case 2:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(38, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(38, 5, str);}break;
		case 3:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(39, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(39, 5, str);}break;
		}
	}
	else
	{
		switch(nTonnage)
		{
			//case 1:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(9, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(9, 5, str);}break;
		case 2:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(35, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(35, 5, str);}break;
		case 3:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(36, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(36, 5, str);}break;
		}
	}

	m_fTotalAmount += fCharge;
}

void CFeeTablesView::RegistrationRIVehPCar(const CString& strSQL)
{
	CString strSql(strSQL);
	strSql.AppendFormat(L"and (DetLog.DetType_M is NULL and DetLog.DetType is not NULL) ");
	// 定义检测类型
	strSql.AppendFormat(L"and DetLog.DetType  = '注册登记检验' ");
	// 客车
	strSql.AppendFormat(L"and HisVehInfo.VehType not like ('%%货车%%') and HisVehInfo.VehType not like ('%%挂车%%') \
						 and HisVehInfo.VehType not like ('%%作业车%%') and HisVehInfo.VehType not like ('%%牵引车%%') ");

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}


	CString str;
	str = m_pGridCtrl->GetItemText(42,3);
	float fCharge;
	fCharge = _wtof(str);


	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}
	GV_ITEM Item;
	//Item.col = 0;
	//Item.row = 0;
	//Item.mask = GVIF_TEXT|GVIF_FORMAT;
	//Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	//Item.szText.Format(L"营业日表格");
	//m_pGridCtrl->SetItem(&Item);

	str.Format(L"%d", nTotalAmount);
	m_pGridCtrl->SetItemText(42, 4, str);
	str.Format(L"%.1f", fCharge);
	m_pGridCtrl->SetItemText(42, 5, str);

	m_fTotalAmount += fCharge;
}

void CFeeTablesView::RegistrationRIVehTruck(const CString& strSQL, const int& nTonnage)
{
	CString strSql(strSQL);
	strSql.AppendFormat(L"and (DetLog.DetType_M is NULL and DetLog.DetType is not NULL) ");
	// 定义检测类型
	strSql.AppendFormat(L"and DetLog.DetType  = '注册登记检验' ");
	// 货车或牵引车
	strSql.AppendFormat(L"and (HisVehInfo.VehType like ('%%货车%%') or HisVehInfo.VehType like ('%%牵引车%%')) ");
	// 吨位 //牵引车按总质量30t以上收费
	// 1.总质量3.5t以下
	// 2.总质量3.5-4.5t
	// 3.总质量4.5t-31t以上
	if (nTonnage == 1)
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass < 3500 and HisVehInfo.VehType not like ('%%牵引车%%') ");
	}
	else if (nTonnage == 2)
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass > 3500 and HisVehInfo.MaximumTotalMass < 4500 and HisVehInfo.VehType not like ('%%牵引车%%') ");
	}
	else
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass > 4500 and HisVehInfo.MaximumTotalMass < 31000 and HisVehInfo.VehType like ('%%牵引车%%') ");
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}

	CString str;
	switch(nTonnage)
	{
	case 1:{str = m_pGridCtrl->GetItemText(43,3);}break;
	case 2:{str = m_pGridCtrl->GetItemText(44,3);}break;
	case 3:{str = m_pGridCtrl->GetItemText(45,3);}break;
	}
	float fCharge;
	fCharge = _wtof(str);

	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}

	switch(nTonnage)
	{
	case 1:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(43, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(43, 5, str);}break;
	case 2:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(44, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(44, 5, str);}break;
	case 3:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(45, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(45, 5, str);}break;
	}


	m_fTotalAmount += fCharge;
}

void CFeeTablesView::RegistrationRIVehSOVeh(const CString& strSQL)
{
	CString strSql(strSQL);
	strSql.AppendFormat(L"and (DetLog.DetType_M is NULL and DetLog.DetType is not NULL) ");
	// 定义检测类型
	strSql.AppendFormat(L"and DetLog.DetType  = '注册登记检验' ");
	// 专项作业车
	strSql.AppendFormat(L"and (HisVehInfo.VehType like ('%%专项作业%%')) ");

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}

	CString str;
	str = m_pGridCtrl->GetItemText(46,3);

	float fCharge;
	fCharge = _wtof(str);

	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}

	str.Format(L"%d", nTotalAmount);
	m_pGridCtrl->SetItemText(46, 4, str);
	str.Format(L"%.1f", fCharge);
	m_pGridCtrl->SetItemText(46, 5, str);

	m_fTotalAmount += fCharge;
}

void CFeeTablesView::NewTheToOneRIVehTruck(const CString& strSQL)
{
	CString strSql(strSQL);
	strSql.AppendFormat(L"and (DetLog.DetType_M is not NULL and DetLog.DetType is not NULL) ");
	// 定义检测类型
	strSql.AppendFormat(L"and DetLog.DetType_M  = '技术等级评定' and DetLog.DetType  = '注册登记检验' ");
	// 货车或牵引车
	strSql.AppendFormat(L"and (HisVehInfo.VehType like ('%%货车%%') or HisVehInfo.VehType like ('%%牵引车%%')) ");

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}

	CString str;

	str = m_pGridCtrl->GetItemText(49,3);

	float fCharge;
	fCharge = _wtof(str);

	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}

	str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(49, 4, str);
	str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(49, 5, str);


	m_fTotalAmount += fCharge;
}

void CFeeTablesView::NoFixedCheck(const CString& strSQL)
{
	CString strSql(strSQL);
	// 
	strSql.AppendFormat(L"and (DetLog.DetType_M is NULL and DetLog.DetType is not NULL) ");
	// 定义检测类型
	strSql.AppendFormat(L"and DetLog.DetType  = '在用车检验（非定检）' ");

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}

	CString str;

	str = m_pGridCtrl->GetItemText(52,3);

	float fCharge;
	fCharge = _wtof(str);

	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}

	str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(52, 4, str);
	str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(52, 5, str);


	m_fTotalAmount += fCharge;
}

void CFeeTablesView::TemIns(const CString& strSQL, const int& nTonnage)
{
	CString strSql(strSQL);
	// 
	strSql.AppendFormat(L"and (DetLog.DetType_M is NULL and DetLog.DetType is not NULL) ");
	// 定义检测类型
	strSql.AppendFormat(L"and DetLog.DetType  = '临时检测' ");

	// 1.过户
	// 2.转出
	// 3.转入
	if (nTonnage == 1)
	{
		strSql.AppendFormat(L"and Charge.ChargeItem = '过户' ");
	}
	else if (nTonnage == 2)
	{
		strSql.AppendFormat(L"and Charge.ChargeItem = '转出' ");
	}
	else
	{
		strSql.AppendFormat(L"and Charge.ChargeItem = '转入' ");
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}

	CString str;

	switch(nTonnage)
	{
	case 1:{str = m_pGridCtrl->GetItemText(54,3);}break;
	case 2:{str = m_pGridCtrl->GetItemText(55,3);}break;
	case 3:{str = m_pGridCtrl->GetItemText(56,3);}break;
	}

	float fCharge;
	fCharge = _wtof(str);

	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}

	switch(nTonnage)
	{
	case 1:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(54, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(54, 5, str);}break;
	case 2:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(55, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(55, 5, str);}break;
	case 3:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(56, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(56, 5, str);}break;
	}
}

void CFeeTablesView::Mis(const int& nTonnage)
{
	COleDateTime odtBeginTime(COleDateTime::GetCurrentTime());
	COleDateTime odtEndTime(COleDateTime::GetCurrentTime());
	m_dtcBegTime.GetTime(odtBeginTime);
	m_dtcEndTime.GetTime(odtEndTime);

	CString strSql(L"");

	strSql.AppendFormat(L" select *");
	strSql.AppendFormat(L" from Charge");
	strSql.AppendFormat(L" where Charge.PlateNumber = '杂项' ");
	strSql.AppendFormat(L" and (Charge.ChargingTime between '%s 00:00:00' and '%s 23:59:59') ", 
		odtBeginTime.Format(L"%Y-%m-%d"),  odtEndTime.Format(L"%Y-%m-%d"));

	// 1.A
	// 2.B
	// 3.摩托车
	// 4.反光膜
	// 5.三角警告牌
	// 6.灭火器
	// 7.照相
	// 8.预留项
	switch(nTonnage)
	{
	case 1:{strSql.AppendFormat(L" and Charge.ChargeItem = 'A' ");}break;
	case 2:{strSql.AppendFormat(L" and Charge.ChargeItem = 'B' ");}break;
	case 3:{strSql.AppendFormat(L" and Charge.ChargeItem = '摩托车' ");}break;
	case 4:{strSql.AppendFormat(L" and Charge.ChargeItem = '反光膜' ");}break;
	case 5:{strSql.AppendFormat(L" and Charge.ChargeItem = '三角警告牌' ");}break;
	case 6:{strSql.AppendFormat(L" and Charge.ChargeItem = '灭火器' ");}break;
	case 7:{strSql.AppendFormat(L" and Charge.ChargeItem = '照相' ");}break;
	case 8:{strSql.AppendFormat(L" and Charge.ChargeItem = '预留项' ");}break;
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// 打开查询失败
		MessageBox(L"查询数据库失败,请检查网络连接!", L"查询统计", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// 关闭查询失败
	}

	CString str;

	switch(nTonnage)
	{
	case 1:{str = m_pGridCtrl->GetItemText(58,3);}break;
	case 2:{str = m_pGridCtrl->GetItemText(59,3);}break;
	case 3:{str = m_pGridCtrl->GetItemText(60,3);}break;
	case 4:{str = m_pGridCtrl->GetItemText(61,3);}break;
	case 5:{str = m_pGridCtrl->GetItemText(62,3);}break;
	case 6:{str = m_pGridCtrl->GetItemText(63,3);}break;
	case 7:{str = m_pGridCtrl->GetItemText(64,3);}break;
	case 8:{str = m_pGridCtrl->GetItemText(65,3);}break;
	}

	float fCharge;
	fCharge = _wtof(str);

	if (nTotalAmount != 0)
	{
		fCharge = nTotalAmount * fCharge;
	}
	else
	{
		fCharge = 0.0f;
	}

	switch(nTonnage)
	{
	case 1:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(58, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(58, 5, str);}break;
	case 2:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(59, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(59, 5, str);}break;
	case 3:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(60, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(60, 5, str);}break;
	case 4:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(61, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(61, 5, str);}break;
	case 5:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(62, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(62, 5, str);}break;
	case 6:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(63, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(63, 5, str);}break;
	case 7:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(64, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(64, 5, str);}break;
	case 8:{str.Format(L"%d", nTotalAmount);m_pGridCtrl->SetItemText(65, 4, str);str.Format(L"%.1f", fCharge);m_pGridCtrl->SetItemText(65, 5, str);}break;
	}

	m_fTotalAmount += fCharge;

}