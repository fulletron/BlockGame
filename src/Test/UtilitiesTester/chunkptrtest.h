#ifndef __CHUNKPTRTEST_H_
#define __CHUNKPTRTEST_H_

#ifndef TEST_ENABLED
#define TEST_ENABLED
#endif

#include <gtest/gtest.h>
#include <Utilities/utilities.h>

// To use a test fixture, derive a class from testing::Test.
class MockChunkPtrManager : public testing::Test 
{
protected:
	GS::Utilities::ChunkManager 	m_man;
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
		m_man.init(TESTNUMCHUNKS,TESTSIZECHUNK);

		m_man.createFrame( CV8("frame001") );
		m_man.createFrame( CV8("frame002") );

		m_pBaseFrame = m_man.getFrame( CV8("frame001") );
	}

	// happens every test case
	virtual void TearDown() 
	{
		m_man.shutdown();
	}
};

TEST_F(MockChunkPtrManager, init_test)
{
	_TChunkPtr<_UINT64> pUint;
	pUint = m_man.allocate( CV8("frame001"), 8, TOP );

	pUint.dereference() = 100;
	EXPECT_EQ( 100, pUint.dereference() );
};

TEST_F(MockChunkPtrManager, move_test_small)
{
	_TChunkPtr<_UINT64> pUint;
	pUint = m_man.allocate( CV8("frame002"), 8, TOP );

	pUint.dereference() = 100;
	EXPECT_EQ( 100, pUint.dereference() );

	_UINT64 * pFullUintBefore = RC( _UINT64 *, pUint.m_pData );

	m_man.destroyFrame( CV8("frame001") );

	pUint.dereference() = 100;
	EXPECT_EQ( 100, pUint.dereference() );

	_UINT64 * pFullUintAfter = RC( _UINT64 *, pUint.m_pData );

	EXPECT_NE( pFullUintBefore, pFullUintAfter );
};

TEST_F(MockChunkPtrManager, move_test)
{
	m_man.createFrame( CV8("frame003") );
	m_man.createFrame( CV8("frame004") );

	_TChunkPtr<_UINT64> pUint;
	pUint = m_man.allocate( CV8("frame004"), 8, TOP );

	pUint.dereference() = 100;
	EXPECT_EQ( 100, pUint.dereference() );

	_UINT64 * pFullUintBefore = RC( _UINT64 *, pUint.m_pData );

	m_man.destroyFrame( CV8("frame001") );

	pUint.dereference() = 100;
	EXPECT_EQ( 100, pUint.dereference() );

	_UINT64 * pFullUintAfter = RC( _UINT64 *, pUint.m_pData );

	EXPECT_NE( pFullUintBefore, pFullUintAfter );
};

#endif
