#include <gtest/gtest.h>


#include <iostream>
#include "vector_wrapper.h"

using namespace std;

TEST(some_vector_test_s, test_int){
    VectorWrapper<int> vw;

    vw.push_back(1);
    vw.push_back(2);
    vw.push_back(3);
    vw.push_back(4);
    vw.push_back(5);

    ASSERT_EQ(1, vw[0]);
    ASSERT_EQ(2, vw[1]);
    ASSERT_EQ(3, vw[2]);
    ASSERT_EQ(4, vw[3]);
    ASSERT_EQ(5, vw[4]);

    ASSERT_EQ(5, vw.size());
}


TEST(some_vector_test_s, test_float){
    VectorWrapper<float> vw;

    vw.push_back(1.5);
    vw.push_back(2.5);
    vw.push_back(3.5);
    vw.push_back(4.5);
    vw.push_back(5.5);

    ASSERT_EQ(1.5, vw[0]);
    ASSERT_EQ(2.5, vw[1]);
    ASSERT_EQ(3.5, vw[2]);
    ASSERT_EQ(4.5, vw[3]);
    ASSERT_EQ(5.5, vw[4]);

    ASSERT_EQ(5, vw.size());
}


TEST(some_vector_test_s, test_resize){
    VectorWrapper<int> vw;

    for(int i = 0; i < 100000; i++){
      if(i == 32){
        int debug = 0;
      }
        vw.push_back(i);
    }

    for(int i = 0; i < 100000; i++){
        ASSERT_EQ(i, vw[i]);
    }
}