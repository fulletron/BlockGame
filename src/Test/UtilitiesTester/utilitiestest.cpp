#include <iostream>
#include <gtest/gtest.h>

#include "chunkmanagertest.h"
#include "frametest.h"
#include "gshandlertest.h"
#include "gsvectortest.h"

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
