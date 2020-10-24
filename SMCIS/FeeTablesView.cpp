// FeeTablesView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SMCIS.h"
#include "FeeTablesView.h"

#define DLG_CAPTION L"�շ�ͳ�Ʊ��"
// CFeeTablesView

IMPLEMENT_DYNCREATE(CFeeTablesView, CFormView)

	CFeeTablesView::CFeeTablesView()
	: CFormView(CFeeTablesView::IDD)
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


// CFeeTablesView ���

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


// CFeeTablesView ��Ϣ�������


void CFeeTablesView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	InitCtrls();
}

void CFeeTablesView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (m_pGridCtrl->GetSafeHwnd())
	{
		CRect rect;
		GetDlgItem(IDC_LST_STAT)->GetClientRect(rect);
		m_pGridCtrl->MoveWindow(rect);
	}
}


void CFeeTablesView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CFormView::OnTimer(nIDEvent);
}


BOOL CFeeTablesView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: �ڴ����ר�ô����/����û���
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
//		// ���� GridCtrl ����
//		m_pGridCtrl = new CGridCtrl;
//		if (!m_pGridCtrl) return;
//
//		// ���� Gridctrl ����
//		CRect rect;
//		GetDlgItem(IDC_LST_STAT)->GetClientRect(rect); // �õ���ʾ����
//		m_pGridCtrl->Create(rect, &m_lstVehCount, IDC_LST_STAT);
//
//		try 
//		{
//			m_pGridCtrl->SetRowCount(43); // ��ʼ������
//			m_pGridCtrl->SetColumnCount(5);	// ��ʼ������
//			m_pGridCtrl->SetFixedRowCount(3);	// //�̶���
//			m_pGridCtrl->SetFixedColumnCount(2);// �̶���
//		}
//		catch (CMemoryException* e)
//		{
//			e->ReportError();
//			e->Delete();
//			return;
//		}
//
//		// ���ÿ������
//		for (int nRow = 0; nRow < m_pGridCtrl->GetRowCount(); nRow++)
//		{
//			for (int nCol = 0; nCol < m_pGridCtrl->GetColumnCount(); nCol++)
//			{
//				GV_ITEM Item;
//				Item.mask = GVIF_TEXT|GVIF_FORMAT;
//				Item.row = nRow;
//				Item.col = nCol;
//
//				// �趨�̶�����(���趨��)
//				if (nCol < 1)
//				{
//					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
//					switch(nRow)
//					{
//					case 0:
//						{
//							Item.szText.Format(L"Ӫҵ�ձ��");
//						}
//						break;
//					case 1:
//						{
//							Item.szText.Format(COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d"));
//						}
//						break;
//					case 2:
//						{
//							Item.szText.Format(L"��Ŀ");
//						}
//						break;
//					case 3:
//						{
//							Item.szText.Format(L"ũ��(�綯)���䳵");
//						}
//						break;
//					case 4:
//						{
//							Item.szText.Format(L"С��");
//						}
//						break;
//					case 5:
//						{
//							Item.szText.Format(L"У��");
//						}
//						break;
//					case 6:
//						{
//							Item.szText.Format(L"�ͳ���20�ˣ�");
//						}
//						break;
//					case 7:
//						{
//							Item.szText.Format(L"����4.5������");
//						}
//						break;
//					case 8:
//						{
//							Item.szText.Format(L"����(4.5-12��)");
//						}
//						break;
//					case 9:
//						{
//							Item.szText.Format(L"����(12-30��)");
//						}
//						break;
//					case 10:
//						{
//							Item.szText.Format(L"����(30-45��)");
//						}
//						break;
//					case 11:
//						{
//							Item.szText.Format(L"�ҳ�");
//						}
//						break;
//					case 12:
//						{
//							Item.szText.Format(L"�ҳ�(Σ��)");
//						}
//						break;
//					case 13:
//						{
//							Item.szText.Format(L"���ֳ���");
//						}
//						break;
//					case 14:
//						{
//							Item.szText.Format(L"�����һ");
//						}
//						break;
//					case 21:
//						{
//							Item.szText.Format(L"����ϼ�");
//						}
//						break;
//					case 22:
//					case 23:
//					case 24:
//					case 25:
//						{
//							Item.szText.Format(L"�ȼ�����");
//						}
//						break;
//					case 26:
//						{
//							Item.szText.Format(L"�ۼ�ϼ�");
//						}
//						break;
//					case 27:
//					case 28:
//					case 29:
//					case 30:
//					case 31:
//						{
//							Item.szText.Format(L"�³����");
//						}
//						break;
//					case 32:
//						{
//							Item.szText.Format(L"�³��ϼ�");
//						}
//						break;
//					case 33:
//						{
//							Item.szText.Format(L"����");
//						}
//						break;
//					case 34:
//						{
//							Item.szText.Format(L"����");
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
//							Item.szText.Format(L"���ܻ���ҵ��ϼ�");
//						}
//						break;
//					case 38:
//						{
//							Item.szText.Format(L"Ħ�г�");
//						}
//						break;
//					case 39:
//						{
//							Item.szText.Format(L"���");
//						}
//						break;
//					case 40:
//						{
//							Item.szText.Format(L"����");
//						}
//						break;
//					case 41:
//						{
//							Item.szText.Format(L"�����ϼ�");
//						}
//						break;
//					case 42:
//						{
//							Item.szText.Format(L"�ۼ�");
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
//							Item.szText.Format(L"������4.5t");
//						}
//						break;
//					case 15:
//						{
//							Item.szText.Format(L"�ͳ�(10-19)");
//						}
//						break;
//					case 16:
//						{
//							Item.szText.Format(L"�ͳ�20��");
//						}
//						break;
//					case 17:
//						{
//							Item.szText.Format(L"����4.5-12��");
//						}
//						break;
//					case 18:
//						{
//							Item.szText.Format(L"Σ��4.5-12��");
//						}
//						break;
//					case 19:
//						{
//							Item.szText.Format(L"����12������");
//						}
//						break;
//					case 20:
//						{
//							Item.szText.Format(L"Σ��12������");
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
//				// �趨�̶�����(���趨��)
//				if (nRow == 2)
//				{
//					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
//					switch(nCol)
//					{
//					case 2:
//						{
//							Item.szText.Format(L"����");
//						}
//						break;
//					case 3:
//						{
//							Item.szText.Format(L"����");
//						}
//						break;
//					case 4:
//						{
//							Item.szText.Format(L"���");
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
//		// �ϲ���Ԫ��(�У��У��кϲ������кϲ���)
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
//	// �������и�
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
		// ���� GridCtrl ����
		m_pGridCtrl = new CGridCtrl;
		if (!m_pGridCtrl) return;

		// ���� Gridctrl ����
		CRect rect;
		GetDlgItem(IDC_LST_STAT)->GetClientRect(rect); // �õ���ʾ����
		m_pGridCtrl->Create(rect, &m_lstVehCount, IDC_LST_STAT);

		try 
		{
			m_pGridCtrl->SetRowCount(68); // ��ʼ������
			m_pGridCtrl->SetColumnCount(6);	// ��ʼ������
			m_pGridCtrl->SetFixedRowCount(3);	// //�̶���
			m_pGridCtrl->SetFixedColumnCount(4);// �̶���
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

				// �趨�̶�����(���趨��)
				if (nCol < 1)
				{
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					switch(nRow)
					{
					case 0:
						{
							Item.szText.Format(L"Ӫҵ�ձ��");
						}
						break;
					case 1:
						{
							Item.szText.Format(COleDateTime::GetCurrentTime().Format(L"%Y-%m-%d"));
						}
						break;
					case 2:
						{
							Item.szText.Format(L"�������");
						}
						break;
					case 3:
						{
							Item.szText.Format(L"���ó����飨���죩");
						}
						break;
					case 21:
						{
							Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
							Item.szText.Format(L"���ó����죨���죩�ϼƣ�");
						}
						break;
					case 22:
						{
							Item.szText.Format(L"�����ȼ�����");
						}
						break;
					case 31:
						{
							Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
							Item.szText.Format(L"�ڼ����ȼ�����ͳ�ƣ�");
						}
						break;
					case 32:
						{
							Item.szText.Format(L"���ó����飨���죩//�����ȼ�����");
						}
						break;
					case 41:
						{
							Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
							Item.szText.Format(L"���ó������һͳ�ƣ�");
						}
						break;
					case 42:
						{
							Item.szText.Format(L"ע��ǼǼ���");
						}
						break;
					case 48:
						{
							Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
							Item.szText.Format(L"ע��ǼǼ���ͳ�ƣ�");
						}
						break;
					case 49:
						{
							Item.szText.Format(L"ע��ǼǼ���//�����ȼ�����");
						}
						break;
					case 51:
						{
							Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
							Item.szText.Format(L"ע��Ǽ������һͳ�ƣ�");
						}
						break;
					case 52:
						{
							Item.szText.Format(L"���ó����飨�Ƕ��죩");
						}
						break;
					case 53:
						{
							Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
							Item.szText.Format(L"���ó����飨�Ƕ��죩ͳ�ƣ�");
						}
						break;
					case 54:
						{
							Item.szText.Format(L"��ʱ����");
						}
						break;
					case 57:
						{
							Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
							Item.szText.Format(L"��ʱ����ͳ�ƣ�");
						}
						break;
					case 58:
						{
							Item.szText.Format(L"����");
						}
						break;
					case 66:
						{
							Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
							Item.szText.Format(L"����ͳ�ƣ�");
						}
						break;
					case 67:
						{
							Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
							Item.szText.Format(L"�ۼƣ�");
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
							Item.szText.Format(L"�����ȼ�����");
						}
						break;
					case 32:
						{
							Item.szText.Format(L"���ó����飨���죩//�����ȼ�����");
						}
						break;
					case 42:
						{
							Item.szText.Format(L"00");
						}
						break;
					case 49:
						{
							Item.szText.Format(L"ע��ǼǼ���//�����ȼ�����");
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
							Item.szText.Format(L"����");
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
							Item.szText.Format(L"ũ��(�綯�����䳵");
						}
						break;
					case 4:
						{
							Item.szText.Format(L"��Ӫ�˿ͳ���9������");
						}
						break;
					case 5:
						{
							Item.szText.Format(L"���Ϳͳ���10-19��");
						}
						break;
					case 6:
						{
							Item.szText.Format(L"���Ϳͳ���20�˼�����");
						}
						break;
					case 7:
						{
							Item.szText.Format(L"У����10-19��");
						}
						break;
					case 8:
						{
							Item.szText.Format(L"У����20�˼�����");
						}
						break;
					case 9:
						{
							Item.szText.Format(L"������������4.5t����");
						}
						break;
					case 10:
						{
							Item.szText.Format(L"������������4.5-12t");
						}
						break;
					case 11:
						{
							Item.szText.Format(L"������������12-30t");
						}
						break;
					case 12:
						{
							Item.szText.Format(L"������������30t����");
						}
						break;
					case 13:
						{
							Item.szText.Format(L"������Σ������������4.5t����");
						}
						break;
					case 14:
						{
							Item.szText.Format(L"������Σ������������4.5-12t");
						}
						break;
					case 15:
						{
							Item.szText.Format(L"������Σ������������12-30t");
						}
						break;
					case 16:
						{
							Item.szText.Format(L"������Σ������������30t����");
						}
						break;
					case 17:
						{
							Item.szText.Format(L"�ҳ���30t����");
						}
						break;
					case 18:
						{
							Item.szText.Format(L"�ҳ�(Σ������30t����");
						}
						break;
					case 19:
						{
							Item.szText.Format(L"ר����ҵ������������30t����");
						}
						break;
					case 20:
						{
							Item.szText.Format(L"Ԥ����");
						}
						break;
					case 22:
						{
							Item.szText.Format(L"����������С�ͳ���");
						}
						break;
					case 23:
						{
							Item.szText.Format(L"���Ϳͳ���10-19��");
						}
						break;
					case 24:
						{
							Item.szText.Format(L"���Ϳͳ���20�˼�����");
						}
						break;
					case 25:
						{
							Item.szText.Format(L"������������4.5-12t");
						}
						break;
					case 26:
						{
							Item.szText.Format(L"������������12t����");
						}
						break;
					case 27:
						{
							Item.szText.Format(L"Σ����������4.5t����");
						}
						break;
					case 28:
						{
							Item.szText.Format(L"Σ����������4.5-12t");
						}
						break;
					case 29:
						{
							Item.szText.Format(L"Σ����������12t����");
						}
						break;
					case 30:
						{
							Item.szText.Format(L"Ԥ����");
						}
						break;
					case 32:
						{
							Item.szText.Format(L"����������С�ͳ���");
						}
						break;
					case 33:
						{
							Item.szText.Format(L"���Ϳͳ���10-19��");
						}
						break;
					case 34:
						{
							Item.szText.Format(L"���Ϳͳ���20�˼�����");
						}
						break;
					case 35:
						{
							Item.szText.Format(L"������������4.5-12t");
						}
						break;
					case 36:
						{
							Item.szText.Format(L"������������12t����");
						}
						break;
					case 37:
						{
							Item.szText.Format(L"Σ����������4.5t����");
						}
						break;
					case 38:
						{
							Item.szText.Format(L"Σ����������4.5-12t");
						}
						break;
					case 39:
						{
							Item.szText.Format(L"Σ����������12t����");
						}
						break;
					case 40:
						{
							Item.szText.Format(L"Ԥ����");
						}
						break;
					case 42:
						{
							Item.szText.Format(L"�����С�Ϳͳ�");
						}
						break;
					case 43:
						{
							Item.szText.Format(L"������������3.5t����");
						}
						break;
					case 44:
						{
							Item.szText.Format(L"������������3.5-4.5t");
						}
						break;
					case 45:
						{
							Item.szText.Format(L"������������4.5-31t");
						}
						break;
					case 46:
						{
							Item.szText.Format(L"ר����ҵ������������30t����");
						}
						break;
					case 47:
						{
							Item.szText.Format(L"Ԥ����");
						}
						break;
					case 49:
						{
							Item.szText.Format(L"������������4.5-31t");
						}
						break;
					case 50:
						{
							Item.szText.Format(L"Ԥ����");
						}
						break;
					case 52:
						{
							Item.szText.Format(L"����ʵ�������д����");
						}
						break;
					case 54:
						{
							Item.szText.Format(L"����");
						}
						break;
					case 55:
						{
							Item.szText.Format(L"ת��");
						}
						break;
					case 56:
						{
							Item.szText.Format(L"ת��");
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
							Item.szText.Format(L"Ħ�г�");
						}
						break;
					case 61:
						{
							Item.szText.Format(L"����Ĥ");
						}
						break;
					case 62:
						{
							Item.szText.Format(L"���Ǿ�����");
						}
						break;
					case 63:
						{
							Item.szText.Format(L"�����");
						}
						break;
					case 64:
						{
							Item.szText.Format(L"����");
						}
						break;
					case 65:
						{
							Item.szText.Format(L"Ԥ����");
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

				// �趨�̶�����(���趨��)
				if (nRow == 2)
				{
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					switch(nCol)
					{
					case 1:
						{
							Item.szText.Format(L"����������");
						}
						break;
					case 2:
						{
							Item.szText.Format(L"��Ŀ");
						}
						break;
					case 3:
						{
							Item.szText.Format(L"����");
						}
						break;
					case 4:
						{
							Item.szText.Format(L"����");
						}
						break;
					case 5:
						{
							Item.szText.Format(L"���");
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
		// �ϲ���Ԫ��(�У��У��кϲ������кϲ���)
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

	// �������и�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_pGridCtrl->GetSafeHwnd())
	{
		return;
	}
	// ɾ��֮ǰ��¼
	//m_pGridCtrl->DeleteAllItems();

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
	m_nTotNum = 0;
	m_fAmountOfCharges = 0.0f;

	CString strSql;
	strSql = GetSQL();
	// ��ȷ������������ۼ죬���죬�����һ�ڷּ������
	m_fTotalAmount = 0.0f;
	// ũ��(�綯�����䳵
	DetTypeRIVehATVeh(strSql);
	// �ͳ���9������
	DetTypeRIVehPCar(strSql, 1);
	DetTypeRIVehPCar(strSql, 2);
	DetTypeRIVehPCar(strSql, 3);
	// У��
	DetTypeRIVehSchbus(strSql, 1);
	DetTypeRIVehSchbus(strSql, 2);
	// ����
	for (int i=1; i<5;i++)
	{
		DetTypeRIVehTruck(strSql, i, false);
		DetTypeRIVehTruck(strSql, i, true);
	}
	// �ҳ�
	DetTypeRIVehTrailer(strSql, false);
	DetTypeRIVehTrailer(strSql, true);
	// ר����ҵ��
	DetTypeRIVehSOVeh(strSql);
	// ���ó��ܽ��
	TotalAmountOfTestCategory(1, m_fTotalAmount);

	// �����ȼ�����
	m_fTotalAmount = 0.0f;
	// С������
	TGECoachLeaseSmallVeh(strSql);
	TGERIVehPCar(strSql, 1);
	TGERIVehPCar(strSql, 2);
	TGERIVehTruck(strSql, 1, true);
	TGERIVehTruck(strSql, 2, true);
	TGERIVehTruck(strSql, 2, false);
	TGERIVehTruck(strSql, 3, true);
	TGERIVehTruck(strSql, 3, false);
	TotalAmountOfTestCategory(2, m_fTotalAmount);

	// �����һ
	m_fTotalAmount = 0.0f;
	// С������
	TheToOneCoachLeaseSmallVeh(strSql);
	TheToOneRIVehPCar(strSql, 1);
	TheToOneRIVehPCar(strSql, 2);
	TheToOneRIVehTruck(strSql, 1, true);
	TheToOneRIVehTruck(strSql, 2, true);
	TheToOneRIVehTruck(strSql, 2, false);
	TheToOneRIVehTruck(strSql, 3, true);
	TheToOneRIVehTruck(strSql, 3, false);
	TotalAmountOfTestCategory(3, m_fTotalAmount);

	// ע��Ǽ�
	m_fTotalAmount = 0.0f;
	RegistrationRIVehPCar(strSql);
	RegistrationRIVehTruck(strSql, 1);
	RegistrationRIVehTruck(strSql, 2);
	RegistrationRIVehTruck(strSql, 3);
	RegistrationRIVehSOVeh(strSql);
	TotalAmountOfTestCategory(4, m_fTotalAmount);

	// �����һ (�³�)
	m_fTotalAmount = 0.0f;
	NewTheToOneRIVehTruck(strSql);
	TotalAmountOfTestCategory(5, m_fTotalAmount);

	// �Ƕ���
	m_fTotalAmount = 0.0f;
	NoFixedCheck(strSql);
	TotalAmountOfTestCategory(6, m_fTotalAmount);

	// ��ʱ���
	m_fTotalAmount = 0.0f;
	TemIns(strSql, 1);
	TemIns(strSql, 2);
	TemIns(strSql, 3);
	TotalAmountOfTestCategory(7, m_fTotalAmount);
	
	// ����
	m_fTotalAmount = 0.0f;
	for (int i =0;i<8; i++)
	{
		Mis(i+1);
	}
	TotalAmountOfTestCategory(8, m_fTotalAmount);

	// �ۼ�

	TotalAmountOfTestCategory(9, 0.0f);

	//// ����
	//strSql.AppendFormat(L"and (DetLog.DetType_M is NULL and DetLog.DetType is not NULL) ");
	//// �ۼ�
	//strSql.AppendFormat(L"and (DetLog.DetType_M is not NULL and DetLog.DetType is NULL) ");
	//// �����һ
	//strSql.AppendFormat(L"and (DetLog.DetType_M is not NULL and DetLog.DetType is not NULL) ");

	m_pGridCtrl->Invalidate(); // ˢ�¿ؼ�
}


void CFeeTablesView::OnBnClickedBtnPrint()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pGridCtrl->GetSafeHwnd())
	{
		m_pGridCtrl->AutoSize();
		m_pGridCtrl->Print();
	}
}


void CFeeTablesView::OnBnClickedBtnExport()
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

CString CFeeTablesView::GetSQL(void)
{
	/*
	��ͬ������ͳһд�������ķֿ�
	*/
	COleDateTime odtBeginTime(COleDateTime::GetCurrentTime());
	COleDateTime odtEndTime(COleDateTime::GetCurrentTime());
	m_dtcBegTime.GetTime(odtBeginTime);
	m_dtcEndTime.GetTime(odtEndTime);

	CString strSql;
	strSql.AppendFormat(L"select * ");
	// ���ع��� DetLog��Charge��DetPeriod��HisVehInfo����
	strSql.AppendFormat(L"from DetLog ");
	strSql.AppendFormat(L"INNER Join Charge ON Charge.RunningNumber = DetLog.RunningNumber ");
	strSql.AppendFormat(L"INNER Join DetPeriod ON  DetPeriod.DetPeriodID = DetLog.DetPeriodID ");
	strSql.AppendFormat(L"INNER Join HisVehInfo ON HisVehInfo.RunningNumber = DetLog.RunningNumber ");
	strSql.AppendFormat(L"where ");
	// ������ȡ�����
	strSql.AppendFormat(L"(DetLog.DetStatus != 'CANDET') ");
	// �Ƿ�Ҫ��ɼ�� ��ʱ��Ҫ
	//strSql.AppendFormat(L"and (DetLog.DetStatus = 'FINDET') ");
	// ��½ʱ��
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
	// ����������
	strSql.AppendFormat(L"and DetLog.DetType  = '���ó����飨���죩' ");
	// ũ��(�綯�����䳵
	strSql.AppendFormat(L"and (HisVehInfo.FuelType like '%%��%%'  or DetLog.PlateType like '%%ũ��%%' or DetLog.PlateType like '%%����%%') ");

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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
	//Item.szText.Format(L"Ӫҵ�ձ��");
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
	// ����������
	strSql.AppendFormat(L"and DetLog.DetType  = '���ó����飨���죩' ");
	// ����ũ��(�綯�����䳵
	strSql.AppendFormat(L"and (HisVehInfo.FuelType not like '%%��%%'  or DetLog.PlateType not like '%%ũ��%%' or DetLog.PlateType not like '%%����%%') ");
	// �ͳ� У���ֿ���
	strSql.AppendFormat(L"and HisVehInfo.VehType not like ('%%����%%') and HisVehInfo.VehType not like ('%%�ҳ�%%') \
						 and HisVehInfo.VehType not like ('%%��ҵ��%%') and HisVehInfo.VehType not like ('%%ǣ����%%') \
						 and HisVehInfo.VehType not like ('%%У��%%') ");
	if (nNumber == 1)
	{
		// С�ڵ���9��
		strSql.AppendFormat(L"and HisVehInfo.RatedPassengerCapacity <= 9 ");
	}
	else if (nNumber == 2)
	{
		// 10-19��
		strSql.AppendFormat(L"and (HisVehInfo.RatedPassengerCapacity >= 10 and  HisVehInfo.RatedPassengerCapacity <= 19) ");
	}
	else
	{
		// 20�˼�����
		strSql.AppendFormat(L"and HisVehInfo.RatedPassengerCapacity >= 20 ");
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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
	//Item.szText.Format(L"Ӫҵ�ձ��");
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
	// ����������
	strSql.AppendFormat(L"and DetLog.DetType  = '���ó����飨���죩' ");
	// ����ũ��(�綯�����䳵
	strSql.AppendFormat(L"and (HisVehInfo.FuelType not like ('%%��%%')  or DetLog.PlateType not like ('%%ũ��%%') or DetLog.PlateType not like ('%%����%%')) ");
	// У��
	strSql.AppendFormat(L"and HisVehInfo.VehType like ('%%У��%%') ");
	if (nNumber == 1)
	{
		// 10-19��
		strSql.AppendFormat(L"and (HisVehInfo.RatedPassengerCapacity >= 10 and  HisVehInfo.RatedPassengerCapacity <= 19) ");
	}
	else
	{
		// 20�˼�����
		strSql.AppendFormat(L"and HisVehInfo.RatedPassengerCapacity >= 20 ");
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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
	// ����������
	strSql.AppendFormat(L"and DetLog.DetType  = '���ó����飨���죩' ");
	// ����ũ��(�綯�����䳵
	strSql.AppendFormat(L"and (HisVehInfo.FuelType not like ('%%��%%')  or DetLog.PlateType not like ('%%ũ��%%') or DetLog.PlateType not like ('%%����%%')) ");
	// ������ǣ����
	strSql.AppendFormat(L"and (HisVehInfo.VehType like ('%%����%%') or HisVehInfo.VehType like ('%%ǣ����%%')) ");
	// �Ƿ�Σ�����䳵
	strSql.AppendFormat(L"and HisVehInfo.UseCharacter ");
	if (!bDANGER)
	{
		strSql.AppendFormat(L"not ");
	}
	strSql.AppendFormat(L"like ('%%Σ%%') ");
	// ��λ //ǣ������������30t�����շ�
	// 1.������4.5t����
	// 2.������4.5-12t
	// 3.������12-30t
	// 4.������30t����
	if (nTonnage == 1)
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass < 4500 and HisVehInfo.VehType not like ('%%ǣ����%%') ");
	}
	else if (nTonnage == 2)
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass > 4500 and HisVehInfo.MaximumTotalMass < 12000 and HisVehInfo.VehType not like ('%%ǣ����%%') ");
	}
	else if (nTonnage == 3)
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass > 12000 and HisVehInfo.MaximumTotalMass < 30000 and HisVehInfo.VehType not like ('%%ǣ����%%') ");
	}
	else 
	{
		strSql.AppendFormat(L"and (HisVehInfo.MaximumTotalMass > 30000 or HisVehInfo.VehType like ('%%ǣ����%%')) ");
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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
	// ����������
	strSql.AppendFormat(L"and DetLog.DetType  = '���ó����飨���죩' ");
	// ����ũ��(�綯�����䳵
	strSql.AppendFormat(L"and (HisVehInfo.FuelType not like ('%%��%%')  or DetLog.PlateType not like ('%%ũ��%%') or DetLog.PlateType not like ('%%����%%')) ");
	// �ҳ�
	strSql.AppendFormat(L"and (HisVehInfo.PlateType like ('%%��%%')) ");
	// �Ƿ�Σ�����䳵
	strSql.AppendFormat(L"and HisVehInfo.UseCharacter ");
	if (!bDANGER)
	{
		strSql.AppendFormat(L"not ");
	}
	strSql.AppendFormat(L"like ('%%Σ%%') ");

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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
	// ����������
	strSql.AppendFormat(L"and DetLog.DetType  = '���ó����飨���죩' ");
	// ����ũ��(�綯�����䳵
	strSql.AppendFormat(L"and (HisVehInfo.FuelType not like ('%%��%%')  or DetLog.PlateType not like ('%%ũ��%%') or DetLog.PlateType not like ('%%����%%')) ");
	// ר����ҵ��
	strSql.AppendFormat(L"and (HisVehInfo.VehType like ('%%ר����ҵ%%')) ");

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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
	// ����������
	strSql.AppendFormat(L"and DetLog.DetType_M  = '�����ȼ�����' ");
	// ������С������ ����С��4.5���ͳ���λС��10
	strSql.AppendFormat(L"and (HisVehInfo.MaximumTotalMass < 4500 and HisVehInfo.RatedPassengerCapacity < 10)" );


	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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
	// ����������
	strSql.AppendFormat(L"and DetLog.DetType_M  = '�����ȼ�����' ");
	// �ͳ�
	strSql.AppendFormat(L"and HisVehInfo.VehType not like ('%%����%%') and HisVehInfo.VehType not like ('%%�ҳ�%%') \
						 and HisVehInfo.VehType not like ('%%��ҵ��%%') and HisVehInfo.VehType not like ('%%ǣ����%%') ");
	if (nNumber == 1)
	{
		// 10-19��
		strSql.AppendFormat(L"and (HisVehInfo.RatedPassengerCapacity >= 10 and  HisVehInfo.RatedPassengerCapacity <= 19) ");
	}
	else
	{
		// 20�˼�����
		strSql.AppendFormat(L"and HisVehInfo.RatedPassengerCapacity >= 20 ");
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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
	//Item.szText.Format(L"Ӫҵ�ձ��");
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
	// ����������
	strSql.AppendFormat(L"and DetLog.DetType_M  = '�����ȼ�����' ");
	// ������ǣ����
	strSql.AppendFormat(L"and (HisVehInfo.VehType like ('%%����%%') or HisVehInfo.VehType like ('%%ǣ����%%')) ");
	// �Ƿ�Σ�����䳵
	strSql.AppendFormat(L"and HisVehInfo.UseCharacter ");
	if (!bDANGER)
	{
		strSql.AppendFormat(L"not ");
	}
	strSql.AppendFormat(L"like ('%%Σ%%') ");
	// ��λ //ǣ������������30t�����շ�
	// 1.������4.5t����
	// 2.������4.5-12t
	// 3.������12-30t
	// 4.������30t����
	if (nTonnage == 1 && bDANGER)
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass < 4500 and HisVehInfo.VehType not like ('%%ǣ����%%') ");
	}
	else if (nTonnage == 2 )
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass > 4500 and HisVehInfo.MaximumTotalMass < 12000 and HisVehInfo.VehType not like ('%%ǣ����%%') ");
	}
	else 
	{
		strSql.AppendFormat(L"and (HisVehInfo.MaximumTotalMass > 12000 or HisVehInfo.VehType like ('%%ǣ����%%')) ");
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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
	// ����������
	strSql.AppendFormat(L"and DetLog.DetType_M  = '�����ȼ�����' and DetLog.DetType  = '���ó����飨���죩' ");
	// ������С������ ����С��4.5���ͳ���λС��10
	strSql.AppendFormat(L"and (HisVehInfo.MaximumTotalMass < 4500 and HisVehInfo.RatedPassengerCapacity < 10)" );


	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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
	// ����������
	strSql.AppendFormat(L"and DetLog.DetType_M  = '�����ȼ�����' and DetLog.DetType  = '���ó����飨���죩' ");
	// �ͳ�
	strSql.AppendFormat(L"and HisVehInfo.VehType not like ('%%����%%') and HisVehInfo.VehType not like ('%%�ҳ�%%') \
						 and HisVehInfo.VehType not like ('%%��ҵ��%%') and HisVehInfo.VehType not like ('%%ǣ����%%') ");
	if (nNumber == 1)
	{
		// 10-19��
		strSql.AppendFormat(L"and (HisVehInfo.RatedPassengerCapacity >= 10 and  HisVehInfo.RatedPassengerCapacity <= 19) ");
	}
	else
	{
		// 20�˼�����
		strSql.AppendFormat(L"and HisVehInfo.RatedPassengerCapacity >= 20 ");
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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
	//Item.szText.Format(L"Ӫҵ�ձ��");
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
	// ����������
	strSql.AppendFormat(L"and DetLog.DetType_M  = '�����ȼ�����' and DetLog.DetType  = '���ó����飨���죩' ");
	// ������ǣ����
	strSql.AppendFormat(L"and (HisVehInfo.VehType like ('%%����%%') or HisVehInfo.VehType like ('%%ǣ����%%')) ");
	// �Ƿ�Σ�����䳵
	strSql.AppendFormat(L"and HisVehInfo.UseCharacter ");
	if (!bDANGER)
	{
		strSql.AppendFormat(L"not ");
	}
	strSql.AppendFormat(L"like ('%%Σ%%') ");
	// ��λ //ǣ������������30t�����շ�
	// 1.������4.5t����
	// 2.������4.5-12t
	// 3.������12-30t
	// 4.������30t����
	if (nTonnage == 1 && bDANGER)
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass < 4500 and HisVehInfo.VehType not like ('%%ǣ����%%') ");
	}
	else if (nTonnage == 2 )
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass > 4500 and HisVehInfo.MaximumTotalMass < 12000 and HisVehInfo.VehType not like ('%%ǣ����%%') ");
	}
	else 
	{
		strSql.AppendFormat(L"and (HisVehInfo.MaximumTotalMass > 12000 or HisVehInfo.VehType like ('%%ǣ����%%')) ");
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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
	// ����������
	strSql.AppendFormat(L"and DetLog.DetType  = 'ע��ǼǼ���' ");
	// �ͳ�
	strSql.AppendFormat(L"and HisVehInfo.VehType not like ('%%����%%') and HisVehInfo.VehType not like ('%%�ҳ�%%') \
						 and HisVehInfo.VehType not like ('%%��ҵ��%%') and HisVehInfo.VehType not like ('%%ǣ����%%') ");

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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
	//Item.szText.Format(L"Ӫҵ�ձ��");
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
	// ����������
	strSql.AppendFormat(L"and DetLog.DetType  = 'ע��ǼǼ���' ");
	// ������ǣ����
	strSql.AppendFormat(L"and (HisVehInfo.VehType like ('%%����%%') or HisVehInfo.VehType like ('%%ǣ����%%')) ");
	// ��λ //ǣ������������30t�����շ�
	// 1.������3.5t����
	// 2.������3.5-4.5t
	// 3.������4.5t-31t����
	if (nTonnage == 1)
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass < 3500 and HisVehInfo.VehType not like ('%%ǣ����%%') ");
	}
	else if (nTonnage == 2)
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass > 3500 and HisVehInfo.MaximumTotalMass < 4500 and HisVehInfo.VehType not like ('%%ǣ����%%') ");
	}
	else
	{
		strSql.AppendFormat(L"and HisVehInfo.MaximumTotalMass > 4500 and HisVehInfo.MaximumTotalMass < 31000 and HisVehInfo.VehType like ('%%ǣ����%%') ");
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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
	// ����������
	strSql.AppendFormat(L"and DetLog.DetType  = 'ע��ǼǼ���' ");
	// ר����ҵ��
	strSql.AppendFormat(L"and (HisVehInfo.VehType like ('%%ר����ҵ%%')) ");

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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
	// ����������
	strSql.AppendFormat(L"and DetLog.DetType_M  = '�����ȼ�����' and DetLog.DetType  = 'ע��ǼǼ���' ");
	// ������ǣ����
	strSql.AppendFormat(L"and (HisVehInfo.VehType like ('%%����%%') or HisVehInfo.VehType like ('%%ǣ����%%')) ");

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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
	// ����������
	strSql.AppendFormat(L"and DetLog.DetType  = '���ó����飨�Ƕ��죩' ");

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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
	// ����������
	strSql.AppendFormat(L"and DetLog.DetType  = '��ʱ���' ");

	// 1.����
	// 2.ת��
	// 3.ת��
	if (nTonnage == 1)
	{
		strSql.AppendFormat(L"and Charge.ChargeItem = '����' ");
	}
	else if (nTonnage == 2)
	{
		strSql.AppendFormat(L"and Charge.ChargeItem = 'ת��' ");
	}
	else
	{
		strSql.AppendFormat(L"and Charge.ChargeItem = 'ת��' ");
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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
	strSql.AppendFormat(L" where Charge.PlateNumber = '����' ");
	strSql.AppendFormat(L" and (Charge.ChargingTime between '%s 00:00:00' and '%s 23:59:59') ", 
		odtBeginTime.Format(L"%Y-%m-%d"),  odtEndTime.Format(L"%Y-%m-%d"));

	// 1.A
	// 2.B
	// 3.Ħ�г�
	// 4.����Ĥ
	// 5.���Ǿ�����
	// 6.�����
	// 7.����
	// 8.Ԥ����
	switch(nTonnage)
	{
	case 1:{strSql.AppendFormat(L" and Charge.ChargeItem = 'A' ");}break;
	case 2:{strSql.AppendFormat(L" and Charge.ChargeItem = 'B' ");}break;
	case 3:{strSql.AppendFormat(L" and Charge.ChargeItem = 'Ħ�г�' ");}break;
	case 4:{strSql.AppendFormat(L" and Charge.ChargeItem = '����Ĥ' ");}break;
	case 5:{strSql.AppendFormat(L" and Charge.ChargeItem = '���Ǿ�����' ");}break;
	case 6:{strSql.AppendFormat(L" and Charge.ChargeItem = '�����' ");}break;
	case 7:{strSql.AppendFormat(L" and Charge.ChargeItem = '����' ");}break;
	case 8:{strSql.AppendFormat(L" and Charge.ChargeItem = 'Ԥ����' ");}break;
	}

	_RecordsetPtr pRecordset(NULL);

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, pRecordset, strSql))
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ѯ���ݿ�ʧ��,������������!", L"��ѯͳ��", MB_OK|MB_ICONWARNING);
	}

	int nTotalAmount(0);
	nTotalAmount = pRecordset->GetRecordCount();

	if (0x00 != CNHSQLServerDBO::CloseQuery(pRecordset))
	{
		// �رղ�ѯʧ��
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