//
// Created by tmarc on 29/03/2023.
//

#ifndef RA_HANDIN_2_SKETCHSUMSET_H
#define RA_HANDIN_2_SKETCHSUMSET_H

#include "SumSet.h"
#include "../hash-function/HGHash.h"


template <typename HashFn = HGHash>
class SketchSumSet: public SumSet {
    HashFn hashFn;
    std::vector<long long> data;

public:
    explicit SketchSumSet(size_t r): hashFn(r) {
        // TODO: Raise exc. if r is not a power of 2
        data.resize(hashFn.size());
    }

    void update(KeyType key, ElemType value) override {
        auto [h, g] = hashFn.hash(key);
        data[h] += g * value;
    }

    [[nodiscard]] RetType query() const override {
        RetType r {};
        for (auto v: data) {
            r += v * v;
        }
        return r;
    }

    void clear() override {
        data.clear();
    }
};

#endif //RA_HANDIN_2_SKETCHSUMSET_H
