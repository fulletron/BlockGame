#include <iostream>
//#include <conio.h>

#include <boost\thread.hpp>
#include <Utilities\utilities.h>

int main()
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
	test.add(a);
	test.add(b);
	test.remove((_UINT32)1);

	char t = *(char *)test.get(0);

	printf( "hello world! %c \n", t );
	return 0;
}
