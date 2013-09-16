#include <Utilities/utilities.h>
#include <gtest/gtest.h>

TEST(ChunkManager, init)
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

	handle[0] = g_handler.insert(a);
	handle[1] = g_handler.insert(b);
	handle[2] = g_handler.insert(c);
	handle[3] = g_handler.insert(d);

	t = *(char *)g_handler.get(handle[2]);

	printf( "hello world! %c \n", t );

	//Assert.IsTrue(true);
};
