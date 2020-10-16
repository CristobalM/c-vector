
extern "C"{
#include "intvector.h"
}

#include <iostream>
#include <chrono>

constexpr long total_insertions = 1 << 30;

void new_vec_experiment();
void raw_array_experiment();

int main(void){
    new_vec_experiment();
    raw_array_experiment();
}

void new_vec_experiment(){
    std::cout << "\n\nNEW VECTOR" << std::endl;
    struct vector_int vi;
    vector_int__init_vector_with_capacity(&vi, total_insertions);

    auto start = std::chrono::high_resolution_clock::now();
    for(long i = 0; i < total_insertions; i++){
        vector_int__insert_element(&vi, i);
        // vi.data[i] = i;
        // vector_int__set_element_at(&vi, i, i);
    }
    auto end = std::chrono::high_resolution_clock::now();


    auto duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "insertion: Total time in nanoseconds: " << duration.count() << std::endl;
    std::cout << "insertion: Average time in nanoseconds: " <<(double) duration.count() / (double)total_insertions   << std::endl;
     
    start = std::chrono::high_resolution_clock::now();
    int b = 0;
    for(long i = 0; i < total_insertions; i++){
        int a = vi.data[i];
        b += a;
    }
    end = std::chrono::high_resolution_clock::now();


    duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "lookup: Total time in nanoseconds: " << duration.count() << std::endl;
    std::cout << "lookup: Average time in nanoseconds: " <<(double) duration.count() / (double)total_insertions   << std::endl;
    std::cout << "b" << b << std::endl;



    vector_int__free_vector(&vi);

}

void raw_array_experiment(){

    std::cout << "\n\nRAW ARRAY" << std::endl;

    const long total_insertions = 1 << 30;

    int *arr = new int[total_insertions];
    
    auto start = std::chrono::high_resolution_clock::now();
    for(long i = 0; i < total_insertions; i++){
        arr[i] = i;
    }
    auto end = std::chrono::high_resolution_clock::now();


    auto duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "insertion: Total time in nanoseconds: " << duration.count() << std::endl;
    std::cout << "insertion: Average time in nanoseconds: " <<(double) duration.count() / (double)total_insertions   << std::endl;
     

    int b = 0;
    start = std::chrono::high_resolution_clock::now();
    for(long i = 0; i < total_insertions; i++){
        int a = arr[i];
        b += a;
    }
    end = std::chrono::high_resolution_clock::now();


    duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "lookup: Total time in nanoseconds: " << duration.count() << std::endl;
    std::cout << "lookup: Average time in nanoseconds: " <<(double) duration.count() / (double)total_insertions   << std::endl;
    std::cout << "b" << b << std::endl;
    
    delete [] arr;

}