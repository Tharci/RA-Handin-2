//
// Created by tmarc on 29/03/2023.
//

#ifndef RA_HANDIN_2_SUMSET_H
#define RA_HANDIN_2_SUMSET_H

using ElemType = int;
using KeyType = int;
using RetType = unsigned long long;

class SumSet {
public:
    virtual void update(KeyType key, ElemType value) = 0;
    virtual RetType query() const = 0;
    virtual void clear() = 0;
};

#endif //RA_HANDIN_2_SUMSET_H
