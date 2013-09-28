#ifndef __FRAMETEST_H_
#define __FRAMETEST_H_

#ifndef TEST_ENABLED
#define TEST_ENABLED
#endif

#include <gtest/gtest.h>
#include <Utilities/utilities.h>

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
		m_man.createFrame( CV8("frame001") );
		m_pBaseFrame = m_man.getFrame( CV8("frame001") );
	}

	// happens every test case
	virtual void TearDown() 
	{
		m_man.shutdown();
	}
};

TEST_F(MockFrameManager, setfStop_test_BOT)
{
	char *test, *test2, *test3, *test4, *test5 = 0;
	bool set = false;

	test = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, BOT ));
	set = m_pBaseFrame->setfStop(BOT);
	EXPECT_EQ( true, set ) 
		<< "Could not set the damn fStop.";
	EXPECT_EQ( test + 1, reinterpret_cast<char *>(m_pBaseFrame->m_pfStop[BOT][0]) ) 
		<< "fStop is in the wrong spot.";
	set = false;

	test2 = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, BOT ));
	set = m_pBaseFrame->setfStop(BOT);
	EXPECT_EQ( true, set ) 
		<< "Could not set the damn fStop 2.";
	EXPECT_EQ( test2 + 1, reinterpret_cast<char *>(m_pBaseFrame->m_pfStop[BOT][0]) ) 
		<< "fStop 2 is in the wrong spot.";
	set = false;

	test3 = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, BOT ));
	set = m_pBaseFrame->setfStop(BOT);
	EXPECT_EQ( true, set ) 
		<< "Could not set the damn fStop 3.";
	EXPECT_EQ( test3 + 1, reinterpret_cast<char *>(m_pBaseFrame->m_pfStop[BOT][0]) ) 
		<< "fStop 3 is in the wrong spot.";
	set = false;

	test4 = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, BOT ));
	set = m_pBaseFrame->setfStop(BOT);
	EXPECT_EQ( true, set ) << "Could not set the damn fStop 4.";
	EXPECT_EQ( test4 + 1, reinterpret_cast<char *>(m_pBaseFrame->m_pfStop[BOT][0]) )
	    << "fStop 4 is in the wrong spot.";	
	//set = false;

	set = true;
	test5 = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, BOT ));
	set = m_pBaseFrame->setfStop(BOT);
	EXPECT_EQ( false, set ) 
		<< "Was incorrectly able to set the fStop.";
};

TEST_F(MockFrameManager, setfStop_test_TOP)
{
	char *test, *test2, *test3, *test4, *test5 = 0;
	bool set = false;

	test = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, TOP ));
	set = m_pBaseFrame->setfStop( TOP );
	EXPECT_EQ( true, set ) 
		<< "Could not set the damn fStop.";
	EXPECT_EQ( test, reinterpret_cast<char *>(m_pBaseFrame->m_pfStop[TOP][0]) )
		<< "fStop is in the wrong spot.";
	set = false;

	test2 = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, TOP ));
	set = m_pBaseFrame->setfStop(TOP);
	EXPECT_EQ( true, set ) 
		<< "Could not set the damn fStop 2.";
	EXPECT_EQ( test2, reinterpret_cast<char *>(m_pBaseFrame->m_pfStop[TOP][0]) ) 
		<< "fStop 2 is in the wrong spot.";
	set = false;

	test3 = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, TOP ));
	set = m_pBaseFrame->setfStop(TOP);
	EXPECT_EQ( true, set ) 
		<< "Could not set the damn fStop 3.";
	EXPECT_EQ( test3, reinterpret_cast<char *>(m_pBaseFrame->m_pfStop[TOP][0]) ) 
		<< "fStop 3 is in the wrong spot.";
	set = false;

	test4 = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, TOP ));
	set = m_pBaseFrame->setfStop(TOP);
	EXPECT_EQ( true, set ) 
		<< "Could not set the damn fStop 4.";
	EXPECT_EQ( test4, reinterpret_cast<char *>(m_pBaseFrame->m_pfStop[TOP][0]) ) 
		<< "fStop 4 is in the wrong spot.";	
	//set = false;

	set = true;
	test5 = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, TOP ));
	set = m_pBaseFrame->setfStop(TOP);
	EXPECT_EQ( false, set ) 
		<< "Was incorrectly able to set the fStop.";
};

TEST_F(MockFrameManager, freefStop_test_BOT)
{	
	_CHAR *test[MAX_FSTOPS];
	bool unset = false;

	_BYTE* pStart[MAX_FSTOPS];

	for(int i = 0; i < MAX_FSTOPS; ++i)
	{
		test[i] = reinterpret_cast<char *>(m_pBaseFrame->allocate(1, BOT));
		pStart[i] = m_pBaseFrame->m_pCurrentLoc[BOT];
		m_pBaseFrame->setfStop(BOT);
	}

	for(int i = 0; i < MAX_FSTOPS; ++i)
	{
		unset = m_pBaseFrame->freefStop(BOT);
		EXPECT_EQ(true, unset) 
			<< "Could not unset the damn fstop " << i+1 << ".";

		EXPECT_EQ( pStart[MAX_FSTOPS-1-i], m_pBaseFrame->m_pCurrentLoc[BOT] )
			<< "Current location " << i+1 << " was not set properly.";
	}
};

