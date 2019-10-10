#include "pch.h"
#include "Handle.h"

CHandle::CHandle(_In_ HANDLE _handle) : m_handle{ _handle }
{

}

CHandle::~CHandle()
{
	if (m_handle) {
		CloseHandle(m_handle);
		m_handle = nullptr;
	}
}

DWORD CHandle::Wait(_In_ DWORD _dwMilliseconds)
{
	DWORD dwRetVal = WaitForSingleObject(m_handle, _dwMilliseconds);

	return dwRetVal;
}

BOOL CHandle::Close()
{
	BOOL bRetVal = CloseHandle(m_handle);

	return bRetVal;
}

HANDLE CHandle::GetHandle() const noexcept
{
	return m_handle;
}