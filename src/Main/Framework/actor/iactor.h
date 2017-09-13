#ifndef __ACTOR_H_
#define __ACTOR_H_

#include <Utilities/definitions_types.h>
#include <Graphics/resource/iresourcerequirer.h>
#include <Graphics/library/ilibrary.h>

namespace GS {
namespace Actor {
class IActor : public GS::Resource::IResourceRequirer,
				public GS::Library::ISubscriber
{
selective:
	virtual _UINT32 __subscribe(const _UINT64 & a_id) = 0;
	virtual _UINT32 __unsubscribe(const _UINT64 & a_id) = 0;
public:
	virtual _BOOL areResourcesReady() = 0;
	virtual _UINT32 performSubscriptions() = 0;
	virtual _UINT32 performUnsubscriptions() = 0;

	virtual void setSubscriptionPriority(const _BOOL a_flag) = 0;
};

class TestActor : public IActor
{
selective:
	_BOOL m_priority;
selective:
	virtual _UINT32 __subscribe(const _UINT64 & a_id) { return 0; }
	virtual _UINT32 __unsubscribe(const _UINT64 & a_id) { return 0; }

public:
	virtual _BOOL areResourcesReady() { return true; }
	virtual _UINT32 performSubscriptions() { return 0; }
	virtual _UINT32 performUnsubscriptions() { return 0; }

	virtual void setSubscriptionPriority(const _BOOL a_flag) { m_priority = a_flag; }
};

};
};

#endif