TEST_F(MockFrameManager, allocate_test_BOT_basic)
{
	char * test = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, BOT ));
	EXPECT_EQ( reinterpret_cast<char *>(m_pBaseFrame->m_pMemBlock), test );

	char * test2 = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, BOT ));
	EXPECT_EQ( reinterpret_cast<char *>(m_pBaseFrame->m_pMemBlock) + 1, test2 );

	_UINT32 * test3 = reinterpret_cast<_UINT32 *>(m_pBaseFrame->allocate( 4, BOT ));
	EXPECT_EQ( reinterpret_cast<_BYTE *>(m_pBaseFrame->m_pMemBlock) + 4, reinterpret_cast<_BYTE *>(test3) );
}

TEST_F(MockFrameManager, allocate_test_TOP_basic)
{
	char * test = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, TOP ));
	EXPECT_EQ( reinterpret_cast<char *>(m_pBaseFrame->m_pMemBlock) + m_man.m_sizeOfChunk - 1, test );

	char * test2 = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, TOP ));
	EXPECT_EQ( reinterpret_cast<char *>(m_pBaseFrame->m_pMemBlock) - 2 + m_man.m_sizeOfChunk, test2 );

	_UINT32 * test3 = reinterpret_cast<_UINT32 *>(m_pBaseFrame->allocate( 4, TOP ));
	EXPECT_EQ( reinterpret_cast<_BYTE *>(m_pBaseFrame->m_pMemBlock) - 4 + m_man.m_sizeOfChunk, reinterpret_cast<_BYTE *>(test3) );
};

TEST_F(MockFrameManager, allocate_test_BOT_overflow)
{
	char * test = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, BOT ));
	EXPECT_EQ( reinterpret_cast<char *>(m_pBaseFrame->m_pMemBlock), test );

	char * test2 = reinterpret_cast<char *>(m_pBaseFrame->allocate( 2, BOT ));
	EXPECT_EQ( reinterpret_cast<char *>(m_pBaseFrame->m_pMemBlock) + 2, test2 );

	_UINT32 * test3 = reinterpret_cast<_UINT32 *>(m_pBaseFrame->allocate( 4, BOT ));
	EXPECT_EQ( reinterpret_cast<_BYTE *>(m_pBaseFrame->m_pMemBlock) + 4, reinterpret_cast<_BYTE *>(test3) );

	_UINT64 * test4 = reinterpret_cast<_UINT64 *>(m_pBaseFrame->allocate( 8, BOT ));
	EXPECT_EQ( reinterpret_cast<_BYTE *>(m_pBaseFrame->m_pMemBlock) + 8, reinterpret_cast<_BYTE *>(test4) );

	char * test8 = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, BOT ));
	EXPECT_EQ( 0, reinterpret_cast<_BYTE *>(test8) );
};

TEST_F(MockFrameManager, allocate_test_TOP_overflow)
{
	char * test = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, TOP ));
	EXPECT_EQ( reinterpret_cast<char *>(m_pBaseFrame->m_pMemBlock) + m_pBaseFrame->m_size - 1, test );

	char * test2 = reinterpret_cast<char *>(m_pBaseFrame->allocate( 2, TOP ));
	EXPECT_EQ( reinterpret_cast<char *>(m_pBaseFrame->m_pMemBlock) + m_pBaseFrame->m_size - 4, test2 );

	_UINT32 * test3 = reinterpret_cast<_UINT32 *>(m_pBaseFrame->allocate( 4, TOP ));
	EXPECT_EQ( reinterpret_cast<_BYTE *>(m_pBaseFrame->m_pMemBlock) + m_pBaseFrame->m_size - 8, reinterpret_cast<_BYTE *>(test3) );

	_UINT64 * test4 = reinterpret_cast<_UINT64 *>(m_pBaseFrame->allocate( 8, TOP ));
	EXPECT_EQ( reinterpret_cast<_BYTE *>(m_pBaseFrame->m_pMemBlock) + m_pBaseFrame->m_size - 16, reinterpret_cast<_BYTE *>(test4) );

	//char * test8 = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, TOP ));
	//EXPECT_EQ( 0, reinterpret_cast<_BYTE *>(test8) );
};

TEST_F(MockFrameManager, allocate_test_5)
{
	
};

TEST_F(MockFrameManager, isValid_test)
{
	
};

TEST_F(MockFrameManager, adjustment_test)
{
	
};

#endif
