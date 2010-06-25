
// CWDoc.h : interface of the CCWDoc class
//


#pragma once


class CCWDoc : public CDocument
{
protected: // create from serialization only
	CCWDoc();
	DECLARE_DYNCREATE(CCWDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CCWDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


