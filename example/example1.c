#include <stdio.h>

#include "intvector.h"
int main(void) {

  struct vector_int vi;

  vector_int__init_vector_with_capacity(&vi, 10);

  for (int i = 0; i < 100; i++) {
    vector_int__insert_element(&vi, i);
  }

  for (int i = 0; i < 100; i++)
    printf("%d\n", vi.data[i]);

  return 0;
}
