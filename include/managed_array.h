#pragma once

/* Managed generic resizeable array */

#include "includes.h"

typedef struct array
{
    void *start; /* First element of the array */

    size_t element_size; /* Size of the stored elements in bytes */
    size_t capacity;     /* Max length (allocated size - 1) */
    size_t length;       /* Current length */
} array;

/*
 * Allocates memory for a new array of a given length with elements of a given size.
 * Returns allocated array on NULL on error.
 */
array *array_make_new(size_t size, size_t len);
/*
 * Allocates memory for a new array of a given length and fills with elements of a given size from the passed buffer.
 * Returns alloocated array on NULL on error.
 */
array *array_make_from_buffer(size_t size, size_t len, void *);

/*
 * Appends given element to a given array.
 * Returns the passed array or null on error. 
 */
array *array_append(array *, void *);
/*
 * Inserts given element to a given array at the specified index.
 * Returns the passed array or null on error. 
 */
array *array_insert(array *, size_t, void *);
/*
 * Removes an element from the top of the array.
 * Returns the passed array or null on error. 
 */
array *array_remove_top(array *);
/*
 * Removes an element from the array at the given index.
 * Returns the passed array or null on error. 
 */
array *array_remove(array *, size_t);

/*
 * Returns pointer to the array element at the given index.
 * Returns NULL on error. 
 */
void *array_get_element(array *, size_t);
/*
 * Sets an element of the array at the given index.
 */
void array_set_element(array *, size_t, void *);

/*
 * Replaces buffer of the given array.
 * Returns the passed array pointer or null on error.
 */
array *array_set_buffer(array *, size_t, const void *);

/*
 * Returns the end pointer of the array (last element + 1). 
 * Returns null on error.
 */
void *array_get_end(const array *);

/* 
 * Frees passed array.
 */
void array_free(array *);
