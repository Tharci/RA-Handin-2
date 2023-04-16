//
// Created by tmarc on 29/03/2023.
//

#ifndef RA_HANDIN_2_HGHASHSLOW_H
#define RA_HANDIN_2_HGHASHSLOW_H

#include <cmath>
#include <memory>
#include "../random-gen/PseudoRandomGen.h"
#include "FourWiseHashSlow.h"


class HGHashSlow {
    unsigned int universe_size;
    unsigned int l;
    FourWiseHashSlow fourWiseHash {};

public:

    explicit HGHashSlow(unsigned int universe_size): universe_size(universe_size) {
        l = (int) std::log2(universe_size);
    }

    HGHashSlow() : HGHashSlow(1) {}

    [[nodiscard]] std::pair<unsigned int, short> hash(const int& element) const {
        auto k = fourWiseHash.hash(element);
        short g = 2 * (k & 1) - 1;
        auto h = (k >> 1) & (universe_size - 1);
        return {h, g};
    }

    [[nodiscard]] size_t size() const {
        return universe_size;
    }

    [[nodiscard]] std::pair<unsigned int, short> operator()(const int& element) const {
        return hash(element);
    }
};

#endif //RA_HANDIN_2_HGHASHSLOW_H
