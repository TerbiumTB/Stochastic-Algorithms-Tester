#ifndef SET_3_ARRAY_GENERATOR_H
#define SET_3_ARRAY_GENERATOR_H

#include "vector"

class ArrayGenerator {
protected:
    int min = 0;
    int max = 6000;
public:
    ArrayGenerator() = default;
    virtual ~ArrayGenerator() = default;


    ArrayGenerator(int min, int max) : min(min), max(max) {};

    virtual std::vector<int> generate(int) const ;
};

class DescArrayGenerator : public ArrayGenerator {
public:
    std::vector<int> generate(int) const override;

};

class AlmostDescArrayGenerator : public ArrayGenerator {
public:
    std::vector<int> generate(int) const override;

};

#endif //SET_3_ARRAY_GENERATOR_H
