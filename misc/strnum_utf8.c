#include <strnum.h>
#include <better_string.h>
#include <macros.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define BASE DEFAULT_NUMBER_BASE
#define B_ODD (BASE % 2)
#define N_O_D (BASE + 2 * (1 - B_ODD))
#define RADIUS (BASE / 2 + 1)
#define D_LEN (digits[N_O_D - 1] - digits[0] + sizeof_utf8(digits[N_O_D - 1]))
#define MODULO 15

// in the future, do not use pointer arrays for utf32
byte_t *digits[N_O_D];
int digit_values[MODULO];
byte_t *negation_table[MODULO];
byte_t *addition_carry_table[MODULO][MODULO];
byte_t *addition_sum_table[MODULO][MODULO];
byte_t *subtraction_carry_table[MODULO][MODULO];
byte_t *subtraction_sum_table[MODULO][MODULO];
byte_t *multiplication_table[MODULO][MODULO];
byte_t *multiplication_table[MODULO][MODULO];
byte_t *srt_division_table[MODULO][MODULO];

/*
  int di(wchar_t d) {
  return d % MODULO;
  }
*/

int di(byte_t *d) {
  return *d % MODULO;
}

int didx(int i) {
  return di(digits[i]);
}

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
  negation_table[di(digits[0])] = digits[RADIUS * (1 - B_ODD)];
  for (int i = 1; i < RADIUS; i++) {
    negation_table[di(digits[i])] = digits[RADIUS - B_ODD + i];
  }
  for (int i = RADIUS; i < N_O_D; i++) {
    negation_table[di(digits[i])] = digits[i - RADIUS + B_ODD];
  }
  printf("init neg: ");
  for (int i = 0; i < N_O_D; i++) {
    printf("%.*s", sizeof_utf8(negation_table[di(digits[i])]),
           negation_table[di(digits[i])]);
  }
  printf("\n");
}

void init_digit_values() {
  for (int i = 0; i < RADIUS; i++) {
    digit_values[di(digits[i])] = i;
  }
  for (int i = RADIUS; i < N_O_D; i++) {
    digit_values[di(digits[i])] = RADIUS - i - B_ODD;
  }
}

void init_add() {
  int sum, carry;
  int b, a = 0;
  for (int i = 0; i < RADIUS; i++) {
    b = 0;
    for (int j = 0; j < RADIUS; j++) {
      sum = i + j;
      carry = sum/RADIUS;
      addition_carry_table[didx(a)][didx(b)] = digits[carry];
      sum -= carry * BASE;
      if (sum >= 0)
        addition_sum_table[didx(a)][didx(b)] = digits[sum];
      else
        addition_sum_table[didx(a)][didx(b)] = digits[RADIUS - B_ODD - sum];
      b++;
    }
    for (int j = B_ODD; j < RADIUS; j++) {
      sum = i - j;
      addition_carry_table[didx(a)][didx(b)] = digits[0];
      if (sum > 0) {
        addition_sum_table[didx(a)][didx(b)] = digits[sum];
      } else if (sum == 0) {
        addition_sum_table[didx(a)][didx(b)] = digits[(1 - B_ODD) * RADIUS];
      } else {
        addition_sum_table[didx(a)][didx(b)] = digits[RADIUS - B_ODD - sum];
      }
      b++;
    }
    a++;
  }
  for (int i = B_ODD; i < RADIUS; i++) {
    b = 0;
    for (int j = 0; j < RADIUS; j++) {
      sum = j - i;
      addition_carry_table[didx(a)][didx(b)] = digits[RADIUS * (1 - B_ODD)];
      if (sum >= 0)
        addition_sum_table[didx(a)][didx(b)] = digits[sum];
      else
        addition_sum_table[didx(a)][didx(b)] = digits[RADIUS - B_ODD - sum];
      b++;
    }
    for (int j = B_ODD; j < RADIUS; j++) {
      sum = i + j;
      carry = sum/RADIUS;
      addition_carry_table[didx(a)][didx(b)] =
        digits[(RADIUS + carry - B_ODD) * ( 1 + B_ODD * (carry - 1))];
      sum -= carry * BASE;
      if (sum >= 0)
        addition_sum_table[didx(a)][didx(b)] = digits[RADIUS - B_ODD + sum];
      else
        addition_sum_table[didx(a)][didx(b)] = digits[-sum];
      b++;
    }
    a++;
  }
  printf("init add:\n");
  // print out resulting table
  for (int i = 0; i < N_O_D; i++) {
    for (int j = 0; j < N_O_D; j++) {
      byte_t *b1 = addition_carry_table[didx(i)][didx(j)];
      byte_t *b2 = addition_sum_table[didx(i)][didx(j)];
      printf("%.*s%.*s ", sizeof_utf8(b1), b1, sizeof_utf8(b2), b2);
    }
    printf("\n");
  }
}

