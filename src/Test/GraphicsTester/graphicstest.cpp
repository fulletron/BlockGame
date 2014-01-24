#include <iostream>
#include <gtest/gtest.h>

#include "Utilities/chunkmanager.h"
#include "graphicstest.h"

GS::Utilities::ChunkManager g_chunkman;

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
