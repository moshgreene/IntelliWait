#pragma once
#include "Handle.h"
class CEvent :
	public CHandle
{
public:
	CEvent(_In_ HANDLE hEvent = nullptr);
	CEvent(_In_ CEvent&& _event) noexcept;
	CEvent(_In_ const CEvent& _event);
	virtual ~CEvent();
	CEvent& operator=(_In_ CEvent&& _event) noexcept;
	CEvent& operator=(_In_ const CEvent& _event);
	static CEvent Create(
		_In_ LPSECURITY_ATTRIBUTES	lpEventAttributes	= nullptr,
		_In_ BOOL					bManualReset		= FALSE,
		_In_ BOOL					bInitialState		= FALSE,
		_In_ LPCWSTR					lpName				= nullptr
	);

	BOOL Set();
	BOOL Reset();
};

