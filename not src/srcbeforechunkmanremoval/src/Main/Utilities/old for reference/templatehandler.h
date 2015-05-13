#ifndef __TEMPLATEHANDLE_H_
#define __TEMPLATEHANDLE_H_

namespace GS {
namespace Utilities {

template <typename T>
class Handle 
{
public:
	Handle() : m_handle(0) {}

	void init( unsigned int a_index );
	unsigned int getIndex() const { return ( m_index ); }
	unsigned int getMagic() const { return ( m_magic ); }
	unsigned int getHandle() const { return ( m_handle ); }
	bool isNull() const { return ( !m_handle ); }

	operator unsigned int () const  { return ( m_handle ); } 

private:
	union 
	{
		enum 
		{
			MAX_BITS_INDEX = 16;
			MAX_BITS_MAGIC = 16;

			MAX_INDEX = ( 1 << MAX_BITS_INDEX ) - 1;
			MAX_MAGIC = ( 1 << MAX_BITS_MAGIC ) - 1;
		};

		struct 
		{
			unsigned m_index : MAX_BITS_INDEX;
			unsigned m_magic : MAX_BITS_MAGIC;
		};

		unsigned int m_handle;
	};
	
};

template< typename T >
inline bool operator != ( Handle<T> a_l, Handle<T> a_r )
{
	return ( a_l.getHandle() != a_r.getHandle() );
}

template< typename T >
inline bool operator == ( Handle<T> a_l, Handle<T> a_r )
{
	return ( a_l.getHandle() == a_r.getHandle() );
}




template< typename DATA, typename HANDLE >
class HandleMgr
{
private:
	static const int MAX_NUM = 1024;
	DATA m_userVec[MAX_NUM];
	unsigned int m_magicVec[MAX_NUM];
	unsigned int m_freeVec[MAX_NUM];

public:
	HandleMgr(){}
	~HandleMgr(){}

	DATA * acquire( HANDLE & a_handle );
	void release( HANDLE a_handle );

	DATA * dereference( HANDLE a_handle );
	const DATA * dereference( HANDLE a_handle ) const;
	
	unsigned int getUsedHandleCount() const
	{
		return ( m_magicVec )
	}
};

};
};

#endif