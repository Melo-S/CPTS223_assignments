// OpenMP header
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <numeric>

void hello_world()
{
    std::cout << "(0) Test OpenMP" << std::endl;

    // Get the total number of cores in the system
    const auto processor_count = std::thread::hardware_concurrency();
    // Set the number of threads used in OpenMP
    omp_set_num_threads(processor_count);
    // Begin of parallel region
#pragma omp parallel
    {
        // Getting thread number
        int tid = omp_get_thread_num();
        printf("Welcome from thread = %d\n",
            tid);

        if (tid == 0)
        {

            // Only master thread does this
            int nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n",
                nthreads);
        }
    }

    std::cout << "OpenMP test finished" << std::endl << std::endl;
}

void calSum()
{
    std::cout << "(1) Test calSum()" << std::endl;
    
    int sum = 0;
    int data_size = 100000000;
    int num_threads = 8;
    int workload = data_size / num_threads;
    int *data = new int[data_size];
    for (int i = 0; i < data_size; ++i)
    {
        data[i] = 1;
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // -------------- below TODO: OpenMP implementation --------------
// find the sum of the array "data" and assign to the variable "sum"
// will compare it with the one found by STL accumulate() later
    omp_set_num_threads(num_threads);
#pragma omp parallel
    {
        int local_sum = 0;

#pragma omp for
        for (int i = 0; i < data_size; ++i)
        {
            local_sum += data[i];
        }

#pragma omp critical
        {
            sum += local_sum;  
        }
    }

    // -------------- above TODO: OpenMP implementation --------------

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time of calSum() by OpenMP = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
              << "[milliseconds]" << std::endl;

    std::vector<int> vect(data, data + data_size);
    begin = std::chrono::steady_clock::now();
    int sumSTL = std::accumulate(vect.begin(), vect.end(), 0);
    end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time of calSum() by STL accumulate() = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
              << "[milliseconds]" << std::endl;

    assert(sum == data_size);
    assert(sum == sumSTL);
    std::cout << "calSum() assert pass!" << std::endl << std::endl;
}

// Find the max value in the data array
void calMax()
{
    std::cout << "(2) Test calMax()" << std::endl;
    
    int max = 0;
    int data_size = 100000000;
    int num_threads = 2;
    int workload = data_size / num_threads;
    int *data = new int[data_size];
    for (int i = 0; i < data_size; ++i)
    {
        data[i] = rand() % data_size;
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    // -------------- below TODO: OpenMP implementation --------------
 // find the max value from the array "data" and assign to the variable "max"
 // will compare it with the one found by STL max_element() later
    omp_set_num_threads(num_threads);
#pragma omp parallel
    {
        int local_max = INT_MIN;

#pragma omp for
        for (int i = 0; i < data_size; ++i)
        {
            if (data[i] > local_max)
            {
                local_max = data[i];
            }
        }

#pragma omp critical
        {
            if (local_max > max)
            {
                max = local_max;  
            }
        }
    }

    // -------------- above TODO: OpenMP implementation --------------


    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time of calMax() by OpenMP = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
              << "[milliseconds]" << std::endl;

    std::vector<int> vect(data, data + data_size);
    begin = std::chrono::steady_clock::now();
    int maxSTL = *std::max_element(vect.begin(), vect.end());
    end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time of calMax() by STL max_element() = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
              << "[milliseconds]" << std::endl;

    assert(max == maxSTL);
    std::cout << "calMax() assert pass!" << std::endl << std::endl;
}