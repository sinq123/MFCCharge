// Author:      SFr frydaysoft@gmx.de

#include "stdafx.h"
#include "ColorListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning (push)
#pragma warning (disable:311)
/////////////////////////////////////////////////////////////////////////////
// CColorListCtrl

CColorListCtrl::CColorListCtrl(int colSize)
{
	////////////////我加入的变量 判断上一次单击的列数///////////////////////
	m_ClickCol=0;
	////////////////////////////////////////
    m_columnSize=colSize;       // number of columns
    m_fullColumnLines=TRUE;     // paint vert. lines | | |
    m_withSingleRect=FALSE;     // paint single rect for all sub-items
#ifdef _DEBUG
    m_BigFocusRect=TRUE;        // focus-rect with small/big dots
#endif
#ifndef _DEBUG
    m_BigFocusRect=FALSE;       // focus-rect with small/big dots
#endif
    IsCreated=FALSE;
	ISInit=FALSE;
	m_bNeedRedraw = FALSE;
}

//***************************************************************
CColorListCtrl::~CColorListCtrl()
{
}

//***************************************************************
BEGIN_MESSAGE_MAP(CColorListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CColorListCtrl)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
//	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnLvnColumnclick)
//ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnLvnColumnclick)
ON_WM_HSCROLL()
ON_WM_VSCROLL()
ON_WM_LBUTTONUP()
ON_WM_NCLBUTTONUP()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f黵 Nachrichten CColorListCtrl 

BOOL CColorListCtrl::SetColSize(int colSize)
{
    m_columnSize=colSize;       // number of columns
	return TRUE;
}

void CColorListCtrl::OnDestroy() 
{
	DeleteAllItems();	
	CListCtrl::OnDestroy();
}

//***************************************************************
void CColorListCtrl::SetColumnType(BOOL bNew)
{
    m_fullColumnLines=bNew;     // paint no/vert. lines | | |
    if (IsCreated) 
    {
        RedrawWindow();
    }
}
void CColorListCtrl::SetRectType(BOOL bNew)
{
    m_withSingleRect=bNew;     // paint no/single rect for all sub-items
    if (IsCreated)
    {
        RedrawWindow();
    }
}
void CColorListCtrl::SetFocusType(BOOL bNew)
{
    m_BigFocusRect=bNew;       // focus-rect with small/big dots
    if (IsCreated)
    {
        RedrawWindow();
    }
}

//***************************************************************
CMyLParam*	CColorListCtrl::GetMyLParam(int Index)
{
    LVITEM	Item;
	Item.mask		= LVIF_PARAM;
	Item.iItem		= Index;
	Item.iSubItem	= 0;
	CListCtrl::GetItem(&Item);
	return (CMyLParam*)Item.lParam;
}

//***************************************************************
CRect CColorListCtrl::GetFullCellRect(int nItem, BOOL outside)
{
	static CRect rectCell;
    CListCtrl::GetItemRect(nItem, rectCell, LVIR_BOUNDS);
    if (!outside)
    {   //decrease 1 pixel
        rectCell.left++;    rectCell.right--;
        rectCell.top++;     rectCell.bottom--;
    }
	return rectCell;
}

//***************************************************************
CRect CColorListCtrl::GetCellRect(int nItem, int nColumn, BOOL outside)
{
	static CRect rectCell;

	// Get the height
    CListCtrl::GetItemRect(nItem, rectCell, LVIR_BOUNDS);
    LV_COLUMN column;
	column.mask = LVCF_WIDTH;        // Set the mask to only return the width

    for (int x=0; x<nColumn; x++)
    {
        column.iSubItem=1;
        CListCtrl::GetColumn(x, &column); // Get rect-edge (left/top)
        rectCell.left+=column.cx;
    }
    column.iSubItem=1;
    CListCtrl::GetColumn(nColumn, &column); // Get rect-edge (right/bottom)
    rectCell.right = rectCell.left + column.cx;

    if (!outside)
    {   //decrease 1 pixel
        rectCell.left++;    rectCell.right--;
        rectCell.top++;     rectCell.bottom--;
    }
	return rectCell;
}

