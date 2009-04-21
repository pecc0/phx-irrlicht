
#include "fast_atof.h"
#include "PhXFormattedString.h"

namespace irr
{
	namespace core
	{
		char g_buffer [512]={0};
		PhXFormattedString::PhXFormattedString(c8*format, ...)
		{
			
			va_list args;
			va_start( args, format);
			g_buffer[0] = 0;
			int ret = vsprintf( g_buffer, format, args );
			_IRR_DEBUG_BREAK_IF (ret >= 512)
			
			//call operator=
			stringc::operator = (g_buffer);
			va_end(args);
		}
		
		list <PhXFormattedString> PhXFormattedString::split(c8* delim){
			list<PhXFormattedString> result;
			int len = strlen(delim);
			int j = 0;
			for (int i = find(delim, j); i>=0; )
			{
				result.push_back(PhXFormattedString(subString(j, i - j)));
				j = i + len;
				i = this->find(delim, j);
			}
			result.push_back(this->subString(j, 5000));

			return result;
		}
	}
}