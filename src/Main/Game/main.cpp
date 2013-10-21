#include <iostream>

#include <Graphics/graphics.h>
#include <boost/thread.hpp>
#include <Utilities/utilities.h>

int globalInt = 0;

int test()
{
	globalInt++;
	return 1;
}

int main()
{
	boost::thread thred(test);

	thred.start_thread();
	thred.join();

	printf("%d", globalInt);

	printf( "hello world! \n" );
	return 0;
}
