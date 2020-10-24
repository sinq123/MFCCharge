// ChargeDetTypeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SMCIS.h"
#include "ChargeDetTypeDlg.h"
#include "afxdialogex.h"


// ChargeDetTypeDlg �Ի���

IMPLEMENT_DYNAMIC(ChargeDetTypeDlg, CDialogEx)

ChargeDetTypeDlg::ChargeDetTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChargeDetTypeDlg::IDD, pParent)
{
	m_nDlgFontSize = 16;
	m_fontDlgFont.CreateFont(m_nDlgFontSize,
		0, 
		0, 
		0, 
		FW_BOLD,
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

ChargeDetTypeDlg::~ChargeDetTypeDlg()
{
	m_fontDlgFont.DeleteObject();
}

void ChargeDetTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ED_TYPR_OF_CHARGE, m_edTypeOfCharge);
	DDX_Control(pDX, IDC_ED_AMOUNT_OF_CHARGE, m_edAmountOfCharge);

	DDX_Control(pDX, IDC_LS_DATA_INFO, m_lsDataInfo);
	DDX_Control(pDX, IDC_BTN_DATA_UPDATE, m_btnDataUpdate);
	DDX_Control(pDX, IDC_BTN_DATA_ADD, m_btnDataAdd);
	DDX_Control(pDX, IDC_BTN_DATA_MOD, m_btnDataMod);
	DDX_Control(pDX, IDC_BTN_DATA_DEL, m_btnDataDel);
}


BEGIN_MESSAGE_MAP(ChargeDetTypeDlg, CDialogEx)
ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_DATA_ADD, &ChargeDetTypeDlg::OnBnClickedBtnDataAdd)
	ON_BN_CLICKED(IDC_BTN_DATA_MOD, &ChargeDetTypeDlg::OnBnClickedBtnDataMod)
	ON_BN_CLICKED(IDC_BTN_DATA_DEL, &ChargeDetTypeDlg::OnBnClickedBtnDataDel)
	ON_BN_CLICKED(IDC_BTN_DATA_UPDATE, &ChargeDetTypeDlg::OnBnClickedBtnDataUpdate)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LS_DATA_INFO, &ChargeDetTypeDlg::OnLvnItemchangedLsDataInfo)
END_MESSAGE_MAP()


// ChargeDetTypeDlg ��Ϣ�������



BOOL ChargeDetTypeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDataInfoLst();
	InitCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void ChargeDetTypeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnTimer(nIDEvent);


}



void ChargeDetTypeDlg::OnBnClickedBtnDataAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ȡ�ؼ�ֵ
	CString strAmountOfCharge, strTypeOfCharge;
	if(!GetCtrlValue(strAmountOfCharge, strTypeOfCharge))
	{
		return ;
	}

	// �����Ƿ�����ͬ�Ĵ���ֵ
	CString strSQL;
	int nCount(0);
	strSQL.Format(L"select COUNT(*) AS CountNum from Charge_DetType where  TypeOfCharge = '%s' ", 
		strTypeOfCharge);
	CNHSQLServerDBO::ExecuteCount(theApp.m_pConnection,strSQL,&nCount);
	if(nCount>0)
	{
		MessageBox(L"�Ѵ���["+ strTypeOfCharge +L"]�ļ�����ͣ������ظ����", L"�������ά��");
		return;
	}

	SCharge_DetType sCharge_DetType;

	sCharge_DetType.strName = strTypeOfCharge.GetString();
	sCharge_DetType.strCode = strAmountOfCharge.GetString();

	if (CCharge_DetTypeService::SetCharge_DetType(theApp.m_pConnection, sCharge_DetType)  == 0x01)
	{
		MessageBox(L"����["+ strTypeOfCharge +L"]�ļ�����ͳɹ�", L"�������ά��");
	}
	else
	{
		MessageBox(L"����["+ strTypeOfCharge +L"]�ļ������ʧ��", L"�������ά��");
	}
	// ˢ���б�
	UpdateDataInfoLst();
}


