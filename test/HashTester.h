//
// Created by tmarc on 29/03/2023.
//

#ifndef RA_HANDIN_2_HASHTESTER_H
#define RA_HANDIN_2_HASHTESTER_H

#include <string>
#include <chrono>


template <typename HashFn>
class HashTester {
    HashFn hashFn;

public:
    explicit HashTester(HashFn hashFn) : hashFn(hashFn) {}

    [[nodiscard]] auto test(unsigned long long n) {
        auto start = std::chrono::high_resolution_clock::now();

        for (unsigned long long i = 0; i < n; i++) {
            auto h = hashFn.hash(i);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        return time;
    }
};

#endif //RA_HANDIN_2_HASHTESTER_H
