#include <better_string.h>
#include <strnum.h>
#include <stdio.h>

int main(int argv, char **argc) {

  init_math();

  string_t *num1 = init_string(U"123.012342");
  string_t *num2 = init_string(U"892.298761");

  print(num1);
  printf("\n");
  print(num2);
  printf("\n");

  string_t *sm = sum(num1, num2, NULL, NULL, NULL, NULL);

  print(sm);
  printf("\n^ sum\n");

  double dsm = string_to_double(sm);
  printf("float: %f\n", dsm);

  ip(sm);
  int ism = string_to_int(sm);
  printf("ip: ");
  print(sm);
  printf("\nint: %d\n", ism);

  string_t *intstr = int_to_string(1);
  print(intstr);
  printf("\n");

  string_t *doublestr = double_to_string(6, 3, false);
  print(doublestr);
  printf("\n");

  string_free(intstr);
  string_free(doublestr);

  string_reverse(num1);
  printf("num1 reversed: ");
  print(num1);
  printf("\n");

  string_free(num1);
  string_free(num2);
  string_free(sm);

  string_t *two = int_to_string(2);
  string_t *three = int_to_string(3);
  print(two);
  printf("\n");
  print(three);
  printf("\n* =\n");

  string_t *prod = product(two, three);
  print(prod);
  printf("\n");

  string_free(two);
  string_free(three);
  string_free(prod);

  math_free();

  FILE *FP = fopen("test.txt", "rb");
  string_t *f = file_read(FP);
  if (!f) return 1;
  fclose(FP);
  print(f);
  string_free(f);

  return 0;
}
