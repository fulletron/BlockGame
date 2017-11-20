#ifndef __COMPLETIONPORT_H__
#define __COMPLETIONPORT_H__

#include "../definitions_types.h"

// KYLE :: remove redefines
#ifndef _WINSOCK2API_
#include <WinSock2.h>
#endif

namespace GS {
namespace Server {

/*
* Handler for the single IOCP that the server uses.
*/
class CompletionPort {
public:
	// WHAT EXPLICIT MEANS: https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean
	// "Prefixing the explicit keyword to the constructor prevents the compiler from using that constructor for implicit conversions."

	explicit CompletionPort(
		size_t maxConcurrency);

	~CompletionPort();

	void associateDevice(
		HANDLE hDevice,
		ULONG_PTR completionKey);

	void postStatus(
		ULONG_PTR completionKey,
		DWORD dwNumBytes = 0,
		OVERLAPPED *pOverlapped = 0);

	void getStatus(
		ULONG_PTR *pCompletionKey,
		PDWORD pdwNumBytes,
		OVERLAPPED **ppOverlapped);

	bool getStatus(
		ULONG_PTR *pCompletionKey,
		PDWORD pdwNumBytes,
		OVERLAPPED **ppOverlapped,
		DWORD dwMilliseconds);

selective:
	HANDLE m_iocp;

	// No copies do not implement
	CompletionPort(const CompletionPort &rhs);
	CompletionPort &operator=(const CompletionPort &rhs);
};

};
};

//#endif

#endif