void ChargeDetTypeDlg::OnBnClickedBtnDataMod()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const int nIndex = m_lsDataInfo.GetSelectionMark();

	if (nIndex == -1)
	{
		return;
	}

	// ��ȡ�ؼ�ֵ
	CString strAmountOfCharge, strTypeOfCharge;
	if(!GetCtrlValue(strAmountOfCharge, strTypeOfCharge))
	{
		return ;
	}

	CString strSQL;
	int nCount(0);
	strSQL.Format(L"select COUNT(*) AS CountNum from Charge_DetType where TypeOfCharge = '%s'", 
		strTypeOfCharge);
	CNHSQLServerDBO::ExecuteCount(theApp.m_pConnection,strSQL,&nCount);
	if(nCount <= 0)
	{
		MessageBox(L"�����ڸ�["+ strTypeOfCharge +L"]�ļ�����ͣ��밴���Ӱ�ť���������޸�", L"�������ά��");
		return;
	}

	// ��ɾ��������
	strSQL.Empty();
	strSQL.Format(L"delete Charge_DetType  where TypeOfCharge = '%s'", 
		strTypeOfCharge);
	nCount = 0;

	if (0x01 != CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSQL, &nCount))
	{
		SCharge_DetType sCharge_DetType;

		sCharge_DetType.strName = strTypeOfCharge.GetString();
		sCharge_DetType.strCode = strAmountOfCharge.GetString();

		if (CCharge_DetTypeService::SetCharge_DetType(theApp.m_pConnection, sCharge_DetType)  == 0x01)
		{
			MessageBox(L"�޸�["+ strTypeOfCharge +L"]�ļ�����ͳɹ�", L"�������ά��");
		}
		else
		{
			MessageBox(L"�޸�["+ strTypeOfCharge +L"]�ļ������ʧ��", L"�������ά��");
		}
	}
	else
	{
		MessageBox(L"�޸�["+ strTypeOfCharge +L"]�ļ������ʧ��", L"�������ά��");
	}
	// ˢ���б�
	UpdateDataInfoLst();
}


void ChargeDetTypeDlg::OnBnClickedBtnDataDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const int nIndex = m_lsDataInfo.GetSelectionMark();

	if (nIndex != -1)
	{
		CString strDetType, strDetTypeCode, strAmountOfCharge, strTypeOfCharge;
		strTypeOfCharge = m_lsDataInfo.GetItemText(nIndex, 1);
		strAmountOfCharge = m_lsDataInfo.GetItemText(nIndex, 2);

		if(IDNO==MessageBox(L"�Ƿ�ɾ��["+ strTypeOfCharge +"]�ļ�¼��", L"�������ά��", MB_YESNO))
		{
			return;
		}
		//���ݴ���ɾ����Ӧ��¼
		CString strSQL;
		strSQL.Format(L"delete Charge_DetType  where Name = '%s'", 
		strTypeOfCharge);
		int nCount(0);

		//����ɾ��������ķ���
		if (0x01 == CNHSQLServerDBO::ExecuteDML(theApp.m_pConnection, strSQL, &nCount))
		{
			MessageBox(L"ɾ��[" + strTypeOfCharge+ L"]��¼ʧ��", L"�������ά��");
			return;
		}
		MessageBox(L"ɾ��[" + strTypeOfCharge+ L"]��¼�ɹ�", L"�������ά��");
	}
	else
	{
		MessageBox(L"��ѡ����Ӧ��¼", L"�������ά��");
	}
	// ˢ���б�
	UpdateDataInfoLst();
}


void ChargeDetTypeDlg::OnBnClickedBtnDataUpdate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ˢ���б�
	UpdateDataInfoLst();
}

void ChargeDetTypeDlg::OnLvnItemchangedLsDataInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const int nIndex = m_lsDataInfo.GetSelectionMark();

	if(-1!=nIndex)
	{
		CString strTemp(L"");
		strTemp = m_lsDataInfo.GetItemText(nIndex, 1);
		m_edTypeOfCharge.SetWindowTextW(strTemp);
		strTemp = m_lsDataInfo.GetItemText(nIndex, 2);
		m_edAmountOfCharge.SetWindowTextW(strTemp);
	}
	else
	{
		m_edTypeOfCharge.SetWindowTextW(L"");
		m_edAmountOfCharge.SetWindowTextW(L"");
	}

	*pResult = 0;
}


