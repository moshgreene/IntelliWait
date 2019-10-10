#include "pch.h"
#include "Job.h"

// Constructor that takes a handle to a job object.
CJob::CJob(_In_ HANDLE _handle) : CHandle{ _handle }
{

}

// Move Constructor
CJob::CJob(_In_ CJob&& _job) noexcept :
	CHandle{ _job.m_handle }
{
	_job.m_handle = nullptr;
}

// Copy Constructur
CJob::CJob(_In_ const CJob& _job) :
	CHandle{ _job.m_handle }
{

}

CJob::~CJob()
{
	if (m_handle) {
		CloseHandle(m_handle);
		m_handle = nullptr;
	}
}

// Move operator
CJob& CJob::operator=(_In_ CJob&& _job) noexcept
{
	m_handle = _job.m_handle;
	_job.m_handle = nullptr;

	return *this;
}

// Copy operator
CJob& CJob::operator=(_In_ const CJob& _job)
{
	m_handle = _job.m_handle;

	return *this;
}

// Job Factory method
CJob CJob::Create(_In_ LPSECURITY_ATTRIBUTES _pSecurityAttributes, _In_ LPCTSTR _szJobName)
{
	HANDLE hJob = CreateJobObject(_pSecurityAttributes, _szJobName);

	if (nullptr == hJob)
	{
		// ERROR
		DWORD dwErr = GetLastError();
		return nullptr;
	}
	else
	{
		CJob job{ hJob };
		return job;
	}
}

// Assign a process to the job object.
BOOL CJob::AssignProcess(_In_ HANDLE _hProcess)
{
	return AssignProcessToJobObject(m_handle, _hProcess);
}

// Associate the I/O Completion Port to the job object.
BOOL CJob::AssociateCompletionPort(_In_ HANDLE _hIocp, _In_ ULONG_PTR _CompletionKey)
{
	JOBOBJECT_ASSOCIATE_COMPLETION_PORT joacp = { (PVOID)_CompletionKey, _hIocp };

	return SetInformationJobObject(m_handle,
		JobObjectAssociateCompletionPortInformation,
		&joacp,
		sizeof(JOBOBJECT_ASSOCIATE_COMPLETION_PORT));
}

// Forcefully terminate the job
BOOL CJob::Terminate(_In_ UINT _uExitCode)
{
	return TerminateJobObject(m_handle, _uExitCode);
}