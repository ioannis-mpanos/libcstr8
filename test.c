/*
    libcstr: A minimal and simple C library for dynamic strings
    Copyright (C) 2014 Ioannis Mpanos

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include <stdio.h>
#include "cstr.h"

int main(int argc, char **argv)
{
	str8_t str1 = str8new("Hello world!");
	str8_t str2 = str8clone(str1);

	printf("(%lu)'%s'\n", str8len(str1), cstr(str1));
	printf("(%lu)'%s'\n", str8len(str2), cstr(str2));
	str8cat(str1, str1);
	printf("(%lu)'%s'\n", str8len(str1), cstr(str1));
	str8free(str1);
	str8free(str2);
	return 0;
}
