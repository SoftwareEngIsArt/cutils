#include "managed_array.h"
#include "math_utils.h"

array *array_make_new(size_t size, size_t len)
{
    if (!size) /* Cannot create array for elements with 0 size */
        return NULL;

    len = nearest_even_ceil_size_t(len);
    len = len ? len : 2;

    /* Allocate new buffer */
    void *new_buffer = malloc((size + 1) * len);
    if (!new_buffer) /* If error, return null */
        return NULL;

    /* Allocate managed array */
    array *a = (array *)malloc(sizeof(array));
    if (!a) /* If error, return null */
    {
        free(new_buffer);
        return NULL;
    }

    a->start = new_buffer;
    a->capacity = len;
    a->length = 0;
    a->element_size = size;

    return a;
}
array *array_make_from_buffer(size_t size, size_t len, void *buf)
{
    if (!size) /* Cannot create array for elements with 0 size */
        return NULL;

    /* Create new array */
    array *a = array_make_new(size, len);
    return array_set_buffer(a, len, buf);
}

array *array_append(array *a, void *e)
{
    if (!a) /* Return null if array is invalid */
        return NULL;
    if (!e) /* Return if the element is invalid */
        return a;

    size_t new_length = a->length + 1;
    /* Reallocate if exceeds capacity */
    if (new_length > a->capacity)
    {
        /* Double the length */
        new_length = new_length * 2;
        /* Allocate new buffer */
        void *new_buffer = malloc((a->element_size + 1) * new_length);
        if (!new_buffer) /* If error, return null */
            return NULL;

        /* Copy old elements */
        for (size_t i = a->length * a->element_size; i > 0; i--)
            ((uint8_t *)new_buffer)[i - 1] = ((uint8_t *)a->start)[i - 1];

        free(a->start);
        a->start = new_buffer;
        a->capacity = new_length;
    }

    /* Copy bytes of the new element to the end of the array */
    for (size_t i = 0, j = a->length * a->element_size; i < a->element_size; i++, j++)
        ((uint8_t *)a->start)[j] = ((uint8_t *)e)[i];

    a->length++;

    return a;
}
array *array_insert(array *a, size_t idx, void *e)
{
    if (!a) /* Return null if array is invalid */
        return NULL;
    if (!e) /* Return if the element is invalid */
        return a;

    size_t new_length = a->length + 1;
    /* Reallocate if exceeds capacity */
    if (new_length > a->capacity)
    {
        /* Double the length */
        new_length = new_length * 2;
        /* Allocate new buffer */
        void *new_buffer = malloc((a->element_size + 1) * new_length);
        if (!new_buffer) /* If error, return null */
            return NULL;

        /* Copy old elements */
        for (size_t i = a->length * a->element_size; i > 0; i--)
            ((uint8_t *)new_buffer)[i - 1] = ((uint8_t *)a->start)[i - 1];

        free(a->start);
        a->start = new_buffer;
        a->capacity = new_length;
    }

    /* Make space for the new element */
    for (size_t i = a->length; i > idx; i--)
    {
        /* Find byte indexes of the current element and the previous element */
        size_t element_i = i * a->element_size;
        size_t previous_i = element_i - a->element_size;

        /* Copy bytes of the previous element to the current element */
        for (size_t byte_i = 0; byte_i < a->element_size; byte_i++)
            ((uint8_t *)a->start)[element_i + byte_i] = ((uint8_t *)a->start)[previous_i + byte_i];
    }

    /* Copy bytes of the new element */
    for (size_t i = 0, j = idx * a->element_size; i < a->element_size; i++, j++)
        ((uint8_t *)a->start)[j] = ((uint8_t *)e)[i];
    a->length++;

    return a;
}
array *array_remove_top(array *a)
{
    if (!a || !a->start) /* Return null if array is invalid */
        return NULL;

    /* Skip if the array is empty */
    if (a->length)
        a->length--;
    return a;
}
array *array_remove(array *a, size_t idx)
{
    if (!a || !a->start) /* Return null if array is invalid */
        return NULL;

    /* Skip if the array is empty */
    if (!a->length)
        return a;

    /* Check bounds */
    if (idx > a->length)
        idx = a->length - 1;

    for (size_t i = idx; i < a->length; i++)
    {
        /* Find byte indexes of the current element and the next element */
        size_t element_i = i * a->element_size;
        size_t next_i = element_i + a->element_size;

        /* Copy bytes of the next element to the current element */
        for (size_t byte_i = 0; byte_i < a->element_size; byte_i++)
            ((uint8_t *)a->start)[element_i + byte_i] = ((uint8_t *)a->start)[next_i + byte_i];
    }

    a->length--;
    return a;
}

void *array_get_element(array *a, size_t idx)
{
    if (!a || !a->start) /* Return null if array is invalid */
        return NULL;

    /* Check bounds */
    if (idx >= a->length)
        idx = a->length - 1;

    return (void *)((uint8_t *)a->start + idx * a->element_size);
}
void array_set_element(array *a, size_t idx, void *e)
{
    if (!a || !a->start || !e) /* Return if array or the element is invalid */
        return;

    /* Check bounds */
    if (idx >= a->length)
        idx = a->length - 1;

    /* Copy bytes of the element to the index */
    for (uint8_t *start = (uint8_t *)a->start + idx * a->element_size, *end = start + a->element_size, *element_byte = (uint8_t *)e;
         start != end;
         start++, element_byte++)
        *start = *element_byte;
}

array *array_set_buffer(array *a, size_t len, const void *buf)
{
    if (buf && len && a)
    {
        a->length = 0;
        /* Append all buffer elements */
        for (size_t i = 0; i < len; i++)
            if (!array_append(a, (void *)((uint8_t *)buf + a->element_size * i)))
                return NULL;
    }

    return a;
}

void *array_get_end(const array *a)
{
    if (!a || !a->start)
        return NULL;

    return (void *)((uint8_t *)a->start + a->element_size * a->length);
}

void array_free(array *a)
{
    if (!a) /* Return if given pointer is null */
        return;

    if (!a->start) /* Free buffer if the buffer is valid */
        free(a->start);
    free(a);
}
