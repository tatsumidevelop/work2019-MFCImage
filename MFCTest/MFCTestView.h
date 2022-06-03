
// MFCTestView.h : CMFCTestView クラスのインターフェイス
//

#pragma once


class CMFCTestView : public CView
{
protected: // シリアル化からのみ作成します。
	CMFCTestView() noexcept;
	DECLARE_DYNCREATE(CMFCTestView)

// 属性
public:
	CMFCTestDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 実装
public:
	virtual ~CMFCTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:


public:
	int m_nFirstFlag;
	Bitmap* m_pcBitmap;
	int m_nWidth, m_nHeight;
	Bitmap* m_pcDstBitmap;
	int m_nDstWidth, m_nDstHeight;

public:
	void FirstExecute();


protected:
// 生成された、メッセージ割り当て関数
public:
	afx_msg void OnHalftone();
};

#ifndef _DEBUG  // MFCTestView.cpp のデバッグ バージョン
inline CMFCTestDoc* CMFCTestView::GetDocument() const
   { return reinterpret_cast<CMFCTestDoc*>(m_pDocument); }
#endif

