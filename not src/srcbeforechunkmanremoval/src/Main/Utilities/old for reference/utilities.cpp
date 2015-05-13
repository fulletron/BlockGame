#include "utilities.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <stdlib.h>
#include <string.h>
#endif

namespace GS {
namespace Utilities {

CStatPage * CStatBase::m_pCurrentPage;
CStatPage * CStatBase::m_pFirstPage;
int			CStatBase::m_maxViewedLines;
bool		CStatBase::m_statsVisible;
bool		CStatBase::m_statsEditable;
char		CStatBase::m_entryBuffer[LABEL_MAX]; // used for editing a value.
int			CStatBase::m_frameAccumulator;
bool		CStatBase::m_debounceOnOff = FALSE; // debounce on/off
bool		CStatBase::m_debounceEditView = FALSE; // debounce edit/view
bool		CStatBase::m_needsInit = TRUE; // debounce edit/view


// ================================
CStatEntry::CStatEntry(CStatPage * a_pPage, char * a_label, int a_priority )
{
	setLabel(a_label);
	m_priority = a_priority;
	m_pPreviousEntry = NULL;
	m_pNextEntry = NULL;

	a_pPage->addEntry(this);
}

CStatEntry::~CStatEntry()
{

}

char * CStatEntry::getLabel()
{
	return m_label;
}

void CStatEntry::setLabel( char * a_label )
{
	strncpy( m_label, a_label, LABEL_MAX - 1 );
	m_label[LABEL_MAX - 1] = NULL;
}

int CStatEntry::getPriority()
{
	return m_priority;
}

int CStatEntry::print(char * a_outputBuffer, int a_maxLength )
{
	return 0;
}

void CStatEntry::deltaValue(int a_value)
{
}

void CStatEntry::setValue( char * a_name )
{
}

//=============================================


//=============================================

CStatPage::CStatPage( char * a_label, int a_priority )
{
	setLabel( a_label );
	m_priority = a_priority;
	m_pTopEntry = NULL;
	m_pCurrentEntry = NULL;
	m_pTopViewedEntry = NULL;
	m_pPreviousPage = NULL;
	m_pNextPage = NULL;

	CStatBase::addPage(this);
}

CStatPage::~CStatPage(){}

char * CStatPage::getLabel()
{
	return m_label;
}

void CStatPage::setLabel( char* a_label )
{
	strncpy( m_label, a_label, LABEL_MAX - 1 );
	m_label[LABEL_MAX - 1] = NULL;
}


int CStatPage::getPriority()
{
	return m_priority;
}

CStatEntry * CStatPage::getTopEntry()
{
	return m_pTopEntry;
}

void CStatPage::addEntry( CStatEntry * a_pEntry )
{
	if( m_pTopEntry == NULL )
		m_pTopEntry = m_pCurrentEntry = m_pTopViewedEntry = a_pEntry;
	else if( m_pTopEntry->m_priority > a_pEntry->m_priority )
	{
		m_pTopEntry->m_pPreviousEntry = a_pEntry;
		a_pEntry->m_pNextEntry = m_pTopEntry;
	}
	else
	{
		CStatEntry * looper = m_pTopEntry;
		bool done = FALSE;
		while( looper && !done )
		{
			if( (looper->m_priority > a_pEntry->m_priority) 
				|| (looper->m_pNextEntry == NULL) )
			{
				a_pEntry->m_pNextEntry = looper->m_pNextEntry;
				a_pEntry->m_pPreviousEntry = looper;
				looper->m_pNextEntry = a_pEntry;

				if( a_pEntry->m_pNextEntry != NULL )
					a_pEntry->m_pNextEntry->m_pPreviousEntry = a_pEntry;

				done = TRUE;
			}
			looper = looper->m_pNextEntry;
		}
	}
}

void CStatPage::print( char* a_outputBuffer, int a_maxViewedLines )
{
	CStatEntry * looper;
	int lineSum = 0;
	int lineCurrent = 0;
	char printBuffer[PRINT_BUFFER_LENGTH];

	strcpy( a_outputBuffer, m_label );
	strcat( a_outputBuffer, "\n" );

	for( looper = m_pTopEntry; looper != NULL && lineSum < a_maxViewedLines; looper = looper->m_pNextEntry )
	{
		strcat( a_outputBuffer, looper->getLabel() );
		for( int i = strlen(looper->getLabel()); i < LABEL_MAX; i++ )
			strcat(a_outputBuffer, " " );
		
		if( looper == m_pCurrentEntry && CStatBase::m_statsEditable)
			strcat( a_outputBuffer, ">" );
		else
			strcat( a_outputBuffer, " " );

		lineCurrent = looper->print( printBuffer, PRINT_BUFFER_LENGTH );
		if( lineCurrent )
		{
			strcat( a_outputBuffer, printBuffer );
			strcat( a_outputBuffer, "\n" );

			lineSum += lineCurrent;
		}
		else
		{
			strcat( a_outputBuffer, "\n" );
			lineSum++;
		}
	}
}

//==============================================

void CStatBase::init()
{
	m_needsInit = FALSE;
	m_pCurrentPage = NULL;
	m_maxViewedLines = 20;
	m_statsVisible = TRUE;
	m_statsEditable = FALSE;
}

void CStatBase::checkInput( unsigned char * a_keyboardState )
{
	// Check for on/off. (f12)
	if(a_keyboardState[VK_F12] && !m_debounceOnOff)
	{
		m_statsVisible = !m_statsVisible;
		m_debounceOnOff = TRUE;
	}
	if(!a_keyboardState[VK_F12])
	{
		m_debounceOnOff = FALSE;
	}
	if(!a_keyboardState[VK_F11])
	{
		m_debounceEditView = FALSE;
	}
	// Make sure we have something worth processing.
	if(m_statsVisible)
	{
		int zoomFactor = 1;

		if(a_keyboardState[VK_SHIFT])
			zoomFactor *= 10;
		if(a_keyboardState[VK_CONTROL])
			zoomFactor *= 100;

		m_frameAccumulator+= zoomFactor; // should actually scale _frameAccumulator based on time this frame

		// If no keys are down, set accumulator to 20 so next key hit is processed immediately.
		bool anyKeyHit = FALSE;
		for(int i = 0; i < 256; i++)
		{
			if(a_keyboardState[i])
			{
				anyKeyHit = TRUE;
				break;
			}
		}
		if(!anyKeyHit)
		{
			m_frameAccumulator = 20;
			return;
		}
		if(m_frameAccumulator < 20)
		{
			return;
		}
		// Okay, we're processing a key so reset the accumulator.
		m_frameAccumulator = 0;

		// Check for view/edit. (f11)
		if(a_keyboardState[VK_F11] && !m_debounceEditView)
		{
			m_statsEditable = !m_statsEditable;
			m_debounceEditView = TRUE;
		}
		if(m_statsEditable)
		{
			int iDelta = 0;
			if(0) // If not in keyboard data entry mode and <return>
			{
				// Put into keyboard data entry mode.
				// clear data entry buffer.
			}
			if(0) // in keyboard data entry mode
			{
				if(0) // return
				{
					// terminate keyboard data entry mode and assign value.
				}
				else
				{
					// append to edited buffer.
				}
			}
			// Check for incriment/decriment. (+,-)
			if(a_keyboardState[VK_SUBTRACT] && m_pCurrentPage&& m_pCurrentPage->m_pCurrentEntry)
			{
				iDelta = - zoomFactor;
				m_pCurrentPage->m_pCurrentEntry->deltaValue(iDelta);
			}
			if(a_keyboardState[VK_ADD] && m_pCurrentPage&& m_pCurrentPage->m_pCurrentEntry)
			{
				iDelta = zoomFactor;
				m_pCurrentPage->m_pCurrentEntry->deltaValue(iDelta);
			}
			// Check for page selection (page up, page down)
			if(a_keyboardState[VK_PRIOR] && m_pCurrentPage)
			{
				// Go to previous page.
				if(m_pCurrentPage->m_pPreviousPage)
					m_pCurrentPage = m_pCurrentPage->m_pPreviousPage;
			}
			if(a_keyboardState[VK_NEXT] && m_pCurrentPage)
			{
				// Go to next page.
				if(m_pCurrentPage->m_pNextPage)
					m_pCurrentPage = m_pCurrentPage->m_pNextPage;
			}
			// Check for entry selection (up, down)
			if(a_keyboardState[VK_NUMPAD8] || a_keyboardState[VK_UP])
			{
				// Move to previous entry on current page.
				if(m_pCurrentPage->m_pCurrentEntry && m_pCurrentPage->m_pCurrentEntry->m_pPreviousEntry)
					m_pCurrentPage->m_pCurrentEntry = m_pCurrentPage->m_pCurrentEntry->m_pPreviousEntry;
			}
			if(a_keyboardState[VK_NUMPAD2] || a_keyboardState[VK_DOWN])
			{
				// Move to next entry on current page.
				if(m_pCurrentPage->m_pCurrentEntry && m_pCurrentPage->m_pCurrentEntry->m_pNextEntry)
					m_pCurrentPage->m_pCurrentEntry = m_pCurrentPage->m_pCurrentEntry->m_pNextEntry;
			}
		}
	}
}

void CStatBase::addPage(CStatPage * a_pPage)
{
	if(m_needsInit)
		init();
	if( m_pFirstPage == NULL )
		m_pFirstPage = m_pCurrentPage = a_pPage;
	else if( m_pFirstPage->m_priority > a_pPage->m_priority )
	{
		m_pFirstPage->m_pPreviousPage = a_pPage;
		a_pPage->m_pNextPage = m_pFirstPage;
	}
	else
	{
		CStatPage * looper = m_pFirstPage;
		bool done = FALSE;
		while(looper && !done)
		{
			if((looper->m_priority > a_pPage->m_priority) || (looper->m_pNextPage == NULL))
			{
				// Add after this entry.
				a_pPage->m_pNextPage = looper->m_pNextPage;
				a_pPage->m_pPreviousPage = looper;
				// Adjust looper to point at entry.
				looper->m_pNextPage = a_pPage;
				// If one exists, fix the entry following the new one.
				if(a_pPage->m_pNextPage != NULL)
				{
					a_pPage->m_pNextPage->m_pPreviousPage = a_pPage;
				}
				done = TRUE;
			}
			looper = looper->m_pNextPage;
		}
	}
}

void CStatBase::print( char* a_outputBuffer )
{
	if( m_pCurrentPage && m_statsVisible )
		m_pCurrentPage->print(a_outputBuffer, m_maxViewedLines);
}

CStatInt::CStatInt( CStatPage * a_pPage, char * a_title, int a_priority, int a_value )
: CStatEntry(a_pPage, a_title, a_priority)
{
	m_value = a_value;
	m_min = m_max = 0;
	m_rangeUsed = FALSE;
}

int CStatInt::print( char * a_outputBuffer, int a_maxLength )
{
	sprintf( a_outputBuffer, "%d", m_value );
	return 1;
}

void CStatInt::setValue( int a_value )
{
	m_value = a_value;
}

void CStatInt::setValue( char* a_name ) 
{
	m_value = atoi(a_name);
}

int CStatInt::getValue()
{
	return m_value;
}

void CStatInt::setRange( int a_min, int a_max )
{
	if( a_min > a_max )
	{
		m_min = a_max;
		m_max = a_min;
	}
	else
	{
		m_min = a_min;
		m_max = a_max;
	}
	m_rangeUsed = TRUE;
	deltaValue(0);
}

void CStatInt::clearRange()
{
	m_rangeUsed = 0;
}

void CStatInt::deltaValue( int a_delta )
{
	m_value += a_delta;
	if( m_rangeUsed )
		if( m_value < m_min )
			m_value = m_min;
		else if( m_value > m_max )
			m_value = m_max;
}

CStatIntPtr::CStatIntPtr(CStatPage * a_pPage, char * a_title, int a_priority, int * a_pValue)
: CStatEntry(a_pPage, a_title, a_priority)
{
	m_pValue = a_pValue;
	m_min = m_max = 0;
	m_rangeUsed = FALSE;
}

int CStatIntPtr::print(char * a_outputBuffer, int a_maxLength)
{
	sprintf(a_outputBuffer,"%d", *m_pValue);
	return 1; // We print one line of data into the buffer.
}

void CStatIntPtr::setValue(int *a_pValue)
{
	m_pValue = a_pValue;
}

void CStatIntPtr::setValue(char * a_name)
{
	*m_pValue = atoi(a_name);
}

int *CStatIntPtr::getValue(void)
{
	return m_pValue;
}

void CStatIntPtr::setRange(int a_min, int a_max)
{
	if(a_min > a_max)
	{
		m_min = a_max;
		m_max = a_min;
	}
	else
	{
		m_min = a_min;
		m_max = a_max;
	}
	m_rangeUsed = TRUE;
	deltaValue(0); // Force value into range.
}

void CStatIntPtr::clearRange(void)
{
	m_rangeUsed = 0;
}

// Scale delta for non-integer variables.
void CStatIntPtr::deltaValue(int delta)
{
	*m_pValue += delta;
	if(m_rangeUsed)
	{
		if(*m_pValue < m_min)
		{
			*m_pValue = m_min;
		}
		else if(*m_pValue > m_max)
		{
			*m_pValue = m_max;
		}
	}
}

//----------------------------------
// Float stat class.
//----------------------------------

CStatFloat::CStatFloat(CStatPage * a_pPage, char * a_title, int a_priority, float a_value)
: CStatEntry(a_pPage, a_title, a_priority)
{
	m_value = a_value;
	m_min = m_max = 0;
	m_rangeUsed = FALSE;
}

int CStatFloat::print(char * a_outputBuffer, int a_maxLength)
{
	sprintf(a_outputBuffer,"%.5f", m_value);
	return 1; // We print one line of data into the buffer.
}

void CStatFloat::setValue(float a_value)
{
	m_value = a_value;
}

void CStatFloat::setValue(char * a_name)
{
	m_value = (float)atof(a_name);
}

float CStatFloat::getValue(void)
{
	return m_value;
}

void CStatFloat::setRange(float a_min, float a_max)
{
	if(a_min > a_max)
	{
		m_min = a_max;
		m_max = a_min;
	}
	else
	{
		m_min = a_min;
		m_max = a_max;
	}
	m_rangeUsed = TRUE;
	deltaValue(0); // Force value into range.
}

void CStatFloat::clearRange(void)
{
	m_rangeUsed = 0;
}

// Scale delta for non-integer variables.
void CStatFloat::deltaValue(int a_delta)
{
	m_value += a_delta/1000.0f;
	if(m_rangeUsed)
	{
		if(m_value < m_min)
		{
			m_value = m_min;
		}
		else if(m_value > m_max)
		{
			m_value = m_max;
		}
	}
}

//----------------------------------
// float pointer stat class.
//----------------------------------

CStatFloatPtr::CStatFloatPtr(CStatPage *a_pPage, char * a_title, int a_priority, float *a_pValue)
: CStatEntry(a_pPage, a_title, a_priority)
{
	m_pValue = a_pValue;
	m_min = m_max = 0;
	m_rangeUsed = FALSE;
}

int CStatFloatPtr::print(char * a_outputBuffer, int a_maxLength)
{
	sprintf(a_outputBuffer,"%.5f", *m_pValue);
	return 1; // We print one line of data into the buffer.
}

void CStatFloatPtr::setValue(float * a_value)
{
	m_pValue = a_value;
}

void CStatFloatPtr::setValue(char * a_name)
{
	*m_pValue = (float)atoi(a_name);
}

float *CStatFloatPtr::getValue(void)
{
	return m_pValue;
}

void CStatFloatPtr::setRange(float a_min, float a_max)
{
	if(a_min > a_max)
	{
		m_min = a_max;
		m_max = a_min;
	}
	else
	{
		m_min = a_min;
		m_max = a_max;
	}
	m_rangeUsed = TRUE;
	deltaValue(0); // Force value into range.
}

void CStatFloatPtr::clearRange(void)
{
	m_rangeUsed = 0;
}

// Scale delta for non-integer variables.
void CStatFloatPtr::deltaValue(int a_delta)
{
	*m_pValue += a_delta/1000.0f;
	if(m_rangeUsed)
	{
		if(*m_pValue < m_min)
		{
			*m_pValue = m_min;
		}
		else if(*m_pValue > m_max)
		{
			*m_pValue = m_max;
		}
	}
}

};
};