
// CWView.cpp : implementation of the CCWView class
//

#include "stdafx.h"
#include "CW.h"

#include "CWDoc.h"
#include "CWView.h"

#include "CWaveFile.h"
#include "MyEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SZLENGTH 512

// CCWView

IMPLEMENT_DYNCREATE(CCWView, CView)

BEGIN_MESSAGE_MAP(CCWView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCWView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &CCWView::OnFileOpen)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

// CCWView construction/destruction

CCWView::CCWView()
{
	// TODO: add construction code here
}

CCWView::~CCWView()
{
	delete pMyEdit;
}

BOOL CCWView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCWView drawing

void CCWView::OnDraw(CDC* /*pDC*/)
{
	CCWDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CCWView printing


void CCWView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CCWView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCWView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCWView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CCWView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCWView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CCWView diagnostics

#ifdef _DEBUG
void CCWView::AssertValid() const
{
	CView::AssertValid();
}

void CCWView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCWDoc* CCWView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCWDoc)));
	return (CCWDoc*)m_pDocument;
}
#endif //_DEBUG


// CCWView message handlers

void CCWView::OnFileOpen()
{
	// TODO: Add your command handler code here

	static TCHAR szFilter[256]=_T("wave file (*.wav)|*.wav|all files (*.*)|*.*||");
	CFileDialog filDlg (TRUE, NULL, NULL, 
		OFN_DONTADDTORECENT|OFN_ENABLESIZING|OFN_EXPLORER|OFN_FILEMUSTEXIST, 
		szFilter, NULL);
	if (filDlg.DoModal()==IDOK)
	{
		_tcscpy_s(fP, SZLENGTH, filDlg.GetPathName());
		_tcscpy_s(fN, SZLENGTH, filDlg.GetFileName());
	}



	int  iLength ;
	TCHAR szBuffer [40] ;
	InvalidateRect(NULL);
	line=pMyEdit->GetWindowTextLength();
	pMyEdit->SetSel(0, line, 0);
	pMyEdit->Clear();

	line=0;

	try
	{
		CWaveFile wavefile(fP);
		WAVEFORM *format = wavefile.GetWaveFormat ();
		CDC *dc=GetDC();
		HDC hdc=dc->m_hDC;

		iLength = wsprintf (szBuffer, TEXT ("Format: %i \r\n"), format->wFormatTag);
		pMyEdit->SetSel(-1, -1, 1);
		pMyEdit->ReplaceSel(szBuffer);
		iLength = wsprintf (szBuffer, TEXT ("Samples per second: %i \r\n"), format->nSamplesPerSec);
		pMyEdit->SetSel(-1, -1, 1);
		pMyEdit->ReplaceSel(szBuffer);
		iLength = wsprintf (szBuffer, TEXT ("Channels: %i \r\n"), format->nChannels);
		pMyEdit->SetSel(-1, -1, 1);
		pMyEdit->ReplaceSel(szBuffer);
		iLength = wsprintf (szBuffer, TEXT ("Bit per sample: %i \r\n"), format->wBitsPerSample);
		pMyEdit->SetSel(-1, -1, 1);
		pMyEdit->ReplaceSel(szBuffer);
		


		if( format->wBitsPerSample == 16 ) 
		{
			AudioWord *buffer = reinterpret_cast <AudioWord *> (wavefile.GetData());
			DATA *data = wavefile.GetWaveData();
			LPVOID AudioData=wavefile.GetData ();
			DWORD samples = data->dataSIZE/sizeof(AudioData);
			iLength = wsprintf (szBuffer, TEXT ("Samples number: %i \r\n"), samples);
			pMyEdit->SetSel(-1, -1, 1);
			pMyEdit->ReplaceSel(szBuffer);

			pMyEdit->SetSel(-1, -1, FALSE);
			pMyEdit->ReplaceSel("\r\nLast 100 lines: \r\n ... \r\n ... \r\n ... \r\n");
			DWORD p=samples-100;
			if (p<0)
			{
				p=0;
			}
			for( p; p < samples; p++ ) 
			{
				iLength = wsprintf (szBuffer, TEXT ("%i: %i \r\n"), p, buffer[p]);
				pMyEdit->SetSel(-1, -1, FALSE);
				pMyEdit->ReplaceSel(szBuffer);
			}
		}
		line=pMyEdit->GetWindowTextLength();

		ReleaseDC(dc);

	}
	catch (WaveErrors::FileOperation * e)
	{
		
	}
	catch (WaveErrors::RiffDoesntMatch * e)
	{
	}
	catch (WaveErrors::WaveDoesntMatch * e)
	{
	}
	catch (WaveErrors::FmtDoesntMatch * e)
	{
	}
	catch (WaveErrors::DataDoesntMatch  * e)
	{
	}

	
}

int CCWView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	
	
	CDC	*pdc = GetDC();
	HDC hdc=pdc->m_hDC;
	GetTextMetrics (hdc, &tm) ;
	cxChar = tm.tmAveCharWidth ;
	cyChar = tm.tmHeight+tm.tmExternalLeading;
	

	ReleaseDC (pdc);
	pMyEdit=new CMyEdit;
	pMyEdit->Create (WS_CHILD | WS_VISIBLE | WS_VSCROLL |	WS_BORDER | ES_LEFT | ES_MULTILINE |
					ES_AUTOHSCROLL | ES_AUTOVSCROLL,
					CRect(0, 0, 0, 0),  
					this,  
					1); 
	pMyEdit->ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_DRAWFRAME);

	return 0;
}

void CCWView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	cxClient = cx;
	cyClient = cy;
	pMyEdit->MoveWindow(CRect(0,0,cxClient,cyClient/2), 0);

}

void CCWView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	// TODO: Add your message handler code here
	pMyEdit->SetFocus();
}
