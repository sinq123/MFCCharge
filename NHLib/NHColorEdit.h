#pragma once

#include "NHEdit.h"

class AFX_EXT_CLASS CLightGreyEdit:public CNHEdit
{
public:
	CLightGreyEdit()
	{
		SetBKColorValue(RGB(211, 211, 211));
	}
};

class CGainsboroEdit:public CNHEdit
{
public:
	CGainsboroEdit()
	{
		SetBKColorValue(RGB(220, 220, 220));
	}
};

class CLightSteelBlueEdit:public CNHEdit
{
public:
	CLightSteelBlueEdit()
	{
		SetBKColorValue(RGB(176,196,222));
	}
};

class CSkyBlueEdit:public CNHEdit
{
public:
	CSkyBlueEdit()
	{
		SetBKColorValue(RGB(135,206,235));
	}
};