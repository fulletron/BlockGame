#include "useswinsock.h"

namespace GS {
namespace Server {

UsesWinsock::UsesWinsock()
{
	WORD wVersionRequested = 0x202;

	if (0 != ::WSAStartup(wVersionRequested, &m_data))
	{
		DEBUG_OUT("WSAStartup Error");
		//throw CWin32Exception(_T("CUsesWinsock::CUsesWinsock()"), ::WSAGetLastError());
	}
}

UsesWinsock::~UsesWinsock()
{
	WSACleanup();
}

};
};
