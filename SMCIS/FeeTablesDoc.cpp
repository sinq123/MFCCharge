// SMDVehInfoEntryDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SMCIS.h"
#include "FeeTablesDoc.h"


// CFeeTablesDoc

IMPLEMENT_DYNCREATE(CFeeTablesDoc, CDocument)

CFeeTablesDoc::CFeeTablesDoc()
{
}

BOOL CFeeTablesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CFeeTablesDoc::~CFeeTablesDoc()
{
}


BEGIN_MESSAGE_MAP(CFeeTablesDoc, CDocument)
END_MESSAGE_MAP()


// CFeeTablesDoc ���

#ifdef _DEBUG
void CFeeTablesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CFeeTablesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CFeeTablesDoc ���л�

void CFeeTablesDoc::Serialize(CArchive& ar)
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


// CFeeTablesDoc ����
