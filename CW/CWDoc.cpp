
// CWDoc.cpp : implementation of the CCWDoc class
//

#include "stdafx.h"
#include "CW.h"

#include "CWDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCWDoc

IMPLEMENT_DYNCREATE(CCWDoc, CDocument)

BEGIN_MESSAGE_MAP(CCWDoc, CDocument)
END_MESSAGE_MAP()


// CCWDoc construction/destruction

CCWDoc::CCWDoc()
{
	// TODO: add one-time construction code here

}

CCWDoc::~CCWDoc()
{
}

BOOL CCWDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CCWDoc serialization

void CCWDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CCWDoc diagnostics

#ifdef _DEBUG
void CCWDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCWDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCWDoc commands
