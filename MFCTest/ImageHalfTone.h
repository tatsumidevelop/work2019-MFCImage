
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
	int m_tblHalfTone[17][17] = {
		  1,  0,  3,  6,  9,  4, 12, 14, 16,  8,  7, 15, 13, 11,  2, 10,  5
		, 9,  4, 12, 14, 16,  8,  7, 15, 13, 11,  2, 10,  5,  1,  0,  3,  6
		,16,  8,  7, 15, 13, 11,  2, 10,  5,  1,  0,  3,  6,  9,  4, 12, 14
		,13, 11,  2, 10,  5,  1,  0,  3,  6,  9,  4, 12, 14, 16,  8,  7, 15
		, 5,  1,  0,  3,  6,  9,  4, 12, 14, 16,  8,  7, 15, 13, 11,  2, 10
		, 6,  9,  4, 12, 14, 16,  8,  7, 15, 13, 11,  2, 10,  5,  1,  0,  3
		,14, 16,  8,  7, 15, 13, 11,  2, 10,  5,  1,  0,  3,  6,  9,  4, 12
		,15, 13, 11,  2, 10,  5,  1,  0,  3,  6,  9,  4, 12, 14, 16,  8,  7
		,10,  5,  1,  0,  3,  6,  9,  4, 12, 14, 16,  8,  7, 15, 13, 11,  2
		, 3,  6,  9,  4, 12, 14, 16,  8,  7, 15, 13, 11,  2, 10,  5,  1,  0
		,12, 14, 16,  8,  7, 15, 13, 11,  2, 10,  5,  1,  0,  3,  6,  9,  4
		, 7, 15, 13, 11,  2, 10,  5,  1,  0,  3,  6,  9,  4, 12, 14, 16,  8
		, 2, 10,  5,  1,  0,  3,  6,  9,  4, 12, 14, 16,  8,  7, 15, 13, 11
		, 0,  3,  6,  9,  4, 12, 14, 16,  8,  7, 15, 13, 11,  2, 10,  5,  1
		, 4, 12, 14, 16,  8,  7, 15, 13, 11,  2, 10,  5,  1,  0,  3,  6,  9
		, 8,  7, 15, 13, 11,  2, 10,  5,  1,  0,  3,  6,  9,  4, 12, 14, 16
		,11,  2, 10,  5,  1,  0,  3,  6,  9,  4, 12, 14, 16,  8,  7, 15, 13
	};

public:
	void MainExecute(CView* pcView);
	void MainLoop(Bitmap* pcBitmap);
	void SetTonePattern(int nCenterX, int nCenterY, int nTone);
	void CreateTwoToneBitmap(int xdot, int ydot);
	void SaveTwoToneBitmap(LPTSTR lpFileName);
	void OnPixcel(int x, int y);
	void OffPixcel(int x, int y);


};

