#include "pch.h"
#include "Iocp.h"

CIocp::CIocp(_In_ HANDLE _handle) : CHandle{ _handle }
{
}

// Copy constructor
CIocp::CIocp(_In_ const CIocp& _iocp) :
	CHandle{_iocp.m_handle}
{

}

// Move constructor
CIocp::CIocp(_In_ CIocp&& _iocp) noexcept :
	CHandle{ _iocp.m_handle }
{
	_iocp.m_handle = nullptr;
}

// Copy operator=
CIocp& CIocp::operator=(_In_ const CIocp& _iocp)
{
	m_handle = _iocp.m_handle;

	return *this;
}

// Move operator=
CIocp& CIocp::operator=(_In_ CIocp&& _iocp) noexcept
{
	m_handle = _iocp.m_handle;
	_iocp.m_handle = nullptr;

	return *this;
}

// CIocp Factory method.
CIocp CIocp::Create(_In_ ULONG_PTR _CompletionKey, _In_ DWORD _dwMaxConcurrentThreads)
{
	HANDLE handle = CreateIoCompletionPort(
		INVALID_HANDLE_VALUE,
		nullptr,
		_CompletionKey,
		_dwMaxConcurrentThreads);

	CIocp iocp{ handle };

	return iocp;
}

// Destructor
CIocp::~CIocp()
{
	if (m_handle) {
		CloseHandle(m_handle);
		m_handle = nullptr;
	}
}

BOOL CIocp::GetQueuedCompletionStatus(_Out_ LPDWORD _lpNumberOfBytesTransferred,
	_Out_ PULONG_PTR lpCompletionKey,
	_Out_ LPOVERLAPPED* lpOverlapped,
	_In_ DWORD        dwMilliseconds)
{
	return ::GetQueuedCompletionStatus(m_handle, _lpNumberOfBytesTransferred, lpCompletionKey, lpOverlapped, dwMilliseconds);
}

BOOL CIocp::AssociateDevice(_In_ HANDLE _handle, _In_ ULONG_PTR _CompletionKey)
{
	assert(INVALID_HANDLE_VALUE != _handle);
	assert(NULL != _handle);
	BOOL bRetVal = FALSE;

	if ((nullptr == m_handle) || (INVALID_HANDLE_VALUE == m_handle)) {
		return bRetVal;
	}
	else {
		HANDLE hIocp = CreateIoCompletionPort(_handle, m_handle, _CompletionKey, 0);

		return hIocp == m_handle;
	}
}
BOOL CIocp::AssociateDevice(_In_ CHandle _handle, _In_ ULONG_PTR _CompletionKey)
{
	return AssociateDevice(_handle.GetHandle(), _CompletionKey);
}