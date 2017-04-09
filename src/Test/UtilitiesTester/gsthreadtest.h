#ifndef __GSTHREADTEST_H_
#define __GSTHREADTEST_H_

#ifndef TEST_ENABLED
#define TEST_ENABLED
#endif

#include <gtest/gtest.h>
//#include <Utilities/utilities.h>

/*
// To use a test fixture, derive a class from testing::Test.
class MockFrameManager : public testing::Test 
{
protected:
	GS::Utilities::ChunkManager 	m_man;
	GS::Utilities::Frame * 		m_pBaseFrame;
	static const int		TESTSIZECHUNK = 16;
	static const int		TESTNUMCHUNKS = 4;

public:
	// happens once
	static void SetUpTestCase()
	{
	}

	// happens once
	static void TearDownTestCase()
	{
	}

	// happens every test case
	virtual void SetUp() 
	{
		m_man.init(TESTNUMCHUNKS,TESTSIZECHUNK);
		m_man.createFrame( CV8::FRAME001 );
		m_pBaseFrame = m_man.getFrame( CV8::FRAME001 );
	}

	// happens every test case
	virtual void TearDown() 
	{
		m_man.shutdown();
	}
};

*/

namespace ThreadTestNS {
	/*
class MockObject2
{
private:
	int data;
public:
	int getData(){ return data; };
	void setData(int a_data) { data = a_data; }
};

class MockObject3
{
private:
	int data;
	GS::Utilities::BT::GSMutex lock;
public:
	int getData()
	{ 
		if(lock.lock_flag_bit)
			return 0;
		return data; 
	};
	void setData(int a_data) 
	{ 
		data = a_data; 
	}
};

#define TEST_NUM 10

class MockPresenterObject
{
private:
	GS::Utilities::BT::GSMutex mutex;
	_VECTOR<_INT32> queue;
	_VECTOR<_INT32> data;
	typedef _VECTOR<_INT32>::iterator _ITER;

public:
	void addIntToQueue( _INT32 a_int )
	{
		GSScopedLock lock (mutex);
		queue.push_back( a_int );
		std::cout << "pushing " << a_int << "back" << std::endl;
	}

	bool isDoneProcessing()
	{
		if( data.size() == TEST_NUM )
			return true;
		return false;
	}

	void processQueueLoop()
	{
		while( !isDoneProcessing() ) {
			while( queue.size() > 0 )
			{
			    GSScopedLock lock (mutex);
				_INT32 x = queue.back();
				data.push_back( x );
				queue.pop_back();
				std::cout << "popping " << x << std::endl;
			}
		}
	}

	void printData()
	{
	  for (_ITER it = data.begin() ; it != data.end(); ++it)
		std::cout << ' ' << *it;
	  std::cout << '\n';
	}


	_VECTOR<_INT32> getData() const
	{
		return data;
	}
};

boost::mutex io_mutex;

void count(int id)
{
	for (int i = 0; i < 10; ++i)
	{
	boost::mutex::scoped_lock
		lock(io_mutex);
	std::cout << id << ": " <<
		i << std::endl;
	}
}

int boop()
{
	boost::thread thrd1(
	boost::bind(&count, 1));

	for(int i = 0; i < 900000; ++i )
		int test[12];

	count(2);
	//boost::thread thrd2(
	//boost::bind(&count, 2));
	thrd1.join();
	//thrd2.join();
	return 0;
}

TEST(Thread, basicthread)
{
	boop();
}
*/
/*
TEST(Thread, init)
{
	static const int NUMOBJS = 120;
	MockObject2 pObjs[NUMOBJS];
	GS::Utilities::BT::GSThreadGroup threadgroup;

	int test = 0;

	for( int i = 0; i < NUMOBJS; i++ )
	{
		threadgroup.add_thread(new GS::Utilities::BT::GSThread( &MockObject2::setData, &(pObjs[i]), i));
	}
	threadgroup.join_all();

	for( int i = 0; i < NUMOBJS; ++i )
	{
		EXPECT_EQ(i, pObjs[i].getData());
	}

	test++;
}
*/
/*
void dotest( MockPresenterObject * pres )
{
	for (int i = 0; i < TEST_NUM; ++i)
		pres->addIntToQueue(i);

	while (!pres->isDoneProcessing()){}
}
*/
/*
TEST(Thread, mutex)
{
	MockPresenterObject pres;
	GS::Utilities::BT::GSThread presthread( &MockPresenterObject::processQueueLoop, &pres );
	presthread.start_thread();

	for (int i = 0; i < TEST_NUM; ++i)
		pres.addIntToQueue(i);

	//while (!pres.isDoneProcessing()){}
	std::cout << " WHATTTT " << std::endl;

	presthread.join();
}

*/
};

#endif
