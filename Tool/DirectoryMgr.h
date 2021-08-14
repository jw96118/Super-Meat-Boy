#pragma once
class CDirectoryMgr
{
private:
	CDirectoryMgr();
	~CDirectoryMgr();

public:
	static CString ConvertRelativePath(const TCHAR* pFullPath);
};

