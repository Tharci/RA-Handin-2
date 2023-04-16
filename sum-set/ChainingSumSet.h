//
// Created by tmarc on 29/03/2023.
//

#ifndef RA_HANDIN_2_CHAININGSUMSET_H
#define RA_HANDIN_2_CHAININGSUMSET_H

#include <vector>
#include <list>
#include <algorithm>
#include <functional>

#include "SumSet.h"
#include "../hash-function/MultiplyShiftHash.h"
#include "../random-gen/PseudoRandomGen.h"

class ChainingSumSet: public SumSet {
    MultiplyShiftHash hashFunction;
    std::vector<std::list<std::pair<KeyType, ElemType>>> data;

public:
    explicit ChainingSumSet(size_t n): hashFunction(n, std::make_shared<PseudoRandomGen>()), data(n) {}

    void update(KeyType key, ElemType value) override {
        auto i = hashFunction(key);
        auto& list = data[i];

        for (auto& p: list) {
            if (p.first == key) {
                p.second += value;
                return;
            }
        }

        list.emplace_back(key, value);
    }

    [[nodiscard]] RetType query() const override {
        RetType r {};

        for (const auto& list: data) {
            for (const auto& p: list) {
                r += (RetType) p.second * p.second;
            }
        }

        return r;
    }

    void clear() override {
        data.clear();
    }
};

#endif //RA_HANDIN_2_CHAININGSUMSET_H
