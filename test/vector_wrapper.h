#include <cstring>
#include <exception>
#include <string>
extern "C" {
#include "vector.h"
}

template <typename T> class VectorWrapper {
  struct vector v;

public:
  VectorWrapper() {
    v.capacity = 1 << 5;
    v.element_size = sizeof(T);
    v.nof_items = 0;
    v.data = (char *)malloc(v.capacity * v.element_size);
  }

  ~VectorWrapper() { free(v.data); }

  void push_back(T element) {
    char *c_element = (char *)&element;
    int err = insert_element(&v, c_element);
    if (err)
      throw std::runtime_error("There was an error of code = " +
                               std::to_string(err) + " within push_back");
  }

  void insert(T element, int position) {
    char *c_element = (char *)&element;
    int err = insert_element_at(&v, c_element, position);
    if (err)
      throw std::runtime_error("There was an error of code = " +
                               std::to_string(err) + " within insert");
  }

  T operator[](int position) {
    T result;
    char *c_result;
    int err = get_element_at(&v, position, &c_result);
    memcpy(&result, c_result, v.element_size);
    return result;
  }

  int size() { return v.nof_items; }
};