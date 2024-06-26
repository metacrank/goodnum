#ifndef BETTER_STRING_H
#define BETTER_STRING_H
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>
/*! We want better strings to realloc less and keep track of the length of the
 * string so we don't have to call strlen every time */

typedef unsigned char byte_t;

/*! @brief An array implementation of the string data structure */
typedef struct STRING_STRUCT {
  /*! @brief length of string */
  size_t length;
  /*! @brief Size of current value buffer */
  size_t bufsize;
  /*! @brief String value of struct */
  byte_t *value;
  /* for future utf-32 support */
  //wchar_t *value;
} string_t;

/* returns the number of bytes encoding the unicode character at b */
int sizeof_utf8(byte_t *b);

/* increments a byte pointer to the next unicode character */
void inc_utf8(byte_t **b);

/* decrements a byte pointer to the previous unicode character */
void dec_utf8(byte_t **b);

int utf8cmp(byte_t *b1, byte_t *b2);

/* analagous to strcmp for better_string */
int string_comp(string_t *s1, string_t *s2);

/* returns an identical string with the bufsize 'size' */
string_t *realloc_string(string_t *s, size_t size);

/* ensures there is space to put n characters in the string by reallocing if necessary */
void string_ensure_space(string_t *s, size_t n);

/*! Allocates memory for new string */
string_t *init_string(void *value);

/*! Copies string to another string */
string_t *string_copy(string_t *s);

/*! Concatenates a string_t type and a char * type */
void string_concat(string_t *s1, string_t *s2);

/*! Appends single characters */
void string_append(string_t *s, byte_t *c);

/* reverse order of characters of a string */
void string_reverse(string_t *s);

/* gets a pointer to the utf-8 character at index i */
/* void *string_at(string_t *s, size_t i); */

/* prints a string */
void print(string_t *s);

/*! Frees space for string */
void string_free(string_t *s);

/* returns allocated space to pool */
void string_recycle(string_t *s);

#endif
