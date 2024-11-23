#include "../include/sort_tester.h"
#include "chrono"

Test TestResults::mean() {
    int test_size = tests[0].size();
    Test tests_mean(test_size);

    for (int i = 0; i < test_size; ++i) {
        tests_mean[i].first = tests[0][i].first;
        for (auto & test : tests) {
            tests_mean[i].second += test[i].second;
        }
        tests_mean[i].second /= tests.size();
    }

    return tests_mean;
}

Test TestResults::deviation(double x) {
    int test_size = tests[0].size();
    Test tests_deviation(test_size);

    for (int i = 0; i < test_size; ++i) {
        tests_deviation[i].first = tests[0][i].first;
        for (auto & record : tests) {
            tests_deviation[i].second += abs(record[i].second - x);
        }
        tests_deviation[i].second /= tests.size();
    }

    return tests_deviation;
}

TestResults SortTester::run(const ArrayGenerator &generator) {
    std::vector<Test> tests;
    for (int i = 0; i < repetitions; ++i) {
        Test test;
        auto array = generator.generate(end_size);


        for (int size = start_size; size <= end_size; size += step) {

            std::vector<int> subarray(array.begin(), array.begin() + size);

            auto start = std::chrono::high_resolution_clock::now();

            sorter.sort(subarray.begin(), subarray.end());

            auto elapsed = std::chrono::high_resolution_clock::now() - start;

            long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
            test.emplace_back(size, msec);
        }
        tests.push_back(test);
    }
    return {tests};
}