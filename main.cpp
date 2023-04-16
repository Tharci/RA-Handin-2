#include <iostream>
#include <string>
#include <memory>
#include <filesystem>

#include "hash-function/MultiplyShiftHash.h"
#include "hash-function/HGHash.h"
#include "hash-function/HGHashMultiplyShift.h"
#include "hash-function/HGHashSlow.h"
#include "test/HashTester.h"

#include "sum-set/ChainingSumSet.h"
#include "sum-set/SketchSumSet.h"
#include "test/SumSetTester.h"

#include "test/SketchTester.h"


int main() {
    std::cout << 1e6 << std::endl;

    auto multTime = HashTester(MultiplyShiftHash {}).test(1e6);
    auto hgTime = HashTester(HGHash {}).test(1e6);
    auto hgSlowtime = HashTester(HGHashSlow {}).test(1e6);

    std::cout << "Avg MulttiplyShiftHash: " << (double) multTime / 10e6 << "ns" << std::endl;
    std::cout << "Avg HGHash: " << (double) hgTime / 10e6 << "ns" << std::endl;
    std::cout << "Avg HGHashSlow: " << (double) hgSlowtime / 10e6 << "ns" << std::endl;

    const auto updateCount = 1e8;

    SumSetTester chainingTester;
    SumSetTester sketchTester7;
    SumSetTester sketchTester10;
    SumSetTester sketchTester20;

    for (int N = 6; N <= 28; N++) {
        std::cout << "########## N = " << N << " ##########" << std::endl;
        auto n = (unsigned long long) pow(2, N);

        auto set = ChainingSumSet(n);
        auto result = chainingTester.test(set, n, updateCount);
        std::cout << result << std::endl;

        auto set2 = SketchSumSet((size_t)pow(2, 7));
        auto result2 = sketchTester7.test(set2, n, updateCount);
        std::cout << result2 << std::endl;

        auto set3 = SketchSumSet((size_t)pow(2, 7));
        auto result3 = sketchTester10.test(set3, n, updateCount);
        std::cout << result3 << std::endl;

        auto set4 = SketchSumSet((size_t)pow(2, 7));
        auto result4 = sketchTester20.test(set4, n, updateCount);
        std::cout << result4 << std::endl;

        std::cout << std::endl;
    }


    // Delete files in output folder
    std::filesystem::remove_all("output-task7");
    std::filesystem::create_directory("output-task7");

    chainingTester.dumpResults("output-task7/chaining");
    sketchTester7.dumpResults("output-task7/sketch, r=2^7");
    sketchTester10.dumpResults("output-task7/sketch, r=2^10");
    sketchTester20.dumpResults("output-task7/sketch, r=2^20");


    SketchTester sketchTester;
    for (int i = 3; i <= 20; i++) {
        auto result = sketchTester.test<HGHash>((unsigned long long) pow(2, i));
        std::cout << result << std::endl;
    }

    // Delete files in output folder
    std::filesystem::remove_all("output-task8");
    std::filesystem::create_directory("output-task8");

    sketchTester.dumpResults("output-task8/sketch");


    SketchTester sketchTesterTask9;
    for (int i = 3; i <= 20; i++) {
        auto result = sketchTesterTask9.test<HGHashMultiplyShift>((unsigned long long) pow(2, i));
        std::cout << result << std::endl;
    }

    // Delete files in output folder
    std::filesystem::remove_all("output-task9");
    std::filesystem::create_directory("output-task9");

    sketchTesterTask9.dumpResults("output-task9/sketch");


    return 0;
}
