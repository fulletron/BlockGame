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
	EXPECT_EQ( true, destroyed )  << "Test A Failed.";

	pFrameFromGet = m_man.getFrame( CV8("frame001") );
	EXPECT_EQ( 0, pFrameFromGet )  << "Test B Failed.";
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
	EXPECT_EQ( pFrame2, pFrameFromGet )  << "Test B Failed.";

	EXPECT_EQ( *pFrameMemBlock, *pFrameFromGet->m_pMemBlock ) << "Test C Failed.";
	EXPECT_EQ( 0, pFrame4->getName() ) << "Test D Failed.";
};



TEST(ChunkManager, initbale)
{
	GS::Utilities::ChunkManager g_man;
	g_man.init();
	GS::Utilities::Frame * pFrame = g_man.createFrame((_INT64)"trash000");
	GS::Utilities::GSVector<void *> test;
	test.init(pFrame, 12);
	char * a = new char[1];
	a[0] = 'a';
	char * b = new char[1];
	b[0] = 'b';
	char * c = new char[1];
	c[0] = 'c';
	char * d = new char[1];
	d[0] = 'd';


	test.add(a);
	test.add(b);
	test.remove((_UINT32)1);

	char t = *(char *)test.get(0);

	printf( "hello world! %c \n", t );

	GS::Utilities::GSHandler g_handler;
	g_handler.init(pFrame, 4);

	_UINT64 handle[4];

	//handle[0] = g_handler.insert(a);
	//handle[1] = g_handler.insert(b);
	//handle[2] = g_handler.insert(c);
	//handle[3] = g_handler.insert(d);

	//t = *(char *)g_handler.get(handle[2]);

	printf( "hello world! %c \n", t );

	//Assert.IsTrue(true);
};


#endif
