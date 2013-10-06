#ifndef __GSHANDLERTEST_H_
#define __GSHANDLERTEST_H_

#ifndef TEST_ENABLED
#define TEST_ENABLED
#endif

#include <gtest/gtest.h>
#include <Utilities/utilities.h>

class TestC : public GS::Utilities::GSObject
{
public:
	_UINT32 test;

	_INT32 handleMsg( const GS::Utilities::GSMsg & a_msg )
	{
		return 0;
	}
};

class MockObject : public GS::Utilities::GSObject
{
protected:
	//_UINT32 m_data;
public:	
	MockObject()
	{
		m_data = 2000;
	}
	~MockObject()
	{
	}

	_UINT32 m_data;
	_INT32 handleMsg( const GS::Utilities::GSMsg & a_msg )
	{
		return 0;
	}

	void setData( const _UINT32 a_data ){m_data = a_data;}
	_UINT32 getData(){ return m_data; }
};

// To use a test fixture, derive a class from testing::Test.
class MockHandlerManager : public testing::Test 
{
protected:
	GS::Utilities::ChunkManager 	m_man;
	GS::Utilities::Frame * 		m_pBaseFrame;
	static const int		TESTSIZECHUNK = 64;
	static const int		TESTNUMCHUNKS = 4;
	GS::Utilities::GSHandler	m_handler;

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
		m_initStatus = 99;
		m_man.init(TESTNUMCHUNKS,TESTSIZECHUNK);

		m_man.createFrame( CV8("frame001") );
		m_man.createFrame( CV8("frame002") );
		m_man.createFrame( CV8("frame003") );
		m_man.createFrame( CV8("frame004") );

		m_pBaseFrame = m_man.getFrame( CV8("frame001") );

		m_initStatus = m_handler.init( m_pBaseFrame, 4 );

		m_man.addInvestor(&m_handler);
	}

	GS::Utilities::_GSKeyPair createHandledMockObject( const _UINT64 a_ownerFrame, const _UINT32 a_data )
	{
		GS::Utilities::Frame * pFrame = m_man.getFrame( a_ownerFrame );

		int size1 = sizeof(TestC);

		int size = sizeof(MockObject);

		_BYTE * pObj = pFrame->allocate( size, BOT );
		MockObject * testObj = new (pObj) MockObject();

		//MockObject * testObj = RC(MockObject*, pObj);

		testObj->setData( a_data );


		void * test2 = testObj;
		void * test3 = &(testObj->m_data);

		/*
		_UINT32 test = *RC(_UINT32*,pObj);

		test;
		a_data;
		*/
		int tust = 0;

		return m_handler.insert( testObj, a_ownerFrame );
	}

	// happens every test case
	virtual void TearDown() 
	{
		m_handler.shutdown();
		m_man.shutdown();
	}
};

TEST_F(MockHandlerManager, init_test)
{
	EXPECT_EQ( 0, m_initStatus );
};

TEST_F(MockHandlerManager, insert_test)
{
	MockObject * testObj = RC(MockObject*, m_man.getFrame( CV8("frame003") )->allocate( sizeof(MockObject), BOT ));
	
	testObj->setData( 1 );

	GS::Utilities::_GSKeyPair testKeyPair1 = m_handler.insert( testObj, CV8("frame003") );

	EXPECT_EQ( 0, testKeyPair1.key );
	EXPECT_EQ( CV8("frame003"), testKeyPair1.ownerFrameName );


	GS::Utilities::_GSKeyPair testKeyPair2 = createHandledMockObject( CV8("frame004"), 2 );

	EXPECT_EQ( 1, testKeyPair2.key );
	EXPECT_EQ( CV8("frame004"), testKeyPair2.ownerFrameName );
};


TEST_F(MockHandlerManager, get_test)
{
	GS::Utilities::_GSKeyPair testKeyPair = createHandledMockObject( CV8("frame003"), 1 );
	GS::Utilities::GSObject * pTestObj = m_handler.get( testKeyPair.key );

	MockObject * pMO = static_cast<MockObject *>(pTestObj);

	EXPECT_EQ( 1, pMO->getData() );
};

TEST_F(MockHandlerManager, remove_test)
{
	GS::Utilities::_GSKeyPair testKeyPair = createHandledMockObject( CV8("frame003"), 1 );

	m_handler.remove( testKeyPair.key );

	GS::Utilities::GSObject * pTestObj = m_handler.get( testKeyPair.key );
	EXPECT_EQ( 0, pTestObj );
};

TEST_F(MockHandlerManager, ins_rem_ins_test)
{
	GS::Utilities::_GSKeyPair testKeyPair(0,0), firstKey(0,0);
       
	firstKey = createHandledMockObject( CV8("frame003"), 1 );
	m_handler.remove( firstKey.key );
	testKeyPair = createHandledMockObject( CV8("frame003"), 2 );

	EXPECT_EQ( firstKey.key, testKeyPair.key );

	GS::Utilities::GSObject * pTestObj = m_handler.get( testKeyPair.key );
	MockObject * pMO = static_cast<MockObject *>(pTestObj);

	EXPECT_EQ( 2, pMO->getData() );
};

TEST_F(MockHandlerManager, readjust_test)
{
	GS::Utilities::_GSKeyPair key(0,0);
	GS::Utilities::GSObject * pTestObj, *pTestObj2 = 0;
	GS::Utilities::Frame * pFrame = 0;
	MockObject * pMO = 0;

	key = createHandledMockObject( CV8("frame004"), 3 );

	pFrame = m_man.getFrame( CV8("frame004") );

	_INT64 frame1 = CV8("frame001");
	_INT64 frame2 = CV8("frame002");
	_INT64 frame3 = CV8("frame003");
	_INT64 frame4 = CV8("frame004");

	void * test = pFrame->m_pMemBlock;
	pTestObj = m_handler.get( key.key );
	pMO = static_cast<MockObject *>(pTestObj);

	EXPECT_EQ( 3, pMO->getData() );

	//EXPECT_EQ(3, *);

	bool destroyed = m_man.destroyFrame( CV8("frame002") );
	EXPECT_EQ( true, destroyed )  << "FRAME DESTRUCTION FAILED.";

	pTestObj2 = m_handler.get( key.key );

	EXPECT_NE(pTestObj, pTestObj2);

	pMO = static_cast<MockObject *>(pTestObj2);

	EXPECT_EQ( 3, pMO->getData() );
};


#endif
