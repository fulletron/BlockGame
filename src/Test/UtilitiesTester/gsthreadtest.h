#ifndef __GSTHREADTEST_H_
#define __GSTHREADTEST_H_

#ifndef TEST_ENABLED
#define TEST_ENABLED
#endif

#include <gtest/gtest.h>
#include <Utilities/utilities.h>

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

class MockObject2
{
private:
	int data;
public:
	int getData(){ return data; };
	void setData(int a_data) { data = a_data; }
};

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

};

#endif
