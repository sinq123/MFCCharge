// ScriptHeaderCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ScriptHeaderCtrl.h"

// CScriptHeaderCtrl

IMPLEMENT_DYNAMIC(CScriptHeaderCtrl, CHeaderCtrl)

CScriptHeaderCtrl::CScriptHeaderCtrl()
{

}

CScriptHeaderCtrl::~CScriptHeaderCtrl()
{
}


BEGIN_MESSAGE_MAP(CScriptHeaderCtrl, CHeaderCtrl)
END_MESSAGE_MAP()



// CScriptHeaderCtrl ��Ϣ�������



void CScriptHeaderCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	HTHEME	hTheme = NULL;
	hTheme = m_Theme.OpenThemeData(GetSafeHwnd(), L"HEADER");
	if (hTheme)
	{
		// ������
		int iStateId = 0;
		iStateId = HIS_NORMAL;	
		if(lpDrawItemStruct->itemState == ODS_SELECTED)
			iStateId = HIS_PRESSED;
		else if(lpDrawItemStruct->itemState == ODS_HOTLIGHT)
			iStateId = HIS_HOT;
		m_Theme.DrawThemeBackground(hTheme, m_hWnd, lpDrawItemStruct->hDC, HP_HEADERITEM, iStateId, &lpDrawItemStruct->rcItem, NULL);

		m_Theme.CloseThemeData(hTheme);
	} 	

	// �������
	HDITEM hdi;
	TCHAR  lpBuffer[256];
	int justif=0;
	hdi.mask = HDI_TEXT | HDI_FORMAT;
	hdi.pszText = lpBuffer;
	hdi.cchTextMax = 256;
	GetItem(lpDrawItemStruct->itemID, &hdi);		
	switch (hdi.fmt)
	{
	case HDF_CENTER:
		justif = DT_CENTER;
		break;
	case HDF_LEFT:
		justif = DT_LEFT;
		break;
	case HDF_RIGHT:
		justif = DT_RIGHT;
		break;
	}
	ScriptTextOut(lpDrawItemStruct->hDC,lpBuffer,&CRect(lpDrawItemStruct->rcItem),justif);
}

void CScriptHeaderCtrl::ScriptTextOut(HDC hDC, CString data , CRect* drawRect, int justification)
{
	CDC *pDC = CDC::FromHandle(hDC);
	
	CSize sz,szScr,szScr2;
	CRect outRect(0,0,0,0);
	CFont* pFont = pDC->GetCurrentFont();// ȡ�õ�ǰ����
	CFont* oldFont;


	LOGFONT lf;
	pFont->GetLogFont(&lf);// ȡ������ṹ


	////////// �������±�����
	lf.lfHeight=lf.lfHeight*3/4;
	CFont ScrFont;
	ScrFont.CreateFontIndirect(&lf);
	

	////////////��λ�������
	int nCountScr=0;
	int nCount = data.GetLength(); 
	for(int i=0;i<nCount;i++)// �ҵ��������
	{
		if(data[i]==L'^'||data[i]==L'_')
		{
			nCountScr++;
			if(i+1!=nCount)
				if(data[i]==data[i+1])// ת���
					i++;// ����
		}
	}
	
	oldFont = pDC->SelectObject(&ScrFont);// ѡ�����±�����
	szScr = pDC->GetTextExtent(L"^",1);// ȡ�õ�����Ƿ�����������С
	pDC->SelectObject(oldFont);// �ָ�����

	szScr2 = pDC->GetTextExtent(L"^",1);// ȡ�õ�����Ƿ��ű�׼��������С

	sz = pDC->GetTextExtent(data);// ȡ���ַ�����Ĭ����������С	
	sz.cx = sz.cx - szScr2.cx*nCountScr*2 + szScr.cx*nCountScr;// ������������ַ�������������С
	
	int x=0,y=0;

	if(justification & DT_CENTER)
		x = drawRect->left + drawRect->Width()/2-sz.cx/2;	
	else if(justification & DT_RIGHT) 
		x = drawRect->right-sz.cx;
	else 
		x = drawRect->left+2;

	if(justification & DT_VCENTER)
	{
		y=drawRect->Height()/2 - sz.cy/2;
	}

	//////////// ����ַ���	
	int nPos=0;
	CString temp;
	bool bFind=true;	
	int sy=y;// y�����
	while(bFind)
	{
		nPos = data.FindOneOf(L"^_");
		if (nPos==-1) // �Ҳ���
		{
			bFind=false;
			temp = data;
			pDC->TextOut(x,sy,temp);
		}
		else
		{
			// ������ǰ���ַ�
			if(nPos>0)
			{
				temp = data.Left(nPos);
				data.Delete(0,nPos);// ɾ���ַ�	
				pDC->TextOut(x,sy,temp);
				sz = pDC->GetTextExtent(temp);
				x+=sz.cx;
			}

			if(data[0]==L'_')
				y = sy+(sz.cy - szScr.cy);
			else
				y = sy;
			data.Delete(0);// ɾ������ַ�

			// �����Ǻ���ַ�
			if(data.GetLength()>0)
			{
				temp = data.Left(1);
				data.Delete(0);// ɾ���ַ�
				oldFont = pDC->SelectObject(&ScrFont);// ѡ�����±�����
				pDC->TextOut(x,y,temp);// ȡ�õ�����Ƿ�����������С
				pDC->SelectObject(oldFont);// �ָ�����
				x+=szScr.cx;				
			}
		}
	}
}
