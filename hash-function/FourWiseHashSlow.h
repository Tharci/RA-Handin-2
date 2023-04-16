//
// Created by tmarc on 29/03/2023.
//

#ifndef RA_HANDIN_2_FOURWISEHASHSLOW_H
#define RA_HANDIN_2_FOURWISEHASHSLOW_H

#include <cmath>

#include "../random-gen/RandomGen.h"
#include "../random-gen/PseudoRandomGen.h"


class FourWiseHashSlow {
    const unsigned long long p = (unsigned long long) pow(2, 31) - 1;
    const unsigned int l = 31;
    unsigned long long a, b, c, d;

public:

    explicit FourWiseHashSlow(const std::shared_ptr<RandomGen<unsigned long long>>& randomGen) {
        a = randomGen->random() % p;
        b = randomGen->random() % p;
        c = randomGen->random() % p;
        d = randomGen->random() % p;
    }

    FourWiseHashSlow(): FourWiseHashSlow(std::make_shared<PseudoRandomGen>()) {}

    [[nodiscard]] unsigned long long hash(const int& element) const {
        unsigned long long h;
        h = (a * element + b) % p;
        h = (h * element + c) % p;
        h = (h * element + d) % p;
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

#endif //RA_HANDIN_2_FOURWISEHASHSLOW_H
