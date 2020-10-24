// ChargeLogMgntView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SMCIS.h"
#include "ChargeLogMgntView.h"

#define DLG_CAPTION L"�շ���־��ѯ"

// CChargeLogMgntView

IMPLEMENT_DYNCREATE(CChargeLogMgntView, CFormView)

CChargeLogMgntView::CChargeLogMgntView()
	: CFormView(CChargeLogMgntView::IDD)
	, m_pRecordset(NULL)
	, m_nPageSize(11)
	, m_nTotalNum(0)
	, m_nTotalPage(0)
	, m_nCurrentPage(0)
{
	// ���1280*1024�ֱ��ʽ��п���
	int nSM_CYSCREEN = GetSystemMetrics(SM_CYSCREEN);
	// ���ݷֱ���Y������е���
	//m_nDlgFontSize = nSM_CYSCREEN * 25 / 1024;
	m_nDlgFontSize = 23;
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

CChargeLogMgntView::~CChargeLogMgntView()
{
	m_fontDlgFont.DeleteObject();

	// �رղ�ѯ
	if (m_pRecordset != NULL)
	{
		if (0x00 != CNHSQLServerDBO::CloseQuery(m_pRecordset))
		{
			// �رղ�ѯʧ��
		}
		m_pRecordset = NULL;
	}
}

void CChargeLogMgntView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_SYSTEM_LOG, m_lstSystemLog);
	DDX_Control(pDX, IDC_ST_TOTAL_NUM, m_stTotalNum);
	DDX_Control(pDX, IDC_ST_TOTAL_PAGE, m_stTotalPage);
	DDX_Control(pDX, IDC_ST_CURRENT_PAGE, m_stCurrentPage);
	DDX_Control(pDX, IDC_DTP_COND_BEGIN_TIME, m_dtBeginTime);
	DDX_Control(pDX, IDC_DTP_COND_END_TIME, m_dtEndTime);
	DDX_Control(pDX, IDC_BTN_QUERY, m_btnQuery);
	DDX_Control(pDX, IDC_BTN_PREVIOUS_PAGE, m_btnPrevious);
	DDX_Control(pDX, IDC_BTN_NEXT_PAGE, m_btnNext);
}

BEGIN_MESSAGE_MAP(CChargeLogMgntView, CFormView)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_QUERY, &CChargeLogMgntView::OnBnClickedBtnQuery)
	ON_BN_CLICKED(IDC_BTN_PREVIOUS_PAGE, &CChargeLogMgntView::OnBnClickedBtnPreviousPage)
	ON_BN_CLICKED(IDC_BTN_NEXT_PAGE, &CChargeLogMgntView::OnBnClickedBtnNextPage)
END_MESSAGE_MAP()


// CChargeLogMgntView ���

#ifdef _DEBUG
void CChargeLogMgntView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CChargeLogMgntView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CChargeLogMgntView ��Ϣ�������


void CChargeLogMgntView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if(nType==1) return;//��С����ʲô������  

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


void CChargeLogMgntView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CFormView::OnTimer(nIDEvent);
}


void CChargeLogMgntView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	// ��ʼ���ؼ�
	InitCtrls();

	QuerySystemLogData();
}

void CChargeLogMgntView::InitCtrls(void)
{
	GetDocument()->SetTitle(DLG_CAPTION);

	SetDlgFont();

	// ��ʼ��ϵͳ��־�б�
	InitSystemLogList();

	m_btnQuery.SetIcon(IDI_ICON_MAGNIFIER);
	m_btnQuery.SetFlat(FALSE);
	m_btnPrevious.SetWindowText(L"");
	m_btnPrevious.SetIcon(IDI_ICON_PREVIOUS);
	m_btnPrevious.SetTooltipText(L"��һҳ");
	m_btnNext.SetWindowText(L"");
	m_btnNext.SetIcon(IDI_ICON_NEXT);
	m_btnNext.SetTooltipText(L"��һҳ");
}

void CChargeLogMgntView::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);
		pWnd = pWnd->GetNextWindow();
	}
}

void CChargeLogMgntView::InitSystemLogList(void)
{
	m_lstSystemLog.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_lstSystemLog.InsertColumn(0, L"���", LVCFMT_CENTER, 50, 0);
	m_lstSystemLog.InsertColumn(1, L"ʱ��", LVCFMT_CENTER, 170, 1);
	m_lstSystemLog.InsertColumn(2, L"����", LVCFMT_CENTER, 880, 2);

	m_ilRowHeight.Create(1, theApp.m_nListRowHeight, ILC_COLOR, 1, 1);
	m_lstSystemLog.SetImageList(&m_ilRowHeight, LVSIL_SMALL);
	m_lstSystemLog.SetFont(&theApp.m_fontListCtrl);
}

