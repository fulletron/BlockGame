#ifndef __CHUNKPTRTEST_H_
#define __CHUNKPTRTEST_H_

#ifndef TEST_ENABLED
#define TEST_ENABLED
#endif

#include <gtest/gtest.h>
#include <Utilities/utilities.h>

extern 	GS::Utilities::ChunkManager 	g_chunkman;

// To use a test fixture, derive a class from testing::Test.
class MockChunkPtrManager : public testing::Test 
{
protected:
	GS::Utilities::Frame * 		m_pBaseFrame;
	static const int		TESTSIZECHUNK = 64;
	static const int		TESTNUMCHUNKS = 4;

	_INT32				m_initStatus;

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
		g_chunkman.init(TESTNUMCHUNKS,TESTSIZECHUNK);

		g_chunkman.createFrame( CV8::FRAME001 );
		g_chunkman.createFrame( CV8::FRAME002 );

		m_pBaseFrame = g_chunkman.getFrame( CV8::FRAME001 );
	}

	// happens every test case
	virtual void TearDown() 
	{
		g_chunkman.shutdown();
	}
};

TEST_F(MockChunkPtrManager, init_test)
{
	_TChunkPtr<_UINT64> pUint;
	pUint = g_chunkman.allocate( CV8::FRAME001, 8, TOP );

	pUint.dereference() = 100;
	EXPECT_EQ( 100, pUint.dereference() );
};

TEST_F(MockChunkPtrManager, move_test_small)
{
	_TChunkPtr<_UINT64> pUint;
	pUint = g_chunkman.allocate( CV8::FRAME002, 8, TOP );

	pUint.dereference() = 100;
	EXPECT_EQ( 100, pUint.dereference() );

	_UINT64 * pFullUintBefore = RC( _UINT64 *, pUint.pointer() );

	g_chunkman.destroyFrame( CV8::FRAME001 );

	pUint.dereference() = 100;
	EXPECT_EQ( 100, pUint.dereference() );

	_UINT64 * pFullUintAfter = RC( _UINT64 *, pUint.pointer() );

	EXPECT_NE( pFullUintBefore, pFullUintAfter );
};

TEST_F(MockChunkPtrManager, move_test)
{
	g_chunkman.createFrame( CV8::FRAME003 );
	g_chunkman.createFrame( CV8::FRAME004 );

	_TChunkPtr<_UINT64> pUint;
	pUint = g_chunkman.allocate( CV8::FRAME004, 8, TOP );

	pUint.dereference() = 100;
	EXPECT_EQ( 100, pUint.dereference() );

	_UINT64 * pFullUintBefore = RC( _UINT64 *, pUint.pointer() );

	g_chunkman.destroyFrame( CV8::FRAME001 );

	pUint.dereference() = 100;
	EXPECT_EQ( 100, pUint.dereference() );

	_UINT64 * pFullUintAfter = RC( _UINT64 *, pUint.pointer() );

	EXPECT_NE( pFullUintBefore, pFullUintAfter );
};

#endif
