// NumericEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NumericEdit.h"


// CNumericEdit

IMPLEMENT_DYNAMIC(CNumericEdit, CEdit)

CNumericEdit::CNumericEdit()
{
	// Ĭ��Ϊ��������
	m_bAllowNegative = FALSE;
	// Ĭ��Ϊ����2λС��
	m_nMaxDecimalPlaces = 2;
}

CNumericEdit::~CNumericEdit()
{
}


BEGIN_MESSAGE_MAP(CNumericEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CNumericEdit ��Ϣ�������


void CNumericEdit::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���

	// ȥ��ֻ�������ֵ�����
	ModifyStyle(ES_NUMBER, 0);

	CEdit::PreSubclassWindow();
}

// �����Ƿ�������
void CNumericEdit::AllowNegative(BOOL bAllowNegative)
{
	m_bAllowNegative = bAllowNegative;
}

// ��ȡ�Ƿ�������
BOOL CNumericEdit::IsNegativeAllowed() const
{
	return m_bAllowNegative;
}

// ��������С��λ��
void CNumericEdit::SetMaxDecimalPlaces(int nMaxDecimalPlaces)
{
	m_nMaxDecimalPlaces = nMaxDecimalPlaces;
}

// ��ȡ����С��λ��
int CNumericEdit::GetMaxDecimalPlaces() const
{
	return m_nMaxDecimalPlaces;
}

void CNumericEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	// ����ɾ����
	if (nChar == VK_BACK)
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	    return;
	}
	// End ����ɾ����

	// �����ܴ�ӡ�ַ�����(�����ַ�)
	// ���� Backspace,Ctrl+C,Ctrl+V,Ctrl+X,Ctrl+Z
	// ��Ҫ��Լ���,����,ճ��
	if (!_istprint(nChar))
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		Adjustment();  // ����
		return;
	}
	// End �����ܴ�ӡ�ַ�����(�����ַ�)


	// ����ȫ������������������,С����,����

	CString strText;
	GetWindowText(strText);  // ��ȡ�ؼ�����
	int nLen = strText.GetLength();
	int nStartChar, nEndChar;
	GetSel(nStartChar, nEndChar);
	int nNumericDecimalPos = strText.Find(_T('.'));  // Ѱ��С����

	// С���㴦��
	if (nChar == (UINT)_T('.'))
	{
		bool bDelimSelected = false;

		// ���ȫ�����ݱ�ѡ��,����"0."�滻(����û���ı��������)
		if ((nStartChar==0) && (nEndChar==strText.GetLength()))
		{
			ReplaceSel(_T("0."));
			return;
		}
		// һ�������ݱ�ѡ��
		else if (nStartChar < nEndChar) 
		{ 
			// ��ѡ������Ѱ��С����
			for (int i=nStartChar; i<nEndChar; i++)
			{
				if (strText[i] == _T('.'))
				{
					// ����ӵ�һλ��ʼѡ��,���ߴӵ�2λ��ʼѡ��,�����Ը��ſ�ͷ
					if (nStartChar==0 || (nStartChar==1 && strText[0]==_T('-')))
					{
						ReplaceSel(_T("0."));
						return;
					}
					bDelimSelected = true;
					break;
				}
			}
		}

		// ���С�����Ѿ�����,����û�б�ѡ�У���������
		if (nNumericDecimalPos!=-1 && bDelimSelected==false)
		{
			SetSel(nNumericDecimalPos+1, nNumericDecimalPos+1, FALSE);
			return;
		}
		// ����С������С��λ������
		else if (m_nMaxDecimalPlaces>0 && strText.Mid(nEndChar).GetLength()>m_nMaxDecimalPlaces)
		{
			// ��ʼλ��
			if (nStartChar == 0)
			{
				CString str = _T("0.") + strText.Mid(nEndChar, m_nMaxDecimalPlaces);
				SetSel(nStartChar, nLen);
				ReplaceSel(str);
				SetSel(nStartChar+2, nStartChar+2);
			}
			// ���ǿ�ʼλ��
			else
			{
				CString str = _T(".") + strText.Mid(nEndChar, m_nMaxDecimalPlaces);
				SetSel(nStartChar, nLen);
				ReplaceSel(str);
				SetSel(nStartChar+1, nStartChar+1);
			}
			return;
		}
	}

	// ���Ŵ���
	if (nChar == (UINT)_T('-'))
	{
		if (!m_bAllowNegative || nStartChar!=0 || strText.Find(_T("-"))>=0)
		{
			return;
		}
	}

	// С��λ������
	if (m_nMaxDecimalPlaces>0 &&
		nNumericDecimalPos!=-1 &&
		nChar>=(UINT)_T('0') &&
		nChar<=(UINT)_T('9') &&
		nStartChar>nNumericDecimalPos &&
		nEndChar==nStartChar &&
		strText.Mid(nNumericDecimalPos + 1).GetLength()>=m_nMaxDecimalPlaces)
	{
		// ����ԭ����С��
		if (nStartChar <= (nNumericDecimalPos+m_nMaxDecimalPlaces))
		{
			SetSel(nStartChar, nStartChar+1);
			TCHAR tch[2];
			tch[0] = static_cast<TCHAR>(nChar);
			tch[1] = _T('\0');
			ReplaceSel(tch);
		}
		return;
	}

	// ����ָ���ַ�
	if ((nChar>=(UINT)_T('0') && nChar<=(UINT)_T('9')) || (nChar==(UINT)_T('.')) || (nChar==(UINT)_T('-')))
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
}

  // ������������,����,ճ��ʱ
void CNumericEdit::Adjustment()
{
	// ��ȡ���ı�
	CString strOldText;
	GetWindowText(strOldText);
	CString strNewText;
	bool bIsNegative = false;

	// ɾ������Ҫ���ַ�
	//int iPos;
	int nDecimalPos = -1;
	int nNewLen = 0;
	int nLen = strOldText.GetLength();
	for (int iPos=0; iPos<nLen; iPos++)
	{
		TCHAR tc = strOldText[iPos];

		// ��鸺��
		if (m_bAllowNegative && tc==_T('-'))
			bIsNegative = true;

		// �������
		else if (_istdigit(tc))
		{
			//// Make sure it doesn't go beyond the limits
			//if (nDecimalPos < 0 && nNewLen == m_nMaxWholeDigits)
			//	continue;

			if (nDecimalPos>=0 && nNewLen>(nDecimalPos+m_nMaxDecimalPlaces))
				break;

			strNewText += tc;
			nNewLen++;
		}
		
		// ���С����
		else if (tc==_T('.') && nDecimalPos<0)
		{
			if (m_nMaxDecimalPlaces == 0)
				break;

			strNewText += tc;
			nDecimalPos = nNewLen;
			nNewLen++;
		}
	}

	// ����Ǹ���,���ϸ���
	if (bIsNegative)
	{
		strNewText.Insert(0, _T("-"));
		nNewLen++;
	}

	// �����ı��������о��ı�,���ѹ��ŵ��ı����
	SetWindowText(strNewText);
	SetSel(nNewLen, nNewLen, FALSE);
	//SetSel(0, -1, FALSE);
	//ReplaceSel(strNewText);
}