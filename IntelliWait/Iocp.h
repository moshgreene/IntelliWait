#pragma once
#include "Handle.h"
// I/O Completion Port class
class CIocp :
	public CHandle
{
public: 
	CIocp(_In_ HANDLE _handle = INVALID_HANDLE_VALUE);
	CIocp(_In_ const CIocp& _iocp);
	CIocp(_In_ CIocp&& _iocp) noexcept;
	CIocp& operator=(_In_ const CIocp& _iocp);
	CIocp& operator=(_In_ CIocp&& _iocp) noexcept;
	static CIocp Create(_In_ ULONG_PTR _CompletionKey = 0, _In_  DWORD _dwMaxConcurrentThreads = 0);
	virtual ~CIocp();
	BOOL AssociateDevice(_In_ HANDLE _handle, _In_ ULONG_PTR _CompKey);
	BOOL AssociateDevice(_In_ CHandle _handle, _In_ ULONG_PTR _CompKey);
	BOOL GetQueuedCompletionStatus(_Out_ LPDWORD lpNumberOfBytesTransferred,
								_Out_	PULONG_PTR		lpCompletionKey,
								_Out_	LPOVERLAPPED*	lpOverlapped,
								_In_	DWORD			dwMilliseconds = INFINITE);
};

