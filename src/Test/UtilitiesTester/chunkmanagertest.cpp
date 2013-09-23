#define TEST_ENABLED
#include <gtest/gtest.h>
#include <Utilities/utilities.h>
#include "chunkmanagertest.h"

TEST(ChunkManager, init_test)
{
	GS::Utilities::ChunkManager man;
	_UINT32 ret = man.init(4,16);
	EXPECT_EQ( ret, 0 );
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

	EXPECT_EQ( reinterpret_cast<GS::Utilities::Frame *>(0), pFrame );
};

TEST_F(MockChunkManager, get_frame_test)
{
	GS::Utilities::Frame * pFrame = m_man.createFrame( CV8("frame001") );

	GS::Utilities::Frame * pFrameFromGet = m_man.getFrame( CV8("frame001") );

	EXPECT_EQ( pFrame, pFrameFromGet );

	pFrame = m_man.createFrame( CV8("frame001") );

	m_man.createFrame( CV8("frame001") );

	pFrameFromGet = m_man.getFrame( CV8("frame001") );

	EXPECT_EQ( pFrame, pFrameFromGet );

	m_man.destroyFrame( CV8("frame001") );

	pFrameFromGet = m_man.getFrame( CV8("frame001") );

	EXPECT_EQ( 0, pFrameFromGet );
};

TEST_F(MockChunkManager, destroy_frame_test)
{

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
