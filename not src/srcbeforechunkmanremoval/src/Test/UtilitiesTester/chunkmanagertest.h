#ifndef __CHUNKMANTEST_H_
#define __CHUNKMANTEST_H_

#ifndef TEST_ENABLED
#define TEST_ENABLED
#endif

#include <gtest/gtest.h>
#include <Utilities/utilities.h>

extern GS::Utilities::ChunkManager g_chunkman;

// To use a test fixture, derive a class from testing::Test.
class MockChunkManager : public testing::Test 
{
protected:

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
		g_chunkman.init(4,16);
	}

	// happens every test case
	virtual void TearDown() 
	{
		g_chunkman.shutdown();
	}
};

TEST_F(MockChunkManager, two_minus_one_check_TOP)
{
	g_chunkman.shutdown();
	g_chunkman.init(2,16);
	g_chunkman.createFrame( 1 );
	g_chunkman.createFrame( 2 );

	_TChunkPtr<_UINT64> test;
	test = g_chunkman.allocate( 2, 8, TOP );
	test.dereference() = 19;

	EXPECT_EQ( 19, test.dereference() );
	_UINT64 * pInt = test.pointer();

	g_chunkman.destroyFrame( 1 );

	EXPECT_EQ( 19, test.dereference() );

	EXPECT_NE( pInt, test.pointer() );
};

TEST_F(MockChunkManager, two_minus_one_check_SUC)
{
	g_chunkman.shutdown();
	g_chunkman.init(16,16);
	g_chunkman.createFrame( 1 );
	g_chunkman.createFrame( 2 );

	_TChunkPtr<_UINT64> test;
	test = g_chunkman.allocate( 2, 8, TOP );
	test.dereference() = 19;

	EXPECT_EQ( 19, test.dereference() );

	g_chunkman.destroyFrame( 1 );

	EXPECT_EQ( 19, test.dereference() );
};

TEST(ChunkManager, init_test)
{
	GS::Utilities::ChunkManager man;
	_UINT32 ret = man.init(4,16);
	EXPECT_EQ( 0, ret );
};

/*
TEST(CV8, converter_test)
{
	EXPECT_EQ( CV8::FRAME001, CV8::FRAME001 );
}
*/

TEST_F(MockChunkManager, create_frame_test)
{
	GS::Utilities::Frame * pFrame = g_chunkman.createFrame( CV8::FRAME001 );
	EXPECT_EQ( pFrame->m_pMemBlock, g_chunkman.m_pChunk );
};

TEST_F(MockChunkManager, create_nameclash_test )
{
	GS::Utilities::Frame * pFrame = g_chunkman.createFrame( CV8::FRAME001 );
	pFrame = g_chunkman.createFrame( CV8::FRAME001 );
	EXPECT_EQ( 0, pFrame );
};

TEST_F(MockChunkManager, get_frame_test_1)
{
	GS::Utilities::Frame *pFrame = 0, *pFrameFromGet = 0, *pNull = 0;

	pFrame = g_chunkman.createFrame( CV8::FRAME001 );
	pFrameFromGet = g_chunkman.getFrame( CV8::FRAME001 );
	EXPECT_EQ( pFrame, pFrameFromGet );
};

TEST_F(MockChunkManager, get_frame_test_2)
{
	GS::Utilities::Frame *pFrame = 0, *pFrameFromGet = 0, *pNull = 0;

	pFrame = g_chunkman.createFrame( CV8::FRAME001 );
	pNull = g_chunkman.createFrame( CV8::FRAME001 );
	EXPECT_EQ( 0, pNull ) << "Test A Failed.";

	pFrameFromGet = g_chunkman.getFrame( CV8::FRAME001 );
	EXPECT_EQ( pFrame, pFrameFromGet ) << "Test B Failed.";
};

TEST_F(MockChunkManager, get_frame_test_3)
{
	GS::Utilities::Frame *pFrame = 0, *pFrameFromGet = 0, *pNull = 0;

	pFrame = g_chunkman.createFrame( CV8::FRAME001 );
	bool destroyed = g_chunkman.destroyFrame( CV8::FRAME001 );
	EXPECT_EQ( true, destroyed )  
		<< "FRAME WAS NOT DESTROYED.";

	pFrameFromGet = g_chunkman.getFrame( CV8::FRAME001 );
	EXPECT_EQ( 0, pFrameFromGet )  
		<< "COULD STILL INCORRECTLY GRAB FRAME.";
};

TEST_F(MockChunkManager, destroy_frame_test_1)
{
	GS::Utilities::Frame	*pFrame = 0, 
							*pFrame2 = 0,
							*pFrameFromGet = 0;

	pFrame = g_chunkman.createFrame( CV8::FRAME001 );
	pFrame2 = g_chunkman.createFrame( CV8::FRAME002 );

	bool destroyed = g_chunkman.destroyFrame( CV8::FRAME002 );
	EXPECT_EQ( true, destroyed )  << "Test A Failed.";

	pFrameFromGet = g_chunkman.getFrame( CV8::FRAME002 );
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

	pFrame = g_chunkman.createFrame( CV8::FRAME001 );
	pFrame2 = g_chunkman.createFrame( CV8::FRAME002 );
	pFrame3 = g_chunkman.createFrame( CV8::FRAME003 );
	pFrame4 = g_chunkman.createFrame( CV8::FRAME004 );

	_BYTE* pFrameMemBlock = pFrame2->m_pMemBlock;

	bool destroyed = g_chunkman.destroyFrame( CV8::FRAME002 );
	EXPECT_EQ( true, destroyed )  << "Test A Failed.";

	pFrameFromGet = g_chunkman.getFrame( CV8::FRAME004 );
	EXPECT_EQ( pFrame2, pFrameFromGet )  << "FRAME 4 WAS NOT PROPERLY MOVED.";

	EXPECT_EQ( *pFrameMemBlock, *pFrameFromGet->m_pMemBlock ) << "Test C Failed.";
	EXPECT_EQ( 0, pFrame4->getName() ) << "Test D Failed.";
};

