#ifndef __WINDOWTEST_H_
#define __WINDOWTEST_H_

#ifndef TEST_ENABLED
#define TEST_ENABLED
#endif

#include <gtest/gtest.h>
#include <Graphics/window.h>
#include <Utilities/glfwerrorfunc.h>

// To use a test fixture, derive a class from testing::Test.
class MockWindowManager : public testing::Test 
{
protected:
	GS::Graphics::Window m_window;

	bool m_errors;
		//GS::Utilities::ChunkManager m_man;	

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
		m_errors = false;
		//m_man.init(4,16);
	}

	// happens every test case
	virtual void TearDown() 
	{
		//m_man.shutdown();
	}
};

TEST_F(MockWindowManager, init_test)
{
	EXPECT_EQ(0, m_window.init() );

	m_errors = GS::Utilities::ErrorCallbacks::errorsExist();
	//EXPECT_EQ( false, m_errors ); // bizarre -Wconversion-null warning
	EXPECT_FALSE( m_errors );

	EXPECT_TRUE( m_window.isOpen() );

	m_window.shutdown();

	m_errors = GS::Utilities::ErrorCallbacks::errorsExist();
	EXPECT_FALSE( m_errors );
	EXPECT_FALSE( m_window.isOpen() );
};



#endif
