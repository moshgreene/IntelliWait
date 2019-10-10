// IntelliWait.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Handle.h"
#include "Process.h"
#include "Event.h"
#include "Iocp.h"
#include "Job.h"
#include "Thread.h"

using namespace std;

constexpr UINT_PTR COMPKEY_TERMINATE = 2;
constexpr UINT_PTR COMPKEY_JOBOJECT = 1;

const std::wstring HELP{ L"/?" };
std::wstring EXE;
std::wstring ARGS;

DWORD WINAPI JobNotify(_In_ LPVOID lpParam);
bool ParseCmdArgs(_In_ int argc, _In_ wchar_t* argv[]);
void PrintUsage();

// This struct is used to pass data into the thread routine
typedef struct tagJobInfo {
	CJob* pJob;
	CIocp* pIocp;
	CEvent* pEvent;
} JobInfo;

bool g_Verbose = false;

int wmain(int argc, wchar_t* argv[])
{
	ParseCmdArgs(argc, argv);

	LPCTSTR exe = const_cast<LPCTSTR>(EXE.c_str());
	LPTSTR args = const_cast<LPTSTR>(ARGS.c_str());

	// Create a suspsended process so it can be added to the job object
	CProcess process = CProcess::Create(
		exe,
		args,
		nullptr,
		nullptr,
		FALSE,
		CREATE_SUSPENDED);
	
	// Create the job object
	CJob job = CJob::Create();

	// Create an event to signal when the job object is complete
	CEvent jobCompletionEvent = CEvent::Create();

	// Create an I/O Completion Port to receive job notifications.
	CIocp iocp = CIocp::Create(0);

	// Assign the process to the job.
	if (!job.AssignProcess(process.GetHandle())) {
		return ERROR_INSTALL_FAILURE;
	}

	// Associate the I/O Completion Port with the job.
	if (!job.AssociateCompletionPort(iocp.GetHandle(), COMPKEY_JOBOJECT)) {
		return ERROR_INSTALL_FAILURE;
	}

	// This JobInfo instance will be passed to a thread to monitor the IOCP
	JobInfo jobInfo;
	jobInfo.pEvent	= &jobCompletionEvent;
	jobInfo.pJob	= &job;
	jobInfo.pIocp	= &iocp; 

	// This new thread will listen for iocp completions
	CThread thread = CThread::Create(nullptr, 0, JobNotify, &jobInfo);

	// Everything is now wired up, so resume our root process
	process.Resume();

	// Wait for the job completion event
	jobCompletionEvent.Wait();

	// The thread is complete, but wait to make sure.
	thread.Wait();

	wcout << L"Complete." << endl;
}

// ==========================================================
// JobNotify -	This function runs the loop to process job
//				object notifications. It runs a as separate 
//				thread.
//
// Parameter:	lpParam - This is a pointer to a JobInfo
//				object.
//			
// Returns:		DWORD
// ==========================================================
DWORD WINAPI JobNotify(_In_ LPVOID lpParam)
{
	JobInfo* pJobInfo = static_cast<JobInfo*>(lpParam);

	CEvent* pResetEvent =  pJobInfo->pEvent;
	CIocp* pIocp =  pJobInfo->pIocp;

	// This is used to track the number of processes. Initially, the count will go to 1 because
	// of our first process.  When it goes *back* to zero, we know everything will be complete.
	LONG processCount = 0;

	// This is used to keep track of process images & PIDs.
	unordered_map<DWORD, wstring> processMap;

	for (;;) {
		// This has the job notification events.
		DWORD dwBytesTransferred = 0;
		ULONG_PTR CompletionKey = 0;

		// This will contain the PID of the process we recieve the notification.
		LPOVERLAPPED lpOverlapped = nullptr;
		DWORD dwProcessId = 0;

		// Wait for completion events.
		pIocp->GetQueuedCompletionStatus(&dwBytesTransferred, &CompletionKey, &lpOverlapped);

		if (COMPKEY_TERMINATE == CompletionKey) {
			break;
		}

		if (COMPKEY_JOBOJECT != CompletionKey) {
			continue;
		}

		switch (dwBytesTransferred) {
		case JOB_OBJECT_MSG_NEW_PROCESS:
			{
				dwProcessId = reinterpret_cast<DWORD>(lpOverlapped);
				CProcess p = move(CProcess::GetProcessById(dwProcessId));
				pair<DWORD, wstring> processInfo = make_pair<DWORD, wstring>((DWORD)lpOverlapped, p.GetImagePath());
				processMap.insert(processInfo);
				wcout << L"Process created: [" << dwProcessId << L"] " << p.GetImagePath() << endl;

				// Increment the process count
				InterlockedIncrement(&processCount);
			}
			break;
		case JOB_OBJECT_MSG_EXIT_PROCESS:
		case JOB_OBJECT_MSG_ABNORMAL_EXIT_PROCESS:
			{
				dwProcessId = reinterpret_cast<DWORD>(lpOverlapped);
				wcout << L"Process complete: [" << processMap[dwProcessId]  << L"]" << endl;

				// This process exited, so we don't need to keep track of it any longer.
				processMap.erase(dwProcessId);

				if (0 == InterlockedDecrement(&processCount)) {
					// Process count has reached 0. There nothing else to wait on. So we set the event & return.
					pResetEvent->Set();
					return 0;
				}
			}
			break;
		default:
			break;
		}
	}

	return 0;
}

// ==============================================================
// ParseCmdArgs -	This function processes command line args
//
// Parameter:	
//		int			argc - The number of arguments passed in argv
//		wchar_t*	argv - an array of command line tokens
//			
// Returns:		
//		true if command line arguments are valid
//		false if command line arguments are invalid
// =============================================================
bool ParseCmdArgs(_In_ int argc, _In_ wchar_t* argv[])
{
	if (argc < 2) {
		PrintUsage();
		return false;
	}

	if (argc >= 2) {
		int i = 1;
		std::wstring tmpArg{ argv[i] };
		if (HELP == tmpArg) {
			// User has queried for help.
			PrintUsage();
			return false;
		}

		if (tmpArg.compare(L"/v") || tmpArg.compare(L"/V")) {
			g_Verbose = true;
			i++;
		}

		EXE = argv[i];
		std::wstring otherArgs;
		i++;
		for (; i < argc; i++) {
			std::wstring _arg{ argv[i] };
			bool bWhiteSpaceFound = false;
			if (_arg.find_first_of(L" ") != std::wstring::npos) {
				bWhiteSpaceFound = true;
				otherArgs.append(L"\"");
			}

			otherArgs.append(argv[i]);

			if (bWhiteSpaceFound) {
				otherArgs.append(L"\"");
			}
			otherArgs.append(L" ");
		}

		ARGS = otherArgs;
	}
	return true;
}

void PrintUsage()
{
	std::wcout << L"IntelliWait [/v] process [args]" << std::endl;
}