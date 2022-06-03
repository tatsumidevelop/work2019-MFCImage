
#pragma once
class CZipEx
{
public:
	CZipEx();
public:
	int FileInit(LPCTSTR  lpZipFile);
	BOOL FileExist(LPCTSTR lpszPathname);
	CString GetFilename(LPCTSTR lpszPathname);
};