//***************************************************************
void CColorListCtrl::InvalidateFullItem(int nItem, BOOL bErase)
{
    CRect rcBounds=GetFullCellRect(nItem, TRUE);
	InvalidateRect(rcBounds, bErase);

}

//***************************************************************
// create ListCtrl-head
int CColorListCtrl::InitCtrl(CStringArray *phead, CByteArray *pProcent)
{
    if ( (!phead)||(!pProcent)) return 1;
	LV_COLUMN lvc;
	int cx=0;
    int count = (int)phead->GetSize(); 
    if (count!=m_columnSize) return 2;
    if (pProcent->GetSize() != count) return 3;
    for (int x=0; x<count; x++) cx+=pProcent->GetAt(x);
    if (cx!=100) return 4;

	HeadText=phead;
	ColsWide=pProcent;

	CRect rect_listbox;

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	GetWindowRect( rect_listbox );
	cx=int((rect_listbox.right-rect_listbox.left)-20); //some Pixel for Scrollbar

    //set head-columns in ListBox
	lvc.iSubItem = 0;
	lvc.fmt = LVCFMT_LEFT ;		
	
    for (int x=0; x<count; x++)
    {
        lvc.cx = int(cx*pProcent->GetAt(x)/100);
	    lvc.pszText = (TCHAR*)LPCTSTR(phead->GetAt(x));
	    CListCtrl::InsertColumn(x,&lvc);
    }
	ISInit=TRUE;
    return 0;
}

int CColorListCtrl::InsertColumn(int nCol, LPCTSTR lpszColumnHeading,	int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem)
{
	CListCtrl::InsertColumn(nCol,lpszColumnHeading,nFormat,nWidth,nSubItem);
	m_columnSize++;
	return 0;
}

int CColorListCtrl::InsertItem(int nItem, LPCTSTR lpszItem)
{
	CStringArray Head;
	Head.RemoveAll();
	Head.Add(lpszItem);
	for(int i=1;i<m_columnSize;i++)
		Head.Add(L"");
	AddItem(&Head,nItem);
	return nItem;
}

int CColorListCtrl::GetColumnCount()
{
	return m_columnSize;
}

/*
BOOL CColorListCtrl::DeleteColumn(int nCol)			//Delete by Raylee 2009-9-27
{
	if(nCol<0)
		return FALSE;
	CListCtrl::DeleteColumn(nCol);
	if(m_columnSize>0)
		m_columnSize--;
	return TRUE;
}
*/
BOOL CColorListCtrl::DeleteColumn(int nCol)			//Add by Raylee 2009-9-27
{
	if(nCol<0)
		return FALSE;
	if(m_columnSize>0)
		m_columnSize--;
	return 	CListCtrl::DeleteColumn(nCol);
}

