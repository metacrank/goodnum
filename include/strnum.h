#ifndef STRNUM_H_
#define STRNUM_H_
#include <better_string.h>
#include <macros.h>
#include <stdbool.h>

typedef struct RELATION_STRUCT {
  size_t size;
  byte_t **relation;
} relation_t;

typedef struct MAPPING_STRUCT {
  size_t n;
  size_t m;
  byte_t **buf;

} mapping_t;

void init_math();

void math_free();

bool isfloat(string_t *s);

bool isint(string_t *s);

long order(string_t *s);

string_t *neg(string_t *s);

string_t *ip(string_t *s);

string_t *fp(string_t *s);

string_t *sum(string_t *m, string_t *n);

string_t *diff(string_t *m, string_t *n);

string_t *product(string_t *m, string_t *n);

string_t *quotient(string_t *m, string_t *n);

#endif // STRNUM_H_
