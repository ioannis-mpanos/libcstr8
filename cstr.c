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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cstr.h"

#define STR8_MIN_CAPACITY	16

typedef struct str8_struct_t
{
	char * string8;
	size_t length;
	size_t capacity;
} _str8;



/*---------------------------- Inline functions ------------------------------*/
extern const char * cstr(str8_t str);
extern char * str8dup(str8_t str);
extern str8_t str8clone(str8_t str);
extern size_t str8len(str8_t str);
/*----------------------------------------------------------------------------*/

static inline size_t _aligned_capacity(size_t length)
{
	size_t size = 1;
	while (length) { length >>=1; size<<=1; }
	return size>STR8_MIN_CAPACITY ? size:STR8_MIN_CAPACITY;
}

static inline int _ensure_capacity(str8_t str, size_t alloc_len)
{
	if (alloc_len > str->capacity)
	{
		char * mem;
		mem = realloc(str->string8, alloc_len);
		if (!mem) return 0;
		str->string8 = mem;
		str->capacity = alloc_len;
	}
	return 1;
}

str8_t str8new(const char * cstr_ptr)
{
	if (cstr_ptr)
	{
		str8_t result;

		result = calloc(1, sizeof(_str8));
		if (result)
		{
			result->length = strlen(cstr_ptr);
			if (!_ensure_capacity(result, _aligned_capacity(result->length+1)))
				return 0;
			strcpy(result->string8, cstr_ptr);
			return result;
		}
	} else
		return str8new("");
	return 0;
}

str8_t str8cpy(str8_t dst, str8_t src)
{

	if (dst != NULL)
	{
		if (src != NULL)
		{
			if (!_ensure_capacity(dst, _aligned_capacity(src->length+1)))
				return 0;
			dst->length = src->length;
			strcpy(dst->string8, src->string8);
		}
		return dst;
	}
	return NULL;
}

str8_t str8cat(str8_t str1, str8_t str2)
{
	if (str1 != NULL)
	{
		if (str2 != NULL)
		{
			size_t offset = str1->length;
			if (!_ensure_capacity(str1, _aligned_capacity(str1->length+str2->length+1)))
				return 0;

			str1->length += str2->length;
			memcpy(str1->string8+offset, str2->string8, str2->length);
			str1->string8[str1->length] = '\0';
		}
		return str1;
	}
	return NULL;
}


void str8free(str8_t str)
{
	if (str == 0) return;
	free(str->string8);
	free(str);
}

