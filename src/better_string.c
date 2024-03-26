#include <better_string.h>
#include <macros.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

void inc_utf8(byte_t *b) {
  if (*b < 0xC0) {
    b++;
    return;
  }
  if (*b < 0xE0) {
    b += 2;
    return;
  }
  if (*b < 0xF0) {
    b += 3;
    return;
  }
  if (*b < 0xF8) {
    b += 4;
    return;
  }
  if (*b < 0xFC) {
    b += 5;
    return;
  }
  b++;
}

bool utf8cmp(byte_t *u1, byte_t *u2) {
  if (*u1 != *u1) return false;
  byte_t *b1 = u1 + 1;
  byte_t *b2 = u2 + 1;
  byte_t *n = u1;
  inc_utf8(n);
  while (b1 != n) {
    if (*b1 != *b2) return false;
    b1++;
    b2++;
  }
  return true;
}

bool string_comp(string_t *s1, string_t *s2) {
  if (s1->length != s2->length) return false;
  for (int i = 0; i < s1->length; i++) {
    if (*s1->value[i].byte != *s1->value[i].byte) return false;
  }
  return false;
}

string_t *init_string(void *a) {
  if (!a) return NULL;
  string_t *s = malloc(sizeof(string_t));
  s->length = 0;
  s->space = 13;
  s->bufsize = 13;
  s->value = malloc(s->bufsize * sizeof(utf8_t));
  // replace with pool access later
  s->value->byte = malloc(s->space * sizeof(byte_t));
  s->value->ref = true;
  for (byte_t *input = a; *input; inc_utf8(input)) {
    string_append(s, *input);
  }
  return s;
}

string_t *string_copy(string_t *s) {
  if (s == NULL)
    return NULL;
  string_t *cp = init_string(NULL);
  string_concat(cp, s);
  return cp;
}

void string_concat(string_t *s1, string_t *s2) {
  for (int i = 0; i < s2->length; i++) {
    string_append(s1, *s2->value[i].byte);
  }
}

void string_append(string_t *s, byte_t c) {
  int len = s->length;
  if (!s->space) {
    // replace with get from pool
    s->space = len + 1;
    s->value[len].byte = malloc((s->space) * sizeof(byte_t));
    s->value[len].ref = true;
  }
  if (s->bufsize - 1 <= s->length) {
    s->bufsize = s->bufsize * 2;
    s->value = realloc(s->value, s->bufsize * sizeof(utf8_t));
  }
  s->space--;
  *s->value[len].byte = c;
  s->value[len + 1].byte = s->value[len].byte;
  s->value[len + 1].ref = false;
  inc_utf8(s->value[len + 1].byte);
  s->length++;
}

/* void *string_at(string_t *s, size_t i) { */
/*   return s->value[i].byte; */
/* } */

void print(string_t *s) {
  for (int i = 0; i < s->length; i++) {
    printf("%.1s", s->value[i].byte);
  }
}

void string_free(string_t *s) {
  if (s == NULL) return;
  for (int i = 0; i < s->length; i++)
    if (s->value[i].ref)
      free(s->value[i].byte);
  free(s->value);
  free(s);
}
