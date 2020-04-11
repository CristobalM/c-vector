#include <cstring>
#include <exception>
#include <string>
extern "C" {
#include "vector.h"
}

template <typename T> class VectorWrapper {
  struct vector v;

public:
  VectorWrapper() { init_vector(&v, sizeof(T)); }

  ~VectorWrapper() { free_vector(&v); }

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

  T operator[](int position) { return *((T *)v.data + position); }

  int size() { return v.nof_items; }
};