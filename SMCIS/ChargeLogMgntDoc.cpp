// SystemLogMgntDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SMCIS.h"
#include "ChargeLogMgntDoc.h"


// CChagerLogMgntDoc

IMPLEMENT_DYNCREATE(CChagerLogMgntDoc, CDocument)

CChagerLogMgntDoc::CChagerLogMgntDoc()
{
}

BOOL CChagerLogMgntDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CChagerLogMgntDoc::~CChagerLogMgntDoc()
{
}


BEGIN_MESSAGE_MAP(CChagerLogMgntDoc, CDocument)
END_MESSAGE_MAP()


// CChagerLogMgntDoc ���

#ifdef _DEBUG
void CChagerLogMgntDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CChagerLogMgntDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CChagerLogMgntDoc ���л�

void CChagerLogMgntDoc::Serialize(CArchive& ar)
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


// CChagerLogMgntDoc ����
