#pragma once

/* Simple managed string implementation */

#include "includes.h"

typedef struct string
{
    char *start; /* First character of the string */

    size_t capacity; /* Max length (allocated size - 1) */
    size_t length;   /* Current length */
} string;

/* 
 * Allocates memory for a new managed string of a given size.
 * Returns the new string pointer or NULL if an error occured.
 */
string *string_make_new(size_t);
/* 
 * Allocates memory for a new managed string and copies the given buffer to it.
 * Returns the new string pointer or NULL if an error occured.
 */
string *string_make_from_buffer(const char *);
/* 
 * Allocates memory for a new managed string of maximum length and copies the given buffer to it.
 * Returns the new string pointer or NULL if an error occured.
 */
string *string_make_from_buffer_safe(size_t, const char *);

/* 
 * Sets string characters to null.
 * Returns the passed string pointer or NULL if an error occured.
 */
string *string_clear(string *);

/* 
 * Appends given character to the given string.
 * Returns the passed string pointer or NULL if an error occured.
 */
string *string_append_char(string *, char);

/* 
 * Appends given character buffer to the given string.
 * Returns the passed string pointer or NULL if an error occured.
 */
string *string_append_chars(string *, const char *);
/* 
 * Appends given character buffer up to the max length to the given string.
 * Returns the passed string pointer or NULL if an error occured.
 */
string *string_append_chars_safe(string *, size_t, const char *);

/* 
 * Inserts a given character at the given index in the string.
 * Returns the passed string pointer or NULL if an error occured.
 */
string *string_insert_char(string *, size_t, char);
/* 
 * Inserts a given character buffer at the given index in the string.
 * Returns the passed string pointer or NULL if an error occured.
 */
string *string_insert_chars(string *, size_t, const char *);
/* 
 * Inserts a given character buffer of a given size at the given index in the string.
 * Returns the passed string pointer or NULL if an error occured.
 */
string *string_insert_chars_safe(string *, size_t, size_t, const char *);

/*
 * Replaces buffer of the given string.
 * Returns the passed string pointer or null on error.
 */
string *string_set_buffer(string *, const char *);
/*
 * Replaces buffer of the given string up to the specified number of characters.
 * Returns the passed string pointer or null on error.
 */
string *string_set_buffer_safe(string *, size_t, const char *);

/*
 * Removes n characters starting at the given index from the string.
 * Returns the passed string or NULL on error.  
 */
string *string_remove_range(string *, size_t, size_t n);

/*
 * Checks whether the string is empty.
 * If the string is invalid always returns true. 
 */
char string_is_empty(const string *);
/*
 * Returns the string size.
 * If the string is invalid, always returns 0. 
 */
size_t string_get_size(const string *);
/*
 * Returns the string's end pointer (last char + 1).
 * If the string is invalid, always returns null. 
 */
char *string_get_end(const string *);

/*
 * Frees memory allocated for a given managed string and it's buffer. 
 */
void string_free(string *);
