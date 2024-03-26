#include <better_string.h>
#include <strnum.h>
#include <stdio.h>

int main(int argv, char **argc) {

  string_t *num1 = init_string("1931");
  string_t *num2 = init_string("193");
  string_t *longstr = init_string("this is a long string (longer than thirteen characters)\n");

  printf("strings: ");
  print(num1);
  printf(" ");
  print(num2);
  printf("\n");

  printf("1: %lu, 2: %lu\n", num1->length, num2->length);

  printf("%d\n", string_comp(num1, num2));
  printf("%d\n", utf8cmp(num1->value[0].byte, num2->value[0].byte));

  print(longstr);

  string_free(num1);
  string_free(num2);
  string_free(longstr);

  return 0;
}
