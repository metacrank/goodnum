#include <better_string.h>
#include <macros.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

int sizeof_utf8(byte_t *b) {
  if (*b < 0xC0) {
    return 1;
  }
  if (*b < 0xE0) {
    return 2;
  }
  if (*b < 0xF0) {
    return 3;
  }
  return 4;
}

void inc_utf8(byte_t **b) {
  *b += sizeof_utf8(*b);
}

void dec_utf8(byte_t **b) {
  do {
    (*b)--;
  } while (0x80 <= **b && **b < 0xC0);
}

int utf8cmp(byte_t *b1, byte_t *b2) {
  int size1 = sizeof_utf8(b1);
  int size2 = sizeof_utf8(b2);
  int retval;
  int i;
  for (i = 0; i < size1; i++) {
    if (i == size2) return b1[i];
    if ((retval = b1[i] - b2[i])) return retval;
  }
  if (i != size2)
    return - b2[i];
  return 0;
}

int string_comp(string_t *s1, string_t *s2) {
  int retval;
  int i;
  for (i = 0; i < s1->length; i++) {
    if (i == s2->length) return s1->value[i];
    if ((retval = s1->value[i] - s2->value[i])) return retval;
  }
  if (i != s2->length)
    return - s2->value[i];
  return 0;
}

string_t *realloc_string(string_t *s, size_t size) {
  string_t *newstr = malloc(sizeof(string_t));
  newstr->bufsize = size;
  newstr->length = s->length;
  //fetch from pool
  newstr->value = malloc(size * sizeof(byte_t));
  memcpy(newstr->value, s->value, s->length * sizeof(byte_t));
  //add to pool
  string_free(s);
  return newstr;
}

void string_ensure_space(string_t **s, size_t n) {
  if ((*s)->bufsize - n <= (*s)->length)
    (*s) = realloc_string(*s, 2 * (*s)->bufsize);
}

string_t *init_string(void *a) {
  if (!a) return NULL;
  string_t *s = malloc(sizeof(string_t));
  s->length = 0;
  s->bufsize = 24;
  // replace with pool access later
  s->value = malloc(s->bufsize * sizeof(byte_t));
  byte_t *input = a;
  /* wchar_t append; */
  while (*input != '\0') {
    /* append = 0; */
    /* for (int size = sizeof_utf8(input); size > 0; size--) { */
    /*   append += *input; */
    /*   input++; */
    /* } */
    /* string_append(s, append); */
    string_ensure_space(&s, 1);
    memcpy(s->value + s->length, input, sizeof(byte_t));
    s->length++;
    input++;
  }
  memcpy(s->value + s->length, input, sizeof(byte_t));
  return s;
}

string_t *string_copy(string_t *s) {
  if (s == NULL)
    return NULL;
  string_t *cp = malloc(sizeof(string_t));
  cp->bufsize = s->bufsize;
  cp->length = s->length;
  cp->value = malloc(cp->bufsize * sizeof(byte_t));
  memcpy(cp->value, s->value, (s->length + 1) * sizeof(byte_t));
  return cp;
}

void string_concat(string_t *s1, string_t *s2) {
  string_ensure_space(&s1, s2->length);
  memcpy(s1->value + s1->length, s2->value, (s2->length + 1) * sizeof(byte_t));
  s1->length += s2->length;
}

/* void string_append(string_t *s, wchar_t c) { */
/*   int len = s->length; */
/*   if (s->bufsize <= len) { */
/*     //add to pool */
/*     string_t *memstr = malloc(sizeof(string_t)); */
/*     memstr->bufsize = s->bufsize; */
/*     memstr->value = s->value; */
/*     s->bufsize *= 2; */
/*     //fetch from pool */
/*     s->value = malloc(s->bufsize * sizeof(wchar_t)); */
/*     memcpy(s->value, memstr->value, memstr->bufsize); */
/*   } */
/*   s->value[len] = c; */
/*   s->length++; */
/* } */

void string_append(string_t *s, byte_t *p) {
  int size = sizeof_utf8(p);
  string_ensure_space(&s, size);
  memcpy(s->value + s->length, p, size * sizeof(byte_t));
  s->length += size;
}

void string_reverse(string_t *s) {
  // fetch big enough string from pool
  string_t *r = malloc(sizeof(string_t));
  r->bufsize = s->bufsize;
  r->length = 0;
  r->value = malloc(s->length * sizeof(byte_t));
  byte_t *p = &s->value[s->length];
  dec_utf8(&p);
  int utf8size;
  while (p > s->value) {
    utf8size = sizeof_utf8(p);
    memcpy(r->value + r->length, p, utf8size);
    r->length += utf8size;
    dec_utf8(&p);
  }
  memcpy(r->value + r->length, p, sizeof_utf8(p));
  s->value = r->value;
  r->value = p;
  // push to pool
  string_free(r);
}

/* void *string_at(string_t *s, size_t i) { */
/*   return s->value[i].byte; */
/* } */

void print(string_t *s) {
  printf("%.*s", (int)s->length, s->value);
}

void string_free(string_t *s) {
  if (s == NULL) return;
  free(s->value);
  free(s);
}
