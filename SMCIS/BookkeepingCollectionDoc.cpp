// SMDVehInfoEntryDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SMCIS.h"
#include "BookkeepingCollectionDoc.h"


// CBookkeepingCollectionDoc

IMPLEMENT_DYNCREATE(CBookkeepingCollectionDoc, CDocument)

CBookkeepingCollectionDoc::CBookkeepingCollectionDoc()
{
}

BOOL CBookkeepingCollectionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CBookkeepingCollectionDoc::~CBookkeepingCollectionDoc()
{
}


BEGIN_MESSAGE_MAP(CBookkeepingCollectionDoc, CDocument)
END_MESSAGE_MAP()


// CBookkeepingCollectionDoc ���

#ifdef _DEBUG
void CBookkeepingCollectionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CBookkeepingCollectionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CBookkeepingCollectionDoc ���л�

void CBookkeepingCollectionDoc::Serialize(CArchive& ar)
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


// CBookkeepingCollectionDoc ����
