#include <better_string.h>
#include <strnum.h>
#include <stdio.h>

int main(int argv, char **argc) {

  init_math();

  string_t *num1 = init_string(U"16,2");
  string_t *num2 = init_string(U"9,99");

  print(num1);
  printf("\n");
  print(num2);
  printf("\n");

  string_t *sm = sum(num1, num2, NULL, NULL, NULL, NULL);

  print(sm);
  printf("\n");

  string_free(num1);
  string_free(num2);
  string_free(sm);

  math_free();

  return 0;
}
