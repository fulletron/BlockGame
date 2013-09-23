#ifndef __CHUNKMANTEST_H_
#define __CHUNKMANTEST_H_

#ifndef TEST_ENABLED
#define TEST_ENABLED
#endif

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

#endif
