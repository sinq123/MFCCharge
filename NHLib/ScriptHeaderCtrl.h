#pragma once

#include "ThemeHelperST.h"

// CScriptHeaderCtrl

class CScriptHeaderCtrl : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CScriptHeaderCtrl)

public:
	CScriptHeaderCtrl();
	virtual ~CScriptHeaderCtrl();

protected:
	DECLARE_MESSAGE_MAP()

	CThemeHelperST		m_Theme;
	void ScriptTextOut(HDC hDC, CString data , CRect* drawRect, int justification);
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	

};


