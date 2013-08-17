#ifndef __UTILITIES_H_
#define __UTILITIES_H_

//int utest_function();

#define LABEL_MAX 30
#define PRINT_BUFFER_LENGTH 1000

#ifdef _WIN32
#include <windows.h>  // for all the VK_ constants.
#endif
#include <stdio.h>    // for sprintf
//#include <string.h> // Use this if not using Windows.h for string stuff.

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

class CStatPage;

class CStatEntry
{
public:
	CStatEntry(CStatPage *a_pPage, char * a_label, int a_priority);
	~CStatEntry();
	char* getLabel();
	void setLabel(char * a_label);
	int getPriority();
	virtual int print(char * a_outputBuffer, int a_maxLength);
	virtual void deltaValue( int a_delta );
	virtual void setValue( char * a_name );
	CStatEntry *		m_pNextEntry;
	CStatEntry *		m_pPreviousEntry;
	int					m_priority;
	char				m_label[LABEL_MAX];
};

class CStatPage 
{
public:
	CStatPage( char * a_label, int a_priority );
	~CStatPage();
	char* getLabel();
	void setLabel( char* a_label );
	CStatEntry* getTopEntry();
	int getPriority();
	void addEntry( CStatEntry * a_pEntry );
	void print( char* a_outputBuffer, int a_maxViewedLines );

	CStatPage *			m_pNextPage;
	CStatPage *			m_pPreviousPage;
	CStatEntry *		m_pTopEntry;
	CStatEntry *		m_pCurrentEntry;
	CStatEntry *		m_pTopViewedEntry;
	int					m_priority;
	char				m_label[LABEL_MAX];
};

class CStatBase 
{
public:
	static void init();
	static void checkInput( unsigned char * a_keyboardState );
	static void addPage( CStatPage * a_pPage );
	static void print(char * a_outputBuffer);
	// CStatPage wants to see some of these
	static CStatPage *	m_pCurrentPage;
	static CStatPage *	m_pFirstPage;
	static int			m_maxViewedLines;
	static bool			m_statsVisible;
	static bool			m_statsEditable;
	static char			m_entryBuffer[LABEL_MAX];
	static int			m_frameAccumulator;
	static bool			m_debounceOnOff;
	static bool			m_debounceEditView;

};

class CStatInt : public CStatEntry
{
public:
	CStatInt( CStatPage * a_pPage, char * a_title, int a_priority, int a_value );
	int print( char * a_outputBuffer, int a_maxLength );
	void setValue( int a_value );
	void setValue( char* a_name );
	int getValue();
	void setRange( int a_min, int a_max );
	void clearRange();
	void deltaValue( int a_delta );

protected:
	int				m_value;
	bool			m_rangeUsed;
	int				m_min;
	int				m_max;
};


class CStatIntPtr : public CStatEntry
{
public:
	CStatIntPtr( CStatPage * a_pPage, char* a_title, int a_priority, int * a_pValue );
	int print( char * a_outputBuffer, int a_maxLength );
	void setValue( int * a_pValue );
	void setValue( char* a_name );
	int * getValue();
	void setRange( int a_min, int a_max );
	void clearRange();
	void deltaValue( int a_delta );

protected:
	int * m_pValue;
	bool m_rangeUsed;
	int m_min;
	int m_max;

};

class CStatFloat : public CStatEntry
{
public:
	CStatFloat( CStatPage * a_pPage, char* a_title, int a_priority, float a_value );
	int print( char * a_outputBuffer, int a_maxLength );
	void setValue( float a_value );
	void setValue( char* a_name );
	float getValue();
	void setRange( float a_min, float a_max );
	void clearRange();
	void deltaValue( int a_delta );

protected:
	float m_value;
	bool m_rangeUsed;
	float m_min;
	float m_max;
};

class CStatFloatPtr : public CStatEntry
{
public:
	CStatFloatPtr( CStatPage * a_pPage, char* a_title, int a_priority, float * a_pValue );
	int print( char * a_outputBuffer, int a_maxLength );
	void setValue( float * a_pValue );
	void setValue( char* a_name );
	float * getValue();
	void setRange( float a_min, float a_max );
	void clearRange();
	void deltaValue( int a_delta );

protected:
	float * m_pValue;
	bool m_rangeUsed;
	float m_min;
	float m_max;
};


#endif