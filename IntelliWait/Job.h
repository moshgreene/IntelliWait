#pragma once
#include "Handle.h"
// Windows Job Object class
class CJob :
	public CHandle
{
public:
	CJob(_In_ HANDLE _handle = nullptr);
	CJob(_In_ CJob&& _job) noexcept;
	CJob(_In_ const CJob& _job);
	virtual ~CJob();
	CJob& operator=(_In_ const CJob& _job);
	CJob& operator=(_In_ CJob&& _job) noexcept;
	static CJob Create(_In_ LPSECURITY_ATTRIBUTES _pSecurityAttributes = nullptr, _In_ LPCTSTR _szJobName = nullptr);
	BOOL AssignProcess(_In_ HANDLE _hProcess);
	BOOL AssociateCompletionPort(_In_ HANDLE _hIocp, _In_ ULONG_PTR _CompletionKey);
	BOOL Terminate(_In_ UINT _uExitCode);
};

