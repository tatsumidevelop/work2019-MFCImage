// DialogTest.cpp : 実装ファイル
//

#include "pch.h"
#include "MFCTest.h"
#include "DialogTest.h"
#include "afxdialogex.h"


// CDialogTest ダイアログ

IMPLEMENT_DYNAMIC(CDialogTest, CDialog)

CDialogTest::CDialogTest(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TESTDLG, pParent)
{

}

CDialogTest::~CDialogTest()
{
}

void CDialogTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDBAR, m_slidBar);
	DDX_Control(pDX, IDC_EDINFO, m_edInfo);
}


BEGIN_MESSAGE_MAP(CDialogTest, CDialog)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDBAR, &CDialogTest::OnNMReleasedcaptureSldrbar)
END_MESSAGE_MAP()


// CDialogTest メッセージ ハンドラー


BOOL CDialogTest::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_slidBar.SetRange(0, 220);

	// TODO: ここに初期化を追加してください

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
void CDialogTest::OnNMReleasedcaptureSldrbar(NMHDR* pNMHDR, LRESULT* pResult)
{
	int nPos;
	TCHAR	szNumStr[32];

	UpdateData(TRUE);
	nPos = m_slidBar.GetPos();
	_stprintf_s(szNumStr, _T("%d"), nPos);
	m_edInfo.SetWindowText(szNumStr);
	*pResult = 0;
}
