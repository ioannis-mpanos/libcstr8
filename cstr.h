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

/** \file cstr.h
	\brief Definitions and prototypes for the str8 library.

	This file defines a new type str8_t
*/
#ifndef CSTR_HEADER_DEFINED
#define CSTR_HEADER_DEFINED

#include <stdlib.h>
#include <string.h>

#define STR8_SANITY_CHECKS	1


/** \brief The type \a str8_t is the one used for representing dynamic strings.*/
typedef struct str8_struct_t * str8_t;


/** Create and destroy strings
	==========================
*/


/** \brief Initialize a new string object from a C string.
	Create a new dynamic string, copying the contents of the null terminated
	string in \a cstr. If \b NULL is passed as an argument, a new empty string is
	returned.
	\param cstr A pointer to a null terminated string, or 0.
	\return The new string on success, \b NULL on error.
*/
str8_t str8new(const char * cstr);

/** \brief Deallocate the resources used by the dynamic string \a str.
	\param str The dynamic string to deallocate.
*/
void str8free(str8_t str);


/** Manipulate strings
	==================
*/


/** \brief Copy the contents of dynamic string \a src into \a dst.
	\param dst The dynamic string to copy into.
	\param src The dynamic string to copy from.
	\return \a dst on success, \b NULL on error.
*/
str8_t str8cpy(str8_t dst, str8_t src);
/** \brief Concatenate the dynamic string \a str2 after \a str1.
	\param str1 The dynamic string to hold the result of concatenation.
	\param str2 The dynamic string to concatenate after \a str1.
	\return \a str1 on succes, \b NULL on error.
*/
str8_t str8cat(str8_t str1, str8_t str2);

/** \brief Find the first dynamic string \a needle in the dynamic string \a haystack.
	\param haystack The dynamic string to be searched.
	\param needle The dynamic string to look for.
	\return The offset from the beginning of \a haystack where \a needle was
	found, or -1 when the search failed.
*/
int str8findfirst(str8_t haystack, str8_t needle);

/** \brief Find the dynamic string \a needle in the dynamic string \a haystack beginning from offset .
	\param haystack The dynamic string to be searched.
	\param needle The dynamic string to look for.
	\param offset The offset byte in \a haystack to start searching from
	\return The offset from the beginning of \a haystack where \a needle was
	found, or -1 when the search failed.
*/

int str8find(str8_t haystack, str8_t needle, int offset);


/** Accessors for the string buffer
	===============================
*/


/** \brief Provide read access to the buffer in the dynamic string \a str.
	The returned pointer should not be used to manipulate the null byte at
	the end of the string, as this invalidates the validity of str. Manipulating
	the string in any way that does not alter it's length is acceptable, but
	generally discouraged.
	\param str The dynamic string to access.
	\return a read only C string pointer to the underlying buffer.
*/
inline const char * cstr(str8_t str)
{
	return *(const char **)str;
}

/** \brief Provide access to a copy of the underlying buffer in the dynamic stirng \a str.
	\param str The dynamic string from which to copy the character buffer.
	\return A copy of the underlying buffer, NULL on error.
	The returned pointer should be disposed of with free() when no longer needed.
*/
inline char * str8dup(str8_t str)
{
	return strdup(cstr(str));
}

/** \brief Clone the dynamic string \a str.
	\param str The dynamic string to clone.
	\return A new dynamic string with the same contents as \a str or NULL on error.
*/
inline str8_t str8clone(str8_t str)
{
	return str==0 ? 0 : str8new(cstr(str));
}

/**	\brief Get the length of the dynamic string \a str.
	\param str The dynamic string for which the length is needed.
	\return The length of the dynamic string.
	This function is O(1), as the length of the dynamic string is always known
	when the string is manipulated through library calls, or the string buffers
	null terminator is not altered by caller code.
*/
inline size_t str8len(str8_t str)
{
	return *(size_t *)((char *)str + sizeof(char *));
}

#endif