void CChargeLogMgntView::AutoFitColumnWidth(CListCtrl &list)
{
	CHeaderCtrl* pHeaderCtrl = list.GetHeaderCtrl();
	ASSERT(pHeaderCtrl);
	if (pHeaderCtrl)
	{
		for (int iCurrCol = 0; iCurrCol < pHeaderCtrl->GetItemCount(); iCurrCol++)
		{
			list.SetColumnWidth(iCurrCol, LVSCW_AUTOSIZE);
			int nCurrWidth = list.GetColumnWidth(iCurrCol);
			list.SetColumnWidth(iCurrCol, LVSCW_AUTOSIZE_USEHEADER);
			int nColHdrWidth = list.GetColumnWidth(iCurrCol);
			list.SetColumnWidth(iCurrCol, max(nCurrWidth, nColHdrWidth));
		}
	}
}

DWORD CChargeLogMgntView::QuerySystemLogData(void)
{
	// ���ð�ť
	GetDlgItem(IDC_BTN_PREVIOUS_PAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_NEXT_PAGE)->EnableWindow(FALSE);

	// ����ϴ���Ϣ
	m_stTotalNum.SetWindowTextW(L"0");
	m_stTotalPage.SetWindowTextW(L"0");
	m_stCurrentPage.SetWindowTextW(L"0");

	// ����б�
	m_lstSystemLog.DeleteAllItems();

	// ����SQL���
	CString strSQL = GenerateQuerySQL();

	// �رղ�ѯ
	if (m_pRecordset != NULL)
	{
		if (0x00 != CNHSQLServerDBO::CloseQuery(m_pRecordset))
		{
			// �رղ�ѯʧ��
			MessageBox(L"�ر�[�ϴβ�ѯ]ʧ�ܡ�", DLG_CAPTION);
			return 0xFF;
		}
		m_pRecordset = NULL;
	}

	if (0x00 != CNHSQLServerDBO::OpenQuery(theApp.m_pConnection, m_pRecordset, strSQL))
	{
		// �򿪲�ѯʧ��

		MessageBox(L"��ȡ[�����־]ʧ�ܡ�", DLG_CAPTION);
		return 0xFF;
	}

	if (m_pRecordset->adoEOF)
	{
		if (0x00 != CNHSQLServerDBO::CloseQuery(m_pRecordset))
		{
			// �رղ�ѯʧ��
		}
		m_pRecordset = NULL;

		return 0x00;
	}

	m_pRecordset->PageSize = m_nPageSize;//����ҳ���С
	m_nTotalNum = m_pRecordset->RecordCount;//������
	m_nTotalPage = m_pRecordset->PageCount;//��ҳ��

	if (m_nTotalPage > 1)
	{
		GetDlgItem(IDC_BTN_NEXT_PAGE)->EnableWindow(TRUE);
	}
	m_nCurrentPage = 1;
	m_pRecordset->AbsolutePage = PositionEnum_Param(m_nCurrentPage);	//��ǰҳ

	// ��ʾ������Ϣ
	CString str;
	str.Format(L"%d", m_nTotalNum);
	m_stTotalNum.SetWindowTextW(str);
	str.Format(L"%d", m_nTotalPage);
	m_stTotalPage.SetWindowTextW(str);
	str.Format(L"%d", m_nCurrentPage);
	m_stCurrentPage.SetWindowTextW(str);

	// ��ʾ�����־
	SystemLogDataToList();

	return 0x01;
}

CString CChargeLogMgntView::GenerateQuerySQL(void)
{
	CString strSQL(L"");

	//��ȡ��ѯ����

	//��ʼʱ��
	COleDateTime odtBeginTime;
	m_dtBeginTime.GetTime(odtBeginTime);
	CString strBeginTime;
	strBeginTime = odtBeginTime.Format(L"%Y-%m-%d 00:00:00");

	//����ʱ��
	COleDateTime odtEndTime;
	m_dtEndTime.GetTime(odtEndTime);
	CString strEndTime;
	strEndTime = odtEndTime.Format(L"%Y-%m-%d 23:59:59");

	//����SQL���
	strSQL.Format(L"select * from Charge_log_record where Times >= '%s' and Times <= '%s'", 
		strBeginTime,
		strEndTime);

	return strSQL;
}

