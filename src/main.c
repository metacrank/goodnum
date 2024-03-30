#include <better_string.h>
#include <strnum.h>
#include <stdio.h>

int main(int argv, char **argc) {

  string_t *num1 = init_string("1931");
  string_t *num2 = init_string("193");
  string_t *longstr = init_string("this is a long string\u218b...\n");

  printf("strings: ");
  print(num1);
  printf(" ");
  print(num2);
  printf("\n");

  printf("1: %lu, 2: %lu\n", num1->length, num2->length);

  printf("%d\n", string_comp(num1, num2));

  printf("longlen=%lu\n", longstr->length);

  print(longstr);

  string_free(num1);
  string_free(num2);
  string_free(longstr);

  init_math();

  num1 = init_string("123000.012345678900000034030v00");
  print(num1);
  printf("\n");
  neg(num1);
  print(num1);
  printf("\n");
  fp(num1);
  print(num1);
  printf("\n");
  string_reverse(num1);
  print(num1);
  printf("\n");
  string_free(num1);

  math_free();

  return 0;
}
