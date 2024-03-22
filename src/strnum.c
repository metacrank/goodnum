//#include <strnum.h>
#include "../include/strnum.h"
#include "../include/better_string.h"
#include <ctype.h>
#include <stdio.h>

//to be removed:
typedef unsigned char byte_t;

bool isfloat(string_t *s) {
  for (long i = 0; i < s->length; i++)
    if (!isdigit(s->value[i]) && s->value[i] != '.') return false;
  return true;
}

bool isint(string_t *s) {
  for (long i = 0; i < s->length; i++)
    if (!isdigit(s->value[i])) return false;
  return true;
}

long order(string_t *s) {
  long i = 0;
  if (s->value[0] == '-') i = 1;
  while (i < s->length) {
    if (s->value[i] == '.') return i - 1;
    i++;
  }
  return s->length - 1 - i;
}

string_t *neg(string_t *s) {
  if (s->value[0] == '-') {
    for (long i = 0; i < s->length; i++)
      s->value[i] = s->value[i + 1];
  } else {
    string_append(s, ' ');
    for (long i = 1; i < s->length; i++)
      s->value[i] = s->value[i - 1];
    s->value[0] = '-';
  }
  return s;
}

string_t *ip(string_t *s) {
  for (long i = 0; i < s->length; i++) {
    if (s->value[i] == '.') {
      s->value[i] = '\0';
      break;
    }
  }
  return s;
}

string_t *fp(string_t *s) {
  long idx = 0;
  while (s->value[idx] != '.' && s->value[idx] != '\0') {
    idx++;
  }
  long nidx = 0;
  do {
    s->value[nidx] = s->value[idx];
    idx++;
    nidx++;
  } while (s->value[idx] != '\0');
  return s;
}

string_t *sum(string_t *m, string_t *n) {
  if (n->value[0] == '-' && m->value[0] != '-') {
    neg(n);
    return diff(m, n);
  }
  int negative = 0;
  if (m->value[0] == '-') {
    if (n->value[0] != '-') {
      neg(m);
      return diff(n, m);
    }
    negative = 1;
  }
  long moffset = order(m);
  long noffset = order(n);
  long doffset = moffset - noffset;
  if (doffset < 0) {
    long tmp = moffset;
    moffset = noffset;
    noffset = tmp;
    doffset = -doffset;
    string_t *str = m;
    m = n;
    n = str;
  }
  char *mval = m->value;
  char *nval = n->value;
  if (negative) {
    mval = m->value + 1;
    nval = n->value + 1;
  }
  if (nval[noffset + 1] == '.')
    if (mval[moffset + 1] == '\0')
      string_append(m, '.');
  for (long i = m->length; i < n->length + doffset; i++) {
    string_append(m, '0');
  }
  char carry = 0;
  long i = n->length + doffset - 1 - negative;
  while (i >= doffset) {
    if (mval[i] != '.') {
      mval[i] = (int)nval[i - doffset] + carry - '0' + mval[i];
      carry = mval[i] - 10 - '0';
      if (carry < 0) carry = 0;
      else carry = 1;
      mval[i] -= carry * 10;
    }
    i--;
  }
  while (i >= 0 && carry) {
    mval[i] = mval[i] + carry;
    carry = mval[i] - 10 - '0';
    if (carry < 0) carry = 0;
    else carry = 1;
    mval[i] -= carry * 10;
    i--;
  }
  if (carry) {
    string_append(m, ' ');
    for (int i = 1; i < m->length - negative; i++) {
      mval[i] = mval[i - 1];
    }
    mval[0] = '1';
  }
  string_free(n);
  return m;
}

string_t *diff(string_t *m, string_t *n) {}
