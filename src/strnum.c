#include <strnum.h>
#include <better_string.h>
#include <macros.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define BASE DEFAULT_NUMBER_BASE
#define B_ODD (BASE % 2)
#define N_O_D (BASE + 2 * (1 - B_ODD))
#define RADIUS (BASE / 2 + 1)
#define D_LEN (digits[N_O_D - 1] - digits[0] + sizeof_utf8(digits[N_O_D - 1]))

byte_t *digits[N_O_D];
byte_t *negation_table[N_O_D];
byte_t *addition_table[N_O_D][N_O_D];
byte_t *subtraction_table[N_O_D][N_O_D];
byte_t *multiplication_table[N_O_D][N_O_D];
byte_t *srt_division_table[N_O_D][N_O_D];

void table_buffer_ensure_space(int *len, int *bufsize, byte_t **buf) {
  if (*len > *bufsize - 8) {
    *buf = realloc(*buf, 2 * *bufsize);
    if (!buf) die("error on realloc");
    *bufsize *= 2;
  }
}

void init_digits() {
  if (BASE > 11)
    die("unsupported number base");
  byte_t d_positive[] = { '0', '1', '2', '3', '4', '5' };
  byte_t d_negative[] = { 0xC5, 0x8C, '9', '8', '7', '6', 0xE2, 0x86, 0x8A };
  byte_t *buf = malloc(15 * sizeof(byte_t));
  byte_t *ptr = d_positive;
  int utf8size;
  int len = 0;
  for (int i = 0; i < RADIUS; i++) {
    utf8size = sizeof_utf8(ptr);
    memcpy(buf + len, ptr, utf8size * sizeof(byte_t));
    digits[i] = buf + len;
    ptr += utf8size;
    len += utf8size;
  }
  ptr = d_negative + B_ODD * sizeof_utf8(d_negative);
  for (int i = RADIUS; i < N_O_D; i++) {
    utf8size = sizeof_utf8(ptr);
    memcpy(buf + len, ptr, utf8size * sizeof(byte_t));
    digits[i] = buf + len;
    ptr += utf8size;
    len += utf8size;
  }
  printf("init digits: ");
  printf("%.*s", (int)D_LEN, digits[0]);
  printf("\n");
}

void init_neg() {
  byte_t *buf = malloc(D_LEN * sizeof(byte_t));
  byte_t *ptr = buf;
  if (B_ODD) {
    memcpy(buf, digits[0], sizeof_utf8(digits[0]) * sizeof(byte_t));
    ptr += sizeof_utf8(digits[0]);
  }
  for (int i = RADIUS; i < N_O_D; i++) {
    int utf8size = sizeof_utf8(digits[i]);
    memcpy(ptr, digits[i], utf8size * sizeof(byte_t));
    ptr += utf8size;
  }
  for (int i = B_ODD; i < RADIUS; i++) {
    int utf8size = sizeof_utf8(digits[i]);
    memcpy(ptr, digits[i], utf8size * sizeof(byte_t));
    ptr += utf8size;
  }
  ptr = buf;
  for (int i = 0; i < N_O_D; i++) {
    negation_table[i] = ptr;
    inc_utf8(&ptr);
  }
  printf("init neg: ");
  for (int i = 0; i < N_O_D; i++) {
    printf("%.*s", sizeof_utf8(negation_table[i]), negation_table[i]);
  }
  printf("\n");
}

void init_add() {
  int bufsize = D_LEN * N_O_D * 2;
  byte_t *buf = malloc(bufsize * sizeof(byte_t));
  int len = 0;
  byte_t *d;
  int sum;
  int carry;
  for (int i = 0; i < RADIUS; i++) {
    for (int j = 0; j < RADIUS; j++) {
      table_buffer_ensure_space(&len, &bufsize, &buf);
      sum = i + j;
      carry = sum/RADIUS;
      d = digits[carry];
      memcpy(buf + len, d, sizeof_utf8(d) * sizeof(byte_t));
      len += sizeof_utf8(d);
      sum -= carry * BASE;
      if (sum >= 0)
        d = digits[sum];
      else
        d = digits[RADIUS - B_ODD - sum];
      memcpy(buf + len, d, sizeof_utf8(d) * sizeof(byte_t));
      len += sizeof_utf8(d);
    }
    for (int j = B_ODD; j < RADIUS; j++) {
      table_buffer_ensure_space(&len, &bufsize, &buf);
      sum = i - j;
      d = digits[0];
      memcpy(buf + len, d, sizeof_utf8(d) * sizeof(byte_t));
      len += sizeof_utf8(d);
      if (sum > 0) {
        d = digits[sum];
      } else if (sum == 0) {
        d = digits[(1 - B_ODD) * RADIUS];
      } else {
        d = digits[RADIUS - B_ODD - sum];
      }
      memcpy(buf + len, d, sizeof_utf8(d) * sizeof(byte_t));
      len += sizeof_utf8(d);
    }
  }
  for (int i = B_ODD; i < RADIUS; i++) {
    for (int j = 0; j < RADIUS; j++) {
      table_buffer_ensure_space(&len, &bufsize, &buf);
      sum = j - i;
      d = digits[RADIUS * (1 - B_ODD)];
      memcpy(buf + len, d, sizeof_utf8(d) * sizeof(byte_t));
      len += sizeof_utf8(d);
      if (sum >= 0) {
        d = digits[sum];
      } else d = digits[RADIUS - B_ODD - sum];
      memcpy(buf + len, d, sizeof_utf8(d) * sizeof(byte_t));
      len += sizeof_utf8(d);
    }
    for (int j = B_ODD; j < RADIUS; j++) {
      table_buffer_ensure_space(&len, &bufsize, &buf);
      sum = i + j;
      carry = sum/RADIUS;
      d = digits[(RADIUS + carry - B_ODD) * ( 1 + B_ODD * (carry - 1))];
      memcpy(buf + len, d, sizeof_utf8(d) * sizeof(byte_t));
      len += sizeof_utf8(d);
      sum -= carry * BASE;
      if (sum >= 0)
        d = digits[RADIUS - B_ODD + sum];
      else
        d = digits[-sum];
      memcpy(buf + len, d, sizeof_utf8(d) * sizeof(byte_t));
      len += sizeof_utf8(d);
    }
  }
  byte_t *ptr = buf;
  for (int i = 0; i < N_O_D; i++) {
    for (int j = 0; j < N_O_D; j++) {
      printf("%.*s", sizeof_utf8(ptr), ptr);
      ptr += sizeof_utf8(ptr);
      printf("%.*s ", sizeof_utf8(ptr), ptr);
      ptr += sizeof_utf8(ptr);
    }
    printf("\n");
  }
  free(buf);
}

void init_math() {
  init_digits();
  init_neg();
  init_add();
}

void math_free() {
  free(digits[0]);
  free(negation_table[0]);
  //free(addition_table[0]);
  /* free(multiplication_table[0]); */
  /* free(srt_division_table[0]); */
}

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
  while (i < s->length) {
    if (s->value[i] == '.') return i - 1;
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
