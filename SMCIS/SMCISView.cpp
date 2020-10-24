
// SMCISView.cpp : CSMCISView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "SMCIS.h"
#endif

#include "SMCISDoc.h"
#include "SMCISView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSMCISView

IMPLEMENT_DYNCREATE(CSMCISView, CView)

BEGIN_MESSAGE_MAP(CSMCISView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSMCISView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CSMCISView ����/����

CSMCISView::CSMCISView()
{
	// TODO: �ڴ˴���ӹ������

}

CSMCISView::~CSMCISView()
{
}

BOOL CSMCISView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CSMCISView ����

void CSMCISView::OnDraw(CDC* /*pDC*/)
{
	CSMCISDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CSMCISView ��ӡ


void CSMCISView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSMCISView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSMCISView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSMCISView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CSMCISView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSMCISView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSMCISView ���

#ifdef _DEBUG
void CSMCISView::AssertValid() const
{
	CView::AssertValid();
}

void CSMCISView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSMCISDoc* CSMCISView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSMCISDoc)));
	return (CSMCISDoc*)m_pDocument;
}
#endif //_DEBUG


// CSMCISView ��Ϣ�������
