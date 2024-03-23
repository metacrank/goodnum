#include <better_string.h>
#include <strnum.h>
#include <stdio.h>

int main(int argv, char **argc) {

  string_t *num1 = init_string((byte_t*)"123");
  string_t *num2 = init_string((byte_t*)"5.4");

  printf("strings: %s, %s\n", num1->value, num2->value);
  for (int i = 0; i < num2->length; i++) {
    printf("%d ", (int)(num2->value[i]));
  }
  printf("\n");


  string_free(num1);
  string_free(num2);

  return 0;
}
