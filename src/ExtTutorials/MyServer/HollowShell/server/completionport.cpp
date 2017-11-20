#include "completionport.h"

namespace GS {
namespace Server {

CompletionPort::CompletionPort(
	size_t maxConcurrency)
	: m_iocp(::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, maxConcurrency))
{
	if (m_iocp == 0)
	{
		DEBUG_OUT("FAILED TO CREATE IO COMPLETION PORT.");
	}
}

CompletionPort::~CompletionPort()
{
	::CloseHandle(m_iocp);
}

void CompletionPort::getStatus(
	ULONG_PTR *pCompletionKey,
	PDWORD pdwNumBytes,
	OVERLAPPED **ppOverlapped)
{
	if (0 == ::GetQueuedCompletionStatus(m_iocp, pdwNumBytes, pCompletionKey, ppOverlapped, INFINITE))
	{
		//throw CWin32Exception(_T("CIOCompletionPort::GetStatus() - GetQueuedCompletionStatus"), ::GetLastError());
		DEBUG_OUT("GetQueuedCompletionStatus failed. A.");
	}
}

bool CompletionPort::getStatus(
	ULONG_PTR *pCompletionKey,
	PDWORD pdwNumBytes,
	OVERLAPPED **ppOverlapped,
	DWORD dwMilliseconds)
{
	bool ok = true;

	if (0 == ::GetQueuedCompletionStatus(m_iocp, pdwNumBytes, pCompletionKey, ppOverlapped, dwMilliseconds))
	{
		DWORD lastError = ::GetLastError();

		if (lastError != WAIT_TIMEOUT)
		{
			//throw CWin32Exception(_T("CIOCompletionPort::GetStatus() - GetQueuedCompletionStatus"), lastError);
			DEBUG_OUT("GetQueuedCompletionStatus failed. B.");
		}

		ok = false;
	}

	return ok;
}

void CompletionPort::associateDevice(
	HANDLE hDevice,
	ULONG_PTR completionKey)
{
	if (m_iocp != ::CreateIoCompletionPort(hDevice, m_iocp, completionKey, 0))
	{
		DEBUG_OUT("associating IOCP failed.");
	}
}

void CompletionPort::postStatus(
	ULONG_PTR completionKey,
	DWORD dwNumBytes,
	OVERLAPPED * pOverlapped)
{
	if (0 == ::PostQueuedCompletionStatus(m_iocp, dwNumBytes, completionKey, pOverlapped))
	{
		DEBUG_OUT("postQueuedCompletionStatus failed.");
	}
}

};
};