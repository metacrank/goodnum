#include <strnum.h>
#include <better_string.h>
#include <ctype.h>
#include <stdio.h>

bool isfloat(string_t *s) {
  for (long i = 0; i < s->length; i++)
    if (!isdigit(s->value[i].byte) && *s->value[i].byte != '.') return false;
  return true;
}

bool isint(string_t *s) {
  for (long i = 0; i < s->length; i++)
    if (!isdigit(s->value[i].byte)) return false;
  return true;
}

long order(string_t *s) {
  long i = 0;
  while (i < s->length) {
    if (*s->value[i].byte == '.') return i - 1;
    i++;
  }
  return s->length - 1 - i;
}

string_t *neg(string_t *s) {
  return s;
}

string_t *ip(string_t *s) {
  return s;
}

string_t *fp(string_t *s) {
  return s;
}

string_t *diff(string_t *m, string_t *n) {}

string_t *product(string_t *m, string_t *n) {}

string_t *quotient(string_t *m, string_t *n) {}
