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

/** \file cstr.c
    \brief Implementation of the prototypes in \ref cstr.h.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cstr.h"

/** \brief Minimum capacity of a new string in bytes */
#define STR8_MIN_CAPACITY   16

struct _str8_tag
{
    char * string8;
    size_t length;
    size_t capacity;
};



/*---------------------------- Inline functions ------------------------------*/
extern const char * cstr(str8_t str);
extern char * str8dup(str8_t str);
extern str8_t str8clone(str8_t str);
extern size_t str8len(str8_t str);
/*----------------------------------------------------------------------------*/

/* Returns a capacity greater or equal to length, such as the capacity is
a power of 2. The "naive" computation is short, but can be optimized. */
static inline size_t _aligned_capacity(size_t length)
{
    size_t size = 1;
    while (length) { length >>=1; size<<=1; }
    return size>STR8_MIN_CAPACITY ? size:STR8_MIN_CAPACITY;
}

/* Ensures that the capacity of the character buffer in the dynamic string str
is greater or equal to alloc_len */
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

/* NULL is used for emphasis in the following function implementations */

/* Sanity checks may be switched out of compilation for more efficient production code. */


str8_t str8new(const char * cstr_ptr)
{
    str8_t result;

    /* When NULL is passed, we create a new empty string */
    if (!cstr_ptr)
        cstr_ptr = "";

    /* Allocate the needed memory */
    if (!(result = calloc(1, sizeof(struct _str8_tag))))
        return NULL;
    result->length = strlen(cstr_ptr);
    if (!_ensure_capacity(result, _aligned_capacity(result->length+1)))
        return NULL;

    /* Copy the string and return the new object */
    strcpy(result->string8, cstr_ptr);
    return result;
}

str8_t str8cpy(str8_t dst, str8_t src)
{
    #ifdef STR8_SANITY_CHECKS
    if (!dst)
        return NULL;
    else if (!src)
        return dst;
    #endif
    if (!_ensure_capacity(dst, _aligned_capacity(src->length+1)))
        return NULL;
    /* Copy the string and return a reference to dst */
    dst->length = src->length;
    strcpy(dst->string8, src->string8);
    return dst;
}

str8_t str8cat(str8_t str1, str8_t str2)
{
    size_t offset;
    #ifdef STR8_SANITY_CHECKS
    if (!str1)
        return NULL;
    else if (!str2)
        return str1;
    #endif
    /* Save the length of the first string */
    offset = str1->length;
    if (!_ensure_capacity(str1, _aligned_capacity(str1->length+str2->length+1)))
        return NULL;
    str1->length += str2->length;
    /* Use memcpy to avoid looking for the null byte.
    This ensures that str8cat(s,s) works as expected, but we have to null terminate
    the result ourselves. */
    memcpy(str1->string8+offset, str2->string8, str2->length);
    str1->string8[str1->length] = '\0';
    return str1;
}

int str8findfirst(str8_t haystack, str8_t needle)
{
    char * needle_ptr;
    #ifdef STR8_SANITY_CHECKS
    if (!haystack || !needle)
        return -1;
    #endif
    needle_ptr = strstr(haystack->string8, needle->string8);
    if (needle_ptr)
        return needle_ptr - haystack->string8;
    return -1;
}

int str8find(str8_t haystack, str8_t needle, size_t offset)
{
    char * needle_ptr;
    #ifdef STR8_SANITY_CHECKS
    if (!haystack || !needle)
        return -1;
    #endif
    /* Searching beyond the end of the character buffer is a failure. */
    if (offset>=haystack->length)
        return -1;
    needle_ptr = strstr(haystack->string8 + offset, needle->string8);
    if (needle_ptr)
        return needle_ptr - haystack->string8;
    return -1;
}

void str8free(str8_t str)
{
    if (str == 0) return;
    free(str->string8);
    free(str);
}