void CChargeLogMgntView::SystemLogDataToList(void)
{
	m_lstSystemLog.SetRedraw(FALSE);
	m_lstSystemLog.DeleteAllItems();

	try
	{
		CString str;
		COleDateTime odt;
		_variant_t v;
		wchar_t wchBuf[1024] = {L'\0'};

		for (int i = 1; i <= m_nPageSize; i++ )
		{
			int nSubItem(0);
			if (!m_pRecordset->adoEOF)
			{	
				// ���
				str.Format(L"%d", i);
				const int nIndex = m_lstSystemLog.InsertItem((i-1), str);
				str.Format(L"%d",(m_nCurrentPage-1)*m_nPageSize + i);
				m_lstSystemLog.SetItem (nIndex, nSubItem, LVIF_TEXT, str, 0, 0, 0, 0);
				nSubItem++;

				// ʱ��
				// Time
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(m_pRecordset, v, L"Times");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					DATE dt = static_cast<DATE>(v);
					SYSTEMTIME st;
					VariantTimeToSystemTime(dt, &st);
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%04hu-%02hu-%02hu %02hu:%02hu:%02hu", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}

				if (odt.ParseDateTime(wchBuf))
				{
					str = odt.Format(L"%Y-%m-%d %H:%M:%S");
				}
				else
				{
					str = L"";
				}
				m_lstSystemLog.SetItem (nIndex, nSubItem, LVIF_TEXT, str, 0, 0, 0, 0);
				nSubItem++;

				// ����
				// Description
				v.ChangeType(VT_NULL);
				ZeroMemory(wchBuf, sizeof(wchBuf));
				CNHSQLServerDBO::GetFieldValue(m_pRecordset, v, L"Description");
				if (VT_NULL!=v.vt && VT_EMPTY!=v.vt)
				{
					_snwprintf_s(wchBuf, _countof(wchBuf), _TRUNCATE, L"%s", (wchar_t*)(_bstr_t)v);
				}
				else
				{
					wcsncpy_s(wchBuf, _countof(wchBuf), L"", _TRUNCATE);
				}
				m_lstSystemLog.SetItem (nIndex, nSubItem, LVIF_TEXT, wchBuf, 0, 0, 0, 0);

				m_pRecordset->MoveNext();
			}
		}
	}
	catch (_com_error& e)
	{
		CNHSQLServerDBO::OutputDBErrMsg(e);

		// �쳣����б�
		m_lstSystemLog.DeleteAllItems();
	}


	m_lstSystemLog.SetRedraw(TRUE);
}

bool CChargeLogMgntView::VerifyQueryCond(void)
{
	COleDateTime odtCondBeginTime,odtCondEndTime;

	m_dtBeginTime.GetTime(odtCondBeginTime);
	m_dtEndTime.GetTime(odtCondEndTime);

	if (odtCondBeginTime > odtCondEndTime)
	{
		MessageBox(L"[��ʼ����]���ܴ���[��������]��", DLG_CAPTION);
		return false;
	}
	else
	{
		return true;
	}
}

void CChargeLogMgntView::OnBnClickedBtnQuery()
{
	if (VerifyQueryCond())
	{
		// ��ѯϵͳ��־����
		if (0x00 == QuerySystemLogData())
		{
			MessageBox(L"û�з��������ļ�¼��", DLG_CAPTION);
		}
	}

}

void CChargeLogMgntView::OnBnClickedBtnPreviousPage()
{
	m_nCurrentPage--;

	CString str;
	str.Format(L"%d", m_nCurrentPage);
	m_stCurrentPage.SetWindowTextW(str);

	GetDlgItem(IDC_BTN_NEXT_PAGE)->EnableWindow(TRUE);
	if (m_nCurrentPage > 1)
	{
		GetDlgItem(IDC_BTN_PREVIOUS_PAGE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_PREVIOUS_PAGE)->EnableWindow(FALSE);
	}

	m_pRecordset->AbsolutePage = PositionEnum_Param(m_nCurrentPage);	//��ǰҳ
	SystemLogDataToList();//��ʾ��ǰҳ����
}

void CChargeLogMgntView::OnBnClickedBtnNextPage()
{
	m_nCurrentPage++;

	CString str;
	str.Format(L"%d", m_nCurrentPage);
	m_stCurrentPage.SetWindowTextW(str);

	GetDlgItem(IDC_BTN_PREVIOUS_PAGE)->EnableWindow(TRUE);
	if (m_nCurrentPage < m_nTotalPage)
	{
		GetDlgItem(IDC_BTN_NEXT_PAGE)->EnableWindow(TRUE);	
	}
	else
	{
		GetDlgItem(IDC_BTN_NEXT_PAGE)->EnableWindow(FALSE);	
	}

	m_pRecordset->AbsolutePage = PositionEnum_Param(m_nCurrentPage);	//��ǰҳ
	SystemLogDataToList();//��ʾ��ǰҳ����
}