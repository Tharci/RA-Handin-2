//
// Created by tmarc on 29/03/2023.
//

#ifndef RA_HANDIN_2_HGHASH_MULTIPLY_SHIFT_H
#define RA_HANDIN_2_HGHASH_MULTIPLY_SHIFT_H

#include <cmath>
#include <memory>
#include "../random-gen/PseudoRandomGen.h"
#include "MultiplyShiftHashTask9.h"

class HGHashMultiplyShift {
    unsigned int universe_size;
    MultiplyShiftHashTask9 hashFn {};

public:

    explicit HGHashMultiplyShift(unsigned int universe_size): universe_size(universe_size) {

    }

    HGHashMultiplyShift() : HGHashMultiplyShift(32) {}

    [[nodiscard]] std::pair<unsigned int, short> hash(const int& element) const {
        auto k = hashFn.hash(element);
        short g = 2 * (k & 1) - 1;
        unsigned int h = (k >> 1) & (universe_size - 1);
        return {h, g};
    }

    [[nodiscard]] size_t size() const {
        return universe_size;
    }

    [[nodiscard]] std::pair<unsigned int, short> operator()(const int& element) const {
        return hash(element);
    }
};

#endif //RA_HANDIN_2_HGHASH_MULTIPLY_SHIFT_H
