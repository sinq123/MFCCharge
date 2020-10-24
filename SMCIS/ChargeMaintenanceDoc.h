#pragma once

// CChargeMaintenanceDoc 文档

class CChargeMaintenanceDoc : public CDocument
{
	DECLARE_DYNCREATE(CChargeMaintenanceDoc)

public:
	CChargeMaintenanceDoc();
	virtual ~CChargeMaintenanceDoc();
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