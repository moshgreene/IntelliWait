#pragma once
class CHandle
{
protected:
	HANDLE m_handle;

public:
	CHandle(_In_ HANDLE _handle = nullptr);
	virtual ~CHandle();
	virtual DWORD Wait(_In_ DWORD _dwMilliseconds = INFINITE);
	HANDLE GetHandle() const noexcept;
	BOOL Close();
};

