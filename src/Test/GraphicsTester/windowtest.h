#ifndef __WINDOWTEST_H_
#define __WINDOWTEST_H_

#ifndef TEST_ENABLED
#define TEST_ENABLED
#endif

#include <gtest/gtest.h>
#include <Graphics/window/window.h>
#include <Utilities/gserrorfunc.h>

// To use a test fixture, derive a class from testing::Test.
class MockWindowManager : public testing::Test 
{
protected:
	GS::Graphics::IWindow * m_pWindow;

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
	}

	// happens every test case
	virtual void TearDown() 
	{
	}
};

TEST_F(MockWindowManager, init_test)
{
	m_pWindow = new GS::Graphics::Window();

	EXPECT_TRUE(G_CheckForNoErrorOrSpecificError(1282));

	EXPECT_EQ(0, m_pWindow->init() );

	EXPECT_TRUE(G_CheckForNoErrorOrSpecificError(1280));

	EXPECT_TRUE( m_pWindow->isOpen() );

	EXPECT_FALSE(G_CheckForErrors());

	EXPECT_EQ(0, m_pWindow->shutdown());

	// KYLE :: WHY 1282 HERE?
	EXPECT_TRUE(G_CheckForNoErrorOrSpecificError(1282));

	EXPECT_FALSE( m_pWindow->isOpen() );

	delete m_pWindow;
};



#endif