//***************************************************************
// add an item
int CColorListCtrl::AddItem(CStringArray *line, int pos)
{
    int ret_index=LISTCTRL_ERROR;
    if (!line) return ret_index;

	LV_ITEM lvi;
    
	//set List-properties
	lvi.mask = LVIF_TEXT ; 
	lvi.iSubItem = 0;
    lvi.pszText = L"";

    int count=GetItemCount();
    int columns=(int)line->GetSize();

    if (m_columnSize!=columns) return ret_index;

    if (DWORD(pos)<=DWORD(count)) count=pos;
	
    lvi.iItem = count;
    //lvi.lParam= count;
	lvi.mask = LVIF_TEXT ; 
	lvi.iSubItem = 0;   //refer to no Item
    // insert an new line
	ret_index=CListCtrl::InsertItem(&lvi);
    // set item text for additional columns		
    for (int x=0; x<columns; x++)
    {
        CListCtrl::SetItemText(count,x,(TCHAR*)LPCTSTR(line->GetAt(x)) );
    }
	lvi.mask = LVIF_STATE;
	lvi.iSubItem = 1;
	lvi.stateMask = 0xFFFFFFFF ; 
	lvi.state = 0;

	if (CListCtrl::SetItem(&lvi)) 
    {
        CMyLParam *p=new CMyLParam(m_columnSize); //init with: DEF_BACKGROUND, def_text

        #ifdef TESTCOLOR
/*            // only for TEST
            if (ret_index<3)
            {
                p->SetBackColor(ITEM_COLOR(ret_index+BLUE),0);
                p->SetTextColor(ITEM_COLOR(ret_index+RED ),0);
            }
            else
            if (ret_index<=6)
            {
                p->SetBackColor(ITEM_COLOR(ret_index+BLUE),1);
                p->SetTextColor(ITEM_COLOR(ret_index+RED ),1);
            }
            else
            {
                p->SetBackColor(ITEM_COLOR((ret_index+BLUE)&0xF),2);
                p->SetTextColor(ITEM_COLOR((ret_index+RED )&0xF),2);
            }
            // end: only for TEST*/
        #endif

        CListCtrl::SetItemData( ret_index, DWORD(p) );
        return ret_index;
    }
    return LISTCTRL_ERROR;
}

//***************************************************************
BOOL CColorListCtrl::DeleteAllItems()
{
	while (CListCtrl::GetItemCount())
        CColorListCtrl::DeleteItem(0);

    return TRUE;
}

//***************************************************************
BOOL CColorListCtrl::DeleteItem(int nItem )
{
    if (CListCtrl::GetItemCount()<=nItem) return FALSE;
    CMyLParam *p=(CMyLParam*)CListCtrl::GetItemData(nItem);
    if (p)
    {
        CListCtrl::SetItemData( nItem, p->GetData() );
        delete p;
        return CListCtrl::DeleteItem( nItem );
    }
    return TRUE;
}


//***************************************************************
DWORD CColorListCtrl::GetItemData( int nItem ) const
{
    CMyLParam *p=(CMyLParam*)CListCtrl::GetItemData(nItem);
    if (p)
    {
        return p->GetData();
        return TRUE;
    }
    return 0;
}

//***************************************************************
BOOL  CColorListCtrl::SetItemData( int nItem, DWORD dwData )
{
    CMyLParam *p=(CMyLParam*)CListCtrl::GetItemData(nItem);
    if (p)
    {
        p->SetData(dwData);
        return TRUE;
    }
    return FALSE;
}

//***************************************************************
BOOL CColorListCtrl::SetItemBackgndColor(COLORREF color, int Index, int iSub)	
{
    CMyLParam *p=GetMyLParam(Index);
    if (!p) return FALSE;
    if ( p->SetBackColor(color, iSub) )
    {
        RedrawItems( Index, Index );
        return TRUE;
    }
    return FALSE;
}
	
BOOL CColorListCtrl::SetItemBKColor(COLORREF color, int Index)
{
	for(int i=0;i<m_columnSize;i++)
		SetItemBackgndColor(color,Index,i);
	return TRUE;
}

//***************************************************************
BOOL CColorListCtrl::SetItemTextColor(COLORREF color, int Index, int iSub)	
{
    CMyLParam *p=GetMyLParam(Index);
    if (!p) return FALSE;
    if ( p->SetTextColor(color, iSub) )
    {
        RedrawItems( Index, Index );
        return TRUE;
    }
    return FALSE;
}

//***************************************************************
COLORREF CColorListCtrl::GetItemBackgndColor(int Index, int iSub)
{
    CMyLParam *p=GetMyLParam(Index);
    if (!p) return 0;
    return p->GetBackColor(iSub);
}

