#include <gtest/gtest.h>
#include <iostream>

extern "C" {
#include "vector.h"
}

define_cvector(int) declare_cvector(int)

    define_cvector(float) declare_cvector(float)

        using namespace std;

TEST(some_vector_test_s, test_int) {

  struct vector_int vi;

  vector_int__init_vector_with_capacity(&vi, 2);

  vector_int__insert_element(&vi, 1);
  vector_int__insert_element(&vi, 2);
  vector_int__insert_element(&vi, 3);
  vector_int__insert_element(&vi, 4);
  vector_int__insert_element(&vi, 5);

  ASSERT_EQ(1, vi.data[0]);
  ASSERT_EQ(2, vi.data[1]);
  ASSERT_EQ(3, vi.data[2]);
  ASSERT_EQ(4, vi.data[3]);
  ASSERT_EQ(5, vi.data[4]);

  ASSERT_EQ(5, vi.nof_items);
  vector_int__free_vector(&vi);
}

TEST(some_vector_test_s, test_float) {
  struct vector_float vf;

  vector_float__init_vector_with_capacity(&vf, 2);

  vector_float__insert_element(&vf, 1.5);
  vector_float__insert_element(&vf, 2.5);
  vector_float__insert_element(&vf, 3.5);
  vector_float__insert_element(&vf, 4.5);
  vector_float__insert_element(&vf, 5.5);

  ASSERT_EQ(1.5, vf.data[0]);
  ASSERT_EQ(2.5, vf.data[1]);
  ASSERT_EQ(3.5, vf.data[2]);
  ASSERT_EQ(4.5, vf.data[3]);
  ASSERT_EQ(5.5, vf.data[4]);

  ASSERT_EQ(5, vf.nof_items);

  vector_float__free_vector(&vf);
}

TEST(some_vector_test_s, test_insert) {

  struct vector_int vi;
  vector_int__init_vector_with_capacity(&vi, 2);

  vector_int__insert_element(&vi, 0);
  vector_int__insert_element(&vi, 2);
  vector_int__insert_element(&vi, 0);

  ASSERT_EQ(2, vi.data[1]);

  vector_int__insert_element_at(&vi, 123, 123);

  ASSERT_EQ(123, vi.data[123]);
  ASSERT_EQ(124, vi.nof_items);

  for (int i = 0; i < 123; i++) {
    if (i != 1)
      ASSERT_EQ(0, vi.data[i]) << "Fails at i  = " << i;
    else
      ASSERT_EQ(2, vi.data[i]) << "Fails at i  = " << i;
  }

  ASSERT_EQ(124, vi.nof_items);

  vector_int__free_vector(&vi);
}

TEST(some_vector_test_s, test_insert_2) {

  struct vector_int vi;
  vector_int__init_vector_with_capacity(&vi, 2);

  vector_int__insert_element(&vi, 0);
  vector_int__insert_element(&vi, 2);
  vector_int__insert_element(&vi, 0);

  ASSERT_EQ(2, vi.data[1]);

  vector_int__insert_element_at(&vi, 123, 0);

  ASSERT_EQ(4, vi.nof_items);
  ASSERT_EQ(123, vi.data[0]);
  ASSERT_EQ(0, vi.data[1]);
  ASSERT_EQ(2, vi.data[2]);
  ASSERT_EQ(0, vi.data[3]);

  vector_int__free_vector(&vi);
}

TEST(some_vector_test_s, test_resize) {

  struct vector_int vi;
  vector_int__init_vector_with_capacity(&vi, 2);

  for (int i = 0; i < 100000; i++) {
    vector_int__insert_element(&vi, i);
  }

  for (int i = 0; i < 100000; i++) {
    ASSERT_EQ(i, vi.data[i]);
  }
  vector_int__free_vector(&vi);
}
