//
// Created by tmarc on 29/03/2023.
//

#ifndef RA_HANDIN_2_FOURWISEHASH_H
#define RA_HANDIN_2_FOURWISEHASH_H

#include <cmath>

#include "../random-gen/RandomGen.h"
#include "../random-gen/PseudoRandomGen.h"


class FourWiseHash {
    const unsigned long long p = (unsigned long long) pow(2, 31) - 1;
    const unsigned int l = 31;
    unsigned long long a, b, c, d;

public:

    explicit FourWiseHash(const std::shared_ptr<RandomGen<unsigned long long>>& randomGen) {
        a = randomGen->random() % p;
        b = randomGen->random() % p;
        c = randomGen->random() % p;
        d = randomGen->random() % p;
    }

    FourWiseHash() : FourWiseHash(std::make_shared<PseudoRandomGen>()) {}

    constexpr static uint64_t mod_mersenne(uint64_t v, uint8_t m_exponent) {
        uint64_t m = (1 << m_exponent) - 1;
        auto res = (v & m) + (v >> m_exponent);
        if(res >= m) res -= m;
        return res;
    }

    [[nodiscard]] unsigned long long hash(const int& element) const {
        unsigned long long h;
        h = mod_mersenne(a * element + b, l);
        h = mod_mersenne(h * element + c, l);
        h = mod_mersenne(h * element + d, l);
        return h;
    }

    [[nodiscard]] size_t size() const {
        return p;
    }

    [[nodiscard]] short getC() const {
        return 4;
    }

    [[nodiscard]] unsigned long long operator()(const int& element) const {
        return hash(element);
    }
};

#endif //RA_HANDIN_2_FOURWISEHASH_H
