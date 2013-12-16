#ifndef __CHUNKMANTEST_H_
#define __CHUNKMANTEST_H_

#ifndef TEST_ENABLED
#define TEST_ENABLED
#endif

#include <gtest/gtest.h>
#include <Utilities/utilities.h>

// To use a test fixture, derive a class from testing::Test.
class MockChunkManager : public testing::Test 
{
protected:
		GS::Utilities::ChunkManager m_man;	

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
		m_man.init(4,16);
	}

	// happens every test case
	virtual void TearDown() 
	{
		m_man.shutdown();
	}
};

TEST_F(MockChunkManager, two_minus_one_check_TOP)
{
	m_man.shutdown();
	m_man.init(2,16);
	m_man.createFrame( 1 );
	m_man.createFrame( 2 );

	_TChunkPtr<_UINT64> test;
	test = m_man.allocate( 2, 8, TOP );
	test.dereference() = 19;

	EXPECT_EQ( 19, test.dereference() );

	m_man.destroyFrame( 1 );

	EXPECT_EQ( 19, test.dereference() );
};

TEST_F(MockChunkManager, two_minus_one_check_SUC)
{
	m_man.shutdown();
	m_man.init(16,16);
	m_man.createFrame( 1 );
	m_man.createFrame( 2 );

	_TChunkPtr<_UINT64> test;
	test = m_man.allocate( 2, 8, TOP );
	test.dereference() = 19;

	EXPECT_EQ( 19, test.dereference() );

	m_man.destroyFrame( 1 );

	EXPECT_EQ( 19, test.dereference() );
};

TEST(ChunkManager, init_test)
{
	GS::Utilities::ChunkManager man;
	_UINT32 ret = man.init(4,16);
	EXPECT_EQ( 0, ret );
};

TEST(CV8, converter_test)
{
	EXPECT_EQ( CV8("frame001"), CV8("frame001") );
}

TEST_F(MockChunkManager, create_frame_test)
{
	GS::Utilities::Frame * pFrame = m_man.createFrame( CV8("frame001") );
	EXPECT_EQ( pFrame->m_pMemBlock, m_man.m_pChunk );
};

TEST_F(MockChunkManager, create_nameclash_test )
{
	GS::Utilities::Frame * pFrame = m_man.createFrame( CV8("frame001") );
	pFrame = m_man.createFrame( CV8("frame001") );
	EXPECT_EQ( 0, pFrame );
};

TEST_F(MockChunkManager, get_frame_test_1)
{
	GS::Utilities::Frame *pFrame = 0, *pFrameFromGet = 0, *pNull = 0;

	pFrame = m_man.createFrame( CV8("frame001") );
	pFrameFromGet = m_man.getFrame( CV8("frame001") );
	EXPECT_EQ( pFrame, pFrameFromGet );
};

TEST_F(MockChunkManager, get_frame_test_2)
{
	GS::Utilities::Frame *pFrame = 0, *pFrameFromGet = 0, *pNull = 0;

	pFrame = m_man.createFrame( CV8("frame001") );
	pNull = m_man.createFrame( CV8("frame001") );
	EXPECT_EQ( 0, pNull ) << "Test A Failed.";

	pFrameFromGet = m_man.getFrame( CV8("frame001") );
	EXPECT_EQ( pFrame, pFrameFromGet ) << "Test B Failed.";
};

TEST_F(MockChunkManager, get_frame_test_3)
{
	GS::Utilities::Frame *pFrame = 0, *pFrameFromGet = 0, *pNull = 0;

	pFrame = m_man.createFrame( CV8("frame001") );
	bool destroyed = m_man.destroyFrame( CV8("frame001") );
	EXPECT_EQ( true, destroyed )  
		<< "FRAME WAS NOT DESTROYED.";

	pFrameFromGet = m_man.getFrame( CV8("frame001") );
	EXPECT_EQ( 0, pFrameFromGet )  
		<< "COULD STILL INCORRECTLY GRAB FRAME.";
};

TEST_F(MockChunkManager, destroy_frame_test_1)
{
	GS::Utilities::Frame	*pFrame = 0, 
							*pFrame2 = 0,
							*pFrameFromGet = 0;

	pFrame = m_man.createFrame( CV8("frame001") );
	pFrame2 = m_man.createFrame( CV8("frame002") );

	bool destroyed = m_man.destroyFrame( CV8("frame002") );
	EXPECT_EQ( true, destroyed )  << "Test A Failed.";

	pFrameFromGet = m_man.getFrame( CV8("frame002") );
	EXPECT_EQ( 0, pFrameFromGet )  << "Test B Failed.";
};

TEST_F(MockChunkManager, destroy_frame_test_2)
{
	GS::Utilities::Frame	*pFrame = 0, 
							*pFrame2 = 0,
							*pFrameFromGet = 0, 
							*pNull = 0,
							*pFrame3 = 0,
							*pFrame4 = 0;

	pFrame = m_man.createFrame( CV8("frame001") );
	pFrame2 = m_man.createFrame( CV8("frame002") );
	pFrame3 = m_man.createFrame( CV8("frame003") );
	pFrame4 = m_man.createFrame( CV8("frame004") );

	_BYTE* pFrameMemBlock = pFrame2->m_pMemBlock;

	bool destroyed = m_man.destroyFrame( CV8("frame002") );
	EXPECT_EQ( true, destroyed )  << "Test A Failed.";

	pFrameFromGet = m_man.getFrame( CV8("frame004") );
	EXPECT_EQ( pFrame2, pFrameFromGet )  << "FRAME 4 WAS NOT PROPERLY MOVED.";

	EXPECT_EQ( *pFrameMemBlock, *pFrameFromGet->m_pMemBlock ) << "Test C Failed.";
	EXPECT_EQ( 0, pFrame4->getName() ) << "Test D Failed.";
};

TEST_F(MockChunkManager, destroy_frame_test_fStop)
{
	GS::Utilities::Frame	*pFrame = 0, 
							*pFrame2 = 0,
							*pFrameFromGet = 0, 
							*pNull = 0,
							*pFrame3 = 0,
							*pFrame4 = 0;

	pFrame = m_man.createFrame( CV8("frame001") );
	pFrame2 = m_man.createFrame( CV8("frame002") );

	_BYTE* pFrameMemBlock = pFrame2->m_pMemBlock;

	pFrame2->setfStop(BOT);

	bool destroyed = m_man.destroyFrame( CV8("frame001") );
	EXPECT_EQ( true, destroyed )  << "Frame 1 could not be destroyed";

	pFrameFromGet = m_man.getFrame( CV8("frame002") );
	EXPECT_EQ( pFrame->m_pMemBlock, pFrameFromGet->m_pfStop[BOT][0] ) 
		<< "Frame2's fstop was not moved correctly.";
};


#endif