//***************************************************************
COLORREF CColorListCtrl::GetItemTextColor(int Index, int iSub)
{
    CMyLParam *p=GetMyLParam(Index);
    if (!p) return 0;
    return p->GetTextColor(iSub);
}

//***************************************************************
void CColorListCtrl::OnPaint() 
{
	// First let the control do its default drawing.
	const MSG *msg = GetCurrentMessage();
	DefWindowProc( msg->message, msg->wParam, msg->lParam );

    if (!m_fullColumnLines) return;

	// Draw the lines only for LVS_REPORT mode
	if( (GetStyle() & LVS_TYPEMASK) == LVS_REPORT )
	{
		// Get the number of columns
		CClientDC dc(this );
		CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
		int nColumnCount = pHeader->GetItemCount();

		// The bottom of the header corresponds to the top of the line 
		RECT rect;
		pHeader->GetClientRect( &rect );
		int top = rect.bottom;

		// Now get the client rect so we know the line length and
		// when to stop
		GetClientRect( &rect );

		// The border of the column is offset by the horz scroll
		int borderx = 0 - GetScrollPos( SB_HORZ );

        CPen       *pOldPen;
        CPen        pen;
        CGdiObject *pOldBrush;
        pen.CreatePen( PS_DOT, 0, ::GetSysColor(COLOR_HIGHLIGHTTEXT) );
        pOldPen  =dc.SelectObject(&pen);
        pOldBrush=dc.SelectStockObject(NULL_BRUSH);

		for( int i = 0; i < nColumnCount; i++ )
		{
			// Get the next border
			borderx += GetColumnWidth( i );

			// if next border is outside client area, break out
			if( borderx >= rect.right ) break;

			// Draw the line.
			dc.MoveTo( borderx-1, top);
			dc.LineTo( borderx-1, rect.bottom );
		}
        dc.SelectObject(pOldPen);
        dc.SelectObject(pOldBrush);

	}
	// Do not call CListCtrl::OnPaint() for painting messages
}

//***************************************************************
void CColorListCtrl::RepaintSelectedItems()
{
	// Invalidate focused item so it can repaint 
	int nItem = GetNextItem(-1, LVNI_FOCUSED);

	if(nItem != -1)
	{
        InvalidateFullItem(nItem, FALSE);
	}

	// Invalidate selected items depending on LVS_SHOWSELALWAYS
	if((GetStyle() & LVS_SHOWSELALWAYS))
	{
		for(nItem = GetNextItem(-1, LVNI_SELECTED);
			nItem != -1; nItem = GetNextItem(nItem, LVNI_SELECTED))
		{
            InvalidateFullItem(nItem, FALSE);
		}
	}
	UpdateWindow();
}

//***************************************************************
BOOL CColorListCtrl::SetSel(int pos, BOOL bSelect)
{
    // LVS_ES_FULLROWSELECT only works with newer version of Comctl32
    // This style and some of the other new extended styles 
    // only work with version 4.72 (or higer) of COMCTL32.DLL 

    UINT nState=0;
    if (bSelect) nState=LVIS_SELECTED|LVS_EX_FULLROWSELECT; else nState=0;
    if (SetItemState(pos, nState, LVIS_SELECTED|LVS_EX_FULLROWSELECT))
    {
        if((GetStyle() & LVS_SHOWSELALWAYS))
        {
            InvalidateFullItem(pos, TRUE);
        }
        return TRUE;
    }
    return FALSE;
}
//***************************************************************
void CColorListCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	SendMessage(WM_PAINT);
    CListCtrl::OnKillFocus(pNewWnd);
	// check if we are losing focus
	if(pNewWnd != NULL && pNewWnd->GetParent() == this)
		return;

	// repaint items that should change appearance
	if((GetStyle() & LVS_TYPEMASK) == LVS_REPORT)
		RepaintSelectedItems();
}

