

#include "pch.h"
#include "ImageHalfTone.h"

CImageHalfTone::CImageHalfTone()
{
	m_ptHalfTone[0].X = 0;   m_ptHalfTone[0].Y = 0;   // 1
	m_ptHalfTone[1].X = 1;   m_ptHalfTone[1].Y = 0;   // 2
	m_ptHalfTone[2].X = 1;   m_ptHalfTone[2].Y = 1;   // 3
	m_ptHalfTone[3].X = 0;   m_ptHalfTone[3].Y = 1;   // 4
	m_ptHalfTone[4].X = -1;  m_ptHalfTone[4].Y = 0;   // 5
	m_ptHalfTone[5].X = 2;   m_ptHalfTone[5].Y = 1;   // 6
	m_ptHalfTone[6].X = 1;   m_ptHalfTone[6].Y = -1;  // 7
	m_ptHalfTone[7].X = 0;   m_ptHalfTone[7].Y = 2;   // 8
	m_ptHalfTone[8].X = -1;  m_ptHalfTone[8].Y = 1;   // 9
	m_ptHalfTone[9].X = 2;   m_ptHalfTone[9].Y = 0;   // 10
	m_ptHalfTone[10].X = 0;  m_ptHalfTone[10].Y = -1; // 11
	m_ptHalfTone[11].X = 1;  m_ptHalfTone[11].Y = 2;  // 12
	m_ptHalfTone[12].X = -1; m_ptHalfTone[12].Y = -1; // 13
	m_ptHalfTone[13].X = 2;  m_ptHalfTone[13].Y = 2;  // 14
	m_ptHalfTone[14].X = 2;  m_ptHalfTone[14].Y = -1; // 15
	m_ptHalfTone[15].X = -1; m_ptHalfTone[15].Y = 2;  // 16

}
CImageHalfTone::~CImageHalfTone()
{

}
void CImageHalfTone::MainExecute(CView* pcView)
{
	TCHAR	szFileName[FNAMEMAX];
	Bitmap* pcBitmap;

	m_pcView = (CMFCTestView*)pcView;
	_tcscpy_s(szFileName, _T("d:\\test.jpg"));
	pcBitmap = new Bitmap(szFileName);
	m_pcView->m_pcBitmap = pcBitmap;
	m_pcView->m_nWidth = pcBitmap->GetWidth();
	m_pcView->m_nHeight = pcBitmap->GetHeight();
	MainLoop(pcBitmap);
	_tcscpy_s(szFileName, _T("d:\\test2.bmp"));
	SaveTwoToneBitmap(szFileName);
	pcBitmap = new Bitmap(szFileName);
	m_pcView->m_pcDstBitmap = pcBitmap;
	m_pcView->m_nDstWidth = pcBitmap->GetWidth();
	m_pcView->m_nDstHeight = pcBitmap->GetHeight();

}
void CImageHalfTone::MainLoop(Bitmap *pcBitmap)
{
	int nSrcXDot, nSrcYDot;
	int nPicupXDot, nPicupYDot;
	int nX, nY;
	int nSetX, nSetY;
	Gdiplus::Color clr;
	DBL dR, dG, dB;
	DBL dTone;
	int nTone;

	nSrcXDot = pcBitmap->GetWidth();
	nSrcYDot = pcBitmap->GetHeight();
	CreateTwoToneBitmap(nSrcXDot, nSrcYDot);
	nPicupXDot = nSrcXDot / 4;
	nPicupYDot = nSrcYDot / 4;
	for (nX = 0; nX < nPicupXDot; nX++) {
		nSetX = nX * 4 + 2;
		for (nY = 0; nY < nPicupYDot; nY++) {
			nSetY = nY * 4 + 2;
			pcBitmap->GetPixel(nSetX, nSetY, &clr);
			dR = clr.GetR(); dG = clr.GetG(); dB = clr.GetB();
			dTone = (0.299 * dR + 0.587 * dG + 0.114 * dB) / 255;
			nTone = dTone * 16;
			SetTonePattern(nSetX, nSetY, nTone);
		}
	}
}
void CImageHalfTone::SetTonePattern(int nCenterX, int nCenterY, int nTone)
{
	int nSetX, nSetY;
	int idx, max;

	max = 16;
	for (idx = 0; idx < max; idx++) {
		nSetX = nCenterX + m_ptHalfTone[max - idx - 1].X;
		nSetY = nCenterY + m_ptHalfTone[max - idx - 1].Y;
		OnPixcel(nSetX, nSetY);
		if (nTone  < idx) {
			break;
		}
	}
}
void CImageHalfTone::CreateTwoToneBitmap(int xdot, int ydot)
{

	int	headsize;

	m_nXDot = xdot;
	m_nYDot = ydot;
	m_nXByteSize = ((((xdot + 7) / 8) + 3) / 4L) * 4L;
	m_nXDot = m_nXByteSize * 8;
	m_lBitsSize = m_nXByteSize * m_nYDot;

	m_hBits = GlobalAlloc(GHND, m_lBitsSize);
	if (m_hBits == 0) {
		return;
	}
	m_lpBits = (BYTE*)GlobalLock(m_hBits);
	if (m_lpBits == NULL) {
		GlobalFree(m_hBits);
		return;
	}
	memset(m_lpBits, 0, m_lBitsSize);

	memset((LPTSTR)(&m_bif), 0, sizeof(BITMAPFILEHEADER));
	memset((LPTSTR)(&m_bih), 0, sizeof(BITMAPINFOHEADER));
	headsize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 2;
	m_bif.bfType = 0x4D42;
	m_bif.bfSize = m_lBitsSize + headsize;
	m_bif.bfOffBits = headsize;

	m_bih.biSize = sizeof(BITMAPINFOHEADER);
	m_bih.biWidth = m_nXDot;
	m_bih.biHeight = m_nYDot;
	m_bih.biPlanes = 1;
	m_bih.biBitCount = 1;
	m_bih.biCompression = 0;

	m_clr[0].rgbBlue = 0;
	m_clr[0].rgbGreen = 0;
	m_clr[0].rgbRed = 0;
	m_clr[0].rgbReserved = 0;
	m_clr[1].rgbBlue = 255;
	m_clr[1].rgbGreen = 255;
	m_clr[1].rgbRed = 255;
	m_clr[1].rgbReserved = 0;
}