void init_sub() {
  int m, n, r;
  for (int i = 0; i < N_O_D; i++) {
    for (int j = 0; j < N_O_D; j++) {
      m = di(digits[i]);
      n = di(digits[j]);
      r = di(negation_table[di(digits[j])]);
      subtraction_carry_table[m][n] = addition_carry_table[m][r];
      subtraction_sum_table[m][n] = addition_sum_table[m][r];
    }
  }
  printf("init sub:\n");
  // print out resulting table
  for (int i = 0; i < N_O_D; i++) {
    for (int j = 0; j < N_O_D; j++) {
      byte_t *b1 = subtraction_carry_table[didx(i)][didx(j)];
      byte_t *b2 = subtraction_sum_table[didx(i)][didx(j)];
      printf("%.*s%.*s ", sizeof_utf8(b1), b1, sizeof_utf8(b2), b2);
    }
    printf("\n");
  }
}

void init_mul() {
  int product, carry;
  int b, a = 0;
  for (int i = 0; i < RADIUS; i++) {
    b = 0;
    for (int j = 0; j < RADIUS; j++) {

      b++;
    }
    for (int j = B_ODD; j < RADIUS; j++) {

      b++;
    }
    a++;
  }
  for (int i = B_ODD; i < RADIUS; i++) {
    b = 0;
    for (int j = 0; j < RADIUS; j++) {

      b++;
    }
    for (int j = B_ODD; j < RADIUS; j++) {

      b++;
    }
    a++;
  }
}

void init_math() {
  init_digits();
  init_digit_values();
  init_neg();
  init_add();
  init_sub();
}

