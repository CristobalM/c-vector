#ifndef _VECTOR_H_
#define _VECTOR_H_

/* BEGIN Error codes */
#define VECTOR_SUCCESS_ECODE 0
/* END Error codes */

struct vector {
  int element_size;
  int nof_items;
  int capacity;
  char *data;
};

int insert_element(struct vector *v, char *element);
int insert_element_at(struct vector *v, char *element, int position);
int set_element_at(struct vector *v, char *new_element, int position);
int get_element_at(struct vector *v, int position, char **element_result);

int init_vector(struct vector *v);

#endif /* _VECTOR_H_ */
