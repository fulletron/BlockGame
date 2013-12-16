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
	GS::Utilities::ChunkVector<_UINT64>		m_vector;

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
		m_man.createFrame( 1 );
		m_man.createFrame( 2 );
		m_pBaseFrame = m_man.getFrame( 2 );

		m_vector = m_man.allocate( m_pBaseFrame, 8 * sizeof(_UINT64), TOP );
		m_vector.init( 8 );
	}

	// happens every test case
	virtual void TearDown() 
	{
		m_vector.shutdown();
		m_man.shutdown();
	}
};

TEST_F(MockVectorManager, init)
{
	static int VAL = 100;
	for( int i = 0; i < 4; ++i )
		m_vector.add(i + VAL);

	GS::Utilities::Frame * pFrame1 = m_man.getFrame( 1 );
	GS::Utilities::Frame * pFrame2 = m_man.getFrame( 2 );

	EXPECT_EQ(VAL, *RC(_UINT64 *, pFrame2->getMemBlock() ));

	for( int i = 0; i < 4; ++i )
		EXPECT_EQ( i + VAL, m_vector.get(i) );
};

TEST_F(MockVectorManager, moving)
{
	static int VAL = 100;
	for( int i = 0; i < 4; ++i )
		m_vector.add(i + VAL);

	GS::Utilities::Frame * pFrame1 = m_man.getFrame( 1 );
	GS::Utilities::Frame * pFrame2 = m_man.getFrame( 2 );

	EXPECT_EQ(VAL, *RC(_UINT64 *, pFrame2->getMemBlock() ));

	m_man.destroyFrame( 1 );

	for( int i = 0; i < 4; ++i )
		EXPECT_EQ( i + VAL, m_vector.get(i) );

	EXPECT_EQ(VAL, *RC(_UINT64 *, pFrame1->getMemBlock() ));
};

#endif
