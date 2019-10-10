#include "pch.h"
#include "Event.h"

// This constructor takes an existing event handle
CEvent::CEvent(_In_ HANDLE hEvent) : CHandle{ hEvent }
{
}

// Move Constructor
CEvent::CEvent(_In_ CEvent&& _event) noexcept :
	CHandle{ _event.m_handle }
{
	_event.m_handle = nullptr;
}

// Copy Constructur
CEvent::CEvent(_In_ const CEvent& _event) :
	CHandle{ _event.m_handle }
{

}

CEvent::~CEvent()
{
	if (m_handle) {
		CloseHandle(m_handle);
		m_handle = nullptr;
	}
}

// Move operator=
CEvent& CEvent::operator=(_In_ CEvent&& _event) noexcept
{
	m_handle = _event.m_handle;
	_event.m_handle = nullptr;

	return *this;
}

// Copy operator=
CEvent& CEvent::operator=(_In_ const CEvent& _event)
{
	m_handle = _event.m_handle;

	return *this;
}

// CEvent Factor method
CEvent CEvent::Create(
	_In_ LPSECURITY_ATTRIBUTES	lpEventAttributes,
	_In_ BOOL					bManualReset, 
	_In_ BOOL					bInitialState,
	_In_ LPCWSTR				lpName)
{
	HANDLE h = CreateEvent(nullptr,
		bManualReset,
		bInitialState,
		lpName);

	CEvent e{ h };

	return e;
}

// Set the event
BOOL CEvent::Set()
{
	return SetEvent(m_handle);
}

// Reset the event
BOOL CEvent::Reset()
{
	return ResetEvent(m_handle);
}