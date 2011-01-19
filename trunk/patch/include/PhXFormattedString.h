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

#ifndef __IRR_PHXFORMATTEDSTRING_H_INCLUDED__
#include "irrString.h"
#include <stdarg.h>
#include "irrList.h"
#include "fast_atof.h"

#define __IRR_PHXFORMATTEDSTRING_H_INCLUDED__

namespace irr{
	namespace core{
		class PhXFormattedString : public stringc
		{
		public:
			PhXFormattedString(const c8*format, ...);
			PhXFormattedString()
			{
			}

			PhXFormattedString(const stringc& other)
			{
				*this = other;
			}

			PhXFormattedString(u32 i):stringc(i){}
			PhXFormattedString(double d):stringc(d){}

			PhXFormattedString& operator=(const c8* other)
			{
				stringc::operator = (other);
				return *this;
			}

			PhXFormattedString& operator=(const stringc& other)
			{
				stringc::operator = (other);
				return *this;
			}
			s32 find(const c8* const str, int start) const
			{
				if (str && *str)
				{
					u32 len = 0;

					while (str[len])
						++len;

					if (len > used-1)
						return -1;

					for (u32 i=start; i<used-len; ++i)
					{
						u32 j=0;

						while(str[j] && array[i+j] == str[j])
							++j;

						if (!str[j])
							return i;
					}
				}

				return -1;
			}

			list <PhXFormattedString> split(const c8* delim);

			bool getInt(int& out)
			{
				const char* ierr;
				out = core::strtol10(c_str(), &ierr);
				return (unsigned)(ierr - c_str()) == size();
			}
		};

	}
}
#endif