TEST_F(MockChunkManager, destroy_frame_test_currentloc)
{
	GS::Utilities::Frame	*pFrame = 0, 
							*pFrame2 = 0,
							*pFrameFromGet = 0, 
							*pNull = 0,
							*pFrame3 = 0,
							*pFrame4 = 0;

	g_chunkman.m_pFramesInRelation[0];


	pFrame = g_chunkman.createFrame( CV8::FRAME001 );
	pFrame2 = g_chunkman.createFrame( CV8::FRAME002 );
	
	pFrame->setfStop(BOT);
	pFrame2->setfStop(BOT);

	_BYTE * pFirstLoc = pFrame->m_pCurrentLoc[BOT];

	bool destroyed = g_chunkman.destroyFrame( CV8::FRAME001 );
	EXPECT_EQ( true, destroyed )  << "Frame 1 could not be destroyed";

	pFrameFromGet = g_chunkman.getFrame( CV8::FRAME002 );

	EXPECT_EQ( pFirstLoc, pFrameFromGet->m_pCurrentLoc[BOT] )
		<< "The currentLoc moves incorrectly.";
};

TEST_F(MockChunkManager, destroy_frame_test_fStop)
{
	GS::Utilities::Frame	*pFrame = 0, 
							*pFrame2 = 0,
							*pFrameFromGet = 0, 
							*pFrame0 = 0;

	pFrame0 = g_chunkman.createFrame( CV8::FRAME003 );
	pFrame = g_chunkman.createFrame( CV8::FRAME001 );
	pFrame2 = g_chunkman.createFrame( CV8::FRAME002 );

	_TChunkPtr<_UINT64> testInt, testInt2, testInt3;
	pFrame2->setfStop( BOT );
	testInt = g_chunkman.allocate( CV8::FRAME002 , sizeof( _UINT64 ), BOT );
	testInt.dereference() = 100;
	pFrame2->setfStop( BOT );
	testInt2 = g_chunkman.allocate( CV8::FRAME002 , sizeof( _UINT64 ), BOT );
	testInt.dereference() = 101;
	pFrame2->setfStop( BOT );
	testInt3 = g_chunkman.allocate( CV8::FRAME002 , sizeof( _UINT64 ), BOT );
	testInt.dereference() = 102;

	_UINT64 diff1 = RC( _UINT64, pFrame2->m_pfStop[BOT][0] ) - RC( _UINT64, pFrame2->getMemBlock() );
	_UINT64 diff2 = RC( _UINT64, pFrame2->m_pfStop[BOT][1] ) - RC( _UINT64, pFrame2->getMemBlock() );
	_UINT64 diff3 = RC( _UINT64, pFrame2->m_pfStop[BOT][2] ) - RC( _UINT64, pFrame2->getMemBlock() );

	bool destroyed = g_chunkman.destroyFrame( CV8::FRAME001 );
	EXPECT_EQ( true, destroyed )  << "Frame 1 could not be destroyed";

	pFrameFromGet = g_chunkman.getFrame( CV8::FRAME002 );
	_UINT64 diffA = RC( _UINT64, pFrameFromGet->m_pfStop[BOT][0] ) - RC( _UINT64, pFrameFromGet->getMemBlock() );
	_UINT64 diffB = RC( _UINT64, pFrameFromGet->m_pfStop[BOT][1] ) - RC( _UINT64, pFrameFromGet->getMemBlock() );
	_UINT64 diffC = RC( _UINT64, pFrameFromGet->m_pfStop[BOT][2] ) - RC( _UINT64, pFrameFromGet->getMemBlock() );


	EXPECT_EQ( diff1, diffA ) 
		<< "Frame2's fstop did not change correctly.";
	EXPECT_EQ( diff2, diffB ) 
		<< "Frame2's fstop did not change correctly.";
	EXPECT_EQ( diff3, diffC ) 
		<< "Frame2's fstop did not change correctly.";
};

TEST_F(MockChunkManager, destroy_frame_test_fStop_2)
{
	GS::Utilities::Frame	*pFrame = 0, 
							*pFrame2 = 0,
							*pFrameFromGet = 0, 
							*pNull = 0,
							*pFrame3 = 0,
							*pFrame4 = 0;

	g_chunkman.m_pFramesInRelation[0];


	pFrame = g_chunkman.createFrame( CV8::FRAME001 );
	pFrame2 = g_chunkman.createFrame( CV8::FRAME002 );
	
	pFrame->setfStop(BOT);
	_BYTE * fStopO = pFrame->m_pfStop[BOT][0];

	pFrame2->setfStop(BOT);
	_BYTE * fStopP = pFrame2->m_pfStop[BOT][0];

	bool destroyed = g_chunkman.destroyFrame( CV8::FRAME001 );
	EXPECT_EQ( true, destroyed )  << "Frame 1 could not be destroyed";

	pFrameFromGet = g_chunkman.getFrame( CV8::FRAME002 );
	EXPECT_NE( fStopP, pFrameFromGet->m_pfStop[BOT][0] ) 
		<< "Frame2's fstop did not change";

	EXPECT_EQ( fStopO, pFrameFromGet->m_pfStop[BOT][0] ) 
		<< "Frame2's fstop did not change correctly.";
};


#endif