void ChargeDetTypeDlg::InitDataInfoLst()
{
	int nColumn(0);
	m_lsDataInfo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_lsDataInfo.InsertColumn(nColumn++, L"���", LVCFMT_LEFT, 80);
	m_lsDataInfo.InsertColumn(nColumn++, L"�������", LVCFMT_LEFT, 300);
	m_lsDataInfo.InsertColumn(nColumn++, L"������ʹ���", LVCFMT_LEFT, 180);
	m_lsDataInfo.SetImageList(&theApp.m_ilRowHeight, LVSIL_SMALL);
	m_lsDataInfo.SetFont(&theApp.m_fontListCtrl);
}

void ChargeDetTypeDlg::InitCtrl()
{
	SetDlgFont();

	SetWindowText(L"�������ά��");

	UpdateDataInfoLst();

	m_btnDataUpdate.SetFlat(FALSE);

	m_btnDataAdd.SetFlat(FALSE);

	m_btnDataMod.SetFlat(FALSE);

	m_btnDataDel.SetFlat(FALSE);
}

void ChargeDetTypeDlg::SetDlgFont(void)
{
	CWnd *pWnd = GetTopWindow();
	while (NULL != pWnd)
	{
		pWnd->SetFont(&m_fontDlgFont);

		TCHAR tchs[20] = {0};
		GetClassName(pWnd->GetSafeHwnd(), tchs, 20);
		if (_tcscmp(tchs, _T("ComboBox")) == 0)
		{
			((CComboBox *)pWnd)->SetItemHeight(-1, 25);
		}

		pWnd = pWnd->GetNextWindow();
	}
}

void ChargeDetTypeDlg::ClearCtrls(void)
{
	m_edAmountOfCharge.SetWindowTextW(L"");
	m_edTypeOfCharge.SetWindowTextW(L"");

}

bool ChargeDetTypeDlg::GetCtrlValue(CString& strAmountOfCharge, CString& strTypeOfCharge)
{
	m_edAmountOfCharge.GetWindowTextW(strAmountOfCharge);
	if(strAmountOfCharge.IsEmpty())
	{
		MessageBox(L"�����������ʹ���", L"�������ά��");
		return false;
	}

	m_edTypeOfCharge.GetWindowTextW(strTypeOfCharge);
	if(strTypeOfCharge.IsEmpty())
	{
		MessageBox(L"������������", L"�������ά��");
		return false;
	}


	return true;
}

void ChargeDetTypeDlg::UpdateDataInfoLst()
{
	// ˢ��ǰ����տؼ�
	ClearCtrls();

	CString strSql;

	// ����
	//strSql.Format(L" select * from Charge_DetType order by AutoID desc ");
	// ����
	strSql.Format(L" select * from Charge_DetType order by AutoID asc ");

	std::list<SCharge_DetType> lsCharge_DetType;
	if (CCharge_DetTypeService::GetCharge_DetType(theApp.m_pConnection, strSql.GetString(), lsCharge_DetType) != 0xFFFFFFFF)
	{
		m_lsDataInfo.DeleteAllItems();
		m_lsDataInfo.SetRedraw(FALSE);
		int nItem(0);

		std::list<SCharge_DetType>::const_iterator iter = lsCharge_DetType.begin();
		for ( ; iter != lsCharge_DetType.end(); iter++)
		{
			CString str;
			int nSubItem(0);
			// ���
			str.Format(L"%02d", nItem+1);
			const int nIndex = m_lsDataInfo.InsertItem(nItem++, str);
			nSubItem++;
			// �������
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strName.c_str());
			// ������ʹ���
			m_lsDataInfo.SetItemText(nIndex, nSubItem++, iter->strCode.c_str());
		}

		m_lsDataInfo.SetRedraw(TRUE);
		m_lsDataInfo.Invalidate();
	}
	else
	{
		// �򿪲�ѯʧ��
		MessageBox(L"��ȡ[�������ά��]�б�ʧ�ܡ�", L"�������ά��");
	}
}