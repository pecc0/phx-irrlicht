
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