void math_free() {
  free(digits[0]);
  //free(negation_table[0]);
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

long string_to_int(string_t *s) {
  byte_t *p = s->value + s->length;
  dec_utf8(&p);
  long d = 0;
  long i;
  for (i = 0; p > s->value; i++) {
    d += digit_values[di(p)] * pow(BASE, i);
    dec_utf8(&p);
  }
  d += digit_values[di(p)] * pow(BASE, i);
  return d;
}

long double string_to_double(string_t *s) {
  byte_t *p = s->value + s->length;
  dec_utf8(&p);
  long double d = 0;
  long r = 0;
  long i;
  for (i = 0; p > s->value; i++) {
    if (*p == '.') {
      r = i;
      i--;
      p--;
      continue;
    }
    d += digit_values[di(p)] * pow(BASE, i);
    dec_utf8(&p);
  }
  d += digit_values[di(p)] * pow(BASE, i);
  d = d / pow(BASE, r);
  return d;
}

string_t *int_to_string(long d) {
  // get from pool;
  string_t *s = init_string("");
  int offset = (1 - (d < 0) * 2) * 0.001;
  long abs_d = d * ((d >= 0) * 2 - 1);
  int power = log10(abs_d) / log10(BASE) + 1;
  int digit = round(d / pow(BASE, power) + offset);
  if (digit == 1) {
    string_append(s, digits[1]);
  } else if (digit == -1) {
    string_append(s, digits[RADIUS - B_ODD + 1]);
  }
  d -= digit * pow(BASE, power);
  long next;
  while(power > 0) {
    power--;
    digit = round(d / pow(BASE, power) + offset);
    d -= digit * pow(BASE, power);
    if (digit > 0) {
      string_append(s, digits[digit]);
    } else if (digit < 0) {
      string_append(s, digits[RADIUS - B_ODD - digit]);
    } else {
      if (d + offset > 0 || !B_ODD) {
        string_append(s, digits[0]);
      } else {
        string_append(s, digits[RADIUS]);
      }
    }
  }
  return s;
}

string_t *double_to_string(long double f) {
  // get from pool;
  string_t *s = init_string("");
  return s;
}


/*
string_t *neg(string_t *s) {
  for (int i = 0; i < s->length; i++) {
    s->value[i] = *negation_table[di(s->value[i])];
  }
}
*/

string_t *neg(string_t *s) {
  int idx = 0;
  while(idx < s->length) {
    if (s->value[idx] == '.') {
      idx++;
      continue;
    }
    byte_t *neg = negation_table[di(s->value + idx)];
    if (neg == NULL) return s;
    int utf8size = sizeof_utf8(s->value + idx);
    int neg_size = sizeof_utf8(neg);
    if (utf8size > neg_size) {
      int c = idx + neg_size;
      for (int i = idx + utf8size; i < s->length; i++) {
        s->value[c] = s->value[i];
        c++;
      }
      s->length -= utf8size - neg_size;
    } else if (utf8size < neg_size) {
      string_ensure_space(s, neg_size - utf8size);
      int c = s->length - 1 + neg_size - utf8size;
      for (int i = s->length - 1; i >= idx + utf8size; i--) {
        s->value[c] = s->value[i];
        c--;
      }
      s->length += neg_size - utf8size;
    }
    memcpy(s->value + idx, neg, neg_size);
    idx += neg_size;
  }
  return s;
}

string_t *ip(string_t *s) {
  int len;
  for (len = 0; len < s->length; len++) {
    if (s->value[len] == '.') break;
  }
  s->length = len;
  return s;
}

string_t *fp(string_t *s) {
  int len;
  for (len = 0; len < s->length; len++) {
    if (s->value[len] == '.') break;
  }
  int i;
  for (i = 0; len < s->length; i++) {
    s->value[i] = s->value[len];
    len++;
  }
  s->length = i;
  return s;
}

string_t *sum(string_t *m, string_t *n, byte_t *m_radix, byte_t *n_radix, string_t *sum_buffer, byte_t *sb_radix) {
  // get from pool
  // check whether string will be long enough and won't need to be realloced
  string_t *s = init_string("");
  byte_t *svalue = s->value;

  bool m_high = false;
  byte_t *pm = m->value;
  byte_t *pn = n->value;
  byte_t *sum;
  byte_t *carry = digits[0];

  byte_t *m_end = pm + m->length;
  byte_t *n_end = pn + n->length;
  while(true) {
    inc_utf8(&pm);
    inc_utf8(&pn);
    if (pm == m_end || *pm == '.') {
      while (pn != n_end && *pn != '.') {
        inc_utf8(&pn);
      }
      break;
    } else if (pn == n_end || *pn == '.') {
      while (pm != m_end && *pm != '.') {
        inc_utf8(&pm);
      }
      m_high = true;
      break;
    }
  }
  if (pm != m_end) {
    if (pn != n_end) {
      byte_t *pm2 = pm + 1;
      byte_t *pn2 = pn + 1;
      while(true) {
        if (pm2 == m_end) {
          if (pn2 != n_end) {
            byte_t *p = n_end;
            dec_utf8(&p);
            while(p >= pn2) {
              // replace with memcpy when bufsize is guaranteed to be enough
              string_append(s, p);
              dec_utf8(&p);
            }
          }
          break;
        } else if (pn2 == n_end) {
          byte_t *p = m_end;
          dec_utf8(&p);
          while (p >= pm2) {
            // replace with memcpy
            string_append(s, p);
            dec_utf8(&p);
          }
          break;
        }
        inc_utf8(&pm2);
        inc_utf8(&pn2);
      }
      // add up until radix point
      dec_utf8(&pm2);
      dec_utf8(&pn2);
      //TODO: for even bases, check if rightmost digit will be a positive or negative form of 0 or B/2
      while(pm2 > pm) {
        sum = addition_sum_table[di(pm2)][di(pn2)];
        sum = addition_sum_table[di(sum)][di(carry)];
        carry = addition_carry_table[di(pm2)][di(pn2)];
        // replace with memcpy
        string_append(s, sum);
        dec_utf8(&pm2);
        dec_utf8(&pn2);
      }
      //replace with memcpy
      string_append(s, pm);

    } else {
      byte_t *p = m_end;
      dec_utf8(&p);
      while(p >= pm) {
        // replace with memcpy
        string_append(s, p);
        dec_utf8(&p);
      }
    }
  } else {
    if (pn != n_end) {
      byte_t *p = n_end;
      dec_utf8(&p);
      while(p >= pn) {
        string_append(s, p);
        dec_utf8(&p);
      }
    }
  }

  while(pm > m->value) {
    dec_utf8(&pm);
    dec_utf8(&pn);
    sum = addition_sum_table[di(pm)][di(pn)];
    sum = addition_sum_table[di(sum)][di(carry)];
    carry = addition_carry_table[di(pm)][di(pn)];
    //replace with memcpy
    string_append(s, sum);
  }

  string_reverse(s);
  return s;
}

string_t *diff(string_t *m, string_t *n) {
  // temporary definition
  string_t *nneg = string_copy(n);
  neg(nneg);
  return sum(m, nneg, NULL, NULL, NULL, NULL);
}

string_t *product(string_t *m, string_t *n) {}

string_t *quotient(string_t *m, string_t *n) {}
