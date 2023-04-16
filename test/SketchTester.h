//
// Created by tmarc on 14/04/2023.
//

#ifndef RA_HANDIN_2_SKETCHTESTER_H
#define RA_HANDIN_2_SKETCHTESTER_H

#include "../sum-set/SketchSumSet.h"
#include "../sum-set/ChainingSumSet.h"
#include <cmath>
#include <fstream>


struct SketchTesterResult {
    unsigned long long r;
    double avgError;
    double maxError;

    friend std::ostream& operator<<(std::ostream& os, const SketchTesterResult& result) {
        os << "R: " << result.r << std::endl;
        os << "Avg error: " << result.avgError << std::endl;
        os << "Max error: " << result.maxError << std::endl;
        return os;
    }
};


class SketchTester {
    std::vector<SketchTesterResult> results;

public:
    SketchTester() = default;

    template <typename HashFn = HGHash>
    auto test(unsigned long long r, unsigned long long updateCount = 1000) {
        double avgError = 0;
        double maxError = 0;

        const int testCount = 1000;
        for (int j = 0; j < testCount; j++) {
            auto sketchSet = SketchSumSet<HashFn>(r);
            auto chainingSet = ChainingSumSet(updateCount);

            unsigned long long actualvalidquerystuff {};
            for (int i = 0; i < updateCount; i++) {
                sketchSet.update(i, i * i);
                chainingSet.update(i, i * i);
                actualvalidquerystuff += (unsigned long long) pow(i, 4);
            }

            auto a = sketchSet.query();
            auto b = chainingSet.query();

            double error;
            if (a > b) error = ((double)(a - b)) / b;
            else       error = ((double)(b - a)) / b;

            avgError += error;
            if (error > maxError) maxError = error;
        }

        avgError /= testCount;

        SketchTesterResult result = {
            .r = r,
            .avgError = avgError,
            .maxError = maxError
        };

        results.push_back(result);
        return result;
    }

    void dumpResults(const std::string& filename) {
        std::ofstream file;
        file.open(filename);

        file << "R\tAvg Error\tMax Error" << std::endl;
        for (const auto& result : results) {
            file << result.r << "\t" << result.avgError << "\t" << result.maxError << std::endl;
        }

        file.close();
    }
};

#endif //RA_HANDIN_2_SKETCHTESTER_H
