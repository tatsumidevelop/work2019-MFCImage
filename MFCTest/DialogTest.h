#pragma once


// CDialogTest ダイアログ

class CDialogTest : public CDialog
{
	DECLARE_DYNAMIC(CDialogTest)

public:
	CDialogTest(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CDialogTest();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CSliderCtrl m_slidBar;
	CEdit m_edInfo;
	afx_msg void OnNMReleasedcaptureSldrbar(NMHDR* pNMHDR, LRESULT* pResult);
};
