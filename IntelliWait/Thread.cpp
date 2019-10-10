#include "pch.h"
#include "Thread.h"

CThread::CThread(_In_ HANDLE _handle) : CHandle{ _handle }, m_dwThreadId{ 0 }
{

}

CThread::CThread(_In_ CThread&& _thread) :
	CHandle{ _thread },
	m_dwThreadId{_thread.m_dwThreadId}
{
	_thread.m_handle = nullptr;
}

CThread::CThread(_In_ const CThread& _thread) :
	CHandle{ _thread },
	m_dwThreadId{_thread.m_dwThreadId}
{
}

CThread::~CThread()
{
	if (m_handle) {
		CloseHandle(m_handle);
		m_handle = nullptr;
	}
}

CThread CThread::Create(
	_In_ LPSECURITY_ATTRIBUTES   lpThreadAttributes,
	_In_ SIZE_T                  dwStackSize,
	_In_ LPTHREAD_START_ROUTINE  lpStartAddress,
	_In_ LPVOID					lpParameter,
	_In_ DWORD                   dwCreationFlags)
{
	DWORD dwThreadId = 0;

	HANDLE h = CreateThread(
		lpThreadAttributes,
		dwStackSize,
		lpStartAddress,
		lpParameter,
		dwCreationFlags,
		&dwThreadId
	);

	CThread t;
	t.m_dwThreadId = dwThreadId;
	t.m_handle = h;

	return t;
}

DWORD CThread::GetThreadId() const
{
	return m_dwThreadId;
}

HANDLE CThread::GetHandle() const
{
	return m_handle;
}