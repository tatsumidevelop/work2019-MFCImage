
// MFCTestView.cpp : CMFCTestView クラスの実装
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "MFCTest.h"
#endif

#include "MFCTestDoc.h"
#include "MFCTestDoc.h"
#include "MFCTestView.h"

#include "ImageHalfTone.h"

using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCTestView

IMPLEMENT_DYNCREATE(CMFCTestView, CView)

BEGIN_MESSAGE_MAP(CMFCTestView, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_HALFTONE, &CMFCTestView::OnHalftone)
END_MESSAGE_MAP()

// CMFCTestView コンストラクション/デストラクション

CMFCTestView::CMFCTestView() noexcept
{
	m_nFirstFlag = TRUE;
	m_nWidth = 0;
	m_nHeight = 0;
	// TODO: 構築コードをここに追加します。

}

CMFCTestView::~CMFCTestView()
{
}

BOOL CMFCTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CMFCTestView 描画

void CMFCTestView::OnDraw(CDC* pcDC)
{
	

	CMFCTestDoc* pcDoc = GetDocument();
	ASSERT_VALID(pcDoc);
	if (!pcDoc)
		return;

	if (m_nFirstFlag == TRUE) {
		m_nFirstFlag = FALSE;
		FirstExecute();
	}
	if (m_nWidth == 0) {
		return;
	}
	Graphics cGrph(pcDC->m_hDC);
	cGrph.SetPageUnit(UnitPixel);
	cGrph.DrawImage(m_pcBitmap, 0, 0, m_nWidth, m_nHeight);
	cGrph.DrawImage(m_pcDstBitmap, m_nWidth, 0, m_nDstWidth, m_nDstHeight);
}


// CMFCTestView の印刷

BOOL CMFCTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return DoPreparePrinting(pInfo);
}

void CMFCTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CMFCTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}


// CMFCTestView の診断

#ifdef _DEBUG
void CMFCTestView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCTestDoc* CMFCTestView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCTestDoc)));
	return (CMFCTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCTestView メッセージ ハンドラー

void CMFCTestView::FirstExecute()
{

}

void CMFCTestView::OnHalftone()
{
	CImageHalfTone* pcImageHalfTone;

	pcImageHalfTone = new CImageHalfTone();

	pcImageHalfTone->MainExecute(this);

	Invalidate(TRUE);
}

