#include <better_string.h>
#include <strnum.h>
#include <stdio.h>

int main(int argv, char **argc) {

  string_t *num1 = init_string("123");
  string_t *num2 = init_string("5.4");

  printf("strings: ");
  print(num1);
  printf(" ");
  print(num2);
  printf("\n");

  string_free(num1);
  string_free(num2);

  return 0;
}
