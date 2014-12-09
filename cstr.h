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
#ifndef CSTR_HEADER_DEFINED
#define CSTR_HEADER_DEFINED

#include <stdlib.h>
#include <string.h>

#define STR8_SANITY_CHECKS	1

struct str8_struct_t;

typedef struct str8_struct_t * str8_t;

str8_t str8new(const char * cstr);
void str8free(str8_t str);

str8_t str8cpy(str8_t dst, str8_t src);
str8_t str8cat(str8_t str1, str8_t str2);

int str8findfirst(str8_t haystack, str8_t needle);
int str8find(str8_t haystack, str8_t needle, int offset);

inline const char * cstr(str8_t str)
{
	return *(const char **)str;
}

inline char * str8dup(str8_t str)
{
	return strdup(cstr(str));
}

inline str8_t str8clone(str8_t str)
{
	return str==0 ? 0 : str8new(cstr(str));
}

inline size_t str8len(str8_t str)
{
	return *(size_t *)((char *)str + sizeof(char *));
}

#endif