//***************************************************************
void CColorListCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	CListCtrl::OnSetFocus(pOldWnd);
	
	// check if we are getting focus
	if(pOldWnd!=NULL && pOldWnd->GetParent()==this)
		return;

	// repaint items that should change appearance
	if((GetStyle() & LVS_TYPEMASK)==LVS_REPORT)
		RepaintSelectedItems();
}

//***************************************************************
void CColorListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    if (!lpDrawItemStruct) return;
    IsCreated=TRUE;
	CDC*		pDC			= CDC::FromHandle(lpDrawItemStruct->hDC);
	CMyLParam*	pMyLParam	= GetMyLParam(lpDrawItemStruct->itemID);
	CRect		rcItem;

    if (!pMyLParam) return;
    int x=0;
    typedef enum {R_NOTHINGS=0, R_FOCUS, R_SELECT, R_NORMAL, R_SEL_NOFOCUS} redrawmode;
    redrawmode redraw=R_NORMAL;

	// Get item image and state info
	LV_ITEM lvi;
	lvi.mask = LVIF_IMAGE | LVIF_STATE;
	lvi.iItem = lpDrawItemStruct->itemID;
	lvi.iSubItem = 0;
	lvi.stateMask = 0xFFFF;		// get all state flags
	GetItem(&lvi);

	BOOL bHighlight =   (   (lvi.state & LVIS_DROPHILITED)
                            ||
				            (
                                (lvi.state & LVIS_SELECTED) 
                                && 
                                (  ( GetFocus() == this )  || ( GetStyle() & LVS_SHOWSELALWAYS ) )
					        )
				        );

    BOOL bLostFocus=(GetFocus()!=this);


    if ( (lpDrawItemStruct->itemAction&ODA_FOCUS)==ODA_FOCUS)
    {   //the control gains or loses input focus
        if (bLostFocus) redraw=R_SEL_NOFOCUS;
        else
        if ((lvi.state&LVIS_FOCUSED)==LVIS_FOCUSED) redraw=R_FOCUS;
        else 
        {
            if (bHighlight) redraw=R_SELECT;
            else redraw=R_NORMAL;
        }
    }
    else
    if ((lpDrawItemStruct->itemAction&ODA_SELECT)==ODA_SELECT)
    {   //the selection status has changed
            if (bHighlight)
            {
                if (bLostFocus) redraw=R_SEL_NOFOCUS;
                 else redraw=R_SELECT;
            }
            else redraw=R_NORMAL;
    }
    else
    {   //redraw the item
        if (bLostFocus)
        {
            if (bHighlight) redraw=R_SEL_NOFOCUS;
             else
              redraw=R_NORMAL;
        }
        else 
        {
            if ((lvi.state&LVIS_FOCUSED)==LVIS_FOCUSED) redraw=R_FOCUS;
            else 
            {
                if (bHighlight) redraw=R_SELECT;
                 else redraw=R_NORMAL;
            }
        }
    }

    CPen       *pOldPen;
    CPen        pen;
    CGdiObject *pOldBrush;

    switch(redraw)
    {

        case R_FOCUS:
            rcItem=GetFullCellRect(lpDrawItemStruct->itemID, TRUE);
            pDC->FillSolidRect(rcItem, ::GetSysColor(COLOR_ACTIVECAPTION));
            pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
            if (m_BigFocusRect)
            {
                pen.CreatePen( PS_DOT, 0, ::GetSysColor(COLOR_HIGHLIGHTTEXT) );
                pOldPen  =pDC->SelectObject(&pen);
                pOldBrush=pDC->SelectStockObject(NULL_BRUSH);
                pDC->Rectangle(rcItem);
                pDC->SelectObject(pOldPen);
                pDC->SelectObject(pOldBrush);
            }
            else pDC->DrawFocusRect(rcItem);
            for (x=0; x<m_columnSize; x++)
            {
                rcItem	= GetCellRect(lpDrawItemStruct->itemID, x, FALSE);
                pDC->DrawText(CListCtrl::GetItemText(lpDrawItemStruct->itemID,x), rcItem, DT_SINGLELINE | DT_LEFT | DT_VCENTER );
            }
            break;
        case R_SELECT:
            rcItem=GetFullCellRect(lpDrawItemStruct->itemID, TRUE);
            pDC->FillSolidRect(rcItem, ::GetSysColor(COLOR_ACTIVECAPTION));
            pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
            for (x=0; x<m_columnSize; x++)
            {
                rcItem	= GetCellRect(lpDrawItemStruct->itemID, x, FALSE);
                pDC->DrawText(CListCtrl::GetItemText(lpDrawItemStruct->itemID,x), rcItem, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
            }
            break;
        case R_SEL_NOFOCUS:
            rcItem=GetFullCellRect(lpDrawItemStruct->itemID, TRUE);
            pDC->FillSolidRect(rcItem, ::GetSysColor(COLOR_INACTIVECAPTION));
            pDC->SetTextColor(pMyLParam->GetTextColor(5));
            pen.CreatePen( PS_DOT, 0, ::GetSysColor(COLOR_INACTIVECAPTION) );
            pOldPen  =pDC->SelectObject(&pen);
            pOldBrush=pDC->SelectStockObject(NULL_BRUSH);
            if (!m_withSingleRect)
                pDC->Rectangle(rcItem);
            for (x=0; x<m_columnSize; x++)
            {
                rcItem	= GetCellRect(lpDrawItemStruct->itemID, x, FALSE);
                pDC->DrawText(CListCtrl::GetItemText(lpDrawItemStruct->itemID,x), rcItem, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
            }
            pDC->SelectObject(pOldPen);
            pDC->SelectObject(pOldBrush);
            break;
        case R_NORMAL:
            for (x=0; x<m_columnSize; x++)
            {
	            rcItem	= GetCellRect(lpDrawItemStruct->itemID, x, TRUE);
                pDC->FillSolidRect(rcItem, pMyLParam->GetBackColor(x));
                pDC->SetTextColor(pMyLParam->GetTextColor(x));
                if (m_withSingleRect)
                {
                    pOldBrush=pDC->SelectStockObject(NULL_BRUSH);
                    pDC->Rectangle(rcItem);
                    pDC->SelectObject(pOldBrush);
                    
                }
                rcItem	= GetCellRect(lpDrawItemStruct->itemID, x, FALSE);
                pDC->DrawText(CListCtrl::GetItemText(lpDrawItemStruct->itemID,x), rcItem, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
            }
            break;
    }

    return;
}

void CColorListCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CListCtrl::OnSize(nType, cx, cy);
    if (IsCreated) 
    {
        RedrawWindow();
    }
	//if(ISInit)
	//{
	//	int cx=0;
	//	int count = HeadText->GetSize(); 
	//	int colwide;

	//	CRect rect_listbox;

	//	GetWindowRect( rect_listbox );
	//	cx=int((rect_listbox.right-rect_listbox.left)-20); //some Pixel for Scrollbar

	//	for (int x=0; x<count; x++)
	//	{
	//		colwide = int(cx*ColsWide->GetAt(x)/100);
	//		CListCtrl::SetColumnWidth(x,colwide);
	//	}
	//}
}



void CColorListCtrl::OnListSort(int clk_col)         //排序
{
	int row=0;
	row=GetItemCount();
	int RowStart,RowEnd;
	RowStart=row;
	if(row>1)
	{

		//降序
		if(m_ClickCol!=clk_col)
        {
			for(int i=RowStart;i<2*RowStart;i++)
			{
				CStringArray Head;
				CString str;
				str.Format(L"%d",i);
				Head.Add(str);
				Head.Add(L"1");
				Head.Add(L"1");
				AddItem(&Head);
				Head.RemoveAll();
				//DeleteAllItems();
			}
            RowEnd=GetItemCount();
			//PopSort(0, row-1, clk_col);
			QuickSort(0,row-1, clk_col,RowStart,RowEnd);
			for(int i=RowEnd;i>RowStart;i--)
			{

				DeleteItem(i-1);
			}


		}
		else if(m_ClickCol==clk_col)
		{
			if(row%2==0)
			{
				
				for(int i=0;i<row/2;i++)
				{
					 ExChangeRow(row-i-1,i);		
				}

			}
			else
			{
				for(int i=0;i<(row-1)/2;i++)
				{
					ExChangeRow(row-i-1,i);		

				}

			}
		}
	}

	m_ClickCol=clk_col;


}

void CColorListCtrl::ExChangeRow(int Row1, int Row2)
{
	int col=GetHeaderCtrl()->GetItemCount();
	CString m_Values[30];
	for(int j=0;j<col;j++)
	{
		m_Values[j]=GetItemText(Row1,j);

		SetItemText(Row1,j,GetItemText(Row2,j));
		SetItemText(Row2,j,m_Values[j]);
	}
}

void CColorListCtrl::CopyRow(int RowSource, int RowAim)
{
    int col=GetHeaderCtrl()->GetItemCount();
	CString m_Values[30];
	for(int j=0;j<col;j++)
	{
		SetItemText(RowAim,j,GetItemText(RowSource,j));
	}
}



void CColorListCtrl::PopSort(int NumStart, int NumEnd, int clk_col)
{
	int stop=0;
	int col=GetHeaderCtrl()->GetItemCount();

	do
	{
		int i=NumEnd;
		stop=0;
		for(i;i>NumStart;i--)
		{
			if(GetItemText(i,clk_col).Compare(GetItemText(i-1,clk_col))>0)
			{
				stop=1;
				ExChangeRow(i-1,i);						
			}
            ///////////////////////////////////////
			//else if(GetItemText(i,clk_col).Compare(GetItemText(i-1,clk_col))==0)
			//{
			//	
			//	if(col>1 && clk_col!=0)
			//	{
			//		if(GetItemText(i,0).Compare(GetItemText(i-1,0))>0)
			//		{
			//			stop=1;
			//			ExChangeRow(i-1,i);		
			//		}
			//	}
			//	else if(col>1 && clk_col==0)
			//	{
			//		if(GetItemText(i,1).Compare(GetItemText(i-1,1))>0)
			//		{
			//			stop=1;
			//			ExChangeRow(i-1,i);		
			//		}
			//	}
			//}
			////////////////////////////////////////
		}
	}while(stop==1);
}

void CColorListCtrl::QuickSort(int NumStart, int NumEnd, int clk_col,int RowStart, int RowEnd)
{
	int NumCompare;
	/////////////////////////////////////
	int Rows[1000],NumOfRows;
	NumOfRows=0;
    //////////////////////////////////////////
	int LeftSide,RightSide;
    LeftSide=0;RightSide=0;
	if(NumEnd-NumStart<=15)
	{
		PopSort(NumStart,NumEnd,clk_col);
	}
	else 
	{
		NumCompare=NumStart+(NumEnd-NumStart)/2;            //数据分界点
		////////////////////////////////////////////////////////////////
        for(int i=NumStart;i<NumCompare;i++)                                          
		{
            if(GetItemText(i,clk_col) > GetItemText(NumCompare,clk_col))
			{
				CopyRow(i,RowStart+NumStart+LeftSide);
                LeftSide++;
			}
			else if(GetItemText(i,clk_col) < GetItemText(NumCompare,clk_col))

			{
				//CopyRow(i,RowEnd-RightSide-1);
				CopyRow(i,(RowEnd-1)-(RowStart-NumEnd-1)-RightSide);

				RightSide++;
			}
			else
			{
				Rows[NumOfRows]=i;
                NumOfRows++;
			}
		}
        /////////////////////////////////////////////////////////		
		for(int i=NumCompare+1;i<=NumEnd;i++)
		{
            if(GetItemText(i,clk_col) > GetItemText(NumCompare,clk_col))
			{
				CopyRow(i,RowStart+NumStart+LeftSide);
                LeftSide++;
			}
			else if(GetItemText(i,clk_col) < GetItemText(NumCompare,clk_col))
			{
				CopyRow(i,(RowEnd-1)-(RowStart-NumEnd-1)-RightSide);
				//CopyRow(i,RowEnd-RightSide-1);
				RightSide++;
			}
			else
			{
				Rows[NumOfRows]=i;
                NumOfRows++;
			}
		}
        ///////////////////////////////////////////////////////////////
		CopyRow(NumCompare,(RowStart+NumStart)+LeftSide);
		if(NumOfRows!=0)
		{
			for(int i=0;i<NumOfRows;i++)
			{
				CopyRow(Rows[i],(RowStart+NumStart+LeftSide+1)+i);

			}
		}
		////////////////////////////////////////////////////////////////
		for(int i=0;i<LeftSide;i++)
		{
			CopyRow(RowStart+NumStart+i,NumStart+i);

		}
        
		CopyRow(RowStart+NumStart+LeftSide,LeftSide+NumStart);
        for(int i=0;i<NumOfRows;i++)
			{
				CopyRow((RowStart+NumStart+LeftSide+1)+i,NumStart+LeftSide+1+i);

			}
        
        for(int i=0;i<RightSide;i++)
		{
			//CopyRow(RowEnd-i-1,NumEnd-i);
		    CopyRow((RowEnd-1)-(RowStart-NumEnd-1)-i,NumEnd-i);
		}
		////////////////////////////////////////////////
		QuickSort(NumStart,NumStart+LeftSide-1,clk_col,RowStart, RowEnd);
        QuickSort(NumEnd-RightSide+1,NumEnd,clk_col,RowStart, RowEnd);
		if(NumOfRows!=0)
		{
            QuickSort(LeftSide+NumStart, NumStart+LeftSide+NumOfRows, 0, RowStart, RowEnd);

		}


	}
}


void CColorListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_bNeedRedraw=TRUE;

	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
	//TRACE(L"OnHScroll nSBCode=%d\n", nSBCode);
	if (nSBCode != SB_THUMBTRACK)
	{
		this->Invalidate();	//Add by Raylee 2009-9-27
	}
}

void CColorListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_bNeedRedraw=TRUE;

	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
	//TRACE(L"OnVScroll nSBCode=%d\n", nSBCode);
	if (nSBCode != SB_THUMBTRACK)
	{
		this->Invalidate();	//Add by Raylee 2009-9-27
	}
}

void CColorListCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(m_bNeedRedraw)
	{
		RedrawWindow();
		m_bNeedRedraw = FALSE;
	}
	CListCtrl::OnLButtonUp(nFlags, point);
}

void CColorListCtrl::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	if(m_bNeedRedraw)
	{
		RedrawWindow();
		m_bNeedRedraw = FALSE;
	}

	CListCtrl::OnNcLButtonUp(nHitTest, point);
}

void CColorListCtrl::PreSubclassWindow()
{
	CHeaderCtrl* pHeader = GetHeaderCtrl();

	if(pHeader==NULL)
		return ;

	VERIFY(m_hdr.SubclassWindow(pHeader->m_hWnd));

	CListCtrl::PreSubclassWindow();
}

//  上下标头
void CColorListCtrl::ScriptHeader(void)
{
	HDITEM hdItem;
	hdItem.mask = HDI_FORMAT;
	int nCount = m_hdr.GetItemCount();
	for(int i=0; i < nCount; i++)
	{
		m_hdr.GetItem(i,&hdItem);
		hdItem.fmt|= HDF_OWNERDRAW;
		m_hdr.SetItem(i,&hdItem);
	}
}

#pragma warning (pop)