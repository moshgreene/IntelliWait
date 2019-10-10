#pragma once
#include "Handle.h"
class CProcess : public CHandle
{
private:
	STARTUPINFO m_startupInfo;
	PROCESS_INFORMATION m_processInfo;
	DWORD m_dwExitCode;
	DWORD m_dwProcessId;
	BOOL m_bProcessCreated;
	BOOL m_bCreateSuspended;

public:
	CProcess(_In_ HANDLE _hProcess = nullptr);
	CProcess(_In_ CProcess&&);
	CProcess(_In_ const CProcess&);
	CProcess(_In_ PROCESS_INFORMATION);
	virtual ~CProcess();
	static CProcess Create(_In_ LPCTSTR	szApplicationName,
			_In_ LPTSTR					lpCommandLine = nullptr,
			_In_ LPSECURITY_ATTRIBUTES	lpProcessAttributes = nullptr,
			_In_ LPSECURITY_ATTRIBUTES	lpThreadAttributes = nullptr,
			_In_ BOOL					bInheritHandles = FALSE,
			_In_ DWORD					dwCreationFlags = 0,
			_In_ LPVOID					lpEnvironment = nullptr,
			_In_ LPCTSTR				lpCurrentDirectory = nullptr,
			_In_ LPSTARTUPINFO			lpStartupInfo = nullptr);
	DWORD Resume();
	DWORD GetProcessId() const;
	static CProcess GetProcessById(_In_ DWORD, _In_ DWORD dwDesiredAccess = PROCESS_QUERY_INFORMATION, _In_ BOOL bInheritHandle = FALSE);
	std::wstring GetImagePath() const;
};

