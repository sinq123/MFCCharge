// SMDVehInfoEntryDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SMCIS.h"
#include "DetCountStatDoc2.h"


// CDetCountStatDoc2

IMPLEMENT_DYNCREATE(CDetCountStatDoc2, CDocument)

CDetCountStatDoc2::CDetCountStatDoc2()
{
}

BOOL CDetCountStatDoc2::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CDetCountStatDoc2::~CDetCountStatDoc2()
{
}


BEGIN_MESSAGE_MAP(CDetCountStatDoc2, CDocument)
END_MESSAGE_MAP()


// CDetCountStatDoc2 ���

#ifdef _DEBUG
void CDetCountStatDoc2::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CDetCountStatDoc2::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CDetCountStatDoc2 ���л�

void CDetCountStatDoc2::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}
#endif


// CDetCountStatDoc2 ����
