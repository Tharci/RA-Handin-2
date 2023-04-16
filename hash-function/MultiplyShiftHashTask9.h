//
// Created by tmarc on 01/03/2023.
//

#ifndef PERFECT_HASHING_MULTIPLYSHIFTHASHTASK9_H
#define PERFECT_HASHING_MULTIPLYSHIFTHASHTASK9_H

#include "../random-gen/PseudoRandomGen.h"

#include <cmath>


class MultiplyShiftHashTask9 {
    unsigned long long a;
    unsigned long long b;

public:
    explicit MultiplyShiftHashTask9(const std::shared_ptr<RandomGen<unsigned long long>>& randomGen) {
        a = randomGen->random();
        b = randomGen->random();
    }

    MultiplyShiftHashTask9() : MultiplyShiftHashTask9(std::make_shared<PseudoRandomGen>()) {}

    [[nodiscard]] unsigned long long hash(const int& element) const {
        return (a * element + b) >> 33;
    }

    [[nodiscard]] unsigned long long operator()(const int& element) const {
        return hash(element);
    }
};

#endif //PERFECT_HASHING_MULTIPLYSHIFTHASHTASK9_H
