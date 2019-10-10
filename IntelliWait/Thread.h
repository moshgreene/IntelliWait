#pragma once
#include "Handle.h"
class CThread :
	public CHandle
{
private:
	DWORD m_dwThreadId;
public:
	CThread(_In_ HANDLE _handle = nullptr);
	CThread(_In_ CThread&&);
	CThread(_In_ const CThread&);
	virtual ~CThread();
	static CThread Create(
		_In_ LPSECURITY_ATTRIBUTES   lpThreadAttributes,
		_In_ SIZE_T                  dwStackSize,
		_In_ LPTHREAD_START_ROUTINE  lpStartAddress,
		_In_ LPVOID					lpParameter = nullptr,
		_In_ DWORD                   dwCreationFlags = 0);
	DWORD GetThreadId() const;
	HANDLE GetHandle() const;
};

