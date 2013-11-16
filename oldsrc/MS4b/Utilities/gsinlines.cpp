#include "gsinlines.h"

namespace GS {
namespace UtilitiesNS {

	static char * MASTERBUFFER = 0;

	_CHAR * itoa10_prebuf(int val)
	{
		if(!MASTERBUFFER)
			MASTERBUFFER = new char[256];

		itoa10(val, MASTERBUFFER);

		return MASTERBUFFER;
	}

	int itoa10(int val, _CHAR* buf)
	{
		const unsigned int radix = 10;

		_CHAR* p;
		unsigned int a;        //every digit
		int len;
		_CHAR* b;            //start of the digit char
		_CHAR temp;
		unsigned int u;

		p = buf;

		if (val < 0)
		{
			*p++ = '-';
			val = 0 - val;
		}
		u = (unsigned int)val;

		b = p;

		do
		{
			a = u % radix;
			u /= radix;

			*p++ = a + '0';

		} while (u > 0);

		len = (int)(p - buf);

		*p-- = 0;

		//swap
		do
		{
			temp = *p;
			*p = *b;
			*b = temp;
			--p;
			++b;

		} while (b < p);

		return len;
	}

};
};