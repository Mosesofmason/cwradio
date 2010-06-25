
// CWView.h : interface of the CCWView class
//

#include "MyEdit.h"

#pragma once


class CCWView : public CView
{
protected: // create from serialization only
	CCWView();
	DECLARE_DYNCREATE(CCWView)

// Attributes
public:
	CCWDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCWView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();

protected:
	TCHAR fN[512];
	TCHAR fP[512];

private:
	int cxChar, cyChar;
	int cxClient, cyClient;
	TEXTMETRIC tm;
	int line;


public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

private:
	CMyEdit *pMyEdit;
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};

#ifndef _DEBUG  // debug version in CWView.cpp
inline CCWDoc* CCWView::GetDocument() const
   { return reinterpret_cast<CCWDoc*>(m_pDocument); }
#endif

