#include "managed_string.h"
#include "math_utils.h"

string *string_make_new(size_t len)
{
    /* Allocate new buffer */
    len = nearest_even_ceil_size_t(len);
    len = len ? len : 2;

    char *chars_begin = (char *)malloc((len + 1) * sizeof(char));
    if (!chars_begin) /* If error, return null */
        return NULL;

    /* Create new string */
    string *s = (string *)malloc(sizeof(string));
    if (!s) /* If error, free the bugger and return null */
    {
        free(chars_begin);
        return NULL;
    }

    /* Assign managed string variables */
    s->start = chars_begin;
    s->length = 0;
    s->capacity = len;

    return s;
}
string *string_make_from_buffer(const char *buf)
{
    string *new_string = string_make_new(0);
    if (!buf)
        return new_string;
    else
        return string_set_buffer(new_string, buf);
}
string *string_make_from_buffer_safe(size_t len, const char *buf)
{
    string *new_string = string_make_new(0);
    if (!buf)
        return new_string;
    else
        return string_set_buffer_safe(new_string, len, buf);
}

string *string_clear(string *s)
{
    if (!s->start)
        return NULL;

    /* Null all characters in the string */
    for (char *current = s->start, *end = string_get_end(s); current != end; current++)
        *current = 0;

    /* Reset length */
    s->length = 0;

    return s;
}

string *string_append_char(string *s, char c)
{
    /* Return null if the string pointert is invalid */
    if (!s)
        return NULL;

    size_t new_length = s->length + 1;
    /* Make new buffer if new length exceeds capacity */
    if (new_length > s->capacity)
    {
        /* Double the length */
        new_length = new_length * 2;

        /* Allocate new buffer for the combined string */
        char *new_begin = (char *)malloc((new_length + 1) * sizeof(char));
        if (!new_begin) /* If error, return null */
            return NULL;
        new_begin[new_length] = 0;

        /* Copy the original string into new buffer */
        for (size_t i = 0; i < s->length; i++)
            new_begin[i] = s->start[i];
        s->capacity = new_length;

        /* Free the old buffer */
        free(s->start);
        s->start = new_begin;
    }

    s->start[s->length] = c;
    s->length++;
    *string_get_end(s) = 0;

    return s;
}
string *string_append_chars(string *s, const char *buf)
{
    /* Return null if the string pointert is invalid */
    if (!s)
        return NULL;
    /* Do not do anything if the buffer is штмфдшв */
    if (!buf)
        return s;

    size_t buffer_length = strlen(buf);

    /* Copy the buffer at the end of the string */
    for (size_t i = s->length, j = 0; i < buffer_length; j++, i++)
        if (!string_append_char(s, buf[i]))
            return NULL;

    return s;
}
string *string_append_chars_safe(string *s, size_t len, const char *buf)
{
    /* Return null if the string pointert is invalid */
    if (!s)
        return NULL;
    /* Do not do anything if the buffer is штмфдшв */
    if (!buf || !len)
        return s;

    size_t buffer_length = strnlen(buf, len);

    /* Copy the buffer at the end of the string */
    for (size_t i = s->length, j = 0; i < buffer_length; j++, i++)
        if (!string_append_char(s, buf[i]))
            return NULL;

    return s;
}

string *string_insert_char(string *s, size_t idx, char c)
{
    /* Return null if the string pointert is invalid */
    if (!s)
        return NULL;

    size_t new_length = s->length + 1;
    /* Make new buffer if new length exceeds capacity */
    if (new_length > s->capacity)
    {
        /* Double the length */
        new_length = new_length * 2;

        /* Allocate new buffer for the combined string */
        char *new_begin = (char *)malloc((new_length + 1) * sizeof(char));
        if (!new_begin) /* If error, return null */
            return NULL;
        new_begin[new_length] = 0;

        /* Copy the original string into new buffer */
        for (size_t i = 0; i < s->length; i++)
            new_begin[i] = s->start[i];
        s->capacity = new_length;

        /* Free the old buffer */
        free(s->start);
        s->start = new_begin;
    }

    /* Make space for the new character */
    for (size_t i = s->length; i > idx; i--)
        s->start[i] = s->start[i - 1];

    s->start[idx] = c;
    s->length++;
    *string_get_end(s) = 0;

    return s;
}
string *string_insert_chars(string *s, size_t idx, const char *buff)
{
    /* Return null if the string pointert is invalid */
    if (!s)
        return NULL;

    size_t buffer_length = strlen(buff);
    for (size_t i = 0; i < buffer_length; i++)
        if (!string_insert_char(s, idx + i, buff[i]))
            return NULL;

    return s;
}
string *string_insert_chars_safe(string *s, size_t idx, size_t len, const char *buff)
{
    /* Return null if the string pointert is invalid */
    if (!s)
        return NULL;

    size_t buffer_length = strnlen(buff, len);
    for (size_t i = 0; i < buffer_length; i++)
        if (!string_insert_char(s, idx + i, buff[i]))
            return NULL;

    return s;
}

string *string_set_buffer(string *s, const char *buf)
{
    if (!buf) /* Return if the buffer is invalid */
        return s;

    if (s)
    {
        s->length = 0;
        return string_append_chars(s, buf);
    }

    return NULL;
}
string *string_set_buffer_safe(string *s, size_t len, const char *buf)
{
    if (!buf) /* Return if the buffer is invalid */
        return s;

    if (s)
    {
        s->length = 0;
        return string_append_chars_safe(s, len, buf);
    }

    return NULL;
}

string *string_remove_range(string *s, size_t first, size_t n)
{
    /* Return null if the string pointert is invalid */
    if (!s || !s->start)
        return NULL;

    /* Check bounds */
    if (first >= s->length)
        first = s->length - 1;

    /* Set the chars in range to null */
    for (size_t i = first; i < first + n; i++)
        s->start[i] = 0;

    /* Shift the rest of the string to fill the null bytes */
    for (size_t i = first + n, j = first; i < s->length; i++, j++)
        s->start[j] = s->start[i];

    /* Set new length & end pointer */
    s->length = s->length - n;
    *string_get_end(s) = 0;

    return s;
}

char string_is_empty(const string *s)
{
    /* String is not null if buffer is valid, length is > 0 and first character is not null */
    return !(s && s->start && s->length && s->start[0]);
}
size_t string_get_size(const string *s)
{
    if (!s || !s->start || !s->capacity)
        return 0;

    return s->length;
}
char *string_get_end(const string *s)
{
    if (!s || !s->start)
        return NULL;

    return s->start + s->length;
}

void string_free(string *s)
{
    /* If string pointer is not valid, return */
    if (!s)
        return;

    /* If buffer is a valid pointer, free the buffer */
    if (s->start)
        free(s->start);
    /* Free the string */
    free(s);
}
