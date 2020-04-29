#include <stdlib.h>
#include <string.h>

#include "vector.h"

#define CHECK_ERR(err)                                                         \
  do {                                                                         \
    if (err) {                                                                 \
      return (err);                                                            \
    }                                                                          \
  } while (0)

static inline int new_element_capacity_check(struct vector *v, int position) {
  int expected_sz;
  if (position > -1 && position + 1 > v->nof_items) {
    expected_sz = position + 1;
  } else {
    expected_sz = v->nof_items;
  }
  if (v->capacity >= expected_sz + 1)
    return 0;

  int next_capacity = v->capacity;
  do {
    next_capacity = next_capacity << 1;
  } while (next_capacity < expected_sz);

  if (next_capacity > VECTOR_MAX_CAPACITY) {
    return VECTOR_MAX_SZ_REACHED;
  }

  char *next_data = calloc(next_capacity, v->element_size);
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
  CHECK_ERR(new_element_capacity_check(v, -1));
  memcpy(v->data + v->nof_items * v->element_size, element, v->element_size);
  v->nof_items++;

  return VECTOR_SUCCESS_ECODE;
}

int insert_element_at(struct vector *v, char *element, int position) {
  CHECK_ERR(new_element_capacity_check(v, position));
  if (position < v->nof_items) {
    memmove(v->data + (position + 1) * v->element_size,
            v->data + position * v->element_size,
            (v->nof_items - position) * v->element_size);
  }
  CHECK_ERR(set_element_at_(v, element, position));
  if (position + 1 > v->nof_items) {
    v->nof_items = position + 1;
  } else {
    v->nof_items++;
  }

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

int init_vector(struct vector *v, int element_size) {
  return init_vector_with_capacity(v, element_size, 8);
}

int init_vector_with_capacity(struct vector *v, int element_size,
                              int capacity) {
  v->capacity = capacity;
  v->data = calloc(v->capacity, element_size);
  v->nof_items = 0;
  v->element_size = element_size;
  return VECTOR_SUCCESS_ECODE;
}

int free_vector(struct vector *v) {
  free(v->data);
  return VECTOR_SUCCESS_ECODE;
}
