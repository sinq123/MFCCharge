// NumericEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "NumericEdit.h"


// CNumericEdit

IMPLEMENT_DYNAMIC(CNumericEdit, CEdit)

CNumericEdit::CNumericEdit()
{
	// 默认为不允许负数
	m_bAllowNegative = FALSE;
	// 默认为允许2位小数
	m_nMaxDecimalPlaces = 2;
}

CNumericEdit::~CNumericEdit()
{
}


BEGIN_MESSAGE_MAP(CNumericEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CNumericEdit 消息处理程序


void CNumericEdit::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类

	// 去掉只输入数字的属性
	ModifyStyle(ES_NUMBER, 0);

	CEdit::PreSubclassWindow();
}

// 设置是否允许负数
void CNumericEdit::AllowNegative(BOOL bAllowNegative)
{
	m_bAllowNegative = bAllowNegative;
}

// 获取是否允许负数
BOOL CNumericEdit::IsNegativeAllowed() const
{
	return m_bAllowNegative;
}

// 设置允许小数位数
void CNumericEdit::SetMaxDecimalPlaces(int nMaxDecimalPlaces)
{
	m_nMaxDecimalPlaces = nMaxDecimalPlaces;
}

// 获取允许小数位数
int CNumericEdit::GetMaxDecimalPlaces() const
{
	return m_nMaxDecimalPlaces;
}

void CNumericEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// 处理删除键
	if (nChar == VK_BACK)
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	    return;
	}
	// End 处理删除键

	// 处理不能打印字符输入(命令字符)
	// 例如 Backspace,Ctrl+C,Ctrl+V,Ctrl+X,Ctrl+Z
	// 主要针对剪贴,复制,粘贴
	if (!_istprint(nChar))
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		Adjustment();  // 调整
		return;
	}
	// End 处理不能打印字符输入(命令字符)


	// 以下全部处理键盘输入的数字,小数点,负号

	CString strText;
	GetWindowText(strText);  // 获取控件文字
	int nLen = strText.GetLength();
	int nStartChar, nEndChar;
	GetSel(nStartChar, nEndChar);
	int nNumericDecimalPos = strText.Find(_T('.'));  // 寻找小数点

	// 小数点处理
	if (nChar == (UINT)_T('.'))
	{
		bool bDelimSelected = false;

		// 如果全部内容被选中,则用"0."替换(包括没有文本的情况下)
		if ((nStartChar==0) && (nEndChar==strText.GetLength()))
		{
			ReplaceSel(_T("0."));
			return;
		}
		// 一部分内容被选中
		else if (nStartChar < nEndChar) 
		{ 
			// 在选中区域寻找小数点
			for (int i=nStartChar; i<nEndChar; i++)
			{
				if (strText[i] == _T('.'))
				{
					// 如果从第一位开始选中,或者从第2位开始选中,并且以负号开头
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

		// 如果小数点已经输入,而且没有被选中，则不再输入
		if (nNumericDecimalPos!=-1 && bDelimSelected==false)
		{
			SetSel(nNumericDecimalPos+1, nNumericDecimalPos+1, FALSE);
			return;
		}
		// 输入小数点后的小数位数处理
		else if (m_nMaxDecimalPlaces>0 && strText.Mid(nEndChar).GetLength()>m_nMaxDecimalPlaces)
		{
			// 开始位置
			if (nStartChar == 0)
			{
				CString str = _T("0.") + strText.Mid(nEndChar, m_nMaxDecimalPlaces);
				SetSel(nStartChar, nLen);
				ReplaceSel(str);
				SetSel(nStartChar+2, nStartChar+2);
			}
			// 不是开始位置
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

	// 负号处理
	if (nChar == (UINT)_T('-'))
	{
		if (!m_bAllowNegative || nStartChar!=0 || strText.Find(_T("-"))>=0)
		{
			return;
		}
	}

	// 小数位数处理
	if (m_nMaxDecimalPlaces>0 &&
		nNumericDecimalPos!=-1 &&
		nChar>=(UINT)_T('0') &&
		nChar<=(UINT)_T('9') &&
		nStartChar>nNumericDecimalPos &&
		nEndChar==nStartChar &&
		strText.Mid(nNumericDecimalPos + 1).GetLength()>=m_nMaxDecimalPlaces)
	{
		// 覆盖原来的小数
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

	// 输入指定字符
	if ((nChar>=(UINT)_T('0') && nChar<=(UINT)_T('9')) || (nChar==(UINT)_T('.')) || (nChar==(UINT)_T('-')))
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
}

  // 调整：当剪贴,复制,粘贴时
void CNumericEdit::Adjustment()
{
	// 获取旧文本
	CString strOldText;
	GetWindowText(strOldText);
	CString strNewText;
	bool bIsNegative = false;

	// 删除不需要的字符
	//int iPos;
	int nDecimalPos = -1;
	int nNewLen = 0;
	int nLen = strOldText.GetLength();
	for (int iPos=0; iPos<nLen; iPos++)
	{
		TCHAR tc = strOldText[iPos];

		// 检查负号
		if (m_bAllowNegative && tc==_T('-'))
			bIsNegative = true;

		// 检查数字
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
		
		// 检查小数点
		else if (tc==_T('.') && nDecimalPos<0)
		{
			if (m_nMaxDecimalPlaces == 0)
				break;

			strNewText += tc;
			nDecimalPos = nNewLen;
			nNewLen++;
		}
	}

	// 如果是负数,加上负号
	if (bIsNegative)
	{
		strNewText.Insert(0, _T("-"));
		nNewLen++;
	}

	// 用新文本代替所有旧文本,并把光标放到文本最后
	SetWindowText(strNewText);
	SetSel(nNewLen, nNewLen, FALSE);
	//SetSel(0, -1, FALSE);
	//ReplaceSel(strNewText);
}