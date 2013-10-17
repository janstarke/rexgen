/*
Copyright (C) 2012-2013  Jan Starke <rexgen@outofbed.org>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/
*/

#ifndef __VERSION_H__
#define __VERSION_H__
#include <librexgen\parser\osdepend.h>
#include <cstdio>
#include <cstdlib>

using namespace std;

namespace rexgen {
	static const int VERSION_MAJOR = 1;
	static const int VERSION_MINOR = 0;
	static const char* VERSION_REVISION = "$Rev: 70 $";

	EXPORT
	const char* getVersion();
}

#endif /* __VERSION_H__ */