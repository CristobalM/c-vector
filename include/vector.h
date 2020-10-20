#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>
#include <string.h>

/* BEGIN Error codes */
#define VECTOR_SUCCESS_ECODE 0
#define VECTOR_MAX_SZ_REACHED 1
/* END Error codes */

#define C_VECTOR_CHECK_ERR(err)                                                \
  do {                                                                         \
    if (err) {                                                                 \
      return (err);                                                            \
    }                                                                          \
  } while (0)

#define define_cvector(vtype, indtype)                                         \
  struct vector_##vtype {                                                      \
    indtype nof_items;                                                         \
    indtype capacity;                                                          \
    vtype *data;                                                               \
  };                                                                           \
  int vector_##vtype##__insert_element(struct vector_##vtype *v,               \
                                       vtype element);                         \
  int vector_##vtype##__insert_element_at(struct vector_##vtype *v,            \
                                          vtype element, indtype position);    \
  int vector_##vtype##__set_element_at(struct vector_##vtype *v,               \
                                       vtype new_element, indtype position);   \
  vtype vector_##vtype##__get_element_at(struct vector_##vtype *v,             \
                                         indtype position);                    \
  int vector_##vtype##__init_vector(struct vector_##vtype *v);                 \
  int vector_##vtype##__init_vector_with_capacity(struct vector_##vtype *v,    \
                                                  indtype capacity);           \
  int vector_##vtype##__free_vector(struct vector_##vtype *v);

#define declare_cvector(vtype, indtype)                                        \
  int vector_##vtype##__new_element_capacity_check(struct vector_##vtype *v,   \
                                                   indtype position);          \
  int vector_##vtype##__new_element_capacity_check(struct vector_##vtype *v,   \
                                                   indtype position) {         \
    indtype expected_sz;                                                       \
    if (position > -1 && position + 1 > v->nof_items) {                        \
      expected_sz = position + 1;                                              \
    } else {                                                                   \
      expected_sz = v->nof_items;                                              \
    }                                                                          \
    if (v->capacity >= expected_sz + 1)                                        \
      return VECTOR_SUCCESS_ECODE;                                             \
    indtype next_capacity = v->capacity;                                       \
    if (next_capacity == 0) {                                                  \
      next_capacity++;                                                         \
    }                                                                          \
    while (next_capacity < expected_sz) {                                      \
      next_capacity <<= 1;                                                     \
    }                                                                          \
    vtype *next_data = (vtype *)malloc(next_capacity * sizeof(vtype));         \
    if (v->capacity > 0) {                                                     \
      memcpy(next_data, v->data, sizeof(vtype) * v->nof_items);                \
      free(v->data);                                                           \
    }                                                                          \
    v->data = next_data;                                                       \
    v->capacity = next_capacity;                                               \
    return VECTOR_SUCCESS_ECODE;                                               \
  }                                                                            \
  static inline int vector_##vtype##__set_element_at_(                         \
      struct vector_##vtype *v, vtype new_element, indtype position) {         \
    v->data[position] = new_element;                                           \
    return VECTOR_SUCCESS_ECODE;                                               \
  }                                                                            \
  int vector_##vtype##__insert_element(struct vector_##vtype *v,               \
                                       vtype element) {                        \
    C_VECTOR_CHECK_ERR(                                                        \
        vector_##vtype##__new_element_capacity_check(v, v->nof_items));        \
    v->data[v->nof_items++] = element;                                         \
    return VECTOR_SUCCESS_ECODE;                                               \
  }                                                                            \
  int vector_##vtype##__insert_element_at(struct vector_##vtype *v,            \
                                          vtype element, indtype position) {   \
    C_VECTOR_CHECK_ERR(                                                        \
        vector_##vtype##__new_element_capacity_check(v, position));            \
    const size_t sz = sizeof(vtype);                                           \
    if (position < v->nof_items) {                                             \
      memmove(v->data + (position + 1), v->data + position,                    \
              (v->nof_items - position) * sz);                                 \
    } else {                                                                   \
      memset(v->data + v->nof_items, 0, (position - v->nof_items) * sz);       \
    }                                                                          \
    v->data[position] = element;                                               \
    if (position + 1 > v->nof_items) {                                         \
      v->nof_items = position + 1;                                             \
    } else {                                                                   \
      v->nof_items++;                                                          \
    }                                                                          \
    return VECTOR_SUCCESS_ECODE;                                               \
  }                                                                            \
  int vector_##vtype##__set_element_at(struct vector_##vtype *v,               \
                                       vtype new_element, indtype position) {  \
    C_VECTOR_CHECK_ERR(                                                        \
        vector_##vtype##__set_element_at_(v, new_element, position));          \
    return VECTOR_SUCCESS_ECODE;                                               \
  }                                                                            \
  vtype vector_##vtype##__get_element_at(struct vector_##vtype *v,             \
                                         indtype position) {                   \
    return v->data[position];                                                  \
  }                                                                            \
  int vector_##vtype##__init_vector(struct vector_##vtype *v) {                \
    return vector_##vtype##__init_vector_with_capacity(v, 0);                  \
  }                                                                            \
  int vector_##vtype##__init_vector_with_capacity(struct vector_##vtype *v,    \
                                                  indtype capacity) {          \
    v->capacity = capacity;                                                    \
    v->nof_items = 0;                                                          \
    if (capacity > 0)                                                          \
      v->data = (vtype *)malloc(v->capacity * sizeof(vtype));                  \
    return VECTOR_SUCCESS_ECODE;                                               \
  }                                                                            \
  int vector_##vtype##__free_vector(struct vector_##vtype *v) {                \
    free(v->data);                                                             \
    return VECTOR_SUCCESS_ECODE;                                               \
  }

#endif /* _VECTOR_H_ */
