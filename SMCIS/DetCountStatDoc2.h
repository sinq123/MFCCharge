#pragma once

// CDetCountStatDoc2 文档

class CDetCountStatDoc2 : public CDocument
{
	DECLARE_DYNCREATE(CDetCountStatDoc2)

public:
	CDetCountStatDoc2();
	virtual ~CDetCountStatDoc2();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // 为文档 I/O 重写
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
};