//
// Created by tmarc on 12/04/2023.
//

#ifndef RA_HANDIN_2_SUMSETTESTER_H
#define RA_HANDIN_2_SUMSETTESTER_H

#include "../sum-set/SumSet.h"
#include <cmath>
#include <chrono>
#include <fstream>


struct SumSetTesterResult {
    unsigned long long keyCount;
    unsigned long long updateCount;
    long long updateTime;

    friend std::ostream& operator<<(std::ostream& os, const SumSetTesterResult& result) {
        os << "Key count: " << result.keyCount << std::endl;
        os << "Update count: " << result.updateCount << std::endl;
        os << "Update time: " << (double) result.updateTime / 1e6 << "ms" << std::endl;
        return os;
    }
};


class SumSetTester {
    std::vector<SumSetTesterResult> results;

public:
    SumSetTester() = default;

    auto test(SumSet& sumSet, unsigned long long keyCount, unsigned long long updateCount = 1e9) {
        auto start = std::chrono::high_resolution_clock::now();

        for (unsigned long long i = 0; i < updateCount; i++) {
            sumSet.update(i % keyCount, 1);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        sumSet.clear();

        SumSetTesterResult result = {
                .keyCount = keyCount,
                .updateCount = updateCount,
                .updateTime = time
        };

        results.push_back(result);
        return result;
    }

    void dumpResults(const std::string& filename) {
        std::ofstream file;
        file.open(filename);

        file << "Key Count\tUpdate Count\tUpdate Time" << std::endl;
        for (const auto& result : results) {
            file << result.keyCount << "\t" << result.updateCount << "\t" << result.updateTime << std::endl;
        }

        file.close();
    }
};

#endif //RA_HANDIN_2_SUMSETTESTER_H
