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
		m_man.init(4,TESTSIZECHUNK);
		m_man.createFrame( CV8("frame001") );
		m_pBaseFrame = m_man.getFrame( CV8("frame001") );
	}

	// happens every test case
	virtual void TearDown() 
	{
		m_man.shutdown();
	}
};

TEST_F(MockFrameManager, setfStop_test)
{
	
};

TEST_F(MockFrameManager, freefStop_test)
{
	
};

TEST_F(MockFrameManager, allocate_test)
{
	char * test = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, GS::Utilities::Frame::PLACE::BOT ));
	//*test = 'a';

	EXPECT_EQ( reinterpret_cast<char *>(m_pBaseFrame->m_pMemBlock), test );

	char * test2 = reinterpret_cast<char *>(m_pBaseFrame->allocate( 1, GS::Utilities::Frame::PLACE::BOT ));
	//*test = 'a';

	EXPECT_EQ( reinterpret_cast<char *>(m_pBaseFrame->m_pMemBlock) + 1, test2 );

	_UINT32 * test3 = reinterpret_cast<_UINT32 *>(m_pBaseFrame->allocate( 4, GS::Utilities::Frame::PLACE::BOT ));
	//*test = 'a';

	EXPECT_EQ( reinterpret_cast<_BYTE *>(m_pBaseFrame->m_pMemBlock) + 4, reinterpret_cast<_BYTE *>(test3) );
}

TEST_F(MockFrameManager, allocate_test_2)
{
	
};

TEST_F(MockFrameManager, allocate_test_3)
{
	
};

TEST_F(MockFrameManager, allocate_test_4)
{
	
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
