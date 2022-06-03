#include "pch.h"
#include "CZipEx.h"


CZipEx::CZipEx()
{

}
int CZipEx::FileInit(LPCTSTR lpZipFile)
{
    char chEmpty[] = { 'P','K',5,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

    CFile fileEmpty;
    fileEmpty.Open(lpZipFile, CFile::modeWrite | CFile::modeCreate);
    fileEmpty.Write(chEmpty, sizeof(chEmpty));
    fileEmpty.Close();
    return 0;
}
BOOL CZipEx::FileExist(LPCTSTR lpszPathname)
{
	CFileFind find;
	return find.FindFile(lpszPathname);
}

CString CZipEx::GetFilename(LPCTSTR lpszPathname)
{
	CFileFind find;
	if (find.FindFile(lpszPathname))
	{
		find.FindNextFile();
		return find.GetFileName();
	}
	else
		return _T("");
}

HRESULT AddFileToZipFile(LPCTSTR lpszZipPathname, LPCTSTR lpszFilePathname)
{
	if (!FileExist(lpszZipPathname))
		CreateEmptyZipFile(lpszZipPathname);

	if (!FileExist(lpszFilePathname))
		return S_FALSE;

	CString strFilename = GetFilename(lpszFilePathname);

	HRESULT hRes = S_FALSE;
	Shell32::IShellDispatchPtr ptrShell;
	hRes = ptrShell.CreateInstance(__uuidof(Shell32::Shell));
	if (hRes == S_OK)
	{
		Shell32::FolderPtr ptrFolder = ptrShell->NameSpace((COleVariant)lpszZipPathname);
		if (ptrFolder)
		{
			Shell32::FolderItemPtr ptrFolderItem = ptrFolder->ParseName((LPCTSTR)strFilename);
			if (ptrFolderItem)
			{
				int iCountBeforeDelete = ptrFolder->Items()->GetCount();
				ptrFolderItem->InvokeVerb((COleVariant)"delete");
				TRACE("<%s> exists. Deleted it.\r\n", strFilename);
				ptrFolderItem.Release();
				ptrFolderItem = NULL;
				int iCountAfterDelete = ptrFolder->Items()->GetCount();

				if (iCountAfterDelete == iCountBeforeDelete)
				{
					ptrFolder.Release();
					ptrFolder = NULL;
					ptrShell.Release();
					ptrShell = NULL;
					return S_OK;
				}
			}

			long iDat = FOF_SILENT | FOF_NOCONFIRMATION;
			int iCountBeforeCopy = ptrFolder->Items()->GetCount();
			hRes = ptrFolder->CopyHere((COleVariant)lpszFilePathname, (COleVariant)iDat);
			int i = 0;

			while (1)
			{
				int iCountAfterCopy = ptrFolder->Items()->GetCount();
				TRACE("CountAfterCopy = %d, CountBeforeCopy = %d   ...\r\n", iCountAfterCopy, iCountBeforeCopy);
				if (iCountAfterCopy > iCountBeforeCopy)
					break;
				Sleep(100);

			}
			ptrFolder.Release();
			ptrFolder = NULL;
		}
		ptrShell.Release();
		ptrShell = NULL;
	}
	return hRes;
}
