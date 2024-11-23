#include "../include/array_generator.h"
#include "random"


std::vector<int> ArrayGenerator::generate(int n) const {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> distrib(min, max);

    std::vector<int> array;
    array.reserve(n);
    for (int i = 0; i < n; ++i) {
        array.push_back(distrib(mt));
    }

    return array;
}

std::vector<int> DescArrayGenerator::generate(int n) const {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> distrib(min, max);

    std::vector<int> array;
    array.reserve(n);
    int a;
    for (int i = 0; i < n; ++i) {
        a = distrib(mt);
        array.push_back(a);
        distrib = std::uniform_int_distribution<>(min, a);
    }

    return array;
}

std::vector<int> AlmostDescArrayGenerator::generate(int n) const {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> distrib(min, max);

    std::vector<int> array;
    array.reserve(n);
    int a;
    for (int i = 0; i < n; ++i) {
        a = distrib(mt);
        array.push_back(a);
        distrib = std::uniform_int_distribution<>(min, a);
    }

    std::uniform_int_distribution<> k_distrib(1, std::max(2, n / 20));
    int k = k_distrib(mt);
    std::uniform_int_distribution<> idx_distrib(0, n - 1);
    for (int i = 0; i < k; ++i) {
        std::swap(array[idx_distrib(mt)], array[idx_distrib(mt)]);
    }

    return array;
}