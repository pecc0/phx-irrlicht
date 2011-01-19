/* AUTORIGHTS
Copyright (C) 2010,2011 Petko Petkov (petkodp@gmail.com)
      
This file is part of JWorld.

JWorld is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include "fast_atof.h"
#include "PhXFormattedString.h"

namespace irr
{
	namespace core
	{
		char g_buffer [512]={0};
		PhXFormattedString::PhXFormattedString(const c8*format, ...)
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

		list <PhXFormattedString> PhXFormattedString::split(const c8* delim){
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
