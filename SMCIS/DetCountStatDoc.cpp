// SMDVehInfoEntryDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SMCIS.h"
#include "DetCountStatDoc.h"


// CDetCountStatDoc

IMPLEMENT_DYNCREATE(CDetCountStatDoc, CDocument)

CDetCountStatDoc::CDetCountStatDoc()
{
}

BOOL CDetCountStatDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CDetCountStatDoc::~CDetCountStatDoc()
{
}


BEGIN_MESSAGE_MAP(CDetCountStatDoc, CDocument)
END_MESSAGE_MAP()


// CDetCountStatDoc ���

#ifdef _DEBUG
void CDetCountStatDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CDetCountStatDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CDetCountStatDoc ���л�

void CDetCountStatDoc::Serialize(CArchive& ar)
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


// CDetCountStatDoc ����
