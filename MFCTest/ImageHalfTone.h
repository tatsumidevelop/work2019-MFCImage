
#pragma once

class CImageHalfTone
{
public:
	CImageHalfTone();
	~CImageHalfTone();

public:
	CMFCTestView* m_pcView;
	int		m_nXDot, m_nYDot;
	int		m_nXByteSize;
	long	m_lBitsSize;
	BITMAPFILEHEADER	m_bif;
	BITMAPINFOHEADER	m_bih;
	RGBQUAD				m_clr[2];
	HANDLE	m_hBits;
	BYTE*	m_lpBits;
	Point	m_ptHalfTone[16];

public:
	void MainExecute(CView* pcView);
	void MainLoop(Bitmap* pcBitmap);
	void SetTonePattern(int nCenterX, int nCenterY, int nTone);
	void CreateTwoToneBitmap(int xdot, int ydot);
	void SaveTwoToneBitmap(LPTSTR lpFileName);
	void OnPixcel(int x, int y);
	void OffPixcel(int x, int y);


};

