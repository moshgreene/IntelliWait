#include "pch.h"
#include "Process.h"

// Constructor takes a handle to a process.
CProcess::CProcess(_In_ HANDLE _hProcess) :
	CHandle{ _hProcess },
	m_startupInfo{ 0 },
	m_dwExitCode{ 0 },
	m_dwProcessId{ 0 },
	m_bCreateSuspended{ FALSE },
	m_bProcessCreated{ FALSE }
{

}

// Move Constructor
CProcess::CProcess(_In_ CProcess&& _process) : 
	CHandle{ _process.m_handle },
	m_startupInfo{ _process.m_startupInfo },
	m_processInfo{ _process.m_processInfo },
	m_dwExitCode{ _process.m_dwExitCode },
	m_dwProcessId{ _process.m_dwProcessId },
	m_bProcessCreated{ _process.m_bProcessCreated },
	m_bCreateSuspended{ _process.m_bCreateSuspended } 
{
	_process.m_handle = nullptr;
	_process.m_startupInfo.cb = 0;
	_process.m_startupInfo.cbReserved2 = 0;
	_process.m_startupInfo.dwFillAttribute = 0;
	_process.m_startupInfo.dwFlags = 0;
	_process.m_startupInfo.dwX = 0;
}

// Copy Constructor
CProcess::CProcess(_In_ const CProcess& _process) :
	CHandle{ _process.m_handle },
	m_startupInfo{ _process.m_startupInfo },
	m_processInfo{ _process.m_processInfo },
	m_dwExitCode{ _process.m_dwExitCode },
	m_dwProcessId{ _process.m_dwProcessId },
	m_bProcessCreated{ _process.m_bProcessCreated },
	m_bCreateSuspended{ _process.m_bCreateSuspended }
{}

// This constructor uses a PROCESS_INFORMATION instance to create the object.
CProcess::CProcess(_In_ PROCESS_INFORMATION _pi) :
	CHandle{ _pi.hProcess },
	m_startupInfo{ 0 },
	m_dwProcessId{ _pi.dwProcessId },
	m_dwExitCode{ 0 },
	m_bCreateSuspended{ FALSE },
	m_bProcessCreated{ FALSE }
{
	m_processInfo.hProcess = _pi.hProcess;
	m_processInfo.hThread = _pi.hThread;
	m_processInfo.dwProcessId = _pi.dwProcessId;
	m_processInfo.dwThreadId = _pi.dwThreadId;
}

CProcess::~CProcess()
{
	if (m_handle) {
		CloseHandle(m_handle);
		m_handle = nullptr;
	}
}

// Process Factory method
CProcess CProcess::Create(
	_In_ LPCTSTR				szApplicationName,
	_In_ LPTSTR					lpCommandLine,
	_In_ LPSECURITY_ATTRIBUTES	lpProcessAttributes,
	_In_ LPSECURITY_ATTRIBUTES	lpThreadAttributes,
	_In_ BOOL					bInheritHandles,
	_In_ DWORD					dwCreationFlags,
	_In_ LPVOID					lpEnvironment,
	_In_ LPCTSTR				lpCurrentDirectory,
	_In_ LPSTARTUPINFO			lpStartupInfo)
{
	STARTUPINFO si = { 0 };

	if (nullptr == lpStartupInfo) {
		si.cb = sizeof(STARTUPINFO);
	}
	else {
		si = *lpStartupInfo;
	}

	BOOL bCreateSuspended = FALSE;

	if ((dwCreationFlags & CREATE_SUSPENDED) == CREATE_SUSPENDED) {
		bCreateSuspended = TRUE;
	}

	PROCESS_INFORMATION pi = { 0 };

	BOOL bProcessCreated = CreateProcess(
		szApplicationName,
		lpCommandLine,
		lpProcessAttributes,
		lpThreadAttributes,
		bInheritHandles,
		dwCreationFlags,
		lpEnvironment,
		lpCurrentDirectory,
		NULL == lpStartupInfo ? &si : lpStartupInfo,
		&pi);

	if (bProcessCreated) {
		CProcess p{ pi };
		p.m_bProcessCreated = bProcessCreated;
		p.m_bCreateSuspended = bCreateSuspended;

		if (!bCreateSuspended) {
			// We don't need a handle to the main thread
			// if Create Process suceeded and it was
			// not created suspended
			CloseHandle(pi.hThread);
		}

		return p;
	}
	else {
		return nullptr;
	}
}

// Returns the full path of the process
std::wstring CProcess::GetImagePath() const
{
	WCHAR exe[MAX_PATH];
	DWORD dwBufferSize = MAX_PATH;

	if (QueryFullProcessImageName(m_handle, 0, exe, &dwBufferSize)) {
		std::wstring imagePath{ exe };
		return std::move(imagePath);
	}
	else {
		return std::wstring{ L"" };
	}
}

// Given a process ID, this will give us a process object.
CProcess CProcess::GetProcessById(_In_ DWORD _dwProcessId, _In_ DWORD _dwDesiredAccess, _In_ BOOL _bInheritHandle)
{
	HANDLE hProcess = OpenProcess(_dwDesiredAccess, _bInheritHandle, _dwProcessId);

	CProcess p(hProcess);

	return p;
}

// Returns the process ID
DWORD CProcess::GetProcessId() const
{
	return m_dwProcessId;
}

// Resumes a process if it was suspended.
DWORD CProcess::Resume()
{
	DWORD dwResume = ResumeThread(m_processInfo.hThread);

	if (m_bCreateSuspended) {
		CloseHandle(m_processInfo.hThread);
	}

	return dwResume;
}