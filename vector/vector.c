#include <stdlib.h>
#include <string.h>

#include "vector.h"

#define CHECK_ERR(err)                                                         \
  do {                                                                         \
    if (err) {                                                                 \
      return (err);                                                            \
    }                                                                          \
  } while (0)

static inline int new_element_capacity_check(struct vector *v) {
  if (v->capacity >= v->nof_items + 1)
    return 0;

  int next_capacity = v->capacity << 1;
  char *next_data = malloc(next_capacity * v->element_size);
  memcpy(next_data, v->data, v->element_size * v->nof_items);
  free(v->data);
  v->data = next_data;
  v->capacity = next_capacity;

  return VECTOR_SUCCESS_ECODE;
}

static inline int set_element_at_(struct vector *v, char *new_element,
                                  int position) {
  memcpy(v->data + position * v->element_size, new_element, v->element_size);

  return VECTOR_SUCCESS_ECODE;
}

int insert_element(struct vector *v, char *element) {
  CHECK_ERR(new_element_capacity_check(v));
  memcpy(v->data + v->nof_items * v->element_size, element, v->element_size);
  v->nof_items++;

  return VECTOR_SUCCESS_ECODE;
}

int insert_element_at(struct vector *v, char *element, int position) {
  CHECK_ERR(new_element_capacity_check(v));
  if (position < v->nof_items) {
    memmove(v->data + (position + 1) * v->element_size,
            v->data + position * v->element_size,
            (v->nof_items - position) * v->element_size);
  }
  CHECK_ERR(set_element_at_(v, element, position));

  return VECTOR_SUCCESS_ECODE;
}

int set_element_at(struct vector *v, char *new_element, int position) {
  CHECK_ERR(set_element_at_(v, new_element, position));

  return VECTOR_SUCCESS_ECODE;
}

int get_element_at(struct vector *v, int position, char **element_result) {
  *element_result = (v->data + position * v->element_size);
  return VECTOR_SUCCESS_ECODE;
}