void CImageHalfTone::SaveTwoToneBitmap(LPTSTR lpFileName)
{
	errno_t error;
	FILE*	fp;
	int		y;
	BYTE* sp;

	try {
		error = _tfopen_s(&fp, lpFileName, _T("wb"));
		if (error != 0) {
			return;
		}
		fwrite(&m_bif, sizeof(BITMAPFILEHEADER), 1, fp);
		fwrite(&m_bih, sizeof(BITMAPINFOHEADER), 1, fp);
		fwrite(m_clr, sizeof(RGBQUAD), 2, fp);
		for (y = 0; y < m_nYDot; y++) {
			sp = m_lpBits + (long)y * (long)m_nXByteSize;
			fwrite(sp, 1, m_nXByteSize, fp);
		}
		fclose(fp);
	}
	catch (CException* pcEx)
	{

	}
}
void CImageHalfTone::OnPixcel(int x, int y)
{
	int nXByte;
	int nSift;
	int nSetbit;
	BYTE* sp;
	BYTE bt;

	y = m_nYDot - y;
	if (x < 0 && m_nXDot <= x
	&& y < 0 && m_nYDot <= y) {
		return;
	}
	nXByte = x / 8;
	nSift = x % 8;
	int add = (long)y * (long)m_nXByteSize + nXByte;
	sp = m_lpBits + add;
	bt = *sp;
	nSetbit = 0x080 >> nSift;
	*sp = *sp | (BYTE)nSetbit;

}
void CImageHalfTone::OffPixcel(int x, int y)
{
	int nXByte;
	int nSift;
	int nSetbit;
	BYTE* sp;

	y = m_nYDot - y;
	if (x < 0 && m_nXDot <= x
		&& y < 0 && m_nYDot <= y) {
		return;
	}
	nXByte = x / 8;
	nSift = x % 8;
	sp = m_lpBits + (long)y * (long)m_nXByteSize + nXByte;
	nSetbit = 0x00FF7F >> nSift;
	*sp = *sp & (BYTE)nSetbit;
}
