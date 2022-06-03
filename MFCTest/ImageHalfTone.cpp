

#include "pch.h"
#include "ImageHalfTone.h"

CImageHalfTone::CImageHalfTone()
{
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
	DBL dXTime, dYTime;
	int nX, nY;
	int nSrcX, nSrcY;
	int nTblX, nTblY;
	Gdiplus::Color clr;
	DBL dR, dG, dB;
	DBL dTone;
	int nTone;

	nSrcXDot = pcBitmap->GetWidth();
	nSrcYDot = pcBitmap->GetHeight();
	CreateTwoToneBitmap(nSrcXDot * 1.5, nSrcYDot * 1.5);
	dXTime = (DBL)nSrcXDot / (DBL)m_nXDot;
	dYTime = (DBL)nSrcYDot / (DBL)m_nYDot;

	for (nX = 0; nX < m_nXDot; nX++) {
		nSrcX = nX * dXTime;
		for (nY = 0; nY < m_nYDot; nY++) {
			nSrcY = nY * dYTime;
			pcBitmap->GetPixel(nSrcX, nSrcY, &clr);
			dR = clr.GetR(); dG = clr.GetG(); dB = clr.GetB();
			dTone = (0.299 * dR + 0.587 * dG + 0.114 * dB) / 255;
			nTone = dTone * 17;
			nTblX = nX % 17;
			nTblY = nY % 17;
			if (m_tblHalfTone[nTblX][nTblY] < nTone) {
				OnPixcel(nX, nY);
			}
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

	m_hBits = GlobalAlloc(GHND, m_lBitsSize + m_nXByteSize);
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
