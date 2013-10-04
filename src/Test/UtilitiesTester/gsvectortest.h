#ifndef __GSVECTORTEST_H_
#define __GSVECTORTEST_H_

#ifndef TEST_ENABLED
#define TEST_ENABLED
#endif

#include <gtest/gtest.h>
#include <Utilities/utilities.h>

// To use a test fixture, derive a class from testing::Test.
class MockVectorManager : public testing::Test 
{
protected:
	GS::Utilities::ChunkManager 	m_man;
	GS::Utilities::Frame * 		m_pBaseFrame;
	static const int		TESTSIZECHUNK = 64;
	static const int		TESTNUMCHUNKS = 2;
	GS::Utilities::GSVector<_UINT64>		m_vector;

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
		m_man.createFrame( CV8("frame001") );
		m_pBaseFrame = m_man.getFrame( CV8("frame001") );

		m_vector.init( m_pBaseFrame, 4 );
	}

	// happens every test case
	virtual void TearDown() 
	{
		m_man.shutdown();
	}
};

TEST_F(MockVectorManager, init)
{
	EXPECT_EQ( 0, 0 );
};

#endif
